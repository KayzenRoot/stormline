# NLE-PRPLAN-DATA-05-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `1a9f3e9`. **Formal packet:** `NLE-PRPLAN-DATA-05-05`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md). **WO:** [NLE-PRPLAN-DATA-05-05](../work-orders/NLE-PRPLAN-DATA-05-05.md).

## Authorization

The owner authorized continuation on 2026-11-22. DATA-05-01..04 are approved/completed. This gate activates only in-memory streaming after Docs Validation and pt-BR audit.

## Capability admission

- Formal dependencies are `DATA-03` and `DATA-04`; neither is module-qualified.
- Admission uses completed DATA-03 and DATA-04 capabilities.
- `module_completion_claimed=false`.

## Activated scope

- `src/stormline/data/bundle/stream_window.hpp`
- `tests/core/data05_stream_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-05-05.md`

STR-01 is required. No network, persistence or native I/O is permitted.

## Gate state after merge

- Manifest root `DATA05_05_READY_L1_CAPABILITY_OVERLAY`: **639 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 86 `COMPLETED`, 22 approved gates**.
- `DATA-05-05` becomes `EXECUTOR_READY`; `DATA-05-06`..`-09` remain `PLANNED_BLOCKED`.
