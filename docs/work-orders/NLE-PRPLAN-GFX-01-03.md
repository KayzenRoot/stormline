# NLE-PRPLAN-GFX-01-03 — Logical adapters/devices (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-01-03`. **Predecessor:** `GFX-01-02` contract. **Issue:** #29. **Base:** `255e8e2`. **ADR:** [ADR-0115](../adr/0115-gfx-01-governance-slice.md). **Contract:** [gfx-01-rhi-v0](../contracts/gfx-01-rhi-v0.md).

## OBJECTIVE

Implement the logical RHI core: Null adapter discovery, device init/close, generation, loss/recover and capability snapshot. No native GPU or rendering.

## CONTEXT

GFX-01-01..02 are approved. No graphics API selected. CORE-01/CORE-02 are not qualified.

## SCOPE

- `rhi_types.hpp`, `rhi_device.hpp` core.
- `tests/core/gfx01_device_tests.cpp`: DEV-01.
- Additive CMake target/test and workflow filters.
- Evidence file.

## OUT OF SCOPE

Queues/buffers/textures/sync/features/qualification; native GPU, shader, swapchain, rendering, dependency, ABI/release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0014/0086/0115, `gfx-01-rhi-v0`, GFX-01-02 evidence, manifest/registry.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0115; DEV-01; Null adapter, generation fence, typed errors.

## ARCHITECTURE RULES

GFX-01 owns logical RHI; no native GPU; CORE boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no GPU/driver/dependency/native I/O/network; CORE-01/02 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- Exact allowlist; DEV-01 adapter/init/loss/recover/close.
- No GPU/native I/O/dependency.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

DEV-01 adapter list, init feature/tier validation, generation, loss/recover, stale generation and close.

## DELIVERABLES

Headers, DEV tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, DEV-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/render/shader, unbounded input, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `255e8e2`; contract blob `8873be5a526ba11045663f33a00673ff41eac993`; GFX-01-02 contract PR #658 merged.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-01-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-01-03.md`.
