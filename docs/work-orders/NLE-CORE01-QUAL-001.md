# NLE-CORE01-QUAL-001 — CORE-01 Exploratory Runtime Baseline

**Status:** OWNER_AUTHORIZED / STANDARD / INTERNAL_ONLY / NOT MODULE QUALIFICATION.  
**Owner authority:** explicit instruction in this conversation, 2026-11-18.  
**Base main:** `80f1610f4ac6da8b8daf7f98bbb4ef209963ad6c`.  
**Execution:** one bounded code-and-test PR; separate audited checkpoint PR only after merge.

## OBJECTIVE
Generate **actual measurements** of CORE-01 headless and SDL3-windowed lifecycle on the existing free Linux, Linux ASan/UBSan, Windows and macOS CI, without changing production code. Record 30 cold + 30 warm samples per mode and platform, p50/p95 of elapsed lifecycle time, process peak resident memory/working-set, runner OS/architecture/toolchain/SDL version and executable SHA256. No benchmark performance acceptance threshold or physical hardware certification. Actual clock readings of zero nanoseconds are valid **censored** observations when a headless operation is shorter than clock resolution; do not replace them with invented positive durations. Count and display such readings separately; zero means *unresolved*, not instantaneous.

## CONTEXT / SOURCES TO READ
Source hierarchy: checkpoint `f74c4df1c5af4ea2b0c7b644f81fa27b8a1e211e` > Decisions Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981` / approved bounded ADR > Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22` > DoD `e0b7c2466ebec9790a715e47490c015cfb502db4` > Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1` > Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; `docs/architecture/core-01-platform-lifecycle.md`, `docs/contracts/core-01-sdl3-runtime-v0.md`, `docs/contracts/core-01-window-lifecycle-v0.md`, `docs/engineering/core-01-01-qualification-gates.md`, `docs/adr/0095-core-01-internal-sequence-closeout.md`, `CMakePresets.json`, current CI workflow, existing tests and GitHub CI receipts.

**Immutable source-lock assumptions:** CORE-01-03..16 COMPLETED, 80/80 module WOs BLOCKED, 0 EXECUTOR_READY; manifest `dc01d3ccc62e857feeb61b3be599f66ae2c08c44`, registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`, `engine_implemented=false`, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, G3 globally NOT_CLEARED. Git blob IDs are version locks, not raw SHA256 of artifacts.

## SCOPE (NECESSARY)
1. A standalone test-only C++20 executable in `tests/core/core01_runtime_baseline_tests.cpp` with strict argument checks and self-tests for parsing/statistics.
2. A single CTest exploratory baseline: 30 **cold** samples each in a *fresh process* and 30 **warm** samples within *one reused process*, for each of headless start/stop and SDL3 init/window create/show/destroy/quit. Timing starts before the lifecycle operation and excludes process spawn time. Cold is not proof of uncached disk/CPU or physical cold boot.
3. Capture `std::chrono::steady_clock` elapsed ns and process **peak** resident usage (Linux `ru_maxrss` KiB, macOS `ru_maxrss` bytes, Windows `PeakWorkingSetSize` bytes). Normalize all to bytes but never claim apples-to-apples idle RSS or leak-free operation. Report exact raw samples, nearest-rank p50/p95, metadata, constraints.
4. Register a distinct Linux-only CTest for **no DISPLAY/WAYLAND_DISPLAY**: force SDL's `x11` backend, prevent dummy fallback, headless must start/stop, SDL windowed video initialization must return typed `SdlError::InitFailed` within 5s, no silent success. For Windows/macOS, true absence of physical display remains `NOT_QUALIFIED`; normal headless uses no DISPLAY/WAYLAND_DISPLAY but does not certify physical device absence.
5. CMake add-only test target, CTests with bounded timeouts and ENVIRONMENT for actual window driver. Build-time execution emits sample summary and SHA256 via `cmake -E sha256sum` for auditable GitHub logs; CTest independently repeats the sample suite. No new external package.

## OUT OF SCOPE
No production source, network operation, persistent data, new dependencies/toolchains/SDKs, GitHub workflows, PR gating/G2/ruleset, engine license or redistribution, ADR promotion, manifest/registry/queue/packet activation, other modules, external ABI, support floors, vendor benchmarking, threshold ratification, security clearance, physical Windows/Linux/macOS/Wayland hardware certification, robust p99/60 FPS claim.

## FILE ALLOWLIST
- `tests/core/core01_runtime_baseline_tests.cpp` **NEW**, test-only
- `CMakeLists.txt` **MODIFIED**, only additive target, CTest and post-build test receipt
- `docs/work-orders/NLE-CORE01-QUAL-001.md` **NEW**, this WO
- `docs/evidence/NLE-CORE01-QUAL-001.md` **NEW**, immutable receipts and audit

## REQUIREMENTS / ARCHITECTURE RULES
D01/D08/D09/D14, G1-M05/M07, G3-P08/P09/P13 (partial exploratory only), C01-Q008/Q012/Q025, GOV-004/005. C++20, internal-only, no SDL in production ABI, no globals or unexpected writes, SDL main-thread affinity, SdlRuntime outlives Window; unchanged production shutdown and ownership contracts. No host-native process handle escapes to production.

## CONSTRAINTS
Risk: **STANDARD** for isolated test helper invoking its own exact executable; no privileged commands or arbitrary shell, no network, no uploads, no payment, no secrets. Process spawn path must be exact test binary, args closed set, no command shell. Failure must be typed, printed and non-zero. Linux negative test subprocess is its own CTest process. Unsupported physical cases must not be reported as successful qualification. Fail-closed on malformed child output, missing resource readings or incomplete samples.

## ACCEPTANCE CRITERIA
- Exactly 30 cold and 30 warm **valid** measurements for headless and windowed; no fabricated values, no silent child failures; p50/p95 computed and raw samples shown.
- Process-peak-memory measurement, unit semantics, runner/compiler/arch/SDL version and binary SHA in actual CI log; metadata and CTest success are not performance acceptance.
- Linux no-display test uses unavailable X11 with no dummy, validates headless/typed InitFailed/<=5s and 0 video initialized, exit 0 only on real proof.
- Full existing CTest regression (92) plus all new tests, Linux, ASan/UBSan, Windows, macOS, no new regression/warnings/known HIGH or CRITICAL. New CTest must be observed in CI count. Docs Validation at exact PR HEAD.
- Evidence Bundle base/head SHA, file list, CI checks/job logs/results, failures, material limitations, rollback, pt-BR independent-objective audit. No unsupported G3/hardware/release status promotion.

## TESTS
`cmake --preset core01-internal-debug`; `cmake --build --preset core01-internal-debug`; `ctest --preset core01-internal-debug --output-on-failure`; Linux ASan equivalent using `core01-internal-asan`; existing `.github/workflows/core01-internal-headless.yml` four jobs and Docs Validation. Explicit new CTest selftest, baseline, Linux-only no-display negative. Existing 92 CTests must remain green. Full OS names, exact git heads and observed runner versions are from CI, not inferred.

## DELIVERABLES
One minimal PR with executable test, additive CMake integration, this WO, Evidence Bundle. Proposed Checkpoint Delta only; if and only if audit APPROVED and merge verified, independent checkpoint PR with its own Docs Validation/audit/merge and main readback.

## REVIEW FORMAT
In Brazilian Portuguese: SOURCE LOCK, exact diff/allowlist, negative tests, CI 4/4 and ASan/UBSan, provenance SHA, raw samples/quantiles, limitations, warnings/risks, `APPROVED` / `CORRECTION REQUIRED` / `BLOCKED`. Auto-approval forbidden; correction stays in same PR.

## STOP CONDITION
STALE source, changed approved decisions, out-of-allowlist request, source edit required, new deps/workflows, missing isolated process, no real output, flaky tests, failed native CI, ASan/UBSan errors, HIGH/CRITICAL, owner decision on p95/RSS or G3 needed to proceed, or forbidden module/ADR/registry promotion. Leave PR Draft / BLOCKED rather than claim completion.

## CORRECTION DELTA CD-01 — observed Windows steady_clock resolution
Native run [#44383510514](https://github.com/KayzenRoot/stormline/actions/runs/44383510514), Windows job 135081790463: all existing regressions passed; the new CTest `core01_runtime_baseline` failed because a repeated no-op-scale headless lifecycle produced an actual `0 ns` reading and the test erroneously rejected it. Build-time output had 30/30 samples and SHA; Windows window timings were valid. This is instrumentation resolution, not a confirmed runtime defect. Correct **only** the test helper: accept zero elapsed as a *censored clock-resolution sample*, count it, never substitute synthetic positive duration or claim an accurate speed below the clock tick. Keep zero/invalid RSS rejected. Selftest covers zero duration validity and rejects malformed/zero-memory input. Rerun 4/4 CI on final HEAD and update Evidence with real receipts. Risk remains STANDARD; no production/contract changes.
