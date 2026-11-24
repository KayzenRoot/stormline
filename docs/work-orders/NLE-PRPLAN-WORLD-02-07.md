# NLE-PRPLAN-WORLD-02-07 — Transform/reparent intent (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-07`. **Predecessor:** `WORLD-02-06` instancing. **Issue:** #42. **Base:** `4d40fe5`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Implement bounded logical transform/reparent intent with finite local TRS values and allowlisted reparent mode.

## CONTEXT

WORLD-02-01..-06 are approved. No matrix composition, world transform, physics authority or runtime graph exists.

## SCOPE

- `transform_plan.hpp` and TRS-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; matrix composition/inversion, world transforms, physics, runtime graph, serializer, journal, spatial, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, instancing boundary.

## REQUIREMENTS

GOV-001..007; ADR-0128; TRS-01.

## ARCHITECTURE RULES

WORLD-02 owns transform intent only; CORE-05 owns math and PHYS/GAME own authoritative state.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no matrix math/physics/runtime/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TRS-01 valid/invalid fixtures.
- No matrix composition, world transform or physics authority.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TRS-01 finite TRS, nonzero scale, reparent mode, unique nodes, capacity, reset and determinism.

## DELIVERABLES

Header, TRS tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRS-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, matrix/physics/runtime selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `4d40fe5`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-07.md`.
