# PLAT-04 — Proposed Mobile Target, GPU Surface, Input, Thermal and Packaging Semantic Contract v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY | [research #333](https://github.com/KayzenRoot/stormline/issues/333) | WO NLE-P00-WO-002-PLAT-04 | code [#88](https://github.com/KayzenRoot/stormline/issues/88) OPEN/BLOCKED | BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`.** Catalog 70/80, formal deps **GFX-01 + GAME-01 ONLY** (ADR-0014/0042 PROPOSED), original registry 69/80 researched, 11 pending, 80 code WOs BLOCKED, zero ready, approved ADR, engine=false and release classes UNDECIDED.


**Design-only versioned logical contracts; not C++/JNI/Swift/ObjC ABI, executable Android/iOS module, app bundle, signing profile, GPU resource or approved platform commitment.**

## Formal owners and integration-only boundaries
| Formal owner | Proposed prior contract | Mobile adapter responsibilities |
|---|---|---|
| **GFX-01 FORMAL** | [RHI](gfx-01-rhi-api.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md) | Android ANativeWindow Vulkan/EGL offer, iOS UIView/CAMetalLayer Metal offer, display/rotation/scale and physical capability/power hint; device queues/resources/loss GFX-owned |
| **GAME-01 FORMAL** | [ActionMap API](game-01-input-actions-api.md), [ADR-0042](../adr/0042-game-01-engine-owned-input-actions.md) | normalized multitouch/stylus/controller/keyboard/IME/gesture event epochs and permissions to GAME action resolver; do not add second action mapper |

CORE-01 SDL3/Android Activity/UIApplication event authority, CORE-04 tick, GFX-02/03 shader/memory, DATA-05 cooked bundles, AUDIO/UI/EDIT, PLAT-05/BIZ-03 signing/store and privacy/security owners remain transitive, never new formal dependencies. Unsupported target cannot be silently reported working.

## V1 proposed logical entities
| Type | Required fields | Invariants and failure |
|---|---|---|
| MobileTargetProfileV1 | target Android/iOS/iPadOS, arm64 ABI, targetSDK/minOS/SDK, store channel/internal, approved release_class, gpu tier, memory/thermal target | release_class UNDECIDED means preview only; targetSDK != minOS |
| MobileHostEnvironmentV1 | physical device model redacted, OS build, runtime ABI, Android page-size, SDK/driver/Metal/Vulkan family, CPU/GPU/memory, simulator flag | native hardware only if physically observed; no model-name inferred feature |
| MobilePlatformLifecycleV1 | ProcessEpoch, Scene/ActivityEpoch, RESUMED/PAUSED/BACKGROUND/SUSPENDED/DESTROYED, surface epoch, cause and tick policy | activity lifetime != surface; stop background render and cancel touches |
| AndroidHostBridgeV1 | Activity backend SDL3/GameActivity approved single owner, JNI/Looper lease, SurfaceView/ANativeWindow opaque token, window/rotation/insets/keyboard state | no independent double event pump or JNI refs after invalidation |
| IosHostBridgeV1 | UIApplication/UIScene/SDL3 owner, UIView/CAMetalLayer token, scene visibility/focus, safe area, keyboard/thermal interrupt | no off-main UIKit updates, no background engine entitlement assumption |
| MobileGpuSurfaceOfferV1 | backend VULKAN/METAL/OPENGLES, device/surface generations, width/height physical pixels, swap/pixel formats, features/limits/quality policy | GFX-01 owns VkDevice/MTLDevice and resources, PLAT handles surface lease only |
| MobileCapabilityProbeV1 | Vulkan API/extensions/profile/texture formats, Metal GPU families/formats, GL ES version if fallback, displays/refresh/touch capabilities, evidence | actual query with UNKNOWN state; Vulkan support != feature parity |
| MobileTouchContactV1 | pointer id + Device/Scene/WindowEpoch, phase DOWN/MOVE/UP/CANCEL, surface logical and pixel coords, pressure/tilt if available, precise ordering | no resurrected contact after CANCEL/rotation/scene loss |
| MobileGestureOfferV1 | touch gesture candidate, conflict group, longpress/doubletap/pinch/drag/scroll, focus, semantic GAME ActionId offered | only GAME-01 resolves gameplay controls and accessibility remap |
| MobileInputPermissionV1 | controller/haptics/IME, sensor/motion/location/microphone/camera if separately approved, request/deny/allow/revocation | no default privileged collection, denies preserve game baseline |
| MobileThermalSignalV1 | Android ADPF status/headroom or iOS thermalState, source timestamp/age, confidence, NaN/UNKNOWN, powerSave | no headroom polling >1 per 10s, stale or missing conservative |
| MobileQualityPolicyV1 | CPU/GPU budgets, tick cap, target FPS range, adaptive resolution bounds (3D only), LOD/shadows/MSAA/postprocess/texture/worker throttle, hysteresis | no automatic UI/pixel art blur, no thermal bypass, bounded transitions |
| MobileMemoryPressureV1 | app RSS/allocator budget and OS trim/memory warning, GPU budget estimate, event generation, trim level, last-good-save receipt | jetsam/kill may not invoke callback; assets recover on restart |
| MobileDisplayMetricsV1 | dp/pt vs physical pixel canvas, orientation, safe areas/notch/hinge, IME insets, refresh range, touch target accessibility | foldable and iPad multiwindow resize refresh dimensions and projection |
| MobileBundleDeliveryV1 | DATA-05 immutable asset manifest/hash/codec/limit, Play asset pack install/fast-follow/on-demand or local iOS bundle, last-good/cache | asset packs contain no executable code; revalidate evicted pack or offline |
| MobileDistributionPolicyV1 | INTERNAL_ONLY/PLAY_STORE/APP_STORE, targetSDK/iOS SDK, native ELF page alignment, signed AAB/IPA, privacy manifest/ATT, version/approval | PLAT-05/BIZ-03 owns publishing, not ready without owner and credentials |
| MobilePlatformErrorV1 | UNSUPPORTED_DEVICE/NO_GRAPHICS_API/OUT_OF_BUDGET/ACTIVITY_LOST/SCENE_SUSPENDED/PERMISSION_DENIED/THERMAL_UNKNOWN/STORE_POLICY_BLOCKED/SIGNING_REQUIRED/RESTART_REQUIRED | typed redacted recoverability; no fake silent PASS |
| MobileDeviceSmokeReceiptV1 | real hardware OS ABI GPU, min/target API, physical and fallback tier, original 2D+3D build/open/close, interactions, warnings | emulator not physical GPU/energy proof |
| MobileSustainedBenchmarkReceiptV1 | source/build/toolchain SHA, original fixture, raw 30-60min frame/input/power/thermal/memory samples and uncertainty, device temperature/ambient, battery | no FPS/energy claims without raw samples and permission |

## Candidate non-executable operations
| Operation | Owner | Outcome |
|---|---|---|
| probe_mobile_target(profile) | PLAT host | MobileHostEnvironment/UNSUPPORTED or unknown |
| select_mobile_host_backend(SDL_or_GameActivity) | CORE-01 | exactly one event authority, no double JNI loop |
| offer_mobile_surface(scene_token) | PLAT -> GFX-01 | capability-gated Vulkan/Metal/GL ES offer/DEVICE_LOST |
| query_mobile_gpu_capabilities(gfx_token) | GFX-01 | actual features/limits/device-generation receipt |
| report_platform_lifecycle(event) | CORE-01 | mobile process/scene/surface epochs and GAME cancel |
| normalize_mobile_touch(event) | CORE-01 -> GAME-01 | pointer/phase epochs and semantic mapping eligibility |
| report_mobile_thermal_or_memory(event) | PLAT -> policy | bounded signal, conservative default if unavailable |
| apply_approved_quality_budget(receipt) | GFX-01/CORE-04/PLAT | staged dynamic resolution/shader/LOD bounds without sim desync |
| request_mobile_permission(intent) | OS bridge | DENIED or scoped authorized device token |
| inspect_mobile_bundle(manifest) | DATA-05 + PLAT-05 | trusted chunk/decompression/memory pack status |
| evaluate_mobile_distribution(policy) | PLAT-05/BIZ-03 | signed/reviewed candidate or BLOCKED |
| produce_real_mobile_smoke_receipt() | QA + CORE-06 | evidence from actual Android/iOS device, not emulator |

## Invariant and rejection rules
- No duplicated SDL/GameActivity or UIScene event loop: CORE-01 single OS event authority (transitive), GAME-01 sole ActionId resolver. All pointer IDs scoped by SceneEpoch/DeviceEpoch; rotation/CANCEL/permission popup stops held gestures.
- GPU surface lease is **not** an owning VkDevice/MTLDevice. GFX-01 owns resource state/generation; different screen orientations, lifecycle, memory pressure and lost/destroyed surface cannot silently reuse stale present handles. GPU fallback requires capability and selected quality equivalence/explicit reduction.
- Android API36 target submission and iOS SDK26 App Store are **2026 store requirements**, independent of min install OS/platform selection; NDK 16KiB pages and all signed libs must be tested on actual devices before store release.
- Energy/thermal signals may be unavailable/stale/NaN; signal source, time and policy hysteresis must be explicit, never boost chip frequency or bypass user/OS thermal limits. Dynamic resolution must preserve accessibility text/UI.
- Store signing/upload credentials/Apple Developer agreements, privacy manifests/Play Data Safety/ATT and high assurance security are governed by PLAT-05/BIZ-03, not automatically adopted in P00. No mobile API for executing arbitrary AI-native scripts, native plugins or extracting paths outside user scope.
- Schemas versioned; incompatible major rejects cleanly; all statuses truthfully NOT_EXECUTED until actual device smoke and benchmark. Source license NLE-D009 OPEN, mobile release class UNDECIDED.

[Architecture](../architecture/plat-04-mobile-target-adaptation.md) · [ADR](../adr/0073-plat-04-mobile-target-android-ios-policy.md) · [128 tests](../testing/plat-04-acceptance-matrix.md).
