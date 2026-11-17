# NLE-PRPLAN-CORE-02-04 — System allocator baseline (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-04`. **Predecessor:** `-03` `COMPLETED` via PR #441. **Issue:** #19. **Base:** `4920c2f4e3bf787f58c867c2df5bd321eaca8729`. **ADR:** [ADR-0096](../adr/0096-core-02-system-allocator-baseline.md). **Contract:** [core-02-system-allocator-v0](../contracts/core-02-system-allocator-v0.md).

## OBJECTIVE

Implement an explicit `SystemMemoryResource` over `::operator new/delete` (aligned and ordinary paths), integrate it with `MemoryBlock`, and provide a report-only comparative harness against the system PMR resource, raw new/delete and malloc/free. No allocator selection or global override.

## CONTEXT

CORE-02-03 delivered ownership. ADR-0004 requires the system baseline before third-party candidates. CORE-01 capabilities `-03/-06/-07/-08` are completed; the formal CORE-01 dependency remains. This slice is baseline/comparison only.

## SCOPE

- `SystemMemoryResource` deriving `std::pmr::memory_resource`; aligned new/delete; zero-byte=1; identity equality.
- `MemoryBlock` integration; 10,000-cycle lifetime; cross-thread release.
- Report-only benchmark vs `new_delete_resource`, `::operator new/delete`, `malloc/free`.
- Tests SYS-01..SYS-06; existing 67 CTests regression; Linux ASan/UBSan.

## OUT OF SCOPE

mimalloc/rpmalloc/jemalloc selection or vendoring; global `new/delete` override; arenas/pools/budgets/leaks/telemetry; RSS/fragmentation/performance verdict; plugin ABI; release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0087/0096, CORE-02 architecture/contracts, MemoryBlock code/tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0096 bounded slice.

## ARCHITECTURE RULES

Internal namespace/header only; standard headers; no SDL/third-party; no global override; explicit resource; matching alloc/dealloc; no exception across MemoryBlock API; no counters/telemetry; no winner selection.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no third-party/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-04`.
- System resource semantics and alignment; MemoryBlock integration; zero/lifetime/cross-thread.
- Report-only benchmark with no threshold; existing 67 CTests; four CI jobs + ASan/UBSan.
- No allocator winner/global override/third-party/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 60+ tests + selector. Native: `ctest -R core02_system_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/memory/system_memory_resource.hpp`, `.cpp`, `tests/core/system_memory_resource_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-04.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, SYS matrix, alignment/lifetime/benchmark evidence, regression/sanitizer, no selection/global/ABI/release overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, global override, third-party, winner/performance/ABI/release overclaim, another packet. No bypass.

## CONTEXT LOCK

Gate base `4920c2f…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-04.md` with PR/CI/audit/merge SHAs, alignment/lifetime/benchmark, regression, sanitizer, limitations, rollback.
