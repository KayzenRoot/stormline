# NLE-PRPLAN-WORLD-03-06 — Streaming plan metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-03-06`. **Predecessor:** `WORLD-03-05` origin. **Issue:** #43. **Base:** `6891266`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Implement bounded logical streaming-plan metadata with unique cell keys, allowlisted priorities, request/cancel generations, per-cell byte budgets and checked totals.

## CONTEXT

WORLD-03-01/-02 are approved and WORLD-03-03/-04/-05 are completed. No streaming task, I/O, decode, cache or bundle execution exists.

## SCOPE

- `streaming_plan.hpp` and STR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Cell/interest/origin changes, qualification, closeout; task creation/cancellation, I/O, decode, cache, bundle loading, origin rebase, physics, networking, renderer, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0129, internal contract, governance contract, `spatial_types.hpp`, `cell_plan.hpp`, `interest_plan.hpp`, `origin_plan.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0129; STR-01.

## ARCHITECTURE RULES

WORLD-03 owns logical spatial metadata intent; WORLD-02 owns scene/prefab identity; DATA-05 owns streaming bundle metadata; CORE-05 owns coordinate math.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no task/I-O/decode/cache/bundle execution, origin rebase, async, physics/network/renderer/editor/GPU/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; STR-01 valid/invalid fixtures.
- No streaming task, I/O, decode, cache, bundle execution or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

STR-01 world/revision/count validation, unique keys, allowlisted priorities, nonzero request generation, cancel `<=` request, per-cell budget `<= 1 GiB`, checked totals, counts, capacity, reset and determinism.

## DELIVERABLES

Header, STR-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, STR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, task/I-O/decode/cache runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `6891266`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-03-06.md`.
