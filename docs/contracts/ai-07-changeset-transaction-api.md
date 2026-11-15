# AI-07 — Typed ChangeSet, Plan, Conflict, Apply, Recovery, Undo/Redo Contracts v0.1

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NOT IMPLEMENTED | research #305 | NLE-P00-WO-002-AI-07 | future code #81 OPEN/BLOCKED | BASE a7d4b3ae7ecab0061ea6d0dd72b2bce3dd185089.** Formal dependencies **AI-01 + AI-06 ONLY** (both ADRs PROPOSED, code blocked). Baseline 62/80 researched, 18 pending; all 80 code packets BLOCKED, engine_implemented=false; NLE-D009 license OPEN.

**Only future logical API contracts, NOT code, wire ABI, real journal, schema migration, owner integration, transaction, runtime endpoint or approved implementation.** Formal deps AI-01 + AI-06 ONLY; DATA-04/02/01, WORLD-02 and AI-04 are transitive/integration owners, not formal new edges.

## 1. Owner-port boundaries and canonical types
| Owner | Existing proposed contract | AI-07 treatment |
|---|---|---|
| AI-01 | CommandId/CommandDescriptorV1, CommandInvocationV1, CommandDryRunPlanV1, CommandPlanApprovalV1, CommandReceiptV1, CommandIdempotencyRecordV1 | sole dispatch and semantic owner command; AI-07 aggregates and versions plans, no new handler registry |
| AI-06 | VerifiedAgentRequestV1, AuthorizationDecisionV1, ConsentIntentV1/ConsentReceiptV1, grant epoch | policy/consent reverified before each owner apply and inverse; plan cannot authorize itself |
| DATA-04 | SceneRevisionV1, ScenePatchV1, SceneDiffV1, owner journal/CAS/semantic digest/migration receipt | only actual source transaction/persistence authority, if implemented |
| WORLD-02 | SceneNodeId/Prefab VariantId, SceneEditTransaction, SourceCommitReceipt, runtime publish | scene/prefab conflicts preserved; source commit separate from renderer |
| DATA-02 | AssetId, source provenance and asset graph revision | references stable across move/rename, owner rights and source graph validation |
| AI-04 | MCP tools/call and structured receipts | adapter maps same AI-01 command plan/commit semantics, no separate permission |

## 2. Proposed V1 types
| Type | Fields (candidate) | Invariants |
|---|---|---|
| ChangeSetDraftV1 | ChangeSetId, ProjectId, verified actor/agent, request origin, typed owner operations, original AI-01 CommandId/version, source revision vector, graph dependencies, resource/byte quota, deadline | immutable after plan creation; no raw file path/shell/network |
| ProposedOwnerOperationV1 | OpId, owner namespace, target stable AssetId/SceneId/PrefabId, CommandId/version, validated typed args+canonical hash, expected owner revision/field digest, side-effect category | owner validates types/revision and permitted resources |
| ChangeDependencyGraphV1 | op nodes + directed edges, constraints, topo order, owner grouping, staged external requirements | reject cycles, cross-project by default, unverified actor |
| ChangePlanV1 | PlanId, ChangeSet hash, schema/canonicalization version, source revisions, target, deterministic semantic diff and affected IDs, required grants/consent, owner support/guarantee class, estimated cost, expires, optional preview images | preview never authors source/OS effects; visual diff is non-authoritative |
| SemanticDiffV1 | typed ADD/MODIFY/DELETE/MOVE/RELINK, field before/after + stable owner IDs, scene/prefab/asset graph impacts, rights constraints, source digests | cannot omit semantic refs/order/defaults, no model-invented citations |
| ConflictSetV1 | owner, resource ID, base/ours/theirs semantic revisions, overlapping fields/dependency edges, merge eligibility/reason, safe resolution alternatives | owner-proven, no unsafe last-write-wins |
| ChangeApprovalBindingV1 | AI-06 ConsentReceipt reference, ProjectId+actor/agent, exact PlanId/digest, base revisions, args+target/destination, policy epoch, one-use nonce+expiry | trusted approval for required risk; stale plan invalidates |
| OwnerPrepareReceiptV1 | owner ID, expected revision, stage refs, participant guarantee, no raw lock pointers, source rights, expiry, cost quota | `PREPARED` not durable final commit |
| ChangeJournalEntryV1 | monotonic seq, ChangeSetId, expected source revision, intent/owner stage, idempotency digest, grant/consent reference, owner receipt/digest, checksum, persistence profile, recovery state | journal owner responsible; AI-07 cannot claim cross-filesystem ACID |
| ChangeApplyReceiptV1 | ChangeSetId, PlanId and digest, actor/project, overall state, per-owner actual committed+readback revisions, affected stable IDs, conflicts, partial/external effects, runtime publish status, trace/audit, retry policy | COMPLETE only with owner readbacks and required derived proof |
| ChangeInversePlanV1 | original receipt/source before/after, inverse owner operations+expected revisions, rollback class, affected IDs, dependency limits, source retention, rights/consent | inverse is a NEW authorized change, not blind reset |
| ChangeHistoryCursorV1 | opaque actor/project/rights/source generation/policy epoch, stable sort and expiry | no other project history leakage; cursor not auth |
| ChangeRecoveryDecisionV1 | intent ID, observed owner stage, source/readback status, classification NOT_APPLIED/APPLIED/IN_DOUBT/PARTIAL/EXTERNAL, safe retry/compensate choices | reconcile before replay; no automatic irreversible retry |
| ChangeErrorV1 | PLAN_STALE/SOURCE_CONFLICT/APPROVAL_STALE/UNSUPPORTED_OWNER/ATOMIC_SCOPE_UNSUPPORTED/DURABILITY_UNPROVEN/JOURNAL_CORRUPT/PARTIAL_COMMIT/RECOVERY_REQUIRED/UNDO_CONFLICT, stage, retryability, redacted refs | no secrets/raw paths; unknown result never success |

## 3. Proposed provider functions (not endpoints)
```text
draft_changeset(VerifiedAI01Context, TypedOwnerOperations, Budget) -> ChangeSetDraftV1 | ChangeErrorV1
preview_changeset(VerifiedAI01Context, ChangeSetDraftV1, OwnerSnapshots)
  -> ChangePlanV1 | ConflictSetV1 | ChangeErrorV1
request_owner_consent(AI06TrustedReviewContext, ChangePlanV1) -> ConsentIntentV1 | ConsentReceiptV1
apply_changeset(VerifiedAI01Context, ChangePlanV1, ConsentReceiptV1?, OwnerPorts, IdempotencyKey)
  -> ChangeApplyReceiptV1 | ChangeErrorV1
status_changeset(VerifiedAI01Context, ChangeSetId) -> ChangeApplyReceiptV1 | ChangeErrorV1
recover_changeset(VerifiedOwnerRecoveryContext, JournalId, ObservedOwnerState)
  -> ChangeRecoveryDecisionV1 | ChangeApplyReceiptV1
preview_undo(VerifiedAI01Context, OriginalChangeReceipt, CurrentOwnerSnapshot)
  -> ChangeInversePlanV1 | ConflictSetV1
apply_undo(VerifiedAI01Context, ChangeInversePlanV1, FreshConsent?, IdempotencyKey)
  -> ChangeApplyReceiptV1 | ConflictSetV1 | ChangeErrorV1
preview_redo(VerifiedAI01Context, UndoReceipt, CurrentOwnerSnapshot)
  -> ChangePlanV1 | ConflictSetV1
history_page(VerifiedAI01Context, BoundedFilter, Cursor?) -> AuthorizedHistoryPageV1
```
All operations route through AI-01 owner dispatcher; `request_owner_consent` cannot mint user approval from model text. None perform unchecked filesystem changes. `recover_changeset` must be a trusted owner-controlled recovery operation, not unrestricted agent retry.

## 4. State machine and guarantee annotation
| Status | Durable source implication | Normal next |
|---|---|---|
| DRAFT/VALIDATING | no source writes | preview/reject |
| PREVIEW_READY | source read-only snapshot, expiry | consent/owner revalidate |
| AWAITING_APPROVAL | source still untouched | trusted UI approve/decline |
| PREPARED | owner-specific staging, no full commit claim | durable intent |
| INTENT_DURABLE | owner-coordinator recovery record verified under declared fsync profile | APPLYING |
| APPLYING | some effects may have occurred; must inspect owner | COMMITTED/PARTIAL/RECOVERY_REQUIRED |
| OWNER_COMMITTED | particular owner durable source receipt only | owner readback/derived publish |
| SOURCE_READBACK_VERIFIED | source revision/digest matches canonical owner | required runtime publish or COMPLETE |
| DERIVED_PUBLISH_PENDING | source committed, renderer/index can lag | publish or STALE |
| COMPLETE | all declared mandatory owner/source/derived proofs verified | undo/redo or history |
| CONFLICT | no automatic overwrite | new preview and consent |
| PARTIAL_COMMIT | one or more owner commits, others not; explicit ledger | compensate/recover |
| RECOVERY_REQUIRED | uncertain effect after crash/timeout | owner state inspection; never blind repeat |

Guarantee label `OWNER_ATOMIC`, `RECOVERABLY_COORDINATED`, `COMPENSATION_ONLY`, or `UNSUPPORTED` is required on each plan and final receipt; `OWNER_ATOMIC` may apply only to specific named owner scope. No `GLOBAL_ACID` label without explicit independently proven transactional owner.

## 5. Concurrency, idempotency and policy checks
`apply` requires current expected canonical source revision vector/digest, AI-06 grant and policy epoch, owner rights, resource graph refs, matching plan/args hash, valid one-use consent if risk requires, and quota/deadline. Validate and consume consent at owner commit boundary, not on preview. A changed preview after source/policy update invalidates it.

Idempotency scopes include `actor + ProjectId + ChangeSetId + planDigest + schemaVersion + expectedRevision + operationKind`; repeated same invocation returns same owner receipt, different payload same key returns IDMP_CONFLICT. Do not reuse MCP JSON-RPC request ID as idempotency. Permission and source rights rechecked on *every* retry/status, even cached receipts (safe redaction possible).

Conflict presentation includes base/ours/theirs typed source IDs and fields, owner merge policy, safe options and dry-run; hidden field never exposed by diff. For a CRDT-managed field, apply only owner-approved semantic safe merge and source reconciliation.

## 6. Undo/redo, source checkpoints and retention
Inverse plan captures enough before/after owner data or a rights-permitted checkpoint to reconstruct operation, bounded source storage, license/provenance and retention floor. Initial commit journal and inverse metadata must be coherent under owner durability guarantee. Selective undo after independent edits either proves disjoint fields or returns UNDO_CONFLICT. Never reset whole project or another actor's changes. Redo is a new forward change with fresh source rev and fresh AI-06 consent if required. External publish/delete with no inverse advertises COMPENSATION_ONLY/IRREVERSIBLE.

An actor losing grant after commit cannot undo without current rights; a previous approval cannot be reused. Audit access to history is scoped to project/actor and redacts secret args/PII. Garbage collection may not prune still-advertised undo metadata or unreconciled intent; independently validate recovery after compaction.

## 7. Safety, failure and future acceptance
Failure injection: each journal transition and owner boundary, machine/power loss, write reorder/fsync failure, disk full, corrupt journal, source changes, policy revoke, malformed typed op, repeated retries, derived publish stall and mid-undo concurrent edits. Recovery must distinguish completed vs unknown owner effects and repair safely without false success. Never silently drop partial state. All 128 future scenarios NOT EXECUTED, no owners implemented.

[Architecture](../architecture/ai-07-transactional-planning-undo.md) · [ADR-0066](../adr/0066-ai-07-recoverable-owner-changesets.md) · [Testing](../testing/ai-07-acceptance-matrix.md).
