# NLE-PRPLAN-DATA-03-02 — Import planning contract (INTERNAL_ONLY)

**STATUS: CONTRACT PACKET — documentary only; implementation remains BLOCKED until DATA-03-03 G6.** **Gate:** G6 contract + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-02`. **Predecessor:** `DATA-03-01` governance. **Issue:** #26. **Base:** `ba715a2`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Freeze the DATA-03 logical import-planning contract: importer descriptors, bounded signature sniffing, import plans, texture/animation/audio metadata validation and provenance receipts. No decoder or file I/O.

## CONTEXT

DATA-03-01 is `APPROVED_GOVERNANCE` only. ADR-0011 is planning direction; ADR-0112 forbids real decoders in this sequence. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. No dependency is selected.

## SCOPE

- Contract `data-03-import-v0`: exact API, semantics, errors, IMP/TEX/ANIM/AUDIO/VAL/REC/QLF oracles and exact allowlists.
- Evidence of contract review and DATA-02 admission boundary.
- No implementation, decoder, dependency, CMake target or code test.

## OUT OF SCOPE

Importer code, image/mesh/audio/archive decoders, conversion, native filesystem, persistence, serialization, editor/MCP, network, public ABI/release, DATA-03-03 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, DATA-03 architecture/research/api, governance contract, DATA-02 closeout, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; bounded signatures/metadata, typed failures, no host leakage, identity via DATA-02.

## ARCHITECTURE RULES

DATA-03 owns logical import planning/validation/receipts; DATA-01 VFS; DATA-02 identity; CORE-01 native OS; CORE-02 memory; CORE-03 jobs; CORE-04 ticks; CORE-06 diagnostics; DATA-04/05 higher layers.

## CONSTRAINTS

Risk `LOW` docs/`ELEVATED` implementation; release `INTERNAL_ONLY`; no code/decoder/dependency/secret/paid service/native I/O/network/ABI/release. DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact API/errors/semantics/test matrix/allowlists.
- No decoder, archive, conversion, native I/O, network or dependency.
- `DATA-03-02` becomes `APPROVED_CONTRACT`; `-03`..`-10` remain `PLANNED_BLOCKED`.
- Manifest `DATA03_02_APPROVED_CONTRACT_ONLY`: **660 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 70 `COMPLETED`, 18 approved gates**.
- Docs Validation + pt-BR audit; no HIGH/CRITICAL; registry byte-identical.

## TESTS

Docs validators, selector denial, contract review. No native code test authorized.

## DELIVERABLES

Contract, G6 activation evidence, activation JSON, manifest/validator/tests/checkpoint. PR, Docs Validation, pt-BR audit, proposed checkpoint only.

## REVIEW FORMAT

pt-BR: base/head, contract fidelity to ADR-0112/0011, admission, no decoder/dependency, blocked packets. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale, missing admission, decoder/archive/conversion/native I/O selected by inference, code implementation, manifest/registry drift, HIGH/CRITICAL, release/ABI/decoder claim. No code before DATA-03-03 G6.

## CONTEXT LOCK

Base `ba715a2`; admission pins DATA-02-03..-09; contract review required before `-03`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-02-G6-ACTIVATION.md`.
