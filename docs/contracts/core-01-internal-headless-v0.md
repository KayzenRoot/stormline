# CORE-01 INTERNAL_ONLY Headless Lifecycle Contract v0 (NLE-PRPLAN-CORE-01-02)

**Status:** CONTRACT PROPOSAL, NOT IMPLEMENTED / NOT EXTERNAL ABI. **Source base:** `13b316153d817b7a49fd1d82ccd7193faa5a50f0`. **Owner:** CORE-01 Platform & Lifecycle. **Formal predecessor modules:** none. **Work Order:** `NLE-PRPLAN-CORE-01-02`, before any `-03` code.

## Objective / bounded scope
For the first `INTERNAL_ONLY` C++20 CPU-only headless engine slice, define a deterministic, RAII-owned process-host lifecycle. **No SDL3, window, GPU, display, audio, networking, external plugin/SDK, public C ABI, renderer, release or product certification.** CORE-01 broader `MANDATORY_1_0` is only a future target, not the shipped capability of this slice.

## Typed internal API contract (exact names proposed for implementation)
Namespace `stormline::core::internal`, no external symbol/ABI stability guarantee:
- `enum class HostState : std::uint8_t { Stopped, Starting, Running, Stopping, Failed };`
- `enum class HostError : std::uint8_t { None, AlreadyRunning, UnsupportedMode, InvalidState, InitFailed, CleanupFailed };`
- `struct HostConfig final { bool headless{true}; };`. `headless=false` must yield `UnsupportedMode` without side effects.
- Noncopyable/nonmovable `class HeadlessHost final`, internal-only. `HostError start(const HostConfig&) noexcept`, `HostError stop() noexcept`, `HostState state() const noexcept`, `~HeadlessHost() noexcept`. Do not leak native handles or raw third-party types. Do not introduce C++ exceptions across any boundary. Additional private methods/types may be used if justified by tests.
- A private RAII `HostResource` / lifecycle lease is acquired on startup and released exactly once. An internal test seam injects init and cleanup failures without making failure injection a public API. Resource counters are observable only by tests; they are not proof of actual OS handles or full memory safety.
- One owner thread by contract. Concurrent calls and reentrancy are `UNSUPPORTED`; do not assert thread safety. No global singleton, static ambient authority or automatic network/telemetry.

## Transition / error oracles
| Current state | Operation/event | Result | New state |
|---|---|---|---|
| Stopped | `start(headless=true)` success | `None`; exactly one resource owner | Running (via Starting) |
| Stopped | `start(headless=false)` | `UnsupportedMode`, no allocation | Stopped |
| Stopped | `start` injected init failure; rollback succeeds | `InitFailed`, zero owned resources | Stopped |
| Stopped | `start` injected init failure; cleanup fails | `CleanupFailed`, retain failure information | Failed |
| Running | `start` again | `AlreadyRunning`; no second init | Running |
| Running | `stop` successful | `None`; release exactly once | Stopped (via Stopping) |
| Stopped | `stop` again | `None`; idempotent no-op | Stopped |
| Running | `stop` cleanup failure | `CleanupFailed` and explicit recovery needed | Failed |
| Failed | `stop` successful retry cleanup | `None` | Stopped |
| Failed | `start` | `InvalidState`, no new allocation | Failed |

Transient Starting/Stopping states are implementation-internal. Any impossible transition returns `InvalidState` without undefined behavior. Destructor always attempts a no-throw cleanup and logs no secrets; if a fault cannot be repaired without exceptions, it must be surfaced in explicit test result, never silently claimed recovered.

## Acceptance & negative proof (STANDARD risk)
- C01-INT-01: 200/200 headless start/stop cycles per provisional target, no graphics/audio/display APIs or dependencies.
- C01-INT-02: duplicated start returns `AlreadyRunning` without resource leak or reallocation; repeated stop succeeds idempotently.
- C01-INT-03: reject window mode, leave state/ownership unchanged.
- C01-INT-04: controlled failure at each init stage; rollback releases previously acquired resources exactly once; repeat/recover when safe.
- C01-INT-05: cleanup fault forces Failed, retry returns to Stopped; no double free.
- C01-INT-06: destructor cleans up Running/Failed instances with no throw, observable in tests.
- C01-INT-07: clean configure/build/CTest on standard GitHub-hosted Ubuntu 24.04, Windows 2025 VS2026 and macOS 15 with **preinstalled** toolchains; log compiler, OS image, architecture, CMake/Ninja and test receipts. Minimum 1 registered CTest per host, `--no-tests=error`; 200 cycles inside test.
- C01-INT-08: GCC/Clang `-Wall -Wextra -Wpedantic -Werror` when supported; MSVC `/W4 /WX`. Linux ASan/UBSan only when toolchain supports them without new installation; otherwise NOT_QUALIFIED (not silently PASS).
- C01-INT-09: no external SDL3/API, no OS handles, no runtime download/install, no secret, fork unsafe event or paid runner; no redistribution/packaging. Demonstrate isolation in diff and CI.
- C01-INT-10: tests in clean build directory, no unexpected cache/artifact uploads, no HIGH/CRITICAL known regression. Record failures verbatim, repeat only after correction.

## Exact provisional CI environment and version separation
| Target / runner | Observed from PR #421, first internal CI only | Ratified G3-V01 release candidates NOT REPLACED |
|---|---|---|
| Ubuntu 24.04 x64 | GCC 13.3.0, CMake 3.31.6, Ninja preinstalled | GCC 16.2 / Clang 23.1.5 |
| Windows Server 2025 x64, VS2026 | MSVC toolset 14.51 / compiler 19.51.36260, CMake 4.4.5, Ninja | MSVC 14.50 reference / 14.52 comparator; Windows SDK 10.0.26100.9457 |
| macOS 15 Apple Silicon | AppleClang 17.0.0.17000013, CMake 4.4.5, Ninja | Xcode 26.3 and exact candidate AppleClang/support target still require independent proof |

Runners can change image/toolchain; log full versions. On unexpected major drift, mark conditional result NOT_QUALIFIED and reopen decision; never relabel CI smoke as global G3 PASS. Provisional CI must never claim physical hardware, SDL, API/ABI, window/headless hardware or memory leak certification.

## Implementation file allowlist for packet -03 (not authorized merely by this contract)
1. `src/stormline/core/internal/headless_host.hpp`
2. `src/stormline/core/internal/headless_host.cpp`
3. `tests/core/headless_host_tests.cpp`
4. `CMakeLists.txt` (new root project, or minimum compatible existing modification after Git inspect)
5. `CMakePresets.json`
6. `.github/workflows/core01-internal-headless.yml`
7. `docs/work-orders/NLE-PRPLAN-CORE-01-03.md`
8. `docs/evidence/NLE-PRPLAN-CORE-01-03.md`

Reuse no third-party code. Do not move/copy the experimental `experiments/core01-headless` code into production without an independent line-by-line review and exact Work Order approval. No additions outside allowlist absent separately ratified Correction Delta.

## Build/test protocol for future -03
- CMake >=3.27, CMakePresets schema 6 only for this internal profile, Ninja; compiler versions inspected before selecting; no installation. Use a clean `build/core01-internal` and command pattern `cmake --preset core01-internal-debug`; `cmake --build --preset core01-internal-debug`; `ctest --preset core01-internal-debug --output-on-failure --no-tests=error`. Implementation must supply accurate preset entries before tests run.
- One internal `stormline_core01_headless_test` executable and CTest, with deterministic return status. Capture real logs per OS; sanitizer separate when available.
- Production claims only after actual CI/sanitizer evidence at exact HEAD. No 100 window cycles, 10k events, 30+30 latency or physical GPU acceptance in this first slice.

## Stop / rollback / security / licensing
STANDARD scope only; headless internal code with no external user data, privileged operations, persistence, network or distribution. Clean rollback by closing/abandoning unmerged -03 branch; merged future code requires normal revert PR, never force push. Public source license `NLE-D009 OPEN`: no permissive grant, package upload or public release inferred. No dependency beyond C++ standard library; build tools remain runner tooling, not vendored. Exclude new paid tools/downloads, secrets and third-party assets. Stop on stale canonical source, unresolved G4/G5/G6, failing docs/native checks, suspected HIGH/CRITICAL or bypass of selector/ruleset.

**Contract is only a proposal until its exact PR passes audit and is merged; code packet -03 is still BLOCKED.**
