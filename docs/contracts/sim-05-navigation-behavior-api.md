# SIM-05 — Semantic Navigation, Path, Steering, Behavior and Perception Contracts v0.1

**WO NLE-P00-WO-002-SIM-05 | Research #186 | Code #50 OPEN/BLOCKED**. A proposed semantic schema only, **NOT** a compiled/stable C++ ABI or published serialization contract.

## Types and ownership
| Type | Fields (proposal) | Validation / authority |
|---|---|---|
| NavWorldHandleV1 | ProjectId, WorldId, WorldEpoch, NavTopologyEpoch, generation, coordinate basis | reject foreign/stale worlds and stale origin revisions |
| NavTileSourceV1 | CellId, NavTileId, source geometry/collider revisions, bounds, agent clearance, build profile hash, checksum and legal provenance | DATA-03/05 cooked source and WORLD-03/PHYS readiness, bounded valid vertices/poly connectivity |
| NavTopologySnapshotV1 | NavWorldEpoch, tile cover set, source revision map, seam signatures and completeness status, lease/expiry | read-only pinned tile collection, UNKNOWN if nonresident/seam incomplete |
| NavAgentHandleV1 | EntityGuid/slot generation, world/nav epoch, SIM-03 MotorHandle link, profile revision | no duplicate or dead agent reference, dimension/units coherent |
| NavAgentProfileV1 | dimension, radius/height/clearance, slope, allowed area/link flags, speed, acceleration, steering and query quotas | finite nonnegative costs and dimensions; physics/motor capability checked |
| NavPathRequestV1 | NavAgentHandle, start/goal, Project/World epoch, start tick, expected topology, filter/area costs, maxVisited, timeout/cancel token, priority and source actor | bounded, authorized, origin epoch checked, no negative/NaN cost or unbounded search |
| NavPathReceiptV1 | request id, status COMPLETE/PARTIAL/PENDING/FAILED, ordered waypoint/corridor, tile revisions, remaining estimates and missing coverage, progress and expiry | deterministic observed completeness semantics, no unstated reachable claim |
| OffMeshLinkV1 | link id, source/dest tile epoch, capability/action type, traversal cost, owner permission, current availability | GAME/SIM-03 validates jump/drop/door traversal; no teleport by nav |
| SteeringProposalV1 | navAgent, TickId, preferred/avoidance velocity, bounded speed/turn, close-neighbor count, obstruction/replan reason | finite suggestion only; SIM-03 motor authoritative |
| NavMovementAckV1 | MotorMotionReceipt source TickId and collision/body revision, requested/applied delta, status | consumers cannot rewrite SIM-03 committed state |
| BehaviorGraphV1 | GraphId/source hash/revision, finite allowlisted node/action types, typed ports, explicit transition loops/guard budget, graph version | DATA-04 revision, no arbitrary plugin/HTML/JS/native code execution |
| BehaviorInstanceHandleV1 | EntityGuid/generation, graph id/rev, blackboard version, authority epoch | actor scoped, stale invalidation, no privileged target override |
| BlackboardSnapshotV1 | typed key GUID, value/unit, visibility capability, source revision, TTL and update TickId | immutable per-tick read, redacted external inspection, no secrets/PII |
| PerceptionProfileV1 | FOV/radius/rays, faction filters, hearing event sources, confidence/suspicion, quotas, expiry | finite source and permission limits, no hidden client knowledge |
| PerceptionReceiptV1 | TickId, observer/target IDs, LOS VISIBLE/OCCLUDED/UNKNOWN, world coverage, collider revision, signal id, expiration | UNKNOWN for stale/unloaded sources; GAME/NET controls truth/publication |
| BehaviorActionIntentV1 | actor, tick, producer seq, decision node, MoveTo/Stop/LookAt/AbilityRequest, expected policy and parameters | finite allowlisted command; GAME/SIM-03 validates authority |
| NavCapabilitiesV1 | 2D grid/3D tiled, supported links, dynamic tile update/crowd, headless/Web features, max size and numeric profile | report tested capability only, not marketing guarantees |
| NavBehaviorErrorV1 | code, actor/world/tick/source epoch, rejected operation, redacted diagnostics and safe fallbacks | explicit failure, no silent success/motion |

## Operations / shared kernel
1. **StageNavAgentProfile / StageNavBuildProfile(profile, expectedRevision, actor)**: schema/permission/cost validation, DATA-04 CAS/journal, no direct live collider mutation.
2. **InspectNavTileCoverage(world, area, epoch, maxTiles)**: paginated WORLD-03 lease-aware read, COMPLETE/PARTIAL/UNKNOWN; never materialize unsafe unloaded geometry.
3. **StageNavTiles(world, tileManifests, expectedSourceRevisions)**: bounded future cook/stage via DATA-03/05, with PHYS collider readiness; no immediate publication.
4. **PublishNavTopologyAtBarrier(world, expectedEpoch, stagedTiles)**: internal WORLD/PHYS/CORE coordination only; atomic adjacency state or typed cancel.
5. **AttachNavAgent(entity, motor, profile, worldEpoch)**: scoped agent handle; validate SIM-03 motor generation.
6. **RequestPath(agent, query, tick, principal)**: asynchronous bounded query ID, pinned epoch and cancel, route receipts; final result revalidates topology/agent generation.
7. **ReadPathReceipt(queryId, maxWaypoints)**: page immutable, typed status and missing-coverage; no internal Detour pointers/poly refs.
8. **SubmitSteeringToMotor(agent, proposedVelocity, targetTick)**: authorized, after path freshness check; delegates accepted motion to SIM-03.
9. **StageBehaviorGraph / StageStatechart / StagePerceptionProfile(source, expectedRevision, actor)**: validated finite allowlist and DATA-04 CAS; shared Editor/CLI/MCP semantics.
10. **TickBehavior(world, tick)**: internal only; sample last committed WORLD/PHYS/perception, bounded graph evaluation and staged game/motor action intents, no arbitrary callback scripts.
11. **ReadPerceptionOrBlackboardSnapshot(agent, cursor, principal)**: role-redacted, paginated, quota-limited and UNKNOWN completeness when streaming.
12. **CancelPath / DetachNavAgent / DetachBehavior**: idempotent cancel, barrier-safe retire, invalidate generations and in-flight callbacks.

## Errors
INVALID_TOPOLOGY, TILE_CORRUPT, TILE_SOURCE_STALE, NAV_PENDING, NAV_UNAVAILABLE, PATH_PARTIAL, PATH_NOT_FOUND, PATH_SEARCH_BUDGET, PATH_CANCELLED, UNREADY_COLLIDER, INVALID_OFFMESH_LINK, INVALID_AGENT_DIMENSION, STEERING_BLOCKED, STALE_WORLD_EPOCH, STALE_NAV_EPOCH, STALE_AGENT_HANDLE, ORIGIN_EPOCH_MISMATCH, INVALID_COST, NONFINITE_VALUE, BEHAVIOR_GRAPH_INVALID, GRAPH_STEP_LIMIT, ASYNC_ACTION_EXPIRED, BLACKBOARD_TYPE_MISMATCH, PERCEPTION_INCOMPLETE, HIDDEN_INFORMATION, PERMISSION_DENIED, DUPLICATE_COMMAND_CONFLICT, RESOURCE_LIMIT, BACKEND_UNSUPPORTED, INTERNAL_FAILURE.

## Invariants
- A path receipt COMPLETE means **complete coverage in validated nav topology and profile** at stamped epoch, not guaranteed physical movement; SIM-03/PHYS receipt is sole movement success.
- Source/collider versions, origin epochs, World/Agent generations and Action Sequence make async completion self-validating. Stale path and incomplete LOS never upgraded to success.
- Stable canonical TickId from CORE-04, with bounded query/behavior tasks; UI/CLI/MCP accesses a single validated authoring kernel. Server chooses NET replication and GAME ability effects.
- Vendor APIs, file paths, native pointers and private blackboard fields never escape stable public schemas. Future migration and ABI are subject to approval.
