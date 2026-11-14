# SIM-07 — Vehicle/Flight Semantic API and Receipts v0.1

**RESEARCH #192 | WO NLE-P00-WO-002-SIM-07 | Future code issue #57 OPEN/BLOCKED.** Proposed semantic contract only; **NOT a compiled API, C++ ABI, shipping serialized layout, implemented algorithm or approved backend.**

## 1. Typed schemas, generations and authority
| Type | Minimum fields (proposed) | Validation / owner |
|---|---|---|
| `VehicleAssetV1` | Project/AssetId, revision, source rights, mass/CG/inertia tensor, hull/body profile, DriveDomain, seat/control and force model references, units/coordinate basis, LOD/FX/audio IDs | DATA-02/03/04 source and cook, stable AssetId and rights; finite mass/positive inertia, bounded descriptors |
| `VehicleHandleV1` | ProjectId/WorldId/WorldEpoch, EntityGuid/generation, vehicle slot/generation, physics BodyHandle/generation, OriginEpoch | WORLD/SIM-02 live entity and nonstale physics authority |
| `VehicleSeatHandleV1` | VehicleHandle, SeatGuid/revision, Occupant EntityGuid/generation, occupant/authority epoch and seat role | GAME policy and SIM-03 safe enter/exit agreement, one driver per seat |
| `VehicleControlProfileV1` | domain, normalized control channels and ranges, slew limits, assistance tier, steering/gear profiles and action policy | GAME-01 canonical remapped inputs, actor capability; no unsigned privileged channels |
| `VehicleControlIntentV1` | Vehicle+SeatHandle, ActorId, AuthorityEpoch, TickId, producer seq, expected profile/source revision, throttle/brake/steer/track ratios or aero surfaces/collective/cyclic, mode | only authorized GAME/NET producer, finite clamped values, idempotent duplicates, stale tick denied |
| `WheeledProfileV1` | wheel count, track/wheelbase, radius, spring/damper/soft limit, tire friction/slip curves, drivetrain/differential, mass/inertia and collision shape | nonzero positive dimensional units, bounded wheel count and lookup table, SIM-02 ground-contact revision |
| `TrackedProfileV1` | track left/right drive, road-wheel points, suspension/contact, track traction and differential steering, turret attachment source | validated independent track impulses; turret motor authority and weapons remain GAME/SIM-02 |
| `WatercraftProfileV1` | hull buoyancy sample points/volumes, displacement, density, drag, rudder and propulsion, wind/current coupling | WORLD-04/PHYS complete water sample with source epoch and physical volume units |
| `WingAeroProfileV1` | wing/surface semispan/chord/area, lift/drag/moment coefficient tables vs alpha/beta/mach, thrust, trim and stall policy | valid finite bounded monotonic axes/tables, required sampling limits, avoid unsupported certified behavior |
| `RotorcraftProfileV1` | rotor count/mount/axis/radius, spool and torque tables, collective/cyclic, tail/coaxial anti-torque, limits | nonfinite and invalid rotor geometry rejected, bound rpm/force and torque, no CFD promise |
| `TerrainContactReceiptV1` | Wheel/TrackContactId, TickId, BodyHandle, ColliderRevision/WorldEpoch, support normal/friction/material, current velocity and readiness | SIM-02 authoritative collision; WORLD-03 lease; no visual height guess |
| `WaterWeatherSampleV1` | WorldCellId, source/wave/weather revisions, TickId, water height/normal/velocity/density, wind vector, coverage/trust and OriginEpoch | WORLD-04/05 owner publishes authoritative complete samples, UNKNOWN if nonresident |
| `VehicleForcePlanV1` | VehicleHandle, TickId, origin/profile epoch, bounded per-contact force/moment impulses and constraint controls, model revision, expected PHYS state | **internal only**, submitted to SIM-02 at safe pre-step barrier, never direct ECS transform |
| `VehiclePhysicsAckV1` | SIM-02 post-step TickId/BodyHandle/WorldEpoch, accepted/partially applied/rejected plan, actual pose/velocity/contact and reasons | authoritative PHYS-only receipt; never inferred from input or graphics |
| `VehicleStateSnapshotV1` | Handle, TickId, BodyHandle pose/velocity, wheel/track telemetry, water/flight state, control mode, pose source epoch, completeness | immutable headless server output with NET-authorized fields/redaction |
| `VehicleEventReceiptV1` | TickId, event ID, producer seq, engine/gear/slip/water splash/rotor/landing flags, audio/FX request seed, source revision | bounded idempotent events, cosmetic dispatch to AUD/GFX owners |
| `VehicleNetworkStateV1` | server TickId, authority/seat/vehicle version, packed pose/velocity/control/gear state, backend fingerprint, snapshot cursor | NET-02/03/04 owns replication, rollback, compression, trust and visibility |
| `VehicleCapabilitiesV1` | domain/tier, native/Web, headless, network mode, max wheels/tracks/rotors, physics precision, explicit unsupported features | advertise measured actual support only |
| `VehicleErrorV1` | typed code, principal/vehicle/tick, expected/actual source epochs, last safe PHYS state, recoverability and redacted diagnostics | no success on dropped force or wrong owner |

## 2. Semantic operations through shared authoring and runtime owners
1. `StageVehicleAsset(profile, expectedSourceRevision, principal)` → DATA-03 source scan and DATA-04 CAS/journal validated authoring. Same Editor/CLI/MCP schema and permissions; no live actor forces.
2. `StageForceModel(profile, tableFingerprint, principal)` → bounded wheel/tire/water/wing/rotor source data validated and versioned. No untrusted JS/XML expression evaluator or native code execution.
3. `AttachVehicle(entity, BodyHandle, SourceRevision, WorldEpoch)` → SIM-02 body exists, WORLD entity live, physics/domain capabilities match, owner creates generation-scoped handle at fixed safe barrier.
4. `RequestEnterSeat(vehicle, seat, occupant, tick, actor)` → GAME permission and SIM-03 motor/vehicle occupancy/clearance stage, accepted/rejected receipt, no immediate player teleport.
5. `RequestExitSeat(vehicle, seat, desiredExitPose, tick, actor)` → SIM-03 clearance and collision-resident world check; fail without ejecting into nonresident/wall region.
6. `SubmitVehicleControls(vehicle, seat, tick, seq, actions, actor)` → GAME/NET-authorized idempotent normalized control intent, queued for correct future CORE-04 tick.
7. `EvaluateVehicleForcesAtTick(vehicle, tick)` → **internal** finite forces and constraint plan from pinned valid ground/water/wind source. No own integrator.
8. `StageForcePlanAtPhysicsBarrier(plan, expectedPhysEpoch)` → SIM-02 accepts/rejects and integrates once; returns physical acknowledgement after step.
9. `ReadVehicleState(handle, confirmedTick, principal)` → immutable PHYS-derived pose+telemetry and completeness, NET privacy/authority checked.
10. `ReadVehicleEvents(handle, cursor, maxRecords)` → page immutable event receipts for AUD/GFX; visual output never becomes force/damage authority.
11. `RequestVehicleModeSwitch(vehicle, newDomainOrAssistanceTier, expectedRevision, actor)` → allowlisted GAME authority, clearance/PHYS state compatibility, no instant unbounded force; gameplay-relevant mode requires NET acknowledgment.
12. `StageVehicleHotReload(vehicle, newProfileRevision)` → at safe pre-step barrier with cancellation/epoch migration and explicit state preserve/reject; changing inertia/BodyHandle requires SIM-02 approval.
13. `DetachVehicle(vehicle, expectedGeneration)` → deferred retire after PHYS/world/NET/GFX consumers finish, revoke seat and in-flight controls safely.
14. `SnapshotVehicle/RestoreVehicle` → server/replay source and solver fingerprint, tick and complete authority state with versioned error/migration, not arbitrary client snapshot overwrite.

## 3. Error catalog and invariants
`UNAUTHORIZED_DRIVER`, `SEAT_OCCUPIED`, `SEAT_CLEARANCE_DENIED`, `NO_ACTIVE_BODY`, `INVALID_VEHICLE_DOMAIN`, `UNSUPPORTED_FORCE_MODEL`, `INVALID_INPUT_RANGE`, `NONFINITE_COEFFICIENT`, `INVALID_MASS_INERTIA`, `TIRE_TABLE_OUT_OF_RANGE`, `GROUND_NOT_READY`, `WATER_SAMPLE_UNKNOWN`, `WIND_SOURCE_STALE`, `WRONG_TICK`, `STALE_WORLD_EPOCH`, `STALE_ORIGIN_EPOCH`, `STALE_BODY_HANDLE`, `STALE_SEAT_GENERATION`, `PROFILE_REVISION_MISMATCH`, `DUPLICATE_COMMAND_CONFLICT`, `FORCE_PLAN_REJECTED`, `PHYSICS_NOT_READY`, `NETWORK_AUTHORITY_MISMATCH`, `REPLAY_BACKEND_MISMATCH`, `RESOURCE_BUDGET`, `CAPABILITY_UNAVAILABLE`, `INTERNAL_FAILURE`.

- Exactly one SIM-02-authoritative integration of each physical body per tick; SIM-07 does not integrate position/rotation, only proposes validated force/constraints. No double JSBSim+SIM-02 integration.
- Seat/input/flight model commands are allowed only for authorized actor/gameplay principal. Duplicate identical tick/sequence returns idempotent receipt; conflicting replay rejected, so no duplicated acceleration or gear toggles.
- Missing/partial physics or ground/water source cannot claim valid tire or flotation support; conservative fail-closed or bounded loss-of-force profile must be explicit and replay-consistent. No visual wave/road mesh used as collision authority.
- NET sends only approved interest/authority state; a modified client cannot set server BodyHandle, impulse, fuel, current wind/aircraft state. Headless CPU and visual tiers must produce same server physics outcome within verified selected numeric profile.
- All field names and operations are conceptual. No C++ ABI/serialization bytes, schema sizes, random seed, QoS/retransmission policy or performance thresholds approved. Future work must freeze them under an accepted implementation Work Order with tests.
