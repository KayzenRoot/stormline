# NLE-PRPLAN-GFX-01-04 — Logical queue roles (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-04`. **Predecessor:** `GFX-01-03` devices. **Issue:** #29. **Base:** `90b247c`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement logical queue role support and submit accounting over the Null device: Graphics/Compute/Transfer, state checks and bounded command counts. No native queue or GPU.

## CONTEXT

GFX-01-01..03 are approved/completed. Logical device core exists. No native backend.

## SCOPE

- `rhi_queue.hpp` and additive device submit state.
- `tests/core/gfx01_queue_tests.cpp`: QUE-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Buffers/textures/sync/features/qualification; native GPU/queue, rendering, shader, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-03 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; QUE-01; role support, state, count bounds.

## ARCHITECTURE RULES

GFX-01 owns logical queues; no native backend; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; QUE-01 roles/submit/state/count.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QUE-01 Graphics/Compute/Transfer support, invalid count, uninitialized/lost/disposed state and submit counter.

## DELIVERABLES

Header, QUE tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QUE-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/render/shader, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `90b247c`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-03 code PR #660 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-04-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-04.md`.
