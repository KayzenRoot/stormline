# TWO-04 — Hybrid 2D/3D Technologies, Correctness, Portability and License Matrix

**Research #156 | NLE-P00-WO-002-TWO-04 | ADR-0025 PROPOSED**  
All entries are research only: **no SDK/engine code, image, art, shader, binary, platform API, measured performance or license adopted**.

| Candidate/method | Classification | Correctness/platform trade-off | License/provenance | Future objective proof |
|---|---|---|---|---|
| Stormline typed depth-aware hybrid composition | NECESSARY architecture proposal | shared view/projection, GFX-03 graph, masked sprites and opaque 3D depth test | original code, engine license undecided | sprite/mesh mutual occlusion, scene depth correctness |
| Explicit ordered Canvas overlay | NECESSARY | sprite/clip order exact, no 3D per-pixel occlusion | original TWO-01 plan | HUD/text crisp after post and alpha groups |
| Ortho/perspective bridge + billboard/ground plane | NECESSARY | 2D px↔3D meters, camera conventions, reversed-Z and large-world origin | CORE/GFX owners, no vendor | projection, actor feet/ground occlusion under camera motion |
| Alpha cutout + stable mixed transparents | NECESSARY for basic sprites | cutout may depth-write, alpha-blend generally test-only; global painter order not exact for intersecting 3D | GFX-05 material owner, engine original draw plans | overlapping sprite/glass/grass goldens |
| Masked world sprite shadow+lighting | IMPORTANT feature handoff | GFX-06 light/shadow and proxies, correct normals/two-sided | no third-party solver selected | light energy/color/shadow edge quality |
| GFX-07 temporal flags/motion vectors/reactive | IMPORTANT integration | TAA/DLSS/FSR HDR and cutscene/teleport history; preserve native HUD | GFX-07 owner and vendor SDK gating separate | no temporal ghost, HDR/SDR color and pixel-art crispness |
| Subviewport render-to-texture | IMPORTANT bounded mode | can mix 2D in 3D/3D in 2D; color is flat unless explicit depth reprojection | GFX-03 transient budget, original | graph hazard, stale-frame and memory tests |
| Weighted Blended OIT | OPTIONAL approximation, not baseline | bounded buffers, approximate transparency only, cannot guarantee correct refraction/complex overlaps | public research article != source code license; implement own after rights/quality | image/error and memory vs stable sorted blend |
| Per-pixel linked list OIT | FUTURE opt-in | atomic fragment storage and high VRAM, not WebGL2 fallback | original if built, transitive GPU capability | compare worst-case memory/overflows |
| Depth reprojection across subviews | FUTURE opt-in | camera/projection mismatch/disocclusion errors and artifact risk | original validation, not implicit mode | depth reprojection image oracle |
| Godot 4.6 CanvasItem y-sort/Z-index | REFERENCE ONLY | y sort scoped to same z; layering not true world depth | Godot engine MIT, no source/assets copied | independently authored scenes matched by semantics |
| Godot 4.6 SubViewport | REFERENCE ONLY | isolated render target for 2D-in-3D/3D-in-2D, depth separate | Godot MIT, no engine code used | mode comparisons, resource costs |
| Unity 6 sprite sorting/custom axis/Sorting Group | REFERENCE ONLY | sorting layer/order and camera distance; Sort-as-2D drops depth affecting depth post | Unity proprietary terms, no source/art copied | independent depth/post regression tests |
| W3C WebGPU API and formats | NECESSARY public spec | depth24plus/depth32float, texture usage, sampling/resolve and adapter-specific limits | W3C spec, NOT automatically runtime feature | feature probes and WebGPU/WebGL2 safe fallback |
| Khronos glTF 2.0 coordinate system | IMPORTANT interoperable input | right-handed +Y-up meters; source conversion belongs DATA-03; asset art licenses separate | Khronos spec public; loader not licensed by spec | transformed 3D mesh normals/winding and 2D anchor |
| SDOI static depth-order inspector | OPTIONAL PROVE-OR-DROP | authoring diagnostics not depth solution, false positives risk | hypothesis, no proven novelty | quality/cost against mode validators |

## Known hard constraints
- Godot 4.6 CanvasItem official docs distinguish y-sort/Z-index vs tree draw order; Godot SubViewport isolates color output and does not automatically solve world-space depth. These are licensed MIT **design references only**; do not paste Godot code/assets.
- Unity 6 official 2D-with-3D "Sort as 2D" workflow explicitly warns removing object depth information makes depth-dependent post processing inapplicable to it. This is a **warning about that workflow**, not evidence that every Unity project or Stormline mode has identical behavior. Unity software/art usage remains under its own proprietary terms.
- glTF 2.0 specification states source model right-handed, +Y-up, meters. Do not blindly rewrite Stormline global axes. DATA-03 import is the only format conversion owner; no third-party glTF importer licensed/installed in this research.
- W3C WebGPU depth24plus may be implementation-defined depth precision in its allowed formats; `depth32float` and render/copy/sample usages require API capability compatibility. WebGL2 compute/storage buffer/PPLL is NOT a fallback baseline. No promise that all browser GPUs support MSAA/depth resolve/acceleration identically.
- McGuire/Bavoil Weighted Blended OIT (JCGT) is a publicly published technique. A paper being freely readable DOES NOT automatically authorize reuse of accompanying third-party code/images. OIT is an approximation, not mathematically exact overlapping refractive geometry.
- Original HDR/alpha/shadow VFX artworks/3D models/assets and comparative benchmark screenshots need explicit rights. No claimed 60FPS, CPU/GPU time, quality superiority, 3D model import, HDR display or Web shipping here.
- No mandatory paid runtime, dependency or asset pack, no GPL/proprietary copied code. Later code activation needs exact versioned license+SBOM check for every module and platform.

## Primary official and research references (reference, NOT adopted code)
- Unity 6 sorting 2D with 3D: https://docs.unity.com/en-us/engine/6000.6/manual/unity2d/2d-urp/2d-renderer-urp-features/sorting-workflows
- Unity 6 sprite sorting queue and custom axis: https://docs.unity.cn/Documentation/Manual/2d-renderer-sorting.html
- Godot 4.6 CanvasItem layer/z/y sorting: https://docs.godotengine.org/en/4.6/classes/class_canvasitem.html
- Godot 4.6 Viewports and compositing: https://docs.godotengine.org/en/4.6/tutorials/rendering/viewports.html
- Godot 4.6 HDR 2D and pixel-snapping project settings: https://docs.godotengine.org/en/4.6/classes/class_projectsettings.html
- W3C WebGPU depth formats and texture attachment usage: https://www.w3.org/TR/webgpu/
- Khronos glTF 2.0 canonical source-coordinate, +Y-up/meters: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html
- McGuire and Bavoil, weighted blended order-independent transparency (JCGT 2013, limitations as approximate blending): https://jcgt.org/published/0002/02/09/
