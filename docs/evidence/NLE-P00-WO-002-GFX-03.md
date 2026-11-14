# Evidence Bundle — NLE-P00-WO-002-GFX-03

**Date:** 2026-11-14 | **Research issue:** #129 | **Future code issue:** #31 BLOCKED
**Evidence state:** RESEARCH IN PROGRESS, DOCUMENTS ONLY. No C++ graph, GPU heap, shaders, SDK, benchmarks, driver tests, render pass or deployment.
**BASE main:** `e76d561d98dd4192d8bae1fb66cab09e194fbc70`; **research branch:** `docs/NLE-P00-WO-002-GFX-03-rendergraph-research`.
**Risk:** LOW docs, future ELEVATED GPU memory alias, async sync and recovery.

## Canonical Context Lock
Critical fingerprint values below are **Git blob object IDs, NOT SHA-256 hashes of file contents**. At future actual implementation, re-read committed repo and compute SHA-256 hashes of critical source files; STALE if checkpoint/Scope/DoD/ADR/Architecture changes:
- `docs/11-checkpoint.md`: `f2296d1f0e105465bc041c1b9f32e8c1c36929b6`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `c5a84e29d49bdc80c4b4c83eb60536f4244e2fe2`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/queue/work-orders/GFX-03.md`: `1da40a11b80fd6860c75e4d587162807bf4074e2`
- `docs/queue/implementation-registry.json`: `d2aa73df51210e9866cef68a30f37177c7c5eef1`
- `docs/contracts/gfx-01-rhi-api.md`: `822cbd118df75b4acf033443d5f75842d1344ae7`
- `docs/contracts/gfx-02-shader-api.md`: `2e7e14f5f598d25229582683ea4a9d0d531e8580`
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`

## Authored and explicitly NOT implemented
- Owned declarative Pass/Resource DAG, hazards, deterministic graph compilation, explicit imported states and temporal history.
- Lifetime plan cross-frame and per GPU fence, optional proven transient memory alias, serial/no-alias fallback, safe VRAM pressure policy for UMA/discrete/Web, generational recovery.
- Candidate Vulkan sync2, D3D12 legacy/enhanced optional, native Metal MTLHeap tracked/untracked/hazards, WebGPU usage scopes. GPUOpen VMA/D3D12MA MIT candidate with exact-tag SBOM before use; no package selected/vendored.
- Typed API with secure read-only Editor/CLI/MCP inspect and preview; no native GPU commands/driver input from LLM.
- Architecture, technology matrix, ADR-0016 PROPOSED, 34 future RGP scenarios, research WO and Source Pack/future #31 blocked packet links.
- SAFG experimental prove-or-drop, no claimed extra frames/sec, RAM saving or VRAM allocator performance.

## Actual tests/evidence log (must be updated from real runs)
- GitHub docs-validation on final research HEAD: PENDING.
- PR diff, CI and objective pt-BR audit: PENDING.
- RGP-001..034, real C++/GPU builds, native Windows/Linux/macOS/Web, fuzz GPU, driver validation, CPU/GPU/VRAM p95/p99, SAFG benchmarks: **NOT RUN**.
- Squash merge SHA and main readback / same-WO checkpoint reconciliation: PENDING.

## Risks and future gates
Unsafe GPU memory aliasing can corrupt output and crash drivers. CPU DAG ordering is insufficient proof of GPU completion across queues and epochs. GFX-01/CORE-03 code not implemented, RHI feature tiers remain research proposed, VMA/D3D12MA version/driver hardware/SBOM and physical VRAM budgets not locked; no remote telemetry or GPU SDK installed. All 80 implementation packets stay BLOCKED, none executor_ready.

## Proposed Checkpoint Delta (not active until objective audit)
After research docs CI and audit APPROVED and research squash merge read back, promote only GFX-03.research_status=RESEARCH_DOCUMENTED_ADR_PROPOSED via a separate same-WO checkpoint reconciliation PR. Leave ADR-0016 PROPOSED, future code #31 / 80 WOs BLOCKED, executor_ready=false. Next GFX-04 research only after checkpoint audited/merged.
