# GFX-07 — Future Camera/Color/Post Acceptance Matrix

**WO NLE-P00-WO-002-GFX-07** | **Research #141** | **Future implementation #35 BLOCKED**.  
**77 scenarios specified below are FUTURE / NOT EXECUTED.** No C++/shader benchmark, GPU capture, real HDR display measurement, security fuzz or SDK integration was run. Platform/fixture/numerical thresholds still require a future frozen DoD.

| Test ID | Future proof obligation | Evidence surface |
|---|---|---|
| CAM-001 | Perspective FOV/aspect/near/far and inverse matrix golden | CPU numeric |
| CAM-002 | Orthographic projection 2D pixel/camera alignment | 2D CPU |
| CAM-003 | 2.5D layered projection occlusion mapping | 2.5D |
| CAM-004 | Reversed-Z & backend depth convention crosscheck | native |
| CAM-005 | Invalid NaN/Inf/singular camera rejected | fuzz |
| CAM-006 | Camera teleports/cuts invalidate history | temporal |
| CAM-007 | Origin rebase retains projection precision | large world |
| CAM-008 | Multi-camera/split viewport history isolation | native |
| CAM-009 | Jitter on world but never on UI/font layer | 2D/3D |
| CAM-010 | Motion vectors previous/current sign and units | geometry |
| CAM-011 | Skinned/WPO/material animated pixel motion inputs | GFX-04/05 |
| CLR-001 | sRGB OETF inverse/forward roundtrip | CPU golden |
| CLR-002 | Scene-linear wide gamut vs REC709/ACEScg proposal | CPU golden |
| CLR-003 | Whitepoint chromatic adaptation known reference | CPU golden |
| CLR-004 | No double sRGB decode on PBR textures | GFX-05 |
| CLR-005 | HDR scene values above 1 retain highlight radiance | CPU/GPU |
| CLR-006 | Out-of-gamut compression no illegal negative output | golden |
| CLR-007 | ACES2 versus neutral view transform test assets | CPU/GPU |
| CLR-008 | OCIO CPU/GPU 1D/3D LUT transform parity | interop |
| CLR-009 | Malformed .cube/ICC/OCIO input fails safe | fuzz |
| CLR-010 | Corrupt oversized LUT dimensions/payload rejected | security |
| CLR-011 | LUT source rights and revision invalidation | DATA-03 |
| CLR-012 | Alpha premultiply/composite once | UI/PBR |
| CLR-013 | Neutral grading round trip and skin chart hue | golden |
| HDR-001 | SDR sRGB true render -> display output correctness | native/Web |
| HDR-002 | HDR10 BT2020/PQ encode with known nit mapping | CPU numeric |
| HDR-003 | HDR monitor/swapchain capability proven not inferred | native |
| HDR-004 | HDR disabled -> typed safe SDR fallback | device fault |
| HDR-005 | HDR toggle device+history+UI reset | native |
| HDR-006 | Move window between HDR/SDR displays | native |
| HDR-007 | Capture HDR scene to SDR screenshot correct mapping | capture |
| HDR-008 | HDR UI paper white and SDR overlay fidelity | UI |
| HDR-009 | WebGPU display-p3 canvas not mistaken for HDR10 | browser |
| HDR-010 | WebGL2 sRGB safe reduced default | browser |
| EXP-001 | EV100/aperture/shutter/ISO numeric golden | CPU |
| EXP-002 | Auto histogram percentile and excluded outliers | CPU/GPU |
| EXP-003 | Flash/explosion adapt speed and visible recovery | ARPG |
| EXP-004 | Camera cut resets exposure under new scene | temporal |
| EXP-005 | Local exposure optional no halo/banding | image |
| EXP-006 | White balance/grade double transform guard | golden |
| AA-001 | Native render no-AA pixel-art and text crisp | 2D UI |
| AA-002 | Spatial FXAA/SMAA quality and aliasing vs native | golden |
| AA-003 | Bicubic/Lanczos/CAS/FSR1-like spatial ringing bounds | image |
| AA-004 | TAA jitter sample convergence static detail | temporal |
| AA-005 | TAAU alpha foliage thin line temporal stability | temporal |
| AA-006 | TAAU skinned character silhouette and velocity | ARPG |
| AA-007 | TAAU fireworks/explosions no ghost trails | ARPG |
| AA-008 | TAAU out-of-view & disocclusion response | temporal |
| AA-009 | TAAU semi-transparent particles missing vectors fallback | VFX |
| AA-010 | Fast camera pan/specular anti-flicker and sharpening | video |
| AA-011 | Invalid velocity field forces spatial safe path | fault |
| AA-012 | GPU frame history fence and alias correctness | GFX-03 |
| AA-013 | Frame-to-frame exposure ratio and pre-exposure consistency | golden |
| UP-001 | AMD FSR signed DLL missing -> optional fallback | vendor fault |
| UP-002 | FSR DX12/Vulkan only with actual SDK target/driver | native |
| UP-003 | NVIDIA Streamline DLSS-G binary rights/driver gate | legal |
| UP-004 | Intel XeSS binary-only license notice and failover | legal |
| UP-005 | Dynamic resolution change scale hysteresis frame p99 | hardware |
| UP-006 | Frame generation not counted as game tick/input FPS | benchmark |
| FX-001 | Bloom threshold/gamut and UI mask correctness | image |
| FX-002 | DoF CoC/focal plane and transparency edge | golden |
| FX-003 | Motion blur reduced-motion setting disallows blur | accessibility |
| FX-004 | Grain/chromatic aberration/vignette opt-out | UI |
| FX-005 | Volumetric bright light output and lens bloom stages | GFX-06 |
| SYS-001 | Device loss, history invalidation and recovery | fault |
| SYS-002 | Window resize/fullscreen HDR toggle and screenshot | native |
| SYS-003 | Win Vulkan+DX12 color capture and latency | hardware |
| SYS-004 | Linux Vulkan color/AA capture and profile | hardware |
| SYS-005 | macOS Apple Silicon Metal SDR/EDR hardware probe | hardware |
| SYS-006 | WebGPU browser output/adapter color profile | browser |
| SYS-007 | WebGL2 low-end fallback and alpha correctness | browser |
| SYS-008 | MCP cross-project edit/unsafe LUT path rejected | security |
| SYS-009 | Signed SDK substitution/rogue loader blocked | security |
| BEN-001 | P50/P95/P99 post-only and total frame CPU/GPU/VRAM | hardware |
| BEN-002 | Unreal TSR comparator matched motion quality | competitive |
| BEN-003 | GFX-06 burst stress image and input responsiveness | ARPG |
| BEN-004 | SRCC prove-or-drop against fixed TAAU/spatial | R&D |

## Golden workloads and oracle requirements
- Color: licensed RGB/neutral charts, known linear HDR samples, ACES2/OCIO reference transform outputs at agreed tolerance, clipping/chromatic adaptation/ICC fuzz. Distinguish sRGB viewer preview from real HDR10 monitor.
- Motion: authored 2D pixel/gradient UI, layered 2.5D, detailed static scene, high-motion ARPG with 10/100+ emissive spell sources as **test workload** not promised max dynamic lights, moving skinned/foliage/alpha particles, camera cut/teleport and fog.
- Hardware: named GPUs/displays/drivers, Win DX12/Vulkan, Linux Vulkan, macOS Metal Apple Silicon, WebGPU, WebGL2; no substitute synthetic CPU pass for hardware result. The project has no current GPU renderer.
- Predefine frame sequence, warm/cold shader cache, native/render/output resolution, upscaler version/mode, jitter and motion vector conventions, static/dynamic latency, screenshots/video/capture rights. Quantify ghosting/shimmer/alias/hue error and pass CPU/GPU p50/p95/p99, VRAM/UMA bytes and total frame-time. Owner DoD numeric thresholds TBD, no invented PASS.
- Security: untrusted LUT/ICC/OCIO configs through DATA-03 sandbox, SDK signed binary rights/provenance, GPU loss and privacy-safe MCP. Zero known HIGH/CRITICAL before implementation approvals.
