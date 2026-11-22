# NLE-PRPLAN-DATA-03-03 — Importer descriptors and plans (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-02 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-03-03`. **Predecessor:** `DATA-03-02` contract. **Issue:** #26. **Base:** `8d3fb1c`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Implement importer descriptors, fixed-capacity registry, bounded Png/Jpeg/Glb/Wav signature sniffing and import plans tied to a valid DATA-01 path. No decoders, conversion, native I/O, network or ABI.

## CONTEXT

DATA-03-01..02 are approved. DATA-02 is `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; admission uses completed DATA-02 capabilities. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `import_types.hpp`, `importer_registry.hpp`.
- `tests/core/data03_importer_tests.cpp`: IMP-01.
- Additive CMake target/test and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Texture/animation/audio validators, receipts, qualification; real decoders, native I/O, persistence, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03 governance, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; IMP-01; bounded signatures, typed errors, no host leakage.

## ARCHITECTURE RULES

DATA-03 owns logical planning; DATA-01 VFS; DATA-02 identity; CORE boundaries unchanged. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; IMP-01 descriptors/sniff/plan.
- No decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

IMP-01 descriptor add/find/duplicates/capacity, signature sniff exact/truncated/unknown, declared mismatch, valid plan, empty path. Existing suite required.

## DELIVERABLES

Headers, IMP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, IMP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, decoder/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8d3fb1c`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-02 contract PR #613 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-03.md`.
