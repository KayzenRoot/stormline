# NLE-PRPLAN-GFX-01-06 — Logical textures (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-06`. **Predecessor:** `GFX-01-05` buffers. **Issue:** #29. **Base:** `010f584`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement logical texture descriptors/handles: dimensions/levels/format/usage validation, slot generations and release. No native texture or GPU memory.

## CONTEXT

GFX-01-01..05 are approved/completed. Device/queue/buffer core exists. No native backend.

## SCOPE

- `rhi_texture.hpp` and additive texture resource state.
- `tests/core/gfx01_texture_tests.cpp`: TEX-01.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Sync/features/qualification; native texture/GPU memory, rendering, shader, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-05 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; TEX-01; 4096×4096 cap, levels/format/usage, generation.

## ARCHITECTURE RULES

GFX-01 owns logical resources; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/allocator/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; TEX-01 descriptor/handle/release/capacity.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

TEX-01 dimension/level/format/usage boundaries, create/info/release, stale handle and 64-resource capacity.

## DELIVERABLES

Header, TEX tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, TEX-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/render/shader, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `010f584`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-05 code PR #664 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-06.md`.
