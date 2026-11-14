# WORLD-03 — Spatial Structures, Streaming Frameworks, Formats and License Matrix

**Research #165 | NLE-P00-WO-002-WORLD-03 | ADR-0028 PROPOSED**. This is a design/license survey, no dependency pinned or installed and no measured world-streaming performance.

| Candidate/method | Classification | Technical, accuracy and portability tradeoff | Rights / license status | Future proof |
|---|---|---|---|---|
| Sparse hashed grid of canonical global `CellId` (2D/3D) | NECESSARY primary coarse streaming candidate | cheap cell lookup, poor for giant spanning objects/nonuniform worlds, negative-coordinate and adversarial hash limits | original algorithm, no vendor source | correct border/giant objects and memory/fanout |
| Loose dynamic BVH/AABB tree for local loaded-cell interest | IMPORTANT candidate | fast broadphase candidate sets, maintenance under high churn; NOT PHYS solver or GFX occlusion | original or future authorized adapter | oracle exact-vs-candidate, update p99 |
| Hierarchical loose octree/quadtree | IMPORTANT alternate | handles disparate sizes and vertical density, update/rebalance complexity/overlap | original algorithm plan | clustered/wide uneven scene quality |
| Boost.Geometry.Index R-tree/R*-tree | OPTIONAL C++ index adapter | R-tree query/intersection/nearest; dependencies Boost.Container/Core/Move/MPL/Range/Tuple, balancing affects insert/query perf | **Boost Software License 1.0**, exact package notices needed | compiler/Web builds, update/queries under churn |
| libspatialindex R*-tree / MVRT / TPR | OPTIONAL C++ index adapter | richer spatial/tree variants, potential footprint/disk serialization duplication DATA-05 | **MIT since 1.8.0**, prior to 1.8.0 **LGPL** according to upstream COPYING, must pin and verify | exact release license, memory/time vs baseline |
| GPU meshlet/frustum occlusion culling | OUT OF SCOPE WORLD-03 | belongs GFX-04, consumed as visibility receipt | GFX-04, GPU backend owners | no second culler or GPU code |
| HLOD and terrain mesh streaming | FUTURE GFX-04 / WORLD-04 | visual LOD/popping, need separate gameplay collision policy | owner renderer/terrain; not this code | image/frame physical proof |
| DATA-05 I/O + cook + decode/cache orchestrator | NECESSARY integration, NOT runtime copy | async returns safe staged cells, asset hashes/dependency ownership, decompression caps | DATA-05 owner | cancel/rollback/integrity/lease correctness |
| Zstandard compressed cooked bundles | OPTIONAL DATA-05 technology | fast decode for bundles, decompression bombs and platform packaging | reference lib **BSD** (Zstd official), exact pin/license/SBOM after decision | size/fetch/decode/main stall vs no compression |
| Unreal Engine 5.8 World Partition/Data Layers | REFERENCE ONLY | automatic grid cells and distance streaming, streaming sources, HLOD/data layers, platform/editor system | **Unreal/Epic proprietary engine terms**, no code/assets copied | clean-room original scene comparison |
| Godot 4.6 HLOD visibility ranges/large world coordinates | REFERENCE ONLY | range hysteresis, per-node LOD and 64-bit precision trade-offs; 2D double precision caveats | **Godot MIT** core, original art rights independent | camera/origin error and LOD shift baseline |
| Unity Addressables 2.x | REFERENCE ONLY | async dependency loading handles and release; not a world spatial index by itself | **Unity proprietary package/editor terms**, no code/assets copied | cancellation/refcount/IO fault comparison |
| OGC 3D Tiles 1.1 implicit hierarchy and geospatial payloads | OPTIONAL FUTURE interoperability only | public streaming standard for massive geospatial 3D, coordinate/extension requirements; not default game world format | public OGC standard, not SDK/license of a vendor client nor free art | rights/format importer and Web geometries |
| `SIP` heuristic/prediction | OPTIONAL PROVE-OR-DROP | speculative prefetch may raise cache misses/VRAM and amplify malicious interest | research hypothesis only | miss rate vs velocity baseline at equal correctness/memory |

## Copyright, source and feature correctness
- Boost.Geometry docs identify an R-tree implementation with balancing options and dependencies; its published microbenchmarks use old hardware/datasets and **are not Stormline measurements**. Pin exact Boost version, compiler, transitive packages and notices if adopted. License is Boost Software License 1.0.
- libspatialindex upstream COPYING explicitly states **MIT since release 1.8.0**, earlier LGPL, not “all versions MIT.” An upstream R-tree is not necessarily right for dynamic scene cell aggregation, and its disk storage is not automatically the DATA-05 source format.
- Zstandard official reference library BSD and stable format RFC 8878. **No zstd package installed in WORLD-03**. Compression and decompression control belong to DATA-05, with independent content-rights and decompression-size policy.
- Epic Unreal World Partition, Unity Addressables are **vendor/proprietary implementation references**, not licensed code to copy, and their assets/benchmark levels may not be redistributed. Godot HLOD and large-world docs under MIT engine reference, not a claim of precision equivalence.
- OGC 3D Tiles 1.1 specification is a public interoperability standard for geospatial streaming. The standard itself does not grant distribution rights to sample tile datasets, code libraries, map imagery or private terrain. A normal offline game does not require 3D Tiles.
- Coordinate system (absolute global / local GPU float and world epoch), asset hash, memory/fence/lease and authority ownership are non-negotiable for stable semantic API even if index/backend is swapped. No mandatory paid tool, runtime or vendor engine chosen.
- No throughput, stall-free, frame p99, million cells, no jitter or network interoperability performance has been verified in this documentation phase.

## Official, version-sensitive reference documents (not vendor code or adopted runtime)
- Epic Unreal Engine 5.8 World Partition, cells and streaming sources: https://dev.epicgames.com/documentation/en-us/unreal-engine/world-partition-in-unreal-engine
- Godot 4.6 visibility ranges / HLOD and hysteresis: https://docs.godotengine.org/en/4.6/tutorials/3d/visibility_ranges.html
- Godot 4.6 large world coordinate limits and double precision/origin-shifting tradeoffs: https://docs.godotengine.org/en/4.6/tutorials/physics/large_world_coordinates.html
- Boost.Geometry spatial R-tree tradeoffs: https://www.boost.org/latest/libs/geometry/doc/html/geometry/spatial_indexes/introduction.html
- Boost Software License 1.0: https://live.boost.org/users/license.html
- libspatialindex COPYING license: https://github.com/libspatialindex/libspatialindex/blob/main/COPYING (MIT since >=1.8.0, earlier LGPL)
- Unity Addressables asynchronous load and dependency lifecycle overview (proprietary reference): https://docs.unity3d.com/cn/current/Manual/com.unity.addressables.html
- OGC 3D Tiles 1.1 public hierarchical geospatial standard, optional future interoperability: https://www.ogc.org/standards/3DTiles/
- Zstandard public format RFC 8878 / BSD-licensed reference library, DATA-05 owner only: https://facebook.github.io/zstd/
