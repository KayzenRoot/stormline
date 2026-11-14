# SIM-01 — Future 2D Physics Collision/CCD/Replay and Stability Acceptance Matrix

**Research #174 | NLE-P00-WO-002-SIM-01 | Future code #46 OPEN/BLOCKED.**  
**ALL 159 TESTS ARE FUTURE / NOT EXECUTED.** No Stormline rigid-body engine, actual physics colliders/joints/sensor events, C17 library build, native/WASM, golden replay, headless stress or measured frame/CPU performance exists.

| ID | Future objective test | Evidence surface |
|---|---|---|
| IDN-001 | Body shape joint handles invalid after world destroy | unit |
| IDN-002 | Reused body slot increments generation and rejects stale handle | unit |
| IDN-003 | Foreign physics world handle rejected by shape command | unit |
| IDN-004 | ECS EntityGuid never treated as backend raw object ID | architecture |
| IDN-005 | Deleting ECS source body during step queues safe poststep retirement | concurrency |
| IDN-006 | Multiple colliders on a body preserve owning EntityGuid | integration |
| IDN-007 | Prefab body instance maps stable WORLD02 source ID | integration |
| IDN-008 | Rapid create delete create body preserves event identity | stress |
| IDN-009 | Destroyed shape appears in delayed event only with validated generation | event |
| IDN-010 | Unknown BodyId or malformed handle rejected before dereference | fuzz |
| UNT-001 | Physics meters vs sprite pixels conversion explicit and invertible | CPU |
| UNT-002 | Canvas DPI and camera zoom do not change body position | integration |
| UNT-003 | Screen y down to physics y up preserves orientation | CPU |
| UNT-004 | Wrong handedness or physical unit errors fail before step | unit |
| UNT-005 | Nonuniform source parent scale demands collider recook approval | integration |
| UNT-006 | Mirrored negative parent scale checked and winding repaired or denied | unit |
| UNT-007 | Large global coordinate rebase uses new origin epoch safely | integration |
| UNT-008 | Signed coordinate overflow and NaN force rejected | fuzz |
| UNT-009 | Static authored body transformed only through source revision | integration |
| UNT-010 | Dynamic physics state authoritative over read-only visual interp | integration |
| BOD-001 | Gravity falling box trajectory within finite solver tolerance | oracle |
| BOD-002 | Static body unaffected by force application | unit |
| BOD-003 | Kinematic target moves through fixed tick not render delta | unit |
| BOD-004 | Dynamic body mass density inertia positive and bounded | unit |
| BOD-005 | Zero or negative density policy explicit and tested | unit |
| BOD-006 | Two dynamic bodies broadphase and manifold separation correct | oracle |
| BOD-007 | Resting block on plane has bounded penetration and jitter | stress |
| BOD-008 | Tower of boxes stable over approved step count | stress |
| BOD-009 | Pile of 2D circles no blow-up or NaN energy | stress |
| BOD-010 | Sleep wake transition correct for force and contact change | unit |
| BOD-011 | Friction coefficient effect on box sliding within tolerance | oracle |
| BOD-012 | Restitution energy never increases beyond approved tolerance | oracle |
| BOD-013 | Damping and gravity scale effects match fixed step contract | unit |
| BOD-014 | Fast body impulse stays below owner approved velocity budget | stress |
| BOD-015 | Body type changes only at validated pre-step barrier | concurrency |
| SHP-001 | Circle radius finite positive and ShapeAsset source verified | fuzz |
| SHP-002 | Capsule and rounded rectangle geometry valid at edge cases | unit |
| SHP-003 | Convex polygon rejects nonconvex self-crossing vertices | fuzz |
| SHP-004 | Polygon winding and vertex max validated before import | security |
| SHP-005 | Multiple shape compound body yields correct mass and collision | unit |
| SHP-006 | Chain collider with valid ghost vertices eliminates tile snag | TWO02 |
| SHP-007 | Invalid chain winding ghost points rejected with typed error | fuzz |
| SHP-008 | One-way platform not claimed as SIM01 automatic solver feature | contract |
| SHP-009 | Terrain tile collider source revision tied to cooked asset hash | DATA05 |
| SHP-010 | Concave static terrain approximation has no false collision gaps | oracle |
| SHP-011 | Dynamic concave collider requires validated decomposition or reject | security |
| SHP-012 | Shape scale edit recooks and invalidates stale contact references | integration |
| SHP-013 | Filter group index and mask symmetry tested exhaustively small matrix | property |
| SHP-014 | Render sprite ordering does not change physics category bits | integration |
| SHP-015 | Sensor shape overlap produces no physical collision response | unit |
| SHP-016 | Enable sensor event opt-in limits needless event cost | benchmark |
| SHP-017 | Sensor versus sensor pair follows documented enable policy | unit |
| SHP-018 | Cross-world source shapes cannot be shared as live mutable collider | security |
| EVT-001 | Contact begin and end emitted at documented poststep tick | event |
| EVT-002 | Contact hit impulse generation bounded and finite | event |
| EVT-003 | Sensor enter leave correct after movement | event |
| EVT-004 | Filter edit may deliver change events next step documented | event |
| EVT-005 | Events immutable while GAME/AI consumes buffer after step | concurrency |
| EVT-006 | Event pair stable ordering independent of backend callback order | replay |
| EVT-007 | Event references generation-check disposed shape after step | security |
| EVT-008 | Contact subscription disabled does not fabricate hit events | unit |
| EVT-009 | Contact callback cannot destroy body inside concurrent step | concurrency |
| EVT-010 | Event queue overflow returns typed backpressure not drop critical | stress |
| EVT-011 | Rapid repeated overlap begin end no duplicate pair notifications | replay |
| EVT-012 | Collision audio effect cannot mutate authoritative physics state | integration |
| EVT-013 | Multi-world events never leak across project boundaries | security |
| QRY-001 | Ray cast on circle gives correct hit fraction and normal | oracle |
| QRY-002 | Ray cast empty region truthfully returns none for resident physics | oracle |
| QRY-003 | Shape cast against static box detects swept first impact | oracle |
| QRY-004 | AABB overlap broadphase candidates refined by exact geometry | oracle |
| QRY-005 | Point query shape boundaries and tangencies follow epsilon policy | CPU |
| QRY-006 | Query filter category group and sensor inclusion exact | property |
| QRY-007 | Paged result limit prevents unbounded query allocation | stress |
| QRY-008 | Queries during simulation step reject or queue documented snapshot | concurrency |
| QRY-009 | Query stale world epoch returns typed stale rather than pointer | security |
| QRY-010 | Unloaded tile reports incomplete collision not empty complete | WORLD03 |
| QRY-011 | Physics broadphase independence from WORLD03 cell metadata | architecture |
| QRY-012 | Sorted query when requested reproducible across worker counts | replay |
| CCD-001 | Fast bullet to thin static wall blocked at permitted tolerance | CCD |
| CCD-002 | Fast bullet to moving dynamic target tests optional CCD mode | CCD |
| CCD-003 | Fast sensor versus fast sensor cannot claim guaranteed overlap | contract |
| CCD-004 | High speed trigger uses explicit cast fallback instead of missed event | CCD |
| CCD-005 | Substeps 1 2 4 8 solver behavior compared with costs | benchmark |
| CCD-006 | Large timestep rejected if beyond approved stability limits | safety |
| CCD-007 | Tiny shape high speed swept cast bound stable near tolerance | oracle |
| CCD-008 | CCD recovery from invalid TOI returns typed failure not NaN | fuzz |
| JNT-001 | Distance joint fixed length within tolerance under gravity | oracle |
| JNT-002 | Revolute joint anchor/angle limits obey finite bounds | oracle |
| JNT-003 | Prismatic joint translation limits and motor caps | oracle |
| JNT-004 | Weld joint breaks only if explicit backend feature supported | unit |
| JNT-005 | Motor/spring/damping parameter conversion version pinned | unit |
| JNT-006 | Joint with destroyed body retires safely without stale event | concurrency |
| JNT-007 | Joint chain tower stress finite solve and memory | stress |
| JNT-008 | CollideConnected policy honored for jointed pair | unit |
| JNT-009 | Unsupported joint type fails typed backend feature error | contract |
| JNT-010 | Joint dynamic toggle queued before step | concurrency |
| TIM-001 | Fixed timestep 1 over 60 candidate reproducible for same tick count | replay |
| TIM-002 | Variable rendering framerate does not alter physics step count/results | replay |
| TIM-003 | Catch-up max caps frame runaway and signals backlog | budget |
| TIM-004 | Paused physics world performs zero solver steps and maintains state | unit |
| TIM-005 | Game time scale applied by CORE clock not Canvas delta | integration |
| TIM-006 | Poststep ECS transform publication single consistent tick snapshot | integration |
| TIM-007 | Single worker vs multithread replay same frozen physics profile | replay |
| TIM-008 | Command admission order stable for same tick and entity generation | replay |
| TIM-009 | World origin shift at safe tick preserves global locations | integration |
| TIM-010 | Contact force applied by gameplay arrives next tick not current callback | replay |
| TIM-011 | Snapshot includes solver/contact and joint warm-start state or rejects | rollback |
| TIM-012 | Restore snapshot remaps body handles or invalidates safely | rollback |
| TIM-013 | Replay body and event hashes equal after full restore on same backend | rollback |
| TIM-014 | Mixed precision FMA/SIMD flag differences not mislabeled deterministic | compiler |
| TIM-015 | Native Win Linux macOS golden replay byte and numeric profile | hardware |
| TIM-016 | Web WASM CPU replay matches approved golden profile or unsupported | browser |
| TIM-017 | Different solver backend simulation hashes not falsely promised equal | contract |
| INT-001 | WORLD01 generational ECS mapping and source component lifecycle | integration |
| INT-002 | TWO01 camera interpolation never feeds solver authoritative pose | integration |
| INT-003 | TWO02 contiguous tile chain and ghost vertex authored source | integration |
| INT-004 | WORLD03 streamer collider pin ack before active traversable cell | integration |
| INT-005 | WORLD02 scene reparent correct physics frame and scale recook | integration |
| INT-006 | DATA04 journal physics config CAS and undo redo source truth | integration |
| INT-007 | DATA05 cooked shape hash and importer provenance check | integration |
| INT-008 | CORE06 scheduler tick and budget authority preserved | integration |
| INT-009 | CORE05 global origin shift exact owner handoff | integration |
| INT-010 | SIM02 3D physics does not share 2D contact/manifold without bridge | architecture |
| INT-011 | SIM03 controller receives collision query but owns motor | integration |
| INT-012 | NET authoritative body forces and teleport not editable by viewer MCP | security |
| INT-013 | AUDIO impact sound event consumption occurs after physics step | integration |
| INT-014 | Headless dedicated server runs without GPU or Canvas | headless |
| INT-015 | Windows native C17 wrapper build and runtime contact smoke | hardware |
| INT-016 | Linux amd64/ARM64 native headless collision smoke | hardware |
| INT-017 | macOS Apple Silicon native physics smoke | hardware |
| INT-018 | Web WASM no threaded worker fallback remains bounded | browser |
| SEC-001 | Nonfinite force torque angle speed rejected before stepping | fuzz |
| SEC-002 | Polygon vertex shape count and joint count quota bounded | stress |
| SEC-003 | Untrusted collider data import subject to DATA03 safety checks | security |
| SEC-004 | Unauthorized MCP cannot add physics impulse to server client actor | security |
| SEC-005 | Cross-project editor shape reference denied | security |
| SEC-006 | Event flood cannot exhaust memory or silently drop critical event | stress |
| SEC-007 | Stale contact handle cannot access freed solver memory | ASan |
| SEC-008 | Destroy world in flight step protected by safe barrier | TSan |
| SEC-009 | Callback that attempts ECS mutation rejected with receipt | security |
| SEC-010 | Malicious chain ghost self intersect or degenerate rejected | fuzz |
| SEC-011 | Collision filter 64-bit masks or groups serialized version-checked | security |
| SEC-012 | Render camera DPI cannot change game collision geometry | security |
| SEC-013 | Box2D MIT pinned notice and source version audited before code | license |
| SEC-014 | Chipmunk MIT/Rapier Apache 2.0 transitive notices audited | license |
| SEC-015 | No unlicensed physics demo scene copied into engine | license |
| SEC-016 | No HIGH CRITICAL known security or regression in future implementation | audit |
| BEN-001 | Analytic freefall and stacks small medium huge stress stability | benchmark |
| BEN-002 | 10k+ bodies synthetic scene input not capability claim | benchmark |
| BEN-003 | Broadphase versus brute force query false negatives absent | benchmark |
| BEN-004 | CCD bullet and tile chain under stress p95 p99 measured | benchmark |
| BEN-005 | Joint constraints chain precision versus substeps/CPU cost | benchmark |
| BEN-006 | Per fixed tick CPU p50 p95 p99 and max stall by phase | benchmark |
| BEN-007 | Peak per-world memory and event buffer bytes under flood | benchmark |
| BEN-008 | Physics source collider stream load and unload spike measured | benchmark |
| BEN-009 | Headless vs native rendered scene identical physics event hashes | benchmark |
| BEN-010 | Box2D versus Chipmunk/Rapier on identical oracle under adapter | benchmark |
| BEN-011 | WASM browser CPU stepping with/without SIMD feature flags | benchmark |
| BEN-012 | No asserted 60fps perfect determinism or stability without tests | audit |

## Future proof plan, none executed
- Recreate independent original fixtures: analytical fall/pendulum, static chain from tiled collision source, 1/10/100/1000+ body piles and joint chains, wall high-speed bullet, sensor fast motion, filters, concave invalid input, multiworld/stale handles, moving platform, 2.5D depth sorting separate from collision. No competitor demo assets copied or proprietary physics art.
- Freeze exact `PhysicsProfile`, backend pinned version+compiler+single-precision/FMA/SIMD/substeps, CORE fixed tick, command order and source shape AssetId hash, world/ECS IDs, local/global units and origin epoch. Compare event batches and body/joint states against independent geometric/analytic or replay oracle where mathematically valid. Measure penetration/jitter and energy drift with friction tolerances, not promise ideal perpetual conservation.
- Verify CCD and fast sensor edge cases: Box2D docs do NOT promise continuous overlap for two moving sensors; a cast/query fallback is needed for gameplay relying on guaranteed detection. Chain winding/ghost vertices and imported polygon strictness must be tested, not assumed.
- Actual rollback requires complete state including constraints/warm starts or a backend-specific documented supported snapshot; saving transforms alone fails. Two backend versions are NOT assumed output-equal. Cross-Win/Linux/macOS/WASM equality only after golden byte/float profile proof.
- Security/source: bounded events/shape counts, nonfinite and unknown world handles, unauthorized editor/MCP impulse, DATA-03 import rights, DATA-04 source persistence, WORLD-03 critical collider readiness, native/Web/headless ASan/TSan and no known HIGH/CRITICAL. All benchmarks target p50/p95/p99 and peak bytes on owner-selected devices, budget values TBD.
