# NLE-PRPLAN-SIM-02-09 — Integrated 3D physics metadata qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-02-09`. **Predecessor:** `SIM-02-08` integrations. **Issue:** #47. **Base:** `0907615b`. **ADR:** [ADR-0133](../adr/0133-sim-02-internal-physics-3d-metadata.md). **Contract:** [sim-02-physics3d-internal-v0](../contracts/sim-02-physics3d-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal 3D metadata sequence with one chained plan, deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

SIM-02-01..-08 are approved or completed. No solver, broadphase, query execution, contact or simulation exists.

## SCOPE

- `tests/core/sim02_qualification_tests.cpp` with QLF-S201..S204.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Production header or earlier test changes, closeout; solver/backend, broadphase/narrowphase execution, query execution, contacts, simulation, ECS mutation, GPU, physics runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0133, internal contract, governance contract and all six physics3d headers.

## REQUIREMENTS

GOV-001..007; ADR-0133; QLF-S201..S204.

## ARCHITECTURE RULES

SIM-02 owns logical metadata intent; qualification exercises only the frozen planners and adds no collision, broadphase or runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, solver/backend, broadphase/query execution, contacts, simulation, ECS mutation, GPU, runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S201..S204 executed as four CTest cases.
- No production header change, contact, broadphase or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S201 chained planning (body → shape → layer → query → constraint → integration); QLF-S202 identical repeated plans; QLF-S203 typed failure followed by valid plans; QLF-S204 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S201..S204, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `0907615b`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-02-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-02-09.md`.
