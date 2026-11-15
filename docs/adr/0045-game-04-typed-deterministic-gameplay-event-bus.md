# ADR-0045 — Stormline-owned deterministic typed gameplay event bus and command gateway

**Status: PROPOSED (NOT OWNER APPROVED)** | Date 2026-11-15 | Research `NLE-P00-WO-002-GAME-04` / issue #220 | Future implementation #60 BLOCKED.

## Context
Stormline catalogs 2D/2.5D/3D/Web genre-independent gameplay; GAME-01 input frames, GAME-02 sandbox scripts and WORLD-02 scene/prefab world mapping are documented only. Any generic immediate emitter risks handler-order nondeterminism, recursive world mutation, stale entity access and unauthorized multiplayer item grants. Conversely, full event sourcing of every entity/component change would multiply persistence, ABI and performance risks. Need stable typed semantics separate from optional third-party ECS libraries.

## Proposed decision
1. Own `GameCommandGatewayV1`, `GameEventEnvelopeV1`, bounded `GameEventQueueV1` and `GameCommitReceiptV1` semantic API. Events are versioned data with stable IDs, scope, epoch/tick/phase, origin/causation and typed payload; an arbitrary event string cannot invoke game code.
2. **Simulation commands** validated for authority/read-set/expected state, staged before CORE-03/WORLD-01 deterministic commit. Subscriptions are read-only observers producing typed subsequent intents. No synchronous reentrant gameplay writes; deterministic sort/tie-breaking and bounded queues at phase barriers.
3. **Cosmetic cues** are separate non-authoritative best-effort projections, never combat/inventory/quest sources of truth. **Editor/authoring** is a third lane using DATA-04 CAS, not live privileged command.
4. Lifecycle and scene transitions hold expected world epoch/revision, staging/quiescence and explicit cancellation. WORLD-02 composes scenes; GAME-04 coordinates policy only.
5. Define composable data models for abilities, cooldowns, damage/status, inventory, quests and save hooks. Never hardcode a genre. GAME-02 script hooks stage actions through same validator. NET owns server role, replication and prediction, not GAME-04.
6. Track logical committed events for deterministic replay/quest audit. Do **not** mandate a complete append-only persistence architecture or claim atomicity across ECS, DATA-04 and network. Durable outbox and idempotent recovery are future proof gates.
7. C++20 strong types and Stormline-owned public ABI are *hypotheses*. Compare EnTT (MIT), Flecs (MIT) and owned minimal event queue before selecting an implementation. No library is selected, linked, pinned or copied. Engine code license NLE-D009 stays OPEN.

## Alternatives and trade-offs
| Alternative | Advantages | Risks and reason not auto-chosen |
|---|---|---|
| Immediate global message bus (`std::function`, EnTT trigger) | simple, low dispatch overhead | handler ordering/recursive mutation; cannot be core authoritative bus |
| EnTT `dispatcher` + deterministic Stormline wrapper | C++20-friendly MIT, queued API and scoped connections | upstream immediate/queued behavior does **not** guarantee authoritative total order; owns no server auth, persistence, stable schema |
| Flecs observers/staging | MIT, ECS-local queries and event observers | coupling WORLD-01 to second ECS and stage semantics; avoid reusing as public cross-system event ABI |
| Owned minimal typed queue + compile-time registry | explicit bounded order/ownership and minimal dependencies | maintenance, reflection and memory cost; profile and fuzz before selection |
| Generic third-party event sourcing broker | durable audit/history | external costs/complexity, serialization and replay of every mutation; reject for current generic engine scope |
| Unity/Unreal gameplay frameworks | rich examples of fixed-tick/prediction/ability lifecycle | proprietary platform integration and incompatible engine runtime; **conceptual comparisons only**, no copying code |

## Consequences / quality gates
Benefits: shared engine contracts for shooter/platformer/RPG/puzzle; stable replay semantics; explicit authority, event/cue separation; clear extension points for visual scripts. Costs: ceremony, schema migrations, queue memory and incident receipts; deterministic multi-threading may reduce peak throughput and require stress/profiling. Benchmark throughput/tails and target tests before any claim. Future implementation risk **ELEVATED** due to persistence, deterministic state, multiplayer and security; privileged money/transaction use would independently be **HIGH_ASSURANCE** and outside baseline.

**Acceptance evidence required:** eight research docs, 128 future tests accurately tagged NOT EXECUTED, benchmark protocol, official license/source matrix, exact-head Docs Validation, pt-BR audit, normal squash/readback, separate checkpoint PR with only GAME-04 `research_status` change. **No implementation authorization**, 80 code packets remain blocked and `executor_ready=false`.

**Decision owners:** product owner accepts/rejects after review; embedding any dependency requires a separately approved/pinned supply-chain ADR and exact-license audit. `PROPOSED` is not a binary release, not a merged technical adoption.
