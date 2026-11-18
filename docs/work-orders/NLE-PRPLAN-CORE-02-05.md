# NLE-PRPLAN-CORE-02-05 — Monotonic arena (INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE.** **Gate:** G6 individual + capability admission. **Formal packet:** `NLE-PRPLAN-CORE-02-05`. **Predecessor:** `-04` `COMPLETED` via PR #466. **Issue:** #19. **Base:** `9d49dc3da22d245daf1df95d0f27ee56588904af`. **ADR:** [ADR-0097](../adr/0097-core-02-monotonic-arena.md). **Contract:** [core-02-monotonic-arena-v0](../contracts/core-02-monotonic-arena-v0.md).

## OBJECTIVE

Implement a fixed-capacity monotonic arena with one backing `MemoryBlock`, bump allocation, explicit reset, alignment/high-water tracking and typed overflow/error behavior.

## CONTEXT

CORE-02-03 ownership and -04 system baseline are completed. ADR-0004 proposes bounded scratch arenas; CORE-04 owns frame/job reset barriers. This slice is the arena primitive only, not a pool/budget/leak/telemetry layer.

## SCOPE

- `ArenaError`, `ArenaSlice`, `MonotonicArena`; capacity/backing alignment constructor; one backing allocation.
- Bump allocation, alignment padding, overflow, reset/high-water, owner-thread, typed errors.
- Tests ARN-01..ARN-06; existing 73 CTests; Linux ASan/UBSan.

## OUT OF SCOPE

Per-slice free, pools, budgets, leak tracking, telemetry, frame/job reset barriers, global/static arena, allocator winner, third-party dependency, public ABI, release.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADRs 0004/0086/0087/0096/0097, CORE-02 architecture/contracts, MemoryBlock/SystemMemoryResource code/tests, manifest/activation, CI evidence.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction; ADR-0086 capability rule; ADR-0097 bounded slice.

## ARCHITECTURE RULES

Internal namespace/header; standard/internal headers; no SDL/third-party; one backing block; no per-slice free; owner-thread; typed errors; no exception across API; no global/static; no telemetry.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`; no dependency/package/secret/paid service; standard CI; ADR-0004 `PROPOSED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs `BLOCKED`; engine=false.

## ACCEPTANCE CRITERIA

- Exact allowlist; selector only `-05`.
- ARN-01..ARN-06; alignment/overflow/reset/high-water/wrong-thread/lifetime/resource.
- Existing 73 CTests; four CI jobs + ASan/UBSan.
- No pool/budget/leak/telemetry/global/static/ABI/release claim.
- Docs Validation + native CI; no HIGH/CRITICAL; pt-BR audit.

## TESTS

Docs validators + 62+ tests + selector. Native: `ctest -R core02_arena_`, full preset four jobs. Exact: `cmake --preset core01-internal-debug`, build, ctest, asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/memory/monotonic_arena.hpp`, `.cpp`, `tests/core/monotonic_arena_tests.cpp`, additive `CMakeLists.txt`, additive workflow filters, `docs/evidence/NLE-PRPLAN-CORE-02-05.md`. PR, CI, Evidence, pt-BR audit, proposed checkpoint.

## REVIEW FORMAT

pt-BR: base/head, files, ARN matrix, alignment/overflow/reset/resource evidence, regression/sanitizer, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

STALE, gate not merged, selector blocked, regression, CI red, HIGH/CRITICAL, out-of-allowlist, per-slice free/global/static/third-party/ABI/release overclaim, another packet. No bypass.

## CONTEXT LOCK

Gate base `9d49dc3…`; activation pins ADR/contract/source blobs and capability admission. Recompute after gate merge.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-02-05.md` with PR/CI/audit/merge SHAs, alignment/overflow/reset/high-water, regression, sanitizer, limitations, rollback.
