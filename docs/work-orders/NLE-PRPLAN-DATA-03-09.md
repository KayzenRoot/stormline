# NLE-PRPLAN-DATA-03-09 — Integrated import qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-03-09`. **Predecessor:** `DATA-03-08` receipts. **Issue:** #26. **Base:** `ae1bab2`. **ADR:** [ADR-0112](../adr/0112-data-03-governance-slice.md). **Contract:** [data-03-import-v0](../contracts/data-03-import-v0.md).

## OBJECTIVE

Qualify the integrated logical import pipeline in CI: sniff→plan→metadata validation→receipt, deterministic repeat, typed-failure recovery and 10,000 bounded attempts. Internal/CI only; no decoder, native I/O, hardware, ABI or release claim.

## CONTEXT

DATA-03-01..08 are approved/completed. Each slice has its own tests; this packet adds QLF-I01..04 without production changes.

## SCOPE

- `tests/core/data03_import_qualification_tests.cpp`: QLF-I01..04.
- Additive CMake target/tests and workflow TSan target.
- `docs/evidence/NLE-PRPLAN-DATA-03-09.md`.

## OUT OF SCOPE

Production changes, decoders, conversion, archive, native filesystem, persistence, serialization, MCP, hardware/soak, ABI/release, DATA-03-10.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0011/0086/0112, `data-03-import-v0`, DATA-03-08 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0112; QLF-I01..04; fixed capacities, typed errors, deterministic results.

## ARCHITECTURE RULES

Qualification exercises frozen DATA-03 headers only; no alternate API or production behavior.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/decoder/native I/O/network/persistence; DATA-02 not qualified; CORE-01 not module-qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-I01..04 pass.
- No production change; no decoder/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-I01 integrated pipeline; I02 deterministic repeat; I03 recovery after typed errors; I04 10,000 descriptor/plan/validation/receipt attempts with stable capacities.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-I01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production/API drift, decoder/native I/O, allowlist violation, failed test, HIGH/CRITICAL, hardware/release/ABI claim.

## CONTEXT LOCK

Base `ae1bab2`; contract blob `2d893edd867be8dac20494bc50e0cd32a0b86a24`; DATA-03-08 code PR #625 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-03-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-03-09.md`.
