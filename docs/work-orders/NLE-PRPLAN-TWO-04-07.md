# NLE-PRPLAN-TWO-04-07 — Integrated hybrid qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-TWO-04-07`. **Predecessor:** `TWO-04-06` effects. **Issue:** #40. **Base:** `efd3a4f`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Contract:** [two-04-hybrid-internal-v0](../contracts/two-04-hybrid-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal hybrid planners with deterministic repeat, failure recovery and bounded overload fixtures.

## CONTEXT

TWO-04-01..-06 are approved. No runtime rendering, GPU, lighting or subview execution exists.

## SCOPE

- `two04_hybrid_qualification_tests.cpp` with QLF-T401..T404.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; runtime, renderer, GPU, lighting, shadows, subview execution, editor, export, hardware, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0126, internal contract, camera/layer/sort/effect headers.

## REQUIREMENTS

GOV-001..007; ADR-0126; QLF-T401..T404.

## ARCHITECTURE RULES

Qualification exercises planner contracts only; no runtime or rendering behavior is claimed.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/render/GPU/dependency/native I/O/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-T401..T404 pass.
- 10,000 bounded attempts stay within caps.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-T401 integrated planners; QLF-T402 deterministic repeat; QLF-T403 failure recovery; QLF-T404 bounded overload.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-T401..T404, sanitizers/CI, errors/corrections, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/render/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `efd3a4f`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-TWO-04-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-TWO-04-07.md`.
