# NLE-PRPLAN-GFX-01-09 — Internal RHI qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-09`. **Predecessor:** `GFX-01-08` feature tiers. **Issue:** #29. **Base:** `b580648`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Add CI-only qualification tests QLF-G01..G04 over the complete logical RHI: integrated flow, deterministic repeat, failure recovery and bounded overload. No native GPU qualification.

## CONTEXT

GFX-01-01..08 are approved/completed. The logical Null/reference RHI is complete; qualification is internal only.

## SCOPE

- `tests/core/gfx01_rhi_qualification_tests.cpp`: QLF-G01..G04.
- Additive CMake target/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout (`-10`); native GPU/driver/hardware, rendering, shaders, performance, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-08 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; QLF-G01..G04.

## ARCHITECTURE RULES

GFX-01 owns logical qualification; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; qualification does not imply physical hardware, ABI or release; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G01..G04 pass.
- 10,000 bounded attempts keep capacities and reject excess with typed errors.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G01 integrated adapter/device/queue/buffer/texture/barrier/loss/recover; QLF-G02 deterministic repeated snapshot; QLF-G03 each typed failure followed by valid operation; QLF-G04 10,000 create/submit/barrier attempts with bounded capacities.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G01..G04, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, native GPU/hardware/performance claim, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `b580648`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-08 code PR #670 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-09.md`.
