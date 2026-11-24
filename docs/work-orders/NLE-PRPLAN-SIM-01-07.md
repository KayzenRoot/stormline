# NLE-PRPLAN-SIM-01-07 — Trigger/sensor metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-07`. **Predecessor:** `SIM-01-06` joints. **Issue:** #46. **Base:** `f5ddeea`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Implement bounded logical trigger/sensor metadata with unique IDs, body/shape references, masks and event-enablement flags.

## CONTEXT

SIM-01-01..-06 are approved or completed. No sensor overlap detection, event dispatch or runtime trigger exists.

## SCOPE

- `trigger_plan.hpp` and TRG-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Prior slice changes, masks, qualification, closeout; sensor detection, event dispatch, solver/backend, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract, prior physics headers.

## REQUIREMENTS

GOV-001..007; ADR-0132; TRG-01.

## ARCHITECTURE RULES

SIM-01 owns logical trigger descriptors only; no event is dispatched and no runtime sensor exists.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no event dispatch/sensor detection/solver/backend/GPU/physics runtime/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; TRG-01 valid/invalid fixtures.
- No sensor detection, event dispatch or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TRG-01 world/revision/count validation, unique trigger IDs, nonzero body/shape refs/revisions, mask nonzero, at least one event enabled, enter/exit/both counts, capacity, reset and determinism.

## DELIVERABLES

Header, TRG-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TRG-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, event dispatch/backend selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `f5ddeea`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-07.md`.
