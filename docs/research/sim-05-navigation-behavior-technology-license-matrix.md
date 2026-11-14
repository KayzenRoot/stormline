# SIM-05 — Technology, License, Runtime and Feature-Compatibility Matrix

**Status: OFFICIAL UPSTREAM RESEARCH; CANDIDATES ONLY. NO LIBRARY ADOPTED/INSTALLED.**  
WO NLE-P00-WO-002-SIM-05 | Research #186 | Future code #50 OPEN/BLOCKED | 2026-11-14.

| Candidate | Verified upstream capability | License of core (validate pin+closure) | Limitation / integration risk | Decision |
|---|---|---|---|---|
| [Recast](https://github.com/recastnavigation/recastnavigation) | Build static/tiled navigation mesh from source geometry using voxel-based walkable region pipeline | **zlib**, upstream README/License.txt | Source/bake tool, not directly a dynamic authoritative physics collision representation. Must pin geometry and source/collider revisions via WORLD/DATA | **LEADING 3D BAKE CANDIDATE; NOT ADOPTED** |
| [Detour](https://github.com/recastnavigation/recastnavigation/tree/main/Detour) | Runtime path queries, nav polygons, corridors and pathfinding | **zlib** project license | Native Detour polygon refs/allocators have no stable public Stormline ABI; authoritative world completeness and streamed tile read barriers need owner adapter | **LEADING RUNTIME PATH CANDIDATE; NOT ADOPTED** |
| [DetourTileCache](https://github.com/recastnavigation/recastnavigation/tree/main/DetourTileCache) | Tiled cache/dynamic obstacle and rebuild pathways | **zlib** project license | Not infinite dynamic terrain engine; tile rebuild and world streaming leases, physics readiness and queue ordering need proof | **OPTIONAL DYNAMIC NAV CANDIDATE** |
| [DetourCrowd](https://github.com/recastnavigation/recastnavigation/tree/main/DetourCrowd) | Crowd agent movement, local avoidance and related nav path follow | **zlib** project license | Native approach vs RVO2 alternative; crowd intent is not SIM-03 collision success; instrument neighbor and update costs | **FIRST CROWD COMPARATOR, NOT ADOPTED** |
| [RVO2](https://github.com/snape/RVO2) | 2D ORCA reciprocal obstacle/agent velocity avoidance | **Apache-2.0**, SPDX source | Algorithm concerns **planar 2D**, not arbitrary 3D flying nav; OpenMP/configure with CORE scheduling; license notice and patent review where applicable | **ALTERNATIVE STEERING BENCHMARK, NOT ADOPTED** |
| [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP) | C++17 reactive/async BT, typed ports/blackboard, XML/DSL and profiling; ROS/robotics heritage | **MIT** upstream LICENSE | XML load and native plugins require security gating; transitive dependencies + public ABI compatibility must be reviewed. **Groot2/third-party GUI not implied MIT** | **BT ENGINE COMPARATOR; NOT ADOPTED** |
| [[Boost::ext].SML](https://github.com/boost-ext/sml) | Header-only C++14 state machine with nesting and compile-time graph support | **BSL-1.0** upstream repo | Not officially Boost; compile-time focus may not suit dynamic authored graphs; map to Stormline type schema with tests | **STATECHART COMPARATOR; NOT ADOPTED** |
| Stormline authored graph/2D grid/perception | Declarative typed behavior graph/blackboard and 2D grid candidate; private C++ adapter to chosen planner | Engine license itself **OPEN** by NLE-D009 | Must minimize graph runtime and maintain Editor/CLI/MCP parity, headless/security | **PROPOSED OWNED SEMANTICS, NO CODE** |
| Experimental voxel/sparse navigation + GPU path or AI planning | Alternative large-world/vertical navigation and batch inference | Version/third-party IP/data rights not established | No cross-platform GPU/vision/LLM inference dependency or deterministic superiority claim | **FUTURE / PROVE-OR-DROP** |

## Licenses and compatibility decision checklist
- Verify exact upstream tags/commits, zlib/MIT/Apache-2.0/BSL-1.0 notices, bundled code, sample assets, transitive dependency licenses, SBOM, CVEs and supported toolchains before any use. Engine distribution license is OPEN and not inferred from permissible upstream libraries.
- Recast requires custom engine-owned contract wrapper; upstream [BuildingAndIntegrating](https://github.com/recastnavigation/recastnavigation/blob/main/Docs/_2_BuildingAndIntegrating.md) notes **no stable official C API**, and custom allocators are available. Toolchain and plugin ABI constraints matter.
- BehaviorTree.CPP upstream package metadata and README may differ on branch/version. Do **not** hard-pin a version based on unpinned master; confirm exact stable release and transitive XML/ZeroMQ/SQLite/license implications, and avoid any paid GUI requirement.
- RVO2 2D is a local steering option, not a guarantee of obstacle-free 3D collision. DetourCrowd vs RVO2 comparisons should use same objective collision traces, agent count, world revision and CPU/heap p95/p99.
- Compare 2D grid A*/Dijkstra/portal/hierarchical algorithms against Recast 3D **only where the navigation domain is equivalent**; do not falsely declare a universal winner.
- Native Linux/Windows/macOS/ARM and WebAssembly build headless to be verified in code increment. No platform performance, source reproducibility or deterministic cross-OS proof today.

## Primary official sources read
- [RecastNavigation README](https://github.com/recastnavigation/recastnavigation), [Recast Navigation integration](https://github.com/recastnavigation/recastnavigation/blob/main/Docs/_2_BuildingAndIntegrating.md), [license](https://github.com/recastnavigation/recastnavigation/blob/main/License.txt)
- [BehaviorTree.CPP README](https://github.com/BehaviorTree/BehaviorTree.CPP), [MIT license](https://github.com/BehaviorTree/BehaviorTree.CPP/blob/master/LICENSE), [documentation](https://www.behaviortree.dev/)
- [RVO2 C++ implementation and Apache-2.0 notice](https://github.com/snape/RVO2)
- [[Boost::ext].SML repository](https://github.com/boost-ext/sml)
- Internal [WORLD-03 architecture](../architecture/world-03-spatial-index-streaming.md), [SIM-02 architecture](../architecture/sim-02-physics-3d.md) and [SIM-03 controller API](../contracts/sim-03-character-motor-api.md).

**Research-only limitations:** no source/vendor download, installed SDK, compiled smoke test, license closure/SBOM or headless/crowd benchmark was performed as part of SIM-05.
