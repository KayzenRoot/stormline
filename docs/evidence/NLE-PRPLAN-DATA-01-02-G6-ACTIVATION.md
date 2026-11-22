# NLE-PRPLAN-DATA-01-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `626a11c4c198a8eb32373b733b7353c84980f4a0`. **Formal packet:** `NLE-PRPLAN-DATA-01-02`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md). **WO:** [NLE-PRPLAN-DATA-01-02](../work-orders/NLE-PRPLAN-DATA-01-02.md).

## Authorization

The owner instructed continuation on 2026-11-22. DATA-01-01 governance is `APPROVED_GOVERNANCE`; this gate prepares only the `DATA-01-02` contract after Docs Validation and pt-BR audit. It does not activate `DATA-01-03`, write VFS code, select PhysicsFS/libzip, add native I/O/writes/network, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Contract scope

- ASCII path validation and bounded components.
- Read-only mount table with generation.
- Deterministic overlay resolution.
- Workspace/mount read capabilities.
- Bounded cache keyed by mount/generation/path.
- Memory-only storage abstraction.
- PATH/MOUNT/OVERLAY/CAP/CACHE/STORAGE and QLF oracles; exact `DATA-01-03`..`-09` allowlists.
- No implementation, dependency, native path, public ABI, serialization or release.

## Gate state after merge

- Manifest root `DATA01_02_APPROVED_CONTRACT_ONLY`: **680 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 54 `COMPLETED`, 14 approved gates**.
- `DATA-01-02` becomes `APPROVED_CONTRACT`; `DATA-01-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this contract gate.
