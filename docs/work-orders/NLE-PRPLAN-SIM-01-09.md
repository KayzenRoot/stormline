# NLE-PRPLAN-SIM-01-09 — Integrated physics 2D qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-01-09`. **Predecessor:** `SIM-01-08` masks. **Issue:** #46. **Base:** `b9833f50`. **ADR:** [ADR-0132](../adr/0132-sim-01-internal-physics-2d-metadata.md). **Contract:** [sim-01-physics2d-internal-v0](../contracts/sim-01-physics2d-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal physics 2D metadata sequence with one chained plan, deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

SIM-01-01..-08 are approved or completed. No contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU or physics runtime exists.

## SCOPE

- `tests/core/sim01_qualification_tests.cpp` with QLF-S101..S104.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Changes to production headers or earlier slice tests, closeout, contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU, physics runtime, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0132, internal contract, governance contract and all six physics2d headers.

## REQUIREMENTS

GOV-001..007; ADR-0132; QLF-S101..S104.

## ARCHITECTURE RULES

SIM-01 owns logical metadata intent; qualification exercises only the frozen planners and adds no collision, broadphase or runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, contact generation, broadphase, solver/backend, simulation, ECS mutation, GPU, physics runtime, editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S101..S104 executed as four CTest cases.
- No production header change, contact generation or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S101 chained planning (body → shape → query → joint → trigger → mask); QLF-S102 identical repeated plans; QLF-S103 typed failure followed by valid plans; QLF-S104 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S101..S104, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `b9833f50`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-01-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-01-09.md`.
