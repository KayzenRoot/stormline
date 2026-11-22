# NLE-PRPLAN-DATA-04-02 — Scene document contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until DATA-04-03 G6.** **Formal packet:** `NLE-PRPLAN-DATA-04-02`. **Predecessor:** `DATA-04-01` governance. **Issue:** #27. **Base:** `50836b4`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Freeze the DATA-04 logical scene-document contract: schema descriptors, entities/components/asset refs, atomic patches and semantic diffs. No byte format.

## CONTEXT

DATA-04-01 is `APPROVED_GOVERNANCE` only. ADR-0012 is planning direction; ADR-0113 forbids byte formats in this sequence. CORE-05/DATA-02 are not qualified.

## SCOPE

- Contract `data-04-scene-v0`: exact API, semantics, errors, SCH/DOC/PATCH/DIFF/QLF oracles and allowlists.
- Evidence of contract review and CORE-05/DATA-02 admission boundary.
- No implementation, codec, dependency, CMake target or code test.

## OUT OF SCOPE

Scene code, JSON/CBOR, schema validator, persistence, migration journal, native filesystem, network, editor/MCP, public ABI/release, DATA-04-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, DATA-04 architecture/research/api, governance contract, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; bounded schema/document/patch/diff, typed failures, no byte format.

## ARCHITECTURE RULES

DATA-04 owns logical scene documents; CORE-05 typed IDs/math; DATA-01/02/03 boundaries unchanged; DATA-05 bundles.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence/ABI/release. CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No JSON/CBOR, schema validator, persistence, native I/O, network or dependency.
- `DATA-04-02` becomes `APPROVED_CONTRACT`; `-03`..`-08` remain `PLANNED_BLOCKED`.
- Manifest `DATA04_02_APPROVED_CONTRACT_ONLY`: **650 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 78 `COMPLETED`, 20 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity, admission, no-codec boundary, blocked packets.

## STOP CONDITION

Stale, missing admission, codec/format/persistence selected by inference, code implementation, manifest drift, HIGH/CRITICAL, release/ABI/roundtrip claim.

## CONTEXT LOCK

Base `50836b4`; admission pins CORE-05-03..10 and DATA-02-03/07/09; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-02-G6-ACTIVATION.md`.
