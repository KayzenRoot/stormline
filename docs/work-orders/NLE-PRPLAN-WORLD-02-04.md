# NLE-PRPLAN-WORLD-02-04 — Prefab composition metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-04`. **Predecessor:** `WORLD-02-03` hierarchy. **Issue:** #42. **Base:** `fa9d8e7`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Implement bounded logical prefab composition metadata with nested references, depth and self-reference rejection.

## CONTEXT

WORLD-02-01..-03 are approved. No prefab expansion, runtime graph or serializer exists.

## SCOPE

- `prefab_composition_plan.hpp` and PFC-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Variants, instancing, transforms, qualification, closeout; prefab expansion, runtime graph, serializer, journal, spatial, physics, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, hierarchy boundary.

## REQUIREMENTS

GOV-001..007; ADR-0128; PFC-01.

## ARCHITECTURE RULES

WORLD-02 owns logical composition intent; DATA-02/04 own prefab assets/revisions/journal.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no expansion/runtime graph/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; PFC-01 valid/invalid fixtures.
- No prefab expansion, override merge or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PFC-01 prefab identity, depth, nested IDs, self-reference, duplicates, capacity, reset and determinism.

## DELIVERABLES

Header, PFC tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PFC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, expansion/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `fa9d8e7`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-04.md`.
