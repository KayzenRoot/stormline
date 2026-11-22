# NLE-PRPLAN-DATA-03-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `8d3fb1c`. **Formal packet:** `NLE-PRPLAN-DATA-03-03`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-03](../work-orders/NLE-PRPLAN-DATA-03-03.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01..02 are approved. This gate activates only descriptors, sniffing and plans after Docs Validation and pt-BR audit. It does not authorize decoders, conversion, texture/animation/audio validation, receipts, persistence, native I/O, network, ABI or release.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission uses completed DATA-02 identity, dependencies, tags, queries, schema, references and qualification.
- `module_completion_claimed=false`.
- No decoder, archive, native filesystem, persistence, network, MCP or release capability is used.

## Activated scope

- `src/stormline/data/import/import_types.hpp`
- `src/stormline/data/import/importer_registry.hpp`
- `tests/core/data03_importer_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-03-03.md`

No other production file is authorized. IMP-01 is required. No decoder, OS path, allocation, archive, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA03_03_READY_L1_CAPABILITY_OVERLAY`: **659 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 70 `COMPLETED`, 18 approved gates**.
- `DATA-03-03` becomes `EXECUTOR_READY`; `DATA-03-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-03-03`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No decoder/native PASS is claimed by this gate.
