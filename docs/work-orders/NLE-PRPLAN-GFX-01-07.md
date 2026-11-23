# NLE-PRPLAN-GFX-01-07 — Logical synchronization (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-07`. **Predecessor:** `GFX-01-06` textures. **Issue:** #29. **Base:** `ee0802f`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement logical barrier validation over current resource handles: generation/slot checks and access/stage bit validation. No native synchronization or GPU.

## CONTEXT

GFX-01-01..06 are approved/completed. Device/resources exist. No native backend.

## SCOPE

- `rhi_sync.hpp`.
- `tests/core/gfx01_sync_tests.cpp`: SYN-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Features/qualification; native GPU/fence/timeline, rendering, shader, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-06 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; SYN-01; handle generation and access/stage bits.

## ARCHITECTURE RULES

GFX-01 owns logical barriers; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; SYN-01 valid/invalid/stale.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

SYN-01 valid barrier, released/stale handle, device loss, zero/invalid access and stage bits.

## DELIVERABLES

Header, SYN tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, SYN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/fence, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ee0802f`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-06 code PR #666 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-07-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-07.md`.
