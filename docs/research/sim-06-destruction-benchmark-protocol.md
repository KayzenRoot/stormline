# SIM-06 — Destruction, Debris, Terrain and VFX Reproducible Benchmark Protocol

**Status: FUTURE-ONLY RESEARCH DESIGN, ZERO MEASUREMENTS** | #189 | WO NLE-P00-WO-002-SIM-06 | 2026-11-14

## 1. Benchmark questions
How many verified **authoritative rigid bodies**, chunk bonds and concurrent impacts can Stormline manage while sustaining bounded CPU/memory latency and no false collisions? Does prefractured geometry produce acceptable interior geometry and believable material-specific patterns at low cook cost? Do GPU cosmetic shards/dust improve visuals without changing gameplay physics? Does an interrupted terrain/collider/nav rebuild always preserve physically safe source and leave a recoverable state?

## 2. Original future fixtures (not created now)
- **DEST-WALL1:** original stone wall, 2 m wide, 16/64/256 author-generated fracture candidates, strong/weak bonds, authored interior surface material, two collider LODs and one stable floor/character support.
- **DEST-GLASS1:** glass plate/panes with 128 proposed visual shards but bounded SIM-02 active bodies; correct normal, material, lit PBR and decal surface attachment.
- **DEST-WOOD1:** wooden pillars/beams with directed split grain, stair/ramp support and 2-agent NPC NAV corridor.
- **DEST-TERRAIN1:** originally authored 128 m region with a bridge/cave/crater-ready section and versioned WORLD-03 cells; damage hole must trigger SIM-02 collider and SIM-05 nav coordination.
- **DEST-CROWD1:** 100 targets/agents with 10/100 impact-per-tick workloads, GFX-08 dust/sparks while the authoritative server is headless. Cosmetic rates do not alter gameplay.
- **DEST-FAULT1:** corrupt and oversized geometry, huge chunk count, negative force, forged actor, stale source/OriginEpoch, cell unloading, interrupted PHYS/nav commit and crash halfway through DATA-04 persisted structural journal.
- **DEST-2D:** original 2D wall/prop break pattern and 2.5D hybrid translucent dust and crack marks where 3D rigid body is not silently substituted for 2D physics.

All assets future **original authored** with source hash, generation seed, units, profile, declared rights and redistributable fixture manifest. No third-party game/fracture samples copied. No fixture is currently present.

## 3. Benchmark matrix
| Profile | Workload | Measurements and correctness |
|---|---|---|
| Offline authoring | 16/64/256 chunk Voronoi and reference pre-bake on legal source | cook wall CPU, peak memory, asset bytes, manifold/volume/UV/collider accuracy, user-visible artist control |
| Single prop | 1/16/64 dynamic major chunks + 1024 cosmetic visual shards | CPU SIM-02 cost, contact pairs, GFX-08/GFX-03 GPU ms and VRAM, culling vs authoritative bodies |
| Impact swarm | 10/100/1000 hits under different tick policies and quotas | event queue latency, tick p50/p95/p99, bond decision time, active chunk cap and rejected statuses |
| Streaming topology | remove bridge/wall while camera and NPC traverse tiles | PHYS+WORLD+SIM-05 ACK p95/p99, nav/collider unavailability, no false grounded/traversable state |
| Persistence | 100 edits/snapshots across reload, rebase and artificial crash | byte growth/CPU, recovery time, stable IDs/source hashes, rollback truth |
| VFX tiers | static damage vs low particle vs high density with same GAME hit log | CPU/headless structural parity, GPU/VRAM/p95/p99 visual time, readable cinematics |
| Stress/endurance | 1-hour cyclic load/unload/origin-shift with constrained heap | memory growth, dangling handles, race/sanitizer failures, asset leaks and fairness |
| Portability | native Win/Linux/macOS and optional Web/WASM CPU/graphics capabilities | actual compile/run, allowed numerical tolerance, feature fallback, no implicit CUDA dependency |

## 4. Instrumentation and method
Pin exact main/head SHA, source copyright/rights and geometry hashes, toolchain/compiler/linker/architecture, vendor versions and LICENSE + full SBOM, physics backend settings, nav/stream source revisions, CORE-04 tick rate/rational numeric profile and canonical EventId order. Measure N repeated warm/cold trials with thermals/power state and GPU settings recorded. Report p50/p95/p99 and peak allocation/VRAM, error bars/variance with failed and aborted runs included, not selected samples.
For a real comparison to NVIDIA Blast or proprietary engines, use matched original scene, comparable collision/VFX quality, identical hardware and explicit licensed versions; **no superiority without proof**.
Quality rubric future blind panel: convincing fracture material, contact force response, silhouette/volume conservation, no unlit interior, dust layering, performance-tier parity, broken bridge nav and terrain hole collision truth. Separation of structural and cosmetic body counts, persistent marks and true game damage must be auditable.

## 5. Acceptance thresholds and future release gates
Targets for p95/p99 CPU ms, max bodies per cell/second, max VFX VRAM, collision topology publish latency, cook throughput and visual quality are **NOT FIXED** until measured baseline with real hardware/gameplay. Safety invariants are logical requirements to test, not present PASS: stale/unknown terrain never knowingly traversable, no GPU-cosmetic collision authority, no unauthorized damage or broken revision recovery.
Future Evidence Bundle must include build/test commands, fixtures, outputs/screenshots/frame captures, traces, data provenance, min/mean/max/error, sanitizers/fuzz/permission results, replay/rollback, missed event/physics defects and objective verdict. This P00 research executes **none** of them.
