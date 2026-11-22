# NLE-PRPLAN-DATA-02-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `f846dad`. **Formal packet:** `NLE-PRPLAN-DATA-02-08`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-08](../work-orders/NLE-PRPLAN-DATA-02-08.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-02-01..07 are approved/completed. This gate activates only ID-based references, rename and impact after Docs Validation and pt-BR audit. It does not authorize persistence, SQLite, serialization, native I/O, network, ABI or release.

## DATA-01 capability admission

- Formal dependency is `DATA-01`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission is limited to completed DATA-01 path validation, mount table, overlay, capabilities and qualification.
- `module_completion_claimed=false`.
- No persistence, serialization, native filesystem, network, MCP or release capability is used.

## Activated scope

- `src/stormline/data/registry/asset_registry.hpp` additive reference/rename/impact methods.
- `tests/core/data02_reference_tests.cpp`
- Additive `CMakeLists.txt` target/test and workflow filters.
- `docs/evidence/NLE-PRPLAN-DATA-02-08.md`.

No other production file is authorized. REF-01 is required. No persistence, OS path, allocation, database, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA02_08_READY_L1_CAPABILITY_OVERLAY`: **664 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 67 `COMPLETED`, 16 approved gates**.
- `DATA-02-08` becomes `EXECUTOR_READY`; `DATA-02-09`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-02-08`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
