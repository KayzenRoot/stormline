# NLE-PRPLAN-SIM-03-07 — Integrated character motor metadata qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-SIM-03-07`. **Predecessor:** `SIM-03-06` camera. **Issue:** #48. **Base:** `694a50e8`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Contract:** [sim-03-character-internal-v0](../contracts/sim-03-character-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal character motor metadata sequence with one chained plan, deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

SIM-03-01..-06 are approved or completed. No motor, sweeper, contact execution, input layer or camera update exists.

## SCOPE

- `tests/core/sim03_qualification_tests.cpp` with QLF-S301..S304.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Production header or earlier test changes, closeout; motor/sweeper, contacts, solver/backend, input devices, camera update, ECS mutation, GPU, character runtime.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0134, internal contract, governance contract and all four character headers.

## REQUIREMENTS

GOV-001..007; ADR-0134; QLF-S301..S304.

## ARCHITECTURE RULES

SIM-03 owns logical metadata intent; qualification exercises only the frozen planners and adds no movement, contact or runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, motor/sweeper, contact, input device, camera update, ECS mutation, GPU, runtime; CORE-01/02/03 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S301..S304 executed as four CTest cases.
- No production header change, contact or movement simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S301 chained planning (controller → locomotion → input → camera); QLF-S302 identical repeated plans; QLF-S303 typed failure followed by valid plans; QLF-S304 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S301..S304, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `694a50e8`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-SIM-03-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-SIM-03-07.md`.
