# NLE-PRPLAN-CORE-05-02 — Typed math contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until CORE-05-03 G6.** **Gate:** G6 contract + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-02`. **Predecessor:** `CORE-05-01` governance. **Issue:** #22. **Base:** `d08150a11b9688482ae2aa4d84b3a5756830fa75`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-math-v0](../contracts/core-05-math-v0.md).

## OBJECTIVE

Freeze the first internal CORE-05 contract: owned scalar/vector/matrix/quaternion types, typed errors, explicit coordinate spaces, unit-bearing quantities, `f64` world position with origin epoch, stable persistent IDs versus generational runtime handles, and MATH-01..MATH-12 golden oracles. No implementation.

## CONTEXT

CORE-05-01 is `APPROVED_GOVERNANCE` only. ADR-0007 is ratified as planning direction; ADR-0108 limits admission to completed CORE-01 capabilities. CORE-01 is not module-qualified. This packet prepares the contract; no third-party math library, SIMD path, serialization format or ABI is selected.

## SCOPE

- Contract `core-05-math-v0`: exact logical API, conventions, error model, semantics, MATH-01..MATH-12 and exact file allowlists.
- Evidence of contract review and CORE-01 admission boundary.
- No implementation, dependency, CMake target or code test.

## OUT OF SCOPE

Math code, GLM/Eigen/DirectXMath/MathFu, SIMD intrinsics, serialization implementation, physics/netcode/GFX/WORLD integration, public ABI, release, CORE-01 completion, CORE-05-03 or any later packet.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, CORE-05 architecture/research, governance contract, module catalog, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086 capability rule; right-handed +Y-up/-Z-forward; meters/seconds/radians; column-vector algebra; column-major storage declared separately; no technology/dependency selection.

## ARCHITECTURE RULES

CORE-05 owns math value types, coordinate/unit tags, world precision/origin epoch and stable identifier contracts. CORE-01 platform/CPU, CORE-02 memory/alignment, CORE-03 scheduling, CORE-04 `TickId`, GFX clip/projection, SIM solver precision, DATA serialization, WORLD origin-shift orchestration and NET replication remain their owners. No architecture cycle.

## CONSTRAINTS

Risk `LOW` for this documentary contract; future implementation `ELEVATED`; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/ABI/release; header-only internal API; C++20; no exception across API. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact contract/API/errors/semantics/MATH matrix/allowlists.
- CORE-01 capability admission recorded; no technology, SIMD, serialization or code authorized.
- `CORE-05-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE05_02_APPROVED_CONTRACT_ONLY`: **700 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 38 `COMPLETED`, 10 approved gates**.
- Docs Validation and pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators and selector denial; contract review traceability. No native code test is authorized by this packet.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0108/0007, admission, no code/technology, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, missing admission, technology selected by inference, API/code implementation, manifest/registry drift, HIGH/CRITICAL, release/ABI claim. No code before CORE-05-03 G6.

## CONTEXT LOCK

Base `d08150a`; admission pins CORE-01-03/-06/-07/-08/-12/-13; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-02-G6-ACTIVATION.md` with contract review, admission, manifest effect and no-code statement.
