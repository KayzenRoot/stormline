# NLE-PRPLAN-CORE-02-03 — Ownership (`MemoryBlock`, INTERNAL_ONLY)

**STATUS: EXECUTOR_READY ONLY AFTER THE GATE PR PASSES DOCS VALIDATION, PT-BR AUDIT AND SQUASH MERGE; not executable while the manifest is in a blocked state.** **Gate:** G6 individual, conditional on that merge and a fresh executor Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-02-03`. **Predecessor:** `NLE-PRPLAN-CORE-02-02` (contract gate in the same audited gate PR). **Issue:** #19. **Base:** `bb7229496a5c015ae4d2e31be444381cefc49c1f`. **ADR:** [ADR-0087](../adr/0087-core-02-ownership-slice.md). **Capability admission:** [ADR-0086](../adr/0086-capability-based-l1-dependency.md). **Contract:** [core-02-ownership-v0](../contracts/core-02-ownership-v0.md).

## OBJECTIVE

Implement the first real CORE-02 ownership primitive: an internal, move-only `MemoryBlock` over an explicit `std::pmr::memory_resource`, with exact allocation metadata, typed errors, single release and no global allocator override.

## CONTEXT

CORE-02 research and architecture are documented. ADR-0004 remains `PROPOSED`, the module WO remains `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, and the owner approved capability-based L1 admission. Completed CORE-01 packets provide the build/test/CI baseline; no CORE-01 window/input/DPI capability is used. This packet is ownership only, not allocator selection, arenas, budgets, leak tracking or telemetry.

## SCOPE

- Internal `MemoryDomain` (9 logical domains), `MemoryError` (6 typed states), `MemoryBlock` (`allocate`, `release`, `data`, `size`, `alignment`, `domain`, `valid`, `operator bool`).
- Explicit `std::pmr::memory_resource*`; `nullptr` resolves to `std::pmr::new_delete_resource()`; no global default-resource change.
- Move-only ownership transfer; idempotent release; no-throw destructor; exact bytes/alignment deallocation.
- `OWN-01`..`OWN-08` tests, existing 23 CTests regression, Linux ASan/UBSan, Windows and macOS, Evidence Bundle.

## OUT OF SCOPE

Global `operator new`/`delete` replacement; mimalloc/rpmalloc/jemalloc/Tracy/SMF; allocator comparison or benchmarks; arenas, pools, frame/job scratch reset, budgets, pressure, leak tracking, telemetry, snapshots, plugin/SDK ABI, GPU VRAM, renderer/GPU/audio/network, physical-hardware qualification, packaging/release, other modules or packets.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Ledger/ADRs 0003/0004/0083..0087; Scope/DoD/Architecture/Requirements; CORE-02 architecture and technology matrix; this gate's ADR/contract/activation; CORE-01 completed code/tests/CMake/CI evidence; C++20 `std::pmr::memory_resource` standard semantics. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-009/010, NFR-002/003/005; ADR-0004 proposed direction (explicit `std::pmr`, system baseline, no global override); ADR-0086 capability admission; ADR-0087 bounded ownership slice. No new owner technology decision beyond the explicit `std::pmr`/system-baseline direction and the capability admission recorded in the gate.

## ARCHITECTURE RULES

Internal namespace/header only; standard headers only in the header; no SDL/platform/third-party type; explicit resource injection; no global mutable state; one releaser; move-only; typed errors; no exception across the boundary; exact bytes/alignment on deallocate; no renderer/GPU/audio/network call. Do not modify existing CORE-01 behavior or targets beyond additive CMake/test wiring.

## CONSTRAINTS

Risk `STANDARD`, release `INTERNAL_ONLY`. No third-party dependency, package installation, secret, upload, runtime download, paid runner/service or release. Standard public CI on Linux, Linux ASan/UBSan, Windows and macOS. ADR-0004/0003 `PROPOSED`; G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; `engine_implemented=false` at module/product level.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector ready only for `NLE-PRPLAN-CORE-02-03`.
- `MemoryBlock` contract implemented: invalid inputs/`AlreadyOwned`, resource injection, exact metadata, move-only transfer, idempotent release, no-throw destructor.
- `OWN-01`..`OWN-08` executed on Linux, Linux ASan/UBSan, Windows and macOS; 23 existing CTests regression; no leak from ownership tests; no global allocator override or third-party dependency.
- Docs Validation + native CI PASS at exact PR HEAD; no HIGH/CRITICAL; pt-BR audit; squash/readback; no allocator-selection/arena/budget/leak/telemetry/release/ABI claim.

## TESTS

Docs: `validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: `OWN-01` basic, `OWN-02` invalid, `OWN-03` owned, `OWN-04` move, `OWN-05` release, `OWN-06` resource/OOM, `OWN-07` cross-thread, `OWN-08` lifetime/regression; CMake Presets; ASan/UBSan on Linux. Exact commands: `cmake --preset core01-internal-debug`, `cmake --build --preset core01-internal-debug`, `ctest --preset core01-internal-debug --output-on-failure`, plus the asan preset.

## DELIVERABLES

Exactly: `src/stormline/core/memory/memory_block.hpp`, `memory_block.cpp`, `tests/core/memory_block_tests.cpp`, `CMakeLists.txt` (additive), `.github/workflows/core01-internal-headless.yml` (additive path filters), `docs/evidence/NLE-PRPLAN-CORE-02-03.md`. GitHub PR, exact CI receipts, Evidence, pt-BR audit, proposed checkpoint. Gate files separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, OWN matrix, resource/OOM/move/cross-thread evidence, existing regression, sanitizer, no global override, no third-party/SDL/ABI claim, risk/security. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, missing capability evidence, existing test regression, CI red, HIGH/CRITICAL, unsafe write, out-of-allowlist change, global allocator override, third-party dependency, SDL call, allocator-selection/arena/budget/leak/telemetry/release/ABI overclaim, another packet/module unlock, or destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `bb7229496a5c015ae4d2e31be444381cefc49c1f`; activation pins the exact ADR/contract/source blobs and the completed CORE-01 capability packets. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive change.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-02-03.md` with PR/CI/audit/merge SHAs, exact files, resource/OOM/move/cross-thread results, OWN-01..08, regression, sanitizer, no-global-override proof, limitations and rollback. Gate evidence never masquerades as implemented code.
