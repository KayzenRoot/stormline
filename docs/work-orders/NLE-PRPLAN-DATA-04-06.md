# NLE-PRPLAN-DATA-04-06 — Semantic scene diffs (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-04-06`. **Predecessor:** `DATA-04-05` patches. **Issue:** #27. **Base:** `46ef785`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Implement deterministic semantic entity diffs over stable IDs: added/removed/enabled/name changes, sorted and bounded. No byte format, persistence, network or ABI.

## CONTEXT

DATA-04-01..05 are approved/completed. Documents and atomic patches exist. CORE-05/DATA-02 are not qualified.

## SCOPE

- `scene_diff.hpp`.
- `tests/core/data04_diff_tests.cpp`: DIFF-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; JSON/CBOR, persistence, migration, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, `data-04-scene-v0`, DATA-04-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; DIFF-01; stable order, bounded output, no duplicate kinds.

## ARCHITECTURE RULES

DATA-04 owns diffs; CORE-05 typed IDs; DATA-01/02/03 boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; DIFF-01 add/remove/enabled/name/order/buffer.
- No codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DIFF-01 changed/added/removed, dual kind, sorted IDs, identical, buffer full, scene mismatch. Existing suite required.

## DELIVERABLES

Header, DIFF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DIFF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/native I/O, unstable order/unbounded output, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `46ef785`; contract blob `99962b6a800d5219db46ce42cf4abb34f6d0ac57`; DATA-04-05 code PR #636 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-04-06.md`.
