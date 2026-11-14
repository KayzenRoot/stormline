# GFX-03 — Typed Render Graph / GPU Resource & Budget API

**Research WO:** NLE-P00-WO-002-GFX-03 | **Issue:** #129 | **Future code #31:** BLOCKED.
**State:** PROPOSED semantic interface, no C++ ABI, real GPU, native backend or working MCP server.

## Proposed contract types

| Logical type | Mandatory fields / purpose | Validation / invariant |
|---|---|---|
| `RenderGraphDefinitionV1` | project/renderer id, graph/schema revision, device generation, sorted pass/resources, target features, frame-in-flight policy | immutable compile snapshot; no raw GPU handles from remote API |
| `PassNodeV1` | stable PassId, queue role preference, pass category, input/output uses, observable side effect/export flag, required feature set | duplicate IDs, unsupported stage or unbounded work rejected; no culling of observable passes |
| `ResourceDescriptorV1` | ResourceId, external/persistent/transient/history category, format, byte dimensions/alignment, aspect/layers/mips, usage, initial/final states, aliasability | checked overflow, RHI caps, source ownership and lifetime |
| `ResourceUseV1` | PassId, ResourceId, `SubresourceRangeV1` (mip/layer/aspect or buffer byte range), READ/WRITE/RW, access stage, attachments, load/store/clear/discard | reject out-of-range, stale, unknown or uninitialized read, incompatible simultaneous use |
| `RenderGraphCompileRequestV1` | graph revision, GFX-01 DeviceCapabilitiesV1 fingerprint, shader reflection/layout version, memory budget, aliasing/sync policy and desired frame epoch | preconditions and resource limits; no compilation of arbitrary code |
| `GraphDependencyEdgeV1` | source/target PassId, resource/subresource, RAW/WAR/WAW/temporal/observable type, original declaration span | cycle diagnosis and topological schedule proof |
| `GraphPlanV1` | immutable plan id/digest, schema/feature version, topo order, culled reason, complete SyncPlan/AllocationPlan, validation receipt, epoch policy | bound to device generation/layout; not GPU execution evidence |
| `SyncTransitionV1` | resource/subresource, prior & next stage/access/layout, queue owner, semaphore/fence/timeline requirements and backend target | typed, checked, no hidden barrier omission; supports conservative serial fallback |
| `SyncPlanV1` | ordered barrier groups, queue handoff, wait/signal, cross-frame dependency and backend compatibility | await producer writes before consumer reads, no cyclic waits or unsignaled fence |
| `GpuBudgetSnapshotV1` | adapter/generation, known/estimated/unknown source, UMA/dedicated tier, reported total/free if available, headroom, budget and timestamp | no fake VRAM totals on Web/UMA; optimistic numbers never guarantee allocatable bytes |
| `AllocationRequestV1` | resource id, category, size/alignment, heap/usage compatibility, residency/pin, expected GPU lifetime | no overflow, no unrestricted overcommit |
| `LifetimeIntervalV1` | resource, first/last graph pass, first/last GPU submission and completion fence/epoch, frames-in-flight | CPU topo duration insufficient proof for alias, conservatively extend until last required signal |
| `AliasingGroupV1` | compatible resource IDs, heap/allocation slot, non-overlap proof IDs, fence/queue and region compatibility | cannot alias persistent/history/external or outstanding GPU reads; require full proof |
| `AllocationPlanV1` | physical heap/offset mapping, transient vs persistent accounting, alias proofs, estimated peak, fragmentation/eviction cost | proposed only until actual allocation success; safe no-alias fallback |
| `ResourceResidenceV1` | resource/generation, residency state, pin/inflight, DATA-05 AssetId optional ref, last-use GPU fence, eviction allowed | resource owner confirms safe destroy/evict; never delete source bundle |
| `GraphSubmitReceiptV1` | plan+device+frame generation, submit ids, GPU fence markers, results, resource retirement ownership | submitted != completed; report final success only after required completion/present |
| `GraphDiagnosticV1` | severity/code, PassId/ResourceId, subresource, stage, dependency path, sanitized context and optional fix | bounded redacted, project relative, no native pointers or binary dumps |
| `GraphErrorV1` | stable code, phase, generation, retryability, recovery action | fail closed for invalid graph/alias/rights; never hide GPU device loss |
| `GraphAuditReceiptV1` | plan/hash provenance, validation version, evaluated limits, library/adapter profile, no-alias fallback chosen and warnings | not a substitute for real GPU debug/validation tests |

## Safe state machine
```text
GraphDefinition
  -> INSPECTED -> VALIDATED -> DAG_COMPILED -> SYNC_PLANNED
  -> MEMORY_PLANNED -> PLAN_VERIFIED -> STAGED_FOR_SUBMISSION
  -> SUBMITTED -> GPU_COMPLETE -> PRESENTED / EXPORT_READY -> RETIRED
                          \
                           -> INVALIDATED / FAILED / RESTART_REQUIRED
```
Any device loss, pipeline hot-reload, incompatible resize or feature change invalidates plans/handles bound to the old generation. No success claim until requested observable output reached. Plans are immutable snapshots; per-frame fences/present state not shared across epochs.

## Hazard rules (must be tested for each subresource)
- RAW, WAR, WAW on overlapping byte/aspect/mip/layer ranges create directed synchronization/dependency constraints. RAR may overlap only when backend compatible.
- Unknown initial state of imported native resource is **not** implicitly `UNDEFINED` unless initialized/reset contract says so. Read of undefined transient memory is a hard error.
- GPU completion and queue ownership/fences, not CPU DAG pass order, determine safe memory aliasing. Multiple frames in flight, async compute and readback/present extend the lifetime.
- ShaderReflectionV1 from GFX-02 validates declared binding and write/read resource role, independently of native compiler.
- Driver/OS unsupported queue/feature => explicitly serial no-alias plan or typed `UNSUPPORTED_FEATURE`. Never fake multiple GPU hardware queues.
- WebGPU has resource usage-scope semantics and no portable manual Vulkan/D3D barrier command; a graph may need splitting or must reject usage conflicts.

## Editor / CLI / MCP parity

| Semantic command | Scope | Effect |
|---|---|---|
| `rendergraph.inspect` | `project.graphics.inspect` | readonly bounded nodes/resources, no backend calls |
| `rendergraph.dependencies` | `project.graphics.inspect` | readonly DAG/hazard evidence |
| `rendergraph.validate` | `project.graphics.inspect` | pure schema/hazard/graph checks, no native GPU command |
| `rendergraph.compile.preview` | `project.graphics.propose` | predicted sorted pass list + barriers/alias estimate, never commit |
| `rendergraph.memory.preview` | `project.graphics.propose` | budget and fallback estimation, no physical resource allocation |
| `rendergraph.diagnostics.read` | `project.graphics.debug.read` | bounded redacted errors, no raw GPU data |
| `rendergraph.trace.inspect` | `project.graphics.debug.read` | aggregate time, alias bytes and queue stats if actually available |
| `rendergraph.plan.commit` | trusted Editor/runtime internal operation | allowed only after approved workflow and GFX-01 device policy; NOT generic MCP |
| `rendergraph.submit` | native engine private | **NOT** exposed to MCP/agent raw code |
| `rendergraph.resource.alloc` | native engine private | **NOT** exposed to MCP/agent raw commands |

All calls scoped by authenticated project/actor, expected revision, capability, quotas, source DAG/graph snapshot, operation ID and cancel/expiry. A caller cannot inject native GPU handles, arbitrary callback, shader, driver/OS command, raw alias offset or unbounded pass count via typed interface.

## Errors and recovery
`INVALID_PASS_DESC`, `INVALID_RESOURCE_DESC`, `GRAPH_CYCLE`, `GRAPH_UNINITIALIZED_READ`, `GRAPH_AMBIGUOUS_WRITER`, `GRAPH_MISSING_OUTPUT`, `GRAPH_SIDE_EFFECT_CULL_FORBIDDEN`, `INVALID_SUBRESOURCE_RANGE`, `REFLECTION_MISMATCH`, `UNSUPPORTED_BACKEND`, `UNSUPPORTED_QUEUE`, `UNSUPPORTED_FORMAT`, `INVALID_STAGE_ACCESS`, `INVALID_BARRIER`, `QUEUE_OWNERSHIP_CONFLICT`, `GPU_DEADLOCK_RISK`, `ALIAS_LIFETIME_OVERLAP`, `ALIAS_HEAP_INCOMPATIBLE`, `RESOURCE_IN_FLIGHT`, `GPU_BUDGET_UNKNOWN`, `GPU_BUDGET_EXCEEDED`, `MEMORY_ALLOCATION_FAILED`, `DEVICE_LOST`, `GRAPH_PLAN_STALE`, `FRAME_EPOCH_MISMATCH`, `STALE_GENERATION`, `PRESENT_NOT_READY`, `GPU_TIMING_UNAVAILABLE`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`, `UNKNOWN`.

Each error reports stage and safe recovery/fallback, not a fake rendering success. No source/data loss on graph compilation failure or budget rejection. Concrete C++ ABI/backend memory arrangement remains unapproved; #31 and 80 WOs stay blocked.

References: [architecture](../architecture/gfx-03-render-graph-gpu-memory.md), [ADR-0016](../adr/0016-gfx-03-render-graph-policy.md), [tests](../testing/gfx-03-acceptance-matrix.md).
