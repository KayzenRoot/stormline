# NLE-PRPLAN-DATA-02-06 — Deterministic bounded queries (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-06`. **Predecessor:** `DATA-02-05` tags. **Issue:** #25. **Base:** `72aa0ef`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Add deterministic bounded queries over active assets: project, kind, tag and DATA-01 path-prefix filters, ascending `AssetId` order, caller-owned output and offset cursor. No persistence, serialization, native I/O, network or ABI.

## CONTEXT

DATA-02-01..05 are approved/completed. IDs, paths, tombstones, dependencies and tags exist. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `asset_registry.hpp` additive `AssetQuery`/`query`.
- `tests/core/data02_query_tests.cpp`: QUERY-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Metadata schema, references/rename/impact; persistence, SQLite, serialization, native filesystem, network, MCP, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; QUERY-01; ascending order, offset/cursor, bounded output, no hash iteration order.

## ARCHITECTURE RULES

DATA-02 owns queries; DATA-01 owns `VfsPath` prefix semantics; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 open.

## ACCEPTANCE CRITERIA

- Exact allowlist; QUERY-01 filters/order/offset/buffer/invalid.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

QUERY-01 project/kind/tag/prefix isolation, combined filters, ascending order, pagination cursor, past-end, empty output, invalid project/tag/prefix, tombstone exclusion. Existing suite remains required.

## DELIVERABLES

Additive `asset_registry.hpp`, query tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QUERY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/native I/O, unstable order/unbounded output, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `72aa0ef`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-05 code PR #602 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-06-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-06.md` for implementation.
