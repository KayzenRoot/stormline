# GFX-04 INTERNAL_ONLY Geometry Pipeline Governance Contract v0 (NLE-PRPLAN-GFX-04-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `07c8a92`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md), [ADR-0017](../adr/0017-gfx-04-visibility-geometry-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-04-01](../work-orders/NLE-PRPLAN-GFX-04-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-04 implementation. No native GPU/mesh shader/indirect draw, mesh codec, streaming service, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `DATA-05`; neither is module-qualified.
- GFX-04 owns logical instance/culling/LOD/stream/vegetation/geometry budget planning.
- GFX-03 render graph; DATA-05 verified chunks; DATA-02 identities; GFX-01 RHI; CORE-05 coordinates; GFX-05 materials; world/vegetation placement modules.
- No Vulkan/D3D12/Metal/WebGPU, mesh/task shader, indirect draw, meshoptimizer, VMA/D3D12MA or streaming service is selected.

## Policy invariants

1. **No native GPU or mesh library.** Logical plans only; no command submission, rendering, decode or simplification.
2. **Conservative visibility.** Unknown bounds are visible; culling requires a fully outside conservative test.
3. **Bounded.** Instances/meshes/LODs/chunks/batches and arithmetic are fixed and checked.
4. **Fail closed.** Duplicate IDs, invalid bounds/camera, generation mismatch, cycles, invalid LOD chains and unverified chunks are typed errors.
5. **Verified chunks only.** Streaming requests reference caller-provided verified chunk metadata; no network or file access.
6. **Authored identity preserved.** Derived IDs are metadata; no AssetId rewrite.
7. **NO false-negative by construction in this sequence.** Overdraw is preferred to uncertain culling.
8. **No execution evidence.** A plan is not a draw, stream, render or hardware result.
9. **Release boundary.** `INTERNAL_ONLY`; no ABI, performance, security, release or production claim.

## First-slice scope (future, blocked)

- `-03` instance validation/batching.
- `-04` conservative frustum/distance culling.
- `-05` LOD/HLOD chains and selection.
- `-06` verified-chunk stream request planning.
- `-07` vegetation classification.
- `-08` geometry budget validation.
- `-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX04_01_APPROVED_GOVERNANCE_ONLY`: **606 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 113 `COMPLETED`, 29 approved gates**.
- `GFX-04-01` becomes `APPROVED_GOVERNANCE`; `GFX-04-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/mesh library/codec selection, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
