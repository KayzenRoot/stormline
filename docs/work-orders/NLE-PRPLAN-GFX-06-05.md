# NLE-PRPLAN-GFX-06-05 — GI fallback planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-05`. **Predecessor:** `GFX-06-04` shadows. **Issue:** #34. **Base:** `40c1e0d`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded GI mode selection with explicit baked/probe/environment fallback and typed unavailability.

## CONTEXT

GFX-06-01/-04 are approved/completed. No GI bake, probe eval, ray tracing, GPU or visual exists.

## SCOPE

- `gi_plan.hpp` and GI-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Probes, reflections, volumetrics, qualification; dynamic GI/bake, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, lighting headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; GI-01.

## ARCHITECTURE RULES

GFX-06 owns logical GI fallback; no bake, probe evaluation or ray tracing is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/GI compute/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; GI-01 valid/invalid fixtures.
- No GI bake/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

GI-01: baked/probe/environment/degraded/unavailable/unsupported.

## DELIVERABLES

Header, GI tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, GI-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, GI/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `40c1e0d`; contract blob pinned in activation; GFX-06-04 merge `40c1e0d`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-05.md`.
