# TWO-01 — Reproducible 2D Quality & Batching Benchmark Protocol

**Research #147 | WO NLE-P00-WO-002-TWO-01 | NOT EXECUTED**. The catalog's “2D scene 60 FPS with correct sprites and text” is an **unverified future target**. No real renderer or benchmark exists.

## Comparison tracks
1. **Reference exactness**: CPU math for ortho camera/pixel snapping/subpixel vs native, painter alpha group order, UV atlas bleed/gutters, clip/mask and color linear/sRGB, Unicode text glyph positions from independently licensed font shaping. Compare exact owned sprite/paths against reference image/glyph/geometry oracles.
2. **Simple scene**: 100/1000/10000 sprites as **test loads**, not current throughput guarantees; few atlases vs many, opaque vs overlapping alpha, small sprite vs screen-filling translucent background. Record draw calls/overdraw, GPU upload and frame-time.
3. **Real 2D gameplay**: original pixel-art world/tile textures with parallax and camera pans, sprite animations, sprite lights delegated to GFX-06, GFX-08 spell particles and unjittered UI. Mixed DPI/zoom, aspect/letterbox, atlas repack, pause and device recovery.
4. **Vector/text scenario**: complex SVG Tiny paths/nested clips/gradients, fallback for unsupported SVG2, locale text with Arabic/Indic/CJK/emoji using appropriately licensed fonts, MSDF vs hinted grayscale and 1x/2x/4x scale. License report/embedding metadata attached to artifacts.
5. **Cross-platform**: real Windows Vulkan/D3D12, Linux Vulkan, macOS Metal Apple Silicon, WebGPU and WebGL2 browser adapter; no binary/runtime installed now. Compare matched scenes against optional ThorVG/Skia/Blend2D/lyon and Godot/Unreal as publicly lawful algorithmic references, not raw games or non-comparable settings.

## Measurement rules
- Record exact commit/build/compiler/driver/API/OS/monitor/memory/source art hash and font licenses, viewport logical and physical pixels, DPI, render scaling, pixel-snap mode, AA, atlas packing/texture format, GPU cache state, scene camera path and timing sample count.
- Report CPU render-plan/update, GPU uploads, pipeline draw, vector tessellation/text glyph raster, GPU frame+full frame p50/p95/p99, VRAM actual/UNKNOWN, clip/group offscreen bytes and latency if measurable. Explicit cold/warm shader caches and outstanding font downloads denied.
- Pair image fidelity with cost: correct paint order, alpha and font layout, integer sharpness, color gamma, missing glyph/source rights, and quality vs GPU/CPU cost Pareto frontier. A lower draw-call count with wrong translucent ordering **does not count as performance improvement**.
- 60 FPS at 16.67ms average is insufficient alone: owner must define p95/p99 frame targets, device/scene and acceptable visual error/low-power hardware. Do not claim no-artifacts without golden captures.
- S2CC prove-or-drop vs fixed stable batching and traditional CPU raster/atlas; if cache/motion costs, risk or image regressions occur, remove proposal. No outperformance or novelty established in P00.

## Deliverable evidence after implementation authorization
Golden original sources and attribution, scripts+seed, raw frame captures, GPU timestamp measurements, processed image error plots, platform logs, device-loss recoveries, line/character output references and camera replay. **All future, no measurement today.**
