# NLE-PRPLAN-SIM-04-03 — Retarget profile metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-03`. **Predecessor:** `SIM-04-02` contract. **Issue:** #49. **Base:** `2ec52f00`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical retarget profile metadata with unique profiles, joint mapping pairs, positive bind scale and enabled counts.

## CONTEXT

SIM-04-01 and -02 are approved. No pose conversion, evaluator or animation runtime exists.

## SCOPE

- `animation_types.hpp`, `retarget_plan.hpp` and RET-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, later slices, qualification, closeout; pose conversion/evaluation, graph runtime, IK, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, ADR-0034 research architecture.

## REQUIREMENTS

GOV-001..007; ADR-0135; RET-01.

## ARCHITECTURE RULES

SIM-04 owns logical retarget metadata only; no pose conversion, runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no pose/solver/codec/ragdoll/root-motion/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; RET-01 valid/invalid fixtures.
- Unique profiles/joint pairs, positive bind scale, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RET-01 owner/revision/count validation, unique profile IDs, nonzero joint pairs, unique source/target joints, positive finite bind scale, capacity, reset and determinism.

## DELIVERABLES

Headers, RET-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RET-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, pose/runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2ec52f00`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-03.md`.
