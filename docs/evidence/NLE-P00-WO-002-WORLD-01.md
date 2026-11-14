# Evidence Bundle — NLE-P00-WO-002-WORLD-01 ECS Research

**Status:** RESEARCH DOCUMENTATION APPROVED/MERGED; CHECKPOINT PR PENDING INDEPENDENT EXACT-HEAD CI/AUDIT | Research #159 | Future code #41 OPEN/BLOCKED.  
**BASE main:** 7a9385aa739edec145a5c417ca7a2b45acda0766. **Branch:** docs/NLE-P00-WO-002-WORLD-01-ecs-research. No installed ECS binary/tool, C++ source implementation, headless running world, test harness, performance benchmark or compiled reflection delivered.

## Canonical source check
- Verified Git BASE Source Hierarchy: Checkpoint > Decisions/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS, catalog/registry/blocked future WO. TWO-04 research #156 PR #157 and checkpoint #158 merged. **22/80** research statuses documented, 58 pending including **CORE-04 research gap**; all 80 coding WOs BLOCKED and executor_ready=false, #41 OPEN/BLOCKED.
- Dependencies CORE-05 and DATA-04 are research-only and future code not integrated; WORLD-02 hierarchy/prefab and WORLD-03 spatial streaming to be researched later. No foreign world/physics/network authority created by this design.
- Research refs official Flecs MIT C++/archetype/relationships/defer commands, EnTT C++ sparse-set and versioned handle with MIT candidate to pin, Bevy ECS MIT OR Apache-2 table/sparse+change references, Unity Entities proprietary structural sync/command buffers, WG21 C++26 P2996R13 accepted in working draft with compiler rollout gate. All are technical/license **references**, no runtime/library/source copied or installed.
- Original proposed safe entity Guid vs runtime world-instance/slot/generation, generation retirement on wrap, typed schema/source-generated baseline, queries/borrows/epoch fences, deterministic deferred structural command transactions, DATA-04 persistence and AI-native edit rights. STLG optional PROVE-OR-DROP, no novelty/speed claim.

## Canonical Git fingerprints at BASE (Git blob SHA-1 OIDs, NOT raw file SHA-256)
- `docs/11-checkpoint.md`: `745173adbd2ec58336d4901cfce7139ab86a98c7`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `3253e2f493e1a39a3a3c93e8be9bfea3336a6e46`
- `docs/queue/work-orders/WORLD-01.md`: `4d312e110cd4adacc6858f8c1dea7ddd898f6799`
These are Git object hashes at research baseline, NOT SHA-256 of raw file bytes. Future implementation Context Lock must compute true SHA-256 and rebase when canonical sources change.

## Research PR file inventory and truth
- Expected 11 research-only docs: 8 new architecture/matrix/ADR-0026/API/test-matrix/benchmark/research WO/Evidence; 3 additive docs Architecture/Backlog/blocked WORLD-01 packet. **NO Checkpoint or implementation-registry modification in initial research PR**.
- [Research PR #160](https://github.com/KayzenRoot/stormline/pull/160), initial head `a35841a4d8091ca724edaa4dc3548356521cd40e` and [Docs Validation #43634445055](https://github.com/KayzenRoot/stormline/actions/runs/43634445055) **SUCCESS on initial exact HEAD**; initial Socket Security Project Report SUCCESS. This evidence update changes HEAD and demands **new exact-final-HEAD CI** before approval/merge.
- [Research PR #160](https://github.com/KayzenRoot/stormline/pull/160), BASE 7a9385aa739edec145a5c417ca7a2b45acda0766, audited final HEAD af5152a74fe57558171fd4adf67fab20b11346f0, [Docs Validation #43634492193](https://github.com/KayzenRoot/stormline/actions/runs/43634492193) SUCCESS on exact final HEAD with Socket Security and SonarCloud SUCCESS, pt-BR objective audit APPROVED documentation-only, 11 scoped files, no known HIGH/CRITICAL. Normal squash merged main 33de3993eedaf7c4b07cdbda092c2268296bed9d. Checkpoint awaits its own PR/CI/audit.
- **117 tests FUTURE / NOT EXECUTED**: no real generational handle code, memory/TSan/ASan/UBSan, entity destruction, data reserialize, WASM build, CPU p95/p99, archetype/sparse comparative benchmark or MCP security verification. No “millions of entities supported” declaration.
- Risk LOW current docs; future ELEVATED ABA/after-free, untrusted schema migrations, concurrent access, persistent scene integrity and possible C++ plugin code. ADR-0026 PROPOSED, release class UNDECIDED and approved_adr=null.

## Proposed Checkpoint Delta NOT APPLIED
After objective research PR audit/merge and its exact-head SUCCESS, open a **separate same-WO** checkpoint PR: change ONLY WORLD-01.research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED; update Checkpoint/Backlog/WO/EB to observed true evidence; preserve 80 blocked code WOs, zero executor_ready, approved_adr=null, release class UNDECIDED, #41 OPEN. Historical CORE-04 pending remains explicit; next WORLD-02 only after checkpoint PR passes independent exact-final-HEAD CI/audit/squash/readback.

## Proposed exact checkpoint delta in separate same-WO PR
Only WORLD-01.research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED, tally 23/80 documented, 57 pending including CORE-04 historical gap. Preserve all 80 code packets work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null and release_class=UNDECIDED, #41 coding OPEN. ADR-0026 PROPOSED. All 117 future ECS/identity/concurrency/CPU/ASan/TSan tests NOT EXECUTED; no runtime ECS implementation. Require independent checkpoint exact final-head Docs Validation/audit/squash/main readback before WORLD-02.
