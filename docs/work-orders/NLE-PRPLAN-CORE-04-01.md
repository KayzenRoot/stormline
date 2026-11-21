# NLE-PRPLAN-CORE-04-01 — CORE-04 governance (INTERNAL_ONLY)

**STATUS: GOVERNANCE PACKET — documentary only; no implementation authorized.** **Gate:** G6 governance + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-CORE-04-01`. **Predecessor:** CORE-03 internal sequence complete (`NOT_QUALIFIED`). **Issue:** #21. **Base:** `6747eb9fd6949c177e293ed2d754661929f16451`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-governance-v0](../contracts/core-04-governance-v0.md).

## OBJECTIVE

Record the bounded owner governance decision for CORE-04: planning direction, risk/release, capability admission from CORE-01 and the gates that must precede contract and code. No implementation.

## CONTEXT

CORE-03 closed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-04 research/architecture/ADR-0006 exist but no executable code. CORE-01 is not a qualified module; selected completed capabilities are admitted. The owner instructed continuation on 2026-11-21.

## SCOPE

- ADR-0107 governance decision and ADR-0006 planning-only ratification.
- Governance contract: ownership, determinism envelope, debt policy, capability admission, gates.
- WO/G6 evidence/activation JSON, manifest/validator/tests/checkpoint.
- No code, dependency, CMake, workflow or public ABI.

## OUT OF SCOPE

CORE-04 implementation, exact API/ABI, fixed-step code, replay code, third-party timing libraries, allocator selection, physics/network determinism, public release, license, CORE-01 completion, CORE-04-02 or any later packet.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0006/0086/0107, CORE-04 architecture/research/matrix, CORE-01 capability evidence, CORE-03 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0107; ADR-0086 capability rule; no technology/dependency selection.

## ARCHITECTURE RULES

CORE-01 owns OS time acquisition; CORE-04 owns tick timeline/debt/interpolation phase; CORE-03 consumes tick IDs; CORE-06 diagnostics; SIM/GFX/NET/AUD boundaries unchanged. No architecture cycle.

## CONSTRAINTS

Risk `LOW` documentary / `ELEVATED` future implementation; release `INTERNAL_ONLY`; no code, dependency, secret, paid service, public ABI or release. CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03 NOT_QUALIFIED; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- ADR-0107 and governance contract record ownership, determinism envelope, debt policy and capability admission.
- `CORE-04-01` becomes `APPROVED_GOVERNANCE`; `CORE-04-02`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `CORE04_01_APPROVED_GOVERNANCE_ONLY`: **711 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 30 `COMPLETED`, 7 approved gates**.
- Docs Validation and pt-BR audit `APPROVED`; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, manifest/validator tests. No native code test is authorized by this packet.

## DELIVERABLES

ADR-0107, ADR-0006 status update, governance contract, WO, G6 evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, governance fidelity, capability admission, risk/release, determinism envelope, no code/dependency, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale context, missing owner continuation, technology selected by inference, code/dependency/ABI/release, manifest/registry drift, HIGH/CRITICAL. No code before CORE-04-02 contract and CORE-04-03 G6.

## CONTEXT LOCK

Base `6747eb9fd6949c177e293ed2d754661929f16451`; ADR-0006 planning-only; capability admission pins completed CORE-01-03/-06/-07/-08/-12/-13.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-01-G6-ACTIVATION.md` with governance decision, admission, manifest effect and no-code statement.
