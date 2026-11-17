# NLE-PRPLAN-CORE-02-03 — G6 activation (ownership slice)

**Status:** `G6 PROPOSAL / CAPABILITY-ADMITTED / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `bb7229496a5c015ae4d2e31be444381cefc49c1f`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-02-03`. **ADR:** [ADR-0087](../adr/0087-core-02-ownership-slice.md). **Capability admission:** [ADR-0086](../adr/0086-capability-based-l1-dependency.md). **Contract:** [core-02-ownership-v0](../contracts/core-02-ownership-v0.md). **WO:** [NLE-PRPLAN-CORE-02-03](../work-orders/NLE-PRPLAN-CORE-02-03.md).

## Owner authorization

The owner approved capability-based L1 dependencies and the 3-4 PRs per response cadence on 2026-11-17 (`STORM-CORE-01-IMPL-001/issue-387/2026-11-17/next-increments`). This gate activates **only** `NLE-PRPLAN-CORE-02-03`: the internal ownership primitive, after exact-head Docs Validation, objective pt-BR audit and squash/readback.

It does not approve ADR-0003/0004/0075 globally, clear G3, select mimalloc/rpmalloc/Tracy/SMF, authorize arenas/budgets/leaks/telemetry, change any module release class, or unlock another packet/module.

## Predecessors and capability admission

CORE-02-01 and CORE-02-02 are the governance/contract entries in this same gate PR. CORE-02-03 keeps its formal `CORE-01` dependency; it is admitted only through the exact capability set below. This does not claim CORE-01 is complete.

| Capability | Completed packet | Evidence |
|---|---|---|
| `CORE01_HEADLESS_BUILD_AND_TEST` | `NLE-PRPLAN-CORE-01-03` | PR #428, Linux/Windows/macOS headless CTest |
| `CORE01_PORTABLE_PATHS` | `NLE-PRPLAN-CORE-01-06` | PR #432, portable paths tests and regression |
| `CORE01_SDL3_BUILD_BASELINE` | `NLE-PRPLAN-CORE-01-07` | PR #435, pinned SDL3 3.4.20 build baseline |
| `CORE01_NATIVE_CI_MATRIX` | `NLE-PRPLAN-CORE-01-08` | PR #438, 23/23 CTest on Linux/Xvfb, ASan/UBSan, Windows, macOS |

**Not required and not used:** window lifecycle runtime, input/event pump, DPI, IME, hotplug, sleep/resume, soak/qualification, renderer/GPU/audio, network, public ABI, release. The ownership code links no SDL target and calls no SDL function.

## Bounded technical slice

- `MemoryDomain`, `MemoryError`, `MemoryBlock` in `stormline::core::memory`.
- Explicit `std::pmr::memory_resource*`; `nullptr` → `std::pmr::new_delete_resource()`; no global override.
- Move-only, exactly one release, idempotent release, no-throw destructor, typed errors, no exception across the API.
- Exact bytes/alignment stored and returned to `deallocate`; invalid size/alignment and already-owned output rejected before allocation.
- No third-party dependency, benchmark, arena, budget, leak tracker, telemetry or public ABI.
- Exact code allowlist: `memory_block.hpp`, `memory_block.cpp`, `tests/core/memory_block_tests.cpp`, additive `CMakeLists.txt`, additive workflow path filters, `docs/evidence/NLE-PRPLAN-CORE-02-03.md`.

## Gate state after merge (expected, not yet promoted)

- Manifest root `CORE02_03_READY_L1_CAPABILITY_OVERLAY`: **737 `PLANNED_BLOCKED`, 6 `COMPLETED` (CORE-01 `-03`..`-08`), 4 approved gate entries (CORE-01 `-01`/`-02`, CORE-02 `-01`/`-02`), 1 `EXECUTOR_READY` (`CORE-02-03`)**.
- `select_packet.py NLE-PRPLAN-CORE-02-03` → exit 0; every other ID, including CORE-01 `-09` and CORE-02 `-04`, exit 2.
- 80/80 module WOs remain `BLOCKED`; registry unchanged; ADR-0003/0004/0075 `PROPOSED`; ADR-0086/0087 bounded; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; `engine_implemented=false` at module/product level.

## Proof obligations for the code PR

`OWN-01`..`OWN-08`: basic allocate/write/read/release; invalid size/alignment; already-owned output; move construction/assignment; repeated release/destructor; custom resource exact arguments and OOM; cross-thread ownership transfer; 1000-cycle lifetime and existing 23 CTests regression. Real Linux, Linux ASan/UBSan, Windows and macOS; no leak; no global allocator override; no SDL/third-party/ABI/release claim; exact-head Docs Validation and pt-BR audit.

No code or native PASS is claimed by this gate.

## Security and rollback

No dependency, package installation, secret, upload, paid service or runtime download. Unmerged: close the gate branch; `main` untouched. After merge: normal revert PR, never force push. SDL3 zlib notice remains preserved for future distribution; `NLE-D009 OPEN`; no release.
