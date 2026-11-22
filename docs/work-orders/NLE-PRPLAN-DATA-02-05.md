# NLE-PRPLAN-DATA-02-05 — Bounded tags (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-05`. **Predecessor:** `DATA-02-04` dependencies. **Issue:** #25. **Base:** `cd13d94`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Add bounded, validated tags per active asset: add/remove/has/list, duplicate idempotence and per-asset quota. No persistence, serialization, native I/O, network or ABI.

## CONTEXT

DATA-02-01..04 are approved/completed. IDs, paths, tombstones and dependencies exist. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `asset_registry.hpp` additive tag type/state/methods.
- `tests/core/data02_tag_tests.cpp`: TAG-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Queries, metadata schema, references/rename/impact; persistence, SQLite, serialization, native filesystem, network, MCP, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; TAG-01; ASCII validation, 8 tags/asset, 32 bytes/tag, insertion order, typed errors.

## ARCHITECTURE RULES

DATA-02 owns tags; DATA-01 owns paths; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; TAG-01 valid/invalid text, duplicate, quota, remove/has/list.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

TAG-01 boundaries 1/32 bytes, rejected 33/control/space/slash, case sensitivity, duplicate idempotence, 8-tag quota, missing asset/tag and buffer-full required count. Existing suite remains required.

## DELIVERABLES

Additive `asset_registry.hpp`, tag tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TAG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/native I/O, unbounded tags, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `cd13d94`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-04 code PR #600 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-05-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-05.md` for implementation.
