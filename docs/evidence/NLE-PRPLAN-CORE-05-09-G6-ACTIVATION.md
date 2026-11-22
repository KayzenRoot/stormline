# NLE-PRPLAN-CORE-05-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `5553af9434fdc86fde801a727432fc54d692cefc`. **Formal packet:** `NLE-PRPLAN-CORE-05-09`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-09](../work-orders/NLE-PRPLAN-CORE-05-09.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01..08 are approved/completed. This gate activates only the integrated internal qualification test after Docs Validation and pt-BR audit. It does not authorize production API changes, third-party math, SIMD, serialization, backend projection, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `tests/core/core05_qualification_tests.cpp`
- Additive `CMakeLists.txt` target/CTest entries and workflow TSan target list.
- `docs/evidence/NLE-PRPLAN-CORE-05-09.md`.

No production source change is authorized. QLF-01..04 are required. The qualification is internal/CI-only and does not certify physical hardware, soak, SIMD, compiler bit-identity, ABI or release.

## Gate state after merge

- Manifest root `CORE05_09_READY_L1_CAPABILITY_OVERLAY`: **693 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 44 `COMPLETED`, 10 approved gates**.
- `CORE-05-09` becomes `EXECUTOR_READY`; `CORE-05-10` remains `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-05-09`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
