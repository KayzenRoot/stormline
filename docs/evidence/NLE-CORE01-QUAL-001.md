# NLE-CORE01-QUAL-001 — Exploratory Runtime Baseline Evidence

**Status:** CODE IN REVIEW / NOT APPROVED / NOT MODULE QUALIFICATION.  
**Owner scope:** limited technical evidence, 2026-11-18. **Risk:** STANDARD, test-only.  
**Base main:** `80f1610f4ac6da8b8daf7f98bbb4ef209963ad6c`.  
**Current PR HEAD:** pending final readback.  
**PR:** to be linked after creation.

## Source Check and Context Lock
Canonical hierarchy and Git blob receipts checked before changes:
- Checkpoint `f74c4df1c5af4ea2b0c7b644f81fa27b8a1e211e`.
- Decisions Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981`.
- Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`.
- DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`.
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`.
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
- Manifest `dc01d3ccc62e857feeb61b3be599f66ae2c08c44` and registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`.
- Existing `core01-internal-headless.yml` and `CMakePresets.json` remain unchanged. These are Git blob identities, not raw SHA256 of source files.

## Implemented, not yet proven
- Exactly 30 independent-child **cold** lifecycle samples and 30 repeated same-process **warm** samples, each for `HeadlessHost` and SDL3 `SdlRuntime+Window`.
- Sample clock: `std::chrono::steady_clock`, nanoseconds; measured start/init to complete teardown; process launch/OS boot *excluded*. These are exploratory host lifecycle samples, not physical cold boot, FPS, graphics or caching certification.
- Process memory: **peak** Linux/macOS `getrusage(ru_maxrss)` or Windows `PeakWorkingSetSize`, converted to bytes. Linux ru_maxrss unit KiB; macOS bytes; Windows working set. NOT steady RSS or direct proof of zero leaks.
- Median p50 / p95 nearest-rank, full raw 30-sample arrays, no p99 acceptance claim; no numeric threshold and no benchmark pass/fail on performance values.
- Closed-set process spawn of own benchmark executable with no shell/network. Fail-closed on malformed/missing samples; test selftest for statistics/parser.
- Linux-only CTest `no-display` clears `DISPLAY/WAYLAND_DISPLAY`, forces X11 (no SDL dummy driver), checks headless success and windowed typed `InitFailed` within 5 seconds; **Windows/macOS absent physical display NOT_QUALIFIED**.
- `cmake -E sha256sum` post-build logs exact benchmark binary hash. Build-time benchmark execution prints metadata/raw results into native job log because normal CTest suppresses successful test output. CTest repeats the benchmark independently.
- Expected CTest count: 95 Linux and Linux ASan/UBSan, 94 Windows and macOS, from 92 existing. Do NOT claim PASS until logs verified.

## Tests, baseline results, corrections
- **Native Linux:** PENDING.
- **Linux ASan/UBSan:** PENDING.
- **Windows MSVC:** PENDING.
- **macOS AppleClang:** PENDING.
- **Docs Validation:** PENDING.
- **Result counts/quantiles/SHA256:** PENDING receipt from exact-head native CI; never invent numbers.
- **Known HIGH/CRITICAL:** none identified during source inspection; not a security certification.

## Scope / risks / stop
Allowed: `tests/core/core01_runtime_baseline_tests.cpp` new, `CMakeLists.txt` additive, this Evidence and corresponding WO. No production sources, CI workflows, ADRs, manifest, registry, G2 or license changes. Process spawn is intentionally constrained to the executing test image; each child inherits only normal test environment and emits numeric samples. The Linux negative test mutates environment **in its isolated test process** only.

`CORE-01-03..16` remain COMPLETED internal; 80/80 module WOs BLOCKED, 0 EXECUTOR_READY, G3 global NOT_CLEARED, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, `engine_implemented=false`. The G1 30+30 obligation is measured as a limited exploratory baseline only; physical platform, vendor ABI, thresholds and global module release still require separate owner decisions.

## Proposed checkpoint delta / audit
**NOT PROMOTED.** Only after an objective pt-BR APPROVED on final PR HEAD and GitHub squash merge may a separate checkpoint PR record exact results, known limitations and main SHA. Final audit, final HEAD native CI and merge: PENDING. On any failure, fix only within this same WO/PR, rerun and maintain Draft / CORRECTION REQUIRED.
