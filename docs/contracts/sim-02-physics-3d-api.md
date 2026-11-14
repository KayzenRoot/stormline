# SIM-02 — Typed 3D Physics World, Shape, Constraint, Event and Query API v0.1

**Research #177 | NLE-P00-WO-002-SIM-02 | Coding #47 OPEN/BLOCKED.** Semantic proposal only, NOT a C++/Rust/C binary ABI or real interpreter/editor/backend.

| Proposed versioned type | Fields / semantics | Owner and invariant |
|---|---|---|
| `PhysicsWorld3DIdV1` | ProjectId, ECS WorldId, PhysicsWorldEpoch, PhysicsBackendProfileId, physics-unit/axes profile, revision | multiple worlds and epochs isolated; SIM-01 2D separate |
| `PhysicsBody3DHandleV1` | WorldEpoch, slot+generation, optional WORLD-01 EntityGuid, source asset revision | no external native solver ID, reject stale/foreign-world |
| `PhysicsShape3DHandleV1` | body+slot+generation, source ShapeAssetId/hash, child index and cook revision | owner body lifetime, collision geometry source rights |
| `PhysicsConstraint3DHandleV1` | world+slot+generation, two body handles, type, source constraint revision | reject stale endpoints, retire before body destroy |
| `PhysicsWorld3DSettingsV1` | gravity vector, fixed tick, substeps, solver iterations, job budget, scale/coordinate handedness, sleep/CCD and profile | CORE fixed time and CORE-05 units, owner-approved numeric thresholds TBD |
| `PhysicsBody3DDefV1` | static/dynamic/kinematic, world/local transform, mass/density/inertia, gravity factor, damping/friction, sleep/CCD flags | source DATA-04 vs runtime authoritative pose, finite ranges |
| `PhysicsShape3DDefV1` | sphere/box/capsule/convex/compound/static triangle mesh/static heightfield, source rights/AssetId and cook hints | static mesh/heightfield default, dynamic concave rejected unless audited backend |
| `PhysicsColliderCook3DV1` | GeometryAssetId, vertex/triangle/height sample hash, collider scale, voxel/triangle/winding metadata and DATA-05 cook version | validated DATA-03 assets, stale source revision disallowed |
| `PhysicsLayerFilter3DV1` | collision category/mask/broadphase layer, group policy, sensor flag, contact event opt-in | exact/symmetric policy, independent from renderer layers |
| `PhysicsConstraint3DDefV1` | fixed/distance/hinge/slider/cone_twist/6dof, anchors, axes, limits, motor/impulse/damping and break capability | actual pinned backend supports or typed UNSUPPORTED |
| `PhysicsCommand3DV1` | CommandId, expected WorldEpoch+Tick, target generation, source revision, GAME/NET authority and typed action | stable pre-step sort, never mutate from callback |
| `PhysicsStep3DV1` | fixed tick, backend/config hash, source scene epoch, ordered commands and CPU budget | CORE-06 owns tick, no render delta/GPU need |
| `PhysicsBodyState3DV1` | body handle + EntityGuid, position/quaternion/velocities, sleep/activity and origin epoch | snapshot poststep, GFX render interp read-only |
| `PhysicsContact3DEventV1` | WorldEpoch+tick, pair handles/gens, begin/persist/end, normals/impulses/shape child data, validity epoch | immutable buffered poststep, no reentrant mutation |
| `PhysicsQuery3DV1` | ray/overlap/sphere_cast/box_cast/capsule_cast/convex_cast, origin/extent, source frame, filters, max results | broadphase candidate then exact narrowphase, stable optional sort |
| `PhysicsQuery3DReceiptV1` | hit IDs/normal/distance/fraction, source epoch/snapshot completeness/residency, total+truncated | cannot report nonresident terrain COMPLETE |
| `PhysicsColliderStage3DV1` | CellId, global origin epoch, ShapeSourceRevision/cook hash, action STAGE/RETIRE, pins and owner receipts | WORLD-03 stage, DATA-05 cook, PRE_STEP PHYS ACK before active |
| `PhysicsOriginShift3DV1` | old/new origin, global/local mapping, CORE epoch, owner ack and barrier tick | global source persists intact |
| `PhysicsSimulationSnapshot3DV1` | backend/tag/build numeric profile, source+cook hash, complete body+constraint/contact/sleep/island warm-start state or explicit unsupported | transforms alone no rollback, handles remapped/invalidated |
| `Physics3DPerfReceiptV1` | measured/estimated/unknown, CPU tick p50/p95/p99 and max, broad/narrow/constraints/CCD/job, body counts/bytes and mempeak | never fabricate native/Web performance |
| `Physics3DSourceTransactionV1` | DATA-04 expected source CAS, shape/joint authored config, impacted cell/physics bodies, undo journal/rights | editor/CLI/MCP cannot directly mutate server runtime |

## Future semantic operations
`CreatePhysicsWorld3D`, `Stage/CreateBody3D`, `Stage/CreateShape3D`, `Stage/CreateConstraint3D`, `ApplyForce/Impulse/Torque3D`, `SetKinematicTarget3D`, `QueueBodyTeleport3D`, `SetLayerFilter3D`, `DestroyBody/Shape/Constraint3D`, `StepFixed3DTick`, `DrainPostStep3DContactEvents`, `QueryPhysics3D`, `StageCookedCollider3D`, `AckColliderCellReady3D`, `ShiftPhysics3DOriginAtBarrier`, `Capture/RestoreCompletePhysics3DSnapshot` (optional feature gated), `InspectPhysics3DPerformance`. All ProjectId/WorldEpoch/permissions/quotas typed. Editor/CLI/MCP may `Inspect/PreviewPhysicsShape3D`, `Stage/Validate/Commit/UndoPhysicsSource3D` **via DATA-04 CAS**; unprivileged agents cannot inject authoritative GAME/NET physics impulses.

## Publication/safety pipeline (not executed)
`WORLD-02 scene+WORLD-04 terrain source author -> DATA-03 import validation/rights -> DATA-05 cook immutable shape SourceRevision -> WORLD-03 cell STAGED -> SIM-02 PRE_STEP shape commands -> CORE fixed step -> physics collider and contact data ACK -> WORLD-01 ECS consistent post-step snapshot -> WORLD-03 ACTIVE_COLLISION -> GFX render interpolation`. Persisted scene changes can be `SOURCE_COMMITTED_PHYSICS_PENDING` until sim ACK; retain last-good physics ground or explicit traversal barrier on failure. For unload, lease+pins+constraint refs must release at safe barrier; no freeing native shape while worker/contact in use.

## Error vocabulary / future constraints
`PHYS3D_WORLD_STALE`, `PHYS3D_FOREIGN_WORLD`, `PHYS3D_HANDLE_EXPIRED`, `PHYS3D_ENTITY_GUID_UNRESOLVED`, `PHYS3D_UNIT_MISMATCH`, `PHYS3D_NONFINITE_TRANSFORM`, `PHYS3D_COORD_PRECISION_LIMIT`, `PHYS3D_SHAPE_INVALID`, `PHYS3D_HULL_NONCONVEX`, `PHYS3D_TRIANGLE_INDEX_OOB`, `PHYS3D_DYNAMIC_MESH_UNSUPPORTED`, `PHYS3D_HEIGHTFIELD_STATIC_ONLY`, `PHYS3D_COLLIDER_SOURCE_UNAUTHORIZED`, `PHYS3D_ASSET_CRC_MISMATCH`, `PHYS3D_COLLIDER_REVISION_STALE`, `PHYS3D_CONSTRAINT_AXIS_INVALID`, `PHYS3D_CONSTRAINT_UNSUPPORTED`, `PHYS3D_FILTER_DENIED`, `PHYS3D_QUERY_INCOMPLETE`, `PHYS3D_QUERY_BUDGET`, `PHYS3D_EVENT_HANDLE_STALE`, `PHYS3D_EVENT_QUEUE_OVERFLOW`, `PHYS3D_IN_STEP_MUTATION_DENIED`, `PHYS3D_JOB_SHUTDOWN_PENDING`, `PHYS3D_RESOURCE_BUDGET`, `PHYS3D_COLLIDER_ACK_PENDING`, `PHYS3D_ORIGIN_SHIFT_ACK_PENDING`, `PHYS3D_CCD_LIMIT`, `PHYS3D_SNAPSHOT_UNSUPPORTED`, `PHYS3D_NUMERIC_DETERMINISM_UNVERIFIED`, `PHYS3D_GPU_BACKEND_NOT_PORTABLE`, `PHYS3D_CANCELLED`, `PHYS3D_RECOVERY_REQUIRED`. Structured diagnostics must redact private source paths and contain no backend pointer.

## Future activation requirements
Owner-approved 1.0 Scope/DoD and ADR-0032, code prerequisites WORLD-02+CORE-03 merged/audited, CORE time/coordinates/heap, WORLD-03/04 and DATA source contracts, pinned solver version/license/SBOM/compile flags, actual raw source SHA-256 and C++ ABI file inventory, native/headless/Web builds, independent collision/stability/fuzz/replay and memory p95/p99 tests and zero known HIGH/CRITICAL. NONE DONE NOW.

## Primary license and technical references (research only)
- Jolt MIT source/LICENSE: https://github.com/jrouwe/JoltPhysics/blob/master/LICENSE
- Jolt 5.6 docs archive and deterministic-simulation caveats: https://jrouwe.github.io/JoltPhysicsDocs/5.6.0/ and https://github.com/jrouwe/JoltPhysics/blob/master/Docs/Architecture.md
- NVIDIA Omniverse PhysX 5 BSD-3-Clause CPU source license: https://github.com/NVIDIA-Omniverse/PhysX/blob/main/LICENSE.md
- NVIDIA PhysX v5 official documentation and CPU/GPU distinctions: https://nvidia-omniverse.github.io/PhysX/physx/latest/index.html and https://nvidia-omniverse.github.io/PhysX/physx/5.4.0/docs/GPURigidBodies.html
- Rapier 3D Rust Apache-2.0 official overview: https://rapier.rs/docs/ and current crate feature contract: https://docs.rs/crate/rapier3d/latest/source/Cargo.toml
- Rapier deterministic mode and exact input prerequisites: https://rapier.rs/docs/user_guides/templates/determinism/
- Bullet Physics zlib source license, Extras/ThirdPartyLibs separate: https://github.com/bulletphysics/bullet3/blob/master/LICENSE.txt
