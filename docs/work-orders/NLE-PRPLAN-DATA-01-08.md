# NLE-PRPLAN-DATA-01-08 — Memory storage (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-08`. **Predecessor:** `DATA-01-07` completed. **Issue:** #24. **Base:** `932950f5c5c81b1a753680c49d37396d48a2fa13`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Implement the frozen memory-only storage abstraction: `StorageDescriptor`, `StorageBackend` and fixed 64-file `MemoryStorage` with put/read/erase, duplicate update, insufficient output, missing path, oversize and capacity behavior. No native filesystem, archive, network, write-through or persistence.

## CONTEXT

DATA-01-01..07 are approved/completed. ADR-0110 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of DATA-01..04 on 2026-11-22.

## SCOPE

- `src/stormline/data/vfs/vfs_storage.hpp`: `StorageDescriptor`, `StorageBackend`, `MemoryStorage`.
- `tests/core/data01_storage_tests.cpp`: STORAGE-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Native filesystem, archive codec, writes to host, network, serialization, persistence, public ABI/release, DATA-01-09 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, `data-01-vfs-v0`, DATA-01 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; STORAGE-01; bounded fixed table, exact path keys, typed failures, no OS calls.

## ARCHITECTURE RULES

DATA-01 owns logical storage values; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-02..05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; STORAGE-01 put/read/update/missing/insufficient/erase/capacity.
- No native I/O, archive, network or persistence code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

STORAGE-01 plus invalid/oversize/capacity/missing fixtures and base-class dispatch. Existing full CTest suite remains required.

## DELIVERABLES

`vfs_storage.hpp`, storage tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, STORAGE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, native I/O/network/archive, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `932950f5c5c81b1a753680c49d37396d48a2fa13`; contract blob `8f85e3a68c2ff90e26a344b47d96f57ae90fdfe9`; DATA-01-07 code PR #589 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-08-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-01-08.md` for implementation.
