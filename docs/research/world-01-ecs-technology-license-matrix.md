# WORLD-01 — ECS Technology, Data-Layout, Reflection and Licensing Decision Matrix

**Research issue #159 | WO NLE-P00-WO-002-WORLD-01 | PROPOSED ONLY.** No library, compiler fork, binary or sample art installed/adopted. Compare by exact workload, code provenance and platform proof before selection.

| Candidate | Role / scope | Tradeoff and portability | Rights / license | Required future evidence |
|---|---|---|---|---|
| Original World/EntityGuid/GenerationalHandle & safe ECS semantic API | NECESSARY | native+Web/headless and module-independent; more development effort | original; license of Stormline engine still UNDECIDED | ABA, generation exhaustion, save/reload liveness |
| Archetype/chunked SoA layout | IMPORTANT primary candidate | fast hot multi-component iteration, expensive structural moves/archetype proliferation | implementation undecided, no direct Flecs structs | mixed game query vs structural churn, memory |
| Sparse-set per-component storage | IMPORTANT alternate/fallback | frequent add/remove/random entity lookup, may be worse for hot joins | original or EnTT-adapter rights separately | high churn, cache locality and query costs |
| Per-component hybrid TABLE_DENSE / SPARSE_STABLE | OPTIONAL design candidate | two storage paths increase maintenance and migration risk | own type schema, optional after benchmark | complexity/p99+memory vs single layout |
| Flecs ECS v4.1 C/C++ | OPTIONAL library/reference | modern archetype/SoA, cached queries, 64-bit entity ID and relationships, defer stages, native+browser claims; exact pin/build unverified | **MIT** upstream LICENSE, retain notice and dependency SBOM | actual Win/Linux/macOS/Web builds and public API isolation |
| EnTT C++ ECS registry | OPTIONAL library/reference | header-only sparse set, versioned/recycled entity IDs and views, component pools, C++ footprint; version/ABI/thread rules to pin | EnTT **MIT candidate**; verify exact selected LICENSE and third-party files before bundling | compaction/ref invalidation/generation limits+MSVC/Clang/Emscripten |
| Bevy ECS Rust | REFERENCE ONLY, optional FFI candidate later | Archetype/Tables vs SparseSet tradeoffs, change detection and jobs, Rust build+FFI adds complexity | `bevy_ecs` **MIT OR Apache-2.0** in upstream Cargo.toml, exact transitive cargo licenses TBD | no mandatory Rust toolchain without measured win |
| Unity Entities 1.x structural ECB/sync points | REFERENCE ONLY | field-proven buffered structural changes design, Unity/IL2CPP not Stormline runtime | Unity proprietary editor/runtime terms, code/art not copied | independently designed command buffer, no brand/tool lock-in |
| C++20/23 source-generated reflection | NECESSARY baseline candidate | stable cross-compiler type IDs/field schema, code generation needs robust build | own codegen and build scripts, no arbitrary plugin | build reproducibility and schema migration |
| C++26 static reflection P2996R13 | OPTIONAL FUTURE | incorporated in C++26 working draft, compiler feature rollout uncertain; no mandate on Web/desktop initial toolchain | ISO WG21 public paper, implementation/compiler redistribution independent | supported stable compilers on target platforms, no fork requirement |
| Per-world stable GUID and ephemeral generational slot | NECESSARY | extra resolve map/cost, prevents stale cross-world handles and persisted slot leaks | original typed IDs; DATA-02 authority | destroy/recreate, remount, duplicate import |
| Deterministic buffered structural changes + borrowing | NECESSARY | sync barrier, command conflict resolution, query epoch invalidation; scheduler CORE-owned | original semantic plan, no Unity code | exact tick/cmd conflict/replay and no data race |
| Reflection/metadata Editor/CLI/MCP interface | NECESSARY contract | user permissions, fields and source revision, no C++ address leakage | DATA-04/EDIT ownership; no arbitrary script eval | restricted edit/serialization/least privilege |
| STLG temporal lifetime guard | OPTIONAL PROVE-OR-DROP | metadata storage/CPU and false positives | original research hypothesis, not proven novel | catches stale query/async reference with cost justification |

## Legal, security and maturity caveats
- Flecs official MIT and docs state cached archetype queries/relationships plus defer/stages and portable C99/C++17; these claims are vendor descriptions **not a verified Stormline throughput/target compatibility measurement**. Its default entity id packing and world ID semantics may not match ours; do not expose `flecs::entity` in public SDK or persist it as a stable Guid.
- EnTT official ECS reference describes sparse-set components and versioned handles; candidate MIT must be reconfirmed against precise pinned upstream LICENSE before any code vendoring. Engine must explicitly protect generation wrap and cross-world ABA even if upstream IDs appear valid locally.
- Bevy ECS current docs document table insertion/removal slower vs sparse but fast iteration tradeoff; Rust ECS is useful as design comparison but introducing Rust FFI into a C++ engine needs an independent cost/security decision. `MIT OR Apache-2.0` option is scoped to `bevy_ecs`, not automatically every crate/media asset.
- Unity Entities own docs describe archetype structural change sync points and EntityCommandBuffers; proprietary Unity source and asset files are not to be copied into Stormline. Use independent semantics and tests.
- ISO WG21 accepted C++26 P2996R13 static reflection into working draft in June 2025; availability and consistent library/compiler ABI on target OS/Web are a **future feature probe**, not proof that a product's 2026 shipping compiler supports all proposals. Portable source-generated reflection remains baseline.
- Benchmark must capture allocator, page size/cache, compiler, schema changes, thread count/job barriers, query shapes and scene/entity count. No “Flecs fastest”/“EnTT millions”/“C++26 mandatory” commitments from documentation.
- Component content can contain personal/privileged fields and AI tools may obtain metadata; require allowlist and per-project access, no arbitrary host pointers, untrusted schemas or direct memory snapshot export. License notices/NOTICE/SBOM and security advisories per exact release before integrating.

## Sources: official primary references only (research, NOT integrated)
- Flecs v4.1 ECS archetypes, queries/relationships: https://www.flecs.dev/flecs/Queries.html
- Flecs command defer/readonly stage boundary: https://www.flecs.dev/flecs/group__commands.html
- Flecs MIT upstream license: https://github.com/SanderMertens/flecs/blob/master/LICENSE
- EnTT ECS registry/sparse sets/version handles (upstream wiki): https://github.com/skypjack/entt/wiki/Entity-Component-System
- EnTT source license to verify exact pin: https://github.com/skypjack/entt/blob/main/LICENSE
- Bevy ECS tables vs sparse sets, change detection: https://docs.rs/bevy/latest/bevy/ecs/
- Bevy ECS MIT OR Apache-2.0 license and Rust ABI/toolchain (reference only): https://github.com/bevyengine/bevy/blob/main/crates/bevy_ecs/Cargo.toml
- Unity Entities 1.3 structural change and sync point (proprietary design reference only): https://docs.unity.cn/Packages/com.unity.entities%401.3/manual/concepts-structural-changes.html
- WG21 C++26 reflection proposal P2996R13 accepted in working draft (compiler support remains a gate): https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/p2996r13.html
- WG21 reflection vote minutes 2025-06: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2025/n5016.pdf
