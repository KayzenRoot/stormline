# EDIT-03 — Versioned Scene, Prefab, Gizmo, Terrain and Editor Transaction Semantic API v0.1

**P00 proposed only, NOT COMPILED OR DEPLOYED.** Research [#260](https://github.com/KayzenRoot/stormline/issues/260), WO NLE-P00-WO-002-EDIT-03, future code #70 OPEN/BLOCKED, BASE `e0463818e6dda79cabd26e49f81eca38cd507782`. Names below are semantic design, not C++ headers, serialization schema, runtime or selected SDK. Formal predecessors EDIT-02 and WORLD-04 research only. All authoring commands fail closed if target owner is unimplemented.

## 1. Typed contract registry
| Candidate V1 type | Required fields/semantics | Sole owner / security invariant |
|---|---|---|
| `SceneDocumentRefV1` | project ID, DATA-04 SceneId, schema revision/content hash, editable lease + target platform | DATA-04 actual source authority; EDIT-03 cannot own independent scene serializer |
| `SceneNodeRefV1` | WORLD-01 EntityId+generation, scene revision, optional parent/instance origin and cell | stale/unloaded entity denied, path/label not identity |
| `SceneHierarchyQueryV1` | loaded/unloaded/virtualized filter, root, depth, snapshot revision, page token | safe bounded hierarchy, no full scene blocking UI |
| `SceneSelectionSnapshotV1` | immutable deduped ordered refs, active ref, loaded-cell generations, selection revision | EDIT-01 selection host; EDIT-03 validates before applying |
| `SceneReflectPropertyV1` | CORE-05 component/type/property stable ID, units, ranges, enum, mutability, metadata version, provenance | actual reflection owner CORE-05, no arbitrary property offsets |
| `SceneInspectorEditV1` | property path by stable IDs, typed old/new values, mixed-state, expected revisions, multiple selected refs | all-or-nothing batch or explicit per-target failure, permission checked |
| `SceneTransformSpaceV1` | LOCAL/PARENT/WORLD, handedness and units, selected pivot ACTIVE/MEDIAN/CURSOR/INDIVIDUAL | WORLD transform semantics, no unlabeled matrix convention |
| `SceneGizmoStateV1` | TRANSLATE/ROTATE/SCALE, axis locks, snap distance/angle/surface, numeric override and input focus | visual-only overlay GFX/EDIT-01; canonical world not mutated on drag |
| `SceneTransformDeltaV1` | quaternion+translation+scale canonical, finite values, active pivot, parent/world versions, operation id | WORLD owner checks parent inverse/singular/precision |
| `ScenePickRequestV1` | GFX viewport/window+device epoch, camera/origin, pointer DIP→pixel transform, world/cell generation | GFX picking only, no stale readback entity |
| `ScenePickReceiptV1` | hit EntityId+generation, depth, world/cell revision, GFX frame epoch, visibility/permission | reject hidden/unloaded/destroyed entities |
| `SceneOperationV1` | CREATE/DELETE/REPARENT/DUPLICATE/RENAME/SET_PROPERTY/TRANSFORM/PREFAB_APPLY/TERRAIN_STROKE | actor capability, expected source revision and nonmutating preview |
| `SceneEditPreviewV1` | affected refs, before/after semantic diff, errors, estimated files/memory, required user consent | immutable plan until commit; no cache writes trusted as source |
| `SceneEditTransactionV1` | idempotency ID, project/source+cell expected CAS, actor, before hashes, delta stage and reversible inverse | DATA-04 and WORLD owners alone write canonical source |
| `SceneEditReceiptV1` | committed/conflict/rejected/recovered, new revision, hashes, author+provenance, undo handle and warnings | persistent evidence not UI toast |
| `SceneHistoryEntryV1` | scope scene/terrain/prefab, before/after CAS, inverse diff, original author/operation and storage budget | EDIT-03 scene undo separate from EDIT-01 layout undo |
| `PrefabDefinitionRefV1` | DATA-02 stable AssetId, revision, root stable child IDs, required components | source provenance/asset graph DATA-02 |
| `PrefabInstanceRefV1` | stable instance ID, source ref, scene owner, revision, instance path only display | no unintended source/sibling mutation |
| `PrefabOverridePatchV1` | stable target component/field, tombstones/create/delete, value and base revision, resolution order | DATA-04 composition and conflict detection |
| `PrefabRebasePlanV1` | source old→new and instance overrides, three-way conflicts, invalid refs and user choices | source upgrade never silently loses user overrides |
| `WorldCellRefV1` | WORLD-04 stable cell ID, level/coords/origin, loaded state, generation, neighborhood | world partition and streaming owner WORLD-04 |
| `SceneCellLeaseV1` | loaded/readonly/writer, expected source revision and expiry/cancel reason | DATA-04/CAS, no "multi-user writes just work" |
| `TerrainLayerRefV1` | WORLD-04 terrain ID, layer stable ID, HEIGHT/WEIGHT/FOLIAGE/HOLES/SPLINE/PROC, revision | manual layers persist independent of procedural/cache |
| `TerrainStrokeV1` | op RAISE/LOWER/SMOOTH/FLATTEN/ERODE/STAMP/PAINT, radius/falloff/strength, resampled world points, seed, sample schema, cell revisions | WORLD-04 validates tiles/precision/bounds; deterministic seed |
| `TerrainLayerDeltaV1` | before/after tile hashes, signed/quantized height or mask deltas, affected neighbor refs and halo | no GPU-only terrain source, bound memory, seams |
| `TerrainFoliagePatchV1` | stable foliage source AssetId, instance IDs, cell seed, weight/density and max count | WORLD-04 placement/LOD, no arbitrary instantiated scripts |
| `TerrainBakePlanV1` | selected source stack, immutable backup, LOD target, licensing, budget, destructive warning | data bakes optional and require explicit user approval |
| `TerrainPreviewLeaseV1` | GFX surface epoch, visible tile refs/LOD, overlay buffer and cancellation, saved source revision | GFX owns GPU/LOD presentation and device-loss recovery |
| `SceneStreamingBudgetV1` | visible/dirty loaded cells, memory/VRAM/IO limits and residency priority | WORLD-04 streaming, UI cannot unload dirty cell |
| `ScenePreviewModeV1` | EDIT/PLAY_ISOLATED/DEBUG_ATTACH, clock/viewpoint and writeback permission default false | EDIT-07 simulation preview, CORE-04 tick independent |
| `ScenePluginCapabilityV1` | approved plugin/manifest hash, tool IDs, scene+cell scopes, schema and resource limit, isolation mode | no in-process native plugin isolation claimed |
| `SceneAutomationPrincipalV1` | UI/CLI/MCP actor, per-project/scene permission, expected source CAS and consent flags | all origins share public authorizer, no raw shell |
| `SceneEvidenceBundleV1` | base/head source, scene/asset hashes, OS/renderer, fixture seed, command receipts, recovery trace | no "completed" without real evidence |

## 2. Proposed operations (not actual callable software)
- `ListSceneHierarchy` / `InspectSceneSelection` / `ResolvePropertyMetadata`: bounded filtered projection and typed CORE-05 reflection with no side effects. `PreviewSceneOperation` validates WORLD generation, DATA-04 source CAS, project lease and permissions.
- `StartGizmoPreview` / `UpdateGizmoPreview` / `CancelGizmoPreview` / `CommitTransform`: bounded visual math, no source write until commit; local/world/pivot/snapping numeric and finite matrix preconditions. Picking is validated against GFX frame and loaded WORLD cell epoch.
- `StageSceneTransaction` / `ValidateSceneDelta` / `CommitSceneTransaction`: DATA-04 delegated durable write with rollback/recovery, game sim/EDIT-07 runtime unaffected. `UndoSceneTransaction` / `RedoSceneTransaction`: explicit owner scope and expected revision; conflicts produce review, not overwrite.
- `InspectPrefabOverrideGraph` / `PreviewPrefabRebase` / `CommitPrefabOverride` / `ApplyOverrideToSource` / `RevertPrefabOverride`: stable IDs, cycle detection, three-way merge and source write privilege for apply.
- `PreviewTerrainStroke` / `CommitTerrainLayerStroke` / `RestoreTerrainLayerRevision`: WORLD-04 tiles, neighbor halos and bounded deterministic seed, DATA-04 versioned delta; no direct GPU texture as sole canonical source. `RequestTerrainBake`: explicit approval and last-known-good snapshot, GFX only previews.
- `LeaseSceneCell` / `LoadSceneCellProjection` / `UnloadCleanCell`: WORLD-04 residency/dirty state and budget, DATA-04 save confirmation, editor never drops dirty cell. `InvokeSceneEditViaMCP` must follow same preview/commit, capability, rate/size quotas and user approval as GUI/CLI.

## 3. Non-negotiable invariants
1. No second canonical scene/ECS/terrain format in editor; source ownership DATA-04/WORLD-01/WORLD-04, asset IDs DATA-02, file grants DATA-01, GFX GPU and EDIT-01 host.
2. Any stale EntityId generation, unloaded cell, unmatched document/actor privilege, unsupported schema or missing dependency must reject before source mutation.
3. Undo scope **scene vs layout vs simulation** explicit; one committed gesture yields one history group unless explicitly split; finite limits and crash recovery.
4. A prefab instance override changes only its instance without privileged apply-to-source. Invalid cycles/refs/tombstones produce typed conflict; preserve source and overrides.
5. Every terrain brush stroke records bounded reproducible semantic delta and stable source layer, not screenshot/GPU-only data. LOD and streaming cache regenerable.
6. Multi-file operations use real DATA-04 transaction/recovery; OS process crash, disk full/power failure distinct, no blanket atomic durability claim.
7. AI/MCP, CLI and editor share typed permission/expected CAS, no autonomous paid terrain assets or arbitrary script/renderer injection.
8. Accessible keyboard numeric transforms and hierarchy inspector, real Windows/Linux/macOS tests needed; P00 docs ≠ functioning system.

**Typed failure taxonomy:** `SCENE_NOT_IMPLEMENTED, SCENE_ADR_UNAPPROVED, SCENE_PROJECT_LEASE_MISSING, SCENE_DOCUMENT_SCHEMA_UNSUPPORTED, SCENE_DOCUMENT_REVISION_STALE, SCENE_ENTITY_GENERATION_STALE, SCENE_HIERARCHY_CYCLE, SCENE_PARENT_ACCESS_DENIED, SCENE_SELECTION_CELL_UNLOADED, SCENE_MULTI_EDIT_PARTIAL_DENIED, SCENE_REFLECTION_PROPERTY_UNKNOWN, SCENE_PROPERTY_OUT_OF_RANGE, SCENE_TRANSFORM_NAN_INF, SCENE_TRANSFORM_SINGULAR_PARENT, SCENE_TRANSFORM_HANDEDNESS_CONFLICT, SCENE_TRANSFORM_AXIS_LOCK_INVALID, SCENE_PICK_GPU_EPOCH_STALE, SCENE_PICK_VISIBILITY_DENIED, SCENE_PREFAB_SOURCE_MISSING, SCENE_PREFAB_CYCLE, SCENE_PREFAB_OVERRIDE_CONFLICT, SCENE_PREFAB_APPLY_SOURCE_DENIED, SCENE_PREFAB_REBASE_FAILED, SCENE_UNDO_WRONG_SCOPE, SCENE_UNDO_REVISION_CONFLICT, SCENE_UNDO_LOG_QUOTA, SCENE_TRANSACTION_DUPLICATE, SCENE_TRANSACTION_STAGE_INCOMPLETE, SCENE_TRANSACTION_COMMIT_FAILED, SCENE_TRANSACTION_RECOVERY_REQUIRED, SCENE_TERRAIN_CELL_MISSING, SCENE_TERRAIN_CELL_STALE, SCENE_TERRAIN_BRUSH_QUOTA, SCENE_TERRAIN_LAYER_NONDESTRUCTIVE_REQUIRED, SCENE_TERRAIN_HEIGHTFIELD_TOPOLOGY_UNSUPPORTED, SCENE_TERRAIN_NEIGHBOR_SEAM_INVALID, SCENE_TERRAIN_SEED_VERSION_MISMATCH, SCENE_TERRAIN_FOLIAGE_OVERFLOW, SCENE_TERRAIN_BAKE_APPROVAL_REQUIRED, SCENE_STREAMING_DIRTY_UNLOAD_DENIED, SCENE_GPU_VIEWPORT_LOST, SCENE_OS_ACCESSIBILITY_NOT_PROVEN, SCENE_IMPORT_UNTRUSTED_ASSET, SCENE_PLUGIN_UNTRUSTED_SCRIPT_DENIED, SCENE_VFS_ESCAPE_DENIED, SCENE_MCP_CAPABILITY_DENIED, SCENE_PRIVACY_REDACTED, SCENE_RESOURCE_LIMIT`. All outcomes typed, localized, redacted, retriable where safe; ZERO code, 128 future tests NOT EXECUTED.
