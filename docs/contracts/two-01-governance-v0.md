# TWO-01 INTERNAL_ONLY Canvas Governance Contract v0 (NLE-PRPLAN-TWO-01-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `74e7256`. **ADR:** [ADR-0123](../adr/0123-two-01-internal-canvas-pipeline.md), [ADR-0022](../adr/0022-two-01-native-2d-renderer-policy.md) planning-only. **WO:** [NLE-PRPLAN-TWO-01-01](../work-orders/NLE-PRPLAN-TWO-01-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before TWO-01 implementation. No GPU renderer, swapchain, sprite draw, atlas upload, text/vector engine, lighting, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- TWO-01 owns logical canvas sprite/atlas/layer/camera/snap/light plans and typed fallback metadata.
- GFX-01 device/presentation; GFX-02 shaders; GFX-03 resources/fences; GFX-05 textures/materials; GFX-06 lighting; GFX-07 output/post; DATA-02/03/04/05 asset identity/import/authoring/cook.
- No Vulkan/D3D12/Metal/WebGPU, sprite/text/vector engine, atlas cooker, font engine, codec or hardware driver is selected.

## Policy invariants

1. **No GPU or image output.** Metadata/planning only; no instance, texture upload, sampler, draw, composite or pixel.
2. **Bounded and finite.** Fixed capacities; NaN/Inf, zero/negative dimensions, overflow and illegal references are rejected.
3. **Fail closed.** Unknown layers/assets/atlases, stale revisions and invalid modes are typed errors or declared safe degradation.
4. **Painter order is semantic.** Declared layer/order is never reordered for batching in this logical layer.
5. **Deterministic.** Stable IDs, declared order and checked caps determine output.
6. **Ownership preserved.** GFX-06 owns lighting; GFX-05 textures; GFX-03 resources; DATA owns durable assets. TWO-01 duplicates none.
7. **No visual/performance claim.** Plans are not frames, sprites, text, 60 FPS, VRAM or DPI results.
8. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` sprite draw metadata.
- `-04` atlas region/gutter/mip metadata.
- `-05` layer order/blend/clip metadata.
- `-06` orthographic camera/viewport/dpi metadata.
- `-07` pixel-snapping policy metadata.
- `-08` typed 2D light requests for GFX-06.
- `-09` integrated qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `TWO01_01_APPROVED_GOVERNANCE_ONLY`: **556 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 153 `COMPLETED`, 39 approved gates**.
- `TWO-01-01` becomes `APPROVED_GOVERNANCE`; `TWO-01-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/text/vector/atlas engine selection, painter-order violation, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
