# NLE-PRPLAN-DATA-03-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `27131f2`. **Formal packet:** `NLE-PRPLAN-DATA-03-08`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-08](../work-orders/NLE-PRPLAN-DATA-03-08.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01..07 are approved/completed. This gate activates only bounded provenance receipts after Docs Validation and pt-BR audit.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission uses completed DATA-02 capabilities.
- `module_completion_claimed=false`.
- No persistence, serialization, native filesystem, network, MCP or release capability is used.

## Activated scope

- `src/stormline/data/import/import_receipt.hpp`
- `tests/core/data03_receipt_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-03-08.md`

No other production file is authorized. REC-01 is required.

## Gate state after merge

- Manifest root `DATA03_08_READY_L1_CAPABILITY_OVERLAY`: **654 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 75 `COMPLETED`, 18 approved gates**.
- `DATA-03-08` becomes `EXECUTOR_READY`; `DATA-03-09`..`-10` remain `PLANNED_BLOCKED`.
