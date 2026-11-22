# NLE-PRPLAN-DATA-01-07 — G6 implementation activation

**Status:** `G6 IMPLEMENTATION ACTIVATION / CODE AUTHORIZED ONLY AFTER THIS GATE MERGES`. **Base main:** `0bc6987a90f81e61024f2e0b017a89fa9d0d37a5`. **Formal packet:** `NLE-PRPLAN-DATA-01-07`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-07](../work-orders/NLE-PRPLAN-DATA-01-07.md).

## Authorization

The owner authorized completion of DATA-01..04 on 2026-11-22. DATA-01-01..06 are approved/completed. This gate activates only the cache after Docs Validation and pt-BR audit. It does not authorize storage/native I/O, writes, dependency, ABI or release.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Activated scope

- `src/stormline/data/vfs/vfs_cache.hpp`
- `tests/core/data01_cache_tests.cpp`
- Additive `CMakeLists.txt` target/tests and workflow filters.
- `docs/evidence/NLE-PRPLAN-DATA-01-07.md`.

No other production file is authorized. CACHE-01 is required. No storage backend, OS path, allocation, network or third-party type is permitted.

## Gate state after merge

- Manifest root `DATA01_07_READY_L1_CAPABILITY_OVERLAY`: **675 `PLANNED_BLOCKED`, 1 `EXECUTOR_READY`, 58 `COMPLETED`, 14 approved gates**.
- `DATA-01-07` becomes `EXECUTOR_READY`; `DATA-01-08`..`-10` remain `PLANNED_BLOCKED`.
- Selector permits only `NLE-PRPLAN-DATA-01-07`; all other IDs remain denied; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, activation review, selector behavior, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this gate.
