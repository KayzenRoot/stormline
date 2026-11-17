# NLE-PRPLAN-CORE-01-10 — G6 activation (display, DPI and surface validity)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `7e42b48f19272498c732d75f2051704f5b82311f`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-10`. **ADR:** [ADR-0089](../adr/0089-core-01-display-surface-slice.md). **Contract:** [core-01-display-surface-v0](../contracts/core-01-display-surface-v0.md). **WO:** [NLE-PRPLAN-CORE-01-10](../work-orders/NLE-PRPLAN-CORE-01-10.md).

## Owner authorization

The owner explicitly authorized unlocking the next planned packet on 2026-11-17 (`desbloqueia com minha autorização e continue avançando seguindo o planejado no repositorio`). C01-D03 (SDL3 display/capability integration) and C01-D04 (owner/main-thread video calls) are owner-ratified bounded directions. This gate activates **only** `NLE-PRPLAN-CORE-01-10`, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0075 globally, clear G3, authorize renderer/GPU/VRAM, physical hotplug/DPI certification, IME, fullscreen, HDR, public ABI/release, or another packet/module.

## Predecessors

`-03` headless host PR #428; `-04`/`-05` reconciled; `-06` paths PR #432; `-07` SDL3 runtime PR #435; `-08` window lifecycle PR #438; `-09` event queue PR #444. All `COMPLETED`; no predecessor reopened. CORE-02-03 ownership is also `COMPLETED` via PR #441 and unaffected.

## Bounded technical slice

- `DisplayInfo`/`DisplayError`/`DisplayService`: owner-thread enumeration, primary display, bounds/usable bounds/content scale; caller-owned fixed arrays; no strings or SDL pointers.
- Additive `SurfaceMetrics`, `Window::query_surface`, `Window::surface_valid`; generation invalidation on successful resize and observed display/pixel-size change.
- No renderer/swapchain/GPU/VRAM, physical hotplug/display-removal certification, real DPI transition qualification, IME/fullscreen/HDR, public ABI or release.
- Exact code allowlist: `display.hpp`, `display.cpp`, additive `window.hpp`/`window.cpp`, `tests/core/display_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-01-10.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE01_10_READY_PREDECESSORS_COMPLETED`: **735 `PLANNED_BLOCKED`, 8 `COMPLETED` (CORE-01 -03..-09 + CORE-02-03), 4 approved gate entries, 1 `EXECUTOR_READY` (`CORE-01-10`)**.
- `select_packet.py NLE-PRPLAN-CORE-01-10` → exit 0; every other ID, including `-11` and `CORE-02-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0075 `PROPOSED`; ADR-0089 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

DPY-01..DPY-08: display enumeration/primary; buffer/argument errors; runtime/thread errors; surface metrics; resize generation invalidation; surface errors; stability/lifetime and existing 40 CTests regression. Real Linux, Linux ASan/UBSan, Windows and macOS; no SDL in headers; no physical hotplug/DPI/renderer/GPU/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
