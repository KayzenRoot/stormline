# NLE-P00-WO-002-AI-02 — Project Semantic Index P00 Documentary Research Work Order

**2026-11-15 | research [#285](https://github.com/KayzenRoot/stormline/issues/285) | catalog_order=58/80 | future code [#76](https://github.com/KayzenRoot/stormline/issues/76) OPEN/BLOCKED | SOURCE BASE `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`.** Baseline 57/80 research documented (71.25%), 23 pending, zero engine, all 80 future code WOs BLOCKED. Formal deps **AI-01 + DATA-02**; research ADR-0060 and ADR-0010 PROPOSED and code #75/#25 OPEN/BLOCKED. Risk current docs LOW, future index/data/ACL ELEVATED, privileged cross-project/remote data HIGH_ASSURANCE separately approved.

## OBJECTIVE
Deeply research a **rebuildable, scoped, incremental semantic read index** for approved scenes/prefabs/scripts/assets/references/documents/schemas, with typed owner-provided IDs/revisions/edges, AI-01 shared query commands, indexed source generation/freshness, deterministic filtered/ranked paginated retrieval, minimum context budgets, safe snippets and permissions, FTS5/WAL/cache alternatives, versioned tokenizer, offline/headless native targets, 128 FUTURE tests and benchmark. Catalog acceptance **"Consultas filtradas com contexto mínimo e atualização incremental."** Do not implement code.

## CONTEXT / SOURCE CHECK
Canonical: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > catalog/registry + blocked code packet. Verified `main` identical to `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`, zero open PRs before #285/branch. Registry 80 entries 57 researched/23 pending, AI-02 `research_status=RESEARCH_PENDING` and code `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Formal owners researched: AI-01 CommandId/Invocation/Principal/Receipt (ADR-0060 PROPOSED), DATA-02 canonical AssetId/revision/provenance/dependency graph and proposed portable sidecars with rebuildable SQLite derived registry (ADR-0010 PROPOSED), no implementation. Future code issues #75/#25 remain OPEN/BLOCKED. NLE-D009 engine license OPEN.

## SCOPE: exactly eight NEW Markdown
1. [Architecture](../architecture/ai-02-project-semantic-index.md)
2. [ADR-0061 PROPOSED](../adr/0061-ai-02-rebuildable-authorized-semantic-index.md)
3. [Technology/license/interop/security matrix](../research/ai-02-semantic-index-technology-license-matrix.md)
4. [Typed owner/index/freshness/cursor/context API](../contracts/ai-02-semantic-index-api.md)
5. [128 unique A02-T001..A02-T128 FUTURE tests](../testing/ai-02-acceptance-matrix.md)
6. [Reproducible incremental/quality/crash/WAL/ACL benchmark](../research/ai-02-semantic-index-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-02.md)

Research PR adds **only** these eight NEW Markdown (no code/CI/checkpoint/backlog/registry). After final HEAD Docs Validation SUCCESS + objective pt-BR audit APPROVED, normal squash and factual main readback, **independent FIVE-file checkpoint PR** updates checkpoint/backlog/registry (SOLE AI-02 research_status transition)/this WO/Evidence. Target **58/80 documented (72.5%), 22 pending, zero engine** and all 80 implementation WOs remain blocked. Own exact-head CI, pt-BR audit, normal squash, readback. Close research #285 **only after** checkpoint readback. Optional independent four-Markdown closeout with own CI/audit/squash/readback. No next AI-03 before completed closeout if performed.

## OUT OF SCOPE
Engine/editor/native index code, installed SQLite/FTS/Tree-sitter/Tantivy/ICU SDK, search/MCP server, LLM/embedding/remote vector DB, raw SQL/path queries, canonical asset schema migration, new authoritative DB, source parser/script VM, privileged file reads, automatic paid/cloud API or external network listener, source license/release class approval, actual performance benchmarks and runtime tests, broad refactor/cleanup, paid CI/CodeRabbit/required external human reviewer, force push/bypass and ALL code issue unblock. Future implementation #76 stays OPEN/BLOCKED.

## FILES / SOURCES TO READ
Canonical: `docs/00-source-hierarchy.md`, `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `AGENTS.md`, `docs/product/module-catalog.md`, `docs/queue/implementation-registry.json`, `docs/queue/work-orders/AI-02.md`, `docs/product/ai-mcp-contract.md`.
Formal owner research: `docs/architecture/ai-01-headless-command-kernel.md`, `docs/contracts/ai-01-command-kernel-api.md`, `docs/adr/0060-ai-01-shared-semantic-command-kernel.md`; `docs/architecture/data-02-asset-registry.md`, `docs/contracts/data-02-registry-api.md`, `docs/adr/0010-data-02-asset-identity.md`, `docs/research/data-02-asset-registry-technology-matrix.md`.
Integration contracts: `docs/architecture/data-04-serialization-scene-format.md`, `docs/contracts/data-04-scene-api.md`, `docs/architecture/world-02-scene-prefab-hierarchy.md`, `docs/contracts/world-02-scene-prefab-api.md`, `docs/architecture/game-02-gameplay-scripting-api.md`, `docs/contracts/game-02-gameplay-scripting-api.md`, CORE-06 diagnostics, DATA-01 VFS, AI-05/MCP integration. External official primary docs SQLite FTS5/WAL/isolation/copyright/JSON1, Tree-sitter, Tantivy, Xapian GPL, Unicode/ICU, linked in matrix.

## REQUIREMENTS
GOV-001..005, NLE-D013..020, CAP-008 assets/versioning, CAP-009 scalable performance, CAP-010 extensibility/diagnostics/testing, CAP-011 2D/2.5D, CAP-012 Web, CAP-013 authorized public CLI/MCP, CAP-014 full v1 DoD before public release, CAP-016 Windows/Linux/macOS Apple Silicon, NFR-001..005. Exact catalog acceptance requires **real filtered minimal-context query and incremental update on canonical owner-committed data**, measured coverage/latency/recall/security, not UI demo or document CI.

## ARCHITECTURE RULES
Formal DAG **AI-01 + DATA-02 ONLY**. DATA-02 owns stable AssetId/source revision/provenance/dependencies/derived index candidate; AI-01 owns public versioned commands/ProjectId/actor/capability gates. AI-02 is **derived projection**, not another source of truth, AssetId generator, source writer, command bus or privileged LLM backend. DATA-04 owns scene source/CAS/journal, WORLD-02 scene/prefab, GAME-02 scripts/source map; integrations only, no new DAG edges. Source receipts committed, watchers hints, revisions/watermarks and idempotent dirty closure. Query ACL checked before fetch and on hydration, filter fields scoped, no cross-project leakage. Snapshot generation and cursor bound to query/project/actor/rev/policy; quotas for rows/bytes/tokens/edges/deadline. SQLite FTS5 external content/delete consistency and WAL checkpoint/growth proof before adoption; no false DB+files ACID. Owner-approved source readback remains oracle, and Embeddings/ANN/cloud are FUTURE prove-or-drop.

## CONSTRAINTS
Docs-only risk LOW. **Source fingerprint list below contains Git blob object SHA-1 OIDs, NOT computed SHA-256 byte fingerprints.** Recheck main and critical source paths before write; if checkpoint, approved ADR, Scope, DoD or Architecture changed mark Context Lock STALE/rebase/recompile. No technology/engine license adopted; no claims of index/search or 128 tests executed. Owner code #75/#25 not implemented, so future index code BLOCKED even after docs APPROVED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown with stable ID and no code/SDK/CI/checkpoint/backlog/registry mutation in research PR.
- [ ] ADR-0061 **PROPOSED**; formal dependencies AI-01+DATA-02 unchanged, explicit ownership of canonical AssetId and command permission.
- [ ] Strict derived index schema, owner revision vector/operation id, incremental invalidation, rename/move/duplicate/delete, dependency cycles, crash/rebuild and no fake global ACID.
- [ ] Typed structured/lexical/graph queries, source citations and owner revision, minimal context budgets and truthful token estimates, deterministic pagination/freshness/coverage.
- [ ] ACL before query and hydration, revocation/cross-project safety, no private content/secret/prompt injection, no raw SQL/regex/path, privacy/rights.
- [ ] SQLite FTS5/WAL/Unicode/FTS backfill and legal-license alternatives evaluated with official sources, no adopted SDK.
- [ ] Exactly **128 distinct A02-T001..A02-T128 FUTURE/NOT EXECUTED** and reproducible stress/quality/bench/security plans with numeric goals TBD.
- [ ] Research PR Docs Validation **exact final HEAD SUCCESS** (Source Pack/local links, 80 DAG, registry, blocked Zcode selector), objective pt-BR audit APPROVED, no HIGH/CRITICAL and normal squash/main readback.
- [ ] Separate **five-file** checkpoint PR sole AI-02 research_status transition; own exact-head CI/audit/merge/readback; every code WO remains BLOCKED.
- [ ] Close research #285 only after factual checkpoint readback; optional historical four-file PR own gates. No code issue #76 unblock.

## TESTS
Actual Docs Validation/source link/DAG/registry/blocked-selector checks only after GitHub Actions run at exact HEAD. Count/uniqueness 128 A02 IDs. **ALL** real index, native Win/Linux/macOS/Web/headless query, ACL, stale/recovery, FTS/WAL, perf/quality and data-integrity tests are future/not executed. Documentation CI does not prove search functionality.

## DELIVERABLES
Eight research Markdown, GitHub issue/branch/PR, diff/sha/CI job, objective pt-BR audit, Evidence Bundle, proposed independent checkpoint, normal merge and main readback. No compiled index, benchmark, SDK, closed code issue or approved owner architecture.

## REVIEW FORMAT
Pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED, base/head SHA, exact changed paths, CI run/job/steps, 128 test IDs, owner source/privacy/ACL/FTS risks, license/OS/snapshot/quality, defects/priority, checkpoints and stop condition.

## STOP CONDITION
Stop if source STALE, direct DAG edge inflation, loss of canonical DATA-02 AssetId, independent DB source, unbounded SQL/scope, FTS dirty terms returned as current, unauthorized project leak, no permission recheck, false index atomicity/ready, hidden upload, selected GPL/SDK/license without approval, CI failure, 128 count mismatch, unexpected files, HIGH/CRITICAL or code unblock.

## CONTEXT LOCK — VERIFIED BASE RESEARCH, NOT CODE ACTIVATION
Main at Source Check: `a3a36248ffa6da5b5d3b1329a969b52b63bca49d`. Git blob object SHAs (SHA-1 Git OIDs, **not byte SHA-256**):
- Source Hierarchy `58a377bc76cafdd3377d733d4f30ef53661bb034`
- Checkpoint `74be95de490cb94eac769d34a38313ca159dfd5f`
- Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Registry `ed9d1a21b81ef5c881fc2615cca1609eaa20f266`
- AI-02 implementation packet `77d9c65fb01cf123629ecbcb9514e0047ede35ec`
- AI-01 architecture/API/ADR `b9c3495de91e38b80c679db6ffc980f31dd76170` / `ca0803152773395ac8f2868126d8cf2446fa4062` / `bf0b04c0e0539f081c3f4804daf0b5645db7bc57`
- DATA-02 architecture/API/ADR/matrix `8838799363620c2cc77b90bd76a0151bfca696ff` / `e1fe73afe60906c3bf1cfdd7c1d508a6d2bc99ff` / `c9465747dc6589ceed121e89bcdf211687021d00` / `65e3fefc7ae34afb72e1daa1902d81c581c0f315`
- DATA-04 architecture/API `7e88d4fecaa83c9922f255087df9f97f6300b61f` / `33b096149df35d20b3fe9e9d21e4bc6f22d71d5c`
- WORLD-02 architecture/API `e04b640df6e3741d324c33d5dd9735696ed69d98` / `c98ea5d49e3b792057c1d14706b9e2f4cfca9550`
- GAME-02 architecture/API `c5429cabdf14bc1e7dc8b3eac11e77274dc51776` / `3dd5ad89e25e7fd39779eded236f26ab2d4a282b`
- Product AI/MCP contract `161183078034162ca458212e65a47cd17a112394`

If main/critical files change, stop/rebuild Context Lock, not blind rebase. Before **code activation**, actual SHA-256 byte fingerprints, source-owner implementations/approval, license and numeric DoD are required.

## EVIDENCE BUNDLE
See [Evidence](../evidence/NLE-P00-WO-002-AI-02.md), factual only after CI/audit/readback. Proposed checkpoint not self-promoted.
