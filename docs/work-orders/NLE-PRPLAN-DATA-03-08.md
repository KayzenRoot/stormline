# NLE-PRPLAN-DATA-03-08 — Provenance receipts (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-08`. **Predecessor:** `DATA-03-07` validation. **Issue:** #26. **Base:** `27131f2`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Add bounded logical provenance receipts: operation ID, DATA-02 AssetId, importer/version, format, source fingerprint, artifact/warning counts and validation status. No persistence, serialization, native I/O, network or ABI.

## CONTEXT

DATA-03-01..07 are approved/completed. Importer planning and metadata validation exist. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## SCOPE

- `src/stormline/data/import/import_receipt.hpp`.
- `tests/core/data03_receipt_tests.cpp`: REC-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; persistence, database, serialization, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; REC-01; 64 receipts, duplicate operation rejection, saturating warning total.

## ARCHITECTURE RULES

DATA-03 owns receipts; DATA-02 owns AssetId; boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/persistence/serialization/native I/O/network; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; REC-01 add/find/duplicate/capacity/warnings.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

REC-01 valid/missing/duplicate, invalid operation/asset/format/importer/artifacts, full capacity, warning sum and saturation. Existing suite required.

## DELIVERABLES

Header, REC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, REC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/native I/O, unbounded receipts, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `27131f2`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-07 code PR #623 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-08.md`.
