# DATA-04 — Semantic Scene Document and Authoring API Contract (Proposed)

**WO:** NLE-P00-WO-002-DATA-04 | **Research:** #117 | **Implementation:** #27 BLOCKED.
This is a **semantic specification**, not implemented C++ ABI, JSON schema file, MCP server, executable endpoint or approved stable protocol.

## Types and ownership

| Logical contract | Mandatory proposed fields | Invariant / bounded failure |
|---|---|---|
| SchemaDescriptorV1 | schema_id, schema_version, required_capabilities, known_component_namespaces, canonicalization_version | reject unsupported required capability |
| SceneDocumentV1 | schema, project_id, scene_id, document_revision, entities, components, asset_refs, extension_fields, authoring_metadata | valid IDs, no duplicate keys, limits, scope |
| EntityRecordV1 | entity_id, name, parent_id?, child_order?, enabled, component_refs, tags | parent cycles fail; order explicit |
| ComponentRecordV1 | component_instance_id, entity_id, type_id, type_version, typed_properties, required_feature? | plugin data never auto-instantiates executable code |
| AssetRefV1 | asset_id (DATA-02), expected_revision?, subasset_key?, usage_role | path/hash not identity; missing references typed |
| PropertyValueV1 | typed scalar/array/map/union, units, type_id and constraints | finite numbers, bounded containers |
| SceneRevisionV1 | document_revision, digest_algorithm, canonicalization_version, semantic_digest, project_revision | algorithm/version explicit, no weak implicit equality |
| SceneInspectV1 | schema/capability summary, scene counts, unresolved refs, fingerprint, warnings | read-only, redacted, bounded |
| ScenePatchV1 | operation_id, actor_context, base_revision, target_scene_id, operations, preconditions | idempotent, stale conflict |
| SceneOperationV1 | op_type, target stable IDs, typed_path, expected_old_value?, new_value?, order intent | no raw JSON pointer privilege escalation |
| SceneDiffV1 | base/new revision, typed changes, affected assets/entities, conflicts, unknown field handling | stable-ID comparison |
| MigrationPlanV1 | from/to versions, graph path, required plugin/permission checks, loss report, backup plan, expected_digest | inspect/preview-only until approved |
| MigrationReceiptV1 | operation_id, before/after digest, migration IDs/versions, stage/commit journal ref, backup ref, warnings | recovering same ID is idempotent |
| SceneErrorV1 | stable code, stage, entity/field locator, retryable, safe summary | no arbitrary paths, tokens or private content |

**ID representation:** stable opaque string in wire format; version/schema identifiers explicit. Runtime handles must not be persisted. Use CORE-05 typed spatial values and DATA-02 AssetId.

## Source document shape (illustrative, not actual JSON schema)
- schema: schema_id + schema_version + canonicalization_version.
- scene_id and project_id: persistent opaque ID strings.
- document_revision: DATA-02-associated revision with optimistic concurrency.
- required_capabilities and required_plugin_schemas: complete feature negotiation.
- entities: keyed by stable entity ID, with separately encoded render/hierarchy order when meaningful.
- components: keyed by durable component instance ID; properties validated against namespace/type version.
- asset_refs: typed DATA-02 references with unresolved-reference diagnostics.
- extensions: bounded unknown optional data, preserved without execution.
- authoring_metadata: deliberately allowed text/notes, sanitized for display and never treated as LLM instructions.
- explicit provenance reference: not redundant copy of DATA-02 identity source.

## Semantic command kernel: Editor, CLI, MCP parity

| Command | Authorization | Behavior |
|---|---|---|
| scene.inspect | project.scene.read | limited metadata and warnings, no mutation |
| scene.validate | project.scene.read | parse/schema+graph+quota verdict |
| scene.diff | project.scene.read | compare authorized revisions, bounded changes |
| scene.patch.preview | project.scene.propose | simulate typed operations, report loss/conflicts |
| scene.patch.commit | project.scene.write + explicit approved intent | revalidate base, journal, commit/recover |
| scene.migration.plan | project.scene.read | compatibility graph, backup, risk preview |
| scene.migration.preview | project.scene.propose | dry-run validated target, no disk mutations |
| scene.migration.commit | project.scene.migrate + explicit approval | stage, verify, receipt and recovery |
| scene.recovery.inspect | project.scene.read | safe status/read-only recovery details |
| scene.recovery.execute | privileged project recovery scope | authorized repair with audit and receipt |

Mandatory request envelope: project scoped capability, target scene ID, schema version, expected_revision, idempotency key, bounded typed options, actor policy and audit correlation. Deadline/cancellation honored. MCP cannot send an arbitrary OS path, shell command, C++ type constructor, unrestricted VFS write, raw SQL or executable plugin object. Unauthorized requests must return CAPABILITY_DENIED with no side effects.

## Semantic write states
INSPECTED -> PLANNED -> PREVIEWED -> STAGED -> VERIFIED -> INTENT_RECORDED -> COMMITTED/RECOVERY_REQUIRED. COMMITTED only after readback+integrity reconciliation. Cancellation before intent aborts without publication; cancellation after intent requires defined completion/recovery protocol. A retry with same idempotency key returns the same receipt or RECOVERY_REQUIRED, not a second independent migration.

## Conflict and schema errors
MALFORMED_DOCUMENT, ENCODING_INVALID, DUPLICATE_KEY, RESOURCE_LIMIT, NONFINITE_VALUE, SCHEMA_UNSUPPORTED, REQUIRED_COMPONENT_UNKNOWN, UNSUPPORTED_DOWNGRADE, ENTITY_ID_COLLISION, PARENT_CYCLE, ASSET_REF_MISSING, EXTENSION_LIMIT, STALE_REVISION, PATCH_CONFLICT, CAPABILITY_DENIED, MIGRATION_LOSS_RISK, STAGE_FAILED, DISK_FULL, COMMIT_FAILED, RECOVERY_REQUIRED, CANCELLED and UNKNOWN. Each error specifies retryability, stage and redacted context; never leaks arbitrary file contents.

## Compatibility and validation
- Source JSON decoding is strict, not implicit default coercion. Schema Draft 2020-12 can verify structure, while cross-field graph/reference and auth invariants require dedicated validators.
- Byte-for-byte roundtrip is not the same as semantic roundtrip. Unknown optional fields preserved according to declared policy; require a test for lossless values/metadata.
- Source representation independent of binary DATA-05 packs. No direct reflection-derived schema that invents public commands.
- Version transitions monotonic unless a specific reversible downgrade is proven. Read-only mode on unsupported new format.
- Scenario IDs SER-001..SER-020 in the linked [matrix](../testing/data-04-acceptance-matrix.md) are future tests only, not passing results.

## Interface freeze gates
Before issue #27 is executable: define actual schema JSON files, exact type IDs/commands, C++/CLI/MCP adapter boundaries, source paths, validator library/version, license notices, error/test harness, recovery journal and target matrix, plus user-approved ADR/release class and fresh SHA-256 Context Lock. No versioned API has been built.
