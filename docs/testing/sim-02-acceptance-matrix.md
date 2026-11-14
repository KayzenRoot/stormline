# SIM-02 — Future 3D Physics Stability, Collider, Determinism and Security Matrix

**Research #177 | WO NLE-P00-WO-002-SIM-02 | future code #47 OPEN/BLOCKED.**  
**ALL 170 CASES ARE FUTURE / NOT EXECUTED.** Stormline has no 3D rigid-body engine, vendor SDK, native/Web/headless binary, body collider, benchmark or generated scene.

| Test ID | Future independent acceptance scenario | Proof surface |
|---|---|---|
| IDN-001 | 3D WorldId and PhysicsEpoch isolated from ECS and 2D physics | unit |
| IDN-002 | Body handle slot reuse increments generation and rejects stale handle | ASan |
| IDN-003 | Shape handle after body destruction cannot access freed SDK memory | ASan |
| IDN-004 | Constraint references both live bodies and retires safely | concurrency |
| IDN-005 | Foreign world handle for force or query rejected before solver | security |
| IDN-006 | EntityGuid remains stable after prefab reparent and physics rebuild | WORLD02 |
| IDN-007 | Multiple shapes per compound body retain source AssetId identity | unit |
| IDN-008 | Body removal during contact listener defers to post-step barrier | TSan |
| IDN-009 | Fast world unload and recreation does not resurrect old callbacks | fault |
| IDN-010 | No native Jolt/PhysX/Rapier/Bullet ID leaks public ABI | architecture |
| UNI-001 | World coordinate and physics gravity unit meter per second squared | CPU |
| UNI-002 | Quaternion normalization and sign-equivalence well-defined | CPU |
| UNI-003 | Physics transform handedness matches CORE05 approved axes | CPU |
| UNI-004 | Nonuniform negative scale re-cook or explicit reject | unit |
| UNI-005 | Camera zoom and HDR render changes cannot affect body pose | integration |
| UNI-006 | Large positive and negative global coordinates remain source stable | CPU |
| UNI-007 | Origin shift epoch realigns local physics island at safe tick | integration |
| UNI-008 | Origin shift during active solver step must be deferred | concurrency |
| UNI-009 | NaN Inf and overflow transforms rejected before native SDK call | fuzz |
| UNI-010 | Dynamic body pose poststep authoritative; GFX interpolation readonly | integration |
| SHP-001 | Sphere box capsule dimensions validated and finite | unit |
| SHP-002 | Convex hull points winding and coplanar degenerates denied | fuzz |
| SHP-003 | Convex hull volume positive and inertia tensor reasonable | oracle |
| SHP-004 | Compound shape maximum depth/count enforced before cook | security |
| SHP-005 | Tri mesh source indices bounded by vertex length | fuzz |
| SHP-006 | Static triangle mesh with holes yields correct ray contact | oracle |
| SHP-007 | Heightfield static-only shape linked to WORLD04 source revision | integration |
| SHP-008 | Dynamic triangle mesh against static heightfield unsupported Jolt mode rejected | unit |
| SHP-009 | Dynamic concave polygon soup requires source-approved convex decomposition | security |
| SHP-010 | Triangle normals orientation matches imported handedness | oracle |
| SHP-011 | Malformed mesh with NaN vertices yields typed import error | fuzz |
| SHP-012 | Negative nearzero scale and huge triangle count quotas enforced | security |
| SHP-013 | Sphere resting on convex ramp no false slope sticking | stress |
| SHP-014 | Convex corner contact normal orientation correct | oracle |
| SHP-015 | Cooked mesh hash invalidated after source geometry edit | DATA05 |
| SHP-016 | Shape source rights/license verified on archive import | security |
| BOD-001 | Static body unaffected by impulse and gravity | unit |
| BOD-002 | Dynamic box falls with finite gravity reference trajectory | oracle |
| BOD-003 | Kinematic platform moves only with approved fixed-tick target | unit |
| BOD-004 | Compounds mass center and inertia reflect child changes | unit |
| BOD-005 | Static and dynamic collision restitution bounded | oracle |
| BOD-006 | Friction contact sliding matches source material rule | oracle |
| BOD-007 | Sleeping body wakes on impact or command with event receipt | unit |
| BOD-008 | Body stack tower stability no NaN or nonbounded jitter | stress |
| BOD-009 | Pile 100 1000 10000 synthetic body counts no unexplained state loss | stress |
| BOD-010 | High velocity impulse can be bounded by owner budgets | stress |
| BOD-011 | Body created and destroyed at same tick maintains event epoch | unit |
| BOD-012 | Changing mass inertia during step deferred until barrier | concurrency |
| BOD-013 | Wrong actor cannot apply force to foreign authoritative body | NET |
| BOD-014 | Dynamic body cannot be duplicated across two WORLD03 cells | integration |
| BRD-001 | Static dynamic broadphase layers preserve filter membership | unit |
| BRD-002 | Broadphase candidates refined by exact narrowphase collider | oracle |
| BRD-003 | Ray cast exact sphere and box hit fraction normal | oracle |
| BRD-004 | Sphere/capsule/convex cast first hit matches independent oracle | oracle |
| BRD-005 | Broadphase query sorting by stable IDs when deterministic mode enabled | replay |
| BRD-006 | Concurrent AABB widening candidate order never treated as stable without refine | replay |
| BRD-007 | Queries on nonresident WORLD03 terrain return incomplete | integration |
| BRD-008 | Layer mask group and connected body flags symmetric as policy | property |
| BRD-009 | Sensor overlaps no solid contact impulse | unit |
| BRD-010 | Query result max hit memory/time budget and truncation reported | security |
| BRD-011 | Query during step uses approved snapshot or typed denied | concurrency |
| BRD-012 | Slow motion query and high velocity broadphase remain consistent | oracle |
| BRD-013 | No collision spatial index reuses WORLD03 streaming index incorrectly | architecture |
| BRD-014 | GFX04 occlusion and frustum never affect contact broadphase | architecture |
| CTK-001 | Contact begin persist end emitted after correct fixed tick | event |
| CTK-002 | Contact manifold normals and impulses finite and correct direction | oracle |
| CTK-003 | Sensor enter exit event coalesced and generation validated | event |
| CTK-004 | Contact event ordering by engine stable key not SDK callback order | replay |
| CTK-005 | Contact listener cannot mutate body or constraint during update | TSan |
| CTK-006 | Contact listener cannot run arbitrary editor script or path fetch | security |
| CTK-007 | Contact emitter after body destroy retains safe ID and expires | ASan |
| CTK-008 | Contact event queue overpressure returns typed backpressure | stress |
| CTK-009 | Multi-thread contact callbacks produce one deduplicated pair record | concurrency |
| CTK-010 | Contact disabled/filter changed event lifecycle predictable | event |
| CTK-011 | Audio/AI effects consume immutable post-step events | integration |
| CTK-012 | Physics event after world reload rejected on stale origin epoch | fault |
| CON-001 | Fixed constraint maintains relative anchors within tolerance | oracle |
| CON-002 | Distance constraint length stable under gravity and impact | oracle |
| CON-003 | Hinge constraint normalized axis and angular limit honored | oracle |
| CON-004 | Slider constraint max translation and motor force respected | oracle |
| CON-005 | Cone twist swing limits remain finite in extreme rotations | oracle |
| CON-006 | SixDOF supported only with pinned backend and typed fallback | contract |
| CON-007 | Constraint motor and spring damping unit conversions pinned | unit |
| CON-008 | Unsupported constraint returns precise type error no mutation | unit |
| CON-009 | Constraint chain pendulum stress stable across worker count | stress |
| CON-010 | Constraint with destroyed body releases references safely | ASan |
| CON-011 | Constraint update while simulation running deferred | concurrency |
| CON-012 | Nested ragdoll features not claimed by basic joint support | architecture |
| CCD-001 | Fast sphere against thin wall TOI collision bounded | CCD |
| CCD-002 | High speed convex against moving dynamic target tested | CCD |
| CCD-003 | Sweep of capsule against terrain triangle corner no tunneling within limits | CCD |
| CCD-004 | Two moving sensors fast pass not assumed guaranteed events | contract |
| CCD-005 | Gameplay high-speed trigger uses explicit shape cast fallback | CCD |
| CCD-006 | CCD disabled vs enabled performance cost documented | benchmark |
| CCD-007 | Extreme velocity invalid TOI yields bounded failure | fuzz |
| CCD-008 | CCD stage can never create NaN velocity | fuzz |
| TER-001 | Terrain source mesh and heightfield body source revision linked | WORLD04 |
| TER-002 | WORLD03 staged ground waits for physics collider ACK before traversable | integration |
| TER-003 | Late DATA05 collider cook from obsolete region does not publish | fault |
| TER-004 | Terrain cell unloading waits dynamic bodies and contact leases | integration |
| TER-005 | Dynamic entity crossing cells keeps one ECS/PHYS owner | integration |
| TER-006 | Terrain visual mesh LOD may change without altering collider revision | integration |
| TER-007 | Edited terrain height requires PHYS collision recook acknowledged | WORLD04 |
| TER-008 | Cave mesh and terrain seam collider continuity checked | oracle |
| TER-009 | Source save COMMITTED and runtime PENDING distinguished | DATA04 |
| TER-010 | Origin rebase while streaming terrain retains exact global CellId mapping | integration |
| TER-011 | Source cook failure retains last good physics ground or safe barrier | recovery |
| TER-012 | Static collider unavailable reports incomplete world rather than empty | safety |
| DET-001 | CORE06 fixed tick independent of variable GFX render delta | replay |
| DET-002 | 1 2 8 worker count with Jolt profile golden same or unsupported | replay |
| DET-003 | Jolt cross platform deterministic flag compiled with same defines | compiler |
| DET-004 | Jolt broadphase query nondeterminism mitigated by bounding shape refinement | oracle |
| DET-005 | Win Linux macOS x86 ARM replay source and result hashes compared | hardware |
| DET-006 | Web WASM Jolt or alternative backend build tested not assumed supported | browser |
| DET-007 | Identical command admission and entity creation order yields stable replay | replay |
| DET-008 | Different backend Jolt PhysX Rapier hashes not claimed identical | contract |
| DET-009 | FMA SIMD mixed precision incompatible builds don't claim bit exact | compiler |
| DET-010 | Snapshot rollback includes joint/contact warmstart and sleep state or denies | rollback |
| DET-011 | Restored body handles remapped or generation changed safely | rollback |
| DET-012 | NET authoritative rollback not implied by solver replay | NET |
| DET-013 | Headless dedicated server produces same source-approved body states as rendered | headless |
| DET-014 | Pausing physics does not advance tick and stale commands handled | unit |
| DET-015 | Origin epoch shift repeat/replay ordering stable | replay |
| SEC-001 | Untrusted triangle soup recursion or huge compound denied by quota | fuzz |
| SEC-002 | Malformed NaN hull, bad normals or indices rejected before Jolt | fuzz |
| SEC-003 | Unauthorized remote force teleport and collision source edit denied | security |
| SEC-004 | MCP viewer not allowed to enqueue GAME authoritative impulse | security |
| SEC-005 | Cross-project PhysicsWorldId reference denied | security |
| SEC-006 | Contact listener cannot deadlock by re-entrant shape query | TSan |
| SEC-007 | Use-after-free in joint/body destruction caught by ASan | ASan |
| SEC-008 | Job shutdown waits all physics worker callbacks before freeing arena | TSan |
| SEC-009 | Event flood and huge scene memory cap safe failure | stress |
| SEC-010 | Decompression/import archive geometry rights validated DATA03 | license |
| SEC-011 | Jolt MIT notices and pinned source revision audited | license |
| SEC-012 | PhysX CPU BSD3 and GPU binary redistribution assessed separately | license |
| SEC-013 | Rapier Apache2 Rust FFI crates transitive SBOM audited | license |
| SEC-014 | Bullet zlib core Extras/ThirdPartyLibs excluded until license review | license |
| SEC-015 | No proprietary NVIDIA/competitor test asset copied | license |
| SEC-016 | No known HIGH CRITICAL security finding in future runtime accepted | audit |
| INT-001 | WORLD02 prefab reparent maintains collider world transform and source ID | integration |
| INT-002 | WORLD01 ECS state snapshots receive coherent poststep transforms | integration |
| INT-003 | CORE03 allocator bytes and safe perworld ownership measured | integration |
| INT-004 | CORE05 global local transform and epochs match physics source | integration |
| INT-005 | CORE06 scheduler does fixed tick and worker admission correctly | integration |
| INT-006 | WORLD03 cell stream/lease and collider ACK gate tested | integration |
| INT-007 | WORLD04 terrain/caves source rights and collision source linked | integration |
| INT-008 | DATA03 mesh import validation and DATA05 cook hash respected | integration |
| INT-009 | DATA04 undo scene physics source CAS not solver mutation | integration |
| INT-010 | SIM01 physics2d independent from PHYS3D body and collision layers | architecture |
| INT-011 | SIM03 character controller queries physics but owns movement | architecture |
| INT-012 | SIM04 ragdoll cannot be claimed delivered by basic joint API | architecture |
| INT-013 | SIM05 vehicle and SIM06 soft body not silently part of SIM02 | architecture |
| INT-014 | NET server authorization keeps authoritative physics state | integration |
| INT-015 | GFX04 render interpolation read-only with server no GPU | headless |
| INT-016 | Linux x86 and ARM64 native CPU headless physical world smoke | hardware |
| INT-017 | Windows x64 CPU physical world smoke | hardware |
| INT-018 | macOS arm64 CPU physical world smoke | hardware |
| INT-019 | Web WASM CPU collision and memory smoke or explicit unsupported | browser |
| BEN-001 | Box stack CPU physics tick p50 p95 p99 and worst on named hardware | benchmark |
| BEN-002 | 10k synthetic rigid body stress is workload not guaranteed product capacity | benchmark |
| BEN-003 | Broadphase 1 2 8 worker scales and query false negative count | benchmark |
| BEN-004 | CCD thin wall and fast body accuracy vs CPU time | benchmark |
| BEN-005 | Contact and constraint memory usage active body source counts | benchmark |
| BEN-006 | Terrain stream collider CPU spike and latency to physics ACK | benchmark |
| BEN-007 | Jolt vs PhysX CPU vs Rapier vs Bullet at same oracle workload | benchmark |
| BEN-008 | Web WASM cold load/step memory/precision and no thread fallback | benchmark |
| BEN-009 | Crossplatform deterministic profile golden and costs measured | benchmark |
| BEN-010 | S3P optional prove or drop vs basic barrier CPU time and memory | R&D |
| BEN-011 | Origin shift and terrain recook regression under many cells | benchmark |
| BEN-012 | No 60FPS perfect CCD or engine superiority asserted without proof | audit |

## Independent evidence obligations (not satisfied today)
- Golden original fixtures: analytic falling/rolling convex bodies, static mesh and cave heightfield, convex ramp, compound inertia, 100/1000/10000+ synthetic boxes and constraints, high-speed small CCD, ray/overlap/convex cast, cross-world and destroy/recreate stale epoch, source terrain at huge/negative coordinates.
- Pin exact Jolt (or chosen alternative) source version/CMake build flags/float precision/SIMD/compiler, 1/2/8 workers and command ordering, source AssetId+rights/cooked geometry and WORLD-03 cell revisions. Benchmark *actual* 3D body/tick and server response against independent contact/geometry oracle with p50/p95/p99, max, active bytes/memory peak and query completeness. No “Jolt 5.6 works on WASM” claim without real build.
- Test static/dynamic triangle mesh restrictions (Jolt native docs warn mesh-vs-mesh/heightfield unsupported dynamic contacts), malformed hull/triangle indices and synthetic denial of service; critical walkable ground requires PHYS ACK before WORLD-03 active cell. Contact callbacks must never write ECS or query reentrantly during native step.
- Replay and rollback: cross-platform deterministic CMake option vendor docs do not prove engine-wide event/entity/state replay. Golden tests may need actual collision shape refine for parallel broadphase queries; snapshots must include solver warmstart/constraint/sleep state. If bitwise proof fails, report UNSUPPORTED for that hardware/profile rather than fabricated success.
- Source security: DATA-03 verified rights and import quotas, DATA-04 source journal, CORE job/allocator, server NET permissions, nonfinite/memory and multithread TSan/ASan, no external script or unlicensed vendor demo. Zero known HIGH/CRITICAL for future release.
- Numeric acceptance thresholds and specific supported build/hardware 1.0 DoD UNDECIDED, so this is a **test specification**, not a benchmark pass.
