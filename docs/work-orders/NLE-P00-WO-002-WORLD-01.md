# Research Work Order — NLE-P00-WO-002-WORLD-01

**Date:** 2026-11-14 | **Research issue #159** | **Future coding issue #41 OPEN/BLOCKED**  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #160) | **ADR-0026:** PROPOSED | **Context Lock BASE main:** 7a9385aa739edec145a5c417ca7a2b45acda0766 (TWO-04 research PR #157 and checkpoint PR #158 integrated).  
**Risk:** LOW documentation; future ELEVATED memory safety, ABA generational handles, data/schema corruption, concurrent borrows/structural change and privileged world edits.

## OBJECTIVE
Create original, portable and performance-evidence-driven engine Entity Component Model specification for safe lifecycle, stable identity, versioned component schema/reflection, typed queries, deferred transactional changes and source-of-truth persistence. Prevent stale recycled handles, data races and invalid editor/network mutations before any performance optimization. Hand future Zcode executor a scoped approved code Work Order only after objective gates.

## CONTEXT
Stormline P00 documentation-only, public repo, Windows/Linux/macOS and browser targets, editor+headless server/AI native authoring; no public MVP. Git registry currently **22/80 research documented and 58 pending** (including historical CORE-04 research gap), but **all 80 implementation WOs BLOCKED/executor_ready=false**. WORLD-01 is next per approved checkpoint despite CORE-04 gap; this research neither amends nor approves CORE-04. Future coding #41 has mandatory CORE-05 and DATA-04 implementation dependencies, both unavailable.

## SCOPE
- Versioned project/world identity and fresh world epoch, persisted stable DATA-02 EntityGuid vs transient generational entity handle with slot retirement on generation exhaustion, generation/epoch/ref verification across unload/reload and stale/ABA cases.
- Entity lifecycle ALIVE/DESTROY_REQUESTED/TOMBSTONED/RETIRED with safe destructor once, observer/idempotency/late job receipts and explicit ownership; no serialized runtime slot or raw pointer.
- Typed versioned component metadata/TypeId field schema and serialization/migration contracts DATA-04, portable C++20/23 source-generated reflection baseline, optional C++26 P2996 after cross-platform compiler proof; no unsafe dynamic plugin code or exported C++ memory.
- Table/chunk archetype SoA vs sparse-set registry candidate and possible hybrid trade-offs for hot query vs high churn. Flecs MIT, EnTT MIT pinned-license candidate, Bevy ECS MIT OR Apache-2 Rust reference, Unity Entities proprietary sync/ECB reference, no adopted package or vendor ABI.
- Typed include/exclude/optional/changed queries, deterministic sort opt-in, read/write borrow tracking and epoch invalidation, CORE scheduler-owned job fence, deterministic bounded entity command buffers applied at safe structural boundaries with conflict/atomicity and fail-safe receipts.
- DATA-04 durable world authoring/CAS/save/undo, WORLD-02 prefab hierarchy, WORLD-03 spatial/stream, GFX/PHYS/NET and TWO content owners, headless server, safe Editor/CLI/MCP scope/permission and no malicious schema script, quotas, side-channel secret leakage.
- ADR-0026 PROPOSED, architecture/technology+license matrix, typed API, **117 FUTURE NOT EXECUTED** acceptance cases and original workload benchmark protocol, optional STLG prove-or-drop, this research WO/Evidence Bundle, 3 additive Architecture/Backlog/blocked packet links.
- Initial 11-file docs-only research PR with exact-head CI/audit/squash/readback, **separate same-WO checkpoint reconciliation PR** updating only WORLD-01 research_status and retaining all 80 implementation tickets BLOCKED.

## OUT OF SCOPE
No new C++/Rust engine library or compiled binary, ECS running code, assets, world scene, actual sanitizer/benchmarks/throughput claims, mandatory Rust/third-party toolkit or modern C++26 fork, hierarchy/prefabs WORLD-02, spatial index WORLD-03, physics/NET authority implementation, CORE-04 historic research closure, CodeRabbit/paid CI, mandatory external reviewer, bypass, force push or WORLD-02 research before checkpoint is reconciled.

## FILES / SOURCES TO READ
Canonical docs/11-checkpoint.md > docs/10-decisions-ledger.md / approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md; then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/WORLD-01.md, prior CORE-05, DATA-02/04 and GFX/TWO research, world/PHYS/NET interface ownership. Upstream Flecs/EnTT/Bevy/Unity/WG21 official source references recorded in technology matrix. Read exact Git tree/ref/issue/PR before code. Future C++ file paths and ABI TBD after DoD, never guessed.

## REQUIREMENTS
GOV-001..005, CAP-001/004/005/008/009/010/011/012/013/014/016, NFR-001..005 and approved owner NLE-D013..020 where applicable. Future catalog acceptance: creation/destruction with valid invariants/references. Numeric p99, max entities, schema/ID widths, determinism policy, valid storage choices and release 1.0 class UNDECIDED.

## ARCHITECTURE RULES
CORE scheduler owns jobs and memory; DATA-02 source IDs, DATA-04 transactional persistence and migration, DATA-05 cook/stream. WORLD-01 only entity runtime identity/lifecycle/storage/queries. WORLD-02 prefab/hierarchy, WORLD-03 spatial and streaming, PHYS and GAME/NET gameplay authority, GFX/TWO render and animation; no duplicate owner. Public stable API never exposes Flecs/EnTT types or compiler RTTI. Runtime stale generational handle must fail, explicit borrow boundaries and no untrusted code executed from data schemas or Editor/MCP.

## CONSTRAINTS
Research LOW/docs only, existing free GitHub docs-validation and Socket/SonarCloud when present. All 80 code WOs blocked, zero executor-ready and approved_adr=null; WORLD-01 #41 OPEN/BLOCKED, ADR-0026 PROPOSED; historical CORE-04 still pending; actual toolchain/metrics not measured. No claim test/build/production ECS.

## ACCEPTANCE CRITERIA
- [ ] Persistent EntityGuid and transient world-instance+slot+generation handles, no ABA/wrap and safe world remount; lifecycle destructor-once and stale reference rejection specified.
- [ ] Versioned stable component TypeId/schema metadata reflection and DATA-04 safe serialization/migration, portable C++20/23 baseline and optional C++26 static reflection with actual compiler gate.
- [ ] Table archetype vs sparse set vs hybrid storage compared fairly, Flecs MIT, EnTT MIT exact license confirmation before use, Bevy MIT OR Apache-2 and Unity proprietary reference only; public engine ABI stable and no mandatory paid tools.
- [ ] Bounded typed queries/read-write borrowing/epochs and deferred deterministic command buffers with CORE scheduler barrier/atomicity, WORLD-02/03/PHYS/NET source authority separated.
- [ ] Rights/security safe Editor/CLI/MCP CAS, 117 FUTURE NOT EXECUTED tests, repeatable CPU/memory/ABA stress benchmark and STLG prove-or-drop with no invented million-entity claims.
- [ ] Exact 11 docs-only research files, exact-final-HEAD docs-validation SUCCESS, objective pt-BR architecture/security/DoD/source licensing audit no known HIGH/CRITICAL, normal squash/no bypass and readback.
- [ ] Separate same-WO checkpoint PR only WORLD-01.research_status change, code #41 and all 80 code WOs BLOCKED, ADR PROPOSED, next WORLD-02 only after checkpoint validated/integrated; CORE-04 gap remains explicit.

## TESTS
In P00 use GitHub Actions docs-validation on exact final HEAD and existing Socket/SonarCloud status; local if checkout available scripts/validate_docs.py, scripts/validate_module_catalog.py, scripts/validate_wo_registry.py, scripts/select_wo.py WORLD-01 expected reject blocked. **All 117 proposed CPU/C++/race/memory/portability/security/benchmark cases are FUTURE NOT EXECUTED**; no sanitizer, engine benchmark or WEB binary.

## DELIVERABLES
8 new research docs (architecture, tech/license matrix, ADR-0026, semantic API, acceptance matrix, benchmark, WO, Evidence Bundle), 3 additive references in docs/04-architecture.md, docs/08-backlog.md and docs/queue/work-orders/WORLD-01.md. Research issue #159, PR+exact head audit and separate checkpoint reconciliation PR+audit; no code or deployed engine.

## REVIEW FORMAT
pt-BR objective reviewer: BASE/HEAD SHA and Git fingerprints, diff/11 files, observed exact HEAD CI run, rights/architecture/security/DoD, 117 FUTURE test honesty, CORE-04 remaining gap, proposed checkpoint delta and APPROVED/CORRECTION REQUIRED/BLOCKED verdict. No known HIGH/CRITICAL may pass.

## STOP CONDITION
Unexpected main/canonical drift, failed exact-head CI, unlicensed third-party source, dangerous type schema loophole, false throughput/implementation claim, scope creep or HIGH/CRITICAL => CORRECTION REQUIRED / BLOCKED in same WO/PR. No next WORLD-02 while current WO unresolved, no force push, bypass, paid CI or outside human reviewer mandate.

## CONTEXT LOCK
BASE main 7a9385aa739edec145a5c417ca7a2b45acda0766. Git blob OIDs are NOT raw-file SHA-256 fingerprints. Before runtime authorization compute actual SHA-256 source bytes, reconcile CORE-04 gap where necessary, approve 1.0 Scope/DoD and implement/audit CORE-05+DATA-04 dependencies, exact ABI and benchmark proof.

## Verified research PR #160 receipts
BASE main 7a9385aa739edec145a5c417ca7a2b45acda0766; final objective pt-BR audited HEAD af5152a74fe57558171fd4adf67fab20b11346f0; [Docs Validation #43634492193](https://github.com/KayzenRoot/stormline/actions/runs/43634492193) SUCCESS exact final HEAD and Socket Security/SonarCloud PASS; 11 docs-only files with 0 known HIGH/CRITICAL documentation defects, APPROVED research only and normal squash merged main 33de3993eedaf7c4b07cdbda092c2268296bed9d. Same-WO checkpoint is separate 5-file PR requiring its own exact-head CI/audit. All 117 tests FUTURE NOT EXECUTED, ADR-0026 PROPOSED, issue #41 OPEN/BLOCKED. CORE-04 historical research status remains pending.
