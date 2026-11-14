# SIM-03 — Typed Character Motor, Intent, Contact and Movement Receipt API v0.1

**Research #180 | WO NLE-P00-WO-002-SIM-03 | Code #48 BLOCKED**. Semantic proposal, NOT compiled C++ ABI or stable persisted schema.

| Type | Proposed fields | Validation / authority |
|---|---|---|
| `CharacterMotorHandleV1` | ProjectId, WorldId, WorldInstanceEpoch, slot, generation, Dimension | Reject stale, foreign-world and dimension mismatched handle |
| `CharacterMotorProfileV1` | AssetId/revision/hash, movement dimension, mode, shape source, physical scale, acceleration, max speed, gravity, jump, slope, skin, snap, step, iteration budget, collision filter, action policy | DATA-04 owns saved source; finite positive dimensions, units, caps and rights |
| `CharacterIntentV1` | MotorHandle, TickId, ProducerId, AuthorityEpoch, Sequence, desired move vector, heading/aim, action flags, optional root motion request, expected profile revision | Only approved GAME/AI/NET producer, exact tick and finite bounded input; idempotent duplicate handling |
| `GroundSupportV1` | Support BodyHandle/CellId/CollideRevision/WorldEpoch, normal, local hit point, linear/angular support velocity, trust/ready flag | No stale platform generation or nonresident ground claimed grounded |
| `CharacterMotorStateV1` | TickId, global/local pose, velocity, grounded/wall/ceiling state, support, action grace counters, active motion mode, origin epoch, backend numeric profile | Readonly post-tick snapshot; no renderer overwrite |
| `MotorMotionReceiptV1` | TickId, accepted Sequence, requested/applied delta, contact normals+IDs, source collider revisions, action results, completeness, bounded diagnostics/events | Egress after safe post-step barrier, immutable and redacted |
| `CharacterMotionErrorV1` | Code, severity, handle, TickId, expected/observed epoch or revision, recoverability, safe last state | Typed errors never claim successfully moved on unknown collider |
| `CharacterMotionCapabilitiesV1` | Dimension, kinematic/dynamic, shape types, step/snap/one-way/platform, deterministic profile/precision, native/WASM support | Expose measured backend support, never assume all tiers |

## Operations (semantic)
1. `StageMotorProfile(profile, expected_source_revision, actor)` → validated DATA-04 authored change preview; durable CAS/journal independent from runtime install. Does not mutate physics immediately.
2. `AttachMotor(entity, profile, physics_world_epoch)` → a scoped MotorHandle at a pre-step barrier; requires SIM-01/02 collider validated + WORLD entity live.
3. `SubmitIntent(motor, tick, seq, actor, requested_motion)` → queued intent receipt, idempotence key and authorization; never direct memory write.
4. `StepMotorAtFixedTick(world, tick)` → internal only, bounded collision query and effect publication after PHYS step agreement; rejects double step or unready world.
5. `ReadMotorState(motor, confirmed_tick)` → immutable snapshot, completeness and generation checks.
6. `ReadMotionReceipts(world, after_tick, max_events)` → quota and privacy filtered, cursor and dropped-event explicit.
7. `StageCrouchOrShapeRevision(motor, source_revision)` → safe clearance and contact rebuild or explicit denied reason.
8. `DetachMotor(motor, expected_epoch)` → deferred retirement after PHYS contacts consumed; invalidates generation.
9. `ApplyOriginRebase(world, expected_epoch, new_epoch)` → internal barrier coordinated with WORLD-03 and SIM owners, no mid-tick offset mutation.

## Explicit error codes
`INVALID_INPUT`, `NONFINITE`, `OUT_OF_BOUNDS`, `UNAUTHORIZED`, `STALE_HANDLE`, `WRONG_WORLD`, `WRONG_DIMENSION`, `PROFILE_REVISION_MISMATCH`, `TICK_OUT_OF_ORDER`, `DUPLICATE_CONFLICT`, `COLLIDER_PENDING`, `COLLIDER_REVISION_MISMATCH`, `MOTION_BLOCKED`, `SWEEP_BUDGET_EXCEEDED`, `BACKEND_UNSUPPORTED`, `ORIGIN_EPOCH_MISMATCH`, `WORLD_UNLOADING`, `RESOURCE_LIMIT`, `INTERNAL_FAILURE`.

## Contract invariants
- At most one committed authoritative motor step per motor per `TickId`. Duplicate identical intents have idempotent receipt; conflicting duplicates fail.
- Character 2D vs 3D is explicit; physics engine owns collision filters and shape casts. The motor returns `PARTIAL` or `COLLIDER_PENDING` if grounding data are incomplete.
- Render interpolation, root-motion visual playback and camera look never alter committed pose.
- Epoch and profile revision are included in every replay artifact; rollback snapshot must include motor state **and** complete solver state, or explicitly restart from a canonical initial world and full input log.
- Editor/CLI/MCP may author approved profile fields through DATA-04 common transactional kernel, not teleport a privileged live player unless a separate explicitly authorized GAME command exists.
