# NLE-PRPLAN-WORLD-01-04 — Component schema metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-04`. **Predecessor:** `WORLD-01-03` identity. **Issue:** #41. **Base:** `67599dd`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Implement bounded logical component type and field schema metadata with stable IDs, versions and finite field ranges.

## CONTEXT

WORLD-01-01..-03 are approved. No ECS storage, memory layout, type construction or serializer exists.

## SCOPE

- `component_schema_plan.hpp` and CMP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Lifecycle, queries, reflection, qualification, closeout; storage, allocator, pointer access, RTTI identity, serialization, migration, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, identity boundary.

## REQUIREMENTS

GOV-001..007; ADR-0127; CMP-01.

## ARCHITECTURE RULES

WORLD-01 owns logical schema intent; DATA-04 owns persistence/migration and C++ type layout is not represented.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no storage/pointer/RTTI/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CMP-01 valid/invalid fixtures.
- No storage, layout, RTTI hash, serializer or migration.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CMP-01 unique type/field IDs, versions, kinds, finite ordered ranges, capacity, reset and determinism.

## DELIVERABLES

Header, CMP tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CMP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, storage/RTTI/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `67599dd`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-04.md`.
