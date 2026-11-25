# NLE-PRPLAN-SIM-04-08 — Sync group metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-08`. **Predecessor:** `SIM-04-07` compression. **Issue:** #49. **Base:** `790b4359`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Implement bounded logical sync group metadata with leader/member references, phase bounds and enabled counts.

## CONTEXT

SIM-04-01..-07 are approved or completed. No runtime synchronization or animation runtime exists.

## SCOPE

- `sync_plan.hpp` and SYNC-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Earlier slice changes, later slices, qualification, closeout; sincronização runtime, codec, pose evaluation, graph runtime, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract, `skeletal_types.hpp`.

## REQUIREMENTS

GOV-001..007; ADR-0135; SYNC-01.

## ARCHITECTURE RULES

SIM-04 owns logical sync metadata only; no runtime synchronization, runtime handle or backend type is exposed.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no sync runtime/codec/pose/graph/ECS/GPU/runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; SYNC-01 valid/invalid fixtures.
- Leader/member refs, phase `[0,1]`, unique IDs, capacity, reset and determinism.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SYNC-01 owner/revision/count validation, unique group IDs, nonzero leader, member count 1..32, phase bounds, phased/enabled counts, reset and determinism.

## DELIVERABLES

Header, SYNC-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SYNC-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/codec/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `790b4359`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-08.md`.
