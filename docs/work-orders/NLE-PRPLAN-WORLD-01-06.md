# NLE-PRPLAN-WORLD-01-06 — Query intent metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-06`. **Predecessor:** `WORLD-01-05` lifecycle. **Issue:** #41. **Base:** `ad8eecf`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Implement bounded logical query intent metadata over required and excluded component type IDs.

## CONTEXT

WORLD-01-01..-05 are approved. No storage iteration, result set, borrow checker or query cache exists.

## SCOPE

- `query_plan.hpp` and QRY-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Reflection, qualification, closeout; storage iteration, query execution, results, caching, jobs, borrow checker, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, lifecycle boundary.

## REQUIREMENTS

GOV-001..007; ADR-0127; QRY-01.

## ARCHITECTURE RULES

WORLD-01 owns logical query intent; no storage access, iteration or result set is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no storage/iteration/cache/jobs/borrow/serializer/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QRY-01 valid/invalid fixtures.
- No storage access, query execution, cache or result iteration.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QRY-01 required/excluded sets, unique/nonzero type IDs, overlap rejection, bounds, reset and determinism.

## DELIVERABLES

Header, QRY tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QRY-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, storage/iteration/cache selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ad8eecf`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-06.md`.
