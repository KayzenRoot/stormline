# PLAT-02 — Linux Desktop Target: Host, Compositor, GPU, Input and Distribution Architecture

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**DESIGN ONLY.** No Linux process, Editor, exported game, native build, hardware sample or package exists.

## Goals and authority
The approved catalog requires *Build e smoke test em Linux definido* for BOTH Editor and exported Game. A support claim needs the actual distribution release, libc/ABI, desktop environment/compositor protocol, GPU/driver, monitor, input, sound and artifact digest. Never infer cross-distro support from one CI run, a container, Xvfb, llvmpipe or binary compilation.

| Owner | Formal dependency / integration | Linux boundary, not a new owner |
|---|---|---|
| GFX-01 **FORMAL** | [RHI](../contracts/gfx-01-rhi-api.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md) PROPOSED | Vulkan surface/provider, backend availability, surface epochs, driver evidence; no duplicate RHI, device or swapchain |
| GAME-01 **FORMAL** | [actions](../contracts/game-01-input-actions-api.md), [ADR-0042](../adr/0042-game-01-engine-owned-input-actions.md) PROPOSED | Translate trusted host-scoped input; no action-mapping or gamepad device poller |
| CORE-01 **TRANSITIVE** | [lifecycle](core-01-platform-lifecycle.md), [ADR-0003](../adr/0003-core-01-platform-technology.md) PROPOSED | ONE SDL3 host/event pump, thread/window/focus epochs, no second Linux loop |
| AUD owner, CORE-06, DATA-01/05, PLAT-05, BIZ-03 | audio endpoint, redacted observability, VFS/cook, export, release/updater | Integration only, no added formal DAG dependency |

## Native session and compositor contract
- Candidate native host: C++20 + SDL3 via CORE-01, **Wayland preferred where usable, X11/XWayland explicitly supported as conditional fallback**, not an independent parallel event pump. SDL3 is an evaluation candidate, not yet adopted/pinned. SDL 3 names the environment override SDL_VIDEO_DRIVER; SDL_VIDEODRIVER is a backward-compat alias, not the contract. Any backend selection must happen before SDL_Init and be recorded without leaking untrusted env into privileged execution.
- Wayland session selection depends on actual compositor and protocol availability. **Wayland forbids arbitrary top-level window positioning** and may not report user-initiated minimize to SDL; restore window geometry with capabilities/UNKNOWN, not misleading guarantees. Window decorations, icons, progress and session restoration are compositor/protocol-dependent. Native xdg_toplevel role remains CORE-01 owned. X11 fallback is allowed only when X11/XWayland server is actually present; no synthetic success.
- Window identity: opaque WindowId + WindowEpoch, SessionEpoch, DisplayEpoch and SurfaceEpoch. Host emits ordered immutable transitions for create, configure/ack, close, scale change, focus, visibility/occlusion unknown, suspend, display disconnect, relaunch. EGL/Wayland/XCB native pointers are **internal leases** only; never expose over Editor/CLI/MCP or persist. Destruction/resize must invalidate GFX-01 presentation generations after GPU work retires.
- Logical window size, framebuffer pixel extent, content scale, fractional scaling factor, transform/orientation and input coordinate domain are distinct measured quantities. No 1:1 claim on fractional 125%/150%/175% scaling; compensate via hit-test oracle, not screenshot alone. Zero extent suspends presenting; avoid divide-by-zero, spinner and resize deadlock.
- On focus loss/rebind/seat switch: release stuck buttons, pointer lock/relative mode, clipboard/IME transient state through GAME-01/CORE-01. Wayland pointer confinement/warp restrictions, privileged global hooks or synthetic injection are not permitted by default. SDL text composition must not be treated as a gameplay key.
- Multiple monitors, refresh/VRR/HDR, remote login, GNOME/KDE and X11 compositor settings are **observations**, not a universal capability. Offer explicit UNSUPPORTED/UNKNOWN/DENIED outcomes; avoid assuming HDR/tearing/color pipeline from desktop branding.

## Linux GPU presentation without duplicating GFX-01
- Candidate Vulkan Linux WSI: VK_KHR_wayland_surface for Wayland; VK_KHR_xcb_surface (or xlib as required by actual adapter) for X11, and VK_KHR_swapchain under GFX-01. SDL3 GPU is a comparator under GFX-01, not a PLAT-owned graphics backend. Adapter selection, feature tiers, fences, queue/present families, surface formats, buffer lifetime, HDR and device-loss policy remain GFX-01.
- Vulkan loader discovers host ICD manifests; driver/layer overrides (VK_DRIVER_FILES, VK_ADD_DRIVER_FILES, VK_ICD_FILENAMES legacy) and env search can alter trust. Do not vendor an arbitrary GPU ICD or loader state as a magical fallback; record loader, Mesa/proprietary drivers and the actual physical device. llvmpipe/lavapipe/VK_NULL or virtual GPU is software/CI diagnostic only unless deliberately approved as a supported tier.
- Handle eGPU/hybrid PRIME offload, GPU hotplug, device-lost, failed WSI present, compositor restart, resize, suspend/resume with typed retry or RESTART_REQUIRED. No silent GPU switching, no stale swapchain/surface generation and no raw GPU pointer reaching AI tools.
- Distinguish compositor presentation feedback, CPU submit time, Vulkan GPU timestamps, VRR/tearing behavior and actual monitor scanout. Treat unknown precision as unknown rather than inventing latency numbers. Screenshot equality does not measure hardware present.

## Input, audio and accessibility
- SDL3 event sources/udev/libinput/HID access stay inside CORE-01, normalized into GAME-01 versioned physical events and immutable action frames. Real USB/BT gamepad, keyboard layouts/compose/AltGr, IBus/Fcitx IME, hotplug/seat and focus tests are required. Never assume /dev/input or hidraw privileged access, and never log typed credentials or HID serial.
- AUD owner chooses PipeWire native candidate, PulseAudio-compatible and ALSA fallbacks after real session probing. JACK/realtime privileges optional only with owner permission; no secondary PLAT audio engine or blocking, allocation or I/O on realtime callback. Endpoint-epoch + explicit loss/rebind for USB/Bluetooth and portal/sandbox audio support.
- UI/Editor handles clipboard, drag/drop, accessibility semantics, input method and font shaping via existing owners. Portal-mediated file chooser, OpenURI and optional ScreenCast (not automated capture without user consent). Accessibility API (AT-SPI/DBus) integration requires separate accessibility owner and real assistive-technology tests; no unsupported certification.

## User files, linker, sandbox and packaging
- Respect XDG_CONFIG_HOME, XDG_DATA_HOME, XDG_STATE_HOME, XDG_CACHE_HOME and XDG_RUNTIME_DIR, validating **absolute** paths/ownership/permissions. User documents remain under DATA-01 scoped VFS with resolved symlinks, TOCTOU defenses, traversal checks, quotas and staged writes. Unicode filenames, case sensitivity, mount/noexec/read-only and removable media are explicit failure paths.
- Treat project files, .desktop launchers, GPU manifests, runtime shared libraries and environment as untrusted. Defend LD_PRELOAD/LD_LIBRARY_PATH/RUNPATH/RPATH, $ORIGIN and plugin injection via fixed trusted binary directories, ELF dependency inventory, no shell-evaluated arguments and no setuid/setgid/sudo/pkexec. No copy from project into executable search path. Model multiarch libc/GLIBCXX/CXXABI/architecture/version compatibility, glibc versus musl **as distinct profiles**, not a static-link cure-all.
- PLAT-02 defines build/ABI/permissions/desktop integration capability **only**. PLAT-05 owns final export template and BIZ-03 production install/update/signature/rollback. Compare native distro package/portable tarball, AppImage (old-supported-glibc build floor; **do not bundle GPU driver system libs**) and Flatpak (sandbox and portals/runtime/extension GPU). None approved for 1.0 distribution, Store/Flathub fees/accounts/signer require separate permission. Package checks include SBOM/license NOTICE, .desktop/desktop-file-validate, MIME/icon/icon theme and clean-machine install/update/uninstall. No automatic chmod executable, root installation, updates or network.
- Ship internal test artifact only after future code scope approval; no engine runtime/build now.

## Integration states and error ownership
| Event | Linux adapter does | Other owner does |
|---|---|---|
| Wayland configure/scale | reports committed logical/pixel/window generation | CORE-01 pumps; GFX-01 recreates swapchain |
| X11 fallback selected | records backend reason + XWayland status | CORE-01 one event stream; GAME-01 resolves actions |
| Vulkan ICD missing/invalid | reports GPU_BACKEND_UNAVAILABLE / DRIVER_INVALID with provenance | GFX-01 chooses truthful tier/restart |
| Focus lost/controller removed | propagates WindowEpoch/DeviceEpoch change | GAME-01 releases held actions |
| PipeWire/Pulse endpoint lost | reports device capability epoch | AUD recovers or declares endpoint lost |
| Portal/user denies | returns USER_DENIED, no host-file side effects | DATA-01 controls file operations |
| Sandboxed package cannot access dir | returns scoped CAPABILITY_DENIED | user-mediated portal where authorized |
| ELF/GLIBC mismatch or noexec | build/launch receipt with exact symbol/permission cause | PLAT-05/BIZ-03 packaging corrections |

## Future acceptance gates
1. Owner-ratified distro+OS/kernel/glibc/GPU/DE support matrix including at least Wayland GNOME, KDE and X11 conditional smoke; Linux x86_64 as candidate baseline, aarch64/musl/Steam Deck separately gated.
2. Real physical Linux workstation shows repeatable launch, render and exit for BOTH Editor and exported Game with nonadmin user, rights-cleared 2D and 3D fixtures, interactive input/audio; VM/headless tests in separate bucket.
3. Exact-tag SDL3, Vulkan loader/headers/ICD and packaging tool SBOM, redistribution, notices, CVEs and compatibility review; NLE-D009 OPEN until owner approval.
4. 128 future cases, measurable frame/launch/memory/latency with p50/p95/p99 samples and uncertainty, compiler+sanitizer and security negative tests. No hardware benchmark invented in P00.
5. Independent pt-BR audit, no known HIGH/CRITICAL, explicit rollback/recovery. All 80 code WOs stay blocked.

[ADR-0070](../adr/0070-plat-02-linux-host-compatibility-policy.md) · [Linux API](../contracts/plat-02-linux-target-api.md) · [technology matrix](../research/plat-02-linux-technology-license-security-matrix.md).
