# NLE-PRPLAN-DATA-01-09 — Integrated VFS qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification code authorized only after this gate merges.** **Gate:** G6 qualification + CORE-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-01-09`. **Predecessor:** `DATA-01-08` completed. **Issue:** #24. **Base:** `962d780885fcf249be4f92e851615a33a76d745b`. **ADR:** [ADR-0110](../adr/0110-data-01-governance-slice.md). **Contract:** [data-01-vfs-v0](../contracts/data-01-vfs-v0.md).

## OBJECTIVE

Qualify the integrated logical VFS inside CI: path→mount→overlay→capability→cache→memory storage, deterministic repeat, typed-failure recovery and bounded overload. Qualification is internal/CI-only; no native filesystem confinement, archive, write, hardware, ABI or release claim.

## CONTEXT

DATA-01-01..08 are approved/completed. The individual slices each have their own tests; this packet adds the required cross-slice QLF-01..04 evidence without changing production headers.

## SCOPE

- `tests/core/data01_vfs_qualification_tests.cpp`: QLF-01..04.
- Additive CMake target/tests and workflow TSan/path filters.
- `docs/evidence/NLE-PRPLAN-DATA-01-09.md`.

## OUT OF SCOPE

Production header changes, native filesystem/OS sandbox, archive codec, host writes, persistence, network, serialization, hardware/soak qualification, public ABI/release, DATA-01-10 or later.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0009/0086/0110, `data-01-vfs-v0`, DATA-01 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0110; ADR-0086; QLF-01..04; fixed capacities and drop accounting; no host path leakage.

## ARCHITECTURE RULES

Qualification exercises only the frozen DATA-01 headers; it must not introduce an alternate API or production behavior. Header-only internal C++20; single-owner values.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network; CORE-01 not module-qualified; CORE-02 NOT_QUALIFIED; CORE-03/04/05/06 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-01..04 all pass.
- No production file change; no native I/O/archive/network/persistence code.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; no dependency/ABI/release change; pt-BR audit `APPROVED`.
- Explicit statement that CI qualification is not physical/hardware or release qualification.

## TESTS

QLF-01 integrated pipeline; QLF-02 deterministic repeat; QLF-03 recovery after each typed error; QLF-04 10,000 bounded attempts with stable capacities and drop counts. Existing full CTest suite remains required.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, production/API drift, native I/O/network/archive, allowlist violation, failed test, HIGH/CRITICAL, hardware/release/ABI claim. Stop and report.

## CONTEXT LOCK

Base `962d780885fcf249be4f92e851615a33a76d745b`; contract blob `8f85e3a68c2ff90e26a344b47d96f57ae90fdfe9`; DATA-01-08 code PR #591 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-01-09-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-01-09.md` for qualification.
