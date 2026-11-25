# NLE-PRPLAN-SIM-04-06 — Ragdoll profile metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-06`. **Predecessor:** `SIM-04-05` IK. **Issue:** #49. **Base:** `e2c3428b`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical ragdoll profile metadata with body/constraint mapping references, activation weight and auto/enabled counts.

## CONTEXT

SIM-04-01..-05 are approved or completed. SIM-02 owns physics lifetime; no ragdoll activation or animation runtime exists.

## SCOPE

- `ragdoll_plan.hpp` and RAG-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; ragdoll runtime/activation, physics solver/backend, pose evaluation, graph runtime, codec, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, `skeletal_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0135; RAG-01.

## ARCHITECTURE RULES

SIM-04 owns logical ragdoll mapping metadata only; SIM-02 owns physics lifetime; no runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no ragdoll/physics/solver/pose/graph/codec/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; RAG-01 valid/invalid fixtures.
- Mapping refs nonzero, activation weight `[0,1]`, unique IDs, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

RAG-01 owner/revision/count validation, unique profile IDs, nonzero body/constraint mappings, activation weight bounds, capacity, reset and determinism.

## DELIVERABLES

Header, RAG-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, RAG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, physics/ragdoll runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `e2c3428b`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-06.md`.
