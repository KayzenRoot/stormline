# PLAT-06 — November 2026 macOS Technology, Compatibility, License and Security Matrix

**2026-11-15 | P00 RESEARCH ONLY | WO NLE-P00-WO-002-PLAT-06 | research #329 | code #87 OPEN/BLOCKED | base 109287f928b4436b31188c1dd8cf4f7a454ad989.** Formal deps CORE-01 + GFX-01 + GAME-01 only. ADR-0003/0014/0042 PROPOSED; all 80 code WOs BLOCKED, engine_implemented=false, no SDK/build or signed Mac binary.


**Source-backed candidates, not adopted technology/license, runtime compatibility certification, actual Apple Silicon/Intel Mac hardware, SDK, build or notarization.** Engine source license NLE-D009 OPEN.

## Platform and upstream 2026 verified evidence
| Topic | Primary reference | Engineering constraint |
|---|---|---|
| Intel Mac OS cutoff | [Apple WWDC26 Platforms State of the Union](https://developer.apple.com/videos/play/wwdc2026/102/) | macOS Tahoe 26 is final Intel Mac major OS release; Apple Silicon mandatory; Intel hardware <=26 conditional |
| Rosetta transition | [Apple September 2026 news](https://developer.apple.com/news/?id=w5ngl9k2) | macOS27 final general Rosetta, later narrow exception old unmaintained games; arm64 natively mandatory |
| Xcode 27 ARM host | [Xcode27 release notes](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes) | Apple Silicon-only Xcode host; SDK supports universal backdeployment; ARCHS_STANDARD excludes x86_64 with >=27 target |
| Universal Mach-O | [Apple universal app binaries](https://developer.apple.com/documentation/apple-silicon/building-a-universal-macos-binary) | all nested helpers/frameworks and executable slices must be validated with lipo/file/otool/vtool |
| SDL3 Cocoa | [SDL3 macOS](https://wiki.libsdl.org/SDL3/README-macos) | SDL3 can be built for universal, but its example SDK/min OS is not selected Stormline minimum; delegate collisions and native bundle |
| SDL3 Metal bridge | [SDL3 SDL_Metal_CreateView](https://wiki.libsdl.org/SDL3/SDL_Metal_CreateView) | main-thread only, creates CAMetalLayer view without assigning MTLDevice |
| Cocoa AppKit | [NSApplicationMain](https://developer.apple.com/documentation/appkit/nsapplicationmain), [backingScaleFactor](https://developer.apple.com/documentation/appkit/nswindow/backingscalefactor) | application main-thread, point to backing conversion not physical pixels |
| Metal / present | [CAMetalLayer](https://developer.apple.com/documentation/QuartzCore/CAMetalLayer), [Metal](https://developer.apple.com/documentation/metal/) | GPU belongs GFX-01; actual device/format/features and context/layer generation |
| Metal 4 | [macOS26 Metal release notes](https://developer.apple.com/br/documentation/macos-release-notes/macos-26-release-notes) | Metal4 is a feature family and actual availability must be queried; no Intel blanket support |
| GPU working set | [Apple recommendedMaxWorkingSetSize](https://developer.apple.com/documentation/metal/mtldevice/recommendedmaxworkingsetsize), [multi-GPU](https://developer.apple.com/documentation/metal/selecting-device-objects-for-graphics-rendering) | advisory not total VRAM; Intel GPU switch/eGPU conditional |
| Game controllers | [Apple Game Controller](https://developer.apple.com/documentation/gamecontroller/) | SDL/GameController duplicates possible, user remap and TCC permissions |
| Hardened runtime | [Apple Hardened Runtime](https://developer.apple.com/documentation/security/hardened-runtime) | no blanket unsigned executable memory/JIT or disabled library validation |
| Developer ID notarization | [Apple notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/), [Developer ID](https://developer.apple.com/developer-id/) | certificate validity, hardened runtime, secure timestamp, approved notary ticket/Gatekeeper on real Mac |
| Mac App Store | [Apple App Sandbox](https://developer.apple.com/documentation/security/app-sandbox) | sandbox mandatory for Store channel, signed entitlements and user-file scope |
| Mac bundle metadata | [Apple distribution prep](https://developer.apple.com/documentation/Xcode/preparing-your-app-for-distribution) | Info.plist bundle ID/version/resources and nested signatures; release owner PLAT-05 |
| macOS27 installer behavior | [macOS27 release notes](https://developer.apple.com/br/documentation/macos-release-notes/macos-27-release-notes) | default arm64 hostArchitecture for installation packages in relevant cases; verify in actual build |

## Candidate license, maintenance and cost matrix (no approvals)
| Candidate | Probable license/terms, VERIFY PINNED TAG | Expected role | Required evidence and traps |
|---|---|---|---|
| C++20 + CMake/Ninja | platform toolchain/stdlib terms, CMake BSD3, Ninja Apache2 (verify exact tags) | cross-platform build | C++ ABI, arm64/x86_64, exact SDK/arch, reproducibility and licenses |
| Xcode27 Apple Clang/macOS SDK | Apple proprietary developer license; costs, certificate availability not assumed | Apple Silicon native build/Metal/Instruments | licensed download and official Xcode host only on Apple Silicon |
| SDL3 | zlib root, transitive source licenses by tag | CORE-01 single window/event pump | custom NSApp delegate and SDL_Metal_CreateView main-thread semantics |
| Objective-C++ AppKit/QuartzCore | Apple platform SDK terms, native frameworks | narrow Cocoa bridge | no extra NSEvent event loop, TCC and main-thread callbacks |
| Native Metal/CAMetalLayer | Apple platform SDK | GFX-01 RHI and presentation | Metal4/family/format/device query and shader validation, GFX-02 own |
| Optional MTKView | Apple SDK | UI wrapper comparator | may duplicate surface scheduling/MTLDevice ownership |
| Vulkan-on-Metal KosmicKrisp/MoltenVK | third-party exact tag/license maintenance VERIFY | GFX-01 optional A/B | NOT native macOS prerequisite; portability/cost/Metal feature differences |
| SDL3/Apple Game Controller | SDL zlib plus Apple SDK terms | GAME-01 semantic input | duplicated pad events, privacy/Input Monitoring, remap and haptics |
| CoreAudio, AVFoundation | Apple SDK | AUD integration only | audio output permission vs input TCC, no auto microphone |
| NSOpenPanel, scoped bookmarks | Apple SDK, App Sandbox entitlement | Editor user-selected files | stale bookmark, symlink escapes, revocation, consent |
| .app, DMG/PKG, Mac App Store | packaging vendor/service contracts unknown | PLAT-05/BIZ-03 | no invented signed/notarized public binary, explicit owner channel |
| Developer ID, notary/stapling | Apple Developer Program terms and certificate credentials | secure external distribution | account cost/access unapproved; not achievable from free docs validation |
| Mac App Sandbox | platform security rules | App Store distribution | per-file and network/plug-in/AI permissions, no broad entitlements |
| GitHub Actions macOS runner | availability/quota/OS SDK terms change | future CI for deterministic compile | hosted runner not proof of real monitor/GPU/thermal/TCC/sleep |
| Apple Instruments, Metal debugger | Xcode licensed developer tools | future frame/memory diagnosis | actual Mac/device + raw trace needed |
| Third-party font/asset/shader | potentially proprietary per asset | high-quality Editor/2D/3D | separate copyright/per-asset permissions/SBOM, no auto bundling |

## Threat model and fail-closed future oracles
| Risk | Negative-test obligation |
|---|---|
| DYLD injection, rpath poisoning, unsigned libraries | Hardened Runtime signature + signed nested framework and no debug/global bypass |
| App JIT/scripting plugin escapes | deny untrusted shell/JIT/unsigned plugin, explicit narrow capability only |
| Mac SDK signature mistaken for Developer ID | verify certificate chain, secure timestamp, notary ticket, Gatekeeper test |
| Signing key leakage in public Actions | no private key/cert in public repo, logs or downloadable artifacts |
| Intel vs ARM architecture confusion | actual physical Intel native test, not Rosetta; each Mach-O slice verified |
| macOS27 running on Intel claim | reject invalid OS/physical architecture profile |
| Unsafe AppKit off-main thread | future main-thread guard assertion, no callback use-after-free |
| Metal drawable/device lost/reuse | generation-bound resource lease, fail typed or bounded restart |
| Unified memory oversubscription | engine budgets, advisory working set, pressure/thermal signals |
| App Sandbox escape/user file leak | NSOpenPanel user selection, security-scoped grant bounds and expiration |
| TCC Accessibility/Input Monitoring silently captured | explicit user denial and fallback; no private keystroke logging |
| Input duplicated SDL/GameController | sole CORE-01 event authority, GAME-01 action oracle |
| IME composition as gameplay hotkey | physical vs text channels and focus/typing proof |
| Save project lost on quit/crash/upgrade | Editor transactional veto, source model last-good, rollback |
| No Gatekeeper/quarantine check | fresh machine security verification, no xattr override |
| Plugin/AI privileged native file patch | operation capability + expected revision and audit receipt |
| Unknown SDK API min OS | weak-link runtime availability with explicit unsupported branch |
| Code or font license not cleared | exact compiler/SDL/fonts/framework tags and NOTICE inventory |

## Evaluation (unscored)
Future owner criteria proposed: 25% native correctness, 25% security/distribution/rights, 20% real Apple Silicon + conditional Intel compatibility, 20% Metal/2D/2.5D/3D quality, 10% startup/energy/maintainability. **No performance scores, chosen exact versions, legal clearance, commercial cost or deployed results today.** ADR-0072 remains PROPOSED and implementation #87 BLOCKED.

[Architecture](../architecture/plat-06-macos-desktop-target.md) · [benchmark](plat-06-macos-benchmark-protocol.md) · [ADR](../adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md).
