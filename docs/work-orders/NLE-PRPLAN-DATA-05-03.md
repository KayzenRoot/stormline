# NLE-PRPLAN-DATA-05-03 — Target profiles and cook plans (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-03`. **Predecessor:** `DATA-05-02` contract. **Issue:** #28. **Base:** `31c22d3`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Implement target profile validation and bounded cook plans over DATA-02 AssetIds. No external codec, archive, persistence, network or ABI.

## CONTEXT

DATA-05-01..02 are approved. DATA-03/DATA-04 are internally complete. CORE boundaries unchanged.

## SCOPE

- `bundle_types.hpp`, `cook_plan.hpp`.
- `tests/core/data05_target_tests.cpp`: TGT-01.
- Additive CMake target/test and workflow filters.
- Evidence file.

## OUT OF SCOPE

RLE/streaming/manifests/patch/qualification; codec/signing/persistence/native I/O/network/ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-02 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; TGT-01; target flags/tier and asset quotas.

## ARCHITECTURE RULES

DATA-05 owns logical cook plans; DATA-02 identity; DATA-03/04 sources; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; TGT-01 target/plan valid-invalid.
- No codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TGT-01 target id/flags/tier; asset count, duplicate, invalid id/revision, over-capacity and estimated bytes.

## DELIVERABLES

Headers, TGT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TGT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `31c22d3`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-02 contract PR #643 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-03.md`.
