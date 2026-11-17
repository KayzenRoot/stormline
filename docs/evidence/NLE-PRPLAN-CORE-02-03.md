# NLE-PRPLAN-CORE-02-03 — Ownership (`MemoryBlock`)

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / MERGED`. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-02-03`. **ADR:** [ADR-0087](../adr/0087-core-02-ownership-slice.md). **Capability admission:** [ADR-0086](../adr/0086-capability-based-l1-dependency.md). **Contract:** [core-02-ownership-v0](../contracts/core-02-ownership-v0.md). **WO:** [NLE-PRPLAN-CORE-02-03](../work-orders/NLE-PRPLAN-CORE-02-03.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

First real CORE-02 code: an internal, move-only `MemoryBlock` over an explicit `std::pmr::memory_resource`, with exact allocation metadata, typed errors and single release. No global allocator replacement, third-party allocator, arena, budget, leak tracker, telemetry, public ABI or release.

## 1. Authorization and Context Lock

- **Gate:** [PR #440](https://github.com/KayzenRoot/stormline/pull/440) squash-merged as `2b5f8fa032f3544fd0ba52683ac2ff7be17b3496`; audit [#6957966885](https://github.com/KayzenRoot/stormline/pull/440#issuecomment-6957966885) **APPROVED**.
- **Code PR:** [PR #441](https://github.com/KayzenRoot/stormline/pull/441), HEAD auditado `a84574b6664f4b68bcdd4f7a55a20ed09d31fc80`, [auditoria pt-BR #6958320627](https://github.com/KayzenRoot/stormline/pull/441#issuecomment-6958320627) **APPROVED**; squash-merged as `ab12abd51499abfe9f0c7e5bac27227516c49ca2`.
- **Base:** `2b5f8fa032f3544fd0ba52683ac2ff7be17b3496`.
- **Selector:** `select_packet.py NLE-PRPLAN-CORE-02-03 --json` → `EXECUTOR_READY`, exit 0; `CORE-02-04`, `CORE-01-09` and every other ID exit 2.
- **Capability admission:** `CORE01_HEADLESS_BUILD_AND_TEST` (`-03`), `CORE01_PORTABLE_PATHS` (`-06`), `CORE01_SDL3_BUILD_BASELINE` (`-07`) and `CORE01_NATIVE_CI_MATRIX` (`-08`) are completed; no CORE-01 window/input/DPI capability is used. CORE-01 is not claimed complete.

| Source | Raw SHA-256 (LF) |
|---|---|
| `docs/11-checkpoint.md` | `4d257070c5179ddce6f0dc474b78d76a0b50fd9df7a7eaeb2c3fa1986732f50a` |
| `docs/adr/0086-capability-based-l1-dependency.md` | `9578629b732c5168ef449c492c57d0d04f5ad2d5bcd1527af3d4c93b985ba39b` |
| `docs/adr/0087-core-02-ownership-slice.md` | `377d48ea8ff4509104b93e250db43b5659918db3cd44a91e9f67e5d0c80a5c18` |
| `docs/contracts/core-02-ownership-v0.md` | `204e9ae2975ed052eb2be1df0d389ee41cf9184ec8b695ea5a2e0dc3525aabc0` |
| `docs/work-orders/NLE-PRPLAN-CORE-02-03.md` | `5fca6e5f2b6f5d827a2dfa051742f2262ca1fafa130f96a2631e087ec816a4fa` |

`validate_pr_plans.py` verifies the activation's live Git blob SHA-1 fingerprints and the exact capability admission.

## 2. Implemented behavior

- `MemoryDomain`: `Persistent`, `Frame`, `Job`, `Streaming`, `Vfx`, `AudioRealtime`, `Network`, `Editor`, `Plugin`.
- `MemoryError`: `None`, `InvalidSize`, `InvalidAlignment`, `OutOfMemory`, `AlreadyOwned`, `InternalFailure`.
- `MemoryBlock::allocate`: rejects an already-owned output, zero size and non-power-of-two alignment before any allocation. `nullptr` resource resolves to `std::pmr::new_delete_resource()`; a custom resource must outlive the block.
- `std::bad_alloc` maps to `OutOfMemory`; other resource exceptions map to `InternalFailure`; a null or misaligned pointer is never handed out. A misaligned pointer is deallocated with the same bytes/alignment and reported as `InternalFailure`.
- Move-only transfer; move assignment releases the previous destination exactly once; self-move is a no-op; source becomes invalid.
- `release()` is idempotent, clears ownership before `deallocate`, and calls `deallocate` with the exact stored bytes/alignment exactly once. The destructor is `noexcept` and releases once.
- Header includes only C++ standard headers; no SDL, platform or third-party type. No `operator new`/`delete` replacement, no default-resource change, no global state.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/memory_block.hpp` | Internal API; standard headers only |
| `src/stormline/core/memory/memory_block.cpp` | `std::pmr` ownership, typed failures, single release |
| `tests/core/memory_block_tests.cpp` | Basic/invalid/owned/move/release/resource/OOM/cross-thread/lifetime tests |
| `CMakeLists.txt` | Additive `stormline_core02_memory` target and nine CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02 source/evidence path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-03.md` | This Evidence Bundle |

No other path changed. Existing CORE-01 targets/tests are unchanged except additive test wiring.

## 4. Tests and real results

### Local preflight (observed)

- Direct MSVC 14.44.35207 compile/link with `/std:c++20 /W4 /WX /EHsc /I src`: **OK**.
- All nine modes executed from the linked binary: `basic`, `invalid`, `owned`, `move`, `release`, `resource`, `oom`, `cross_thread`, `lifetime` → **exit 0**.
- CMake configure with a local SDL3 3.4.20 source override (CI uses the exact pinned commit), `stormline_core02_memory_test` build and `ctest -R core02_`: **9/9 passed**.
- The first link failed because the private `MemoryBlock` constructor was declared but not defined; the definition was added and the rebuild passed. This was a local preflight defect, not a CI PASS.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `4e4b80a10933789cf537fe8c5ad7e1db272e41ba`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44155586578](https://github.com/KayzenRoot/stormline/actions/runs/44155586578) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC 13.3.0, X11 via Xvfb/openbox | **32/32 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan, X11 via Xvfb/openbox | **32/32 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **32/32 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **32/32 CTest passed** |

Native workflow run: [44155586606](https://github.com/KayzenRoot/stormline/actions/runs/44155586606) **SUCCESS**. Job IDs: Linux `134295325459`, sanitizers `134295324701`, Windows `134295325161`, macOS `134295325170`. The nine `core02_memory_*` tests executed in every job in addition to the existing 23 CORE-01 tests; none skipped. The Linux sanitizer job kept ASan/UBSan and the narrow `leak:X11_` SDL3 X11-driver suppression from the window slice; no ownership-test leak was reported.

### Corrections found by real CI (same PR)

1. **GCC/Clang `-Werror=self-move` in the test:** the intentional self-move-assignment case used the direct `self = std::move(self)` form. It was changed to an opaque pointer alias so the semantic test remains while the compiler warning is not triggered. MSVC had accepted the direct form; the Linux/macOS failures were real and are fixed in this PR.
2. The earlier private-constructor link defect was caught by local preflight before the PR and fixed in the same code packet.

No test was skipped and no PASS was claimed before the real runs.

## 5. Security, licensing and limitations

- No third-party dependency, package installation, secret, upload, paid runner/service or runtime download.
- No global allocator override; no `malloc`/`new` replacement; no SDL/platform call.
- The custom test resource must outlive blocks; a resource that violates the `std::pmr` contract can still cause undefined behavior outside this wrapper. Concurrent access to one block is not synchronized; cross-thread release is safe only with a thread-safe resource (the default `new_delete_resource` is).
- This is not CORE-02 complete, not an allocator comparison/benchmark, not arenas/budgets/leaks/telemetry, not a public ABI, not a release. ADR-0004 remains `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- No HIGH/CRITICAL known; native CI passed at the code head and the result remains subject to the independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the memory target/tests, the additive workflow paths and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the first real CORE-02 slice, exact PR/CI/audit/merge SHA, 9 `core02_memory_*` tests and 32 total CTests across Linux, Linux ASan/UBSan, Windows and macOS, and the explicit statement that this is ownership only — not allocator selection, arenas, budgets, leaks, telemetry, public ABI or release. This evidence does not self-promote the checkpoint.

## 8. Actual closure

- [PR #441](https://github.com/KayzenRoot/stormline/pull/441) **squash-merged** at `2026-11-17T19:17:53Z`, merge `ab12abd51499abfe9f0c7e5bac27227516c49ca2`; [auditoria pt-BR #6958320627](https://github.com/KayzenRoot/stormline/pull/441#issuecomment-6958320627) **APPROVED**.
- Final-head Docs Validation [44156511585](https://github.com/KayzenRoot/stormline/actions/runs/44156511585) **SUCCESS**; native [44156511747](https://github.com/KayzenRoot/stormline/actions/runs/44156511747) **SUCCESS**, **32/32 CTest** on Linux, Linux ASan/UBSan, Windows and macOS.
- Packet `CORE-02-03` becomes `COMPLETED` with `github_pr=441`; the manifest has **737 `PLANNED_BLOCKED`, 7 `COMPLETED`, 4 approved gates, 0 `EXECUTOR_READY`**; `select_packet.py` denies every ID. No next packet or module is authorized. CORE-02 remains incomplete; ADR-0004 remains `PROPOSED`.
