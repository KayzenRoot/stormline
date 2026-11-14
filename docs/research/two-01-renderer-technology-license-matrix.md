# TWO-01 — Native 2D Renderer, Text and Vector Technology/License Matrix

**Research #147** | NLE-P00-WO-002-TWO-01 | PROPOSED, **NO DEPENDENCIES INSTALLED**, no fixed version/ABI/art/benchmark.

| Candidate | Class | Platform / operational limitations | License and asset gate | Future proof |
|---|---|---|---|---|
| Original contiguous GPU instance sprite batching | NECESSARY proposed baseline | GFX-01/03, WebGL2 instancing/sampler limits | self-owned only after engine license decision | no transparent reorder/quality loss |
| CPU math/draw-list reference | NECESSARY | no real GPU screenshots, renderer backend separated | self-owned | sprite/clip/golden transforms |
| ThorVG vector renderer | IMPORTANT optional bounded path | SVG Tiny subset, Lottie animation subset, native/web build proof | MIT upstream; codec/tool/asset rights transitive | vector benchmark vs custom tessellator |
| Skia Ganesh/Graphite | IMPORTANT broad alternative | large stack/ABI/backend build and GPU interoperability cost | BSD core plus transitive SBOM | binary size, raster parity and ops cost |
| Blend2D | IMPORTANT CPU optional | C++ zlib, CPU SIMD/JIT + AsmJit; W^X and WebAssembly JIT restrictions | zlib with transitive AsmJit notice | no-JIT fallback and raster quality |
| lyon Rust tessellation | IMPORTANT path alternative | Rust toolchain/FFI and no built-in anti-aliasing | selectable MIT / Apache-2.0 / MPL-2.0, exact crate/deps | edge AA and path correctness |
| msdfgen (core/extensions) | IMPORTANT text/shape option | tiny pixel text often poorer vs hinted grayscale, MSDF UV/mips | MIT core, ext FreeType/TinyXML2/libpng/optional Skia, font rights | tiny glyph, MSDF sharp corner artifact |
| HarfBuzz | NECESSARY candidate shaping | shaping not full bidi layout, Unicode grapheme/input/IME/line wrap separate | upstream old MIT terms, exact source/dep notices | Arabic/Indic/CJK and variation |
| FreeType | IMPORTANT glyph raster | FTL credit OR GPLv2 choice; font asset license separately | upstream dual license, FTL needs citation/credit, not MIT | grayscale hint, glyph privacy/source |
| Rive C++ runtime/renderer | FUTURE optional asset interop | runtime MIT but art/editor/CLI file-export rights and splash | MIT runtime; free exports splash, paid removes; art licenses separate | no paid core path or required brand splash |
| Lottie/SVG import | IMPORTANT limited interop | SVG Tiny != SVG2, Lottie effects subsets, untrusted files and URL embeds | external content copyright, sanitizer quotas | unsupported SVG explicit warning |
| Pure path + GPU tessellation | OPTIONAL | shader features, AA/clipping and invalid geometry, WebGL2 compute absent | original code | benchmark vs CPU raster/ThorVG |
| 2D normal-mapped lights | IMPORTANT integration | GFX-06 lights and masks, no Canvas light solver | no duplication, material owners | lit sprite/occluder parity |
| Pixel snapping and native 2D camera | NECESSARY | fractional DPI/rotated camera needs explicit continuous policy | original math | high DPI / pixel art readability |
| S2CC clarity governor | OPTIONAL prove-or-drop | extra cache overhead, clip/order/readability failures | R&D idea not novel proven | image-cost Pareto against static |

## Licensing/security caveats
- FreeType is NOT simply MIT. Official site offers FTL (BSD-like with credit obligation) or GPLv2. Font binaries have separate redistribution/embedding and vendor licensing.
- HarfBuzz shapes OpenType, not complete BiDi/IME/text editing. Unicode algorithm dependencies and ICU-like data must be evaluated separately.
- Rive C++ runtime/renderer is MIT, but upstream `rive-runtime` README states free export contains Rive splash; removing requires paid plan. No account/payment/branding assumption in Stormline core.
- ThorVG MIT is not automatically full SVG 2.0; upstream documents SVG Tiny subset. Skia BSD core may require large transitive deps; Blend2D zlib/JIT has runtime platform restrictions, lyon toolchain/FI cost and optional multiple licenses. Do not present all as zero-cost drop-in on Web.
- msdfgen MIT **core** and its extras have distinct FreeType, Skia, PNG and TinyXML2 dependencies. Font and sample artwork rights never follow a graphics library license.
- SVG input may contain scripts, external resources, XML entities and large paths; DATA-03 must sanitize and cap before tessellation/runtime. Reject source import triggered by user-supplied external URLs in MCP.
- No measured frame-times or color accuracy here, no SDK pinned/installed, no hardware compatibility guarantee. Confirm exact revision/NOTICE/SBOM before implementation #37.

## Upstream research references (documentation only)
- Skia BSD and cross-platform 2D: https://skia.org/docs/
- ThorVG MIT, SVG Tiny/Lottie subset: https://www.thorvg.org/about
- Blend2D zlib CPU JIT: https://blend2d.com/
- lyon Rust tessellation MIT/Apache-2.0/MPL-2.0: https://github.com/nical/lyon
- msdfgen MIT core; ext FreeType/TinyXML2/libpng/Skia: https://github.com/Chlumsky/msdfgen
- HarfBuzz shaping: https://github.com/harfbuzz/harfbuzz
- FreeType FTL with attribution versus GPLv2: https://freetype.org/license
- Rive C++ runtime MIT, optional proprietary authoring/free splash export conditions: https://github.com/rive-app/rive-runtime
- WebGPU limits/canvas semantics: https://www.w3.org/TR/webgpu/
- W3C SVG external resource/security considerations: https://www.w3.org/wiki/SVG_Security
