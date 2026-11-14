# Evidence Bundle — NLE-P00-WO-002-WORLD-01 ECS Research

**Status:** DRAFT / RESEARCH PR CI/AUDIT PENDING | Research #159 | Future code #41 OPEN/BLOCKED.  
**BASE main:** 7a9385aa739edec145a5c417ca7a2b45acda0766. **Branch:** docs/NLE-P00-WO-002-WORLD-01-ecs-research. No installed ECS binary/tool, C++ source implementation, headless running world, test harness, performance benchmark or compiled reflection delivered.

## Canonical source check
- Verified Git BASE Source Hierarchy: Checkpoint > Decisions/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS, catalog/registry/blocked future WO. TWO-04 research #156 PR #157 and checkpoint #158 merged. **22/80** research statuses documented, 58 pending including **CORE-04 research gap**; all 80 coding WOs BLOCKED and executor_ready=false, #41 OPEN/BLOCKED.
- Dependencies CORE-05 and DATA-04 are research-only and future code not integrated; WORLD-02 hierarchy/prefab and WORLD-03 spatial streaming to be researched later. No foreign world/physics/network authority created by this design.
- Research refs official Flecs MIT C++/archetype/relationships/defer commands, EnTT C++ sparse-set and versioned handle with MIT candidate to pin, Bevy ECS MIT OR Apache-2 table/sparse+change references, Unity Entities proprietary structural sync/command buffers, WG21 C++26 P2996R13 accepted in working draft with compiler rollout gate. All are technical/license **references**, no runtime/library/source copied or installed.
- Original proposed safe entity Guid vs runtime world-instance/slot/generation, generation retirement on wrap, typed schema/source-generated baseline, queries/borrows/epoch fences, deterministic deferred structural command transactions, DATA-04 persistence and AI-native edit rights. STLG optional PROVE-OR-DROP, no novelty/speed claim.

## Research PR file inventory and truth
- Expected 11 research-only docs: 8 new architecture/matrix/ADR-0026/API/test-matrix/benchmark/research WO/Evidence; 3 additive docs Architecture/Backlog/blocked WORLD-01 packet. **NO Checkpoint or implementation-registry modification in initial research PR**.
- PR number, final HEAD, exact-head Docs Validation and Socket/SonarCloud results: **PENDING**.
- Objective pt-BR documentary audit/merge SHA/main readback: **PENDING**.
- **117 tests FUTURE / NOT EXECUTED**: no real generational handle code, memory/TSan/ASan/UBSan, entity destruction, data reserialize, WASM build, CPU p95/p99, archetype/sparse comparative benchmark or MCP security verification. No “millions of entities supported” declaration.
- Risk LOW current docs; future ELEVATED ABA/after-free, untrusted schema migrations, concurrent access, persistent scene integrity and possible C++ plugin code. ADR-0026 PROPOSED, release class UNDECIDED and approved_adr=null.

## Proposed Checkpoint Delta NOT APPLIED
After objective research PR audit/merge and its exact-head SUCCESS, open a **separate same-WO** checkpoint PR: change ONLY WORLD-01.research_status from RESEARCH_PENDING to RESEARCH_DOCUMENTED_ADR_PROPOSED; update Checkpoint/Backlog/WO/EB to observed true evidence; preserve 80 blocked code WOs, zero executor_ready, approved_adr=null, release class UNDECIDED, #41 OPEN. Historical CORE-04 pending remains explicit; next WORLD-02 only after checkpoint PR passes independent exact-final-HEAD CI/audit/squash/readback.
