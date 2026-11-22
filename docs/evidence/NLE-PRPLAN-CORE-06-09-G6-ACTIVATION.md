# NLE-PRPLAN-CORE-06-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `51342e965bbb38144869e665f71801d3183821c6`. **Formal packet:** `NLE-PRPLAN-CORE-06-09`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-diagnostics-v0](../contracts/core-06-diagnostics-v0.md). **WO:** [NLE-PRPLAN-CORE-06-09](../work-orders/NLE-PRPLAN-CORE-06-09.md).

## Authorization

The owner authorized completion of CORE-06 on 2026-11-22. CORE-06-01..08 are approved/completed. This gate activates only the integrated internal qualification test after Docs Validation and pt-BR audit. It does not authorize new API, network/upload, crash handler, profiler, serialization, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `tests/core/core06_diagnostics_qualification_tests.cpp`
- Additive `CMakeLists.txt` target/CTest entries and workflow filters.
- `docs/evidence/NLE-PRPLAN-CORE-06-09.md`.

No production source change is authorized. QLF-D01..04 are required. Qualification is internal/CI-only and does not certify network privacy, real crash capture, profiler overhead, hardware or release.

## Gate state after merge

- Manifest root `CORE06_09_READY_L1_CAPABILITY_OVERLAY`: **683 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 52 `COMPLETED`, 12 approved gates**.
- `CORE-06-09` becomes `EXECUTOR_READY`; `CORE-06-10` remains `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-CORE-06-09`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
