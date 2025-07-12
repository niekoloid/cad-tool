// JWW to SXF Format Converter

import {
  JWWDocument,
  JWWEntity,
  JWWGeometry,
  JWWLineGeometry,
  JWWArcGeometry,
  JWWCircleGeometry,
  JWWPolylineGeometry,
  JWWTextGeometry,
  JWWPointGeometry,
  JWWToSXFConversionOptions
} from '@/types/jww';

// SXFEntity type will be defined as needed for conversion

export class JWWConverter {
  private options: Required<JWWToSXFConversionOptions>;

  constructor(options: JWWToSXFConversionOptions = {}) {
    this.options = {
      scaleFactor: options.scaleFactor || 1.0,
      layerMapping: options.layerMapping || {},
      colorMapping: options.colorMapping || {},
      units: options.units || 'mm',
      precision: options.precision || 2
    };
  }

  convertToSXF(jwwDocument: JWWDocument): any[] {
    const sxfEntities: any[] = [];

    for (const entity of jwwDocument.entities) {
      const converted = this.convertEntity(entity);
      if (converted) {
        sxfEntities.push(converted);
      }
    }

    return sxfEntities;
  }

  private convertEntity(entity: JWWEntity): any | null {
    const baseProperties = {
      id: entity.id || `jww_${Date.now()}_${Math.random()}`,
      layer: this.getLayerName(entity.layer),
      color: this.getColorName(entity.color),
      lineType: this.getLineTypeName(entity.lineType),
      lineWidth: entity.lineWidth || 1
    };

    switch (entity.geometry.type) {
      case 'line':
        return this.convertLine(entity.geometry, baseProperties);
      
      case 'arc':
        return this.convertArc(entity.geometry, baseProperties);
      
      case 'circle':
        return this.convertCircle(entity.geometry, baseProperties);
      
      case 'polyline':
        return this.convertPolyline(entity.geometry, baseProperties);
      
      case 'text':
        return this.convertText(entity.geometry, baseProperties);
      
      case 'point':
        return this.convertPoint(entity.geometry, baseProperties);
      
      default:
        return null;
    }
  }

  private convertLine(geometry: JWWLineGeometry, baseProperties: any): any {
    return {
      ...baseProperties,
      type: 'line',
      geometry: {
        start: this.convertPoint3D(geometry.start),
        end: this.convertPoint3D(geometry.end)
      }
    };
  }

  private convertArc(geometry: JWWArcGeometry, baseProperties: any): any {
    // Convert angles from degrees to radians for calculation
    const startAngleRad = (geometry.startAngle * Math.PI) / 180;
    const endAngleRad = (geometry.endAngle * Math.PI) / 180;

    // Calculate start and end points
    const startPoint = {
      x: geometry.center.x + geometry.radius * Math.cos(startAngleRad),
      y: geometry.center.y + geometry.radius * Math.sin(startAngleRad)
    };

    const endPoint = {
      x: geometry.center.x + geometry.radius * Math.cos(endAngleRad),
      y: geometry.center.y + geometry.radius * Math.sin(endAngleRad)
    };

    return {
      ...baseProperties,
      type: 'arc',
      geometry: {
        center: this.convertPoint3D(geometry.center),
        radius: this.scaleValue(geometry.radius),
        startAngle: geometry.startAngle,
        endAngle: geometry.endAngle,
        startPoint: this.convertPoint3D(startPoint),
        endPoint: this.convertPoint3D(endPoint),
        clockwise: geometry.clockwise || false
      }
    };
  }

  private convertCircle(geometry: JWWCircleGeometry, baseProperties: any): any {
    return {
      ...baseProperties,
      type: 'circle',
      geometry: {
        center: this.convertPoint3D(geometry.center),
        radius: this.scaleValue(geometry.radius)
      }
    };
  }

  private convertPolyline(geometry: JWWPolylineGeometry, baseProperties: any): any {
    const points = geometry.points.map(point => this.convertPoint3D(point));

    return {
      ...baseProperties,
      type: 'polyline',
      geometry: {
        points,
        closed: geometry.closed || false,
        bulges: geometry.bulges || []
      }
    };
  }

  private convertText(geometry: JWWTextGeometry, baseProperties: any): any {
    return {
      ...baseProperties,
      type: 'text',
      geometry: {
        position: this.convertPoint3D(geometry.position),
        content: geometry.content,
        height: this.scaleValue(geometry.height),
        rotation: geometry.rotation || 0,
        style: {
          fontName: geometry.fontName || 'Arial',
          bold: geometry.style?.bold || false,
          italic: geometry.style?.italic || false,
          alignment: {
            horizontal: geometry.alignment?.horizontal || 'left',
            vertical: geometry.alignment?.vertical || 'bottom'
          }
        }
      }
    };
  }

  private convertPoint(geometry: JWWPointGeometry, baseProperties: any): any {
    return {
      ...baseProperties,
      type: 'point',
      geometry: {
        position: this.convertPoint3D(geometry.position),
        symbol: geometry.symbol || 'dot',
        size: this.scaleValue(geometry.size || 1)
      }
    };
  }

  private convertPoint3D(point: { x: number; y: number; z?: number }) {
    return {
      x: this.scaleValue(point.x),
      y: this.scaleValue(point.y),
      z: this.scaleValue(point.z || 0)
    };
  }

  private scaleValue(value: number): number {
    return parseFloat((value * this.options.scaleFactor).toFixed(this.options.precision));
  }

  private getLayerName(layerId: number): string {
    return this.options.layerMapping[layerId] || `Layer_${layerId}`;
  }

  private getColorName(colorId: number): string {
    const defaultColors: Record<number, string> = {
      0: 'black',
      1: 'red',
      2: 'green',
      3: 'blue',
      4: 'yellow',
      5: 'magenta',
      6: 'cyan',
      7: 'white'
    };

    return this.options.colorMapping[colorId] || defaultColors[colorId] || 'black';
  }

  private getLineTypeName(lineTypeId: number): string {
    const lineTypes: Record<number, string> = {
      0: 'solid',
      1: 'dashed',
      2: 'dotted',
      3: 'dash-dot',
      4: 'dash-dot-dot'
    };

    return lineTypes[lineTypeId] || 'solid';
  }

  // Extract geometries in a format compatible with the existing viewer
  extractGeometriesFromDocument(jwwDocument: JWWDocument): any[] {
    const geometries: any[] = [];

    for (const entity of jwwDocument.entities) {
      const geometry = this.convertEntityToGeometry(entity);
      if (geometry) {
        geometries.push(geometry);
      }
    }

    return geometries;
  }

  private convertEntityToGeometry(entity: JWWEntity): any | null {
    const baseId = entity.id || `jww_${Date.now()}_${Math.random()}`;
    const layerName = this.getLayerName(entity.layer);

    switch (entity.geometry.type) {
      case 'line':
        const lineGeom = entity.geometry as JWWLineGeometry;
        return {
          id: baseId,
          type: 'line',
          layer: layerName,
          geometry: {
            start: {
              x: this.scaleValue(lineGeom.start.x),
              y: this.scaleValue(lineGeom.start.y)
            },
            end: {
              x: this.scaleValue(lineGeom.end.x),
              y: this.scaleValue(lineGeom.end.y)
            }
          }
        };

      case 'circle':
        const circleGeom = entity.geometry as JWWCircleGeometry;
        return {
          id: baseId,
          type: 'circle',
          layer: layerName,
          geometry: {
            center: {
              x: this.scaleValue(circleGeom.center.x),
              y: this.scaleValue(circleGeom.center.y)
            },
            radius: this.scaleValue(circleGeom.radius)
          }
        };

      case 'arc':
        const arcGeom = entity.geometry as JWWArcGeometry;
        return {
          id: baseId,
          type: 'arc',
          layer: layerName,
          geometry: {
            center: {
              x: this.scaleValue(arcGeom.center.x),
              y: this.scaleValue(arcGeom.center.y)
            },
            radius: this.scaleValue(arcGeom.radius),
            startAngle: arcGeom.startAngle,
            endAngle: arcGeom.endAngle
          }
        };

      case 'polyline':
        const polylineGeom = entity.geometry as JWWPolylineGeometry;
        return {
          id: baseId,
          type: 'polyline',
          layer: layerName,
          geometry: {
            points: polylineGeom.points.map(p => ({
              x: this.scaleValue(p.x),
              y: this.scaleValue(p.y)
            })),
            closed: polylineGeom.closed || false
          }
        };

      case 'text':
        const textGeom = entity.geometry as JWWTextGeometry;
        return {
          id: baseId,
          type: 'text',
          layer: layerName,
          geometry: {
            position: {
              x: this.scaleValue(textGeom.position.x),
              y: this.scaleValue(textGeom.position.y)
            },
            content: textGeom.content,
            height: this.scaleValue(textGeom.height),
            rotation: textGeom.rotation || 0
          }
        };

      case 'point':
        const pointGeom = entity.geometry as JWWPointGeometry;
        return {
          id: baseId,
          type: 'point',
          layer: layerName,
          geometry: {
            position: {
              x: this.scaleValue(pointGeom.position.x),
              y: this.scaleValue(pointGeom.position.y)
            }
          }
        };

      default:
        return null;
    }
  }

  // Get document statistics
  getDocumentStats(jwwDocument: JWWDocument) {
    const stats = {
      totalEntities: jwwDocument.entities.length,
      entitiesByType: {} as Record<string, number>,
      entitiesByLayer: {} as Record<number, number>,
      bounds: {
        minX: Infinity,
        minY: Infinity,
        maxX: -Infinity,
        maxY: -Infinity
      },
      layers: jwwDocument.layers.length,
      version: jwwDocument.metadata?.version || 'Unknown'
    };

    // Count entities by type and layer
    for (const entity of jwwDocument.entities) {
      const type = entity.geometry.type;
      stats.entitiesByType[type] = (stats.entitiesByType[type] || 0) + 1;
      stats.entitiesByLayer[entity.layer] = (stats.entitiesByLayer[entity.layer] || 0) + 1;

      // Calculate bounds
      this.updateBoundsFromEntity(entity, stats.bounds);
    }

    return stats;
  }

  private updateBoundsFromEntity(entity: JWWEntity, bounds: any): void {
    const geometry = entity.geometry;

    switch (geometry.type) {
      case 'line':
        const lineGeom = geometry as JWWLineGeometry;
        this.updateBoundsFromPoint(lineGeom.start, bounds);
        this.updateBoundsFromPoint(lineGeom.end, bounds);
        break;

      case 'circle':
        const circleGeom = geometry as JWWCircleGeometry;
        const radius = circleGeom.radius;
        bounds.minX = Math.min(bounds.minX, circleGeom.center.x - radius);
        bounds.minY = Math.min(bounds.minY, circleGeom.center.y - radius);
        bounds.maxX = Math.max(bounds.maxX, circleGeom.center.x + radius);
        bounds.maxY = Math.max(bounds.maxY, circleGeom.center.y + radius);
        break;

      case 'arc':
        const arcGeom = geometry as JWWArcGeometry;
        // Simplified bounds calculation - could be more precise
        const arcRadius = arcGeom.radius;
        bounds.minX = Math.min(bounds.minX, arcGeom.center.x - arcRadius);
        bounds.minY = Math.min(bounds.minY, arcGeom.center.y - arcRadius);
        bounds.maxX = Math.max(bounds.maxX, arcGeom.center.x + arcRadius);
        bounds.maxY = Math.max(bounds.maxY, arcGeom.center.y + arcRadius);
        break;

      case 'polyline':
        const polylineGeom = geometry as JWWPolylineGeometry;
        for (const point of polylineGeom.points) {
          this.updateBoundsFromPoint(point, bounds);
        }
        break;

      case 'text':
      case 'point':
        const pointGeom = geometry as JWWTextGeometry | JWWPointGeometry;
        this.updateBoundsFromPoint(pointGeom.position, bounds);
        break;
    }
  }

  private updateBoundsFromPoint(point: { x: number; y: number }, bounds: any): void {
    bounds.minX = Math.min(bounds.minX, point.x);
    bounds.minY = Math.min(bounds.minY, point.y);
    bounds.maxX = Math.max(bounds.maxX, point.x);
    bounds.maxY = Math.max(bounds.maxY, point.y);
  }
}

// Utility function to create JWW converter
export function createJWWConverter(options?: JWWToSXFConversionOptions): JWWConverter {
  return new JWWConverter(options);
}