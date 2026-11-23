# GFX-07 INTERNAL_ONLY Camera/Color/Post Governance Contract v0 (NLE-PRPLAN-GFX-07-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `a2a0154`. **ADR:** [ADR-0121](../adr/0121-gfx-07-internal-post-processing-pipeline.md), [ADR-0020](../adr/0020-gfx-07-camera-color-reconstruction-policy.md) planning-only. **WO:** [NLE-PRPLAN-GFX-07-01](../work-orders/NLE-PRPLAN-GFX-07-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before GFX-07 implementation. No native GPU, swapchain, HDR output, tone mapper, LUT/OCIO runtime, TAA, vendor upscaler, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependency is `GFX-06`; it is not module-qualified.
- GFX-07 owns logical camera/view, exposure, tone/color policy, HDR availability, reconstruction strategy, motion-blur and upscale plans.
- GFX-01 HDR/swapchain; GFX-02 shaders; GFX-03 graph/resources/history; GFX-04 velocity; GFX-05 materials; GFX-06 lighting; DATA-02/03/04 identity/color assets/scene edits.
- No Vulkan/D3D12/Metal/WebGPU, HDR monitor, LUT/OCIO runtime, FSR/DLSS/XeSS or frame-generation dependency is selected.

## Policy invariants

1. **No native GPU or image output.** Metadata/planning only; no swapchain, shader, pixel, tone map, AA, blur, upscale, LUT or HDR signal.
2. **Bounded and finite.** Fixed capacities; NaN/Inf, zero dimensions, illegal exposure/shutter and overflow are rejected.
3. **Fail closed.** Unknown IDs/modes/transfers, stale generations, double transfer/tone and invalid history are typed errors or safe fallback.
4. **Deterministic.** Stable IDs and declared order determine output.
5. **SDR baseline.** SDR sRGB remains the mandatory fallback; HDR is never inferred from an internal float format or web canvas.
6. **No visual/performance claim.** Plans are not images, HDR captures, color accuracy, latency or frame-time results.
7. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` camera/projection/exposure metadata.
- `-04` tone/color and SDR/HDR output planning.
- `-05` HDR capability negotiation/fallback.
- `-06` reconstruction/antialiasing strategy.
- `-07` optional motion-blur planning.
- `-08` render-scale/upscale planning.
- `-09` integrated qualification and `-10` closeout remain blocked.

## Gate state after merge

- Manifest root `GFX07_01_APPROVED_GOVERNANCE_ONLY`: **576 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 137 `COMPLETED`, 35 approved gates**.
- `GFX-07-01` becomes `APPROVED_GOVERNANCE`; `GFX-07-02`..`-10` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, native GPU/display/SDK selection, host I/O, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
