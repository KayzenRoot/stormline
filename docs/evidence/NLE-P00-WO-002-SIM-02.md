# Evidence Bundle — NLE-P00-WO-002-SIM-02 Physics 3D Research

**Status: DRAFT RESEARCH PR, EXACT FINAL HEAD CI/AUDIT PENDING | Research #177 | Code #47 OPEN/BLOCKED**  
**BASE main 6099128ead915e010ef252f57cd880f441303d59 | branch docs/NLE-P00-WO-002-SIM-02-physics-3d-research.** No C++/WASM/Rust backend, vendor SDK, native/Web/headless simulator, compiler, physics scene, collision benchmark, actual GPU/CPU memory measurements or sample scene exists for this increment.

## Canonical source and dependencies
- Verified Git source priority checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/blocked future #47 packet. SIM-01 research #174 PR #175 and checkpoint PR #176 merged/read back at BASE main. BASE registry **28/80 research documented**, **52 pending including historic CORE-04**, **all 80 coding work orders BLOCKED/executor_ready=false**, zero engine runtime.
- Mandatory future coding prerequisites WORLD-02 and CORE-03 CODE not implemented; WORLD-01/03/04, DATA-03/04/05 and GFX/NET owner contracts remain documentary. Code issue #47 OPEN/BLOCKED, ADR-0032 PROPOSED/approved_adr=null/release UNDECIDED.
- Official source/rights research: Jolt MIT C++ vendor docs 5.6, CROSS_PLATFORM_DETERMINISTIC build conditioned on same source/defines/API order and warnings on parallel broadphase query reproducibility, dynamic triangle mesh vs static mesh/heightfield limitations. PhysX5 CPU BSD-3-Clause, CUDA GPU optional specialized Win/Linux platform and binary license gate, Rapier3D Rust Apache-2.0 with optional enhanced determinism, Bullet core zlib Extras/third party separately licensed. **No packages/binaries/vendor sample art imported or adopted.**
- Original proposed stable PhysicsWorld3D+WorldEpoch, Body/Shape/Constraint handles and ECS EntityGuid mapping, CORE-06 fixed tick/CORE-03 jobs and allocation, contact poststep immutable buffer, exact narrowphase refinement, WORLD-02 prefab source and DATA-04 journal, WORLD-03/04/05 staged static collider and PHYS ready ACK, no GPU requirement. S3P optional PROVE-OR-DROP, no performance claim.

## Honest research scope and checks
- Intended exactly 11 docs-only files: 8 new architecture, matrix, ADR-0032, versioned semantic API, **170 future NOT EXECUTED scenarios**, reproducible native/Web/headless/CPU p95/p99 benchmark protocol, research WO and Evidence Bundle; 3 additive links in Architecture/Backlog/blocked future coding #47 packet. **No checkpoint or implementation-registry changed in research PR.**
- Research PR, final audited HEAD exact Docs Validation and security receipts: PENDING.
- Objective pt-BR audit, normal squash/main readback: PENDING.
- **All 170 cases FUTURE / NOT EXECUTED**. No C++ library/CPU headless/native/WASM build, physics contacts, joints, sweeps, stream terrain/PHYS ACK, memory/TSan/ASan, determinism/cross-platform replay, snapshot/rollback or actual benchmark. No 60fps, perfect CCD, portable GPU or engine superiority claims.
- Docs risk LOW; future ELEVATED body/constraint lifetime/collision rights, source integrity, multithreaded callbacks and worker shutdown, physics gameplay authority and large-world precision.

## Proposed Checkpoint Delta NOT APPLIED
After research PR final exact HEAD Docs Validation and any Socket/SonarCloud SUCCESS, objective pt-BR Scope/Architecture/licensing/security audit APPROVED no known HIGH/CRITICAL, normal squash/main readback, open separate **same WO checkpoint PR** changing **only SIM-02.research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, update Checkpoint/Backlog/WO/Evidence with observed receipts. All 80 coding packets remain BLOCKED/executor_ready=false/approved_adr=null/release UNDECIDED, future #47 OPEN, ADR-0032 PROPOSED and historic CORE-04 pending. Require checkpoint own exact final HEAD CI/audit/normal squash/main readback, then close research #177 and begin SIM-03 research only.
