# CAD Web Viewer

SXF (Standard Exchange Format) と STEP Part21 (ISO 10303-21) 形式に対応したWebベースCADビューアー

## 機能

- **SXF形式対応**: .sxf, .sfc ファイルの読み込みと表示
- **STEP Part21対応**: .p21, .stp, .step ファイルの読み込みと表示
- **統一インターフェース**: 両形式を同じUIで操作
- **インタラクティブ表示**: ズーム、パン、レイヤー切り替え
- **メタデータ表示**: 図面情報、作成者、組織等の詳細表示

## 対応形式

### SXF (Standard Exchange Format)
日本の建設業界で使用される2D CADデータ交換標準

### STEP Part21 (ISO 10303-21)
国際標準のCADデータ交換形式

## 技術仕様

- **フロントエンド**: Next.js 14, TypeScript, Tailwind CSS
- **レンダリング**: Canvas 2D API
- **パーサー**: WebAssembly (フォールバック: JavaScript)
- **対応幾何要素**: 線、円、弧、楕円、ポリライン、点、テキスト

## 開発

```bash
# 依存関係のインストール
npm install

# 開発サーバー起動
npm run dev

# ビルド
npm run build
```

## デプロイ

Vercel等のプラットフォームでの自動デプロイに対応。WebAssemblyコンパイラが利用できない環境では自動的にJavaScriptフォールバックを使用。

## ライセンス

MIT License
