# NLE-PRPLAN-GFX-04-09 — Geometry pipeline qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-09`. **Predecessor:** `GFX-04-08` budget. **Issue:** #32. **Base:** `15c30b8`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Add CI-only qualification QLF-G401..G404 over the complete logical geometry pipeline: integrated flow, deterministic repeat, failure recovery and bounded overload.

## CONTEXT

GFX-04-01..08 are approved/completed. No native GPU, mesh library, I/O, submission or renderer exists.

## SCOPE

- `tests/core/gfx04_geometry_qualification_tests.cpp`: QLF-G401..G404.
- Additive CMake target/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout (`-10`); native GPU/mesh library/hardware, I/O, submission, rendering, performance, ABI or release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, contract, budget evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; QLF-G401..G404.

## ARCHITECTURE RULES

GFX-04 owns logical qualification; no native GPU/mesh library/submission; qualification is not hardware proof.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/IO/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G401..G404 pass.
- 10,000 pipeline attempts keep capacities.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G401 integrated; QLF-G402 deterministic snapshot; QLF-G403 typed failure then valid; QLF-G404 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G401..G404, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, native GPU/mesh library/hardware/performance claim, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `15c30b8`; contract blob pinned in activation; GFX-04-08 merge `15c30b8`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-09.md`.
