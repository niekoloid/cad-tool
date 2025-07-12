'use client';

import { useEffect, useRef, useState, useCallback } from 'react';
import { SXFDocument, SXFGeometry, SXFLine, SXFCircle, SXFPolyline } from '@/types/sxf';
import { CADDocument, CADGeometry } from '@/types/p21';

interface CADViewerProps {
  document: CADDocument;
}

interface ViewState {
  scale: number;
  offsetX: number;
  offsetY: number;
}

export default function CADViewer({ document }: CADViewerProps) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [viewState, setViewState] = useState<ViewState>({
    scale: 1,
    offsetX: 0,
    offsetY: 0
  });
  const [isDragging, setIsDragging] = useState(false);
  const [lastMousePos, setLastMousePos] = useState({ x: 0, y: 0 });

  const drawGeometry = useCallback(
    (ctx: CanvasRenderingContext2D, geometry: CADGeometry, viewState: ViewState) => {
      ctx.save();
      
      // Apply view transformation
      ctx.translate(viewState.offsetX, viewState.offsetY);
      ctx.scale(viewState.scale, viewState.scale);

      // Set style based on geometry properties
      const layer = document.layers.find(l => l.id === geometry.layer) || document.layers[0];
      ctx.strokeStyle = geometry.style?.color || layer?.color || '#000000';
      ctx.lineWidth = (geometry.style?.lineWidth || 1) / viewState.scale;

      // Draw based on geometry type
      switch (geometry.type) {
        case 'line':
          if (geometry.geometry.start && geometry.geometry.end) {
            ctx.beginPath();
            ctx.moveTo(geometry.geometry.start.x, geometry.geometry.start.y);
            ctx.lineTo(geometry.geometry.end.x, geometry.geometry.end.y);
            ctx.stroke();
          }
          break;
          
        case 'circle':
          if (geometry.geometry.center && geometry.geometry.radius) {
            ctx.beginPath();
            ctx.arc(
              geometry.geometry.center.x, 
              geometry.geometry.center.y, 
              geometry.geometry.radius, 
              0, 
              2 * Math.PI
            );
            ctx.stroke();
          }
          break;
          
        case 'arc':
          if (geometry.geometry.center && geometry.geometry.radius) {
            ctx.beginPath();
            const startAngle = geometry.geometry.startAngle || 0;
            const endAngle = geometry.geometry.endAngle || Math.PI * 2;
            ctx.arc(
              geometry.geometry.center.x,
              geometry.geometry.center.y,
              geometry.geometry.radius,
              startAngle,
              endAngle
            );
            ctx.stroke();
          }
          break;
          
        case 'polyline':
          if (geometry.geometry.points && geometry.geometry.points.length > 1) {
            ctx.beginPath();
            ctx.moveTo(geometry.geometry.points[0].x, geometry.geometry.points[0].y);
            for (let i = 1; i < geometry.geometry.points.length; i++) {
              ctx.lineTo(geometry.geometry.points[i].x, geometry.geometry.points[i].y);
            }
            ctx.stroke();
          }
          break;
          
        case 'ellipse':
          if (geometry.geometry.center && geometry.geometry.radiusX && geometry.geometry.radiusY) {
            ctx.beginPath();
            ctx.ellipse(
              geometry.geometry.center.x,
              geometry.geometry.center.y,
              geometry.geometry.radiusX,
              geometry.geometry.radiusY,
              geometry.geometry.rotation || 0,
              0,
              2 * Math.PI
            );
            ctx.stroke();
          }
          break;
          
        case 'point':
          if (geometry.geometry.x !== undefined && geometry.geometry.y !== undefined) {
            ctx.beginPath();
            ctx.arc(geometry.geometry.x, geometry.geometry.y, 2 / viewState.scale, 0, 2 * Math.PI);
            ctx.fill();
          }
          break;
          
        case 'text':
          if (geometry.geometry.position && geometry.geometry.text) {
            ctx.fillStyle = geometry.style?.color || '#000000';
            ctx.font = `${(geometry.geometry.height || 12) / viewState.scale}px Arial`;
            ctx.fillText(
              geometry.geometry.text,
              geometry.geometry.position.x,
              geometry.geometry.position.y
            );
          }
          break;
      }

      ctx.restore();
    },
    [document.layers]
  );

  const redraw = useCallback(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;

    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    // Clear canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Set background
    ctx.fillStyle = '#ffffff';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Draw grid (optional)
    ctx.save();
    ctx.translate(viewState.offsetX, viewState.offsetY);
    ctx.scale(viewState.scale, viewState.scale);
    
    ctx.strokeStyle = '#f0f0f0';
    ctx.lineWidth = 0.5 / viewState.scale;
    
    const gridSize = 50;
    const startX = Math.floor(-viewState.offsetX / viewState.scale / gridSize) * gridSize;
    const startY = Math.floor(-viewState.offsetY / viewState.scale / gridSize) * gridSize;
    const endX = startX + (canvas.width / viewState.scale) + gridSize;
    const endY = startY + (canvas.height / viewState.scale) + gridSize;

    ctx.beginPath();
    for (let x = startX; x <= endX; x += gridSize) {
      ctx.moveTo(x, startY);
      ctx.lineTo(x, endY);
    }
    for (let y = startY; y <= endY; y += gridSize) {
      ctx.moveTo(startX, y);
      ctx.lineTo(endX, y);
    }
    ctx.stroke();
    ctx.restore();

    // Draw geometries
    document.geometries.forEach(geometry => {
      const layer = document.layers.find(l => l.id === geometry.layer);
      if (!layer || !layer.visible) return;
      
      drawGeometry(ctx, geometry, viewState);
    });
  }, [document, viewState, drawGeometry]);

  // Redraw when view state or document changes
  useEffect(() => {
    redraw();
  }, [redraw]);

  // Mouse event handlers
  const handleMouseDown = useCallback((e: React.MouseEvent) => {
    setIsDragging(true);
    setLastMousePos({ x: e.clientX, y: e.clientY });
  }, []);

  const handleMouseMove = useCallback((e: React.MouseEvent) => {
    if (isDragging) {
      const deltaX = e.clientX - lastMousePos.x;
      const deltaY = e.clientY - lastMousePos.y;
      
      setViewState(prev => ({
        ...prev,
        offsetX: prev.offsetX + deltaX,
        offsetY: prev.offsetY + deltaY
      }));
      
      setLastMousePos({ x: e.clientX, y: e.clientY });
    }
  }, [isDragging, lastMousePos]);

  const handleMouseUp = useCallback(() => {
    setIsDragging(false);
  }, []);

  const handleWheel = useCallback((e: React.WheelEvent) => {
    e.preventDefault();
    
    const rect = canvasRef.current?.getBoundingClientRect();
    if (!rect) return;

    const mouseX = e.clientX - rect.left;
    const mouseY = e.clientY - rect.top;
    
    const scaleFactor = e.deltaY > 0 ? 0.9 : 1.1;
    const newScale = Math.max(0.1, Math.min(10, viewState.scale * scaleFactor));
    
    setViewState(prev => ({
      scale: newScale,
      offsetX: mouseX - (mouseX - prev.offsetX) * (newScale / prev.scale),
      offsetY: mouseY - (mouseY - prev.offsetY) * (newScale / prev.scale)
    }));
  }, [viewState.scale]);

  // Fit to content
  const fitToContent = useCallback(() => {
    if (!document.geometries.length) return;

    let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;

    document.geometries.forEach(geometry => {
      switch (geometry.type) {
        case 'line':
          if (geometry.geometry.start && geometry.geometry.end) {
            minX = Math.min(minX, geometry.geometry.start.x, geometry.geometry.end.x);
            minY = Math.min(minY, geometry.geometry.start.y, geometry.geometry.end.y);
            maxX = Math.max(maxX, geometry.geometry.start.x, geometry.geometry.end.x);
            maxY = Math.max(maxY, geometry.geometry.start.y, geometry.geometry.end.y);
          }
          break;
        case 'circle':
        case 'arc':
          if (geometry.geometry.center && geometry.geometry.radius) {
            minX = Math.min(minX, geometry.geometry.center.x - geometry.geometry.radius);
            minY = Math.min(minY, geometry.geometry.center.y - geometry.geometry.radius);
            maxX = Math.max(maxX, geometry.geometry.center.x + geometry.geometry.radius);
            maxY = Math.max(maxY, geometry.geometry.center.y + geometry.geometry.radius);
          }
          break;
        case 'ellipse':
          if (geometry.geometry.center && geometry.geometry.radiusX && geometry.geometry.radiusY) {
            minX = Math.min(minX, geometry.geometry.center.x - geometry.geometry.radiusX);
            minY = Math.min(minY, geometry.geometry.center.y - geometry.geometry.radiusY);
            maxX = Math.max(maxX, geometry.geometry.center.x + geometry.geometry.radiusX);
            maxY = Math.max(maxY, geometry.geometry.center.y + geometry.geometry.radiusY);
          }
          break;
        case 'polyline':
          if (geometry.geometry.points) {
            geometry.geometry.points.forEach((point: any) => {
              minX = Math.min(minX, point.x);
              minY = Math.min(minY, point.y);
              maxX = Math.max(maxX, point.x);
              maxY = Math.max(maxY, point.y);
            });
          }
          break;
        case 'point':
          if (geometry.geometry.x !== undefined && geometry.geometry.y !== undefined) {
            minX = Math.min(minX, geometry.geometry.x);
            minY = Math.min(minY, geometry.geometry.y);
            maxX = Math.max(maxX, geometry.geometry.x);
            maxY = Math.max(maxY, geometry.geometry.y);
          }
          break;
      }
    });

    if (minX !== Infinity) {
      const canvas = canvasRef.current;
      if (!canvas) return;

      const contentWidth = maxX - minX;
      const contentHeight = maxY - minY;
      const padding = 50;

      const scaleX = (canvas.width - padding * 2) / contentWidth;
      const scaleY = (canvas.height - padding * 2) / contentHeight;
      const newScale = Math.min(scaleX, scaleY, 2);

      const centerX = (minX + maxX) / 2;
      const centerY = (minY + maxY) / 2;

      setViewState({
        scale: newScale,
        offsetX: canvas.width / 2 - centerX * newScale,
        offsetY: canvas.height / 2 - centerY * newScale
      });
    }
  }, [document.geometries]);

  return (
    <div className="relative w-full h-full">
      {/* Toolbar */}
      <div className="toolbar absolute top-0 left-0 right-0 z-10 bg-white border-b border-gray-300">
        <button
          onClick={fitToContent}
          className="toolbar-button"
        >
          全体表示
        </button>
        <button
          onClick={() => setViewState(prev => ({ ...prev, scale: prev.scale * 1.2 }))}
          className="toolbar-button"
        >
          拡大
        </button>
        <button
          onClick={() => setViewState(prev => ({ ...prev, scale: prev.scale * 0.8 }))}
          className="toolbar-button"
        >
          縮小
        </button>
        <span className="text-sm text-gray-600 ml-4">
          倍率: {(viewState.scale * 100).toFixed(0)}%
        </span>
      </div>

      {/* Canvas */}
      <canvas
        ref={canvasRef}
        width={800}
        height={600}
        className="cad-canvas absolute top-16 left-0 w-full h-full"
        style={{ height: 'calc(100% - 4rem)' }}
        onMouseDown={handleMouseDown}
        onMouseMove={handleMouseMove}
        onMouseUp={handleMouseUp}
        onMouseLeave={handleMouseUp}
        onWheel={handleWheel}
      />
    </div>
  );
}