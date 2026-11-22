# ADR-0115 — GFX-01 governance and backend-neutral RHI direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0014 (planning only) and ADR-0086 (capability admission). Does not select Vulkan/D3D12/Metal/SDL GPU, approve native GPU code, rendering, public ABI, release or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-GFX-01-01` | **Parent:** GFX-01 | **Issue:** #29.

## Context

DATA-05 closed its internal logical sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. GFX-01 (`Graphics Abstraction/RHI`) has research, architecture, ADR-0014 `PROPOSED`, a semantic contract and a blocked WO; no executable RHI exists. The owner has not selected a native graphics API; physical GPU/driver qualification is unavailable in the current CI.

## Decision

- **A:** ADR-0014 is ratified only as planning direction. No Vulkan, D3D12, Metal, SDL3 GPU, Dawn/wgpu, bgfx, SDK or driver dependency is selected by this ADR.
- **B:** The first GFX-01 sequence is a backend-neutral, in-memory logical RHI: opaque adapters, device generations, lifecycle states, queues, buffer/texture descriptors and handles, synchronization barriers and feature tiers. A **Null/reference backend** exercises the contract without opening a GPU.
- **C:** No native device creation, swapchain, shader/pipeline, rendering, presentation, GPU timing, driver validation or physical hardware is implemented or claimed.
- **D:** Native backends require a separate approved ADR/G6 with exact API/SDK pins, license/SBOM, CI hardware and driver matrix.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for implementation/state handling. Release class is `INTERNAL_ONLY`; no rendering, ABI, performance, security or release claim.
- **F:** CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-05 math/IDs; CORE-06 diagnostics; DATA-05 bundles; GFX-02 shaders; GFX-03 render graph.
- **G:** Stale device/resource generations, unsupported features, invalid descriptors and invalid barriers fail closed with typed errors.

## Required before code

1. `GFX-01-02` contract with exact C++ API, error model, capacities, state transitions and per-slice test oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for device generation/loss, resource lifetime, queue roles, descriptor bounds, barrier validation and feature tiers.
4. Separate G6/ADR for any native backend, shader compiler, swapchain, rendering and physical GPU qualification.
5. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no GPU/rendering/ABI/release claim.

## Consequence

- `GFX-01-01` may be prepared as `APPROVED_GOVERNANCE`; `GFX-01-02`..`-10` remain `PLANNED_BLOCKED`.
- DATA-05..01 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not renderer-ready.
