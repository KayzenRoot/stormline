# AI-05 — MCP Context Resources & Templates Architecture v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | [research issue #297](https://github.com/KayzenRoot/stormline/issues/297) | Work Order NLE-P00-WO-002-AI-05 | [future code #79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Research baseline: 60/80 documented, 20 pending; 80/80 code WOs BLOCKED, zero engine; NLE-D009 license OPEN. Formal dependencies **AI-02 + AI-04 ONLY**, whose ADR-0061/0063 are PROPOSED.

## 1. Product objective and independently observable acceptance
The AI-05 catalog acceptance is **"Agente descobre estrutura sem copiar repositório inteiro."** To prove it, an authorized host must navigate project, scene, asset, script-symbol, schema, documentation and curated recipe context through bounded MCP listings and targeted reads. A labeled query fixture must demonstrate that selected resources contain the relevant source references and revision/rights information, with smaller total transferred context than a rights-equivalent full-project dump; **no fixed reduction, token count, latency, search recall, or host interoperability is claimed without measurements**. It must preserve access controls, freshness and completeness reporting. An unsupported owner/partial index must be explicitly reported, not fabricated.

AI-05 is a *read-only, derived, revision-aware context presentation layer*, not a second project index, canonical asset database, file reader, MCP wire server, command router, LLM, code generator, data migration tool or authorization grant issuer. MCP prompts/recipes are *descriptive user-invoked templates*, never self-executing tools.

## 2. Formal dependency and ownership graph
```text
Human selection / Codex / Claude / other MCP host
                     |
            AI-04 MCP protocol adapter
    resources/list, resources/templates/list, resources/read
       prompts/list, prompts/get, completion/complete
                     |
      AI-05 Authorized Context Provider (this module)
   catalog | render | citation | budget | context recipes
                     |
       AI-02 Project Semantic Index (read projection)
       bounded query | owner revision vector | source locator
                     |
  AI-01 / DATA-02 / DATA-04 / WORLD-02 / GAME-02 owners
```

**Formal dependencies exactly AI-02 + AI-04.** AI-02 research ADR-0061 is PROPOSED and code #76 BLOCKED; AI-04 research ADR-0063 is PROPOSED and code #78 BLOCKED. AI-01/AI-03/DATA-02/DATA-04/WORLD-02/GAME-02/EDIT and AI-06 are transitive or integration owners only, not new DAG edges. The providers do not elevate those dependencies' research-only status.

- **AI-02** owns rebuildable semantic index, committed source revision vector, index generation, source provenance, query sort/ACL, signed/opaque generation-bound cursors and bounded cited snippets. Its SemanticContextPack is a read-only retrieval result, not an MCP resource.
- **AI-04** owns the actual negotiated MCP wire semantics, resource/template/prompt endpoints, version negotiation, subscriptions and transports. AI-05 never emits raw JSON-RPC nor overrides the MCP auth gate.
- **AI-05** owns logical resource inventory policy, resource URI identifiers and versioned template/recipe declarations, context-pack composition and size policy, safe formatting, citation normalization and an AI-04 provider adapter interface. It does not rewrite AI-02 entries, synthesize authoritative source IDs or directly mutate project source.
- **Canonical owners** retain stable ProjectId/AssetId, SceneRevision, ScriptModuleId, SchemaId, owner commits/readback, security grants and license/provenance. Data availability is scoped to actually integrated owners.
- **Future AI-06** may refine grant management but authorization is mandatory now via AI-04 verified principal/context and AI-02 owner-rechecked ACL. No implicit permission when AI-06 code is absent.

## 3. Context discovery model: progressive disclosure, not repository export
A proposed multi-step workflow:
1. **Inventory:** `resources/list` returns an intentionally small project-scoped set of stable entry resources such as project synopsis, module summaries, permitted root scenes and schema catalog. `resources/templates/list` advertises parameterized, bounded categories; it must not enumerate every symbol/asset.
2. **Select:** host or user chooses an eligible resource or specific template URI; autocomplete is optional, filtered, and bounded. An index search uses AI-02's typed query port; do not invent a new unrestricted MCP search endpoint. If tool-based search is required, route it through an AI-01/AI-03 owner descriptor projected by AI-04, never as privileged resource side effect.
3. **Hydrate:** AI-05 requests a particular AI-02 generation/snapshot and owner-validated source references, with explicit context budget, freshness mode and grant. It formats a small, typed Context Capsule with enough citation/provenance data to verify exact revisions.
4. **Expand:** host may select further resource URIs or next pages, each requiring a fresh read authorization; no automatic whole-repository traversal. Unknown owner/source or insufficient evidence returns coverage=PARTIAL/UNSUPPORTED or typed error.
5. **Operate separately:** any edits/builds/exports remain AI-01 commands and AI-04 tools. `prompts/get`, `completion/complete` and `resources/read` cannot commit anything.

Catalog seed families (examples, not implemented): `project/summary`, `project/schema-catalog`, `scene/{sceneId}/outline`, `scene/{sceneId}/object/{objectId}`, `asset/{assetId}/provenance`, `asset/{assetId}/references`, `script/{moduleId}/symbols`, `script/{moduleId}/symbol/{symbolId}`, `doc/{documentId}/excerpt`, `capability/{commandId}/schema`, `diagnostics/{reportId}/summary`. Any family lacking an authorized source provider returns UNSUPPORTED; these are not claims of an existing asset reader, code compiler or diagnostic engine.

## 4. Resource identity and RFC 6570 template safety
Proposed logical opaque URI: `stormline://context/v1/{opaqueProjectId}/{kind}/{opaqueOwnerId}{?revision,view}`; literal URI authority, grammar and encoding need an exact approval before code. The public MCP resource URI is *a locator and cache key*, not a bearer capability or direct filesystem path.

- Template expansion must conform to **RFC 6570** for supported operators. Limit server-authored templates to a reviewed subset of named, scalar ID fields; reserved expansion such as `{+path}`, unconstrained path splats, fragments and user-provided schemes are forbidden by design. Never concatenate an unsanitized path, `../`, percent-encoded separator, NUL or double-decoded Unicode into a filesystem path.
- Parse/normalize once to the canonical UTF-8 percent-encoding policy and compare against typed owner IDs. Reject duplicate conflicting query keys, ambiguous percent encodings, path traversal, URI confusion and arbitrary `http(s)://` / `file://` / `data:` dereference.
- Stable ID survives source rename/move; resource revision and content policy identify the rendered view. Never treat content hash, display filename, runtime handle or path as source identity.
- No untrusted icon fetch, external image URL or embedded resource may trigger privileged network access. MIME and binary sizes are bounded; when unavailable, give a typed metadata-only result rather than smuggling external links.

## 5. Schema/document/example/scene projections
A Context Capsule is a *rendered, typed selection of source facts* with:
- `project_id`, principal policy generation reference (opaque), owner source revision vector, AI-02 index generation, inclusion/freshness status, source coverage and explicit unsupported/missing owners.
- `sections` containing stable source locator + owner name + revision/digest + section kind + exact bounded excerpt/shape + source range and field visibility, rights/provenance/license status and redaction status.
- `budget_receipt`: actual UTF-8 bytes/rows/characters, approximately estimated tokens (provider-neutral unless tokenizer pinned), omitted/rejected counts, pagination continuation and truncation reasoning; no silently cut JSON or Markdown data structure.
- `citation_refs`: typed source/owner references and revision; never assistant-generated fictitious quotes or refs, never a bare file path without owner validation.

Scene context is *authoring* scene/revision facts, not a runtime GPU/EntityHandle snapshot. Script context is owner-validated symbol/source map, not executing a script. Schema context is AI-03/DATA-04 owner-approved descriptors with schema IDs and digests, not an unbounded generated swagger dump. Documentation/context text is **untrusted data**, escaped/redacted and labeled as reference, not agent/host instructions.

## 6. Prompt and recipe policy
MCP prompts are **user-controlled**. Create a versioned, finite recipe catalog with a stable prompt ID, title, locale, owner, provenance/licensing, required arguments, declared context-resource dependencies, target engine capabilities and warnings. Examples: inspect a 2D scene, plan a 2.5D ARPG prototype, explain a shader compile report, review a resource import, locate a script symbol, describe a proposed asset reference change, validate a web export plan. Only recipes with supported context sources are advertised; hidden templates and future commands are not claimed as executable.

`prompts/get` validates named string arguments according to MCP version and the internal typed recipe manifest, then performs **read-only** safe interpolation/selection. For richer nested forms, do not fake protocol prompt argument schema: direct nested typed actions to owner tools after explicit selection. Escape interpolation of HTML/Markdown, control chars, surrogate/Unicode edge cases and instruction-like content. The returned prompt contains citations and the role "untrusted project context"; it is never a command grant. A recipe may *suggest* a safe workflow but must not call tools or apply transactions itself. Localized strings go through approved Unicode/translation pipelines (GAME-03 and EDIT-04 integration only), no silent fallback that changes semantics.

## 7. Bounded pagination, freshness, deterministic ordering and caches
- Stable deterministic order for a fixed owner-snapshot + filter + ranking version. `nextCursor` is an opaque AI-05 envelope over AI-02 source index generation and owner policy, bound to actor+project+grant/policy epoch+normalized filter+sort+representation version+expiry. A cursor never authorizes a read; reauthorize at page retrieval, listing, completion and hydration.
- Source/index are **not globally ACID**. `REQUIRE_AT_LEAST_SOURCE_REVISION` waits only within a deadline then returns STALE; `SNAPSHOT_EXACT` fails if owner/index generations are not available; `ALLOW_STALE_WITH_PROVENANCE` may return labeled old non-sensitive data *only after current ACL and rights check*. An index hit is not permission.
- MCP 2026-07-28 requires cache hints on eligible results. Default **`ttlMs: 0, cacheScope: private`**, especially for project-scoped/sensitive lists, resources and prompts. Positive private TTL needs owner-proven immutable revision and revocation policy; a remote client cache cannot be forcibly erased, so revoke only prevents *future server reads*. `cacheScope: public` is forbidden for any project/user-dependent content absent independent proof identical across callers. Header `Cache-Control`, if used by AI-04, must not weaken MCP result hints.
- A listChanged/resource update subscription is a **hint**, not canonical source truth or guaranteed delivery. Only AI-04 sends opt-in subscriptions/listen notifications. On missed events/disconnect, caller re-lists and re-reads by revision; no claim of replay.
- Prevent side-channel counts, sort-key leakage and completion suggestions from exposing unauthorized names. Do not emit exact global totals from AI-02 if filtering invalidates their meaning.

## 8. Security, privacy, rights and resilience
Threats and controls:
| Threat | Control and negative acceptance oracle |
|---|---|
| Cross-project/actor leakage | authorize before listing/counts/templates/completion and again before owner hydration; zero unauthorized content/metadata |
| Cache after revoke | policy-epoch bound cursors/keys, TTL=0 by default; reject new reads after revoke; do not promise remote cache deletion |
| Prompt injection in docs/source | text is labeled/escaped as untrusted, not execute/authorize; no model credentials or command tool side effects |
| Symlinks/path traversal | typed opaque IDs; never convert templates into raw host paths |
| Resource provider SSRF | no arbitrary `https/file/data` URI fetch, external embedded URLs, icon fetch, or credentials |
| Secret/PII/third-party IP exfiltration | owner field-level ACL and provenance/redaction; rights-clear fixtures; no whole-file dump |
| Cursor forgery/replay | principal/project/filter/generation/policy/expiry binding and owner recheck |
| Index stale/corruption | explicit owner watermarks/coverage; PARTIAL/UNAVAILABLE, safe rebuild owner control |
| Context exhaustion | bounded bytes, rows, depth, pages, completion count, per-request deadline and stable partial reason |
| Recipe permission spoof | prompt text never modifies grants and never runs privileged tools |
| Unicode bidi/control spoofing | safe display escaping and canonical typed identifiers; detect collisions |
| Licence/notice drift | exact-source classification, citation/right metadata, exclude restricted content by policy |

Log only correlation, category, byte counts, decision and latency; hash/redact source/URI/token/secret and arguments. No cloud upload, hosted embedding or vendor model dependency. Avoid proprietary or copyleft obligations before owner licensing decision NLE-D009.

## 9. Platform and acceptance demonstrations
Research targets Windows/Linux/macOS Apple Silicon desktop/headless with stdio, optional remote HTTPS handled by AI-04, Web clients only when enabled by relevant host. No native engine/runtime exists. Future demonstrations:
1. Given synthetic 100k entry project, locate a scene+shader+asset via 1-page inventory and 2 bounded reads, with correct owner citations, no full project dump.
2. Change one scene/asset committed source: new generation and freshness; no unrelated full rescan.
3. Revoke project grant mid-list/URL template; no subsequent unauthorized read, cursor or autocomplete leak.
4. Inject prompt-instruction payload in documentation, script names and a URI template; no privilege escalation/SSRF.
5. Demonstrate a user-selected recipe and completion/complete with bounded suggestions, no tool execution.
6. Compare full-repo rights-equivalent read vs selective flow using bytes/estimated tokens, recall@k and supported host compatibility under pinned fixtures. No fabricated performance claim.

[ADR-0064](../adr/0064-ai-05-authorized-context-projections.md) · [Technology/license matrix](../research/ai-05-context-technology-license-security-matrix.md) · [Typed API](../contracts/ai-05-context-resource-api.md) · [128 future tests](../testing/ai-05-acceptance-matrix.md) · [Benchmark](../research/ai-05-context-benchmark-protocol.md).
