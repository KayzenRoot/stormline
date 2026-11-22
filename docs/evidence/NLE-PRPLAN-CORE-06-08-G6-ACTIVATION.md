# NLE-PRPLAN-CORE-06-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `07caee3493de5744c9933ea82090d4774a459825`. **Formal packet:** `NLE-PRPLAN-CORE-06-08`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-08](../work-orders/NLE-PRPLAN-CORE-06-08.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01..07 are approved/completed. This gate activates only local opt-in telemetry after Docs Validation and pt-BR audit. It does not authorize network, upload, cloud/analytics service, consent UI, persistence, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/diag/telemetry.hpp`
- `tests/core/core06_telemetry_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-CORE-06-08.md`.

No other production file is authorized. TEL-01 is required. No network socket, upload, file, cloud service, external SDK or third-party type is permitted.

## Gate state after merge

- Manifest root `CORE06_08_READY_L1_CAPABILITY_OVERLAY`: **684 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 51 `COMPLETED`, 12 approved gates**.
- `CORE-06-08` becomes `EXECUTOR_READY`; `CORE-06-09`/`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-06-08`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
