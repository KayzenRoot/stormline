# NLE-PRPLAN-DATA-03-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `cfce630`. **Formal packet:** `NLE-PRPLAN-DATA-03-04`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md). **WO:** [NLE-PRPLAN-DATA-03-04](../work-orders/NLE-PRPLAN-DATA-03-04.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-03-01..03 are approved/completed. This gate activates only texture metadata validation after Docs Validation and pt-BR audit. It does not authorize decoders, conversion, animation/audio/composite validation, receipts, persistence, native I/O, network, ABI or release.

## DATA-02 capability admission

- Formal dependency is `DATA-02`, `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- Admission uses completed DATA-02 capabilities.
- `module_completion_claimed=false`.
- No decoder, archive, native filesystem, persistence, network, MCP or release capability is used.

## Activated scope

- `src/stormline/data/import/texture_metadata.hpp`
- `tests/core/data03_texture_tests.cpp`
- Additive CMake/workflow entries
- `docs/evidence/NLE-PRPLAN-DATA-03-04.md`

No other production file is authorized. TEX-01 is required.

## Gate state after merge

- Manifest root `DATA03_04_READY_L1_CAPABILITY_OVERLAY`: **658 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 71 `COMPLETED`, 18 approved gates**.
- `DATA-03-04` becomes `EXECUTOR_READY`; `DATA-03-05`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-03-04`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL.
