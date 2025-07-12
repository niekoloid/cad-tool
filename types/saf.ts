// SAF (Structural Analysis Format) Type Definitions
// SAF is an Excel-based format for structural analysis model exchange

import { CADDocument, CADLayer, CADGeometry, CADMetadata } from './p21';

// SAF Node (Point in 3D space)
export interface SAFNode {
  id: string;
  name?: string;
  x: number;
  y: number;
  z: number;
  coordinateSystem?: string;
}

// SAF Cross Section
export interface SAFCrossSection {
  id: string;
  name: string;
  material?: string;
  area?: number;
  momentOfInertiaY?: number;
  momentOfInertiaZ?: number;
  description?: string;
}

// SAF Material
export interface SAFMaterial {
  id: string;
  name: string;
  elasticModulus?: number;
  poissonRatio?: number;
  density?: number;
  description?: string;
}

// SAF Member (Structural Element)
export interface SAFMember {
  id: string;
  name?: string;
  type: 'beam' | 'column' | 'brace' | 'truss' | 'other';
  startNodeId: string;
  endNodeId: string;
  crossSectionId?: string;
  materialId?: string;
  length?: number;
  orientation?: number;
}

// SAF Load
export interface SAFLoad {
  id: string;
  name?: string;
  type: 'point' | 'distributed' | 'moment';
  memberId?: string;
  nodeId?: string;
  direction: 'x' | 'y' | 'z' | 'mx' | 'my' | 'mz';
  magnitude: number;
  position?: number; // For distributed loads
  length?: number; // For distributed loads
}

// SAF Support/Constraint
export interface SAFSupport {
  id: string;
  name?: string;
  nodeId: string;
  dx: boolean; // Translation X constraint
  dy: boolean; // Translation Y constraint
  dz: boolean; // Translation Z constraint
  rx: boolean; // Rotation X constraint
  ry: boolean; // Rotation Y constraint
  rz: boolean; // Rotation Z constraint
}

// SAF Project Information
export interface SAFProjectInfo {
  name?: string;
  description?: string;
  author?: string;
  date?: Date;
  software?: string;
  version?: string;
  units?: {
    length?: string;
    force?: string;
    moment?: string;
    stress?: string;
  };
}

// Main SAF Document Structure
export interface SAFDocument {
  projectInfo: SAFProjectInfo;
  nodes: SAFNode[];
  members: SAFMember[];
  crossSections: SAFCrossSection[];
  materials: SAFMaterial[];
  loads: SAFLoad[];
  supports: SAFSupport[];
  
  // Additional metadata
  sheets: string[]; // List of Excel sheet names processed
  originalData?: any; // Raw Excel data for debugging
}

// SAF Worksheet Names (standard SAF format)
export const SAF_WORKSHEET_NAMES = {
  PROJECT_INFO: 'ProjectAndModelInfo',
  NODES: 'Nodes',
  MEMBERS: 'Members', 
  CROSS_SECTIONS: 'CrossSections',
  MATERIALS: 'Materials',
  LOADS_POINT: 'PointLoads',
  LOADS_LINE: 'LineLoads',
  LOADS_SURFACE: 'SurfaceLoads',
  SUPPORTS: 'Supports',
  NODAL_RELEASES: 'NodalReleases',
  MEMBER_RELEASES: 'MemberReleases'
} as const;

// SAF to CAD conversion options
export interface SAFConversionOptions {
  view: '3d' | 'xy' | 'xz' | 'yz';
  showNodes: boolean;
  showMembers: boolean;
  showLoads: boolean;
  showSupports: boolean;
  scale: number;
  
  // Styling options
  nodeStyle?: {
    radius: number;
    color: string;
  };
  memberStyle?: {
    lineWidth: number;
    color: string;
  };
  loadStyle?: {
    color: string;
    arrowSize: number;
  };
  supportStyle?: {
    size: number;
    color: string;
  };
}

// SAF Parser Result
export interface SAFParseResult {
  success: boolean;
  document?: SAFDocument;
  error?: string;
  warnings?: string[];
}