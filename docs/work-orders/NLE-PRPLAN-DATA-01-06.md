# NLE-PRPLAN-DATA-01-06 — Capabilities (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Gate:** G6 implementation + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-06`. **Predecessor:** `DATA-01-05` completed. **Issue:** #24. **Base:** `1cee5dd7c810970d5e92f99c109c2d9520a52104`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Implement explicit read capabilities: `AccessCapability`, bounded `CapabilitySet` grant/revoke/allows. No cache, storage, native I/O, write, network, dependency, ABI or release.

## CONTEXT

DATA-01-01..05 are approved/completed. ADR-0110 admits only completed CORE-01 capabilities; CORE-01 is not module-qualified. The owner authorized completion of DATA-01..04 on 2026-11-22.

## SCOPE

- `vfs_capability.hpp`: `AccessCapability`, `CapabilitySet` with least-privilege read grant.
- `tests/core/data01_capability_tests.cpp`: CAP-01.
- Additive CMake target/tests and workflow TSan/path filters.
- Evidence file.

## OUT OF SCOPE

Cache, storage, native filesystem, archive, writes, network, serialization, public ABI/release, DATA-01-07 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, `data-01-vfs-v0`, DATA-01 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; CAP-01; least privilege, explicit workspace/mount, no ambient authority.

## ARCHITECTURE RULES

DATA-01 owns logical capabilities; CORE-01 native OS, CORE-02 memory, CORE-03 jobs, CORE-04 ticks, CORE-06 diagnostics, DATA-02..05 higher layers. Header-only internal C++20.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; CAP-01 grant/revoke/allows, duplicate update, invalid workspace/mount/read=false, capacity.
- No cache/storage/native I/O code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.

## TESTS

CAP-01 plus invalid/duplicate/capacity/revoke-missing fixtures. Existing full CTest suite remains required.

## DELIVERABLES

`vfs_capability.hpp`, capability tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CAP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, API drift, native I/O/network, cache/storage code, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `1cee5dd7c810970d5e92f99c109c2d9520a52104`; contract blob `8f85e3a68c2ff90e26a344b47d96f57ae90fdfe9`; DATA-01-05 code PR #585 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-06-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-01-06.md` for implementation.
