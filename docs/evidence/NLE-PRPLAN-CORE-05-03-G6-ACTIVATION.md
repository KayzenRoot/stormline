# NLE-PRPLAN-CORE-05-03 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `de206bfc17f2f43011ca06effe9993baee85cab3`. **Formal packet:** `NLE-PRPLAN-CORE-05-03`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-03](../work-orders/NLE-PRPLAN-CORE-05-03.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01 governance and CORE-05-02 contract are approved. This gate activates only the scalar/error/vector slice after Docs Validation and pt-BR audit. It does not authorize matrices, quaternions, coordinates, units, precision, IDs, SIMD, third-party math, serialization, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/math_types.hpp`
- `src/stormline/core/math/vec.hpp`
- `tests/core/core05_vector_tests.cpp`
- Additive `CMakeLists.txt` target/tests and `.github/workflows/core01-internal-headless.yml` filters.
- `docs/evidence/NLE-PRPLAN-CORE-05-03.md`.

No other production file is authorized. MATH-01/MATH-02 and typed `MathResult` fixtures are required. The scalar reference path is the only implementation; no SIMD, fast-math, FMA or third-party type.

## Gate state after merge

- Manifest root `CORE05_03_READY_L1_CAPABILITY_OVERLAY`: **699 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 38 `COMPLETED`, 10 approved gates**.
- `CORE-05-03` becomes `EXECUTOR_READY`; `CORE-05-04`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-03`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
