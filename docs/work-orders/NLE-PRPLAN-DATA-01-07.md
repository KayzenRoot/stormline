# NLE-PRPLAN-DATA-01-07 — Cache (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-07`. **Predecessor:** `DATA-01-06` completed. **Issue:** #24. **Base:** `0bc6987a90f81e61024f2e0b017a89fa9d0d37a5`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Implement bounded `PathCache` keyed by mount/generation/path: put/get, duplicate update, stale generation, insufficient output, invalidate mount and drop accounting. No storage backend, native I/O, writes, network, dependency, ABI or release.

## CONTEXT

DATA-01-01..06 are approved/completed. ADR-0110 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of DATA-01..04 on 2026-11-22.

## SCOPE

- `vfs_cache.hpp`: `CacheKey`, fixed 64-entry `PathCache`.
- `tests/core/data01_cache_tests.cpp`: CACHE-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Storage backend, native filesystem, archive, writes, network, serialization, public ABI/release, DATA-01-08 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, `data-01-vfs-v0`, DATA-01 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; CACHE-01; generation fencing, bounded capacity, no stale data after invalidate.

## ARCHITECTURE RULES

DATA-01 owns logical cache; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-02..05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; CACHE-01 put/get/update/stale/insufficient/invalidate/full.
- No storage/native I/O/write code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

CACHE-01 plus invalid mount/generation/size and drop fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`vfs_cache.hpp`, cache tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CACHE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, native I/O/network, storage/write code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `0bc6987a90f81e61024f2e0b017a89fa9d0d37a5`; contract blob `8f85e3a68c2ff90e26a344b47d96f57ae90fdfe9`; DATA-01-06 code PR #587 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-07-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-01-07.md` for implementation.
