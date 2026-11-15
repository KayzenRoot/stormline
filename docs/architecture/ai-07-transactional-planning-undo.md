# AI-07 — Transactional Planning & Undo Architecture v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal dependencies **AI-01 + AI-06 ONLY** (both ADRs PROPOSED, code blocked). Baseline 62/80 researched, 18 pending; all 80 code packets BLOCKED, engine_implemented=false; NLE-D009 license OPEN.

## 1. Objective and guarantee boundary
Catalog acceptance **"Mudança multi-objeto pode ser revisada, revertida e repetida."** Future observer must demonstrate (1) exact typed multi-object preview/diff, (2) explicit owner/agent authorization and consent where needed, (3) durable, idempotent owner-coordinated change application with a replayable receipt, (4) conflict detection and non-destructive selective undo/redo, (5) recoverable crash states and no silent partial-success claim.

**AI-07 is a planning/coordinating layer, not the source-of-truth, file writer or global ACID transaction manager.** Truthful guarantees:
| Domain | Permissible claim only AFTER future proof | Forbidden shortcut |
|---|---|---|
| One DATA-04 source transaction/owner | ACID or atomic state transition only if owner persistence engine truly supports and test proves | presume all files, indexes, GPU and network share its transaction |
| Multiple changes under one source owner | owner-atomic batch using explicit expected revision/CAS and journal | call a list of independent writes "atomic" |
| Multiple source owners/stores | recoverable **coordination**, durable intent, staged owner receipts, reconciliation/compensation or explicit PARTIAL; any global atomicity requires demonstrated common transactional authority | promise cross-owner all-or-nothing from SQLite alone |
| Derived index/cache/runtime | generation invalidation or separately verified publish receipt; source committed does not imply runtime published | show rendered scene as commit proof |
| External side effects (network export/publish/payment) | irreversible or compensatable based on destination; separate explicit consent/readback, never automatic universal rollback | call cancellation an undo of external effects |

SQLite local ACID, journaling and WAL semantics are not an all-stores distributed transaction. Attached SQLite databases in WAL have per-database atomicity, not multi-database crash atomicity. DATA-01 VFS file writes and DATA-02 SQLite cannot automatically share one atomic transaction. Owner controls source; AI-07 only coordinates **bounded authorized semantic operations**.

## 2. Formal and transitive owners
```text
Editor / CLI / MCP host (via AI-04)
             |
    AI-01 typed command kernel (only dispatch authority)
             |
     AI-07 ChangeSet Planner + Coordinator
       |                         |
 AI-06 policy + consent       owner transaction ports
       |                         |
 OWNER JIT recheck          DATA-04 / WORLD-02 / GAME-02 / DATA-02
                                  |
                           durable committed source
                                  |
                           derived runtime/index/cook
```
**Formal prerequisites exactly AI-01 + AI-06.** AI-01 owns CommandId, typed command signature, owner dispatch/receipt, idempotency, preconditions and source authoring semantic parity. AI-06 owns attenuated grants, explicit trusted-UI consent, policy epoch and owner JIT recheck. AI-07 owns draft ChangeSet, deterministic plan fingerprint, dependency DAG/topological ordering of owner operations, staged coordination state, selective undo and follow-up recovery recommendations; it never invents new ProjectId/AssetId/SceneRevision or grants itself permission.

DATA-04 owns durable project source/schema/CAS, WORLD-02 owns scene/prefab conflict and source/runtime receipts, DATA-01 owns filesystem, DATA-02 owns AssetId graph, CORE-06 owns telemetry, AI-04 MCP maps outputs, EDIT-01/03/04 UI, AI-08 future workflows. All **integration owners**, not additional formal DAG edges. A future unsupported owner port MUST yield UNSUPPORTED rather than a raw file fallback.

## 3. Typed ChangeSet / revision and diff semantics
A proposed `ChangeSetV1` is a bounded, versioned, declarative collection of `ProposedOwnerOperationV1`, each containing: stable owner command/version/typed args, targeted canonical ProjectId/resources, expected base revision and structural digest, dependency edges, side-effect/risk class, budget, permission requirements, deterministic canonicalization version and requested semantics. Changes are **instructions for an owner**, not runnable script strings or raw filesystem patches.

Preview must be **side-effect-free for authoring source and external targets**; transient bounded computation/cache for preview cannot be claimed as data mutation. Owner constructs a typed `ChangePlanV1`: immutable PlanId, original source snapshots/revision vector, command args/diff digest, affected stable asset/scene IDs, ordered user-readable changes (ADD/MODIFY/DELETE/MOVE/RELINK), pre/post validation, asset dependency impacts, target constraints, rights/license info, risk, grant/consent obligations, rollback class, cost bounds and expiry.

Diff may include semantic and human-readable forms; user-approved plan is bound to deterministic canonical owner state fingerprint and canonical typed diff. **Do not drop semantic asset links, scene order, prefab variant ancestry or rights metadata while normalizing.** Exact string patch and identity mapping alone is not enough to prove engine state parity.

Plans must be deterministic for fixed source revision, policy, command args and target. If non-deterministic owner service cannot supply a reproducible plan, return PREVIEW_UNSUPPORTED; do not fill gaps with an LLM guess.

## 4. State machine and commit points
```text
DRAFT -> VALIDATING -> PREVIEW_READY -> AWAITING_APPROVAL? 
   -> PREPARED(owner preconditions) -> INTENT_DURABLE
   -> APPLYING -> OWNER_COMMITTED -> SOURCE_READBACK_VERIFIED
   -> DERIVED_PUBLISH_PENDING -> COMPLETE
                                    |
                               COMPENSATION_NEEDED
Any preparatory failure -> REJECTED/CANCELLED (no source commit)
After durable intent / uncertain effects -> RECOVERY_REQUIRED
Source conflict -> CONFLICT (new preview, no overwrite)
```

- `PREVIEW_READY` is a *proposal*, not committed or irrevocable. AI-06 consent is tied to exact command/args/plan digest, actor/agent/project, source revision vector, risk, destination and policy epoch with one-use nonce.
- `PREPARED` means owner has validated/staged what it can, **not** universally held long-lived database locks or guaranteed successful commit.
- `INTENT_DURABLE` means owner-approved recovery records flushed with verified durability under declared storage profile, *before* applying effects. SQLite `synchronous=NORMAL` WAL may lose most recent commits across power loss; choose actual durability settings only after evidence.
- `OWNER_COMMITTED` follows owner-specific durable receipt; AI-07 does not manufacture global commit success for multi-owner flow.
- `COMPLETE` only after canonical source readback and required derived/runtime confirmations under declared acceptance. If partial or external effects remain, `PARTIAL_COMMIT/RECOVERY_REQUIRED`, never "complete".

## 5. Optimistic concurrency and conflict policy
Use **expected base owner revision + semantic digest + resource set + current AI-06 policy/consent epoch** as Compare-and-Swap (CAS) preconditions just before commit; no stale preview silently applies. Stable ID and schema validation must run *again* at owner. Conflict categories: base revision advanced, same field edited, scene node moved/deleted, prefab override changed, asset renamed or removed, permission revoked, incompatible schema migration, resource lock conflict, external publish already happened.

Three-way merge can be **proposed only** for owner structures with a well-defined merge function and stable IDs. Git illustrates base/ours/theirs diff and explicit human conflict resolution; do not use Git textual merge for semantic SceneIR/MaterialDefinition/AssetId graph. Avoid "last write wins" for authoring critical data. A conflict returns a typed `ConflictSetV1` with safe affected IDs, base/ours/theirs semantic refs, alternatives and prohibited auto-merge conditions. Require user selection and new preview/consent when plan changes.

Different owners may have different concurrency/transaction support. If a required owner lacks CAS, journaling, durable receipt, rollback/compensation contract, return `UNSUPPORTED_ATOMIC_SCOPE` or limit ChangeSet to one proven owner. No silent downgrade.

## 6. Undo, redo and repeat semantics
Undo is a **new authorized inverse ChangeSet**, not erasing history, `git reset --hard`, or blind replay of a stale inverse.
- Owner generates and persists reversible operation metadata/inverse plan (or source checkpoint) at the time of original commit, recording exact before/after owner revisions, stable ID maps, dependency graph, source rights and undo limitations.
- `undo.preview` rebases/checks the inverse against current state. If other users or agents changed a dependent field or resource since original commit, return conflict. If safe, owner commits inverse under new revision, new AI-06 grant/consent and audit. Undo cannot revert another actor's unrelated work.
- `redo` is a forward operation derived from successful undo, with fresh source preconditions and authorization. It is **not** reuse of an expired consent or plan. Repeated invocation uses explicit owner idempotency key and receipt to avoid duplicate side effects.
- For non-reversible DELETE/publish/export, declare `IRREVERSIBLE/COMPENSATION_ONLY`, ask for higher-risk consent and never advertise a one-click perfect undo. Source content may require rights-clear checkpoints and retention.
- UI undo stack per project/actor/branch, with event grouping and selective origin; cross-agent selective undo conflict policy is explicit and never bypasses owner ACL. Yjs selective UndoManager and Automerge CRDT are *reference technologies for future collaboration only*, not permission to replace source transactions.

## 7. Durable journal, recovery, reconcile
Proposed `ChangeJournalV1` stores append-only owner intent, per-owner staged and committed receipt hashes, checkpoints, before/after revision vectors, permission/approval reference, cancellation/retry IDs and recovery status. **Where journal is physically stored is owner/DATA-04 decision and unresolved**; AI-07 cannot make AI-01/OS writes atomic by fiat.

On restart, load verified journal, inspect canonical owner source and any external destination independently:
- `NOT_APPLIED`: safe abort or resubmit if current grant/revision/consent remains valid.
- `APPLIED_CONFIRMED`: reconcile receipt, publish required derived state.
- `UNKNOWN/PARTIAL`: report RECOVERY_REQUIRED with concrete owner history; do not retry non-idempotent operation.
- `DERIVED_STALE`: rebuild/refetch derived artifacts without rewriting committed source.
- `IRREVERSIBLE_SIDE_EFFECT`: manual/authorized compensation only, never false rollback.
Retries require idempotency scope bound to principal+ProjectId+ChangeSetId+schema+args digest+owner revision, with retained receipt and expiry. No duplicate commands from MCP retry after timeout.

Compaction/checkpoint and garbage collection require verified ownership, retention floors for undo/legal/source history, and crash-safe migration; cannot prune inverse metadata needed by still-advertised Undo.

## 8. Bounded operation, rights and security
Every ChangeSet has caps on op count, graph depth/edges, bytes, source read spans, validation CPU/memory, deadline, potential export bytes and preview size. Dependency graph must be acyclic (or return conflict); no arbitrary scripts, OS paths, network endpoint or shell command in a plan. Treat AI-generated narratives/labels, prompt text, imported docs and tool descriptions as **untrusted data**. AI-06 deny-overrides and owner PEP on every step; no implicit ambient agent authority. Consent preview must not hide destructive effects in summarized diff. No cross-project plan without an explicitly proven/approved multi-project protocol; default reject.

Source snapshots and inverse metadata may contain private licensed assets/PII; encrypt/control access if needed and never store raw source or tokens in logs. Future audit ties AI-01 owner receipt to AI-06 actor and AI-07 ChangeSet with redaction.

## 9. Future demonstrations and risk
1. User via Editor creates ChangeSet across scene nodes+prefab overrides+asset refs; dry-run displays exact IDs/semantic diff and has **zero** source/OS delta.
2. Apply to one owner atomically and verify canonical source reopen/revision/receipt; ensure no false runtime-publish success.
3. Inject source conflict/revoked grant between preview and commit, ensure no unsafe write.
4. Crash at every state transition and recover with zero duplicate/phantom success and truthful PARTIAL states.
5. Undo one actor change after independent edits; preserve unrelated work or report conflict; redo with new authorization.
6. Multi-owner file+SQLite and external export experiments prove documented coordination limits and compensating actions; never claim cross-store ACID unless real owner demonstrates it.
7. Editor/CLI/MCP same typed command and source semantic fingerprint/readback, with no self-authorizing LLM action.
8. Windows/Linux/macOS Apple Silicon durability, pathname and OS restart matrix with power-loss fault injection in supported harness.

All are **FUTURE / NOT EXECUTED**. No runtime or engine exists. ADR-0066 PROPOSED, future code #81 OPEN/BLOCKED.

[ADR-0066](../adr/0066-ai-07-recoverable-owner-changesets.md) · [Technology matrix](../research/ai-07-transaction-technology-license-matrix.md) · [Contracts](../contracts/ai-07-changeset-transaction-api.md) · [128 future tests](../testing/ai-07-acceptance-matrix.md) · [Benchmark](../research/ai-07-transaction-benchmark-protocol.md).
