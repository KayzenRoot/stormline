# NLE-PRPLAN-CORE-05-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `4fea483465cdbc54aec7a3ba52533842236c6a33`. **Formal packet:** `NLE-PRPLAN-CORE-05-08`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-08](../work-orders/NLE-PRPLAN-CORE-05-08.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01..07 are approved/completed. This gate activates only stable ID/runtime handle values after Docs Validation and pt-BR audit. It does not authorize ECS, asset persistence, serialization, SIMD, third-party math, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/core/math/ids.hpp`
- `tests/core/core05_id_tests.cpp`
- Additive `CMakeLists.txt` test target and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-08.md`.

No other production file is authorized. MATH-10/MATH-11, zero-ID, byte-order and generation-recycling fixtures are required. No world/ECS or persistence layer is implemented.

## Gate state after merge

- Manifest root `CORE05_08_READY_L1_CAPABILITY_OVERLAY`: **694 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 43 `COMPLETED`, 10 approved gates**.
- `CORE-05-08` becomes `EXECUTOR_READY`; `CORE-05-09`/`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-08`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
