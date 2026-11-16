# PLAT-01 — Reproducible Windows Hardware Build/Launch/Present/Input/Audio Benchmark Protocol

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | [future code #84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, formal deps **GFX-01 + GAME-01 ONLY**, ADR-0014/0042 PROPOSED, CORE-01 transitive; 65/80 baseline research documented, 15 pending, 80/80 implementation WOs BLOCKED; engine=false, NLE-D009 OPEN.

**ALL FUTURE / NOT MEASURED. No Windows engine executable, no Windows native SDK toolchain pinned or run, no Editor exported game, no GPU/API device, no installation/signing, no real hardware benchmark exists in P00.** No invented milliseconds, FPS, input latency or compatibility tiers.

## 1. Study and acceptance
Acceptance catalog "Build e smoke test em hardware Windows definido" requires actual reproducible Editor AND Game Windows binaries, clean-machine OS/hardware launch and functional minimal rights-cleared fixture, GFX-01 adapter/present, GAME-01 input actions and AUD owner audio if declared, stable process/window lifecycle and typed failure. A hosted CI build cannot substitute for actual GPU driver, real monitors, gamepads, audio endpoint, installation or signing. Benchmarks characterize target capability; do not select Vulkan over D3D based on anecdotes.

## 2. Exact environment lock (proposed)
| Layer | Lock fields |
|---|---|
| Git/build | source base/head SHAs, GFX-01/GAME-01/CORE-01 owner versions, CMake presets, compiler MSVC+Clang-cl, link flags, reproducible binary digest, symbols and runtime CRT/ABI |
| Windows | exact OS build e.g. supported Win11 servicing x64 (not frozen), SKU/license/channel, hotfix level, secure boot policy/UAC user role, optional Windows ARM64/Win10 LTSC only approved tier |
| Windows SDK | installed Windows SDK version (candidate 28000.2957/26100.9457), optional Windows App SDK 2.x and bootstrap/dependencies, D3D Agility runtime, SDL3 exact release |
| Hardware | CPU model/microcode, GPU vendor/model/integrated/discrete/hybrid, driver build/firmware, VRAM, RAM/SSD, monitor EDID redacted, physical/native refresh/DPI/HDR/VRR, audio USB/BT, gamepad/keyboard layouts |
| Rendering | GFX-01 backend Windows Vulkan vs D3D12 if actually available, color primaries/HDR/AA/swapchain vsync/tearing/present queue, GPU clock query validity and device generations |
| Input/audio | GAME-01 device epochs/action map/focus event sequence, keyboard layout + IME mode, SDL native or optional GameInput version, AUD endpoint selection/audio sample rate + callback |
| Packaging | portable dev vs MSIX vs unpackaged EXE/MSI, BIZ-03 owner, CRT and optional GameInput/Windows App SDK runtime, Authenticode signer and consent state |
| Evidence | raw samples, monotonic clock domains, event loss/invalid data, owner receipts, simulator/real hardware designation, logs redacted, binary hash and independent reviewer |

## 3. Candidate physical QA tiers (not owner-frozen)
- **WIN-HW-0**: non-admin clean serviced Windows 11 x64 desktop with Intel/AMD iGPU and one SDR display, 60Hz, basic mouse+keyboard+audio endpoint. Do not declare minimum GPU support until actual tests.
- **WIN-HW-1**: x64 desktop Nvidia or AMD discrete GPU + 1080p/1440p, 120/144Hz VRR when available, HDR monitor when available.
- **WIN-HW-2**: x64 hybrid iGPU/dGPU laptop with two monitors 100%/150%/200% DPI, USB/Bluetooth gamepad and headset, lid/sleep/Alt-Tab.
- **WIN-HW-3**: Windows x64 no GPU/headless server and remote/virtual desktop negative capabilities.
- **WIN-HW-4 optional**: Windows ARM64 native device with real ARM64 binary+GPU, separately approved and compiler/third-party ABI; Windows 10 LTSC separately isolated policy if approved.
- **CI-only WIN-CI**: GitHub-hosted Windows build + headless smoke, explicitly virtual/hosted; **not** counted as WIN-HW real-hardware proof.

## 4. Future benchmark cases, no measured results
| ID | Case | Objective oracle / metrics |
|---|---|---|
| WIN-B01 | cold/warm Editor start vs clean machine | actual process exit/setup dependencies, latency, RSS/CPU, reproducible hashes |
| WIN-B02 | cold/warm exported game start | source/cooked manifest, first-frame readiness, latency p50/p95/p99 |
| WIN-B03 | SDL3 window create/close+main-thread pump | observed WindowEpoch lifecycle, event latency, no handle leak |
| WIN-B04 | mixed DPI/multi-monitor resize | hitboxes and framebuffer pixel/content-scale, resize stalls p95/p99 |
| WIN-B05 | 60/120/144Hz present+VRR across backends | real present times/tearing capability, GPU/CPU time domains separate |
| WIN-B06 | Vulkan vs D3D12 owner-backed same scene tier | CPU/GPU p50/p95/p99, VRAM, power, shader/cook, visual semantic parity |
| WIN-B07 | SDR/HDR monitor and color changes | calibrated color/gamut/exposure, actual display supported, fallbacks |
| WIN-B08 | alt-tab/device loss/GPU change | lost resources, recovery time and status, no invalid generation |
| WIN-B09 | SDL/XInput/optional GameInput hotplug | GAME-01 action frame correctness, duplicate edges and p95 latency |
| WIN-B10 | ABNT2/US IME and DPI mouse movement | composition privacy, focus keyboard/hit-test oracles |
| WIN-B11 | WASAPI AUD owner endpoint and device swap | glitch/dropout, power, safe callback and latency |
| WIN-B12 | sleep/resume/occlusion/minimize low-power | CPU, thermal/power, no busy loop, correct event reset |
| WIN-B13 | Win32 DLL/ACL/junction hardening negative tests | zero unauthorized native loading/host file effects |
| WIN-B14 | unsigned internal vs signed clean MSIX/EXE install | dependency and Smart App Control compliance, rollback, independent BIZ-03 |
| WIN-B15 | real hardware + hosted CI difference | report exact availability, missing physical GPU/input/audio |
| WIN-B16 | repeat lifecycle and crash diagnostics | 1k starts/reshapes, leak counts, redacted CORE-06 trace, no upload |

## 5. Statistical protocol and interpretation
- At least five independent trials and enough frame/input samples for tail percentiles; report raw ordered times and p50/p95/p99 with uncertainty. **Five trial runs alone do not support p99 inference**. Record cold/warm conditions, randomized A/B backend order, power mode/thermal limits and observer instrumentation overhead.
- E2E launch latency is distinct from GPU render time and `Present` CPU call duration. Correct CPU/GPU clocks plus DXGI/Vulkan present statistics and display domain calibration if supported. No arbitrary subtraction between clock domains.
- Evaluate multiple settings on same scene/assets/driver/hardware and same shader quality/cook. A backend wins only if all functionality/visual/privacy/security passes and meaningful measured improvement; unsupported GPU feature explicitly UNAVAILABLE.
- Crash tests, DeviceEpoch, WindowEpoch, GPU generations, audio endpoints and file path tests require *actual Windows OS and hardware*; simulated fault tests are supplementary.
- Avoid real user files, proprietary game assets/music, external downloads or paid signing. Place reproducible synthetic inputs under isolated runner with explicit quotas.
- For installer/signature real release gate use BIZ-03 separate owner workflow, do not charge fees/purchase certificates or publish in P00. Signing is an external approval boundary.

## 6. Future evidence schema
```text
PLAT01BenchmarkReceiptV1 {
  git_base_head_sha,owner_gfx01_game01_core01_api_rev,windows_build_sku_servicing,
  windows_sdk_msvc_clangcl_sdl3_d3d_agility_gameinput_versions,
  compiler_flags_crt_abi_sanitizer,editor_game_artifact_digest_symbols,
  physical_hardware_or_hosted_runner, cpu_gpu_driver_vram_ram_storage,
  monitors_dpi_scale_pixel_density_refresh_hdr_vrr,keyboard_layout_controller_audio,
  source_fixture_asset_rights_scene_hash,render_backend_rhi_feature_profile,
  window_display_device_present_epochs,headless_mode,os_user_privilege_scope,
  cold_warm_run_order_all_raw_samples,frame_p50_p95_p99_present_input_audio,
  gpu_timestamp_clock_uncertainty,source_owner_receipts,device_loss_recovery_result,
  installed_redistributables,signing_or_unsigned_dev_flag,biz03_package_receipt,
  ssl_sbx_license_sprint_notices,security_leaks,latency_statistics_intervals,
  actual_smoke_errors,redacted_core06_capture,independent_review_verdict
}
```
Fields conceptual only. No measurements recorded.

[Windows DPI](https://learn.microsoft.com/en-us/windows/win32/hidpi/high-dpi-desktop-application-development-on-windows) · [SDL3 DPI](https://wiki.libsdl.org/SDL3/README-highdpi) · [DXGI flip](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/for-best-performance--use-dxgi-flip-model) · [Architecture](../architecture/plat-01-windows-desktop-target.md).
