# NLE-PRPLAN-SIM-04-07 — Compression profile metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-07`. **Predecessor:** `SIM-04-06` ragdoll. **Issue:** #49. **Base:** `2b2c0d9e`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical animation compression profile metadata with bit widths, keyframe intervals, lossless flags and enabled counts.

## CONTEXT

SIM-04-01..-06 are approved or completed. No codec, compression or animation runtime exists.

## SCOPE

- `compression_plan.hpp` and CMP-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; codec/compressão real, pose evaluation, graph runtime, ragdoll, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, `skeletal_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0135; CMP-01.

## ARCHITECTURE RULES

SIM-04 owns logical compression metadata only; no codec, runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no codec/pose/graph/IK/ragdoll/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; CMP-01 valid/invalid fixtures.
- Bit widths `1..32`, keyframe interval `1..240`, unique IDs, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

CMP-01 owner/revision/count validation, unique profile IDs, bit widths, keyframe interval bounds, lossless/enabled counts, reset and determinism.

## DELIVERABLES

Header, CMP-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, CMP-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, codec/runtime/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `2b2c0d9e`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-07.md`.
