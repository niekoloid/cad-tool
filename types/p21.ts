// ISO 10303-21 STEP Part21 Data Structure Types

// Header section types
export interface P21Header {
  fileDescription: string[];
  fileName: string;
  fileSchema: string[];
  implementationLevel: string;
  timeStamp: string;
  author: string[];
  organization: string[];
  preprocessorVersion: string;
  originatingSystem: string;
  authorization: string;
}

// Basic data types
export interface P21Instance {
  id: number;
  entityType: string;
  attributes: any[];
}

export interface P21Point {
  x: number;
  y: number;
  z?: number;
}

export interface P21Direction {
  directionRatios: number[];
}

export interface P21Vector {
  orientation: P21Direction;
  magnitude: number;
}

export interface P21Axis2Placement {
  location: P21Point;
  axis?: P21Direction;
  refDirection?: P21Direction;
}

// Geometric entities
export interface P21CartesianPoint {
  coordinates: number[];
}

export interface P21Line {
  point: P21Point;
  direction: P21Vector;
}

export interface P21Circle {
  position: P21Axis2Placement;
  radius: number;
}

export interface P21Ellipse {
  position: P21Axis2Placement;
  semiAxis1: number;
  semiAxis2: number;
}

export interface P21Polyline {
  points: P21Point[];
}

export interface P21BSplineCurve {
  degree: number;
  controlPoints: P21Point[];
  curveForm: string;
  closedCurve: boolean;
  selfIntersect: boolean;
  knotMultiplicities?: number[];
  knots?: number[];
  knotSpec?: string;
}

export interface P21TrimmedCurve {
  basisCurve: any;
  trim1: any[];
  trim2: any[];
  senseOfTrim: boolean;
  masterRepresentation: string;
}

export interface P21CompositeCurve {
  segments: P21CompositeCurveSegment[];
  selfIntersect: boolean;
}

export interface P21CompositeCurveSegment {
  transition: string;
  sameSense: boolean;
  parentCurve: any;
}

// Presentation entities
export interface P21ColourRgb {
  red: number;
  green: number;
  blue: number;
}

export interface P21DraughtingPreDefinedColour {
  name: string;
}

export interface P21CurveStyle {
  name?: string;
  curveFont: any;
  curveWidth: any;
  curveColour: any;
}

export interface P21CurveStyleFont {
  name?: string;
  patternList: P21CurveStyleFontPattern[];
}

export interface P21CurveStyleFontPattern {
  visibleSegmentLength: number;
  invisibleSegmentLength: number;
}

export interface P21PresentationStyleAssignment {
  styles: any[];
}

export interface P21StyledItem {
  item: any;
  styles: P21PresentationStyleAssignment[];
  name?: string;
}

// Layer and drawing organization
export interface P21PresentationLayerAssignment {
  assignedItems: any[];
  name: string;
  description?: string;
}

export interface P21PresentationLayerUsage {
  assignment: P21PresentationLayerAssignment;
  presentation: any;
}

export interface P21DrawingDefinition {
  drawingNumber: string;
  drawingType?: string;
}

export interface P21DrawingRevision {
  revision: string;
  drawingIdentifier: P21DrawingDefinition;
  intendedScale?: string;
}

export interface P21DraughtingTitle {
  contents: any[];
  language: string;
  title: string;
}

// Text entities
export interface P21TextLiteralWithExtent {
  literal: string;
  placement: P21Axis2Placement;
  alignment: string;
  path: string;
  extent: any;
}

export interface P21TextStyleForDefinedFont {
  textColour?: any;
  textFont: any;
  characterHeight: number;
  characterWidth?: number;
  characterSpacing?: number;
  wordSpacing?: number;
  textBoxCharacteristics?: any[];
}

// Dimension entities
export interface P21LinearDimension {
  contents: any[];
  language: string;
}

export interface P21AngularDimension {
  contents: any[];
  language: string;
}

export interface P21DiameterDimension {
  contents: any[];
  language: string;
}

export interface P21RadiusDimension {
  contents: any[];
  language: string;
}

// Symbol entities
export interface P21DefinedSymbol {
  definition: any;
  target: any;
}

export interface P21ExternallyDefinedSymbol {
  itemId: string;
  source: any;
}

export interface P21PreDefinedPointMarkerSymbol {
  name: string;
}

export interface P21AnnotationSymbol {
  item: any;
  styles: any[];
}

// Geometry union types
export type P21Curve = 
  | P21Line 
  | P21Circle 
  | P21Ellipse 
  | P21Polyline 
  | P21BSplineCurve 
  | P21TrimmedCurve
  | P21CompositeCurve;

export type P21GeometricRepresentationItem = 
  | P21CartesianPoint
  | P21Curve
  | P21TextLiteralWithExtent
  | P21DefinedSymbol
  | P21AnnotationSymbol;

export type P21PresentationItem = 
  | P21GeometricRepresentationItem
  | P21StyledItem;

// Main document structure
export interface P21Document {
  header: P21Header;
  instances: Map<number, P21Instance>;
  
  // Organized data for easier access
  geometricItems: P21GeometricRepresentationItem[];
  layers: P21PresentationLayerAssignment[];
  styles: P21PresentationStyleAssignment[];
  colors: (P21ColourRgb | P21DraughtingPreDefinedColour)[];
  
  // Drawing information
  drawingDefinition?: P21DrawingDefinition;
  drawingRevision?: P21DrawingRevision;
  title?: P21DraughtingTitle;
}

// File format detection
export interface FileFormatInfo {
  format: 'SXF' | 'P21';
  extension: string;
  mimeType?: string;
}

// Common interface for unified handling
export interface CADDocument {
  format: 'SXF' | 'P21';
  originalData: any; // SXFDocument | P21Document
  
  // Unified properties
  title: string;
  layers: CADLayer[];
  geometries: CADGeometry[];
  metadata: CADMetadata;
}

export interface CADLayer {
  id: string;
  name: string;
  visible: boolean;
  color?: string;
  items: CADGeometry[];
}

export interface CADGeometry {
  id: string;
  type: 'point' | 'line' | 'circle' | 'arc' | 'ellipse' | 'polyline' | 'spline' | 'text' | 'symbol';
  layer: string;
  style?: CADStyle;
  geometry: any; // Specific geometry data
}

export interface CADStyle {
  color?: string;
  lineWidth?: number;
  lineType?: string;
  fillColor?: string;
}

export interface CADMetadata {
  format: string;
  title?: string;
  author?: string;
  organization?: string;
  created?: Date;
  modified?: Date;
  scale?: string;
  units?: string;
}