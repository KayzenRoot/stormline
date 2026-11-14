# TWO-01 — Stormline Native 2D Renderer & Canvas

**Research #147 | WO NLE-P00-WO-002-TWO-01 | Future implementation #37 BLOCKED**  
**BASE main `2ec91d4cf0f3062745a5d4b6d340da7027317348`** | **Status PROPOSED, DOCS ONLY**. No GPU/CPU renderer, executable engine, 60 FPS proof, shader or installed third-party software. Risk LOW docs, future ELEVATED native graphics, external vector/font assets.

## Mission: pixel-perfect and cinematic 2D, not just flat 3D
A native Canvas scene semantics with stable sprites, layers, cameras, clipping, optional vector/text paths, atlases, texture/filter/color precision and transparent batching. First-class 2D/2.5D, Web and Win/Linux/macOS, with CPU/headless mathematical oracle and conservative WebGL2 non-compute fallback. Actual 60 FPS per catalog is future benchmark target only under specified scene, hardware and numeric quality criteria.

## Boundary map
| Authority | TWO-01 interaction, no duplicate |
|---|---|
| DATA-01/02/03/04/05 | permanent CanvasId/SpriteAssetId/FontAssetId, asset rights, safe image/font/SVG import, scene edit journal, cooked atlas/texture/glyph manifest |
| GFX-01 | native/API/Web device backend, screen/display/swapchain/feature+device-generation |
| GFX-02 | shader compiler/layout/variants, no Canvas-specific compiler or arbitrary user shaders |
| GFX-03 | RenderGraph/buffers/VRAM/transient instances/fence+device loss; TWO-01 only submits typed pass/resource plans |
| GFX-04/05 | bounded visibility/culling/LOD; material/texture/alpha/linear light and atlas sampling |
| GFX-06 | 2D lights, sprite normal-map occluders, shadows and GI; Canvas only requests typed lighting |
| GFX-07 | ortho view/viewport/output SDR/HDR, pixel-jitter/history/post; Canvas preserves crisp unjittered UI |
| GFX-08 | sprites from VFX pipeline, no Canvas-owned particle simulation |
| TWO-02/03/04 | tilemap/world, animation/timeline, hybrid 2.5D, later separate modules |
| WORLD, EDIT, UI, CORE | world identity/coordinates/time, editor widgets/input/IME and accessibility semantics, not Canvas-controlled game logic |

## Canvas coordinate and image truth
- `Canvas2DSceneV1` stable project+SceneId+CanvasId/revision, logical design pixels, target viewport, camera, DPI/device pixels and per-layer space. Explicit transform handedness, top-left/Y coordinate, pixel-center and world/logical/physical scale; finite validation, no NaN/Inf/overflow.
- `Camera2DV1` orthographic world/logical transform, integer/snap/continuous modes; correct integer nearest-neighbor scale with letterbox/pillarbox and fractional DPI/zoom policy. Rotated/animated camera may need continuous sampling instead of forced snapping. UI/text/pixel art always unjittered unless explicitly opted in; GFX-07 owns camera output.
- Immutable `CanvasLayerV1` order/id, group masks, isolation alpha, blend, clip, transparency and deterministic submission index. Painter order is semantic: **never re-sort overlapping alpha across layers, masks or paint groups to reduce draw calls**. Batch only contiguous compatible draw spans or proven equivalent opaque disjoint spans; stable sort by layer/order/stable submission sequence.
- Source-over premultiplied alpha with explicit additive/multiply alternatives, defined sampling in scene-linear/sRGB compatible with GFX-05 and GFX-07. No double gamma or accidental HUD tone-mapping. Offscreen alpha group composition must preserve opacity semantics.
- Nested scissor/stencil/path clipping with bounded depth; unsupported clip operation must degrade visibly or fail typed, not silently leak pixels.

## Sprite, nine-slice and atlas pipeline
- Typed `SpriteDrawV1`: source asset+revision, atlas region/gutter/UV, pivot, trim/flip/rotation, nine-slice, material, tint in correct alpha/color space, layer/clip/transform and device generation. CPU reference validates UV and ordering without GPU.
- GPU sprite instance buffer+quad drawing is baseline candidate; GFX-03 schedules buffer uploads/draws/fences. WebGL2 bounded texture-unit and instancing fallback; no required WebGPU storage or compute for 2D. CPU-only headless plan never claims actual screenshot.
- Atlas source ownership DATA-03, cooking DATA-05, VRAM GFX-03. Stable per-target atlas manifest, mips, gutters/edge extrusion to prevent bleed, UV texel-center, rotatable packing and immutable version table. Repack/streaming/texture loss invalidates old instances after fences; handle source deletion and missing atlas generation with typed fallback. No second atlas importer or GPU allocator.
- Texture nearest+integer scale for crisp pixel art; smooth vector/text and high DPI filtering per profile. Nine-slice corner dimensions must remain nonnegative; negative/world transform and 0-width slices safe. Sprite batching cost measured as contiguous spans and GPU driver draw calls, not guessed.

## Vector shapes, SVG, text
- `VectorPathV1` lines/quadratic/cubic, contours fill EVEN_ODD/NON_ZERO, stroke join/cap/dash/miter, linear/radial gradient, transform and bounded scissor/path mask. CPU tessellation/raster fallback, triangles via GFX-02 shader and GFX-03 graph. Self-intersection, winding, degenerate stroke, enormous coordinates and excessive tessellation rejected/guarded.
- **Technology policy proposed:** original Canvas sprite renderer; ThorVG MIT optional bounded SVG Tiny/vector adapter (not full SVG2), Skia BSD broad alternative with large stack, Blend2D zlib CPU raster/JIT where host policy allows (JIT not universal on Web/restricted targets), lyon Rust MIT/Apache/MPL path tessellation if FFI cost justified. Never leak third-party ABI into public SDK.
- Imported SVG/XML via DATA-03 **sanitizer** only: no script/foreignObject, remote URL/XML external entity, CSS external font/image, arbitrary filter/download, unbounded recursion/segments/time/size. Unsupported features produce visible warning/rejection; do not claim all SVG2.
- Text responsibility: TWO-01 renders validated glyph runs and glyph atlases; higher UI/EDIT owns text input, IME, bidirectional line layout/selection, accessibility tree. HarfBuzz shapes complex glyph sequences but is NOT complete BiDi/line breaking/IME; FreeType candidate raster/hinting choose FTL credit or GPLv2 explicitly; msdfgen MIT core for MSDF large scale, ext deps separately. Font files have independent embed/redistribution licenses, no arbitrary system font copies. Latin/Arabic/Indic/CJK/emoji coverage and tiny grayscale vs MSDF sampling tested individually.
- Color emoji, variable fonts, fallback and atlas glyph cache by font revision/size/hinting/script/DPI/locale and device generation, capped VRAM/fence eviction. Missing glyph yields explicit fallback or reported error, not tofu masked as PASS.

## 2D lighting, VFX, visuals and quality
- Unlit Canvas baseline always; optional 2D normal-mapped sprites, source/projection and 2D cast shadows only GFX-06. GFX-08 2D VFX submits Canvas draw plans with stable layer order. GFX-07 exposure/AA/post and native-res HUD composition; pixel-art should not be forced through temporal jitter or frame reconstruction.
- `CanvasQualityBudgetV1`: sprite count, batch count, alpha overdraw pixels, atlas/glyph bytes, clip depth, vector path segments/raster scale, CPU/GPU time and total frame, device caps, fallback choices; actual vs ESTIMATED/UNKNOWN provenance. Correct painter order, UI legibility and predictable frame time outrank draw-call count.
- WebGL2 reduced native/CPU-tessellation fallback, WebGPU instanced path after feature checks, Vulkan/DX12/Metal equivalent semantic tests. Headless maths/UV/clip/text receipts never count as GPU success. Real 60FPS target needs named GPU, OS, resolution, atlas/fonts, camera and p95/p99 measurements.
- Invalid imported assets, font/SVG, lost GPU, DPI/layout change, atlas stream/repack and old material revision => safe rebuild/placeholder/typed error with no stale GPU descriptor, unsignaled clip mask or leaked foreign scene data.

## Secure AI-native authoring
Editor/CLI/MCP shared kernel `InspectCanvas`, `InspectLayer`, `PreviewCanvasBatch`, `PreviewCanvasBudget`, `GetCanvasReceipt`, and `Stage/Validate/CommitCanvasEdit` with expected revision, asset rights and DATA-04 transaction/rollback. No arbitrary SVG/HTML/JS execution, URL fetch, direct GPU memory access, unsafe font/script upload, cross-project leakage or unbounded scene graph. Preview is estimate, not measured/rendered preview.

## R&D prove-or-drop
**S2CC** clarity-conscious render optimizer: adapt atlas sampling, batch cache, vector tessellation and pixel-art preservation under overdraw/DPI without altering painter order. Independent research HYPOTHESIS, not proven novel or faster. Compare fixed stable batches, ordinary atlases and CPU fallback with matched image reference.

## Future code activation
Release classes/DoD, exact C++/shader ABI/file inventory, implemented & audited GFX-01/DATA-03, GFX-03/05/06/07 integration, font and tool licenses/NOTICE/SBOM, first-class WebGL2/native targets, actual 60FPS fixture+numerical tolerances and 2D golden screenshots, SHA-256 Context Lock. #37 remains BLOCKED and all 80 future implementations executor_ready=false.

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
