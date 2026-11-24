# NLE-PRPLAN-WORLD-03-03 — Spatial cell metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-03-03`. **Predecessor:** `WORLD-03-02` contract. **Issue:** #43. **Base:** `24f30ce`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Implement bounded logical cell metadata with stable nonzero keys, unique coordinates, signed coordinates, mathematical floor division and coordinate-bound plans.

## CONTEXT

WORLD-03-01/-02 are approved. No spatial index, cell storage, streaming runtime, I/O, cache or serializer exists.

## SCOPE

- `spatial_types.hpp`, `cell_plan.hpp` and CEL-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Interest queries, origin epochs, streaming plans, qualification, closeout; spatial index/storage, async tasks, I/O, decode, cache, origin rebase, physics, networking, renderer, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0129, internal contract, governance contract.

## REQUIREMENTS

GOV-001..007; ADR-0129; CEL-01.

## ARCHITECTURE RULES

WORLD-03 owns logical spatial metadata intent; WORLD-02 owns scene/prefab identity; DATA-05 owns streaming bundle metadata; CORE-05 owns coordinate math.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no spatial index/storage, async, I/O, decode, cache, origin rebase, physics/network/renderer/editor/GPU/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CEL-01 valid/invalid fixtures.
- No spatial index, cell storage, streaming task, I/O or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CEL-01 floor division (including negative values and `INT64_MIN`), world/revision/cell-count validation, unique keys and coordinates, signed bounds, capacity, reset and determinism.

## DELIVERABLES

Headers, CEL-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CEL-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, spatial index/storage/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `24f30ce`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-03-03.md`.
