# ADR-0006 — CORE-04 Monotonic Clock and Rational Fixed-Step Timeline

**Status:** PROPOSED; NOT APPROVED FOR IMPLEMENTATION  
**Date:** 2026-11-14 | **WO:** NLE-P00-WO-002-CORE-04 | **Issue:** #99

## Context
Stormline needs a predictable frame-independent simulation clock for realistic 3D and native 2D, without tying headless server/gameplay to graphics FPS. CORE-01 owns OS time and CORE-03 owns work execution; neither has executable code yet. Fixed timestep, exact long-duration scheduling and explicit overload diagnostics are necessary to make later physics/netcode validation meaningful.

## Proposed choice
1. Use an injectable, monotonic ClockSource adapter based primarily on C++20 std::chrono::steady_clock; do not read calendar/wall time for gameplay ticks.
2. Represent logical time by monotonically increasing uint64 TickId and a rational fixed step; use checked integer math with carried remainder, never accumulate approximate 1/60 seconds as a fixed rounded nanosecond integer.
3. Keep rendering interpolation and audio presentation separate from simulation; pause/one-step operations return typed outcomes. Clock sampling failures and debt/clamp policies must be observable, not silently ignored.
4. Default test case is 60Hz, not a frozen game-specific value. Fixed period, scale and debt policy must be explicit, validated and versioned.
5. Reject unconditional variable-dt physics and float-only accumulated simulation as baseline. No third-party timing SDK introduced; evaluate SDL3/natives only at CORE-01 adapter boundary.
6. Define exact deterministic **tick scheduling envelope** while deferring numerical physics/network determinism, rollback, snapshots and stable replay state hash to downstream modules.
7. Permit no arbitrary remote AI/MCP clock mutation. Expose approved pause/step via future authorization kernel only.

## Alternatives and why not selected
- Direct SDL3 time globally: unnecessary headless/library coupling before CORE-01 is implemented.
- Raw QPC/native per-platform through engine surface: not portable; platform adapter handles it.
- Variable timestep: violates frame-independent update envelope.
- Always catch up on accumulated wall time: may spiral under overload; offline/server policies must be separately explicit.
- Stop counting time without an event: violates replay/observability and hides overload.
- Bit-exact cross-platform physics claim: cannot be inferred from a clock architecture alone.

## Proof obligations before promoting
Versioned contract and exact file ownership; integer overflow/rational remainder proof; fake-clock tests with 30/60/144 FPS partitions and long-run tick count; pause/one-step/suspend/backwards-time and server overload tests; MSVC/GCC/Clang/AppleClang CI and real hardware; CORE-03 phase ordering integration; license/security review; performance cost and deterministic replay envelope observed on target implementations.

## Consequences
Future CORE-04 code is small and test-first, but requires careful arithmetic and typed error handling. The public API stays independent of SDL/graphics/physics. This ADR can be integrated as a **research proposal** only; no module issue becomes executor-ready. A final technology/ABI decision needs approved evidence and context-lock before coding.
