# AI-03 — Proposed Capability Discovery, Schema and Compatibility Contracts v0.1

**2026-11-15 | P00 RESEARCH ONLY, NOT IMPLEMENTED | [research #289](https://github.com/KayzenRoot/stormline/issues/289) | NLE-P00-WO-002-AI-03 | [future code #77](https://github.com/KayzenRoot/stormline/issues/77) OPEN/BLOCKED | BASE `1db368aa555f7a8eb2fa1a1eb3a38744a23ef6bb`.** 58/80 researched at baseline, 22 pending, zero engine, all 80 implementation packets BLOCKED. Formal dependency **AI-01 ONLY**; ADR-0060 PROPOSED and code #75 OPEN/BLOCKED. NLE-D009 engine license OPEN.

All types/commands below are **research-only proposed contracts**, not compiled headers, active API methods, a running MCP service or an approved owner schema.

## 1. Owner declaration source (AI-01 authoritative)
```text
AI01CommandDescriptorRefV1 {
  command_id: NamespacedCommandIdV1,
  owner_module_id: ModuleId,
  handler_owner_binding: OpaqueOwnerBinding,
  command_version: {major:uint16, minor:uint16, patch:uint16},
  input_schema_ref: SchemaIdWithDigest,
  output_schema_ref: SchemaIdWithDigest,
  error_contract_ref: SchemaIdWithDigest,
  side_effect: READ|PREVIEW|STAGE|COMMIT|EXTERNAL,
  required_capability: NamedCapability,
  project_scope_required: bool,
  target_predicate: ApprovedTargetCapability,
  feature_predicate: ApprovedFeatureRequirements,
  requires_confirmation: bool,
  supports_undo: bool,
  idempotency_policy: AI01OwnerPolicyRef,
  ui_cli_route_ids: array<RouteId>,
  deprecation: Optional<DeprecationV1>,
  owner_receipt_ref: AI01CommandReceiptContract
}
```
The descriptor is an **AI-01 owned source**. Registry build checks existence, only approved owner functions, output/error schemas and route manifest. AI-03 cannot register a different handler on behalf of AI-01 and cannot override any permission.

## 2. Immutable publication and schema types
```text
CapabilitySchemaRefV1 {
  id: stable scoped URI, dialect: "https://json-schema.org/draft/2020-12/schema",
  digest_algorithm: ApprovedHashAlgorithm, digest: bytes,
  media_type: "application/schema+json", local_dependencies: [SchemaRef],
  validation_profile: PinnedProfileId, size_bytes: uint64, provenance: OwnerManifestId
}
CapabilityRegistryGenerationV1 {
  generation_id: opaque, source_commit: GitCommitOid, owner_manifest_digest: bytes,
  schema_bundle_digest: bytes, inventory_digest: bytes, policy_epoch: uint64,
  target_feature_manifest_digest: bytes, schema_profile: PinnedProfileId,
  stage: STAGED|VALIDATING|READY|ACTIVE|REJECTED|RECOVERY_REQUIRED,
  previous_good_generation: Optional<opaque>, verifier_receipt: OpaqueReceiptId
}
CapabilityDescriptorV1 {
  command_id: CommandIdV1, owner: ModuleId, version: {major,minor,patch},
  schema_input: SchemaRef, schema_output: SchemaRef, schema_error: SchemaRef,
  permission: NamedCapability, side_effect: SideEffectClass,
  project_required: bool, requires_confirmation: bool,
  target_features: [FeaturePredicate], ui_cli_routes: [RouteId],
  status: AVAILABLE|UNSUPPORTED|LOCKED|DEPRECATED|REMOVED,
  deprecation: Optional<DeprecationV1>, safe_display_text: BoundedLocalizedText
}
```

## 3. Read-only discovery API (logical, not executable)
| Logical operation | Request | Outcome and failure |
|---|---|---|
| `capabilities.list` | ProjectId, verified actor/grant, target, features, accepted major versions, page limit and bytes/deadline budget | Sorted safe authorized page + generation + opaque cursor; PARTIAL/UNAVAILABLE if required owner unknown |
| `capabilities.describe` | CommandId, supported major/minor, project, target, grant, optional include schema | One visibility-filtered descriptor, no private schema/handler/secret leakage |
| `capabilities.schema.get` | scoped SchemaRef/digest, actor, requested dialect/profile, bytes budget | Valid local public schema, hash readback, unsupported vocab error; no remote resolve |
| `capabilities.compatibility.diff` | old/new generation, client versions, target | Behavioral compatibility evidence and reasoned BREAKING/COMPATIBLE/NEEDS_REVIEW classification |
| `capabilities.coverage.report` | independent owner-approved action-manifest snapshot + registry generation | complete mapped/missing/orphan/excluded set, numerator/denominator and evidence IDs; admin/test access only |
| `capabilities.errors.describe` | CommandId/version, authorized scope | Stable safe error taxonomy and actionable recovery; no raw internal diagnostics |

**None of these read calls may invoke owner mutations.** Every actual `CommandInvocationV1` travels to AI-01, which rechecks actor/ProjectId/permissions/owner source revision and returns owner receipt. No capability enumeration can set flags that upgrade permissions.

## 4. Example illustrative PUBLIC command (not actually registered)
```json
{
  "command_id":"world.scene.inspect",
  "owner":"WORLD-02",
  "version":{"major":1,"minor":0,"patch":0},
  "side_effect":"READ",
  "project_required":true,
  "required_capability":"scene.read",
  "schema_input":{"$schema":"https://json-schema.org/draft/2020-12/schema",
    "type":"object","required":["projectId","sceneId"],
    "properties":{"projectId":{"type":"string","minLength":1},
    "sceneId":{"type":"string","minLength":1}},
    "unevaluatedProperties":false},
  "schema_output":{"$schema":"https://json-schema.org/draft/2020-12/schema",
    "type":"object","required":["ownerRevision","sceneId"],
    "properties":{"ownerRevision":{"type":"string"},"sceneId":{"type":"string"}}}
}
```
Example is a **proposed shape**; actual AssetId/SceneId formats and ownership come from DATA-04/WORLD-02 and must be adopted independently. Runtime UI/CLI/MCP are absent. These schemas validate shape, not actor right to access the named scene.

## 5. Error and state taxonomy
| Code | Condition | Safe recovery |
|---|---|---|
| `REGISTRY_UNAVAILABLE` | No valid signed/verified generation or owner not ready | wait for approved generation; no auto permissive fallback |
| `DESCRIPTOR_NOT_VISIBLE` | unknown/unauthorized command | generic safe response; no command-existence leakage |
| `SCHEMA_UNSUPPORTED_DIALECT` | dialect/vocab not pinned | explicit compatible version or reject |
| `SCHEMA_REFERENCE_FORBIDDEN` | external or cyclic resource beyond budget | local allowlisted bundle only |
| `SCHEMA_INVALID` | malformed schema / input instance fails | safe path/keyword details without raw secrets |
| `CAPABILITY_UNAVAILABLE` | target/build feature absent | supported targets, if disclosure permitted |
| `CAPABILITY_VERSION_MISMATCH` | no compatible semantic major/feature | negotiation/upgrade, never downgrade silently |
| `CAPABILITY_REVOKED` | auth or policy epoch stale | reauthorize and discover new scope |
| `REGISTRY_CURSOR_EXPIRED` | generation, actor, revocation epoch or filter changed | restart authorized page walk |
| `REGISTRY_GENERATION_CONFLICT` | concurrent publish or incompatible owner receipt | retry verified build, preserve prior-good |
| `COVERAGE_INCOMPLETE` | eligible action missing or orphan route | block promotion until independently mapped |
| `REGISTRY_RESOURCE_LIMIT` | depth, CPU, memory, rows, bytes or deadline exhausted | fail bounded, stable backpressure |

Stable errors include trace ID, owner/stage, retryable flag, safe context and recovery. Do not emit exception stacks, project paths, secrets, private capability names or internal handler pointers.

## 6. Compatibility / discovery invariants
- Stable namespaced CommandId never reassigned to another owner/effect. Schema hashes are content-addressed under explicit dialect+canonicalizer profile, not DATA-04 semantic scene hash.
- A change to required arguments, meaning of enum, side effects, consent or privilege is breaking regardless of cosmetic JSON Schema compatibility. Adding an unknown field or enum output is review-required for exhaustive clients.
- An inactive/deprecated command remains discoverable only as explicitly allowed; removal is not silent, including MCP tool name reuse. Clients requesting unsupported major get typed error.
- Pagination is deterministic by CommandId+major+scope; opaque cursor binds generation, request fingerprint, actor/project, auth revocation and page budget. Cannot infer hidden counts, names or schema hashes.
- MCP 2026-07-28 inputSchema **must be a JSON object schema**, outputSchema can describe any JSON value; metadata annotations are hints, not grants. Full adapter protocol belongs AI-04.
- Publish immutable generation only after schema compilation, 100% external inventory coverage, compatibility and provenance checks. Rollback to validated prior-good **does not rollback revoked permissions**.

## 7. Future conformance checks
Use an independent owner/Editor route manifest and command fixture dataset. Enumerate all eligible public authoring operations, perform 100% bijective or approved alias mapping, exercise Editor/CLI/MCP (once available), validate schema instances, owner permissions and source receipts. Cross-version/cross-target compatibility, a11y descriptions, localization, privacy, mutation fuzz and stale/auth race are future; see [matrix](../testing/ai-03-acceptance-matrix.md) and [benchmark](../research/ai-03-capability-benchmark-protocol.md).
