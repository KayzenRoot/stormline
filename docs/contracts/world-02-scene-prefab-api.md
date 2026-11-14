# WORLD-02 — Typed Scene, Prefab, Instance, Variant and Rebase API v0.1

**Research #162 | WO NLE-P00-WO-002-WORLD-02 | Future code #42 OPEN/BLOCKED**. Semantic proposal, **not** compiled ABI, actual serializer, native editor API, running ECS or MCP endpoint.

| Proposed type | Fields / purpose | Explicit invariant and owner |
|---|---|---|
| `SceneAssetV1` | ProjectId, SceneId, schema/revision/hash, root NodeIds, ordered scene contents and rights | canonical DATA-04 source, DATA-02 AssetId, cycle-free child graph |
| `PrefabAssetV1` | PrefabId/revision, local NodeIds, component defaults/parameters/nested references | typed WORLD-01 components, DATA-02 asset identity, bounded expansion |
| `SceneNodeIdV1` | stable per-source NodeGuid independent of node name/path/array index | never use raw runtime EntityHandle in serialized source |
| `SceneInstanceIdV1` | durable scene placement identifier + source prefab ID/revision+local node mapping | uniqueness on clone/copy, cross-instance remap receipts |
| `HierarchyLinkV1` | parent/child NodeIds, stable sibling order, owner SceneId, relation kind | 1 structural parent max, no cycles/cross-world by accident |
| `SceneTransformV1` | local affine matrix or checked TRS/pivot/units, parent/source transform epoch | CORE-05 math, invertibility/representability; PHYS authority preserved |
| `ReparentPolicyV1` | KEEP_LOCAL / KEEP_WORLD, expected revisions, allowed ownership | avoid singular inverse and silent shear loss, cycle check |
| `PrefabVariantV1` | VariantId/rev, BasePrefabId/rev, ordered sparse override ops and nested references | variant dependency DAG cycle-free, stable source IDs |
| `PrefabInstanceLinkV1` | InstanceId, source PrefabId/rev, external refs and source-node map | persistent link, lazy readiness typed, no silent break |
| `PrefabOverrideV1` | key {sourceNodeGuid,ComponentTypeId,FieldId}, old base rev, value/tombstone, local author | explicit inherited/local provenance, only schema-allowed values |
| `PrefabStructuralPatchV1` | ADD_CHILD/REMOVE_CHILD/MOVE_CHILD/ADD_COMPONENT/REMOVE_COMPONENT/REORDER, expected source-node rev | no index-only diffs, target existence, permission, tombstone |
| `PrefabPropagationPlanV1` | base change set and transitively affected instances, stale/cycle/cap quotas, update-vs-preserve counts | dry-run estimate not actual saved instances |
| `PrefabRebaseReceiptV1` | base(old), ours(local override), theirs(new base), field/structural conflict keys, resolutions | 3-way typed policy, no silent winner on conflicting edits |
| `SceneSnapshotV1` | composed rev, source refs, node-to-EntityGuid mapping, roots/transforms, complete/incomplete stage | published only as generation-consistent snapshot; WORLD-01 remaps handles |
| `SceneEditTransactionV1` | project/scene/prefab/instance scope, expected DATA-04 rev, staged typed operations, journal token and role | CAS, rollback, access and rights, no direct file write |
| `SceneCommitReceiptV1` | committed source revision, runtime published revision/epoch, pending/recovery and conflict counts | journal durable != live ECS/PHYS published, receipts separate |
| `SceneQualityReceiptV1` | expanded nodes/depth, dirty/fan-out, CPU compose p95/p99, bytes and status measured/ESTIMATED/UNKNOWN | no fake throughput/perf from planning |

## Semantics and pseudoflow (FUTURE)
`StageScene/PrefabEdit(expectedRevision) -> ValidateNodeForest/TemplateDAG/Schema/ACL -> PreviewPrefabRebase(base,ours,theirs) -> DATA04_SourceCommitCAS -> WORLD01_CommandBufferAtBarrier -> ReconcileDownstreamSnapshot -> PublishSceneRevisionReceipt`. An operation that has committed source but not runtime returns `SOURCE_COMMITTED_RUNTIME_PENDING` or `RECOVERY_REQUIRED`; idempotent outbox and last-good runtime snapshot prevent a broken partial world, no fabricated cross-service atomicity.

`ResolveSceneNodeId` returns durable stable identity and world scoped generational handle when loaded; `CopyPrefabInstance` allocates new InstanceId, deterministic mapping for imported reference remaps and preserves prefab link+overrides. `ApplyOverrideToSource` requires explicit scope and rights to edit source; `RevertOverride` clears local patch and reevaluates latest authorized source revision, not old value blindly. `DetachInstance` requires dry-run, loss report and explicit authorization; never performed by failed import.

## Editor, CLI and MCP parity
Readonly: `InspectScene`, `InspectPrefab`, `InspectPrefabVariant`, `ListSceneHierarchyPage`, `InspectInstanceLink`, `PreviewPrefabPropagation`, `PreviewPrefabRebase`, `PreviewReparentTransform`, `GetSceneQualityReceipt`. Mutating: `StageSceneEdit`, `StagePrefabEdit`, `StageVariantEdit`, `StageReparent`, `ValidateSceneTransaction`, `CommitSceneTransaction`, `UndoSceneTransaction`, `RedoSceneTransaction`, `CancelSceneOperation`. All are versioned, project/asset ID plus expected source revision and role; MAX changes/size/depth, transparent diff+owner receipt, no untrusted script or shell.

## Typed failures
`SCENE_SOURCE_NOT_FOUND`, `SCENE_REVISION_CONFLICT`, `SCENE_DUPLICATE_NODE_ID`, `SCENE_PARENT_CYCLE`, `SCENE_PARENT_MULTIPLE`, `SCENE_WRONG_PROJECT`, `SCENE_ENTITY_HANDLE_STALE`, `SCENE_EXTERNAL_REF_UNLOADED`, `PREFAB_SOURCE_MISSING`, `PREFAB_DEPENDENCY_CYCLE`, `PREFAB_EXPANSION_LIMIT`, `PREFAB_OVERRIDE_TARGET_MISSING`, `PREFAB_BASE_REMOVAL_CONFLICT`, `PREFAB_REBASE_CONFLICT`, `PREFAB_INSTANCE_MAPPING_COLLISION`, `PREFAB_LOCAL_OVERRIDE_PRESERVED`, `PREFAB_BREAK_LINK_REQUIRES_APPROVAL`, `TRANSFORM_NONINVERTIBLE`, `TRANSFORM_NOT_REPRESENTABLE`, `TRANSFORM_PRECISION_EXCEEDED`, `SCENE_CAS_CONFLICT`, `SOURCE_COMMITTED_RUNTIME_PENDING`, `RUNTIME_EPOCH_STALE`, `SCENE_FANOUT_BUDGET_EXCEEDED`, `SCENE_IMPORT_RIGHTS_DENIED`, `ASSET_REFERENTIAL_INTEGRITY_FAILED`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Every error has safe scope/stage/retryability/redacted affected IDs, not raw private paths.

## Freeze before implementation
Approved ADR-0027/Scope/1.0 DoD, actual integrated WORLD-01 and DATA-02 code, DATA-04 source journal/migration, CORE-05 transforms, source serialization identity and exact owner rights, typed Windows/Linux/macOS/Web/headless test fixtures, numeric fidelity/p95/memory budgets, pinned optional parser licenses/SBOM and raw SHA-256 Context Lock. **NONE satisfied for code #42**.
