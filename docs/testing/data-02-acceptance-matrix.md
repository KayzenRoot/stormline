# DATA-02 — Proposed Acceptance & Benchmark Matrix

**Work Order:** NLE-P00-WO-002-DATA-02 | **Status:** PLANNED TESTS ONLY, NOT RUN

## Coverage inventory

| ID | Risk | Fixture / action | Acceptance proof |
|---|---|---|---|
| AR-001 | STANDARD | Create 2D sprite/3D mesh and query by AssetId | persistent unique ID, stable typed lookup |
| AR-002 | ELEVATED | Rename or move asset referenced by 10 scenes/materials | **zero broken references**, stable AssetId and reversible journal |
| AR-003 | ELEVATED | Duplicate same content, source-control copy | independent AssetIds; explicit collision diagnostics |
| AR-004 | ELEVATED | Reimport source/revision under changing recipe | original asset ID preserved, new digest/revision and provenance retained |
| AR-005 | STANDARD | Dependency graph with cycle, soft/strong edges, 100k nodes | bounded traversal, deterministic capped impact report, no stack overflow |
| AR-006 | ELEVATED | Crash/kill at each of 6 transaction stages | deterministic recovery, valid canonical truth and index reconciliation |
| AR-007 | ELEVATED | Corrupt/missing SQLite index, WAL and metadata | `integrity_check`/restore or rebuild; no silent ID invention |
| AR-008 | ELEVATED | Disk full, partial IO, read-only VFS root, symlink race | rollback/typed failure, no unsafe host access |
| AR-009 | ELEVATED | DB foreign-key, SQL injection attempt, untrusted huge tags | parameter binding, schema limits, no leaked secrets or unauthorized query |
| AR-010 | STANDARD | 1k, 100k, 1m asset projects on measured low and high spec | p50/p95/p99 point/filtered/graph query; index latency and peak RAM/disk captured |
| AR-011 | STANDARD | Windows x64, Linux x64, macOS arm64, Intel feasibility | per-OS native behavior, case/Unicode, safe VFS integration |
| AR-012 | STANDARD | Editor vs headless server vs Web adapter | no GPU requirement, target-specific persistence compatible contract |
| AR-013 | ELEVATED | MCP actor read/write with distinct project capabilities | read-only scopes enforced, transaction preview before permitted writes |
| AR-014 | STANDARD | Compare SQLite-derived/SQLite-authoritative/manifest-only | measured complexity, recovery, version control and index performance |
| AR-015 | STANDARD | Schema v1->v2 migration, downgrade refusal, backup/restore | data preservation, migration log, forward recovery and clear unsupported schema error |
| AR-016 | ELEVATED | Copy two projects with colliding AssetIds but unrelated origin | safe conflict report, deterministic user-authorized remap only |

## Future executable test organization (paths subject to real repo)
- `unit`: parsing, UUID validation/generation, filter checks, typed contract serialization, metadata and edge rules.
- `integration`: DATA-01 staged VFS + registry file/DB operations, module exports, Editor/CLI/MCP semantic parity.
- `property-based/fuzz`: malformed metadata, path/ID conflation, graphs/cycles, SQL injection, malicious project copy.
- `recovery`: deterministic fault-injection harness for kill after each transaction step, simulated disk full, redo/undo.
- `bench`: fixture generator (seeded), low-end and higher-end PC, project size tiers, cold/warm caches, stable compiler/SQLite versions.
- `security`: least privilege, denial of dangerous MCP requests, project cross-tenant boundary, secret/absolute path redaction.
- `platform`: Windows/Linux/macOS native and PLAT-03 browser adapter proof rather than assuming SQLite WAL compatibility.

## Evidence contract
Record base/head SHA, test seed, source fixture hashes, operations count, OS/filesystem type, CPU/RAM/SSD, SQLite/runtime versions, durability setting and WAL checkpoint, command invocations, actual outputs and CI run. Latency and memory measurements must provide distribution and sample size, not one unexplained FPS number.

## Scope of the current WO
The **only real automated checks permitted now** are the existing Source Pack/links, module catalog DAG, registry 80 WOs and blocked-selector tests. C++ builds, DB integration, benchmarks, native security and migration tests **have not run**. All above scenarios are future acceptance obligations, not claims of success.
