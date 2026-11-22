# NLE-PRPLAN-DATA-01-09 — G6 qualification activation

**Status:** `G6 QUALIFICATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `962d780885fcf249be4f92e851615a33a76d745b`. **Formal packet:** `NLE-PRPLAN-DATA-01-09`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-09](../work-orders/NLE-PRPLAN-DATA-01-09.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-01-01..08 are approved/completed. This gate activates only the integrated QLF qualification after Docs Validation and pt-BR audit. It does not authorize production changes, native filesystem access, archive codecs, host writes, persistence, hardware/soak, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `tests/core/data01_vfs_qualification_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-DATA-01-09.md`.

No production file is authorized. QLF-01..04 are required. Qualification is internal/CI-only and is not physical hardware, sandbox, ABI or release qualification.

## Gate state after merge

- Manifest root `DATA01_09_READY_L1_CAPABILITY_OVERLAY`: **673 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 60 `COMPLETED`, 14 approved gates**.
- `DATA-01-09` becomes `EXECUTOR_READY`; `DATA-01-10` remains `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-01-09`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No native/hardware/release PASS is claimed by this gate.
