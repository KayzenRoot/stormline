# NLE-PRPLAN-SIM-04-04 — Blend tree metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-04`. **Predecessor:** `SIM-04-03` retargeting. **Issue:** #49. **Base:** `90ea070b`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical blend-tree node metadata with kind allowlist, weight/threshold bounds and enabled counts.

## CONTEXT

SIM-04-01..-03 are approved or completed. No graph evaluation, pose blending or animation runtime exists.

## SCOPE

- `blend_tree_plan.hpp` and BLEND-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; graph evaluation, blend execution, pose evaluation, IK, ragdoll, codec, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, `skeletal_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0135; BLEND-01.

## ARCHITECTURE RULES

SIM-04 owns logical blend-node metadata only; no graph evaluation, runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no blend/graph/pose/solver/codec/ragdoll/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BLEND-01 valid/invalid fixtures.
- Kind allowlist, weights/thresholds in `[0,1]`, unique IDs, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BLEND-01 owner/revision/count validation, unique node IDs, kind allowlist, weight/threshold bounds, capacity, reset and determinism.

## DELIVERABLES

Header, BLEND-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BLEND-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, graph/evaluation/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `90ea070b`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-04.md`.
