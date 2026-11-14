# Evidence Bundle — NLE-P00-WO-002-GFX-01

**Date:** 2026-11-14 | **Research issue:** #123 | **Future code issue:** #29 BLOCKED.
**State:** IN PROGRESS, research docs only. No C++ graphics code, GPU backend, Vulkan/D3D/Metal/SDL GPU SDK, shader compiler, benchmark or deployment.
**BASE main:** `36f08368be2c1d1cdd8aa7bd553f4fed7d610d56`; research branch `docs/NLE-P00-WO-002-GFX-01-rhi-research`. LOW research risk; future ELEVATED device/driver/resource/sync safety.

## Baseline canonical Context Lock
These are exact **Git blob object hashes, NOT SHA-256 of file content**:
- `docs/11-checkpoint.md`: `d1eeee81ebf6cfc6a33d84a0926e7fcf348860db`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `48e3ad640c67a829e2a7098751c544fa0b18a846`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/queue/work-orders/GFX-01.md`: `22025aa422ce38394a23508ad5ece122b0120e3b`
- `docs/queue/implementation-registry.json`: `036b8f3c20a8ecd2ba8ec1192d48efb0fed6fbff`
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`

An updated Checkpoint, ADR, Scope/DoD/Architecture or critical source makes old context STALE. Implementation must pin new BASE and real SHA-256 bytes, not these Git object IDs.

## Authored deliverables
- RHI lifecycle/feature tiers, backend selection boundaries, generational resource handles, queue/sync, swapchain/resize and device-lost/restart-safe recovery.
- Technology matrix comparing native Vulkan/Metal/D3D12, SDL GPU, Dawn/wgpu-native, bgfx, WebGPU and WebGL2 with Khronos 2026 MoltenVK deprecation guidance.
- ADR-0014 remains PROPOSED, no runtime stack selected.
- Typed semantic API covers device/adapters/resources/sync/presentation/errors, safe Editor/CLI/MCP scoped read-only operations.
- 28 future scenarios RHI-001..028, security/pixel golden/VRAM/benchmarks, test and platform matrix.
- Research WO, future blocked packet #29, architecture/backlog links, SCGF optional prove-or-drop hypothesis.

## Scope and risk review
Documented barriers: GPU driver is a privileged/complex boundary; shader binaries can be hostile; resource release requires fence-safe ownership, device lost must invalidate handles. Future physical Windows/Linux/macOS Apple Silicon GPU and Web browser tests required; unsupported WebGPU and Mac Intel constraints not hidden. Cross-platform SDK/code license and SBOM remain open gates. No hardware performance claim, no shaders, no GFX-03 graph code. All 80 implementation WOs remain BLOCKED, executor_ready=false.

## Tests / audit evidence (fill from real GitHub results)
- Exact final research HEAD docs-validation: PENDING.
- PR/diff/CI/audit: PENDING. Cannot declare success until observed.
- RHI-001..028, native compiler/GPU real hardware, perf p50/p95/p99, device loss, race/fuzz, Web browser, Apple Silicon: **NOT RUN**.
- Normal merge SHA/main readback and same-WO checkpoint reconciliation: PENDING.

## Proposed Checkpoint Delta (not yet approved)
After docs-only PR CI+review APPROVED and squash merge/readback, record GFX-01 research as RESEARCH_DOCUMENTED_ADR_PROPOSED; ADR-0014 remains PROPOSED, #29/80 future coding WOs all BLOCKED/executor_ready=false, no code. Checkpoint reconciliation happens in separate audited docs PR for this **same WO** before researching GFX-02.
