# NLE-PRPLAN-WORLD-03-07 — Integrated spatial qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-03-07`. **Predecessor:** `WORLD-03-06` streaming. **Issue:** #43. **Base:** `4cb6a6d`. **ADR:** [ADR-0129](../adr/0129-world-03-internal-spatial-streaming-metadata.md). **Contract:** [world-03-spatial-internal-v0](../contracts/world-03-spatial-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal sequence cells → interest → origin → streaming with deterministic repetition, typed failure recovery and bounded overload behavior.

## CONTEXT

WORLD-03-01..-06 are approved or completed. No spatial index, storage, asynchronous task, I/O or bundle execution exists.

## SCOPE

- `world03_qualification_tests.cpp` with QLF-W301..W304.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Changes to production headers or earlier slice tests, closeout, spatial index/storage, async tasks, I/O, decode, cache, origin rebase, physics, networking, renderer, editor, GPU, performance.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0129, internal contract, governance contract and all four WORLD-03 headers.

## REQUIREMENTS

GOV-001..007; ADR-0129; QLF-W301..W304.

## ARCHITECTURE RULES

WORLD-03 owns logical spatial metadata intent; the qualification exercises only the frozen public planners and never adds engine/runtime behavior.

## CONSTRAINTS

Risk `LOW`; `INTERNAL_ONLY`; no production-code change, spatial index/storage, async, I/O, decode, cache, origin rebase, physics/network/renderer/editor/GPU/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-W301..W304 executed as four CTest cases.
- No production header change, index, storage, task, I/O or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-W301 chained planning; QLF-W302 identical repeated plans; QLF-W303 typed failure followed by valid plans; QLF-W304 10,000 bounded attempts honoring all capacities.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-W301..W304, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, production drift, allowlist violation, failed test, HIGH/CRITICAL, qualification/release/ABI overclaim.

## CONTEXT LOCK

Base `4cb6a6d`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-03-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-03-07.md`.
