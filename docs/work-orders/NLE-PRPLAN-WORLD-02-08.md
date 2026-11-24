# NLE-PRPLAN-WORLD-02-08 — Integrated scene/prefab qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-02-08`. **Predecessor:** `WORLD-02-07` transforms. **Issue:** #42. **Base:** `8819d57`. **ADR:** [ADR-0128](../adr/0128-world-02-internal-scene-prefab-metadata.md). **Contract:** [world-02-scene-internal-v0](../contracts/world-02-scene-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal WORLD-02 planners with deterministic repeat, failure recovery and bounded overload fixtures.

## CONTEXT

WORLD-02-01..-07 are approved. No scene runtime, prefab expansion, merge or serializer exists.

## SCOPE

- `world02_qualification_tests.cpp` with QLF-S201..S204.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; scene runtime/expansion, serializer/journal, transform math, spatial, physics, networking, editor, GPU, hardware, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0128, internal contract, hierarchy/composition/variant/instance/transform headers.

## REQUIREMENTS

GOV-001..007; ADR-0128; QLF-S201..S204.

## ARCHITECTURE RULES

Qualification exercises planner contracts only; no runtime scene or prefab behavior is claimed.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/expansion/serializer/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-S201..S204 pass.
- 10,000 bounded attempts stay within caps.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-S201 integrated planners; QLF-S202 deterministic repeat; QLF-S203 failure recovery; QLF-S204 bounded overload.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-S201..S204, sanitizers/CI, errors/corrections, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/expansion/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `8819d57`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-02-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-02-08.md`.
