# SIM-05 — Acceptance Matrix: 112 FUTURE Cases, NONE EXECUTED

Research #186 | WO NLE-P00-WO-002-SIM-05 | Future coding #50 BLOCKED | DOCUMENTARY ONLY.

**All 112 cases are FUTURE / NOT EXECUTED.** No navigation runtime, native/wasm builds, NPC agent, fixtures, workload trace, sanitizer or benchmark has been executed in Stormline. Catalog criterion NPCs navigate a dynamic world with streaming remains FUTURE.

## Proposed test matrix
| ID | Prospective case | Status |
|---|---|---|

| SIM05-GEO-01 | Static courtyard two profiles with different radius | FUTURE / NOT EXECUTED |
| SIM05-GEO-02 | Reject NaN/infinite coordinates in polygon source | FUTURE / NOT EXECUTED |
| SIM05-GEO-03 | Reject negative triangle/index and nonmanifold seam | FUTURE / NOT EXECUTED |
| SIM05-GEO-04 | Reject solid obstacle represented as walkable area | FUTURE / NOT EXECUTED |
| SIM05-GEO-05 | Different agent heights/slope yield distinct validated topology | FUTURE / NOT EXECUTED |
| SIM05-GEO-06 | Cross-border tile seam has matching compatible signatures | FUTURE / NOT EXECUTED |
| SIM05-GEO-07 | Cyclic/invalid off-mesh portal is rejected | FUTURE / NOT EXECUTED |
| SIM05-GEO-08 | Negative global coordinate and origin rebase tile key safe | FUTURE / NOT EXECUTED |

| SIM05-TIL-01 | Valid cooked tile hash/schema and source geometry hash | FUTURE / NOT EXECUTED |
| SIM05-TIL-02 | Reject truncated or corrupted Detour tile blob | FUTURE / NOT EXECUTED |
| SIM05-TIL-03 | Tile register rejects mismatch geometry/PHYS revision | FUTURE / NOT EXECUTED |
| SIM05-TIL-04 | Retire tile invalidates stale query leases/handles | FUTURE / NOT EXECUTED |
| SIM05-TIL-05 | Atomic neighboring tile replacement publishes coherent epoch | FUTURE / NOT EXECUTED |
| SIM05-TIL-06 | Duplicate tile IDs and generations do not alias | FUTURE / NOT EXECUTED |
| SIM05-TIL-07 | Corrupted compressed bundle is rejected without crash | FUTURE / NOT EXECUTED |
| SIM05-TIL-08 | Thousands of tiles respect count/heap/CPU quotas | FUTURE / NOT EXECUTED |

| SIM05-PTH-01 | A* returns complete route on reference topology | FUTURE / NOT EXECUTED |
| SIM05-PTH-02 | Unreachable goal yields distinct PATH_NOT_FOUND | FUTURE / NOT EXECUTED |
| SIM05-PTH-03 | Unloaded target yields NAV_PENDING not false reachability | FUTURE / NOT EXECUTED |
| SIM05-PTH-04 | Zero-cost legal edge and nonnegative heuristic policy checked | FUTURE / NOT EXECUTED |
| SIM05-PTH-05 | Reject negative, NaN, overflow area costs | FUTURE / NOT EXECUTED |
| SIM05-PTH-06 | Bound search maxVisited/timeout with partial status | FUTURE / NOT EXECUTED |
| SIM05-PTH-07 | Stable tie-break produces replay-compatible waypoint order | FUTURE / NOT EXECUTED |
| SIM05-PTH-08 | Cancel and priority queue do not starve lower priority agents | FUTURE / NOT EXECUTED |

| SIM05-STR-01 | WORLD-03 load lease and PHYS-ready gate NAV publish | FUTURE / NOT EXECUTED |
| SIM05-STR-02 | Collider unload revokes active route safely | FUTURE / NOT EXECUTED |
| SIM05-STR-03 | Streaming cell hole produces explicit incomplete coverage | FUTURE / NOT EXECUTED |
| SIM05-STR-04 | Terrain edit rebake staging cannot mix stale seams | FUTURE / NOT EXECUTED |
| SIM05-STR-05 | Cross-cell teleport request does not reuse old nav path | FUTURE / NOT EXECUTED |
| SIM05-STR-06 | Hot unload while path job in-flight cancels stale result | FUTURE / NOT EXECUTED |
| SIM05-STR-07 | Long-distance path prefetch respects authority and caps | FUTURE / NOT EXECUTED |
| SIM05-STR-08 | Partial tiles do not claim full-world LineOfSight | FUTURE / NOT EXECUTED |

| SIM05-DYN-01 | Moving physics body steered around without tile rebuild | FUTURE / NOT EXECUTED |
| SIM05-DYN-02 | Door close changes valid off-mesh/link or topology | FUTURE / NOT EXECUTED |
| SIM05-DYN-03 | Unbounded door toggle throttled with hysteresis | FUTURE / NOT EXECUTED |
| SIM05-DYN-04 | Terrain collision source revision forces path invalidation | FUTURE / NOT EXECUTED |
| SIM05-DYN-05 | DetourTileCache rebuild obeys memory/latency quota | FUTURE / NOT EXECUTED |
| SIM05-DYN-06 | Path invalidation and new epoch do not race physics step | FUTURE / NOT EXECUTED |
| SIM05-DYN-07 | Persistent debris area cost blocked/updated by GAME owner | FUTURE / NOT EXECUTED |
| SIM05-DYN-08 | Dynamic obstacle cannot forge traversability without PHYS | FUTURE / NOT EXECUTED |

| SIM05-LNK-01 | Jump link checks SIM-03 ability/clearance | FUTURE / NOT EXECUTED |
| SIM05-LNK-02 | Ladder link capability explicit instead of planar walking | FUTURE / NOT EXECUTED |
| SIM05-LNK-03 | Drop link one-way edge semantics verified | FUTURE / NOT EXECUTED |
| SIM05-LNK-04 | Elevator/platform travel validates moving support epoch | FUTURE / NOT EXECUTED |
| SIM05-LNK-05 | Door interaction denied from unauthorized agent | FUTURE / NOT EXECUTED |
| SIM05-LNK-06 | Off-mesh link source stale yields typed invalid result | FUTURE / NOT EXECUTED |
| SIM05-LNK-07 | Link cancellation mid traversal maintains motor safe state | FUTURE / NOT EXECUTED |
| SIM05-LNK-08 | 2D side-scroller domain not assumed 3D navmesh | FUTURE / NOT EXECUTED |

| SIM05-STE-01 | Route generated velocity bounded by movement profile | FUTURE / NOT EXECUTED |
| SIM05-STE-02 | Local avoidance velocity cannot teleport ECS | FUTURE / NOT EXECUTED |
| SIM05-STE-03 | MotorMotionReceipt blocked by wall triggers bounded replan | FUTURE / NOT EXECUTED |
| SIM05-STE-04 | Moving platform support and origin rebase integrated | FUTURE / NOT EXECUTED |
| SIM05-STE-05 | DetourCrowd vs RVO2 planar comparator same fixture | FUTURE / NOT EXECUTED |
| SIM05-STE-06 | RVO2 out-of-plane/flying use rejected unless profiled | FUTURE / NOT EXECUTED |
| SIM05-STE-07 | Steering updated at fixed tick independent render FPS | FUTURE / NOT EXECUTED |
| SIM05-STE-08 | Agent detach invalidates pending steering intents | FUTURE / NOT EXECUTED |

| SIM05-CRD-01 | 10 agents bidirectional narrow corridor | FUTURE / NOT EXECUTED |
| SIM05-CRD-02 | 100 agents four-way crossing with contact oracle | FUTURE / NOT EXECUTED |
| SIM05-CRD-03 | 1000 controlled visual crowd LOD with gameplay receipts | FUTURE / NOT EXECUTED |
| SIM05-CRD-04 | Bottleneck reservation suppresses oscillatory replans | FUTURE / NOT EXECUTED |
| SIM05-CRD-05 | Stationary obstacle avoidance prevents persistent push | FUTURE / NOT EXECUTED |
| SIM05-CRD-06 | Priority aging/fairness prevents low priority starvation | FUTURE / NOT EXECUTED |
| SIM05-CRD-07 | Agent churn add/remove generation safe under concurrency | FUTURE / NOT EXECUTED |
| SIM05-CRD-08 | Crowd memory/CPU p95/p99 measured at target hardware | FUTURE / NOT EXECUTED |

| SIM05-BT-01 | Sequence/selector/condition typed truth table | FUTURE / NOT EXECUTED |
| SIM05-BT-02 | Reactive abort clears outstanding motor intent | FUTURE / NOT EXECUTED |
| SIM05-BT-03 | Async action complete exactly once with idempotent token | FUTURE / NOT EXECUTED |
| SIM05-BT-04 | Async action timeout/cancel cleans resources | FUTURE / NOT EXECUTED |
| SIM05-BT-05 | Reject unbounded recursion/cycle in authored nodes | FUTURE / NOT EXECUTED |
| SIM05-BT-06 | Bound parallel children/event emission/CPU budget | FUTURE / NOT EXECUTED |
| SIM05-BT-07 | Typed blackboard keys enforce scoped permissions | FUTURE / NOT EXECUTED |
| SIM05-BT-08 | Vendor XML/plugin path cannot load arbitrary code | FUTURE / NOT EXECUTED |

| SIM05-FSM-01 | Idle/patrol/chase/attack state transition canonical order | FUTURE / NOT EXECUTED |
| SIM05-FSM-02 | Nested states enter/exit only once per valid transition | FUTURE / NOT EXECUTED |
| SIM05-FSM-03 | Interrupted attack cannot double emit GAME ability intent | FUTURE / NOT EXECUTED |
| SIM05-FSM-04 | Finite loops per tick stop with GRAPH_STEP_LIMIT | FUTURE / NOT EXECUTED |
| SIM05-FSM-05 | Retreat/flee policy respects world coverage UNKNOWN | FUTURE / NOT EXECUTED |
| SIM05-FSM-06 | Graph source revision hot swap stage at safe tick | FUTURE / NOT EXECUTED |
| SIM05-FSM-07 | Reverse state change on entity destroy cancels jobs | FUTURE / NOT EXECUTED |
| SIM05-FSM-08 | One actor command ordering stable across worker counts | FUTURE / NOT EXECUTED |

| SIM05-PER-01 | Vision cone and distance filter using WORLD candidates | FUTURE / NOT EXECUTED |
| SIM05-PER-02 | PHYS ray occlusion behind validated wall | FUTURE / NOT EXECUTED |
| SIM05-PER-03 | Unloaded occluder yields UNKNOWN rather than VISIBLE | FUTURE / NOT EXECUTED |
| SIM05-PER-04 | Audio sound stimulus only via owner GAME/AUD schema | FUTURE / NOT EXECUTED |
| SIM05-PER-05 | Faction/team filter and stealth GAME rule override | FUTURE / NOT EXECUTED |
| SIM05-PER-06 | Last-seen target expires and stale entity invalidates | FUTURE / NOT EXECUTED |
| SIM05-PER-07 | Client debug view redacts hidden opponent position | FUTURE / NOT EXECUTED |
| SIM05-PER-08 | High-frequency perception ray requests obey quota | FUTURE / NOT EXECUTED |

| SIM05-SEC-01 | Fuzz nav tile parser and bounded decompressor | FUTURE / NOT EXECUTED |
| SIM05-SEC-02 | Reject oversized polygon count and integer overflow | FUTURE / NOT EXECUTED |
| SIM05-SEC-03 | Reject malicious behavior script/arbitrary JSON pointer | FUTURE / NOT EXECUTED |
| SIM05-SEC-04 | Unauthorized MCP navigation/bot control denied | FUTURE / NOT EXECUTED |
| SIM05-SEC-05 | Query from wrong WorldId/AgentGeneration denied | FUTURE / NOT EXECUTED |
| SIM05-SEC-06 | Async result-after-unload UAF sanitizer future test | FUTURE / NOT EXECUTED |
| SIM05-SEC-07 | TSan/ASan/UBSan report results explicitly future | FUTURE / NOT EXECUTED |
| SIM05-SEC-08 | Secret/PII and hidden blackboard never logged or replicated | FUTURE / NOT EXECUTED |

| SIM05-PLT-01 | Windows x64/ARM headless build planned | FUTURE / NOT EXECUTED |
| SIM05-PLT-02 | Linux x64/ARM headless build planned | FUTURE / NOT EXECUTED |
| SIM05-PLT-03 | macOS ARM64 and Intel support policy checked | FUTURE / NOT EXECUTED |
| SIM05-PLT-04 | WASM scalar/SIMD and memory limits separately tested | FUTURE / NOT EXECUTED |
| SIM05-PLT-05 | Reproduce fixed TickId path/event trace with FPS change | FUTURE / NOT EXECUTED |
| SIM05-PLT-06 | Cross-compiler divergence reports numeric tolerance | FUTURE / NOT EXECUTED |
| SIM05-PLT-07 | Editor/CLI/MCP same StageProfile schema and permissions | FUTURE / NOT EXECUTED |
| SIM05-PLT-08 | Scene source origin rebase has no stale query success | FUTURE / NOT EXECUTED |

| SIM05-BEN-01 | 100x100 meter static path latency p50/p95/p99 | FUTURE / NOT EXECUTED |
| SIM05-BEN-02 | 4-km^2 tiled world streaming under agent movement | FUTURE / NOT EXECUTED |
| SIM05-BEN-03 | 1000 concurrent queries fixed cap CPU/memory | FUTURE / NOT EXECUTED |
| SIM05-BEN-04 | 100 agent pursuit/avoidance + perception costs | FUTURE / NOT EXECUTED |
| SIM05-BEN-05 | 500 statechart+BT instances with async work budgets | FUTURE / NOT EXECUTED |
| SIM05-BEN-06 | Dynamic tile rebake/collision turnover latency | FUTURE / NOT EXECUTED |
| SIM05-BEN-07 | One hour agent churn no leak/stranded tasks | FUTURE / NOT EXECUTED |
| SIM05-BEN-08 | NPCs in original dynamic map complete safe paths verified | FUTURE / NOT EXECUTED |

## Evidence and run policy
1. Unit and deterministic reference oracles: small manually verified nav topology, A*/Dijkstra path cost, polygon validation, integer overflow, nav tile seam, tick/graph ordering, typed authorization and blackboard.
2. Integration: WORLD-03 streamed cell and source revisions; SIM-02 collider readiness/revision; SIM-03 CharacterIntent and MotorMotionReceipt; GAME/NET/AUD authority; DATA-03/04/05 import/cook; all depend on runtime modules that do not exist.
3. Robustness and privacy: hostile tiles/graph/async/fuzz, missing/corrupt cell, malicious principal, line-of-sight unknown, data leak, TSan/ASan/UBSan and controlled failure recovery.
4. Benchmarks: bounded path latency, tile rebuild p95/p99, agents/s, crowd and perception rays, active bytes and allocations, queue depth and starvation across native OS and optional WASM; exact targets from measured baseline, not fabricated now.
5. Editor/CLI/MCP: same source revision CAS and permission gates, no direct arbitrary AI behavior script execution, correct redaction and rate limits.
6. Quality proof: original source asset rights, deterministic seeded behavior fixture, real NPC traversals through dynamic stream with collision oracle and measurable stuck/deadlock and unreachable/incomplete receipts.

**None have PASS/FAIL evidence.** Documentation CI passes do not execute engine tests. Exact code commands, hardware, fixture hashes, acceptance thresholds and numerical tolerances are future implementation WO decisions. Cross-OS bitwise determinism is not established.
