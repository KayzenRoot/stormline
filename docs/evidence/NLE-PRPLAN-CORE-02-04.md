# NLE-PRPLAN-CORE-02-04 — System allocator baseline and report-only measurement

**Status:** `CODE_IMPLEMENTED / NATIVE_CI_PASS / MERGED`. **Formal packet:** `NLE-PRPLAN-CORE-02-04`. **ADR:** [ADR-0096](../adr/0096-core-02-system-allocator-baseline.md). **Contract:** [core-02-system-allocator-v0](../contracts/core-02-system-allocator-v0.md). **WO:** [NLE-PRPLAN-CORE-02-04](../work-orders/NLE-PRPLAN-CORE-02-04.md). **Issue:** [#19](https://github.com/KayzenRoot/stormline/issues/19).

Explicit `SystemMemoryResource` over ordinary/aligned `::operator new/delete`, integrated with `MemoryBlock`, plus a report-only benchmark against `std::pmr::new_delete_resource`, raw new/delete and malloc/free. No third-party allocator, global override, winner selection or performance PASS.

## 1. Authorization and Context Lock

- **Gate:** [PR #465](https://github.com/KayzenRoot/stormline/pull/465) squash-merged as `574bc4bfd13213a480c2bfa0b467754413269548`; audit #6964591046 **APPROVED**.
- **Base:** `574bc4bfd13213a480c2bfa0b467754413269548`.
- **Code PR:** [PR #466](https://github.com/KayzenRoot/stormline/pull/466), HEAD auditado `58ca01f…`, [auditoria pt-BR #6965080349](https://github.com/KayzenRoot/stormline/pull/466#issuecomment-6965080349) **APPROVED**; squash-merged as `e04e2cd…`.
- **Selector:** during execution, `select_packet.py NLE-PRPLAN-CORE-02-04 --json` → `EXECUTOR_READY`, exit 0; after closeout every ID exits 2.
- **Capability admission:** `CORE-01-03/-06/-07/-08` completed; formal CORE-01 dependency retained; no module completion claim.

## 2. Implemented behavior

- `SystemMemoryResource final : public std::pmr::memory_resource`.
- Ordinary `::operator new/delete` for alignment ≤ `alignof(std::max_align_t)`, aligned new/delete otherwise.
- Zero-byte requests allocate one byte; deallocation of the original zero-byte request uses the same effective size.
- Non-power-of-two alignment falls back to `alignof(std::max_align_t)` inside the resource (the `memory_resource` caller contract still requires a power of two).
- Identity-based `do_is_equal`; no global override, counters, logging or third-party dependency.
- `MemoryBlock` integration; release uses the exact original bytes/alignment through the resource.
- Report-only benchmark compares system resource, `new_delete_resource`, raw new/delete and malloc/free; no threshold.

## 3. Exact changed files

| File | Purpose |
|---|---|
| `src/stormline/core/memory/system_memory_resource.hpp` | Internal resource API |
| `src/stormline/core/memory/system_memory_resource.cpp` | Ordinary/aligned new/delete paths |
| `tests/core/system_memory_resource_tests.cpp` | basic/alignment/block/lifetime/cross-thread/benchmark |
| `CMakeLists.txt` | Additive `stormline_core02_system_allocator` target and six CTests |
| `.github/workflows/core01-internal-headless.yml` | Additive CORE-02-04 path filters |
| `docs/evidence/NLE-PRPLAN-CORE-02-04.md` | This Evidence Bundle |

No other path changed. Existing CORE-01/CORE-02 targets are unchanged except additive allocator wiring.

## 4. Tests and real results

### Local preflight (observed)

- CMake/Ninja build of `stormline_core02_system_allocator_test`: **OK**.
- `ctest -R core02_system_`: **6/6 passed** on Windows/MSVC 14.44.
- Full local matrix: **73/73 CTests passed** (67 previous + 6 system tests).
- Local benchmark output (MSVC, one run, **not a product verdict**):
  `SYSTEM_ALLOC_BENCHMARK system_ns_op=1105.098 pmr_ns_op=652.083 new_ns_op=594.131 malloc_ns_op=566.510`
- This order/warm-up-sensitive local number is not a winner selection or performance PASS.

### Native CI (authoritative, observed)

All jobs ran at the exact HEAD `a5f783ef0531165e5dc7198f4cc17766c45e742d`:

| Job | Runner / toolchain | Result |
|---|---|---|
| `docs-validation` | required G2 check | [run 44204175688](https://github.com/KayzenRoot/stormline/actions/runs/44204175688) **SUCCESS** |
| `linux` | ubuntu-24.04, GCC, X11 via Xvfb/openbox | **73/73 CTest passed** |
| `linux-sanitizers` | ubuntu-24.04, ASan/UBSan | **73/73 CTest passed** |
| `windows` | windows-2025-vs2026, MSVC | **73/73 CTest passed** |
| `macos` | macos-15-arm64, Apple clang | **73/73 CTest passed** |

Native workflow run: [44204176376](https://github.com/KayzenRoot/stormline/actions/runs/44204176376) **SUCCESS**. Job IDs: Linux `134465742652`, sanitizers `134465742439`, Windows `134465742179`, macOS `134465742668`. The six `core02_system_*` tests executed in every job; 67 CTests anteriores continuam passando. No correction was required.

## 5. Security, licensing and limitations

- No third-party allocator, package, secret, upload, paid runner/service or runtime download.
- No global `new/delete` override, arena/pool/budget/leak/telemetry, plugin ABI or release.
- No mimalloc/rpmalloc comparison or selection; ADR-0004 remains `PROPOSED`.
- The benchmark is report-only; no RSS/fragmentation/p95/p99 budget or winner.
- ADR-0003/0004/0075 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false`.
- No HIGH/CRITICAL known; final status subject to exact-head CI and independent pt-BR audit.

## 6. Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the system-allocator target/tests/benchmark and this evidence restores the previous state.

## 7. Proposed checkpoint delta (promoted only by the independent closeout)

After an approved squash merge and readback, a separate closeout PR records the system allocator baseline, exact PR/CI/audit/merge SHA, 6 `core02_system_*` tests, 73 total CTests and the report-only benchmark output. It explicitly states that no third-party allocator was selected and no performance/RSS/fragmentation verdict was made. This evidence does not self-promote the checkpoint.

## 8. Actual closure

- [PR #466](https://github.com/KayzenRoot/stormline/pull/466) **squash-merged** at `2026-11-18T00:17:58Z`, merge `e04e2cd…`; audit #6965080349 **APPROVED**.
- Final-head Docs Validation [44206099358](https://github.com/KayzenRoot/stormline/actions/runs/44206099358) **SUCCESS**; native [44206099425](https://github.com/KayzenRoot/stormline/actions/runs/44206099425) **SUCCESS**, **73/73 CTest** on Linux, Linux ASan/UBSan, Windows and macOS.
- Packet `CORE-02-04` becomes `COMPLETED` with `github_pr=466`; manifest **728 `PLANNED_BLOCKED`, 16 `COMPLETED`, 4 approved gates, 0 `EXECUTOR_READY`**; selector denies every ID. No third-party allocator selected; no performance/RSS/fragmentation verdict. No next packet/module authorized.
