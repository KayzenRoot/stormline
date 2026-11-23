# NLE-PRPLAN-GFX-02-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `5cadb01`. **Formal packet:** `NLE-PRPLAN-GFX-02-03`. **ADR:** [ADR-0116](../adr/0116-gfx-02-internal-shader-pipeline.md). **Contract:** [gfx-02-shader-internal-v0](../contracts/gfx-02-shader-internal-v0.md). **WO:** [NLE-PRPLAN-GFX-02-03](../work-orders/NLE-PRPLAN-GFX-02-03.md).

## Authorization

The owner authorized continuation on 2026-11-22. GFX-02-01/-02 are approved. This gate activates only the SSCL-0 parser/IR after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `GFX-01` and `DATA-03`; neither is module-qualified.
- Admission uses completed GFX-01 RHI and DATA-03 import/validation capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/graphics/shader/shader_types.hpp`
- `src/stormline/graphics/shader/shader_parser.hpp`
- `tests/core/gfx02_shader_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-GFX-02-03.md`

PAR-01 is required. No native compiler/GPU/artifact is permitted.

## Gate state after merge

- Manifest root `GFX02_03_READY_L1_CAPABILITY_OVERLAY`: **622 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 99 `COMPLETED`, 26 approved gates**.
- `GFX-02-03` becomes `EXECUTOR_READY`; `GFX-02-04`..`-09` remain `PLANNED_BLOCKED`.
