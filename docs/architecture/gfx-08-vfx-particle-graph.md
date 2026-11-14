# GFX-08 — Stormline VFX & Particle Graph: Portable Cinematic Effects

**WO:** NLE-P00-WO-002-GFX-08 | **Research issue:** #144 | **Future implementation #36:** BLOCKED  
**BASE main:** `729f111d30fe927107f42fe6e4b951d17f357e10` | **Status:** RESEARCH PROPOSED / DOCS ONLY. **No C++, GPU particles, shader, effects asset, FPS result or demo exists.**

## 1. Goal
Own a versioned artist and AI-authorable effect graph producing highly readable, spectacular ARPG combat magic, explosions, sparks, trails, ribbon spells, particles, debris-like cosmetic objects, fog density, sprite FX, 2D/2.5D lighting and 3D effects on Windows/Linux/macOS/Web. Visual beauty is subject to measured p50/p95/p99 CPU/GPU/VRAM and quality; no “better than Unreal/GGG” claim without matched fixtures.

### Prime invariants
1. **Cosmetic only**: damage, hit validation, combat RNG, vehicle physics, server authority and network state are decided upstream by gameplay/physics/network systems. GPU simulation never becomes gameplay-authoritative or a source of authoritative collisions.
2. **Stable IDs and deterministic intents**: authored VFX asset revision/instance handle, spawn seed, tick-based emitter events with reproducible reference CPU simulation for repeatable validation. Floating point GPU across vendor backends is not promised bit-exact deterministic; CPU/GPU visual equivalence tolerances must be frozen.
3. **Bounded work**: max emitters/particles/spawn per tick, graph complexity, recursion depth, trail vertices, ribbon segments, sorting/transparent overlap, draw batches, texture atlas usage, GPU memory, compute dispatches and expensive light emission. No infinite burst or unbounded subemitters.
4. **Safe display**: scene-linear HDR and GFX-07 reactive/motion/depth semantics; preserve UI readability, reduced-flash/reduced-motion, non-punitive light attenuation, and 2D pixel-art mode.
5. **Portable fallback**: CPU reference + bounded instanced billboard/mesh render path, no mandatory compute, sort, opaque proprietary SDK or ray tracing. GPU compute path optional where feature-proved.

## 2. Ownership and module contracts (NO duplicate subsystems)
| Owner | Owns / VFX consumes |
|---|---|
| CORE-03/04/05/06 | jobs, fixed-step and pause/simulation tick, origin/coordinate math, diagnostic trace |
| DATA-01/02/03/04/05 | VFX asset ID/revision/provenance, signed/allowed source files, image/mesh/SDF/VDB import validation, serializable graph edits/journal, cooked target format/LOD, asset streaming and recovery |
| GFX-01 | device capabilities Vulkan/DX12/Metal/WebGPU/WebGL2 and device-generation handles |
| GFX-02 | shader compilation/reflection/variant budgets, bounded compiled typed node IR, no private VFX shader compiler and NO arbitrary user shader upload |
| GFX-03 | GPU RenderGraph, dispatch/barrier, pass graph, buffer allocation, VRAM pressure, fences/device lost, frame-in-flight safe pooling; no GFX-08 GPU allocator |
| GFX-04 | geometry visibility/LOD, source surfaces for mesh particles, optional scene depth/motion/scene SDF with validity and no false-negative culling |
| GFX-05 | PBR/unlit material, alpha premultiply/transmission/depth, texture sampling and residency; VFX references MaterialId + correct revision |
| GFX-06 | bounded authored particle light **requests**, volumetric lighting/scattering, GI/reflections/probes. VFX owns visual density emission, NOT lighting solver or unlimited GPU lights |
| GFX-07 | exposure/tone map/temporal AA/Upscaler, reactive and velocity masks, bloom integration and output SDR/HDR, frame jitter metadata; no duplicate GFX-07 post-stack |
| TWO-01/04 | 2D Canvas/layer, sprite/parallax and 2.5D depth semantics, UI safe separation |
| WORLD/PHYS/GAME/NET | scene transforms, physics simulation truth, damage/collision authority; cosmetic visual approximation and event links only; headless server never loads particle GPU |

## 3. VFX Graph architecture
- Single durable `VfxGraphAssetV1` with project+AssetId/revision, graph schema version, node stable ID, edges/port types, declared resource and feature dependencies, provenance and authored quality overrides; refer to DATA-04 graph transaction and DATA-05 cooked asset, not a second asset registry.
- Typed node families: `EMITTER` (rate/burst/shape/surface), `INIT` (seed/lifetime/position/velocity/size/color), `FORCE` (gravity/vector fields/attractor/noise), `UPDATE` (integrate/fade/curve/turn), `EVENT` (bounded death/collision/spawn and authored audio/light requests), `RENDER` (sprite/flipbook/mesh/ribbon/trail/volume), `OUTPUT` (material/camera/depth/reactive light). Extend through versioned allowlisted ports with physical units and serializable assets.
- **Acyclic data DAG** for evaluation; no unrestricted recursion or arbitrary loops. Feedback/delay if eventually required must be an explicitly bounded previous-step state node with memory/quota proof. Subemitters use maximum nesting, depth-independent total per-tick spawn budget, explicit node/instance ownership and cancellation propagation. Reject cycles/bad ports/NaN/negative life/invalid transforms and asset rights before commit.
- CPU reference graph interpreter operating on safe fixed bounded arrays and deterministic PRNG seed. GFX-02 shader compilation produces validated render/compute programs from approved typed IR; GPU compute path optional, not a string-to-driver code injection entry.
- Compiler versions, artifacts and source fingerprints recorded in DATA-05 receipt; preserve previous-good runtime asset on reload failure, atomically swap only after verified GPU fences with GFX-03.
- Render graph invocation must be independent of Editor/UI/MCP; offline tool/CLI can validate/preview planned cost, NOT claim real GPU preview without executing graphics.

## 4. Particle simulation and lifecycle
- Simulation partition candidate: CPU path for tiny/interactive/low-end/headless reference; GPU SoA buffers for high counts if compute feature, shader capabilities and measured benefits support; hybrid transparent to artist via `ParticleSimulationPolicyV1`. GPU overhead can dominate low particle count; dynamically changing backend requires saved authoritative emitter seed/tick, visual restart/crossfade or explicit fallback receipt, never replicate prior GPU particles as gameplay state.
- Typed phases: `SPAWN_BATCH -> INITIALIZE -> UPDATE_FIXED_SUBSTEPS -> ALIVE_COMPACTION -> CULL/LOD -> OPTIONAL_DEPTH_SORT -> RENDER -> RECLAIM_FENCE_SAFE`. Bounded accumulator, max substeps to avoid a freeze after pause/background or a particle crash; record dropped cosmetic ticks and visual recovery.
- Spawn counts use checked 64-bit sums and caps, queue overflow policies, backpressure, ring/arena generation handles and explicit typed `PARTICLE_BUDGET_EXCEEDED`. Pool reuses only after correct CPU ownership and GPU fences; no stale indices/aliased history.
- Velocity, position, lifetime, age, quaternion/billboard orientation, color in scene-linear, soft-opacity, size, atlas/flipbook frame, layer and seed, local/world coordinate transform/origin epoch. Reject nonfinite physical inputs, protect half precision overflows.
- Sparse fields/attractor zones, depth/heightfield/SDF collision are **cosmetic** and approximated from GFX-04 validated scene data, no hard requirement for RT or true fluid particle collision. On missing depth/SDF, use safe no-collision/floor fallback and diagnostics; never tell gameplay “hit” based on a GPU approximation.
- Nonplaying emitter/source deleted, scene unload, camera cut, device loss and old graph revision must cancel/retire correctly without dangling resources. Offscreen sim update/culling policy is effect-specific; don't stop important persistent trails by naively hiding offscreen origin.

## 5. Rendering: ribbons, layers, translucency and overdraw
- Proposed render primitives: 2D billboard and animated sprite/flipbook, 2.5D layer-aware sprite, velocity-aligned ribbon, tube trail, camera-facing strip, mesh particle/decal/beam/arc/portal, volume density local proxy and high-tier distortion/heat haze. Trails have bounded source segment count, spline/tessellation, rollover and join/miter guards; camera near-plane, fast turn and zero-length segment robust.
- **Transparency**: material-owned GFX-05 `OPAQUE/MASK/BLEND/TRANSMISSION`, explicit premultiplied alpha, local depth write/test, soft-particle fade against validated GFX-04 depth and roughness/translucency semantics. Sorting stable CPU for small sets; GPU radix sort optional DX12/Vulkan after capability and license; weighted blended OIT as **approximate** alternative with documented failure for intersecting high-alpha layers and refraction, not "perfect sorting." No sorting if additive effect does not need it.
- Bounds and overdraw via GFX-04 conservative visibility; renderer resolution/scene HDR output from GFX-07 and sampling/texture budget GFX-05. Overdraw tile heatmap and alpha coverage score inform budget; a cheap particle that covers entire 4K screen can cost more than many tiny particles.
- Correct motion vectors/reactive masks on fast alpha, emissive bursts, VFX flipbook changes and depth; without reliable velocity mark reactive or choose conservative spatial/temporal fallback via GFX-07 to avoid ghost trails. GFX-07 owns bloom, not VFX bypassing post pipeline.
- 2D/2.5D: layer ordering, normal/lit sprite, parallax, pixel-snapping quality option, local sprite mask, exact UI exclusion. No mandatory expensive 3D pipeline for 2D effects.

## 6. Light, fog, fluids and audio boundaries
- VFX may declare `LightEmissionRequestV1` with physical intensity/size/radius/lifetime/priority and GFX-06 budget; coalesce many sparks into few proxy emitters or emissive-only pixels with **explicit loss receipt**, preserve authored high-salience combat indicators and no unlimited per-particle lights.
- VFX may author `VolumetricDensityStampV1` with bounded density/extinction/time/region for GFX-06 fog grid, but **GFX-06 owns scattering/shadow integration**. Sprite flipbook smoke is essential portable baseline; OpenVDB/NanoVDB runtime sparse-grid path optional only after exact source license/format/decoder/security and platform proof. No Houdini/EmberGen proprietary dependency required.
- Audio events are intents to AUDIO owner, one-shot and quota-limited, never create media mixers/audio devices inside GFX-08. Camera shake is semantic request to camera/gameplay owner, with reduced-motion/accessibility control. Physics/impacts originate upstream from authoritative gameplay; particle visual collisions remain best-effort only.

## 7. Scalability and quality policy
- Each `VfxQualityProfileV1` budgets per-frame `spawn_per_tick`, `alive_max`, emitter count, CPU job time, GPU compute/render time, overdraw in screen-space pixels, transparency sort workload, trail vertices, texture/descriptors, volume grid and outstanding emitter light requests, GPU bytes and frame graph time. Device snapshots and `UNKNOWN` budget sources are explicit; no invented Web VRAM.
- Degradation precedence must be author-aware: preserve *readability/safety-critical telegraphs* (gameplay signal remains independent); downgrade cosmetic background sparks, shorten decorative ribbons, adjust distant density/flipbook frame fidelity, switch expensive sort to acceptable blend where material allows, replace 3D fog with sprite sheets. User can opt out of flashes/motion. Never claim fidelity not actually rendered.
- Profiler exposes `VfxQualityReceiptV1`: per-effect emitter id, requested/actual alive and spawn counts, skipped budget cause, overdraw bins, sort passes, GFX-06 emitted light count, CPU/GPU P50/P95/P99 actual/estimated provenance, VRAM and scene total. Report degraded priorities and fallback reasons; no secret silent culling.
- Hot reload / version mismatch / GPU loss recovery may reset purely visual particles with notice, never corrupt gameplay state or stale GPU handles. Keep CPU conservative path when compute missing, late SDK load or device loss.

## 8. Platform matrix, untested
| Tier | Necessary candidate path | Optional |
|---|---|---|
| CPU/headless reference | parse/validate typed graph, deterministic emitter ticks, bounds and quotas, no GPU-required service | no visual frame/FPS proof |
| WebGL2 reduced | CPU particle simulation + bounded instanced sprite/ribbon, reduced alpha/flipbooks, 2D/2.5D | NO compute, native GPU radix/VDB requirement |
| WebGPU | bounded compute particles + storage buffers if feature/limits; sprite and depth-sort CPU fallback | WGSL compute/atomic and GPU sorting only after adapter proof |
| Win DX12/Vulkan / Linux Vulkan | CPU baseline; optional compute SoA, GPU culling/sort, GFX-03 fences and GFX-05 materials | AMD Parallel Sort DX12/Vulkan MIT candidate, high-tier mesh/ribbon/volume |
| macOS Metal | CPU and Metal-native compute candidate with per-device capabilities, depth/OIT fallback | no DX12/Vulkan SDK binary assumption; sparse volume conditional |

## 9. Security and AI-native authoring
- All VFX graph assets untrusted until validated: type DAG, graph size/edge count, subemit depth, spawn bounds, curve/LUT lengths, image/mesh licenses, number overflow, invalid Unicode/asset paths, nondeterministic extensions, zip bombs/EXR/VDB metadata and runtime uniform caps.
- Editor, CLI and MCP use common staged project-scoped semantic commands `InspectVfxGraph`, `PreviewVfxBudget`, `ValidateVfxGraph`, `StageVfxGraphEdit`, `CommitVfxGraphEdit`, `GetVfxQualityReceipt` (plus cancellation), with role capabilities, expected revision and DATA-04 journal; preview is static estimate, not GPU simulation.
- No arbitrary shader bytecode/string, filesystem or URL import, native GPU pointer/driver or OS command, unbounded nested graph, private asset/screenshot export, unapproved plugin install or silent third-party source/code copying.

## 10. Research optional: SVAG (Stormline Visual Allocation Governor)
Experimental adaptation by effect *salience*, temporal confidence, screen-space cost, GPU pressure and estimated frame QoS. Compare with fixed tier and simple distance/area LOD. **PROVE-OR-DROP**: if it increases flicker/latency/overhead or degrades essential readability, reject. No claim it is novel, implemented or beats Niagara/PoE2.

## 11. Future gating
Before #36 code: owner-approved 1.0 release class/DoD, exact C++ API+files/ABI/assets/license/codec and GFX-03/05 mandatory code integrated, feature probes/graphics shader bridge and source digests, typed GFX-06/07 integration, measured hardware platforms and numeric visual/CPU/GPU/VRAM budgets, security fuzz, unsigned driver/source protection and SHA-256 Context Lock. Entire 80 code WOs remain BLOCKED/`executor_ready=false` now.

## Primary references and upstream licensing evidence
- Epic Niagara scalability and GPU/CPU budget caveats: https://dev.epicgames.com/documentation/en-us/unreal-engine/scalability-and-best-practices-for-niagara
- Godot stable GPU/CPU particles (independent reference): https://docs.godotengine.org/en/stable/tutorials/3d/particles/index.html
- Godot GPUParticles3D trails and restart semantics: https://docs.godotengine.org/en/stable/classes/class_gpuparticles3d.html
- Effekseer MIT runtime code: https://github.com/effekseer/Effekseer/blob/master/LICENSE
- Effekseer Tool runtime/backend license notices: https://effekseer.github.io/Help_Tool/en/overview.html
- Effekseer platform and source compatibility: https://github.com/effekseer/Effekseer
- AMD GPUOpen FidelityFX Parallel Sort (MIT DX12/Vulkan): https://gpuopen.com/fidelityfx-parallel-sort/
- AMD FidelityFX Parallel Sort documentation: https://gpuopen.com/manuals/fidelityfx_sdk/techniques/parallel-sort/
- OpenVDB Apache-2.0 current upstream LICENSE: https://github.com/AcademySoftwareFoundation/openvdb/blob/master/LICENSE
- W3C WebGPU GPU compute/capability standard: https://www.w3.org/TR/webgpu/
