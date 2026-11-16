# NLE-P00-WO-002-PLAT-04 — Mobile Target Adaptation Research Work Order

**2026-11-15 | P00 DOCUMENTATION ONLY | research [#333](https://github.com/KayzenRoot/stormline/issues/333) OPEN pending checkpoint | [future code #88](https://github.com/KayzenRoot/stormline/issues/88) OPEN/BLOCKED | BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`.** Current risk **LOW** for docs; future native GPU/memory/lifecycle ELEVATED, signing/privileged permissions/trading/payment/key custody HIGH_ASSURANCE if actually introduced.

## OBJECTIVE
Research Android/iOS/iPadOS C++20 mobile host targets and actual 2026 submission constraints, GFX-01 Vulkan/Metal + conditional GL ES capability tiers, GAME-01 touch/gamepad/IME permissions and accessibility, Android 16KiB pages and native ABI, iOS app/scene lifecycle, portable memory/asset bundles, thermal-aware sustainable frame pacing, battery, packaging and store privacy/signing. Produce an ADR PROPOSED, 8 Markdown, 128 future test objectives and real-device performance protocol without approving mobile platforms as 1.0 mandatory before owner cost/Scope/DoD decision.

## CONTEXT & SOURCE CHECK
Source precedence checkpoint > Ledger/ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/queue. Verified initial main HEAD **b12e0755fd9539406a2f92c8e51f1a6d6e19c73a** and **zero open PRs**. Registry 80 modules; **69/80 research documented, 11 pending, PLAT-04 catalog ordinal 70 RESEARCH_PENDING, all 80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. Owner NLE-D013 no public MVP, D014 2D/2.5D/3D+Web, D015 authorized AI, D016 catalog, D017 mandatory desktop but mobile conditional, D018 routine docs with no unapproved spend, D019/020 blocked queue, NLE-D009 engine source license OPEN. **Formal dependency graph exactly GFX-01 + GAME-01**; predecessor ADR-0014 and ADR-0042 PROPOSED and NOT implemented. No code #88 authorized.

## CONTEXT LOCK and STALE detection
BASE main `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`. These verified Git blob **SHA-1 object IDs are NOT raw SHA-256 file digests**. If checkpoint, Ledger/approved ADR, Scope, DoD, Architecture, Requirements, catalogue, registry, GFX/GAME contract or HEAD unexpectedly changes, mark STALE, stop and recompile Context Lock; future executable preflight must generate actual raw SHA-256 fingerprints:
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md`: `4cbd736185b1f98be3546cf45a87fb866e493497`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json`: `4ec1712c9fe945281266cf7c180291930208cb43`
- `docs/queue/work-orders/PLAT-04.md`: `00657b9b5e0600a51d6ea5638c7b2c8689656782`
- `docs/adr/0014-gfx-01-rhi-backends.md`: `27b3f4533083c6b6a23a989e0eb8661898d44ade`
- `docs/architecture/gfx-01-graphics-rhi.md`: `4512de487da7df97969b56f8e5f508a56125ab32`
- `docs/contracts/gfx-01-rhi-api.md`: `822cbd118df75b4acf033443d5f75842d1344ae7`
- `docs/adr/0042-game-01-engine-owned-input-actions.md`: `377bfee8b464bc7c9dfcaca1f6ff8452a9616441`
- `docs/architecture/game-01-input-control-mapping.md`: `5f86d817a26a7142496788963453caf247dbfa50`
- `docs/contracts/game-01-input-actions-api.md`: `cc2598fe117ae4a60d7746028df084d7be229426`
- `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`

## SCOPE — EXACTLY EIGHT NEW Markdown files, NECESSARY
1. [Architecture](../architecture/plat-04-mobile-target-adaptation.md).
2. [ADR-0073 PROPOSED](../adr/0073-plat-04-mobile-target-android-ios-policy.md).
3. [Technology/license/security research](../research/plat-04-mobile-technology-license-security-matrix.md).
4. [Semantic mobile contracts](../contracts/plat-04-mobile-target-api.md).
5. [Exactly 128 FUTURE P04 test cases](../testing/plat-04-acceptance-matrix.md).
6. [Physical mobile benchmark protocol](../research/plat-04-mobile-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-04.md).

Research PR adds ONLY eight new Markdown. No changes to original CORE/GFX/GAME/PLAT predecessors, code, existing ADR, CI, catalogue, checkpoint, backlog, registry, 80 code WOs or release classes in research PR.

## OUT OF SCOPE
Compiling C++/JNI/Kotlin/Swift/Objective-C++, installing SDK/Xcode/Android tools, modifying source/CI/Gradle/Info.plist/AndroidManifest, Android/iOS playable binary/APK/AAB/IPA, uploading Play/App Store account, license/sdk/vendor adoption, hardware GPU proof, public MVP, fees/signing/Developer Program enrollment, Cloud build paid services, admin permissions/JIT/plugin, mobile Editor as mandatory, unrelated backlog or broad refactor.

## FILES / SOURCES TO READ
All Context Lock files, [future code #88](https://github.com/KayzenRoot/stormline/issues/88), GFX-01/GAME-01 ADR+architecture+contracts, GFX-02/03, CORE-01 integration docs, DATA-05 cooking, PLAT-05/BIZ-03 distribution, user owner directives. Primary official references: [Android Vulkan](https://developer.android.com/games/develop/vulkan/overview), [GameActivity](https://developer.android.com/games/agdk/game-activity/get-started), [Android 16KiB](https://developer.android.com/guide/practices/page-sizes), [Play target API](https://developer.android.com/google/play/requirements/target-sdk), [ADPF](https://developer.android.com/games/optimize/adpf), [Play Asset Delivery](https://developer.android.com/guide/playcore/asset-delivery), [SDL3 iOS](https://wiki.libsdl.org/SDL3/README-ios), [Apple UIKit lifecycle](https://developer.apple.com/documentation/uikit/managing-your-app-s-life-cycle), [Apple App Store SDK minimum](https://developer.apple.com/news/upcoming-requirements/), [Apple App Review](https://developer.apple.com/app-store/review/guidelines/), [Apple SDK privacy manifests](https://developer.apple.com/support/third-party-SDK-requirements/). Primary source dates/effective requirements must be revalidated on actual future release.

## REQUIREMENTS
GOV-001..005, candidate CAP mobile, NLE-D013..020, catalog acceptance **"Plataformas móveis selecionadas com smoke/compatibilidade documentadas."** Owner 1.0 target classification **UNDECIDED** and selected Android/iOS device budgets unresolved. Formal deps **ONLY GFX-01 + GAME-01**. Future acceptance requires actual game exporter physical Android and/or iOS build/open/close/graphics/input, security/privacy, energy/thermal and store requirements *for selected platforms*.

## ARCHITECTURE RULES
- GFX-01 owns Vulkan Android / native Metal iOS devices, surface/device generation, shader/memory/render cap and GFX-02/03/07 integration. PLAT-04 only offers Android ANativeWindow/iOS CAMetalLayer surface and orientation/viewport/power signal. OpenGL ES optional reduced tier after owner GFX proof.
- GAME-01 owns semantic action maps and touch gestures, controller, keyboard/IME, accessibility; CORE-01 integration must choose one SDL3/GameActivity/UIKit lifecycle event authority, no second event pump.
- Android ARM64 + native 16KiB ELF/page support, real Vulkan1.1 features and fallback optional; distinguish Google Play API36+ target from minOS, native 4KiB/16KiB and signing. iOS native arm64 + actual Metal, UIKit SceneDelegate, App Store 2026 SDK rule separate from supported deployment min.
- Bound mobile RAM, GPU resources, network, background, thermal and power; ADPF headroom NaN/unsupported and max 1 poll/10s; iOS thermalState/Low Power, adaptive 3D scale not blur UI/2D, avoid OS thermal/permission overrides. Persist last-good user project before kill without assuming callback.
- DATA-05/PLAT-05/BIZ-03 own assets/cook/delivery and release/sign/store/account. Explicit platform privacy manifests/Play data safety, scoped storage/Apple sandbox, user approval/ATT, no unrestricted native AI plugins or secret telemetry.

## CONSTRAINTS
Documentation LOW, physical mobile security/signing high assurance only later. Free public GitHub Docs Validation, no CodeRabbit/mandatory outside reviewer, external paid API/dev account/signing/upload without owner approval, force push/irreversible action, invented benchmark/engineering PASS. Source Lock freshness and zero HIGH/CRITICAL mandatory.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight newly ADDED .md in research PR, correct links/Source Pack; no source code/registry/checkpoint/backlog/CI.
- [ ] ADR-0073 **PROPOSED** and two formal deps GFX-01+GAME-01 ONLY, transitive owners not new DAG; mobile release classes stay UNDECIDED.
- [ ] Deep current official Android Vulkan/SDK/GameActivity/16KiB/Play API36/ADPF/PAD and Apple UIKit/Metal/iOS submission/SDK/privacy/security/storage and exact tags/cost gaps honestly documented.
- [ ] Eight groups x16 unique **P04-T001..P04-T128 FUTURE/NOT EXECUTED**, physical test/thermal/battery/benchmark/signed-store proof **future**, no fake PASS.
- [ ] Exact-head research Docs Validation CI SUCCESS, objective pt-BR audit APPROVED documentation, squash/main readback.
- [ ] Independent checkpoint five modified files with **sole semantic registry PLAT-04 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**; other 79 modules and flags unchanged, 70/80 documented (87.5%), 10 pending, all 80 code packets blocked, ready=0, approved_adr=0, release classes undecided, engine=false; own CI/audit/squash/main readback before research issue #333 can close, code #88 OPEN/BLOCKED.
- [ ] Final four-Markdown historical closeout own CI/audit/squash/main readback, next real catalog **PLAT-05 Build, Export & Distribution** ordinal 71, deps PLAT-01+PLAT-02+PLAT-03+PLAT-06+DATA-05.

## TESTS
P00: GitHub Docs Validation Source Pack/links, module DAG/80 registry/blocked selector, API PR file statuses, unique 128 future IDs, semantic registry checkpoint diff later. **No real tests of mobile app, device/SDK, GPU, thermal or signing executed.** Future physical testing only once owner selects target/Scope, with iPhone/iPad and/or Android ARM64 device matrix, actual power/perf and native graphics/gestures/security/privacy/store proof.

## DELIVERABLES
Eight docs, source-specific issue, research PR and exact base/head, primary sources, Evidence Bundle, Docs CI run+job and pt-BR audit, normal squash and main readback; proposed independent checkpoint and historical closure PRs only after gates. No engine.

## REVIEW FORMAT
Português brasileiro, **APPROVED / CORRECTION REQUIRED / BLOCKED**, exact diff scope/HEAD, Source Check SHA and hashes, formal DAG, Android/iOS ABI/thermal/accessibility/store security, licensing/fees, CI run/job, defect severity/rollback, 128 test statuses and proposed Checkpoint Delta. Research APPROVED does not approve code or mobile mandatory 1.0.

## STOP CONDITION
STALE critical source, wrong eight files/128 tests, CI failed, unapproved Android/iOS releases/fees/store accounts/signing or code, new high/critical license/security risk, false hardware benchmark, hidden permission/JIT or source drift: BLOCKED or same-WO/PR CORRECTION REQUIRED. Never activate #88 or next before evidence.

## CHECKPOINT DELTA PROPOSED ONLY
After research CI/audit/squash/main readback, five files: docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO and Evidence; **only PLAT-04 research_status** in registry changes. Own CI/audit/squash/readback before closing research #333. Then separate four-Markdown history with own CI/audit/squash/readback and next **PLAT-05** (71/80). All 80 future coding WOs remain BLOCKED.


## Research PR #334 evidence and independent checkpoint proposal
- [Research PR #334](https://github.com/KayzenRoot/stormline/pull/334) BASE `b12e0755fd9539406a2f92c8e51f1a6d6e19c73a`, HEAD `e85f9f3d2a4fd832dd9e6fe840d4de4cc9fc69b1`, exactly eight ADDED Markdown (architecture, ADR-0073 PROPOSED, license/security matrix, API, 128 future P04 tests, real-device benchmark, Work Order, Evidence); [Docs Validation #43793218005](https://github.com/KayzenRoot/stormline/actions/runs/43793218005) **SUCCESS**, job #133056115079 Source Pack/links, DAG, registry/blocked selector; [objective pt-BR audit #6905748502](https://github.com/KayzenRoot/stormline/pull/334#issuecomment-6905748502) **APPROVED documentary**, normal squash/main readback `56cad8539bf247cf2f0b92020fe2af3f869b54d0` with ADR-0073 PROPOSED and unchanged 69/80 registry at research merge.
- Proposed independent checkpoint **SOLE semantic registry mutation** PLAT-04 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; other 79 modules and root flags unchanged. Target **70/80 researched (87.5%), 10 pending; ALL 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine_implemented=false**. Catalog deps GFX-01+GAME-01 only, source license NLE-D009 OPEN, ADR-0073 PROPOSED, P04-T001..P04-T128 FUTURE/NOT EXECUTED; no Android/iOS mobile app, actual GPU, thermal/battery benchmark, signed store package or public release.
- [Research #333](https://github.com/KayzenRoot/stormline/issues/333) appeared CLOSED automatically after research PR merge before independent checkpoint; it was immediately **REOPENED to preserve gate integrity**. Keep OPEN until independent checkpoint Docs CI/audit/squash/main readback, then close. Future coding [#88](https://github.com/KayzenRoot/stormline/issues/88) remains OPEN/BLOCKED. After audited checkpoint, separate **four-Markdown historical closeout** with own CI/audit/squash/readback before next catalog **PLAT-05 Build, Export & Distribution**, ordinal 71/80, formal deps PLAT-01+PLAT-02+PLAT-03+PLAT-06+DATA-05, code issue #89 blocked.
- Future code #88 stays blocked; this checkpoint own CI/audit/merge/readback required before research issue #333 closes.
