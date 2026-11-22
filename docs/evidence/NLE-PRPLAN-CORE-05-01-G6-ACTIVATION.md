# NLE-PRPLAN-CORE-05-01 — G6 governance activation

**Status:** `G6 GOVERNANCE PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `0e5d6e5ae0b418823d667aa7e67d0e82154d532c`. **Packet:** `NLE-PRPLAN-CORE-05-01`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-governance-v0](../contracts/core-05-governance-v0.md). **WO:** [NLE-PRPLAN-CORE-05-01](../work-orders/NLE-PRPLAN-CORE-05-01.md).

## Authorization

The owner instructed continuation on 2026-11-22 after CORE-04 closeout. This gate activates only `CORE-05-01` governance after Docs Validation and pt-BR audit. It does not activate `CORE-05-02`, write math code, select GLM/Eigen/DirectXMath, approve release/ABI or declare CORE-01 complete.

## CORE-01 capability admission

Formal `CORE-01` dependency remains; CORE-01 is not module-qualified. Admission is limited to completed `-03` headless build/test, `-06` portable paths, `-07` SDL3 baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph. `module_completion_claimed=false`; window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release not used.

## Governance scope

- ADR-0007 planning-only: right-handed +Y-up/-Z-forward, meters/seconds/radians, column-vector, storage separate from composition.
- f32 local/render; f64 global-origin candidate; signed-cell alternative unselected.
- Owned scalar types first; GLM/Eigen/DirectXMath/MathFu evaluation only; no third-party type in core/public API.
- Persistent opaque IDs vs runtime generational handles; typed math errors.
- Risk `LOW` docs / `ELEVATED` implementation; release `INTERNAL_ONLY`.

## Gate state after merge

Manifest root `CORE05_01_APPROVED_GOVERNANCE_ONLY`: **701 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 38 `COMPLETED`, 9 approved gates**; `CORE-05-02`..`-10` blocked; selector denies all; registry byte-identical.

No code/native PASS is claimed by this governance gate.
