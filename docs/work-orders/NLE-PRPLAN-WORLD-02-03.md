# NLE-PRPLAN-WORLD-02-03 — Scene hierarchy metadata (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-03`. **Predecessor:** `WORLD-02-02` contract. **Issue:** #42. **Base:** `848e89a`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Implement bounded logical scene hierarchy metadata with stable node IDs, single parents, roots, cycle/depth rejection and ordered siblings.

## CONTEXT

WORLD-02-01/-02 are approved. No scene runtime, node storage, prefab expansion or serializer exists.

## SCOPE

- `scene_types.hpp`, `hierarchy_plan.hpp` and HIR-01 tests.
- Additive CMake target/test and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Composition, variants, instancing, transforms, qualification, closeout; scene runtime, storage, serializer, journal, spatial, physics, networking, editor, GPU.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, governance contract.

## REQUIREMENTS

GOV-001..007; ADR-0128; HIR-01.

## ARCHITECTURE RULES

WORLD-02 owns logical hierarchy intent; WORLD-01 owns entity/component identity and CORE-05 owns transform math.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/storage/serializer/thread/network/dependency; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; HIR-01 valid/invalid fixtures.
- No runtime node storage, transform math, prefab expansion or serializer.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

HIR-01 unique nodes, parents/roots, sibling order, self/cycle, depth, capacity, reset and determinism.

## DELIVERABLES

Headers, HIR tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, HIR-01, sanitizers/CI, errors/corrections, security/rollback, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/storage/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `848e89a`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-03-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-03.md`.
