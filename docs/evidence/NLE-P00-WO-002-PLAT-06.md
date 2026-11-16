# Evidence Bundle — NLE-P00-WO-002-PLAT-06 macOS Target Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY | [research #329](https://github.com/KayzenRoot/stormline/issues/329) open pending checkpoint | [future implementation #87](https://github.com/KayzenRoot/stormline/issues/87) OPEN/BLOCKED. No Mac binary/hardware/GPU/performance/signing or notarization.**

## 1. Observed Source Check before writing
- Main exact requested **109287f928b4436b31188c1dd8cf4f7a454ad989**, no open PRs, last PLAT-03 historical closeout already merged/readback.
- Canonical source order: checkpoint > decisions/approved ADRs > scope > DoD > architecture > requirements. Inventory PLAT-06 69/80, formal deps **CORE-01 + GFX-01 + GAME-01 only**, predecessor ADR-0003/0014/0042 PROPOSED and none implemented.
- Registry 80 entries, **68 research documented, 12 pending, all 80/80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. NLE-D009 engine source license OPEN, owner D013 no public MVP and D017 Mac Editor+export mandatory.
- [Work Order](../work-orders/NLE-P00-WO-002-PLAT-06.md) records Git blob OIDs in Context Lock (SHA-1 object identifiers, **not raw content SHA-256**). Future executor must recalculate SHA-256 on exact files before code.

## 2. High confidence 2026 upstream sources / no adopted tech
- [Apple WWDC26](https://developer.apple.com/videos/play/wwdc2026/102/) macOS Tahoe 26 final major Intel Mac OS; macOS27 Apple Silicon transition.
- [Apple Rosetta notice Sep 1 2026](https://developer.apple.com/news/?id=w5ngl9k2) macOS27 final general translation release, later limited legacy-game exception **not** permission for new Intel-only Stormline.
- [Xcode27 notes](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes): Apple-Silicon-only Xcode host, SDK backdeploy universal, ARCHS_STANDARD x86_64 no longer automatic when min deployment>=27. [Apple universal guide](https://developer.apple.com/documentation/apple-silicon/building-a-universal-macos-binary) nested slices required.
- [SDL3 macOS](https://wiki.libsdl.org/SDL3/README-macos) app delegate conflict and [SDL Metal view](https://wiki.libsdl.org/SDL3/SDL_Metal_CreateView) main thread/no auto MTLDevice. [Metal CAMetalLayer](https://developer.apple.com/documentation/QuartzCore/CAMetalLayer), [recommended GPU budget](https://developer.apple.com/documentation/metal/mtldevice/recommendedmaxworkingsetsize), [NSWindow backing](https://developer.apple.com/documentation/appkit/nswindow/backingscalefactor), [Game Controller](https://developer.apple.com/documentation/gamecontroller/) support design.
- [Apple Developer ID notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/), [Hardened Runtime](https://developer.apple.com/documentation/security/hardened-runtime), [App Sandbox](https://developer.apple.com/documentation/security/app-sandbox) require exact signed channel and entitlements, **not** implicit free distribution or public code execution.
- Third-party versions, Xcode install, SDK license, Apple Developer account/cert costs, supported Intel release class, exact Mac hardware min, GPU benchmark, signed release are ALL UNVERIFIED/NOT APPROVED.

## 3. Research PR EXACT eight NEW Markdown documents
1. [Architecture](../architecture/plat-06-macos-desktop-target.md).
2. [ADR-0072 PROPOSED](../adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md).
3. [Technology/license/security matrix](../research/plat-06-macos-technology-license-security-matrix.md).
4. [Semantic Mac target API](../contracts/plat-06-macos-target-api.md).
5. [Exactly 128 P06 future acceptance tests](../testing/plat-06-acceptance-matrix.md).
6. [Actual Mac future benchmark protocol](../research/plat-06-macos-benchmark-protocol.md).
7. [Research Work Order](../work-orders/NLE-P00-WO-002-PLAT-06.md).
8. This Evidence Bundle.

No executable Mac code, launch/build, CMake/CI files, registry, backlog, checkpoint, older ADR, source asset, tool SDK, signing/deployment or issue #87 change in research PR.

## 4. Evidence and NOT proven table
| Documentary evidence | Source truth | NOT proven |
|---|---|---|
| ARM primary + Intel conditional support | 2026 Apple WWDC/Xcode/Rosetta official source | native Intel physical Mac or Apple Silicon executable |
| Coco/SDL one event authority | CORE-01 proposed ADR and SDL3 macOS notes | native app delegate/main-thread tested |
| Metal RHI and Retina | GFX-01 ADR + Apple layer/device references | real GPU feature, 2D/2.5D/3D quality, device loss |
| Input focus/TCC/IME and accessibility | GAME-01 ADR and Apple Game Controller | physical pad, VoiceOver, TCC tests |
| Security/signing/distribution | Hardened/Sandbox/Developer ID official notes | membership, key, notary ticket, approved store channel |
| 128 future tests | unique P06-T001..128 8 groups, FUTURE NOT EXECUTED | zero tests passed/hardware benchmark |
| GitHub CI | **PENDING** PR exact SHA and docs job readback | no app compiled or secured |

## 5. PR/CI/audit/squash facts PENDING until observed
Research branch docs/NLE-P00-WO-002-PLAT-06-macos-research, base 109287f928b4436b31188c1dd8cf4f7a454ad989. Research PR number/head, exact diff, actual Docs Validation run/job, objective pt-BR verdict and normal squash/main readback will be recorded as facts in separate checkpoint/history (not invented now).

Risks documentary LOW, future GPU and device-loss ELEVATED, certificate keys/notary/permission and privileged execution HIGH_ASSURANCE. No public deployment or user data/secret touched. Revert docs only by new audited PR, no force push.

## 6. Independent Checkpoint Delta PROPOSAL, NOT SELF-PROMOTED
After research PR exact-head Docs Validation success, objective audit APPROVED and normal squash/main readback: prepare separate **5 modified files** checkpoint, backlog, registry, research WO, this Evidence. Sole semantic registry PLAT-06 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. Expected **69/80 researched (86.25%), 11 pending, all 80 future code WOs BLOCKED, ready=0, approved_adr=0, all release_class UNDECIDED, engine=false**. ADR-0072 remains PROPOSED, P06 tests FUTURE. Checkpoint must pass its OWN CI/pt-BR audit/squash/main readback, then close research #329, code #87 stays OPEN/BLOCKED. Separate **four-Markdown factual historical closeout** with independent CI/audit/squash/main readback, then next REAL catalog PLAT-04 Mobile Target Adaptation 70/80 with formal GFX-01 + GAME-01.
