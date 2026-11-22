# NLE-PRPLAN-CORE-05-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `cdda5ab9c4082e3ead5c42317c8b1277416dc0be`. **Formal packet:** `NLE-PRPLAN-CORE-05-07`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-07](../work-orders/NLE-PRPLAN-CORE-05-07.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01..06 are approved/completed. This gate activates only precision/origin after Docs Validation and pt-BR audit. It does not authorize stable IDs, serialization, backend conversion, SIMD, third-party math, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/precision.hpp`
- `tests/core/core05_precision_tests.cpp`
- Additive `CMakeLists.txt` test target and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-07.md`.

No other production file is authorized. MATH-08/MATH-09 and epoch/overflow/non-finite fixtures are required. No origin orchestration or serialization format is implemented.

## Gate state after merge

- Manifest root `CORE05_07_READY_L1_CAPABILITY_OVERLAY`: **695 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 42 `COMPLETED`, 10 approved gates**.
- `CORE-05-07` becomes `EXECUTOR_READY`; `CORE-05-08`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-07`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
