/** @type {import('next').NextConfig} */
const nextConfig = {
  experimental: {
    // WebAssembly support
    esmExternals: 'loose'
  },
  webpack: (config) => {
    // WebAssembly support
    config.experiments = {
      ...config.experiments,
      asyncWebAssembly: true,
    };
    
    // Handle .wasm files
    config.module.rules.push({
      test: /\.wasm$/,
      type: 'webassembly/async',
    });

    return config;
  },
}

module.exports = nextConfig