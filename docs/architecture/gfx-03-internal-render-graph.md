# GFX-03 internal logical render graph

**Status:** `GOVERNANCE-SCOPED / NOT IMPLEMENTED / NO NATIVE GPU`. **ADR:** [ADR-0117](../adr/0117-gfx-03-internal-render-graph.md). **Parent research:** [gfx-03-render-graph-gpu-memory](gfx-03-render-graph-gpu-memory.md), planning only.

## Purpose

Define the first executable GFX-03 slice without selecting a native graphics API or GPU allocator. The graph is a bounded, in-memory compiler over declarative pass/resource metadata. It produces deterministic dependency, synchronization, transient-alias and budget plans; it never records or submits GPU commands.

## Hard boundaries

- No Vulkan/D3D12/Metal/WebGPU, VMA/D3D12MA, native heap or driver barrier.
- No native resource, command buffer, fence, timeline, queue submission, swapchain or presentation.
- No pixel/render output, visual golden, GPU timing or hardware measurement.
- No shader compilation; GFX-02 reflection remains separate metadata.
- No public ABI, persistence, release, performance or security certification.

## Logical model

- **Resources:** bounded declarations with stable numeric ID, category (`External`, `Persistent`, `Transient`, `History`), byte size and alignment.
- **Passes:** stable numeric ID, queue preference (GFX-01 `QueueRole`), category and observable-side-effect flag.
- **Uses:** pass/resource pair with access (`Read`, `Write`, `ReadWrite`) and deterministic declaration order.
- **Graph definition:** immutable pass/resource/use tables plus device generation.

## Compilation phases

```text
definition validation
  -> unique IDs, capacities, sizes/alignment, references
  -> writer/reader analysis
  -> hazard edges RAW/WAR/WAW
  -> cycle detection and stable topological order
  -> logical synchronization transitions
  -> transient lifetime and conservative alias groups
  -> VRAM admission plan
```

No phase invokes a GPU, driver, external process or host file.

## Hazard rules

- One writer per resource in a compiled graph; multiple writers return `AmbiguousWriter`.
- A transient read before any writer returns `UninitializedRead`; external/persistent/history resources may be pre-initialized.
- Edges: writer to each reader (RAW); writer after earlier reader is represented by the same writer/reader ordering; cycles across resources return `Cycle` with typed diagnostic.
- Topological order is stable: repeatedly choose the lowest declaration-index pass whose dependencies are satisfied.
- Observable side-effect passes are never culled.
- Synchronization output is logical `GraphAccess`/queue transitions only; it is not a native barrier promise.

## Transient and memory rules

- Only `Transient` resources are alias candidates.
- Lifetimes are first/last pass positions in the topological order.
- Alias groups require equal byte size and alignment and strictly disjoint lifetimes; otherwise resources remain distinct.
- Budget admission uses checked arithmetic and conservative headroom. Unknown budget fails closed; overcommit returns `BudgetExceeded`.
- Alias bytes saved are planning estimates, not measured VRAM savings.

## Determinism

- Tables preserve declaration order; edges and alias groups are sorted by stable IDs/indices.
- Topological order uses declaration index as the tie-break.
- No unordered container iteration determines output.
- Repeated compilation of an unchanged definition produces identical plans.

## Failure model

Typed diagnostics cover duplicate IDs, capacity, invalid ranges, unknown references, ambiguous writers, uninitialized reads, cycles, unsupported queues, incompatible aliases, unknown/exceeded budget and stale generation. Diagnostics are bounded and contain only logical IDs/pass/resource references.
