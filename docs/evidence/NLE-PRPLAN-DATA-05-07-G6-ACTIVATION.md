# NLE-PRPLAN-DATA-05-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `1386689`. **Formal packet:** `NLE-PRPLAN-DATA-05-07`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-07](../work-orders/NLE-PRPLAN-DATA-05-07.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01..06 are approved/completed. This gate activates only incremental reuse planning after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/bundle/patch_plan.hpp`
- `tests/core/data05_patch_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-05-07.md`

PAT-01 is required. No download, signing, persistence or native I/O is permitted.

## Gate state after merge

- Manifest root `DATA05_07_READY_L1_CAPABILITY_OVERLAY`: **637 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 88 `COMPLETED`, 22 approved gates**.
- `DATA-05-07` becomes `EXECUTOR_READY`; `DATA-05-08`..`-09` remain `PLANNED_BLOCKED`.
