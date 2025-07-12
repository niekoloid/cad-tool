// Emscripten TypeScript definitions

declare global {
  interface EmscriptenModule {
    _malloc(size: number): number;
    _free(ptr: number): void;
    getValue(ptr: number, type: string): number;
    setValue(ptr: number, value: number, type: string): void;
    UTF8ToString(ptr: number): string;
    writeStringToMemory(str: string, ptr: number): void;
    ccall(name: string, returnType: string, argTypes: string[], args: any[]): any;
    cwrap(name: string, returnType: string, argTypes: string[]): (...args: any[]) => any;
  }

  function ccall(name: string, returnType: string, argTypes: string[], args: any[]): any;
  function cwrap(name: string, returnType: string, argTypes: string[]): (...args: any[]) => any;
}

export {};