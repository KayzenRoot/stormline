# GFX-01 INTERNAL_ONLY RHI Governance Contract v0 (NLE-PRPLAN-GFX-01-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `c87e9f7`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md), [ADR-0014](../adr/0014-gfx-01-rhi-backends.md) planning-only. **WO:** [NLE-PRPLAN-GFX-01-01](../work-orders/NLE-PRPLAN-GFX-01-01.md).

## Objective

Record ownership, backend/trust boundaries, release/risk classes and gates before GFX-01 implementation. No native GPU backend, shader compiler, swapchain, rendering, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `CORE-01` and `CORE-02`; neither is module-qualified.
- GFX-01 owns the logical RHI contract: adapters, devices/generations, queues, resources, barriers and feature tiers.
- CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-05 math/IDs; CORE-06 diagnostics; DATA-05 bundles; GFX-02 shaders; GFX-03 render graph.
- No Vulkan/D3D12/Metal/SDL GPU/Dawn/wgpu/bgfx dependency or SDK is selected.

## Policy invariants

1. **No native GPU in the first sequence.** Null/reference backend only; no device creation, swapchain, rendering or presentation.
2. **Opaque handles.** Resource handles carry device generation and slot generation; no raw GPU pointer.
3. **Feature negotiation.** Required features/limits are explicit; unsupported fails closed.
4. **Bounded.** Adapters, queues, resources, capabilities and barriers are fixed.
5. **Generation fencing.** Device loss/recovery invalidates old handles; stale access fails.
6. **Descriptor validation.** Buffer/texture sizes, formats and ranges are checked.
7. **No rendering claim.** No shader, pipeline, draw, present, timing or frame claim.
8. **No ambient GPU.** No driver command, native handle or MCP GPU access.
9. **Release boundary.** Internal-only; no rendering, performance, ABI or release claim.

## First-slice scope (future, blocked)

- `-03` adapters/devices/lifecycle/generation.
- `-04` queue roles and submit accounting.
- `-05` buffers and resource handles.
- `-06` textures and format validation.
- `-07` synchronization barriers/fences.
- `-08` feature tiers/capability negotiation.
- `-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX01_01_APPROVED_GOVERNANCE_ONLY`: **634 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 91 `COMPLETED`, 23 approved gates**.
- `GFX-01-01` becomes `APPROVED_GOVERNANCE`; `GFX-01-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/driver/API selection, shader/render/swapchain code, host GPU pointer, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
