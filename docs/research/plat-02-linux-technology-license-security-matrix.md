# PLAT-02 — Linux 2026 Technology, Licensing, ABI, Wayland/X11, GPU and Packaging Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research [#321](https://github.com/KayzenRoot/stormline/issues/321) | NLE-P00-WO-002-PLAT-02 | future code [#85](https://github.com/KayzenRoot/stormline/issues/85) OPEN/BLOCKED | BASE 6271e5482e02fbc575d401feb2d72a24eaff2854.** Catalog 67/80; formal dependencies **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), CORE-01 transitive; 66/80 research documented at source, 14 pending, all 80 coding WOs BLOCKED; engine_implemented=false; engine license NLE-D009 OPEN.


**Candidate research, not technology adoption, feature implementation, license clearance or supported-distro certification.**

## Source-backed upstream facts and verification points
| Layer | Primary official source | Consequence |
|---|---|---|
| SDL Linux | [SDL3 Linux README](https://wiki.libsdl.org/SDL3/README-linux) | SDL dynamically discovers much of the native desktop support, requiring runtime probes; never run as setuid/setgid |
| SDL Wayland | [SDL3 Wayland README](https://wiki.libsdl.org/SDL3/README-wayland) | Wayland favored where usable; constrained top-level positioning, session restore/minimize/icon behavior, fractional DPI caveats |
| SDL driver selection | [SDL_HINT_VIDEO_DRIVER](https://wiki.libsdl.org/SDL3/SDL_HINT_VIDEO_DRIVER), [SDL3 migration](https://wiki.libsdl.org/SDL3/README-migration) | SDL_VIDEO_DRIVER and pre-init backend override, X11 conditional fallback; not a second event loop |
| SDL license | [SDL LICENSE](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) | zlib-style SDL root license; exact tag, transitives and NOTICE required |
| Vulkan Wayland | [VK_KHR_wayland_surface](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_wayland_surface.html) | separately capability probe surface and present queue for Wayland |
| Vulkan XCB | [VK_KHR_xcb_surface](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_xcb_surface.html) | X11/XCB surface extension; no assumption interchangeable with Wayland |
| Vulkan surface | [VK_KHR_surface](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_surface.html) | GFX-01 owns native surface/swapchain lifetime |
| Vulkan ICD | [Khronos Vulkan Loader driver discovery](https://github.com/KhronosGroup/Vulkan-Loader/blob/main/docs/LoaderDriverInterface.md) | XDG/system ICD manifests and VK_DRIVER_FILES/env overrides affect driver provenance |
| XDG dirs | [freedesktop XDG Base Directory](https://specifications.freedesktop.org/basedir/) | absolute dirs, config/data/state/cache/runtime split; invalid relative env ignored |
| XDG portal | [FileChooser portal](https://flatpak.github.io/xdg-desktop-portal/docs/doc-org.freedesktop.portal.FileChooser.html) | user-mediated scoped file access, denied requests never bypass sandbox |
| Flatpak | [developer documentation](https://docs.flatpak.org/en/latest/) | manifest runtime, permissions, portals, GPU extension, sandbox lifecycle; not auto selected |
| AppImage | [AppImage concepts](https://docs.appimage.org/introduction/concepts.html) | compile on oldest supported distro and avoid bundling incompatible GPU/system libs |
| CMake | [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) | pinned target-specific ABI/build reproducibility, no native build in P00 |
| Linux desktop entry | [Desktop Entry spec](https://specifications.freedesktop.org/desktop-entry-spec/latest/) | icons/MIME/application identifiers, Exec must not interpolate untrusted project data |
| Linux audio | [PipeWire documentation](https://docs.pipewire.org/) and [SDL Linux README](https://wiki.libsdl.org/SDL3/README-linux) | AUD-owned PipeWire/PulseAudio/ALSA session-dependent adapter, no guaranteed audio target |
| Linux package sandbox | [Flatpak sandbox permissions](https://docs.flatpak.org/en/latest/sandbox-permissions.html) | filesystem/network/device/bus access must be minimized and consented |
| libc runtime ABI | [glibc ABI documentation](https://sourceware.org/glibc/manual/latest/html_mono/libc.html) | GLIBC/GLIBCXX/CXXABI symbol floor requires actual clean-machine tests |

## Technology / rights / threat matrix
| Candidate | Licence/redistribution and owner | Benefit | Gate / risk |
|---|---|---|---|
| SDL3 CORE-01 Wayland/X11 host | SDL zlib root, transitive licenses by exact tag | shared host, event/pointer/IME portability | wrong backend, pre-init env, modifier/IME/fractional scaling and compositors |
| Wayland + libdecor + xdg-shell protocols | protocol specs often MIT-style, libdecor version/license to audit | native secure compositor support | protocol versions, decoration/position/minimize restrictions, D-Bus and fd permissions |
| X11/XCB + XWayland | X.Org/XCB various permissive licenses/version-by-version | legacy desktop and debugging fallback | key grabbing, X authority, lack of XWayland, mixed DPI |
| Vulkan loader/headers and layers | loader/headers mostly Apache-2.0/MIT by component; inspect exact tags | portable GPU and validation | malicious ICD/layer JSON, loader env, incompatible driver, untrusted build chain |
| Mesa Radeon/Intel Vulkan drivers | Mesa MIT-like, LGPL/GPL and component notices vary; inspect redistribution | mainstream GPU reference tiers | distro packages/driver/firmware ABI; not bundle blindly |
| NVIDIA proprietary Vulkan driver | vendor EULA, no assumption of source rights | major Linux GPU tier | license redistribution, Wayland, PRIME, driver version, runtime ABI |
| SDL GPU, software Vulkan lavapipe | SDL zlib/Mesa component license | comparator/headless smoke | software fallback does NOT prove physical GPU feature support |
| PipeWire, PulseAudio, ALSA, JACK | LGPL/MIT/GPL among components; audit precise versions and linker obligations | actual Linux audio availability | realtime callback, user session, permission/socket/sandbox and latency |
| udev/libinput/SDL HID, IBus/Fcitx | libudev LGPL family, libinput MIT, input framework licenses vary | controller/keyboard/IME | serial logging/privacy, /dev/input access, hotplug, accessibility |
| DBus + xdg-desktop-portal | portal/interface components mixed LGPL/GPL/MIT; audit exact binary | standard permission mediation | forged app identifier, file chooser denial, invalid URI/permissions |
| C++20 Clang/GCC + libstdc++/libc++ | GCC/runtime license and exceptions; LLVM Apache-2.0 with LLVM exception; inspect packages | cross-distro compiler baseline | ABI symbol mismatch and glibc floor, compiler version drift |
| Flatpak runtime & SDK | Flatpak LGPL-2.1+ component, freedesktop runtimes mixed sources/licenses | sandboxed integration | GPU runtime extension, portal, manifests, publishing ownership |
| AppImageKit/portable tar | AppImage runtime/tool licensing varies; verify concrete tool revision | one-file or simple internal artifact | glibc/FUSE, system lib excludes, legacy kernel |
| DEB/RPM packages | toolchain/project licenses, distribution conventions | managed OS integration | root install/update, unattended package scripts, signing and rollback |
| Steam Linux Runtime / Proton | third-party runtime/compat tooling mixed licenses and terms | optional game-store distribution | not native Linux guarantee, storefront/SteamOS profile separate |
| Linux aarch64/musl | separate ABI/third-party binaries/licenses | broaden potential platforms | unapproved smoke floor, not x86_64 equivalence |

## Security threat register / mandatory future negatives
| Threat | Required protective behavior/evidence |
|---|---|
| Loader injection via LD_PRELOAD/LD_LIBRARY_PATH/RPATH/$ORIGIN | restrict trusted load paths; test hostile project folder; no library execution |
| Vulkan ICD/layer manifest spoofing | documented host driver provenance, controlled test override only, reject untrusted app-local manifests |
| Symlink, hardlink, TOCTOU, path traversal | DATA-01 canonical scoped writes/owner protections and outside-project sentinel |
| .desktop Exec command injection or MIME spoofing | validated launcher and fixed args, no shell escape from untrusted metadata |
| Flatpak portal or filesystem permission escalation | explicit user mediation, no silent host filesystem/device grants |
| Wayland forbidden input capture / global injection | no hidden grabs or background keylogger; capabilities DENIED/UNSUPPORTED |
| X11 less-isolated key capture | no global grabbing, no sensitive event traces |
| Root/pkexec/setuid untrusted installer or engine | reject privilege escalation unless separately owner approved and independently audited |
| Udev/hidraw device overreach | minimal permissions and no permanent device serial collection |
| Audio socket or DBus session spoofing | per-user/session binding, safe error propagation and no auto privileged fallback |
| Old glibc/GLIBCXX packaging | clean distro symbol/runtime check, no bundled GPU ABI drivers |
| Unsigned update/plugin/supply chain | provenance/SBOM/signature verification by BIZ-03, no local arbitrary shell |
| GPU driver crash/epoch reuse | GFX-01 generation invalidation, typed recover/restart, no use-after-free |
| Crash logs with paths/usernames/IME | CORE-06 local redaction, opt-in export; avoid persistent device fingerprint |

## Candidate matrix, not approved support commitments
- LNX-HW-A: x86_64 nonadmin workstation with distro-version+kernel+glibc pinned, Intel/AMD integrated GPU, GNOME Wayland, single SDR monitor, keyboard/mouse and PipeWire.
- LNX-HW-B: x86_64 KDE Wayland, AMD discrete GPU, fractional scale/multimonitor, gamepad and headset.
- LNX-HW-C: x86_64 GNOME/X11 or XWayland as actually available, NVIDIA proprietary or separately tested AMD/Intel GPU; explicit loader WSI.
- LNX-HW-D: laptop hybrid GPU/PRIME and suspend/resume, controller hotplug, audio switch and power metrics.
- LNX-CI: container/headless/Xvfb/lavapipe/virtual, used solely for build/unit/negative tests. **Cannot substitute physical hardware.**
- LNX-OPTIONAL: aarch64, musl, SteamOS, Flatpak release, HDR/VRR advanced path only with separately authorized coverage and cost.

No scoring winner selected. Before adoption pin exact release/tag/commit SHA, license/SPDX/NOTICE/SBOM for each included binary, vulnerability state, transitive link obligations, distro and GPU driver matrix, default user permissions and real integration A/B evidence. Engine NLE-D009 OPEN, no paid dependencies and no claim any software is preinstalled.

[Architecture](../architecture/plat-02-linux-desktop-target.md) · [ADR-0070](../adr/0070-plat-02-linux-host-compatibility-policy.md) · [benchmark](plat-02-linux-benchmark-protocol.md).
