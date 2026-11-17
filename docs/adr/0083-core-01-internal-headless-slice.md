# ADR-0083 — CORE-01 internal-only CPU headless host slice

**Status:** OWNER_RATIFIED_BOUNDED / TECHNICAL_APPROVAL_CONDITIONAL_ON_AUDIT_AND_MERGE. **This ADR is subordinate to and DOES NOT approve ADR-0003 as a whole.**
**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-01-02` | **Parent:** `NLE-PRPLAN-CORE-01-01` | **Issue:** #387 / original implementation issue #18.

## Context and authorization
The owner expressly ratified Option A in chat, linked to [proposal #6954081280](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280): internal C++20 CPU-only headless slice without SDL3, future CORE-01 `MANDATORY_1_0` objective with code initially `INTERNAL_ONLY`, risk `STANDARD` for this slice, typed states/errors/RAII/rollback and provisional CI under the toolchains proven by [PR #421](https://github.com/KayzenRoot/stormline/pull/421). No ADR-0003 or ADR-0075 integral approval; G3 global still not cleared; engine license NLE-D009 OPEN.

## Bounded technical decision
For **only** the first internal harness: C++20 standard library, no external dependencies, no platform window/input/graphics/audio integration. Internal `HeadlessHost` contract in [CORE-01 headless v0](../contracts/core-01-internal-headless-v0.md), strict single-thread lifecycle, RAII, rollback, no public ABI/C boundary, typed errors and safe no-throw cleanup. CMake/CTest + Ninja and provisional CI on standard runners. ABI/plugin/license integration deliberately excluded.

## Alternatives considered and rejection boundaries
- **Use SDL3 in first harness:** defer to later CORE-01 window/OS adapter slice, not necessary for a CPU-only state machine; defer library licenses, adapters, main thread and native handles.
- **Wait for MSVC14.50/14.52, GCC16.2/Clang23.1.5 and Windows SDK .9457 before any code:** keep these as global G3 candidates, but for INTERNAL_ONLY C++20 stdlib smoke allow 14.51/GCC13.3/AppleClang17 *provisionally*; do not claim platform release support or ABI equivalence.
- **C++23 / external libraries:** rejected as unnecessary new compatibility/supply-chain risk for first slice.
- **Expose public API now:** deferred until G3/ADR-0003 broader checks and stable ownership contract; internal API may change.
- **Rebrand experimental fixture as product:** rejected: existing PR #421 only proves a tiny isolated state-machine, no real engine host.

## Proof and consequence
Standard-risk implementation requires tests per OS + error/rollback, sanitizer when available, no leaked native/SDL types, no secrets/network/paid runners; toolchain provenance logs and truthful NOT_QUALIFIED for unavailable target versions. Gate G4 can be marked **APPROVED_BOUNDED_INTERNAL_SLICE ONLY** only if this ADR/contract PR passes exact-head docs validation, owner ratification provenance and objective pt-BR review; G5 contract acceptance and G6 separate executable readiness are STILL prerequisites for code.

No general promotion of G3; original [ADR-0003](0003-core-01-platform-technology.md) and QA-01 [ADR-0075](0075-qa-01-ci-matrix-security-policy.md) retain PROPOSED status. All remaining 79 modules, 80 code WOs and 748 planned packet entries remain unchanged at this stage. No redistribution or release.
