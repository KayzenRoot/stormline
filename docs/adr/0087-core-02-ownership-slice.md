# ADR-0087 — CORE-02 ownership slice (`MemoryBlock`)

**Status:** `TECHNICAL_SLICE_PROPOSED / CAPABILITY_ADMITTED_BY_ADR-0086 / CONDITIONAL_ON_AUDIT_AND_MERGE`. **Subordinate to ADR-0004, which remains `PROPOSED`; it does not approve the module technology, an allocator selection, a release class or G3 globally.**

**Date:** 2026-11-17 | **WO:** `NLE-PRPLAN-CORE-02-03` | **Parent:** `NLE-PRPLAN-CORE-02-01` | **Issue:** #19.

## Context

CORE-02 research and the memory architecture are documented, but ADR-0004 is still proposed and the blocked module WO requires a planner-approved first slice, exact interfaces, files, commands and OS matrix. The first NECESSARY increment is **ownership**, not a benchmark, arena, leak tracker, budget graph, telemetry system or global allocator replacement.

ADR-0004 proposes a C++20 `std::pmr`-compatible resource interface, system allocators as the reproducible baseline, and no global allocation override during the first implementation step. This ADR applies only that bounded direction.

## Bounded technical decision

- Add an internal `stormline::core::memory` ownership primitive: `MemoryDomain`, `MemoryError`, `MemoryBlock`.
- `MemoryBlock::allocate` takes an explicit `std::pmr::memory_resource*`; `nullptr` resolves to `std::pmr::new_delete_resource()`. A block stores the resource, pointer, exact bytes, exact alignment and domain, and calls `deallocate` exactly once with the same bytes/alignment.
- `MemoryBlock` is move-only. Copy is deleted. Move transfers the single ownership token and leaves the source invalid. `release()` is idempotent, and the destructor releases on the owner thread of the block.
- No exception crosses the API: allocation failures map to `MemoryError`; a throwing `deallocate` maps to `InternalFailure` without a second release.
- Validation: `bytes > 0`; alignment is a power of two; the output block must be invalid. Requested alignment is honored by the resource and checked in tests.
- No third-party dependency. No `operator new`/`delete` replacement, no global default-resource change, no mimalloc/rpmalloc/Tracy/SMF, no SDL call, no renderer/GPU/audio/network, no public ABI.

## Alternatives rejected

- **Global allocator override now:** rejected by ADR-0004 and the owner's bounded direction; it would change every allocation before benchmarks and ABI ownership are qualified.
- **Adopt mimalloc/rpmalloc now:** rejected; no comparison workload, pinned release audit or security advisory review exists.
- **Arena or leak tracker first:** rejected; those packets depend on an ownership primitive and would widen the slice without evidence.
- **Raw `new`/`delete` without a resource:** rejected; it would not exercise the proposed `std::pmr` boundary or a replaceable test resource.
- **Expose a stable public handle/ABI:** rejected; this is an internal slice only and NLE-D009/licensing remain open.

## Contract and test obligations

Exact API, semantics, allowlist and oracles: [core-02-ownership-v0](../contracts/core-02-ownership-v0.md) and [WO](../work-orders/NLE-PRPLAN-CORE-02-03.md). Required proof:

- `OWN-01` allocate/write/read/release; metadata and alignment.
- `OWN-02` zero size and non-power-of-two alignment rejected without allocation.
- `OWN-03` allocation into an already-owned block rejected without disturbing the owner.
- `OWN-04` move construction/assignment transfers ownership; source invalid; previous destination released exactly once.
- `OWN-05` repeated release and destructor release exactly once.
- `OWN-06` custom resource receives exact bytes/alignment; `bad_alloc` maps to `OutOfMemory`; no deallocate on failure.
- `OWN-07` ownership can be moved and released on another thread; the default resource is thread-safe and the custom test resource uses atomics.
- `OWN-08` existing 23 CORE-01 CTests still pass on Linux, Linux ASan/UBSan, Windows and macOS; no leak from the ownership tests.

## Consequences

- This is the first real CORE-02 code only if the gate and code PRs pass exact-head CI and pt-BR audit. It is not "CORE-02 implemented", not an allocator comparison, not arenas/budgets/leaks/telemetry, and not a release.
- ADR-0004 remains `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.
- The capability admission is only the one recorded in ADR-0086 and expires at packet closeout.

## Rollback

Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push. Removing the memory target/tests and the gate state restores the prior blocked state; no G2, registry, license or release change is part of this ADR.
