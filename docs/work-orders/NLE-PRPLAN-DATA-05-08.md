# NLE-PRPLAN-DATA-05-08 — Integrated bundle qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-08`. **Predecessor:** `DATA-05-07` patch plan. **Issue:** #28. **Base:** `eee95bc`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Qualify the integrated logical bundle pipeline in CI: target/cook→RLE→manifest/store→stream→patch, deterministic repeat, typed-failure recovery and 10,000 bounded attempts. Internal/CI only.

## CONTEXT

DATA-05-01..07 are approved/completed. This packet adds QLF-B01..04 without production changes.

## SCOPE

- `tests/core/data05_bundle_qualification_tests.cpp`: QLF-B01..04.
- Additive CMake target/tests and workflow TSan target.
- `docs/evidence/NLE-PRPLAN-DATA-05-08.md`.

## OUT OF SCOPE

Production changes, external codec, signing, network, persistence, native I/O, hardware/soak, ABI/release, DATA-05-09.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; QLF-B01..04; fixed capacities, deterministic results.

## ARCHITECTURE RULES

Qualification exercises frozen DATA-05 headers only; no alternate API.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/signing/network/persistence/native I/O; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-B01..04 pass.
- No production change; no codec/network/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-B01 integrated; B02 repeat; B03 recovery; B04 10,000 cook/RLE/manifest attempts with stable capacities.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-B01..04, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production/API drift, codec/network/native I/O, allowlist violation, failed test, HIGH/CRITICAL, hardware/release/ABI claim.

## CONTEXT LOCK

Base `eee95bc`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-07 code PR #653 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-08.md`.
