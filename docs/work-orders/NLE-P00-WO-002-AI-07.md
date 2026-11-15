# NLE-P00-WO-002-AI-07 — Transactional Planning & Undo Research Work Order

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal deps **AI-01 + AI-06 ONLY**, ADRs 0060/0065 PROPOSED; 62/80 researched baseline, 18 pending, all 80 code WOs BLOCKED, engine false, NLE-D009 OPEN.

**Research issue [#305](https://github.com/KayzenRoot/stormline/issues/305) OPEN; future implementation [#81](https://github.com/KayzenRoot/stormline/issues/81) OPEN/BLOCKED.** Catalog #63/80. Formal deps AI-01 + AI-06 only; ADR-0060 and ADR-0065 PROPOSED and no code. Risk P00 doc LOW, future privilege+destructive source actions **HIGH_ASSURANCE**.

## OBJECTIVE
Specify reviewable and repeatable typed multi-object ChangeSets, deterministic semantic dry-run, owner CAS and revision/rights preconditions, trusted AI-06 consent, durability-class guarantees, owner journaling, idempotent replay, typed conflict resolution, selective undo/redo, bounded retention, crash recovery and reproducible acceptance tests/benchmark, without code. Catalog acceptance: **"Mudança multi-objeto pode ser revisada, revertida e repetida."**

## CONTEXT / SOURCE CHECK
Main `a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089` exact live requested HEAD; zero open PR; registry 80 modules, 62/80 research documented, 18 pending, 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=null, release_class 80/80 UNDECIDED, engine_implemented=false. Future code #81 OPEN/BLOCKED; NLE-D009 license OPEN. Canonical precedence checkpoint > Decisions Ledger and approved ADRs > Scope > DoD > Architecture > Requirements > remaining. No ProjectId/owner transaction engine exists yet.

## CONTEXT LOCK (Git blob SHA-1 IDs, NOT raw byte SHA-256)
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`; `docs/11-checkpoint.md`: `c584567ebf975c2ee99c8cfb85d6595b0682e1fd`; `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`.
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`; `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`; `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`; `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`; `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; `docs/product/ai-mcp-contract.md`: `161183078034162ca458212e65a47cd17a112394`.
- `docs/queue/implementation-registry.json`: `b8ec9a2933c7a0864b164fcc00ccffdb5cfb2c2f`; `docs/queue/work-orders/AI-07.md`: `968058925fd85d9cdb0da03ec3eed09566f9e8cc`.
- `docs/architecture/ai-01-headless-command-kernel.md`: `b9c3495de91e38b80c679db6ffc980f31dd76170`; `docs/contracts/ai-01-command-kernel-api.md`: `ca0803152773395ac8f2868126d8cf2446fa4062`; `docs/adr/0060-ai-01-shared-semantic-command-kernel.md`: `bf0b04c0e0539f081c3f4804daf0b5645db7bc57`.
- `docs/architecture/ai-06-agent-security-authorization.md`: `5c0130ab3ab70b02cd4546c84aff719af2dae9f2`; `docs/contracts/ai-06-authorization-api.md`: `74b27624869c5032912b7b159f93d5d220dace6e`; `docs/adr/0065-ai-06-agent-grant-consent-policy.md`: `dcbf4f559abd9ecca704d469784e02916e68d2f2`.
If checkpoint, Decisions Ledger, Scope, DoD, Architecture or critical OIDs change, mark STALE, stop and rebase/recompile before write/merge.

## SCOPE: precisely eight NEW Markdown
1. [Architecture](../architecture/ai-07-transactional-planning-undo.md)
2. [ADR-0066 PROPOSED](../adr/0066-ai-07-recoverable-owner-changesets.md)
3. [Technology, license and durability matrix](../research/ai-07-transaction-technology-license-matrix.md)
4. [Typed ChangeSet/plan/undo API](../contracts/ai-07-changeset-transaction-api.md)
5. [128 unique future tests](../testing/ai-07-acceptance-matrix.md)
6. [Reproducible benchmark protocol](../research/ai-07-transaction-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-AI-07.md)

Research PR exactly these eight NEW Markdown; no registry, backlog, checkpoint, workflows, code, SDK or license changes.

## OUT OF SCOPE
Native C++/Rust/JS engine, SQLite/other DB install, journal runtime, source code changes, MCP runtime, actual authorization, third-party service, asset import/export, GPU/render jobs, transactional editor UI, external publish, undo runtime, compaction, migration, benchmarks, real test execution, future AI-08 coding, public release, hidden all-or-nothing across stores, force push, history rewrite, paid CI/CodeRabbit or mandatory external reviewers.

## FILES/SOURCES TO READ
All canonical Source Pack and fingerprints above, AI-01 and AI-06 architecture/contracts/ADRs, DATA-04/02/01 and WORLD-02 canonical owner specs where relevant, formal catalog and future code WO, official SQLite atomic/WAL/savepoint/ATTACH/sync docs, Git merge/revert, PostgreSQL prepared transactions tradeoffs, Yjs/Automerge selective undo and CRDT references, Windows file replacement and POSIX rename/fsync; exact tags/licenses when selecting candidate.

## REQUIREMENTS
GOV-001..005, CAP-010/013/014/016 and relevant NFR-002..005; approved NLE-D015, D018, D019. Editor/CLI/MCP semantic parity requires AI-01 owner results and AI-06 policy. Diff plan shows actual owner operations before consent; source owner retains rollback/commit truth; partial side effects are never called atomically committed.

## ARCHITECTURE RULES
- Formal deps **AI-01 + AI-06 only**; no new DAG edge or circular dependency. AI-01 owner sole command dispatcher; AI-06 grants/consent and owner JIT authorization; AI-07 coordinator only, no raw path.
- Deterministic typed ChangeSet DAG, exact owner source revision/semantic diff and cost quotas; dry-run must be side-effect-free for canonical source/OS/external target.
- Owner-atomic guarantee only where owner supports it; cross-owner/stores recoverably coordinated with explicit PARTIAL and compensation, no blanket ACID.
- Record durable intent before side effect under proved filesystem/SQLite profile, per-owner receipts/idempotency and independently reopen canonical source; no false success.
- Conflict base/ours/theirs semantic owner metadata; avoid silent LWW, text merge for structured graph; changed plan requires new consent.
- Undo/redo new owner-authorized inverse/forward ChangeSet at current revision; selective concurrent edit preservation, not reset hard; external side effects may be irreversible.
- Cross-project denial default, no agent self-approval or shell/network/FS access, redacted logs and rights-classified inverse snapshots.
- SQLite WAL/ATTACH and synchronous semantics documented, caveats verified; technology/license NLE-D009 OPEN; no SDK/lib adopted.
- 80/80 implementation work orders remain BLOCKED, executor_ready=false, approved_adr=null, release_class=UNDECIDED, engine_implemented=false.

## CONSTRAINTS
P00 documentary LOW. Eventual writes to source/auth/irreversible export HIGH_ASSURANCE. No claimed executing test or host conformance. No paid external dependency or destructive operation. No known HIGH/CRITICAL may advance. No engine implementation.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown, valid links, no unrelated code/registry/checkpoint/backlog/CI file change in research PR.
- [ ] ADR-0066 status PROPOSED, formal deps AI-01+AI-06 only, risk/retention/owner guarantees explicit, NLE-D009 OPEN.
- [ ] 128 individually numbered A07-T001..A07-T128 unique ordered FUTURE/NOT EXECUTED and eight groups of 16 with independent source/OS oracles.
- [ ] Benchmark reproducible with pinned environment and no numerical fantasy, realistic power loss/cross-store partial guarantees.
- [ ] Exact HEAD Docs Validation SUCCESS including Source Pack/links, module DAG, WO registry and blocked selector.
- [ ] Objective pt-BR audit APPROVED, normal squash/main readback and zero HIGH/CRITICAL known in doc scope.
- [ ] Independent checkpoint PR exactly five existing files (checkpoint/backlog/registry/WO/Evidence), only AI-07 research_status from RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED in registry. Own CI/audit/squash/readback.
- [ ] After checkpoint readback **63/80 researches (78.75%), 17 pending, zero engine; all 80 coding WOs BLOCKED, zero ready, zero approved ADR, all release_class UNDECIDED**.
- [ ] Close research #305 only after independent checkpoint proof; future code #81 OPEN/BLOCKED; historical closeout four Markdown with own CI/audit/squash/readback before AI-08.

## TESTS
This P00: `python3 scripts/validate_docs.py`; `scripts/validate_module_catalog.py`; `scripts/validate_wo_registry.py`; `python3 scripts/select_wo.py CORE-01 --json` must reject BLOCKED; exact GitHub Docs Validation run and job success. Future 128 A07 tests, owner atomicity/fsync crash/undo and host conformance are NOT EXECUTED.

## DELIVERABLES
Research issue #305, eight new docs incl ADR PROPOSED / 128 tests / benchmark / Evidence, PR, real docs CI, pt-BR audit, squash and readback, independent five-file checkpoint with gates, separate four-Markdown historical closeout. No code authorization.

## REVIEW FORMAT
Pt-BR APPPROVED/CORRECTION REQUIRED/BLOCKED, base/head Git SHA, exact file list, link validation, 128 IDs, owner transitory semantic receipts and denial/undo design, SQLite durability caveats, CI run/job and decision, risks, Checkpoint Delta, squash commit/main readback, no invented host/security benchmarks.

## STOP CONDITION
STALE context, wrong formal deps/registry, faulty links/tests, unsupported atomic claim, unsafe permission/undo/path, unselected license falsely marked adopted, CI failure, HIGH/CRITICAL, changed approved decision, unlocked packet, false implementation claim, or missing main readback. Do not start AI-08 before AI-07 factual closeout.
