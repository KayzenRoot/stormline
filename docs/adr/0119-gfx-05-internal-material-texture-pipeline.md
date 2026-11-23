# ADR-0119 — GFX-05 internal logical material and texture pipeline

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0018 (planning only) and ADR-0086 (capability admission). Does not select a GPU API, KTX2/Basis, image codec, shader compiler, GPU allocator, public ABI or release.**

**Date:** 2026-11-23 | **WO:** `NLE-PRPLAN-GFX-05-01` | **Parent:** GFX-05 | **Issue:** #33.

## Context

GFX-02 completed its logical shader pipeline and DATA-03 its import/validation sequence. GFX-05 has research, architecture, ADR-0018 `PROPOSED`, a semantic contract and a blocked WO. Native GPU, texture codecs, image decoders and physical hardware are not approved.

## Decision

- **A:** ADR-0018 remains planning direction only. No Vulkan/D3D12/Metal/WebGPU, KTX2/Basis, image decoder, GPU allocator or shader compiler is selected.
- **B:** The first GFX-05 sequence is an in-memory **logical material/texture pipeline**: PBR parameter validation, texture/mip metadata, optional virtual-page request planning, sampler/filter profiles, decal ordering and transparency sort/overdraw budgets.
- **C:** No image decode, texture encode, GPU upload, BRDF rendering, pixel output, hardware or performance measurement is implemented or claimed.
- **D:** Native texture/material backends require a separate approved ADR/G6 with exact codec/library pins, licenses/SBOM, target hardware and driver/browser matrix.
- **E:** Risk is `LOW` for documentation and `ELEVATED` for material/texture planning. Release class is `INTERNAL_ONLY`.
- **F:** Ownership: GFX-02 shader semantics; DATA-01/02/03/04/05 assets/import/cook; GFX-01 RHI; GFX-03 upload/residency; GFX-04 visibility; GFX-06 lighting; GFX-07 tone mapping; EDIT-05 authoring.
- **G:** Non-finite/out-of-range parameters, invalid mips, unsupported sampler combinations, duplicate decals, invalid alpha/blend states and budget overflow fail closed with typed errors.

## Required before code

1. `GFX-05-02` contract with exact C++ API, capacities, material/texture/sampler/decal/transparency oracles.
2. Individual G6 activation and explicit owner authorization per implementation slice.
3. Tests for PBR ranges, mip metadata, virtual pages, samplers, decals and transparency.
4. GCC/Clang/MSVC/AppleClang CI; no HIGH/CRITICAL; no GPU/rendering/ABI/release claim.

## Consequence

- `GFX-05-01` may be prepared as `APPROVED_GOVERNANCE`; `GFX-05-02`..`-10` remain `PLANNED_BLOCKED`.
- GFX-01..04, DATA-01..05 and CORE-02/03/05 remain `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; CORE-01 not module-qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; no material renderer is claimed.
