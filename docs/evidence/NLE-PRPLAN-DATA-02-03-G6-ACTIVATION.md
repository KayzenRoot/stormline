# NLE-PRPLAN-DATA-02-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `840a7ff`. **Formal packet:** `NLE-PRPLAN-DATA-02-03`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md). **WO:** [NLE-PRPLAN-DATA-02-03](../work-orders/NLE-PRPLAN-DATA-02-03.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-02-01..02 are approved. This gate activates only the identity/path core after Docs Validation and pt-BR audit. It does not authorize dependencies, tags, queries, schema, references, persistence, SQLite, native I/O, network, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/data/registry/registry_types.hpp`
- `src/stormline/data/registry/asset_registry.hpp` core methods
- `tests/core/data02_id_tests.cpp`
- Additive `CMakeLists.txt` target/test and workflow filters
- `docs/evidence/NLE-PRPLAN-DATA-02-03.md`

No other production file is authorized. ID-01 is required. No persistence, OS path, allocation, database, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA02_03_READY_L1_CAPABILITY_OVERLAY`: **669 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 62 `COMPLETED`, 16 approved gates**.
- `DATA-02-03` becomes `EXECUTOR_READY`; `DATA-02-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-02-03`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
