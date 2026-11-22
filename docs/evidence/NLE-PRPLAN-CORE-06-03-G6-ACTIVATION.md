# NLE-PRPLAN-CORE-06-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `ce6858841d38d06c116eca3a9f7f7009dd16de5c`. **Formal packet:** `NLE-PRPLAN-CORE-06-03`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-03](../work-orders/NLE-PRPLAN-CORE-06-03.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01/02 are approved. This gate activates only types/logs after Docs Validation and pt-BR audit. It does not authorize traces, counters, crash handler/envelope, profiling, telemetry, network/file I/O, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/diag/diagnostics_types.hpp`
- `src/stormline/core/diag/log.hpp`
- `tests/core/core06_log_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-CORE-06-03.md`.

No other production file is authorized. LOG-01/02/03 are required. No allocation, file, network, third-party type or crash handler is permitted.

## Gate state after merge

- Manifest root `CORE06_03_READY_L1_CAPABILITY_OVERLAY`: **689 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 46 `COMPLETED`, 12 approved gates**.
- `CORE-06-03` becomes `EXECUTOR_READY`; `CORE-06-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-06-03`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
