# Research Work Order — NLE-P00-WO-002-WORLD-05

**2026-11-14 | Research #171 | Future coding issue #45 OPEN/BLOCKED**  
**Status:** APPROVED/MERGED FOR RESEARCH DOCS ONLY (PR #172), NO CODE | **ADR-0030 PROPOSED** | **Context Lock BASE main:** 6a52aef21150e815692b83a4060a994f46d835f9 (WORLD-04 research #168 PR #169 and checkpoint #170 merged).  
**Risk:** LOW documentation, future ELEVATED due to nondeterministic data, manual authoring loss, untrusted generator graph, large CPU/WFC costs, source corruption and cache/streaming races.

## OBJECTIVE
Produce an original typed, secure and finite procedural DAG and versioned generator recipe that makes the catalog acceptance objectively testable: **"Mesmo seed + versão produz resultado idêntico; edição manual preservada."** Freeze algorithm/graph/source asset versions, numeric/coordinate/seed profile, canonical byte encoding and stable global sample keys; generate proposal-only biome/height/geometry/2D tile/placement outputs independent from scheduling and cell request order. Preserve artist edits via DATA-04 overlay and field/instance conflict receipts, no unconsented source mutation. Equip future Zcode executor with precise references, tests, proof gates and stable Work Order ID, NOT runtime authorization.

## CONTEXT
Stormline P00 documentary planning, public free solo CI, native Win/Linux/macOS and browser/Web/headless, original 2D/2.5D/3D and AI-native Editor/CLI/MCP. Verified baseline **26/80 research documented (32.5%)**, **54 RESEARCH_PENDING**, historical CORE-04 still pending; all 80 implementation WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`/executor_ready=false and no shipped engine. Mandatory future code dependencies `WORLD-04` and `DATA-03` not implemented. Future issue #45 OPEN/BLOCKED; ADR-0030 technical PROPOSED, release class UNDECIDED.

## SCOPE
- Stable `MasterSeed128` and domain-separated global World/Graph/Node/Cell/Patch/Output/Counter seed key, exact integer/float rounding/endianness, version pin/source hashes and reference canonical CPU profile; no ambient RNG/scheduler drift, proof-based Web/WASM equality, GPU preview explicitly noncanonical until independently bitwise proved.
- Original pure typed DAG with stable NodeGuids, type-safe ports with units/resolution/coordinate convention, bounded maximum nodes/depth/operations, deterministic topological order, invalid input/revision/license and script/URL denial, explicit algorithm version migrations.
- Terrain height/mask/biome/vegetation placement proposals and optional controlled geometry/tile/constraint rules, local per-cell seam halos or global bounded region solve when cross-cell dependencies demand; single WORLD-05 generator owner, no WORLD-04/03/DATA-05/GFX/TWO/PHYS/NET owner duplication.
- Compare FastNoiseLite MIT noise/cellular/domain warp, OpenSimplex2 file-level CC0/Unlicense, WFC MIT *software* with separately rights-checked samples and bounded contradictory constraint failure, Random123 BSD-style optional counter RNG with exact pin if used; Unreal PCG proprietary and Houdini PDG commercial/proprietary only design references. No package/source/media integrated.
- Versioned generated content IDs, DATA-05 dependent cook/cache source hashes and invalidation, cancellation and streaming via WORLD-03, generated base separated from DATA-04 manual authoring overlay; three-way old-generator/new-generator/artist diff, tombstone suppressions, stable placement remap and explicit orphan conflicts, journal/CAS/undo/redo and safe owner ACK publish.
- Editor/CLI/MCP semantic inspect/stage/preview/compare/authorize/commit with least privileges/quotas, no arbitrary host scripts/shaders/URL/plugins, simulation server authority stays GAME/NET/PHYS.
- ADR-0030 PROPOSED, architecture/tech-license matrix, typed API, **160 FUTURE NOT EXECUTED** acceptance tests, deterministic golden corpus and original benchmark plan, SCDI optional PROVE-OR-DROP, this WO/Evidence Bundle plus 3 additive Architecture/Backlog/blocked code #45 packet links.
- **Research PR 11 docs-only files**, exact final HEAD free Docs Validation + available Socket/SonarCloud, pt-BR objective audit no known HIGH/CRITICAL, normal squash main readback; **separate same-WO checkpoint PR** changing exclusively WORLD-05.research_status with independent exact HEAD checks/audit/merge/readback and research issue #171 closure.

## OUT OF SCOPE
No C++/WASM interpreter, actual generator output, art/asset import, mesh GPU or shaders, live editor, native/Web build, WFC runtime, code benchmark, selected deterministic library, vendor code/media, runtime graph scripting, authoritative simulation/quest/NET generation, proof of 100% cross-platform equality or performance, automatic migration of artist edits. No unrelated CORE-04 research closure, SIM-01 research before checkpoint, required external human reviewer/CodeRabbit/paid CI, force push/bypass or broad cleanup.

## FILES / SOURCES TO READ
Priority Source Hierarchy: docs/11-checkpoint.md > docs/10-decisions-ledger.md/approved ADRs > docs/03-scope.md > docs/09-definition-of-done.md > docs/04-architecture.md > docs/02-requirements.md, then AGENTS.md, docs/product/module-catalog.md, docs/queue/implementation-registry.json, docs/queue/work-orders/WORLD-05.md; WORLD-04 terrain authoring, WORLD-03 spatial/cells, WORLD-02 scene/prefab, WORLD-01 ECS, DATA-02/03/04/05, CORE-05/06 and GFX/TWO/PHYS/NET contracts. Official upstream version/license references in matrix. Future runtime target filenames and ABI TBD after owner-approved 1.0 DoD and code prerequisites, never invented.

## REQUIREMENTS
GOV-001..005 and applicable CAP-001/003/004/005/008/009/010/011/012/013/014/016, NFR-001..005, NLE-D001..020 only with actual Ledger state. Future catalog test is **same master seed + full pinned recipe/algorithm/source/numeric/cell scope = identical canonical bytes** across approved real native/WASM CPU builds, original manual editor overlays not overwritten. Numeric max graph/cells, WFC iterations, cache and CPU p95/p99 and release class UNDECIDED.

## ARCHITECTURE RULES
WORLD-05 only pure typed generation graph and immutable proposals+provenance. WORLD-04/02 authored content and scene owner, DATA-04 journal/CAS/undo/redo, DATA-05 cache/I/O/cook, WORLD-03 cell residency, CORE jobs/numeric, GFX/TWO rendering and PHYS/GAME/NET authority. CPU exact reference before GPU acceleration authoring; no silent cross-version golden match claim or manually overwritten source. Headless canonical CPU independent of GPU.

## CONSTRAINTS
LOW current docs, future ELEVATED. Only scoped markdown in first PR, no checkpoint or registry; only separate checkpoint after objective CI/audit. 160 proposed tests FUTURE NOT EXECUTED. All 80 code WOs BLOCKED/executor_ready=false, `approved_adr=null`, ADR-0030 PROPOSED and #45 OPEN/BLOCKED; historical CORE-04 research gap remains.

## ACCEPTANCE CRITERIA
- [ ] Canonical versioned seed graph/node/region/cell/algorithm input and source hashes, stable known byte encoding, distinct source key domains and independent jobs; no false CPU/GPU mathematical equality promise, Web/native proof in future.
- [ ] Explicit type/port/units/resolution, acyclic DAG and bounded exception for WFC/erosion, deterministic topo/worker order and portable negative world cell/halo seams with shared solver region when required.
- [ ] FastNoiseLite MIT, OpenSimplex2 mixed CC0/Unlicense, WFC MIT software but asset rights independent, Random123 BSD-style optional exact pin, Unreal PCG and Houdini PDG proprietary references, no vendor package/assets installed.
- [ ] Generator writes proposals only with stable IDs/provenance and DATA-05 content hash; DATA-04 artist stroke/overrides/tombstone and WORLD-02 prefab edits remain intact after regeneration; 3-way orphan conflict/CAS/undo/redo/recovery.
- [ ] Typed Editor/CLI/MCP least-privileged semantic operations, script/URL denial, graph resource/seed output budgets, GAME/NET/PHYS server authority and replay safety.
- [ ] **160 FUTURE NOT EXECUTED** cases and independent canonical golden corpus/byte+cross-target/CPU/memory benchmark protocol; optional SCDI PROVE-OR-DROP, no claimed world generation results or numeric throughput.
- [ ] Initial 11 docs-only research files, exact final HEAD Docs Validation SUCCESS + security when present, pt-BR audit no known HIGH/CRITICAL and normal squash/main readback. Separate same-WO checkpoint PR only WORLD-05.research_status change and independent CI/audit/squash/readback.
- [ ] Coding #45 remains OPEN/BLOCKED, 80 code WOs BLOCKED, ADR-0030 PROPOSED, CORE-04 research gap not hidden. Next SIM-01 only research **after** checkpoint reconciled.

## TESTS
In current P00: GitHub Actions `docs-validation` exact-final-HEAD and available Socket/SonarCloud; if checkout available `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py WORLD-05` must deny executor while code blocked. **All 160 seed, graph, CPU/WASM, regeneration/undo, security, memory, WFC and performance cases FUTURE NOT EXECUTED**; no real binary, scene, graphic, source migration or runtime verification.

## DELIVERABLES
8 new docs architecture, technology/license matrix, ADR-0030, semantic API, 160 future tests, benchmark protocol, research WO, Evidence Bundle; 3 additive docs Architecture/Backlog/blocked WORLD-05 coding packet references; issue #171 and scoped research PR, plus separate checkpoint reconciliation PR both with CI/audit/readback. No engine release.

## REVIEW FORMAT
Objective pt-BR review: BASE/HEAD SHA and Git source fingerprints, 11-file diff, exact HEAD CI run, 160 tests honesty, licensing and rights, graph/security/manual edits, owner architecture/Scope/DoD, risks and Checkpoint Delta, verdict APPROVED/CORRECTION REQUIRED/BLOCKED. Review solo objective but no mandatory outside human reviewer; correct same WO/PR only if needed, never advance with known HIGH/CRITICAL.

## STOP CONDITION
Main/canonical source drift => STALE and re-lock, failed CI/security, unlicensed sample asset, unbounded scripts/unsafe graph, false byte portability/perf claim, unexpected code/registry change or HIGH/CRITICAL => CORRECTION REQUIRED/BLOCKED same WO/PR; no SIM-01 until checkpoint. No force-push, paid required CI or bypass.

## CONTEXT LOCK
Research BASE Git 6a52aef21150e815692b83a4060a994f46d835f9. Git blob SHA-1 object IDs are NOT raw source byte SHA-256. Before any future Zcode coding, owner-approved 1.0 Scope/DoD, ADR-0030, integrated WORLD-04+DATA-03 code and all owner contracts, exact ABI/source file inventory and raw SHA-256 context lock are mandatory.

## Verified research PR #172 and same-WO correction receipts
Research BASE 6a52aef21150e815692b83a4060a994f46d835f9, initial HEAD 2735772a2faa3830383ace314ae1533c7f2cc7da failed [Docs Validation #43640529671](https://github.com/KayzenRoot/stormline/actions/runs/43640529671) due escaped Markdown in 4 new docs. Same WO/PR Correction Delta removed escapes and documented failed CI. Audited final HEAD b2a1bb6c46ddf0e63ca2eebfa9c336adc305ab57 passed [Docs Validation #43640639332](https://github.com/KayzenRoot/stormline/actions/runs/43640639332) on exact final HEAD plus Socket Security/SonarCloud SUCCESS, 11 docs-only files, objective pt-BR audit APPROVED doc-only with no known HIGH/CRITICAL. Normal squash merged main 36e71c4e582da9086f19065993fe2165dfe7f656, Git readback. Separate same-WO checkpoint PR requires its own exact final HEAD CI/audit/merge/readback. 160 future golden/runtime/CPU/WASM/security/manual editing tests NOT EXECUTED, ADR-0030 PROPOSED and future #45 OPEN/BLOCKED.
