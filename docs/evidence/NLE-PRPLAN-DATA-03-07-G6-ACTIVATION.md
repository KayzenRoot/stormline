# NLE-PRPLAN-DATA-03-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `778c06d`. **Formal packet:** `NLE-PRPLAN-DATA-03-07`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-07](../work-orders/NLE-PRPLAN-DATA-03-07.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01..06 are approved/completed. This gate activates only composite metadata validation after Docs Validation and pt-BR audit.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission uses completed DATA-02 capabilities.
- `module_completion_claimed=false`.
- No decoder, archive, native filesystem, persistence, network, MCP or release capability is used.

## Activated scope

- `src/stormline/data/import/import_validation.hpp`
- `tests/core/data03_validation_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-03-07.md`

No other production file is authorized. VAL-01 is required.

## Gate state after merge

- Manifest root `DATA03_07_READY_L1_CAPABILITY_OVERLAY`: **655 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 74 `COMPLETED`, 18 approved gates**.
- `DATA-03-07` becomes `EXECUTOR_READY`; `DATA-03-08`..`-10` remain `PLANNED_BLOCKED`.
