'use client';

import { useState } from 'react';
import { SXFDocument, SXFLayer } from '@/types/sxf';
import { CADDocument } from '@/types/p21';

interface LayerPanelProps {
  document: CADDocument;
  onLayerVisibilityChange: (layerIndex: number, visible: boolean) => void;
}

export default function LayerPanel({ document, onLayerVisibilityChange }: LayerPanelProps) {
  const [isExpanded, setIsExpanded] = useState(true);

  const handleVisibilityToggle = (layerIndex: number) => {
    const layer = document.layers[layerIndex];
    onLayerVisibilityChange(layerIndex, !layer.visible);
  };

  const handleAllVisible = () => {
    document.layers.forEach((_, index) => {
      onLayerVisibilityChange(index, true);
    });
  };

  const handleAllHidden = () => {
    document.layers.forEach((_, index) => {
      onLayerVisibilityChange(index, false);
    });
  };

  return (
    <div className="w-64 bg-white border-l border-gray-300 h-full overflow-hidden flex flex-col">
      {/* Header */}
      <div className="p-4 border-b border-gray-200">
        <div className="flex items-center justify-between">
          <h3 className="text-lg font-medium text-gray-900">レイヤー</h3>
          <button
            onClick={() => setIsExpanded(!isExpanded)}
            className="text-gray-500 hover:text-gray-700"
          >
            <svg
              className={`w-5 h-5 transform transition-transform ${isExpanded ? 'rotate-180' : ''}`}
              fill="none"
              stroke="currentColor"
              viewBox="0 0 24 24"
            >
              <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M19 9l-7 7-7-7" />
            </svg>
          </button>
        </div>
        
        {isExpanded && (
          <div className="mt-2 flex space-x-2">
            <button
              onClick={handleAllVisible}
              className="text-xs px-2 py-1 bg-green-100 text-green-800 rounded hover:bg-green-200"
            >
              すべて表示
            </button>
            <button
              onClick={handleAllHidden}
              className="text-xs px-2 py-1 bg-red-100 text-red-800 rounded hover:bg-red-200"
            >
              すべて非表示
            </button>
          </div>
        )}
      </div>

      {/* Layer List */}
      {isExpanded && (
        <div className="flex-1 overflow-y-auto">
          {document.layers.map((layer, index) => (
            <div
              key={index}
              className={`layer-item ${layer.visible ? 'active' : ''}`}
            >
              <div className="flex items-center space-x-3">
                {/* Visibility Toggle */}
                <button
                  onClick={() => handleVisibilityToggle(index)}
                  className="text-gray-500 hover:text-gray-700"
                >
                  {layer.visible ? (
                    <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
                      <path d="M10 12a2 2 0 100-4 2 2 0 000 4z" />
                      <path fillRule="evenodd" d="M.458 10C1.732 5.943 5.522 3 10 3s8.268 2.943 9.542 7c-1.274 4.057-5.064 7-9.542 7S1.732 14.057.458 10zM14 10a4 4 0 11-8 0 4 4 0 018 0z" clipRule="evenodd" />
                    </svg>
                  ) : (
                    <svg className="w-4 h-4" fill="currentColor" viewBox="0 0 20 20">
                      <path fillRule="evenodd" d="M3.707 2.293a1 1 0 00-1.414 1.414l14 14a1 1 0 001.414-1.414l-1.473-1.473A10.014 10.014 0 0019.542 10C18.268 5.943 14.478 3 10 3a9.958 9.958 0 00-4.512 1.074l-1.78-1.781zm4.261 4.26l1.514 1.515a2.003 2.003 0 012.45 2.45l1.514 1.514a4 4 0 00-5.478-5.478z" clipRule="evenodd" />
                      <path d="M12.454 16.697L9.75 13.992a4 4 0 01-3.742-3.741L2.335 6.578A9.98 9.98 0 00.458 10c1.274 4.057 5.065 7 9.542 7 .847 0 1.669-.105 2.454-.303z" />
                    </svg>
                  )}
                </button>

                {/* Color Indicator */}
                <div
                  className="w-4 h-4 border border-gray-300 rounded"
                  style={{ backgroundColor: layer.color || '#000000' }}
                />

                {/* Layer Name */}
                <span className={`text-sm ${layer.visible ? 'text-gray-900' : 'text-gray-500'}`}>
                  {layer.name}
                </span>
              </div>

              {/* Layer Info */}
              <div className="text-xs text-gray-500">
                {document.geometries.filter(g => g.layer === layer.id).length} 要素
              </div>
            </div>
          ))}
        </div>
      )}

      {/* Document Information */}
      <div className="p-4 border-t border-gray-200 bg-gray-50">
        <h4 className="text-sm font-medium text-gray-900 mb-2">図面情報</h4>
        <div className="space-y-1 text-xs text-gray-600">
          <div><span className="font-medium">形式:</span> {document.format}</div>
          <div><span className="font-medium">タイトル:</span> {document.title}</div>
          {document.metadata.author && (
            <div><span className="font-medium">作成者:</span> {document.metadata.author}</div>
          )}
          {document.metadata.scale && (
            <div><span className="font-medium">縮尺:</span> {document.metadata.scale}</div>
          )}
          {document.metadata.created && (
            <div><span className="font-medium">作成日:</span> {document.metadata.created.toLocaleDateString()}</div>
          )}
          <div><span className="font-medium">レイヤー数:</span> {document.layers.length}</div>
          <div><span className="font-medium">要素数:</span> {document.geometries.length}</div>
        </div>
      </div>
    </div>
  );
}