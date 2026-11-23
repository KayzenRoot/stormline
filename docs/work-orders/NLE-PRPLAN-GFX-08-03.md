# NLE-PRPLAN-GFX-08-03 — Particle graph and spawn budget (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-08-03`. **Predecessor:** `GFX-08-02` contract. **Issue:** #36. **Base:** `754f7b5`. **ADR:** [ADR-0122](../adr/0122-gfx-08-internal-vfx-pipeline.md). **Contract:** [gfx-08-vfx-internal-v0](../contracts/gfx-08-vfx-internal-v0.md).

## OBJECTIVE

Implement bounded logical VFX graph validation and particle emitter/spawn-budget metadata.

## CONTEXT

GFX-08-01/-02 are approved. No particle simulation, GPU, compute, shader or render exists.

## SCOPE

- `vfx_types.hpp`, `graph_plan.hpp`, `emitter_plan.hpp` and VFX-01/SPAWN-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Qualification, closeout; particle simulation, GPU/compute, sorting, OIT, rendering, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0122, internal contract, GFX-08 governance.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0122; VFX-01 and SPAWN-01.

## ARCHITECTURE RULES

GFX-08 owns logical graph/emitter plans; no particle state, PRNG stream, shader, GPU resource or visual output.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/compute/sort/OIT/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; VFX-01/SPAWN-01 valid/invalid fixtures.
- No simulation/GPU/render.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

VFX-01 graph IDs, counts, kinds, ports, duplicate/self edges, cycle and order; SPAWN-01 IDs, lifetime, spawn+burst overflow and caps.

## DELIVERABLES

Headers, VFX-01/SPAWN-01 tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, VFX-01/SPAWN-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, simulation/GPU/compute/sort/SDK selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `754f7b5`; contract blob pinned in activation; GFX-08-02 merge `754f7b5`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-08-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-08-03.md`.
