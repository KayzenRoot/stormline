# DATA-04 — Versioned Scene Serialization, Semantic Diffs and Safe Migrations

**WO:** NLE-P00-WO-002-DATA-04 | **Research issue:** #117 | **Future code issue:** #27
**State:** RESEARCH PROPOSED / NO CODE | **Context Lock main:** 3f03773cf5ca9cba0d2ebda4b6c142f0fc93e45d
**Risk:** LOW docs, ELEVATED future persistence, migration, collaboration and project integrity.

## Mission and architectural boundary

Stormline needs portable, editable, secure and versioned serialization for 2D, 2.5D, 3D scenes and project documents. Preserve artist edits and AI-authoring changes while supporting engine updates, file review in Git, headless tooling and Windows/Linux/macOS/Web portability. The authoritative authoring representation is **proposed** as strict UTF-8 JSON under a Stormline-owned semantic schema with stable IDs. **It is not yet an approved or implemented wire format.** Packed runtime representations are DATA-05, and runtime entity execution belongs WORLD/SIM, not DATA-04.

Ownership:
- **CORE-05** owns coordinate/unit/value conventions, numeric precision and runtime identifiers.
- **DATA-01** owns capability-scoped VFS paths, staged writes and file recovery primitives; does not provide cross-file/DB ACID.
- **DATA-02** owns durable AssetId, asset revision, provenance and dependency index. Scene references AssetId, never makes path/hash the identity.
- **DATA-03** owns importer-specific parsing/conversion and import receipts. DATA-04 stores references and author-controlled composition, not decoder ASTs.
- **DATA-04** owns canonical scene/project schema, semantic validation, roundtrip, diff, merge and migration plans/receipts.
- **DATA-05** owns packaged binary runtime bundles and target cooking. Runtime binary codecs must not rewrite authoritative authoring data.
- **WORLD/EDIT/AI** consume typed scene operations and shared schema; no direct privileged low-level mutations from MCP.

## Proposed two-layer representation

1. **Authoritative source**: versioned SceneDocument with project namespace, scene ID, schema dialect/version, format revision, required capabilities/plugins, entity table, component table, reference table, authored defaults, extension fields and provenance references. Editable text is pretty-printed with stable ordering and LF line endings to minimize Git noise; comments are not permitted in the authoritative core syntax. Human notes live in typed metadata, so parse/write preserves them.
2. **Validated semantic SceneIR**: in-memory typed graph obtained only after safe parse, schema validation, identity checks and reference-resolution planning. Serializer does not create runtime scripts, ECS systems or plugin objects from untrusted payloads.
3. **Optional cached compiled representation**: binary scene artifacts for shipping, mapped by revision and toolchain fingerprint. FlatBuffers, Protobuf, Cap'n Proto and owned chunked encoding are candidates for DATA-05 comparison; never imply bitwise identical versions without proof.
4. **Extension policy**: namespaced, schema-versioned plugin component payloads may roundtrip as opaque safe data. Unknown optional fields are preserved with byte/semantic fidelity policy, size budgets and upgrade report; unknown **required** component types/capabilities prevent unsafe activation or editing. A scene can enter inspect-only/read-only mode rather than discard or instantiate unknown content.

## Invariants and canonicalization

- Persistent SceneId/EntityId/ComponentInstanceId do not depend on display name, hierarchy path, asset file path or array position; distinguish durable IDs from generation-counted runtime handles. DATA-02 AssetId is an explicit typed reference.
- Strongly typed reference kinds: entity, component, prefab, asset, external scene; unresolved references and cycles are diagnosed with a bounded graph walk. Cycles are allowed only if schema declares semantic legality; hierarchy/transform parent cycles reject before commit.
- Coordinate policy follows proposed CORE-05 right-handed Y-up, meters and radians with double precision where world-space needs it; stored unit/axis are explicit or schema-defaulted with a recorded conversion history. No silent coordinate conversion.
- Strict UTF-8, no duplicate object keys, no invalid surrogate/scalar, no NaN or Infinity, no numeric overflow, no implicit coercion. Normalize -0 and finite floating representations by a versioned policy to be verified against platform fixtures.
- Use a stable writer order for source text: sorted entities by stable ID when order has no semantics; explicit separate order arrays for layer, scene draw order, child order and animation tracks where order matters.
- **RFC 8785 JCS is only a candidate for content hashes/signatures**, not a human-friendly editing layout. JCS has IEEE-754 number constraints and UTF-16 key sorting; 64-bit IDs must be typed strings. A naive C++ map sort or JSON pretty printer is not automatically JCS-conformant.
- Fingerprints use algorithm-tagged digests and canonicalization_version; canonical text is not a guarantee of cross-platform bitwise replay. Structural semantic equality is separately specified and tested.
- Size/depth/field/entity/component/string/ref count quotas; rejected schema must never partially mutate live scenes.

## Versioning and extensibility

Proposed fields include schema_id, schema_version, document_version, project_id, scene_id, document_revision, required_features, required_plugin_schemas, asset_refs, entities, components, authoring_metadata, extensions, and optional migration_receipts. All identifiers are strings conforming to explicit validation, never raw arbitrary JSON numbers.

- Schema compatibility distinguishes backward-readable, forward-readable with opaque optional preservation, and incompatible required features. New fields need declared default/semantic meaning; removal or reinterpretation requires migration.
- ComponentTypeId uses registered namespace + version + immutable type identity. Plugin component payloads stay data until signed/authorized executable plugin capability is verified **outside DATA-04**; a schema is not an executable plugin loader.
- Deserializing an old document does not upgrade it silently. Open -> Inspect -> Validate -> PlanMigration -> Preview -> Backup/Stage -> Verify -> Commit -> Receipt -> Reopen/Recovery.
- Migration graph is explicit, bounded and acyclic for version forward transitions. Downgrades are not promised; unsupported downgrades fail with a recoverable report.
- Migration functions are deterministic, pure with respect to input SceneIR and pinned schema/transform versions whenever possible. Any side effects must be declared and staged through DATA-01/DATA-02.
- Golden compatibility corpus per schema revision, plugin unknown-field corpus, documented deprecations, and CI detection of accidental schema breakage.

## Semantic diff, merge and human/AI concurrency

Compare normalized, validated semantic graphs **by stable IDs and typed field paths**, not raw text lines or unstable array indices. Operations: CreateEntity, DeleteEntity, SetField, RemoveField, AttachComponent, DetachComponent, MoveParent, Reorder, SetAssetRef, SetRequiredCapability. Each operation carries expected_revision and optional expected_old_value_hash plus idempotency key and provenance actor category.

- Distinguish set-like collections from order-sensitive sequences. Never sort gameplay order merely to make diffs deterministic.
- Preview returns changed fields, dependency impact, unknown-field policy, required permissions, budget estimate and explicit conflicts.
- Three-way merge uses shared base revision. Nonoverlapping edits may merge; same field or hierarchy conflicts require user-visible resolution, never silently last-writer-wins.
- Undo/redo is not destructive rollback of an unrelated later edit: use explicit inverse operation with precondition on current revision, preserving conflict records and old revision.
- All Editor/CLI/MCP operations pass the same semantic command validation. MCP may inspect/preview under scopes; commit is denied without authority, explicit project capability and revision precondition.
- Stormline Semantic Scene Delta (SSD) is an R&D **prove-or-drop** idea for compact explainable patch plans, compared against ordinary ID-aware AST diffs/JSON Patch; do not create a second source of truth or assume speed benefit.

## Durability and recovery state machine

READ_ONLY_INSPECT -> VALIDATE -> PLAN -> PREVIEW -> STAGE -> VERIFY_STAGED -> INTENT_RECORDED -> COMMIT_FILE -> RECONCILE_REGISTRY -> COMMITTED. Errors may lead to ABORTED (before commit) or RECOVERY_REQUIRED (after intent). Use operation IDs and retained prior-good revision; no false atomicity across filesystem files and DATA-02 derived index/SQLite.

- Data-01 scoped VFS mediates reads/writes; project-local stage and backup with quota and ownership validation.
- Validate project/base revision, source hash and exact schema snapshot **again before commit**. Reject stale edits with conflict summary.
- For multi-file project updates, use recoverable journal/manifest and a recovery protocol. Ensure crash between staged writes and index reconciliation cannot expose an acknowledged partially committed project.
- Never delete prior-good schema bytes until readback/validation and retention policy allow it. Restore/replay is idempotent after repeated crash.
- Unknown plugin data, user metadata and asset references survive migration or migration fails; report exceptions before committing.
- Migration may be irreversible. Explicitly classify reversible vs rollback-via-backup; no invented mathematically invertible transformation guarantee.

## Security, privacy, licensing

Threats: malformed JSON, extreme nesting/strings/entity explosion, duplicate keys, cyclic graph reference attacks, huge opaque plugin blobs, numerical extremes, path escape, unauthorized scene updates, deserialization-based code execution, hidden private metadata, prompt injection inside names/notes, downgrade/version spoof, hash collisions and unsafe migration code.

- Parse under bounded quotas and validated encoding; no network, shell, reflection-based constructors or dynamic code execution in scene parser.
- VFS-scoped resource resolution, no absolute host paths or credentials serialized by default; semantic fields may contain adversarial text and must be treated as data, not developer instructions.
- No reliance on JSON Schema alone for cross-reference invariants, authorization, plugin capabilities or migration transactional proof.
- Treat scene file rights and third-party library dependencies separately; exact tag, notices, SBOM, CVE/sanitizer review before shipping.
- Generated examples and fixture assets must be original or rights-cleared; avoid protected game content.

## Future performance and portability proof

Measure parse, validate, serialize, diff, merge and migration p50/p95/p99 and peak RSS/bytes on 1k/100k/1m entities with explicit component density and size; avoid assuming million-entity authoring is a mandatory v1 performance target. Check cold/warm IO, textual diff size, runtime binary footprint as optional, and headless/Windows/Linux/macOS/Apple Silicon + browser adapter semantics. Specify reproducible corpus, compiler/schema versions, CPU/OS/hardware, seeds, failure counts and actual benchmark logs before a performance claim.

### Gates before executable #27
Approved global release class/DoD; DATA-01/02 and CORE-05 implemented predecessor interfaces; exact schema/codec versions and license evidence; target source paths and CI commands; schema IDs and migration corpus; detailed command auth and rollback; future test passes; fresh SHA-256 Context Lock. These docs **do not** unblock Zcode.

See [technology matrix](../research/data-04-scene-technology-matrix.md), [ADR-0012](../adr/0012-data-04-scene-schema-policy.md), [semantic API](../contracts/data-04-scene-api.md), [future tests](../testing/data-04-acceptance-matrix.md).
