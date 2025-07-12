// JWW (Jw_cad Windows) File Format Type Definitions

export interface JWWDocument {
  header: JWWHeader;
  projectInfo: JWWProjectInfo;
  layers: JWWLayer[];
  entities: JWWEntity[];
  settings: JWWSettings;
  metadata?: {
    version: string;
    filename?: string;
    parsedAt: Date;
  };
}

export interface JWWHeader {
  signature: string; // "JwwData._"
  version: number; // Internal version number (e.g., 700 for v7.02)
  fileSize?: number;
  dataOffset?: number;
}

export interface JWWProjectInfo {
  title?: string;
  memo?: string;
  author?: string;
  company?: string;
  createdDate?: Date;
  modifiedDate?: Date;
  drawingSize?: JWWDrawingSize;
}

export interface JWWDrawingSize {
  width: number;
  height: number;
  units: 'mm' | 'cm' | 'm' | 'inch' | 'feet';
  paperSize?: 'A0' | 'A1' | 'A2' | 'A3' | 'A4' | 'custom';
}

export interface JWWLayer {
  id: number;
  name: string;
  visible: boolean;
  color: number;
  lineType: number;
  lineWidth: number;
  printable: boolean;
}

export interface JWWSettings {
  units: 'mm' | 'cm' | 'm' | 'inch' | 'feet';
  precision: number;
  gridSpacing?: number;
  snapSettings?: JWWSnapSettings;
  viewSettings?: JWWViewSettings;
}

export interface JWWSnapSettings {
  enabled: boolean;
  gridSnap: boolean;
  pointSnap: boolean;
  lineSnap: boolean;
  tolerance: number;
}

export interface JWWViewSettings {
  zoom: number;
  panX: number;
  panY: number;
  backgroundColor: number;
}

export interface JWWEntity {
  id?: string;
  type: JWWEntityType;
  layer: number;
  color: number;
  lineType: number;
  lineWidth: number;
  geometry: JWWGeometry;
  attributes?: JWWEntityAttributes;
}

export type JWWEntityType = 
  | 'line'
  | 'arc'
  | 'circle'
  | 'polyline'
  | 'text'
  | 'dimension'
  | 'point'
  | 'solid'
  | 'block'
  | 'hatch'
  | 'spline';

export interface JWWEntityAttributes {
  visible?: boolean;
  locked?: boolean;
  selected?: boolean;
  groupId?: string;
  userData?: Record<string, any>;
}

export type JWWGeometry = 
  | JWWLineGeometry
  | JWWArcGeometry  
  | JWWCircleGeometry
  | JWWPolylineGeometry
  | JWWTextGeometry
  | JWWPointGeometry
  | JWWSolidGeometry
  | JWWDimensionGeometry;

export interface JWWPoint {
  x: number;
  y: number;
  z?: number;
}

export interface JWWLineGeometry {
  type: 'line';
  start: JWWPoint;
  end: JWWPoint;
}

export interface JWWArcGeometry {
  type: 'arc';
  center: JWWPoint;
  radius: number;
  startAngle: number; // in degrees
  endAngle: number;   // in degrees
  clockwise?: boolean;
}

export interface JWWCircleGeometry {
  type: 'circle';
  center: JWWPoint;
  radius: number;
}

export interface JWWPolylineGeometry {
  type: 'polyline';
  points: JWWPoint[];
  closed?: boolean;
  bulges?: number[]; // For arc segments between points
}

export interface JWWTextGeometry {
  type: 'text';
  position: JWWPoint;
  content: string;
  height: number;
  rotation?: number; // in degrees
  fontName?: string;
  style?: JWWTextStyle;
  alignment?: JWWTextAlignment;
}

export interface JWWTextStyle {
  bold?: boolean;
  italic?: boolean;
  underline?: boolean;
  strikethrough?: boolean;
}

export interface JWWTextAlignment {
  horizontal: 'left' | 'center' | 'right';
  vertical: 'top' | 'middle' | 'bottom';
}

export interface JWWPointGeometry {
  type: 'point';
  position: JWWPoint;
  symbol?: string;
  size?: number;
}

export interface JWWSolidGeometry {
  type: 'solid';
  boundary: JWWPoint[];
  fillPattern?: number;
  fillColor?: number;
}

export interface JWWDimensionGeometry {
  type: 'dimension';
  dimensionType: 'linear' | 'angular' | 'radial' | 'diameter';
  point1: JWWPoint;
  point2: JWWPoint;
  textPosition: JWWPoint;
  value?: number;
  text?: string;
  style?: JWWDimensionStyle;
}

export interface JWWDimensionStyle {
  arrowSize: number;
  textHeight: number;
  precision: number;
  units: string;
}

// JWW File parsing result
export interface JWWParseResult {
  success: boolean;
  document?: JWWDocument;
  error?: string;
  warnings?: string[];
}

// Binary data structures for parsing
export interface JWWBinaryHeader {
  signature: Uint8Array; // 8 bytes: "JwwData."
  version: number;       // 4 bytes: DWORD
  reserved: Uint8Array;  // Additional header data
}

export interface JWWBinaryEntity {
  entityType: number;
  layer: number;
  color: number;
  lineType: number;
  dataSize: number;
  data: Uint8Array;
}

// Constants
export const JWW_SIGNATURE = 'JwwData.';
export const JWW_HEADER_SIZE = 12; // Minimum header size

export const JWW_ENTITY_TYPES = {
  LINE: 1,
  ARC: 2,
  CIRCLE: 3,
  POLYLINE: 4,
  TEXT: 5,
  DIMENSION: 6,
  POINT: 7,
  SOLID: 8,
  BLOCK: 9,
  HATCH: 10,
  SPLINE: 11
} as const;

export const JWW_LINE_TYPES = {
  SOLID: 0,
  DASHED: 1,
  DOTTED: 2,
  DASH_DOT: 3,
  DASH_DOT_DOT: 4
} as const;

export const JWW_COLORS = {
  BLACK: 0,
  RED: 1,
  GREEN: 2,
  BLUE: 3,
  YELLOW: 4,
  MAGENTA: 5,
  CYAN: 6,
  WHITE: 7
} as const;

// Utility type for converting JWW to SXF format
export interface JWWToSXFConversionOptions {
  scaleFactor?: number;
  layerMapping?: Record<number, string>;
  colorMapping?: Record<number, string>;
  units?: 'mm' | 'cm' | 'm';
  precision?: number;
}