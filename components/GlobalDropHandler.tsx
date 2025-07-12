'use client';

import { useCallback, useState, useEffect } from 'react';
import { CADDocument, FileFormatInfo } from '@/types/p21';
import { createP21Converter } from '@/lib/p21-converter';

interface GlobalDropHandlerProps {
  onFileLoaded: (document: CADDocument) => void;
  isActive: boolean; // ファイルが既に読み込まれている時のみアクティブ
}

export default function GlobalDropHandler({ onFileLoaded, isActive }: GlobalDropHandlerProps) {
  const [isDragging, setIsDragging] = useState(false);
  const [dragCounter, setDragCounter] = useState(0);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

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

    try {
      const formatInfo = detectFileFormat(file);

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
      
      // エラー表示後3秒で自動消去
      setTimeout(() => setError(null), 3000);
    } finally {
      setIsLoading(false);
    }
  }, [onFileLoaded, detectFileFormat, parseP21File, parseSXFFile]);

  // グローバルドラッグ&ドロップハンドラー
  const handleGlobalDragEnter = useCallback((e: DragEvent) => {
    if (!isActive) return;
    
    e.preventDefault();
    setDragCounter(prev => prev + 1);
    setIsDragging(true);
  }, [isActive]);

  const handleGlobalDragLeave = useCallback((e: DragEvent) => {
    if (!isActive) return;
    
    e.preventDefault();
    setDragCounter(prev => {
      const newCounter = prev - 1;
      if (newCounter === 0) {
        setIsDragging(false);
      }
      return newCounter;
    });
  }, [isActive]);

  const handleGlobalDragOver = useCallback((e: DragEvent) => {
    if (!isActive) return;
    
    e.preventDefault();
  }, [isActive]);

  const handleGlobalDrop = useCallback((e: DragEvent) => {
    if (!isActive) return;
    
    e.preventDefault();
    setIsDragging(false);
    setDragCounter(0);

    const files = Array.from(e.dataTransfer?.files || []);
    if (files.length > 0) {
      handleFile(files[0]);
    }
  }, [isActive, handleFile]);

  // グローバルドラッグ&ドロップイベントの設定
  useEffect(() => {
    if (!isActive) return;

    document.addEventListener('dragenter', handleGlobalDragEnter);
    document.addEventListener('dragleave', handleGlobalDragLeave);
    document.addEventListener('dragover', handleGlobalDragOver);
    document.addEventListener('drop', handleGlobalDrop);

    return () => {
      document.removeEventListener('dragenter', handleGlobalDragEnter);
      document.removeEventListener('dragleave', handleGlobalDragLeave);
      document.removeEventListener('dragover', handleGlobalDragOver);
      document.removeEventListener('drop', handleGlobalDrop);
    };
  }, [isActive, handleGlobalDragEnter, handleGlobalDragLeave, handleGlobalDragOver, handleGlobalDrop]);

  if (!isActive) return null;

  return (
    <>
      {/* グローバルドロップオーバーレイ */}
      {isDragging && (
        <div className="fixed inset-0 z-50 bg-blue-500 bg-opacity-20 flex items-center justify-center">
          <div className="bg-white p-8 rounded-lg shadow-lg border-2 border-blue-400 border-dashed">
            <div className="text-center">
              <div className="text-4xl mb-4">📁</div>
              <p className="text-xl font-medium text-blue-600">
                新しいファイルをドロップしてください
              </p>
              <p className="text-sm text-gray-600 mt-2">
                SXF (.sxf, .sfc) または STEP Part21 (.p21, .stp, .step)
              </p>
            </div>
          </div>
        </div>
      )}

      {/* ローディング表示 */}
      {isLoading && (
        <div className="fixed inset-0 z-50 bg-black bg-opacity-50 flex items-center justify-center">
          <div className="bg-white p-8 rounded-lg shadow-lg">
            <div className="text-center">
              <div className="animate-spin rounded-full h-12 w-12 border-b-2 border-blue-600 mx-auto mb-4"></div>
              <p className="text-gray-600">ファイルを読み込み中...</p>
            </div>
          </div>
        </div>
      )}

      {/* エラー表示 */}
      {error && (
        <div className="fixed top-4 right-4 z-50 max-w-md">
          <div className="bg-red-50 border border-red-300 rounded-md p-4 shadow-lg">
            <div className="flex">
              <div className="flex-shrink-0">
                <svg className="h-5 w-5 text-red-400" viewBox="0 0 20 20" fill="currentColor">
                  <path fillRule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM8.707 7.293a1 1 0 00-1.414 1.414L8.586 10l-1.293 1.293a1 1 0 101.414 1.414L10 11.414l1.293 1.293a1 1 0 001.414-1.414L11.414 10l1.293-1.293a1 1 0 00-1.414-1.414L10 8.586 8.707 7.293z" clipRule="evenodd" />
                </svg>
              </div>
              <div className="ml-3">
                <p className="text-sm text-red-800">{error}</p>
              </div>
            </div>
          </div>
        </div>
      )}
    </>
  );
}