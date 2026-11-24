# NLE-PRPLAN-WORLD-05-09 — Integrated procedural qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-05-09`. **Predecessor:** `WORLD-05-08` generators. **Issue:** #45. **Base:** `4226875`. **ADR:** [ADR-0131](../adr/0131-world-05-internal-procedural-generation-metadata.md). **Contract:** [world-05-procedural-internal-v0](../contracts/world-05-procedural-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal procedural sequence with deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

WORLD-05-01..-08 are approved or completed. No graph evaluation, RNG/noise, WFC, artifact production, cache or asset I/O exists.

## SCOPE

- `world05_qualification_tests.cpp` with QLF-W501..W504.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Changes to production headers or earlier slice tests, closeout, graph evaluation, RNG/noise, WFC, artifact production, asset I/O, cook/cache, GPU, physics, networking, editor.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0131, internal contract, governance contract and all six WORLD-05 headers.

## REQUIREMENTS

GOV-001..007; ADR-0131; QLF-W501..W504.

## ARCHITECTURE RULES

WORLD-05 owns logical metadata intent; qualification exercises only the frozen planners and adds no generation/runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, evaluation, RNG/noise, WFC, artifacts, cache, GPU, physics/network/editor; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-W501..W504 executed as four CTest cases.
- No production header change, evaluation, artifact or cache.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-W501 chained planning (seed → graph → rule → biome → geometry → generator); QLF-W502 identical repeated plans; QLF-W503 typed failure followed by valid plans; QLF-W504 10,000 bounded attempts honoring capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-W501..W504, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `4226875`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-05-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-05-09.md`.
