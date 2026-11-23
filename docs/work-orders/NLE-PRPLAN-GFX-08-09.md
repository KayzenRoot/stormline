# NLE-PRPLAN-GFX-08-09 — Integrated VFX qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — qualification test authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-09`. **Predecessor:** `GFX-08-08` pooling. **Issue:** #36. **Base:** `02adcbf`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Execute integrated logical qualification QLF-G801..G804 across graph, emitter/spawn, ribbon, trail, blend, density and pool plans.

## CONTEXT

GFX-08-01/-08 are approved/completed. No particle simulation, GPU, compute, sort, OIT, volume or render exists.

## SCOPE

- `tests/core/gfx08_vfx_qualification_tests.cpp`.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; particle simulation, GPU/compute, sort/OIT, volume rendering, assets, dependencies, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, all GFX-08 headers/tests.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; QLF-G801..G804.

## ARCHITECTURE RULES

Qualification is logical/CI-only; no particle, GPU or visual behavior is asserted.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/sort/OIT/volume/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-G801..G804 pass.
- No simulation/GPU/render claim.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-G801 integrated pipeline; G802 deterministic repeat; G803 typed failure recovery; G804 10,000 bounded attempts.

## DELIVERABLES

Qualification test, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-G801..G804, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, simulation/GPU/sort/OIT/volume claim, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `02adcbf`; contract blob pinned in activation; GFX-08-08 merge `02adcbf`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-09-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-09.md`.
