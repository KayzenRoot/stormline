# Work Order — NLE-P00-WO-002-DATA-02

**Module:** DATA-02 Asset Registry & Metadata | **Research issue:** #111 | **Blocked implementation issue:** #25  
**Risk:** LOW for documentation, future persistence/schema changes ELEVATED.  
**Status:** APPROVED / MERGED (research documentation only, PR #112; ADR-0010 remains PROPOSED; NOT IMPLEMENTED). **Context Lock main:** `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb`.

## OBJECTIVE
Research and specify a production-quality asset registry technology/identity model, API, data recovery, provenance and dependency graph for Stormline. Preserve stable references across rename/move/reimport and supply Zcode with future test obligations, **not** premature implementation authorization.

## CONTEXT
DATA-01 VFS research/ADR-0009 and checkpoint APPROVED/MERGED (PRs #109/#110). CORE-01..CORE-06 research documented, 80 implementation WOs blocked and no C++ engine. Long-term 2D/2.5D/3D/Web AI-native commercial engine with Windows/Linux/macOS Editor and exported games, no public MVP.

## SCOPE
- Stable AssetId vs path/digest/runtime handle; UUIDv7 and v4 options.
- Canonical portable metadata vs SQLite-derived index and alternatives; data ownership, migrations and provenance.
- Reference/dependency graph, revision and edge taxonomy, impact query, asset identity-safe rename/move/duplicate and conflict resolution.
- Candidate SHA-256/BLAKE3 revisions and supply-chain/license review; SAPG original hypothesis with prove-or-drop.
- Typed versioned semantic API, Editor/CLI/MCP authorization, privacy and data integrity.
- Threat/error/recovery model, benchmark and test matrix, ADR-0010 PROPOSED, Work Order/Source Pack links and Evidence Bundle.
- Documentation-only GitHub PR and audit, checkpoint reconciliation after merge in same WO.

## OUT OF SCOPE
No C++ or actual SQLite DB/schema migration, game editor implementation, VFS filesystem access, asset conversion, cloud, mandatory paid tool, CodeRabbit, outside human reviewer, branch bypass or claim of tested durability/performance.

## FILES / SOURCES TO READ
In canonical order: `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`/approved ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, then DATA-01 architecture/ADR/evidence, module catalog, blocked DATA-02 WO #25, AGENTS.md, and upstream SQLite/UUIDv7/BLAKE3 official docs.

## REQUIREMENTS
GOV-001..005, CAP-008/009/010/013/014/016 and NFR-001..005 where relevant, NLE-D013..020, DATA-02 module catalog and DATA-01 prerequisite. No unstated MUST-HAVE release claims.

## ARCHITECTURE RULES
- Asset identity stable independent of VFS path/content digest/sessions.
- Metadata and reference graph versioned, typed and recoverable; no unsafe cross-file+DB atomicity claim.
- Read-only game exports may use compact cooked snapshot, live editor registry scoped separately.
- Project authorization and MCP/CLI/editor parity for allowed semantic commands, no raw SQL/host paths.
- Zero hard dependence on cloud, GPU/editor in headless. Schema/migration authority coordinated with DATA-04.

## CONSTRAINTS
Only docs, CI free for public repo, no external reviewer/CodeRabbit, no force-push/ruleset bypass. Do not promote proposed ADR to production without later proof, no unapproved payment or source manipulation.

## ACCEPTANCE CRITERIA
- [ ] Architecture compares at least SQLite-derived, SQLite-authoritative, manifest-only and in-memory baselines with tradeoffs.
- [ ] Identity, reference, revision, provenance, graph edges, rename/move/reimport and duplicate semantics explicit.
- [ ] API/transaction/typed error model and project scope/MCP security contracts documented.
- [ ] Critical SQLite WAL/local-only single-writer, foreign keys, backup, power-loss durability and DB+file reconciliation risks correctly represented.
- [ ] UUIDv7 RFC 9562 and BLAKE3/SHA-256 license and security alternatives considered.
- [ ] Crash/fault/ID collision, migrations and 1k–1m assets test plan across native OS and Web adapter documented.
- [ ] ADR-0010 PROPOSED, implementation issue #25 and 80-WO queue remain BLOCKED, no runtime code.
- [ ] Real docs-validation PASS on exact PR HEAD, scoped patch, Evidence Bundle and review pt-BR.
- [ ] Only after audit/merge: same-WO checkpoint delta, no advance to DATA-03 while reconciliation incomplete.

## TESTS
Existing docs-validation on PR: Source Pack/links, 80-module DAG, Work Order registry and blocked selector. Proposed future native recovery, migration, benchmark, fuzz/security and UI/AI tests are NOT EXECUTED.

## DELIVERABLES
DATA-02 architecture, technology matrix, ADR-0010, semantic contract, acceptance test matrix, this WO, Architecture/Backlog/blocked-issue links, Evidence Bundle, PR and audited checkpoint delta. No engine software.

## REVIEW FORMAT
Brazilian Portuguese. `APPROVED / CORRECTION REQUIRED / BLOCKED`, risk and severity, base/head SHA, exact CI run/job, file diff, license/security, tests run versus not run, residual risks and proposed Checkpoint Delta.

## STOP CONDITION
STALE sources, violated DATA-01 contract, incorrect identity design, claim of DB/file atomicity, unsafe project data operation, paid tool, HIGH/CRITICAL defect, missing CI, unapproved code or scope expansion. Correct in the **same** WO/PR.

## CONTEXT LOCK
Base main `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb`. Git blob IDs for critical files in Evidence Bundle are not content SHA-256; future implementation must compute fresh SHA-256 fingerprints. Refresh if checkpoint, Scope, DoD, Architecture or approved ADR changes.
