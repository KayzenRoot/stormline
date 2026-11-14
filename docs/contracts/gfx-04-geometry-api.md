# GFX-04 — Geometry Visibility, Instancing, LOD/HLOD and Mesh Stream Semantic API

**Research WO:** NLE-P00-WO-002-GFX-04 | **Issue:** #132 | **Future code:** #32 BLOCKED.
**State:** PROPOSED LOGICAL CONTRACT, NOT C++/GPU IMPLEMENTATION. All definitions require version/ABI approval and real test evidence.

## Typed entities

| Logical contract | Suggested fields | Non-negotiable invariant |
|---|---|---|
| `GeometryAssetProfileV1` | DATA-02 MeshAssetId/revision, DATA-03 source rights/provenance, format, coordinate convention, material/skeleton/morph/tangent/UV dependencies, fidelity policy | authored AssetId preserved, no generated GPU address as source identity |
| `GeometryCookRecipeV1` | target capability and precision, quantization and meshopt tag, simplification error, meshlet bounds, cluster/HLOD mode, allowed material and deformation classes | DATA-05 owns cooking/manifest; any loss of authored data is explicit and user approved |
| `MeshLODManifestV1` | source id, derived generation, parent/child cluster DAG, bounds, geometric error, material/attribute mappings, coarsest fallback, chunk references | acyclic hierarchy, no unreachable required cluster, fallback exists or typed missing-content |
| `MeshClusterV1` | stable derived cluster id, parent/ref, local/global bounds, error envelope, triangle/vertex ranges, cone cull applicability, material refs | bounds conservative under transforms and deformation; indices checked |
| `GeometryInstanceV1` | instance id, AssetId/revision, transform/precision origin, material variant, animation/morph/WPO bounds, picking/interaction class, visibility flags | no loss of object identity, false grouping of material/animation/picking prohibited |
| `ViewVisibilityRequestV1` | camera id/matrix epoch, frustum, projection/viewport, origin/near/far/reversed-Z, temporal history validity, depth pyramid gen, device feature tiers, quality/cost policy | reject stale/invalid matrices, unsafe occlusion history; unknown bounds treated visible |
| `VisibilityDecisionV1` | PassId/ResourceId/instance/cluster, visible/coarse/cull candidate, conservative reason, confidence/validation mode, screen-space error | no false-negative without proof; unexpected uncertainty => draw |
| `OcclusionEvidenceV1` | pyramid frame/generation, camera epoch, resolution, depth convention, conservative coverage/bias/occluder class, rejection/fallback reason | transparent/alpha masked/unknown deformations not trusted opaque by default; history invalidated on discontinuities |
| `LODSelectionReceiptV1` | selected source/derived LOD, quality cap/error, hysteresis reason, residency, proxy/fallback, revision and per-view generation | no missing required geometry hidden as successful cull |
| `GeometryStreamRequestV1` | DATA-05 manifest/chunk ref, verified source digest, desired LOD and importance, IO/CPU/upload/VRAM cap, cancellation and generation | GFX-04 requests only; DATA-05 verifies bytes/source and GFX-03 owns GPU upload |
| `GeometryStreamReceiptV1` | chunk verification, source provenance level, residency state, target device generation, bytes and errors, fallback still resident | SHA digest != publisher identity; no activating unverified chunk |
| `GeometryResidencySnapshotV1` | per-mesh root LOD pinned, available levels, missing chunks, GPU RHI handles/epochs (internal), budget known/estimated/unknown, last use fence | don't evict in-flight/last-good coarse LOD under request |
| `InstanceBatchPlanV1` | grouping by compatible Mesh/Material/Shader/RenderState, per-instance transforms and IDs, buffer range/stride, GPU feature set | bounded count, preserve instance-specific picking/animation and rights |
| `GeometryDrawPlanV1` | GFX-03 pass ids/indirect or vertex-index route, RHI feature requirements, safe draw count, visibility receipts and source generation | only feature-available path; indirect counter range/validation and full barrier plan |
| `GeometryQualityPolicyV1` | max screen-space error, LOD hysteresis, distortion tolerance, foliage class, min proxy, GPU/IO/CPU budgets, optional quality downgrade allowed | lower-quality path may not violate required authored/picking/collision behavior |
| `GeometryDiagnosticV1` | code, sanitized project-relative AssetId, view/instance/cluster, source span, stage and safe recommendation | bounded redacted, no absolute path, binary mesh leak or native pointers |
| `GeometryErrorV1` | code, input revision, device/scene generation, phase, retryability, proposed recovery | invalid bounds/cull/LOD/cache not silently hidden or acknowledged as rendered |

## Logical pipeline, type checking and fallback
1. DATA-03 import source; DATA-02 own permanent id; DATA-05 cook immutable mesh-derived LOD chunks and manifest with rights/version receipt.
2. Scene collects `GeometryInstanceV1` under CORE-05 and derives conservative expanded bounds (animation/morph/negative scale/WPO).
3. `geometry.visibility.plan` computes frustum/coarse-distance CPU reference. When optional GPU Hi-Z present, validate `OcclusionEvidence` camera/viewport/depth epoch and classify occluder material first. Unknown histories and deformations prefer visible.
4. `geometry.lod.plan` uses bounded pixel error and hysteresis with residency; no requested high LOD => resident root/coarse fallback, or explicit `REQUIRED_GEOMETRY_MISSING`.
5. `geometry.stream.plan` produces bounded DATA-05 requests, with no direct URL/proprietary asset access from MCP; only validated chunks are eligible to be uploaded to GFX-03 residency.
6. `geometry.instance.batch.plan` and `geometry.draw.plan` output typed GFX-03 pass declarations; GFX-01/GFX-02 capabilities restrict compute/mesh shader/indirect route. Serial vertex-index path exists when advanced GPU support unavailable.
7. Device loss, HLOD source revision, shader reflection/scene edits, camera cut/FOV/projection/resize/origin rebase or patch failure invalidates relevant plan generations and visibility history; old in-flight RHI resources retire under GFX-03 fences, last-good source kept.

## Error and recovery taxonomy
`MESH_ASSET_UNKNOWN`, `SOURCE_RIGHTS_DENIED`, `SOURCE_REVISION_STALE`, `GEOMETRY_SCHEMA_MISMATCH`, `INVALID_VERTEX_LAYOUT`, `INDEX_OUT_OF_BOUNDS`, `BOUND_UNKNOWN`, `BOUND_INVALID`, `DEFORM_BOUND_UNVERIFIED`, `CLUSTER_HIERARCHY_CYCLE`, `LOD_ERROR_OUT_OF_RANGE`, `LOD_HIERARCHY_CRACK_RISK`, `LOD_REQUIRED_PROXY_MISSING`, `STREAM_CHUNK_UNVERIFIED`, `STREAM_DEADLINE_MISSED`, `REQUIRED_GEOMETRY_MISSING`, `OCCLUSION_HISTORY_STALE`, `OCCLUDER_NOT_OPAQUE`, `CAMERA_EPOCH_MISMATCH`, `UNSUPPORTED_MESH_SHADER`, `INDIRECT_COUNT_OVERFLOW`, `GPU_RESOURCE_STALE`, `GPU_BUDGET_EXCEEDED`, `CANCELLED`, `CAPABILITY_DENIED`, `UNKNOWN`.
Typed caller can request conservative draw/coarse proxy; source-provenance errors never masked as harmless occlusion.

## Editor/CLI/MCP controlled parity
| Operation | Authorized scope | Mutation |
|---|---|---|
| `geometry.asset.inspect` | project.geometry.read | bounded sanitized geometry metadata |
| `geometry.instances.inspect` | project.geometry.read | paginated instance counts/state; no unrestricted scene export |
| `geometry.lod.preview` | project.geometry.propose | quality/error/hysteresis and proxy plan, no asset rewrite |
| `geometry.visibility.inspect` | project.geometry.debug.read | bounded conservative reasons and camera/epoch context |
| `geometry.occlusion.validate` | project.geometry.propose | history/bounds simulation, no GPU draw |
| `geometry.stream.plan` | project.geometry.propose | bounded chunk list preview; no actual network fetch |
| `geometry.diagnostics.snapshot` | project.geometry.debug.read | privacy-minimized counters |
| `geometry.cook.propose` | project.asset.propose | DATA-05 typed recipe preview only |
| `geometry.cook.execute` | privileged DATA-05 service | requires approved workflow/rights/quotas, NOT general raw MCP API |
| `geometry.draw.submit` | GFX runtime only | never exposed as raw MCP/driver command |

Every request must check project/actor capability, expected AssetId revision and device/scene epoch, bounded graph/mesh/LOD counts, CPU/IO/GPU upload quotas, logs redacted and disallow arbitrary source code/host file/url or signed bundle bypass. No blanket authorization from "AI-native" status.

## Performance and future proof
No algorithm is considered correct/fast until reference occlusion oracle yields **zero false negative** in declared test envelope; on unprovable cases fallback visible. Validate across real hardware/OS/browser, foliage/deformed geometry, WPO, different shading/alpha and streamed scenes. Unknown performance is **not** 0 ms/0 bytes. See [ADR](../adr/0017-gfx-04-visibility-geometry-policy.md), [architecture](../architecture/gfx-04-geometry-visibility-lod.md), [test matrix](../testing/gfx-04-acceptance-matrix.md). This document alone does not change future code issue #32.
