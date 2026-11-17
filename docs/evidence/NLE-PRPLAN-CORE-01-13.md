# NLE-PRPLAN-CORE-01-13 — Capability graph prototype and report-only measurement

**Status:** `CODE_IMPLEMENTED / LOCAL_PREFLIGHT_PASS / NATIVE_CI_PENDING / AWAITING_AUDIT`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-13`. **ADR:** [ADR-0092](../adr/0092-core-01-capability-graph-prototype.md). **Contract:** [core-01-capability-graph-v0](../contracts/core-01-capability-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-01-13](../work-orders/NLE-PRPLAN-CORE-01-13.md). **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

Fixed-capacity capability graph prototype with explicit Unknown/Supported/Unsupported states, a thin SDL3 probe, and a **report-only** benchmark against direct `SDL_WasInit`. Not a SAPL adoption, not a performance PASS, no threshold.

## 1. Authorization and Context Lock

- **Gate:** [PR #455](https://github.com/KayzenRoot/stormline/pull/455) squash-merged as `92fba81b9d0966b211db1003284577296d223567`; audit #6961080626 **APPROVED**.
- **Base:** `92fba81b9d0966b211db1003284577296d223567`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-01-13 --json` → `EXECUTOR_READY`, exit 0; `-14`, `CORE-02-04` and every other ID exit 2.
- **Predecessors:** `-03`..`-12` completed; CORE-02-03 ownership completed via PR #441.

## 2. Implemented behavior

- `CapabilityId`: Video, Events, Window, Displays, WaylandRuntime.
- `CapabilityState`: Unknown, Supported, Unsupported; `CapabilitySource`: Unknown, SdlProbe, Explicit.
- `CapabilityGraph`: fixed capacity 8, no allocation; set/overwrite/find/state/count/clear; invalid id rejected; absent capability is Unknown.
- `CapabilityProbe`: owner-thread SDL3 probe; before video init all five are Unknown; after init video/events/window/displays are Supported; WaylandRuntime is Supported on Wayland, Unsupported on X11/Win32/Cocoa, Unknown on dummy/offscreen.
- Benchmark mode runs 1,000,000 graph lookups and 1,000,000 `SDL_WasInit` calls, prints graph ns/op, direct ns/op and ratio, and asserts only correctness. No timing threshold or performance PASS.
- No SAPL production layer, direct OS API, renderer/GPU/audio, public ABI or release.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/capability_graph.hpp` | Capability ids/states/sources/graph/probe API |
| `src/stormline/core/internal/capability_graph.cpp` | Fixed graph and SDL3 probe |
| `tests/core/capability_graph_tests.cpp` | states/uninitialized/dummy/real/wrong-thread/benchmark |
| `CMakeLists.txt` | Additive `stormline_core01_capability_graph` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-01-13 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-01-13.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive capability-graph wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core01_capability_graph_test`: **OK**.
- `ctest -R core01_capability_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **65/65 CTests passed** (59 previous + 6 capability tests).
- Local benchmark output (MSVC, dummy driver, one run, **not a product verdict**):
  `CAPABILITY_BENCHMARK graph_ns_per_op=24.554 direct_ns_per_op=18.107 ratio=1.356 iterations=1000000`
- This single local number is noisy and must not be read as a speedup/regression decision.

### Native CI (authoritative, pending)

Pending exact-head Docs Validation and native Linux/Linux-sanitizers/Windows/macOS runs. This document will be updated with run IDs, CTest counts and the benchmark output captured in CI logs. No native or performance PASS is claimed yet.

Expected matrix: existing 59 CTests plus 6 capability tests = **65 CTests** per native job, with Linux ASan/UBSan.

## 5. Security, licensing and limitations

- No third-party dependency beyond the pinned SDL3 baseline; no package installation, secret, upload, paid runner/service or runtime download.
- The graph is fixed-capacity and allocation-free; it is not thread-safe for concurrent mutation. The probe is owner-thread only.
- The benchmark is report-only: shared CI runners are noisy, no owner-approved hardware/threshold exists, and **no SAPL adoption or performance verdict** is made.
- ADR-0003/0075 remain `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; final status subject to exact-head CI and independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the capability-graph target/tests/benchmark and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the ninth real CORE-01 slice, exact PR/CI/audit/merge SHA, 6 `core01_capability_*` tests and 65 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, plus the CI benchmark stdout. It explicitly records that this is a **prototype/report-only** measurement, not SAPL adoption, a performance budget or a product decision. This evidence does not self-promote the checkpoint.
