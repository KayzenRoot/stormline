# PLAT-02 — Exactly 128 FUTURE Linux Desktop Target Acceptance Tests

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**EXACTLY P02-T001..P02-T128, eight groups of sixteen. NOT EXECUTED; NO native engine, C++ code, test harness, PASS results or GPU hardware benchmarks.** P01 is the *future* implementation phase, not an already executed suite.

## Independent evidence standards
- Every future test requires target distro ID/release/kernel/libc/ELF architecture, binary/build digests, exact SDL/Vulkan/driver/desktop/backend and compositor capability, own expected oracle, reasoned PASS/FAIL/UNSUPPORTED/NOT_RUN distinct, and artifact/timestamp.
- Separate native real-hardware Editor AND exported game smoke from CI virtual/headless/Xvfb/software Vulkan; compilation cannot prove GL/physical GPU present or user input/audio/portal behavior.
- Enumerate both Wayland and X11/XWayland when physically available; never simulate forbidden compositor operations and mark PASS. Test fractional DPI/input targets by independent pixel and pointer oracle.
- GFX-01 actual Vulkan WSI, device generations/fence lifetime and GPU time; GAME-01 immutable semantic actions/epoch reset; CORE-01 one event pump; AUD realtime callback; DATA-01 strict file-scope and BIZ-03 owner release policy.
- Negative security tests are limited to synthetic isolated fixtures with no real secrets or outside-file deletion. Denied access and unsupported feature are not PASS. Check real filesystem sentinel unchanged.
- Benchmarks must preserve raw trial samples, p50/p95/p99 and uncertainty with adequate sample size, no imaginary values, no mixed CPU/GPU/display clocks.
- Owner chooses supported distro/hardware and budgets before P01. No automatic acceptance for Linux aarch64/musl/SteamOS/NVIDIA/Flatpak/production signing and no public MVP.

## Group 1 — BUILD-DISTRO-ABI

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T001 | Clean supported GNU/glibc x86_64 distro reports exact ID/version/kernel | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T002 | Editor target compiles with pinned clang/CMake preset and warnings policy | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T003 | Game target compiles with pinned GCC/CMake preset and source digest | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T004 | Clean machine runs Editor without developer SDK or shell wrappers | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T005 | Clean machine runs exported game without developer SDK | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T006 | Unsupported old glibc symbol requirement fails with explicit ABI error | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T007 | libstdc++ GLIBCXX/CXXABI mismatch produces no partial install | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T008 | 32-bit ELF on unsupported 64-bit-only target is rejected | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T009 | ELF target arch mismatch is rejected without execution | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T010 | aarch64 unapproved profile reports UNSUPPORTED not PASS | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T011 | musl unapproved runtime profile cannot claim glibc binary support | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T012 | Relative XDG_CONFIG_HOME is ignored safely to absolute default | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T013 | Missing writable XDG_STATE_HOME yields typed read-only failure | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T014 | CMake/ELF metadata includes hardening PIE/linker flags and symbols | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T015 | Build rerun locks source/compiler/dependency digests deterministically | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |
| P02-T016 | Hosted runner reports VIRTUAL/HEADLESS and not native GPU smoke | clean-matrix compile/build log, ELF readelf/ldd provenance, exact distro+ABI+artifact checksum | FUTURE / NOT EXECUTED |

## Group 2 — COMPOSITOR-DISPLAY

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T017 | SDL3 Wayland session probes actual compositor and xdg-shell | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T018 | SDL3 X11 session probes actual X server availability | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T019 | XWayland fallback is only attempted when X server is present | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T020 | Wayland toplevel positioning forbidden returns UNSUPPORTED | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T021 | User-triggered minimize UNKNOWN does not fabricate minimize event | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T022 | Wayland configure ack ordering prevents pre-configure present | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T023 | Window create/destroy cycles invalidate WindowEpoch handles | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T024 | Multiwindow editor focus and popout transition preserves events | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T025 | Fractional 125% scaling preserves UI pointer hit targets | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T026 | Fractional 150% scaling preserves framebuffer sharpness | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T027 | Fractional 175%/mixed DPI monitors preserve coordinate conversion | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T028 | Zero-size framebuffer suspends GPU present without spin | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T029 | Wayland decoration/icon support absence is capability-reported | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T030 | X11 maximize/restore and monitor disconnect safely reorder | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T031 | Compositor restart/Wayland disconnect requires typed recovery | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |
| P02-T032 | Headless/no WAYLAND_DISPLAY/DISPLAY yields NO_DISPLAY_SERVER | CORE-01 monotonic event/window/scale journal and physical screenshot+pixel hit-test oracle | FUTURE / NOT EXECUTED |

## Group 3 — VULKAN-GPU-WSI

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T033 | Wayland VkSurface creation gated on VK_KHR_wayland_surface | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T034 | XCB VkSurface creation gated on VK_KHR_xcb_surface | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T035 | Swapchain format/present mode individually queried on real surface | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T036 | Missing host Vulkan ICD returns GPU_BACKEND_UNAVAILABLE | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T037 | Tampered VK_DRIVER_FILES manifest is rejected in controlled test | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T038 | Lavapipe software renderer cannot satisfy physical GPU smoke | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T039 | AMD/Intel Mesa device driver and firmware revision recorded | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T040 | NVIDIA proprietary GPU runtime capability queried without license assumption | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T041 | PRIME hybrid GPU selection records actual adapter and offload environment | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T042 | GPU device loss invalidates device and presentation generations | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T043 | Window resize waits safe GPU retirement then recreates swapchain | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T044 | GPU/driver hotplug records SurfaceEpoch and typed restart-required | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T045 | Invalid GPU queue present family cannot be used | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T046 | Vsync/VRR/tearing claims derive from observed available present support | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T047 | SDR-to-HDR request on unsupported compositor degrades safely | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |
| P02-T048 | GPU timestamps/present clock domain never conflated | actual GFX-01 driver/WSI/device generation, Vulkan validation and hardware identifier-redacted receipt | FUTURE / NOT EXECUTED |

## Group 4 — INPUT-IME-GAMEPAD

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T049 | SDL3 event loop is called by CORE-01 exactly once | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T050 | XKB US keyboard scancode vs composed key remains separate | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T051 | ABNT2 international layout preserves AltGr/compose mappings | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T052 | Dead-key/IME composition not treated as gameplay physical action | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T053 | IBus IME composition is confined to focused text widget | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T054 | Fcitx IME unavailable yields typed fallback not leaked text | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T055 | Mouse relative motion uses permitted compositor capability | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T056 | Wayland pointer warp denied without infinite retry | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T057 | Gamepad USB hotplug updates DeviceEpoch and seat | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T058 | Gamepad Bluetooth reconnect resets held actions | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T059 | Device removed mid-chord emits exactly one safe release | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T060 | Alt-tab/focus loss cancels held game actions and pointer lock | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T061 | SDL gamepad duplicate source cannot double action frame | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T062 | Multiwindow GAME-01 context routing respects modal focus | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T063 | Event queue overflow triggers safe resync/release | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |
| P02-T064 | No global /dev/input hooks or keyboard logging permitted | GAME-01 action frame and CORE-01 device/window epoch capture with source dedup | FUTURE / NOT EXECUTED |

## Group 5 — AUDIO-PORTALS-A11Y

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T065 | PipeWire default endpoint probe delegated to AUD | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T066 | PulseAudio compatibility endpoint selection is explicit | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T067 | ALSA fallback only if actual device/permission available | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T068 | USB headset loss increments audio endpoint epoch safely | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T069 | Bluetooth audio profile switch reports latency/format change | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T070 | Realtime audio callback has no blocking file or logger operations | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T071 | Sandboxed Flatpak playback honors session audio permission | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T072 | FileChooser portal grant scoped to user-picked project file | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T073 | Portal denial produces no host filesystem side effects | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T074 | OpenURI portal denial cannot execute arbitrary shell | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T075 | ScreenCast portal is never auto-invoked without explicit consent | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T076 | Clipboard copy/paste isolated to focused Editor permission | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T077 | Accessibility AT-SPI availability is reported not fabricated | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T078 | GNOME/KDE screen reader label/input navigation tested separately | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T079 | Missing font/script shaping gracefully reports an owned UI error | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |
| P02-T080 | Input/audio/portal telemetry redacts user paths and composition | AUD/portal/UI ownership receipt with consent, endpoint gen and privacy sentinel | FUTURE / NOT EXECUTED |

## Group 6 — FS-LINKER-SECURITY

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T081 | ../ traversal cannot escape DATA-01 project VFS | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T082 | Symlink to outside project cannot modify external sentinel | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T083 | Atomic rename against swapped symlink fails closed | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T084 | Filesystem case conflict does not silently overwrite asset | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T085 | Read-only/noexec mount produces typed save/start error | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T086 | XDG_RUNTIME_DIR owner/permission mismatch rejected | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T087 | LD_PRELOAD inherited from untrusted project cannot load plugin | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T088 | LD_LIBRARY_PATH/CWD injection denied in release artifact | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T089 | Malicious RPATH/RUNPATH/$ORIGIN traversal rejected | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T090 | Untrusted project-provided Vulkan ICD manifest cannot be elevated | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T091 | World-writable installed program dir rejected for load path | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T092 | No automatic sudo/setuid/pkexec on launch/install | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T093 | Malicious .desktop Exec field does not trigger shell command | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T094 | Sandbox filesystem permission denial cannot be bypassed via path alias | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T095 | Crash logs suppress HOME/username/HID serial/IME text | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |
| P02-T096 | Unauthorized out-of-project file/network sentinel stays unchanged | isolated negative fixture, VFS/ELF loader permission/sentinel; no outside effect | FUTURE / NOT EXECUTED |

## Group 7 — PACKAGING-INTEGRATION

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T097 | Portable tarball lists full ELF dependency/version closure | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T098 | AppImage built on pinned oldest supported glibc baseline | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T099 | AppImage never bundles host libGL/Vulkan proprietary driver blindly | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T100 | AppImage execution mode/FUSE need recorded per distro | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T101 | Flatpak manifest uses minimal permissions and locked runtime | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T102 | Flatpak GPU driver extension selected compatibly or denied | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T103 | Flatpak FileChooser grant survives only approved scope | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T104 | Flatpak OpenURI does not gain arbitrary shell authority | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T105 | DEB package clean nonadmin runtime launch after approved install | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T106 | RPM package clean nonadmin runtime launch after approved install | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T107 | Desktop entry Exec and app ID validated with icons | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T108 | MIME association test cannot invoke file from untrusted shell path | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T109 | BIZ-03 owns updater, so PLAT cannot auto update | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T110 | Artifact SBOM/SPDX/NOTICE covers transitive libraries | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T111 | Unsigned internal artifact is not labeled production signed release | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |
| P02-T112 | Uninstall/rollback preserves user-owned projects and last-good | clean install/package manifest/NOTICE, BIZ-03 policy, no privileged change | FUTURE / NOT EXECUTED |

## Group 8 — E2E-HARDWARE-BENCH

| Future ID | Case / expected condition | Independent oracle | State |
|---|---|---|---|
| P02-T113 | Editor launches and exits on real GNOME Wayland x86_64 hardware | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T114 | Exported game launches on real GNOME Wayland physical GPU | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T115 | Editor and game work on real KDE Wayland test machine | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T116 | X11 or XWayland real GPU path executes only if present | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T117 | Real multi-monitor GPU/scale resize has no corrupted hitboxes | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T118 | Physical USB+BT controller actions remain correct after focus loss | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T119 | Physical audio endpoint switches without hung realtime callback | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T120 | Real device lost/suspend-resume returns recovered or restart-required | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T121 | Cold/warm Editor startup times captured as raw samples | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T122 | Cold/warm exported game startup times captured as raw samples | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T123 | Vulkan frame GPU times include supported clock/validity domains | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T124 | CPU frame,present tail p50/p95/p99 with uncertainty recorded | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T125 | RSS,VRAM and shader/cache pressure tracked with known probes | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T126 | Idle/minimize power CPU and wake events measured with real session | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T127 | 1000 create/destroy/reconnect repeats show no leaks or stale epochs | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |
| P02-T128 | Final complete receipt pins CPU/GPU/driver/distro/artifact/licenses and audit | real physical test harness, raw samples/traces and environment-complete signed-off proof | FUTURE / NOT EXECUTED |


## Final future gate, not satisfied
Catalog acceptance: **Build e smoke test em Linux definido** including Editor and exported Game on actual nonadmin Linux desktop hardware, with distro/version, compositor/GPU and audio/input source oracles, permission/capability negative tests, license inventory, runtime/packaging rights and a separately approved target matrix. Zero HIGH/CRITICAL known before future code release. GFX-01/GAME-01 and host owner implementations independently audited/merged before PLAT-02 code issue #85 can be considered. ADR-0070 remains PROPOSED. All **80 future coding packets BLOCKED**.

[Architecture](../architecture/plat-02-linux-desktop-target.md) · [API](../contracts/plat-02-linux-target-api.md) · [benchmark](../research/plat-02-linux-benchmark-protocol.md).
