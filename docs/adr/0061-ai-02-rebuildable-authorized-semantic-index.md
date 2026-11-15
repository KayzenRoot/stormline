# ADR-0061 — Rebuildable, Incremental and Authorization-Filtered Project Semantic Index

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NO CODE AUTHORIZATION | 2026-11-15 | [research #285](https://github.com/KayzenRoot/stormline/issues/285) | WO NLE-P00-WO-002-AI-02 | code #76 OPEN/BLOCKED | BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d` | NLE-D009 engine license OPEN.**

## Context
AI-02 catalog acceptance **"Consultas filtradas com contexto mínimo e atualização incremental."** AI agents and human Editor/CLI clients need quick navigation across verified scenes, prefabs, scripts, assets, source references, docs and schemas. **DATA-02 is already the proposed sole asset registry/identity/provenance/dependency owner**, with portable canonical sidecars/manifest and rebuildable SQLite index as one candidate. **AI-01 is proposed sole typed command/capability entry**, not an actual compiled API. Indexing must not create a second source of truth or a bypass around owner ACL/revisions. Owner ADR-0010 and ADR-0060 are PROPOSED; no runtime code or search database exists.

## Proposed decision (NOT adopted)
1. **AI-02 owns only a rebuildable, local-first, project-scoped semantic discovery projection**. DATA-02 remains canonical AssetId/revision/provenance/asset dependency authority; DATA-04 scene source/journal, WORLD-02 scene/prefab, GAME-02 script symbol/source maps are integration providers. Index only immutable owner-approved snapshots/committed receipts.
2. **Formal dependencies exactly AI-01 + DATA-02.** Other owners and downstream AI-03/04/05/06 are NOT new direct DAG edges. Missing integration owner APIs yield explicit partial coverage, not guessed parses or circular prerequisites.
3. **Prefer evaluating SQLite FTS5 + structured tables over DATA-02 rebuildable cache** for lexical, metadata and graph lookup, with owner-versioned tokenizer/schema and verified generation. Compare in-memory inverted index, Tantivy/Xapian (rights/platform review) and custom embeddings only with real measurements; **no backend adopted**.
4. Maintain `IndexGenerationV1` and per-owner committed revision vector, generation checksum, source manifest digest, source kind/coverage, schema/tokenizer policy version and ACL policy revision. Build/change records are idempotent by source OperationId/revision and only publish `READY` after derived index integrity check and readback. Crash/gap/corruption ⇒ `REBUILD_REQUIRED`, never rewrite canonical source.
5. Incremental indexer consumes DATA-02/AI-01 **authoritative committed** change receipts, not file-watcher hints. Compute bounded dirty closures including rename/move/reimport, child/script symbol edges, tombstones, schema change; process dependency cycles and fanout quotas. Full rebuild on initial import, cursor gaps, major schema/tokenizer changes or failed integrity/ACL reconciliation.
6. Query **authorization before and after candidate retrieval**: project scope + principal/grant, EntryKind/field/owner content rights, owner revision and ACL revocation revalidation, and no cross-project result/count/snippet/cursor leakage. Existing AI-01 minimal owner-check required even before AI-06. A derived index entry **does not** grant permissions.
7. `IndexQueryV1` enforces kind/tag/owner/text/exact ID/dependency depth filters with bounded max_rows/max_bytes/max_estimated_tokens/max_snippet_chars/max_edges/max_deadline; deterministic ranking/keyset pagination with stable IDs, opaque principal/project/policy/snapshot/query-bound cursor, and explicit partial/missing/stale states. Token estimate without pinned model tokenizer is approximate.
8. Freshness is negotiated: `REQUIRE_AT_LEAST_SOURCE_REVISION` waits within deadline then returns typed STALE; `SNAPSHOT_EXACT` pins verified owner index generation; `ALLOW_STALE_WITH_PROVENANCE` displays source watermark and coverage only if ACL still valid. Do not claim global atomicity across DATA-02/DATA-04/WORLD/FTS.
9. Indexed documents/script/project names are **untrusted data** and can contain prompt injection, secret values and third-party copyrighted source. Source references and excerpt inclusion are owner scoped, redacted and bounded. No remote LLM/embedding/cloud upload or arbitrary SQL/regex/shell. Generated AI summary **not** authoritative project state.
10. SQL/FTS backends require explicit `integrity-check`, rebuild/backfill testing, delete/tombstone cleanup, WAL checkpoint memory/disk quotas and safety under long-lived readers; a clean SQLite commit does **not** prove canonical source & index atomicity.
11. Search quality and minimum context must be measured against labeled ground truth with `recall@k`, `MRR`, `nDCG@k`, freshness and p50/p95/p99, with injected crash/ACL/symlink/Unicode/tokenizer cases. Exactly 128 future test IDs and reproducible hardware/OS fixtures, no fabricated speed or recall targets.
12. Indexing scripts is via GAME-02 validated source-map/grammar adapter and approved source ownership; optional Tree-sitter never replaces GAME-02 VM/typechecker/ScriptApiSchema nor executes script.

## Alternatives / rejection reasons
| Alternative | Strength | Why not default |
|---|---|---|
| Reuse DATA-02 canonical registry directly without semantic projection | consistent asset identity and low complexity | does not provide source symbol/docs/schema search or bounded context ranking; use as baseline, **not** copy it |
| Separate AI-owned authoritative SQLite asset database | fast search | identity drift, duplicate AssetIds and unrecoverable source split-brain |
| Raw filesystem watcher/mtime as authoritative updates | easy change notice | missed/coalesced events, rename ambiguity, cross-project paths and uncommitted content |
| Full reindex every keystroke | simple correctness idea | wrong incremental acceptance, heavy CPU/disk and editor latency |
| Always stale/transparent eventual consistency | cheap updates | "latest" may silently omit new edits or expose deleted private data |
| Unrestricted fulltext raw SQL/FTS syntax to MCP | powerful flexibility | SQL injection, FTS query DoS, ACL bypass and metadata inference |
| Embeddings/vector DB as the only semantic index | fuzzy matching | expensive, hallucinated links, leakage of code, model drift/offline/performance; optional future |
| Shared global index across projects/tenants | space savings | privilege propagation and cross-project existence leaks |
| Infinite pagination with reusable bearer cursor | convenience | leaks beyond revoked grants/snapshot and unbounded memory |
| Xapian GPLv2+ embedded proprietary engine | mature C++ search library | license conflict risk until NLE-D009 owner/legal and GPL obligations resolved |
| Pretend full atomic DB/files/source commit | simple status | DATA-02 and DATA-04 expressly reject unsupported cross-file ACID guarantee |

## Risks/owner proof before promotion
Unresolved SQLite vs baseline score, actual owner event schema/revision vector, authorization granularity and cursor signing policy, source symbol adapter, schema/Unicode tokenizer, index storage/VFS/OS-WAL constraints, FTS content sync, crash recovery/incremental correctness, cache/snapshot TTL and privacy/rights. Future code risk **ELEVATED** (data consistency/ACL/search), with privileged cross-project/remote data HIGH_ASSURANCE separately. Test Windows/Linux/macOS Apple Silicon/headless and Web fallback; model/tokenizer provider variations. ADR-0061 only **PROPOSED**, NLE-D009 OPEN, all 80 implementation WOs BLOCKED.

**No index service, SQLite/FTS database, script parser, vector embeddings, MCP resources or search API has been implemented/selected.**
