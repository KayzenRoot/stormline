# SIM-02 — Reproducible 3D Collision/Scale/Memory/Headless Benchmark Protocol

**Research #177 | WO NLE-P00-WO-002-SIM-02 | ALL FUTURE / NOT EXECUTED.** Nothing here proves a 3D solver, engine FPS, cross-platform determinism or memory performance.

## Clean-room source-owned fixtures
1. **Freefall/rest/contact oracle**: original 3D spheres and boxes with controlled gravity/velocity, convex piles, ramps, friction, springs, inertia and torque. Compare analytic results where appropriate against measured iterative solver tolerance; separate numeric precision vs visual render interpolation and PhysicsWorld/ECS source.
2. **Static terrain/mesh/cave source**: WORLD-04 authored heightfield tile and separate cliff/cave triangle mesh, dynamic convex sphere/capsule, ragged mesh seams, origin rebases and streamed cells. Require matching collision source revisions and PHYS ACK prior to walking; reject illegal dynamic mesh-vs-static heightfield/mesh if chosen backend disallows.
3. **Constraints**: chains of fixed/distance/hinge/slider/cone-twist/6DOF primitives with finite damping/motor and difficult stacking. Quantify anchor drift, penetration jitter, iteration count, sleep status, memory, resize/destroy during active contact; actual ragdoll/controller/vehicle remains other owner modules.
4. **High-speed CCD and queries**: small bullet vs thin static wall, moving targets, fast sensors, casts along terrain and multi-layer filter matrix; independent brute-force geometric oracle for no false negatives on resident shapes, broadphase candidate refinement and stable sorted output under 1/2/8 workers. Jolt broadphase nondeterminism caveat requires test, not unverified guarantee.
5. **Headless scale and memory**: synthetic 100/1000/10000+ bodies (workload inputs NOT product-supported capacity), diverse collider types, static-dynamic layers, collision events, server no-GPU/suspended render, cell mass insertion/removal. Freeze OS/CPU/GPU absence, memory allocator/worker, contact event quotas. Measure p50/p95/p99 and worst CPU fixed tick, broad/narrow/constraints/CCD, world/shape bytes, peak arena, stream-to-PHYS-ready latency and fault recovery.
6. **Backend comparison**: exact same source scene and independent physics oracle, Jolt C++ MIT leading candidate vs PhysX CPU BSD-3 vs Rapier Rust Apache2/FFI vs Bullet zlib, all chosen features truly supported. Capture build complexity, license notices, native Windows/Linux x64/ARM64/macOS arm64, CPU WASM Web single-worker fallback, binary and initialization size, contact correctness, numeric and replay. PhysX CUDA GPU is optional Win/Linux only and **not portable baseline**.
7. **Determinism/snapshot/failure**: identical source+backend tag+build defines/precision and sorted command log, 1/2/8 workers, two compilers and CPU/OS versions; compare canonical full solver state and ordered event hashes. If rollback not supported, report explicit unsupported instead of restoring transforms alone. Inject malformed mesh/constraint, mid-step destroy, hostile import, stale world/CellEpoch, failed cook, source undo and memory OOM; verify no gameplay leaks.
8. **S3P optional PROVE-OR-DROP**: compare basic WORLD-03/PHYS pre-step publish barrier vs speculative staged collider publication on identical assets, ticks and memory budget; discard if p99/memory/complexity regress, missing collider or race.

## Evidence collection and stop
Freeze git BASE/HEAD, raw source SHA-256 only after implementation exists, exact vendor versions/licenses/SBOM, compiler/linker flags, CORE-03 allocator and CORE-06 fixed tick/substeps, shape source rights and hashes, WORLD-03 CellId/WorldEpoch, reproducible input command log and hardware/OS/browser descriptors. Record p50/p95/p99/max CPU tick, memory/allocator peak, active/sleeping bodies, constraint error, CCD miss/penetration, query correctness, contact event overflow and native/Web headless behavior; visual FPS unrelated to correctness. Actual DoD numeric target/hardware not yet approved. Fail unsafe memory/event/editor auth, stale collider, fabricated cross-platform golden or unknown HIGH/CRITICAL. **Today: ZERO experiments and ZERO performance observations**.

## Primary sources
- https://jrouwe.github.io/JoltPhysicsDocs/5.6.0/
- https://github.com/jrouwe/JoltPhysics/blob/master/Docs/Architecture.md
- https://nvidia-omniverse.github.io/PhysX/physx/latest/index.html
- https://rapier.rs/docs/user_guides/templates/determinism/
- https://github.com/bulletphysics/bullet3/blob/master/LICENSE.txt
