// P21 Data Conversion Layer
import { CADDocument, CADLayer, CADGeometry, CADMetadata } from '@/types/p21';
import { P21WASMParser, getP21Parser } from './p21-wasm';

export interface ConversionOptions {
  coordinateSystem?: 'right-handed' | 'left-handed';
  unitScale?: number;
  precision?: number;
}

export class P21Converter {
  private options: ConversionOptions;

  constructor(options: ConversionOptions = {}) {
    this.options = {
      coordinateSystem: 'right-handed',
      unitScale: 1.0,
      precision: 0.001,
      ...options
    };
  }

  async convertP21File(fileContent: string, filename: string): Promise<CADDocument> {
    try {
      // Parse using WebAssembly if available, otherwise fall back to mock
      let parsedData;
      
      try {
        const parser = await getP21Parser();
        const result = await parser.parseP21File(fileContent);
        
        if (result.success && result.data) {
          parsedData = result.data;
        } else {
          throw new Error(result.error || 'WASM parsing failed');
        }
      } catch (wasmError) {
        console.warn('WASM parsing failed, using fallback parser:', wasmError);
        parsedData = await this.fallbackParser(fileContent);
      }

      // Convert to CADDocument format
      const document: CADDocument = {
        format: 'P21',
        originalData: parsedData,
        title: filename,
        layers: this.convertLayers(parsedData.layers || []),
        geometries: this.convertGeometries(parsedData.geometries || []),
        metadata: this.extractMetadata(fileContent, filename)
      };

      return document;
    } catch (error) {
      console.error('P21 conversion error:', error);
      throw new Error(`Failed to convert P21 file: ${error}`);
    }
  }

  private async fallbackParser(fileContent: string): Promise<any> {
    // Simple text-based P21 parser for basic geometry extraction
    const lines = fileContent.split('\n').map(line => line.trim());
    
    const entities: any[] = [];
    const header: any = {};
    
    let inDataSection = false;
    
    for (const line of lines) {
      if (line.startsWith('HEADER;')) {
        inDataSection = false;
        continue;
      }
      
      if (line.startsWith('DATA;')) {
        inDataSection = true;
        continue;
      }
      
      if (line.startsWith('ENDSEC;')) {
        continue;
      }
      
      if (inDataSection && line.startsWith('#')) {
        const entity = this.parseP21Entity(line);
        if (entity) {
          entities.push(entity);
        }
      }
    }

    return {
      layers: [{ name: 'Default', visible: true, color: '#000000' }],
      geometries: this.extractGeometriesFromEntities(entities),
      colors: ['black', 'red', 'green', 'blue'],
      lineTypes: ['solid']
    };
  }

  private parseP21Entity(line: string): any | null {
    const match = line.match(/^#(\d+)\s*=\s*([A-Z_]+)\s*\((.*)\)\s*;?$/);
    if (!match) return null;

    const [, id, entityType, params] = match;
    
    return {
      id: parseInt(id),
      type: entityType,
      parameters: this.parseParameters(params)
    };
  }

  private parseParameters(paramStr: string): any[] {
    // Enhanced parameter parser for P21 format
    const params: any[] = [];
    let current = '';
    let depth = 0;
    let inString = false;
    
    for (let i = 0; i < paramStr.length; i++) {
      const char = paramStr[i];
      
      if (char === "'" && paramStr[i-1] !== '\\') {
        inString = !inString;
        current += char;
      } else if (!inString) {
        if (char === '(') {
          depth++;
          current += char;
        } else if (char === ')') {
          depth--;
          current += char;
        } else if (char === ',' && depth === 0) {
          const value = this.parseValue(current.trim());
          if (value !== undefined) {
            params.push(value);
          }
          current = '';
        } else {
          current += char;
        }
      } else {
        current += char;
      }
    }
    
    if (current.trim()) {
      const value = this.parseValue(current.trim());
      if (value !== undefined) {
        params.push(value);
      }
    }
    
    return params;
  }

  private parseValue(value: string): any {
    value = value.trim();
    
    if (value.startsWith("'") && value.endsWith("'")) {
      return value.slice(1, -1); // String
    } else if (value.startsWith('#')) {
      return parseInt(value.slice(1)); // Reference
    } else if (value === '$') {
      return null; // Undefined
    } else if (value.startsWith('(') && value.endsWith(')')) {
      // Parse coordinate tuple or list
      const innerContent = value.slice(1, -1);
      if (innerContent.includes('#')) {
        // List of references like (#150,#160,#170,#180,#190)
        return innerContent.split(',').map(ref => {
          const trimmed = ref.trim();
          return trimmed.startsWith('#') ? parseInt(trimmed.slice(1)) : trimmed;
        });
      } else {
        // Coordinate values like (10.000000,-30.000000)
        return innerContent.split(',').map(coord => parseFloat(coord.trim()));
      }
    } else if (!isNaN(parseFloat(value))) {
      return parseFloat(value); // Number
    } else if (value === '.T.') {
      return true; // Boolean true
    } else if (value === '.F.') {
      return false; // Boolean false
    } else {
      return value; // Enum or other
    }
  }

  private extractGeometriesFromEntities(entities: any[]): any[] {
    const geometries: any[] = [];
    
    // Create a map of entities by ID for reference resolution
    const entityMap = new Map();
    entities.forEach(entity => {
      entityMap.set(entity.id, entity);
    });
    
    // Only process geometric entities (not individual points that are part of other geometries)
    const referencedPoints = new Set();
    
    // First pass: find all points that are referenced by other geometries
    for (const entity of entities) {
      if (entity.type === 'POLYLINE' && entity.parameters.length >= 2 && Array.isArray(entity.parameters[1])) {
        entity.parameters[1].forEach((ref: any) => {
          if (typeof ref === 'number') {
            referencedPoints.add(ref);
          }
        });
      }
    }
    
    for (const entity of entities) {
      // Skip standalone points that are part of polylines
      if (entity.type === 'CARTESIAN_POINT' && referencedPoints.has(entity.id)) {
        continue;
      }
      
      const geometry = this.convertEntityToGeometry(entity, entityMap);
      if (geometry) {
        geometries.push(geometry);
      }
    }
    
    return geometries;
  }

  private convertEntityToGeometry(entity: any, entityMap: Map<number, any>): any | null {
    switch (entity.type) {
      case 'CARTESIAN_POINT':
        if (entity.parameters.length >= 2 && Array.isArray(entity.parameters[1])) {
          const coords = entity.parameters[1];
          return {
            id: `point_${entity.id}`,
            type: 'point',
            layer: 'default',
            geometry: {
              x: coords[0] || 0,
              y: coords[1] || 0,
              z: coords[2] || 0
            }
          };
        }
        return null;
      
      case 'POLYLINE':
        if (entity.parameters.length >= 2 && Array.isArray(entity.parameters[1])) {
          const pointRefs = entity.parameters[1];
          const points: any[] = [];
          
          for (const ref of pointRefs) {
            if (typeof ref === 'number' && entityMap.has(ref)) {
              const pointEntity = entityMap.get(ref);
              if (pointEntity.type === 'CARTESIAN_POINT' && 
                  pointEntity.parameters.length >= 2 && 
                  Array.isArray(pointEntity.parameters[1])) {
                const coords = pointEntity.parameters[1];
                points.push({
                  x: coords[0] || 0,
                  y: coords[1] || 0
                });
              }
            }
          }
          
          if (points.length >= 2) {
            return {
              id: `polyline_${entity.id}`,
              type: 'polyline',
              layer: 'default',
              geometry: {
                points: points
              }
            };
          }
        }
        return null;
      
      case 'LINE':
        // LINE has a point and a vector (VECTOR(direction, magnitude))
        if (entity.parameters.length >= 2) {
          const startPointRef = entity.parameters[0];
          const vectorRef = entity.parameters[1];
          
          let startPoint = { x: 0, y: 0 };
          let endPoint = { x: 100, y: 100 };
          
          // Resolve start point
          if (typeof startPointRef === 'number' && entityMap.has(startPointRef)) {
            const pointEntity = entityMap.get(startPointRef);
            if (pointEntity.type === 'CARTESIAN_POINT' && 
                pointEntity.parameters.length >= 2 && 
                Array.isArray(pointEntity.parameters[1])) {
              const coords = pointEntity.parameters[1];
              startPoint = { x: coords[0] || 0, y: coords[1] || 0 };
            }
          }
          
          // Try to resolve vector for proper end point calculation
          if (typeof vectorRef === 'number' && entityMap.has(vectorRef)) {
            const vectorEntity = entityMap.get(vectorRef);
            if (vectorEntity.type === 'VECTOR' && vectorEntity.parameters.length >= 2) {
              const directionRef = vectorEntity.parameters[0];
              const magnitude = vectorEntity.parameters[1];
              
              if (typeof directionRef === 'number' && entityMap.has(directionRef)) {
                const directionEntity = entityMap.get(directionRef);
                if (directionEntity.type === 'DIRECTION' && 
                    directionEntity.parameters.length >= 1 && 
                    Array.isArray(directionEntity.parameters[0])) {
                  const direction = directionEntity.parameters[0];
                  const dx = direction[0] || 0;
                  const dy = direction[1] || 0;
                  
                  endPoint = {
                    x: startPoint.x + dx * magnitude,
                    y: startPoint.y + dy * magnitude
                  };
                }
              }
            }
          } else {
            // Fallback - create a horizontal line
            endPoint = { x: startPoint.x + 100, y: startPoint.y };
          }
          
          return {
            id: `line_${entity.id}`,
            type: 'line',
            layer: 'default',
            geometry: {
              start: startPoint,
              end: endPoint
            }
          };
        }
        return null;
      
      case 'TRIMMED_CURVE':
        // TRIMMED_CURVE references a base curve and trim parameters
        if (entity.parameters.length >= 3) {
          const baseCurveRef = entity.parameters[1];
          const startTrimRef = entity.parameters[2];
          const endTrimRef = entity.parameters[3];
          
          // Try to resolve the base curve (could be LINE)
          if (typeof baseCurveRef === 'number' && entityMap.has(baseCurveRef)) {
            const baseCurve = entityMap.get(baseCurveRef);
            if (baseCurve.type === 'LINE') {
              // Extract line geometry
              return this.convertEntityToGeometry(baseCurve, entityMap);
            }
          }
        }
        return null;
      
      case 'CIRCLE':
        return {
          id: `circle_${entity.id}`,
          type: 'circle',
          layer: 'default',
          geometry: {
            center: { x: 0, y: 0 }, // Would need to resolve placement reference
            radius: entity.parameters[1] || 25
          }
        };
      
      default:
        return null;
    }
  }

  private convertLayers(rawLayers: any[]): CADLayer[] {
    return rawLayers.map((layer, index) => ({
      id: `layer_${index}`,
      name: layer.name || `Layer ${index + 1}`,
      visible: layer.visible !== false,
      color: layer.color || '#000000',
      items: []
    }));
  }

  private convertGeometries(rawGeometries: any[]): CADGeometry[] {
    return rawGeometries.map((geom, index) => {
      const converted = this.transformCoordinates(geom);
      
      return {
        id: geom.id || `geom_${index}`,
        type: geom.type || 'line',
        layer: geom.layer || 'default',
        style: {
          color: geom.style?.color || '#000000',
          lineWidth: geom.style?.lineWidth || 1,
          lineType: geom.style?.lineType || 'solid'
        },
        geometry: converted.geometry
      };
    });
  }

  private transformCoordinates(geometry: any): any {
    // Apply coordinate system transformations
    const transformed = { ...geometry };
    
    if (this.options.coordinateSystem === 'left-handed') {
      // Convert from right-handed to left-handed coordinate system
      transformed.geometry = this.flipYCoordinates(geometry.geometry);
    }
    
    if (this.options.unitScale !== 1.0) {
      transformed.geometry = this.scaleCoordinates(transformed.geometry, this.options.unitScale!);
    }
    
    return transformed;
  }

  private flipYCoordinates(geom: any): any {
    const flipped = { ...geom };
    
    if (geom.start && geom.end) {
      // Line
      flipped.start = { ...geom.start, y: -geom.start.y };
      flipped.end = { ...geom.end, y: -geom.end.y };
    } else if (geom.center) {
      // Circle/Arc
      flipped.center = { ...geom.center, y: -geom.center.y };
    } else if (geom.points) {
      // Polyline
      flipped.points = geom.points.map((p: any) => ({ ...p, y: -p.y }));
    }
    
    return flipped;
  }

  private scaleCoordinates(geom: any, scale: number): any {
    const scaled = { ...geom };
    
    if (geom.start && geom.end) {
      // Line
      scaled.start = { x: geom.start.x * scale, y: geom.start.y * scale };
      scaled.end = { x: geom.end.x * scale, y: geom.end.y * scale };
    } else if (geom.center) {
      // Circle/Arc
      scaled.center = { x: geom.center.x * scale, y: geom.center.y * scale };
      if (geom.radius) scaled.radius = geom.radius * scale;
    } else if (geom.points) {
      // Polyline
      scaled.points = geom.points.map((p: any) => ({ x: p.x * scale, y: p.y * scale }));
    }
    
    return scaled;
  }

  private extractMetadata(fileContent: string, filename: string): CADMetadata {
    const metadata: CADMetadata = {
      format: 'STEP Part21',
      title: filename,
      created: new Date()
    };

    // Extract header information
    const headerMatch = fileContent.match(/HEADER;([\s\S]*?)ENDSEC;/);
    if (headerMatch) {
      const headerContent = headerMatch[1];
      
      // Extract file description
      const descMatch = headerContent.match(/FILE_DESCRIPTION\s*\(\s*\('([^']+)'/);
      if (descMatch) {
        metadata.title = descMatch[1];
      }
      
      // Extract author
      const authorMatch = headerContent.match(/FILE_NAME\s*\([^,]*,\s*'([^']*)',\s*\(([^)]*)\)/);
      if (authorMatch) {
        const authors = authorMatch[2].replace(/'/g, '').split(',');
        if (authors.length > 0) {
          metadata.author = authors[0].trim();
        }
      }
      
      // Extract organization
      const orgMatch = headerContent.match(/\(([^)]*'[^']*'[^)]*)\)/);
      if (orgMatch) {
        const orgData = orgMatch[1];
        const orgNameMatch = orgData.match(/'([^']+)'/);
        if (orgNameMatch) {
          metadata.organization = orgNameMatch[1];
        }
      }
    }

    return metadata;
  }
}

// Utility function to create converter with default options
export function createP21Converter(options?: ConversionOptions): P21Converter {
  return new P21Converter(options);
}