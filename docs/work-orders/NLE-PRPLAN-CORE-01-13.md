# NLE-PRPLAN-CORE-01-13 — Capability graph prototype and comparative measurement (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #456](https://github.com/KayzenRoot/stormline/pull/456), merge `f744914c113c0e272cc26259480632272b1d25e3`. This packet must not be re-executed; no next packet or module is authorized.** **Gate:** G6 individual, conditional on that merge and a fresh executor Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-13`. **Predecessor:** `-12` `COMPLETED` via PR #453. **Issue:** #18. **Base:** `967e136d517c6d78430bcde1fd66ef97a283efe5`. **ADR:** [ADR-0092](../adr/0092-core-01-capability-graph-prototype.md). **Contract:** [core-01-capability-graph-v0](../contracts/core-01-capability-graph-v0.md).

## OBJECTIVE

Implement a fixed-capacity capability graph prototype with explicit Unknown/Supported/Unsupported states and a thin SDL3 probe, plus a **report-only** comparative measurement of graph lookup vs direct `SDL_WasInit`. This is not a SAPL production layer and does not produce a performance PASS.

## CONTEXT

`-07`..`-12` delivered SDL runtime, window, event queue, display/surface, native handle and lifecycle state machine. C01-D10 requires Unknown vs Unsupported and a thin adapter before SAPL. This packet is the prototype measurement only; SAPL adoption, performance thresholds and product architecture remain owner decisions.

## SCOPE

- `CapabilityId`, `CapabilityState`, `CapabilitySource`, `CapabilityRecord`, `CapabilityError`, `CapabilityGraph`, `CapabilityProbe`.
- Fixed-capacity graph (8), no allocation; explicit Unknown/Supported/Unsupported; source metadata.
- SDL3 probe: video/events/window/displays; WaylandRuntime Supported on Wayland, Unsupported on X11/Win32/Cocoa, Unknown on dummy/uninitialized.
- Report-only benchmark of graph lookup vs `SDL_WasInit`; no threshold assertion.
- Tests CAP-01..CAP-06, existing 59 CTests regression, Linux ASan/UBSan, Evidence Bundle.

## OUT OF SCOPE

SAPL production adoption, performance verdict/threshold, direct OS APIs, OS permission model, renderer/GPU/audio, public ABI/plugin SDK, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0075/0083..0092; Scope/DoD/Architecture/Requirements; CORE-01 architecture and C01-D10; SDL3 runtime/event/display/native contracts; this gate's ADR/contract/activation; completed CORE-01 code/tests/CMake/CI evidence. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D10 bounded; CORE-01 catalog acceptance. No new owner technology decision beyond the prototype measurement; no SAPL adoption or performance threshold.

## ARCHITECTURE RULES

Internal namespace/header only; standard headers in the graph; SDL confined to the probe `.cpp`; fixed capacity/no allocation; explicit source/state; owner-thread probe; typed errors; no exception across the boundary; no global state/singleton; report-only benchmark. Existing targets preserved.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. SDL3 3.4.20 static build-time fetch; no package installation, paid runner, secret, upload, runtime download or release. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; Linux ASan/UBSan. ADR-0003/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-01-13`.
- Graph states/sources/round-trip/capacity implemented; Unknown ≠ Unsupported; probe before/after init; real-driver Wayland Unsupported; wrong-thread typed.
- Report-only benchmark prints ns/op and ratio; no timing threshold/performance PASS.
- CAP-01..CAP-06 on Linux, Linux ASan/UBSan, Windows and macOS; existing 59 CTests regression; no SAPL/OS/ABI/release overclaim.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `CAP-01` states, `CAP-02` before init, `CAP-03` dummy, `CAP-04` real driver, `CAP-05` wrong-thread, `CAP-06` benchmark/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/internal/capability_graph.hpp`, `capability_graph.cpp`, `tests/core/capability_graph_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive CORE-01-13 path filters), `docs/evidence/NLE-PRPLAN-CORE-01-13.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, CAP matrix, state/source/probe/benchmark evidence, existing regression, sanitizer, no SAPL/performance/OS/ABI/release overclaim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, SAPL adoption/performance threshold/OS/ABI/release overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `967e136d517c6d78430bcde1fd66ef97a283efe5`; activation pins the exact ADR/contract/source blobs. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-13.md` with PR/CI/audit/merge SHAs, exact files, state/probe/benchmark results, CAP-01..06, regression, sanitizer, limitations and rollback. Gate evidence never masquerades as implemented code or a performance PASS.
