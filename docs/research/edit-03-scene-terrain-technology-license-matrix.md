# EDIT-03 — Scene/Terrain Technology, License, Threat and Interoperability Matrix

**2026-11-15 | Source-backed P00 RESEARCH ONLY.** All software/frameworks are **comparative candidates**, none installed/imported/chosen/pinned. Engine license **NLE-D009 OPEN** and scene ADR-0055 PROPOSED. Verify exact Git tag, source SPDX/file-level and transitive dependencies, asset rights, platforms, GPU driver, ABI and security record before implementation. Product screenshots/templates from other engines are copyrighted; study behavior, not copy code or imported content.

## 1. Professional architecture references, no source dependency
| Official reference | Relevant architectural observation | Stormline-original alternative and difference |
|---|---|---|
| [Godot 4.6 unique node IDs](https://godotengine.org/releases/4.6/) / [TSCN format](https://github.com/godotengine/godot-docs/blob/master/engine_details/file_formats/tscn.rst) | scene node persistent IDs reduce rename/reparent broken refs; version 4.6 requires resaving existing scenes to benefit | stable WORLD-01 EntityId+generation with DATA-04 serialization; scene paths are not primary identity |
| [Godot EditorUndoRedoManager](https://docs.godotengine.org/en/4.6/classes/class_editorundoredomanager.html) | per-scene history separate from global edit history | typed per-scene undo from real DATA-04 commits, EDIT-01 host layout undo separate |
| [Godot scene inheritance](https://docs.godotengine.org/en/latest/tutorials/assets_pipeline/importing_3d_scenes/import_configuration.html) | editing import-derived scene without destroying reimported source | original prefab instances/overrides with owner-reviewed reconcile, never directly mutate imported asset |
| [Unreal 5.8 World Partition](https://dev.epicgames.com/documentation/en-us/unreal-engine/world-partition-in-unreal-engine) and [One File Per Actor](https://dev.epicgames.com/documentation/en-us/unreal-engine/one-file-per-actor-in-unreal-engine) | streaming cells from one persistent level and actor-specific external authoring files reduce version control collisions | WORLD-04 owns streaming/cells; DATA-04 scene-per-cell/per-actor *candidate*, do not assume no conflict across shared terrain borders |
| [Unreal 5.8 Landscape Edit Layers](https://dev.epicgames.com/documentation/unreal-engine/landscape-edit-layers-in-unreal-engine) | non-destructive height, weight and spline/patch layers with reorder, selective flatten | original layer stack with provenance; destructive bake requires explicit permission and backup |
| [Unity TerrainData](https://github.com/Unity-Technologies/UnityCsReference/blob/master/Modules/Terrain/Public/TerrainData.bindings.cs) | height data, detail/density maps and prototype-layer indexing | original WORLD-04 terrain/foliage ownership, brush mask and stable layer IDs independent from array order |
| [OpenUSD layers](https://docs.nvidia.com/learn-openusd/latest/composition-basics/layers.html) and [instance edit targets](https://docs.omniverse.nvidia.com/usd/latest/learn-openusd/independent/modularity-guide/instancing.html) | compositions/overrides can be non-destructive but instance prototypes are implicit, cannot be edited like ordinary source | explicit source vs instance override, edit-source confirmation, ID/diff, future optional USD adapter |

**License caveat:** Epic's [Unreal Engine EULA](https://www.unrealengine.com/eula/unreal) imposes licensing and editor-tool distribution restrictions; publicly available Unreal docs or sample projects do **not** grant permissive rights to copy Unreal Editor source/branding/paid Marketplace art into Stormline.

## 2. Potential third-party components and exact license facts (not installed)
| Candidate and authoritative upstream | Current license (must verify pinned release) | Potential role vs avoid false claims |
|---|---|---|
| [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo/blob/master/LICENSE) | **MIT** | C++ transform/pivot gizmo atop Dear ImGui, prototype only; matrix decomposition, coordinate conventions, accessibility, mouse capture and multi-selection must be independently proven. |
| [Dear ImGui](https://github.com/ocornut/imgui/blob/master/LICENSE.txt) | **MIT** | editor shell candidate under EDIT-01 ADR-0053; docking/multi-viewport support branch specifics, not automatically native a11y/complex IME |
| [meshoptimizer](https://github.com/zeux/meshoptimizer/blob/master/LICENSE.md) | **MIT** | GFX/WORLD mesh simplification, LOD and compact runtime data, not owner of scene source, terrain deltas or authoring identity; experimental APIs need pin |
| [Assimp](https://github.com/assimp/assimp) | main code **modified BSD-3-Clause**, bundled contributors/formats/sample assets have other rights | future import pipeline belongs DATA-03/EDIT-02, not default source-native scene; third-party licenses and model files must be tracked separately |
| [OpenUSD current dev LICENSE](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt) | **Tomorrow Open Source Technology License 1.0** (different trademark `6 vs Apache 2.0), many bundled 3P licenses | optional USD scene interop/composition, NOT selected default scene format or "plain Apache-2.0" |
| [OpenVDB](https://www.openvdb.org/license/index.html) | **MPL-2.0**, file-based copyleft and 3P obligations | potential volumetric tiles/cave editing after WORLD-04 model; **heightfield mode cannot do overhangs**, no need first slice |
| [FastNoise2](https://github.com/Auburn/FastNoise2/blob/master/LICENSE) | **MIT** | deterministic procedural noise candidate for WORLD-05, version/seed/vector ISA must be pinned for reproducibility, not automatic terrain authoring backend |
| [OpenImageIO 3.x copyright](https://openimageio.readthedocs.io/en/stable/copyr.html) | **Apache-2.0** for new/relicensed code; remaining small legacy **BSD-3-Clause** and independent dependencies | external texture/heightmap import backend candidate, still need decompression/dimensions/stride quotas |
| [Recast Navigation](https://github.com/recastnavigation/recastnavigation/blob/main/License.txt) | **zlib** | terrain navigation export integration owned world/nav module if cataloged, no editor navmesh authority here |
| [3D Tiles specification](https://github.com/CesiumGS/3d-tiles/blob/main/specification/README.adoc) | open specification distinct from SDK/service/content rights | hierarchical streaming/reference for huge worlds, optional geospatial adapter, not mandatory offline terrain runtime |
| [Cesium World Terrain](https://cesium.com/platform/cesium-ion/content/cesium-world-terrain) | hosted world-data service **requires separate account/usage/content licensing** | NEVER assume free commercial worldwide dataset can be embedded in Stormline, no automatic paid/cloud fallback |
| own typed scene/prefab/terrain editor abstractions | engine source license OPEN, no third-party import | **leading architectural proposal**, protects module authority but implementation/perf/accessibility must be proven |

## 3. Rendering, data structures and backend options
| Axis | Candidate | Future decision proof |
|---|---|---|
| scene layout | one scene file + hierarchical refs / split external actor documents / per streaming cell documents | DATA-04 schema/merge/diff, VFS source-control conflict and recovery, not implicit OFPA import |
| hierarchy | WORLD-01 ECS object projection and typed stable refs | 1k/10k/100k nodes virtualized, O(visible) UI and safe stale entity generation |
| picking | GFX ID-buffer async readback / CPU BVH raycast / hybrid | stale GPU epoch/cell selection rejected, transparent/hidden object policy, exact origin transforms |
| gizmos | Stormline original semantic math with optional ImGuizmo front-end | correctly handle singular/negative scale, parent inverse, numeric keyboard input and undo group |
| prefab | original flattened canonical entity graph with overlay patch / external USD composition | stable nested source+instance IDs and override conflicts, reject cycles; avoid OS/path identity |
| terrain | WORLD-04 tiled heightfield + non-destructive layers / mesh terrain / voxel future | seams/holes, LOD, limits; caves need separate topology; no stolen UE asset/sample |
| large world | fixed grid/quadtree, hierarchical HLOD, floating origin, double world coords | streaming dirty cells keep durable edits, origin rebasing/picking accuracy |
| procedural | deterministic seed+version graph from WORLD-05 | manual layer untouched after regenerate, independent CPU canonical vs GPU preview tolerance |
| persistence | DATA-04 serializer with CAS/journal and DATA-01 VFS | multi-file durability after process/power fault, source refs after restart; no "single rename means ACID" |
| OS/editor | EDIT-01 UI backend candidate Qt Widgets vs Dear ImGui; X11/Wayland/macOS | actual keyboard/IME/accessibility/UIA/AX/AT-SPI, GPU device loss and multi-monitor real builds |

## 4. Security, licensing, privacy threat register
| Threat | Security boundary | Proposed mitigation / test evidence FUTURE |
|---|---|---|
| malformed huge hierarchy, recursive prefab cycle | CORE-05/DATA-04 deserialize | bounded nodes/depth/refs, versioned schema, reject before allocation |
| stale entity and generation reuse, GPU pick after cell unload | WORLD-01/GFX picker | opaque EntityId+generation+revision+frame epoch check |
| gizmo NaN, zero scale, self-parent, parent-child double transform | WORLD transform and command handler | finite math, reject singular inverse, stable pivot/space validation |
| rogue asset path, symlink/sandbox escape, malicious importer code | DATA-01/DATA-02/03 | scoped granted VFS root, no arbitrary plugin native sandbox assumption |
| malicious heightmap dimensions/decompression bomb/texture stride | WORLD-04/DATA import | pre-allocation height/width/byte limits, runtime bounded decode |
| prefab override silently lost on source reimport | DATA-04/Data-02 | semantic three-way merge and explicit conflict, preserve original source |
| terrain bakes erase authored layer or overflow disk | WORLD-04/DATA-04 | non-destructive source snapshot, bounded delta, recoverable commit |
| cross-cell neighbors desync/seams, LOD crack | WORLD-04/GFX | neighbor halo, stitch, deterministic cross-tile tests |
| misused AI/MCP automation, expensive batch edits | EDIT-03 semantic authorizer / DATA-04 CAS | preview/cell scope/explicit destructive consent, budget and rollback |
| privileged plugin can inject executable native code | editor plugin host and QA-04 | process isolation/review, signed manifest by future owner, no "capability list implies native sandbox" |
| other player's/private project source revealed in preview/log | DATA-04/CORE-06 | redact private paths/asset provenance, permit only scoped data |
| copyrighted UE content, samples, brushes, fonts or trademark | asset distribution legal owner | original assets, per-file license and author permission; engine EULA not MIT |
| cloud/world terrain paid service or tracking | operator + service connector | opt-in review, license, privacy, budget, no automatic network |
| future collaboration conflict/corruption | DATA-04/source CAS | local lease first, stale writes denied, remote merge deferred |
| false cross-platform claims | OS/GFX native target | native tests Windows/Linux/macOS, screen reader and power failure proof |

## 5. Actual status / adoption gate
Only official docs/specs and existing repo are evaluated. **Nothing downloaded/installed, no third-party code or sample art imported, no synthetic terrain generated, no runtime code built.** All 128 E03 tests FUTURE/NOT EXECUTED; perf figures and compatible OS targets not measured. Owner must approve NLE-D009 source license, ADR-0055, actual types/schemas/SDK version, security and source rights, DoD and risk before execution. No change to the 80 blocked work orders.
