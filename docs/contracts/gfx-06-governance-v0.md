# GFX-06 INTERNAL_ONLY Lighting Governance Contract v0 (NLE-PRPLAN-GFX-06-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `de396b2`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md), [ADR-0019](../adr/0019-gfx-06-adaptive-lighting-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-06-01](../work-orders/NLE-PRPLAN-GFX-06-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-06 implementation. No native GPU, shadow map, ray tracing, GI/probe bake, reflection, volumetric, shader compiler, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-03` and `GFX-05`; neither is module-qualified.
- GFX-06 owns logical light definitions, shadow/GI/probe/reflection/volumetric plans and degradation metadata.
- GFX-01 RHI; GFX-02 shaders; GFX-03 graph/resources; GFX-04 casters; GFX-05 BRDF/alpha; GFX-07 output; DATA-02/04/05 identity/scene/cook.
- No Vulkan/D3D12/Metal/WebGPU, shadow-map, ray-tracing, GI/probe/SSR/froxel dependency is selected.

## Policy invariants

1. **No native GPU or rendering.** Metadata/planning only; no shadow map, GPU resource, shader, descriptor, fence, upload or frame.
2. **Bounded and finite.** Fixed capacities; NaN/Inf, negative/zero illegal values and count overflow are rejected.
3. **Fail closed.** Unknown IDs/types/units, duplicate cells, invalid splits, stale bake/epoch and budget overflow are typed errors.
4. **Deterministic.** Stable IDs and declared ordering determine output; identical input yields identical plans.
5. **Honest fallback.** Missing page/bake/capability produces coarse fallback or typed error, never silent stale or zero light.
6. **No visual/performance claim.** Plans are not shadows, light, GI, reflections, fog, images or timing results.
7. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` logical lights and validation.
- `-04` shadow split/page planning and invalidation metadata.
- `-05` GI/baked/IBL fallback planning.
- `-06` probe volume metadata.
- `-07` reflection/SSR fallback planning.
- `-08` volumetric metadata and budget.
- `-09` integrated qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX06_01_APPROVED_GOVERNANCE_ONLY`: **586 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 129 `COMPLETED`, 33 approved gates**.
- `GFX-06-01` becomes `APPROVED_GOVERNANCE`; `GFX-06-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/shadow/ray-tracing selection, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
