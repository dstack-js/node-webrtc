<h1 align="center">
  <img height="120px" src="https://upload.wikimedia.org/wikipedia/commons/d/d9/Node.js_logo.svg" />&nbsp;&nbsp;&nbsp;&nbsp;
  <img height="120px" src="https://webrtc.github.io/webrtc-org/assets/images/webrtc-logo-vert-retro-dist.svg" />
</h1>

[![NPM](https://img.shields.io/npm/v/@dstack-js/wrtc.svg)](https://www.npmjs.com/package/@dstack-js/wrtc)

@dstack-js/wrtc is a Node.js Native Addon that provides bindings to [WebRTC M87](https://chromium.googlesource.com/external/webrtc/+/branch-heads/4280). This project aims for spec-compliance and is tested using the W3C's [web-platform-tests](https://github.com/web-platform-tests/wpt) project. A number of [nonstandard APIs](docs/nonstandard-apis.md) for testing are also included. Forked from <https://github.com/corwin-of-amber/node-webrtc> to provide pre-built macOS M1 binaries.

Install
-------

```
npm install @dstack-js/wrtc
```

Installing from NPM downloads a prebuilt binary for your operating system × architecture. Set the `TARGET_ARCH` environment variable to "arm" or "arm64" to download for armv7l or arm64, respectively. Linux and macOS users can also set the `DEBUG` environment variable to download debug builds.

You can also [build from source](docs/build-from-source.md).

Supported Platforms
-------------------

The following platforms are confirmed to work with node-webrtc and have prebuilt binaries available. Since node-webrtc targets [N-API version 3](https://nodejs.org/api/n-api.html), there may be additional platforms supported that are not listed here. If your platform is not supported, you may still be able to [build from source](docs/build-from-source.md).

<table>
  <thead>
    <tr>
      <td colspan="2" rowspan="2"></td>
      <th colspan="3">Linux</th>
      <th colspan="2">macOS</th>
      <th>Windows</th>
    </tr>
    <tr>
      <th>armv7l</th>
      <th>arm64</th>
      <th>x64</th>
      <th>x64</th>
      <th>arm64</th>
      <th>x64</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th rowspan="6">Node</th>
      <th>8</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>10</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>11</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>12</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>13</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>14</th>
        <td align="center">✓</td>
        <td align="center">✓</td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th rowspan="2">Electron</th>
      <th>4</th>
        <td align="center"></td>
        <td align="center"></td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
    <tr>
      <th>5</th>
        <td align="center"></td>
        <td align="center"></td>
        <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
      <td align="center">✓</td>
    </tr>
  </tbody>
</table>

Examples
--------

See [node-webrtc/node-webrtc-examples](https://github.com/dstack-js/node-webrtc-examples).

Contributing
------------

Contributions welcome! Please refer to the [wiki](https://github.com/dstack-js/node-webrtc/wiki/Contributing).
