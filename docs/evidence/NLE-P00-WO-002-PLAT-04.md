# Evidence Bundle — NLE-P00-WO-002-PLAT-04 Mobile Android/iOS Documentary Research

**2026-11-15 | [Research #333](https://github.com/KayzenRoot/stormline/issues/333) OPEN pending independently verified checkpoint | [Future coding #88](https://github.com/KayzenRoot/stormline/issues/88) OPEN/BLOCKED | P00 DOCUMENTARY RESEARCH ONLY.** No mobile executable, physical GPU/thermal/battery, signing credentials, payment, SDK install, store publishing or benchmark result.

## 1. Actual pre-write SOURCE CHECK
- Requested main HEAD exactly **b12e0755fd9539406a2f92c8e51f1a6d6e19c73a**, no open PRs. Hierarchy checkpoint > Decisions/ADRs > Scope > DoD > Architecture > Requirements > other.
- Registry has **80 modules, 69 research documented, 11 pending**, PLAT-04 ordinal **70/80 RESEARCH_PENDING**, formal dependencies **GFX-01 + GAME-01 ONLY**, both predecessor ADR-0014/0042 PROPOSED and no executed engine.
- All **80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false. Code #88 remains OPEN/BLOCKED; NLE-D009 engine license OPEN, NLE-D013 no public MVP, NLE-D017 requires desktop native while mobile is cost-conditional.
- [Work Order Context Lock](../work-orders/NLE-P00-WO-002-PLAT-04.md) records actual Git **blob SHA-1 OIDs, NOT raw byte SHA-256** for critical inputs. Any source drift => STALE before future writes; exact SHA-256 required for code preflight.

## 2. Official primary external research and observed changes
- [Google Play API target](https://developer.android.com/google/play/requirements/target-sdk) **since 31 Aug 2026** new phone apps/updates target Android16/API36+; separate minimum Android install version and actual chosen release platform.
- [Android Vulkan](https://developer.android.com/games/develop/vulkan/overview), [native Vulkan requirements](https://developer.android.com/games/develop/vulkan/native-engine-support): Android 64bit new devices from Android10 Vulkan1.1, but graphics feature/driver/min profile must be measured, no universal Vulkan tier.
- [Android GameActivity](https://developer.android.com/games/agdk/game-activity/get-started) modern C++ game host vs candidate SDL3; **one CORE-01 event authority**, no duplicate GameActivity+SDL loops. Android [16KiB native page sizes](https://developer.android.com/guide/practices/page-sizes): NDK r28+ defaults 16KiB alignment, every prebuilt .so and packaged APK must pass, Google Play target API35+ native 16KiB requirement with future update deadline. No actual NDK build.
- [Android ADPF/thermal](https://developer.android.com/games/optimize/adpf/thermal): thermal headroom can be NaN and should be queried no more than every 10sec; sustained quality policy rather than clock forcing. [Play Asset Delivery](https://developer.android.com/guide/playcore/asset-delivery) distribution-specific asset packs, DATA owner, not executable libraries.
- [Apple upcoming 2026 SDK requirements](https://developer.apple.com/news/upcoming-requirements/): Xcode26+/iOS26 SDK submissions since Apr 28 2026 and target iOS13+ since Sep 9 2026. iOS minimum OS and required device class still owner-decision. [SDL3 iOS](https://wiki.libsdl.org/SDL3/README-ios), [UIKit lifecycle](https://developer.apple.com/documentation/uikit/managing-your-app-s-life-cycle), [native Metal](https://developer.apple.com/documentation/metal/) and [App Store privacy/third-party SDK requirements](https://developer.apple.com/support/third-party-SDK-requirements/) used as references; no actual build, Apple developer account or signature.
- SDK/software versions, transitive licenses, SBOM, store signing accounts/fees, real Android/iOS hardware, min supported OS, Android GL fallback, target formats, exact FPS and all runtime security remain **PENDING** rather than inferred.

## 3. Exactly eight NEW research Markdown
1. [Architecture](../architecture/plat-04-mobile-target-adaptation.md).
2. [ADR-0073 PROPOSED](../adr/0073-plat-04-mobile-target-android-ios-policy.md).
3. [Technology/license/security](../research/plat-04-mobile-technology-license-security-matrix.md).
4. [Mobile semantic API](../contracts/plat-04-mobile-target-api.md).
5. [128 future P04 tests](../testing/plat-04-acceptance-matrix.md).
6. [Physical mobile benchmark protocol](../research/plat-04-mobile-benchmark-protocol.md).
7. [Research Work Order](../work-orders/NLE-P00-WO-002-PLAT-04.md).
8. This Evidence Bundle.

## 4. Truthful evidence matrix
| Claim | Documentary research | **NOT** demonstrated |
|---|---|---|
| 8 docs and approved Source Check | GitHub docs PR file list, canonical hierarchy | no compiled Android/iOS engine |
| Android Play/ELF/Vulkan/GameActivity rules | official Google Android 2026 docs | no AAB/APK, Java/JNI loop, Vulkan hardware or Play acceptance |
| iOS UIKit/Metal/SDK/privacy rules | official Apple/SDL3 guides | no iPhone/iPad IPA/Metal screenshot, App Store Connect enrollment |
| GFX-01/GAME-01 ownership | predecessor contracts ADR-0014/0042 PROPOSED | no device loss, gesture/action runtime |
| 128 future test requirements | P04-T001..P04-T128 eight x16, all NOT EXECUTED | no real phone test pass or thermal/battery data |
| Security/rights | threat model, scoped permission and licensing checklist | no penetration test, license clearance, signing credentials |
| Benchmark | physical sustained device measurement protocol | no p50/p95/p99, joules, temperature, OOM/recovery proof |
| CI | **PENDING actual PR run/job** | Docs CI does not validate real GPU, OS, app, privacy or store compliance |

## 5. Research PR/CI/Audit/Merge PENDING observations
Research branch `docs/NLE-P00-WO-002-PLAT-04-mobile-research`, BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`. Actual research head/PR, changed-file statuses, Docs Validation run/job success, objective pt-BR audit and squash/main readback must be verified and recorded in checkpoint/history AFTER occurrence, never pre-claimed.
P00 risk LOW documentary, future GPU/runtime/memory ELEVATED and signing keys/security/privileged permission/payment HIGH_ASSURANCE. No secrets, user files or signed published app. Rollback only via audited non-force revert.

## 6. Checkpoint Delta proposed only, never self-promoted
After research PR actual CI SUCCESS, pt-BR audit APPROVED, squash/main readback: create **five-file independent checkpoint PR** checkpoint/backlog/registry/this WO/this Evidence with **sole semantic registry PLAT-04 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 modules and flags unchanged. Expected **70/80 researches documented (87.5%), 10 pending, 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release class UNDECIDED all, engine_implemented=false**; ADR-0073 still PROPOSED; 128 P04 tests FUTURE, no devices/store.
Own Docs Validation/pt-BR audit/squash/main readback mandatory, then close research #333, future code #88 OPEN/BLOCKED. Separate **four Markdown historical closeout** own CI/audit/squash/readback. Next REAL catalog **PLAT-05 Build, Export & Distribution**, 71/80, formal deps **PLAT-01+PLAT-02+PLAT-03+PLAT-06+DATA-05**, future code issue #89.
