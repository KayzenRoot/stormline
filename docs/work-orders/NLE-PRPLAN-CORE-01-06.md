# NLE-PRPLAN-CORE-01-06 — Portable process paths (INTERNAL_ONLY)

**STATUS: COMPLETED — implemented and merged via [PR #432](https://github.com/KayzenRoot/stormline/pull/432), merge `002162790e61ad64123fb6b187f026b685de7c47`. This packet must not be re-executed; no next packet or module is authorized.**

**Gate:** G6 individual, conditional on gate PR audit/merge and executor fresh Source Check. **Master program:** `STORM-CORE-01-IMPL-001`. **Formal packet:** `NLE-PRPLAN-CORE-01-06`. **Predecessors:** `-04` and `-05` reconciled as already covered by the merged `-03` code/tests (see [G6 evidence](../evidence/NLE-PRPLAN-CORE-01-06-G6-ACTIVATION.md)); `-03` is `COMPLETED` via PR #428. **Issue:** #18. **Base:** `b3638de6c6918e36b49726af63abeb09bd35f140`. **Contract:** [core-01-process-paths-v0](../contracts/core-01-process-paths-v0.md).

## OBJECTIVE

Implement the smallest real CORE-01 capability after the headless host: a read-only, internal C++20 API for current working directory, system temporary directory, absolute normalization, containment within an explicit root, and validated UTF-8 representation, with typed errors and no exceptions across the boundary.

## CONTEXT

`-03` delivered the internal `HeadlessHost` and already implements the `-04`/`-05` acceptance (typed config/states/errors, wrong-transition rejection, duplicate-init no side effects, partial-init rollback, resource ownership, cleanup retry, destructor cleanup, 200 cycles). Those packets are reconciled as `COMPLETED` by objective mapping to the merged code/tests and CI, not by scope similarity. `-06` is the next dependency in the formal chain.

## SCOPE

- `current_directory()`, `temporary_directory()`, `normalize_absolute()`, `normalize_within_root()`, `to_utf8()` exactly as the contract defines.
- Typed `PathError`/`PathResult`/`PathTextResult`, `noexcept`, no exception escape.
- Read-only filesystem queries only; Unicode preservation/validation; symlink-aware containment; permission-denied mapping; deterministic unavailable-path errors.
- New paths library/target and CTests; full regression of the existing 5 headless CTests.
- Minimal evidence and checkpoint delta after observed results.

## OUT OF SCOPE

File/directory creation, writes, deletion, rename, copy, watching, permission changes, environment mutation, VFS/mount/asset resolution, sandbox implementation, logging of private paths, telemetry, network, SDL3, window/GPU/audio, public ABI/plugin/SDK, release/packaging, other modules, next packet.

## FILES / SOURCES TO READ

`AGENTS.md`; checkpoint; Decisions Ledger; Scope/DoD/Architecture/Requirements; `docs/engineering/core-01-01-qualification-gates.md` (C01-Q017 and CORE-01 scope); ADR-0003/ADR-0083; both CORE-01 contracts; PR-plan manifest and activation; the merged `-03` source/tests/CMake/evidence; current main/CI. Inspect Git before editing.

## REQUIREMENTS

GOV-001..005, CAP-010/014, NFR-002/003/005; C01-D09/G1-M06 "caminhos essenciais"; C01-Q017 path oracle where applicable; no new owner technical decision. Preserve `-03` behavior and all 80 module WOs blocked.

## ARCHITECTURE RULES

Internal namespace/header only; `std::filesystem`/C++20 standard library first; no native OS API unless a tested portability gap requires a narrow encapsulated fallback. No VFS, global root, singleton, hidden current-directory mutation or public ABI. Separate paths library, no duplication of `HeadlessHost`. Typed errors and component-wise containment; symlinks resolved before the boundary check. No write call in production code. Tests may use a private temporary fixture and must clean it up.

## CONSTRAINTS

Risk `STANDARD`, release class `INTERNAL_ONLY` only. No external dependency, install, secret, paid runner, upload, cache or deployment. G3 global NOT_CLEARED, ADR-0003/0075 PROPOSED, ADR-0083 bounded, NLE-D009 OPEN. Standard public CI on `ubuntu-24.04`, `windows-2025-vs2026`, `macos-15`; sanitizers when preinstalled. No next packet or module unlock.

## ACCEPTANCE CRITERIA

- Exact allowlist; fresh Context Lock; selector `executor_ready=true` only for `-06`.
- All five contract functions implemented with the exact states/errors; no exception crosses; no write/create/delete in production source.
- PATH-01..PATH-11 executed where the OS supports them; real POSIX access denial where possible; deterministic permission/unavailable mapping on every OS; symlink escape rejected where supported; invalid UTF-8/empty/NUL typed as `InvalidPath`; no unexpected writes.
- Existing 5 headless CTests still pass; warnings as errors; Linux ASan/UBSan when supported; clean build on Windows/Linux/macOS at exact PR HEAD.
- No HIGH/CRITICAL known issue; Docs Validation + native CI PASS; objective pt-BR audit; squash/readback; no product/release/ABI claim.

## TESTS

Docs: `python3 scripts/validate_docs.py`, `validate_wo_registry.py`, `validate_pr_plans.py`, unit tests, packet selector. Native: existing `core01_headless_*` CTests plus new `core01_paths_*` CTests via CMake Presets; 200 repeated queries; Unicode, invalid UTF-8, empty/NUL, traversal, symlink, access-denied mapping, no-write fixture check. Results must be real; skipped/unsupported cases recorded `NOT_QUALIFIED`.

## DELIVERABLES

Exactly: `src/stormline/core/internal/process_paths.hpp`, `src/stormline/core/internal/process_paths.cpp`, `tests/core/process_paths_tests.cpp`, `CMakeLists.txt` (additive), `docs/evidence/NLE-PRPLAN-CORE-01-06.md`. GitHub PR, exact native CI receipts, Evidence Bundle, objective pt-BR audit, proposed checkpoint delta. Gate files are separate.

## REVIEW FORMAT

Portuguese Brazil: base/head, exact files, contract compliance, PATH matrix + sanitizer, existing regression, security/no-write evidence, risk/license/credentials, no HIGH/CRITICAL. Verdict `APPROVED`, `CORRECTION REQUIRED` or `BLOCKED`. Corrections only in the same WO/PR.

## STOP CONDITION

STALE context, gate not merged, selector blocked, existing test regression, CI red, HIGH/CRITICAL, unapproved dependency/write/VFS/ABI, write in production code, out-of-allowlist change, attempt to unlock another packet/module, or any destructive operation. Never bypass G2 or force push.

## CONTEXT LOCK

Gate base `b3638de6c6918e36b49726af63abeb09bd35f140`; activation pins the exact contract/source blobs. Executor must recompute fresh raw SHA-256 after the gate merge and stop/rebase on substantive canonical change. Historical Git blob IDs in the activation are not a substitute for the fresh lock.

## EVIDENCE BUNDLE

Separate `docs/evidence/NLE-PRPLAN-CORE-01-06.md` in the code PR with PR/CI/audit/merge SHAs, exact toolchains, PATH results, existing regression, sanitizer, no-write proof, limitations and rollback. Gate evidence never masquerades as implemented code.
