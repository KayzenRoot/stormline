# Evidence Bundle — NLE-P00-WO-002-CORE-05

**Date:** 2026-11-14 | **Risk:** LOW for research docs; ELEVATED for future engine implementation due to serialization/origin concerns.  
**Research issue:** [#102](https://github.com/KayzenRoot/stormline/issues/102) | **PR:** [#103](https://github.com/KayzenRoot/stormline/pull/103).  
**State:** PENDING FINAL HEAD AUDIT; architecture and ADR-0007 PROPOSED, no runtime code.

## Git and scoped change
- Base main / checkpoint after CORE-04: `c96fcc0d5e5094c84cd1e0af9085fba6849bcecb`.
- Initial research HEAD: `8dabf39cb76fbbf1ec436ed63e6fe8992763c0ca`, branch `docs/NLE-P00-WO-002-CORE-05-math-research`.
- Seven initial changes: architecture, matrix, ADR-0007, research WO plus links in docs/04-architecture.md, docs/08-backlog.md and blocked docs/queue/work-orders/CORE-05.md. This Evidence Bundle is the eighth Markdown file.
- No C++, deps, vendor files, graphics, shader, physics, networking, deploy, credentials or release. The future implementation issue #22 stays BLOCKED.

## Context Lock fingerprints (Git blob SHAs, not SHA-256)
- Checkpoint: `a7f229a6102b7620f62b65b5e1c825197acde9c0`
- Ledger: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope: `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD: `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture: `2a550d3b382cb204cea66de6879401eb4858e15d`
- Requirements: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- CORE-04 ADR-0006: `436413710da01c49eee1042050530937fd50081d`
- The eventual Zcode executor must obtain fresh SHA-256 fingerprints at code-activation preflight. Git blob hashes are not SHA-256 proof.

## Observed Docs Validation
- [CI #43597818853](https://github.com/KayzenRoot/stormline/actions/runs/43597818853) SUCCESS on research-content HEAD `8dabf39cb76fbbf1ec436ed63e6fe8992763c0ca`.
- Steps green: Source Pack/links, catalog+DAG, 80-module WO registry, read-only Zcode selector rejecting blocked WOs.
- **Final CI after adding this file must also pass before approval/merge.** Do not assert a passing final HEAD without an observed run. No native C++/CPU/GPU benchmarks or precision golden tests have run.

## Technical proposal and boundaries
- C++20 portable scalar reference and strong unit/space types, GLM comparator, Eigen/DirectXMath/MathFu alternatives evaluated at research level. No library introduced, version pinned, ABI implemented or external licensing obligation incurred.
- Right-handed +Y-up/-Z-forward, meters/radians/column-vector semantics and explicit clip-space conversion are **proposed**, not proven production conventions.
- f64 global vs cell+offset world precision evaluation, f32 camera-relative rendering, origin epoch/rebasing and stable persistent IDs separated from generation handles; future fixtures specify precision-loss, singularity, NaN/INF and cross-platform SIM/DATA/NET tests.
- Cross-platform numerical parity, hardware performance, renderer quality, exact float tolerances and persisted format compatibility remain **unproven**, blocked until future benchmark/integration tests.

## Safety, license and audit limitations
- Repo remains public with zero-cost CI; no CodeRabbit, required external human reviewer, force push, bypass, unapproved expenditure or secrets. Release classes are UNDECIDED.
- GLM source declares permissive terms and Eigen MPL-2.0 weak copyleft; pinned versions, notices, security provenance and actual distribution/license analysis required before code.
- Implementation packet `NLE-EXEC-WO-CORE-05-001` and issue #22 remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`.
- Objective pt-BR audit to be recorded on the PR. No known HIGH/CRITICAL issue identified in the initial research-only diff; final HEAD requires validation.

## Proposed Checkpoint Delta AFTER approved merge/readback
1. Mark `NLE-P00-WO-002-CORE-05` research as APPROVED/MERGED **docs only**, issue #102, PR #103, final CI HEAD and merge commit, with limitations above.
2. Keep ADR-0007 PROPOSED for engine code, CORE-05 implementation #22 BLOCKED, and 80 planned executor WOs non-executable.
3. Next candidate after checkpoint reconciliation only: `NLE-P00-WO-002-CORE-06` Diagnostics & Observability technical research, planned without code; no premature issue activation.
