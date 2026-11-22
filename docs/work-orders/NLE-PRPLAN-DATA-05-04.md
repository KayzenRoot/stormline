# NLE-PRPLAN-DATA-05-04 — Bounded RLE (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-DATA-05-04`. **Predecessor:** `DATA-05-03` target/cook. **Issue:** #28. **Base:** `348089b`. **ADR:** [ADR-0114](../adr/0114-data-05-governance-slice.md). **Contract:** [data-05-bundle-v0](../contracts/data-05-bundle-v0.md).

## OBJECTIVE

Implement a bounded Stormline-owned RLE codec over at most 256 bytes with run splitting, exact required output size and typed decode limits. No external codec.

## CONTEXT

DATA-05-01..03 are approved/completed. Target/cook plans exist. DATA-03/DATA-04 are not qualified.

## SCOPE

- `rle.hpp`.
- `tests/core/data05_rle_tests.cpp`: RLE-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Streaming/manifests/patch/qualification; external codec, archive, persistence, native I/O, network, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0013/0086/0114, `data-05-bundle-v0`, DATA-05-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0114; RLE-01; 256-byte cap, run split, typed failures.

## ARCHITECTURE RULES

DATA-05 owns logical RLE; no external codec; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no codec/dependency/native I/O/network/persistence; DATA-03/04 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; RLE-01 roundtrip/split/bounds.
- No external codec/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RLE-01 roundtrip, 255-run split, empty, buffer full required sizes, zero/odd run, decode limit.

## DELIVERABLES

Header, RLE tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RLE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, external codec/native I/O, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `348089b`; contract blob `d1f4b3717a391c09ccd47a2b2e2a1261d1e4b348`; DATA-05-03 code PR #645 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-DATA-05-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-DATA-05-04.md`.
