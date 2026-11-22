# NLE-PRPLAN-DATA-01-05 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `071b80a618d33ecde23d4d22b297e96b53d35cc3`. **Formal packet:** `NLE-PRPLAN-DATA-01-05`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-05](../work-orders/NLE-PRPLAN-DATA-01-05.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-01-01..04 are approved/completed. This gate activates only overlays after Docs Validation and pt-BR audit. It does not authorize capabilities, cache, storage, native I/O, writes, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/data/vfs/vfs_overlay.hpp`
- `tests/core/data01_overlay_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-DATA-01-05.md`.

No other production file is authorized. OVERLAY-01 is required. No capability/cache/storage, OS path, allocation, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA01_05_READY_L1_CAPABILITY_OVERLAY`: **677 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 56 `COMPLETED`, 14 approved gates**.
- `DATA-01-05` becomes `EXECUTOR_READY`; `DATA-01-06`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-01-05`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
