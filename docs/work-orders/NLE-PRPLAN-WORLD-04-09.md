# NLE-PRPLAN-WORLD-04-09 — Integrated terrain/environment qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-04-09`. **Predecessor:** `WORLD-04-08` weather. **Issue:** #44. **Base:** `7acca25`. **ADR:** [ADR-0130](../adr/0130-world-04-internal-terrain-environment-metadata.md). **Contract:** [world-04-terrain-internal-v0](../contracts/world-04-terrain-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal terrain/environment sequence with deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

WORLD-04-01..-08 are approved or completed. No heightfield storage, renderer, GPU, simulation, physics or editor exists.

## SCOPE

- `world04_qualification_tests.cpp` with QLF-W401..W404.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Changes to production headers or earlier slice tests, closeout, terrain/water rendering, GPU LOD, texture residency, instancing, simulation, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0130, internal contract, governance contract and all six WORLD-04 headers.

## REQUIREMENTS

GOV-001..007; ADR-0130; QLF-W401..W404.

## ARCHITECTURE RULES

WORLD-04 owns logical metadata intent; qualification exercises only the frozen planners and adds no engine/runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, renderer, GPU, simulation, physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-W401..W404 executed as four CTest cases.
- No production header change, renderer, GPU or simulation.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-W401 chained planning (terrain → splat → vegetation → water → sky → weather); QLF-W402 identical repeated plans; QLF-W403 typed failure followed by valid plans; QLF-W404 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-W401..W404, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `7acca25`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-04-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-04-09.md`.
