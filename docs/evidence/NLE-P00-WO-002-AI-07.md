# Evidence Bundle — NLE-P00-WO-002-AI-07 Transactional Planning & Undo

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal deps **AI-01 + AI-06 ONLY**, ADRs 0060/0065 PROPOSED; 62/80 researched baseline, 18 pending, all 80 code WOs BLOCKED, engine false, NLE-D009 OPEN.

## 1. Preflight / Source Check facts
- Live requested main HEAD `a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089`, no open PR, future code [#81](https://github.com/KayzenRoot/stormline/issues/81) OPEN/BLOCKED; catalog AI-07 order 63/80, formal deps **AI-01 + AI-06 ONLY**, target acceptance **reviewable/revertible/repeatable multi-object changes**.
- Registry baseline: exactly 80 modules, **62/80 research documented, 18 pending, 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class 80/80 UNDECIDED, engine_implemented=false.**
- Canonical checkpoint, decisions, scope, DoD, architecture, requirements, catalog, AI MCP contract, AGENTS, AI-01/AI-06 specs/ADRs and future AI-07 code WO read. Context Lock includes Git **blob SHA-1 object OIDs (not raw byte SHA256)** in [research WO](../work-orders/NLE-P00-WO-002-AI-07.md) and [issue #305](https://github.com/KayzenRoot/stormline/issues/305). Any drift in critical sources requires STALE/rebase.
- AI-01 ADR-0060 and AI-06 ADR-0065 are PROPOSED; no owner command kernel, agent grant service, canonical transaction or engine exists. NLE-D009 engine license OPEN.

## 2. Technical research and rationale
- Official [SQLite atomic commit](https://www.sqlite.org/atomiccommit.html), [SQLite WAL](https://www.sqlite.org/wal.html), [SQLite ATTACH](https://www.sqlite.org/lang_attach.html), [PRAGMA synchronous](https://www.sqlite.org/pragma.html), [SAVEPOINT](https://www.sqlite.org/lang_savepoint.html): one database can offer atomic owner operations under real durability assumptions, but WAL ATTACH **is not cross-DB crash-atomic** and filesystem/assets/external effects cannot be silently folded into one transaction. WAL NORMAL recent commits may disappear after power loss; exact patched release required.
- [Git merge](https://git-scm.com/docs/git-merge) and [Git revert](https://git-scm.com/docs/git-revert): base/ours/theirs and inverse new history useful, **not** universal semantic SceneIR/Prefab/AssetId merge.
- [PostgreSQL 2PC](https://www.postgresql.org/docs/current/two-phase.html): requires durable external transaction manager and owner prepared-state support, with in-doubt/blocking issues; not default native engine. [Yjs UndoManager](https://docs.yjs.dev/api/undo-manager): scoped origin tracking for optional collaboration, cannot authorize source writes. Automerge CRDT optional research, unselected.
- Proposed design is versioned typed ChangeSet DAG, owner-derived diff and revision/args/policy/consent digest, owner JIT CAS and durable intent, per-owner source readback/receipts, explicit OWNER_ATOMIC vs RECOVERABLY_COORDINATED vs COMPENSATION_ONLY, PARTIAL/RECOVERY_REQUIRED truthful states, selective current-rights inverse undo and fresh redo.
- Candidate journal store, lock granularity, serializer, library, schema, SDK, license, agent host and benchmark thresholds are **UNSELECTED/UNMEASURED**. No Source Pack decision or NLE-D009 license overridden.

## 3. Exactly eight new research documents
1. [Architecture](../architecture/ai-07-transactional-planning-undo.md)
2. [ADR-0066 PROPOSED](../adr/0066-ai-07-recoverable-owner-changesets.md)
3. [Technology/license/durability matrix](../research/ai-07-transaction-technology-license-matrix.md)
4. [Typed ChangeSet/conflict/undo contracts](../contracts/ai-07-changeset-transaction-api.md)
5. [128 A07 future acceptance scenarios](../testing/ai-07-acceptance-matrix.md)
6. [Reproducible benchmark protocol](../research/ai-07-transaction-benchmark-protocol.md)
7. [Research WO](../work-orders/NLE-P00-WO-002-AI-07.md)
8. This Evidence Bundle.

Research PR must be exactly eight NEW Markdown, no code/CI/registry/backlog/checkpoint mutation.

## 4. Honest evidence status
- Exactly **A07-T001..A07-T128** individually numbered and ordered, eight groups of 16, FUTURE / NOT EXECUTED. Unique ID count/order requires GitHub branch/head readback.
- No test executable, owner transaction engine, DB journal, filesystem writes, scene edits, undo/redo runtime, Editor/MCP host integration, external publish, CI test build, benchmark or durability proof **executed or created**.
- Research PR/Docs Validation run/job/audit/squash/readback PENDING until observed; documentation validator success proves documentation integrity, not actual owner crash correctness or global atomicity.
- No engine license, SDK, middleware, DB or CRDT library selected/adopted; ADR-0066 PROPOSED.

## 5. Checkpoint Delta proposed ONLY, not promoted by research PR
After exact HEAD Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash and factual main/readback:
- Create **separate five-file checkpoint** modifying only docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this research WO and this Evidence.
- In implementation-registry.json only AI-07 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; all other 79 entries and all fields `work_order_status`, `executor_ready`, `approved_adr`, `release_class`, `risk`, dependencies remain intact. Do not promote ADR status to APPROVED.
- Target **63/80 research documented (78.75%), 17 pending, 80/80 future code WOs BLOCKED, zero ready/approved, release_class UNDECIDED, engine_implemented=false**.
- Checkpoint requires independent exact-head CI, pt-BR objective audit, normal squash and main/registry readback. Close research issue #305 only afterward; code #81 remains OPEN/BLOCKED.
- Historical closeout optional but required by established flow: four Markdown (checkpoint, backlog, research WO, Evidence) PR and its own CI/audit/squash/readback before AI-08.

## 6. Risk, rollback and audit
- P00 research documentation LOW; future cross-owner source modification, destructive/irreversible publish and authorization **HIGH_ASSURANCE**. No known HIGH/CRITICAL *documentary* defect claimed resolved; full crash/integrity/security proofs remain open.
- Principal risks: false ACID across SQLite+file system, stale consent/revision, lost concurrent edit, silent partial commit, source journal corruption, fsync/power-loss gap, duplicate export, incomplete undo metadata, asset rights and hidden resource diff.
- Docs-only rollback via audited ordinary revert PR; no source migration or runtime change in P00. Owners must independently prove journal and selective undo/redo before code can be marked functional.

## Research PR #306 factual gates and proposed independent checkpoint
- [Research PR #306](https://github.com/KayzenRoot/stormline/pull/306) BASE `a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089`, final HEAD `40fb1a4d219af6f7162b59629253ce2d74cd21d9`, exactly **eight NEW Markdown**. [Docs Validation #43776147618](https://github.com/KayzenRoot/stormline/actions/runs/43776147618) SUCCESS job #133002785081, Source Pack/links + DAG + registry + Zcode blocked selector all SUCCESS. [Audit pt-BR #6903342071](https://github.com/KayzenRoot/stormline/pull/306#issuecomment-6903342071) APPROVED documentary only. Normal squash and main readback `a70eb275d8823e7acdcf64fea77015a7e360f070`. Research [#305](https://github.com/KayzenRoot/stormline/issues/305) remains OPEN until checkpoint proof; future code [#81](https://github.com/KayzenRoot/stormline/issues/81) remains OPEN/BLOCKED.
- 128 unique A07 tests future only. Target research checkpoint (subject to own CI/audit/main readback): **63/80 researched (78.75%), 17 pending, engine_implemented=false; 80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release_class 80/80 UNDECIDED.** ADR-0066 PROPOSED, NLE-D009 license OPEN, 128 A07 future tests NOT EXECUTED, zero owner transaction/undo runtime, hosts, builds, recovery testing or benchmark. Independent checkpoint BASE `a70eb275d8823e7acdcf64fea77015a7e360f070`, five files, only registry AI-07 status transition; own CI/audit/squash/readback PENDING. All future code remains BLOCKED.
