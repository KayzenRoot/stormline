# AI-02 — Incremental Semantic Index Benchmark, Quality, Freshness, Privacy and Recovery Protocol

**P00 FUTURE protocol / ZERO EXECUTED RUNS | 2026-11-15 | [research #285](https://github.com/KayzenRoot/stormline/issues/285) | code #76 OPEN/BLOCKED.** No database/index/parser/MCP context extractor, binary or benchmark measurement exists. Numerical thresholds require owner-approved hardware/project tiers and actual evidence.

## 1. Baseline manifest and reproducibility
Pin git HEAD/owner approved schemas, AI-01 CommandDescriptor and DATA-02 RegistrySnapshotToken/source manifest, project/scene/script/asset IDs/revisions/digests, source snapshot vector, index schema/FTS tokenizer/Unicode version/ranking/ACL policy, OS/kernel/compiler/architecture, SQLite exact tag/features/journal/fsync, filesystem and WAL/autocheckpoint settings, parser and script grammar version, hardware CPU/RAM/SSD/GPU (GPU not needed for lexical), locale/case sensitivity, indexed content rights, seeds, workload synthetic asset generation and human-labeled relevance/citation ground truth, auth principals and grant changes. Keep raw redacted receipts+traces with SHA-tagged evidence.

Target matrix: Windows x64 native/headless, Linux x64 native/headless, macOS Apple Silicon native/headless; Web adapter capability/missing-owner fallback (index backend may not work in browser); no GPU/cloud/internet as default. Development on Linux/CI is not proof of all targets. Include compact project 1k entries, medium 100k and stress 1m entries (stress comparison **not 1.0 guarantee**). Separate source-data bytes vs index/FTS/WAL cache bytes; small CJK/RTL/Unicode+source-code corpus with human relevance labels.

## 2. Controlled workloads and owner oracles
| Fixture | Action, expected correctness | Metrics |
|---|---|---|
| IDX-01 | cold canonical asset/scene/script/docs/schema full scan, derived build, integrity check and readback | wall p50/p95/p99, cold startup, peak RSS, CPU, SSD read/write/index/WAL bytes |
| IDX-02 | one DATA-02 asset rename/move (same AssetId), only affected entry/path index changes | invalidated row/edge count vs golden dirty closure; revision-to-ready p95 |
| IDX-03 | script symbol/source revision changed via GAME-02/AI-01 owner, only changed module+dependents invalidated | symbol precision/source-map stability, incremental cost |
| IDX-04 | WORLD-02 prefab instance/variant/scene changed with cycles/overrides and bounded reverse edges | correct graph provenance, rebase/conflict, dirty fanout/limits |
| IDX-05 | asset reimport, duplicate, missing/tombstone/delete, dependency cycles | no ghost FTS results, new ID on duplicate, stable rename ID |
| IDX-06 | 32 simultaneous readers and 1 writer, long-lived snapshot readers | SQLite WAL growth/checkpoint, read jitter, disk quota, snapshot expiry |
| IDX-07 | source commit crash between DATA-04/DATA-02 receipts and FTS update/flush | typed `INDEX_STALE`/replay/rebuild, no source writes |
| IDX-08 | corrupt FTS content mismatch, malformed index schema/tokenizer migration | integrity-check/rebuild, compare full and incremental golden output |
| IDX-09 | scoped multi-project filters/permission revocation during query/pagination | zero unauthorized visible hits, counts, snippets and cursor reuse |
| QRY-01 | exact ID, typed tag/kind/revision filters, graph neighbors and lexical BM25 | precision/recall@1,5,10, MRR, nDCG@10, p50/p95/p99 |
| QRY-02 | long scripts/README/code with secrets/prompt-injection and licensed excerpts | context bytes/tokens, correct source citations, no leakage/execution |
| QRY-03 | Portuguese accents, Turkish dotted I, Arabic RTL, Chinese/Japanese/Korean, emoji, shader `foo_bar` symbols, 1-2 char trigram | tokenizer normalization, fallback cost, expected named symbol precision |
| QRY-04 | `max_rows=1..100`, `max_bytes`, budget edge/cursor, required source fence | strict output budget, deterministic keyset and no false freshness |
| QRY-05 | HEADLESS no display vs editor/MCP wrappers, same AI-01 semantic search command | identical authorized owner refs/coverage, no bypass |
| IDX-10 | burst 10k one-source revisions and WAL/disk pressure | operation dedupe, drop count, fairness, backpressure/rebuild availability |

**Golden:** canonical owner DATA-02 manifest and DATA-04 source readback plus typed WORLD-02 scene and GAME-02 source-map. Use independent brute-force owner snapshot scan as baseline truth, not comparing index to itself. For quality label relevant exact assets/refs/symbols with human-reviewed and license-safe synthetic fixtures; report recall@k, MRR, nDCG@k separately from security/consistency.

## 3. Metrics and acceptance policy
- **Freshness:** owner `SOURCE_COMMITTED` event arrival -> dirty queue -> index generation verified READY; `source_revision_watermark` and owner coverage. Strong `REQUIRE_AT_LEAST` must either honor revision or return typed STALE within deadline, never silently return old. Distinguish source commit latency from index lag.
- **Incrementality:** number/source bytes of changed entries, graph neighbor expansion and unrelated rows touched, index update CPU/SSD, factor versus cold reindex; prove single edit doesn't reindex whole project in normal bounded fixture.
- **Quality:** labeled recall@k/MRR/nDCG@k and correct citation/locator revision, no phantom or duplicate result after move/delete.
- **Minimum context:** max_rows/max_bytes/max_snippet_chars enforced exactly; tokens declared approximate unless pinned tokenizer, count per retrieved relevant item and ranking quality. No truncation yielding invalid JSON or invisible omitted warning.
- **Security:** forbidden tenant/project/field/secret exposure zero in test set, ACL revoke invalidates cursor; FTS raw syntax/SQL/regex/fanout or path escape denied. Logs/output redacted; no network/cloud embeddings by default.
- **Performance:** query index-to-first-result p50/p95/p99, indexing p50/p95/p99, peak RSS, CPU, WAL checkpoint latency/disk, read lease age, storage bytes/indexed item, throughput under 32 reader/1 writer; include cold/hot runs, >=3 independent seeds/runs, >=30 warmups, >=1000 samples for p99 where feasible. No fabricated numeric goals.
- **Availability:** missing owner adapter must return explicit `PARTIAL` coverage, no false all-project completeness. Crash recovery/rebuild time measured and no canonical source mutation.

## 4. Fault and adversarial injection
Inject kill/restart before/after source receipt, FTS trigger missing backfill, incorrect delete term, corrupt FTS external content, WAL long-reader checkpoint starvation, disk-full/read-only filesystem, stale schema/tokenizer, renamed alias/case-only path collision, duplicated AssetId on imported project, cyclic graph, 1m dependency fanout, huge regex/FTS SQL injection, 1-2-char trigram degeneracy, invalid Unicode, timeouts and cancels, multiple project access, stale ACL during streaming, revoked actor after query begun, infected README prompt-injection, malicious script source syntax, fake owner revision digest and external file changes with no committed owner receipt. Verify typed errors, no stale `READY`, no project source writes, no permitted redaction bypass.

## 5. Comparative experiment and proof gates
A: DATA-02 derived SQLite+FTS5 tables, B: owned in-memory inverted map and graph adjacency, C: Tantivy bridge option, Xapian GPL rights review without adoption. Compare identical source generation, rights/ACL, corpus and query labels; no benchmark numbers before actual runs. Optional Tree-sitter grammatical symbols must be validated against GAME-02 source/grammar and compare baseline owner-provided symbols; no parser executing scripts. Vector embeddings or fuzzy semantic reranking are **FUTURE** and must beat lexical+graph at justified CPU/privacy/cost, with local/rights approval.

No exit for implementation until owner-approved schema, exact version/license/SBOM and ACL/retention, DATA-02/AI-01 actual owner APIs, 128 future test passes with injected durability/security faults, reproducible Windows/Linux/macOS/headless/Web evidence and approved noninvented thresholds. This document defines tests, **not results**.

Current status: **128 A02 tests FUTURE/NOT EXECUTED; 0 measured semantic-index runs, 0 SDK chosen, 0 engine source/index code.**

[Architecture](../architecture/ai-02-project-semantic-index.md) · [Typed API](../contracts/ai-02-semantic-index-api.md) · [128 tests](../testing/ai-02-acceptance-matrix.md).
