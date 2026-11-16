# ADR-0073 — Capability-Gated Android/iOS Mobile Targets, Thermal-Aware Quality and Permissioned Touch

**2026-11-15 | P00 DOCUMENTATION ONLY | [research #333](https://github.com/KayzenRoot/stormline/issues/333) | NLE-P00-WO-002-PLAT-04 | future implementation [#88](https://github.com/KayzenRoot/stormline/issues/88) OPEN/BLOCKED | BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`.** Catalog order 70/80, formal DAG **GFX-01 + GAME-01 ONLY**; both predecessor ADR-0014/0042 PROPOSED, 69/80 research documented before this module, 11 pending, 80/80 future code WOs BLOCKED, 0 executor_ready, 0 approved_adr, all release classes UNDECIDED, engine_implemented=false, NLE-D009 engine source license OPEN.


**STATUS: PROPOSED / NOT OWNER-RATIFIED / NO MOBILE CODE OR PUBLIC RELEASE AUTHORIZATION.**

## Decision problem and official 2026 facts
Native Android/iOS mobile ports require a specific OS/graphics/input, security, memory and thermal policy. The catalog explicitly says mobile scope is **subject to validation of cost**, with 1.0 release classes UNDECIDED. Google Play **new apps and updates target API36+ from Aug 31 2026** ([official policy](https://developer.android.com/google/play/requirements/target-sdk)); Apple App Store Connect has required **Xcode26+ and iOS26 SDK since Apr 28 2026** and **iOS13+ submission target since Sep 9 2026** ([official upcoming rules](https://developer.apple.com/news/upcoming-requirements/)). Neither rule selects Stormline min install OS nor grants permission/certificates to publish.

## Proposed decision (not yet adopted)
1. Keep **formal graph EXACT GFX-01 + GAME-01**; predecessor ADR-0014/0042 only PROPOSED. CORE-01 SDL3 platform event/lifecycle, CORE-04 tick, DATA-05 cooked bundles, AUD, UI, GFX-02/03/07, PLAT-05/BIZ-03 distribution and AI permission are **transitive owners**, not extra graph dependencies. PLAT-04 supplies mobile host/surface/feature/permission bridge, no duplicate RHI/action resolver.
2. **Android arm64-v8a primary candidate** with pinned SDK/NDK and optional narrow JNI/Activity. CORE-01 chooses one authoritative SDL3 or GameActivity host; Google recommends GameActivity for C++ games but cannot combine two independent Android event/input pollers. GFX-01 Vulkan runtime feature/tier preferred on actual Vulkan1.1+ Android device; conditional OpenGL ES 3.x reduced fallback only after renderer conformance, not universal Vulkan or compute assumption.
3. Android native binaries must handle 4KiB and 16KiB memory pages and correct ELF and APK alignment plus all prebuilt .so; Android NDK r28+ defaults 16KiB alignment ([Android docs](https://developer.android.com/guide/practices/page-sizes)). Google Play targeting Android15+ requires 16KiB compatibility for 64-bit native code, later Feb 2027 update enforcement noted; distinguish target SDK, min API, OS runtime and 16KiB device. No hardcoded 4096-page assumption.
4. **iOS/iPadOS ARM64 Metal native candidate** through GFX-01 CAMetalLayer, actual MTLDevice family/feature/drawable checks; single SDL3/UIKit UIApplication/UIScene authority, no autonomous second display link or event pump. App Sandbox signed provisioning, TestFlight/App Review etc only after approved PLAT-05/BIZ-03 channel; no downloaded unsigned native/JIT plug-ins, developer membership/cost unapproved.
5. GAME-01 owns all touch multi-finger/drag/pinch/long press/IME/controller/haptic semantic actions and focus. Only normalized OS events via CORE host; pointer/scene/device epochs, ACTION_CANCEL/touchcancel/gesture conflict and VoiceOver/Dynamic Type. Sensor/geo/microphone/camera/ads location tracking have separate opt-in and explicit consent, no default surveillance.
6. **Sustained adaptive quality** informed by actual ADPF thermal/Performance Hint/Game Mode on Android where supported and iOS thermal state/Low Power/scene life cycle. Headroom may be NaN; limit polling and bound every quality transition (preserve UI text/pixel-art, deterministic core tick). Power, battery, device temperature, and sustained p95/p99 rather than burst FPS are mandatory future metrics.
7. GFX-01 owns GPU device/resource epochs/format/queue/presentation, DRR/effective color, Vulkan surface lost or Metal drawable lost; PLAT-04 owns lifecycle and surface leases only. Real mobile memory/OS trim/jetsam can terminate without warning, project save last-good and DATA cooked bundles must recover with bounded RAM and permissions.
8. Packaging: Android AAB + Play App Signing and optional Play Asset Delivery; iOS signed IPA/TestFlight/App Store with per-SDK privacy manifests, Store privacy details and ATT when tracking actually used. PLAT-05/BIZ-03 own release, DATA-05 owns bundle/chunk identity, license and privacy policy owner review. No hidden paid cloud/Play/Apple account, paid SDK or marketplace bypass.
9. **No mobile mandatory-for-1.0 claim yet.** Owner must decide selected platforms, product form (exported games vs mobile Editor), minimum versions/device tiers, revenue/SDK/store policy, release class and acceptance budgets. If rejected/deferred mobile work stays FUTURE/OUT OF SCOPE with explicit entry rather than "implemented".
10. Exactly 128 unique FUTURE P04 tests and actual Android/iPhone/iPad physical validation required before code can be activated. All 80 implementation WOs stay BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS; executor_ready=0, approved_adr=0, release classes UNDECIDED, engine false, NLE-D009 source license OPEN.

## Alternatives and evaluation
| Alternative | Potential value | Not automatic due to |
|---|---|---|
| Android+ iOS both compulsory for 1.0 | market reach | catalog cost/owner review remains unresolved |
| Android Vulkan only, no fallback | lower RHI scope | excludes incompatible hardware; must choose supported device matrix explicitly |
| GL ES only for every Android | broader old devices | missing required advanced GFX; reduced-tier proof required |
| Force Vulkan on iOS via translation | reuse shader compilation | no Apple native Vulkan; Metal GFX-01 candidate is direct |
| Two simultaneous SDL and GameActivity loops | API convenience | duplicate touch/focus/input and incorrect lifecycle |
| iOS app can run heavy sim in background | simpler code | UIKit suspension/energy/OS restrictions |
| "60/120 FPS" fixed at max settings | easy marketing | thermal throttling and mobile energy budget |
| Disable throttling/thermal protections | burst benchmark | unsafe and violates OS/quality gates |
| Hardcode 4KiB allocator pages | old target speed | 16KiB Android device failure and distribution rule |
| Private Android filesystem or Apple arbitrary file paths | convenience | scoped storage, TCC/sandbox and privacy |
| Store signing and accounts implicitly free | fast shipping | credentials, account fees and owner authorization unresolved |
| Download JIT executable plugins to mobile | AI-native flexibility | iOS code signing/review/security and Android arbitrary code policy |
| Promise fullscreen/notch/rotation on all phones | UI consistency | cutouts, foldables, multitasking, permission and physical testing differences |
| GPU device benchmark from emulator/CI | cheap | no real physical thermal/battery/device-lost evidence |

## Deferred decisions and proof gate
Android minSDK/targetSDK/NDK/AGP versions, 4KiB/16KiB baseline, Vulkan1.1/GL ES fallback features, iOS target SDK/deployment min/Metal tier, Apple/Google account fees, OS permissions, data collection/ATT/privacy manifests, cooked asset codec profiles, exact license tags, device/thermal test fleet, numeric p50/p95/p99 sustained budgets, 1.0 release classes and explicit owner ratification. P00 research approval is **not** an ADR code approval.

[Architecture](../architecture/plat-04-mobile-target-adaptation.md) · [security/licenses](../research/plat-04-mobile-technology-license-security-matrix.md) · [API](../contracts/plat-04-mobile-target-api.md).
