# NLE-PRPLAN-SIM-04-05 — IK chain metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-05`. **Predecessor:** `SIM-04-04` blend trees. **Issue:** #49. **Base:** `ee971adf`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical IK chain metadata with chain/bone/iteration bounds, finite tolerance and target weight.

## CONTEXT

SIM-04-01..-04 are approved or completed. No IK solver, pose evaluation or animation runtime exists.

## SCOPE

- `ik_plan.hpp` and IK-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; IK execution/solver, pose evaluation, graph runtime, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, `skeletal_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0135; IK-01.

## ARCHITECTURE RULES

SIM-04 owns logical IK chain metadata only; no solver, runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no IK/pose/graph/codec/ragdoll/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; IK-01 valid/invalid fixtures.
- Bone/iteration bounds, finite tolerance, target weight `[0,1]`, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

IK-01 owner/revision/count validation, unique chain IDs, bone count 1..16, iterations 0..64, finite tolerance, target weight bounds, capacity, reset and determinism.

## DELIVERABLES

Header, IK-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, IK-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, solver/runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ee971adf`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-05.md`.
