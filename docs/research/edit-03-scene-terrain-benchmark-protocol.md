# EDIT-03 — Reproducible Scene, Gizmo, Prefab, Terrain, Streaming and Recovery Benchmark Protocol

**2026-11-15 | P00 PROTOCOL ONLY, NOT RUN.** There is no native editor, GFX/WORLD/DATA source engine, terrain fixture executor, simulated power failure, GPU screenshot or actual frame timing. All E03-T001..128 **FUTURE / NOT EXECUTED**, and no p50/p95/p99, benchmark winner, FPS/CCU/performance or Windows/Linux/macOS feature support has been measured.

## 1. Hypotheses and non-negotiable correctness
H1: one semantic scene transaction path with DATA-04 CAS can preserve hierarchy, multi-object inspector and transform edits across save/undo/reopen; hierarchy and GPU viewport are projections, not second source of truth. H2: nested prefab source + instance overrides rebase without silent overwrite, with typed conflicts. H3: bounded heightfield brush/layer deltas plus deterministic seed reproduce same terrain source state and seam continuity while GPU preview remains disposable. H4: dirty streaming cells never unload without durable state/recovery; GFX device loss leaves source intact. H5: keyboard/screen-reader and AI/MCP typed capability checks reject invalid/destructive edits as GUI. H6: dynamic performance scales with visible nodes and dirty tiles rather than all authored world history, after real baseline.

## 2. Immutable future manifest
`SceneTerrainBenchmarkManifestV1` contains Git base/head/build SHA, owner-approved ADR/DoD, OS+FS Windows NTFS/macOS APFS/Linux ext4/Btrfs X11/Wayland where meaningful, CPU/cores/RAM/GPU VRAM/driver RHI and DPI, editor toolkit tag/NOTICE and third-party license, source ProjectId/SceneId/WorldCellId/AssetId and DATA-04 schema/version/hash, WORLD-01 EntityId generation, WORLD-04 terrain cell size/layer schema/height unit/quantization/tile halo, procedural seed and input sampling rate, GFX viewport resolution and render graph, first-party original mesh/texture/heightmap fixture provenance, scene object/terrain tile counts, marker for loaded/dirty, undo history cap, controlled UI input/keyboard/IME, memory/IO and GPU counters, frame/pick/brush latency p50/p95/p99 and percentile calculation, safe synthetic fault seed/process kill phase/recovery source hashes, exact commands/repeats, redacted CI/trace and independent pt-BR objective auditor.

## 3. Candidate workload axes (NOT capacity or target FPS promises)
| Case | Synthetic fixture variables | Future measured outputs and correctness |
|---|---|---|
| SCENE01_HIERARCHY | 100, 1k, 10k, 100k synthetic nodes, varying depth and tags | tree query/filter/expand time; stable IDs, no unbounded main-thread stalls |
| SCENE02_SELECT | 1/10/100/1k selected nodes and mixed component classes | inspector reflection CPU, batch validation, no partial undesired edits |
| SCENE03_TRANSFORM | nested 1/16/64 levels, negative/nonuniform scales, origin shift | numeric transform error tolerance, snap precision, CAS and single undo |
| SCENE04_PICK | 2D/3D viewport 720p/1080p/4k synthetic IDs, device epoch changes | selection accuracy, async readback latency, stale results rejected |
| SCENE05_UNDO | 1/100/1k semantic transactions and deliberate conflict | history memory/CPU, redo determinism after real scene reopen |
| SCENE06_PREFAB | 2/16/128 instances; shallow/deep nested variants, source reimport | composition/rebase time, invalid cycles denied, unchanged siblings |
| SCENE07_TERRAIN | 16/64/256 synthetic height tiles, fixed brush kernel/seeds | sample throughput, source tile hashes and seam/halo differences |
| SCENE08_LAYERS | 1/4/16 layer stacks height/weight/foliage/holes | composition cost, GPU preview/source divergence, reversible bake |
| SCENE09_FOLIAGE | 1k/100k/1M synthetic foliage records, sparse vs dense | memory, streaming, stable IDs, GPU buffer rebuild |
| SCENE10_STREAM | 4/16/64 loaded dirty tiles, LOD switch, camera sweep | budgeted load/unload, no data loss and neighbor stitch correctness |
| SCENE11_SAVE | scene/prefab/terrain multi-file delta 1/10/100 files | staged write CAS and fresh reopen hashes, I/O throughput |
| SCENE12_RECOVERY | kill before/after staged preview/commit/journal receipt | idempotent restart/undo and original committed files intact |
| SCENE13_GPU | viewport resizing, device loss, render-late and hidden surface | editor latency and source preservation, no stale pick |
| SCENE14_ACCESS | keyboard-only hierarchy/inspector, screen readers and RTL/IME | real UIA/AX/AT-SPI focus and accurate semantic control |
| SCENE15_SECURITY | malformed prefab cycle/scene count/heightmap/asset URI | bounded reject, no path escape, GPU/CPU resource quotas |
| SCENE16_MULTI_OS | Windows/macOS/Linux 2D and 3D+terrain with actual hardware | platform-owned input/FS/driver differences, correct source replay |

**Counts are workload axes only, not accepted supported limits or performance goals.** Actual p95/p99/FPS/VRAM/asset limits and representative hardware set by owner after a truthful native baseline. No promise to sustain 1M real vegetation records or 4k with a particular GPU.

## 4. Reproducible procedure
1. Set up a **disposable synthetic local project** with original assets and granted DATA-01 root, pinned WORLD-01/04, GFX, DATA-02/04 versions, license SBOM and GPU/driver/OS. Deny unauthorized scripts, production projects or external services.
2. Run independent scene hierarchy/gizmo/reflection path with zero mutation before commit; record SceneId/EntityId/parent graph source hashes, transaction receipts, after commit save/reopen/undo/redo source hashes and user-visible output. Verify nested parent numeric matrix math after origin rebasing with finite tolerances.
3. Prefab source/instance override, reimport/rebase, missing source and cycles. Check **all** sibling instances, provenance, instance child references, no silent loss. Use three-way diff and explicitly fail bad conflicts.
4. Terrain stroke fixed world-space samples, seed and parameter schema at border of two cells, record canonical height/mask/layer tile hashes, reconstructed CPU reference and GPU preview divergence. Reorder layers, switch LOD, regenerate WORLD-05 base, verify manual source untouched.
5. Stream and device loss while brush pending and dirty tile, measure loaded cell residency, memory+VRAM and source recovery. GPU readback after cell unload/device generation must never select stale actor.
6. Controlled synthetic crash at each transaction point on disposable VM/root. Restart new process, re-open via DATA-04 and compare files, include idempotent receipt replay; don't conflate **process kill** with physical **power durability**. Power-fault tests only on own safe FS harness after approval.
7. Accessibility actual Windows UI Automation/NVDA, macOS AX/VoiceOver, Linux AT-SPI/Orca, keyboard numeric controls, CJK IME and high-DPI/multi-monitor; mock accessibility metadata isn't full proof. Compare 2D canvas ownership EDIT-04 separate from generic scene shell.
8. Measure disjoint durations editor input-to-preview, picking, CPU semantic commit, DATA-04 flush, world streaming/LOD, GFX GPU present; warmup and repeated samples with OS/power/temp/driver control. Output p50/p95/p99 only when repeated real data exists. Stop on HIGH/CRITICAL corruption, path escape, unreviewed SDK rights, missing scene serializer, failed access grants, mis-rebased prefabs or render loss without source preservation.

## 5. Source/license and P00 truth
Comparative references [Godot 4.6 scene unique IDs](https://godotengine.org/releases/4.6/), [Unreal World Partition](https://dev.epicgames.com/documentation/en-us/unreal-engine/world-partition-in-unreal-engine), [Unreal Landscape Layers](https://dev.epicgames.com/documentation/unreal-engine/landscape-edit-layers-in-unreal-engine) and [OpenUSD layers](https://docs.nvidia.com/learn-openusd/latest/composition-basics/layers.html). Library candidates [ImGuizmo MIT](https://github.com/CedricGuillemet/ImGuizmo/blob/master/LICENSE), [meshoptimizer MIT](https://github.com/zeux/meshoptimizer/blob/master/LICENSE.md), [OpenVDB MPL-2](https://www.openvdb.org/license/index.html), [OpenUSD Tomorrow license](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt), no downloads or source selection.

**Zero benchmark executed, zero actual scene/heightfield edited/saved, no FPS, GFX loss or OS a11y measured; ALL 128 tests FUTURE/NOT EXECUTED.** Only future implementation with independent proof can satisfy the catalog acceptance.
