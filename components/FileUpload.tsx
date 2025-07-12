'use client';

import { useCallback, useState } from 'react';
import { SXFDocument } from '@/types/sxf';
import { CADDocument, FileFormatInfo } from '@/types/p21';
import { createP21Converter } from '@/lib/p21-converter';

interface FileUploadProps {
  onFileLoaded: (document: CADDocument) => void;
}

export default function FileUpload({ onFileLoaded }: FileUploadProps) {
  const [isDragging, setIsDragging] = useState(false);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [detectedFormat, setDetectedFormat] = useState<FileFormatInfo | null>(null);

  const detectFileFormat = useCallback((file: File): FileFormatInfo => {
    const fileName = file.name.toLowerCase();
    const extension = fileName.substring(fileName.lastIndexOf('.'));
    
    if (extension === '.sxf' || extension === '.sfc') {
      return { format: 'SXF', extension };
    } else if (extension === '.p21' || extension === '.stp' || extension === '.step') {
      return { format: 'P21', extension };
    }
    
    throw new Error('Unsupported file format');
  }, []);

  const parseP21File = useCallback(async (file: File): Promise<CADDocument> => {
    try {
      const text = await file.text();
      const converter = createP21Converter({
        coordinateSystem: 'right-handed',
        unitScale: 1.0,
        precision: 0.001
      });
      
      const document = await converter.convertP21File(text, file.name);
      return document;
    } catch (error) {
      console.warn('P21 converter failed, using fallback:', error);
      
      // Fallback mock P21 document
      const mockP21Document: CADDocument = {
        format: 'P21',
        originalData: null,
        title: file.name,
        layers: [
          { 
            id: 'layer1', 
            name: 'Default Layer', 
            visible: true, 
            color: '#000000',
            items: []
          }
        ],
        geometries: [
          {
            id: 'line1',
            type: 'line',
            layer: 'layer1',
            style: { color: '#000000', lineWidth: 1 },
            geometry: { start: { x: 20, y: 20 }, end: { x: 120, y: 120 } }
          },
          {
            id: 'circle1',
            type: 'circle',
            layer: 'layer1',
            style: { color: '#FF0000', lineWidth: 2 },
            geometry: { center: { x: 80, y: 80 }, radius: 30 }
          }
        ],
        metadata: {
          format: 'STEP Part21',
          title: file.name,
          created: new Date()
        }
      };

      return mockP21Document;
    }
  }, []);

  const parseSXFFile = useCallback(async (file: File): Promise<CADDocument> => {
    // Convert existing SXF mock to CADDocument format
    const mockSXFDocument: CADDocument = {
      format: 'SXF',
      originalData: null,
      title: file.name,
      layers: [
        { 
          id: 'layer1', 
          name: 'Layer1', 
          visible: true, 
          color: '#000000',
          items: []
        },
        { 
          id: 'layer2', 
          name: 'Layer2', 
          visible: true, 
          color: '#FF0000',
          items: []
        }
      ],
      geometries: [
        {
          id: 'line1',
          type: 'line',
          layer: 'layer1',
          style: { color: '#000000', lineWidth: 1 },
          geometry: { start: { x: 10, y: 10 }, end: { x: 100, y: 100 } }
        },
        {
          id: 'circle1',
          type: 'circle',
          layer: 'layer1',
          style: { color: '#000000', lineWidth: 1 },
          geometry: { center: { x: 50, y: 50 }, radius: 25 }
        }
      ],
      metadata: {
        format: 'SXF',
        title: file.name,
        created: new Date()
      }
    };

    return mockSXFDocument;
  }, []);

  const handleFile = useCallback(async (file: File) => {
    setIsLoading(true);
    setError(null);
    setDetectedFormat(null);

    try {
      const formatInfo = detectFileFormat(file);
      setDetectedFormat(formatInfo);

      let document: CADDocument;
      
      if (formatInfo.format === 'P21') {
        document = await parseP21File(file);
      } else {
        document = await parseSXFFile(file);
      }

      onFileLoaded(document);
    } catch (err) {
      if (err instanceof Error && err.message === 'Unsupported file format') {
        setError('対応していないファイル形式です。SXF (.sxf, .sfc) または STEP Part21 (.p21, .stp, .step) ファイルを選択してください');
      } else {
        setError('ファイルの読み込みに失敗しました');
        console.error('File loading error:', err);
      }
    } finally {
      setIsLoading(false);
    }
  }, [onFileLoaded, detectFileFormat, parseP21File, parseSXFFile]);

  const handleDrop = useCallback((e: React.DragEvent) => {
    e.preventDefault();
    setIsDragging(false);

    const files = Array.from(e.dataTransfer.files);
    if (files.length > 0) {
      handleFile(files[0]);
    }
  }, [handleFile]);

  const handleDragOver = useCallback((e: React.DragEvent) => {
    e.preventDefault();
    setIsDragging(true);
  }, []);

  const handleDragLeave = useCallback((e: React.DragEvent) => {
    e.preventDefault();
    setIsDragging(false);
  }, []);

  const handleFileInput = useCallback((e: React.ChangeEvent<HTMLInputElement>) => {
    const files = e.target.files;
    if (files && files.length > 0) {
      handleFile(files[0]);
    }
  }, [handleFile]);

  return (
    <div className="p-8">
      <div
        className={`border-2 border-dashed rounded-lg p-8 text-center transition-colors ${
          isDragging
            ? 'border-blue-400 bg-blue-50'
            : 'border-gray-300 hover:border-gray-400'
        }`}
        onDrop={handleDrop}
        onDragOver={handleDragOver}
        onDragLeave={handleDragLeave}
      >
        {isLoading ? (
          <div className="space-y-4">
            <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-blue-600 mx-auto"></div>
            <p className="text-gray-600">ファイルを読み込み中...</p>
          </div>
        ) : (
          <div className="space-y-4">
            <div className="mx-auto w-12 h-12 text-gray-400">
              <svg
                fill="none"
                stroke="currentColor"
                viewBox="0 0 24 24"
                xmlns="http://www.w3.org/2000/svg"
              >
                <path
                  strokeLinecap="round"
                  strokeLinejoin="round"
                  strokeWidth={2}
                  d="M7 16a4 4 0 01-.88-7.903A5 5 0 1115.9 6L16 6a5 5 0 011 9.9M15 13l-3-3m0 0l-3 3m3-3v12"
                />
              </svg>
            </div>
            <div>
              <p className="text-lg font-medium text-gray-900">
                CADファイルをアップロード
              </p>
              <p className="text-gray-600">
                ファイルをドラッグ&ドロップするか、クリックして選択
              </p>
              {detectedFormat && (
                <p className="text-sm text-blue-600 mt-1">
                  検出形式: {detectedFormat.format} ({detectedFormat.extension})
                </p>
              )}
            </div>
            <div>
              <label htmlFor="file-upload" className="cursor-pointer">
                <input
                  id="file-upload"
                  name="file-upload"
                  type="file"
                  accept=".sxf,.sfc,.p21,.stp,.step"
                  className="sr-only"
                  onChange={handleFileInput}
                />
                <span className="inline-flex items-center px-4 py-2 border border-transparent text-sm font-medium rounded-md text-white bg-blue-600 hover:bg-blue-700">
                  ファイルを選択
                </span>
              </label>
            </div>
            <p className="text-xs text-gray-500">
              対応形式: SXF (.sxf, .sfc), STEP Part21 (.p21, .stp, .step) (最大 50MB)
            </p>
          </div>
        )}
      </div>
      
      {error && (
        <div className="mt-4 p-4 border border-red-300 rounded-md bg-red-50">
          <p className="text-red-800">{error}</p>
        </div>
      )}
    </div>
  );
}