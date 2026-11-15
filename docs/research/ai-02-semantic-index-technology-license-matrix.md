# AI-02 — Semantic Index Technology, License, Security, Platform and Research Matrix

**2026-11-15 | P00 DOCUMENTS ONLY | [research #285](https://github.com/KayzenRoot/stormline/issues/285) | BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d` | NLE-D009 engine license OPEN.** This matrix discusses **candidates, not selected or installed dependencies**. Check exact source tag, compiled modules, per-file SPDX, notices/SBOM and optional features before adoption.

## 1. Embedded index and lexical retrieval candidates
| Technology / official source | Feature and architectural fit | License / security, platform or benchmark caveat |
|---|---|---|
| [SQLite](https://www.sqlite.org/) / [license](https://www.sqlite.org/copyright.html) | embedded transactional derived metadata/edges/FTS index; DATA-02 already proposes rebuildable SQLite | core SQLite **public domain**; compile features/OS/SQLITE_FTS5 version must be pinned. SQLITE raw API remains DATA-02/backend private, **never AI/MCP** |
| [SQLite FTS5](https://www.sqlite.org/fts5.html) | BM25 relevance, prefix and Unicode tokenized search, external-content, contentless-delete and integrity-check/rebuild | external-content **must be synchronized** to content table; triggers alone do not backfill existing records. Contentless-delete requires suitable SQLite version; FTS delete sequence correct or ghost tokens. Ranking not a truth probability |
| [FTS5 unicode61/trigram](https://www.sqlite.org/fts5.html#tokenizers) | default `unicode61` tokenization based on **Unicode 6.1**; `trigram` substring search suitable for code symbols/paths | 1–2 Unicode character substrings do not match trigram FTS; LIKE/GLOB may fall back linear scan. Versioned accent/case/locale/CJK/emoji behavior, source code punctuation policies must be tested |
| [SQLite WAL/snapshot](https://www.sqlite.org/wal.html), [isolation](https://www.sqlite.org/isolation.html) | concurrent reader snapshots and a writer with crash-safe derived transactions | long-lived readers may starve checkpoint and cause WAL growth; measure, bound lease+cursor, avoid unsupported network FS; SQLite WAL **does not atomically commit DATA-01 sidecar + DATA-04 source** |
| [SQLite JSON1/JSONB](https://www.sqlite.org/json1.html) | optional internal structured metadata projections | SQLite JSONB is **not** PostgreSQL JSONB and does not promise O(1) lookup; malformed JSONB rejects or returns garbage-in/garbage-out (validation required); source remains typed DATA-02/DATA-04 |
| Portable in-memory inverted map / sorted graph adjacency | small portable C++ standard-lib comparator; no external service | original code only if later approved, memory/perf/rebuild limits and search language quality to measure |
| [Tantivy](https://github.com/quickwit-oss/tantivy) | Lucene-like fast inverted index/tokenizers with Rust implementation | MIT upstream; Rust build/FFI/cross-target and migration footprint, exact tag/license/SBOM check before adoption, NOT automatically superior to SQLite |
| [Xapian](https://xapian.org/) | mature C++ fulltext, Boolean search and weight models | **GPL v2+** per project; license impact important given Stormline's engine code license **OPEN**. Do not bundle without owner/legal approval |
| Remote Elasticsearch/OpenSearch/hosted vector DB | scalable service / fuzzy ranking | cloud/network costs, privacy and ops, inappropriate mandatory local-first prerequisite; **FUTURE/OUT OF P00** |

## 2. Script/symbol extraction and semantic/vector candidates
| Tool/source | Actual role | Caveat |
|---|---|---|
| [Tree-sitter](https://github.com/tree-sitter/tree-sitter) | **MIT** incremental syntax parser; can update CST on source edit, error-tolerant, possible symbol/reference adapter | parser tree **not GAME-02 typechecker or scope authority**; grammar package licenses vary; only owner-validated `ScriptModuleV1` source/revision may be indexed; no executing code |
| [GAME-02 owner API](../contracts/game-02-gameplay-scripting-api.md) | ScriptModule, SourceMap, symbols, imports, typed ScriptApiSchema and versioned validation | best correctness baseline but not implemented; distinguish syntactic text references vs semantically resolved binding with confidence |
| [DATA-02 registry API](../contracts/data-02-registry-api.md) | stable AssetId/revision/provenance/typed dependency edges and snapshots | **canonical** source for asset relationships, never recompute identity from path/hash |
| [DATA-04 semantic source](../contracts/data-04-scene-api.md) and [WORLD-02 scene](../contracts/world-02-scene-prefab-api.md) | scenes/components/prefabs with durable IDs and source revision/ownership | read-only owner integration, no new graph serialization or runtime handle |
| Vector embeddings / approximate nearest neighbor | future fuzzy retrieval/semantic rerank and code search | privacy/licensed source/LLM token costs, model revision, reproducibility, CPU/Web/ARM, hallucination/inference risk. **PROVE-OR-DROP, not NECESSARY** |
| [Unicode Standard](https://www.unicode.org/standard/standard.html) and [ICU](https://icu.unicode.org/) | ICU Unicode normalization/collation/segmentation candidate | ICU Unicode License for ICU data/code (ICU/Unicode license exact release), size/locale costs. Validate CJK/code punctuation/emoji; avoid assuming latest Unicode from SQLite unicode61 |

## 3. Threat/rights/privacy matrix
| Risk | Failure | Proposed gate |
|---|---|---|
| derived cache leaks project text | private scripts/secrets/licensed art paths stored as unrestricted FTS | field-level classification, redaction before indexing, per-project partition, owner-approved allowed excerpts, cache encryption/key policy if later selected |
| cross-project query | guessed AssetId exposes existence/metadata/counts | authorize before candidate query; verify each entry hydration, no totals/cursor leaking forbidden hits |
| stale ACL/revocation | old index entries remain visible after rights revoked | query policy revision included snapshot, force reauthorization and return DENIED/STALE; delete/repair on reindex |
| query syntax attack | raw FTS MATCH/SQL, regex DoS, wildcard huge fanout | typed term AST with allowlisted operators and bound terms/depth/time; prepared internal SQL; no raw query passthrough |
| prompt injection | comments/README/source contain tool commands/instructions | treat indexed content as **untrusted data**, escape/quote, never let contents override agent policy or trigger command |
| index corruption/ghost hits | FTS external content sync or delete incorrect, WAL checkpoint starved | integrity-check, source manifest/digest compare, durable generation/rebuild, bounded readers/quotas |
| copying protected source | whole file/script/asset leaks to LLM or external host | short owner-scoped snippets, origin/license tags, max token/byte/page and explicit permissions; default no remote upload |
| parser/supply chain | hostile grammar/plugin/native executable, malformed JSONB | no grammar auto-install/exec, sandbox/untrusted text parser budgets, pinned SPDX/SBOM |
| false authoritative identity | AssetId derived from path/hash/name, renamed asset breaks links | DATA-02 stable IDs+revision, path display only, tombstone and explicit remap |
| forced embedding external provider | hidden paid API/telemetry/PII transfer | offline-first lexical baseline; no mandatory GPU/LLM/network/services |

## 4. Research tradeoffs & benchmark-first non-selection
**Preferred experiment, NOT implementation decision:** reuse DATA-02's candidate *rebuildable* SQLite derived cache and add scoped FTS5/structured metadata/edge materializations, compare an in-memory inverted map, evaluate Rust/Tantivy/C++ bindings and GPL Xapian license exclusion; use optional Tree-sitter only after GAME-02 parser revision/grammar/capability proof. Measure cold build, incremental dirty closure, query p50/p95/p99, index disk/WAL/CPU memory, ACL cross-project leaks, ranking recall/MRR/nDCG, minimum bytes per relevant result, source watermark correctness and crash/rebuild. No winner, backend, file format, tokenizer or numeric threshold approved.

Official references: [SQLite FTS5](https://www.sqlite.org/fts5.html), [SQLite WAL](https://www.sqlite.org/wal.html), [SQLite isolation](https://www.sqlite.org/isolation.html), [SQLite copyright](https://www.sqlite.org/copyright.html), [SQLite JSON functions](https://www.sqlite.org/json1.html), [Tree-sitter](https://github.com/tree-sitter/tree-sitter), [Tantivy](https://github.com/quickwit-oss/tantivy), [Xapian](https://xapian.org/), [ICU](https://icu.unicode.org/), [Unicode](https://www.unicode.org/standard/standard.html).

**License caution:** SQLite core public domain does not automatically apply to proprietary extensions; Xapian GPLv2+ may be incompatible with eventual Stormline license obligations; Tree-sitter grammars/ICU data have distinct notices. NLE-D009 OPEN; future legal and license audit required. No real index, cache or search measured.
