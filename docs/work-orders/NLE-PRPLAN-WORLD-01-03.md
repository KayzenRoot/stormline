# NLE-PRPLAN-WORLD-01-03 — Generational identity metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-03`. **Predecessor:** `WORLD-01-02` contract. **Issue:** #41. **Base:** `6e1e601`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Implement bounded logical world identity and generational entity handle validation metadata.

## CONTEXT

WORLD-01-01/-02 are approved. No ECS storage, allocator, thread, serializer or runtime handle exists.

## SCOPE

- `world_types.hpp`, `entity_identity_plan.hpp` and ENT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Components, lifecycle, queries, reflection, qualification, closeout; ECS storage, pointer access, serialization, persistence, hierarchy, spatial, physics, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, governance contract.

## REQUIREMENTS

GOV-001..007; ADR-0127; ENT-01.

## ARCHITECTURE RULES

WORLD-01 owns logical identity intent; DATA-02/04 own persistent GUIDs and scenes.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no storage/pointer/serialization/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; ENT-01 valid/invalid fixtures.
- No storage, pointer, serializer, component or lifecycle implementation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

ENT-01 epoch/slot/generation validity, occupied/free/retired slots, stale and cross-epoch rejection, capacity, reset and determinism.

## DELIVERABLES

Headers, ENT tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, ENT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, storage/pointer/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6e1e601`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-03.md`.
