# WORLD-04 — Typed Terrain/Environment Authoring, Render Intent and Physics Contract v0.1

**Research #168 | WO NLE-P00-WO-002-WORLD-04 | Code issue #44 BLOCKED**. Proposals only, not an executable C++ ABI, shader interface, serializer, editor control, physics engine or MCP endpoint.

| Proposed versioned type | Key fields / purpose | Owner/invariant |
|---|---|---|
| `TerrainAssetV1` | ProjectId/AssetId/SceneId/source revision/rights, global meters/grid schema, height tiles and distinct mesh-surface links | DATA-02/04 canonical source, caves not heightfield |
| `TerrainPatchIdV1` | Source TerrainAssetId, world signed tile coords, LOD level and authored patch revision | stable across WORLD-03 streaming, origin epochs, LOD changes |
| `TerrainHeightTileV1` | checked sample resolution/width/height, units/elevation range/no-data policy, border and neighbor IDs, data hash | finite samples, shared edge precision and source/collider basis |
| `TerrainEditLayerV1` | stable layer/source provenance, mode, author, precedence, timestamps/revision and manual override policy | DATA-04 journal/undo, WORLD-05 generator proposal cannot silently overwrite |
| `TerrainBrushStrokeV1` | operation RAISE/LOWER/SMOOTH/FLATTEN/STAMP/ERASE, radius/falloff, affected patch IDs and expected revision | bounded, finite, stage+preview not direct GPU writes |
| `TerrainMaterialMaskV1` | patch layer IDs, bounded normalized splat weight channels/zero sum default, texture AssetIds, color profile | GFX-05 PBR/material and virtual residency owner |
| `TerrainLodHintV1` | patch adjacency, screen-space error candidate, neighbors, morph/skirt selection, camera+origin and stream state | GFX-04 actual mesh/LOD, no GPU cull in WORLD-04 |
| `TerrainCollisionIntentV1` | source patch revision, consistent height/mesh basis, affected PHYS shapes and safe tick ack state | PHYS gameplay/contact owner; no active traversable tile before ACK |
| `BiomeZoneV1` | stable authored zone GUID/region, mixture weight, physical/visual palette, override precedence, source AssetIds | WORLD-04 authoring, WORLD-05 generator has independent ownership |
| `VegetationInstanceGroupV1` | prototype AssetId, stable instance IDs/transforms, density/wind visual mask, collider declaration, revision | GFX-04 instancing, PHYS colliders, no generated WORLD-05 duplicate |
| `WaterBodyV1` | water source ID, class OCEAN/LAKE/RIVER/LOCAL, region/shore, visual flow/waves and PHYS volume link | visual water WORLD-04, PHYS simulation and GAME/NET authority |
| `WaterVisualIntentV1` | wave profile, reflection tier, foam/wetness/shore masks, quality flag, temporal/reactive and source tick | GFX-05/07 shader & HDR, no physics derived from displaced pixels |
| `EnvironmentProfileV1` | authored time/sky atmosphere/wind/cloud/fog/precip palettes, linked weather source/rights and quality tier | visual params, GAME/NET authoritative weather, GFX-06/07/08 render |
| `WeatherVisualIntentV1` | authoritative weather snapshot origin/tick, rain/snow/wind visible values and target systems | core clock/NET authority, GFX-08 weather particles |
| `BiomeFramePlanV1` | source/world/origin revisions, terrain+vegetation+water/sky intents, required resident tiles and quality limits | GFX/PHYS owners ACK; no half-published terrain |
| `TerrainTransactionV1` | project/asset/scene/expected DATA-04 CAS revision, staged layers, impacted neighbors, role and journal token | source undo and cook/stream stage, no arbitrary file/URL |
| `TerrainQualityReceiptV1` | tile seam/gpu quality and CPU p50/p95/p99 measured/ESTIMATED/UNKNOWN, memory, residency errors and capability tier | no fabricated FPS/SSR/cloud fidelity |
| `TerrainPublishReceiptV1` | committed source revision vs runtime PHYS/GFX readiness, pending/last-good and recovery state | DATA-04 disk commit != GPU+PHYS fence atomically |

## Typed semantic API (not implemented)
Readonly `InspectTerrainAsset`, `InspectTerrainPatches`, `PreviewTerrainStroke`, `InspectBiomeZone`, `InspectVegetationInstances`, `InspectWaterBody`, `InspectEnvironmentProfile`, `PreviewTerrainLod`, `InspectTerrainPublishReceipt`, `GetBiomeQualityReceipt`. Authoring `StageTerrainStroke`, `StageMaterialMaskEdit`, `StageBiomeOverride`, `StageVegetationEdit`, `StageWaterEdit`, `StageEnvironmentProfileEdit`, `ValidateTerrainTransaction`, `CommitTerrainTransaction`, `Undo/RedoTerrainTransaction`, `CancelTerrainEdit`. All actions ProjectId+AssetId/SceneId+expected source revision+role and quotas; no direct shader/pointer/fs/URL/cloud-code execution.

## Publication sequence
`StageBrush/EnvironmentalEdit -> PreviewAffectedPatchesNeighbors/CollisionSources/RendererFrames -> Validate input/rights/limits -> DATA-04 source CAS+journal -> DATA-05 cook source-dependent tiles -> WORLD-03 cell staged residency -> CORE tick barrier -> WORLD-01/PHYS collision/GFX-03+04 geometry and GFX-05/06/07/08 intents ACK -> Publish coherent scene+quality receipt`. After source commit and before PHYS/GFX ACK use `SOURCE_COMMITTED_RUNTIME_PENDING` and last-good committed simulation snapshot, not false completed edit. Rollback/forward idempotent by source revision.

## Typed errors and safety
`TERRAIN_BAD_HEIGHT_SAMPLE`, `TERRAIN_PATCH_COORD_OVERFLOW`, `TERRAIN_TILE_SEAM_CONFLICT`, `TERRAIN_LOD_NEIGHBOR_INVALID`, `TERRAIN_TOPOLOGY_UNSUPPORTED`, `TERRAIN_SOURCE_REVISION_STALE`, `TERRAIN_STROKE_BUDGET_EXCEEDED`, `TERRAIN_LAYER_CONFLICT`, `TERRAIN_MATERIAL_WEIGHT_INVALID`, `TERRAIN_TEXTURE_ASSET_UNAUTHORIZED`, `TERRAIN_MESH_LINK_UNRESOLVED`, `VEGETATION_DENSITY_LIMIT`, `VEGETATION_DUPLICATE_INSTANCE`, `VEGETATION_COLLIDER_ACK_PENDING`, `WATER_SHORELINE_INCOMPLETE`, `WATER_PHYSICS_AUTHORITY_REQUIRED`, `ENVIRONMENT_TIME_EPOCH_STALE`, `ENVIRONMENT_WEATHER_AUTHORITY_DENIED`, `ENVIRONMENT_CAPABILITY_UNSUPPORTED`, `TERRAIN_PHYS_COLLISION_ACK_PENDING`, `TERRAIN_RENDER_FENCE_PENDING`, `TERRAIN_ASSET_RIGHTS_DENIED`, `TERRAIN_PROJECT_SCOPE_DENIED`, `TERRAIN_SOURCE_COMMITTED_RUNTIME_PENDING`, `TERRAIN_CAS_CONFLICT`, `TERRAIN_DEVICE_LOST`, `TERRAIN_RESOURCE_BUDGET_UNSATISFIABLE`, `TERRAIN_CANCELLED`, `TERRAIN_RECOVERY_REQUIRED`. Structured errors carry retryability, stage, revision and redacted patch IDs; never private disk path or opaque pointer.

## Future code freeze conditions
Owner-approved ADR-0029/1.0 DoD/Scope, integrated WORLD-03 and GFX-04 (plus DATA/GFX/PHYS owner contracts), exact C++ files/schema/coordinate/ABI, vetted asset provenance, GPU/browser feature table, real original biome fixtures and numeric p95/p99, visual error/seam and gameplay collision budgets, no HIGH/CRITICAL and raw byte SHA-256 context. None of these are satisfied for implementation #44.

## Public first-party/primary sources, research only
- NVIDIA GPU Gems 2 terrain geometry clipmaps chapter (historical performance is not Stormline's): https://developer.nvidia.com/gpugems/gpugems2/part-i-geometric-complexity/chapter-2-terrain-rendering-using-gpu-based-geometry
- Terrain3D Godot plugin **MIT** source license: https://github.com/TokisanGames/Terrain3D/blob/main/LICENSE.txt
- meshoptimizer **MIT** library license and feature maturity: https://github.com/zeux/meshoptimizer/blob/master/LICENSE.md
- Bruneton precomputed atmospheric scattering implementation **BSD**: https://github.com/ebruneton/precomputed_atmospheric_scattering
- Godot 4.6 sky, fog, volumetric and post owner reference: https://docs.godotengine.org/en/4.6/classes/class_environment.html
- Godot 4.6 occlusion and level-of-detail practices: https://docs.godotengine.org/en/4.6/tutorials/3d/occlusion_culling.html
- Unreal Landscape technical design and authoring reference, proprietary Epic terms: https://dev.epicgames.com/documentation/en-us/unreal-engine/landscape-outdoor-terrain
- Khronos glTF EXT_mesh_gpu_instancing public extension reference (asset rights independent): https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_mesh_gpu_instancing/README.md
- WebGPU specification capability/texture/compute restrictions: https://www.w3.org/TR/webgpu/
