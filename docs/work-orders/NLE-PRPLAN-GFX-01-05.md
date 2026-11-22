# NLE-PRPLAN-GFX-01-05 — Logical buffers and handles (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-05`. **Predecessor:** `GFX-01-04` queues. **Issue:** #29. **Base:** `1ef4c35`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement logical buffer descriptors/handles: size/usage/alignment validation, slot generations, release and stale-handle rejection. No native buffer or GPU memory.

## CONTEXT

GFX-01-01..04 are approved/completed. Device/queue core exists. No native backend.

## SCOPE

- `rhi_buffer.hpp` and additive resource-slot state.
- `tests/core/gfx01_buffer_tests.cpp`: BUF-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Textures/sync/features/qualification; native buffer/GPU memory, rendering, shader, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-04 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; BUF-01; 4096-byte cap, alignment/usage, generation.

## ARCHITECTURE RULES

GFX-01 owns logical resources; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; BUF-01 descriptor/handle/release/capacity.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BUF-01 size/usage/alignment boundaries, create/info/release, stale handle, device loss and 64-resource capacity.

## DELIVERABLES

Header, BUF tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BUF-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/render/shader, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `1ef4c35`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-04 code PR #662 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-05-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-05.md`.
