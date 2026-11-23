# GFX-03 INTERNAL_ONLY Render Graph Governance Contract v0 (NLE-PRPLAN-GFX-03-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `4abac08`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md), [ADR-0016](../adr/0016-gfx-03-render-graph-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-03-01](../work-orders/NLE-PRPLAN-GFX-03-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-03 implementation. No native graphics API, GPU allocator, driver synchronization, command submission, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `CORE-03`; neither is module-qualified.
- GFX-03 owns the logical render graph: pass/resource declarations, hazard DAG, logical sync transitions, transient lifetime/alias planning and VRAM admission.
- GFX-01 RHI capabilities; CORE-03 CPU scheduling; CORE-02 CPU allocation; GFX-02 reflection; DATA-02/05 assets; GFX-04+ renderer algorithms; PLAT-03 browser policy.
- No Vulkan/D3D12/Metal/WebGPU, VMA/D3D12MA, native allocator, swapchain or rendering dependency is selected.

## Policy invariants

1. **No native GPU.** Graph compilation only; no command recording, submission, fence/timeline, swapchain, present or rendering.
2. **Declarative and bounded.** Fixed passes/resources/uses/edges/barriers/aliases and checked arithmetic.
3. **Fail closed.** Duplicate IDs, unknown references, ambiguous writers, uninitialized reads, cycles, incompatible aliases and budget overflow are typed errors.
4. **Deterministic.** Stable topological tie-break, sorted edges/groups and repeatable plans.
5. **No culling of observable passes.** Side-effect passes remain in the schedule.
6. **Conservative aliasing.** Only transient, equal-size/alignment, strictly disjoint lifetimes; no native heap claim.
7. **Budget honesty.** Unknown budget fails closed; estimates are not measured VRAM.
8. **No execution evidence.** A plan is not a submit, completion or pixel result.
9. **Release boundary.** `INTERNAL_ONLY`; no ABI, performance, security, release or production claim.

## First-slice scope (future, blocked)

- `-03` pass/resource definition validation.
- `-04` hazard dependency DAG, cycle detection and stable order.
- `-05` logical synchronization transitions.
- `-06` transient lifetimes and conservative alias groups.
- `-07` VRAM budget admission.
- `-08` qualification and `-09` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX03_01_APPROVED_GOVERNANCE_ONLY`: **615 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 106 `COMPLETED`, 27 approved gates**.
- `GFX-03-01` becomes `APPROVED_GOVERNANCE`; `GFX-03-02`..`-09` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/allocator/API selection, command submission, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
