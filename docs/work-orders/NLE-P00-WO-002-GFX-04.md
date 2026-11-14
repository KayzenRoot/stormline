# Research Work Order — NLE-P00-WO-002-GFX-04

**Research issue:** #132 | **Future code issue:** #32 BLOCKED | **Date:** 2026-11-14  
**State:** APPROVED / MERGED FOR RESEARCH DOCS ONLY (PR #133) | **ADR-0017:** PROPOSED / NO ENGINE CODE  
**Context Lock BASE main:** `563f5dff168a688f5d03d959685024dd374de4c9` (GFX-03 research/checkpoint #130/#131 audited/merged).
**Risk:** LOW docs, future ELEVATED visibility correctness, geometry streaming and GPU indirect memory.

## OBJECTIVE
Plan innovative original but safe Geometry, Occlusion & LOD for Stormline, covering native Windows/Linux/macOS and Web, 2D/2.5D/3D, massive geometry with measured quality/perf, instancing, bounds, frustum/Hi-Z culling, HLOD/cluster meshlets, bounded streaming, foliage, fallback and scoped AI-native tools. Author complete contracts/technology/test documentation to minimize future Zcode architecture decisions, no code.

## CONTEXT
Source Pack canonicity, solo PR/CI/audit, no public MVP before owner-approved DoD, R$0 mandatory CI for public repository. GFX-03 and DATA-05 researches approved/documented but **not implemented**, so future implementation packet #32 and all 80 WOs remain BLOCKED/`executor_ready=false`. GFX-01 native features and GFX-02 shader reflection still proposed.

## SCOPE
- Compare meshoptimizer MIT, glTF EXT_meshopt_compression/EXT_mesh_gpu_instancing ratified, gltfpack and experimental/draft KHR options only if officially validated; optional clusterlod.h hierarchy; independent Nanite public conceptual research without proprietary code use.
- Typed source-preserving GeometryAssetProfile, CookRecipe, Cluster/LOD manifest, Instance, conservative ViewVisibilityRequest, OcclusionEvidence, LODReceipt, StreamPlan/Receipt and GPU feature-tier DrawPlan.
- CPU frustum/spatial baseline, optional GPU Hi-Z conservative cull and indirect draws, Vulkan/D3D12 mesh shaders as OPTIONAL, Metal/WebGPU/WebGL2 fallback, robust bounds/animated/alpha foliage cases.
- HLOD fidelity, silhouette/UV/normal/skin/morph/interactive preservation, material classification, seam/crack handling and LOD hysteresis.
- DATA-05 verified chunk streaming and fallback residency, GFX-03 GPU upload/fences/VRAM, device-loss/camera-cut/resize/stream rollback, IO/RAM/VRAM budgets; no second packfile/allocator.
- Safe read-only Editor/CLI/MCP semantic API, visibility trace without private geometry leak, quality preview, security threat model.
- ADR-0017 PROPOSED, technology matrix, source links, 36 future GEO cases, evidence, blocked packet and canonical checkpoint delta; original SVCG hypothesis prove-or-drop.

## OUT OF SCOPE
No engine code, GPU mesh shaders/culling implementation, meshoptimizer install/cook, compiled native shader, new editor, procedural vegetation physics, renderer material/illumination, proprietary Nanite algorithms/assets, paid service, mandatory outside review, CodeRabbit, bypass, force push, app release or deployment. No 80-WO activation.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`; `AGENTS.md`, `docs/00-source-hierarchy.md`, catalog, registry, [GFX-04 blocked packet](../queue/work-orders/GFX-04.md), GFX-01/02/03 and DATA-02/03/05/CORE-05 contracts, exact official upstream meshoptimizer/Khronos/Vulkan/Apple/WebGPU/Epic documentation.

## REQUIREMENTS
GOV-001..005; CAP-001/002/004/005/008/009/010/011/012/013/014/016 and NFR-001..005; owner decisions NLE-D013..020 and GFX-04 catalog acceptance: **large scene with correct culling and measured cost** (future test). 1.0 min hardware/quality, release class and exact C++ source files/commands UNDECIDED.

## ARCHITECTURE RULES
- DATA-05 cooked asset/streaming and DATA-02 AssetId authoritative, GFX-03 render graph/sync/VRAM, GFX-01 RHI feature query, GFX-02 shader reflection, CORE-05 spatial conventions, CORE-03 CPU workers. No duplicate core services.
- Conservative visibility required (unknown/deformed/alpha material/temporal depth -> visible); LOD root/proxy or typed fail, not silent disappearance.
- All optional Hi-Z/indirect/mesh shaders gated on real native/Web GPU support and bounded draw counts, no cross-platform fantasy. Texture/material/skin correctness and rights preserved.
- Portability includes Mac Apple Silicon Metal, Windows/Linux, WebGPU+WebGL2 degraded, headless CPU validation not real GPU render.
- Editor/CLI/MCP scoped inspect/preview, no raw driver or arbitrary source binary/file/URL, quotas and no telemetry leaks.
- Exact library tags and rights/SBOM/provenance before code, real hardware frame-time/VRAM/scene tests before claims, SVCG prove-or-drop.

## CONSTRAINTS
P00 docs only; no C++/GPU/SDK/benchmark, no new paid service, no credential/CodeRabbit/required outside reviewer, no bypass/force-push. Stop if Source Pack STALE, license violations, unsupported GPU platform claims, risky false-negative occlusion, high/critical issue or CI fails.

## ACCEPTANCE CRITERIA
- [ ] Architecture explicitly describes baseline CPU frustum/LOD and optional Hi-Z/meshlet/indirect/mesh shader routes, conservative visibility, streaming and HLOD/foliage fidelity with OWNED module boundaries.
- [ ] Matrix records meshoptimizer MIT + experimental API gates, Khronos EXT ratification, KHR draft caveat, Unreal Nanite comparative/no-copy, actual Apple/Web/weak hardware limitations.
- [ ] ADR-0017 remains PROPOSED, typed contract and secure Editor/CLI/MCP, source ownership, fallback/residency, device/camera invalidation.
- [ ] At least 30 future tests (36 specified) across 2D/2.5D/3D, foliage transparency, camera FOV/teleport, stream loss, Win/Linux/macOS/Web/low end, geometry rights and measured cost.
- [ ] No C++ implementation/SDK, issue #32 and all 80 future code WOs BLOCKED/`executor_ready=false`.
- [ ] Free GitHub docs-validation PASS exact final HEAD, diff only docs, pt-BR objective audit no HIGH/CRITICAL, normal squash merge/readback.
- [ ] Separate same-WO checkpoint reconciliation docs PR must pass before starting GFX-05.

## TESTS
Current doc-only GitHub CI validates Source Pack/local links, 80 module dependency DAG, registry and blocked selector. GEO-001..036 tests are **NOT RUN**. No real GPU, Windows/Linux/macOS/Web, native build/codec/fuzz/benchmark.

## DELIVERABLES
`docs/architecture/gfx-04-geometry-visibility-lod.md`; `docs/research/gfx-04-geometry-technology-matrix.md`; `docs/adr/0017-gfx-04-visibility-geometry-policy.md`; `docs/contracts/gfx-04-geometry-api.md`; `docs/testing/gfx-04-acceptance-matrix.md`; this WO; Evidence Bundle; Architecture/Backlog/future GFX-04 packet links; research PR and checkpoint PR, objective audit and verified main.

## REVIEW FORMAT
Review in Portuguese (pt-BR): base/head SHA, scoped files, CI run and exact test statuses, architecture/requirements/license/rights/security/quality risks, remaining unproven compatibility, proposed checkpoint delta and `APPROVED / CORRECTION REQUIRED / BLOCKED`.

## STOP CONDITION
STALE checkpoint/approved ADR/Scope/DoD/Architecture, unsupported/deprecating codec terms, incorrect occlusion, unbounded GPU/stream, unsafe MCP pointer access, failed docs CI, known HIGH/CRITICAL, payment/bypass or code diff. Correct in SAME WO/PR and do not jump to GFX-05.

## CONTEXT LOCK
BASE `563f5dff168a688f5d03d959685024dd374de4c9`; source Git blob IDs in Evidence Bundle are **Git object IDs not file SHA-256**. New implementation requires fresh actual SHA-256 fingerprints, approval/ready gates, source paths, exact commands and implemented dependencies.

## CHECKPOINT
After research PR audited and squash merged+read back, reconcile Checkpoint/Backlog/this WO/Evidence/registry **only** `GFX-04.research_status` in separate docs-only audited PR of SAME WO. Keep ADR-0017 PROPOSED, GFX-04 code #32 and 80 WOs BLOCKED.
