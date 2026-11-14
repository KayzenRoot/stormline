# SIM-03 — Character Controller & Movement Architecture

**Research WO:** NLE-P00-WO-002-SIM-03 | **Research #180** | **Future code #48 OPEN/BLOCKED**  
**BASE main:** `c8ee0cd07ab30cd207f7ea9b7aedfe06b09b3d64` | **STATE: PROPOSED, DOCS ONLY**  
**Risk:** LOW research; future ELEVATED due to physics contact, replay, numeric precision and authority. No engine runtime, editor, physical backend, replay verification, benchmark or deploy.

## 1. Mission and non-negotiable invariants
Design a **Stormline-owned motor**, not a Jolt/Box2D adapter exposed as the public API, for 2D platformers, 2.5D games, top-down ARPGs, 3D third-person and first-person controllers. Responsive locomotion comes from a deterministic tick-indexed *intent → constrained desired motion → physics query/contact → canonical movement result* pipeline. Physics remains authoritative for collision; presentation never drives the physics tick. The motor may operate headlessly, in Editor preview, or through authorized gameplay/AI, with a single command schema.

Never claim perfect or superior gameplay feel without player testing. Numerical reproducibility is scoped to pinned numeric profiles/builds; cross-OS bitwise identical replay is NOT established.

## 2. Ownership matrix
| Owner | Supplies | SIM-03 must NOT own |
|---|---|---|
| CORE-04 | fixed monotonic simulation time, integer tick and pause/step concepts | independent frame-timing loop or new clock |
| CORE-05 | validated global/local transforms, units, coordinates, origin epoch | second global coordinate system |
| CORE-02/03/06 | allocators and memory budgets (CORE-02), jobs (CORE-03), logs/tracing/profiling (CORE-06) | independent allocator, scheduler, unbounded event log or logging core |
| SIM-01 | 2D collision world, shape casts, bodies, contact snapshots and collision filters | another 2D physics solver |
| SIM-02 | 3D shape casts, body/constraint state, safe pre/post-step barriers | another 3D solver or bypass of collision readiness |
| WORLD-01/02 | ECS generations, prefab identity, scene source, revision and component lifecycle | separate entity registry or scene store |
| WORLD-03/TWO-02/WORLD-04 | streamed cells, tile collision and ground-ready source revision | cell streamer or assumption nonresident terrain is safe |
| GAME/PLAT | authorized player/AI input mapping, actions, game rules and movement authoring | keyboard/gamepad polling, combat abilities or input devices |
| SIM-04 | animation graph, root-motion extraction, retargeting and ragdoll transitions | animation graph or skeletal evaluator |
| NET | prediction/reconciliation, replication and anti-cheat authority | multiplayer netcode or cross-client lockstep promises |
| GFX-07/TWO-01 | camera and presentation interpolation | camera renderer, camera shake/postprocess |
| DATA-02/04 | source IDs/rights, typed profile persist, undo/redo and journaling | direct file writes or unversioned config |
| EDIT/CLI/MCP | validated authoring surfaces via shared command kernel | privileged arbitrary runtime force/teleport from MCP |

## 3. Core movement model and state
- `CharacterMotorProfileV1`: immutable authored profile with `MotorMode=KINEMATIC_QUERY` default and optional `DYNAMIC_ASSISTED` where backend proven; `Dimension=2D|3D`, collision shape asset reference, mass/skin, ground slope cosine/angle, step height, snap-to-ground distance, max slides and iterations, velocity/acceleration/braking/gravity/jump parameters, air control, surface behavior, collision layers and caps. All quantities use typed SI units, finite bounds and versioned semantics. No hardcoded game genre.
- `CharacterMotorHandleV1`: project/world/epoch + slot/generation; not a native physics ID, raw pointer, or durable EntityGuid. A motor may bind a qualified WORLD-01 entity and body/query capsule, but must reject stale handles.
- `CharacterIntentV1`: TickId, producer/permission, authority epoch, monotonically increasing per-producer sequence, desired planar move vector, jump/stop/crouch/dash requests as policy-backed action flags, desired view/orientation control, source profile revision, optional animation root-motion delta *request*, and expected motor generation. No wall-clock timestamp controls physics.
- `CharacterMotorStateV1`: current fixed-tick position/velocity, rotation, support/ground reference with generation/source revision, grounded/slope/wall/ceiling classification, movement state, platform-relative velocity, jump grace counters in integer ticks, collision contact set, world/origin epoch, last confirmed tick and numeric/backend profile, health/errors.
- An authoritative `MotorMotionReceiptV1` includes applied intent sequence/tick, desired vs actual delta, collisions and blocking normals, grounded/support classification, consumed actions, simulation completeness (COMPLETE | COLLIDER_PENDING | PARTIAL | FAILED), source revisions and a bounded set of deterministic post-step events. Never publish a successful ground state from a missing/nonresident collider.

## 4. Fixed-tick pipeline
```text
GAME/AI authorized input for tick N
→ validate epoch, source revision, profile and quotas
→ stable order and consume one intent per actor per tick (policy on duplicates/missing)
→ SIM-03 motor desired acceleration/velocity/gravity/action policy
→ SIM-01/02 bounded shapecast/overlap, only against PHYS-ready source
→ slide/step/snap/ground classification, max substeps/iteration budget
→ publish read-only MotorState and post-tick events to WORLD-01
→ GAME/NET consume immutable receipts; SIM-04 consumes permitted motion cues
→ GFX/TWO interpolate previous/current confirmed states only
```

No mutating ECS/physics from collision callback; all world shape changes are deferred to agreed safe barriers. A moving platform's translation/angular motion is sampled from authoritative tick state, including support attachment, detach and platform deletion. A dynamic character is a distinct opt-in profile: rigid body authority and direct force/impulse routing via SIM-01/02, not a kinematic write into a dynamic solver body.

## 5. High-quality movement features
1. **Ground detection:** feet/shape sweep and contact normal classified against explicit up vector and slope threshold; no single center ray, ambiguous wall-as-floor, or camera-derived up.
2. **Step-up/down:** overlap clearance → bounded vertical clearance → forward sweep → downward grounding, failing closed on ceiling or unsupported terrain. Ground snapping disabled on upward jump. Handle descending ledges and microsteps without unsafe penetration.
3. **Walls, corners and sliding:** apply bounded iterative motion projection along contact tangents with terminal overlap/skin correction; corner trapping must not cause unbounded solver recursion.
4. **Jump buffering/coyote time:** integer tick windows, consumed at most once by policy, no double jump unless explicit GAME policy. Jump apex, gravity multipliers, early release and dashes are profile policies with independent tests, not mandatory combat mechanics.
5. **Moving platforms:** carry linear/angular displacement coherently from prior confirmed platform state, preserve world velocity on detachment according to versioned policy; reject retired support and cross-world handles.
6. **Crouch/stand:** collision shape resize at safe barrier only after clearance sweep and contact reclassification; no teleport through geometry or automatic desync of visuals.
7. **Top-down ARPG:** planar movement aligned to authored world/aim orientation, optional click-to-move target request from GAME path authority; pathfinding belongs SIM-05. Stop distance and path blocked explicit.
8. **2D and 2.5D:** true 2D physics plane and its 2D controller; 2.5D visual depth does not silently enable 3D collisions. Explicit dimension conversion is approved scene data, not a per-frame guess.
9. **Camera decoupling:** GAME can map aim/camera-relative input to world movement intent via typed transforms, but renderer latency and postprocessing do not alter collision results.
10. **Presentation:** motion smoothing/extrapolation budgets apply only to images; no authoritative clipping fix via visual-only position.

## 6. Numerical, streaming and multiplayer boundaries
- Distance, speed, acceleration and gravity have finite caps; sensor, sweep, overlap and solver iteration quotas are per-tick/per-character, with a deterministic failure/partial result rather than ignored collisions.
- Signed global world coordinates and local solver frame tracked through WORLD-03 origin epochs. A mid-tick rebase is prohibited; publication requires PHYS and scene-epoch agreement.
- Streamed ground not yet acknowledged by SIM-01/02 returns `COLLIDER_PENDING`; actor holds last-good safe position/uses configured safe stop, never falls through invisible authoritative terrain by default.
- Replay includes profile/hash, input order, world collider revision/hash, platform motions, physics backend+build/numeric profile, origin epochs and fixed tick count. Snapshots alone are not rollback evidence; complete solver state and NET policy separately required.
- A multiplayer-client controlled character never authorizes itself as server source truth; NET defines ownership and divergence handling.
- Screen-space 2D, rendered 2.5D and 3D controllers share semantic action names but separate physical dimension/ground tests. Cross-backend exact trajectories NOT promised.

## 7. Security, failure handling and verification
Validate every profile, handle, numeric input, serialized action and source permission. Reject NaN/Inf, zero/negative capsule radius, excessive step/snap, mass, speed, acceleration, gravity, deeply nested impulses, repeated unauthorized teleport, event buffer overflow and extremely expensive sweep loops. Avoid use-after-free on platform/shape swap and parent ref changes; isolate tenant/project/world boundaries in CLI/MCP; no raw scripting or physics handle injection from remote actor. Export only bounded, redacted receipts. Offline authoring writes use DATA-04 compare-and-swap transaction and journal, not direct backend memory.

Proof obligations: headless CPU golden 2D+3D motion with independent analytic baseline, fixed-step invariant across presentation FPS 24/30/60/120/240, collider revision under streaming, moving platforms/crouch/high speed, origin rebase, ID generation, step limits, rollback caveats, security fuzz, CPU tick p50/p95/p99 and memory, Windows/Linux/macOS native and Web/WASM availability by supported backend. No evidence has been run. See [API](../contracts/sim-03-character-motor-api.md), [ADR](../adr/0033-sim-03-authoritative-character-motor-policy.md), [test plan](../testing/sim-03-acceptance-matrix.md), [benchmark](../research/sim-03-character-motion-benchmark-protocol.md).
