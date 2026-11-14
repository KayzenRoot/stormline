# ADR-0007 — CORE-05 Math, Units and World Coordinate Policy

**State:** PROPOSED; NOT APPROVED FOR IMPLEMENTATION  
**Date:** 2026-11-14 | **Work Order:** NLE-P00-WO-002-CORE-05 | **Issue:** #102

## Context
Original Stormline must share predictable transforms across 2D, 2.5D, physically realistic 3D, large worlds, save/load, physics/networking, editor and AI, without vendor types leaking into its public ABI. CORE-01/04 timing/lifecycle designs are documented but no engine runtime exists.

## Proposed policy
- Explicit right-handed 3D world (+Y up, +X right, -Z forward), meters/seconds/radians, column-vector transformation semantics and named 2D/UI backend adapters.
- Public API contracts use strongly typed coordinate spaces and unit-bearing values where risk warrants it; all implicit narrowing, nonfinite and invalid math outcomes must be rejected or explicitly handled.
- Distinguish mathematical composition convention from matrix memory layout, clip-space, winding/front face and backend projection.
- Begin with a portable scalar reference path and optional GLM evaluation; library types must stay private to adapters. Exact version, ABI, license and SIMD performance are implementation gates.
- Separate persistent globally stable IDs from volatile generational runtime handles; serializable stable references do not expose memory indices or pointers as identity.
- Compare double-precision global origin with cell-based positions for large worlds; relative single-precision rendering/physics extraction under explicit origin epoch. Origin rebase occurs at a simulation barrier, without gameplay teleport or hidden netcode mutation.
- Persist coordinate metadata/version and validate cross-platform import/export; deterministic schedule alone does not prove numerical physics determinism.

## Alternatives
- GLM as unwrapped SDK: faster initial coding but leaks library ABI/math assumptions.
- Eigen as all-engine default: broad functions but licensing/compile-time complexity may be unnecessary in core runtime.
- DirectXMath globally: Windows-specific design conflicts with native Linux/macOS.
- Always f32 absolute world: less bandwidth, insufficient large-world coordinate robustness.
- Bespoke SIMD and novel algorithms first: complexity unsupported without workload results.

## Proof obligations
Golden basis/transforms/inverse/quaternions; explicit conversions and mixed unit/space compile-time errors; exact null/NaN/singular typed outcomes; f64 vs f32 large coordinate error; origin-rebase snapshots and network replication; stable-ID serialization; endian/ABI and scalar/SIMD differential; Windows/Linux/macOS build/test and web contract; license/supply-chain checks.

## Outcome
Approve only as planning documentation after objective audit. Before Zcode implementation issue #22 can become ready, freeze API/schema, actual source files, exact third-party tag and legal notices, numeric tolerances and target hardware; then retest Context Lock. No program, benchmark or visual quality claim arises from this ADR.
