# NLE-PRPLAN-WORLD-03-05 — Origin epoch metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-03-05`. **Predecessor:** `WORLD-03-04` interest. **Issue:** #43. **Base:** `9e353ca`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Implement bounded logical origin-epoch intent with distinct epochs, finite origins and acceptance gated by physics, render and network acknowledgements.

## CONTEXT

WORLD-03-01/-02 are approved and WORLD-03-03/-04 are completed. No origin rebase, coordinate rewrite, cell storage or streaming runtime exists.

## SCOPE

- `origin_plan.hpp` and ORG-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Cell/interest changes, streaming plans, qualification, closeout; origin rebase execution, entity/cell identity changes, async tasks, I/O, decode, cache, physics, networking, renderer, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0129, internal contract, governance contract, `spatial_types.hpp`, `cell_plan.hpp`, `interest_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0129; ORG-01.

## ARCHITECTURE RULES

WORLD-03 owns logical spatial metadata intent; WORLD-02 owns scene/prefab identity; DATA-05 owns streaming bundle metadata; CORE-05 owns coordinate math.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no origin rebase/identity rewrite, async, I/O, decode, cache, physics/network/renderer/editor/GPU/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; ORG-01 valid/invalid fixtures.
- No origin rebase, coordinate rewrite, cell storage, streaming task, I/O or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

ORG-01 world/revision/epoch validation, distinct epochs, finite old/new origins, acknowledgement matrix (physics/render/network), reset and determinism.

## DELIVERABLES

Header, ORG-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, ORG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, origin rebase/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `9e353ca`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-03-05.md`.
