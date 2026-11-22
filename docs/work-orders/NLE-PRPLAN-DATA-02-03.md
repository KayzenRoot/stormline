# NLE-PRPLAN-DATA-02-03 — Stable asset identity (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-03`. **Predecessor:** `DATA-02-02` contract. **Issue:** #25. **Base:** `840a7ff`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Implement the registry core: opaque 128-bit `AssetId`, `ProjectId`, `AssetRecord`, fixed 64-asset `AssetRegistry` with add/find/path lookup/tombstone and typed ID/path/capacity errors. No persistence, SQLite, serialization, native I/O, dependency or ABI.

## CONTEXT

DATA-02-01 governance and -02 contract are approved. CORE-01 is not module-qualified; admission is limited. DATA-01 is internally complete but not qualified. The owner authorized DATA-01..04 completion on 2026-11-22.

## SCOPE

- `src/stormline/data/registry/registry_types.hpp`: IDs, kinds, status, errors, capacities.
- `src/stormline/data/registry/asset_registry.hpp`: core `AssetRegistry` ID/path/tombstone methods.
- `tests/core/data02_id_tests.cpp`: ID-01.
- Additive CMake target/test and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Dependencies, tags, queries, metadata schema, references/rename/impact (later slices); persistence, SQLite, serialization, native filesystem, network, MCP, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02 governance, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; ID-01; opaque identity, project/path uniqueness, tombstone retention, fixed capacity, stable errors, no host leakage.

## ARCHITECTURE RULES

DATA-02 owns logical identity; DATA-01 owns `VfsPath`; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-03/04/05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; ID-01 add/find/path/duplicate/tombstone/capacity.
- No persistence/serialization/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

ID-01 valid/invalid IDs, duplicate ID/path, same path in different projects, tombstone retention and revision, capacity, missing lookups. Existing full CTest suite remains required.

## DELIVERABLES

`registry_types.hpp`, `asset_registry.hpp` core, ID tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, ID-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, persistence/native I/O, ID reuse/path ambiguity accepted, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `840a7ff`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-02 contract PR #596 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-03-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-03.md` for implementation.
