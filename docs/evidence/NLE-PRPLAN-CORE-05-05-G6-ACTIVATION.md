# NLE-PRPLAN-CORE-05-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `a9e1fce752e8190d875caa5d7fea7415d0a6c8ab`. **Formal packet:** `NLE-PRPLAN-CORE-05-05`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-05](../work-orders/NLE-PRPLAN-CORE-05-05.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01/02/03/04 are approved/completed. This gate activates only coordinate-space wrappers after Docs Validation and pt-BR audit. It does not authorize units, precision, IDs, backend clip/projection, SIMD, third-party math, serialization, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/coords.hpp`
- `tests/core/core05_coord_tests.cpp`
- Additive `CMakeLists.txt` test target and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-05.md`.

No other production file is authorized. MATH-06 and compile-time mismatch fixtures are required. No world/view/clip/pixel conversion is implemented.

## Gate state after merge

- Manifest root `CORE05_05_READY_L1_CAPABILITY_OVERLAY`: **697 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 40 `COMPLETED`, 10 approved gates**.
- `CORE-05-05` becomes `EXECUTOR_READY`; `CORE-05-06`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-05`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
