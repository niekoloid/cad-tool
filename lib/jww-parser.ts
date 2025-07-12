// JWW (Jw_cad Windows) File Format Parser

import {
  JWWDocument,
  JWWHeader,
  JWWProjectInfo,
  JWWLayer,
  JWWEntity,
  JWWEntityType,
  JWWSettings,
  JWWPoint,
  JWWGeometry,
  JWWLineGeometry,
  JWWArcGeometry,
  JWWCircleGeometry,
  JWWPolylineGeometry,
  JWWTextGeometry,
  JWWPointGeometry,
  JWWParseResult,
  JWWBinaryHeader,
  JWW_SIGNATURE,
  JWW_HEADER_SIZE,
  JWW_ENTITY_TYPES
} from '@/types/jww';

export class JWWParser {
  private dataView!: DataView;
  private offset: number = 0;
  private littleEndian: boolean = true; // JWW files use little-endian format

  async parseFile(file: File): Promise<JWWParseResult> {
    try {
      const buffer = await file.arrayBuffer();
      return this.parseArrayBuffer(buffer);
    } catch (error) {
      return {
        success: false,
        error: `Failed to read file: ${error instanceof Error ? error.message : 'Unknown error'}`
      };
    }
  }

  async parseArrayBuffer(buffer: ArrayBuffer): Promise<JWWParseResult> {
    try {
      this.dataView = new DataView(buffer);
      this.offset = 0;

      // Parse and validate header
      const header = this.parseHeader();
      if (!header) {
        return {
          success: false,
          error: 'Invalid JWW file: Header signature not found'
        };
      }

      // Parse document components
      const projectInfo = this.parseProjectInfo();
      const layers = this.parseLayers();
      const entities = this.parseEntities();
      const settings = this.parseSettings();

      const document: JWWDocument = {
        header,
        projectInfo,
        layers,
        entities,
        settings,
        metadata: {
          version: this.getVersionString(header.version),
          parsedAt: new Date()
        }
      };

      const warnings = this.validateDocument(document);

      return {
        success: true,
        document,
        warnings: warnings.length > 0 ? warnings : undefined
      };

    } catch (error) {
      return {
        success: false,
        error: `Failed to parse JWW file: ${error instanceof Error ? error.message : 'Unknown error'}`
      };
    }
  }

  private parseHeader(): JWWHeader | null {
    try {
      // Read signature (8 bytes)
      const signatureBytes = new Uint8Array(this.dataView.buffer, this.offset, 8);
      const signature = new TextDecoder('ascii').decode(signatureBytes);
      this.offset += 8;

      if (signature !== JWW_SIGNATURE) {
        return null;
      }

      // Read version (4 bytes, DWORD)
      const version = this.dataView.getUint32(this.offset, this.littleEndian);
      this.offset += 4;

      // Read additional header data if available
      const fileSize = this.dataView.byteLength;
      
      return {
        signature,
        version,
        fileSize,
        dataOffset: this.offset
      };

    } catch (error) {
      return null;
    }
  }

  private parseProjectInfo(): JWWProjectInfo {
    const projectInfo: JWWProjectInfo = {};

    try {
      // Try to read memo string (CString format)
      const memo = this.readCString();
      if (memo) {
        projectInfo.memo = memo;
      }

      // Skip to drawing size info if available
      // This is a simplified implementation - actual JWW format may vary
      if (this.hasMoreData()) {
        const width = this.readFloat64();
        const height = this.readFloat64();
        
        if (width > 0 && height > 0) {
          projectInfo.drawingSize = {
            width,
            height,
            units: 'mm' // Default unit
          };
        }
      }

    } catch (error) {
      // Continue parsing even if project info fails
    }

    return projectInfo;
  }

  private parseLayers(): JWWLayer[] {
    const layers: JWWLayer[] = [];

    try {
      // Default layers - JWW typically has 16 layers
      for (let i = 0; i < 16; i++) {
        layers.push({
          id: i,
          name: `Layer ${i}`,
          visible: true,
          color: i % 8, // Cycle through basic colors
          lineType: 0,  // Solid line
          lineWidth: 1,
          printable: true
        });
      }

    } catch (error) {
      // Return default layers on error
    }

    return layers;
  }

  private parseEntities(): JWWEntity[] {
    const entities: JWWEntity[] = [];

    try {
      while (this.hasMoreData()) {
        const entity = this.parseEntity();
        if (entity) {
          entities.push(entity);
        } else {
          // Skip unknown data
          if (this.hasMoreData()) {
            this.offset += 1;
          } else {
            break;
          }
        }
      }

    } catch (error) {
      // Return entities parsed so far
    }

    return entities;
  }

  private parseEntity(): JWWEntity | null {
    try {
      // Read entity header
      if (!this.hasMoreData(8)) {
        return null;
      }

      const entityType = this.dataView.getUint16(this.offset, this.littleEndian);
      this.offset += 2;

      const layer = this.dataView.getUint8(this.offset);
      this.offset += 1;

      const color = this.dataView.getUint8(this.offset);
      this.offset += 1;

      const lineType = this.dataView.getUint8(this.offset);
      this.offset += 1;

      const lineWidth = this.dataView.getUint8(this.offset);
      this.offset += 1;

      const dataSize = this.dataView.getUint16(this.offset, this.littleEndian);
      this.offset += 2;

      // Parse geometry based on entity type
      const geometry = this.parseEntityGeometry(entityType, dataSize);
      if (!geometry) {
        // Skip this entity
        this.offset += dataSize;
        return null;
      }

      return {
        id: `entity_${Date.now()}_${Math.random()}`,
        type: this.getEntityTypeName(entityType),
        layer,
        color,
        lineType,
        lineWidth,
        geometry
      };

    } catch (error) {
      return null;
    }
  }

  private parseEntityGeometry(entityType: number, dataSize: number): JWWGeometry | null {
    const startOffset = this.offset;

    try {
      switch (entityType) {
        case JWW_ENTITY_TYPES.LINE:
          return this.parseLineGeometry();
        
        case JWW_ENTITY_TYPES.ARC:
          return this.parseArcGeometry();
        
        case JWW_ENTITY_TYPES.CIRCLE:
          return this.parseCircleGeometry();
        
        case JWW_ENTITY_TYPES.POLYLINE:
          return this.parsePolylineGeometry();
        
        case JWW_ENTITY_TYPES.TEXT:
          return this.parseTextGeometry();
        
        case JWW_ENTITY_TYPES.POINT:
          return this.parsePointGeometry();
        
        default:
          // Skip unknown entity type
          this.offset = startOffset + dataSize;
          return null;
      }

    } catch (error) {
      // Reset offset and skip entity
      this.offset = startOffset + dataSize;
      return null;
    }
  }

  private parseLineGeometry(): JWWLineGeometry {
    const start = this.readPoint();
    const end = this.readPoint();
    
    return {
      type: 'line',
      start,
      end
    };
  }

  private parseArcGeometry(): JWWArcGeometry {
    const center = this.readPoint();
    const radius = this.readFloat64();
    const startAngle = this.readFloat64();
    const endAngle = this.readFloat64();
    
    return {
      type: 'arc',
      center,
      radius,
      startAngle,
      endAngle
    };
  }

  private parseCircleGeometry(): JWWCircleGeometry {
    const center = this.readPoint();
    const radius = this.readFloat64();
    
    return {
      type: 'circle',
      center,
      radius
    };
  }

  private parsePolylineGeometry(): JWWPolylineGeometry {
    const pointCount = this.dataView.getUint16(this.offset, this.littleEndian);
    this.offset += 2;

    const points: JWWPoint[] = [];
    for (let i = 0; i < pointCount; i++) {
      points.push(this.readPoint());
    }

    const closed = this.dataView.getUint8(this.offset) !== 0;
    this.offset += 1;

    return {
      type: 'polyline',
      points,
      closed
    };
  }

  private parseTextGeometry(): JWWTextGeometry {
    const position = this.readPoint();
    const height = this.readFloat64();
    const rotation = this.readFloat64();
    const content = this.readCString() || '';

    return {
      type: 'text',
      position,
      content,
      height,
      rotation
    };
  }

  private parsePointGeometry(): JWWPointGeometry {
    const position = this.readPoint();
    
    return {
      type: 'point',
      position
    };
  }

  private parseSettings(): JWWSettings {
    return {
      units: 'mm',
      precision: 2,
      gridSpacing: 10,
      snapSettings: {
        enabled: true,
        gridSnap: true,
        pointSnap: true,
        lineSnap: true,
        tolerance: 1.0
      },
      viewSettings: {
        zoom: 1.0,
        panX: 0,
        panY: 0,
        backgroundColor: 0
      }
    };
  }

  // Utility methods
  private readPoint(): JWWPoint {
    const x = this.readFloat64();
    const y = this.readFloat64();
    const z = this.hasMoreData(8) ? this.readFloat64() : 0;
    
    return { x, y, z };
  }

  private readFloat64(): number {
    const value = this.dataView.getFloat64(this.offset, this.littleEndian);
    this.offset += 8;
    return value;
  }

  private readFloat32(): number {
    const value = this.dataView.getFloat32(this.offset, this.littleEndian);
    this.offset += 4;
    return value;
  }

  private readCString(): string | null {
    try {
      // Read string length (DWORD)
      const length = this.dataView.getUint32(this.offset, this.littleEndian);
      this.offset += 4;

      if (length === 0 || length > 1000) { // Sanity check
        return null;
      }

      // Read string data
      const bytes = new Uint8Array(this.dataView.buffer, this.offset, length);
      this.offset += length;

      // Convert to string (assuming Shift-JIS or UTF-8)
      return new TextDecoder('utf-8').decode(bytes);

    } catch (error) {
      return null;
    }
  }

  private hasMoreData(bytes: number = 1): boolean {
    return this.offset + bytes <= this.dataView.byteLength;
  }

  private getEntityTypeName(entityType: number): JWWEntityType {
    const typeMap: Record<number, JWWEntityType> = {
      [JWW_ENTITY_TYPES.LINE]: 'line',
      [JWW_ENTITY_TYPES.ARC]: 'arc',
      [JWW_ENTITY_TYPES.CIRCLE]: 'circle',
      [JWW_ENTITY_TYPES.POLYLINE]: 'polyline',
      [JWW_ENTITY_TYPES.TEXT]: 'text',
      [JWW_ENTITY_TYPES.POINT]: 'point',
      [JWW_ENTITY_TYPES.DIMENSION]: 'dimension',
      [JWW_ENTITY_TYPES.SOLID]: 'solid',
      [JWW_ENTITY_TYPES.BLOCK]: 'block',
      [JWW_ENTITY_TYPES.HATCH]: 'hatch',
      [JWW_ENTITY_TYPES.SPLINE]: 'spline'
    };

    return typeMap[entityType] || 'line';
  }

  private getVersionString(version: number): string {
    // Convert internal version number to readable format
    const major = Math.floor(version / 100);
    const minor = version % 100;
    return `${major}.${minor.toString().padStart(2, '0')}`;
  }

  private validateDocument(document: JWWDocument): string[] {
    const warnings: string[] = [];

    if (!document.header.signature || document.header.signature !== JWW_SIGNATURE) {
      warnings.push('Invalid JWW file signature');
    }

    if (document.entities.length === 0) {
      warnings.push('No entities found in JWW file');
    }

    if (document.layers.length === 0) {
      warnings.push('No layers found in JWW file');
    }

    // Check for entities on invalid layers
    const validLayers = new Set(document.layers.map(l => l.id));
    const invalidLayerEntities = document.entities.filter(e => !validLayers.has(e.layer));
    if (invalidLayerEntities.length > 0) {
      warnings.push(`${invalidLayerEntities.length} entities reference invalid layers`);
    }

    return warnings;
  }
}

// Utility function to create JWW parser
export function createJWWParser(): JWWParser {
  return new JWWParser();
}