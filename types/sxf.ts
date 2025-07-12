// SXF Data Structure Types
export interface SXFPoint {
  x: number;
  y: number;
}

export interface SXFLayer {
  name: string;
  visible: boolean;
  color?: string;
}

export interface SXFSheet {
  name: string;
  type: number;
  orientation: number;
  width: number;
  height: number;
}

export interface SXFAttribute {
  projectName: string;
  companyName: string;
  companyType: string;
  drawingTitle: string;
  drawingNumber: string;
  drawingType: string;
  scale: string;
  year: number;
  month: number;
  day: number;
  contractor: string;
  owner: string;
}

// Geometric Elements
export interface SXFGeometryBase {
  layer: number;
  color: number;
  type: number;
  lineWidth: number;
}

export interface SXFPointMarker extends SXFGeometryBase {
  position: SXFPoint;
  markerCode: number;
  rotateAngle: number;
  scale: number;
}

export interface SXFLine extends SXFGeometryBase {
  start: SXFPoint;
  end: SXFPoint;
}

export interface SXFPolyline extends SXFGeometryBase {
  points: SXFPoint[];
}

export interface SXFCircle extends SXFGeometryBase {
  center: SXFPoint;
  radius: number;
}

export interface SXFArc extends SXFGeometryBase {
  center: SXFPoint;
  radius: number;
  direction: number;
  startAngle: number;
  endAngle: number;
}

export interface SXFEllipse extends SXFGeometryBase {
  center: SXFPoint;
  radiusX: number;
  radiusY: number;
  rotationAngle: number;
}

export interface SXFEllipseArc extends SXFEllipse {
  direction: number;
  startAngle: number;
  endAngle: number;
}

export interface SXFText extends SXFGeometryBase {
  position: SXFPoint;
  text: string;
  font: string;
  height: number;
  rotationAngle: number;
}

// Union type for all geometry elements
export type SXFGeometry = 
  | SXFPointMarker 
  | SXFLine 
  | SXFPolyline 
  | SXFCircle 
  | SXFArc 
  | SXFEllipse 
  | SXFEllipseArc 
  | SXFText;

// Complete SXF Document Structure
export interface SXFDocument {
  sheet: SXFSheet;
  layers: SXFLayer[];
  attributes: SXFAttribute;
  geometries: SXFGeometry[];
  predefinedColors: string[];
  userDefinedColors: { red: number; green: number; blue: number }[];
  lineTypes: string[];
  lineWidths: number[];
  fonts: string[];
}