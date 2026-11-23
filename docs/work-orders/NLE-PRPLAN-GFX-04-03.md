# NLE-PRPLAN-GFX-04-03 — Geometry instances and batches (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-GFX-04-03`. **Predecessor:** `GFX-04-02` contract. **Issue:** #32. **Base:** `d80343d`. **ADR:** [ADR-0118](../adr/0118-gfx-04-internal-geometry-pipeline.md). **Contract:** [gfx-04-geometry-internal-v0](../contracts/gfx-04-geometry-internal-v0.md).

## OBJECTIVE

Implement bounded instance validation and deterministic batching by mesh/material.

## CONTEXT

GFX-04-01/-02 are approved. No native GPU, mesh library, submission or renderer exists.

## SCOPE

- `geometry_types.hpp`, `geometry_instance.hpp` and INS-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Culling, LOD/HLOD, stream, vegetation, geometry budget, qualification; native GPU/mesh library, submission, render, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0118, internal contract, governance contract.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-001..005; ADR-0118; INS-01.

## ARCHITECTURE RULES

GFX-04 owns logical instances/batches; no native GPU/mesh library; identities preserved.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no GPU/mesh codec/dependency/native I/O/network; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; INS-01 valid/invalid fixtures.
- No native GPU/mesh library/dependency/native I/O.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

INS-01: add/validate/duplicate/capacity/bounds/generation, batch grouping and deterministic order.

## DELIVERABLES

Headers, INS tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, INS-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, native GPU/mesh library, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d80343d`; contract blob pinned in activation; GFX-04-02 merge `d80343d`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-GFX-04-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-GFX-04-03.md`.
