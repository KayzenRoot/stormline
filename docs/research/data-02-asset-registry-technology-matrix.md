# DATA-02 — Asset Registry Technology and Licensing Research

**Work Order:** NLE-P00-WO-002-DATA-02 | **Issue:** #111 | **Status:** RESEARCH PROPOSED / NO CODE

| Candidate | Role | License/standard | Advantages | Risks/gate |
|---|---|---|---|---|
| **SQLite** | embedded ACID relational index, read transactions, adjacency edges | core **public domain** | serverless, SQL indexes and transactions, native editor/headless | WAL one writer, not network FS; DB+VFS cross-transaction problem; version/compile options |
| **Versioned project sidecars/manifest** | portable canonical identity/metadata | Stormline-owned format to define under DATA-04 | source-control diffs, recoverable DB derived index | atomic writes of many files, duplicated ID/case collision, external editing |
| **SQLite canonical + manifest export** | alternative authoritative DB | SQLite core public domain | simpler atomic registry updates and large queries | corruption recovery, project git sharing/merge and cross-file durability |
| **Minimal in-memory map + scan** | independent reference baseline | C++20 standard library | no vendor, simple rebuild and reproducible correctness | scalability, query complexity, startup latency |
| **UUIDv7** | persistent AssetId candidate | IETF RFC 9562 | sortable IDs, distributed generation without server | clock regressions, entropy, collisions, timestamp observability; no auth |
| **UUIDv4** | random persistent ID baseline | IETF RFC 9562 | simple uniform random generation | index locality; collision check still required |
| **BLAKE3** | content digest for revisions/cache | CC0 1.0 OR Apache-2.0 OR Apache-2.0 LLVM exception (upstream) | efficient hashing and incremental content checking | pin C implementation/version and notices, platform SIMD testing |
| **SHA-256** | standard content integrity comparator | algorithm standard, implementation-specific license | interoperable digest, widespread tooling | measured throughput; digest does not prove authentic source |
| **LMDB/other KV** | optional low-level alternative | license/version not yet verified | simple key/value lookup | extra graph/query logic, multiple-reader writer tradeoffs, integration risk |
| **Stormline Asset Provenance Graph (SAPG)** | hypothetical explainable dependency/change-impact graph | original R&D, unimplemented | potential AI-informed workflow and rebuild explainability | prove-or-drop vs SQLite edges/simple manifest |

## Preliminary evaluation recommendation

1. Prototype **SQLite as derived index** behind a Stormline-owned registry contract, while evaluating canonical portable metadata sidecars/manifest. Treat both as proposals until failure testing establishes cross-file reconciliation.
2. Compare a small **in-memory index** as correctness and footprint baseline; don't introduce distributed databases or a cloud subscription.
3. Trial **UUIDv7** against UUIDv4 and clearly separate AssetId from digest, path and session handle. Generate with secure entropy and explicit project merge behavior, never use as authorization.
4. Trial **BLAKE3 and SHA-256** over identical asset sets, tagging digest algorithms. Hash identity is **not** asset identity or publisher authenticity.
5. Treat `PRAGMA foreign_keys=ON`, `integrity_check`, `foreign_key_check`, backup API, WAL checkpoint policies as explicit SQLite safety tests, not a guarantee.
6. SQLite WAL is for local device concurrency, **not** network filesystem shared editing. Only one writer at once. Evaluate `synchronous=FULL` vs `NORMAL` according to required durability.
7. DB size/lookup latency and metadata provenance tests must use real Windows/Linux/macOS and low-end hardware. No invented numeric thresholds or winner.
8. Keep SAPG only if a **measured** diagnostic/invalidation/correctness advantage over standard indexed dependency table is shown.

## Proposed evaluation weights (not measured)

- Reference correctness, recovery and data integrity: 30%.
- Query/index p95/p99 and memory/I/O across 1k–1m assets: 20%.
- Windows/Linux/macOS portability, Web/headless adapters: 15%.
- Security, authorization, metadata sanitization, privacy: 15%.
- Supply chain/licensing/maintenance: 10%.
- Integration simplicity, API ergonomics and source-control workflows: 10%.

**All scores blank pending code/hardware evidence.**

## Primary references
- SQLite public domain and commercial use: https://www.sqlite.org/copyright.html
- SQLite WAL one-writer/network limitations: https://www.sqlite.org/wal.html
- SQLite PRAGMA foreign-key/integrity checks: https://www.sqlite.org/pragma.html
- SQLite online backup: https://www.sqlite.org/backup.html
- UUIDv7 standard: https://www.rfc-editor.org/rfc/rfc9562.html
- BLAKE3 C implementation/licenses: https://github.com/BLAKE3-team/BLAKE3
