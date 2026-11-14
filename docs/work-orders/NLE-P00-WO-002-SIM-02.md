# Research Work Order — NLE-P00-WO-002-SIM-02

**2026-11-14 | Research issue #177 | Future coding issue #47 OPEN/BLOCKED**  
**Status:** RESEARCH IN PROGRESS / DOCUMENTATION ONLY, ADR-0032 PROPOSED. **Context Lock BASE main:** 6099128ead915e010ef252f57cd880f441303d59 (SIM-01 research PR #175 and separate checkpoint PR #176 merged).  
**Risk:** LOW docs-only; future ELEVATED native memory, concurrency, game collision integrity, cross-target floating-point and source/stream authority.

## OBJECTIVE
Specify original Stormline **3D Physics** stable body/shape/constraint semantics, fixed-tick CPU-first headless rigid bodies, sphere/box/capsule/convex/compound and static triangle mesh/heightfield, collision broadphase/narrowphase, contact/sensor events, shape casts/queries, CCD, joints/limits/motors, ECS/scene links and WORLD-03/WORLD-04 streamed collision readiness. Compare Jolt Physics MIT **leading C++ candidate** vs PhysX 5 CPU BSD-3-Clause, Rapier3D Rust Apache-2.0 and Bullet zlib, freeze licensing and determinism/benchmark proof obligations. Future Zcode receives typed contracts and objective gates; no implementation authorized now.

## CONTEXT
Stormline original 2D/2.5D/3D/native/Web engine, docs-first P00, owner solo GitHub free CI and objective pt-BR audit. At verified BASE **28/80 researched/documents (35%)**, **52 research pending** incl historical CORE-04 gap; 80 code WOs BLOCKED/executor_ready=false and zero engine implemented. Coding #47 mandatory prerequisites WORLD-02+CORE-03 CODE **not implemented**. ADR-0032 PROPOSED, release class UNDECIDED, approved_adr=null.

## SCOPE
- Engine-owned PhysicsWorld3D, opaque generational Body/Shape/Constraint/ECS EntityGuid and WorldEpoch, body modes static/dynamic/kinematic, meters, gravity/inertia, CORE-05 origin epoch and WORLD-02 prefab authoring transforms.
- CORE-06 single fixed tick and bounded worker/job/physics state, deferred stable pre-step commands and poststep immutable contact/sensor event & ECS publish, no direct callback scene mutators or reentrant deadlock. Headless CPU without graphics.
- Colliders sphere/box/capsule/convex/compound; dynamic concave mesh unsupported by default; static terrain heightfield/triangle mesh with DATA-03 untrusted geometry validation, DATA-05 cook/hash/source rights and WORLD-04 height source. Safe scaling/winding/precision, collision layers/masks and physically correct narrowphase ray/overlap/casts.
- Constraint fixed/hinge/distance/slider/cone/6DOF only as pinned backend supports, CCD with fast-sensor caveat, sleep/wake, source revision and simulation barrier.
- WORLD-03 streamed cell ground collider becomes traversable only after source revision+WORLD-03/PHYS readiness ACK; safe physics island origin shift and critical pin/fence retirement, last-good collision on failure. SIM-03 controllers, SIM-04 ragdolls, SIM-05 vehicles and SIM-06 deformables external owners.
- Jolt 5.6 docs C++ MIT leading candidate with CROSS_PLATFORM_DETERMINISTIC option+same flags/inputs and parallel broadphase nondeterminism warning, PhysX 5 BSD-3 CPU and optional CUDA GPU (not portable), Rapier3D Apache2 Rust FFI/WASM, Bullet core zlib but Extras excluded; no third-party library, binaries or artwork installed/adopted.
- ADR-0032 PROPOSED, architecture, license matrix, typed API, **170 FUTURE NOT EXECUTED tests**, original 3D stability/memory/headless benchmark, S3P optional PROVE-OR-DROP, this WO+Evidence Bundle and 3 additive source packet links.
- Research PR exactly 11 docs-only files (8 new and 3 additive) with exact final HEAD Docs Validation and available Socket/SonarCloud, pt-BR objective audit and normal squash/main readback; separate same-WO checkpoint PR changes only SIM-02.research_status and independently validates/audits/merges/readbacks before closing research #177. SIM-03 only after checkpoint.

## OUT OF SCOPE
No C++/WASM/Rust adapter, actual runtime physics engine, GPU compute solver, Jolt/PhysX/Rapier/Bullet source install, shader/mesh/asset, game scene, material collider import, build/deploy, compiler, benchmark, deterministic replay proof, actual memory numbers, server auth/lockstep policy, ragdoll, vehicle, soft body or character motor, broad cleanup or historical CORE-04 adoption. No paid CI/CodeRabbit, required human external reviewer, force-push or bypass.

## FILES / SOURCES TO READ
Canonical Source Hierarchy: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and APPROVED ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`. Then `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/SIM-02.md`, WORLD-01/02 ECS+scene source, CORE-03/05/06, WORLD-03/04 cell and terrain, DATA-02/03/04/05 rights/cook/journal, SIM-01 2D contract, SIM-03/04/05/06 ownership, GFX/NET/GAME/EDITOR. Official vendor docs/license refs in technology matrix. Future real C++ filenames/ABI TBD after owner-approved DoD and actual code inventory, do not fabricate.

## REQUIREMENTS
GOV-001..005 and applicable owner Ledger NLE-D001..020, CAP-001/003/004/008/009/010/011/012/013/014/016 and NFR-001..005 as requirements truly applicable. Catalog acceptance "Testes de colisão/escala, memória e simulação headless" NOT MET. Numerical 1.0 release class, collision error thresholds, memory and tick p95/p99 budgets/hardware targets currently UNDECIDED.

## ARCHITECTURE RULES
SIM-02 owns physical 3D broadphase/narrowphase/constraint solver and casts, never WORLD-03 world streaming interest spatial index or GFX-04 visibility/renderer. WORLD-02 owns prefab graph/source, CORE-03 memory and CORE-06 fixed scheduler, DATA-04 authoring CAS, WORLD-04 terrain source, DATA-05 cook/cache, GAME/NET authoritative gameplay and rollback policy. No mutable ECS callbacks or backend public types. Origin changes coordinated and source/collision revision checks mandatory. Physics CPU-first and headless no GPU requirement.

## CONSTRAINTS
P00 LOW docs-only; future ELEVATED. 170 tests FUTURE NOT RUN. ADR-0032 PROPOSED, code issue #47 OPEN/BLOCKED, 80 coding packets BLOCKED, executor_ready=false, approved_adr=null, release class UNDECIDED, historical CORE-04 pending. Only free doc validation and present security CI; no vendor source or performance experiment.

## ACCEPTANCE CRITERIA
- [ ] Versioned engine-owned World/Body/Shape/Constraint/ECS bridges, generational safe handles/WorldEpoch, coordinate units/quaternion/origin, source prefab generation and safe ECS poststep publish.
- [ ] CORE-06 fixed tick and worker quotas, commands pre-step, immutable events poststep, collision filtering, ray/overlap/convex casts exact vs broadphase candidates, no reentrant listener ECS/queries, headless CPU.
- [ ] Sphere/box/capsule/convex/compound dynamic and static heightfield/triangle mesh plus DATA-03 validation, Jolt dynamic mesh caveat, WORLD-03 critical collider stage/ack/pin, constraints/joint subtype feature gates, CCD/sensors caveats, source authoring DATA-04 independent from physics state.
- [ ] Jolt MIT C++ leading candidate but NOT selected, PhysX CPU BSD3/GPU CUDA special binary distinct, Rapier Rust Apache2, Bullet core zlib Extras caveat. Determinism Jolt exact tag/source+defines+input order and broadphase query caveat; independent golden profile future.
- [ ] **170 FUTURE NOT EXECUTED** objective cases and reproducible native Linux/Windows/macOS/ARM64/Web WASM/headless p50/p95/p99/memory/source/CCD/constraints and security benchmark plan; optional S3P PROVE-OR-DROP; no actual FPS/solver/replay test claim.
- [ ] Research PR exactly 11 `docs/` files (8 new+3 additive), no checkpoint/registry, exact-final-HEAD Docs Validation SUCCESS and available security check; pt-BR objective audit, no known HIGH/CRITICAL, normal squash/main readback.
- [ ] Separate same-WO checkpoint PR changes ONLY SIM-02.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED; coding #47 and all 80 code WOs BLOCKED, ADR-0032 PROPOSED, historical CORE-04 pending, own CI/audit/squash/main readback before next SIM-03 research.

## TESTS
Now only free GitHub exact HEAD `docs-validation` and present Socket/SonarCloud checks; if repository checkout available `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py SIM-02` expected reject code because BLOCKED. **All 170 future geometry/solver/CCD/joints/replay/native/WASM/headless/security/memory/bench cases NOT EXECUTED**.

## DELIVERABLES
8 new docs (architecture, technology+license, ADR-0032, semantic API, 170 acceptance scenarios, benchmark, research WO, Evidence) and 3 additive docs (Architecture, Backlog, future code #47 blocked packet links); research issue #177, research PR with exact final HEAD CI/audit/normal squash and separate same WO checkpoint PR with its own independent CI/audit/main readback. No code/SDK/deploy.

## REVIEW FORMAT
Objective pt-BR BASE/head SHA and source Git blob IDs (NOT raw SHA-256), 11/5-file diffs, exact final HEAD Docs Validation and security receipts, ownership/Scope/DoD/ADR/licenses, 170 tests future/not run and missing native baseline, risks and proposed Checkpoint Delta. Verdict APPROVED / CORRECTION REQUIRED / BLOCKED; correction only same WO/PR, no HIGH/CRITICAL accepted, no mandatory outside human reviewer.

## STOP CONDITION
Changed main/Scope/DoD/approved ADR means Context Lock STALE and rebase. CI fail, unsupported shape/rights, unsafe callback, false performance claim or code/registry changes in research PR, or known HIGH/CRITICAL -> CORRECTION REQUIRED/BLOCKED. Do not start SIM-03 until checkpoint approved. No force-push, bypass or paid CI mandate.

## CONTEXT LOCK
BASE Git SHA 6099128ead915e010ef252f57cd880f441303d59. Git blob SHA-1 OIDs NOT source raw SHA-256. Future executor needs actual byte SHA-256, code target file/ABI, approved Scope/DoD/ADR-0032 and integrated WORLD-02+CORE-03 and owner contracts before implementation.
