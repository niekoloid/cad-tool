// WebAssembly P21 Parser TypeScript Interface
import '../types/emscripten';

export interface P21WASMModule extends EmscriptenModule {
  ccall: (name: string, returnType: string, argTypes: string[], args: any[]) => any;
  cwrap: (name: string, returnType: string, argTypes: string[]) => (...args: any[]) => any;
  
  // Wrapped functions
  SXFopen_AP202: (filename: string, rw_flag: number, tolerance1: number, tolerance2: number, divide: number, level: number, mode: number) => number;
  SXFread_table_AP202: (tableType: number, structPtr: number, endFlagPtr: number) => number;
  SXFread_assembly_name_AP202: (type: number, structPtr: number, endFlagPtr: number) => number;
  SXFread_next_feature_AP202: (typePtr: number, structPtr: number, endFlagPtr: number) => number;
  SXFclose_AP202: () => number;
}

export interface P21WASMResult {
  success: boolean;
  data?: any;
  error?: string;
}

export class P21WASMParser {
  private module: P21WASMModule | null = null;
  private initialized = false;

  async initialize(): Promise<boolean> {
    try {
      // Check if WebAssembly module exists, otherwise use fallback
      let createP21Module;
      try {
        // Dynamic import for WebAssembly module (may not exist during development)
        const wasmModule = await fetch('/p21-parser.js');
        if (wasmModule.ok) {
          const moduleScript = await wasmModule.text();
          // eslint-disable-next-line no-eval
          createP21Module = eval(moduleScript);
        } else {
          throw new Error('WASM module not found');
        }
      } catch (importError) {
        console.warn('P21 WebAssembly module not found, parser will use fallback mode');
        return false;
      }
      
      this.module = await createP21Module();
      
      if (!this.module) {
        throw new Error('Failed to create P21 module');
      }
      
      // Wrap the C functions for easier use
      this.module.SXFopen_AP202 = this.module.cwrap('SXFopen_AP202', 'number', 
        ['string', 'number', 'number', 'number', 'number', 'number', 'number']);
      
      this.module.SXFread_table_AP202 = this.module.cwrap('SXFread_table_AP202', 'number',
        ['number', 'number', 'number']);
      
      this.module.SXFread_assembly_name_AP202 = this.module.cwrap('SXFread_assembly_name_AP202', 'number',
        ['number', 'number', 'number']);
      
      this.module.SXFread_next_feature_AP202 = this.module.cwrap('SXFread_next_feature_AP202', 'number',
        ['number', 'number', 'number']);
      
      this.module.SXFclose_AP202 = this.module.cwrap('SXFclose_AP202', 'number', []);
      
      this.initialized = true;
      return true;
    } catch (error) {
      console.error('Failed to initialize P21 WASM module:', error);
      return false;
    }
  }

  async parseP21File(fileContent: string): Promise<P21WASMResult> {
    if (!this.initialized || !this.module) {
      return { success: false, error: 'WASM module not initialized' };
    }

    try {
      // Write file content to WASM memory
      const contentPtr = this.module._malloc(fileContent.length + 1);
      this.module.writeStringToMemory(fileContent, contentPtr);

      // Open the P21 file
      const result = this.module.SXFopen_AP202(
        'temp.p21', // filename (not used in memory mode)
        0,          // read mode
        0.01,       // tolerance1
        0.01,       // tolerance2  
        0.0,        // divide
        2,          // level
        2           // mode
      );

      if (result < 0) {
        this.module._free(contentPtr);
        return { success: false, error: 'Failed to open P21 file' };
      }

      // Parse tables and features
      const parsedData = {
        layers: await this.readLayers(),
        colors: await this.readColors(),
        lineTypes: await this.readLineTypes(),
        geometries: await this.readGeometries()
      };

      // Clean up
      this.module.SXFclose_AP202();
      this.module._free(contentPtr);

      return { success: true, data: parsedData };
    } catch (error) {
      return { success: false, error: `Parsing error: ${error}` };
    }
  }

  private async readLayers(): Promise<any[]> {
    if (!this.module) return [];
    
    const layers: any[] = [];
    const structPtr = this.module._malloc(256); // Allocate memory for layer struct
    const endFlagPtr = this.module._malloc(4);
    
    this.module.setValue(endFlagPtr, 0, 'i32');
    
    while (this.module.getValue(endFlagPtr, 'i32') === 0) {
      const result = this.module.SXFread_table_AP202(1, structPtr, endFlagPtr);
      if (result > 0) {
        // Parse layer structure from memory
        // This would need to match the C++ Layer_Struct definition
        const name = this.module.UTF8ToString(structPtr);
        const visible = this.module.getValue(structPtr + 64, 'i32') !== 0; // Assuming name is 64 chars
        
        layers.push({
          name,
          visible,
          color: '#000000' // Default color
        });
      }
    }
    
    this.module._free(structPtr);
    this.module._free(endFlagPtr);
    
    return layers;
  }

  private async readColors(): Promise<any[]> {
    if (!this.module) return [];
    
    const colors: any[] = [];
    const structPtr = this.module._malloc(256);
    const endFlagPtr = this.module._malloc(4);
    
    this.module.setValue(endFlagPtr, 0, 'i32');
    
    // Read predefined colors (table type 2)
    while (this.module.getValue(endFlagPtr, 'i32') === 0) {
      const result = this.module.SXFread_table_AP202(2, structPtr, endFlagPtr);
      if (result > 0) {
        const name = this.module.UTF8ToString(structPtr);
        colors.push(name);
      }
    }
    
    this.module._free(structPtr);
    this.module._free(endFlagPtr);
    
    return colors;
  }

  private async readLineTypes(): Promise<string[]> {
    if (!this.module) return [];
    
    const lineTypes: string[] = [];
    const structPtr = this.module._malloc(256);
    const endFlagPtr = this.module._malloc(4);
    
    this.module.setValue(endFlagPtr, 0, 'i32');
    
    // Read predefined line types (table type 4)
    while (this.module.getValue(endFlagPtr, 'i32') === 0) {
      const result = this.module.SXFread_table_AP202(4, structPtr, endFlagPtr);
      if (result > 0) {
        const name = this.module.UTF8ToString(structPtr);
        lineTypes.push(name);
      }
    }
    
    this.module._free(structPtr);
    this.module._free(endFlagPtr);
    
    return lineTypes;
  }

  private async readGeometries(): Promise<any[]> {
    if (!this.module) return [];
    
    const geometries: any[] = [];
    const structPtr = this.module._malloc(1024); // Larger buffer for geometry data
    const endFlagPtr = this.module._malloc(4);
    const featureNamePtr = this.module._malloc(64);
    
    // Read different assembly types (SHEET, SFIG_ORG, CCURVE_ORG)
    const assemblyTypes = [0, 1, 2]; // These would map to actual constants
    
    for (const assemblyType of assemblyTypes) {
      this.module.setValue(endFlagPtr, 0, 'i32');
      
      while (this.module.getValue(endFlagPtr, 'i32') === 0) {
        const assemblyResult = this.module.SXFread_assembly_name_AP202(assemblyType, structPtr, endFlagPtr);
        if (assemblyResult >= 0) {
          // Read features within this assembly
          const featureEndFlagPtr = this.module._malloc(4);
          this.module.setValue(featureEndFlagPtr, 0, 'i32');
          
          while (this.module.getValue(featureEndFlagPtr, 'i32') === 0) {
            const featureResult = this.module.SXFread_next_feature_AP202(featureNamePtr, structPtr, featureEndFlagPtr);
            if (featureResult > 0) {
              const featureName = this.module.UTF8ToString(featureNamePtr);
              const geometry = this.parseGeometryFromStruct(featureName, structPtr);
              if (geometry) {
                geometries.push(geometry);
              }
            }
          }
          
          this.module._free(featureEndFlagPtr);
        }
      }
    }
    
    this.module._free(structPtr);
    this.module._free(endFlagPtr);
    this.module._free(featureNamePtr);
    
    return geometries;
  }

  private parseGeometryFromStruct(featureName: string, structPtr: number): any | null {
    if (!this.module) return null;
    
    // Parse geometry based on feature type
    // This would need to match the C++ struct definitions
    switch (featureName.toUpperCase()) {
      case 'LINE':
        return {
          type: 'line',
          geometry: {
            start: {
              x: this.module.getValue(structPtr + 8, 'double'),  // Offset for start_x
              y: this.module.getValue(structPtr + 16, 'double')  // Offset for start_y
            },
            end: {
              x: this.module.getValue(structPtr + 24, 'double'), // Offset for end_x
              y: this.module.getValue(structPtr + 32, 'double')  // Offset for end_y
            }
          },
          layer: this.module.getValue(structPtr, 'i32').toString(),
          style: {
            color: '#000000',
            lineWidth: 1
          }
        };
        
      case 'CIRCLE':
        return {
          type: 'circle',
          geometry: {
            center: {
              x: this.module.getValue(structPtr + 8, 'double'),
              y: this.module.getValue(structPtr + 16, 'double')
            },
            radius: this.module.getValue(structPtr + 24, 'double')
          },
          layer: this.module.getValue(structPtr, 'i32').toString(),
          style: {
            color: '#000000',
            lineWidth: 1
          }
        };
        
      case 'ARC':
        return {
          type: 'arc',
          geometry: {
            center: {
              x: this.module.getValue(structPtr + 8, 'double'),
              y: this.module.getValue(structPtr + 16, 'double')
            },
            radius: this.module.getValue(structPtr + 24, 'double'),
            startAngle: this.module.getValue(structPtr + 32, 'double'),
            endAngle: this.module.getValue(structPtr + 40, 'double')
          },
          layer: this.module.getValue(structPtr, 'i32').toString(),
          style: {
            color: '#000000',
            lineWidth: 1
          }
        };
        
      default:
        return null;
    }
  }
}

// Singleton instance
let wasmParser: P21WASMParser | null = null;

export async function getP21Parser(): Promise<P21WASMParser> {
  if (!wasmParser) {
    wasmParser = new P21WASMParser();
    await wasmParser.initialize();
  }
  return wasmParser;
}