'use client';

import { useState } from 'react';
import FileUpload from '@/components/FileUpload';
import CADViewer from '@/components/CADViewer';
import LayerPanel from '@/components/LayerPanel';
import GlobalDropHandler from '@/components/GlobalDropHandler';
import { SXFDocument } from '@/types/sxf';
import { CADDocument } from '@/types/p21';

export default function Home() {
  const [document, setDocument] = useState<CADDocument | null>(null);

  const handleFileLoaded = (doc: CADDocument) => {
    setDocument(doc);
  };

  const handleLayerVisibilityChange = (layerIndex: number, visible: boolean) => {
    if (!document) return;

    const updatedDocument = {
      ...document,
      layers: document.layers.map((layer, index) =>
        index === layerIndex ? { ...layer, visible } : layer
      )
    };
    setDocument(updatedDocument);
  };

  const handleReset = () => {
    setDocument(null);
  };

  return (
    <main className="min-h-screen bg-gray-50">
      {/* グローバルドロップハンドラー */}
      <GlobalDropHandler 
        onFileLoaded={handleFileLoaded} 
        isActive={!!document} 
      />

      {/* Header */}
      <header className="bg-white border-b border-gray-300 px-6 py-4">
        <div className="flex items-center justify-between">
          <div>
            <h1 className="text-2xl font-bold text-gray-900">CAD Web Viewer</h1>
            <p className="text-sm text-gray-600">
              SXF・STEP Part21対応WebCADビューアー
            </p>
            {document && (
              <p className="text-xs text-blue-600 mt-1">
                読み込み形式: {document.format}
              </p>
            )}
          </div>
          {document && (
            <div className="flex space-x-2">
              <p className="text-xs text-gray-500 self-center">
                画面のどこにでもファイルをドロップできます
              </p>
              <button
                onClick={handleReset}
                className="px-4 py-2 bg-gray-600 text-white rounded hover:bg-gray-700"
              >
                新しいファイル
              </button>
            </div>
          )}
        </div>
      </header>

      {/* Main Content */}
      <div className="flex h-screen" style={{ height: 'calc(100vh - 80px)' }}>
        {!document ? (
          /* File Upload Screen */
          <div className="flex-1 flex items-center justify-center">
            <div className="max-w-lg w-full">
              <FileUpload onFileLoaded={handleFileLoaded} />
            </div>
          </div>
        ) : (
          /* CAD Viewer Screen */
          <>
            {/* Main Viewer Area */}
            <div className="flex-1 relative">
              <CADViewer document={document} />
            </div>

            {/* Side Panel */}
            <LayerPanel
              document={document}
              onLayerVisibilityChange={handleLayerVisibilityChange}
            />
          </>
        )}
      </div>

      {/* Footer */}
      <footer className="bg-white border-t border-gray-300 px-6 py-3">
        <div className="flex items-center justify-between text-sm text-gray-600">
          <div>
            SXF (Standard Exchange Format) ・ STEP Part21 (ISO 10303-21) 対応CADビューアー
          </div>
          <div>
            © 2024 CAD Web Viewer
          </div>
        </div>
      </footer>
    </main>
  );
}