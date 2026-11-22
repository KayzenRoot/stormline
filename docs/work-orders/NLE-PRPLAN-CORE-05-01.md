# NLE-PRPLAN-CORE-05-01 — CORE-05 governance (INTERNAL_ONLY)

**STATUS: GOVERNANCE PACKET — documentary only; no implementation authorized.** **Gate:** G6 governance + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-05-01`. **Predecessor:** CORE-04 internal sequence complete. **Issue:** #22. **Base:** `0e5d6e5ae0b418823d667aa7e67d0e82154d532c`. **ADR:** [ADR-0108](../adr/0108-core-05-governance-slice.md). **Contract:** [core-05-governance-v0](../contracts/core-05-governance-v0.md).

## OBJECTIVE

Record the bounded owner governance decision for CORE-05: conventions, precision/ID policy, risk/release, CORE-01 capability admission and the gates before contract/code. No implementation.

## CONTEXT

CORE-04 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-05 research/architecture/ADR-0007 exist; no code. CORE-01 is not module-qualified; selected capabilities are admitted. The owner instructed continuation on 2026-11-22.

## SCOPE

- ADR-0108 governance and ADR-0007 planning-only ratification.
- Governance contract: ownership, conventions, precision/ID policy, admission, gates.
- WO/G6 evidence/activation JSON, manifest/validator/tests/checkpoint.
- No code, dependency, CMake, workflow or public ABI.

## OUT OF SCOPE

CORE-05 implementation, exact API/ABI, third-party math libraries, SIMD, serialization, physics/netcode integration, public release, license, CORE-01 completion, CORE-05-02 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0007/0086/0108, CORE-05 architecture/research/matrix, CORE-01 capabilities, CORE-04 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0108; ADR-0086 capability rule; no technology/dependency selection.

## ARCHITECTURE RULES

CORE-05 owns math/coordinate/unit/identifier contracts; CORE-01 platform, CORE-02 memory, CORE-03 scheduling, CORE-04 time, GFX-01 clip projection, SIM physics precision. No architecture cycle.

## CONSTRAINTS

Risk `LOW` documentary / `ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/ABI/release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- ADR-0108/governance contract record conventions, precision/ID policy and admission.
- `CORE-05-01` becomes `APPROVED_GOVERNANCE`; `CORE-05-02`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE05_01_APPROVED_GOVERNANCE_ONLY`: **701 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 38 `COMPLETED`, 9 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, manifest/validator tests. No native code test authorized.

## DELIVERABLES

ADR-0108, ADR-0007 status, governance contract, WO, G6 evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, audit.

## REVIEW FORMAT

pt-BR: base/head, governance fidelity, admission, risk/release, conventions, no code/dependency, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale context, missing owner continuation, technology selected by inference, code/dependency/ABI/release, drift, HIGH/CRITICAL. No code before CORE-05-02 contract and CORE-05-03 G6.

## CONTEXT LOCK

Base `0e5d6e5`; ADR-0007 planning-only; capability admission pins CORE-01-03/-06/-07/-08/-12/-13.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-05-01-G6-ACTIVATION.md`.
