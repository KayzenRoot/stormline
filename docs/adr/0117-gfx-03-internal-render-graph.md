# ADR-0117 — GFX-03 internal logical render graph

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0016 (planning only) and ADR-0086 (capability admission). Does not select Vulkan, D3D12, Metal, WebGPU, VMA, D3D12MA, a native GPU allocator, public ABI or release.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-GFX-03-01` | **Parent:** GFX-03 | **Issue:** #31.

## Context

GFX-01 completed its logical RHI sequence and GFX-02 its logical shader pipeline, both as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-03 completed its internal scheduling sequence. GFX-03 has research, architecture, ADR-0016 `PROPOSED`, a semantic contract and a blocked WO; no executable render graph exists. ADR-0016 defers native backend, allocator, synchronization and hardware selection.

## Decision

- **A:** ADR-0016 remains planning direction only. No Vulkan/D3D12/Metal/WebGPU, VMA/D3D12MA, native heap, driver barrier, swapchain, rendering or GPU execution is selected.
- **B:** The first GFX-03 sequence is an in-memory **logical render graph compiler**: bounded pass/resource declarations, hazard dependency DAG with cycle detection, logical synchronization transitions, transient lifetime/alias planning and VRAM budget admission.
- **C:** No native command recording, GPU submission, fence/timeline, pixel output, rendering, performance timing or physical hardware is implemented or claimed.
- **D:** Native backend/allocator/synchronization requires a separate approved ADR/G6 with exact API/SDK pins, license/SBOM, target hardware and driver matrix.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for graph/hazard/memory planning. Release class is `INTERNAL_ONLY`; no rendering, ABI, performance, security or release claim.
- **F:** Ownership: GFX-01 RHI capabilities/handles; CORE-03 CPU scheduling; CORE-02 CPU allocation; GFX-02 shader reflection; DATA-02/05 assets; GFX-04+ visual algorithms; PLAT-03 browser policy; EDIT/AI/MCP read-only plan inspection.
- **G:** Invalid passes/resources, ambiguous writers, uninitialized reads, cycles, incompatible aliases and budget overflow fail closed with typed errors; no path may turn a failed graph into a rendering success claim.

## Required before code

1. `GFX-03-02` contract with exact C++ API, capacities, deterministic ordering, hazards, sync/alias/budget oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for DAG/cycle, read/write hazards, sync transitions, transient lifetimes, alias safety and budget admission.
4. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no native GPU/rendering/ABI/release claim.

## Consequence

- `GFX-03-01` may be prepared as `APPROVED_GOVERNANCE`; `GFX-03-02`..`-09` remain `PLANNED_BLOCKED`.
- GFX-01/02, DATA-01..05 and CORE-03 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; no renderer is claimed.
