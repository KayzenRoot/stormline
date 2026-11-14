# SIM-07 — Acceptance Matrix: 144 FUTURE Tests, None Executed

**Research issue #192 | WO NLE-P00-WO-002-SIM-07 | Future implementation issue #57 OPEN/BLOCKED | DOCUMENTS ONLY.** The catalog proof is a drivable **original tank, truck and fixed-wing/rotorcraft reference test** with reproducible physics/network timing; it has **NOT been achieved**. Exactly **144** cases below are planned; zero have executable results, coverage, PASS/FAIL, screenshots or benchmark measurements.

## Future acceptance cases by category

| Test ID | Scenario | State |
|---|---|---|
| SIM07-SRC-01 | Accept original car/truck/tank/boat/aircraft/rotor profiles with manifest | FUTURE / NOT EXECUTED |
| SIM07-SRC-02 | Reject imported proprietary sample aircraft without rights declaration | FUTURE / NOT EXECUTED |
| SIM07-SRC-03 | Reject negative/nonfinite mass or invalid inertia tensor | FUTURE / NOT EXECUTED |
| SIM07-SRC-04 | Reject gigantic coefficient table or unbounded wheel/rotor count | FUTURE / NOT EXECUTED |
| SIM07-SRC-05 | Detect incompatible source model revision on hot reload | FUTURE / NOT EXECUTED |
| SIM07-SRC-06 | Stable AssetId and renamed authored profile mapping | FUTURE / NOT EXECUTED |
| SIM07-SRC-07 | Exact unit/basis conversions between model sources | FUTURE / NOT EXECUTED |
| SIM07-SRC-08 | Reject XML external entity, path traversal and executable profile | FUTURE / NOT EXECUTED |
| SIM07-CLK-01 | One control/force plan per vehicle per TickId | FUTURE / NOT EXECUTED |
| SIM07-CLK-02 | Repeat identical control sequence idempotent; contradictory duplicate rejected | FUTURE / NOT EXECUTED |
| SIM07-CLK-03 | Pause/single-step never accrues hidden throttle time | FUTURE / NOT EXECUTED |
| SIM07-CLK-04 | Fixed rational tick unchanged by 20/60/240 render FPS | FUTURE / NOT EXECUTED |
| SIM07-CLK-05 | Reorder async terrain sample responses without applying stale data | FUTURE / NOT EXECUTED |
| SIM07-CLK-06 | Replay includes physics backend/source profile fingerprint | FUTURE / NOT EXECUTED |
| SIM07-CLK-07 | Cross-worker event receipt order matches declared deterministic model | FUTURE / NOT EXECUTED |
| SIM07-CLK-08 | Cross-platform numeric deviations reported against declared tolerances | FUTURE / NOT EXECUTED |
| SIM07-GRD-01 | Four-wheel suspension query on source-revisioned flat ground | FUTURE / NOT EXECUTED |
| SIM07-GRD-02 | Wheel airborne loses load without false traction | FUTURE / NOT EXECUTED |
| SIM07-GRD-03 | Sloped bank/contact normal/curb profile behavior | FUTURE / NOT EXECUTED |
| SIM07-GRD-04 | Moving platform support velocity and revision validation | FUTURE / NOT EXECUTED |
| SIM07-GRD-05 | Reject missing collider or unloaded road as valid grip | FUTURE / NOT EXECUTED |
| SIM07-GRD-06 | Body/ColliderRevision change cancels old wheel ray query | FUTURE / NOT EXECUTED |
| SIM07-GRD-07 | Origin rebase preserves wheel-to-chassis contact coordinates | FUTURE / NOT EXECUTED |
| SIM07-GRD-08 | Static and dynamic physics obstacle contacts obey SIM-02 | FUTURE / NOT EXECUTED |
| SIM07-SUS-01 | Spring force changes correctly with compression under units | FUTURE / NOT EXECUTED |
| SIM07-SUS-02 | Damper compression and rebound have correct bounded sign | FUTURE / NOT EXECUTED |
| SIM07-SUS-03 | Suspension hard stop prevents impossible wheel force impulse | FUTURE / NOT EXECUTED |
| SIM07-SUS-04 | Antiroll optional model preserves contact authority | FUTURE / NOT EXECUTED |
| SIM07-SUS-05 | Saturated spring travel returns explicit status | FUTURE / NOT EXECUTED |
| SIM07-SUS-06 | Truck loaded CG and load transfer affects per-wheel contact | FUTURE / NOT EXECUTED |
| SIM07-SUS-07 | Asymmetric road and cornering checked against reference oracle | FUTURE / NOT EXECUTED |
| SIM07-SUS-08 | Suspension solver stable under low tick/high contact frequency | FUTURE / NOT EXECUTED |
| SIM07-TIR-01 | Tire longitudinal traction vs slip curve within finite range | FUTURE / NOT EXECUTED |
| SIM07-TIR-02 | Lateral force and steering input sign conventions | FUTURE / NOT EXECUTED |
| SIM07-TIR-03 | Wet/dry surface friction profile source revisions | FUTURE / NOT EXECUTED |
| SIM07-TIR-04 | Brake lock vs low speed no NaN or sign oscillation | FUTURE / NOT EXECUTED |
| SIM07-TIR-05 | Acceleration with differentials does not invent wheel energy | FUTURE / NOT EXECUTED |
| SIM07-TIR-06 | Tire contact on dynamic body respects SIM-02 impulse ownership | FUTURE / NOT EXECUTED |
| SIM07-TIR-07 | Cornering under high speed avoids unbounded lateral impulse | FUTURE / NOT EXECUTED |
| SIM07-TIR-08 | Simplified grip model labels limits versus high fidelity tire oracle | FUTURE / NOT EXECUTED |
| SIM07-DRV-01 | Torque/RPM curve and gear ratio drives correct wheel impulse | FUTURE / NOT EXECUTED |
| SIM07-DRV-02 | Shift command at correct tick with rate cap | FUTURE / NOT EXECUTED |
| SIM07-DRV-03 | Reverse/neutral/brake action authorization | FUTURE / NOT EXECUTED |
| SIM07-DRV-04 | Low rpm stall/spool respects model policy | FUTURE / NOT EXECUTED |
| SIM07-DRV-05 | Differential and per-wheel axle mapping stable | FUTURE / NOT EXECUTED |
| SIM07-DRV-06 | Fuel resource authority stays GAME while SIM-07 requests motor load | FUTURE / NOT EXECUTED |
| SIM07-DRV-07 | ABS/traction optional assist explicitly flagged and replayed | FUTURE / NOT EXECUTED |
| SIM07-DRV-08 | Malicious boost cannot exceed server power/torque cap | FUTURE / NOT EXECUTED |
| SIM07-TRK-01 | Left/right track speed and differential yaw on uniform plane | FUTURE / NOT EXECUTED |
| SIM07-TRK-02 | Counterrotating tracks execute bounded stationary turn | FUTURE / NOT EXECUTED |
| SIM07-TRK-03 | Unequal track friction on mixed surfaces | FUTURE / NOT EXECUTED |
| SIM07-TRK-04 | Multi-roadwheel suspension contact with PHYS source revision | FUTURE / NOT EXECUTED |
| SIM07-TRK-05 | Track damage/repair as GAME/SIM-06 authorized state not direct NET | FUTURE / NOT EXECUTED |
| SIM07-TRK-06 | Turret hinge position authority not weapon gameplay hit | FUTURE / NOT EXECUTED |
| SIM07-TRK-07 | Tracks under large impulse stay under chassis stability constraints | FUTURE / NOT EXECUTED |
| SIM07-TRK-08 | TrackedVehicleController vs Chrono reference uses same input fixture | FUTURE / NOT EXECUTED |
| SIM07-MAR-01 | Displaced hull volume yields expected hydrostatic buoyancy | FUTURE / NOT EXECUTED |
| SIM07-MAR-02 | Reject water density<=0 or negative volume | FUTURE / NOT EXECUTED |
| SIM07-MAR-03 | Half-submerged and fully submerged hull states | FUTURE / NOT EXECUTED |
| SIM07-MAR-04 | Water-source coverage missing does not claim floating support | FUTURE / NOT EXECUTED |
| SIM07-MAR-05 | Wind/current/reverse propeller create bounded moments | FUTURE / NOT EXECUTED |
| SIM07-MAR-06 | Wave phase/sample epoch consistent with CORE-04 tick | FUTURE / NOT EXECUTED |
| SIM07-MAR-07 | Roll/pitch stability with asymmetric buoyancy points | FUTURE / NOT EXECUTED |
| SIM07-MAR-08 | Simple boat mooring/shore contact remains SIM-02 authoritative | FUTURE / NOT EXECUTED |
| SIM07-AIR-01 | Straight and level trimmed flight reference at stated density | FUTURE / NOT EXECUTED |
| SIM07-AIR-02 | Lift/drag coefficient interpolation at valid alpha | FUTURE / NOT EXECUTED |
| SIM07-AIR-03 | Stall transition at beyond declared alpha without NaNs | FUTURE / NOT EXECUTED |
| SIM07-AIR-04 | Aileron/elevator/rudder control axes/torque signs | FUTURE / NOT EXECUTED |
| SIM07-AIR-05 | Wind gust and crosswind only from versioned world samples | FUTURE / NOT EXECUTED |
| SIM07-AIR-06 | Thrust/drag energy and velocity bounds on dive/climb | FUTURE / NOT EXECUTED |
| SIM07-AIR-07 | Landing gear/wheels share SIM-02 contact authority | FUTURE / NOT EXECUTED |
| SIM07-AIR-08 | Owned simple FDM vs standalone JSBSim reference no double integration | FUTURE / NOT EXECUTED |
| SIM07-ROT-01 | Rotor collective changes upward thrust at safe bounded RPM | FUTURE / NOT EXECUTED |
| SIM07-ROT-02 | Cyclic pitch/roll changes moment with correct sign | FUTURE / NOT EXECUTED |
| SIM07-ROT-03 | Yaw anti-torque tail rotor or coaxial profile validation | FUTURE / NOT EXECUTED |
| SIM07-ROT-04 | Rotor spool and shutdown avoid instantaneous infinite torque | FUTURE / NOT EXECUTED |
| SIM07-ROT-05 | Forward translational lift optional profile vs hover | FUTURE / NOT EXECUTED |
| SIM07-ROT-06 | Ground effect only if PHYS/WORLD valid support revision | FUTURE / NOT EXECUTED |
| SIM07-ROT-07 | Autorotation unsupported tier returns explicit capability not invented | FUTURE / NOT EXECUTED |
| SIM07-ROT-08 | Helicopter landing under contact and engine failure bounded | FUTURE / NOT EXECUTED |
| SIM07-CTL-01 | Remap keyboard/gamepad/touch to same normalized control intent | FUTURE / NOT EXECUTED |
| SIM07-CTL-02 | Clamp nonfinite and out-of-range throttle/steering | FUTURE / NOT EXECUTED |
| SIM07-CTL-03 | GAME validates driver seat and actor role | FUTURE / NOT EXECUTED |
| SIM07-CTL-04 | Tick and per-channel slew rate with no frame-time dependence | FUTURE / NOT EXECUTED |
| SIM07-CTL-05 | Mutually exclusive steer/track channels validated by mode | FUTURE / NOT EXECUTED |
| SIM07-CTL-06 | Pause/focus loss neutralization policy explicit and replayed | FUTURE / NOT EXECUTED |
| SIM07-CTL-07 | AI pilot path submits authorized control not raw BodyHandle | FUTURE / NOT EXECUTED |
| SIM07-CTL-08 | Emergency disable/unseat reset cannot alter server physics directly | FUTURE / NOT EXECUTED |
| SIM07-SEAT-01 | Board when parked with occupant collider clearance | FUTURE / NOT EXECUTED |
| SIM07-SEAT-02 | Reject two drivers claiming one seat concurrently | FUTURE / NOT EXECUTED |
| SIM07-SEAT-03 | Exit on cliff/in unloaded cell safely denied | FUTURE / NOT EXECUTED |
| SIM07-SEAT-04 | Detach motor and attach seating coordinated with SIM-03 | FUTURE / NOT EXECUTED |
| SIM07-SEAT-05 | Vehicle destruction during boarding cancels and recovers motor | FUTURE / NOT EXECUTED |
| SIM07-SEAT-06 | Seat role passenger cannot send privileged steering | FUTURE / NOT EXECUTED |
| SIM07-SEAT-07 | Camera follows PHYS snapshot without ECS teleport | FUTURE / NOT EXECUTED |
| SIM07-SEAT-08 | Origin rebase and hot reload preserve occupant generation | FUTURE / NOT EXECUTED |
| SIM07-PHY-01 | One SIM-02 integration per body per TickId | FUTURE / NOT EXECUTED |
| SIM07-PHY-02 | Reject untrusted direct transform/velocity force setting | FUTURE / NOT EXECUTED |
| SIM07-PHY-03 | Jolt adapter body/constraint generation checked | FUTURE / NOT EXECUTED |
| SIM07-PHY-04 | Reject force plan after body destroyed/unloaded | FUTURE / NOT EXECUTED |
| SIM07-PHY-05 | Mass/inertia matrix valid, finite torque clamps enforced | FUTURE / NOT EXECUTED |
| SIM07-PHY-06 | SIM-02 poststep ACK source exactly matches applied forces | FUTURE / NOT EXECUTED |
| SIM07-PHY-07 | No second Chrono/JSBSim step on same BodyHandle | FUTURE / NOT EXECUTED |
| SIM07-PHY-08 | Collision/recovery and sleep/wake under body retire safe | FUTURE / NOT EXECUTED |
| SIM07-WLD-01 | WORLD-03 terrain cell unload invalidates grip safely | FUTURE / NOT EXECUTED |
| SIM07-WLD-02 | WORLD-04 water sample source supports boat buoyancy complete status | FUTURE / NOT EXECUTED |
| SIM07-WLD-03 | Wind/temperature/weather sample epoch stamp validated | FUTURE / NOT EXECUTED |
| SIM07-WLD-04 | Bridge destruction SIM-06 changes support before vehicle path response | FUTURE / NOT EXECUTED |
| SIM07-WLD-05 | Cross-cell terrain and origin rebase remain consistent | FUTURE / NOT EXECUTED |
| SIM07-WLD-06 | No ground from GFX-only visual LOD or wave vertex height | FUTURE / NOT EXECUTED |
| SIM07-WLD-07 | Vehicle parked over streamed cell keeps required physics lease | FUTURE / NOT EXECUTED |
| SIM07-WLD-08 | Missing water/weather data returns safe incomplete not fabricated value | FUTURE / NOT EXECUTED |
| SIM07-NET-01 | Forged client throttle/force request rejected | FUTURE / NOT EXECUTED |
| SIM07-NET-02 | Passenger can't drive after seat authority epoch changes | FUTURE / NOT EXECUTED |
| SIM07-NET-03 | Duplicate/reordered packet commands idempotent | FUTURE / NOT EXECUTED |
| SIM07-NET-04 | 100ms delay/jitter/loss fixture server trajectory corrections | FUTURE / NOT EXECUTED |
| SIM07-NET-05 | Client prediction uses snapshot profile and quantization schema | FUTURE / NOT EXECUTED |
| SIM07-NET-06 | Rollback mismatch reports physics/terrain/backend hash | FUTURE / NOT EXECUTED |
| SIM07-NET-07 | Interest pruning never removes server-authoritative moving vehicle | FUTURE / NOT EXECUTED |
| SIM07-NET-08 | Reconnect restores server seat/vehicle source state not client override | FUTURE / NOT EXECUTED |
| SIM07-FX-01 | Engine RPM/gear change emits AUD event only after acknowledged state | FUTURE / NOT EXECUTED |
| SIM07-FX-02 | Tire slip/spray/tracks emit GFX-08 visual effect without collision | FUTURE / NOT EXECUTED |
| SIM07-FX-03 | Rotor blur and wheel mesh motion nonauthoritative | FUTURE / NOT EXECUTED |
| SIM07-FX-04 | Boat wake/GFX wave doesn't affect server water physics | FUTURE / NOT EXECUTED |
| SIM07-FX-05 | Device loss/restoring renderer preserves headless state | FUTURE / NOT EXECUTED |
| SIM07-FX-06 | Server runs with no GPU or audio device | FUTURE / NOT EXECUTED |
| SIM07-FX-07 | GFX LOD reduces draw only, no damage or physics differences | FUTURE / NOT EXECUTED |
| SIM07-FX-08 | Visual interpolation renders no new authoritative vehicle ticks | FUTURE / NOT EXECUTED |
| SIM07-SEC-01 | Fuzz wheel/tire/flight curve parser with bounded count | FUTURE / NOT EXECUTED |
| SIM07-SEC-02 | Reject malformed aircraft XML/XXE and dangerous paths | FUTURE / NOT EXECUTED |
| SIM07-SEC-03 | ASan/UBSan stale physics pointer/handle future test | FUTURE / NOT EXECUTED |
| SIM07-SEC-04 | TSan simultaneous detach and pending force job future test | FUTURE / NOT EXECUTED |
| SIM07-SEC-05 | Reject malicious MCP arbitrary live force/body mutation | FUTURE / NOT EXECUTED |
| SIM07-SEC-06 | Rate-limit 10k control packets/sec attack and log denial | FUTURE / NOT EXECUTED |
| SIM07-SEC-07 | Recover incomplete authoring CAS after crash or migration | FUTURE / NOT EXECUTED |
| SIM07-SEC-08 | License and provenance audit on sample vehicle/test data | FUTURE / NOT EXECUTED |
| SIM07-BEN-01 | Vehicle single-car CPU p50/p95/p99 per fixed tick | FUTURE / NOT EXECUTED |
| SIM07-BEN-02 | 100 wheeled and 20 tracked NPC vehicles crowd CPU | FUTURE / NOT EXECUTED |
| SIM07-BEN-03 | 10 boats with dynamic wave source and streaming | FUTURE / NOT EXECUTED |
| SIM07-BEN-04 | 10 airplanes and 10 rotorcraft headless 6DoF latency | FUTURE / NOT EXECUTED |
| SIM07-BEN-05 | Win/Linux/macOS x64/ARM build and numerical tolerance | FUTURE / NOT EXECUTED |
| SIM07-BEN-06 | Web/WASM scalar SIMD/threads fallback and memory cap | FUTURE / NOT EXECUTED |
| SIM07-BEN-07 | Original road/boat/flight human playtest versus model oracle | FUTURE / NOT EXECUTED |
| SIM07-BEN-08 | One hour stress heap/contact/NET correction and frame stability | FUTURE / NOT EXECUTED |

## Future proof obligations and test tiers
1. **Unit:** profile/schema, fixed rational TickId, force-sign/origin/units, finite coefficient interpolation, wheel/suspension/track/buoyancy/aero/rotor force plans, input authority and idempotency.
2. **Integration:** SIM-02 real PHYS Body/ColliderEpoch; SIM-03 seat occupant motor; GAME-01 remap/role; NET-02/03/04 authoritative input/snapshot/rollback; WORLD-03/04 ground/water/wind source; GFX/AUD optional receipts and headless server.
3. **Security/reliability:** untrusted vehicle/aircraft source fuzz, XML hostile fixtures, illegal force injection, stale body/world/seat generations, Physics-ACK races, ASan/UBSan/TSan, rate limits, recovery/rollback from crash and hot-reload.
4. **Headless/native/Web:** exact source and toolchain fingerprint, compiler numeric profile and deterministic input order, runtime and memory under Win/Linux/macOS ARM/x64 and optional WASM scalar/SIMD/threads. No false "cross-OS bitwise replay" guarantee; choose acceptable state tolerances when supported.
5. **Quality and benchmark:** original legal car/tank/boat/aircraft/rotorcraft assets and prescribed test courses, human driver rubric, physics oracles and reference trajectories, CPU p50/p95/p99, heap, worker contention, rollback/NET correction and GPU/AUD presentation independence.

**NOT RUN** means no current CI runtime pass, no code, no game scene, no real vehicle or network. Docs Validation can approve the documentation only. Numerically bounded budgets must be frozen from measured hardware baselines in future code WOs; do not label tests passed simply because described.
