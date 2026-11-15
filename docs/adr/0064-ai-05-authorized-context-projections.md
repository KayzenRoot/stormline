# ADR-0064 — Authorized, Revision-Pinned MCP Context Projections and User-Controlled Recipes

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NOT CODE-AUTHORIZED. 2026-11-15 | [research #297](https://github.com/KayzenRoot/stormline/issues/297) | NLE-P00-WO-002-AI-05 | [future code #79](https://github.com/KayzenRoot/stormline/issues/79) OPEN/BLOCKED | BASE `ec1a8efc89de6e90d53f7b56fd31bc874335a2ff`.** Dependencies **AI-02 + AI-04 only**, both research-only ADRs PROPOSED. NLE-D009 license OPEN. All 80 implementation WOs blocked.

## Context and problem
The Stormline catalog requires agents to discover project structure without copying the whole repository. AI-02 proposes an incremental, rebuildable, ACL-filtered semantic index with stable source IDs, owner revision vectors, freshness/coverage receipts, cursors and bounded SemanticContextPack. AI-04 proposes MCP 2026-07-28 stateless wire handling, stdio/Streamable HTTP, resources, prompts, templates and completion ports. Neither has implemented code.

The missing component is a reliable, source-cited **context presentation policy**: which limited resources to expose, how to expand typed URIs safely, how to compose minimal context, how to package source provenance and partial results, and how to present user-selected prompt recipes. A naive full-project dump would create security, licensing and token-cost risks, and a second index would create identity/revision split-brain.

## Proposed decision (not adopted)
1. **AI-05 is a read-only, derived Context Resource Provider**, not an index or canonical owner. Query and source freshness come from AI-02; MCP transport, negotiation and JSON-RPC are owned by AI-04. AI-01 and DATA-02 are upstream/transitive authorities, not new formal dependency edges.
2. Expose a **finite, curated inventory** through MCP resources/list and resources/templates/list. Listings are small and deterministic, support pagination and do not enumerate all source files/symbols. Discovery is progressive: inventory -> target selection -> bounded authorized hydration -> optional next page. No repository export as default.
3. Use **versioned opaque `stormline://` resource URIs** with typed ProjectId/source owner IDs/revision. Implement a strict allowlisted RFC 6570 subset for template arguments. Reject free-form filesystem paths, host URLs, reserved expansion, double-decode, path traversal and ambiguous Unicode. An URI/cursor is not permission.
4. Generate **read-only Context Capsules** composed of AI-02 owner-proven excerpts/structure, exact source IDs and revisions/digests, rights/provenance, coverage/partial/freshness, actual byte counts and approximate token estimates. Avoid freeform model-synthesized fact. An AI-02 SemanticContextPack may be consumed, but AI-05 must not create a second source index, score authority or full-text parser.
5. **Authorize before listing/counting/autocomplete and again before each hydration/read** via verified AI-04 request context and AI-02/owner checks. Denied/hidden resource must not reveal names, counts, spans, paths or existence through cursor/suggestions. Fail closed when owner identity, grant, source revision, index or coverage is unverified.
6. **Pin source/index generation and policy to pagination.** An opaque continuation includes project/principal/grant/policy epoch, AI-02 generation and owner revision vector, normalized filter and result order, template/schema profile and expiry, protected by a non-forgeable server-side policy (exact signing/key strategy deferred). Revoke or source generation change invalidates cursor. Never claim global cross-owner ACID or exact freshness if unsupported.
7. MCP 2026-07-28 default cache hint **`ttlMs:0` and `cacheScope:"private"`** for all actor/project-sensitive data. Positive TTL is conditional on independently proven immutable rights and revocation handling. **A host cache that already received plaintext cannot be remotely revoked**; server stops new reads but cannot erase external copies. Never advertise public cache for project-private content.
8. **Prompts/recipes are user-controlled text templates** with stable IDs, locale, version, validated flat named-string MCP arguments, declared context dependencies and capability restrictions. prompts/get does not dispatch tools, approve changes or create arbitrary files. Any richer typed action must go through AI-01/AI-03 tools after separate authorization. All embedded source text remains untrusted data.
9. Optional **completion/complete** offers strictly scoped and bounded prompt/template parameter suggestions, with upstream ACL/filter checks, rate limits, max 100 protocol values and no access to hidden names. Missing completion support must not break resources/templates/prompts.
10. Align modern MCP resource/template/prompt results with cache fields and pagination; 2025-11-25 compatibility is an AI-04-negotiated projection only when tested with pinned host versions. AI-05 never implements a second protocol server, legacy GET stream or transport sessions.
11. Choose offline-first, rights-respecting formatting using approved stdlib/owner safe serializers where feasible. Optional RFC6570/Mustache/Markdown/Unicode libraries need exact release/notice/SPDX/SBOM/CVE and cross-platform checks. Do not adopt general logic/execution-capable template languages or paid SaaS as default.
12. Enforce the catalog's acceptance with **labeled retrieval fixtures** and rights-equivalent full-dump comparator: relevance/recall, exact provenance, freshness, bytes and provider-specific token estimate *only when tokenizer pinned*, p50/p95/p99, resource/ACL proof, host interoperability. Numerical thresholds not invented. Exactly 128 future scenarios are specified but NOT EXECUTED.
13. The ADR is **PROPOSED**, code #79 OPEN/BLOCKED, NLE-D009 OPEN, no engine runtime exists and no implementation package unlock is implied.

## Alternatives considered
| Alternative | Benefits | Why not proposed default |
|---|---|---|
| Entire project/repository as a single MCP resource | easy to prototype | unbounded context, prompt injection, secrets, IP rights and latency; fails minimum-context goal |
| AI-05-owned second search DB/FTS/vector index | local ranking control | duplicates AI-02 and DATA-02 source, creates conflicting generations and ACL leaks |
| Filesystem URI templates `file:///{path}` | familiar MCP examples | path traversal, symlink/host exposure, exfiltration; use typed owner IDs |
| Arbitrary `https://` resources/remote fetch | broad docs access | SSRF, credential passthrough, uncontrolled rights; only through explicit future trusted integration |
| Prompt recipes that execute tools automatically | convenience | bypasses user control/permission and conflates MCP prompts with AI-01 commands |
| Global shared public cache for project sources | speed | cross-user/tenant data and revoked grant leakage |
| Always use latest index silently | simple API | false freshness, TOCTOU after source commit and partial owner coverage |
| Model-generated summaries treated as source citations | short | hallucinated ownership/intent; authoritative citations must come from owners |
| Full RFC6570 user-defined template expression surface | flexibility | reserved expansion introduces path/URI confusion, unsafe dynamic routing |
| Cloud embeddings/LLM summarization default | fuzzy navigation | cost, privacy, licensing, network and model dependency; future separate prove-or-drop |
| Single generic search tool in AI-05 | flexible | duplicates AI-01/AI-03 tool owner, bypasses AI-04 adapter and ACL |
| In-memory per-connection MCP context session | quick shortcut | violates modern stateless assumptions and leaks across concurrent requests |

## Consequences and costs
Advantages: bounded model-neutral context, stable citations, independent source truth, explicit partial coverage, safe caching defaults, deterministic pagination, discoverability without bulk copy and replaceable template renderer. Costs: revision+policy binding, rights/redaction metadata, source snapshot availability, more precise error states, pagination design, optional completion and host-compatibility maintenance. Every dereference incurs an authorization cost; optimize only after correctness measurement.

## Security and privacy proof obligations
- Unknown/denied resources and prompt recipes indistinguishable where policy requires; no index counts/names/suggestions leakage.
- Revoked grant cannot create a new server read, but already disclosed client plaintext cannot be remotely recalled; don't falsely claim cryptographic erasure.
- URI template and Unicode confusables cannot escape typed IDs or owner scopes; no symlink, file://, unapproved HTTPS, arbitrary network or shell execution.
- Source text containing fake system prompts remains inert; prompts/get never invokes command owner.
- License/provenance and authoring rights are included in citation policy; unauthorized third-party samples excluded.
- CacheScope/TTL and cursor/tokens are bound to principal/project/policy/snapshot, with tested cross-user isolation.
- Zero HIGH/CRITICAL data leak, SSRF, path traversal, prompt execution or policy bypass in eventual implementation.

## Ratification prerequisites
Approve dependency interfaces and exact source owner contracts, license/policy, concrete resource ID/template grammar, URI parser/renderer versions, cache/revocation semantics, CI conformance, 128 executed tests, Windows/Linux/macOS/Apple Silicon matrix, target-tier benchmark thresholds, selected host versions, pt-BR objective audit, rollback and independent checkpoint. No code may start until all required decisions are ratified.

[Architecture](../architecture/ai-05-context-resources-templates.md) · [Contracts](../contracts/ai-05-context-resource-api.md) · [Technology matrix](../research/ai-05-context-technology-license-security-matrix.md) · [Acceptance tests](../testing/ai-05-acceptance-matrix.md).
