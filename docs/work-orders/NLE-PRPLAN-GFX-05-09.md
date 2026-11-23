# NLE-PRPLAN-GFX-05-09 — Integrated material/texture qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-05-09`. **Predecessor:** `GFX-05-08` transparency. **Issue:** #33. **Base:** `953dc83`. **ADR:** [ADR-0119](../adr/0119-gfx-05-internal-material-texture-pipeline.md). **Contract:** [gfx-05-material-internal-v0](../contracts/gfx-05-material-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-G501..G504 across PBR, textures/pages, mips, samplers, decals and transparency.

## CONTEXT

GFX-05-01/-08 are approved/completed. No native GPU, codec, upload, renderer or hardware path exists.

## SCOPE

- `tests/core/gfx05_material_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout, native GPU/codec, upload, rendering, driver/hardware, visual golden, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0119, internal contract, all GFX-05 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0119; QLF-G501..G504.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no native GPU/codec/upload/render/hardware behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G501..G504 pass.
- No native GPU/codec/upload/render/hardware claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G501 integrated pipeline; G502 deterministic repeat; G503 typed failure recovery; G504 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G501..G504, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/codec/hardware claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `953dc83`; contract blob pinned in activation; GFX-05-08 merge `953dc83`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-05-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-05-09.md`.
