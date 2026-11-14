# GFX-07 — Camera, Color and Post Semantic API v0.1

**WO NLE-P00-WO-002-GFX-07** | **Research #141** | **Future implementation #35 BLOCKED**. Conceptual only, NOT compiled C++ ABI, JSON schema, operating GPU pipeline or MCP server.

| Logical type | Required fields | Invariant / dependency |
|---|---|---|
| `CameraProjectionV1` | scene+CameraId/revision, perspective/orthographic/layer, FOV or ortho extent, near/far/aspect, inverse/current+previous matrices | finite/invertible, CORE-05 space and DATA-04 scene identity |
| `CameraRenderViewV1` | view_id, render/output pixel dims, viewport/subview, pixel ratio, jitter/previous jitter, camera cut/rebase epoch | world jitter only; UI unjittered; safe multi-view and size |
| `MotionVectorContractV1` | GFX-04 depth/velocity signature, pixel/NDC units, previous-current sign, jitter subtraction, deformation/reactive coverage | invalid/stale vectors reset history; no silent mismatch |
| `SceneLinearColorContractV1` | GFX-05/06 primaries, white point, linear transfer, alpha semantics, source profile/revision, light epoch | no duplicate decode; finite HDR values and specified gamut |
| `ExposureProfileV1` | manual EV100/auto, metering bins/percentiles/region, adaptation and flash policy | nonfinite/bad percentiles rejected, well-defined reset |
| `ColorTransformProfileV1` | ACES2/neutral/custom profile, in/out primaries/transfer, white point/gamut mapping, 1D/3D LUT AssetId/revision/rights | DATA-03 validates file, GFX-02 compiles safe transform, no shader injection |
| `DisplayOutputCapabilitiesV1` | GFX-01 adapter+monitor/browser, OS/swapchain/device generation, actual SDR/HDR/colorSpace, source/provenance nits | HDR not inferred from scene FP16; UNKNOWN permitted |
| `DisplayOutputPlanV1` | SDR sRGB or negotiated HDR10 PQ/EDR mode, UI paper white nits, capture transform, fallback and warnings | safe SDR on failed HDR/monitor switch |
| `PostEffectStackV1` | ordered exposure/recon/bloom/DoF/motion blur/grade/gamut/UI passes, alpha masks, accessibility overrides | GFX-03 resource DAG owns execution, no double tone map |
| `ReconstructionInputV1` | scene HDR, depth, motion vectors, alpha/reactive mask, jitter, exposure ratio, viewport/render scale, device generations | all valid GFX-03 fence-resident textures |
| `ReconstructionStrategyV1` | NATIVE/SPATIAL/TAA_TAAU/FSR/DLSS/XESS, required feature, signed SDK provenance, quality/fallback | no unsafe vendor install, compatible target only |
| `PostHistoryKeyV1` | project/scene/view/camera, projection, epochs, render/output size and scale, light/material/layout/device/swapchain revisions | mismatch invalidates; no unsignaled alias |
| `PostProcessingBudgetV1` | CPU/GPU ms goals, memory source known/unknown, history bytes, LUT limits, scale/hysteresis caps | estimates clearly labeled and GFX-03 allocation ownership |
| `PostQualityReceiptV1` | input and frame signature, color/output strategy, artifact/rejection/degrade details, measured/estimated/unknown timing, normalized errors | no disguised estimate or false HDR capture |
| `CameraPostEditV1` | project+scene+expected camera/profile revision, staged allowlisted params, user capability, journal/rollback | DATA-04 owns transactions and permission |

## State machine
`SCENE_SNAPSHOT -> SOURCE_COLOR_VALIDATED -> DISPLAY_NEGOTIATED -> HISTORY_VALIDATED -> GRAPH_PLANNED -> GPU_SUBMITTED -> FENCE_COMPLETE -> DISPLAY_ENCODED -> PRESENTED`. Camera cut, origin rebase, resize, flash, wrong vectors, HDR swapchain mode, hot reload or GPU loss => `HISTORY_INVALID -> SPATIAL/NATIVE_SAFE_FALLBACK` with typed receipt. GFX-01 owns presentation; GFX-03 owns resource lifetime and fences.

## Editor / CLI / MCP bounded command parity
- Readonly: `InspectCamera`, `InspectColorProfile`, `InspectDisplayCapability`, `PreviewExposure`, `PreviewPostBudget`, `GetPostQualityReceipt`, `InspectTemporalHistory`. Project-scoped, paginated, redact private capture/device identifiers. Preview is ESTIMATE, not GPU proof.
- Mutating: `StageCameraEdit`, `StageColorProfileEdit`, `StagePostStackEdit` -> `ValidateCameraPostEdit` -> `CommitCameraPostEdit` under explicit role, revision compare-and-swap, bounded resources/rights, durable DATA-04 journal and rollback, `CancelPostOperation` idempotent.
- Forbidden: arbitrary .cube/ICC/OCIO/EXR host path or URL fetch, plugin DLL load/driver setting change, native GPU pointer/shader source, private screenshot exports, OS HDR calibration overrides or unlimited asset mutation.

## Typed errors
`CAMERA_INVALID`, `PROJECTION_INVALID`, `NONFINITE_PARAM`, `MOTION_VECTOR_MISMATCH`, `COLOR_SPACE_MISMATCH`, `DOUBLE_TRANSFER_GUARD`, `INVALID_LUT`, `LUT_RIGHTS_DENIED`, `EXPOSURE_INVALID`, `HDR_OUTPUT_UNAVAILABLE`, `GAMUT_OUT_OF_RANGE`, `HISTORY_INVALID`, `REACTIVE_MASK_MISSING`, `TEMPORAL_UNSUPPORTED`, `UPSCALE_SDK_INVALID`, `UPSCALE_LICENSE_DENIED`, `BUDGET_EXCEEDED`, `DEVICE_GENERATION_STALE`, `SHADER_LAYOUT_MISMATCH`, `SOURCE_REVISION_CONFLICT`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Errors include retryability, stage, correlation ID and safe reason.

## Implementation freeze
Real ABI, SDK versions and licenses, selected working color primaries, GFX-01 swapchain/monitor and GFX-03 graph, GFX-04 velocity units, GFX-05/06 scene-linear protocols, OS/browser/fixture targets, exact thresholds and 1.0 DoD still TBD. Do not set executor_ready.
