# AI-01 — Typed Headless Command Kernel, GUI/CLI/MCP Parity, Transaction and Job API v0.1

**P00 PROPOSED / NO CODE / NO ABI | 2026-11-15 | [research #281](https://github.com/KayzenRoot/stormline/issues/281) | BASE `dd59a60d4280884dacbb2ec1834a4a5023d9b90c`.** Names here are logical versioned interface proposals, **not implemented structs, binaries, JSON schemas, C++ headers, service or API stability approval**. Owned scene/prefab, serializer and script contracts stay with WORLD-02, DATA-04 and GAME-02, the only formal deps.

## 1. Versioned command descriptors and request types
| Proposed type | Essential fields and invariant | Authority |
|---|---|---|
| `CommandIdV1` | stable namespaced operation ID, owner ModuleId, semantic major/minor revision, schema reference/hash | AI-01 bootstrap routing, owner declares operation; AI-03 future reflection derives from source |
| `CommandDescriptorV1` | CommandId, type, side effect READ/PREVIEW/STAGE/COMMIT/EXTERNAL, required ProjectId/role/capability, input/output schemas, undo policy, version, availability/target, idempotency, deadline/cancel, example/test ID | AI-01 routing metadata bound to owner contracts; not an alternative owner validator |
| `CommandOriginV1` | EDITOR_MENU/EDITOR_BUTTON/SHORTCUT/PALETTE/CLI/HEADLESS/MCP/TEST with recorded source and client version | telemetry/context, **never security authority** |
| `CommandPrincipalV1` | verified actor/role/project/workspace, authn issuer, time-limited scope grant reference, revocation version, consent state | owner/AI-06 later policy, mandatory minimal fail-closed owner gate now |
| `CommandInvocationV1` | schema/version, OperationId, CommandId/major/minor, ProjectId, expected source/owner revision, actor grant, typed args, ID/nonce, deadline, idempotency key, trace ID, target, origin | AI-01 validates and delegates; no raw path/handle/eval |
| `CommandArgumentsV1` | typed immutable ID-based values, optional seed, feature requirements, explicit units, bounded collections; unknown required input rejected | handler owner type schema / DATA-04 source rules |
| `CommandPreconditionV1` | owner source revision + optional expected-old-value digest, owner schema and required feature set, grants and target | DATA-04/WORLD-02/GAME-02 each enforce |
| `CommandDryRunPlanV1` | PlanId, snapshot revision, canonical args digest, typed diff, risk/rights/affected counts, estimated owner cost, expires, permission requirements | owner preview, immutable, no source/OS side effect |
| `CommandPlanApprovalV1` | PlanId/digest, actor/ProjectId, exact revision/capability, explicit consent flags and expiry | owner authorization for destructive/irreversible ops, cannot reuse stale plan |
| `CommandReceiptV1` | OperationId, owner, command/schema version, request/owner stage, before/after revision+semantic digest, changed IDs, warnings/conflicts, idempotency replay, journal/undo token, trace/evidence and safe error | owner result; adapter presents same semantic fields |
| `CommandJobHandleV1` | opaque JobId+generation, ProjectId/owner, operation type/version, target, accepted snapshot/revision, scoped cancellation token and expiry | CORE-03/PLAT/DATA-05 owner, AI-01 just routes/status |
| `CommandJobReceiptV1` | ACCEPTED/QUEUED/RUNNING/VALIDATING/COMPLETED/FAILED/CANCELLED/RECOVERY_REQUIRED with progress units, artifacts/readback hashes and separate export/target evidence | owning build/export/validation module |
| `CommandIdempotencyRecordV1` | scoped principal/ProjectId/CommandId/major + key, payload digest and expected revision, stage, durable owner receipt/retention | DATA-04/owner persistence, AI-01 only request validation |
| `CommandVersionNegotiationV1` | client/owner major-minor ranges, required features, schema hash and adapter capability | AI-01/owner; no unversioned fallback |
| `CommandCapabilityResultV1` | available/unsupported/locked/need-confirmation, target, disabled reason and documentation link | each owner; common UI/CLI/MCP projection |
| `CommandSemanticStateFingerprintV1` | DATA-04 algorithm/tagged canonicalization version, source project/revision, normalized stable IDs & ordered typed graph, asset refs/rights, optional explicit ID-remap mapping | DATA-04 (semantic state) and WORLD-02 prefab semantics, **not** a hash invented by AI-01 |
| `CommandErrorV1` | stable code, owner, stage, retryable, expected/actual version/revision, safe affected IDs, redacted summary and recovery action | owner + CORE-06 redaction |

**No UI-only command success.** An accepted handler call is not a source commit; a source commit is not a runtime publish; a build accepted as job is not a validated export. Each phase has independent status.

## 2. Formal owner contracts reused, not duplicated
| Formal owner | Existing type / action | AI-01 mapping |
|---|---|---|
| WORLD-02 | `SceneAssetV1`, `PrefabAssetV1`, `SceneNodeIdV1`, `PrefabVariantV1`, `SceneEditTransactionV1`, `PrefabRebaseReceiptV1`, `SceneCommitReceiptV1` | commands `scene.inspect`, `scene.patch.preview`, `scene.patch.commit`, `prefab.rebase.preview`; preserve 3-way conflicts, stable IDs and separate runtime receipt |
| DATA-04 | `SchemaDescriptorV1`, `SceneDocumentV1`, `SceneRevisionV1`, `ScenePatchV1`, `SceneDiffV1`, `MigrationPlanV1`, `MigrationReceiptV1` | no raw JSON writes. Delegate inspect/dry-run/validate/stage/CAS/journal/commit/reconcile/readback |
| GAME-02 | `ScriptApiSchemaV1`, `ScriptModuleV1`, `ScriptCapabilityGrantV1`, `ScriptHostCallV1`, `ScriptExecutionReceiptV1`, `ScriptCommandBufferV1` | `script.inspect`, `script.validate`, `script.module.preview`; no unrestricted script eval or VM pointer/OS access |

**Future integrations:** EDIT-01 `EditorCommandIdV1` maps 1:1 onto canonical CommandId for registered public authoring operation; EDIT-02 owns project creation/open; PLAT/DATA-05 own future build/export artifacts; AI-03 reflects bootstrap descriptors; AI-04 MCP server adapts transports; AI-06 later enhances grants; AI-07 composes multi-op changeplans. Not extra formal dependency edges.

## 3. Logical operations and state machine
| Command (illustrative, not registered) | Side effects | Required owner and receipt |
|---|---|---|
| `kernel.capabilities.inspect` | READ | bounded version/availability filtered by granted project, no secret function leakage |
| `project.open` / `project.create` | READ or COMMIT with approval | EDIT-02 scoped project receipt, no arbitrary absolute path |
| `scene.inspect` / `scene.hierarchy.page` | READ | WORLD-02 typed scene snapshot/read granularity, bounded pagination |
| `scene.patch.preview` | PREVIEW | WORLD-02 + DATA-04 validation, affected IDs/typed diff/plan digest |
| `scene.patch.commit` | COMMIT | expected revision, idempotency, owner capability, DATA-04 journal/CAS, WORLD-02 source & runtime receipts |
| `prefab.rebase.preview` | PREVIEW | WORLD-02 3-way base/ours/theirs and loss report |
| `script.validate` | READ/PREVIEW | GAME-02 source hash/target/diagnostics; no executing project script |
| `scene.undo` / `scene.redo` | COMMIT | DATA-04 inverse preconditions / WORLD-02 effects, cannot overwrite intervening changes |
| `build.request` / `build.status` / `build.cancel` | ASYNC EXTERNAL | platform/QA owner future job plan, no arbitrary subprocess, not available at P00 |
| `export.request` / `export.status` | ASYNC EXTERNAL/IRREVERSIBLE when publishing | DATA-05/PLAT owner manifest/source rights/target/destination grant; no export engine at P00 |

`DECODE -> LOOKUP -> VERSION_NEGOTIATE -> AUTHENTICATE -> AUTHORIZE -> OWNER_VALIDATE -> PREVIEW/PLAN -> STAGE -> OWNER_VERIFY -> INTENT_RECORDED -> SOURCE_COMMITTED -> READBACK -> (RUNTIME_PUBLISHED | RUNTIME_PENDING)`. Cancellation before intent may abort without source write; after intent require status/recovery. Build/export jobs `ACCEPTED -> RUNNING -> VERIFYING -> COMPLETED/FAILED/RECOVERY_REQUIRED`, separate signed/authorized distribution gate.

## 4. Semantic parity oracle
Given identical `SceneRevisionV1` and project scope, stable command/schema version, authority/consent, logical typed args and deterministic ID policy, invoke from EDITOR_BUTTON vs CLI (and MCP adapter when supported). Compare:
1. owner validation/permission/typed failure status, diff and affected entity/asset/prefab keys;
2. DATA-04 semantic state fingerprint from independently reopened source after commit, with algorithm/version, stable IDs/refs/order;
3. WORLD-02 prefab override/rebase conflicts and source vs runtime publication receipt, no silent conflict winner;
4. GAME-02 source validation/sandbox receipts for script actions;
5. if stable IDs are minted differently, an explicit **bijective remap preserving all graph edges/references and owner provenance**, not fuzzy equality.

Exclude only **declared volatile** transport IDs, UI dock/focus, wall-clock durations, absolute local paths, trace timestamps and job scheduling noise. Semantic ordering, defaults, rights and references **must not** be ignored. Same raw JSON text does not prove semantic equality when runtime state or validation differs; same exit code certainly does not.

## 5. CLI, GUI, MCP adapter behaviors
- **GUI:** EDIT-01 shared `EditorCommandIdV1`, accessible button labels/tooltip/disabled reasons, keyboard/IME focus and progress/cancel, owner-checked capability; click->typed kernel->owner receipt before success UI.
- **CLI:** `stormline <group> <verb> [options]` future syntax only; no shell execution/shell interpolation. Bounded machine `--json` stdout containing schema-tagged events/receipts, safe human diagnostics stderr, stable typed exit-code categories. Input via scoped VFS/project, never arbitrary `file:///etc` or raw script to eval.
- **MCP adapter:** current spec 2026-07-28 stateless requests and older handshake-era mapping negotiated by actual peer, not hardcoded per provider. Tool calls wrap `CommandInvocationV1` without adding privileged arguments. Internally persistent JobHandle/polling maps to MCP Tasks **only where negotiated**. No default HTTP listener, secrets or upload.
- **HEADLESS:** command kernel functions with CORE/DATA only; editor/GFX/audio/GUI not mandatory for project parse/scene validate.

## 6. Concurrency, errors, audit and quotas
- Pooled workers cannot weaken expected_revision/CAS. Two simultaneous patch requests return one commit and one conflict/explicit rebase, never silent last-write-wins.
- Retry with same idempotency key+same digest resolves prior receipt; key+different digest yields `A01_IDEMPOTENCY_CONFLICT`. A timed-out client must **poll** operation by opaque project-scoped ID; cannot infer rollback.
- Batch is **not implicitly atomic**; atomic multi-asset plans belong future AI-07 and owner journal proof. JSON-RPC notifications have no confirmation; no mutating fire-and-forget through them.
- Strict validation quotas for argument bytes/nesting/strings, depth/records/affected asset count, request/actor rate, wall CPU budgets, output pages, dry-run cost and cancellation. Unknown required schema/version must fail closed.
- Typed error codes: `A01_UNKNOWN_COMMAND`, `A01_SCHEMA_VERSION_UNSUPPORTED`, `A01_REQUIRED_FEATURE_UNKNOWN`, `A01_ARGUMENT_INVALID`, `A01_INPUT_BUDGET_EXCEEDED`, `A01_CAPABILITY_DENIED`, `A01_PROJECT_SCOPE_DENIED`, `A01_ASSET_STALE`, `A01_EXPECTED_REVISION_CONFLICT`, `A01_IDEMPOTENCY_CONFLICT`, `A01_PREVIEW_STALE`, `A01_PLAN_CONFIRMATION_REQUIRED`, `A01_OWNER_UNAVAILABLE`, `A01_SOURCE_COMMITTED_RUNTIME_PENDING`, `A01_JOB_NOT_SUPPORTED`, `A01_JOB_CANCEL_PENDING`, `A01_EXPORT_TARGET_UNAVAILABLE`, `A01_RECOVERY_REQUIRED`, `A01_PARTIAL_OUTCOME`, `A01_OUTPUT_REDACTED`.
- Audit via CORE-06 stable OperationId/actor/CommandId/project/owner/source revision/permission decision, redacted inputs, no secrets/prompts/shell/credentials, local retention. MCP prompts/project text are **untrusted data**.

[Architecture](../architecture/ai-01-headless-command-kernel.md) · [ADR-0060](../adr/0060-ai-01-shared-semantic-command-kernel.md) · [128 tests](../testing/ai-01-acceptance-matrix.md) · [Benchmark](../research/ai-01-command-benchmark-protocol.md).
