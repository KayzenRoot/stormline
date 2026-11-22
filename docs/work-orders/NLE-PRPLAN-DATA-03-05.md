# NLE-PRPLAN-DATA-03-05 — Animation metadata validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-05`. **Predecessor:** `DATA-03-04` textures. **Issue:** #26. **Base:** `4082d51`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Validate caller-supplied animation metadata: joints, tracks, keyframes and duration. No decoding, conversion, native I/O, network or ABI.

## CONTEXT

DATA-03-01..04 are approved/completed. Importer planning and texture metadata exist. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## SCOPE

- `src/stormline/data/import/animation_metadata.hpp`.
- `tests/core/data03_animation_tests.cpp`: ANIM-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Audio/composite validation/receipts/qualification; real decoders, native I/O, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; ANIM-01; fixed joint/track/keyframe/duration quotas.

## ARCHITECTURE RULES

DATA-03 owns metadata validation; DATA-01/02 boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; ANIM-01 boundaries.
- No decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

ANIM-01 joint/track/keyframe/duration minima, maxima and overflow, valid cases. Existing suite required.

## DELIVERABLES

Header, ANIM tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, ANIM-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, decoder/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4082d51`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-04 code PR #617 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-05.md`.
