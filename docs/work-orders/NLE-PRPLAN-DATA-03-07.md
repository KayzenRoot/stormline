# NLE-PRPLAN-DATA-03-07 — Integrated metadata validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-07`. **Predecessor:** `DATA-03-06` audio. **Issue:** #26. **Base:** `778c06d`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Dispatch artifact metadata validation by type and produce a typed `ValidationResult`: texture, animation, audio, opaque mesh/metadata and unknown rejection. No decode, native I/O, network or ABI.

## CONTEXT

DATA-03-01..06 are approved/completed. Texture/animation/audio validators exist. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## SCOPE

- `src/stormline/data/import/import_validation.hpp`.
- `tests/core/data03_validation_tests.cpp`: VAL-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Receipts/qualification; real decoders, native I/O, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; VAL-01; typed dispatch, warning propagation, unknown rejection.

## ARCHITECTURE RULES

DATA-03 owns validation composition; DATA-01/02 boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; VAL-01 dispatch/status/warnings.
- No decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VAL-01 texture/animation/audio valid-invalid, warning propagation, mesh/metadata valid, unknown rejected. Existing suite required.

## DELIVERABLES

Header, VAL tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VAL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, decoder/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `778c06d`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-06 code PR #621 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-07.md`.
