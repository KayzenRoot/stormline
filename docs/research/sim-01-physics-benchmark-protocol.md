# SIM-01 — Reproducible 2D Physics Stability, Replay and Native/Web Benchmark Protocol

**NLE-P00-WO-002-SIM-01 | Research #174 | ALL BENCHMARKS FUTURE / NOT EXECUTED.** This document is a method, not proof of physics, 60fps or cross-target deterministic engine.

## Independent synthetic fixtures
1. **Reference math and collisions:** original generated falling bodies of known dimensions, bounce/rest contact circles/boxes, sliding friction, 2D projected gravity, off-center impulses and angular motion. Independent discrete analytic checks when applicable, tolerance recorded because approximate iterative solvers are not analytical truth. Include static/dynamic/kinematic and sensor/non-sensor.
2. **Tilemap and platform:** source authored tile edge chains with ghost vertices, closed/open shapes, internal vertices, one-way platform gameplay case delegated SIM-03, moving kinematic floor and thin collision wall; TEST for phantom snagging, tunneling, stale collision between streamed cells and PHYS collision-ready ACK before player crosses.
3. **Stress and stacked stability:** 100/1000/10000+ synthetic bodies as scale input (NOT supported capacity claim), towers, piles, spawns/deletes during step, 10/100+ joints pendulum/cradle/motor/spring. Measure solver iteration/substep quality and penetration/jitter/sleep ratio, event pressure, CPU/memory, no NaN/tick runaway.
4. **CCD/queries:** bullets against thin static and moving dynamics, high-speed sensors crossed in one step, casts and overlap/ray queries with exact oracle, category/group filters, bounded pagination, mutation attempts during in-flight step and stale generation. Test real fast sensor fallback rather than assert CCD solves every pair.
5. **Determinism/rollback:** replay **same** frozen world/physics backend build, input command log at tick/substep fixed profile over workers 1/2/8; compare stable canonical state/event hashes across Win/Linux/macOS, Linux ARM64 and browser WASM; origin rebase and pause/resume. Then backend-supported full-state snapshots/restore with joints/contacts; never claim distinct backend hashes equal, and mark platform unsupported if numeric profile cannot be frozen.
6. **Owner integration:** WORLD-01 EntityGuid/effect lifecycle and TWO-01 interpolated view decouple, TWO-02 tile chain, WORLD-03 streamed collider insertion/removal at tick barrier, DATA-04 source save/undo, NET server auth, GAME next-tick contact reaction, dedicated headless without GUI/GPU and native OS/Web reduced profile. Inject malformed huge shape and queue/pool failures.

## Measurement contract
- Record Git BASE/HEAD SHA, raw source SHA-256 after coding, upstream backend exact release+notice/SBOM, ABI/build flags and CPU float/FMA/SIMD, OS/CPU+arch/browser/worker count, fixed dt/substeps, gravity/units/scale, collision tolerances, asset source hashes and rights, seed/command order, source and collision epoch.
- CPU tick p50/p95/p99 and worst max step; narrowphase/broadphase, joints, sleeping, CCD, step/event buffer phase and ECS publish separately; memory/bytes peak, shape/joint counts, false collision/query misses, stack jitter/pile height, penetration, energy within physically appropriate tolerance, source/collider latency at world stream cell edges. Hardware targets and numeric limits must be approved in Scope/DoD, not invented.
- Compare Box2D C17 MIT candidate vs Chipmunk MIT vs Rapier Rust Apache2 optional with identical input/oracle and feature intersection; adapter overhead, Web WASM bundle/cold load, memory and compilation CI, one/two/eight worker, 3.2 vs version-pinned determinism feature settings; no claims competitor superior before actual runs.
- All output statuses `PASS/FAIL/NOT_RUN` based on real executed reproducible logs and independent review, no false "physics world ready" after mere API docs. Fail if gameplay collider absent, AI/body movement based on render delta, input replay diverges under claimed identical profile, contact event use-after-free or resource budget exceeded without explicit receipt.
- This proposal has **zero performed experiments**; SLO owner thresholds (CPU, memory, penetration, CCD failure and replay hashes) and source file ABI are unapproved.

## References
- https://box2d.org/documentation/md_simulation.html
- https://box2d.org/documentation/md_questions.html
- https://box2d.org/documentation/group__chain.html
- https://rapier.rs/docs/
- https://github.com/slembcke/Chipmunk2D
