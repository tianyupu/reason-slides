const path = require('path');
const CopyWebpackPlugin = require('copy-webpack-plugin');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const outputDir = path.join(__dirname, 'build/');
const imageOutputDir = path.join(outputDir, 'img/');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    filename: 'Index.js'
  },
  module: {
    rules: [
      {
        test: /light\.css$/,
        use: [
          {
            loader: 'style-loader',
            options: {
              attrs: {
                id: 'light'
              }
            }
          },
          'css-loader'
        ],
      },
      {
        test: /dark\.css$/,
        use: [
          {
            loader: 'style-loader',
            options: {
              attrs: {
                id: 'dark'
              }
            }
          },
          'css-loader'
        ],
      },
    ],
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: 'src/index.html',
      inject: false
    }),
    new CopyWebpackPlugin([
      { from: './src/slide-content.md', to: outputDir },
      { from: './src/index.css', to: outputDir },
      { from: './src/img/', to: imageOutputDir }
    ])
  ],
  devServer: {
    compress: true,
    contentBase: outputDir,
    port: process.env.PORT || 8000,
    historyApiFallback: true
  }
};
