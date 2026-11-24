# NLE-PRPLAN-WORLD-02-06 — Prefab instancing metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-06`. **Predecessor:** `WORLD-02-05` variants. **Issue:** #42. **Base:** `b0a2135`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Implement bounded logical prefab instance metadata with expansion counts/depth and checked totals.

## CONTEXT

WORLD-02-01..-05 are approved. No runtime instancing, entity creation or prefab expansion exists.

## SCOPE

- `instance_plan.hpp` and INS-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Transforms, qualification, closeout; runtime instancing, entity creation, expansion, serializer, journal, spatial, physics, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, variant boundary.

## REQUIREMENTS

GOV-001..007; ADR-0128; INS-01.

## ARCHITECTURE RULES

WORLD-02 owns logical instance intent; WORLD-01 owns entity creation and DATA-04 owns persistence.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/expansion/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INS-01 valid/invalid fixtures.
- No entity creation, expansion or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INS-01 instance identity, expansion bounds, depth, checked totals, capacity, reset and determinism.

## DELIVERABLES

Header, INS tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INS-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/expansion/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b0a2135`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-06.md`.
