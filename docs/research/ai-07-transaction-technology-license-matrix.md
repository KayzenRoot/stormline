# AI-07 — Technology, License, Consistency, Durability & Conflict Research Matrix

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal dependencies **AI-01 + AI-06 ONLY** (both ADRs PROPOSED, code blocked). Baseline 62/80 researched, 18 pending; all 80 code packets BLOCKED, engine_implemented=false; NLE-D009 license OPEN.

## 1. Official primary research and versioned facts
| Technology / spec | Primary reference | What is actually promised / limitation |
|---|---|---|
| SQLite ACID and rollback journal | [SQLite atomic commit](https://www.sqlite.org/atomiccommit.html) and [SQLite transactional](https://www.sqlite.org/transactional.html) | crash-atomic transactions within described DB durability assumptions, not arbitrary assets/net |
| SQLite WAL | [SQLite WAL](https://www.sqlite.org/wal.html) | one writer at a time, concurrent readers; WAL requires same-host shared memory; do not assume network filesystem |
| SQLite ATTACH | [SQLite ATTACH](https://www.sqlite.org/lang_attach.html) | multi-db commit atomicity only if main is file-based and mode is **not WAL**; WAL is atomic only per DB |
| SQLite durability and synchronous settings | [SQLite PRAGMA](https://www.sqlite.org/pragma.html) | WAL synchronous=NORMAL may lose recent successful commits after power loss; record actual chosen profile |
| SQLite savepoints | [SAVEPOINT](https://www.sqlite.org/lang_savepoint.html) | RELEASE nested savepoint does NOT durable-commit outer transaction |
| SQLite 2026 WAL bug | [SQLite WAL known WAL-reset bug](https://www.sqlite.org/wal.html#wal_reset_bug) | versions <=3.51.2 affected under narrow concurrent scenarios, fixed >=3.51.3; pin actual patched vendor release, CVE/advisories |
| PostgreSQL 2PC | [PostgreSQL two-phase transactions](https://www.postgresql.org/docs/current/two-phase.html) | PREPARE/COMMIT PREPARED requires external coordinator and in-doubt prepared transaction management; not a local game-engine default |
| Git diff/merge | [Git merge](https://git-scm.com/docs/git-merge) and [git revert](https://git-scm.com/docs/git-revert) | text/base/ours/theirs and history-preserving inverse commits useful reference, not a semantic owner runtime |
| Yjs selective undo | [Yjs UndoManager](https://docs.yjs.dev/api/undo-manager) | trackedOrigins and scoped undo; captureTimeout groups edits; does not automatically grant permissions or project transaction |
| Automerge | [Automerge organization](https://github.com/automerge) | offline-first replicated merge, needs data model and conflict semantics suited to owner |
| Windows file replacement | [Microsoft Moving and Replacing Files](https://learn.microsoft.com/en-us/windows/win32/fileio/moving-and-replacing-files) | ReplaceFile/MoveFileEx have flags, sharing, volume and ACL differences; no universal file+DB+network ACID |
| macOS/Linux POSIX filesystem | [Linux rename(2)](https://man7.org/linux/man-pages/man2/rename.2.html) and [fsync(2)](https://man7.org/linux/man-pages/man2/fsync.2.html) | rename atomic namespace replacement on same mounted FS where supported; durability of data+directory requires explicit flush strategy and test |

## 2. Candidate technology choices, **NONE ADOPTED**
| Candidate | License / rights evidence | Integration use | Gap / risk and decision gate |
|---|---|---|---|
| DATA-04 owner transaction journal and CAS, no AI-07 DB | Engine code license NLE-D009 OPEN | **PROPOSED architectural owner-based direction**, not library selection | owner must provide actual durable intent, retention, receipt, CAS and rollback; no code today |
| SQLite (public domain core) | SQLite [public domain](https://sqlite.org/copyright.html); platform builds may have distinct packaging notices | owner source metadata/journal within one DB | exact patched version, WAL safety/durability, attached DB restrictions, VFS owner update coupling |
| Filesystem staged intent manifest plus atomic pointer per owner | authored code license unresolved | source document snapshots/readback | same-device rename/flush/dir fsync, Windows ReplaceFile behavior, recovery races, journal integrity and retention |
| Immutable append-only operation log | owned implementation unselected | replay/idempotency/undo receipts | avoid torn write, index loss, seq gaps, compaction and source digest correctness |
| Git/libgit2 for history/diff | libgit2 commonly GPLv2 with linking exception, exact tag/notice obligations; Git GPLv2 | source-control reference/UI diff, not canonical owner DB | no automatic engine scene/prefab semantic merge and distro/license cost |
| Yjs | MIT per [upstream LICENSE](https://github.com/yjs/yjs/blob/main/LICENSE) | optional future collaborative text/timeline undo | JS dependency, semantically unsafe last-writer behavior for assets, not owner transaction |
| Automerge | exact language package/tag/repo license review required (Rust/JS distribution differs) | future offline collaborative CRDT candidate | conflict semantics and memory/interop, owner asset IDs/revision, storage and rights |
| PostgreSQL local/remote 2PC | PostgreSQL License (per upstream), server runtime and operational complexity | alternative if future distributed owner explicitly requires prepared commit | external coordinator, blocking prepared state, not free across OS file writes and network |
| Protobuf/FlatBuffers/Cap'n Proto transaction envelope | exact project licenses/tags/IDL/versioning to verify | binary typed change plan and durable journal | schema migrations, canonical hashing, unknown field policy, C++/JS bridge; no format chosen |
| Rust/C++ embedded state machine with fuzzer/property tests | engine code license NLE-D009 OPEN | small deterministic planner, no external engine | custom proof burden, sync/storage/ABI portability; not automatically safer |
| CRDT selective semantic merge | Yjs MIT; Automerge exact tag license pending | collaboration only with owner-defined semantics | cannot make export irreversible actions commutative |
| External queue/outbox/reconciliation | exact storage/runtime license and operator cost unresolved | owner commits + eventual derived publish | not source atomicity; at-least-once delivery demands idempotency and audit |

*Do not infer license or safety from a technology's reputation. Exact package/file-level SPDX, notices, transitive SBOM, CVEs, optional GPL/copyleft linking and commercial distribution review remain future gates.*

## 3. Consistency comparison
| Model | Source integrity | Cross-owner coverage | Undo/conflict |
|---|---|---|---|
| Single-owner ACID/CAS | can be atomic with owner-backed DB and proven storage | only that owner/store | inverse recorded and revision guarded |
| Journal + staged assets + owner state pointer | recoverable if flushed correctly and pointer designed atomically | coordination only unless all assets share owner guarantee | source generation, selective inverse and explicit partial |
| Saga/outbox with compensation | eventual reconciliation; partial intermediate externally observable | can compose many owners with explicit compensations | compensation not exact inverse and can fail |
| 2PC prepared participant + durable coordinator | potentially all-or-nothing only participating transactional resources | only owners supporting protocol, indefinite in-doubt risk | still requires semantic undo and external effect handling |
| Git revert/three-way | source control history and textual conflicts | no native source owner transaction | inverse commits preserving history, conflicts must be resolved |
| CRDT selective undo | causal changes under supported CRDT data type | replicated document types only | origin-aware selective undo, no owner rights bypass |
| blind "apply then undo if fail" | not safe | cannot prove | may destroy concurrent edits, irreversible effects |

## 4. Risk and security
- Cross-project multi-object write, symlink/junction path traversal or raw URL/OS side effect without owner = HIGH/CRITICAL.
- Plan/consent TOCTOU: stale revision, changed command args, license/target, export destination and AI-06 policy revocation. Bind digest+revision and recheck at actual commit.
- Git or CRDT merge can silently overwrite semantic asset references/prefab overrides/scene hierarchy; only owner-proven structured merge allowed.
- Power interruption, low disk, torn journal, checksum mismatch, corrupted idempotency table and lost compaction marker: must return RECOVERY_REQUIRED if uncertain, not SUCCESS.
- Private project snapshots/inverse changes may retain licensed content and PII; rights/retention/crypto owner approval required. No secrets in journal or logs.
- Asset file updates + SQLite registry: **never claim one atomic transaction** without explicit proven owner protocol. derived index/renderer may lag committed source and must report stale generation.

## 5. Research-only conclusion
Propose a **semantic owner-backed, revision-pinned plan with recovery/journal**, guarantee-class labeling, honest PARTIAL states and conditional undo as ADR-0066. No journal technology, DB, FFI, schema, compiler, library license, benchmark threshold or SDK is selected here. Exactly 128 future tests remain NOT EXECUTED. All 80 code WOs blocked.

[Architecture](../architecture/ai-07-transactional-planning-undo.md) · [ADR-0066](../adr/0066-ai-07-recoverable-owner-changesets.md) · [Contracts](../contracts/ai-07-changeset-transaction-api.md).
