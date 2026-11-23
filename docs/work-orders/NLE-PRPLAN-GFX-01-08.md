# NLE-PRPLAN-GFX-01-08 — Logical feature tiers (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-08`. **Predecessor:** `GFX-01-07` synchronization. **Issue:** #29. **Base:** `7d89052`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement bounded logical feature/tier helpers and TIER-01 tests over the existing adapter/device capability validation. No native GPU.

## CONTEXT

GFX-01-01..07 are approved/completed. Device init already rejects unsupported feature bits and tiers. No native backend.

## SCOPE

- `rhi_feature.hpp`: supported-tier constant plus feature/tier predicates.
- `tests/core/gfx01_feature_tests.cpp`: TIER-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification/closeout; native GPU, raytracing/mesh shaders, rendering, shader, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-07 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; TIER-01; exact feature/tier semantics.

## ARCHITECTURE RULES

GFX-01 owns logical feature tiers; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; TIER-01 supported/unsupported features and tiers.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TIER-01: each known feature accepted, unknown/zero features rejected, tier 1 accepted, tier 0/2 rejected, capabilities preserved across recovery.

## DELIVERABLES

Header, TIER tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TIER-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/raytracing, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `7d89052`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-07 code PR #668 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-08.md`.
