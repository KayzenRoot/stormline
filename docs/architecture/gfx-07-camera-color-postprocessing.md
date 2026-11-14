# GFX-07 — Stormline Cinematic Camera, Color & Post-processing

**WO NLE-P00-WO-002-GFX-07** | **Research #141** | **Future code issue #35 BLOCKED**  
**BASE:** `bd45e076f789e0b934076a1973139400d3eb382b` | **State:** PROPOSED RESEARCH, DOCS ONLY. No real C++, shader, native GPU, real HDR screenshot, numerical benchmark, SDK integration or release exists.

## Mission
Preserve detailed GFX-05 PBR and GFX-06 linear HDR illumination in artist-controllable, color-accurate, temporally stable images across native Windows/Linux/macOS and reduced Web, including native 2D/2.5D and fast 3D ARPG gameplay. High quality should be **measured** against comparable scene references, not declared better than Unreal/GGG before code and hardware evidence.

## 1. Ownership map
| Owner | Boundary |
|---|---|
| CORE-04/05/06 | frame time, math, coordinates/floating origin, observability |
| DATA-02/03/04/05 | persistent CameraId, SceneId and LUT/color asset rights; robust import and cook; durable scene edits/revisions; GFX-07 never parses host files or invents a cooker |
| GFX-01 | GPU backend and **display/swapchain** HDR/SDR capability/device generation; OS/monitor negotiation, never guessed from internal FP16 texture |
| GFX-02 | shader compiler, reflection, hot reload, variant limits; no separate post compiler |
| GFX-03 | RenderGraph pass scheduling, temporary surfaces/history, VRAM, barriers/fences; no GFX-07 pool |
| GFX-04 | depth, current/previous transforms, skinned/alpha/pixel-animated geometry semantics and motion vectors |
| GFX-05 | texture/color input tags, linear BRDF/alpha/reactive material signal and source imports |
| GFX-06 | scene-linear HDR light, GI/reflection/volume, light-change epochs and emissive reactive flags |
| TWO-01/02, EDIT/AI | independent 2D pixel-art, UI/text and layering, secure project-scoped semantic authoring |
| PLAT | monitor/browser presentation, screenshots/video metadata and actual platform capabilities |

A headless CPU numerical reference never proves real GPU display parity.

## 2. Camera and geometry contracts
- Stable project-scoped camera+scene revision, view+projection, **perspective** with validated vertical FOV/aspect/near/far and **orthographic** for 2D, layered 2.5D projections, multi-camera/viewport and origin rebasing. Camera lens metadata (focal length, sensor, focus, aperture, shutter) is authoring data; gameplay camera collision remains another owner.
- Reversed-Z, NDC depth ranges, projection sign/handedness, frustum, previous-frame matrix and origin epochs align CORE-05/GFX-04/06. Reject NaN/Inf, singular transform, zero aspect and physically impossible near/far.
- Deliberate subpixel jitter only on world geometry, e.g. Halton candidate; **unjittered UI/pixel-art/text and culling contract**, correct previous/current jitter and motion-vector direction/units (pixels vs NDC; render vs output resolution), skinned/alpha/deformed emitters and per-instance movements. Camera cuts/teleports/resize/FOV/rebase update history key and invalidate.
- No mandatory camera motion blur or depth of field for 2D, accessibility, competitiveness or motion-sensitive players.

## 3. Color and HDR: one mathematical truth
`ColorSourceTag(DATA-03/GFX-05) -> explicit scene-linear working primaries/white point -> GFX-06 HDR radiance -> exposure/pre-exposure -> scene-referred post effects/reconstruction (versioned order) -> view transform/tone mapping + gamut mapping -> output encoding and GFX-01 swapchain/canvas -> sharp UI/accessible capture`.

- **Candidate** ACEScg/AP1/D60 wide scene working plus ACES 2.0 Output Transform, color grade/OCIO offline-editor interchange; final working primaries and conversion white point NOT frozen until GFX-05/06 contracts and GPU measurements. OpenColorIO BSD-3-Clause at library level, dependencies/ACES configs/LUT rights audited. ACES 2 2025 is not a free runtime performance guarantee. Don't call random filmic approximation “ACES2”.
- Source sRGB/linear data converted **once**; texture normal maps never gamma corrected. Negative intermediary values/out-of-gamut/HDR finite highlight handling and safe clipping/compression separate. Color pipeline records primaries, transfer (LINEAR/sRGB/PQ/HLG as capability), reference white, gamut, alpha premultiplication, LUT revision and transform order. Disable double gamma and tone mapper repeated passes.
- **SDR** sRGB correct and default. **HDR10** BT.2020/ST2084 PQ (or platform-specific scRGB/EDR/HLG) only if display, OS, swapchain and driver support confirmed; paper-white nits and mastering metadata have trustworthy provenance. Internal R16G16B16A16 HDR does not imply HDR signal.
- **WebGPU** numeric GPUTexture is not intrinsically color managed; canvas/external image color-space conversion is a separate boundary. display-p3 canvas does not prove BT2020/PQ output. WebGL2 reduced SDR sRGB fallback; Mac Metal EDR capability requires real monitor/OS test.
- HDR/SDR switching, monitor move and screenshot/video capture require safe output transforms; screenshots with no HDR metadata must be explicitly SDR mapped, not washed-out FP16 dumps. Distinguish scene-linear, display-referred grade and UI composition (nits for HDR UI).
- Color accessibility: reduced flash/photosensitivity, color-blind assistance and contrast/UI policies are opt-in, never silently mutate authoring assets.

## 4. Exposure, grading and professional authoring
- Manual exposure `EV100` and normalized histogram/spot/average auto-exposure candidate, metering region/percentiles, white/black clipping limits and separate dark/bright adaptation time. Flash-resilient metering avoids unwanted entire-frame brightness pumping from 100 spell explosions, while allowing authored cinematic effect. Nonfinite luminance and overflow handled; deterministic reset on camera cut.
- White balance temp+tint, saturation/hue/contrast, lift-gamma-gain, highlight/mid/shadow, bloom, glare/lens flare optional. All stage-specific and bounded; graded LUT/cube/ICC/OCIO source via DATA-03 sanitized import with dimensions/work quotas/rights, not arbitrary shader code.
- Filmic tone mapping selected under `ColorTransformProfile` and compared to neutral/ACES2 reference on golden color charts, specular fireflies, skin, highlights, gamut boundary and platform output, not “looks nice”.

## 5. Motion integrity and upscaling
- **Baseline native or spatial**: no-AA for crisp pixel art/UI; spatial FXAA/SMAA candidate, bicubic/Lanczos/CAS/FSR1-like spatial sharpening where approved, MSAA only if GFX-03/render architecture actually supports it. Color and alpha guardrails, no oversharpening dark halos.
- **Optional original TAA/TAAU**: jittered scene-linear color, depth, motion vectors, reactive/translucent masks, light-change epoch, previous history and exposure rescale; velocity dilation/clipping, neighborhood/variance rejection, disocclusion confidence, transparent/particle fallback, thin geometry shimmer and specular aliasing. Reject invalid/unreliable vectors; compare stability vs ghost tails and native detail. Maintain correct HUD at display resolution. On invalid history choose native/spatial for safe frame.
- **AMD FSR SDK 2.4 (Oct 2026)** conditional on DX12/Vulkan 1.2 feature/platform and **signed DLL** loader/effect version and legal checks. SDK may publish open integration/sample code, but effect binaries are not therefore modifiable MIT. Vendor ML upscalers have availability/hardware limits and are not mandatory for native Mac/Web.
- **NVIDIA Streamline** framework may ship open parts, whereas DLSS-G is binary-only and other DLSS model/plugin terms vary. **Intel XeSS** SDK supplied license explicitly binary-only under Intel Simplified Software License; not MIT. No dynamic unsigned DLL loading, arbitrary repo download or permanent vendor lock.
- **Dynamic resolution** optional independent governor with measured GPU p95, scale bounds/hysteresis/cooldowns, fixed native UI and reinitialized/sharpened reconstruction on scale transition. Output 4K from 1080p render is not native 4K fidelity.
- **Frame generation** FUTURE/optional: distinct from render/game simulation FPS and input-to-photon latency, VRR/swapchain and driver terms; avoid claiming higher responsiveness from inserted frames. No blanket mandatory frame generation.

## 6. Post stack, order and accessibility
Proposed logical stages: scene-linear GFX-06 HDR -> light histogram/pre-exposure -> correct temporal/spatial resolve/uplift (technically selected DoF/translucency order) -> scene-referred bloom/glare/optional DoF/velocity motion blur -> color correction/grade/tone/gamut once -> output encoding/GFX-01 composite + full-resolution UI and capture. The *actual exact dependency* must be frozen per technique in GFX-03 pass graph, since upscaler, bloom, transparent and DoF may demand different ordering. No accidental double tone/exposure or hidden untested shader combinations.
- Bloom PSF/threshold normalized to scene-linear range and safe on UI/text/transparent; no exaggerated halo replacing real scene light.
- DoF aperture/focal plane/circle-of-confusion, translucency mask and full-resolution UI guard; optional and opt-out.
- Motion blur shutter angle and velocity bound, per-camera/object mask, **OFF** under reduced-motion/pixel art and player choice; grain, chromatic aberration, vignette OFF/ restrained defaults. Photosensitivity flashes require bounded/accessible authoring and preview policy.
- GFX-07 owns *post process* not particle gameplay, lens camera gameplay control, world ECS, audio or input sampling.

## 7. History lifecycle, device failure, authoring
- `PostHistoryKeyV1`: project/scene/camera IDs/revisions, projection & viewport dimensions, render/output res & scale, current/previous jitter, GFX-04 velocity semantics, GFX-05 alpha flags, GFX-06 light-change epoch, color/exposure pipeline revision, GFX-02 shader layout, GFX-01 device+swapchain generation and GFX-03 resources+fences. Any incompatible transition -> invalidate/reseed; no old frame after lost GPU, teleport, HDR off, scene explosion or hot reload.
- Budgets: CPU/GPU ms measured vs ESTIMATED, VRAM/UMA KNOWN/UNKNOWN, history buffer count/bytes, 3D LUT sizes, shader pass costs, thermal/power if available, accessiblity preference. Graceful fallback with `PostQualityReceipt` and exact visual losses, no silent black frame or bogus HDR.
- Editor/CLI/MCP operations are typed read-only inspect/preview/get-receipt and capability-scoped `Stage -> Validate -> Commit` with expected revision, DATA-04 journal, quotas. Never allow OS HDR calibration changes, arbitrary network/host LUT paths, native GPU handle/raw shader/unsigned driver DLL load or private capture export from agent.
- Optional **SRCC: Stormline Reconstruction Confidence Controller**: scene/light motion confidence adaptive AA/resolution R&D PROVE-OR-DROP vs ordinary TAAU, spatial and FSR comparators. Not claimed novel, implemented, faster or better.

## 8. Platform-aware tiers (UNTESTED)
| Target | Mandatory proposed fallback | Conditional high-tier |
|---|---|---|
| CPU/headless | camera/projection, color transforms and metering numerical oracle | not GPU HDR/temporal proof |
| WebGL2 | SDR sRGB, native/spatial/no-AA, constrained bloom | no universal compute/ML SDK/HDR |
| WebGPU | SDR sRGB, display-p3 *if canvas supported*, optional custom TAAU after WGSL/texture proof | no native HDR10/persistent vendor DLL assumption |
| Windows Vulkan/DX12, Linux Vulkan | SDR, native/spatial, validated TAAU | HDR only when output supported, FSR 2.4 signed SDK if legal/compatible |
| macOS Metal Apple Silicon | SDR native/spatial, Metal TAA candidate | EDR/wide gamut only with real platform proof, no DX12 vendor DLL |

## 9. Code activation gates
No implementation until GFX-06 implemented/APPROVED, GFX-01/03/04/05 contracts frozen, 1.0 release class/DoD approved, exact shader/backend/compiler/SDK artifact rights and signed binaries, detailed hardware/browser/monitor fixture matrix and numerical HDR/temporal thresholds, Context Lock SHA-256 and audit. `#35` remains BLOCKED and 80 WOs executor_ready=false.

## Primary technical sources
- Academy OpenColorIO BSD-3-Clause: https://github.com/AcademySoftwareFoundation/OpenColorIO
- OCIO releases and ACES 2 support: https://github.com/AcademySoftwareFoundation/OpenColorIO/releases
- OCIO GPU shaders and LUT architecture: https://opencolorio.readthedocs.io/en/stable/api/shaders.html
- Academy ACES official documentation: https://docs.acescentral.com/
- Unreal TSR and motion-vector/ghosting limitations: https://dev.epicgames.com/documentation/unreal-engine/temporal-super-resolution-in-unreal-engine
- AMD FSR SDK 2.4, October 2026, signed DLLs DX12/Vulkan: https://gpuopen.com/amd-fsr-sdk/
- AMD FidelityFX SDK legacy free shaders: https://gpuopen.com/manuals/fidelityfx_sdk/getting-started/
- NVIDIA Streamline framework and DLSS-G binary plugin: https://github.com/NVIDIA-RTX/Streamline
- Intel XeSS actual binary-only redistribution LICENSE: https://github.com/intel/xess/blob/main/LICENSE.txt
- W3C WebGPU color spaces and canvas transfer: https://www.w3.org/TR/2026/CRD-webgpu-20260512/
- Microsoft Advanced Color/HDR: https://learn.microsoft.com/en-us/windows/win32/direct3darticles/high-dynamic-range
- Microsoft HDR10 reference sample: https://learn.microsoft.com/en-us/samples/microsoft/xbox-gdk-samples/hdr10/
