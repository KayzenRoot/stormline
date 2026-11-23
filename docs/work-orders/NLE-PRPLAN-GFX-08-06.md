# NLE-PRPLAN-GFX-08-06 — Transparency/blend policy (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-06`. **Predecessor:** `GFX-08-05` trails. **Issue:** #36. **Base:** `ac1ef55`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical transparency/blend and depth-policy metadata.

## CONTEXT

GFX-08-01/-05 are approved/completed. No sort, OIT, blend, pixel or GPU path exists.

## SCOPE

- `blend_plan.hpp` and BLD-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; sorting, OIT, blending, GPU/compute, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-05 material boundary.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; BLD-01.

## ARCHITECTURE RULES

GFX-08 owns logical blend policy; GFX-05 owns material truth; no sort/OIT/pixel executes.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/sort/OIT/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; BLD-01 valid/invalid fixtures.
- No sort/OIT/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

BLD-01 opaque/mask/blend/additive depth, premultiplied, sort and OIT policy.

## DELIVERABLES

Header, BLD tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, BLD-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, sort/OIT/GPU/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `ac1ef55`; contract blob pinned in activation; GFX-08-05 merge `ac1ef55`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-06-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-06.md`.
