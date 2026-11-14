# GFX-08 — VFX Graph, Simulation and Performance Semantic API v0.1

**Research WO NLE-P00-WO-002-GFX-08** | **Issue #144** | **Future implementation #36 BLOCKED**.  
Logical contract only, **not** C++ ABI, finalized wire format, operational MCP server, particle renderer or GPU shader code.

| Proposed type | Key fields | Validation and owner |
|---|---|---|
| `VfxGraphAssetV1` | project+AssetId/revision, graph schema, node IDs/edge typed ports, rights/dependency refs, budget class, seed schema | DATA-02/04 IDs+asset journal, GFX-02 compiler interface, no cycles/unbounded loops |
| `VfxNodeDefinitionV1` | kind EMITTER/INIT/FORCE/UPDATE/EVENT/RENDER/OUTPUT, allowed input/output units, parameter bounds, static feature set | allowlist and typed stage, reject unknown required node/invalid numeric/illegal ref |
| `VfxGraphValidationV1` | schema/signature, DAG proof, nesting/spawn/time bounds, cost estimate + confidence, warnings and errors | user text cannot be raw shader/script/device path; no cross-project asset |
| `VfxEmitterDefinitionV1` | EmitterId, graph ID/revision, rate/burst/shape, lifetime/PRNG seed, loop/time, world/layer and owner | finite nonnegative, max burst/lifetime/tick and bounded child emitters |
| `VfxInstanceSnapshotV1` | instance id/generation, graph revision, scene+spawn event tick, transform/origin epoch, states SPAWN/ACTIVE/CANCELLING/DEAD | world/component owns scene transform; no stale cross-device handles |
| `ParticleSimulationPolicyV1` | CPU_REFERENCE/CPU_RENDER/GPU_COMPUTE, substep rate/count, source capability, expected visual errors, fallback | CPU deterministic fixed tick; GPU no bitwise deterministic claim |
| `ParticleStateLayoutV1` | SoA layout version, count/capacity, position+velocity, age/life, size/rotation, color+alpha, atlas frame/seed/flags | checked 64-bit sizes and bounds; GFX-03 owns actual storage |
| `ParticleSpawnReceiptV1` | requested vs admitted spawn, live count, truncation, pool generation, overflow reason, tick/seed | no unbounded append/index, exact reason for downscaling |
| `TrailGeometryPlanV1` | source IDs, sample count/time, segment cap, width/vertex budget, strip/join and material | checked tessellation and frame validity; no degenerate NaN geometry |
| `VfxMaterialBlendProfileV1` | GFX-05 material ID/revision, depth policy, alpha (MASK/BLEND/ADD), soft depth, optional CPU/GPU sort/OIT | material semantics authoritative, no promised exact order-independent OIT |
| `VisualCollisionSourceV1` | GFX-04 depth/SDF/heightfield asset epoch, sampling scale and behavior if absent | best effort cosmetic visual only, never gameplay collision contract |
| `VfxLightEmissionRequestV1` | emission source ID/epoch, GFX-06 light unit/profile, priority, lifetime/radius, cap and fallback proxy | GFX-06 owns actual scene lights/VRAM, no implicit 1 light/particle |
| `VolumetricDensityStampV1` | bounded density/extinction/region/time/LOD, GFX-06 grid compatibility and fallback sprite | density authored only, lighting integrated by GFX-06 |
| `VfxQualityBudgetV1` | caps particles/spawn/ribbons/trails/alpha coverage/VRAM/CPU+GPU ms/draw/sort/light count, quality tier | device capabilities verified, missing memory UNKNOWN, GFX-03 quotas |
| `VfxRenderPlanV1` | GFX-03 pass/resource refs, GFX-05 material, GFX-07 velocity/reactive/linear-HDR target and fallback chain | GFX-03 owns synchronization, resource dependencies, device generation |
| `VfxQualityReceiptV1` | effect/scene revision+ticks, admitted/degraded counts, overdraw, CPU/GPU actual or estimate provenance, resource bytes, lost quality, typed errors | metrics bounded/redacted, no “measured” without real capture |
| `VfxAuthoringTransactionV1` | project/AssetId, expected revision, staged DAG diff, authorized capability and journal token | DATA-04 journal, CAS/recovery and scoped rights |

## Simulation lifecycle / recovery
`AUTHORING -> VALIDATED_GRAPH -> VERSIONED_COOK_VERIFIED -> DEVICE_CAPABILITY_NEGOTIATED -> INSTANCE_SPAWN_ADMITTED -> UPDATE -> COMPACT/CULL -> OPTIONAL_SORT -> RENDERGRAPH_SUBMITTED -> FENCE_COMPLETE -> RECLAIMED`.  
`CANCELLED/POOL_EXHAUSTED/GRAPH_REVISION_STALE/DEVICE_LOSS` cause typed documented fallback and release after fences, not dangling handles. GPU live particles are visual-only, no server hit reports. CPU path can validate graphs headless.

## Unified Editor/CLI/MCP semantics
Readonly `InspectVfxGraph`, `InspectVfxEmitter`, `PreviewVfxBudget`, `PreviewVfxCompile`, `GetVfxQualityReceipt`, `GetVfxValidation`. Mutations `StageVfxGraphEdit`, `ValidateVfxGraphEdit`, `CommitVfxGraphEdit`, `CancelVfxOperation` require project capability, expected revision, bounded DAG nodes and DATA-04 journal/rollback. Preview cost **ESTIMATED**, not GPU tested. No unscoped directories/URL, raw shader, arbitrary plugin/script, raw GPU pointer, unbounded recursive child emitter or private game-art export.

## Typed errors
`VFX_GRAPH_INVALID`, `VFX_GRAPH_CYCLE`, `VFX_PORT_TYPE_MISMATCH`, `VFX_GRAPH_TOO_COMPLEX`, `VFX_INVALID_NUMERIC`, `VFX_BURST_LIMIT`, `VFX_SUBEMITTER_DEPTH`, `PARTICLE_BUDGET_EXCEEDED`, `PARTICLE_POOL_GENERATION_STALE`, `PARTICLE_BUFFER_OVERFLOW`, `VFX_SIMULATION_UNSUPPORTED`, `VFX_COLLISION_VISUAL_UNAVAILABLE`, `VFX_SORT_UNSUPPORTED`, `VFX_OIT_APPROXIMATION`, `TRAIL_GEOMETRY_INVALID`, `VOLUMETRIC_CAP_EXCEEDED`, `EMISSION_LIGHT_BUDGET`, `SHADER_VARIANT_MISMATCH`, `VFX_DEVICE_GENERATION_STALE`, `VFX_GRAPH_REVISION_CONFLICT`, `VFX_RIGHTS_DENIED`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Correlation ID, safe stage, retryability, redacted metadata, no sensitive host paths.

## Freeze before code
Exact ABI/wire schemas and file paths, quotas/limits/performance and color targets, GFX-03/05 implementation receipts, GFX-06 light/GFX-07 motion+reactive data integrated, DATA-04/05 rights/cook, target GPU/backends, benchmark fixtures/asset license, independent CI/perf acceptance and SHA-256 Context Lock. ADR PROPOSED, code #36 BLOCKED.
