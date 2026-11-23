# NLE-PRPLAN-GFX-06-06 — Probe volume metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-06-06`. **Predecessor:** `GFX-06-05` GI. **Issue:** #34. **Base:** `80a2717`. **ADR:** [ADR-0120](../adr/0120-gfx-06-internal-lighting-pipeline.md). **Contract:** [gfx-06-lighting-internal-v0](../contracts/gfx-06-lighting-internal-v0.md).

## OBJECTIVE

Implement bounded probe-volume metadata validation, generation checks and deterministic ordering.

## CONTEXT

GFX-06-01/-05 are approved/completed. No probe bake, SH evaluation, GPU upload or render exists.

## SCOPE

- `probe_plan.hpp` and PRB-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Reflections, volumetrics, qualification; probe bake/eval, GPU, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0120, internal contract, lighting headers.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0120; PRB-01.

## ARCHITECTURE RULES

GFX-06 owns logical probe metadata; no bake, SH evaluation or GPU resource is created.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/probe bake/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; PRB-01 valid/invalid fixtures.
- No probe bake/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

PRB-01: IDs/revisions/spacing/cells/products/generation/order/capacity.

## DELIVERABLES

Header, PRB tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, PRB-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, probe/GPU selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `80a2717`; contract blob pinned in activation; GFX-06-05 merge `80a2717`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-06-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-06-06.md`.
