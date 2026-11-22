# NLE-PRPLAN-DATA-05-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `31c22d3`. **Formal packet:** `NLE-PRPLAN-DATA-05-03`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-03](../work-orders/NLE-PRPLAN-DATA-05-03.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01..02 are approved. This gate activates only target/cook planning after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/bundle/bundle_types.hpp`
- `src/stormline/data/bundle/cook_plan.hpp`
- `tests/core/data05_target_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-05-03.md`

TGT-01 is required. No codec, persistence or native I/O is permitted.

## Gate state after merge

- Manifest root `DATA05_03_READY_L1_CAPABILITY_OVERLAY`: **641 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 84 `COMPLETED`, 22 approved gates**.
- `DATA-05-03` becomes `EXECUTOR_READY`; `DATA-05-04`..`-09` remain `PLANNED_BLOCKED`.
