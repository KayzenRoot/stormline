# GFX-08 INTERNAL_ONLY VFX governance contract v0 (NLE-PRPLAN-GFX-08-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `eb81362`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md), [ADR-0021](../adr/0021-gfx-08-vfx-graph-particle-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-08-01](../work-orders/NLE-PRPLAN-GFX-08-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-08 implementation. No CPU/GPU particle simulation, compute, sorting, OIT, volumetric rendering, shader, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- GFX-08 owns logical VFX graph shape, emitter/spawn budgets, ribbon/trail plans, blend policy, density-stamp metadata and pool/quality budgets.
- GFX-01 device capability; GFX-02 shaders; GFX-03 graph/resources/fences; GFX-04 visibility/depth; GFX-05 materials/alpha; GFX-06 lighting/volumetrics; GFX-07 HDR/post; DATA-02/03/04/05 asset identity/import/authoring/cook.
- No Vulkan/D3D12/Metal/WebGPU, compute backend, particle SDK, volume codec, GPU sorting library or frame-generation dependency is selected.

## Policy invariants

1. **No simulation or image output.** Metadata/planning only; no particle state, PRNG stream, compute dispatch, sort, OIT, volume sample, draw or pixel.
2. **Bounded and finite.** Fixed capacities; NaN/Inf, zero dimensions/lifetimes, overflow, cycles and illegal graph references are rejected.
3. **Fail closed.** Unknown node kinds/ports, stale graph revisions/generations, invalid blends and exhausted pools are typed errors or declared safe degradation.
4. **Deterministic.** Stable IDs, declared order and checked caps determine output; no dependence on time, thread or device state.
5. **Cosmetic only.** VFX never becomes gameplay-authoritative for damage, collision, hit validation or network state.
6. **Ownership preserved.** GFX-06 owns lighting/scattering; GFX-05 materials; GFX-03 resources; DATA owns durable assets. GFX-08 duplicates none.
7. **No visual/performance claim.** Plans are not frames, particle counts, GPU timings, VRAM usage or visual matches.
8. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` logical particle graph and spawn-budget metadata.
- `-04` ribbon geometry-budget metadata.
- `-05` trail geometry-budget metadata.
- `-06` transparency/blend policy metadata.
- `-07` volumetric density-stamp metadata.
- `-08` pooling and quality-budget metadata.
- `-09` integrated qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX08_01_APPROVED_GOVERNANCE_ONLY`: **566 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 145 `COMPLETED`, 37 approved gates**.
- `GFX-08-01` becomes `APPROVED_GOVERNANCE`; `GFX-08-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/compute/sort/SDK selection, gameplay-authority leakage, unbounded graph/spawn/geometry, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
