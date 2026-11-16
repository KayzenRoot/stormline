# QA-05 — OS/GPU/Driver/Browser, Packaging, Licensing, R$0 Technology Matrix (2026)

**2026-11-16 | P00 DOCUMENTARY RESEARCH | [research #357](https://github.com/KayzenRoot/stormline/issues/357) | NLE-P00-WO-002-QA-05 | future coding [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED | base `a42519c8a79346a4974fa74c44f7cac26f4ad43c`.** QA-05 ordinal 76/80; formal dependencies **QA-02 + PLAT-05 ONLY**, predecessor ADR-0076/0074 PROPOSED. Initial 75/80 researched, 5 pending, 80 code WOs BLOCKED, 0 ready/approved ADR, all release classes UNDECIDED, engine_implemented=false.


**Candidates only.** Nothing here certifies operating-system support, GPU/driver presence, export compatibility, license approval or actual tests. Version, host and vendor licensing must be checked at code activation; original commercial game screenshots are not test fixture rights.

## Authoritative 2026 sources and qualification implications
| Official source | Verified fact / capability | Future qualification evidence |
|---|---|---|
| [Microsoft WARP](https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp) | software rasterizer that runs without real GPU; Direct3D 12 through eligible feature levels and OS versions | Win-WARP functional rendering only, tag SOFTWARE_CPU; **never physical AMD/Intel/NVIDIA cert** |
| [Microsoft D3D12 device features](https://learn.microsoft.com/en-us/windows/win32/direct3d12/direct3d-12-feature-support) | `ID3D12Device::CheckFeatureSupport` enumerates supported feature levels/features per adapter | real device+driver and queried feature requirements, shader model by API; mere Windows version not proof |
| [Khronos Vulkan Profiles](https://docs.vulkan.org/guide/latest/vulkan_profiles.html) | named JSON profiles maintained by Khronos/LunarG/Google including Roadmap, device capability check | versioned profile match + actual loader/ICD/queue/swapchain/driver, do not promise broad conformance from profile name |
| [Khronos Vulkan portability](https://docs.vulkan.org/refpages/latest/refpages/source/VK_KHR_portability_subset.html) | portability subset marks optional support constraints on portability implementations | per-device feature and portability extension, not “all Vulkan is identical” |
| [Mesa Vulkan drivers](https://docs.mesa3d.org/vulkan-drivers.html) | Mesa's open Vulkan drivers differ by GPU families and supported features | Linux distro/kernel/Mesa/firmware/GPU/Wayland/X11 matrix, own driver versions and original hardware |
| [Apple 2026 Metal supportsFamily](https://developer.apple.com/documentation/metal/mtldevice/supportsfamily(_:)) | `MTLDevice.supportsFamily(MTLGPUFamily)` is modern capability check; `MTLFeatureSet` deprecated | Apple Silicon vs Intel-native Metal GPU family and exact feature use, not one-size renderer |
| [Apple Xcode 27 release notes](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes) | Xcode 27 host Apple Silicon, supports universal backdeploy macOS 12+, x86_64 no longer standard when deployment target >=27 unless explicit | native arm64 test on real Mac, conditional Intel real macOS 26 or earlier and signed packaging, no translated-only Mac support |
| [Apple Rosetta Sep 2026](https://developer.apple.com/news/?id=w5ngl9k2) | macOS 26 last Intel hardware line and final general-purpose Rosetta macOS 27, narrow future legacy unmaintained games exception | actively maintained Stormline must not rely on Rosetta exception, record native-arch |
| [Apple notarize](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/) | notarization service/signing and Hardened Runtime requirements for distribution path | notarization only when actual signing identity / paid account policy approved; cannot infer from shell script |
| [WebGPU spec](https://www.w3.org/TR/webgpu/) | optional adapter features and limits, privacy buckets, device loss, secure contexts | each browser+OS real adapter/feature matrix and original Web fixture |
| [MDN GPUAdapter limits](https://developer.mozilla.org/en-US/docs/Web/API/GPUAdapter/limits) | browser limits may be bucketed lower than hardware to reduce fingerprinting, support not Baseline everywhere | no GPU model fingerprint/exact raw VRAM inferred from browser, test live adapter limits |
| [Playwright screenshots](https://playwright.dev/docs/test-snapshots) | OS/browser/version/fonts/power source/headless affect snapshot rendering | pin baseline host vs new host and require separate owner approval for golden, no automatic accept |
| [Windows Application Recovery and Restart](https://learn.microsoft.com/en-us/windows/win32/recovery/using-application-recovery-and-restart) | Windows Error Reporting supports opt-in recovery callbacks/restart under conditions | app recovery callbacks not replacement for persisted known-good, test actual failure/restart |
| [POSIX rename semantics](https://pubs.opengroup.org/onlinepubs/9799919799/functions/rename.html) | pathname replacement atomic visibility under specified FS environment, does not alone guarantee power-failure durability | write fsync + directory durability strategy and real injection on each target |
| [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions) | standard GitHub hosted runner compute free for public repositories, storage/cache billed beyond allowances | R$0 service stop, no assumption free real Apple/Windows GPU/larger runner |
| [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) | can select/test/emit JUnit, CMake toolchain and environment dependent | QA-01 integration CTest nonzero actual counts, docs-only CI never pass as qualification |

## Candidate technology/license/support map, all PROPOSED
| Item/tool | Legal/license categories to verify by pinned tag | Needed evidence or constraint |
|---|---|---|
| Windows 11 SDK + D3D12/DXGI and native Win32 | Microsoft proprietary Windows SDK terms and OS distribution | vendor device, CPU arch, feature levels, Win64 C++ runtime/DLL dependency, package signing separately |
| Visual Studio Build Tools/clang-cl/CMake/Ninja | VS Build Tools Microsoft terms; CMake BSD-3; Ninja Apache-2.0 | clean x86_64/ARM64 build if approved, VS redist rights and timing/flags |
| DirectX WARP | Microsoft proprietary OS component | deterministic CPU-only fallback; no physical driver/HDR/frequency proof |
| Vulkan SDK/loader/Validation Layers | Vulkan-Headers license MIT/Apache variations, LunarG SDK EULA and component notices, ValidationLayers Apache-2.0 | actual device/driver version/profile and surface/headless separately, exact runtime libs and redistributability |
| Mesa RADV/ANV and llvmpipe | Mesa generally MIT, embedded per-driver third-party license/firmware | real AMD/Intel GPU vs llvmpipe CPU explicit; Linux distro/firmware, driver benchmark real |
| Proprietary NVIDIA/AMD drivers | vendor proprietary EULA or mixed open modules, separate driver distribution rights | do not bundle drivers or redistributable docs by assumption; test qualified driver |
| Linux glibc/libstdc++/SDL3/Wayland/X11 | glibc LGPL-2.1-or-later; libstdc++ GPL-3.0-with-runtime-library-exception (check tag); SDL3 zlib; Wayland MIT; X.org components MIT/X11 | ABI baseline/GLIBC symbol versions and user-mode dependencies, Wayland/X11 DPI/audio/input, source engine license OPEN |
| Flatpak/AppImage/tarball/native package | Flatpak LGPL-2.1-or-later components, AppImage toolkit terms vary, dpkg/tar GPL/BSD and binaries have own licenses | PLAT-05 selects approved export format, desktop runtime installation and signature checks |
| Apple Xcode 27 SDK, Metal/Cocoa/Universal binaries | Apple proprietary SDK/toolchain developer agreement, sign/notarize service availability | arm64 real Mac, conditional x86_64 eligible macOS, Xcode host Apple Silicon, TCC/Hardened Runtime and owner accounts |
| macOS Metal layer/device families | Apple OS API proprietary framework license terms | real MTL family support + actual render, Intel and ARM not assumed equal, Apple EDR/HDR separate |
| Browser Chrome/Chromium | Chromium mixed BSD-3 + third-party licenses, Chrome Google proprietary distribution | distinct browser versions, GPU backends and testing permissions |
| Firefox/Gecko | MPL-2.0 with third parties | Firefox WebGPU status per OS/build/user agent, feature probe, actual Playwright scope |
| Safari/WebKit | WebKit LGPL-2.1+BSD mix and Apple Safari proprietary browser terms | Safari macOS/WebKit feature+permissions, no “Playwright WebKit == all Safari releases” claim |
| Playwright test framework | Apache-2.0 for Playwright, bundled browser runtime separate rights | browser/OS snapshot stable per profile; no native hardware equivalence |
| CMake/CTest/GoogleTest | CMake BSD-3; GTest BSD-3, test runner libraries exact versions | QA-01 owns runner; actual compile and original QA-02 fixtures required |
| Vulkan SwiftShader CPU | Apache-2.0 with third-party notices | software Vulkan headless, not real GPU, with security restrictions |
| Shader compiler DXC/glslang/SPIRV-Tools | LLVM Apache-2.0 WITH LLVM-exception for DXC components; glslang BSD-3/Apache variations, SPIRV-Tools Apache-2.0 | compile shader ABI/code versions and asset hash, licensing before redistribution |
| AddressSanitizer/UBSan, runtime scanners | LLVM Apache-2.0 WITH LLVM-exception and OS support | QA-04 integrates security, not proof on unsupported release host |
| Original scenes/fonts/audio and golden images | rights per original authored fixture, OFL/CC/license if later assets adopted | signed original ownership metadata, avoid unlicensed game screenshots/audio |
| Cross-platform crash dump reporters | Windows WER Microsoft terms, Linux systemd-coredump LGPL-2.1+ or distro and coredumpctl privileges, macOS DiagnosticReports Apple terms | crash dumps may leak keys/project assets; opt-in/private ACL, no automatic public CI uploads |
| Installer/updates/signing | Microsoft Authenticode/cert CA fees, Apple notarization/account, Linux signing tool chain terms | owner-approved PLAT-05, BIZ-03 release; no purchased cert/release in P00 |
| GitHub standard hosted runners | GitHub SaaS terms, public compute free conditional | Windows/Linux/macOS builds may run basic compile future, **not** physical GPU qualification or free unlimited artifact retention |
| Remote hardware farms | proprietary SaaS and GPU/Apple device cloud fees | OUT OF SCOPE R$0 without owner budget/approval, NOT_QUALIFIED instead |

## Candidate deployment and support tiers, NOT RATIFIED
- **Native Desktop required classes:** WIN-x64 (D3D12/VK per owner backend), LINUX-x64 (Vulkan/Wayland or X11 by owner OS baseline), MAC-arm64 native (Metal real Apple Silicon). QA-05 must prove Editor **and** exported game separately; CPU server/headless separate role. Historical Intel Mac target **conditional** and Web pending specific owner release class (Web games planned).
- **Hardware classes:** affordable Intel UHD/Iris/Arc, AMD Radeon APU/RDNA discrete, NVIDIA GeForce lower VRAM, Apple M-series native Metal, optional qualifying macOS Intel real GPU. These are **families to select physically later** not vendor endorsement and no fabricated purchases/measurements. Each requires actual driver/OS/SDK, render test and recovery evidence.
- **Evidence:** build SHA/artifact/manifest from PLAT-05, original golden+input/audio/scene from QA-02, actual device feature/VRAM/residency and physical flag, accessibility by keyboard/screen reader on device, install/upgrade rollback and soak with crash/restore. QA-03 p95/p99 as integration only; no numeric threshold approved.
- **Security and price:** NLE-D009 engine license OPEN, no public MVP, no paid services, no proprietary assets, no automatic secret crash uploads. All 80 code WOs blocked.

[Architecture](../architecture/qa-05-compatibility-release-qualification.md) · [Benchmark](qa-05-compatibility-soak-recovery-benchmark-protocol.md) · [ADR](../adr/0079-qa-05-platform-compatibility-qualification-policy.md).
