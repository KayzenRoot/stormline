# ADR-0108 — CORE-05 governance and bounded math/coordinate direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0007 (ratified only as planning direction) and ADR-0086 (capability admission). Does not declare CORE-01 complete, approve implementation, public ABI, dependency, release, G3 or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-CORE-05-01` | **Parent:** CORE-05 | **Issue:** #22.

## Context

CORE-04 closed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-05 (`Math / Coordinates / Types`) has research, architecture and ADR-0007 `PROPOSED`; no executable code exists. Its formal dependency `CORE-01` is not a qualified module, but selected CORE-01 capabilities are completed. The owner instructed continuation on 2026-11-22.

## Decision

- **A:** ADR-0007 is ratified only as planning direction for CORE-05: right-handed 3D world (+Y up, +X right, -Z forward), meters/seconds/radians, column-vector semantics, and explicit named 2D/UI/clip adapters. Matrix memory layout is declared separately from algebraic composition order.
- **B:** documentary artifacts are `LOW`; future runtime/serialization integration is `ELEVATED`; first internal slices are `INTERNAL_ONLY`. No public release or ABI.
- **C:** capability admission for CORE-05 preparation uses completed CORE-01 capabilities; CORE-01 module completion is **not** claimed and its formal dependency remains recorded.
- **D:** begin with original, owned scalar reference types and golden tests. GLM/Eigen/DirectXMath/MathFu remain evaluation candidates only; no third-party math type enters the engine core or public API, and no dependency is selected by this ADR.
- **E:** f32 for local/render payloads; f64 as the first global persistent-origin candidate; signed-cell positions are an alternative requiring later evidence. Origin rebase occurs at a simulation/commit barrier; no gameplay teleport, hidden netcode mutation or bit-exact numerical determinism claim.
- **F:** persistent project/scene/asset IDs are stable opaque values; runtime entity handles are separate generational identities. Volatile addresses/indices are never persisted as identity.
- **G:** invalid math outcomes (non-finite, zero-length, singular, overflow, unit/space mismatch, stale ID, invalid origin epoch) return typed errors; no silent narrowing or non-finite propagation.

## Required before code

1. `CORE-05-02` contract audited with exact logical API, error model, file allowlist and golden tests.
2. Individual `CORE-05-03` G6 activation and explicit owner authorization.
3. Golden tests for basis/transform/inverse/quaternion/units/precision/overflow/ID/origin rebase.
4. Dependency/license/security decision if any third-party math is later proposed.
5. MSVC/GCC/Clang/AppleClang CI; no HIGH/CRITICAL; no release/ABI claim.

## Consequence

- `CORE-05-01` may be prepared as `APPROVED_GOVERNANCE`; `CORE-05-02`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 remains not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04 `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- No implementation packet becomes `EXECUTOR_READY` by this ADR.
