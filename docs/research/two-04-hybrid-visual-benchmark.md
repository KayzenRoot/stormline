# TWO-04 — Original Clean-Room Hybrid Visual Quality & Performance Benchmark Protocol

**NLE-P00-WO-002-TWO-04 | Research #156 | NOT EXECUTED**. No GPU, physical HDR monitor, source scene with proof, profiler, video, device matrix, measured transparency, OIT or frame-time.

## Research question
Does an original Stormline typed hybrid depth compositor produce correct *artist-authored 2D/3D depth and alpha order with coherent lighting* without losing HUD pixel sharpness across native and Web targets, while controlling resource cost? Compare against own reference scene/golden and publicly documented behavior in Godot CanvasItem/SubViewports, Unity 6 sorting and W3C WebGPU device limits. Never assert a product beats Godot, Unity, Unreal or GGG from these documents.

## Future scenes and independent oracles
1. **Exact 3D depth crossover:** own rights-cleared terrain/wall/mesh and 2D sprite walker under orthographic and perspective camera, zoom/dolly/tilt, standing feet anchor, mirrored normal map, one sprite behind wall and one in front. Golden alpha-mask per-pixel depth oracle, screenshot reference and world/clip coordinates; show cast/receive light only after GFX-06 enabled.
2. **Layer-ordered composition:** pure Canvas2D HUD/labels/subtitles, click overlays and pixel-art at multiple DPI. Compare stable painter order with 3D world and scene temporal post. Independent CPU Canvas oracle and GPU image compare; any alpha reorder or dynamic-resolution blur is failure.
3. **Complex alpha/overdraw:** foliage, glass, soft VFX, intersecting sprite planes, transparent 3D mesh behind/in front. Capture sorted blend vs optional weighted blended OIT with **image quality error** and VRAM. A transparent solver that changes refractive correctness or painter order is not “better” just for fewer draw calls.
4. **Nested viewports and camera compatibility:** 3D model preview inside 2D UI, 2D animated picture on 3D mesh, minimap and split screen. Explicit render graph dependency DAG, subview dimension/VRAM/latency budget, stale sample age, depth reprojection test under dissimilar cameras (expect rejection/fallback). No arbitrary screen-depth combine.
5. **Lighting and temporal:** light/shadow on normal-mapped sprite and 3D mesh, glTF +Y-up/meter conversion, HDR scene linear/SDR final outputs with GFX-07, transparent motion/reactive masks and camera cut/history resets, same game at native vs reconstructed res while UI remains native. HDR10/P3 only on physically supported hardware with calibration.
6. **Fault and security:** device loss, VRAM pressure, resize, unexpected split-screen viewport, invalid shader/material/alpha blend, cross-project camera request, malicious imported asset/transform, unauthorized MCP scene edits. Fail explicit/last-good scene, no GPU stale buffers.
7. **Comparative documented workflows:** Godot 4.6 y-sort/Z-index/SubViewport and Unity 6 Sort-as-2D depth removal as *risks/reference*. Compare independently authored equivalent scenes after normalizing scene setup, never screenshots/data copied from projects and no vendor code assumed.

## Measurement & scoring methodology
Freeze exact head SHA, C++/shader compiler version, OS and backend, driver/GPU/memory, device caps/depth format/MSAA, display HDR mode/measurement, viewport physical DPI and camera projection, glTF source axis metadata, per-layer alpha/depth policy, light/shadow stage, 2D atlas asset rights and hash, TAA/reconstruction, VFX budgets and subviews frame cadence/size. Attach repeatable scripts, original scene hash and lens/dolly parameters.
- Measure CPU render planning, GPU opaque/depth/masked/transparent/post/subview passes p50/p95/p99, full-frame p50/p95/p99 and stutters, overdraw/pixel layers, physical color/alpha pixel difference, occlusion/painter-order mismatch counts, bloom/TAA ghost/disocclusion, peak VRAM/UMA (or UNKNOWN) and device loss recovery.
- Compare correctness at identical memory budget, and performance at equal pixel/gamut/alpha/depth quality. No reward for flattening depth to boost FPS without explicit mode policy or hiding artifacts behind fake “quality” settings.
- **SDOI PROVE-OR-DROP:** static diagnostic vs simple mode validation, count contradictory authoring setups caught, true positive rate, false positives and authoring overhead. Remove if not materially valuable.
- Numeric PASS tolerances (pixel, depth, p95/p99, VRAM, FPS and HDR) and named devices are **TBD for owner-approved 1.0 DoD**. This protocol is a planned experiment, not observed performance.

## Sources
- https://docs.unity.com/en-us/engine/6000.6/manual/unity2d/2d-urp/2d-renderer-urp-features/sorting-workflows
- https://docs.godotengine.org/en/4.6/classes/class_canvasitem.html
- https://docs.godotengine.org/en/4.6/tutorials/rendering/viewports.html
- https://www.w3.org/TR/webgpu/
- https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html
- https://jcgt.org/published/0002/02/09/
