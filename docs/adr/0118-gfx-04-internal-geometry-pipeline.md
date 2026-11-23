# ADR-0118 — GFX-04 internal logical geometry and visibility pipeline

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0017 (planning only) and ADR-0086 (capability admission). Does not select a GPU API, mesh shader, indirect draw, meshoptimizer, external codec, streaming service, public ABI or release.**

**Date:** 2026-11-23 | **WO:** `NLE-PRPLAN-GFX-04-01` | **Parent:** GFX-04 | **Issue:** #32.

## Context

GFX-03 completed its internal logical render graph; DATA-05 completed its internal bundle/streaming sequence. GFX-04 has research, architecture, ADR-0017 `PROPOSED`, a semantic contract and a blocked WO. Native GPU, mesh shaders, indirect draws, external simplification libraries and physical hardware are not available or approved.

## Decision

- **A:** ADR-0017 remains planning direction only. No Vulkan/D3D12/Metal/WebGPU, mesh/task shader, indirect draw, GPU occlusion, VMA/D3D12MA, meshoptimizer or streaming service is selected.
- **B:** The first GFX-04 sequence is an in-memory **logical geometry visibility pipeline**: bounded instance sets and batching, conservative frustum/distance culling, LOD/HLOD selection, verified-chunk stream request planning, vegetation classification and geometry budget validation.
- **C:** No mesh decoding, simplification, cooking, GPU submission, rendering, occlusion query, indirect command, physical hardware or performance measurement is implemented or claimed.
- **D:** Native geometry/mesh-shader/streaming backends require a separate approved ADR/G6 with exact library/API pins, licenses/SBOM, target hardware and driver/browser matrix.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for culling/LOD/stream planning. Release class is `INTERNAL_ONLY`.
- **F:** Ownership: GFX-03 render graph; DATA-05 verified chunks; DATA-02 identities; GFX-01 RHI capabilities; CORE-05 coordinates; GFX-05 materials; world/vegetation modules placement; CORE-03 CPU jobs; CORE-02 CPU scratch.
- **G:** Unknown bounds and uncertain visibility are conservatively visible; invalid data, cycles, unverified chunks and invalid LOD chains fail closed with typed errors. No false-negative culling is permitted by construction.

## Required before code

1. `GFX-04-02` contract with exact C++ API, capacities, conservative culling rules, LOD/stream/budget oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for instancing/batching, conservative culling, LOD/HLOD, stream requests, vegetation classes and geometry budgets.
4. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no GPU/rendering/ABI/release claim.

## Consequence

- `GFX-04-01` may be prepared as `APPROVED_GOVERNANCE`; `GFX-04-02`..`-10` remain `PLANNED_BLOCKED`.
- GFX-01/02/03, DATA-01..05 and CORE-03/05 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; no renderer is claimed.
