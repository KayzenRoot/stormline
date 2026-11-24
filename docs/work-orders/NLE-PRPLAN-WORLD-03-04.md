# NLE-PRPLAN-WORLD-03-04 — Interest query metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-03-04`. **Predecessor:** `WORLD-03-03` cells. **Issue:** #43. **Base:** `c5cc0e5`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Implement bounded logical interest-source metadata with finite bounds, allowlisted roles, priority metadata, union bounds and completeness counts.

## CONTEXT

WORLD-03-01/-02 are approved and WORLD-03-03 cells are completed. No spatial index, query result, cell storage or streaming runtime exists.

## SCOPE

- `interest_plan.hpp` and INT-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Cell changes, origin epochs, streaming plans, qualification, closeout; spatial index/query results, storage, async tasks, I/O, decode, cache, origin rebase, physics, networking, renderer, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0129, internal contract, governance contract, `spatial_types.hpp`, `cell_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0129; INT-01.

## ARCHITECTURE RULES

WORLD-03 owns logical spatial metadata intent; WORLD-02 owns scene/prefab identity; DATA-05 owns streaming bundle metadata; CORE-05 owns coordinate math.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no spatial index/query result/storage, async, I/O, decode, cache, origin rebase, physics/network/renderer/editor/GPU/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INT-01 valid/invalid fixtures.
- No spatial index, query result, cell storage, streaming task, I/O or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INT-01 world/revision/count validation, unique source IDs and revisions, allowlisted roles, finite ordered bounds, union bounds, completeness counts, capacity, reset and determinism.

## DELIVERABLES

Header, INT-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INT-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, spatial index/query runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `c5cc0e5`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-03-04.md`.
