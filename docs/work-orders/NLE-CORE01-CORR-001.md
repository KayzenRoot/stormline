# NLE-CORE01-CORR-001 — CORE-01 lifecycle and handle safety correction

**Status:** IN_PROGRESS / DRAFT_PR / NOT_MERGED / NOT_MODULE_APPROVAL  
**Risk:** ELEVATED (potential dangling SDL window pointer / ownership)  
**Owner authorization:** explicit user instruction in Stormline conversation, 2026-11-18, limited to this corrective Work Order.  
**Base/Context Lock:** `84c8e2f838c2d2ee80f2079c4f60da096ee8f1b3`. Refresh before every write/merge.  
**Issue:** #18; CORE-01 internal sequence `-03..-16` already COMPLETED. No new packet activated.

## OBJECTIVE
Reproduce and correct only demonstrable bugs in native-window handle validation, stale generations after recreate, SDL runtime ownership, out-of-order SDL shutdown, main-thread enforcement, and Cocoa "NOT_QUALIFIED" falsely represented as successful tests.

## CONTEXT / SOURCES
Canonical order: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and relevant ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`, then CORE-01 contracts, actual source, tests, CI and evidence. All are Git-read at base HEAD.

## SCOPE
Add reproducible regression assertions **before** applying production changes; capture expected baseline failure on CI. Only then repair confirmed cases and rerun full CI. Preserve C++20 internal API boundaries, no SDL types in engine headers and owner-thread model. Keep corrections in this one branch/PR.

## OUT OF SCOPE
New features/modules; renderer, GPU, audio, networking, public ABI; SDL version bump; license choice; altered global G3/G2; registry, manifest or activation; release; hardware certification.

## FILES / SOURCES TO READ
`src/stormline/core/internal/{window.hpp,window.cpp,sdl_runtime.hpp,sdl_runtime.cpp}` and `tests/core/{native_bridge_tests.cpp,window_tests.cpp,display_tests.cpp,sdl_runtime_tests.cpp}`; `CMakeLists.txt`, current workflow and contracts.

## EXACT ALLOWLIST
- `src/stormline/core/internal/window.hpp`
- `src/stormline/core/internal/window.cpp`
- `src/stormline/core/internal/sdl_runtime.hpp`
- `src/stormline/core/internal/sdl_runtime.cpp`
- `tests/core/native_bridge_tests.cpp`
- `tests/core/window_tests.cpp`
- `tests/core/display_tests.cpp`
- `tests/core/sdl_runtime_tests.cpp`
- `docs/work-orders/NLE-CORE01-CORR-001.md`
- `docs/evidence/NLE-CORE01-CORR-001.md`
No workflow/CMake edits without scoped authorization/correction delta. All other paths read-only.

## REQUIREMENTS / ARCHITECTURE RULES
- A handle from another window, or with fabricated value/kind/generation, must not validate.
- A handle/surface token from a destroyed/recreated window must never revive (ABA).
- No SDL_Quit with outstanding window resources; report explicit recoverable error.
- At most one active owned SDL runtime; reject duplicate ownership without perturbing the active one.
- SDL video main-thread enforcement, not just constructor-thread affinity.
- A CI test without its required Cocoa window server must not silently PASS.
- No exceptions across public methods, no new external dependencies and no UAF/leak regressions.

## CONSTRAINTS
Risk ELEVATED: test cases must avoid dereferencing or destroying an already-freed pointer in baseline red reproduction; isolated test process fail-closed if unsafe shutdown succeeds. Correct only after red evidence. Main protected; no force-push or bypass.

## ACCEPTANCE CRITERIA
(A1) stale/cross/forged native and surface tokens rejected; (A2) owner lifecycle unambiguous on duplicate runtime; (A3) shutdown while window active returns typed error, then succeeds after destruction; (A4) off-main thread init rejects; (A5) missing Cocoa server fails qualification transparently; (A6) old tests preserved, all new tests actually executed; (A7) no unapproved changes to packet/registry or ADR; (A8) independent exact-HEAD audit.

## TESTS
First red CI on regression-only commit; then clean Windows MSVC, Linux GCC/X11, Linux ASan/UBSan, macOS AppleClang/Cocoa runs and CTest `--output-on-failure` with no false PASS. Capture test names, counts, job conclusions, toolchain and qualification caveats. Potential UAF requires sanitizer evidence. No new CI labels or installs.

## DELIVERABLES
Single Draft PR; test-before-fix red baseline; minimal production delta; full regression CI; evidence bundle with base/head SHAs, specific bugs and reproduction, diffs, risk and rollback; audit pt-BR; checkpoint Delta proposed only until audit APPROVED.

## REVIEW FORMAT
`APPROVED` / `CORRECTION REQUIRED` / `BLOCKED`, grounded in code + CI, checked against Scope, Architecture, Requirements, DoD, ownership and no-surprise diff.

## STOP CONDITION
Stop on stale HEAD/authority, unclear dependency contract, red after allowed corrections, HIGH/CRITICAL remaining, runner unqualified, unapproved scope/CI/registry changes, or unsafe merge. No merge or checkpoint promotion before APPROVED.