# NLE-PRPLAN-CORE-05-04 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `c81778bc22a6df36553b249e9311772dbf87a19e`. **Formal packet:** `NLE-PRPLAN-CORE-05-04`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-04](../work-orders/NLE-PRPLAN-CORE-05-04.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01/02/03 are approved/completed. This gate activates only matrices and quaternions after Docs Validation and pt-BR audit. It does not authorize coordinates, units, precision, IDs, SIMD, third-party math, serialization, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/mat.hpp`
- `src/stormline/core/math/quat.hpp`
- `tests/core/core05_matrix_quat_tests.cpp`
- Additive `CMakeLists.txt` test target and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-04.md`.

No other production file is authorized. MATH-03/MATH-04/MATH-05 are required. Column-major storage is `elements[column * N + row]`; no clip/projection, SIMD, fast-math, FMA or third-party type.

## Gate state after merge

- Manifest root `CORE05_04_READY_L1_CAPABILITY_OVERLAY`: **698 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 39 `COMPLETED`, 10 approved gates**.
- `CORE-05-04` becomes `EXECUTOR_READY`; `CORE-05-05`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-04`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
