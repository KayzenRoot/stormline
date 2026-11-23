# GFX-05 INTERNAL_ONLY Material/Texture Governance Contract v0 (NLE-PRPLAN-GFX-05-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `eafb62a`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md), [ADR-0018](../adr/0018-gfx-05-material-texture-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-05-01](../work-orders/NLE-PRPLAN-GFX-05-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-05 implementation. No native GPU, texture codec/decoder, shader compiler, allocator, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-02` and `DATA-03`; neither is module-qualified.
- GFX-05 owns logical material parameters, texture/mip metadata, virtual-page requests, samplers, decals and transparency budgets.
- GFX-02 shaders; DATA-01/02/03/04/05 assets/import/cook; GFX-01 RHI; GFX-03 upload/residency; GFX-04 visibility; GFX-06 lighting; GFX-07 tone mapping.
- No Vulkan/D3D12/Metal/WebGPU, KTX2/Basis, image codec, allocator or renderer dependency is selected.

## Policy invariants

1. **No native GPU or codec.** Logical metadata only; no image decode/encode, upload, rendering or allocation.
2. **Bounded and finite.** Fixed capacities; NaN/Inf and out-of-range parameters rejected.
3. **Fail closed.** Duplicate/invalid IDs, bad mip/sampler/alpha states, decal conflicts and budget overflow are typed errors.
4. **Deterministic.** Stable sort keys and IDs determine output.
5. **Residency honesty.** Virtual-page requests are proposals; no hardware sparse or completion claim.
6. **No overdraw guarantee.** Transparency budgets count logical items; no performance promise.
7. **No artifact claim.** PBR parameters/texture metadata are not a rendered image or GPU resource.
8. **Release boundary.** `INTERNAL_ONLY`; no ABI, performance, security, release or production claim.

## First-slice scope (future, blocked)

- `-03` PBR parameter validation.
- `-04` virtual texture page requests.
- `-05` mip metadata.
- `-06` sampler/filter profiles.
- `-07` decal ordering.
- `-08` transparency sort/overdraw budget.
- `-09` qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX05_01_APPROVED_GOVERNANCE_ONLY`: **596 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 121 `COMPLETED`, 31 approved gates**.
- `GFX-05-01` becomes `APPROVED_GOVERNANCE`; `GFX-05-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/codec/allocator selection, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
