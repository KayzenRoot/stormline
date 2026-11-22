# NLE-PRPLAN-DATA-01-08 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `932950f5c5c81b1a753680c49d37396d48a2fa13`. **Formal packet:** `NLE-PRPLAN-DATA-01-08`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-08](../work-orders/NLE-PRPLAN-DATA-01-08.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-01-01..07 are approved/completed. This gate activates only the memory storage abstraction after Docs Validation and pt-BR audit. It does not authorize native filesystem access, archive codecs, host writes, persistence, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/data/vfs/vfs_storage.hpp`
- `tests/core/data01_storage_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-DATA-01-08.md`.

No other production file is authorized. STORAGE-01 is required. No OS path, file descriptor, allocation, archive, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA01_08_READY_L1_CAPABILITY_OVERLAY`: **674 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 59 `COMPLETED`, 14 approved gates**.
- `DATA-01-08` becomes `EXECUTOR_READY`; `DATA-01-09`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-01-08`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
