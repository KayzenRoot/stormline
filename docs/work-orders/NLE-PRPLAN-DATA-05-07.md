# NLE-PRPLAN-DATA-05-07 — Incremental chunk reuse (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-07`. **Predecessor:** `DATA-05-06` manifests. **Issue:** #28. **Base:** `1386689`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Compare two manifest generations and produce a bounded reuse/fetch plan by chunk ID and fingerprint. No download, persistence, signing or network.

## CONTEXT

DATA-05-01..06 are approved/completed. Manifests/fingerprints exist. DATA-03/DATA-04 are not qualified.

## SCOPE

- `patch_plan.hpp`.
- `tests/core/data05_patch_tests.cpp`: PAT-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; download/signing/persistence/network/native I/O/ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; PAT-01; generation fencing, fingerprint-based reuse/fetch.

## ARCHITECTURE RULES

DATA-05 owns logical patch planning; no network/persistence; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no signing/network/persistence/native I/O; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; PAT-01 reuse/fetch/conflict.
- No signing/network/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PAT-01 same/different fingerprint, missing base chunk, generation conflict and zero manifest. Existing suite required.

## DELIVERABLES

Header, PAT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PAT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, signing/network/native I/O, unbounded patch, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `1386689`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-06 code PR #651 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-07.md`.
