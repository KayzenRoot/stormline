# NLE-P00-WO-002-PLAT-06 — macOS Desktop Target Documentary Research Work Order

**2026-11-15 | P00 RESEARCH ONLY | research [#329](https://github.com/KayzenRoot/stormline/issues/329) OPEN pending checkpoint, future code [#87](https://github.com/KayzenRoot/stormline/issues/87) OPEN/BLOCKED | BASE 109287f928b4436b31188c1dd8cf4f7a454ad989.** Documentation risk LOW; future native graphics/OS ELEVATED and private signing/distribution HIGH_ASSURANCE.

## OBJECTIVE
Produce eight NEW Markdown P00 technical documents: real 2026 Apple Silicon/macOS 27 strategy and Intel x86_64 conditional Mac OS<=26, SDL3/Cocoa AppKit event/Retina lifecycle, GFX-01 Metal presentation/device tier/resource recovery, GAME-01 semantic keyboard/controller/IME/TCC, ABI/Universal2, Developer ID notarization versus App Sandbox and secure files, license/security matrix, versioned semantic API, exactly 128 future tests and physical hardware benchmark. Catalog acceptance is actual Editor plus exported 2D/2.5D/3D game build/open/close with native graphics checks and recoverable errors, **NOT demonstrated by research alone**.

## CONTEXT & SOURCE CHECK
Canonical order checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements > rest; AGENTS applies. Main exact requested SHA 109287f928b4436b31188c1dd8cf4f7a454ad989, zero open PRs, registry **68/80 researches documented, 12 pending, PLAT-06 order 69 and RESEARCH_PENDING, 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. NLE-D009 code license OPEN, owner NLE-D013 no public MVP, D014 2D/2.5D/3D, D017 macOS Editor and game native, D018 routine docs autonomy not spending/security bypass, D019/D020 blocked future implementation. Formal deps **CORE-01 + GFX-01 + GAME-01 exactly**; predecessor ADR-0003/0014/0042 PROPOSED, not code.

## CONTEXT LOCK
The following are actual **Git blob SHA-1 OIDs**, not SHA-256 hashes of raw contents. Freeze exact source HEAD 109287f928b4436b31188c1dd8cf4f7a454ad989; if checkpoint, approved ADR/Ledger, Scope, DoD, Architecture, requirements, registry or predecessor changes, mark STALE and reconcile. Exact raw-file SHA-256 fingerprints must be calculated during future code preflight, not fabricated here.

- AGENTS.md — 3e57b719f8651407879ebb641707a048773ea4c2
- docs/00-source-hierarchy.md — 58a377bc76cafdd3377d733d4f30ef53661bb034
- docs/11-checkpoint.md — 689760e93a09d7e6b04379fa43e96741ba623121
- docs/10-decisions-ledger.md — d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e
- docs/03-scope.md — 4ef605c74632ece080b2650e37dd83a415b63310
- docs/09-definition-of-done.md — 160b3054db9ea1961308934b401488b838d24c3e
- docs/04-architecture.md — df62574cb3956c3ac9881631a4cf66be4e1abff1
- docs/02-requirements.md — 14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b
- docs/product/module-catalog.md — 18d69bca439831d65982cb0f8acbca1dbaa2eee9
- docs/queue/implementation-registry.json — fd20f6b59c4deb4e11baf51411a4ce31acb1811f
- docs/queue/work-orders/PLAT-06.md — a357d4198278862e1e4672153a91ad143c1c0c3d
- docs/adr/0003-core-01-platform-technology.md — 2ee92dda5ab81ddcc446b9d5325d29257350e217
- docs/architecture/core-01-platform-lifecycle.md — 11c7ec4125f40cf0172aa552a1e9835e84d2c172
- docs/adr/0014-gfx-01-rhi-backends.md — 27b3f4533083c6b6a23a989e0eb8661898d44ade
- docs/architecture/gfx-01-graphics-rhi.md — 4512de487da7df97969b56f8e5f508a56125ab32
- docs/contracts/gfx-01-rhi-api.md — 822cbd118df75b4acf033443d5f75842d1344ae7
- docs/adr/0042-game-01-engine-owned-input-actions.md — 377bfee8b464bc7c9dfcaca1f6ff8452a9616441
- docs/architecture/game-01-input-control-mapping.md — 5f86d817a26a7142496788963453caf247dbfa50
- docs/contracts/game-01-input-actions-api.md — cc2598fe117ae4a60d7746028df084d7be229426

## SCOPE — exactly eight NEW Markdown docs, NECESSARY
1. [Native architecture](../architecture/plat-06-macos-desktop-target.md).
2. [ADR-0072 PROPOSED](../adr/0072-plat-06-macos-apple-silicon-compatibility-policy.md).
3. [Technology/license/security matrix](../research/plat-06-macos-technology-license-security-matrix.md).
4. [Target semantic API](../contracts/plat-06-macos-target-api.md).
5. [Exactly 128 P06 future tests](../testing/plat-06-acceptance-matrix.md).
6. [Actual-Mac future benchmark](../research/plat-06-macos-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-06.md).

## OUT OF SCOPE
Mac code, .mm/C++/Swift/Info.plist/source/assets, compiled Mac binaries, Xcode/Apple SDK download, Apple Developer paid enrollment, signing keys, notarization/staple, public release/hosting, fake Metal/Retina benchmark, unapproved Intel 1.0 class, changes to CORE/GFX/GAME/other 79 queue WOs, registry/checkpoint/backlog/CI in first research PR, automatic mobile work, broad cleanup, external mandatory reviewer/paid services/force push.

## FILES/SOURCES TO READ
Git source locked list; AGENTS, source hierarchy, checkpoint/Ledger/Scope/DoD/Architecture/Requirements, catalog and future code #87; CORE-01 ADR-0003/lifecycle, GFX-01 ADR-0014/RHI API, GAME-01 ADR-0042/actions API. Official [Apple WWDC26 Intel last OS](https://developer.apple.com/videos/play/wwdc2026/102/), [2026 Rosetta news](https://developer.apple.com/news/?id=w5ngl9k2), [Xcode27 SDK/ARCHS](https://developer.apple.com/documentation/Xcode-Release-Notes/xcode-27-release-notes), [universal binaries](https://developer.apple.com/documentation/apple-silicon/building-a-universal-macos-binary), [SDL3 macOS](https://wiki.libsdl.org/SDL3/README-macos), [SDL Metal view](https://wiki.libsdl.org/SDL3/SDL_Metal_CreateView), [CAMetalLayer](https://developer.apple.com/documentation/QuartzCore/CAMetalLayer), [notarization](https://developer.apple.com/documentation/security/notarizing-macos-software-before-distribution/), [Hardened Runtime](https://developer.apple.com/documentation/security/hardened-runtime), [App Sandbox](https://developer.apple.com/documentation/security/app-sandbox).

## REQUIREMENTS
GOV-001..005 plus product NLE-D013..020, planned 2D/2.5D/3D and Editor native macOS. No owner-finalized min macOS release class or Intel requirement. CORE-01+GFX-01+GAME-01 are **formal** and only prerequisites; future output: actual supported Apple Silicon Editor and export game smoke, security, packaging, accessibility, memory and performance proof.

## ARCHITECTURE RULES
- CORE-01 SDL3 native process/event pump single authority, narrow Objective-C++ AppKit bridge, main-thread NSApplication/SDL_Metal_CreateView, window epochs/unsaved close veto, no mandatory UI for headless.
- GFX-01 owns actual Metal GPU/queues/resource generations and capability tier; PLAT bridge offers NSView/CAMetalLayer/backing metrics and display/sleep/resize failures; GFX-02 shaders, GFX-07 color transitive. No Metal4/Intel parity assumption or dual RHI.
- GAME-01 owns semantic action maps; CORE one event origin; macOS modifier/IME/trackpad/GCController/TCC accessibility normalized, no private keystroke monitoring.
- Native Apple Silicon arm64 mandatory candidate; owner Intel support conditional, physical Intel OS<=26, separate Rosetta translation. Xcode27 Apple-Silicon-only host, explicit ARCHS when needed, nested Mach-O slice/runtime ABI and minimum OS availability.
- PLAT-05/BIZ-03 own release signing, bundle, Developer ID notary or App Store Sandbox; do not claim publicly signed/notarized using free CI; owner consent for account/payment/certificate and no JIT/plugin/permissions bypass.
- Future actual physical Mac hardware and original licensed scenes for benchmarks, no unmeasured FPS/VRAM/compatibility claims; license NLE-D009 OPEN.

## CONSTRAINTS
P00 docs LOW risk; no paid developer program, third-party unpinned license adoption, secrets, unapproved deployment or destructive history, no CodeRabbit/external reviewer. Use free Docs Validation + independent pt-BR audit/squash/readback. Engine code and future issue #87 stay BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown files only in research PR, with correct links, citations and no registry/checkpoint/backlog/CI or code.
- [ ] ADR-0072 PROPOSED; formal deps CORE-01+GFX-01+GAME-01 only; Apple WWDC26, Xcode27, Rosetta2026 facts not conflated; Intel owner unresolved.
- [ ] Cocoa/SDL main loop/Metal layer vs GPU ownership, retina/monitor/sleep, GAME semantic inputs/TCC/IME, package Mach-O/Developer ID/App Sandbox/privacy/license documented.
- [ ] Exactly 128 unique P06-T001..P06-T128, eight 16-case groups, all FUTURE/NOT EXECUTED with real Mac benchmark protocol and no synthetic PASS.
- [ ] Research PR Docs Validation SUCCESS exact HEAD, objective pt-BR audit APPROVED, squash merge and readback.
- [ ] Separate checkpoint PR exactly five MODIFIED files (docs/11-checkpoint.md, docs/08-backlog.md, registry JSON, this WO, Evidence), sole registry PLAT-06 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, **69/80 researches, 11 pending, all 80 coding WOs BLOCKED, zero ready/approved ADR, release classes all undecided, engine false**; its own CI/audit/squash/readback. Research issue #329 closed **only after** independent checkpoint proof, future code #87 OPEN/BLOCKED.
- [ ] Four-Markdown historical closeout separate CI/audit/squash/readback; next actual catalog module **PLAT-04 Mobile Target Adaptation** (70/80, formal deps GFX-01+GAME-01), not arbitrary module sequence.

## TESTS
In P00: Docs Validation source pack/relative links, 80-module catalog/DAG/registry and blocked selector, PR file list exactly eight, test ID uniqueness and FUTURE, GitHub CI/job audit. Future: actual Apple Silicon arm64 hardware/Metal and optional real Intel Mac<=26 if ratified, universal2/linking, SDK, UI/IME/controller/permissions, security/notarization/accessibility and raw p50/p95/p99 benchmark. **None executed now.**

## DELIVERABLES
Eight new Markdown, research issue #329, research PR/CI/audit evidence, normal squash/main readback, independent checkpoint proposal, future five-file checkpoint and four-file closeout only after gates, full historical readback.

## REVIEW FORMAT
pt-BR, actual base/head SHA, files/8+128, source fingerprints, formal DAG, security/rights/Intel OS/Xcode27/Rosetta truth, docs CI job, defects severity, rollback, independent checkpoint Delta and verdict APPROVED / CORRECTION REQUIRED / BLOCKED. Approval for research != owner acceptance of Intel target/version/license/implementation.

## STOP CONDITION
STALE baseline, missing source/CI, altered code/registry in research PR, wrong formal dep, out-of-scope SDK/Apple certificate/payment/signing/permission bypass, HIGH/CRITICAL, test matrix invalid => BLOCKED or CORRECTION REQUIRED on same WO/PR. Never proceed to next module while unresolved.

## CHECKPOINT DELTA PROPOSAL ONLY
After research CI/audit/squash/main readback: independent 5-file checkpoint with sole PLAT-06 research_status update; ensure all other 79 module objects and other flags unchanged; own CI/audit/squash/readback; close #329 only then. Final factual history in 4 Markdown only, own CI/audit/squash/readback and next PLAT-04. No code authorization, no approved ADR change.


## Research #330 factual audit and independent checkpoint proposal
- [Research PR #330](https://github.com/KayzenRoot/stormline/pull/330): BASE `109287f928b4436b31188c1dd8cf4f7a454ad989`, HEAD `a57fa92fd528973a5fd85dca822b8a5737bcda22`, **exactly eight NEW Markdown**, [Docs Validation #43791256693](https://github.com/KayzenRoot/stormline/actions/runs/43791256693) SUCCESS job #133049959252 (Source Pack/links, DAG, 80 registry and selector blocking all coding), [objective pt-BR audit #6905483672](https://github.com/KayzenRoot/stormline/pull/330#issuecomment-6905483672) APPROVED **documentary only**; normal squash/main readback `03bc74db0d61552737947d0702275aaa47f4ba2c` with ADR-0072 PROPOSED and original registry still 68/80.
- Independent checkpoint proposal for PLAT-06 research: **sole semantic registry change** `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; other 79 module records and flags unchanged. Target main registry **69/80 researched (86.25%), 11 pending, all 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class UNDECIDED all, engine_implemented=false**. Formal deps CORE-01+GFX-01+GAME-01 unchanged; ADR-0072 PROPOSED, NLE-D009 engine license OPEN; P06-T001..P06-T128 FUTURE/NOT EXECUTED. No Xcode/macOS app, Apple Silicon/Intel physical GPU, real benchmarks, licensed signed/notarized distribution or test PASS.
- [Research #329](https://github.com/KayzenRoot/stormline/issues/329) must stay OPEN until independent checkpoint CI/audit/squash/readback; it briefly appeared CLOSED immediately following research squash despite no checkpoint, so was explicitly **reopened** to preserve process integrity. Future code [#87](https://github.com/KayzenRoot/stormline/issues/87) remains OPEN/BLOCKED. After audited checkpoint readback close #329 and independently document history in FOUR Markdown only with own CI/audit/squash/main readback. Next REAL catalog **PLAT-04 Mobile Target Adaptation** (70/80), formal GFX-01+GAME-01.
- The checkpoint PR is independent and requires own CI/audit/squash/readback. Issue #329 is open pending proof, code #87 remains blocked.
