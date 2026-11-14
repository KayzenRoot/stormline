# ADR-0016 — GFX-03 Render Graph and Conservative GPU Memory Policy

**Status:** PROPOSED / NOT APPROVED FOR ENGINE IMPLEMENTATION  
**Date:** 2026-11-14 | **Research WO:** NLE-P00-WO-002-GFX-03 | **Issue:** #129 | **Future code:** #31 BLOCKED

## Problem
The Stormline renderer must perform 2D/2.5D/3D passes and future complex VFX with bounded GPU memory and predictable frame times across Vulkan, D3D12, native Metal and browser WebGPU. Explicit APIs expose synchronization, queue, lifetime and aliasing hazards that cannot be solved safely by treating DAG order as proof that GPU work has finished. Low-end devices and unified-memory Apple/browser targets need honest budgets and safe fallback.

## Proposed choices (not runtime-ready)
1. Define Stormline-owned typed, versioned **declarative RenderGraphV1/PassNodeV1/ResourceUseV1**, independent from native pointers. Renderers declare reads/writes and side effects; graph compiles a stable DAG and rejects cycles, read-before-initialize and illegal subresource overlap.
2. GFX-01 owns native RHI resource and queue primitives, GFX-03 owns **graph scheduling and GPU heap plan**; CORE-03 owns CPU task scheduling; CORE-02 CPU memory; GFX-02 shader/reflection; GFX-04+ and TWO own visual passes, DATA-05 source asset streaming. No duplication of scene/material/lighting/physical memory loader.
3. Reify RAW/WAR/WAW hazards with stage, access, layout, ownership and queue handoff; do not assume RAR within incompatible WebGPU usage scopes is legal. Explicit source/target states are required for imported resource.
4. Treat **transient aliasing as optional optimization**, enabled only when both full logical live interval and actual GPU queue/frame completion plus backend heap/type/format conditions are proven. No alias for persistent/temporal/history/swapchain or in-flight assets by default. Conservative no-alias and serial queue baseline always exists.
5. Constrain execution by GFX-01 capability tiers: Vulkan Synchronization2 where available; D3D12 legacy barriers baseline, enhanced optional; Metal MTLHeap hazard mode/fence awareness; WebGPU usage scopes and browser-managed synchronization, no arbitrary native explicit barriers in WebGPU.
6. Evaluate VMA MIT for Vulkan and D3D12MA MIT for Windows allocators; Metal native heaps and WebGPU managed resources remain separate. Vendor helpers are **not** the graph compiler and must be license/tag/driver audited before selection.
7. `GpuBudgetSnapshotV1` distinguishes known vs estimated/unknown driver budget and UMA vs dedicated VRAM; reserve headroom, enforce transient/persistent/upload/readback caps, throttle optional streaming and explicitly degrade authorized postprocess quality on pressure. No silent discard of required resources.
8. Device loss, resize, feature change, shader hot reload and dynamic resolution invalidate generation-tagged resource/graph plans. Only activate new plan after validation; preserve last-good or report restart-required. In-flight handle retirement uses valid GPU sync and cannot be assumed atomic with source document update.
9. Editor/CLI/MCP get scoped inspect/preview/diagnostics and bounded trace export; no native pointer/barrier override, shader execution or runtime memory mutation from untrusted agent.
10. Optional SAFG critical-path/prefetch heuristic is **prove-or-drop** against deterministic topo + conservative scheduling + verified aliasing on real hardware, not a required proprietary architecture.

## Alternatives rejected as defaults
- Render graph as an implicit unversioned pile of command callbacks without resource declarations: impossible to safely infer hazards/recover.
- Compile every scene object as its own graph each frame: high CPU/variant overhead, requires benchmark not assumption.
- One huge renderer package such as Filament/bgfx without boundary control: overlaps GFX-02/04/05 and reduces own contract discipline; study only.
- Always alias all nonoverlapping passes by CPU DAG order: **unsafe** across async queues or frames in flight and may corrupt memory.
- Always async compute or enhanced D3D barriers: feature and real queue behavior varies, can be slower; conditional only.
- Trust driver memory budget as guaranteed available bytes: other processes/compositor/UMA can change pressure, reserve headroom.
- Raw MCP/LLM-supplied GPU barrier/resource command: security and stability violation.
- WebGPU as Vulkan with explicit barriers: APIs and validation differ.
- Original SAFG automatically enabled without A/B evidence: complexity/no guaranteed performance gain.

## Deliberately deferred decisions
Exact graph schema and algorithm, stable tie-breaks and resource/sync contract ABI, minimum Vulkan/D3D12/Metal/Web targets, VMA/D3D12MA pinned tags/transitive SBOM, CPU/GPU memory thresholds, number frames-in-flight, alias compatibility policy, transient pool topology, Apple hazard mode policy, WebGPU fallback coverage, dynamic-resolution scope, output performance targets and release class.

## Future proof obligations
- Compiler/test graph fixtures: deterministic DAG; cycles, R/W, subresource/format constraints; external side effects and history semantics; generated sync plan checked against RHI and backend validation.
- Real GPUs Windows Vulkan/D3D12 (enhanced conditional), Linux Vulkan vendor/Mesa, Apple Silicon native Metal heaps, browser WebGPU usage-scope tests and fallback, with exact drivers/SDK. Do not equate docs CI or CPU mocks with GPU validation.
- Multi-queue and multi-frame fences proven before any alias, including asynchronous compute, readback/present/resize and device loss. Fault injection and GPU debug validation; no corruption or stale handle.
- Budget/pressure benchmarks with memory tier, p50/p95/p99 CPU graph compile and GPU stalls/VRAM, alias savings vs conservative baseline; low-memory and UMA devices.
- Security/abuse/fuzz of pass/resource/offset/overflow/uninitialized and MCP authorization, redaction. Exact library license/SBOM and compilation flags.
- Implemented/merged GFX-01 and CORE-03 predecessors, GFX-02 stable layout contract, selected backend policy, approved Scope/Requirements/DoD/release class, exact source files/build/test commands and fresh SHA-256 Context Lock.
- No code in docs P00; Research approval **does not** unlock #31 or any other 79 implementation WOs.

See [architecture](../architecture/gfx-03-render-graph-gpu-memory.md), [matrix](../research/gfx-03-rendergraph-technology-matrix.md), [contract](../contracts/gfx-03-render-graph-api.md), [future tests](../testing/gfx-03-acceptance-matrix.md).
