# NET-02 — Headless Dedicated Server, Match Lifecycle, Command Admission and Tick Semantic API v0.1

**NET-02 research #232 | NLE-P00-WO-002-NET-02 | future code #63 OPEN/BLOCKED. PROPOSED ONLY: not compiled C++ headers, wire ABI, executable, cloud API or tested security controls.**

## 1. Authoritative semantic types
| Type | Mandatory semantic fields / scope | Ownership and validation |
|---|---|---|
| `DedicatedServerBuildV1` | source Git HEAD, content/ABI/schema revisions, platform/arch, headless=true, toolchain digest, license/SBOM and runtime capabilities | CORE/PLAT; no hidden renderer/GPU/Audio backend |
| `DedicatedServerConfigV1` | expected revision, listen policy, bind port, tick config ref, max match/player/resource budgets, trust profile and privacy | DATA-04 source CAS + secure secrets owner; no inline private key |
| `DedicatedServerProcessIdV1` | process instance opaque ID, generation, boot epoch, host/report origin | never an authentication token |
| `ServerProcessLifecycleV1` | BOOTSTRAP, CONFIG_VALIDATING, BINDING, WARMUP, READY, DRAINING, TERMINATED, FAILED, UNHEALTHY | valid transition table and monotonic deadlines, readiness != socket open |
| `GameMatchIdV1` | match ID, allocation generation, world epoch, game mode/feature pack/content digest and isolation class | NET-05 issues/allocates; NET-02 binds exact authority world |
| `GameMatchLifecycleV1` | CREATED, ALLOCATED, LOADING, WAITING_FOR_PLAYERS, RUNNING, COMPLETING, FINALIZING, CLOSED, FAILED | cannot re-enter RUNNING from CLOSED without fresh generation |
| `GameServerPrincipalV1` | issuer, audience, match ID, player/actor claims, role, expiry, nonce/session generation, revoked flag | NET-05 authenticates, NET-02 checks; NET-01 handshake alone not trusted game identity |
| `AuthoritativeWorldBindingV1` | WORLD-01 WorldId/WorldEpoch, authoritative ECS barrier/version, scene/content hash, physics/sim revision | only WORLD-01 commit alters authoritative state |
| `FixedTickScheduleV1` | CORE-04 TickId/phase, rational rate/step, accumulator/catch-up limit, overrun policy, drift and monotonic clock mapping | CORE-04 clock, CORE-03 scheduler; not packet arrival wallclock |
| `ClientActionIntentV1` | connection epoch, principal/match/world epoch, owner actor, action ID/type, bounded params, client input seq/tick hint, correlation | do not accept client authoritative components, score, health, items |
| `ServerIngressBatchV1` | per-match frozen validated packet batch, ordered sender ordinal, max backlog/bytes/CPU and deadline | NET-02 admission before GAME-04; no handlers reenter ECS |
| `GameCommandValidationReceiptV1` | rejected/validated_pending/committed/duplicate, actor/permissions/phase/rate/tick, reason, world version, gameplay idempotency key | GAME-04 returns game commit receipt, distinct NET-01 transport ACK |
| `ServerTickReceiptV1` | expected/actual TickId, state hash profile, input count, accepted/rejected, work phases CPU, overrun/catch-up, output snapshot handoff | no claiming state hash equal across OS without proven policy |
| `MatchResourceBudgetV1` | max players/sessions, CPU per tick, wallclock, memory/heap, ingress queue, script gas, effects fanout, snapshot and log bytes | quotas local to match and aggregate host, no slow actor starvation |
| `MatchIsolationLeaseV1` | process/match/world epoch, owner, expiry, generation/fence token, allowed resource partitions | can prevent stale ownership but not proof multi-tenant sandboxing |
| `ServerReadinessReportV1` | process health, per-match readiness/overrun, config version, event loop and transport health, last successful tick | aggregate load health must not be falsified by constant /health 200 |
| `ServerDrainIntentV1` | operator permission, no-new-match flag, per-match close grace, save/ack policy, required endpoint status | TERM/SIGKILL may interrupt, no save guarantee |
| `MatchCheckpointPlanV1` | DATA-04 checkpoint/journal id, world source revision, TickId and game event cursor, app side effects/outbox | DATA-04 owns durable CAS, no ad hoc file writing |
| `OptionalRollbackPolicyV1` | NET-04 approved game mode, max rewind ticks/memory, allowlisted state, physics replay and irreversible exclusions | default DISABLED; no purchase/loot reward rollback |
| `ServerDeploymentPlanV1` | LOCAL_PROCESS or OPTIONAL_OCI/AGONES/MANAGED, target OS, network ports, image digest if any, secret references, capability and cost/consent | planned only, never auto-provision paid/public infrastructure |
| `ServerOperationsPrincipalV1` | authenticated operator role and scopes, project/match affinity, action limits, explicit consent token | no public MCP shell or privileged raw world edit |
| `ServerAuditTraceV1` | sanitized match/connection correlation, severity, constraint id, timestamp, redacted actor ID, evidence hash | CORE-06/NET-06 observability, no secret/PII/raw inventory leaks |

## 2. Declared operations (future semantic API, not functioning)
| Operation | Preconditions / receipt |
|---|---|
| `InspectDedicatedServerCapabilities(Target)` | read-only report, honest headless build/backend availability, no OS spawn |
| `PreviewDedicatedServerConfig(Project,Config,Principal)` | read-only validated plan, no network bind/secret read; Editor/CLI/MCP same semantic diff |
| `Stage/Validate/CommitServerConfig(Project,Revision,StageId)` | DATA-04 transactional CAS, authorization, secure secret references, no destructive overwrites |
| `RequestLocalServerBoot(BuildId,ConfigRevision,AdminCapability)` | future privileged CLI/test harness only, PID/epoch and real lifecycle receipts; NOT generic MCP |
| `RegisterServerProcess/ReportServerHealth/RequestDrain/RequestStop` | process lifecycle state machine and orchestration adapter, actual PID and authority, bounded deadlines |
| `AllocateGameMatch(SessionTicket,ContentHash,Limits)` | NET-05 allocation; NET-02 creates match/world binding only under signed ticket and capacity |
| `ValidateAndJoinMatch(TransportConnectionId,Ticket,ActorId)` | NET-01 peer identity checked, NET-05 role/session ticket and epoch, NET-02 actor binding and content |
| `SubmitClientActionIntent(Principal,Action,Epoch,TickHint)` | size/rate/schema/ownership/tick bounds, queue immutable intent, return admission receipt not commit |
| `AdvanceAuthoritativeTick(CORE04_TickId,Batch)` | CORE-03 scheduler barrier, GAME-04 validation, WORLD-01 ECS authoritative commit, game receipts |
| `ObserveServerTick/MatchStats/ServerReadiness` | redacted metrics, honest last successful tick and overload, not fabricated CPU/GPU performance |
| `StageGameCheckpoint/CommitGameCheckpoint` | delegated to DATA-04, game authoritative cursor and CAS; no guarantee partial external effect rollback |
| `RequestMatchComplete/Finalize/Release` | close participant data and leases, return typed reason and durable state outcome |
| `RequestHistoricalRewind(ApprovedRollbackPolicy,Window)` | NET-04 approved only; default CAPABILITY_UNAVAILABLE, no arbitrary state edit |
| `InjectSyntheticAction/Faults(TestHarness,Seed)` | only authorized test-only virtual environment, production reject |
| `ExportServerDeploymentPlan(Target,Profile)` | local-first artifact plan; OCI/Agones optional, must not create resource or charge automatically |

## 3. State machine and authority invariants
- Process may be `READY` while match is not `RUNNING`; a `WARMUP` server is not available for public admission; graceful DRAINING rejects new matches and may allow already-admitted bounded safe commands. Unhealthy readiness must consider tick stall, memory and connection health; cannot be manually asserted by client gameplay.
- Every ActionIntent is authenticated to **match and actor** and checked against current WorldEpoch, principal role, input sequence, CORE-04 tick horizon and current GAME-04 rules. Client-provided full-world `StateSnapshot`, component/health/XP/reward/score fields are **not acceptable command types**. There is no "trust host player" bypass in dedicated server mode.
- Frozen tick queue is stable per server policy and independent of scheduler nondeterministic arrival; application events only after GAME-04/WORLD-01 accepted barrier. `ServerTickReceiptV1` may hold state hash, not proof deterministic all platforms.
- `NET01_TRANSPORT_ACKED` means bytes reached transport; `GAME04_GAME_COMMITTED` means authoritative command applied; `DATA04_DURABLE_CHECKPOINT_COMMITTED` means persistence accepted; these are **three distinct receipts**.
- Each match resource/reward/script/outbox has MatchId + generation + WorldEpoch. No cross-match state reads, role escalation, ghost client replay, after-close callbacks or leaks. A future multi-match process must pass isolation tests and may still not be a safe sandbox for untrusted native code.
- Rollback is **DISABLED** unless explicit future NET-04/owner-authorized policy with bounded immutable historical state and proven exclusion of irreversible durable side effects. Do not claim server rollback as automatic when adding lag compensation.

## 4. Error and recovery taxonomy
`SERVER_NOT_IMPLEMENTED, SERVER_BUILD_HEADLESS_UNAVAILABLE, SERVER_GPU_DEPENDENCY_DETECTED, SERVER_CONFIG_REVISION_CONFLICT, SERVER_ASSET_REVISION_MISMATCH, SERVER_PORT_BIND_FAILED, SERVER_BIND_UNAUTHORIZED, SERVER_PROCESS_UNHEALTHY, SERVER_TICK_STALLED, SERVER_TICK_OVERRUN, SERVER_INPUT_BACKLOG_LIMIT, SERVER_TICK_EPOCH_STALE, SERVER_INVALID_TICK_WINDOW, SERVER_CLIENT_STATE_FORBIDDEN, SERVER_ACTOR_OWNERSHIP_DENIED, SERVER_MATCH_TICKET_INVALID, SERVER_MATCH_TICKET_EXPIRED, SERVER_MATCH_TICKET_REPLAYED, SERVER_SESSION_REVOKED, SERVER_UNKNOWN_ROLE, SERVER_CROSS_MATCH_DENIED, SERVER_MEMORY_QUOTA, SERVER_CPU_QUOTA, SERVER_SCRIPT_QUOTA, SERVER_RATE_LIMITED, SERVER_GAME_RULE_REJECTED, SERVER_ACTION_DUPLICATE, SERVER_WORLD_GENERATION_STALE, SERVER_PHYSICS_RECEIPT_STALE, SERVER_MATCH_ALREADY_CLOSED, SERVER_READINESS_NOT_YET, SERVER_DRAIN_IN_PROGRESS, SERVER_CHECKPOINT_CONFLICT, SERVER_DURABILITY_PENDING, SERVER_IRREVERSIBLE_ROLLBACK_FORBIDDEN, SERVER_ADMIN_AUTH_DENIED, SERVER_PRIVILEGED_MCP_DENIED, SERVER_DEPLOYMENT_COST_APPROVAL_REQUIRED, SERVER_PROVIDER_UNAVAILABLE, SERVER_RECOVERY_REQUIRED, SERVER_INVALID_LOG_SECRET, SERVER_UNSUPPORTED_TARGET`.

Every receipt contains normalized error, retryability, scope/correlation and redaction, never player secret/TLS key, private infrastructure address or raw untrusted payload. Limits/fixed tick numeric target/user auth provider/protobuf/wire schema/server ABI/ports remain **TBD and NOT APPROVED**.

## 5. Evidence obligations before activation
Implement code only after upstream prereqs actually implemented, owner-approved ADR/risk/release/license and Context Lock. Prove headless no GPU in a real OS process, two distinct authenticated clients with invalid state rejection, replayable tick/real match shutdown, metrics and no hidden cloud, in tests mapped to [128 future scenarios](../testing/net-02-acceptance-matrix.md). P00 status **NOT IMPLEMENTED; 0 runtime tests executed**.
