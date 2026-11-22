# NLE-PRPLAN-CORE-06-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `7187cf2750cb3a8fda32b5dfceb7acad00fa98e8`. **Formal packet:** `NLE-PRPLAN-CORE-06-04`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-04](../work-orders/NLE-PRPLAN-CORE-06-04.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01/02/03 are approved/completed. This gate activates only traces after Docs Validation and pt-BR audit. It does not authorize counters, crash, profiling, telemetry, network/file I/O, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/diag/trace.hpp`
- `tests/core/core06_trace_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-CORE-06-04.md`.

No other production file is authorized. TRACE-01 is required. No counter/crash/profile/telemetry, allocation, file, network or third-party type is permitted.

## Gate state after merge

- Manifest root `CORE06_04_READY_L1_CAPABILITY_OVERLAY`: **688 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 47 `COMPLETED`, 12 approved gates**.
- `CORE-06-04` becomes `EXECUTOR_READY`; `CORE-06-05`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-06-04`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
