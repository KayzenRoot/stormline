# NLE-PRPLAN-CORE-01-06 — Portable process paths implementation

**Status:** `CODE_IMPLEMENTED / LOCAL_MSVC_SUPPLEMENTARY / NATIVE_CI_PENDING / AUDIT_PENDING` · **Master program:** `STORM-CORE-01-IMPL-001` · **Formal packet:** `NLE-PRPLAN-CORE-01-06` · **Contract:** [core-01-process-paths-v0](../contracts/core-01-process-paths-v0.md) · **WO:** [NLE-PRPLAN-CORE-01-06](../work-orders/NLE-PRPLAN-CORE-01-06.md) · **Issue:** [#18](https://github.com/KayzenRoot/stormline/issues/18).

This is the second real CORE-01 code slice. It is internal-only, read-only, CPU-only, standard-library C++20, with no SDL3, window, GPU, audio, network, public ABI, VFS, file creation/write or release.

## 1. Authorization and Context Lock

- **G6 gate:** [PR #431](https://github.com/KayzenRoot/stormline/pull/431) merged as `c484b3081ccab40efaef18ec640a203d600601ed`. It reconciled `-04`/`-05` as objectively covered by the merged `-03` code/tests and activated only `-06`.
- **Base:** `c484b3081ccab40efaef18ec640a203d600601ed`. The owner reference `b3638de…` was the previous main; the gate advanced it by one merge. Fresh Context Lock below.
- **Selector:** `python scripts/select_packet.py NLE-PRPLAN-CORE-01-06 --json` → `status=EXECUTOR_READY`, `executor_ready=true`, exit 0. `-03`, `-04`, `-05`, `-07` and every other ID exit 2.

| Source | Raw SHA-256 | Git blob SHA-1 |
|---|---|---|
| `docs/11-checkpoint.md` | `e29d00d3e37b110e895aa228c6f4b71e5aed50d0721b55e4bf12b936b4259d8b` | `a5575fa0fa8d4f72f0e0cde2c22af7f6d80dfcb3` |
| `docs/10-decisions-ledger.md` | `420220915e0600bb84167106d3384b28e27cd2f4375c1e16ccb8374d701e216c` | `01aa967790dc1ea5e72c2ebebae7b832ec579981` |
| `docs/03-scope.md` | `39ad13b45738516904b767a8997551cccce2a9ff8ea8642c152bb815fa67c0c7` | `0b65820507d946d2b2b4ed3a2b869e60cafaaf22` |
| `docs/09-definition-of-done.md` | `7fc04cc33aad22197b68bcda43fbd356726f11e401cf0e2b68c97f685b12778e` | `e0b7c2466ebec9790a715e47490c015cfb502db4` |
| `docs/adr/0083-core-01-internal-headless-slice.md` | `c484fb10aec5a4b61919967b9026494484f6ae11461f90b94cb1e38fdbdc99a9` | `82d4968e37f0400f092e885d9fe201df772f4719` |
| `docs/contracts/core-01-internal-headless-v0.md` | `b4457feaf74379b5ffd3f8e744727a48cc7673383cd5c259073b495dfd10f38b` | `4ea41263bcfd412ca35df2abb32a158706b64e48` |
| `docs/contracts/core-01-process-paths-v0.md` | `4a6cd9fb25f3b60d34fe91373400ebd04e32a0bfa809dd234171110784c3721d` | `e551ad7b3c8112f79b88a65c33050059762b71fc` |

The activation file pins all seven live blobs; `validate_pr_plans.py` recomputes them and fails on drift.

## 2. Implemented behavior

Namespace `stormline::core::internal`, internal header only:

- `PathError` `None/CurrentDirectoryUnavailable/TemporaryDirectoryUnavailable/NotFound/AccessDenied/InvalidPath/PathTraversalRejected/AllocationFailed/InternalFailure`.
- `PathResult` and `PathTextResult`, plus `current_directory()`, `temporary_directory()`, `normalize_absolute()`, `normalize_within_root()`, `to_utf8()`. All are `noexcept`.
- Read-only standard-library filesystem queries; **no create, write, delete, rename, copy, chmod, network or telemetry call** in production code.
- `normalize_absolute` resolves `absolute` + `weakly_canonical` without requiring final existence; empty/NUL/invalid-UTF-8 are `InvalidPath`.
- `normalize_within_root` requires an existing directory root, resolves symlinks, and checks containment component-wise. Parent traversal, absolute outside paths and symlinks pointing outside are `PathTraversalRejected`.
- `to_utf8` uses the standard-library native conversion and validates the UTF-8 byte sequence; invalid sequences are `InvalidPath`. No NFC/NFD normalization is imposed.
- Permission-denied and unavailable-path errors map to typed errors; no exception crosses the API. `std::bad_alloc` → `AllocationFailed`, other caught failures → `InternalFailure`.
- Test seam `ProcessPathsTestAccess` is `thread_local`, internal-only and defaults to no injection.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/internal/process_paths.hpp` | Internal API and typed results |
| `src/stormline/core/internal/process_paths.cpp` | Read-only implementation, error mapping, UTF-8 validation, containment |
| `tests/core/process_paths_tests.cpp` | PATH-01..PATH-12 tests, fixtures, no-write snapshot |
| `CMakeLists.txt` | Additive paths library/targets and 7 CTests; existing headless target preserved |
| `docs/evidence/NLE-PRPLAN-CORE-01-06.md` | This Evidence Bundle |

No other path changed. `CMakePresets.json` did not need a change; the existing Debug/ASan presets build all targets.

## 4. Tests and real results

### Local supplementary check (not a target qualification)

The local machine has no CMake/Ninja in `PATH`; installing new tooling is prohibited. Preinstalled **MSVC 14.44.35207** compiled both sources with `/std:c++20 /W4 /WX /EHsc` and ran every mode:

| Mode | Result |
|---|---|
| `basic` (cwd/temp/absolute, 200 repetitions) | **PASS** |
| `unicode` (ç/日本/🚀, composed/decomposed, UTF-8 round-trip) | **PASS** |
| `traversal` (contained, parent escape, absolute outside) | **PASS** |
| `errors` (empty/NUL/invalid UTF-8, forced access/unavailable, missing/non-dir root) | **PASS** |
| `no_write` (entry snapshot and marker unchanged after 50 query loops) | **PASS** |
| `symlink` | **PASS**, real symlink case `NOT_QUALIFIED` locally (creation privilege unavailable) |
| `access` | **PASS**, real Windows ACL denial `NOT_QUALIFIED` (environment-dependent); deterministic mapping PASS |

MSVC 14.44 is **not** the approved provisional target (14.51); this is supplementary evidence only.

### Native CI (authoritative, pending)

The code PR must run the existing workflow on `ubuntu-24.04`, `windows-2025-vs2026` and `macos-15`, plus Linux ASan/UBSan when preinstalled. It must execute the 5 existing headless CTests and the 7 new paths CTests. The PR stays Draft until exact-head Docs Validation and native results are observed and recorded here. No native PASS is claimed before that.

## 5. Contract mapping and limitations

- Covers PATH-01..PATH-12: cwd/temp absolute and existing, Unicode round-trip, invalid input, traversal, contained normalization, denied/unavailable typed errors, symlink escape, no-write proof, 200 repetitions and full headless regression.
- No Unicode normalization library is added; composed/decomposed forms are preserved per OS. Real Windows ACL denial is environment-dependent and recorded `NOT_QUALIFIED` if unavailable; the deterministic mapping test still runs.
- No real physical hardware, SDL3, window, GPU, audio, ABI, packaging or release certification is claimed.
- No HIGH/CRITICAL defect is known; subject to exact-head native CI and independent audit.

## 6. Security, licensing and rollback

- Only the C++ standard library; no dependency, vendored code, asset or license change. `NLE-D009 OPEN`; ADR-0003/0075 `PROPOSED`; ADR-0083 bounded; G3 global `NOT_CLEARED`.
- No secret, paid runner, upload, cache, install or workflow permission change. Standard public runners only.
- Unmerged rollback: close the branch; `main` untouched. After a future merge: normal revert PR, never force push.
- Risk `STANDARD`, release `INTERNAL_ONLY` only for this slice. 80/80 module WOs remain `BLOCKED`; no next packet or module is unlocked.

## 7. Proposed checkpoint delta (not promoted)

After an approved squash merge and readback, a separate checkpoint PR may record the second real CORE-01 slice, exact PR/CI/audit/merge SHA, the 5+7 CTest matrix including sanitizers, the `NOT_QUALIFIED` ACL/symlink notes and the explicit statement that this is still an internal read-only utility, not CORE-01 completion, SDL3, public ABI or release. This evidence does not self-promote that checkpoint.
