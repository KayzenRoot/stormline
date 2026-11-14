# SIM-01 — Typed Physics World, Body, Shape, Joint, Query and Event API v0.1

**Research #174 | NLE-P00-WO-002-SIM-01 | Coding issue #46 BLOCKED.** Semantic contract proposed only; no C++ implementation, backend adapter, ABI, engine physics or live Editor/MCP.

| Proposed type | Semantic fields | Owner/invariant |
|---|---|---|
| `PhysicsWorld2DIdV1` | ProjectId, WorldId/WorldInstanceEpoch, source schema rev, plane/physical scale and PhysicsProfileId | distinct from WORLD-01 ECS world or 3D sim, isolation and generation checked |
| `PhysicsBodyHandleV1` | world index/generation, slot+generation, optional EntityGuid link | opaque, never exposes Box2D/Chipmunk/Rapier internals or raw ptr |
| `PhysicsShapeHandleV1` | owned by body, shape slot/generation, ShapeAssetId and source rev | safe stale and cross-world rejection, multiple shapes per body |
| `PhysicsJointHandleV1` | world slot/gen, type and two body handles, config rev | reject body lifecycle mismatch, safe joint retirement |
| `PhysicsScaleV1` | meters-per-world-unit, TWO-01 pixel-to-meter conversion, handedness/Y and CORE origin epoch | render zoom/DPI cannot change gameplay |
| `PhysicsWorldSettingsV1` | fixed dt, solver substeps, gravity, sleep/CCD enablement, collision tolerances, numeric/solver backend profile | CORE-06 time ownership, rejected unapproved mutable dt at runtime |
| `PhysicsBodyDefV1` | STATIC/KINEMATIC/DYNAMIC, global/local pose, velocity, density/mass options, damping, gravity multiplier, allowSleep, bullet flag | source DATA-04, finite ranges, only accepted at tick barrier |
| `PhysicsShapeDefV1` | CIRCLE/CAPSULE/BOX/CONVEX/CHAIN, local pose, finite dims, material/density, sensor and filter | convex and chain winding/ghost validation, backend-supported shapes explicit |
| `PhysicsFilterV1` | category bits, mask bits, optional group index, sensor flag and event opt-in | physics not rendering layer; symmetric collision policy |
| `PhysicsJointDefV1` | joint type, anchors, limit/motor/spring parameters, collideConnected and break policy | backend feature gate; no generic fluid/3D constraints |
| `PhysicsCommandV1` | CommandId, WorldEpoch, ExpectedTick, body/shape/joint generational targets, source revision/authority, action and payload | queue and validate before step, idempotent replay; no mutation during callbacks |
| `PhysicsStepRequestV1` | TickId, fixed dt, substeps, expected profile and world epoch, ordered commands from CORE-06 | no variable rendering dt and no implicit pause/unpause |
| `PhysicsBodyStateV1` | body handle and ECS EntityGuid, position/rotation/velocity, sleeping, body type, epoch and tick | authoritative after full sim step only; render interpolation read-only |
| `PhysicsEventBatchV1` | TickId+WorldEpoch+EventGeneration, sorted begin/end/hit and sensor enter/exit with shape gen checked and impulses | poststep immutable, lifetime typed, may be delayed after filter/edit; no external callback mutation |
| `PhysicsQueryV1` | RAY/OVERLAP/SHAPE_CAST/POINT, local/global units, filter and bounded results/time/epoch | CPU solver broadphase oracle and exact shape refine, no fake unloaded world COMPLETE |
| `PhysicsQueryReceiptV1` | hit world/body/shape gen and fractions/normals/points, total/truncated and completeness snapshot tick | no raw contacts/pointers; reject stale world |
| `PhysicsSnapshotV1` | source world/revision, backend+version+numeric profile, complete solver state, hash, tick, remap schema | backend-specific, rollback optional and MUST prove exact replay |
| `PhysicsWorldOriginIntentV1` | old/new CORE-05 origin and epoch, owner ACK, safe step barrier | update physical local origin without rewriting EntityGuid/cell |
| `PhysicsColliderPublishReceiptV1` | TWO-02/World source CellId/ShapeAssetId revision and entity ACK after PHYS step | WORLD-03 streaming ready only when PHYS collider ACK exists |
| `PhysicsPerfReceiptV1` | tick CPU p50/p95/p99, broad/narrow/solve/CCD/joint/event phases, active/sleep bodies, bytes, measured/estimated/unknown | cannot claim benchmark PASS without hardware/toolchain evidence |

## Future semantic commands and lifecycle
CreateWorld/DestroyWorld, StageBody/CreateBody, StageShape/CreateShape, StageJoint/CreateJoint, ApplyForce/Impulse/Torque, SetKinematicTarget, SetFilter, EnableSensorEvents, TeleportAtTick, DestroyBody/Shape/Joint, SetWorldSettings (safe only), StepFixedTick, DrainPostStepEvents, QueryPhysics, CaptureStateSnapshot/RestoreSnapshot (FEATURE_GATED), ShiftPhysicsOriginAtBarrier, Pause/Resume via CORE clock, InspectCollisionDebug (read-only). All methods typed, bounded and source/role checked; no arbitrary host memory, GPU dispatch or private backend structs.

Proposed tick pipeline `DATA-04 authored collision source / WORLD-03 cell staging -> Validate generations/source/units/filter -> Queue stable ordered Commands -> CORE-06 fixed pre-step barrier -> SIM-01 backend Step -> immutable post-step BodyState+EventBatch -> WORLD-01 ECS publish -> PHYS ACK of collision readiness to WORLD-03 -> TWO-01 render interpolation/GAME next-step commands -> retirement only after event lease/fence`. Runtime physics is NOT atomic with source disk commit; include `SOURCE_COMMITTED_PHYSICS_PENDING` and coherent last-good + idempotent retry/rollback receipt.

## Guarantees / typed errors
`PHYS2D_WORLD_EPOCH_STALE`, `PHYS2D_HANDLE_STALE`, `PHYS2D_FOREIGN_WORLD`, `PHYS2D_ENTITY_UNLINKED`, `PHYS2D_BODY_TYPE_UNSUPPORTED`, `PHYS2D_SHAPE_UNSUPPORTED`, `PHYS2D_SHAPE_NONCONVEX`, `PHYS2D_SHAPE_DEGENERATE`, `PHYS2D_CHAIN_GHOST_INVALID`, `PHYS2D_SCALE_INVALID`, `PHYS2D_UNIT_MISMATCH`, `PHYS2D_NONFINITE_VALUE`, `PHYS2D_VELOCITY_LIMIT`, `PHYS2D_COLLIDER_RIGHTS_DENIED`, `PHYS2D_FILTER_INVALID`, `PHYS2D_JOINT_TARGET_INVALID`, `PHYS2D_JOINT_UNSUPPORTED`, `PHYS2D_STEP_IN_PROGRESS`, `PHYS2D_TICK_ORDER_INVALID`, `PHYS2D_COMMAND_STALE`, `PHYS2D_CCD_UNAVAILABLE`, `PHYS2D_CCD_LIMIT`, `PHYS2D_QUERY_LIMIT`, `PHYS2D_QUERY_INCOMPLETE`, `PHYS2D_EVENT_HANDLE_EXPIRED`, `PHYS2D_EVENT_QUEUE_LIMIT`, `PHYS2D_COLLIDER_ACK_PENDING`, `PHYS2D_WORLD_ORIGIN_ACK_PENDING`, `PHYS2D_SNAPSHOT_PROFILE_MISMATCH`, `PHYS2D_ROLLBACK_NOT_SUPPORTED`, `PHYS2D_NUMERIC_DETERMINISM_UNVERIFIED`, `PHYS2D_RESOURCE_BUDGET_UNSATISFIABLE`, `PHYS2D_CAPABILITY_DENIED`, `PHYS2D_SIM_NOT_ADVANCED`, `PHYS2D_RECOVERY_REQUIRED`. Safe diagnostics include world/tick/stable event id only; no raw pointer or private path.

## Editor, CLI, MCP parity (not implemented)
Readonly `InspectPhysicsWorld`, `InspectBodies`, `PreviewCollisionShape`, `InspectContactEvents`, `PreviewJointConstraint`, `QueryPhysics`, `GetPhysicsPerfReceipt`, `InspectPhysicsAssetRights`. Source edits `StagePhysicsConfigEdit`, `ValidatePhysicsConfigEdit`, `CommitPhysicsConfigEdit`, `UndoRedoPhysicsConfigEdit` via DATA-04 expected CAS with role/scoped project. Runtime physics body impulses/teleports are **GAME/NET authoritative** and cannot be injected by an editor/MCP viewer; headless server owns game commands.

## Future code freeze
Owner-approved Scope/1.0 DoD and ADR-0031, measured and vetted backend choice/license+SBOM with exact version/compile flags, WORLD-01+TWO-01 code integration, CORE clock/memory/math contract, DATA shape rights and WORLD-03 streaming, implementation file inventory/ABI, raw source byte SHA-256 fingerprints, native/Web/headless goldens, fuzz, CCD/joints/queries/stack stress and no known HIGH/CRITICAL. No test/performance proof now.

## Primary references (license and API must be pinned on actual implementation)
- Box2D 3.2.0 C17 manual and world/simulation/joint docs: https://box2d.org/documentation/index.html and https://box2d.org/documentation/md_simulation.html
- Box2D MIT LICENSE: https://github.com/erincatto/box2d/blob/main/LICENSE
- Box2D v3 migration events vs callbacks and deterministic hazards: https://box2d.org/documentation/md_migration.html
- Box2D FAQ version 3.1 cross-platform determinism, snapshot, CCD and tile chains: https://box2d.org/documentation/md_questions.html
- Chipmunk2D C99 official upstream MIT: https://github.com/slembcke/Chipmunk2D
- Rapier2D Rust official Apache 2.0 and opt-in cross-platform determinism: https://rapier.rs/docs/
- Rapier Rust/JS/C integration and WASM overview: https://rapier.rs/
- Box2D chain edge and ghost vertices constraints: https://box2d.org/documentation/group__chain.html
- Box2D sensor overlap event limitations: https://box2d.org/documentation/md_simulation.html
