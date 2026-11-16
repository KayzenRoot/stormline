# ADR-0070 — Linux Desktop Host, Compositor, ABI and Package Boundary Policy

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**STATUS: PROPOSED / NOT OWNER-RATIFIED / NOT IMPLEMENTED / NO CODING AUTHORIZATION.**

## Problem
Linux is mandatory for Stormline Editor + exported games, but is not a single ABI/window system or GPU stack. Incorrect choices would create dual event loops, X11-only promises, unsafe Wayland feature assumptions, unbundled ELF dependencies, hidden Flatpak permissions, GPU driver/ICD loading injection or release-quality claims from a headless CI runner.

## Proposed decision
1. Keep **formal DAG edges exactly GFX-01 + GAME-01**; both predecessors have PROPOSED ADRs, **not implemented**. CORE-01 owns SDL3/init/event pump; AUD, DATA-01/05, CORE-06, PLAT-05, BIZ-03 and UI are only transitive/integration owners.
2. **Candidate primary host** C++20 + CORE-01-owned SDL3 with runtime-negotiated Wayland preference and X11/XWayland fallback where available. A separate Wayland/XCB SDL loop or direct PLAT input poller is rejected. Pin supported SDL version later; SDL_VIDEO_DRIVER contract recorded without treating environment override as a valid security boundary.
3. **Compositor policy:** capability-driven, no forbidden top-level placement or unconditional minimize/warp/keyboard grabs on Wayland. Fractional scale, per-window pixel extent and viewport/input transforms have explicit revision IDs. Restore/dock/window decoration and xdg-session-management require actual compositor protocol support.
4. **Presentation:** GFX-01 alone chooses Vulkan WSI and actual VkSurface/queue/device/swapchain. Linux adapter reports WSI extension/ICD/driver/render node, display profile and epochs; probe Wayland vs XCB separately. SDL3 GPU only GFX-01 comparator. Software Vulkan and virtual GPU cannot masquerade as physical hardware.
5. **Input:** CORE-01 emits ordered typed events, GAME-01 owns device/seat/tick/action maps; locale compose/IME and clipboard remain UI. Failure/reconnect/focus reset input states, no global logging, injection or restricted /dev/input access.
6. **Audio:** AUD owner tests PipeWire session, PulseAudio compatibility or ALSA fallback; no PLAT-owned mixer, auto privilege escalation or guaranteed realtime permissions. Endpoint loss and sandbox access typed.
7. **Filesystem/security:** XDG absolute directories, DATA-01 VFS, symlink/race/rename and case-sensitive path policy; sandbox portals for user-mediated access. Treat dynamic loader environment, Vulkan ICD manifests and .desktop launchers as attack surfaces; no untrusted ELF/plugins, arbitrary shell, sudo/setuid or editor-controlled LD_PRELOAD.
8. **Distribution separation:** PLAT-02 defines ABI/build/runtime and package capability; PLAT-05 owns export, BIZ-03 installation/update/signing/rollback. Portable tar, AppImage, Flatpak and distribution-native packages are **alternatives**, not adopted launch formats. AppImage must respect glibc baseline and exclude system GPU driver libs; Flatpak needs explicit portals/perms/runtime compatibility.
9. **Target floor remains open:** Linux x86_64 GNU/glibc with pinned current LTS distro is a candidate smoke floor; Debian/Fedora/GNOME/KDE kernels, AMD/Intel/NVIDIA/Mesa/proprietary GPUs and X11/Wayland matrix require owner ratification and real testing. aarch64, musl, handheld/SteamOS are separate uncommitted profiles.
10. **Proof gate:** exactly 128 future Linux tests, repeatable hardware Editor+exported-game build/smoke, CI vs physical receipts, ABI clean-machine, input/IME/portals/audio, capability denial/failover, source/license/SBOM and quantitative tail latency. None executed in P00.
11. **No stack/license approval now:** SDL3/Vulkan/Flatpak/AppImage/PipeWire exact tags and redistribution/security are unpinned, NLE-D009 engine code license OPEN, all 80 implementation WOs remain BLOCKED, executor_ready=false, release classes UNDECIDED and engine_implemented=false.

## Alternatives and reasons not to adopt automatically
| Candidate | Benefit | Rejection / future gate |
|---|---|---|
| X11-only Linux | legacy ease and position/warp control | fails Wayland-first modern desktop integration; no automatic compositor interoperability |
| Direct Wayland everywhere | modern session semantics and security | breaks X11-only sessions and unsupported protocols; cannot override compositor restrictions |
| SDL3 via CORE-01 with narrow Linux bridge | consistent cross-platform host, conditional fallback | exact SDL version, distribution and actual input/compositor smoke needed |
| Vulkan-only hard requirement for all Linux devices | RHI reuse with Windows | ICD/driver/WSI capability and hardware tier vary; fallback unsupported must be explicit |
| Bundle Mesa/NVIDIA ICD into general AppImage | apparent portability | driver ABI/system coupling, redistribution, unsafe override and breakage |
| Flatpak for every export | reproducible runtime and portal sandbox | permissions, game distribution/Steam path, GPU extensions, driver, file access; BIZ owner |
| AppImage always universal | portable single artifact | old glibc baseline, FUSE/runtime, graphics driver exceptions, update rights |
| Static-link everything/musl to solve Linux | fewer ELF dependencies | graphics/audio/loader/locale complications; distinct ABI matrix, no proof |
| Direct libinput/hidraw polling, global hooks | raw device features | permissions/seat/input privacy conflicts with CORE-01/GAME-01 |
| Run as sudo/pkexec to access GPU/input | expedience | security and consent violation, reject |
| Assume CI Xvfb/lavapipe constitutes physical smoke | cheap automation | virtualized GPU/monitor/input/audio, cannot certify real hardware |
| Claim GNOME/KDE or AMD/NVIDIA support from one distro | market coverage | compositor/GPU/driver/firmware divergence and unknown limits |

## Consequences and approval requirements
The thin Linux adapter improves portability and keeps authority boundaries observable, at cost of an actual matrix and compositor-specific behavior. Require future approved P01 code WO, actual rights-cleared hardware test, security provenance of loader/library inputs, portalled user consent, ABI/packaging profile and owner-approved support floor. Until then **ADR-0070 PROPOSED**; no changes to approved decisions or code issue #85.

[Architecture](../architecture/plat-02-linux-desktop-target.md) · [API contract](../contracts/plat-02-linux-target-api.md) · [research](../research/plat-02-linux-technology-license-security-matrix.md).
