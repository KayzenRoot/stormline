# ADR-0121 — Bounded internal camera, exposure, tone, reconstruction and output planning

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Keeps:** [ADR-0020](0020-gfx-07-camera-color-reconstruction-policy.md) as planning-only context.

## Context

GFX-06 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-07 research and ADR-0020 exist, but no GPU output, swapchain, HDR signal, tone mapper, temporal history, vendor upscaler, monitor negotiation or visual qualification is authorized. A fail-closed logical layer is required before any backend work.

## Decision

Ratify a first GFX-07 internal pipeline that validates and plans metadata only:

1. **Camera/projection.** Stable camera/view IDs and revisions, perspective/orthographic metadata, finite FOV/extent/near/far/aspect, previous view, jitter and world-only-jitter flags. No matrix inversion or GPU projection is claimed.
2. **Exposure.** Manual EV100 or bounded auto-exposure metadata, metering percentiles, adaptation times and flash policy. No histogram is read from an image.
3. **Tone/color plan.** Declared working color space, input/output transfer, tone curve and gamut policy with finite stops/exposure and explicit SDR fallback. No pixel is transformed or tone-mapped.
4. **HDR output availability.** A logical capability request resolves to SDR or declared HDR mode only from supplied flags; internal float texture does not imply HDR. Unknown/unsupported falls back to SDR with a typed receipt.
5. **Spatial/temporal strategy.** Native, spatial, TAA/TAAU, or vendor-gated strategy metadata with required inputs and fallback; no TAA, FSR, DLSS, XeSS or shader executes.
6. **Motion blur.** Optional velocity/shutter metadata, per-view enable and reduced-motion disable. No motion vectors are generated or sampled.
7. **Upscale.** Render/output dimensions, scale ratio, strategy and fallback metadata. No vendor SDK, DLL, signed binary or GPU upscaler is loaded; output resolution is not native fidelity.

## Non-decisions

- No Vulkan/D3D12/Metal/WebGPU, swapchain, HDR10/PQ/HLG output, monitor negotiation, GPU allocator or resource.
- No shader compiler/bytecode, LUT/OCIO/ACES runtime, FSR/DLSS/XeSS SDK, frame generation or signed DLL loading.
- No pixel transform, histogram, tone map, bloom, AA, motion blur or upscale.
- No visual golden, hardware/monitor, performance, latency, HDR or color-accuracy qualification.
- No public ABI, release class beyond `INTERNAL_ONLY`, or engine license decision.

## Ownership

- GFX-01 owns swapchain/device/display capability; GFX-02 shaders; GFX-03 graph/resources/fences; GFX-04 motion vectors; GFX-05 materials; GFX-06 scene-linear lighting.
- DATA-02/03/04 own durable camera IDs, color/LUT assets and scene revisions.
- GFX-07 owns only logical camera/exposure/post plans and their typed fallback metadata.

## Consequences

- The layer is deterministic and testable on all CI platforms without a GPU.
- Any future tone mapper, HDR output, TAA, SDK upscaler or visual comparison requires a new owner-approved contract/slice and platform evidence.
- SDR remains the only guaranteed logical output; HDR is a declared capability, never inferred.

## Evidence gates

Contract `GFX-07-02`, six implementation slices, qualification `-09`, closeout `-10`, exact-head native CI, pt-BR audit. Stop on stale source, native GPU/display/SDK selection, released ABI or HIGH/CRITICAL.
