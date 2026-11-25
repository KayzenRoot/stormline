# NLE-PRPLAN-SIM-04-09 — Integrated skeletal animation qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-04-09`. **Predecessor:** `SIM-04-08` sync. **Issue:** #49. **Base:** `47ffe5cd`. **ADR:** [ADR-0135](../adr/0135-sim-04-internal-skeletal-animation-metadata.md). **Contract:** [sim-04-animation-internal-v0](../contracts/sim-04-animation-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal skeletal animation metadata sequence with one chained plan, deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

SIM-04-01..-08 are approved or completed. No pose evaluator, graph runtime, IK/ragdoll/codec/sync runtime or animation runtime exists.

## SCOPE

- `tests/core/sim04_qualification_tests.cpp` with QLF-S401..S404.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Production header or earlier test changes, closeout; pose evaluation, graph runtime, IK/ragdoll/codec/sync runtime, root motion, ECS mutation, GPU, animation runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0135, internal contract, governance contract and all six skeletal headers.

## REQUIREMENTS

GOV-001..007; ADR-0135; QLF-S401..S404.

## ARCHITECTURE RULES

SIM-04 owns logical metadata intent; qualification exercises only the frozen planners and adds no pose, solver, codec or runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, pose/solver/codec/ragdoll/sync runtime, ECS mutation, GPU; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S401..S404 executed as four CTest cases.
- No production header change, pose evaluation or runtime behavior.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S401 chained planning (retarget → blend → IK → ragdoll → compression → sync); QLF-S402 identical repeated plans; QLF-S403 typed failure followed by valid plans; QLF-S404 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S401..S404, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `47ffe5cd`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-04-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-04-09.md`.
