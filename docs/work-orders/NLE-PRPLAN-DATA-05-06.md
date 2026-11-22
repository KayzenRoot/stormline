# NLE-PRPLAN-DATA-05-06 — Manifests and fingerprints (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-06`. **Predecessor:** `DATA-05-05` streaming. **Issue:** #28. **Base:** `95466bf`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Add FNV-1a 64 fingerprinting and manifest chunk verification. Non-cryptographic integrity only; no signing or trust claim.

## CONTEXT

DATA-05-01..05 are approved/completed. Manifest table and stream window exist. DATA-03/DATA-04 are not qualified.

## SCOPE

- `bundle_manifest.hpp`.
- `tests/core/data05_manifest_tests.cpp`: MAN-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Patch plan/qualification; signing/trust, external codec, network, persistence, native I/O, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; MAN-01; FNV stability, length/fingerprint mismatch.

## ARCHITECTURE RULES

DATA-05 owns manifest verification; no signing claim; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/network/persistence/native I/O; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; MAN-01 FNV/verify.
- No signing/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

MAN-01 known FNV values, match/mismatch, length and missing chunk; no cryptographic claim.

## DELIVERABLES

Header, MAN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, MAN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, signing/crypto claim, native I/O, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `95466bf`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-05 code PR #649 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-06.md`.
