# NLE-PRPLAN-DATA-04-03 — Versioned scene schemas (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-04-03`. **Predecessor:** `DATA-04-02` contract. **Issue:** #27. **Base:** `d2b5dc3`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Implement scene schema IDs/versions/capability checks: schema ID 1, versions 1..3, capability subset `0x3`, canonicalization version 1. No byte format, persistence, network or ABI.

## CONTEXT

DATA-04-01..02 are approved. DATA-03 is internally complete. CORE-05/DATA-02 are not qualified.

## SCOPE

- `scene_types.hpp`, `scene_schema.hpp`.
- `tests/core/data04_schema_tests.cpp`: SCH-01.
- Additive CMake target/test and workflow filters.
- Evidence file.

## OUT OF SCOPE

Documents/patches/diffs/qualification; JSON/CBOR, persistence, migration, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, `data-04-scene-v0`, DATA-04-02 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; SCH-01; typed schema failures.

## ARCHITECTURE RULES

DATA-04 owns logical schema descriptors; CORE-05 typed IDs; DATA-01/02/03 boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; SCH-01 valid/invalid versions/capabilities.
- No codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SCH-01 schema ID/version 1..3/capability bits/canonicalization boundaries. Existing suite required.

## DELIVERABLES

Headers, SCH tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SCH-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d2b5dc3`; contract blob `99962b6a800d5219db46ce42cf4abb34f6d0ac57`; DATA-04-02 contract PR #630 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-04-03.md`.
