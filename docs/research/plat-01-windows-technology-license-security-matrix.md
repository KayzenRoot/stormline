# PLAT-01 — Windows 2026 Host, Presentation, Input, SDK, Packaging, Security & Licensing Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research #317](https://github.com/KayzenRoot/stormline/issues/317) | NLE-P00-WO-002-PLAT-01 | future code [#84](https://github.com/KayzenRoot/stormline/issues/84) OPEN/BLOCKED | BASE `e6ca541df3f08bc46a7f1e5b2f82564cb740f720`.** Catalog 66/80, **formal dependencies GFX-01 + GAME-01 ONLY**, both prior ADR-0014/0042 PROPOSED; CORE-01 transitive ADR-0003 PROPOSED. Baseline research 65/80, 15 pending; 80/80 future coding WOs BLOCKED; engine_implemented=false; NLE-D009 license OPEN.

## 1. Primary official references (2026-11-15 research)
| Technology/contract | Primary source | Grounded choice condition |
|---|---|---|
| Microsoft Windows SDK | [Windows SDK downloads](https://learn.microsoft.com/en-us/windows/apps/windows-sdk/downloads) | Windows 11 SDK 10.0.28000.2957 (Sep 2026) and 26100.9457 candidate supported builds; SDK API compile availability != all OS runtimes |
| Windows OS servicing | [Windows App SDK support](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/support) and [Windows 10 MSIX lifecycle](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/msix-windows10-windows11) | Windows 10 non-LTSC mainstream EOS 2025-10-14; Windows 11 editions/builds have differing support windows. Minimum OS NOT selected |
| Per-Monitor DPI v2 | [Microsoft High-DPI Win32](https://learn.microsoft.com/en-us/windows/win32/hidpi/high-dpi-desktop-application-development-on-windows) | `WM_DPICHANGED`, per-window monitor scaling, dynamic rasterization; actual PMv2 manifest+events required |
| SDL3 high-DPI | [SDL3 README-highdpi](https://wiki.libsdl.org/SDL3/README-highdpi) | SDL3 pixel density and content scale differ by OS, Windows window-size pixels vs UI scale; no double scaling |
| SDL event loop | [SDL_PumpEvents](https://wiki.libsdl.org/SDL3/SDL_PumpEvents) | must run on main thread; reuse CORE-01 event loop, no second PLAT pump |
| SDL3 license | [SDL LICENSE](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) | zlib-style permissive, retain source notice, exact release and bundled dependencies verify |
| GameInput PC | [Microsoft GameInput PC NuGet/redist](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/input/overviews/input-nuget?view=gdk-2510) | GameInput v1+ PC NuGet redist MSI not auto-installed, packaging must account for it |
| GameInput 4.0 | [GameInput sideloading](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/input/overviews/input-agility-redistributable?view=gdk-2610) | optional v4 sideload DLL or installed redistributable; read exact licensing/versions, dedup SDL gamepads |
| DXGI flip / tearing | [Microsoft DXGI flip model](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/for-best-performance--use-dxgi-flip-model), [tearing flags](https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-present) | prefer flip presentation in D3D case, capability check for tearing/VRR, no MSAA swapchain direct |
| D3D12 Agility | [Microsoft Agility SDK releases](https://devblogs.microsoft.com/directx/directx12agility/) | as-of Nov 9 2026 1.620.2 release documented; **candidate not selected**, requires driver/redistributable terms and GPU tiers |
| Windows App SDK deployment | [Microsoft deployment architecture](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/deployment-architecture) | optional framework-dependent packaged/unpackaged; unpackaged requires bootstrapper & runtime deployment, no default WinUI/SDK |
| MSIX packaging | [MSIX packaging overview](https://learn.microsoft.com/en-us/windows/apps/package-and-deploy/packaging/) | packaged package identity/store vs unpackaged MSI/EXE separate business decision |
| Windows DLL security | [Microsoft DLL load security](https://learn.microsoft.com/en-us/windows/desktop/dlls/dynamic-link-library-security) | CWD DLL planting; enforce safe loader search and allowed absolute application/runtime package paths |
| Code signing | [Smart App Control signing](https://learn.microsoft.com/en-us/windows/apps/develop/smart-app-control/code-signing-for-smart-app-control) | trusted publisher/cert required for some protected devices; unsigned smoke != release-ready |
| C++/SDL build | [CMake Presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html), [MSVC docs](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category) | reproducible environment, MSVC/Clang-cl, CRT choice, win x64 and future ARM64 compatibility |
| Vulkan WSI | [Khronos Vulkan Guide](https://docs.vulkan.org/guide/latest/), [GFX-01 RHI research](../architecture/gfx-01-graphics-rhi.md) | Vulkan Windows surface vs D3D12/DXGI compare, no global backend selection |
| Windows audio APIs | [Windows Core Audio APIs](https://learn.microsoft.com/en-us/windows/win32/coreaudio/core-audio-apis-in-windows-vista), [WASAPI docs](https://learn.microsoft.com/en-us/windows/win32/coreaudio/wasapi) | shared/event-driven and endpoint hotplug candidates; AUD owner only |

## 2. Technology/license/ownership candidate matrix, NO ADOPTION
| Candidate | License/distribution status | Advantage | Gate / risk |
|---|---|---|---|
| CORE-01-owned SDL3 native Win32 event host | SDL3 zlib root + exact tag notices; Windows SDK terms | cross-platform parity and main-thread pump | high DPI/focus/IME/relative mouse/monitor/hotplug real test |
| Win32 native bridge for HWND/DPI/clipboard/window APIs | Windows SDK/Windows binary SDK license; not a copied open-source library | precise integration where SDL gap | OS version gating, COM thread/ABI, native handles never escape API |
| Vulkan Windows WSI loader/layers | Khronos open source loader/SDK components and licenses vary by tag | shared native Vulkan with Linux | supported instance/device extensions, GPU tiers, HDR/VRR, driver tested |
| D3D12 + DXGI flip | Windows platform API, Agility runtime licenses/redistributable | Windows advanced GPU and flip presentation | actual GPU feature caps, driver, upload, shader compiler GFX-02 |
| SDL3 GPU | SDL3 zlib, alternate GFX-01 option | cross-platform simple surface/GPU path | feature tier ceiling, no hardcoded AAA assumption |
| GameInput PC v1+/v4 | Microsoft NuGet/GDK runtime redistributable terms require audit | modern controller/impulse/haptics | SDL duplicate events, XInput devices, MSI/sideload and security |
| SDL gamepad/XInput/Raw Input | SDL mapping source rights/third-party database notices | baseline cross-platform support | device IDs and focus epochs, no global raw input logging |
| WASAPI Core Audio | Windows APIs; API host included; playback library dependency separately | low-latency shared/event-driven and device events | AUD owner only, realtime callback safety, real headset switching |
| XAudio2/miniaudio | miniaudio public-domain/MIT-style dual choice to verify exact repo; Microsoft runtime terms | audio mixing backend compare | no second PLAT audio mixer, license/ABI/latency/codec proof |
| Windows App SDK 2.x / WinUI3 | Microsoft NuGet/source distribution and runtime terms | Windows modern shell features | Win32 app may not need it; bootstrap/setup, lifecycle, dependency drag |
| MSIX packaged | Windows packaging/signing terms and package identity | repair/update and Store path | business BIZ-03 publisher/signed install/reputation/cost |
| EXE/MSI unpackaged | installer framework license TBD, VC++ redistributable license | internal portable smoke and direct distribution | DLL search/publisher signature clean-machine prerequisites |
| Windows x64 | MSVC/clang-cl, Windows SDK terms | mandatory candidate desktop CI and hardware proof | official minimum OS+GPU remains OPEN, test on real machine |
| Windows ARM64 | native toolchain and third-party ABI notices | battery-efficient/modern devices | optional future release class; no automatic Windows coverage claim |
| Windows 10 LTSC/ESU | Microsoft per-SKU support + license entitlements | potential enterprise support | not default; mainstream EOS and lifecycle security risk |

## 3. Security threat model and negative acceptance
| Threat | Required future mitigation/oracle |
|---|---|
| DLL hijack via project folder/CWD | Windows secure DLL search, verified module path/signature and OS sentinel |
| Dynamic Win32 symbol/untrusted plugin loading | allowlisted absolute path and signature, no arbitrary plugin discovery |
| OS handle exposed through MCP/LLM | opaque generation-limited WindowId, no HWND/raw HID/GPU pointers |
| Raw input/IME leakage and keylogging | CORE-01 host event authority, GAME-01 context, no background capture |
| SDL+GameInput duplicate gamepad edges | provenance priority and DeviceEpoch source dedup, golden action frame |
| Focus loss leaves mouse captured/stuck attack | reset held state GAME-01, restore cursor, device remove journal |
| High DPI double-scaling clicks and UI | independently measured pixel/content/DPI scales and hit testing |
| Driver GPU loss/resize resources reused | GFX-01 device/surface generation and fences, RESTART_REQUIRED if owner can't recover |
| HDR/tearing silently enabled on wrong monitor | capability guard, valid DXGI flags and independent present receipt |
| CWD path/reparse/OneDrive content escapes project | DATA-01 VFS canonicalization and source license/ACL |
| UAC elevation or installer on game start | least-privileged run; separate BIZ-03 approved installer identity |
| Unsigned or unlicensed binary presented as production | signature/Smart App Control clean machine check and no false release claim |
| Update downloads execute arbitrary code | BIZ-03 signer+manifest/rollback; no PLAT update process |
| Crash dump/telemetry reveals project secrets | CORE-06 local redaction and explicit export consent |
| Unsupported Windows 10 SKUs treated as secure | explicit OS build servicing checks, fail closed for unapproved tier |
| Hardware runner vs real GPU confusion | virtual CI limited to build/headless, independent physical hardware proof |

## 4. Decision policy, no measured technology ranking
A future approved scoring exercise might weigh native input/window parity, device/adapter correctness 25%, security/redistribution 25%, Windows feature coverage 20%, cross-OS reuse 15%, performance/power 10%, maintenance/SDK cost 5%; **all numeric scores currently NOT MEASURED**. Vulkan vs D3D12 cannot be ranked by generic internet opinions. Pin exact SDL, Windows SDK 26100/28000 support, GameInput, Agility, RHI and audio versions, test both GPU/driver tiers, analyze full SPDX/SBOM/NOTICE/CVE, compare clean machine, then owner chooses ADR. NLE-D009 engine license OPEN; no publishing or signing expense approved.

[Architecture](../architecture/plat-01-windows-desktop-target.md) · [ADR-0069](../adr/0069-plat-01-windows-host-boundaries.md) · [Contracts](../contracts/plat-01-windows-target-api.md).
