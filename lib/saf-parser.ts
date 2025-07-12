// SAF (Structural Analysis Format) Parser
import * as XLSX from 'xlsx';
import {
  SAFDocument,
  SAFNode,
  SAFMember,
  SAFCrossSection,
  SAFMaterial,
  SAFLoad,
  SAFSupport,
  SAFProjectInfo,
  SAFParseResult,
  SAF_WORKSHEET_NAMES
} from '@/types/saf';

export class SAFParser {
  
  async parseArrayBuffer(buffer: ArrayBuffer): Promise<SAFParseResult> {
    try {
      const workbook = XLSX.read(buffer, { type: 'array' });
      
      // Validate that this is a SAF file by checking for expected worksheets
      const sheetNames = workbook.SheetNames;
      const hasSAFSheets = sheetNames.some(name => 
        Object.values(SAF_WORKSHEET_NAMES).includes(name as any)
      );
      
      if (!hasSAFSheets) {
        return {
          success: false,
          error: 'This does not appear to be a valid SAF file. Expected worksheets not found.'
        };
      }

      const document: SAFDocument = {
        projectInfo: this.parseProjectInfo(workbook),
        nodes: this.parseNodes(workbook),
        members: this.parseMembers(workbook),
        crossSections: this.parseCrossSections(workbook),
        materials: this.parseMaterials(workbook),
        loads: this.parseLoads(workbook),
        supports: this.parseSupports(workbook),
        sheets: sheetNames
      };

      return {
        success: true,
        document,
        warnings: this.validateDocument(document)
      };

    } catch (error) {
      return {
        success: false,
        error: `Failed to parse SAF file: ${error instanceof Error ? error.message : 'Unknown error'}`
      };
    }
  }

  async parseFile(file: File): Promise<SAFParseResult> {
    const buffer = await file.arrayBuffer();
    return this.parseArrayBuffer(buffer);
  }

  private parseProjectInfo(workbook: XLSX.WorkBook): SAFProjectInfo {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.PROJECT_INFO];
    if (!worksheet) {
      return {};
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const info: SAFProjectInfo = {};

    // Parse project info from key-value pairs
    for (const row of data) {
      if (row.length >= 2) {
        const key = String(row[0]).toLowerCase().trim();
        const value = row[1];

        switch (key) {
          case 'project name':
          case 'name':
            info.name = String(value);
            break;
          case 'description':
            info.description = String(value);
            break;
          case 'author':
            info.author = String(value);
            break;
          case 'software':
            info.software = String(value);
            break;
          case 'version':
            info.version = String(value);
            break;
        }
      }
    }

    return info;
  }

  private parseNodes(workbook: XLSX.WorkBook): SAFNode[] {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.NODES];
    if (!worksheet) {
      return [];
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const nodes: SAFNode[] = [];

    // Skip header row
    for (let i = 1; i < data.length; i++) {
      const row = data[i];
      if (row.length >= 4) {
        const node: SAFNode = {
          id: String(row[0] || `node_${i}`),
          name: row[1] ? String(row[1]) : undefined,
          x: this.parseNumber(row[2]) || 0,
          y: this.parseNumber(row[3]) || 0,
          z: this.parseNumber(row[4]) || 0,
          coordinateSystem: row[5] ? String(row[5]) : undefined
        };
        nodes.push(node);
      }
    }

    return nodes;
  }

  private parseMembers(workbook: XLSX.WorkBook): SAFMember[] {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.MEMBERS];
    if (!worksheet) {
      return [];
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const members: SAFMember[] = [];

    // Skip header row
    for (let i = 1; i < data.length; i++) {
      const row = data[i];
      if (row.length >= 4) {
        const member: SAFMember = {
          id: String(row[0] || `member_${i}`),
          name: row[1] ? String(row[1]) : undefined,
          type: this.parseMemberType(row[2]),
          startNodeId: String(row[3]),
          endNodeId: String(row[4]),
          crossSectionId: row[5] ? String(row[5]) : undefined,
          materialId: row[6] ? String(row[6]) : undefined,
          length: this.parseNumber(row[7]),
          orientation: this.parseNumber(row[8])
        };
        members.push(member);
      }
    }

    return members;
  }

  private parseCrossSections(workbook: XLSX.WorkBook): SAFCrossSection[] {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.CROSS_SECTIONS];
    if (!worksheet) {
      return [];
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const crossSections: SAFCrossSection[] = [];

    // Skip header row
    for (let i = 1; i < data.length; i++) {
      const row = data[i];
      if (row.length >= 2) {
        const crossSection: SAFCrossSection = {
          id: String(row[0] || `cs_${i}`),
          name: String(row[1] || `CrossSection_${i}`),
          material: row[2] ? String(row[2]) : undefined,
          area: this.parseNumber(row[3]),
          momentOfInertiaY: this.parseNumber(row[4]),
          momentOfInertiaZ: this.parseNumber(row[5]),
          description: row[6] ? String(row[6]) : undefined
        };
        crossSections.push(crossSection);
      }
    }

    return crossSections;
  }

  private parseMaterials(workbook: XLSX.WorkBook): SAFMaterial[] {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.MATERIALS];
    if (!worksheet) {
      return [];
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const materials: SAFMaterial[] = [];

    // Skip header row
    for (let i = 1; i < data.length; i++) {
      const row = data[i];
      if (row.length >= 2) {
        const material: SAFMaterial = {
          id: String(row[0] || `mat_${i}`),
          name: String(row[1] || `Material_${i}`),
          elasticModulus: this.parseNumber(row[2]),
          poissonRatio: this.parseNumber(row[3]),
          density: this.parseNumber(row[4]),
          description: row[5] ? String(row[5]) : undefined
        };
        materials.push(material);
      }
    }

    return materials;
  }

  private parseLoads(workbook: XLSX.WorkBook): SAFLoad[] {
    const loads: SAFLoad[] = [];

    // Parse point loads
    const pointLoadSheet = workbook.Sheets[SAF_WORKSHEET_NAMES.LOADS_POINT];
    if (pointLoadSheet) {
      const data = XLSX.utils.sheet_to_json(pointLoadSheet, { header: 1 }) as any[][];
      for (let i = 1; i < data.length; i++) {
        const row = data[i];
        if (row.length >= 4) {
          const load: SAFLoad = {
            id: String(row[0] || `load_${loads.length + 1}`),
            name: row[1] ? String(row[1]) : undefined,
            type: 'point',
            nodeId: String(row[2]),
            direction: this.parseLoadDirection(row[3]),
            magnitude: this.parseNumber(row[4]) || 0
          };
          loads.push(load);
        }
      }
    }

    // Parse line loads
    const lineLoadSheet = workbook.Sheets[SAF_WORKSHEET_NAMES.LOADS_LINE];
    if (lineLoadSheet) {
      const data = XLSX.utils.sheet_to_json(lineLoadSheet, { header: 1 }) as any[][];
      for (let i = 1; i < data.length; i++) {
        const row = data[i];
        if (row.length >= 4) {
          const load: SAFLoad = {
            id: String(row[0] || `load_${loads.length + 1}`),
            name: row[1] ? String(row[1]) : undefined,
            type: 'distributed',
            memberId: String(row[2]),
            direction: this.parseLoadDirection(row[3]),
            magnitude: this.parseNumber(row[4]) || 0,
            position: this.parseNumber(row[5]),
            length: this.parseNumber(row[6])
          };
          loads.push(load);
        }
      }
    }

    return loads;
  }

  private parseSupports(workbook: XLSX.WorkBook): SAFSupport[] {
    const worksheet = workbook.Sheets[SAF_WORKSHEET_NAMES.SUPPORTS];
    if (!worksheet) {
      return [];
    }

    const data = XLSX.utils.sheet_to_json(worksheet, { header: 1 }) as any[][];
    const supports: SAFSupport[] = [];

    // Skip header row
    for (let i = 1; i < data.length; i++) {
      const row = data[i];
      if (row.length >= 7) {
        const support: SAFSupport = {
          id: String(row[0] || `support_${i}`),
          name: row[1] ? String(row[1]) : undefined,
          nodeId: String(row[2]),
          dx: this.parseBoolean(row[3]),
          dy: this.parseBoolean(row[4]),
          dz: this.parseBoolean(row[5]),
          rx: this.parseBoolean(row[6]),
          ry: this.parseBoolean(row[7]),
          rz: this.parseBoolean(row[8])
        };
        supports.push(support);
      }
    }

    return supports;
  }

  private parseNumber(value: any): number | undefined {
    if (value === null || value === undefined || value === '') {
      return undefined;
    }
    const num = Number(value);
    return isNaN(num) ? undefined : num;
  }

  private parseBoolean(value: any): boolean {
    if (typeof value === 'boolean') {
      return value;
    }
    const str = String(value).toLowerCase().trim();
    return str === 'true' || str === '1' || str === 'yes' || str === 'x';
  }

  private parseMemberType(value: any): 'beam' | 'column' | 'brace' | 'truss' | 'other' {
    const str = String(value || '').toLowerCase().trim();
    if (str.includes('beam')) return 'beam';
    if (str.includes('column')) return 'column';
    if (str.includes('brace')) return 'brace';
    if (str.includes('truss')) return 'truss';
    return 'other';
  }

  private parseLoadDirection(value: any): 'x' | 'y' | 'z' | 'mx' | 'my' | 'mz' {
    const str = String(value || '').toLowerCase().trim();
    if (str.includes('mx') || str.includes('moment') && str.includes('x')) return 'mx';
    if (str.includes('my') || str.includes('moment') && str.includes('y')) return 'my';
    if (str.includes('mz') || str.includes('moment') && str.includes('z')) return 'mz';
    if (str.includes('x')) return 'x';
    if (str.includes('z')) return 'z';
    return 'y'; // Default to Y direction
  }

  private validateDocument(document: SAFDocument): string[] {
    const warnings: string[] = [];

    if (document.nodes.length === 0) {
      warnings.push('No nodes found in the SAF file');
    }

    if (document.members.length === 0) {
      warnings.push('No members found in the SAF file');
    }

    // Check for missing node references in members
    const nodeIds = new Set(document.nodes.map(n => n.id));
    for (const member of document.members) {
      if (!nodeIds.has(member.startNodeId)) {
        warnings.push(`Member ${member.id} references missing start node ${member.startNodeId}`);
      }
      if (!nodeIds.has(member.endNodeId)) {
        warnings.push(`Member ${member.id} references missing end node ${member.endNodeId}`);
      }
    }

    return warnings;
  }
}

// Utility function to create SAF parser
export function createSAFParser(): SAFParser {
  return new SAFParser();
}