# ADR-0066 — Owner-Backed Versioned Changesets, Recoverable Coordination and Conditional Undo

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal dependencies **AI-01 + AI-06 ONLY** (both ADRs PROPOSED, code blocked). Baseline 62/80 researched, 18 pending; all 80 code packets BLOCKED, engine_implemented=false; NLE-D009 license OPEN.

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT IMPLEMENTED / NO CODE AUTHORIZATION.**

## Context
Stormline must allow an agent or human editor to propose a multi-object change, inspect a truthful dry-run, commit with exact source and rights preconditions, recover interrupted operations and undo/redo without destroying concurrent work. Previous AI-01 command kernel and AI-06 grant/consent are proposals; no runtime exists. A naive sequence of independent writes with a "transaction" label is unsafe and an unqualified global ACID claim is impossible across independent owners, filesystem and external operations.

## Proposed decision
1. Formal deps **AI-01 + AI-06 ONLY**. AI-01 owns command dispatch, ProjectId/owner typed schema/preconditions, source/owner receipt and idempotency; AI-06 owns policy epoch, grant attenuation and exact-plan trusted UI approval. AI-07 owns a **derived plan and recovery coordination service only**, not canonical DATA-04/01/02 transaction authority or native file operations.
2. Represent ChangeSet as a bounded versioned **typed owner-operation DAG** with stable canonical resource IDs, source revision vector, deterministic owner-schema digests, dependency graph, cost budget, rights/side-effect classes and approved source target. Reject cycles/unknown owners and cross-project plans by default.
3. Produce a **no-source-side-effect** deterministic `ChangePlanV1` via owner preview/validation, with exact semantic diff, affected stable IDs, base revision+digest, owner rebase/conflict rules, permission and consent obligations, invalidation/derived dependencies and rollback category. An LLM explanation is never the source of a diff/citation.
4. Require trusted AI-06 **one-use consent receipt** for higher-risk changes, bound to PlanId+digest, canonical typed args, actor/project/agent, all source revisions and target/destination, policy epoch, expiry. Recheck AI-06 and owner CAS at actual commit; source/rights/plan changes invalidate approval.
5. **Guarantee-class matrix, not blanket atomicity.** Owner-atomic batch only where a single owner implements coherent ACID/CAS and durable journal; cross-owner change uses durable coordinated intent + per-owner receipts + recovery/compensation states with **explicit possible PARTIAL**, not guaranteed distributed all-or-nothing. External publish and irreversible effects never implicitly rollback.
6. **Durable intent, idempotency, readback, replay.** Every owner mutation requires record-before-effect under actually proven flush/durability configuration, stable scoped idempotency key, append/reconcile receipt and independently reopened owner source. After unknown result, query canonical owner state before retry; no blind duplicate actions.
7. **Conflict first, never silent overwrite.** Base/ours/theirs semantic 3-way only for owner-proven safe merge schemas. Wrong revision, deleted resource, incompatible prefab/schema, changed permission or overlapping fields return typed conflict; fresh preview and consent required for changed plan. Last-write-wins forbidden for semantically protected authoring resources.
8. **Selective inverse ChangeSet for undo/redo**, new authorized owner operation with current preconditions and preserved redo history. Inverse metadata/source checkpoints recorded by owner at original commit, rights/retention measured. Undo never unconditionally reverts another actor's changes; redo revalidates against current revision and grant. Nonreversible effects declared.
9. **No hidden global locks or two-phase commit by assumption.** SQLite savepoints within one transaction and local WAL support atomic owner writes only within documented limits. Cross-filesystem/SQLite and network calls require saga/coordination; PostgreSQL prepared transactions would require a separately approved durable coordinator and owner, not a free feature. Exactly which owner journal/storage engine, FFI, locks, compression and external integration to use stays OPEN.
10. **AI-07 must preserve semantic parity** across Editor/CLI/MCP via AI-01 CommandId/typed owner receipt. UI preview is not source commit; committed source is not derived/runtime publish. Distinct receipts and evidence for each.
11. Candidate Git three-way/revert, Yjs selective UndoManager and Automerge CRDT may inform conflict UX and future collaboration but do not define authoritative semantic merges; none is selected/adopted. Engine license NLE-D009 OPEN; exact binary/SDK license/SBOM/security review required before selection.
12. 128 independently specified future tests and benchmark, NOT EXECUTED. Code #81 and all 79 other implementation WOs remain blocked, executor_ready=false, approved_adr=null and release_class UNDECIDED. ADR remains PROPOSED.

## Rejected / deferred alternatives
| Approach | Advantage | Reason not default |
|---|---|---|
| One blind list of AI-01 tool calls | fast prototype | partial commits on failure, no stable rollback or source integrity |
| AI-07 writes raw JSON/project files | skips owner API | violates DATA-04 and AI-01 ownership/ACL; uncontrolled IDs |
| Single SQLite transaction includes filesystem and exports | simple fiction | SQLite cannot atomically commit arbitrary filesystem/network/DB states |
| SQLite WAL multi-ATTACH implies global atomicity | convenient | official SQLite docs exclude multi-file crash atomicity under WAL |
| Unbounded distributed 2PC | conceptual atomicity | blocking/in-doubt coordinator, unsupported owner prepare and external effects |
| Git textual merge/checkout as universal SceneIR/asset undo | reusable source tool | structured prefab/AssetId ownership and links not captured by textual patch |
| Last-write-wins across editors/agents | fewer conflicts | silent data loss, permissions and dependency corruption |
| Snapshot entire project per edit | simple undo | unbounded storage/licensing/PII, expensive and hard to secure |
| CRDT every engine object | automatic merge | mutable source schema and external effects require owner semantics; origin undo not authorization |
| Trust previous approval for changed plan | fewer prompts | stale revision, TOCTOU or destination/rights bypass |
| Treat cancellation after commit as rollback | easy UI | violates actual owner/external side effect |
| Hide PARTIAL behind "retry succeeded" | appealing | can duplicate irreversible actions and fabricate source truth |

## Consequences and costs
Benefits: explicit preview, auditable and replayable owner receipts, safe bounded undo, user conflict resolution and recoverable power loss. Costs: owner journal/retention, per-owner capability negotiation, source revision CAS, security rechecks and potential partial outcomes; UI complexity and storage overhead. Higher assurance when destructive/external operations involved. P00 docs risk LOW; eventual cross-owner mutation and irreversible side effects HIGH_ASSURANCE.

## Ratification conditions
- Owner-approved exact source transaction API, durable journal storage, flush/rename/recovery model on Windows/Linux/macOS and tested single-owner atomicity.
- Proven per-owner CAS/revision, grant/consent JIT, deterministic diff/schema, semantic compare and generated inverse for reversible ops.
- Explicit multi-owner guarantee classes; user-recoverable PARTIAL state, no unsupported atomicity claims.
- Crash injection at each transition, corrupted journal/schema upgrades, repeated idempotency and selective undo under concurrent editors.
- Exact selected library tags/SBOM/licenses NLE-D009 and measurable latency/storage and OS test tiers.
- 128 future scenarios executed and passing, pt-BR objective security audit, approved ADR+checkpoint and functional integration. Not satisfied by P00 research.

[Architecture](../architecture/ai-07-transactional-planning-undo.md) · [Contracts](../contracts/ai-07-changeset-transaction-api.md) · [Matrix](../research/ai-07-transaction-technology-license-matrix.md).
