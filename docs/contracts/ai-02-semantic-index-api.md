# AI-02 — Typed Project Semantic Index, Incremental Update, Search, Snapshot and Context API v0.1

**P00 RESEARCH PROPOSAL ONLY / NOT COMPILED / NOT APPROVED | 2026-11-15 | [research #285](https://github.com/KayzenRoot/stormline/issues/285) | BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`.** Logical V1 proposal, not an actual ABI/JSON schema/database or MCP tool. Formal dependencies **AI-01 + DATA-02 only**, both still research/ADR PROPOSED. Future code #76 OPEN/BLOCKED.

## 1. Existing owner contracts are canonical (AI-02 reuses, never duplicates)
| Source | Authoritative proposed types | AI-02 responsibility |
|---|---|---|
| **AI-01** | `CommandIdV1`, `CommandDescriptorV1`, `CommandPrincipalV1`, `CommandInvocationV1`, `CommandReceiptV1`, `CommandCapabilityResultV1` | register READ/QUERY/rebuild commands through shared routing/capability gate, not a privileged search-only endpoint |
| **DATA-02** | `ProjectId`, `AssetId`, `AssetRevision`, `ContentDigest`, `RegistrySnapshotToken`, `RegistrySnapshotV1`, `AssetMetadataV1`, `DependencyEdgeV1`, `SourceProvenanceV1`, `AssetTombstoneV1` | read immutable owner snapshots, verify owner asset ID and change receipts, do not invent new AssetId, second registry or canonical DB |
| DATA-04 (integration) | `SceneRevisionV1`, `SceneDocumentV1`, `ScenePatchV1`, `SceneDiffV1` | consume owner committed scene and schema revisions, not staged source or live dirty GUI state |
| WORLD-02 (integration) | `SceneAssetV1`, `PrefabAssetV1`, `SceneNodeIdV1`, `SceneInstanceIdV1`, `PrefabOverrideV1`, `PrefabRebaseReceiptV1` | project stable scene/prefab graph references; no runtime EntityHandle stored as durable ID |
| GAME-02 (integration) | `ScriptModuleV1`, `ScriptApiSchemaV1`, `ScriptDependencyManifestV1`, `ScriptCompilerReceiptV1` | syntax/symbol/import/source-map projection only from validated owner source snapshots |
| EDIT-01/AI-04/05/06 (later integration) | editor command button, MCP resource/capability, advanced security and context pack | adapt via AI-01 with same scope/bounds; cannot elevate privilege or create circular dependency |

## 2. Proposed versioned logical interface types, NOT an adopted ABI
| Type | Fields/invariants | Authority / behavior |
|---|---|---|
| `SemanticEntryIdV1` | ProjectId, owner namespace/kind and stable owner ID, optional source-symbol path & revision and projection kind | AI-02 **derived key** for search result, not new canonical `AssetId`; rename/move preserves owner source ID |
| `SemanticEntryV1` | EntryId, kind SCENE/PREFAB/ENTITY/COMPONENT/SCRIPT/SYMBOL/ASSET/DOCUMENT/SCHEMA, SourceOwnerId, source AssetId/SceneId/ScriptModuleId/DocumentId/SchemaId, revision+digest, title/labels, typed tags, rights classification, source locator, snippet availability/confidence, recorded source watermark | AI-02 cached projection; originals always owner authority |
| `SemanticEdgeV1` | EntryId source/target, REFERENCES/IMPORTS/CONTAINS/INSTANCE_OF/OVERRIDES/DEPENDS_ON/DOCUMENTS/SCHEMA_FOR, owner revision, provenance, resolved/stale/unsupported confidence | DATA-02 owns asset dependency edges; AI-02 derived references for other owners |
| `SemanticSourceSnapshotSetV1` | ProjectId, owner/source kinds, per-owner immutable snapshot token+revision+manifest/digest, permission policy version, coverage and unsupported owners | derived **revision vector**, no false globally atomic snapshot |
| `SemanticIndexGenerationV1` | ProjectId, generation id, schema/tokenizer/Unicode/ranking policy version, source snapshot set/owner sequence watermarks, ACL policy revision, status, integrity digest/FTS check, updated count, bytes/drops and expiry | AI-02 rebuildable cache generation; no canonical source mutation |
| `SemanticChangeEnvelopeV1` | originating owner, ProjectId, committed OperationId, source stable IDs/from/to revision/digest, changed fields/edges/tombstones, owner sequence and trust, idempotency | source receipt must be **SOURCE_COMMITTED** or stronger, never file-watcher hint |
| `SemanticDirtyPlanV1` | owner change set, scoped reverse-reference closure, changed entries and edges, max_fanout/depth/time, unsupported source/partial info, expected generation | AI-02 local rebuild plan; no mutation to source |
| `SemanticIndexApplyReceiptV1` | prior+new index generations, owner watermark advancement, applied/skipped/invalidated counts, FTS integrity, dropped/partial/rollback state, index bytes/latency and trace reference | AI-02 derived transaction, **not** source commit receipt |
| `SemanticIndexHealthV1` | status UNINITIALIZED/BUILDING/READY/STALE/REBUILD_REQUIRED/RECOVERING/UNAVAILABLE, source coverage/freshness lag, last-good generation, corruption/gaps/drop counters, WAL/storage quota, platform capability | AI-02, redacted and bounded |
| `SemanticQueryV1` | ProjectId, actor/grant, command ID+schema, scope/owner-kind filter, exact EntryId/AssetId or typed text/filter AST, tag/type/revision, graph edge/depth, freshness mode+source revision, `max_rows/max_bytes/max_estimated_tokens/max_snippet_chars/max_edges`, deadline/cancel, requested fields and sort | AI-01 authenticated READ command; **no raw SQL, arbitrary regex/host path, shell, vendor query expression** |
| `SemanticQueryReceiptV1` | source revision vector, index generation/schema, ACL policy/version, coverage, freshness SATISFIED/STALE/PARTIAL/UNSUPPORTED, matched estimate policy, returned rows/bytes/estimated tokens, dropped/truncated, result items, opaque next cursor, safe trace/error | owner checks before result hydration, controlled redaction; never promise exact full count if rights filtered |
| `SemanticResultItemV1` | typed owner ID+AssetId/revision, kind, title, sanitized excerpt, source owner locator+range, provenance/license visibility, matching field, score/raw rank policy, edge explanation, required capability, confidence and availability, stable tie-break | no arbitrary file dump, **not owner authority nor model-generated fact** |
| `SemanticCursorV1` | opaque signed/validated candidate: ProjectId+actor/policy binding, normalized query digest, generation, sort key, schema/ranking version, exp/nonce | cursor is **not** a bearer token; authorization recheck and rejection on ACL/index generation change |
| `SemanticContextBudgetV1` | maximum returned bytes/rows/Unicode chars/estimated tokens/graph depth/time; counting basis and optional pinned tokenizer identifier | provider-neutral budget defaults; estimated tokens ≠ exact ChatGPT/Claude/Gemini counts |
| `SemanticContextPackV1` | ProjectId, query digest, source/index generation, ordered short entries with citation locators/revisions, bytes/token estimate, partial/unsupported/omitted counts, rights/PII safety and freshness | AI-02 **read-only** context, not AI-05 resources or summary generation |
| `SemanticSourceLocatorV1` | owner-qualified stable source ID/AssetId, exact source revision/ContentDigest, component/symbol path/range, safe relative logical URI only | owner resolves after grant; display path is not identity |
| `SemanticQueryErrorV1` | stable code, source/index/ACL stage, retryability, owner revision, sanitized scope, recovery/rebuild action | never raw private path SQL/stack/secret |

## 3. Command and operation examples, only FUTURE
All enter AI-01 `CommandInvocationV1` with role/capability/project scope and version:
| Candidate CommandId | Operation | Side effect / gate |
|---|---|---|
| `semantic.status.inspect` | bounded index health, schema/tokenizer/coverage/freshness | READ scope, no cross-project counts |
| `semantic.query` | text+structured filters, exact IDs, finite top-k and context budget | READ, deny before index query and owner recheck before each excerpt |
| `semantic.asset.references` | bounded DATA-02 dependency neighbors & source locators | READ, owner EdgeKind and project ACL, cycles/limits |
| `semantic.scene.symbols` | scene hierarchy/ScriptModule/Symbol query via owner references | READ, owner source-map revision required |
| `semantic.context.pack` | minimal cited revision-scoped ordered snippets | READ, no LLM or external HTTP, token budget approximate |
| `semantic.change.status` | source watermark/dirty/lag snapshot by scope | READ, no privileged debug metadata |
| `semantic.index.plan` | explain rebuild/scope/cost and source fingerprint | PREVIEW, no source mutation |
| `semantic.index.rebuild` | rebuild **derived projection** only from owner snapshots | MAINTENANCE capability, bounded job/priority and no canonical delete |
| `semantic.index.cancel` | cancel background rebuild safely | maintenance actor grant, retain prior verified generation |

## 4. Query and indexing state/freshness contracts
- **State machine:** UNINITIALIZED → SCANNING_SOURCE → BUILDING → VERIFYING → READY. Committed source receipt: READY → DIRTY → APPLYING → VERIFYING → READY. Failure CORRUPT/REBUILD_REQUIRED/STALE/RECOVERING/UNAVAILABLE, last-good generation retained per policy.
- **Sources:** verify ProjectId+owner+source revision and checksum/digest before consuming. File watcher is hint only. Update coalescing by owner OperationId+source revision, idempotent changed asset/symbol; source tombstones drop FTS terms and excerpts; no ghost hits.
- **Consistency modes:** REQUIRE_AT_LEAST_SOURCE_REVISION (wait bounded then INDEX_STALE), SNAPSHOT_EXACT (pinned generation and matching source-vector), ALLOW_STALE_WITH_PROVENANCE (explicit watermark/partial and ACL recheck). Failure can't claim READ_YOUR_WRITES if source commit not indexed yet.
- **Cursor:** keyset fixed ranking+stable EntryId and source revision; generation/policy/actor/query/sort/expiry bound; no offset across concurrent generations. Reject stale/forged/foreign scope cursor.
- **Security:** authorize project, kind, field and owner before fetching candidates, and again on actual source/snippet hydration. No existence/count/timing oracle by unauthorized query where practical; no stale grant resurrection. No cache of plaintext secrets as default.
- **FTS5 backend candidate:** update external-content table and FTS atomically **within index DB**, backfill old rows before READY, integrity-check/rebuild; index DB is independent of canonical DATA-02/VFS/DATA-04 commit. SQLite snapshot readers bounded to avoid WAL growth and disk-flood.
- **Schema/tokenizer:** pin version+Unicode/text normalization; incomplete unknown owner schema signals PARTIAL/UNSUPPORTED, never silently drops source or hallucinates script symbols.
- **Completeness:** `INDEX_READY` refers to specified owner set and revision vector only, not ALL possible future sources. Return `coverage`, with `unavailable_owners` and no false total hits.

## 5. Reproducible output and failure codes
Sort exact matches first by declared policy (or deterministic rank bucket) then kind/EntryId/source rev. Return actual source citations and immutable revision IDs, not freeform AI explanations. Graph walk bounded with visited set; cycles are not silently pruned as non-existent edges. Source snippets **data only**, escaped; HTML/terminal control, prompt instructions or markdown links aren't executed. Redaction happens at indexing where policy requires AND at hydration.

Errors: `A02_SOURCE_KIND_UNSUPPORTED`, `A02_INDEX_NOT_INITIALIZED`, `A02_INDEX_STALE`, `A02_SOURCE_WATERMARK_GAP`, `A02_SNAPSHOT_EXPIRED`, `A02_INDEX_GENERATION_MISMATCH`, `A02_INDEX_SCHEMA_UNSUPPORTED`, `A02_TOKENIZER_VERSION_MISMATCH`, `A02_INDEX_CORRUPT_REBUILD_REQUIRED`, `A02_FTS_CONTENT_MISMATCH`, `A02_WAL_QUOTA_EXCEEDED`, `A02_SCOPE_DENIED`, `A02_ACL_POLICY_STALE`, `A02_FIELD_REDACTED`, `A02_CURSOR_INVALID`, `A02_CURSOR_REVOKED`, `A02_QUERY_INVALID`, `A02_QUERY_BUDGET_EXCEEDED`, `A02_RESULT_PARTIAL_BUDGET`, `A02_SOURCE_REVISION_STALE`, `A02_SOURCE_LOCATOR_UNRESOLVED`, `A02_GRAPH_FANOUT_LIMIT`, `A02_DEPENDENCY_CYCLE_DETECTED`, `A02_REBUILD_CANCELLED`, `A02_RECOVERY_REQUIRED`, `A02_OWNER_UNAVAILABLE`, `A02_EMBEDDING_UNSUPPORTED`. Each returns safe stage, retryability, source/owner index version and recovery hint, never secret/host path.

## 6. Future acceptance oracle
For identical owner snapshots, permissions and query, verify same typed IDs/edges and deterministic result order under pinned ranking/tokenizer, source citation and revision. After changing one asset/document/script/scene through authorized AI-01/owner transaction, assert incremental dirty closure and fresh result with new watermark and no reindex of unrelated records. On ACL revoke or source delete, no stale result/excerpt/count/cursor. Compare cold rebuild results to incremental results by EntryId/revision/edge sets; FTS ranking must be stable within pinned policy. Context pack must satisfy max bytes/rows and approximate token budget with exact byte accounting, not dump project source.

All APIs **PROPOSED/NOT IMPLEMENTED**; no actual SQL schema, generated ABI, MCP resource, executable test, index, benchmark or embedded model.

[Architecture](../architecture/ai-02-project-semantic-index.md) · [ADR-0061](../adr/0061-ai-02-rebuildable-authorized-semantic-index.md) · [128 tests](../testing/ai-02-acceptance-matrix.md) · [Benchmark protocol](../research/ai-02-semantic-index-benchmark-protocol.md).
