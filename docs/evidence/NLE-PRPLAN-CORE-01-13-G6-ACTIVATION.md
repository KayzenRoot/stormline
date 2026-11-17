# NLE-PRPLAN-CORE-01-13 — G6 activation (capability graph prototype)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `967e136d517c6d78430bcde1fd66ef97a283efe5`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-13`. **ADR:** [ADR-0092](../adr/0092-core-01-capability-graph-prototype.md). **Contract:** [core-01-capability-graph-v0](../contracts/core-01-capability-graph-v0.md). **WO:** [NLE-PRPLAN-CORE-01-13](../work-orders/NLE-PRPLAN-CORE-01-13.md).

## Owner authorization

The owner authorized continuing and unlocking what is necessary on 2026-11-17 (`autorizado continue`). C01-D10 (Unknown/Supported/Unsupported, thin adapter first, SAPL only after proof) is an owner-ratified bounded direction. This gate activates **only** `NLE-PRPLAN-CORE-01-13` as a **prototype measurement**, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not adopt SAPL, approve a performance threshold, clear G3, authorize a production capability layer, public ABI/release, or another packet/module.

## Predecessors

`-03` headless PR #428; `-04`/`-05` reconciled; `-06` paths PR #432; `-07` SDL3 runtime PR #435; `-08` window PR #438; `-09` event queue PR #444; `-10` display/surface PR #447; `-11` native bridge PR #450; `-12` lifecycle PR #453. All `COMPLETED`; no predecessor reopened. CORE-02-03 ownership is also `COMPLETED` via PR #441 and unaffected.

## Bounded technical slice

- `CapabilityId`/`CapabilityState`/`CapabilitySource`/`CapabilityRecord`/`CapabilityError`/`CapabilityGraph`/`CapabilityProbe`.
- Fixed-capacity graph (8), no allocation; explicit Unknown/Supported/Unsupported and source metadata.
- SDL3 probe: video/events/window/displays; WaylandRuntime Supported on Wayland, Unsupported on X11/Win32/Cocoa, Unknown on dummy/uninitialized.
- Report-only benchmark of graph lookup vs direct `SDL_WasInit`; no threshold/performance PASS.
- Exact code allowlist: `capability_graph.hpp`, `capability_graph.cpp`, `tests/core/capability_graph_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-01-13.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_13_READY_PREDECESSORS_COMPLETED`: **732 `PLANNED_BLOCKED`, 11 `COMPLETED` (CORE-01 -03..-12 + CORE-02-03), 4 approved gate entries, 1 `EXECUTOR_READY` (`CORE-01-13`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-13` → exit 0; every other ID, including `-14` and `CORE-02-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0092 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false`.

## Proof obligations for the code PR

CAP-01..CAP-06: graph states/overwrite/clear; probe before init; dummy; real driver; wrong-thread; report-only benchmark and existing 59 CTests regression. Real Linux/Windows/macOS; Linux ASan/UBSan; no SDL in header; no SAPL adoption, performance threshold, OS/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code, native PASS or performance PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
