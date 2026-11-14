# GFX-03 — Dependency-Safe Render Graph and GPU Resource/VRAM Management

**Research WO:** NLE-P00-WO-002-GFX-03 | **Research issue:** #129 | **Future code issue:** #31 BLOCKED  
**State:** RESEARCH PROPOSED / NO GRAPH EXECUTABLE | **BASE main:** e76d561d98dd4192d8bae1fb66cab09e194fbc70  
**Risk:** LOW current docs; future ELEVATED for GPU races, cross-frame aliasing, out-of-memory and device loss.

## Purpose and isolation boundaries
Define a versioned Stormline **Render Graph** (RG), in which 2D sprites, hybrid 2.5D, 3D stages and future lighting/VFX declare resources, use ranges, queue capabilities, hazards and outputs. Compile that declaration into a safe dependency DAG, a predictable GPU submission schedule and an allocation/retirement plan. The runtime must adapt to VRAM pressure with evidence-based quality fallbacks rather than assuming limitless GPU memory or claiming opaque drivers will fix incorrect barriers.

**Not a renderer**: no PBR, GI, RT, VFX, material shader compiler or scene graph implementation is part of this Work Order.

### Ownership at each seam
- **GFX-01 RHI** owns adapters, device-generation handles, command encoders, queue capabilities, primitive synchronization and swapchain/offscreen presentation. GFX-03 emits a *typed plan* and requests RHI primitives; never exposes native Vulkan/Metal/D3D12 pointers in the public graph API.
- **CORE-03** owns CPU task executor, priority/cancellation and worker bounds. Graph CPU recording tasks can be scheduled there, but CORE-03 is not a GPU queue scheduler. GPU commands must respect actual GFX-01 feature and queue support.
- **CORE-02** owns CPU scratch/allocation. GFX-03 owns **GPU** placement planning, heap pools, transient lifetime constraints and VRAM budgets with backpressure; CORE-02 budgets prevent unbounded CPU staging.
- **CORE-06** owns trace/span/metrics and default-local diagnostics; GFX-03 records plan provenance and bounded GPU counters without automatic telemetry upload.
- **GFX-02** owns ShaderReflectionV1 / PipelineLayoutContractV1 and pipeline compatibility. Graph verifies pass resource declarations against reflection, not recompiles shader source.
- **DATA-02/DATA-05** own stable AssetIds and streamed cooked assets; graph references pinned generation resource handles and residency hints, not authored asset identity or immutable bundle management.
- **TWO/GFX-04+** own visible passes, rendering algorithms, culling and scene/lighting policy. RG provides DAG and memory/synchronization, not implementation of the visual effect.
- **PLAT-03** owns Web browser WebGPU availability and WebGL2 degraded target. Browser WebGPU manages much synchronization implicitly and validates usage scopes. GFX-03 may refuse unsupported graph operations, but cannot expose Vulkan-style barriers to WebGPU.
- **EDIT/AI/MCP** may inspect, validate and preview semantic passes under scoped capabilities; may not submit arbitrary shader code, GPU commands, native pointers or private raw binary dumps.

## Declarative pass and resource model
Each pass is a typed `PassNodeV1` with `PassId`, domain/category (2D/2.5D/3D/postfx/compute/copy/present), required/optional features, queue preference, conservative side-effect classification and lists of `ResourceUseV1` records. A use has resource id and **subresource range**, aspect/plane, mip/layers/buffer byte interval, stage, access READ/WRITE/READ_WRITE, load/store/clear/discard and expected layout/state. Attachment and depth/stencil semantics are explicit. Whole-resource fallback is allowed but should not silently claim subresource precision.

Resource categories:
1. `EXTERNAL_IMPORTED`: swapchain, DATA-05 persistent streamed texture, native-backed video or GPU buffer with scoped RHI generation, explicit entry/exit state and owner. Cannot alias or cull without owner permission.
2. `PERSISTENT_GRAPH_OWNED`: history buffers/temporal accumulation, double/triple buffering and stable all-frame residency; may be recreated after device loss and hot reload. Never treated as transient without a new checked generation.
3. `TRANSIENT_FRAME_LOCAL`: temporary render targets, depth/resolve, intermediate buffers and transient descriptor ranges. Only candidates for safe alias after proven lifetime constraints and GPU completion.
4. `HISTORY_CROSS_FRAME`: explicitly modeled generation/frame index and producer/consumer fences across frames-in-flight; requires initialized-history policy and invalidation on camera cut/resize/device loss. Never assumed disjoint merely from within-one-frame DAG.

Every resource descriptor declares format, dimensions/strides/sample count, usage/heap compatibility, clear/initial state, estimated bytes, alignment, view alias restrictions, memory tier, export/pin contract and residency priority. GFX-01 validates actual backend capabilities. Imported resources without known prior state must enter conservative validation or refuse a pass, not invent prior barrier state.

### Offline graph compilation pipeline (future architecture)
```text
Authorized PassDeclarations / ResourceDescriptors
 -> schema/id/device-generation/feature validation
 -> collect reads/writes and subresource overlap; reflection check
 -> build hazard edges: RAW, WAR, WAW + external/temporal constraints
 -> detect cycles; uninitialized reads; unsupported pass/queue/format
 -> stable deterministic topological order with declared tie-breaks
 -> safe optional pass culling only when no external/observable side effects
 -> minimize serial barriers, choose queue roles if supported, else single queue
 -> calculate resource live intervals INCLUDING GPU completion and frame-in-flight
 -> budget plan for persistent and transient heaps, classify safe alias pairs
 -> emit typed backend SyncPlan (barriers, queue handoffs, fences/semaphores)
 -> validate plan against RHI / GPU profile / budget
 -> freeze GraphPlanV1 and provenance/epoch, allow inspect/preview
 -> resource allocation/staged recording under CORE-03 and GFX-01
 -> GPU submit; completion receipts; deferred GPU-safe resource retirement
```

**Crucial invariant:** pass DAG order on CPU is *not* proof that GPU submissions finish in that order across queues or across frame epochs. Alias only if both logical lifetime AND actual fence/timeline completion make memory reuse legal. In ambiguous cases, **disable aliasing or serialize** and report cost.

### Hazard analysis and barriers
For overlapping byte/subresource ranges:
- RAW (prior write then read) requires visibility/availability and compatible usage state.
- WAR (read then write) requires execution ordering, often queue ownership; conservatively keep edge and explicit transition.
- WAW (write then write) requires strict ordering and appropriate memory guarantees.
- RAR can often overlap if same compatible read state and supported queue semantics; never assume harmless if backend usage scopes conflict.
- Resolve/readback/present/copy edges are observable side effects, not dead-code passes.
- A pass that reads an undefined/transient resource before its first defining write is invalid unless explicit init/clear/upload contract exists. Multiple unordered writers/conflicting subresources diagnosed.
- Cycles detected with stable path and explicit source `PassId` and `ResourceId` diagnostics. No artificial cycle-break barrier that hides dependency error.
- GPU-stage/access layout, ownership transfer and queue families are backend-specific and output `SyncPlanV1`, with conservative feature fallback.

## Per-platform synchronization/placement candidates

| Platform | Low-level truth | Implications |
|---|---|---|
| Vulkan | Khronos Synchronization2 / `vkCmdPipelineBarrier2`, explicit stage/access and queue-family ownership | use Vulkan synchronization validation; Synchronization2 availability/capability gate; VMA optional allocation helper; alias with strict heaps/memory type and cross-queue proofs |
| D3D12 | Legacy resource transition/UAV/alias barriers; **enhanced barriers optional** and driver/capability dependent | compare legacy vs enhanced, never require enhanced support; D3D12MA MIT optional heap suballocator; placed-resource alias only with barriers and completion |
| Metal | `MTLHeap`, storage/hazard mode, tracked/untracked, fences/events; Apple guidance explicitly warns aliased resource reuse without completion is undefined | Metal heap resources may be **untracked by default**, so no assumption automatic tracking; MTLHeap vs placement + GPU command behavior must be tested on Apple Silicon |
| WebGPU | W3C `usage scopes`, render/compute pass validation, API-managed hazards and no portable explicit native barrier API | translate graph to legal usage scopes/command encoders and reject impossible read/write within one scope; avoid assuming native heap aliasing or async queue parallelism |
| Headless validation | CPU-only graph compiler and mock RHI | structural correctness only, not actual GPU allocation/pixels/latency |

Official specs: [Khronos synchronization](https://docs.vulkan.org/guide/latest/synchronization.html), [D3D12 barriers](https://learn.microsoft.com/en-us/windows/win32/direct3d12/using-resource-barriers-to-synchronize-resource-states-in-direct3d-12), [D3D12 enhanced barriers](https://learn.microsoft.com/en-us/windows-hardware/drivers/display/enhanced-barriers), [Apple MTLHeap](https://developer.apple.com/documentation/metal/memory-heaps), [WebGPU](https://www.w3.org/TR/webgpu/).

## GPU memory and residency policy
Propose `GpuBudgetSnapshotV1` from GFX-01 device/driver memory info, with known/estimated/unknown provenance; budget must be conservative (reserving headroom for OS, compositor, driver, other apps) and revisited on pressure/device generation changes. Separate **persistent residency** (geometry/textures/streaming from DATA-05), **graph persistent history**, **transient frame heaps**, **GPU uploads/readback**, **native pipeline caches**. Avoid claiming one global VRAM figure applies across UMA/discrete GPU/browser and Apple shared-memory devices.

Resource manager computes `LifetimeIntervalV1` for each transient based on pass dependencies, physical queue submit/fence/swapchain usage and frames-in-flight; versions resources per generation and identifies `AliasingGroupV1` only when format/usage/heap alignment/size and actual nonoverlap guarantees hold. Aliasing is an **optional optimization**; safe baseline uses distinct allocations / conservative lifetime extension. A mismatched alias group is a correctness bug, not merely a performance issue.

Budget response order (proposed, under renderer quality consent):
1. Prevent overcommit with estimate+admission and enforce per-frame transient cap, queue depth and maximum outstanding work.
2. Reuse cached verified/compatible allocations after completed fences; defer destruction and respect pin/ownership.
3. Release unpinned temporary resources, throttle optional uploads/prefetch, select lower-resolution **optional** targets where explicitly permitted, skip optional postprocessing only if quality policy allows.
4. Ask DATA-05 streaming/texture-Lod and GFX consumer to lower residency rather than deleting immutable asset source.
5. If still unsafe, return `GPU_BUDGET_EXCEEDED`/graceful low-memory mode, never clear borrowed persistent GPU resource without authorization. Never drop required depth/scene data silently.

Defragmentation is **not free nor automatic**. It may require copying resource content with staging and fence safety. Pool sizing, fragmentation, alias bytes saved and memory spike need benchmarks and rollback/fallback.

## Multi-frame execution and lifecycle
Graph plan and resource handles carry device generation, graph revision, frame epoch and descriptor version. Hot reload from GFX-02, swapchain resize and dynamic resolution create candidate generation; do not mutate in-flight descriptors. Persistent history includes camera cut reset, screen-size changes, shader schema/layout compatibility and readback fences.

Device loss transitions graph to `INVALIDATED`, cancels unsafe future submissions, marks GPU handles stale, retains only CPU-authoritative plan/asset receipts, re-probes GFX-01 capabilities and recompiles/reallocates (or signals `RESTART_REQUIRED`). Avoid blindly restoring native driver pipeline cache or GPU memory alias. Current frame failure must not claim successful presentation. Clean shutdown waits only within bounded policy and reports resources that cannot be safely destroyed.

## Graph build/compile caching
Graph *plan cache* keys: pass descriptor/subresource DAG, ShaderReflection layout digest, target caps, surface dimensions/formats, frame-in-flight policy, alias option, versioned compiler algorithm, feature tier and device generation. Input changes invalidate selectively but do not promise a correct incremental cache without proof. Immutable plan can be cached; mutable runtime state (fence values, resource content, device handles, per-frame queue completion) cannot be reused across epochs.

**Dynamic scene changes** can be represented as stable pass templates with resized or conditionally enabled pass variants; avoid compiler path stall on every draw. Prepare fallback precompiled graph plans where possible and measure p95 compile/replan cost.

## Security and auditability
Graph validation is allowed on untrusted **data descriptors** with bounded pass count, edges, graph depth, subresource spans, allocation totals, request size, recursion and CPU time. Do not run arbitrary plugin callback/native render command supplied by external Graph JSON. MCP uses semantic read-only plan inspection/preview with cap/pagination, cannot submit GPU commands, create native buffers, override budget or access raw pointers. Report pass/resource IDs, typed errors, safe logical memory diagram, redacted adapter/driver detail, no raw shader binary or arbitrary absolute host path.

Race/alias mistakes can escalate from visual corruption to driver reset. Test with Vulkan sync validation, D3D12 debug/info queue, Xcode/Metal GPU capture when supported, browser WebGPU validation plus adversarial GPU and CPU fault injection; **docs CI is not equivalent to any of these**.

## Prove-or-drop research: Stormline Adaptive Frame Graph (SAFG)
Experimental derived scheduler that estimates pass critical paths and VRAM pressure, proactively chooses safe queue overlap/prefetch and alias plan. Compare against deterministic topological ordering + conservative single queue + verified non-overlap alias baseline using identical rights-cleared 2D/2.5D/3D scenes on low- and high-memory GPUs. Report p50/p95/p99 frame-time, CPU graph compile overhead, **actual** GPU occupancy, peak heap bytes and correctness. Never require ML or automatic enablement; discard if results inconclusive or complexity creates new hazards.

## Gates for future executable issue #31
Approve actual backend/API/feature tiers, pinned VMA/D3D12MA or native allocators and exact shipped-source licenses/SBOM, target OS+GPU/browser hardware and quantified budgets. Implement/merge GFX-01 and CORE-03 prerequisite code; lock GFX-02 reflection interfaces, DATA-05 streaming contracts, resource and pass ABI, exact paths/test commands, regression/driver tools, feature fallback, risk ELEVATED proof obligations and rollback. Build fresh SHA-256 source fingerprints and approved ADR/Scope/DoD/release class. **This research does not enable engine code.**

See [technology matrix](../research/gfx-03-rendergraph-technology-matrix.md), [ADR-0016](../adr/0016-gfx-03-render-graph-policy.md), [API](../contracts/gfx-03-render-graph-api.md), [future tests](../testing/gfx-03-acceptance-matrix.md).
