# NLE-PRPLAN-DATA-02-09 — Integrated registry qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Gate:** G6 qualification + DATA-01 capability admission. **Formal packet:** `NLE-PRPLAN-DATA-02-09`. **Predecessor:** `DATA-02-08` references. **Issue:** #25. **Base:** `dfb10ed`. **ADR:** [ADR-0111](../adr/0111-data-02-governance-slice.md). **Contract:** [data-02-registry-v0](../contracts/data-02-registry-v0.md).

## OBJECTIVE

Qualify the integrated logical registry inside CI: identity→path→tags→metadata→dependencies→query→reference→rename→impact, deterministic repeat, typed-failure recovery and 10,000 bounded attempts. Internal/CI only; no persistence, database, native I/O, hardware, ABI or release claim.

## CONTEXT

DATA-02-01..08 are approved/completed. Each slice has its own tests; this packet adds cross-slice QLF-R01..04 without production changes.

## SCOPE

- `tests/core/data02_registry_qualification_tests.cpp`: QLF-R01..04.
- Additive CMake target/tests and workflow TSan target.
- `docs/evidence/NLE-PRPLAN-DATA-02-09.md`.

## OUT OF SCOPE

Production header changes, persistence, SQLite, serialization, native filesystem, network, editor/MCP, crash recovery, hardware/soak, ABI/release, DATA-02-10.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0010/0086/0111, `data-02-registry-v0`, DATA-02-08 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0111; QLF-R01..04; fixed capacities, stable ordering, typed errors, no host leakage.

## ARCHITECTURE RULES

Qualification exercises only the frozen DATA-02 headers; no alternate API or production behavior. Header-only internal C++20; single-owner values.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/package/secret/paid service/native I/O/network/persistence; CORE-01 not module-qualified; DATA-01 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-R01..04 pass.
- No production change; no persistence/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.
- Explicit statement that CI qualification is not physical/hardware or release qualification.

## TESTS

QLF-R01 integrated sequence; R02 deterministic repeat; R03 recovery after typed errors; R04 10,000 add/edge/tag/metadata/query attempts with stable capacities. Existing suite required.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-R01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale base, gate not merged, production/API drift, persistence/native I/O, allowlist violation, failed test, HIGH/CRITICAL, hardware/release/ABI claim.

## CONTEXT LOCK

Base `dfb10ed`; contract blob `ada255f8b4dc3d468adabaaecb074bfa3cfdbd1d`; DATA-02-08 code PR #608 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-02-09-G6-ACTIVATION.md` for the gate; `docs/evidence/NLE-PRPLAN-DATA-02-09.md` for qualification.
