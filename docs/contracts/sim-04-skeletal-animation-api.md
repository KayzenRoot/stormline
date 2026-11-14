# SIM-04 — Semantic Skeletal Animation, Motion and Ragdoll Contract v0.1

**WO NLE-P00-WO-002-SIM-04 | Research #183 | Code #49 OPEN/BLOCKED**. Proposed semantic schema only, **NOT** compiled API, native ABI, stable serialized layout or deployed service.

## 1. Versioned identifiers and data contracts
| Contract | Minimum fields | Validation and authority |
|---|---|---|
| `SkeletonAssetV1` | ProjectId, AssetId, ContentHash, JointGuids, parent indices, bind/rest transforms, inverseBindMatrices, unit/basis, source rights | DATA-03 validated DAG, finite transform, unique joint key, no cycles, bounded cardinality and monotonic revision |
| `SkeletalClipV1` | ClipId, SkeletonHash, timebase, duration, key tracks/interpolation, marker/event list, root trajectory, compression codec descriptor/hash | DATA-03 import, DATA-05 cook; sorted bounded finite keys and codec/CRC/size quota |
| `AnimationGraphV1` | GraphId, revision, nodes/edges, params, state transition guards, layer masks, sync groups, event policies | No graph cycles except explicit bounded state transitions, bounded depth, no script function pointers |
| `RetargetProfileV1` | ProfileId/revision, source and target SkeletonHash, joint semantic map, rest-pose corrections, scale/up-axis/twist policy | Finite, bijection where required, missing-joint fallback and exact source/target versions |
| `RagdollProfileV1` | Source SkeletonHash, joint-to-body/constraint mapping, activation policy, collision layer, getup clip IDs | SIM-02 validates bodies/constraints and safe pre/post-step; no arbitrary contact mutation |
| `AnimationInstanceHandleV1` | ProjectId, WorldId, WorldEpoch, entity slot/generation, instance slot/generation, SkeletonHash, GraphRevision | Reject stale/freed generation and foreign world; no native library pointers |
| `GraphParameterCommandV1` | Handle, TickId, ActorId, AuthorityEpoch, sequence, expected graph/source revision, typed parameter writes | Authorized command kernel, exact tick barrier, numeric/domain/size bounds, idempotent duplicate |
| `RootMotionIntentV1` | Handle, TickId, sequence, requested delta position/rotation, velocity cap, source ClipHash/GraphEpoch | Pre-physics request to SIM-03; never direct world transform |
| `RootMotionAckV1` | Requested/applied movement, SIM-03 MotorMotionReceipt reference, collider/world epoch, blocked/partial error | Immutable authoritative receipt; graphics cannot amend |
| `PoseSnapshotV1` | Handle, TickId, skeleton revision, normalized local joints/model matrices or bounded palette, origin epoch, mask/ragdoll state, completeness | Immutable CPU snapshot; GFX consumes read-only, headless possible |
| `AnimationEventReceiptV1` | Handle, TickId, marker ID, graph clip/phase, producer sequence, dedup token, destination domain and trust | Exactly-once **within verified local tick/replay model is a future guarantee to test**; GAME/AUD consume via approved owner |
| `RagdollTransitionReceiptV1` | Instance, target state, SIM-02 Body/WorldEpoch, joint coverage, captured pose hash, accepted/rejected reason | Transition only at PHYS barriers and motor clearance |
| `AnimationErrorV1` | typed code, severity, fields, expected/actual revision, last safe pose, recoverability | No silent deform or success on corrupt/partial bytes |
| `AnimationCapabilitiesV1` | CPU/headless, platform, skinning tier, max joints/tracks/layers, IK, ragdoll, Web/SIMD/threads | Advertise measured support, not hypothetical Web parity |

## 2. Semantic operations, shared authoring kernel
1. `StageSkeletonOrClip(source, expected_revision, principal)` → DATA-03 validation and typed draft receipt, DATA-04 journaling/CAS. No raw disk write from MCP.
2. `StageAnimationGraph(graph, expected_revision, principal)` → validate DAG/guard/event schema; commit separately to DATA-04, not live overwrite.
3. `StageRetargetProfile(profile, source_skeleton_hash, target_skeleton_hash, principal)` → bounded map validation and version pin.
4. `AttachAnimation(entity, graph_id, skeleton_id, world_epoch, principal)` → generation-scoped handle created by WORLD pre-tick barrier; graph+clip revisions pinned.
5. `SubmitGraphParameters(handle, tick, sequence, values, principal)` → queue idempotent changes; unsafe overrides and unauthenticated writes rejected.
6. `EvaluateAnimationTick(world, tick)` → engine-internal bounded graph/clip marker/root sampling; requests `RootMotionIntent` and consumes SIM-03 ack through published step protocol. Never a public direct-sim function.
7. `ReadPoseSnapshot(handle, confirmed_tick, max_joints)` → immutable, privacy/authority filtered pose and explicit incomplete state.
8. `ReadAnimationEventReceipts(world, cursor, max_events)` → bounded authorized marker receipts with dropped-event/completeness flags.
9. `RequestRagdollTransition(handle, target_state, expected_phys_epoch, principal)` → staged PHYS request; return accepted/rejected result only after SIM-02 confirms.
10. `StageGraphHotReload(handle, new_revision)` → safe swap at tick barrier, preserve or invalidate state explicitly, cancel stale jobs.
11. `DetachAnimation(handle, expected_epoch)` → deferred retirement after pose jobs/GFX reads end; invalidate generation.

## 3. Error catalog
`INVALID_SCHEMA`, `NONFINITE_VALUE`, `UNSUPPORTED_CODEC`, `MISSING_ASSET`, `BAD_ASSET_SIGNATURE`, `ASSET_RIGHTS_UNKNOWN`, `SKELETON_CYCLE`, `JOINT_MAP_MISMATCH`, `GRAPH_CYCLE`, `KEY_TIME_INVALID`, `BUDGET_EXCEEDED`, `SOURCE_REVISION_CONFLICT`, `STALE_WORLD_EPOCH`, `STALE_HANDLE_GENERATION`, `WRONG_TICK`, `UNAUTHORIZED_PRODUCER`, `UNREADY_COLLIDER`, `RAGDOLL_UNSUPPORTED`, `PHYSICS_TRANSITION_REJECTED`, `PARTIAL_STREAM`, `DEVICE_LOST_VISUAL_ONLY`.

## 4. Invariants and semantics
- Pre-physics animation **only requests motion**; post-physics pose/IK follows acknowledged collision and origin epoch. Partial/killed clip/stream prevents authoritative new markers/movement; may display clearly marked last-safe pose.
- Source assets never include executable code; allowed graph node set is finite and versioned. Editor/CLI/MCP all use identical permissioned `Stage*` kernel, no arbitrary JSON-pointer write.
- Memory is bounded: joints, tracks, clips, nested graphs, decompressed sizes, transition count, IK iterations, marker events, graph cycles, runtime concurrency and GPU palette uploads have declared limits per capability tier. Limits not selected numerically until profile testing.
- Ragdoll cannot mutate SIM-02 bodies during callback or publish PHYS success from animation state alone; state machine and recovery require receipts.
- Animation and audio marker order follows CORE-04 TickId; AUDIO sample timing remains AUDIO owner. TWO-03 stays 2D/timeline owner.
- Formats: this is a draft contract. C++ symbols/layout, wire serialization, migration format, signed ABI, FFI and platform profiles require later approved implementation WO and source/schema test vectors.
