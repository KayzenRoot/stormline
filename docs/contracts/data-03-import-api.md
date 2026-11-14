# DATA-03 — Import & Conversion Semantic API (PROPOSED v0.1)

**Research WO:** NLE-P00-WO-002-DATA-03 | **Implementation:** #26 BLOCKED  
**Status:** conceptual, no generated ABI/SDK/MCP tool or C++ header.

## Typed semantic objects

```text
ImporterDescriptorV1 {
  importer_id, semantic_version, build_digest, supported_mime_and_sniffed_formats,
  supported_extensions, capability_profile, legal_notice_manifest,
  input_quota_profile, output_artifact_types
}
ImportRequestV1 {
  operation_id, project_scope, source_vfs_path, expected_source_digest?,
  expected_asset_id?, expected_asset_revision?, importer_id?,
  options_schema_version, normalized_options, declared_dependencies,
  max_resources, caller_capability
}
ImportPlanV1 {
  detected_format, importer_version, required_extensions,
  source_and_dependencies_digests, expected_output_types_and_sizes,
  predicted_reference_changes, warnings, preview_digest, constraints
}
ImportArtifactV1 {
  artifact_id, artifact_type, schema_version, stable_subasset_key?,
  semantic_digest, bytes_digest, size, conversion_record, validation_result
}
ImportReceiptV1 {
  operation_id, asset_id, source_fingerprint, importer_id_and_version,
  options_digest, external_dependencies_digests, core05_conversion_policy,
  artifact_manifest_digest, generated_subasset_map, previous_revision?,
  warnings_and_loss_report, commit_state, toolchain_build_id
}
ReimportPlanV1 {
  previous_receipt, new_source, previous_source_owned_metadata,
  user_override_revision, three_way_diff, stable_subasset_mapping,
  conflicts, impacted_dependents, preview_digest
}
```

### Error taxonomy
`INVALID_INPUT`, `UNSUPPORTED_FORMAT`, `UNSUPPORTED_REQUIRED_EXTENSION`, `SOURCE_CHANGED`, `SOURCE_MISSING`, `DEPENDENCY_DENIED`, `RESOURCE_LIMIT`, `DECOMPRESSION_BOMB`, `INVALID_GEOMETRY`, `INVALID_COLOR_PROFILE`, `INVALID_AUDIO_LAYOUT`, `INVALID_ANIMATION`, `NON_REPRODUCIBLE`, `SUBASSET_MAPPING_CONFLICT`, `USER_OVERRIDE_CONFLICT`, `STALE_ASSET_REVISION`, `CAPABILITY_DENIED`, `CANCELLED`, `IMPORTER_CRASH`, `VALIDATION_FAILED`, `COMMIT_FAILED`, `RECOVERY_REQUIRED`, `UNKNOWN`. Errors carry safe stage, request correlation, retryability and redacted notes.

### Candidate semantic command mapping

| Command | Behavior | Security and validation |
|---|---|---|
| `InspectSource` | sniff format and safely list present features/extensions/dependencies | read-only scoped VFS, byte/time quotas, never execute embedded data |
| `PreviewImport` | resolve importer/options and create change+resource plan without publication | report unsupported required extensions and possible fidelity loss |
| `StartImport` | staged job with operation ID, cancellation and progress | capability, source revision and full quota checks |
| `GetImportStatus` | paginated, bounded progress/events | no raw parser logs/secrets |
| `CancelImport` | cooperative cancellation/worker termination per policy | no half-published derived state |
| `GetImportReceipt` | read approved provenance, hash/version/artifact report | redact private paths/prompts, project scope |
| `PreviewReimport` | three-way merge of source edits and authored overrides | no write or automatic override deletion |
| `CommitImport` | approve exact preview hash and expected registry revision | staged file + DATA-02 reconcile, idempotency token |
| `RecoverImport` | resume/roll-forward/rollback approved unfinished operation | never guess conflict resolution or reset valid asset |
| `ListImporters` | supported formats, versions and declared restrictions | no runtime dynamic download/installation implied |

### Transaction lifecycle (logical)
`INSPECTED -> PLANNED -> PARSING -> VALIDATING -> STAGED -> PREVIEW_READY -> COMMIT_INTENT -> ASSET_COMMITTED -> REGISTRY_RECONCILED -> COMPLETE` with explicit `CANCELLED / FAILED / CONFLICT / RECOVERY_REQUIRED` branches.

- Durable intent and idempotent retry are future DATA-01/02 integration obligations, **not** proof a combined VFS/SQLite ACID transaction exists.
- Reimport must preserve `AssetId` and stable key mapping or issue explicit `SUBASSET_MAPPING_CONFLICT`; duplicating a source creates new `AssetId` unless caller explicitly links.
- An approved preview/commit is a **semantic scoped application command**, not permission to run arbitrary tools, shell, SQL, network or filesystem.
- A safe fallback when third-party decoder format unsupported is a typed failure with retained source, not silently substituted output.
- For large projects, publish pagination for status/receipts and provide a stable cursor and bounded event streams instead of loading all traces into AI context.

### Demonstration example
Given `AssetId=A` referencing `project://Characters/hero.glb`, import skeleton+mesh+skin/material with stable subasset keys. Change original to add animation and rename the file via DATA-01/DATA-02. `PreviewReimport` produces a diff, keeps user-authored material override or reports conflict; `CommitImport` preserves `AssetId=A` and all unchanged scene references. A crash during staged import can be recovered without publishing a truncated asset.

**No application, SDK implementation, API endpoint or MCP server was created by this contract.**
