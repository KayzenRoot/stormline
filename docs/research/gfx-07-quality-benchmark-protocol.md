# GFX-07 — Reproducible Cinematic Color, Temporal and Latency Benchmark

**Research issue #141 / NLE-P00-WO-002-GFX-07**, NOT EXECUTED. No claim Stormline outperforms Unreal TSR, AMD FSR, DLSS or PoE2.

## Test tracks
1. **Color numerical correctness:** separately evaluate scene-linear to SDR sRGB, wide gamut to output, ACES2/neutral transform with CPU offline reference, gamma/OETF and HDR10 BT.2020/PQ measured through supported real display/swapchain. Capture original linear EXR-like reference only using licensed self-created fixture. HDR simulation on SDR display must be labeled SIMULATED, not measured HDR.
2. **Algorithm-level reconstruction comparisons:** same scene/camera path/raw render resolution/output, correct velocity/depth/reactive masks, no-AA/native, spatial, Stormline TAA/TAAU, AMD FSR SDK 2.4 on supported signed native targets, optional DLSS/XeSS only licensed and supported. Unreal TSR publicly documented techniques are comparator reference; UE outputs must use legal independently authored scenes. A game-level FPS comparison alone cannot show superior AA.
3. **Fast ARPG stress:** independent rights-cleared arena, moving foliage/skinned enemies, 100 bright short-lived spell lights as workload not supported product promise, huge flash, translucent particles, ghost trails, exposure pumping, contrast/UI readability, fast camera motion and device/HDR changes.
4. **2D/2.5D:** pixel-art native scene, orthographic/parallax camera, alpha sprites/text HUD at display res. Temporal TAA is not rewarded for blurring pixels; opt-out and crispness measured.
5. **User comfort/latency:** input-to-present latency (actual external measurement when available), flash exposure recovery, motion blur/reduced-motion opt-out and frame generation effect on input feel, not just interpolated output FPS.

## Measurement gates
- Freeze numeric tolerances before testing: CIE ΔE-like perceptual chromatic error where meaningful, HDR-linear pixel error, SSIM/edge detail/sharpness and temporal shimmer/ghost tail, view-target gamut, UI contrast, exposure response frames. Define target color probe accuracy and approved display.
- Same named OS/GPU/display/driver, API/backend/shader build, scene/camera path, image/PSNR/reference, render/output resolutions, scaler type, TAA jitter, AA/MSAA, VSync/VRR, power state, device warm-up and shader cache (cold vs warm separately).
- Report CPU/GPU pass p50/p95/p99 vs **whole frame**, VRAM/UMA or UNKNOWN, latency/1% low/frame pacing, shader compile, SDK binary version/signature, screenshots/video with licenses and timestamps, raw data and reproducible scripts.
- Compare image quality at matched GPU cost, and cost at matched image quality (Pareto frontier). No “better” if one path has blurred UI, missing hair/foliage, latency or ghosts. Hardware and monitor test coverage must be explicit.
- SRCC R&D PROVE-OR-DROP: reject if quality/cost/latency on multiple complex scenes loses to fixed native/spatial or standard temporal and if reproducibility fails; no speculative claims.
- All actual test results **NONE**. Hardware fixture and numeric thresholds must be in approved 1.0 DoD, not editorial marketing.

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
