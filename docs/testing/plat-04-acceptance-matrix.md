# PLAT-04 — Exactly 128 FUTURE Mobile Android/iOS Acceptance Tests (P04-T001..T128)

**P00 research / NO CODE / no mobile installation, signed Android/iOS app, real GPU/phone tests, store publishing or benchmark.** WO NLE-P00-WO-002-PLAT-04 | [research #333](https://github.com/KayzenRoot/stormline/issues/333) | future code #88 BLOCKED. Base b12e0755fd9539406a2f92c8e51f1a6d6e19c73a, catalog module 70/80, formal deps **GFX-01 + GAME-01 only**, predecessor ADRs PROPOSED, all 80 coding WOs blocked.

**Exactly eight groups × sixteen unique IDs P04-T001..P04-T128, all FUTURE / NOT EXECUTED, none are PASS.** These are candidate test requirements for later owner-selected platform classes, not claims both Android/iOS are automatically required for 1.0.

## Future required test evidence
1. Real physical arm64 Android and selected iPhone/iPad hardware for supported target(s), exact OS build/API/minSDK/targetSDK/Android NDK/Xcode SDK, GFX Vulkan/Metal/GL capabilities, device GPU/driver, scene fixture hash and code source SHA. Emulators only for supplementary deterministic logic.
2. Original rights-cleared 2D and representative 3D scenes with actual build/open/close; fair reduced tier semantics, GAME-01 touch action remapping, UI accessibility and screen cutouts/foldables. Mobile Editor not presumed required unless release-class owner explicitly adds it.
3. Platform API logic: Google's Aug 2026 target API36+ Play rule, Android 16KiB ELF page support, iOS Xcode26+iOS26 submission SDK and iOS13+ targeting; verify near release, distinguish min runtime versions and simulator/device architecture.
4. Every device/Activity/UIScene/surface, pointer/contact, GPU resource and background cancellation uses generation/epoch validation and snapshots; denial, device loss or low-memory kill never corrupt last-good project save.
5. Android ADPF and iOS thermal/low power signals are conditional; no headroom pollution or 60/120 FPS universal promise. Sustained energy/perf tests must include temperature, battery/charging and frame percentile uncertainty, not burst-only marketing.
6. Security negatives with no real user files/keys; Android scoped storage and Play Signing/asset packs, iOS sandbox/provisioning/privacy manifests/ATT, signed app and store account only if owner approves. No arbitrary project JIT/downloaded executables.
7. Owner release-class decision remains UNDECIDED. A selected target could be marked FUTURE if cost/health/regulatory feasibility blocks it; unselected-target tests are UNSUPPORTED/OUT_OF_SCOPE only **after** owner approval, never fabricated PASS.
8. P00 Docs Validation and future physical test evidence are different categories; Stage P00 tests are not executed and no engine artifact exists.

## Group 1 — MOBILE-OS-ABI-BUILD

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T001 | Android arm64-v8a NDK C++20 native library builds with pinned toolchain | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T002 | Android target API36 application and future minimum API are independent | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T003 | Google Play signed AAB uses required target API at actual submission date | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T004 | Android 16KiB page native ELF segments align with tested memory page | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T005 | Android 4KiB memory-page legacy compatibility retained when approved | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T006 | All nested Android prebuilt .so libraries align for 16KiB-page hardware | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T007 | NDK mmap and allocator code does not assume page size 4096 | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T008 | Android AndroidX GameActivity and SDL3 host choice pinned single authority | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T009 | Android JNI refs/threads/lifecycle wrapper has no stale ref after Activity destroy | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T010 | iOS arm64 app built with pinned Xcode/iOS SDK and approved min OS | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T011 | iOS App Store Connect submission SDK26+ requirements checked as of date | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T012 | iOS Xcode xcframework device/simulator slices are correctly distinguished | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T013 | iPadOS layout and iOS phone architecture tested separately | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T014 | App background/kill/restore resumes signed existing generation | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T015 | Mobile source/build artifact hashes and third-party licenses/SBOM reproducible | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |
| P04-T016 | Unsupported OS/CPU/release-class profile returns explicit not-supported | Gradle/NDK/Xcode build, ABI/SDK/ELF page/xcframework + signed artifact receipt on selected real device | FUTURE / NOT EXECUTED |

## Group 2 — ANDROID-GPU-LIFECYCLE

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T017 | Vulkan instance/device API version features and extensions actually probed | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T018 | Android Vulkan1.1 plus baseline profile never inferred from OS label alone | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T019 | Unsupported required Vulkan feature yields fail or explicit reduced tier | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T020 | OpenGL ES fallback only for approved GFX-01 capability/quality profile | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T021 | Android ANativeWindow surface generation invalid on Activity stop/resize | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T022 | Vulkan swapchain out-of-date and suboptimal present handled safely | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T023 | Android GPU device lost cannot reuse old buffers or command resources | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T024 | Texture ASTC/ETC2 format selection based on actual GPU feature probe | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T025 | Tile-based GPU overdraw and bandwidth pressure measured | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T026 | Vulkan depth/origin/alpha premultiplication golden compatible with RHI | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T027 | Android 2D scene text and UI render readable high-density | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T028 | Android representative 3D scene renders within declared reduced tier | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T029 | Android variable-refresh or Game Mode present pacing user policy respected | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T030 | Foldable hinge/resize destroys or updates surface without race | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T031 | Android background app GPU stops rendering or reports typed block | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |
| P04-T032 | Low-memory GPU driver evictions trigger safe resource rehydrate/restart | GFX-01 Vulkan feature/driver/ANativeWindow generation with real Android original 2D+3D render and lost-state oracle | FUTURE / NOT EXECUTED |

## Group 3 — IOS-METAL-LIFECYCLE

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T033 | Actual iPhone Metal MTLDevice family/limits queried at runtime | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T034 | Required Metal features fail safely on unsupported iPhone GPU | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T035 | iPad Metal features/family profiled independently from iPhone | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T036 | UIKit UIApplication or UIScene delegate is single event lifecycle authority | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T037 | SDL3 iOS host integration does not double pump touch events | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T038 | CAMetalLayer drawable size uses correct points-to-pixels conversion | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T039 | iOS device rotation and safe-area change updates present and hit tests | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T040 | Multiwindow iPad UIScene surfaces maintain distinct epochs | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T041 | Background scene and OS suspension pause rendering safely | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T042 | iOS transient interruptions/audio route/call preserve state | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T043 | iOS low-memory warning/restart restores validated last-good save | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T044 | MTL device resource generation rehydrates after lifecycle loss | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T045 | iOS 2D alpha/text/UI original golden passes native Metal | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T046 | iOS representative 3D geometry/material scene passes native Metal | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T047 | iOS adaptive resolution never blurs logical UI/typography | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |
| P04-T048 | iOS simulator validation not falsely labeled physical iPhone GPU proof | GFX-01 Metal/CAMetalLayer real iPhone/iPad MTLDevice and independent native scene golden lifecycle | FUTURE / NOT EXECUTED |

## Group 4 — TOUCH-CONTROLLER-A11Y

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T049 | Single-touch start/move/end maps stable GAME-01 semantic ActionId | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T050 | Multitouch two-finger tracking preserves separate pointer/device epochs | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T051 | touch cancel/Android ACTION_CANCEL releases all held actions | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T052 | Pinch and rotate gesture conflict policy stable and deterministic | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T053 | Long-press/tap/double-tap latency tolerance measured on real device | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T054 | Physical touch pressure/tilt unavailable reports capability rather than zeros | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T055 | Touch orientation/hinge change transforms hitbox accurately | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T056 | Soft keyboard and IME text composition never interpreted as game input | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T057 | Bluetooth controller disconnect releases GAME-01 held inputs | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T058 | Mobile controller remap matches Editor/game action metadata | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T059 | Android joystick and iOS Game Controller duplicate events rejected | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T060 | Haptic feedback denied/unavailable follows accessible fallback | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T061 | Screen reader/VoiceOver/TalkBack semantic controls and focus usable | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T062 | Font scaling/Dynamic Type/large accessibility text maintains touch target | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T063 | Safe area/notch/home gesture avoids inaccessible interactive controls | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |
| P04-T064 | Keyboard/gamepad-only alternative navigation accessible where declared | CORE normalized pointer stream and GAME-01 semantic ActionMap with screen-reader/IME/controller physical oracle | FUTURE / NOT EXECUTED |

## Group 5 — THERMAL-BATTERY-MEMORY

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T065 | Android ADPF headroom API unsupported/NaN selects conservative policy | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T066 | Android thermal headroom polling interval respects >=10 seconds | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T067 | Android severe thermal signal triggers bounded quality degradation | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T068 | Android Game Mode performance/battery user preference respected | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T069 | Android Performance Hint session unavailable falls back without busy loop | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T070 | iOS ProcessInfo thermalState elevated triggers stable adaptive tier | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T071 | iOS Low Power Mode avoids high-frequency background work | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T072 | 30-60 minute sustained Android frame time distribution captured | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T073 | 30-60 minute sustained iPhone frame time distribution captured | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T074 | Frame pacing reduces GPU load without changing fixed simulation tick | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T075 | Dynamic resolution preserves pixel-art and readable UI glyphs | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T076 | Memory pressure releases noncritical resources under exact budgets | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T077 | iOS jetsam kill without warning recovers previously committed state | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T078 | Android process recreation after low-memory kill restores game state | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T079 | Thermal hysteresis prevents repeated quality up/down oscillation | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |
| P04-T080 | Energy/temperature/VRAM estimates clearly separated and privacy-safe | Android ADPF/iOS ProcessInfo traces, raw sustained power/thermal/RSS/per-frame and last-good save recovery | FUTURE / NOT EXECUTED |

## Group 6 — SECURITY-PACKAGING-ASSET

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T081 | Android permission denied for camera/mic/location does not block core game | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T082 | iOS app prompts privacy permission only when approved feature used | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T083 | Android scoped Storage Access Framework URI grants bounded to user file | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T084 | iOS app sandbox denies project-file path outside selected scope | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T085 | Android exported Activity/deep link hostile payload rejected | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T086 | Android App Bundle/Play App Signing upload-key workflow verified only if approved | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T087 | Play Asset Delivery install-time/fast-follow/on-demand pack version verified | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T088 | Offline missing/evicted asset pack gives typed recovery not asset corruption | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T089 | iOS signed IPA/provisioning profile and entitlement chain valid if approved | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T090 | App Store privacy manifest/signature required SDK inventory complete | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T091 | Apple ATT not silently triggered or bypassed if tracking feature included | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T092 | Android Google Play data safety/permissions disclosure accurate | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T093 | Untrusted downloaded project cannot load unsigned native executable/JIT | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T094 | Malicious decompression and symlink/path traversal denied within quotas | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T095 | Mobile API keys/certificates/IME text/device ID redacted from diagnostics | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |
| P04-T096 | Denied AI/MCP mobile packaging/signing action has no side effects | permissions/Android Play or iOS Store signed release receipt, DATA-05 manifest, denied-side-effect security oracle | FUTURE / NOT EXECUTED |

## Group 7 — PHYSICAL-COMPAT-QUALITY

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T097 | Real Android arm64 Vulkan phone original 2D smoke build/open/close | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T098 | Real Android arm64 Vulkan phone original 3D smoke build/open/close | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T099 | Real Android low-memory 16KiB-page phone smoke or explicit unsupported | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T100 | Real Android approved OpenGL ES fallback phone golden tier smoke | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T101 | Real Android tablet/foldable orientation/hinge touch-layout smoke | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T102 | Real Android controller+IME+TalkBack physical accessibility smoke | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T103 | Real iPhone owner-selected OS native Metal 2D smoke build/open/close | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T104 | Real iPhone owner-selected OS native Metal 3D smoke build/open/close | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T105 | Real iPadOS Metal device with split view/multiscene smoke | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T106 | Real iPhone controller+IME+VoiceOver accessibility smoke | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T107 | Android/iOS thermal throttling behavior during game resume tested | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T108 | Android low battery and iOS Low Power Mode paired device test | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T109 | Unsupported physical GPU tier reports UNSUPPORTED without false PASS | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T110 | Physical touchscreen DPR safe area resolution touch coordinates verified | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T111 | Simulator/emulator results segregated from physical hardware coverage | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |
| P04-T112 | Cross-platform game semantic actions/scene identity match declared tier | real OS/device hardware fingerprint redacted, rights-cleared 2D/3D build/open/close and accessibility fixture | FUTURE / NOT EXECUTED |

## Group 8 — SUSTAINED-BENCH-RELEASE

| Future ID | Objective future scenario / acceptance | Independent oracle | Status |
|---|---|---|---|
| P04-T113 | Android cold vs warm startup with fixed APK/AAB source hash measured | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T114 | iOS cold vs warm startup with fixed signed build hash measured | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T115 | Android 2D/3D actual frame p50/p95/p99 raw samples collected | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T116 | iOS 2D/3D actual frame p50/p95/p99 raw samples collected | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T117 | Input-to-present latency clock domain calibrated or explicitly unknown | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T118 | Mobile GPU frame counters sampled only where hardware supported | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T119 | Sustained 30-60min frame trend and thermal slopes documented | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T120 | Battery capacity/power estimate and temperature confidence labeled | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T121 | Memory peak/reclaimed bytes/last-good checkpoint tested during kill | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T122 | Background suspension/network constraints and resume trace recorded | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T123 | Multiple OS/driver/GPU family quality tiers compared with oracle | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T124 | Asset bundle network/install/decoded bytes and offline cache measured | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T125 | Store signing and policy compliance only claimed with actual receipts | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T126 | All license notices/SBOM/source provenance and privacy data disclosures reviewed | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T127 | Owner-approved budget/min OS/hardware/release scope established before code | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |
| P04-T128 | Security HIGH/CRITICAL closure and global 1.0 DoD checked before release | actual cold/warm/sustained physical device sample, SPDX/Store compliance evidence, owner DoD and audit | FUTURE / NOT EXECUTED |


## Gate remains BLOCKED
Catalog accepts "Plataformas móveis selecionadas com smoke/compatibilidade documentadas" **after platforms selected and actual compatible mobile app smoke/benchmarks**. There are no selected owner-approved Android/iOS 1.0 release classes, code implementations, signed bundles, paid publishing or test PASS yet. ADR-0073 PROPOSED, NLE-D009 source license OPEN, all 80/80 code WOs BLOCKED, executor_ready=0, approved_adr=0.

[Benchmark protocol](../research/plat-04-mobile-benchmark-protocol.md) · [architecture](../architecture/plat-04-mobile-target-adaptation.md) · [semantic API](../contracts/plat-04-mobile-target-api.md).
