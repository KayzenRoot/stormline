# AI-05 — Proposed Typed Context Resource, Template, Recipe and Citation Contracts v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT COMPILED | [research #297](https://github.com/KayzenRoot/stormline/issues/297) | NLE-P00-WO-002-AI-05 | future code #79 OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Formal deps AI-02 + AI-04 only. ADR-0064 PROPOSED, ADR-0061/0063 PROPOSED, NLE-D009 OPEN; 80/80 code WOs blocked.

All types below are **logical candidates, not an adopted JSON Schema, C++ header, ABI, MCP endpoint, parser, database or implementation.** MCP 2026-07-28 and actual negotiated host protocol wire schema remain AI-04-owned.

## 1. Canonical owner ports
| Owner | Input to AI-05 | Authority boundary |
|---|---|---|
| AI-02 | SemanticQueryV1, SemanticQueryReceiptV1, SemanticContextPackV1, SemanticCursorV1, index health/coverage/freshness, owner source locator | sole source of search, rank, committed revision vector, authoritative excerpts and owner ACL rechecks |
| AI-04 | McpRequestContextV1, McpResourceProviderPortV1, McpPromptProviderPortV1, version/transport/capabilities, subscriptions/listen | sole protocol adapter, JSON-RPC/HTTP/stdio/auth transport; AI-05 returns logical resource/provider outcomes |
| DATA-02/AI-01 (transitive) | ProjectId, AssetId, source revisions, actor/grant, owner read receipt | no direct new AI-05 formal dependency or side-channel owner access |
| AI-03/DATA-04/WORLD-02/GAME-02 (integration) | schema IDs, SceneIR/ScriptModule/Document source refs if available | no AI-05 schema database, raw file reading, code execution or source authority |

## 2. Proposed type inventory
| Type | Fields | Key invariant |
|---|---|---|
| `ContextCatalogEntryV1` | stable ResourceId, ProjectId, owner namespace, EntryKind, title/locale, URI, MIME, SourceLocatorRef, rights visibility, icon metadata, source revision, availability | authorized before listed; not every index hit becomes a public entry |
| `ContextResourceTemplateV1` | template ID, version, RFC6570 URI template string, approved argument schema (scalar IDs), owner source kind, availability, output MIME, fixed policy | all URI operators and variables allowlisted; no generic path/URL expression |
| `ContextResourceRequestV1` | AI-04 VerifiedRequestContext, resource URI or template+typed variables, freshness policy, max bytes/rows/depth/time, optional cursor, intended representation version | owner/project/policy verification before resolve and dereference; no raw path |
| `ContextSourceCitationV1` | ProjectId, authoritative SourceOwnerId/owner revision, stable AssetId/SceneId/ScriptModuleId/SchemaId, owner content digest, locator/section/range, rights/provenance, redaction marker | source existence and revision proven by owner; never LLM-invented |
| `ContextSectionV1` | section kind, summary/structural fields/snippet, source citation, byte count, estimated tokens, visibility, omitted fields | source is escaped untrusted data; size bounded |
| `ContextCapsuleV1` | capsule version, project/source revision vector, AI-02 index generation, policy epoch ref, requested freshness, actual freshness, coverage/partial owners, ordered sections/citations, budget receipt, next cursor, errors | read-only projection, not authoritative source or operation proposal |
| `ContextBudgetV1` | max entries, bytes, UTF-8 chars, estimated tokens, owner graph depth/edge count, pages, deadline, optional tokenizer version | enforce UTF-8 bytes deterministically; token estimates approximate without pinned tokenizer |
| `ContextBudgetReceiptV1` | actual bytes/items/edges, estimated tokens + tokenizer basis, omitted/rejected counts, truncation reason, next page, source coverage and owner watermark | no silently truncated JSON or unqualified "complete" |
| `ContextPageCursorV1` | opaque signed/validated envelope over actor/project/grant/policy epoch, query/filter hash, AI-02 generation/source vector, sort/representation version, expiry/nonce | cursor is not an auth grant; recheck ACL per page |
| `ContextRecipeManifestV1` | stable recipe ID, semver, locale, title/description, named-string arguments, required resource refs, capability hints, rights, author and policy, outcome type | user-selected prompt only; never implicit command execution |
| `ContextPromptResultV1` | selected recipe ID/version, escaped argument values, messages with safe role and text/embedded resource refs, citations, missing/unsupported dependencies | prompt data not privilege; owner tools invoked separately |
| `ContextCompletionQueryV1` | approved prompt/template ref, argument name, typed prefix, prior argument context, actor/project/policy, max suggestions/deadline | no hidden names, unauthorized suggestions or arbitrary FTS syntax |
| `ContextCompletionResultV1` | ordered sanitized suggestion values, optional total allowed matches, hasMore, source policy epoch, validity status | maximum 100 MCP values; never global counts over hidden records |
| `ContextAvailabilityV1` | READY, PARTIAL, INDEX_STALE, SOURCE_UNSUPPORTED, OWNER_UNAVAILABLE, DENIED/NOT_FOUND_GENERIC | never fabricate missing content |
| `ContextReadErrorV1` | stable code, stage, retryability, freshness/owner revision redacted, suggested recovery, trace ID | no private host paths, source content, secrets, unauthorized existence |

## 3. URI and template examples, candidates only
```text
stormline://context/v1/{projectOpaqueId}/project/summary
stormline://context/v1/{projectOpaqueId}/scene/{sceneId}/outline{?revision}
stormline://context/v1/{projectOpaqueId}/asset/{assetId}/provenance{?revision}
stormline://context/v1/{projectOpaqueId}/script/{moduleId}/symbols{?revision}
stormline://context/v1/{projectOpaqueId}/doc/{documentId}/excerpt{?revision}
stormline://context/v1/{projectOpaqueId}/schema/{schemaId}{?revision}
```

In examples `{projectOpaqueId}`, `{sceneId}` etc are *restricted URI template variables*, not user-submitted arbitrary file paths or generic glob. Variable matching must validate typed canonical IDs *before* RFC6570 expansion; percent-encoded string cannot become a path delimiter after a second decode. `{+path}`, `{#fragment}`, `../`, `file://`, `https://`, `data:` and arbitrary URI authority switching are forbidden in the proposed resource provider. An MCP URI may be visible to an untrusted host; never embed token/secrets in it.

## 4. Logical provider functions
```text
list_context_resources(VerifiedContext, ListFilters, Budget, Cursor?)
    -> AuthorizedContextPage | ContextReadError

list_context_templates(VerifiedContext, ResourceKinds, Budget, Cursor?)
    -> AuthorizedContextTemplatePage | ContextReadError

resolve_context_uri(VerifiedContext, URI, Freshness, Budget)
    -> ContextCapsule | ContextReadError

list_context_recipes(VerifiedContext, Locale, Budget, Cursor?)
    -> AuthorizedRecipePage | ContextReadError

get_context_recipe(VerifiedContext, RecipeId, NamedStringArgs)
    -> ContextPromptResult | ContextReadError

complete_context_argument(VerifiedContext, PromptOrTemplateRef, Argument, Prefix, PriorArgs, Limit)
    -> ContextCompletionResult | ContextReadError
```

All functions are proposed provider ports called *by AI-04*. They do not themselves open sockets, create protocol sessions, call an LLM, execute tools, mutate scenes/assets/source, create files or run scripts.

## 5. Response and freshness flow
1. AI-04 authenticates and verifies `principal/project/grant/policy_epoch` per request.
2. AI-05 parses/normalizes an allowlisted logical URI/template, checks resource family/rights and caller budget.
3. AI-05 asks AI-02 for bounded owner-index query or ContextPack using source revision/freshness constraints.
4. AI-02 validates project/kind authorization before candidate retrieval and checks actual canonical owner source rights before each hydration; AI-05 independently confirms returned source locator, digest/revision and rights policy.
5. AI-05 packages ordered ContextCapsule sections and citation/provenance, clips only at **whole section boundaries** to preserve structured validity, reports partial/omitted data and safe nextCursor.
6. AI-04 maps logical result to MCP wire resource content and modern cache hints; legacy compatibility only if negotiated by AI-04.
7. Subsequent page/URI/dereference must reauthorize, not trust previously issued cursor or client cache.

**Consistency modes inherited from AI-02:** REQUIRE_AT_LEAST_SOURCE_REVISION (bounded wait or INDEX_STALE), SNAPSHOT_EXACT (generation retained or SNAPSHOT_EXPIRED), ALLOW_STALE_WITH_PROVENANCE (explicit watermarks, never stale ACL). No global transaction guarantee across owners.

## 6. MCP wire mapping (AI-04-owned)
| MCP operation | Logical provider | Behavior |
|---|---|---|
| resources/list | list_context_resources | deterministic bounded page; nextCursor scoped; no hidden counts |
| resources/templates/list | list_context_templates | RFC6570 typed templates only; stable namespace and explicit MIME |
| resources/read | resolve_context_uri | source-aware read-only text or bounded binary data; ttlMs/cacheScope per negotiated protocol |
| prompts/list | list_context_recipes | stable user-selected recipe names/flat string arguments |
| prompts/get | get_context_recipe | bounded messages with escaped source text, no command execution |
| completion/complete | complete_context_argument | optional, max 100 sorted allowed values; no ACL leakage |
| subscriptions/listen | AI-04 only | optional notifications on lists/URI changes, not canonical source reads |

MCP 2026-07-28 requires `resultType:complete` and modern cache hints on eligible responses. AI-05 returns logical provider objects; **never directly constructs JSON-RPC request/response wire payloads** or assumes a particular SDK version. In legacy 2025-11-25, AI-04 adapts response structures and supported methods.

## 7. Pagination, ordering, caching and cancellation
For an immutable owner generation + query + policy: deterministic keyset ordering (owner type rank, stable owner ID, source revision); no random ranking or external LLM. Enforce max pages/bytes/context, reject invalid or expired cursor and source revision changes. Avoid exposed global count when ACL filters. `ttlMs=0` and `cacheScope=private` default for project-specific resources; positive TTL conditional on rights and immutable content. A cache already delivered to host cannot be erased by server revocation. Subscriptions are hints; source revision is read from owner. Cancellation interrupts bounded composition without claiming rollback. No background task handles by default.

## 8. Error and recovery contract
| Code | Trigger | Safe action |
|---|---|---|
| A05_INVALID_URI | unknown scheme, invalid variable/percent escape, path traversal | correct typed opaque ID |
| A05_TEMPLATE_ARGUMENT_INVALID | unsupported variable/operator/type | use advertised template |
| A05_RESOURCE_UNAVAILABLE | owner source kind not implemented | report unsupported/partial, do not fabricate |
| A05_INDEX_STALE | AI-02 generation behind required owner revision | bounded refresh or explicit retry |
| A05_SNAPSHOT_EXPIRED | pinned owner/index generation evicted | re-list and obtain fresh citation |
| A05_POLICY_REVOKED | actor/grant/policy epoch no longer valid | deny subsequent reads and invalidate cursors |
| A05_CURSOR_INVALID | expired/forged/cross-actor/generation cursor | re-list; never trust cursor as auth |
| A05_BUDGET_EXHAUSTED | bounded context size reached | return valid partial capsule if policy permits |
| A05_SOURCE_REDACTED | rights/PII/secret classification forbids excerpt | return metadata-only/denial per owner policy |
| A05_RECIPE_UNSUPPORTED | missing required capability, locale or owner context | user-facing unsupported, no tool call |
| A05_PROMPT_ARGUMENT_INVALID | malformed missing required named-string arg | invalid-params result, no execution |
| A05_COMPLETION_LIMIT | invalid prefix/large result count | bounded suggestions or denial |
| A05_CONTENT_UNTRUSTED | unsafe markup/control/embedded fetch | escape/redact or decline |
| A05_OWNER_UNAVAILABLE | canonical source unavailable | explicit partial/failure, never stale source as fresh |

For unauthorized resources, public responses may deliberately collapse DENIED and NOT_FOUND_GENERIC to avoid enumeration; detailed redacted traces remain internal.

## 9. Acceptance invariants
- No source name, size, existence, count, cursor, completion or excerpt crosses project/principal rights.
- For fixed owner revision and policy, same ordered sections/source citations and exact UTF-8 bytes; token estimates labeled approximate unless tokenizer pinned.
- Any successful resource read includes owner citation/revision/freshness/rights and honest coverage; no entire repository read.
- Prompt selection never commits or authorizes action. Malicious embedded prompt is inert data.
- URI template expansion never becomes filesystem/network access.
- Source/index changes, rights revocation and crash/rebuild degrade explicitly, never silently return obsolete/private content.
- 128 A05-T001..A05-T128 tests are FUTURE/NOT EXECUTED; conformance, host integration and benchmarks require real runtime.

[Architecture](../architecture/ai-05-context-resources-templates.md) · [ADR-0064](../adr/0064-ai-05-authorized-context-projections.md) · [Testing](../testing/ai-05-acceptance-matrix.md).
