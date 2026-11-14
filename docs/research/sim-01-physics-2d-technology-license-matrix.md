# SIM-01 — Physics 2D Solver/Backend Technology, License and Portability Matrix

**Research #174 | NLE-P00-WO-002-SIM-01 | ADR-0031 PROPOSED.** This is a licensing and backend evaluation, NOT a selected/installed physics SDK, integrated binary, executable contact solver, test result or benchmark.

| Candidate | Status / integration cost | Core capability and risk | Licensing / evidence gate |
|---|---|---|---|
| **Box2D 3.x** 3.2.0 docs (C17) | **LEADING CANDIDATE**, not adopted. Engine-owned opaque handles and C ABI bridge | robust 2D bodies, CCD, contact event batches, joints, chain shape, casts, multithread support; 3.1+ upstream claims cross-platform determinism with same precision/input; CPU C/C++/WASM actual release profile needed | **MIT** upstream LICENSE, pin tag/commit and transitive notices; ABI and cross-platform golden/stack p99 before approval |
| Chipmunk2D 7 (C99) | IMPORTANT fallback/comparison; requires adapter to unified Stormline command/events | rigid bodies/sensors/constraints/sleeping, broadphase spatial hash/tree, alternative contact callback model; different lifecycle and deterministic guarantees unproven | **MIT** official upstream; pin exact tag and test event semantics, WASM and rollback needs |
| Rapier2D Rust | IMPORTANT alternative and native/WASM comparator; FFI and Rust toolchain/bundle overhead | CCD, collision, sensors, snapshots and optional enhanced deterministic build; cross-target standard compliance and SIMD feature flags to pin; gameplay commands cannot assume backend parity | **Apache-2.0** per Rapier official docs, Rust crates/transitive licenses additional; pin exact crates/build and license/SBOM |
| Homegrown rigid-body engine from scratch | FUTURE hypothesis, not initial default | maximum control but high collision, CCD, manifold, joints and stability/safety burden with redundant years of code | own implementation cannot be said tested; explicit need/evidence before replacing vendor |
| SIMD/multithread solver | OPTIONAL backend capability | potential throughput but precision and event ordering issues; deterministic replay test required | backend compiler flags/CPU profile pinned, golden replay on 1/2/8 worker |
| Fixed-step 1/60 s and ~4 solver substeps | candidate **numeric initial baseline**, CORE-06 owns clock | stability vs CPU p99 and high-speed penetration tradeoffs; numbers unapproved 1.0 DoD | Box2D current documented recommendation, do not claim 60 FPS engine |
| Rigid bodies (static/kinematic/dynamic), convex primitive shapes, joints, sensors/filter | NECESSARY API contracts | stable handles, strict transform units, events poststep, safe contact and owned ECS snapshots | choose only intersection of pinned backend capabilities or typed unsupported |
| Dynamic AABB tree (physics broadphase) | NECESSARY solver-owned metadata | physics contact candidates, should not replace WORLD-03 streaming spatial query or GFX culling | Box2D exposes standalone dynamic tree but Stormline API separate and no duplicate physics tree |
| Continuous collision detection (CCD) for bullet candidates | IMPORTANT baseline; TOI requires proof | mitigates tunneling, not guaranteed for fast moving sensors or all dynamic pairs | Box2D docs warn sensor fast-moving caveats; cast fallback |
| Chains with ghost vertices for tiles | IMPORTANT TWO-02 integration | fewer internal corners, but chain winding/ghost points and connectivity tricky, invalid polygons/concavity unsafe | validate shape data, crack and ghost-ground collision tests |
| Deterministic replay and snapshot rollback | IMPORTANT conditional future NET/game | vendor determinism is scoped by same input/profile; backend state snapshot may not include every solver contact cache; commands/event ordering owner-defined | no cross-platform bitwise guarantee until actual golden replay + snapshot tests |
| Full deformable/soft body, rope solver, fluid, cloth, fractures | FUTURE/OUT OF SCOPE SIM-01 | overlap with SIM-04/GFX GAME and specialized solvers; no free feature assumption | additional ABI, source rights/performance review |
| Third-party physics visual demos/assets | OUT OF SCOPE P00 | media may have independent copyright or generated code | no screenshot/model/texture/benchmark result copied |

## Rights and technical cautions
- Box2D upstream **MIT** and docs current 3.2.0 (2026-11); C17, multithread and 3.1+ cross-platform deterministic claim **does not prove Stormline's engine-wide deterministic replay**, especially callbacks, simulation command order, varying float precision/FMA, tick settings and entity source. Box2D docs explicitly use post-step events to reduce callback races.
- Chipmunk2D upstream README and docs explicitly **MIT**, C99, contact callback APIs differ; unverified cross-CPU deterministic claims **must not be inferred**. Chipmunk source may be actively maintained or different branches; exact version/support/ARM/Web build needed.
- Rapier2D official site says **Apache-2.0** and optional cross-platform determinism and Rust/JavaScript/C integrations; documentation of `enhanced-determinism` and SIMD incompatibilities varies by crate version, pin direct+transitive package rights and compile flags if selected. Do not mistakenly label Rapier as necessarily MIT/Apache dual without pinned manifest.
- Web WASM is possible but SDK support, binary size, memory and browser event determinism not established by vendor marketing. Separate harness with same C API and vector/deterministic profile.
- 2D mass density/collider scale, sensor event opt-in, chain ghost vertices, sleeping/CCD and contacts are **precise feature/API version constraints**, not user-visible guarantees in docs phase. Box2D supports multiple worlds and standalone collision queries, but Stormline must validate lifecycle/identity and cross-world isolation.
- No backend adopted, no third-party source copied, no compiler flags pinned, no engine/game assets created, no physical simulation or stress result observed. Owner approval after actual code prerequisites, tests, license/SBOM, explicit rollback and numeric p95/p99 memory budgets.

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
