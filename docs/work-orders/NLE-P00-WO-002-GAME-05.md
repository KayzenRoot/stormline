# NLE-P00-WO-002-GAME-05 — Genre Templates & Systems Research Work Order

**Date:** 2026-11-15 | **Research issue:** [#224](https://github.com/KayzenRoot/stormline/issues/224) | **future code issue:** [#61](https://github.com/KayzenRoot/stormline/issues/61) OPEN/BLOCKED | **BASE:** `3101c3c956d4fa876261433ee258fe174e00cf77` | catalog_order 43/80. **Research risk LOW, future coding ELEVATED; no code executor authorization.**

## OBJECTIVE
Perform deep research and draft engine-owned, reusable, rights-safe and capability-aware original genre-pack architecture enabling shooter, ARPG, vehicles/racing, 2D platformer, strategy and puzzle projects to share the SAME Core and gameplay/animation/audio/world/asset APIs without forks. Analyze current source/licensing, typed source/API contracts, data-driven composition, cross-platform/Web/headless export, accessibility/security, 128 future tests and a reproducible benchmark plan.

## CONTEXT
Stormline P00 documentation program (no runtime), 2D/2.5D/3D native Windows/Linux/macOS and Web vision, AI-native Editor/CLI/MCP with no public MVP. Game-04 research #220, PR #221, checkpoint #222, readback closeout #223 APPROVED/MERGED; main `3101c3c956d4fa876261433ee258fe174e00cf77`. **42/80 previously researched, 38 pending, 0 engine; all 80 coding packets blocked**. GAME-04/SIM-04/AUD-04 are the catalog predecessors, all documented only, no executable code.

## SCOPE
Exactly eight new Markdown documents in research PR:
1. [architecture](../architecture/game-05-genre-templates-systems.md)
2. [ADR-0046 PROPOSED](../adr/0046-game-05-declarative-composable-genre-packs.md)
3. [technology and licensing matrix](../research/game-05-genre-technology-license-matrix.md)
4. [semantic API contracts](../contracts/game-05-genre-template-api.md)
5. [128 FUTURE tests](../testing/game-05-acceptance-matrix.md)
6. [benchmark protocol](../research/game-05-genre-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-05.md).

Research PR from branch `docs/NLE-P00-WO-002-GAME-05-genre-templates`; exact-final-HEAD Docs Validation and scoped pt-BR objective audit, ordinary squash/readback. Only after APPROVED, separate checkpoint PR changes exactly checkpoint, backlog, registry **only GAME-05 research_status**, this WO and Evidence Bundle, with own CI/audit/squash/main readback; close research #224 after checkpoint readback. Target **43/80 researched (53.75%), 37 pending, 0 runtime**; all 80 coding packets blocked.

## OUT OF SCOPE
No C++/Rust/C# engine, third-party code/assets/templates, shader, sample scene, gameplay executable, editor functionality, SDK, native export, Web demo, network/game server, asset purchase, testing harness or real test execution, compiler, benchmark, brand/trademark/IP copying, approved code license, auto-merge bypass, new public release, modification of code issue #61 or changing implementation registry statuses other than GAME-05 research_status in independent checkpoint PR.

## FILES / SOURCES TO READ (canonical priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/GAME-05.md`. Relevant prior research: `docs/architecture/game-04-gameplay-systems-event-bus.md`, `docs/contracts/game-04-gameplay-event-api.md`, `docs/architecture/sim-04-skeletal-animation-motion.md`, `docs/architecture/aud-04-music-dialogue-cinematic-audio.md`, GAME-01/02/03, DATA-02/03/04/05, WORLD-02, SIM-02/03/05, relevant NET and AI authoring policies. Upstream official sources/rights in matrix.

## REQUIREMENTS
GOV-001..005, CAP-004/006/007/008/009/010/011/012/013/014/015/016, NFR-001..005, NLE-D002/003/004/005/009/013..020. **Engine license NLE-D009 OPEN**, technologies/asset usage PROPOSED, catalog index is not 1.0 MUST-HAVE. Original genre samples must not imitate protected commercial game code/assets. All 80 coding drafts remain blocked.

## ARCHITECTURE RULES
GAME-05 only composes templates and genre data: GAME-04 owns authoritative typed game commands/state/inventory/abilities/event bus, SIM-04 owns skeletal/animation/root-motion intents, AUD-04 owns dialogue/music/subtitle policies. GAME-01 input, GAME-02 scripts/capabilities, GAME-03 UI/locale, WORLD-01/02 scene/ECS, SIM-02/03/05 physics/vehicles/motor, DATA-01/02/03/04/05 VFS/identities/import/CAS/cook, CORE-03/04 scheduler/tick, PLAT and NET own targets/authority. No second physics, second renderer, unsafe native plugin, template OS shell, direct client loot grant, direct file write or third-party code copying. Editor/CLI/MCP calls same semantic operations and validates roles. Provenance, memory/size/fanout budgets, migrations and failure receipts mandatory.

## CONSTRAINTS
P00 docs only; zero obligatory paid services, no CodeRabbit, no mandated external reviewer, no force push or protection bypass. Context Lock must be refreshed when checkpoint/Scope/DoD/approved ADR/source changes; no "completed" without exact Git/test evidence. No new engine license, imported art/font/SFX/IP or SDK. No invented numerical performance, game exports or security clearance.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown docs, links and Source Pack validation; no engine source, content/imports or accidental CI changes.
- [ ] ADR-0046 PROPOSED, one Stormline-owned pack schema + capability/dependency/overrides, explicit six genre fixtures and trusted authority boundary; no separate core for each genre.
- [ ] Official primary references and licensing matrix including Godot demos MIT but project asset audits, Bevy MIT OR Apache-2.0 with separate example art, O3DE Apache2 OR MIT and 3P obligations, Stride MIT exceptions, Unreal/Unity sample usage restrictions, Jolt MIT SIM-only; no copied IP/SDK.
- [ ] Versioned composable source/Editor/CLI/MCP contracts, DATA-04 CAS/recovery and deterministic replay/type/schema/capability rejection; cross-OS/Web/headless future export gates truthful.
- [ ] Exactly 128 G05-T001..T128 FUTURE/NOT EXECUTED, reproducible p50/p95/p99/content/license/dependency/genre export protocol, no invented results or threshold approvals.
- [ ] Exact-final-HEAD research PR Docs Validation SUCCESS + pt-BR objective audit APPROVED + normal squash/main readback, no known HIGH/CRITICAL in scoped diff.
- [ ] Separate checkpoint PR own exact-final-HEAD Docs Validation/audit/squash/main readback; sole registry field GAME-05 research_status -> RESEARCH_DOCUMENTED_ADR_PROPOSED.
- [ ] Final **43/80 research documented, 37 pending, 0 runtime**; 80/80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`; future issue #61 OPEN/BLOCKED, research #224 closed only after checkpoint readback.
- [ ] No next NET-01 research until closure and readback, no coding unlock.

## TESTS
GitHub **Docs Validation** actual mandatory, including Source Pack link validation, dependency DAG/module registry and Zcode blocked selector on exact HEAD. **128 future GAME-05 runtime tests NOT EXECUTED**, no compiled builds/sanitizers/native/Web/headless sessions/genre samples/benchmarks. No claim of complete accessibility, network/physics/animation/audio integration.

## DELIVERABLES
Research issue #224 and exactly eight documents, research PR with observed CI/audit/squash/main readback, independent checkpoint PR with own gates and only single status delta, Evidence Bundle, objective pt-BR review and final closing readback. Implementation #61 not changed.

## REVIEW FORMAT
Pt-BR verdict **APPROVED / CORRECTION REQUIRED / BLOCKED** with Git BASE/final HEAD and critical blob fingerprints, changed file list/diff, exact CI run/job and results, source/license/provenance, dependency authority, 128 FUTURE tests explicitly NOT RUN, unverified targets/budgets, risks/high-critical count, rollback, **proposed** Checkpoint Delta only until audit. Corrections in same WO/PR.

## STOP CONDITION
STALE source/incorrect base, corrupted catalog count/status, unlicensed asset, copied IP, unsafe authoring shell or native plugins, duplicate GAME/WORLD/SIM/AUD authority, schema/license/privacy threat omitted, failing Docs Validation, known HIGH/CRITICAL, attempted early coding or unmergeable PR => CORRECTION REQUIRED or BLOCKED. No next research until checkpoint audited/read back.

## CONTEXT LOCK (Git blob SHA, not content SHA-256, at base)
BASE `3101c3c956d4fa876261433ee258fe174e00cf77`. Checkpoint `c8caaee00c5fd2bae471c60cc83d06ffc5bc2318`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `10fa02a855c176e7021b3c21b5b2dcf9edc54f3f`; Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; registry `e7c6a3798e35ec6545286dad61a492a18899231a`; code draft GAME-05 `effd5023cc054fd119f0a8e0085b849660910544`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; GAME-04 architecture `a9f12f2281a15cd1306dc0270b6e1dead3639e41`, API `0f5f2edc888052f401ce1c2fe85828a299f43520`; SIM-04 architecture `8f1d0a9211c093322d8a2868cc6ef89a6308c919`; AUD-04 architecture `8104ddac546ab5133372859e71e771b66750ccf0`. Recheck before any changes and use actual HEAD rebase on STALE.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-05.md); until verified, PR/CI/tests/bench/merge **PENDING**, no claim of code.
