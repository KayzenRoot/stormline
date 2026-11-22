# NLE-PRPLAN-CORE-06-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `56a31a7e9a79cf5e9a92a58bd840711b51023145`. **Formal packet:** `NLE-PRPLAN-CORE-06-06`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-06](../work-orders/NLE-PRPLAN-CORE-06-06.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01..05 are approved/completed. This gate activates only the local crash envelope after Docs Validation and pt-BR audit. It does not authorize a crash handler, dump, upload, network/file I/O, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/diag/crash.hpp`
- `tests/core/core06_crash_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-CORE-06-06.md`.

No other production file is authorized. CRASH-01 is required. No signal handler, minidump, parser, symbolication, file, network, allocation or third-party type is permitted.

## Gate state after merge

- Manifest root `CORE06_06_READY_L1_CAPABILITY_OVERLAY`: **686 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 49 `COMPLETED`, 12 approved gates**.
- `CORE-06-06` becomes `EXECUTOR_READY`; `CORE-06-07`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-06-06`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
