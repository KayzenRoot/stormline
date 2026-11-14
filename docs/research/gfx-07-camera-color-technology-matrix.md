# GFX-07 — Technologies, Portability and Licensing Research

**Research issue #141** | **WO NLE-P00-WO-002-GFX-07** | **PROPOSED, NO SOFTWARE INSTALLED** | Snapshot 2026-11-14. No exact dependency revision or ABI has been approved.

| Technology | Class | Device/algorithm constraints | License boundary | Proof |
|---|---|---|---|---|
| ACES2 transforms / ACEScg candidate | IMPORTANT color science | scene-wide gamut/whitepoint, GPU cost, final primaries TBD | open specs; separate LUT/asset rights | neutral/ACES2 SDR+HDR reference |
| OpenColorIO OCIO 2.x | IMPORTANT editor/offline | BSD-3-Clause core; transitive libraries and GPU shader API portability | BSD 3 + SBOM/NOTICE, pin tag | CPU/GPU LUT and color fidelity |
| sRGB SDR pipeline | NECESSARY | all targets, explicit OETF and whitepoint | platform standard | color chart and gamma correctness |
| HDR10 BT.2020 PQ | IMPORTANT native when supported | monitor+OS+swapchain and real nits, not FP16 alone | platform SDK terms | SDR/HDR toggle and capture |
| Metal EDR and display gamut | IMPORTANT conditional | actual Apple display/OS capability | Apple SDK terms | monitor validation |
| WebGPU Canvas P3 | IMPORTANT conditional | texture raw numeric; canvas color management distinct | W3C | no bogus HDR10 assertion |
| Histogram exposure/EV100 | NECESSARY proposal | GPU compute optional; reduced CPU path | own implementation | flash pumping and recovery |
| Native AA-off / spatial FXAA | NECESSARY fallback | GPU/UI/web; third-party filter licenses vary | validate original/selected source | pixel art and fine text crisp |
| SMAA/temporal-compatible AA | IMPORTANT candidate | texture fetches/backends and history | original or licensed implementation | foliage/noise/shimmer |
| Bicubic/Lanczos/CAS/FSR1 spatial | NECESSARY fallback | sharpness/ringing risks, not native detail | own or SDK license | downscale/upscale goldens |
| Own TAA/TAAU | IMPORTANT candidate | velocity/depth/reactive masks/previous scene | original; do not copy Epic TSR | ARPG blast ghosting and input |
| Unreal TSR | REFERENCE | Epic internal velocity/temporal resource integration | Epic protected implementation | temporal artifact comparator |
| AMD FSR SDK 2.4 / FSR4.1.2 | OPTIONAL native plugin | signed SDK effect DLL, DX12 and Vulkan support with hardware/version limits | MIT samples != signed effect binary modification rights | FSR vs own TAAU, failure fallback |
| AMD legacy FidelityFX FSR1/3 | OPTIONAL research | different SDK/API from FSR 2.4, shader portability requires proof | pin open license and exact version | portable spatial/temporal baseline |
| NVIDIA Streamline / DLSS | OPTIONAL vendor plugin | framework open parts; DLSS-G prebuilt plugin, model terms vary | independent SDK/plugin/driver license | hardware missing, signed DLL guard |
| Intel XeSS | OPTIONAL vendor plugin | SDK binary-only, ecosystem/hardware checks | Intel Simplified Software License != MIT | authorized redistribution and fallback |
| Dynamic resolution | IMPORTANT | frame-time/hysteresis and no native UI downgrade | own algorithm | scene change/worst p99 |
| Frame generation | FUTURE | latency, display pacing, driver and player option | binary rights/ABI and platform | simulation vs rendered FPS |
| DoF/motion blur | OPTIONAL | motion accessibility and alpha/HUD separation | algorithm or SDK proven rights | off-by-default/reduced-motion |
| Bloom/glare/grain/lens | IMPORTANT bounded | scene-linear and output-referred ordering, UI masking | own implementation | highlight fidelity/halo |
| 3D LUT / ICC / .cube import | IMPORTANT | untrusted size/profiles, no code injection | DATA-03 sandbox+rights, transitive libraries | fuzz and round trip |
| SRCC confidence policy | OPTIONAL PROVE-OR-DROP | scene history+lights/velocity/budget cost | unproven research hypothesis | Pareto vs fixed temporal |

## Explicit red flags and important distinctions
- OCIO library BSD-3-Clause does **not** grant arbitrary third-party film LUTs, ICC configurations, grading assets or dependency license rights. ACES 2.0 output transforms and GPU shader performance must be validated by exact OCIO/build version.
- AMD **FSR SDK v2.4, October 2026** supports DX12/Vulkan 1.2 via loader plus **prebuilt signed effect DLLs**, even while SDK wrappers/samples are openly licensed. Do NOT mark newer ML effect DLLs as modifiable MIT source code. Different features have different GPU/API/OS requirements. Never install a fake binary or auto-update during baseline tests.
- NVIDIA Streamline framework is open-source in parts but **DLSS-G plugin is binary-only**; DLSS versions/plugins/models/driver rights differ. Exact redistribution and signing must be independently reviewed.
- **Intel XeSS** SDK `LICENSE.txt` is Intel Simplified Software License for binary-only redistribution, no modification/reverse-engineering; not MIT.
- **WebGPU** GPU textures are not globally managed colors; canvas colorSpace and external image conversion are explicit; Display-P3 != HDR10 PQ. WebGL2 reduced route mandatory.
- Unreal TSR can ghost due to invalid motion vectors, pixel shader animation and transparency: it is a benchmark reference, not a free reusable renderer.
- HDR internal FP16, 10-bit swapchain, EDR monitor, HDR10 metadata, color gamut and PQ output are independent capabilities with separate hardware/display tests.
- NO binary version pin or HDR hardware proof is implied by this technology inventory. Review full transitive SBOM/NOTICE and asset provenance before code activation.

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
