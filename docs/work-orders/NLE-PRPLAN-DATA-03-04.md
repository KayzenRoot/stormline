# NLE-PRPLAN-DATA-03-04 — Texture metadata validation (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-04`. **Predecessor:** `DATA-03-03` importers. **Issue:** #26. **Base:** `cfce630`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Validate caller-supplied texture metadata: dimensions, channels, mip levels and non-power-of-two warning. No decoding, conversion, native I/O, network or ABI.

## CONTEXT

DATA-03-01..03 are approved/completed. Importers/sniffing/plans exist. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `src/stormline/data/import/texture_metadata.hpp`.
- `tests/core/data03_texture_tests.cpp`: TEX-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Animation/audio/validation-composite/receipts/qualification; real decoders, native I/O, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; TEX-01; fixed dimension/mip/channel quotas, typed errors.

## ARCHITECTURE RULES

DATA-03 owns metadata validation; DATA-01/02 boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; TEX-01 boundaries/warnings.
- No decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TEX-01 width/height 1/16384/16385, channels 0/1/4/5, mip levels 0/15/16 and per-dimension cap, non-POT warning, POT no warning. Existing suite required.

## DELIVERABLES

Header, TEX tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TEX-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, decoder/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `cfce630`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-03 code PR #615 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-04.md`.
