# SIM-05 — Navigation, Crowd and AI Decision Reproducible Benchmark Protocol

**Date:** 2026-11-14 | WO NLE-P00-WO-002-SIM-05 | Research #186. **Status: FUTURE ONLY, ZERO EXECUTION/RESULTS.**

## 1. Research questions
How much CPU, wall latency, memory and update stall does tile baking/activation, bounded pathfinding, local avoidance, behavior evaluation and perception consume as dynamic terrain loads, obstacles move and agents act? Are incomplete cells correctly rejected rather than granting physically invalid paths? Does gameplay behavior stay stable under presentation FPS, path jobs, rebase and world unloading? Do candidate libraries offer a measurable advantage over a simple owned reference implementation at comparable quality?

## 2. Original reproducible future fixtures
- **NAV-H1:** original static 128m x 128m courtyard with walkable plaza, corridor, narrow door, wall and ramp, two NPC radius/height/capability profiles and annotated path oracle.
- **NAV-H2:** procedural 4 km x 4 km tiled original hills/ruins, cliffs, streams and houses with uniquely versioned WORLD-03 CellIds and PHYS collider source. Source/author/rights and generation seed manifest; no copied game map.
- **NAV-D1:** dynamic version of NAV-H2: door open/close, movers, breakable obstruction, terrain rebase, tile unload/reload, source/collider mutation, staged mesh bake and job cancellation.
- **NAV-C1:** 10/100/1000 original NPC traffic agents across plaza/crossroads/chokepoints in 2D ground plane; controlled desired velocities and SIM-03 motor receipts, constant population churn.
- **NAV-B1:** typed authored patrol/chase/flee/attack/return BT + statechart and authorized blackboard; perception vision cones, occluders, fake audio stimulus and network redaction.
- **NAV-X1:** adversarial invalid nav tile, very deep graph, malformed off-mesh refs, decompression bomb declaration, unauthorized MCA/CLI actor, origin/epoch mismatch and private blackboard read attempt.
- **NAV-2D:** original 2D grid and side-scroller with platformer jump/drop/ladders, never misrepresented as 3D Recast walkable surface.

These fixtures are **NOT CREATED**, need authorship/license manifest and hashes plus geometry/collider/nav builder revision, source dataset, reproducible seeds and golden controlled outputs.

## 3. Candidate workload matrix
| Profile | Workload | Collect |
|---|---|---|
| Headless static | 1/100/1000 path queries, different profile size and path length | p50/p95/p99 query duration, visited nodes, queue latency, optimality/cost oracle, peak bytes |
| Dynamic tiles | repeated door/terrain updates and 1000 streamed tiles with PHYS acknowledgments | ingest/bake/activation p95/p99, max source mismatch, false reachability=0, scratch heap |
| Large world | NPC movement across 4 km world with sparse and dense streaming | nav cache eviction/leases, stall durations, incomplete/pending receipts and memory |
| Crowd | 10, 100, 1000 agents; DetourCrowd vs planar RVO2 only under matched rules | min separation, true PHYS contacts, stuck/deadlock rate, reroutes, CPU/memory |
| Behavior | 1000 BT/statechart per-tick decisions with sleep/LOD/async cancellation | CPU per tick/agent, graph steps, dropped intents, fairness and task leak |
| Perception | 100/1000 agents with occlusion and streaming holes | ray requests, PHYS query CPU, true/false visibility vs oracle, UNKNOWN safety, hidden-data leakage |
| Security | corrupted tile/graph/tool commands and UAF race | expected error, panic/crash, byte budget, sanitizer/fuzz crash count |
| Portability | Win/Linux/macOS native, optional WASM scalar/SIMD/threads | same input trace, typed receipts/numeric tolerance and peak memory per target |

## 4. Measurement, baselines and thresholds
Use pinned main/build/source SHA, vendor releases+licenses, compiler/flags/allocator, OS/CPU architecture, run seed, navmesh tile manifest/WorldEpoch/ColliderRevision, physics backend and game/behavior graph revision. Run on known thermals, power profile and no unrelated jobs. Record N repeated cold/warm runs, median p50/p95/p99, jitter, CI/bootstrap confidence and regression criteria, disclose failed samples.
Log separate timings: Recast **offline bake** vs Detour **runtime query** vs tile cache update, WORLD-03 source activation, SIM-03 accepted movement, crowd steering and BT/perception. Measure CPU time, allocations, resident memory/cache, nodes expanded, false-grounded/false-visible events, queue starvation, path completeness, agent convergence, replan oscillation and collision counts. Never conflate physics wall blocking with path search success.
Numeric thresholds are deliberately **UNDECIDED**; select after first validated baseline for hardware tiers and reproducible scene/crowd loads. A proposed objective is zero knowingly unsafe traversability/hidden information leak, requiring test oracle and real results before PASS. Comparative claims vs commercial engines require same assets/game conditions, hardware and versions plus objective methods; no invented performance superiority.
Cross-OS deterministic simulation requires the full CORE-04, SIM-02, SIM-03, WORLD-03 and job schedule; native or WASM flags alone do not prove cross-platform bitwise replay. Physics perception safety and source provenance must be recorded.

## 5. Future Evidence Bundle and rollback
Provide exact commands, test manifests, source SHA, vendor commit/tag/license SBOM, trace distribution/CPU/heap plots, sanitized log and authorization, all safety test cases and outcomes, role and threat model, incident/failure repro and rollback/roll-forward plan. Proposed DoD thresholds and future M01 release class require objective approval. **No tests or benchmark were actually performed at P00**.
