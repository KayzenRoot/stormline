# TWO-02 — Tilemap, Authoring Tools and Streaming Technology Matrix

**Research issue #150 | WO NLE-P00-WO-002-TWO-02 | PROPOSED ONLY**. Technologies are research candidates, **no tool/library/asset integrated, installed or license frozen**.

| Candidate | Class | Portability / quality constraints | Licensing / provenance | Future proof |
|---|---|---|---|---|
| Own versioned sparse chunk TileMapAsset and 64-bit grid | NECESSARY | negative coordinates, safe rebase, floor div, per-cell chunk and world caps | original, no source imported | 64-bit far tiles and deterministic roundtrip |
| Own chunk streaming/culling planner | NECESSARY | DATA-05 job/cache, GFX-03 fence, CPU/WebGL2 baseline | original, no duplicate I/O pipeline | no seam/pop, bounded p95 frame and bytes |
| Orthogonal square/rect grid | NECESSARY | exact pixel/physical/project-space to TWO-01 Canvas | original | paint/save/reload and collision metadata |
| Isometric/staggered/hex projection | IMPORTANT optional | distinct orientation, transform/flip and tie-break, physics shape mapping | original algorithms after reference check | visual/collision cell inverse |
| Tiled TMX / JSON map format importer | IMPORTANT compatibility | infinite chunks, XML/JSON/CSV, base64 zlib/gzip/zstd, external TSX | published format, imported art rights separate | secure read-only import, no editor linked |
| Tiled editor itself | REFERENCE external authoring only | GPL editor/plugins, JS automation, not required commercial runtime | GPL per upstream COPYING; **not blanket MIT** | compare native editor parity; NO GPL embedding |
| libtiled / tmxrasterizer | OPTIONAL parser/cook candidate | C++ Qt/deps/ABI and exact module subset, Web compatibility unproved | **BSD-2-Clause** for `src/libtiled` and rasterizer in upstream COPYING, transitive Qt license separately | dependency/binary/SBOM vs own parser |
| Tiled 32-bit global GID encoding | NECESSARY for import | four high flag bits, orientation-specific hex flips, map-local GID | format, not stable TileId | bit flags, negative chunks and tilesets |
| Tiled Wang/terrain sets | IMPORTANT optional import rules | edge and corner constraints, tile variation, cross-chunk updates | Tiled script extensions not imported | deterministic terrain seams |
| LDtk editor and JSON 1.5.3 | IMPORTANT compatibility | MIT editor, JSON/iid/world/level .ldtkl external files, auto layers | MIT code, content/files/art rights separate | external path sandbox/auto layers |
| LDtk AutoLayers vs Tiled Wang | IMPORTANT lossy conversion gate | rulesets not equivalent, report incompatibility | no copied proprietary tile art | explicit limitations |
| Godot 4.6 TileMapLayer | REFERENCE only | renderer/physics quadrant batching, signed-16 serialized coords limit | Godot MIT engine, **no source copied** | far-world regression & cross-chunk |
| Rect/polygon collision metadata | NECESSARY authoring contract | PHYS owns broadphase/contact, revision and safe activation | original typed geometry and rights | visual/physics matching after reload |
| Nav grids/waypoints/pathfinding | FUTURE external module | no TWO-02 navigation simulator | WORLD/NAV owner | nav contract later, no hidden code |
| Chunk DB/page index / compression zstd | IMPORTANT candidate | DATA-04/05 must own storage, integrity, max inflate limits | exact zstd license/deps/supply chain review | bytes, corruption recovery |
| Parallax layers / infinite-repeat | NECESSARY rendering candidate | camera scale, negative scroll, seam, pixel art, TWO-01 alpha order | original | native/Web parallax golden |
| Tile animation | IMPORTANT integration only | refer TWO-03 timeline, no animator duplicated | existing tile art rights | frame ID/revision match |
| Runtime procedural terrain generator | FUTURE optional | RNG deterministic, content rules and network safety | own code, no mandatory plugin | only if approved scope |
| SWSP speculative chunk prefetch | OPTIONAL PROVE-OR-DROP | extra I/O/CPU/overfetch, correctness baseline never sacrificed | hypothesis, not proven novel | p95 and seam Pareto versus fixed ring |

## Hard license and security caveats
- Tiled's upstream `COPYING` explicitly distinguishes GPL `src/tiled` and plugins from BSD-2-Clause `src/libtiled` and `tmxrasterizer`. Using public TMX/JSON file compatibility does NOT imply copying GPL editor code, and editor license alone doesn't automatically license a user's exported map artwork. Integration of libtiled needs actual code, dependency and Qt licensing scan.
- LDtk source under MIT, but its level art/assets and map content are licensed independently. `.ldtk` project may refer to external `.ldtkl` levels and images; path traversal/remote fetch/symlink escape prohibited.
- Tiled global 32-bit GID top FOUR flag bits encode flip/hex rotation; strip all four bits and resolve `firstgid` per map, not as stable engine tile id. Import negative chunk coordinates; ensure exact little-endian and inflate-length checks. XML/JSON scripts/typed custom properties are **data only**, never evaluated.
- Godot TileMapLayer documented 16-bit signed serialized coords, so use full signed 64-bit logical cells in Stormline canonical format and test `-32769`, `+32768`, `>2^31` with memory/device/GPU coordinate bounds; no claim infinite GPU precision.
- Saving a map and rendering it is not physics synchronization. Collision metadata must become acknowledged PHYS shape generation before marking critical chunk safe, otherwise an unloaded wall could allow unintended traversal.
- Streaming performance cannot be extrapolated from engine docs or from using zstd/mesh batching: benchmark real original fixtures, disk cache, device memory and p99. No binary/test artifact has been downloaded or created.

## Official and primary technical sources (research, not integrated)
- Tiled editor current capabilities/infinite maps/auto tiling: https://www.mapeditor.org/
- Tiled upstream distinct license inventory (GPL editor, BSD-2-Clause libtiled): https://github.com/mapeditor/tiled/blob/master/COPYING
- Tiled TMX map chunks, compression options: https://docs.mapeditor.org/en/latest/reference/tmx-map-format/
- Tiled JSON tilemap/tileset source: https://github.com/mapeditor/tiled/blob/master/docs/reference/json-map-format.rst
- Tiled Global Tile IDs 4 flag bits and hex rotation: https://docs.mapeditor.org/en/stable/reference/global-tile-ids/
- Tiled Wang Sets / terrains, procedural painting: https://docs.mapeditor.org/en/stable/manual/terrain/
- LDtk MIT LICENSE: https://github.com/deepnight/ldtk/blob/master/LICENSE
- LDtk JSON spec with optional separate .ldtkl levels and stable IID: https://github.com/deepnight/ldtk/blob/master/docs/JSON_DOC.md
- Godot 4.6 TileMapLayer batching/collision quadrant, serialized signed-16 cell-coordinate limitation: https://docs.godotengine.org/en/4.6/classes/class_tilemaplayer.html
- W3C WebGPU constraints and device capability negotiation: https://www.w3.org/TR/webgpu/
