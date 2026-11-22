# NLE-PRPLAN-DATA-04-01 — DATA-04 governance (INTERNAL_ONLY)

**STATUS: GOVERNANCE PACKET — documentary only; no implementation authorized.** **Formal packet:** `NLE-PRPLAN-DATA-04-01`. **Predecessor:** DATA-03 internal sequence complete. **Issue:** #27. **Base:** `a26e463`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-governance-v0](../contracts/data-04-governance-v0.md).

## OBJECTIVE

Record bounded owner governance for DATA-04: in-memory scene documents, versioned schema descriptors, declarative entities/components/asset refs, atomic patches and semantic diffs. No byte format or persistence.

## CONTEXT

DATA-03 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. DATA-04 research/architecture/ADR-0012 exist; no code. CORE-05 and DATA-02 are not qualified. The owner authorized completion of DATA-01..04 on 2026-11-22.

## SCOPE

- ADR-0113 governance and ADR-0012 planning-only ratification.
- Governance contract: ownership, no-byte-format boundary, release/risk, admission, gates.
- WO/G6 evidence, manifest/validator/tests/checkpoint.

## OUT OF SCOPE

DATA-04 implementation, JSON/CBOR codec, schema validator, persistence, migration journal, native I/O, MCP, network, release, license, DATA-04-02 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, DATA-04 architecture/research/api, DATA-03 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; no codec/dependency selection; fail-closed schema/graph/patch validation.

## ARCHITECTURE RULES

DATA-04 owns logical scene documents; CORE-05 typed math/IDs; DATA-01 VFS; DATA-02 identity; DATA-03 import metadata; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-05 bundles.

## CONSTRAINTS

Risk `LOW` documentary / `ELEVATED` implementation; release `INTERNAL_ONLY`; no code/dependency/secret/paid service/native I/O/network/ABI/release. CORE-05/DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- ADR-0113/governance contract record no-byte-format boundary, quotas and admission.
- `DATA-04-01` becomes `APPROVED_GOVERNANCE`; `DATA-04-02`..`-08` remain `PLANNED_BLOCKED`.
- Manifest `DATA04_01_APPROVED_GOVERNANCE_ONLY`: **651 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 78 `COMPLETED`, 19 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, manifest/validator tests. No native code test authorized.

## DELIVERABLES

ADR-0113, governance contract, WO, G6 evidence, manifest/validator/tests/checkpoint.

## REVIEW FORMAT

pt-BR: base/head, governance fidelity, admission, no-codec boundary, no code/dependency, blocked packets.

## STOP CONDITION

Stale context, missing owner continuation, codec/dependency selected by inference, host I/O, unbounded input, code/ABI/release, drift, HIGH/CRITICAL.

## CONTEXT LOCK

Base `a26e463`; ADR-0012 planning-only; formal dependencies CORE-05 and DATA-02.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-01-G6-ACTIVATION.md`.
