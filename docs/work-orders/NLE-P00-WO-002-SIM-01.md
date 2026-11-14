# Research Work Order — NLE-P00-WO-002-SIM-01

**Date:** 2026-11-14 | **Research issue:** #174 | **Future code:** #46 OPEN/BLOCKED  
**Status:** APPROVED/MERGED FOR RESEARCH DOCS ONLY (PR #175), NO CODE | **ADR-0031:** PROPOSED | **Context Lock BASE main:** e7704cecb085db5584c88408e5451c4639780db4 (WORLD-05 research PR #172 and checkpoint PR #173 merged).  
**Risk:** LOW documentary now, future ELEVATED for physics collision/simulation, numeric determinism, stale events/ECS memory, untrusted shapes and save/network authority.

## OBJECTIVE
Prepare complete original Stormline first-class 2D physics research and future, independently testable implementation requirements: fixed-timestep headless world, engine-owned opaque generational Body/Shape/Joint IDs, qualified WORLD-01 EntityGuid bridge and TWO-01 pixel/physical unit conversion, rigid bodies, convex primitives/chain+tile collision, joints, CCD, sensors/filters/contact events, casts/queries, ECS stable post-step publication, validation and safe scene/stream unload. Compare Box2D 3.x C17 MIT **leading candidate**, Chipmunk2D C99 MIT and Rapier2D Rust Apache-2.0 (not adopted), freeze numeric, licensing and stability/benchmark proof gates. This Work Order does NOT authorize coding.

## CONTEXT
Stormline P00 documentary planning, 80 planned module code WOs (none executable), Win/Linux/macOS+Web and headless 2D/2.5D/3D, AI-native Editor/CLI/MCP, owner-approved solo free CI/PR workflow. Current verified registry **27/80 documented researches (33.75%), 53 RESEARCH_PENDING** including historical CORE-04 pending; all 80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` and `executor_ready=false`. Mandatory future code dependencies WORLD-01 and TWO-01 **NOT IMPLEMENTED**, future code #46 OPEN/BLOCKED.

## SCOPE
- Versioned world/scale and reference physical units, CORE-06 fixed tick and bounded catch-up/substeps (1/60 s candidate only; numeric TBD), per-world callback-safe deferred commands and body modes static/kinematic/dynamic.
- Owner `PhysicsBodyHandle/ShapeHandle/JointHandle` world+slot+generation and ECS EntityGuid mapping, source+runtime transforms, CORE-05 origin epoch, stable events and safe ECS poststep snapshots, TWO-01 render interpolation decoupled.
- Circle, capsule, box, convex polygons and tile chain source, compound shapes, filter category/mask/groups, sensors opt-in, collision contact events, queries ray/overlap/shape cast and CCD high-speed caveat, joint types feature gated by pinned backend. WORLD-03 critical tile collider PHYS ACK and DATA-04/05 source/cook lifecycle.
- Security and code rights: Box2D 3.2 C17 MIT leading candidate and 3.1+ vendor determinism claim, Chipmunk2D MIT C99 fallback, Rapier2D Apache-2.0 Rust/C/WASM, notices/SBOM/tag/FFI and precision pinned before adoption. No SDK/assets/samples imported.
- Explicit future deterministic replay/rollback entire state only if supported and proved, native/headless/WASM and 1/2/8 worker golden profiles, collision and tile/CCD stress with source asset rights and type-safe Editor/CLI/MCP.
- ADR-0031 PROPOSED, architecture, technology/license matrix, semantic API/errors, **159 FUTURE NOT EXECUTED tests**, independent headless and native/Web benchmark protocol, WO/Evidence Bundle and additive blocked packet/Architecture/Backlog links.
- First 11 docs-only research PR exact final HEAD free Docs Validation + any Socket/SonarCloud checks, pt-BR objective audit, normal squash and readback; separate same-WO checkpoint PR changing ONLY SIM-01.research_status, independent exact HEAD CI/audit/squash/main readback, close #174 after verified; then next SIM-02 research.

## OUT OF SCOPE
No engine C++ physics source, FFI adapter, vendor dependency installation, executable simulation, game/server/renderer, collision assets or preview, GPU shaders, real trace, rollback build, actual deterministic golden result, software/hardware throughput, promises of zero tunneling, real numeric stability targets, simultaneous SIM-02/03 research, CORE-04 historical cleanup, force-push/bypass, paid CI/CodeRabbit or mandatory external reviewer.

## FILES/SOURCES TO READ
Canonical priority docs/11-checkpoint.md > docs/10-decisions-ledger.md/approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md. Then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/SIM-01.md, WORLD-01 ECS research/contract, TWO-01 native Canvas and TWO-02 tile collision, WORLD-02 source graphs, WORLD-03 spatial streaming, CORE-05/06 time/math, DATA-02/03/04/05, GAME/NET/GFX/AUDIO integration owners, actual code issue #46, official Box2D/Chipmunk/Rapier docs/licenses in research matrix. Do not invent future C++ file inventory/ABI.

## REQUIREMENTS
GOV-001..005, NLE-D001..020 only when approved in Ledger, relevant CAP-001/004/008/009/010/011/012/013/014/016, NFR-001..005. Exact 1.0 Scope/DoD, release class UNDECIDED, actual target physics p95/p99 tick memory, stability/penetration tolerance and supported precise numeric profile TBD owner. Catalog acceptance: 2D collision/stability/stress suite, NOT ACHIEVED NOW.

## ARCHITECTURE RULES
SIM-01 owns physical collision broadphase/narrowphase/solver/query and joint state only, not WORLD-03 scene streaming spatial index, WORLD-01 ECS, TWO-01 Canvas/render, DATA-04 scene journaling, CORE tick, SIM-02 3D, SIM-03 character controllers or NET authority. SDK internal types opaque; commands validated before step, events poststep with generation, no script callbacks/unsafe mutation midstep. Default pipeline headless and platform-neutral. Source units checked against renderer scale, no unapproved real-time variabledt physics.

## CONSTRAINTS
P00 docs-only, all 80 code WOs BLOCKED, zero executor-ready, ADR-0031 PROPOSED and issue #46 OPEN. 159 future CPU/solver/CCD/joint/security/native/Web/golden/bench tests **NOT EXECUTED**. Historical CORE-04 research gap unchanged, no claims source/render/physics implemented or measured. Free docs CI and objective solo pt-BR review only; no force-push/paid tool/human external reviewer mandate.

## ACCEPTANCE CRITERIA
- [ ] Clear ownership and versioned World/Body/Shape/Joint generational IDs with ECS-qualified EntityGuid and source revision, robust stale event/handle/WorldEpoch and unit/physics plane validation.
- [ ] Fixed CORE-06 tick, queued commands, poststep events/snapshot, dynamic vs kinematic vs static transform sync, render interpolation decoupled, source collision reauthoring DATA-04/CAS and WORLD-03 PHYS ready ACK before cell traversal.
- [ ] Convex primitive, chain/ghost tile collision, shape import validation/rights, broadphase exact query refinement, ray/overlap/cast, sensor event opt-in/filter, CCD sensor caveat, joint support feature-gated and stable lifetime; no second 3D physics or ECS.
- [ ] Box2D C17 3.x MIT leading candidate, Chipmunk2D MIT and Rapier Apache-2.0 alternatives; backend type leakage avoided, actual release license/FFI/native/Web deterministic profile only chosen after independent proof.
- [ ] **159 FUTURE NOT EXECUTED** tests and full-headless physics benchmark protocol p50/p95/p99, stress/replay/snapshot only with complete backend state, native Web/WASM and security/fuzz/corruption, no claimed 60fps, perfect CCD or cross-target determinism yet.
- [ ] Exactly 11 docs-only research files (8 new, 3 additive links) no checkpoint/registry changes; exact final HEAD Docs Validation SUCCESS and available security CI, pt-BR documentary audit zero known HIGH/CRITICAL, normal squash/readback.
- [ ] Separate same-WO checkpoint PR modifies only SIM-01.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED. All 80 coding WOs BLOCKED, #46 OPEN, ADR-0031 PROPOSED and CORE-04 old research gap pending; independent exact-final-head CI/audit/normal squash/readback before SIM-02 research.

## TESTS
In P00 only free GitHub Actions docs-validation at FINAL HEAD, any available Socket/SonarCloud; if local checkout available `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py SIM-01` expected refusal for blocked code. All **159 real solver/stability, CPU, security, C17/native/Web/headless/replay/tick p99 tests FUTURE NOT EXECUTED**.

## DELIVERABLES
Eight new docs (architecture, matrix, ADR-0031, typed physics API, 159 future tests, benchmark protocol, WO, Evidence) and three additive Architecture, Backlog, future code #46 packet links, research issue #174, research PR and separate same-WO checkpoint PR with objective CI/audit+merge readbacks. No executable, editor or deployment.

## REVIEW FORMAT
Objective pt-BR verdict APPROVED/CORRECTION REQUIRED/BLOCKED with BASE/HEAD Git SHA, canonical Git blob fingerprints NOT source SHA-256, diff inventory, exact final HEAD CI links, approved Source Pack hierarchy Scope/DoD/security/rights evidence, note 159 tests NOT EXECUTED, future risks/unknown numeric thresholds and Checkpoint Delta. Corrections only same WO/PR and no progress with known HIGH/CRITICAL.

## STOP CONDITION
Changed main/Scope/DoD/approved ADR => STALE/rebase/context lock; failed CI, license conflict, untrusted shape/unsafe callback model, unauthorized code/registry change or known HIGH/CRITICAL => CORRECTION REQUIRED/BLOCKED, do not start SIM-02 before checkpoint approved. No forced push/paid CI/bypass.

## CONTEXT LOCK
Research BASE Git main e7704cecb085db5584c88408e5451c4639780db4, future code requires raw source byte SHA-256, approved release Scope/DoD/ADR-0031, integrated WORLD-01+TWO-01 code prerequisites, actual C++ target paths/ABI and real runtime Evidence Bundle.

## Verified research PR #175 and correction receipts
Research BASE main e7704cecb085db5584c88408e5451c4639780db4, initial HEAD 014de4c56413d373ad1788acf6e01c506da0ea99 failed [Docs Validation #43642247043](https://github.com/KayzenRoot/stormline/actions/runs/43642247043) due two escaped Markdown backticks in physics benchmark. Correction Delta within SAME WO/PR fixed and logged failure in Evidence. Final audited HEAD f594b5f7991e463dc571a135602115d7d3a49e71 passed [Docs Validation #43642341455](https://github.com/KayzenRoot/stormline/actions/runs/43642341455) SUCCESS exact final HEAD plus Socket Security/SonarCloud SUCCESS. Eleven docs-only files, objective pt-BR architecture/security/licensing/DoD audit APPROVED docs only no known HIGH/CRITICAL, normal squash main dabbec4840bf43885f884a6c6a1fd3bc5bac4048 and Git readback confirmed. Same-WO checkpoint PR is separate with own exact HEAD CI/audit gate. 159 FUTURE physics tests NOT EXECUTED, ADR-0031 PROPOSED, coding #46 OPEN/BLOCKED.
