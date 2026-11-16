# PLAT-04 — 2026 Android/iOS Technology, Compatibility, Licensing and Security Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY | [research #333](https://github.com/KayzenRoot/stormline/issues/333) | WO NLE-P00-WO-002-PLAT-04 | code [#88](https://github.com/KayzenRoot/stormline/issues/88) OPEN/BLOCKED | BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`.** Catalog 70/80, formal deps **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), original registry 69/80 researched, 11 pending, 80 code WOs BLOCKED, zero ready, approved ADR, engine=false and release classes UNDECIDED.


**Candidates and primary-source policies, NO pinned SDK/library, no accepted source license or mobile release.** Phone GPUs, OS versions, store rules, charges and hardware compatibility can change: revalidate before code and publication.

## Primary 2026 references and exact implications
| Reference | Verified source / policy | Future enforcement |
|---|---|---|
| Android Vulkan | [Android graphics overview](https://developer.android.com/games/develop/vulkan/overview), [native game Vulkan](https://developer.android.com/games/develop/vulkan/native-engine-support) | Android7/API24 Vulkan available on capable devices, Vulkan1.1 on new 64-bit devices Android10+; no guarantee all shipped games target support selected Vulkan features, GPU family and Baseline profile actual query |
| Android GameActivity | [Android official GameActivity](https://developer.android.com/games/agdk/game-activity/get-started), [overview](https://developer.android.com/games/agdk/game-activity) | Jetpack GameActivity recommended native C++ game integration, TextInput, Native glue vs SDL3 host; never two independent event pumps, inspect AAR/Prefab source/build terms |
| Android SDK/store target | [Google Play targetSdk requirement](https://developer.android.com/google/play/requirements/target-sdk) | **Aug 31 2026 new apps/updates Android16/API36+** for phones; separate minSDK and compileSdk/ABI and OS physical compatibility, exceptions other form factors not automatically mobile |
| Native page size | [Android 16KiB page sizes](https://developer.android.com/guide/practices/page-sizes) | 64-bit native libs on target API35+ must support 16KiB devices; NDK r28+ default ELF alignment; February 1 2027 additional update restriction, all prebuilts/ELF/APK and mmap tested |
| Android ADPF thermal | [ADPF](https://developer.android.com/games/optimize/adpf) and [Thermal API](https://developer.android.com/games/optimize/adpf/thermal) | Game Mode/Performance Hint/Thermal headroom conditional API and device support, NaN/unknown; do not poll ThermalHeadroom > once/10s, no thermal bypass |
| Android package signing | [Play App Signing](https://developer.android.com/studio/publish/app-signing) | upload key/Play generated key, AAB and approval by PLAT-05/BIZ-03; no keystore or store account present |
| Android asset packs | [Play Asset Delivery](https://developer.android.com/guide/playcore/asset-delivery) | install-time, fast-follow, on-demand **assets only**, do not assume external delivery or executable downloads; DATA-05 cooks target-specific verified chunks |
| iOS Store SDK rules | [Apple upcoming requirements](https://developer.apple.com/news/upcoming-requirements/) | **Xcode26+ using iOS26 SDK since Apr 28 2026**, **uploaded iOS apps target iOS13+ since Sep 9 2026**; submission rule is not min OS/owner-required app version |
| SDL3 iOS | [SDL3 iOS README](https://wiki.libsdl.org/SDL3/README-ios) | iOS xcframework/platform slices and UIKit integration candidate, exact tags and Apple toolchain version pin required |
| UIKit lifecycle | [Apple app lifecycle](https://developer.apple.com/documentation/uikit/managing-your-app-s-life-cycle) | UIScene separate foreground/background/suspended sessions, restrictions on ongoing background work and scene/Metal surface lifetimes |
| Apple Metal | [Metal](https://developer.apple.com/documentation/metal/) / [CAMetalLayer](https://developer.apple.com/documentation/QuartzCore/CAMetalLayer) | native iOS Metal per GFX-01, actual GPU feature/limits, no Vulkan iOS default or universal Metal4 tier |
| Game Controller | [Apple Game Controller](https://developer.apple.com/documentation/gamecontroller/) | controller device/haptic support per hardware/permission, GAME semantic input remapping |
| iOS battery/thermal | [Apple ProcessInfo thermal](https://developer.apple.com/documentation/foundation/processinfo/thermalstate), [Low Power Mode](https://developer.apple.com/documentation/foundation/processinfo/islowpowermodeenabled) | adaptive QoS/quality when callbacks available, iOS background and memory pressure can kill process without recovery callback |
| App Store review/privacy | [Apple App Review Guidelines](https://developer.apple.com/app-store/review/guidelines/), [App privacy](https://developer.apple.com/app-store/user-privacy-and-data-use/), [third-party SDK manifests](https://developer.apple.com/support/third-party-SDK-requirements/) | app completeness/account/privacy manifest, listed SDK signatures, tracking/ATT if relevant; no auto-approval |
| Android storage/permissions | [Android target SDK guide](https://developer.android.com/google/play/requirements/target-sdk) | scoped storage, user-granted documents, runtime permission and Play policy, no privileged hidden access |

## Candidate dependency and license matrix (all versions and transitive notices TODO)
| Candidate | Source/license/provenance gate | Value | Risks and alternatives |
|---|---|---|---|
| C++20 CORE+RHI/game engine | **Stormline license NLE-D009 OPEN**, code not present | shared native business logic | no adoption of production code by documentation |
| SDL3 Android/iOS | SDL3 zlib license (inspect exact upstream tag) | single host event loop and native window/input glue | Android GameActivity collision; iOS UIKit scene delegate event ownership/keyboard; framework distribution |
| Android NDK/SDK/Gradle/AGP | Google SDK/NDK and build tool licenses, versions/packs pinned in future | ARM64 native builds and 16KiB ELF | SDK API and third-party .so versions/reproducibility/cost not verified |
| Jetpack GameActivity | AndroidX Apache-2.0 family candidate; actual AAR/Prefab notices verify | native Android Activity/JNI/text input | competing SDL owner and Java lifecycles; choose ONE architecture after A/B |
| Vulkan Android loader/validation | Vulkan-Headers Apache-2.0, loader/SDK component licenses vary by exact upstream tags; OS drivers vendor-proprietary | native Android GPU high-performance path | tile GPUs/profile/driver, queue, loss, FENCE and memory layout; GL ES optional fallback |
| OpenGL ES 3.x/EGL | Khronos API spec, SDK/driver vendor licenses | reduced graphics on supported Android older hardware | no WebGL/Metal equivalence, shader/feature parity owner GFX-01 |
| Android ADPF Game Mode/Performance Hint | Android OS/NDK/AndroidX implementation varied | sustained thermal scheduling | device/API availability and NaN, no thermal safety override |
| Play Asset Delivery / Play App Signing | Google Play services/publishing terms, required account approval; library terms exact | distribution assets and signing | delivery lock-in, dynamic pack eviction, offline/staged patch, not engine core |
| Android user-scoped Storage Access Framework | OS API, not bundled library | user-consented projects/files | permission revocation and persisted grants, no raw storage bypass |
| Apple Xcode/iOS SDK/Objective-C++/UIKit | **Apple proprietary SDK and Program terms**, pin exact Xcode/SDK | native iOS package and UIKit lifecycle | Mac/Xcode host/provisioning requirements, pricing unapproved |
| iOS Metal/CAMetalLayer/MTKView | Apple platform framework license | native high-end rendering via GFX-01 | MTLDevice/generation/feature tier, shader compiler and 3D quality |
| SDL3.xcframework iOS | SDL zlib + nested frameworks/source/Apple bundling rights | platform host candidate | simulator and device slices differ, signing/runtime ABI |
| Apple Game Controller / CoreMotion | Apple SDK terms | optional gamepad and gesture/motion input | no default sensor collection, TCC/permission, sampling/power |
| Foundation ProcessInfo thermal/Low Power | Apple SDK | thermal-aware quality | coarse/late signals and iOS app suspension |
| Texture codecs ASTC/ETC2/PVRTC/KTX2 | KTX-Software, Basis Universal codec and transitive licenses by exact tag | mobile-target cooked textures | every GPU format/driver probe, decompression budget, DATA-05 owner |
| Crash monitoring/analytics/ads | optional third-party SDK privacy/legal terms | future distribution/diagnostics | **NOT selected**, privacy manifests ATT/Play declarations, no paid telemetry or native secrets |
| App Bundle/IPA/TestFlight/App Store/Play | platform terms, account fees/review and store rules owner approval | publish selected games | PLAT-05/BIZ-03 owners, signing keys never in repo or public logs |

## Security threat model, negative tests required before future runtime
| Threat | Required fail-closed proof |
|---|---|
| Arbitrary AI/MCP C++/JNI/Swift execution injected from project | signed/authorized capability-limited authoring, denied native shell, no untrusted binary execution |
| Android exported Activity/deep-link spoofing | nonexported components, scheme/host allowlist, input validation and immutable PendingIntent where relevant |
| Android native .so malicious preload or wrong ABI/page alignment | 16KiB ELF/payload inspection, signed package, checksum/source provenance; reject incompatible |
| Malicious upload/download/asset code in Play delivery packs | DATA-05 trusted manifest + per-chunk integrity and quota, no executable asset pack |
| iOS runtime downloaded code/JIT plug-in | review/signature/sandbox rules, deny code execution outside approved policies |
| Android ALL_FILES_ACCESS/AccessibilityService/overlay misuse | minimum AndroidManifest, no privileged permission without purpose/owner approval |
| iOS location/microphone/camera/motion/ATT misuse | user permission and required-use privacy declaration, no sensor collection by default |
| OS scoped storage/sandbox path escape | user intent scopes, revoked bookmark/URI refusal, symlinks and paths sanitized |
| App store signing key exposed in public GitHub workflows | no secrets stored, signing handled later by approved PLAT-05/BIZ-03 |
| Background app continues 100% render/network/recording | pause, suspension-safe save, no unapproved background mode |
| Device rotation/fold/scene destroy races with GPU or touches | separate epochs, RHI resource invalidation and GAME CANCEL all held gestures |
| Thermal signal NaN/stale or hot device | bounded conservative quality fallback, prevent infinite thrash and safety override |
| Dynamic scale blurs text/pixel art or inaccessible gestures | separate UI overlay scale and keyboard/VoiceOver accessibility, alternate input |
| Resource OOM/jetsam process loss corrupts authored project | transactions/checkpoint, last-good, restart recovery and bounds |
| GPU driver crash/fence/context loss | RHI device generation and clear RESTART_REQUIRED/rehydration |
| Battery fingerprint/sensor/device identifier telemetry | coarse tier/redacted hardware, opt-in diagnostics, no persistent high-entropy serial |
| SSL/network/CSP/URL issues in assets | scoped network endpoints, trusted manifest and no arbitrary plaintext code download |
| Misreported target SDK/store account implies compliance | actual Play/App Store submission API SDK signing/privacy/review evidence or NOT_VERIFIED |

## Proof obligations and scorecard: not measured
Candidate future scoring ONLY after owner picks platform classes: **capability and correctness 25%, security/privacy/licenses 25%, sustained energy and thermal 20%, user touch/accessibility/UX 15%, packaging/test feasibility 15%**. No fake device coverage percentage, GPU feature guarantee, performance target, store enrollment or business class. Current documentation only LOW risk; future permissions/publisher keys/privileged access HIGH_ASSURANCE.

[Architecture](../architecture/plat-04-mobile-target-adaptation.md) · [benchmark](plat-04-mobile-benchmark-protocol.md) · [ADR-0073](../adr/0073-plat-04-mobile-target-android-ios-policy.md).
