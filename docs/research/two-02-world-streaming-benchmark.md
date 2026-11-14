# TWO-02 — Sparse Tilemap Streaming and Collision Benchmark Protocol

**Research #150 | NLE-P00-WO-002-TWO-02 | FUTURE ONLY, NOT EXECUTED.** No editor save, physics activation, resource uploads, video, frame-time, memory or throughput measured.

## Benchmark tracks

1. **Deterministic grid and editor source:** rights-cleared finite/sparse maps, -1/-32/-33 cells, signed16 boundaries (+32768 and -32769) and >2^31 coordinates, 16/32/64 candidate chunk sizes, orthographic and conditional ISO/hex. Validate reversible grid↔world, saved source to restored chunks with same TileId, undo/redo, CAS and journal recovery without dense allocation.
2. **Camera and disk streaming:** fixed seeded camera walk/pan/sprint/teleport, overlapping tall tiles at chunk seams, multiple parallax layers; same scene, atlas, material, viewport and pixel scale. Measure cold/warm DATA-05 loads and chunk corruption/missing asset states, cancellation, hysteresis and no visible seams under known budget.
3. **Physics-safe map editing:** collision-bearing wall on chunk seam; source edit, DATA-04 durable commit, DATA-05 cook, TWO-01 draw and PHYS ack. Never count render ready as collision ready. Under missing chunk or async failure, prove safe interaction gate or last-good barrier, no silent walkable hole.
4. **Interoperability and hostile files:** published Tiled TMX+JSON chunks, orientation/GID top 4 flags, XML/TSX, base64 compressed lengths, LDtk JSON with externalLevels and .ldtkl paths; malformed, duplicate, extreme, missing and path-traversal cases. No third-party game artwork or GPL editor code borrowed. All licenses and maps documented.
5. **Cross-platform comparative study:** actual Win D3D12/Vulkan, Linux Vulkan, macOS Apple Metal, WebGPU and reduced WebGL2; Godot quadrant/coordinate docs and Tiled/LDtk as comparison references only, not assumptions of equal workload or internal access.

## Reproducible measurements and quality gates
- Freeze actual source tree, commit SHA, compiler, codec/parser version and SBOM, OS/GPU/CPU/SSD/browser, licensed tileset hash, map/chunk dimensions, layer count and parallax mode, camera path/seed, GPU/CPU budget, warmup, frame cap and renderer settings.
- Record DATA-05 compressed/decompressed bytes and I/O p50/p95/p99, DATA-04 journal fsync and crash recovery time, CPU culling/cook, GPU sprite uploads/draw+overdraw, camera visible misses/seam count, full-frame CPU/GPU p50/p95/p99, resident bytes GPU/UMA or UNKNOWN, PHYS generation ack delay and missing/corrupt chunk reason.
- Compare performance at equal map correctness and map quality at equal resource cost. Faster streaming by treating collision walls as empty is a **failure**. Native/Web and CPU reference evidence remain separate.
- **SWSP optional PROVE-OR-DROP:** compare speculative camera/actor prefetch against fixed-radius+hysteresis across the same route, measure overfetch and power/CPU overhead versus actual seam/p95 gains. Discard if correctness or reproducibility degrades.
- Deliver original scene sources, scripts/seeds, raw traces and screenshots, device+build SHA, license receipts and exceptions. All evidence is **FUTURE NOT PRODUCED**.

## Primary sources
Tiled: https://docs.mapeditor.org/en/latest/reference/tmx-map-format/
Tiled license: https://github.com/mapeditor/tiled/blob/master/COPYING
LDtk JSON: https://github.com/deepnight/ldtk/blob/master/docs/JSON_DOC.md
Godot comparison: https://docs.godotengine.org/en/4.6/classes/class_tilemaplayer.html
