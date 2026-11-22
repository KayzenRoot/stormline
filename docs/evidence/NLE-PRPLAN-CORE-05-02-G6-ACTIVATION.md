# NLE-PRPLAN-CORE-05-02 — G6 contract activation

**Status:** `G6 CONTRACT PROPOSAL / NO CODE AUTHORIZED / CORE-01 CAPABILITY ADMISSION`. **Base main:** `d08150a11b9688482ae2aa4d84b3a5756830fa75`. **Formal packet:** `NLE-PRPLAN-CORE-05-02`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md). **WO:** [NLE-PRPLAN-CORE-05-02](../work-orders/NLE-PRPLAN-CORE-05-02.md).

## Authorization

The owner instructed continuation on 2026-11-22. CORE-05-01 governance is `APPROVED_GOVERNANCE`; this gate prepares only the `CORE-05-02` contract after Docs Validation and pt-BR audit. It does not activate `CORE-05-03`, write math code, select GLM/Eigen/DirectXMath/MathFu, add SIMD, approve serialization/ABI/release or declare CORE-01 complete.

## CORE-01 capability admission

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified.
- Admission is limited to completed `CORE-01-03` headless build/test, `-06` portable paths, `-07` SDL3 build baseline, `-08` native CI matrix, `-12` lifecycle requests and `-13` capability graph.
- `module_completion_claimed=false`.
- No window/input/DPI/IME/hotplug/sleep-resume/soak/renderer/GPU/audio/network/public ABI/release capability is used.

## Contract scope

- Owned `f32`/`f64` aliases, `MathError`, `MathResult<T>`, `Vec2/3/4`, `Mat3/4`, `Quat` and exact operation names.
- Right-handed `+X/+Y-up/-Z-forward`, meters/seconds/radians and column-vector algebra.
- Column-major storage declared as `elements[column * N + row]`, separate from multiplication order.
- Explicit `WorldSpace`/`LocalSpace`/`ViewSpace`/`ClipSpace`/`PixelSpace`, `Position3`, `Direction3`, `Transform3`; no implicit backend conversion.
- Unit tags and explicit degrees/radians, length and time conversions.
- `WorldPosition` `f64` global truth, `LocalPosition` `f32` relative payload, `OriginEpoch` and rebase that preserves global position exactly.
- `PersistentId` opaque 128-bit value versus `RuntimeHandle{index,generation}`; big-endian ID bytes; no address identity.
- Typed errors and MATH-01..MATH-12 oracles; exact `CORE-05-03`..`-09` allowlists.
- No implementation, dependency, public ABI, serialization format or release.

## Gate state after merge

- Manifest root `CORE05_02_APPROVED_CONTRACT_ONLY`: **700 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 38 `COMPLETED`, 10 approved gates**.
- `CORE-05-02` becomes `APPROVED_CONTRACT`; `CORE-05-03`..`-10` remain `PLANNED_BLOCKED`.
- Selector denies every ID; registry byte-identical; 80/80 module WOs `BLOCKED`.

## Proof obligations

Docs Validation, contract review, selector denial, registry byte-identity, pt-BR audit, no HIGH/CRITICAL. No code/native PASS is claimed by this contract gate.
