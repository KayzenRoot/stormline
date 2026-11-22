# NLE-PRPLAN-DATA-04-04 — Declarative scene document (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-04-04`. **Predecessor:** `DATA-04-03` schemas. **Issue:** #27. **Base:** `a10b825`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Implement the in-memory declarative scene document: entities with parent/name/enabled, components and asset refs, bounded counts and typed failures. No codec, persistence, network or ABI.

## CONTEXT

DATA-04-01..03 are approved/completed. Schema validation exists. CORE-05/DATA-02 are not qualified.

## SCOPE

- `scene_document.hpp`.
- `tests/core/data04_document_tests.cpp`: DOC-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Patches/diffs/qualification; JSON/CBOR, persistence, migration, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, `data-04-scene-v0`, DATA-04-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; DOC-01; parent/name/ID/capacity rules.

## ARCHITECTURE RULES

DATA-04 owns scene documents; CORE-05 typed IDs; DATA-01/02/03 boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; DOC-01 add/find/at/count/remove/capacity.
- No codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DOC-01 entity/component/ref add/find/remove; duplicate ID; name/parent/cycle; capacity 64/128/64. Existing suite required.

## DELIVERABLES

Header, DOC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DOC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `a10b825`; contract blob `99962b6a800d5219db46ce42cf4abb34f6d0ac57`; DATA-04-03 code PR #632 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-04-04.md`.
