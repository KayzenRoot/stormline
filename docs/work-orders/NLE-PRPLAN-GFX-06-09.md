# NLE-PRPLAN-GFX-06-09 — Integrated lighting qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-09`. **Predecessor:** `GFX-06-08` volumetrics. **Issue:** #34. **Base:** `0e254e1`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-G601..G604 across lights, shadows, GI, probes, reflections and volumetrics.

## CONTEXT

GFX-06-01/-08 are approved/completed. No native GPU, shadow map, ray tracing, GI/probe bake, SSR, froxel, renderer or hardware path exists.

## SCOPE

- `tests/core/gfx06_lighting_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout, native GPU/shadow/ray-tracing, rendering, driver/hardware, visual golden, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, all GFX-06 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; QLF-G601..G604.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no native GPU/shadow/GI/probe/SSR/froxel/hardware behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/shadow/ray-tracing/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G601..G604 pass.
- No native GPU/shadow/GI/probe/SSR/froxel/render/hardware claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G601 integrated pipeline; G602 deterministic repeat; G603 typed failure recovery; G604 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G601..G604, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/shadow/GI/SSR/froxel/hardware claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `0e254e1`; contract blob pinned in activation; GFX-06-08 merge `0e254e1`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-09.md`.
