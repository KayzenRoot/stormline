# NLE-G3-V04-EXP-001 — experimental Evidence Bundle

**Status:** NATIVE CI OBSERVED / EXPERIMENTAL SMOKE ONLY / DRAFT PR NOT MERGED.
**Base SHA:** `dfd3451cdf4cc3793c484656e5a4405e39a985eb` | **Initial tested PR HEAD:** `7fb97e9b5cb9b01676108e8abc99fa42c5e1f49a` | **Parent WO:** NLE-PRPLAN-CORE-01-01 | **Issue:** #387 | **PR:** [#421](https://github.com/KayzenRoot/stormline/pull/421).
**Changed file allowlist:** `experiments/core01-headless/headless_host.hpp`, `headless_host_smoke.cpp`, `CMakeLists.txt`, `.github/workflows/g3-v04-headless-smoke.yml`, this evidence and `docs/work-orders/NLE-G3-V04-EXP-001.md`.

## Observed local preliminary (not a certified target runner)
- Standard-library-only original C++20 CPU-only two-state candidate, no product engine interfaces, no graphics/audio/device code.
- CMake 3.31.6 + Ninja, **GCC 14.2.0**: configure/build PASS, CTest **1/1 PASS**.
- CMake 3.31.6 + Ninja, **Clang 17.0.0**: configure/build PASS, CTest **1/1 PASS**.
- Each test executes 200 start/stop cycles, duplicate start/stop errors, state transitions and count assertion.
- Local source SHA-256: `headless_host.hpp 44253b1a66755bff74a025bda2b279dfdf02bfc0f6ad9f41718e35bd8adecbc8`; `headless_host_smoke.cpp b0777443a2cf31e9e2071261490052dba0da90b6975bed32cd7796c80b32504c`; `CMakeLists.txt 3d2bab99ad01bb98e4bcba66e55f3a07c6686e5e50294fa0994373e0cab16859`.

## Observed GitHub CI at initial PR HEAD 7fb97e9 (2026-11-17)
- [Docs Validation run #44123760187](https://github.com/KayzenRoot/stormline/actions/runs/44123760187): `docs-validation` **SUCCESS**, job #134181801369, all 10 substantive project validators PASS (Source Pack/links, taxonomy, registry, blocked selector, skills, PR plans and suites).
- [Native G3-V04 run #44123760383](https://github.com/KayzenRoot/stormline/actions/runs/44123760383): 3 actual jobs **completed/success**. Logs explicitly show CMake compile + link and 1/1 CTest PASS in each job:
  1. [Ubuntu job #134181802741](https://github.com/KayzenRoot/stormline/actions/runs/44123760383/job/134181802741): image `20261111.127.1`, GCC `13.3.0`, CMake `3.31.6`, Ninja preinstalled, **1/1 CTest PASS**.
  2. [Windows job #134181802430](https://github.com/KayzenRoot/stormline/actions/runs/44123760383/job/134181802430): image `20261103.298.1`, MSVC directory `14.51.36231`, `cl.exe 19.51.36260.0`, linker `14.51.36260.0`, CMake `4.4.5`, Ninja preinstalled, **1/1 CTest PASS**.
  3. [macOS job #134181802087](https://github.com/KayzenRoot/stormline/actions/runs/44123760383/job/134181802087): image `20261104.0514.1`, AppleClang `17.0.0.17000013`, CMake `4.4.5`, Ninja preinstalled, **1/1 CTest PASS**.
- This is three-platform **EXPERIMENTAL_SMOKE_PASS**, not the exact G3-V01 target stack. Linux GCC 13.3 is not GCC 16.2; Windows MSVC 14.51 is neither 14.50 nor 14.52; Clang 23.1.5 and SDK servicing 10.0.26100.9457 were not independently qualified. macOS host/SDK and compiler differ from historical V02 image, so do not claim bit-identical cross-run reproducibility.
- GitHub tests actually build a standalone state-machine fixture, **not** product CORE-01 or a fully integrated headless lifecycle; the state machine never calls actual OS APIs.

## Supply chain, rights, safety and limits
- No third-party code dependency or vendor assets, no SDL3 linked, no product license selected, no binary distribution.
- PR-only, same-repo exact-branch guard; `contents: read`, pinned `actions/checkout@11bd71901bbe5b1630ceea73d27597364c9af683`, `persist-credentials: false`; no installer/toolchain download, cache/artifact upload, secret or privileged event, 8-min bounded standard hosted jobs.
- Account-level billing NOT independently read back. R$0 incremental is the requirement, not a proven account charge record.
- Risk classification ELEVATED **proposed only for this experiment**; does not alter release/risk of any coding WO.

## Audit / restrictions / checkpoint delta
- The code tree initial changes are exactly six ADDED files and zero existing file modifications. This evidence-only refresh creates a later PR HEAD that must get its own docs-validation readback; the native results above are for initial test HEAD only (the C++/workflow files do not change in the evidence refresh).
- Full G3 proof obligations, native exact-candidate compiler/SDK compliance, SDL3, product ABI/HostHandle, true OS headless/windowed and advanced 200/100/10k DoD scenarios remain NOT_CLEARED/FUTURE.
- Original G3-V02 results remain unchanged: macOS fixture 1/1 PASS, four target configurations NOT_QUALIFIED. No G3-P full PASS promoted.
- **G2 bounded active**, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, 80/80 implementation WOs BLOCKED, 748 planned packets PLANNED_BLOCKED, executor-ready 0, engine_implemented=false.
- **PROPOSED CHECKPOINT DELTA (NOT APPLIED):** record only isolated experimental prototype/CI results, refs and their limits after explicit approval, not any G3 or engine implementation claim. This draft PR stays unmerged until scope, CI, cost and risk authorization are objectively audited. If independent gate proof or explicit scoped owner approval is insufficient, verdict BLOCKED.
