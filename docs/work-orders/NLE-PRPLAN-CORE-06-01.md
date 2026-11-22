# NLE-PRPLAN-CORE-06-01 — CORE-06 governance (INTERNAL_ONLY)

**STATUS: GOVERNANCE PACKET — documentary only; no implementation authorized.** **Gate:** G6 governance + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-06-01`. **Predecessor:** CORE-05 internal sequence complete. **Issue:** #23. **Base:** `326f83fdfda026d3eb254010f3a82107c3743eb7`. **ADR:** [ADR-0109](../adr/0109-core-06-governance-slice.md). **Contract:** [core-06-governance-v0](../contracts/core-06-governance-v0.md).

## OBJECTIVE

Record bounded owner governance for CORE-06: local-first policy, owned typed facade, release/risk classes, CORE-01 admission and the gates before contract/code. No implementation.

## CONTEXT

CORE-05 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-06 research/architecture/ADR-0008 exist; no code. CORE-01 is not module-qualified; selected capabilities are admitted. The owner instructed continuation on 2026-11-22.

## SCOPE

- ADR-0109 governance and ADR-0008 planning-only ratification.
- Governance contract: ownership, local-first/security invariants, release/risk, admission, gates.
- WO/G6 evidence/activation JSON, manifest/validator/tests/checkpoint.
- No code, dependency, CMake, workflow, network endpoint or public ABI.

## OUT OF SCOPE

CORE-06 implementation, spdlog/Tracy/Perfetto/Crashpad selection, crash upload, telemetry service, profiler listener, binary format, public release, license, CORE-01 completion, CORE-06-02 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0008/0086/0109, CORE-06 architecture/research/matrix, CORE-01 capabilities, CORE-05 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0109; ADR-0086 capability rule; no technology/dependency selection; privacy/local-first invariants.

## ARCHITECTURE RULES

CORE-06 owns diagnostic facade/semantics/local sink policy; CORE-01 OS crash/lifecycle, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, GFX GPU, AUD realtime, DATA provenance, EDIT/QA/AI projections. No architecture cycle.

## CONSTRAINTS

Risk `LOW` documentary / `ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/network/ABI/release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- ADR-0109/governance contract record local-first, owned facade, risk/release and admission.
- `CORE-06-01` becomes `APPROVED_GOVERNANCE`; `CORE-06-02`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE06_01_APPROVED_GOVERNANCE_ONLY`: **691 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 46 `COMPLETED`, 11 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, manifest/validator tests. No native code test authorized.

## DELIVERABLES

ADR-0109, ADR-0008 status, governance contract, WO, G6 evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, audit.

## REVIEW FORMAT

pt-BR: base/head, governance fidelity, admission, risk/release, privacy invariants, no code/dependency, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale context, missing owner continuation, technology selected by inference, network/telemetry/crash upload, code/dependency/ABI/release, drift, HIGH/CRITICAL. No code before CORE-06-02 contract and CORE-06-03 G6.

## CONTEXT LOCK

Base `326f83f`; ADR-0008 planning-only; capability admission pins CORE-01-03/-06/-07/-08/-12/-13.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-06-01-G6-ACTIVATION.md`.
