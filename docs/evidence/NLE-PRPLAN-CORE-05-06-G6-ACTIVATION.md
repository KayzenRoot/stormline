# NLE-PRPLAN-CORE-05-06 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `e2277fd6710c7db4b1c9c1cf709d39f1d3030574`. **Formal packet:** `NLE-PRPLAN-CORE-05-06`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-06](../work-orders/NLE-PRPLAN-CORE-05-06.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01..05 are approved/completed. This gate activates only explicit units after Docs Validation and pt-BR audit. It does not authorize precision/origin, IDs, backend conversion, SIMD, third-party math, serialization, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/units.hpp`
- `tests/core/core05_unit_tests.cpp`
- Additive `CMakeLists.txt` test target and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-06.md`.

No other production file is authorized. MATH-07 and compile-time unit separation are required. No implicit conversion or backend adapter exists.

## Gate state after merge

- Manifest root `CORE05_06_READY_L1_CAPABILITY_OVERLAY`: **696 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 41 `COMPLETED`, 10 approved gates**.
- `CORE-05-06` becomes `EXECUTOR_READY`; `CORE-05-07`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-06`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
