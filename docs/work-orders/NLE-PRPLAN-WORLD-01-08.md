# NLE-PRPLAN-WORLD-01-08 — Integrated entity metadata qualification (INTERNAL_ONLY)

**STATUS: G6 IMPLEMENTATION PACKET — code authorized only after this gate merges.** **Formal packet:** `NLE-PRPLAN-WORLD-01-08`. **Predecessor:** `WORLD-01-07` reflection. **Issue:** #41. **Base:** `d124444`. **ADR:** [ADR-0127](../adr/0127-world-01-internal-entity-metadata.md). **Contract:** [world-01-entity-internal-v0](../contracts/world-01-entity-internal-v0.md).

## OBJECTIVE

Qualify the integrated internal WORLD-01 planners with deterministic repeat, failure recovery and bounded overload fixtures.

## CONTEXT

WORLD-01-01..-07 are approved. No ECS runtime, storage, threading or serializer exists.

## SCOPE

- `world01_qualification_tests.cpp` with QLF-W101..W104.
- Additive CMake targets/tests and workflow TSan target.
- Evidence file.

## OUT OF SCOPE

Closeout; ECS storage, runtime identity, allocator, serializer, hierarchy, spatial, physics, networking, editor, GPU, hardware, performance, ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0127, internal contract, identity/component/lifecycle/query/reflection headers.

## REQUIREMENTS

GOV-001..007; ADR-0127; QLF-W101..W104.

## ARCHITECTURE RULES

Qualification exercises planner contracts only; no runtime ECS or storage behavior is claimed.

## CONSTRAINTS

Risk `ELEVATED`; `INTERNAL_ONLY`; no runtime/storage/threading/serialization/network/hardware; CORE-01/02 not qualified; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## ACCEPTANCE CRITERIA

- Exact allowlist; QLF-W101..W104 pass.
- 10,000 bounded attempts stay within caps.
- Linux, ASan/UBSan, TSan, Windows and macOS CTest pass; pt-BR audit `APPROVED`.

## TESTS

QLF-W101 integrated planners; QLF-W102 deterministic repeat; QLF-W103 failure recovery; QLF-W104 bounded overload.

## DELIVERABLES

Qualification tests, additive CMake/workflow, evidence, CI and pt-BR audit.

## REVIEW FORMAT

pt-BR: base/head, files, QLF-W101..W104, sanitizers/CI, errors/corrections, no overclaim.

## STOP CONDITION

Stale base, gate not merged, API drift, runtime/storage/serializer selection, allowlist violation, failed test, HIGH/CRITICAL, release/ABI claim.

## CONTEXT LOCK

Base `d124444`; internal contract blob pinned in activation.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-WORLD-01-08-G6-ACTIVATION.md`; implementation evidence `docs/evidence/NLE-PRPLAN-WORLD-01-08.md`.
