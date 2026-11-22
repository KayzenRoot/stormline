# NLE-PRPLAN-DATA-01-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `866309f708924ae2d9a0d9ac2519c22272602222`. **Formal packet:** `NLE-PRPLAN-DATA-01-01`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-governance-v0](../contracts/data-01-governance-v0.md). **WO:** [NLE-PRPLAN-DATA-01-01](../work-orders/NLE-PRPLAN-DATA-01-01.md).

## Authorization

The owner instructed continuation on 2026-11-22 after CORE-06 closed. This gate prepares only DATA-01 governance after Docs Validation and pt-BR audit. It does not activate `DATA-01-02`, write VFS code, select PhysicsFS/libzip, add native I/O/writes/network, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Governance scope

- ADR-0110 and ADR-0009 as planning direction only.
- Owned logical namespace, read-only default, path-validation invariants, mount/generation policy.
- First slices lexical path/mount/overlay/capability only; native I/O/archive/write/cache/recovery require separate G6.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.
- No code, dependency, CMake target, workflow, native filesystem, archive codec or public ABI.

## Gate state after merge

- Manifest root `DATA01_01_APPROVED_GOVERNANCE_ONLY`: **681 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 54 `COMPLETED`, 13 approved gates**.
- `DATA-01-01` becomes `APPROVED_GOVERNANCE`; `DATA-01-02`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, governance review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this governance gate.
