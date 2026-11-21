# NLE-PRPLAN-CORE-03-09 — Integrated qualification evidence

**Status:** `TEST-ONLY QUALIFICATION / EXACT-HEAD CI GREEN / AUDIT PENDING`. **Base main:** `9cbf25d` (gate PR #515). **Head:** `614d7219adf25e9737db0bf32ed6ff49d2e05a68`. **Formal packet:** `NLE-PRPLAN-CORE-03-09`. **Risk:** `ELEVATED`. **Release class:** `INTERNAL_ONLY`. **Contract:** [core-03-qualification-v0](../contracts/core-03-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-03-09](../work-orders/NLE-PRPLAN-CORE-03-09.md).

## Scope

Exact allowlist:

1. `tests/core/core03_jobs_qualification_tests.cpp`
2. `CMakeLists.txt` (additive qualification target/tests)
3. `.github/workflows/core01-internal-headless.yml` (TSan target and CORE-03 paths)
4. `docs/evidence/NLE-PRPLAN-CORE-03-09.md` (this file)

No production source, API, dependency, ABI, allocator, threshold or release change.

## QLF matrix

| ID | Result | Evidence |
|---|---|---|
| QLF-01 integrated | PASS | 3 jobs/13 tasks: mixed priorities, worker/MainThread dependencies, cancellation scope 777, commits 10/20/30 in ascending order; stats submitted=13, completed=10, cancelled=3, failed=0, queue=0 |
| QLF-02 stress | PASS | 100 jobs × 100 tasks = **10,000 tasks**; each per-job counter exactly 100; stats submitted/completed 10,000; queue 0 |
| QLF-03 recovery | PASS | 20-job cancellation storm (40 tasks) with zero execution, drain returns Cancelled; cycle `CycleDetected`; zero-capacity `InvalidCapacity`; 20-task overflow `QueueFull`; 2-task recovery executes; fresh executor after stop executes 4 tasks |
| QLF-04 overload | PASS | 4 independent tasks on `max_tasks=2` rejected `QueueFull` 10× with zero submission/queue/execution; 2-task graph then succeeds |
| QLF-05 benchmark | PASS | 20 × 128 tasks; prints `QLF05_BENCH` elapsed/time throughput; no threshold or ranking |

## Local evidence

- Windows 11 x64 / MSVC 19.44, Ninja Debug: CORE-03 **15/15 PASS** (10 JOB + 5 QLF); full CTest **126/126 PASS**.
- WSL Ubuntu 24.04 / GCC 13.3:
  - ASan/UBSan `-O1`: QLF-01..05 **5/5 PASS**, no report.
  - TSan `-O1` with `setarch -R`: QLF-01..05 **5/5 PASS**, no report.
- QLF-05 report-only samples: approximately 18k–39k tasks/s depending on sanitizer/host. Not a threshold.

## Contract fidelity

- Uses only public CORE-03 API and C++20 standard library.
- 10,000-task stress exceeds the contract minimum of 10,000 tasks across 100+ jobs.
- Queue overflow is rejected without mutation; recovery uses a fresh executor, not a forbidden restart.
- Invalid graphs execute nothing; cancellation storm leaves zero executed tasks.
- No production change or new scheduler/allocator/technology.

## Security and rollback

No secret, network, filesystem, upload, paid service, dependency or global allocator override. Unmerged: close the branch; `main` untouched. After merge: normal revert PR, never force push.

## Open risks

- Qualification is CI/desktop-headless, not a physical hardware matrix, real game workload or long-duration production soak.
- No p95/p99 threshold, allocator selection, GPU/audio/network or release qualification is claimed.
- CORE-02 remains `NOT_QUALIFIED`; full Q4 remains `BLOCKED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

- `CORE-03-09` `EXECUTOR_READY` → `COMPLETED` with this code PR number.
- Manifest `CORE03_09_COMPLETED_REST_BLOCKED`: **713 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 29 `COMPLETED`, 6 approved gates**.
- `CORE-03-10` remains `PLANNED_BLOCKED`; selector denies every ID; registry byte-identical.

## Exact-head CI

Native run [44962059212](https://github.com/KayzenRoot/stormline/actions/runs/44962059212) on head `614d7219adf25e9737db0bf32ed6ff49d2e05a68`: **SUCCESS**.

- Linux GCC: **125/125** CTest PASS, including 15 CORE-03 tests.
- Linux ASan/UBSan: **125/125** PASS, no sanitizer failure.
- Linux TSan: **15/15** CORE-03 PASS, no TSan report.
- Windows MSVC: **126/126** PASS, including 15 CORE-03 tests.
- macOS AppleClang: **124/124** PASS, including 15 CORE-03 tests.
- Docs Validation [44962059068](https://github.com/KayzenRoot/stormline/actions/runs/44962059068): SUCCESS.
- SonarCloud and Socket Security: SUCCESS.
- Allocator benchmark matrix: 3/3 PASS (isolated, report-only; no allocator selected).

No native PASS is claimed beyond these exact-head run IDs. Full Q4, CORE-02 module completion and release remain outside this evidence.
