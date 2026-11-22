# NLE-PRPLAN-DATA-02-07 — Typed metadata schema (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-07`. **Predecessor:** `DATA-02-06` queries. **Issue:** #25. **Base:** `0cd0cc8`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Add schema-versioned bounded metadata: typed key/value entries, schema version 1, duplicate-key rejection, atomic replace and per-asset quota. No serialization, persistence, native I/O, network or ABI.

## CONTEXT

DATA-02-01..06 are approved/completed. Registry IDs, paths, dependencies, tags and queries exist. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `asset_registry.hpp` additive metadata schema.
- `tests/core/data02_schema_tests.cpp`: SCHEMA-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

References/rename/impact; serialization, persistence, SQLite, native filesystem, network, MCP, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; SCHEMA-01; version 1 only, 8 entries/asset, 32-byte keys, 64-byte values, atomic replace, typed errors.

## ARCHITECTURE RULES

DATA-02 owns metadata; DATA-01 owns paths; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence/serialization; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; SCHEMA-01 version/keys/values/duplicates/atomicity/quota.
- No serialization/persistence/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

SCHEMA-01 key/value boundaries, invalid chars, duplicate keys, rejected replacement leaves prior state, clear, quota 8, unsupported version, missing/tombstoned asset and buffer full. Existing suite required.

## DELIVERABLES

Additive `asset_registry.hpp`, schema tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SCHEMA-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, serialization/persistence/native I/O, unbounded metadata, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0cd0cc8`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-06 code PR #604 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-07-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-07.md` for implementation.
