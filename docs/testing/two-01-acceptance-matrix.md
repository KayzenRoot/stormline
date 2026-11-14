# TWO-01 — Future Canvas, Sprite, Vector and Text Test Matrix

**Research #147 | WO NLE-P00-WO-002-TWO-01 | Future implementation #37 BLOCKED.**  
**ALL 81 TESTS ARE FUTURE / NOT EXECUTED.** No C++ renderer, GPU shaders, pixels, font shaping binary, memory profiling or native hardware test run. Exact test fixtures/assets/licenses/numeric tolerances to be approved before first code slice.

| ID | Required future proof | Evidence |
|---|---|---|
| CAN-001 | Canvas project/SceneId and revision stable, typed snapshot | unit |
| CAN-002 | Logical/device/world pixel conversion and DPI exact | CPU golden |
| CAN-003 | Orthographic camera, positive/negative zoom and aspect | math |
| CAN-004 | Integer scale letterbox/pillarbox preserves pixel grid | 2D golden |
| CAN-005 | Fractional zoom and subpixel camera preserve sharpness policy | 2D motion |
| CAN-006 | Rotated camera does not force illegal pixel snapping | 2D motion |
| CAN-007 | Camera cut/viewport resize rebases safely | GPU |
| CAN-008 | Multiple canvases split-screen isolation and clip | GPU |
| CAN-009 | NaN/Inf/singular transform rejected with typed error | fuzz |
| CAN-010 | Camera/output GFX-07 color and UI jitter separation | integration |
| CAN-011 | Display DPI change 1x/1.25x/1.5x/2x controlled | native |
| SPR-001 | Atlas region UV bounds, pivot, trim and rotate correct | CPU unit |
| SPR-002 | Sprite flip x/y/negative transform ordering correct | golden |
| SPR-003 | Nine slice tiny rectangle nonnegative corners | unit |
| SPR-004 | Nearest pixel-art integer scale sharp | 2D golden |
| SPR-005 | Linear atlas filtering gutter/edge extrusion bleed absent | GPU |
| SPR-006 | Mipmapped rotated atlas edge neighborhood safe | GPU |
| SPR-007 | sRGB/linear sprite tint exactly one decode | GFX-05 |
| SPR-008 | Premultiplied alpha vs straight source-over correctness | numeric |
| SPR-009 | Repack atlas revision invalidates GPU descriptors | fault |
| SPR-010 | Streaming missing sprite placeholder/typed failure | DATA-05 |
| SPR-011 | Per-target texture sampler caps WebGL2 fallback | browser |
| SPR-012 | Distant/near sprite coverage and overdraw estimate | benchmark |
| LYR-001 | Painter order transparent overlapping sprites preserved | golden |
| LYR-002 | Contiguous compatible run batching count correct | unit |
| LYR-003 | Opaque nonoverlap reorder only after explicit proof | unit |
| LYR-004 | Nested layer group opacity compositing exact | golden |
| LYR-005 | Additive/multiply/source-over blend order correct | golden |
| LYR-006 | Clip scissor nesting and stencil bounds finite | fuzz/GPU |
| LYR-007 | Clip depth exceeding quota fails typed | security |
| LYR-008 | Mask/offscreen isolation and alpha not double applied | golden |
| LYR-009 | High DPI blurred HUD false under TAA and upscale | GFX-07 |
| LYR-010 | 2.5D layer Z sorting future TWO-04 boundary | architecture |
| VEC-001 | Path line quadratic cubic Bézier sample correct | CPU |
| VEC-002 | Even-odd versus nonzero winding fill hole correct | golden |
| VEC-003 | Degenerate closed path and zero-length stroke safe | fuzz |
| VEC-004 | Miter/caps/dash joins no explosive tessellation | CPU fuzz |
| VEC-005 | Self-intersections and winding fallback | golden |
| VEC-006 | Gradient linear/radial colors scene-linear correct | color |
| VEC-007 | SVG Tiny supported feature catalog explicit | import |
| VEC-008 | SVG2 unsupported features produce warning not silent draw | import |
| VEC-009 | SVG script/foreignObject/external URL rejected | security |
| VEC-010 | SVG XML entity expansion/long path/quota denied | fuzz |
| VEC-011 | ThorVG optional native vs CPU fallback and license | R&D |
| VEC-012 | Skia/Blend2D/lyon binary-cost port benchmarking | R&D |
| TXT-001 | HarfBuzz ligatures and kerning glyph plan exact | text |
| TXT-002 | RTL Arabic joining and full bidi layout ownership | locale |
| TXT-003 | Indic clusters/combining mark positions correct | locale |
| TXT-004 | CJK fallback glyph selection and missing rights | locale |
| TXT-005 | Emoji ZWJ/color font failover explicit | locale |
| TXT-006 | Variable font axis and size/shaping cache correctness | text |
| TXT-007 | Small hinted grayscale vs MSDF actual image quality | golden |
| TXT-008 | MSDF edge/color artifact under downscale | golden |
| TXT-009 | Font fallback without illegal system font embedding | license |
| TXT-010 | FreeType FTL credit/GPLv2 choice verified | license |
| TXT-011 | Glyph atlas LRU eviction fence and device generation | GPU |
| TXT-012 | Text baseline and line metrics unjittered | 2D |
| TXT-013 | IME/selection/accessible tree intentionally UI owned | architecture |
| LIT-001 | Normal-mapped lit sprite uses GFX-06 light channel | integration |
| LIT-002 | Canvas 2D shadow layers only GFX-06 owner | architecture |
| LIT-003 | GFX-08 particles use sprite drawing without simulator duplicate | integration |
| LIT-004 | Unlit rendering with unavailable lighting still works | low-end |
| SYS-001 | WebGL2 path without compute native text+sprite baseline | browser |
| SYS-002 | WebGPU canvas feature limits verified per adapter | browser |
| SYS-003 | Windows Vulkan and D3D12 pixel capture | native |
| SYS-004 | Linux Vulkan capture and texture atlas upload | native |
| SYS-005 | macOS Apple Silicon Metal native canvas capture | native |
| SYS-006 | GPU device loss and recover without stale atlas/glyph | fault |
| SYS-007 | Project-scope Editor/CLI/MCP revision conflict denied | security |
| SYS-008 | Untrusted font/SVG/image parsing sandbox import | fuzz |
| SYS-009 | Rive MIT runtime vs editor/free-export splash flagged | legal |
| SYS-010 | msdfgen core/extensions transitive SBOM audited | legal |
| SYS-011 | No paid runtime or unsupervised host file fetch | security |
| BEN-001 | Named device 60fps scene fixture p50/p95/p99 | hardware |
| BEN-002 | Batch draw reduction vs exact transparent output image | benchmark |
| BEN-003 | Sprite count vs screen-space alpha overdraw p99 | benchmark |
| BEN-004 | High DPI pixel art and text SSIM/edge sharpness | benchmark |
| BEN-005 | Vector tessellation/CPU raster/ThorVG quality-cost frontier | benchmark |
| BEN-006 | S2CC prove-or-drop vs stable batch policy | R&D |
| BEN-007 | VRAM/UMA unknown memory source not faked | budget |
| BEN-008 | Unreal/Godot/Skia comparison only matched original scenes | benchmark |

## Future golden assets / acceptance gates
- Rights-cleared sprite sheet, trim/rotate atlas with padded mips and alpha, 2D pixel-art tiles, UI text/icon atlas, vector logo gradients/path strokes, complex multilingual font licenses, orthographic parallax scene and many translucent overlapping quads. No proprietary Godot/Skia/Unreal/Rive artwork.
- CPU deterministic math/reference for transform, UV, path tessellation, painter order and font glyph-metrics. Native GPU screenshot evidence is separately mandatory and cannot be replaced with a CPU numeric PASS. Future font shaping tests need exact Unicode and actual licensed font files.
- For 60 FPS: freeze hardware class, OS, GPU driver, backend, physical resolution, pixel density, sprite count, atlas sizes/texture formats, alpha/overdraw and visibility, shader build, frame cap/VSYNC/VRR and warmup. Measure per pass vs total frame p50/p95/p99 GPU+CPU, VRAM/UMA, draw counts and screen-space overdraw. **No number can be implied as already satisfied.**
- Quality: layer painter-order oracle, alpha/gamut difference, sprite edge bleed pixels, UI contrast/legibility, integer pixel sharpness and scalable glyph accuracy at multiple DPIs. Numeric tolerances and CI platform/hardware still UNDECIDED.
- Security/license: malformed SVG/XML and font (data bombs/host paths/external URL/scripting), atlas overflow, nested clip quota, signed device-fence invalidation, cross-project MCP, Rive splash/editor rights, FreeType FTL attribution, source SBOM; no HIGH/CRITICAL before code.
