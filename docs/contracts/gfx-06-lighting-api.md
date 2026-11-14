# GFX-06 — Versioned Lighting, GI, Shadow and Reflection Semantic API

**Research:** #138 | **WO NLE-P00-WO-002-GFX-06** | **Implementation #34 BLOCKED**.  
Logical proposal only; **not** a compiled C++ ABI, actual GPU API, operational MCP server or frozen binary/wire schema.

| Proposed type | Core fields | Validation and owner |
|---|---|---|
| `LightDefinitionV1` | project/scene, LightId, revision, type, transform, linear color, intensity with explicit unit, radius/area, shadow/volume/channel policy | finite values, photometric units; stable IDs DATA-02, authored scene DATA-04 |
| `LightSetSnapshotV1` | sorted light IDs/revisions, scene/view epoch, camera, frame tick, light count and digest | immutable frame snapshot; revision-check and overflow |
| `LightingTargetProfileV1` | GFX-01 backend+capability fingerprint/device generation, GFX-02 shader layout, viewport/scale, quality tier | not OS-only GPU guess; verified Web/native constraints |
| `LightingQualityBudgetV1` | per-pass time targets, VRAM/UMA unknown source, light/shadow/probe/ray/volume allocation caps and fallback order | bounded and GFX-03 plan-owned resources |
| `ClusteredLightAssignmentV1` | tiles/z-slices, light IDs, counts/prefix ranges, overflow flag and contribution-fallback receipt | checked arithmetic, no silent missing light |
| `ShadowCasterSnapshotV1` | GFX-04 caster IDs, bounds, alpha/deform/LOD/stream revision, light/view projection | animated/foliage/offscreen casters validated |
| `ShadowPlanV1` | per-light CSM splits/atlas/filter/bias, page/clipmap optional, reversed-Z, invalidation/caster epochs | CSM fallback, mapped-page ownership GFX-03 |
| `ShadowPageReceiptV1` | table ID, requested+resident pages, generation, fence completion, bytes, fallback/degradation | never sample incomplete/missing page |
| `IndirectLightingPlanV1` | IBL/probes/lightmaps/SSGI/RadianceCascades/SDF/RT profile, ray/probe budget, offscreen fallback | DATA-05 verified bake, 3D RC explicit experimental |
| `ProbeVolumeDefinitionV1` | scene asset revision, location/cells, SH data/visibility, relocation, provenance and validity | safe bounds, leak risk and source-rights |
| `ReflectionPlanV1` | probe/SSR/RT tier, material roughness signature, offscreen policy, history | SSR offscreen miss reported, GFX-05 compatible |
| `VolumetricPlanV1` | density/extinction/scattering, phase, froxel/analytic tier, per-frame caps | finite nonnegative coefficients, no VFX graph duplication |
| `LightingHistoryKeyV1` | scene, light/caster/material revision, camera/projection/viewport/origin epoch, device generation, shader/layout, technique | mismatches invalidate; GFX-03 owns GPU fences/history |
| `LightingPlanV1` | validated snapshot, GFX-03 pass+resource proposals, dependency/quality constraints, error/fallback | GFX-06 does not own RenderGraph compiler |
| `LightingQualityReceiptV1` | input digest, chosen tiers, degraded quality reasons, cache hit/invalidation, measured/estimated/unknown CPU/GPU/VRAM provenance | diagnostics redacted, never label estimate as measurement |

## Frame lifecycle
`SCENE_SNAPSHOT -> VALIDATED -> CAPABILITY_NEGOTIATED -> GRAPH_PLANNED -> GPU_QUEUED -> FENCE_COMPLETE -> FRAME_PRESENTED`. Camera cut, resize, rebase, dynamic light/geometry/alpha/material change, stream unload, shader layout or device generation mismatch => `HISTORY_INVALID`, reset/fallback and deterministic receipt. No stale VRAM alias after fences; no ghost light after emission ends.

## Semantic Editor/CLI/MCP authorization
- Read-only: `InspectLight`, `InspectLightSet`, `PreviewLightingQuality`, `PreviewShadowPlan`, `PreviewProbeBake`, `GetLightingReceipt`, `GetLightingHistoryDiagnostics`. All scoped/rate-limited/redacted; preview costs explicitly ESTIMATED.
- Authored mutation: `StageLightEdit` -> `ValidateLightEdit` -> `CommitLightEdit`, requiring capability, project+scene/light ID, expected source revision, quota, rights/physics and DATA-04 recoverable edit. `CancelLightingOperation` safe idempotent.
- Forbidden via agent: raw GPU descriptor, shader/binary upload, arbitrary path/URL/process execution, unbounded bake, cross-project scene data, third-party assets, direct device allocation, unapproved paid/download task.

## Errors (typed, recoverable where documented)
`INVALID_LIGHT`, `NONFINITE_INTENSITY`, `UNIT_MISMATCH`, `LIGHT_LIMIT`, `CLUSTER_OVERFLOW`, `SHADOW_CASTER_STALE`, `CASCADE_INVALID`, `SHADOW_PAGE_MISSING`, `SHADOW_POOL_EXHAUSTED`, `HISTORY_INVALID`, `PROBE_LEAK`, `GI_MODE_UNSUPPORTED`, `RAY_TRACING_UNAVAILABLE`, `REFLECTION_OFFSCREEN`, `VOLUMETRIC_LIMIT`, `BUDGET_EXCEEDED`, `SHADER_LAYOUT_MISMATCH`, `DEVICE_GENERATION_STALE`, `SOURCE_REVISION_CONFLICT`, `CAPABILITY_DENIED`, `LICENSE_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Include safe stage, retryability, correlation ID and redacted user message.

## Contract freeze gate
Approved backend shader layouts/format and exact file interfaces, DATA-04 scene schema and GFX-03 fence integration, real platform/quality/rights tests, numeric thresholds. This document does **not** make #34 executable.
