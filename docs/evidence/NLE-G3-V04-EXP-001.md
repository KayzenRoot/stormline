# NLE-G3-V04-EXP-001 — experimental Evidence Bundle (in progress)

**Status:** PROPOSED / LOCAL PRE-FLIGHT ONLY. GitHub native CI receipts pending.
**Base SHA:** `dfd3451cdf4cc3793c484656e5a4405e39a985eb` | **Parent WO:** NLE-PRPLAN-CORE-01-01 | **Issue:** #387.
**Exact changed file allowlist:** `experiments/core01-headless/headless_host.hpp`, `headless_host_smoke.cpp`, `CMakeLists.txt`, `.github/workflows/g3-v04-headless-smoke.yml`, this evidence and `docs/work-orders/NLE-G3-V04-EXP-001.md`.

## Observed local, non-GitHub test evidence (2026-11-17)
- Original C++20 standalone state-machine prototype, no product engine interfaces and no third-party code.
- Local compiler GCC 14.2.0; CMake 3.31.6 + Ninja: configure/build PASS; CTest 1/1 PASS.
- Local compiler Clang 17.0.0; CMake 3.31.6 + Ninja: configure/build PASS; CTest 1/1 PASS.
- Each CTest runs 200 start/stop cycles, duplicate-call/invalid transition checks and count assertion. No graphics/audio/display APIs used.
- Local source SHA-256 from tested files: `headless_host.hpp 44253b1a66755bff74a025bda2b279dfdf02bfc0f6ad9f41718e35bd8adecbc8`; `headless_host_smoke.cpp b0777443a2cf31e9e2071261490052dba0da90b6975bed32cd7796c80b32504c`; `CMakeLists.txt 3d2bab99ad01bb98e4bcba66e55f3a07c6686e5e50294fa0994373e0cab16859`.
- Those local compilers are NOT the exact ratified Windows/Linux evaluation candidates. Local tests do NOT satisfy G3 qualification.
- No local test on Windows or macOS. GitHub Windows/Linux/macOS CTest NOT YET VERIFIED; workflow jobs may fail or be blocked.

## Supply chain, rights, and risk
Only standard C++20; no SDL3 or runtime dependency, no vendor assets, no distribution license chosen. Checkout is pinned to known existing SHA; no installer or artifact upload, cache, privileged event, secret injection, or external third-party action. CI uses public standard runners under bounded timeouts. Account billing readback not obtained, so R$0 is an objective rather than a verified financial receipt.

## G3 proof boundaries and open items
This fixture is non-product. At most it may provide partial lifecycle/build observations after exact CI verification; it does not validate target compiler candidates, true OS lifecycle integration, production ABI, SDL3, headless device independence beyond absence of API calls, performance, license notices or final DoD. All original G3 statuses and 80 coding WOs remain unchanged.

## CI and audit
**PENDING:** exact PR head SHA, docs-validation job, native job run IDs/results on the PR, pt-BR objective audit, confirmed cost eligibility, security and possible correction, and optional checkpoint delta. No G3-P full PASS and no merge authorization asserted.
