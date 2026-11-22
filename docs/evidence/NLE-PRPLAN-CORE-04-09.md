# NLE-PRPLAN-CORE-04-09 — Integrated time qualification evidence

**Status:** `TEST-ONLY QUALIFICATION / EXACT-HEAD CI GREEN / AUDIT PENDING`. **Base main:** `54a320c` (gate PR #532). **Head:** `37039080c2e0af3cf731b3570f0b4c8b771ed975`. **Packet:** `NLE-PRPLAN-CORE-04-09`. **Risk:** `ELEVATED`. **Release:** `INTERNAL_ONLY`. **Contract:** [core-04-qualification-v0](../contracts/core-04-qualification-v0.md). **WO:** [NLE-PRPLAN-CORE-04-09](../work-orders/NLE-PRPLAN-CORE-04-09.md).

## Scope

Exact allowlist:

1. `tests/core/core04_time_qualification_tests.cpp`
2. `CMakeLists.txt` (additive qualification target/tests)
3. `.github/workflows/core01-internal-headless.yml` (TSan target)
4. `docs/evidence/NLE-PRPLAN-CORE-04-09.md`

No production source, API, dependency, ABI, allocator or release change.

## QLF matrix

| ID | Result | Evidence |
|---|---|---|
| QLF-01 integrated | PASS | 60 Hz 10 s at 30 FPS → 600 ticks + pause + one step + 6 resume ticks = 607; 120 Hz 2× scale at 144 FPS → 2,400 ticks; replay exact/mismatch |
| QLF-02 stress | PASS | five independent 24 h runs at 60 Hz, 1 s pumps → 5,184,000 ticks each (25,920,000 total) |
| QLF-03 recovery | PASS | clock error → Failed; fresh timeline starts; invalid config; debt limit; `start_at(max-1)` → `TickOverflow`; replay mismatch |
| QLF-04 overload | PASS | DropExcess cap 4 with dropped_ns; Carry capped with debt; frame clamp 250→100 ms yields 6 ticks and `clamped=true` |
| QLF-05 benchmark | PASS | 1,000,020 ticks; prints elapsed/throughput; no threshold or ranking |

## Local evidence

- Windows 11 x64 / MSVC 19.44, Ninja Debug: CORE-04 qualification **5/5 PASS**; full CTest **148/148 PASS**.
- WSL Ubuntu 24.04 / GCC 13.3: ASan/UBSan **5/5 PASS**; TSan **5/5 PASS**; no sanitizer report.
- QLF-05 samples: ~68M–193M synthetic ticks/s under sanitizer/host; report-only, not a product metric.

## Contract fidelity

- Uses only public CORE-04 API and standard library.
- Recovery uses fresh timelines; no forbidden restart.
- Drop/carry/clamp and clock errors are typed and bounded.
- No production dependency, public ABI, threshold or release claim.

## Limits

CI/headless qualification only; no physical suspend/resume, platform clock resolution, native comparator or long-duration production soak. CORE-01 not qualified; CORE-02 `NOT_QUALIFIED`; CORE-03 `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`; full Q4 `BLOCKED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`.

## Proposed checkpoint delta

- `CORE-04-09` `EXECUTOR_READY` → `COMPLETED` with this code PR number.
- Manifest `CORE04_09_COMPLETED_REST_BLOCKED`: **703 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 37 `COMPLETED`, 8 approved gates**.
- `CORE-04-10` remains blocked; selector denies all; registry byte-identical.

## Exact-head CI

Native run [44992212838](https://github.com/KayzenRoot/stormline/actions/runs/44992212838) on head `37039080c2e0af3cf731b3570f0b4c8b771ed975`: **SUCCESS**.

- Linux GCC: **147/147** CTest PASS, including 5 CORE-04 qualification tests.
- Linux ASan/UBSan: **147/147** PASS, no sanitizer failure.
- Linux TSan: **37/37** PASS (including 5 CORE-04 qualification tests), no TSan report.
- Windows MSVC: **148/148** PASS, including 5 CORE-04 qualification tests.
- macOS AppleClang: **146/146** PASS, including 5 CORE-04 qualification tests.
- Docs Validation [44992212861](https://github.com/KayzenRoot/stormline/actions/runs/44992212861): SUCCESS.
- SonarCloud and Socket Security: SUCCESS.
- Allocator benchmark matrix: 3/3 PASS (isolated, report-only; no allocator selected).

No native PASS is claimed beyond these exact-head run IDs. Full Q4, physical suspend/resume, CORE-02 module completion and release remain outside this evidence.
