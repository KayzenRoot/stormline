# Evidence Bundle — NLE-P00-WO-002-AI-02 Project Semantic Index P00 Research

**2026-11-15 | research [#285](https://github.com/KayzenRoot/stormline/issues/285) | future code [#76](https://github.com/KayzenRoot/stormline/issues/76) OPEN/BLOCKED | BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`.** Baseline 57/80 research documented (71.25%), 23 pending, zero engine, all 80 implementation packets BLOCKED.

## 1. Verified Source Check
- Compared main `a3a36248ffa6da5b5d3b1329a969b52b63bca49d` with current main: identical before research branch; no open PRs. AI-02 catalog order 58, formal deps AI-01 + DATA-02 only, catalog acceptance **"Consultas filtradas com contexto mínimo e atualização incremental."** Research issue #285 and dedicated branch created. Future code #76 OPEN/BLOCKED, predecessor code #75/#25 OPEN/BLOCKED.
- Registry 80 modules: 57 RESEARCH_DOCUMENTED_ADR_PROPOSED, 23 RESEARCH_PENDING, AI-02 RESEARCH_PENDING; every coding WO `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`.
- Checkpoint/Ledger/Scope/DoD/Architecture/Requirements/AGENTS/catalog/registry/AI-02 blocked packet actually inspected via linked GitHub tool. AI-01 architecture/API/ADR and DATA-02 architecture/API/ADR/matrix retrieved, plus DATA-04/WORLD-02/GAME-02 integration docs. Exact Git blob object fingerprints (SHA-1 OIDs, not byte SHA-256) in [WO](../work-orders/NLE-P00-WO-002-AI-02.md). NLE-D009 engine license OPEN; ADR-0061 did not exist before research.
- AI-01 and DATA-02 research only, ADR-0060/0010 PROPOSED; no canonical asset database/index service in compiled engine.

## 2. External technical research, actual sources vs proposed design
- DATA-02 source: stable **AssetId != path != ContentDigest != runtime handle**, source metadata/manifest proposed canonical, SQLite **rebuildable derived index candidate**, typed dependency/provenance/rename/move/revision; no distributed file+DB ACID. AI-01 source: one owner-checked typed read command/grants, no MCP-only privileged path.
- SQLite [FTS5](https://www.sqlite.org/fts5.html) primary docs: Unicode61 default based on Unicode 6.1, trigram short-substring limits, FTS5 external content requires backfill and consistent deletion, integrity-check/rebuild; do not report search index READY with ghost postings. [WAL](https://www.sqlite.org/wal.html) allows snapshot readers but long readers can prevent checkpoint/lead to growth. [SQLite copyright](https://www.sqlite.org/copyright.html): core public domain, licensed proprietary extensions not automatically covered. SQLite [JSON1](https://www.sqlite.org/json1.html): SQLite JSONB not O(1) Postgres JSONB.
- [Tree-sitter](https://github.com/tree-sitter/tree-sitter) MIT parser incremental CST candidate, not GAME-02 typechecker or executable scripts. [Tantivy](https://github.com/quickwit-oss/tantivy) MIT Rust inverted-index alternative with FFI footprint. [Xapian](https://xapian.org/) GPLv2+ alternative with unresolved engine license implications. [Unicode](https://www.unicode.org/standard/standard.html)/[ICU](https://icu.unicode.org/) segmentation/normalization reference, distinct per-release licenses.
- **Proposed** AI-02 solution: project-scoped read-only derived index generation from owner-committed receipts, owner revision vector/permission filtered source refs; deterministic typed query and cursor/budget, untrusted snippets, explicit partial/stale/repair/rebuild. No actual database, scripts, scope, timings, model calls, licenses or secrets created.

## 3. Exactly eight NEW Markdown research deliverables
1. `docs/architecture/ai-02-project-semantic-index.md`
2. `docs/adr/0061-ai-02-rebuildable-authorized-semantic-index.md` (**PROPOSED**)
3. `docs/research/ai-02-semantic-index-technology-license-matrix.md`
4. `docs/contracts/ai-02-semantic-index-api.md`
5. `docs/testing/ai-02-acceptance-matrix.md` (128 distinct FUTURE)
6. `docs/research/ai-02-semantic-index-benchmark-protocol.md`
7. `docs/work-orders/NLE-P00-WO-002-AI-02.md`
8. `docs/evidence/NLE-P00-WO-002-AI-02.md` (this)

## 4. Tests/benchmark status: truthful
- A02-T001..A02-T128 **128 unique FUTURE / NOT EXECUTED**, 0 passed/0 failed.
- Real index DB/FTS, schema, parser, AI-01 shared command and DATA-02 registry, MCP resource/context: **NOT IMPLEMENTED**, no actual queries.
- Indexed AssetId reimport/rename/deletion/provenance readback, ACL/privacy revocation, broken FTS and WAL disk crashes, script parser/symbol quality, full 2D/3D scene references: **NOT RUN**.
- Windows/Linux/macOS/Apple Silicon/Web/headless, GPU-independent search, large-data query, relevance recall/MRR/nDCG, p50/p95/p99 and memory/disk/FTS benchmarks: **0 MEASUREMENTS**.
- Docs Validation, Git PR diff, objective pt-BR audit, squash and checkpoint readback **PENDING until observed**. Successful Docs CI cannot become evidence for native index, semantic relevance or security.

## 5. Proposed independent checkpoint delta, not yet promoted
After exact-final-HEAD research PR Docs Validation SUCCESS, objective pt-BR APPROVED, squash and factual main/API readback: separate five-file checkpoint PR modifies checkpoint/backlog/implementation registry (sole AI-02 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`)/research WO/Evidence. Target **58/80 research documented (72.5%), 22 pending, zero engine**, all 80 code packets BLOCKED, executor_ready=false, approved_adr=null, release_class=UNDECIDED. ADR-0061 PROPOSED, NLE-D009 OPEN, code #76 OPEN/BLOCKED; research #285 closes only after factual checkpoint readback. Optional four-Markdown historical closeout with independent CI/audit/squash/readback.

## 6. Risk and stop conditions
Docs LOW, future derived-cache integrity/ACL/security ELEVATED, privileged cross-project/remote export HIGH_ASSURANCE separately. Stop on Source Pack STALE, wrong DAG, second canonical DB or unchecked AssetId, authorization missing before candidate retrieval/hydration, cursor/ACL leak, wrong FTS backfill/delete, false ready/atomicity, hidden remote upload, unapproved library/license, CI or test count mismatch, unexpected file or HIGH/CRITICAL, or code unlock. No runtime evidence currently.

## Research PR #286 — actual CI, audit, squash and readback
- [PR #286](https://github.com/KayzenRoot/stormline/pull/286): BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`, final HEAD `47e864575ce499c639a836fafe9d867738a13421`, exactly eight new Markdown. [Docs Validation #43760148458](https://github.com/KayzenRoot/stormline/actions/runs/43760148458) SUCCESS at exact final HEAD job #132952909850; all Source Pack/local links, DAG, registry and blocked selector steps SUCCESS. [Pt-BR audit #6901145780](https://github.com/KayzenRoot/stormline/pull/286#issuecomment-6901145780) APPROVED documentary only. Normal squash/main and AI-02 API readback `4bbb783f8710bca676a89a2bce62a3de1cb84e04`, PR merged; registry intentionally unchanged in research PR.
- Actual main baseline still 57/80 researched, 23 pending, AI-02 RESEARCH_PENDING, all 80 code WOs BLOCKED and #76 OPEN/BLOCKED. ADR-0061 PROPOSED, 128 A02 future tests NOT EXECUTED, no SQLite/FTS/search/native/MCP runtime.

## Independent checkpoint PR — proposed, NOT approved yet
- BASE `4bbb783f8710bca676a89a2bce62a3de1cb84e04`, exactly 5 modified files: checkpoint/backlog/registry/research WO/Evidence. Sole AI-02 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`. Target 58/80 research documented (72.5%), 22 pending, zero engine, all 80 coding WOs BLOCKED/executor_ready=false/approved_adr=null/release_class=UNDECIDED. Research issue #285 closes only AFTER checkpoint readback; own CI/audit/squash/main readback PENDING.

## Checkpoint PR #287 — actual CI, squash, factual main readback, research issue closure
- [PR #287](https://github.com/KayzenRoot/stormline/pull/287) BASE `4bbb783f8710bca676a89a2bce62a3de1cb84e04`, final HEAD `79f63c4de5a6cf1b9bcc1a7a75b75e74c242b28d`, exact five modified files and sole AI-02 research_status transition. [Docs Validation #43760426636](https://github.com/KayzenRoot/stormline/actions/runs/43760426636) SUCCESS job #132953772779, all steps SUCCESS; [objective audit #6901181368](https://github.com/KayzenRoot/stormline/pull/287#issuecomment-6901181368) APPROVED documentary only; normal squash `225661a8a39ef035b9f60414a09dc7e6d8bae0a5` confirmed identical to main, registry/issue readback [#6901187686](https://github.com/KayzenRoot/stormline/pull/287#issuecomment-6901187686). Research #285 CLOSED after proof, future code #76 OPEN/BLOCKED.
- Actual registry **58/80 researched (72.5%), 22 pending, zero engine**, all 80 code packets BLOCKED/executor_ready=false/approved_adr=null/release_class UNDECIDED. ADR-0061 PROPOSED, NLE-D009 OPEN, 128 A02 FUTURE/NOT EXECUTED; no live index/query/ACL/FTS/benchmark.
## Historical closeout PR — independent gate
- BASE `225661a8a39ef035b9f60414a09dc7e6d8bae0a5`, exactly FOUR Markdown checkpoint/backlog/research WO/Evidence, NO registry/code/CI/SDK changes. Require independent exact-final-HEAD Docs Validation, objective pt-BR audit, normal squash and main/registry/issues readback. Next module **AI-03 Capability Registry & Schemas** order 59 formal deps AI-01 only when lifecycle complete.
