# AI-08 — Proposed Authoring Recipe, Tool DAG, Capability, Verification and Outcome Contracts v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Catalog 64/80; formal predecessors **AI-05 + AI-07 ONLY**, both ADRs PROPOSED; baseline 63/80 researched, 17 pending, 80/80 code WOs BLOCKED, no engine. NLE-D009 license OPEN.

**Logical research contracts only: no C++/TS ABI, runtime, JSON Schema compiled, API server, agent, tool executor, model, DB, scene source, shader compiler, generator, export or workflow engine implemented.**

## 1. Formal ports and authority
| Formal predecessor | Contract consumed by AI-08 | Unbreakable boundary |
|---|---|---|
| **AI-05** | ContextCapsuleV1, ContextSourceCitationV1, ContextBudget/ReceiptV1, ContextResourceTemplateV1, ContextRecipeManifestV1 and policy/source generation | context read-only, scoped and revision pinned; prompt recipe is user-selected data, no tool dispatch |
| **AI-07** | ChangeSetDraftV1, ProposedOwnerOperationV1, ChangePlanV1, ChangeApplyReceiptV1, ConflictSetV1, ChangeRecoveryDecisionV1, ChangeInversePlanV1 | only owner-backed preview/commit/undo/partial recovery; AI-08 never mutates source directly |

Transitive ports: AI-01 CommandId/owner semantics, AI-06 grant/policy/consent, AI-04 transport/MCP, DATA-02/04 source assets/scene, GFX-07 materials, VFX, AUDIO, GAME scripts/UI, WORLD scenes, DATA-05 cooking, EDIT UI. These are **not formal new dependency edges**.

## 2. Proposed types
| Type | Required fields (candidate) | Invariant |
|---|---|---|
| `AuthoringRecipeManifestV1` | RecipeId, semver, publisher/source digest, localized title, recipe kind, typed input/output schema version, owner required/optional capabilities, target profile, graph descriptor hash, versioned notices/licensing and security class | signed/allowlisted before use; user chooses recipe, never implicit executable import |
| `AuthoringRecipeInputV1` | verified actor/project/agent context ref, recipe Id/version, owner context URI refs, source revision vector, typed parameters, seed, target, output owner namespace and budgets | no raw host files/URLs, no silently invented inputs or scope |
| `AuthoringWorkflowDAGV1` | node ID/owner CommandId/schema, capability guard, typed input/output refs, edges, deterministic topological order, max nodes/depth/fanout/bytes/deadline | acyclic and bounded; no embedded shell/eval or privileged external calls |
| `AuthoringNodeV1` | step Id, immutable typed input, declared output kind/source ID, owner command, expected revision, side effect class, consent category, retry/idempotency policy | owner must support declared node; no hidden side effects |
| `AuthoringContextPinV1` | ProjectId, actor/grant/policy epoch, AI-05 generation, source owner revision/digest, cited resource IDs, availability/coverage and rights | context URI is not authorization and source may be partial/stale |
| `AuthoringCapabilityProfileV1` | target OS/Web/arch, owner module versions, supported command/node/import/export formats, extensions, media codecs, sandbox, permissions and validation tools | unsupported capabilities explicitly marked; no imaginary engine support |
| `AuthoringBudgetV1` | max steps/depth/fanout/model turns, context bytes/token estimate, CPU/RAM/IO, tool calls, expected generated asset bytes, elapsed time, export size, retry count | fail closed on exceed, no autonomous unbounded retries |
| `AuthoringPlanV1` | recipe/input/schema/seed/context hash, ordered DAG, normalized typed AI-07 ChangeSet draft, source citations, expected quality gates, owner/target preconditions and risk/destination, plan expiry | plan is pure proposal, not owner commit nor trusted approval |
| `AuthoringStepReceiptV1` | step ID, owner CommandId, input digest, source owner before/after revision, actual owner receipt, status, support/validation refs, consumed quotas, attempt count | never mark success without owner evidence; optional skip requires declared rule |
| `AuthoringQualityGateV1` | gate id, owner validator/capability, required/optional, source/output artifact IDs, expected fixture metric, failure severity and semantic oracle | AI-09 future may consume evidence, but only actual owner validators prove runtime |
| `AuthoringWorkflowReceiptV1` | workflow ID/recipe version, project+actor, plan digest, context source versions/rights, target, step receipts and owner revision readback, per-gate results, AI-07 guarantee/partial, cook/export receipt, provenance, status and trace | COMPLETE only after all mandatory supported gates; source commit != export |
| `AuthoringWorkflowResumeV1` | opaque principal/project/grant/policy and recipe/plan digest, AI-07 journal handle, owner verified stage and expiry | resume inspects owner before retries; not a permission |
| `AuthoringWorkflowErrorV1` | INVALID_RECIPE/CONTEXT_STALE/SOURCE_DENIED/UNSUPPORTED_CAPABILITY/PLAN_CONFLICT/CONSENT_REQUIRED/BUDGET_EXCEEDED/VALIDATION_FAILED/PARTIAL_COMMIT/RECOVERY_REQUIRED/EXPORT_PENDING, stage, retryable/owner diagnostics redacted | no false success or hidden source/secret |
| `AuthoringReproducibilityReceiptV1` | recipe/owner/schema/capability/target revisions, seed, input asset digests/rights, optional model+sampling profile+output blob hashes, actual source semantic digest and nondeterminism flags | seed is not proof of bit-identical outputs of LLM/media generators |

## 3. Proposed orchestration provider API (not executable)
```text
list_authoring_recipes(VerifiedContext, AuthorizedFilters, Cursor?, Budget)
    -> AuthorizedRecipeCatalogPage | AuthoringError
validate_authoring_recipe(VerifiedContext, RecipeId, Inputs, Target)
    -> CapabilityProfile + ValidatedRecipe | AuthoringError
pin_authoring_context(VerifiedContext, RecipeManifest, SourceRefs, Budget)
    -> AuthoringContextPinV1 | AuthoringError
plan_authoring_workflow(VerifiedContext, PinnedContext, ValidatedRecipe, Inputs)
    -> AuthoringPlanV1 | AuthoringError
preview_authoring_workflow(VerifiedContext, AuthoringPlan)
    -> AI07ChangePlan + TypedSemanticDiff | AuthoringError
apply_authoring_workflow(VerifiedContext, AI07Plan, TrustedApprovalIfRequired, ScopedIdempotencyKey)
    -> AuthoringWorkflowReceiptV1 | AuthoringError
status_or_resume(VerifiedContext, WorkflowHandle)
    -> AuthoringWorkflowReceiptV1 | AuthoringWorkflowResumeV1
validate_authoring_result(VerifiedOwnerContext, OwnerCommittedSource, TargetProfile)
    -> RequiredQualityGateReceipts | AuthoringError
preview_authoring_undo(VerifiedContext, OriginalWorkflowReceipt)
    -> AI07ChangeInversePlanV1 | TypedConflict
```
All owner source mutations invoke **AI-07/AI-01 only**; AI-08 cannot mint AI-06 human approvals, invent owner receipts, run shell, fetch arbitrary network resources or write files directly.

## 4. Typed DAG and lifecycle constraints
Each node declares a *real* owner CommandId and version. Validate connections by exact data type, unit, coordinate convention, temporal semantics, AssetId/SceneId scope and target profile. A lighting/material node cannot silently become a raw shader string; a script step requires approved GAME-02 language sandbox and API binding; audio references require source provenance/license; export requires actual DATA-05/platform owner.

Cycle detection, duplicate node IDs, recursion depth, fanout, maximum event counts and memory quotas are mandatory. Bounded parallelism only for independent read-only/preview nodes. Mutating nodes follow AI-07 owner commit ordering, journal, source CAS and conflict handling; no parallel writes that bypass owner.

## 5. Workflow states and resumability
```text
CREATED -> CONTEXT_PINNED -> CAPABILITIES_VALIDATED -> PLAN_READY
   -> PREVIEW_READY -> CONSENT_REQUIRED? -> APPLYING
   -> OWNER_READBACK -> VALIDATING -> COMPLETE
```
Fail/alternate: INVALID_INPUT, CONTEXT_STALE, DECLINED, UNSUPPORTED_CAPABILITY, CONFLICT, QUOTA_EXCEEDED, PARTIAL_COMMIT, RECOVERY_REQUIRED, EXPORT_PENDING, VALIDATION_FAILED, CANCELLED. Every nonterminal durable handle is actor/project/rights/policy-version scoped and expiration checked. On restart, verify AI-07 actual journal/owner state and source revisions before resuming; cannot fabricate success based on UI progress.

Modern MCP 2026 optional Tasks extension requires AI-04 negotiated host support and per-request opt-in `io.modelcontextprotocol/tasks`; missing capability => bounded supported sync or UNSUPPORTED_TASK_EXECUTION. MRTR input_required is missing nonsecret input, not trusted consent. No mandatory model service.

## 6. Reference workflow graph (concept only)
```text
pin_scene_context + capability_profile
    -> create_scene[owner WORLD/DATA04]
    -> create_camera+lights[typed WORLD/GFX]
    -> create_material_graph[GFX07] -> bind_material[WORLD]
    -> create_script_behavior[GAME02] -> bind_event[GAME01]
    -> create_audio_event[AUDIO owner]
    -> create_vfx_graph[VFX owner]
    -> create_localized_ui[GAME03/EDIT04]
    -> AI07_preview -> AI06_consent_if_needed -> AI07_apply
    -> canonical_source_readback -> owner_validators
    -> optional DATA05 cook/export (separate receipt)
```
If any mandatory owner not available, **NOT COMPLETE/UNSUPPORTED**; no fallback to host shell or unreviewed files. Any output with unknown imported asset rights is blocked for external redistribution.

## 7. Acceptance and security
No hidden manual scene edits on three supported fixture scenarios; trusted consent clicks counted separately, never interpreted as editing; one owner-verified semantic source digest and task completion receipts, budgets, rights, localization/accessibility, physical/render limitations and actual cook/export. Test repeated seeds/digests only for fully pinned deterministic fixtures. No unauthorized file/network/command use, no third-party copyrighted inputs without rights, no stale context/consent after revisions, no omission of mandatory node. Exactly 128 A08 future scenarios NOT EXECUTED.

[Architecture](../architecture/ai-08-authoring-workflows.md) · [ADR-0067](../adr/0067-ai-08-declarative-owner-authoring-recipes.md) · [Testing](../testing/ai-08-acceptance-matrix.md).
