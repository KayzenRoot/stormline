# NLE-PRPLAN-GFX-06-07 — Reflection fallback planning (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-07`. **Predecessor:** `GFX-06-06` probes. **Issue:** #34. **Base:** `10e43ca`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded reflection mode selection with SSR/probe/environment fallback and explicit offscreen metadata.

## CONTEXT

GFX-06-01/-06 are approved/completed. No SSR march, ray query, probe eval, GPU or render exists.

## SCOPE

- `reflection_plan.hpp` and REF-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Volumetrics, qualification; SSR/ray tracing, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, lighting headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; REF-01.

## ARCHITECTURE RULES

GFX-06 owns logical reflection fallback; no SSR pass, ray query or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/SSR/ray-tracing/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; REF-01 valid/invalid fixtures.
- No SSR/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

REF-01: SSR/probe/environment fallback, offscreen/degraded/unavailable, roughness/enum.

## DELIVERABLES

Header, REF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, REF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, SSR/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `10e43ca`; contract blob pinned in activation; GFX-06-06 merge `10e43ca`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-07.md`.
