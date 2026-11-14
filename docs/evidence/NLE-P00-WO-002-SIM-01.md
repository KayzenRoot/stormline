# Evidence Bundle — NLE-P00-WO-002-SIM-01 Physics 2D Research

**State: RESEARCH PR OPEN; INITIAL CI FAILURE REPRODUCED AND CORRECTED; NEW EXACT FINAL HEAD CI/AUDIT PENDING** | Research #174 | Future coding #46 OPEN/BLOCKED.  
**BASE main:** e7704cecb085db5584c88408e5451c4639780db4. **Branch:** docs/NLE-P00-WO-002-SIM-01-physics-2d-research. There is **NO** engine binary, Box2D/Chipmunk/Rapier adapter, physics solver instance, compiled test, real collision/joints/events, native/Web build, screenshot, GPU or CPU benchmark.

## Canonical source and dependency
- Source hierarchy Git checked: checkpoint > Decisions Ledger/APPROVED ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog and future #46 packet. Previous WORLD-05 research #171 PR #172 + checkpoint PR #173 integrated and read back with main e7704cecb085db5584c88408e5451c4639780db4. **27/80** research documented, **53 pending** incl historic CORE-04 gap, all **80 code packets BLOCKED/executor_ready=false**.
- Future code **WORLD-01 and TWO-01** mandatory predecessors NOT IMPLEMENTED; WORLD-02/03 and DATA/CORE code contracts only documentary; SIM-01 code #46 OPEN/BLOCKED. ADR-0031 PROPOSED/release class UNDECIDED, backend candidate NOT ADOPTED.
- Official literature verified: Box2D 3.2.0 docs C17 and MIT LICENSE, upstream FAQ 3.1+ cross-platform determinism claim scoped to same input and precision, post-step contact events and chain ghost/CCD/sensor limitations; Chipmunk2D upstream MIT C99; Rapier official Apache-2.0 Rust/JS/C and optional enhanced deterministic profile. No third-party library, code, sample art or demo files copied/installed.
- Semantic design: engine-owned World+Body/Shape/Joint generational IDs, ECS EntityGuid mapping, CORE fixed tick and optional physics origin epoch, TWO-01 Canvas pixels↔meters adapter and render interpolation, TWO-02 static tile chains/cooked rights, source DATA-04 journal vs runtime safe PHYS step, WORLD-03 active collider ACK and leases, post-step buffered event generations, stable query/CCD and sensors, bounded joins and event/shape resource limits. Deterministic replay and rollback **unproven**.

## Canonical BASE Git object fingerprints (Git blob SHA-1 IDs, NOT raw source SHA-256)
- `docs/11-checkpoint.md`: `9359efe3b21d29185d99bc4c177e091e3f826c68`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `66fe609c354b6ae65b330ae3708ce189d64da528`
- `docs/queue/work-orders/SIM-01.md`: `e5a70432882a1fd1d39fb18f43d90f85a5aa65b4`
These are Git object IDs at BASE, NOT source byte SHA-256. Future code Context Lock must calculate actual byte SHA-256 after approved coding Scope/DoD and re-verify each canonical source.

## Initial research delivery and truthful proof
- Intended exactly 11 docs-only files: 8 new architecture, technology/license matrix, ADR-0031 PROPOSED, typed API, **159 FUTURE NOT EXECUTED** test matrix, headless/OS/WASM benchmark protocol, research WO, this Evidence; plus 3 additive Architecture/Backlog/blocked code #46 packet links. No checkpoint/registry changes in research PR.
- [Research PR #175](https://github.com/KayzenRoot/stormline/pull/175) initial HEAD `014de4c56413d373ad1788acf6e01c506da0ea99`, [Docs Validation #43642247043](https://github.com/KayzenRoot/stormline/actions/runs/43642247043) **FAILURE** (job #132592160202): `escaped Markdown code-fence marker` in `docs/research/sim-01-physics-benchmark-protocol.md`, observed in real job log. **Correction Delta in SAME research WO/PR**: remove escaped Markdown backtick markers ONLY from benchmark and document failure here. NEW exact final HEAD CI/security checks and objective pt-BR audit required before any merge. Initial failed HEAD is NOT approved.
- Objective pt-BR audit, normal squash/main readback: **PENDING**.
- **ALL 159 future physics tests NOT EXECUTED**. No tests of freefall/CCD/stack/joints/sensors/trigger ordering, shape data fuzz, native/Web headless build, backend C17/Rust FFI, ECS source/PHYS collision ACK, rollback golden, determinism or measured p95/p99/memory. No performance or physics success claim.
- Documentation risk LOW; future ELEVATED memory/callback/CCD/security/source integrity and numerical determinism. No unlocked code, APPROVED backend or actual release.

## Checkpoint Delta proposed NOT APPLIED
After research PR exact final HEAD free Docs Validation and any available security checks SUCCESS plus objective pt-BR audit APPROVED no known HIGH/CRITICAL and normal squash/main readback, separate SAME-WO checkpoint PR should change ONLY `SIM-01.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. Update Checkpoint/Backlog/WO/Evidence with actual receipts, retain all 80 coding WOs BLOCKED/executor_ready=false/approved_adr=null/release UNDECIDED, future coding #46 OPEN/BLOCKED, ADR-0031 PROPOSED, CORE-04 historical research gap unresolved. Independently validate checkpoint final HEAD+audit+merge/readback before closing research #174 and beginning SIM-02 research.
