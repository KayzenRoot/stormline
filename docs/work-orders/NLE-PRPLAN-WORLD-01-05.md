# NLE-PRPLAN-WORLD-01-05 — Lifecycle transition metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-05`. **Predecessor:** `WORLD-01-04` components. **Issue:** #41. **Base:** `46834fb`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Implement bounded logical entity lifecycle transition validation with idempotent receipts.

## CONTEXT

WORLD-01-01..-04 are approved. No ECS storage mutation, tombstone storage or runtime destroy exists.

## SCOPE

- `lifecycle_plan.hpp` and LIF-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Queries, reflection, qualification, closeout; storage mutation, destruction, allocator, blueprint, serializer, persistence, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, component boundary.

## REQUIREMENTS

GOV-001..007; ADR-0127; LIF-01.

## ARCHITECTURE RULES

WORLD-01 owns logical transition intent; DATA-04 owns durable tombstones and undo/redo.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no storage/destruction/pointer/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; LIF-01 valid/invalid fixtures.
- No storage mutation, destroy execution or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

LIF-01 allowed/idempotent/invalid transitions, slot/generation bounds, duplicates, capacity, reset and determinism.

## DELIVERABLES

Header, LIF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, LIF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, storage/destroy/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `46834fb`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-05.md`.
