# GAME-04 — Gameplay Systems & Deterministic Typed Event Bus Architecture v0.1

**NLE-P00-WO-002-GAME-04 | research issue #220 | future implementation #60 OPEN/BLOCKED | 2026-11-15.** Base `b64194591d761cd3e785337b10a524d085ec04d1`. **PROPOSED / DOCUMENTARY ONLY.** No engine code, runtime bus, scene loader, inventory, quests, save engine, game executable, multiplayer, tests or performance measurements exist.

## 1. Purpose, flexibility and ownership
GAME-04 is the genre-neutral orchestration layer. It provides typed events, game/session state transitions, scene-flow *requests*, data-driven ability and effect semantics, bounded rule execution, inventory/quest transactions, persistence hooks and simulation receipts. It must permit independent original platformer, shooter, RPG and puzzle game projects to reuse exactly the same engine API without forking CORE or embedding ARPG-only assumptions. These examples are **future acceptance fixtures**, not released templates. Genres ship rules/data or GAME-02 scripts, not specialized engine forks.

| Authority | Owned capabilities / integration | GAME-04 does NOT own |
|---|---|---|
| CORE-04 | TickId, rational fixed simulation step, pause and replay time policy | independent clock or wall-time cooldown |
| CORE-03 | scheduler, read/write dependency jobs, deterministic apply barrier and cancellation | second job pool or unordered world mutation |
| CORE-05/06 | typed quantities / deterministic scalar reference; redacted trace and correlation | unbounded float behavior or live telemetry sink |
| WORLD-01 | ECS entity/component schema, scoped immutable snapshots, generational handles and commit | second ECS, direct archetype writes or raw native pointers |
| WORLD-02 | SceneAsset/Prefab hierarchy, stable NodeGuid/SceneId, source-to-world instance mapping | duplicate scene graph, prefab overrides, transforms or scene ownership |
| GAME-01 | InputActionFrameV1, seat, focus and action maps | raw platform event pump or authority of input provenance |
| GAME-02 | bounded sandboxed textual/visual script invocation, ScriptHostCall/CommandBuffer/Receipt | arbitrary script eval, host privileges, VM/fuel or script hot reload |
| GAME-03 | HUD, semantic UI, focus, read-only view model | game state mutation by widget; UI event bus as game authority |
| DATA-02/03 | AssetId, source provenance/import checking | custom file reader/registry or remote asset import |
| DATA-04/05 | versioned source CAS, durable journal/migration; cooking/target manifests | independent scene/inventory save filesystem, fake multi-service atomicity |
| NET-01..06 | transports, authoritative server, replication, rollback, sessions and abuse controls | sockets, anti-cheat, network security, RPC/replication library |
| AI-01/EDIT/CLI/MCP | role-scoped public author/inspect/preview/commit operations | direct server gameplay powers or shell access |

**Dependency truth:** catalog prerequisites are GAME-02, GAME-01, WORLD-02. WORLD-01, CORE-03, CORE-04, DATA, NET are interface integrations / validation gates, not newly invented catalog prerequisites. All are proposals, none implemented.

## 2. Proposed architecture: one event model, explicit lanes
```text
GAME-01 input frame / NET server-validated command / GAME-02 authorized script intent
       -> GameCommandGatewayV1 (origin, principal, epoch, tick, idempotency)
       -> structural/schema/ability/ACL/resource checks against read snapshot
       -> ordered command plans + bounded deterministic GameEventQueueV1
       -> CORE-03 declared system phase graph and read-only parallel evaluation
       -> deterministic stable sort of proposed effects & event envelopes
       -> WORLD-01 authoritative mutation barrier / transaction receipts
       -> GAME-04 after-commit durable logical event journal and projections
       -> GAME-03 view model + AUD/VFX cosmetic cues; NET replicates authorized subset
       -> DATA-04 durable save snapshots/outbox and migration hooks when requested
```

Three explicitly different lanes:
1. **Simulation authoritative** (`SIM_EVENT`) is tick-bound, typed, ordered, replayable and eligible for state mutation *only* via command validation/commit. No recursive synchronous handlers, no wall clock, no I/O, no GPU.
2. **Presentation cosmetic** (`CUE`) is a derived, droppable, de-duplicated projection; it may drive sound, VFX and UI but must never decide damage, inventory, quests or authority. Missing cues cannot alter truth.
3. **Lifecycle / authoring** (`EDITOR_EVENT`) is out-of-band, transaction-scoped and permissioned; source edits via DATA-04 CAS. Never relay a preview event to live simulation as a command.

No global wildcard synchronous emitter for gameplay. No duplicate authority bus hidden in scripting, UI, WORLD or NET. An optional EnTT/Flecs adapter is internal; the public contract is Stormline-owned.

## 3. Tick phases, determinism and causal boundaries
Proposed simulation phases (names subject to approved CORE-04/WORLD-01 contract): `INGEST_ACTIONS -> READ_WORLD -> EVALUATE_RULES -> VALIDATE_INTENTS -> APPLY_WORLD -> COMMIT_EVENTS -> DERIVE_PRESENTATION -> SAVE_HOOK_STAGE`. Only the CORE-03/WORLD-01 owner publishes a commit barrier. GAME-04 cannot invent thread affinity or tick boundaries.

`GameEventEnvelopeV1` includes: schema ID/version, event UUID or deterministic composite key, world epoch, TickId, phase, source/target stable EntityGuid, origin command/causation ID, correlation chain, server authority role, per-origin monotonic sequence, immutable bounded payload and payload digest, visibility/replication class. Canonical serialization and stable sort (`TickId, phase, authority priority, origin command sequence, stable origin EntityGuid, local event ordinal`) are proposal; stable ordering must be compared against collisions/rollover and cross-target encodings. Do not expose raw pointer/iterator or nondeterministic hash iteration.

Subscribers declare read-set and intent output type. Handler may only enqueue a *next admissible phase/tick* command. Self-emission/fanout chains are guarded by max depth, work bytes, count/tick and rejection with trace; no recursive reentry. On overflow: reject uncommitted intents with explicit bounded error, not drop authoritative transactions silently. Cross-thread work may read immutable snapshots; consolidation is deterministic, never observer-scheduled mutation order. Unsubscribe/world teardown invalidates generation-scoped subscription tokens.

Determinism scope is **same schema, same fixed-tick input, seed, authority state, build/target numeric policy and content revision**. Cross-OS/CPU or floating-point bit-equality is NOT asserted. Define reference fixed-point/integer semantics for economy-like gameplay counters and damage; choose fixed-point or explicit reproducible float when proven. Server simulation is source of truth in multiplayer; client prediction/reconciliation belongs NET-04. GPU, wall time, native thread interleaving and external requests never enter replay hash.

## 4. Game state and scene-flow orchestration
`GameSessionStateV1` has an explicitly validated, extensible state graph (Boot/Loading/Menu/Playing/Paused/Ending sample states only), transition guard, expected revision, world/scene epoch, initiator, reason and stable transition receipt. Guards are pure and evaluated against committed read snapshot; unauthorized, cyclic or concurrent transitions require explicit denial/conflict. State transitions are atomic at a game-state barrier, never mid-physics callback.

`SceneFlowRequestV1` references DATA-02 AssetId/SceneId + expected WorldEpoch, staging policy, serialized handoff scope and cancellation token. WORLD-02 owns loading, composition, prefab/variant resolution and reparenting, WORLD-01 owns entity activation/destruction, DATA-05 owns asset cooking/streaming. GAME-04 only requests and coordinates `PREPARE -> READY -> ACTIVATE_AT_BARRIER -> QUIESCE_OLD -> RETIRE`; on failed load preserve last-good scene and return `SCENE_ACTIVATION_FAILED`. A pause/menu overlay must not implicitly unload persistent world. No hidden cross-scene dangling EntityHandle; durable GUID remapped with explicit receipts.

## 5. Ability, cooldown, combat and status effects
Abilities are **authored data** (`AbilityDefinitionV1`; DATA-02 AssetId, revision) plus optional GAME-02 script hook. They specify grant/require/block tags, cost, targeting, cast/cancel window, cooldown policy, effect graph, max chain and capability. Lifecycle: `GRANTED -> READY -> REQUESTED -> VALIDATED -> ACTIVE -> COMMITTED -> COOLING_DOWN -> READY`, plus DENIED/CANCELLED/INTERRUPTED/REVOKED branches. Cost and cooldown commit together with the authoritative activation or neither does. No arbitrary asynchronous ability task is allowed to mutate ECS off barrier.

- **Cooldown:** deadline in CORE-04 TickId + policy (charges, groups, stacking, dispel, pause effects), not host time; explicit inclusivity of tick boundary and numeric overflow handling. Predicted UI timers are cosmetics.
- **Damage:** pipeline `DamageIntent -> source/target grant and range/LOS validation -> deterministic resistance/mitigation/order -> clamp/saturate -> WORLD-01 HealthComponent patch -> DamageCommitted receipt`. Elemental/status stats are typed IDs and fixed units, never strings at runtime; friendly fire/team rules are project data. Combat hit results/LOS may consume SIM/PHYS authoritative query receipts; GAME-04 never invents collision.
- **Effects:** `StatusEffectDefinitionV1` has ID, duration tick, modifier stacking strategy (`ADD/MAX/REFRESH/REPLACE/INDEPENDENT`), dispel priority, periodic tick, immunity tags and source attribution. Explicit stable order and cap; expired source or target produces cleanup. Prevent recursive on-hit chains, overheal/underflow, poisoned zero-duration loops, NaN/Inf and overflow. Cosmetic CUE is separate from committed effect.
- **Rule purity:** deterministic evaluation reads immutable state, emits bounded typed effect intents. Script can propose but cannot skip GAME-04 validators, WORLD-01 CAS/generation or NET authorization.

## 6. Inventory, quests and persistence
`InventoryLedgerV1`: stable ItemInstanceGuid, ItemDefinition AssetId/revision, quantity typed integer + max bound, container GUID, slot policy and ownership. Item move/stack/split/equip/consume/drop are single validated operations with expected inventory revision, capacity, duplicate/idempotent command key and conflict receipt. No dupe through multi-container partial commit; cross-container atomicity or explicit staged saga with compensation/recovery REQUIRED. Multiplayer loot attribution/spawn authorization server-owned; no client item creation.

`QuestDefinitionV1` (data) and `QuestProgressV1` (player scoped, versioned): FSM objectives with trusted `EventSchemaId` predicates, event cursor/tick and monotonic progress, dedupe by committed authoritative event ID, replay-safe grant/reward once. Branching missions may reset only under explicit scope and revision/authorization. Sandbox script/query cannot read secret player profile fields or award currency. Quest definitions are not hardcoded in core.

`GameplaySaveHookV1` is a **request for DATA-04 snapshot transaction** at safe completed tick, not direct file I/O. Include game-state/quest/inventory versions, pending cooldown/effect deadlines, committed event cursor, content/ABI fingerprint, stable entity GUID and world/scene revision, deterministic RNG state. Stage source/persistence separately from runtime application; `SAVE_STAGED` != `SAVE_DURABLE` != `LOAD_ACTIVATED`. On crash/mismatch: recovery journal, preflight migration, last-known-good and explicit `RECOVERY_REQUIRED`. Side effects (emails, payments, achievements, net dispatch) need authoritative idempotent outbox, never naive replay.

## 7. Multiplayer, rollback and trust
NET-02 validates source principal/session/role, input sequence, world/scene epoch, rate and ability entitlement before applying; NET-03 replicates approved state snapshots/event projections; NET-04 manages prediction rollback and resimulation with snapshot ring under memory budgets. A client-side proposed ability/loot/drop event is **not authority**. `CommandId` and `CommittedEventId` underpin duplicate suppression and reconciliation. Idempotency retention/window and epoch rollover must be explicitly specified before code.

Network serialization formats and wire IDs are owned by NET; GAME-04 provides type semantics, versioned adapter inputs and visibility flags. Quest/inventory/private stats redact to principals/interest scopes, and CUE losses do not desync authoritative state. No game-event envelope is an unrestricted RPC. Disconnect/reconnect and host migration do not imply already-safe transaction replay.

## 8. Authoring parity, security and error model
Editor/CLI/MCP semantic operations: `InspectGameplaySchema`, `StageAbility/Status/Quest/InventoryRules`, `ValidateGameplayDefinition`, `PreviewGameTransition`, `PreviewEventFlow`, `CommitGameplayDefinition(expectedRevision)`, `InspectGameplayTrace`, `GetGameplayCapabilityReport`. Mutations are DATA-04 CAS with project-scoped rights, redacted receipts and no live arbitrary `EmitEvent` from untrusted MCP/LLM. Live game commands are session/NET-authorized and not exposed through generic authoring interface.

Security gates: never trust untyped JSON/mod script/UI/network payload; schema allowlist, UTF-8/string/size/depth/collection quotas, numeric finiteness/overflow, event storm controls, entity/role/epoch check, no payload secrets in telemetry, explicit errors `SCHEMA_UNKNOWN`, `UNAUTHORIZED`, `ENTITY_STALE`, `STATE_CONFLICT`, `EVENT_BUDGET_EXCEEDED`, `ABILITY_ON_COOLDOWN`, `INSUFFICIENT_RESOURCE`, `INVENTORY_REV_CONFLICT`, `QUEST_DUPLICATE`, `SAVE_PENDING`, `RECOVERY_REQUIRED`. No text injection interpreted as gameplay code. Limit subscription lifecycle leaks and denial-of-service via fanout, malformed DAG and hot reload.

## 9. Future evidence, boundaries and delivery stages
**NECESSARY future proof only (still BLOCKED):** one original headless deterministic state machine; typed bounded tick/phase event commit; one data-defined generic ability with cooldown and health effect; scene flow request; save-hook receipt; replay hash; another distinct project reusing API without modifying CORE. Candidate goals not hard acceptance measurements.

**IMPORTANT later:** status stacking, transactional inventory, quest reward idempotency, native+Web parity, scoped game UI, robust network authoritative adapters and rollback tests. **FUTURE:** complex combat designers, visual editors, advanced quests, mod marketplaces, economy SDK and live ops. **OUT OF SCOPE:** MMORPG framework hardcoding, copying proprietary GAS code/assets, direct OS/network IO, paid hosted dependencies.

See [ADR-0045](../adr/0045-game-04-typed-deterministic-gameplay-event-bus.md), [contracts](../contracts/game-04-gameplay-event-api.md), [128 FUTURE tests](../testing/game-04-acceptance-matrix.md) and [benchmark protocol](../research/game-04-gameplay-benchmark-protocol.md). All plans are NOT EXECUTED; numbers, ABI and feature class remain UNDECIDED.
