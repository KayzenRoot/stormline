# NLE-PRPLAN-DATA-05-05 — Chunked streaming window (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-05`. **Predecessor:** `DATA-05-04` RLE. **Issue:** #28. **Base:** `1a9f3e9`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Implement an in-memory chunk store and generation-fenced streaming window with byte budget and idempotent requests. No network, persistence, native I/O or ABI.

## CONTEXT

DATA-05-01..04 are approved/completed. Target/cook and RLE exist. DATA-03/DATA-04 are not qualified.

## SCOPE

- `stream_window.hpp` (manifest entry/table, chunk store, stream window).
- `tests/core/data05_stream_tests.cpp`: STR-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Fingerprint verification/manifests/patch/qualification; network, persistence, native I/O, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; STR-01; generation/budget/range checks.

## ARCHITECTURE RULES

DATA-05 owns logical streaming; no network; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/network/persistence/native I/O; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; STR-01 generation/budget/idempotence/missing.
- No network/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

STR-01 manifest/store/window, generation mismatch, budget overflow, idempotent repeat, missing chunk and store capacity.

## DELIVERABLES

Header, STR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, STR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, network/native I/O, unbounded streaming, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `1a9f3e9`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-04 code PR #647 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-05.md`.
