# PLAT-02 — Reproducible Linux Hardware/Compositor/ABI/Package Benchmark and Smoke Protocol

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**FUTURE ONLY / NOT MEASURED.** No Linux binary, hardware test, code, p50/p95/p99, Ubuntu/Fedora support certificate, real GPU screenshot or package produced.

## Acceptance and scope
Catalog requires built Editor AND exported 2D/3D game running on a defined real Linux distro/hardware profile, with GFX-01 actual WSI presentation and GAME-01 input actions. AUD endpoint, UI/IME and filesystem must work as declared, not implied by a build. All source scenes, fonts, images, audio and controller fixtures original/rights cleared. No benchmarking third-party proprietary game IP.

## Environment lock, capture BEFORE test
| Layer | Immutable evidence |
|---|---|
| Git | source base/head SHA, build tree/toolchain preset, branch, transitive CORE-01/GFX-01/GAME-01/CORE-06/AUD API version, tester name/review |
| OS/runtime | distribution ID and version, kernel release, libc family and symbol floor, GLIBCXX/CXXABI, machine architecture, filesystem mounts and system library paths, locale and IME |
| Compilers | CMake/Ninja, GCC/Clang revisions, link flags, PIE, RPATH/RUNPATH, sanitizer configuration, ELF build ID/digest, SBOM/signatures |
| Desktop | GNOME/KDE session version, Wayland/X11/XWayland selection, compositor/protocol versions, XDG directories, portal services and sandbox policy |
| Graphics | physical AMD/Intel/NVIDIA GPU model/firmware, actual Vulkan loader+ICD manifests, driver version, render node/PRIME, WSI extension, display DPI/refresh/VRR/HDR, surface/adapter generations |
| Input/audio | keyboard layout, IME IBus/Fcitx, physical mouse/USB/BT controller, capture mode permissions, PipeWire/Pulse/ALSA endpoint and latency, headset |
| Package | portable tar/AppImage/Flatpak/DEB/RPM internal channel, dependency closure and GLIBC floor, portals/access, permissions, signer/publisher if approved |
| Evidence | independent hardware classification REAL_PHYSICAL/HOSTED_CI/VIRTUAL/SOFTWARE, raw ordered samples, metric clock source and uncertainty, redacted logs, error reasons and no secret paths |

## Physical target tiers (CANDIDATE, not owner-frozen)
- **LNX-HW-0**: nonadmin x86_64 GNU/glibc current LTS, GNOME Wayland, AMD/Intel iGPU, SDR 60Hz, keyboard/mouse, PipeWire, SSD. Actual release/kernel/GPU remains TBD.
- **LNX-HW-1**: KDE Wayland, AMD dGPU, 120/144Hz as available, multi-monitor mixed DPI, USB+BT controller/headset.
- **LNX-HW-2**: X11/XWayland where installed, NVIDIA proprietary or alternate physical adapter; do not assume same rights across vendors.
- **LNX-HW-3**: laptop hybrid PRIME with suspend/resume, compositor relaunch, power capability and GPU switching.
- **LNX-CI**: hosted x86_64 CLI/CMake/CTest, headless/Xvfb/lavapipe negative; explicitly NOT hardware smoke.
- **OPTIONAL**: Linux ARM64/musl/Steam Deck, Flatpak/Flathub, advanced HDR/VRR profiles only by later owner decision; not required to claim until scope frozen.

## Sixteen future benchmark scenarios
| ID | Scenario | Metrics / oracle |
|---|---|---|
| LNX-B01 | cold/warm Editor startup GNOME Wayland | startup p50/p95, max RSS, first rendered frame, actual exit status |
| LNX-B02 | cold/warm exported game from same fixture | load/cook/assets hash, p50/p95 and shader cache state |
| LNX-B03 | SDL3 Wayland create/configure/close | WindowEpoch events, ack correctness, resource leak |
| LNX-B04 | X11/XWayland native fallback | only if actual X11 server; no event double pump |
| LNX-B05 | fractional-DPI mixed-monitor resize | framebuffer px, pointer hit error and resize stall tails |
| LNX-B06 | Vulkan Wayland vs XCB WSI same scene | GPU/CPU raw times, quality parity, present mode and validated queue |
| LNX-B07 | Mesa vs proprietary ICD profiles | per-GPU driver, capability/failure reason; no guessed ranking |
| LNX-B08 | laptop PRIME selection and suspend | selected physical GPU, wake/recovery/energy if available |
| LNX-B09 | input/IME/gamepad GNOME/KDE | GAME action fidelity, edge loss, input latency p95 |
| LNX-B10 | PipeWire/Pulse/ALSA real endpoint swap | glitch count, jitter, audio callback blocking negatives |
| LNX-B11 | Flatpak portal vs portable runtime | denied vs granted behavior, file access and missing dependencies |
| LNX-B12 | AppImage/ELF baseline on clean distros | GLIBC/GLIBCXX symbol floors, startup and license/dlopen integrity |
| LNX-B13 | hostile launcher/ELF/ICD filesystem | zero untrusted loads and outside project effects |
| LNX-B14 | minimized/occluded/idle energy | CPU wake count, power/thermal only when supported |
| LNX-B15 | long-run device loss/refresh/1000 cycles | stale generation rejection, recovery/RESTART_REQUIRED and leak count |
| LNX-B16 | native vs hosted CI proof and review | signed-off actual hardware witness and limitations |

## Sampling / statistical rules
Minimum five independent warm/cold trials *plus sufficient ordered per-frame/input samples* for tail metrics; five total runs alone do NOT estimate p99 robustly. Report median/p95/p99, bootstrap confidence uncertainty as appropriate, raw samples, invalid/dropped readings and clock-domain calibration. Change one variable at a time: distro/compositor/backend/driver/sandbox/compilation flags. A/B order counterbalanced, same source+assets, time-of-day/power state recorded. GPU timestamps not automatically display scanout times; no invented latency if present feedback unavailable. Pin thermal, shader cache, CPU governor and compositor effects. Instrument overhead measured.

## Future receipt shape (conceptual)
LinuxSmokeBenchmarkReceiptV1: git_base/head, build artifact SHA256 and ELF build ID, rights provenance, kernel+distribution+libc+toolchain, GNOME/KDE/Wayland/X11 compositor caps, SDL3/version, RHI backend/Vulkan loader ICD/driver GPU/VRAM, monitor scale/refresh/HDR/VRR, physical classification, input+IME+controller, PipeWire/Pulse/ALSA endpoint, XDG/portal/sandbox, package+signature/NOTICE/SBOM, scene hash, cold_warm trials, exact raw frame/present/IO samples, clock_domain_precision, cpu_rss, gpu_memory/power availability, fallback/error epochs and security sentinels, independent pt-BR verdict.

## Stop and fallback
Missing physical GPU, disabled portal, unsupported Wayland protocol or unavailable GPU counters => UNSUPPORTED/NOT_MEASURED, never PASS. Stop on unsafe dynamic loader/library injection, secret logs, privileges, unlicensed binary, failing GFX-01/GAME-01 or HIGH/CRITICAL. Internal unsigned artifact is not a release. No paid CI/signing automatically purchased. No benchmark performed in P00.

[128 FUTURE tests](../testing/plat-02-acceptance-matrix.md) · [matrix](plat-02-linux-technology-license-security-matrix.md) · [API](../contracts/plat-02-linux-target-api.md).
