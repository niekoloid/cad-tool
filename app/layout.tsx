import type { Metadata } from 'next'
import './globals.css'

export const metadata: Metadata = {
  title: 'SXF Web Viewer',
  description: 'Web-based CAD viewer for SXF (Standard Exchange Format) files',
}

export default function RootLayout({
  children,
}: {
  children: React.ReactNode
}) {
  return (
    <html lang="ja">
      <body className="bg-gray-50">{children}</body>
    </html>
  )
}