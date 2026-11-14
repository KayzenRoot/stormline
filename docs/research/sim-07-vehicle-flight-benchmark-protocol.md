# SIM-07 — Vehicle, Marine, Aircraft & Rotor Flight Reproducible Benchmark Protocol

**Date:** 2026-11-14 | Research #192 | WO NLE-P00-WO-002-SIM-07 | **STATUS: FUTURE ONLY; ZERO TESTS, ORIGINAL ASSETS OR MEASUREMENTS.**

## Benchmark questions
Can a single owner SIM-02 fixed-tick physics state robustly host ground/wheel/track, water-buoyancy, wing/rotor force models without violating contact truth, server authority or numerical stability? What quality and cost for suspension, tire slip, drivetrain, boat flotation, wing trim/stall and rotor control, each vs independent reference or analytic oracle? Can frame FPS, network packet loss/jitter and world streaming change while server trajectory/receipts remain bounded within approved tolerances? Which feature tiers maximize visual/audio polish while preserving physical truth?

## Original future fixture suite (not built or distributed)
- **VEH-ROAD-H1:** original 3.5-ton class truck and passenger car, wheelbase/CG/spring-damper/torque curves and standardized road slope, curb, wet/slick/rough contact materials. These illustrative dimensions/weights are **fixture choices only**, NOT production default or exact real brand models. Valid tire/road analytic tests.
- **VEH-TRACK-H1:** original tracked vehicle chassis, 6-12 roadwheel contacts candidate, left/right independent drive controls, soft/hard terrain and ramp, turret game-control stub, no real weapons or proprietary tank models.
- **VEH-MAR-H1:** original small displacement boat hull with volume sample grid, waves/currents, shoreline and dock colliders; water density and source revision controlled; righting/stability and propulsion reference.
- **VEH-FIX-H1:** original generic high-wing fixed-wing model with authored legitimate CL/CD/CM tables, mass/inertia/CG, lift/drag, landing gear, power/thrust, wind and crosswind landing; a standalone JSBSim reference only if provenance and LGPL evaluation permit.
- **VEH-ROT-H1:** original generic single-rotor/tail-rotor rotorcraft with bounded actuator disc, spool/anti-torque, hover/translation/yaw/ground contact. No claim of certified real-world helicopter behavior.
- **VEH-NET-H1:** 2, 8, 16 and 32 client controlled vehicle sessions (counts are test proposals) under loss, jitter, latency, reconnect, out-of-order inputs and rollback, with one trusted headless server and deterministic route.
- **VEH-WORLD-H1:** original 4-km streaming road/bridge/water corridor with origin rebase and SIM-06 bridge damage; source/collider/water/wind epochs and vehicle body safe support.
- **VEH-X1:** hostile profiles/oversized aero tables, stale seat/world/BodyHandle, spoofed client controls, extreme/high RPM, negative mass, nonfinite airfoil coefficient and canceled physics jobs.
- **VEH-2D:** original low-speed 2D/2.5D car/boat analog with explicitly separate dynamics profile and no assumption of 3D flight support.

Every fixture future original source and redistribution/rights manifest, content hash, asset/code/physics backend version, numerical unit profile, weather seed, identical test trajectory and approved reference oracle. No real vehicle game/sample content copied from proprietary engines, OEM databases or commercial aircraft models.

## Workloads and measurements
| Domain | Proposed workload | Required signals |
|---|---|---|
| Ground baseline | single truck/car and 100 active cars, flat/grade/offroad, 30/60/120 Hz fixed tick candidates | p50/p95/p99 CPU/tick per vehicle, wheel-ray contact, tire slip, chassis impulses, energy, memory and peak body/constraint cost |
| Tracked | tank 1 and 20, tracks turning/braking on mixed wet/dry/contact patches | yaw/turn-radius vs oracle, slip/traction residuals, contact count and solver iteration cost |
| Marine | 1 and 10 boats with variable water/wave/currents | buoyancy error vs displaced volume, righting moment, roll/pitch stability, water sample readiness and CPU |
| Fixed-wing | 1 and 10 aircraft including stall, trim, crosswind, takeoff and landing | 6DoF state, CL/CD/CM coefficient validation, energy drift, control signs, ground contact, source version and p99 |
| Rotorcraft | 1 and 10 helicopters with hover, lateral translation, spool/shutdown and yaw | lift/RPM/anti-torque envelope, unstable oscillation, stall fallback and CPU p99 |
| Streaming | vehicles traverse 4-km terrain/water and a dynamically removed bridge | source/epoch correctness, no false support, load/lease cancellation, frame/tick stalls |
| Server NET | 2/8/16/32 clients RTT 0/40/100/200ms, loss 0/1/5% and jitter with scripted control | accepted source TickId, client/server trajectory error, correction sizes, late commands, bandwidth and cheat rejection |
| Portability | native Win/Linux/macOS x64/ARM, optional WASM scalar/SIMD/threads | actual build/run, bitwise or numeric tolerance **only if verified**, memory, safety and support matrix |
| Visual presentation | near/far wheel/tread/rotor/boat spray, AUD engine RPM sync, device loss | CPU/GPU/VRAM separate, no physics state change due to graphics/sound tier |
| Endurance | 60-minute attach/detach, driving/streaming, hot reload and seat transfers | memory leaks, stale handles, UAF/TSan, host timing violations and missed receipts |

## Reference/oracle methods
- Tire/friction units vs independent analytic calculations and SIM-02 contact poststep; drivetrain torque balance, suspension spring-damper work/energy and CG/load transfer. Compare Chrono outside engine only on matched definitions; not simultaneous solver.
- Buoyancy `F = rho*g*V_displaced`, torque about CG, wind/current/drag component signs; require actual submerged **volume** rather than visually estimated water triangles.
- Fixed wing `q = 0.5*rho*v^2`, `L=q*S*CL`, `D=q*S*CD`, moment coefficients and Earth reference from declared atmosphere. Distinguish g-load/g-vector from model yaw/pitch/roll in CODE trace; JSBSim can be a separately-run comparison but has own solver and LGPL requirements.
- Simplified rotor thrust/moment must be force-bounded and trim/hover tolerance grounded in measured original model, not falsely equivalent to a certified blade-element simulation.
- NET: match physics backend/step/seed/quantization/latency/jitter and source revisions. Record all dropped/corrected inputs, maximum and percentiles of divergence; never compare single best run.

## Execution and evidence policy
No p95/p99 threshold, maximum wheel/boat/flight agents, safety envelope, flight accuracy, physics tick rate, acceptable bandwidth or GPU budget approved today. First future implement **NECESSARY** car vertical slice, collect actual baseline and set hardware/tier thresholds through audited ADR/DoD. Include exact SHA, original fixture hashes/licensing, compiler/ISA, thermals, CPU/GPU/driver OS, seeds, fixture input command log, captured source+PHYS receipts, repeat count and confidence intervals, failure samples, ASan/TSan/fuzz and rollback plan. Match quality and hardware if comparing commercial engines; **no unmeasured superiority or aviation safety claim**. All results in this P00 remain **NOT EXECUTED**.
