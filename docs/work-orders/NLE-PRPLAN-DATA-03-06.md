# NLE-PRPLAN-DATA-03-06 — Audio metadata validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-06`. **Predecessor:** `DATA-03-05` animations. **Issue:** #26. **Base:** `4189bf9`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Validate caller-supplied audio metadata: sample rate, channels, bit depth and frame count. No decoding, conversion, native I/O, network or ABI.

## CONTEXT

DATA-03-01..05 are approved/completed. Importer planning, texture and animation metadata exist. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.

## SCOPE

- `src/stormline/data/import/audio_metadata.hpp`.
- `tests/core/data03_audio_tests.cpp`: AUDIO-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Composite validation/receipts/qualification; real decoders, native I/O, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; AUDIO-01; fixed rate/channel/bit/frame quotas.

## ARCHITECTURE RULES

DATA-03 owns metadata validation; DATA-01/02 boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; AUDIO-01 boundaries.
- No decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

AUDIO-01 rate/channel/bit/frame minima, maxima, unsupported bit depths and overflow. Existing suite required.

## DELIVERABLES

Header, AUDIO tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, AUDIO-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, decoder/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4189bf9`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-05 code PR #619 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-06.md`.
