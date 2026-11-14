# ADR-0020 — Managed Color, HDR Display and Artifact-Bounded Reconstruction

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **Research #141** | **WO NLE-P00-WO-002-GFX-07** | **Future code #35 BLOCKED**

## Context
GFX-06 produces scene-linear HDR radiance. Without an explicit SDR/HDR/color contract or correct motion vectors, high-quality lighting can degrade into washed-out color, halos, ghost trails and blurred text. Vendor super-resolution SDKs have licensing and binary distribution traps; 2D and Web require safe minimal routes.

## Proposed decisions
1. **Typed camera projection/view**: stable project/scene CameraId, perspective/orthographic/2.5D, validated near/far/reversed-Z, jitter only world rendering, independently crisp UI. CORE-05/GFX-04 own maths/velocity, DATA-04 owns scene edits.
2. **One color transform chain**, no double gamma/exposure: DATA-03/GFX-05 source color tags -> GFX-06 linear HDR working primaries -> metering/exposure -> stage-specific effects -> tone/gamut/output transform -> GFX-01 SDR/HDR display -> crisp UI/capture. ACEScg working and ACES2/OCIO editing candidates; final working gamut and OCIO runtime not frozen.
3. **SDR sRGB required baseline**, true native HDR only if OS/display/swapchain metadata and output encoding validated. Internal FP16 not HDR10; WebGPU Display-P3 not equivalent to HDR10; WebGL2 reduced SDR fallback mandatory. Capture and HDR UI white/nits policy must be explicit.
4. **Native/spatial fallback always** (including pixel art, 2D, UI and low-end). Own TAA/TAAU optional with correct depth/velocity/jitter/light-change/reactive/history contract and deterministic invalidation. Incompatible history -> native or spatial for next frame, no stale ghosting or invalid GPU pointer.
5. **Vendor upscaler gated**: AMD FSR SDK 2.4 DX12/Vulkan signed effect binaries despite MIT wrappers/samples. NVIDIA Streamline open parts ≠ universally open DLSS plugins, DLSS-G binary-only. Intel XeSS uses binary-only license. No mandatory vendor plugin, unverified DLL loader, software spend or unsupported Mac/Web claim.
6. **Opt-in cinematic effects**: histogram/EV100 with flash policy, grade/tone/bloom, optional DoF/motion blur/lens; accessible reduced-motion/flash and pixel-art/UI protections. Frame generation FUTURE, never counted as input-latency/render-simulation improvement.
7. **Immutable GFX-03 pass/history ownership**, full per-view source/device/scale/camera/color/light generations in `PostHistoryKeyV1`, defensive GPU loss and HDR toggle fallback. GFX-02 compiler, GFX-05 materials, GFX-06 lighting and DATA-03 cooker boundaries unmodified.
8. **SRCC** motion/light confidence-based reconstruction and dynamic-res heuristic OPTIONAL PROVE-OR-DROP against ordinary spatial/TAAU and licensed SDK paths. No novelty, quality or performance proven.
9. Secure same Editor/CLI/MCP semantic commands for scoped expected-revision Stage/Validate/Commit; no untrusted LUT/ICC native files, shader injection, private capture export, raw device pointers or unsupervised SDK installs.
10. **No code authorization**: all 80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, #35 open/blocked, release class UNDECIDED. Future freeze requires approved scope/DoD, GFX-06 implemented and integrated, license/source/ABI/version/hardware/monitor/numerical targets, exact file paths and SHA-256 Context Lock.

## Alternatives rejected as universal defaults
Only temporal/ML upscale, mandatory 4K/HDR all browsers, OCIO runtime compulsory before proof, blurry HUD, 2D jitter, frame generation equal “real FPS”, heavy cinematic motion blur for all games, unconstrained LUTs, stale history kept to flatter benchmark, declaring Stormline superior to Unreal/GGG without standardized scenes.

## Future evidence (NOT EXECUTED)
Headless color/camera numeric goldens and 2D/UI, 2.5D, 3D scene sequences, rights-cleared HDR/SDR physical monitors, GPU hardware on Win/Linux/Mac and Web, signed SDK licensing/driver tests, temporal artifact motion/video, GPU loss/resize and p50/p95/p99/VRAM against same-scene baselines. See [architecture](../architecture/gfx-07-camera-color-postprocessing.md), [matrix](../research/gfx-07-camera-color-technology-matrix.md), [semantic API](../contracts/gfx-07-camera-color-api.md), [tests](../testing/gfx-07-acceptance-matrix.md), [comparison protocol](../research/gfx-07-quality-benchmark-protocol.md).
