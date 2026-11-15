# GAME-04 — Typed Gameplay, Events, Abilities, State, Save and NET Semantic API v0.1

**Research #220 | NLE-P00-WO-002-GAME-04 | code #60 OPEN/BLOCKED. PROPOSED semantic contract, not compilable C++ or shipped wire ABI.** Owner is GAME-04 unless noted; no dependent API is implemented.

## 1. Universal envelope primitives and invariants
| Type | Mandatory fields / semantics | Invariant & authority |
|---|---|---|
| `GameWorldContextV1` | ProjectId, WorldId, WorldInstanceEpoch, SceneId, TickId, fixed delta, server role, content revision digest, rules revision | CORE-04 tick, WORLD-01 epoch, WORLD-02 SceneId, NET role |
| `GameIdV1` | namespaced stable identifier/version for ability, rule, state, tag, event, quest, item; canonical bytes | never C++ RTTI/string-only hash as persisted identity; DATA-02 assets |
| `GameplayCommandV1` | command ID, origin (seat/script/server/authoring), actor EntityGuid, action/operation ID, expected epoch/world/state/inventory revisions, principal/role, issued tick, payload schema/version, idempotency key | untrusted until permission/schema/limits/NET verified |
| `GameEventEnvelopeV1` | EventId, EventSchemaId/version, immutable typed payload/hash, WorldEpoch, TickId, phase, origin command, causation, correlation, authority/visibility, source/target stable GUID, stable sequence | bounded, strictly ordered at authoritative barrier |
| `EventSubscriptionV1` | scoped world/epoch, schema filter, capability/read-set, priority, bounded subscriber generation/token | invalidated on world unload/hot reload; no exposed native pointer |
| `EventQueueBudgetV1` | max events/tick, bytes, fanout, recursion/causal depth, per-origin rate, stall limit | fail explicitly for authoritative overflow |
| `GameMutationIntentV1` | typed permitted patch / WorldEntityCommandRef, expected entity generation/schema, declared read/write set, origin | GAME-02 may stage, WORLD-01 commits |
| `GameCommitReceiptV1` | command/event ids, ACCEPTED/DENIED/CONFLICT/STALE/PENDING, before/after world rev, tick, ordered accepted patches, rejected reasons, replay digest, visibility | accepted command is NOT equivalent to durable save or net delivery |
| `GameSystemDescriptorV1` | SystemId, phase, declared read/write components, deterministic priority, dependency IDs, affinity restrictions, max work | CORE-03 scheduler/phase barrier owns execution |
| `GameplayTraceV1` | tick/epoch, input/action digest, event count, stage/commit hashes, system spans, dropped CUE count, redacted error counters | CORE-06 metadata, not player secrets |

## 2. Game states, scene flow and typed outcomes
| Type | Fields | Guarantees |
|---|---|---|
| `GameStateDefinitionV1` | StateId, parent optional, schema revision, allowed transitions, transition guard IDs | no implicit transitions or uncontrolled graph loops |
| `GameStateSnapshotV1` | StateId, revision, world/scene epoch, transition sequence | immutable read side |
| `GameTransitionRequestV1` | old/new StateIds, expected revision, initiator/role, guard args, tick | reject concurrent stale transition; no mid-step mutation |
| `GameTransitionReceiptV1` | id, status, old/new, applied TickId, reject reason | state changes only after successful barrier |
| `SceneFlowRequestV1` | SceneAssetId/SceneId, world epoch, transition kind (PUSH/REPLACE/OVERLAY/RETURN), required assets/revision, expected handoff | WORLD-02 composition and WORLD-01 activation |
| `SceneFlowReceiptV1` | PREPARING/READY/ACTIVATED/CANCELLED/FAILED, source scene rev, activation epoch, failure & recoverability | never claim loaded because requested; last-good on failure |
| `SceneHandoffV1` | stable entity GUID mapping, scoped persisted session state, pending events/cooldowns, stream policy | no ephemeral raw entity handles saved |

## 3. Abilities, combat, effects
| Type | Fields / behavior | Invariants |
|---|---|---|
| `AbilityDefinitionV1` | AssetId/rev, AbilityId, grants/required/blocked tags, charges, resource costs, cast/channel/cancel rules, cooldown group, effects, script hook refs | data source via DATA, no arbitrary native code |
| `AbilityGrantV1` | grantee GUID, grant ID/source, role, expiry/conditions, revoke sequence | verified entitlement, explicit remove |
| `AbilityActivateRequestV1` | actor, target typed refs, aim sample, tick, expected ability/resource/cooldown rev and command id | NET + state/LOS/energy validation |
| `AbilityStateV1` | grant ID, READY/PENDING/ACTIVE/INTERRUPTED/COOLDOWN, charges, expiry TickId | no wall-clock authoritative cooldown |
| `CooldownStateV1` | ability/group key, start tick, deadline tick, pause policy, charges, rev | exact inclusive/exclusive boundary; overflow checked |
| `ResourceCostIntentV1` | typed attribute, amount, expected revision, refund/cancel policy | cost/cooldown/effect commit atomically or explicit rollback |
| `DamageIntentV1` | source/target GUID, typed damage category, amount & unit, stage, hit/physics receipt, expected health rev | finite/clamped, server-authorized, not authoritative cue |
| `DamageCommittedV1` | pre/post health, mitigation components/order, kill/assist attribution, world revision | built from commit, not client message |
| `StatusEffectDefinitionV1` | AssetId/rev, effect ID, duration ticks, periodic interval, stacking/dispel rules, immunities, modifier expression | bounded chain and deterministic comparator |
| `StatusEffectInstanceV1` | EffectInstanceId, source, target, stack, apply/expire tick, next periodic tick, schema rev | no dangling target or recursive fire |
| `AbilityReceiptV1` | activation/denial ID, cost/cooldown state rev, effect commit refs, reason, observed authority | prediction status separate from committed state |

## 4. Inventory, quest and save hooks
| Type | Fields / behavior | Invariants |
|---|---|---|
| `ItemDefinitionV1` | DATA-02 AssetId/rev, class/tags/stack limit/mass/slot restrictions | stable rights/provenance |
| `ItemInstanceV1` | ItemInstanceGuid, definition rev, quantity integer, modifiers, owner/seed | uniqueness across world saves/transfers |
| `InventorySnapshotV1` | container GUID, owner, capacity, slots, revision, item map digest | read scope filtered by principal |
| `InventoryOperationV1` | MOVE/SPLIT/MERGE/ADD/REMOVE/EQUIP/CONSUME, source/destination, qty, revisions, command id | atomic transfer or explicit safe failure, never dupe |
| `InventoryReceiptV1` | status, before/after revisions, item lineage, rejection and idempotency outcome | double-submit cannot grant twice |
| `QuestDefinitionV1` | AssetId/rev, QuestId, state DAG, trusted predicates/condition IDs, reward policies | no direct arbitrary code or self-mint rewards |
| `QuestProgressV1` | player/party scope, active state, objective counters, processed committed event cursor, revision | dedupe out-of-order event repeats |
| `QuestRewardReceiptV1` | quest/reward/grant id, source event, committed inventory/currency rev, once semantics | no reward on CUE or uncommitted event |
| `GameplaySaveHookV1` | save intent, completed tick fence, world epoch, source asset revisions, gameplay snapshot rev, state cursor/RNG seed | DATA-04 owns durable I/O/journal |
| `GameplaySaveReceiptV1` | STAGED/DURABLE/FAILED/RECOVERY_REQUIRED, journal token, schema/manifest digest and durability proof | STAGED is not DURABLE; no fake atomic writes |
| `GameplayLoadPlanV1` | source/schema versions, dependency rights, migrations, preview diff, last-good/rollback | deny incompatible unknown required fields |
| `GameplayRestoreReceiptV1` | loaded source rev, migrated schemas, activated world epoch/tick and reconciliation log | cannot double-apply committed rewards |

## 5. Public semantic operations (future)
Read-only `InspectGameplayCapabilities(project,role,target)`, `ListGameplaySchemasPage`, `InspectGameState`, `InspectGameplayEventTrace(tickRange,visibility)`, `InspectAbilityDefinition`, `InspectQuestDefinition`, `PreviewGameTransition`, `PreviewAbilityActivation`, `PreviewInventoryOperation`, `PreviewSceneFlow`, `InspectSaveStatus`. All must report `UNAVAILABLE` while unimplemented.

Authoring via Editor/CLI/MCP: `StageGameplayDefinition(assetId, source, expectedRevision, principal) -> ValidationPlan`, `ValidateGameplayRules(plan)`, `CommitGameplayDefinition(planId, expectedRevision) -> DATA04Receipt`, `CancelGameplayDefinition(planId)`. Mutation permissions are scoped; preview is pure, no automatic live game effects.

Runtime: `SubmitGameCommand(ctx,typedIntent) -> PendingReceipt`, `ApplyGameCommandsAtBarrier(tick) -> GameCommitReceipt`, `PublishCommittedGameEvents(tick) -> EventBatch`, `SubscribeGameEvents(scope,schema,readGrant) -> EventSubscription`, `UnsubscribeGameEvents(token)`, `RequestGameTransition`, `RequestSceneFlow`, `RequestGameplaySave`, `RestoreGameplaySnapshot`. These are **proposed semantic operations only**; no direct public network/OS call.

## 6. Integration contracts and phase crossing
- GAME-01 `InputActionFrameV1` is source input, not proof of entitlement. GAME-02 `ScriptCommandBufferV1` produces intents only, never a WORLD-01 commit receipt. GAME-04 validates context and produces game-level receipts.
- WORLD-02 `SceneAssetV1/SceneSnapshotV1/SceneCommitReceiptV1` govern composition; WORLD-01 validates `EntityGuidV1` and generation at commit. Save hook only requests DATA-04 journal at completed tick; DATA-05 resolves cooked assets.
- NET-02 server approves `SubmitGameCommand`, NET-03 chooses replicated event subset, NET-04 owns rollback authority/reconciliation. CUE not required reliably. NET-06 ratelimits/injection policy. No network transport in GAME-04.
- CORE-04 logical tick and CORE-03 fence define all authoritative phase scheduling. Pause/single-step, reactivation and old-world teardown invalidate subscriptions and commands by epoch.
- Public ID schema and binary/JSON wire encoding remain TBD. DATA-04/NET must approve schema migrations and unknown required-field handling. Do not rely on type names, `std::hash` iteration or host endianness as persistent encodings.

## 7. Typed failure and proof
`UNAVAILABLE, SCHEMA_UNKNOWN, SCHEMA_VERSION_UNSUPPORTED, PAYLOAD_TOO_LARGE, EVENT_QUEUE_FULL, EVENT_CAUSAL_LOOP, EVENT_FANOUT_LIMIT, EVENT_ORDER_COLLISION, SUBSCRIPTION_STALE, WORLD_EPOCH_STALE, ENTITY_GENERATION_STALE, PHASE_INVALID, AUTHORITY_DENIED, CAPABILITY_DENIED, RATE_LIMITED, GAME_STATE_CONFLICT, TRANSITION_GUARD_DENIED, SCENE_NOT_READY, SCENE_ACTIVATION_FAILED, ABILITY_NOT_GRANTED, ABILITY_ON_COOLDOWN, INSUFFICIENT_RESOURCE, TARGET_INVALID, DAMAGE_OVERFLOW, EFFECT_STACK_LIMIT, INVENTORY_REVISION_CONFLICT, INVENTORY_CAPACITY, ITEM_DUPLICATE, QUEST_EVENT_DUPLICATE, SAVE_PENDING, SAVE_FAILED, MIGRATION_REQUIRED, RECOVERY_REQUIRED, CANCELLED`. Every error includes scope/operation/correlation/phase/retryable, sans secrets.

**Compatibility:** proposed V1 is not an engine ABI; exact enums, serialization, memory limits, lifetime guarantees, migration policy, numeric thresholds and release class require subsequent owner-approved ADR + implementation WO. Future **128 test cases NOT EXECUTED** in [matrix](../testing/game-04-acceptance-matrix.md).
