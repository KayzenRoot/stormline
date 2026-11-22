# NLE-PRPLAN-DATA-04-07 — Integrated scene qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-04-07`. **Predecessor:** `DATA-04-06` diffs. **Issue:** #27. **Base:** `5163c81`. **ADR:** [ADR-0113](../adr/0113-data-04-governance-slice.md). **Contract:** [data-04-scene-v0](../contracts/data-04-scene-v0.md).

## OBJECTIVE

Qualify the integrated logical scene pipeline in CI: schema→document→components/refs→patch→diff, deterministic repeat, typed-failure recovery and 10,000 bounded attempts. Internal/CI only.

## CONTEXT

DATA-04-01..06 are approved/completed. This packet adds QLF-S01..04 without production changes.

## SCOPE

- `tests/core/data04_scene_qualification_tests.cpp`: QLF-S01..04.
- Additive CMake target/tests and workflow TSan target.
- `docs/evidence/NLE-PRPLAN-DATA-04-07.md`.

## OUT OF SCOPE

Production changes, JSON/CBOR, persistence, migration, native filesystem, MCP, hardware/soak, ABI/release, DATA-04-08.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0012/0086/0113, `data-04-scene-v0`, DATA-04-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0113; QLF-S01..04; fixed capacities, deterministic results.

## ARCHITECTURE RULES

Qualification exercises frozen DATA-04 headers only; no alternate API.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; CORE-05/DATA-02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S01..04 pass.
- No production change; no codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S01 integrated; S02 repeat; S03 recovery; S04 10,000 entity/component/ref/patch attempts with stable capacities.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production/API drift, codec/native I/O, allowlist violation, failed test, HIGH/CRITICAL, hardware/release/ABI claim.

## CONTEXT LOCK

Base `5163c81`; contract blob `99962b6a800d5219db46ce42cf4abb34f6d0ac57`; DATA-04-06 code PR #638 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-04-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-04-07.md`.
