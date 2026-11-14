# Research Work Order — NLE-P00-WO-002-WORLD-03

**2026-11-14 | Research issue #165 | Future implementation #43 OPEN/BLOCKED**  
**State:** RESEARCH IN PROGRESS / DOCS ONLY; **ADR-0028 PROPOSED**; **BASE main:** e73765d3884fac6bd925a19a016792718e240050 (WORLD-02 research PR #163 and checkpoint PR #164 merged).  
**Risk:** LOW docs; future ELEVATED world-spatial consistency, I/O safety, async publication, origin rebase, GPU/PHYS/NET synchronization and memory/permissions.

## OBJECTIVE
Specify first-class world-spatial interest queries, coarse stable cell partition, optional fast per-cell query index, predictive bounded streaming requests and source-authoritative staged/validated residency lifecycle, headless+Windows/Linux/macOS/Web. Guaranteed real no-stall traversal is **NOT ACHIEVED**: the catalog acceptance "Percorrer mapa amplo sem stalls além do orçamento definido" requires approved numeric limits and independent native/Web/IO/GPU/PHYS benchmark evidence. Prepare future Zcode executor with scoped architecture and exact gates, no research decisions delegated to code implementation.

## CONTEXT
Stormline P00 planning docs only. Latest checkpoint 24/80 module research documented, 56 pending including historical CORE-04 research gap, 80 coding WOs BLOCKED/executor_ready=false, no engine code or integrated predecessor runtimes. Future #43 mandatory dependencies WORLD-02 and DATA-05 CODE both unimplemented; research #165 separate docs-only increment. Visual quality 2D/2.5D/3D, premium large worlds, optional async data sources and AI-native Editor/CLI/MCP at public repository R$0 mandatory CI.

## SCOPE
- Coarse sparse grid 2D/3D `CellId` global signed coordinates, overlap owner/dedup, hierarchical levels and dynamic per-active-cell BVH/loose octree/R-tree optional, exact/approx bounded query with `MAY_BE_INCOMPLETE` when cells not resident; PHYS broadphase and GFX-04 culling remain different owners.
- Multi-owner interest union, physics/AI/quest/server pins, camera/audio/editor priority, velocity lookahead, boundary hysteresis, fairness and teleport/cancellation generations. NET alone authoritative replication, world/asset permission separate.
- DATA-05 asset I/O/cook/hash/decompress/cache and CORE scheduler job/tick owners, WORLD-01 generational EntityGuid/Handle and WORLD-02 scene graph references, staged/validated CPU/GPU optional and PHYS owner ACK before snapshot ACTIVE, safe backpressure/retry/failover/eviction after pin/fence released.
- CORE-05 global-to-relative origins, precision and shift epochs, PHYS/GFX/NET owner ACK, large/negative coordinates, headless and multi-view; no name/pointer-based persistent IDs.
- Technology+license matrix for sparse grid, loose BVH/trees, Boost.Geometry R-tree (BSL-1.0), libspatialindex >=1.8 MIT (old LGPL), Unreal World Partition proprietary reference, Godot 4.6 HLOD/large-world MIT reference, Unity Addressables proprietary reference, OGC 3D Tiles 1.1 public optional spec and Zstandard BSD DATA-05-owned candidate. No vendors adopted or art/code installed.
- ADR-0028 PROPOSED, versioned semantic API, **132 FUTURE NOT EXECUTED** test matrix, original stress/traversal benchmark with actual full-frame+physics p95/p99 and memory receipts to be measured LATER, optional SIP PROVE-OR-DROP, this WO/Evidence Bundle and 3 additive Architecture/Backlog/blocked packet links.
- Initial 11-docs-only research PR exact-final-HEAD CI/scope+security+license pt-BR audit/normal squash and main readback, then **separate same-WO checkpoint PR** reconciling research status only for WORLD-03 with independent exact HEAD CI/audit/readback, close research #165 only after approvals.

## OUT OF SCOPE
No C++ source/SDK, stream/mesh loader, actual terrain world, network game, Editor GUI, GPU/PHYS/AI simulation, I/O test, benchmark, visual FPS/zero-stall quality claim, shipping asset or selected hardware, Unity/Unreal proprietary copied code, arbitrary external fetch, vendor zstd or Boost runtime integration, WORLD-04 research before checkpoint, correction of historical CORE-04 unrelated research, paid CI/CodeRabbit, mandatory human external review or force/bypass.

## FILES / SOURCES TO READ
Priority Checkpoint `docs/11-checkpoint.md` > Decisions Ledger/approved ADR `docs/10-decisions-ledger.md` > Scope `docs/03-scope.md` > DoD `docs/09-definition-of-done.md` > Architecture `docs/04-architecture.md` > Requirements `docs/02-requirements.md`; then AGENTS, docs/product/module-catalog.md, implementation registry, blocked future packet WORLD-03, WORLD-01/02 research contracts and ADRs, DATA-02/04/05, CORE-05/06, GFX-03/04/07, TWO-02/04, PHYS/NET/AUDIO known source boundaries, exact Git/main/issue. Public upstream docs in technology matrix, with independent license verification. Future real C++ filenames TBD after owner DoD, never fabricated.

## REQUIREMENTS
GOV-001..005, CAP-001/003/004/006/008/009/010/011/012/013/014/016 and NFR-001..005 where catalog/source applies. Future 1.0 performance and supported scene/hardware target, p99 frame+physics tick budget, memory/IO and coordinate precision error thresholds currently UNDECIDED.

## ARCHITECTURE RULES
WORLD-03 owns candidate spatial metadata and cell/interest planning, not GFX mesh culling/GPU allocation, PHYS collision broadphase, NET authority, DATA-05 real I/O/decode/cache or DATA-04 durable scene writer. WORLD-01 handles lifecycle, WORLD-02 scene instance source, CORE fixed jobs and math. Never report exact nonresident query complete, publish partially loaded critical collider, resurrect stale cancelled task, evict required physics pin, use local float as persistent global coordinate, falsely claim async means no main tick stalls.

## CONSTRAINTS
LOW research, ELEVATED future implementation. No executable test, GPU/asset license installation or data benchmark. 132 future cases **NOT EXECUTED**, all 80 future implementation WOs remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` and `executor_ready=false`, ADR-0028 PROPOSED, approved_adr=null, release_class UNDECIDED, #43 coding OPEN/BLOCKED. Historical CORE-04 research status not modified.

## ACCEPTANCE CRITERIA
- [ ] Global signed spatial cell IDs and 2D/3D policy, large cross-cell owner/ref dedup, checked negative/overflow coordinates; index candidates versus reference, explicit exact/nonresident completeness and no duplicate collision authority.
- [ ] Typed scoped multi-owner interest, mission/PHYS/NET pins, camera/AI/audio, hysteresis, priority/fairness, bounded predictive request quotas and teleport generation cancellation.
- [ ] Explicit staged DATA-05 asset request with source hashes/revision and WORLD-01+PHYS/GFX owner ACKs, safe tick publication and rollback/stale token/fence/lease eviction/critical loading barrier. HEADLESS no GPU dependency.
- [ ] Global/local origin precision and epoch with CORE-05/PHYS/GFX/NET coordinated shift acknowledgements; no persisted transform/EntityGuid corruption.
- [ ] Spatial candidate libraries and provenance clearly document Boost BSL-1.0, libspatialindex >=1.8 MIT / old LGPL, Godot MIT, Unreal/Unity proprietary reference, OGC 3D Tiles spec and Zstd BSD via DATA-05, no dependencies installed.
- [ ] Versioned typed API, **132 FUTURE NOT EXECUTED** tests, original traversal+full-frame+PHYS p95/p99/memory benchmark, SIP optional PROVE-OR-DROP; no unmeasured zero-stall/60FPS claim.
- [ ] Initial research PR exactly 11 docs only (8 new and 3 links), exact-final-HEAD Docs Validation SUCCESS and available Socket/SonarCloud, pt-BR objective audit no known HIGH/CRITICAL, normal squash and main readback.
- [ ] Separate same-WO checkpoint PR changes only `WORLD-03.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, all 80 code packets BLOCKED, issue #43 OPEN, ADR-0028 PROPOSED and CORE-04 gap pending; CI/audit/normal squash/readback before next WORLD-04 research.

## TESTS
Now only GitHub Actions free `docs-validation` exact final HEAD, optional available Socket/SonarCloud. Local when checkout available `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py WORLD-03` expected reject blocked. 132 CPU/GPU/PHYS/NET/IO/origin/stream/ASan/Web/native benchmarks are FUTURE **NOT RUN**.

## DELIVERABLES
8 new docs architecture/technology-license matrix/ADR-0028/API/test matrix/benchmark/WO/Evidence; 3 additive docs Architecture/Backlog/blocked WORLD-03 packet; issue #165; research PR with CI/audit and same-WO separate checkpoint PR with its own audit+readback. No game software or deployed engine.

## REVIEW FORMAT
pt-BR objective report BASE/HEAD and source fingerprints, diff file list, exact-head CI/security, ADR/Scope/DoD boundary, licenses, 132 unexecuted future tests, unknowns and security risks, Checkpoint Delta, verdict APPROVED/CORRECTION REQUIRED/BLOCKED. Correction Delta only same WO/PR and no known HIGH/CRITICAL accepted.

## STOP CONDITION
If main/Scope/DoD/ADR changes, mark STALE and re-lock; failed CI, incorrect rights, unsafe cell/authority semantics, invented runtime claim, unrelated code/asset or HIGH/CRITICAL => CORRECTION REQUIRED or BLOCKED, no WORLD-04 progress before resolution. Never force-push, bypass, require paid services or reviewer outside solo objective audit.

## CONTEXT LOCK
BASE Git e73765d3884fac6bd925a19a016792718e240050; Git SHA-1 blob IDs recorded separately are NOT raw file SHA-256. Coding later requires actual source SHA-256 from bytes, integrated WORLD-02/DATA-05 and other owner dependencies, approved Scope/ADR/1.0 DoD and code-specific proof.
