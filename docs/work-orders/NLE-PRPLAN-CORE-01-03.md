# NLE-PRPLAN-CORE-01-03 — CORE-01 INTERNAL_ONLY C++20 CPU-only headless harness

**STATUS: COMPLETED — implemented and merged via [PR #428](https://github.com/KayzenRoot/stormline/pull/428), merge `afdd4ec1ab28eea85c16e459e2f412d5089dcd76`. This packet must not be re-executed; no next packet or module is authorized.**

**Gate:** G6 ONLY for this packet, conditional on the gate PR audit/merge and executor fresh Source Check. **Formal predecessor:** approved NLE-PRPLAN-CORE-01-02 [PR #424](https://github.com/KayzenRoot/stormline/pull/424); G1/G3/G4/G5 bounded as recorded in Ledger and ADR-0083. **Issue:** #18. **G6 baseline main before activation:** `c355de53bca5be1d64dedb4d7111bd40c8859e83`; new executor must confirm latest main and raw SHA-256 of canonical sources before code. All module-level 80 WOs including CORE-01 remain blocked; only this packet may become individually ready.

## OBJECTIVE
Produce first real Stormline code: internal C++20 CPU-only headless host with typed lifecycle/error states, resource ownership and deterministic startup/shutdown/failure cleanup, with CI on Windows/Linux/macOS.

## CONTEXT
Owner ratified narrow INTERNAL_ONLY scope + STANDARD risk, future CORE-01 MANDATORY_1_0 goal; no SDL3, public SDK, window, GPU, audio, persistence, network. [PR #421](https://github.com/KayzenRoot/stormline/pull/421) remains experimental fixture, 3/3 PASS but not real host. Architecture [ADR-0083](../adr/0083-core-01-internal-headless-slice.md) bounded, [contract v0](../contracts/core-01-internal-headless-v0.md).

## SCOPE
Implement internal HostConfig/HostState/HostError/HeadlessHost from contract, single-thread ownership, RAII, rollback/idempotent stop, fixture/failure injection, CMake Presets and CTest, constrained native CI plus evidence and tests.

## OUT OF SCOPE
Full CORE-01 (windows/event queue/path/full error model in later slices), SDL3/linking, window/input, renderer/RHI, audio, threading/job system, plugin C ABI, public API, web, distribution and release license, paid services, code changes to unrelated modules.

## FILES / SOURCES TO READ
`AGENTS.md`, `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `docs/engineering/core-01-01-qualification-gates.md`, `docs/adr/0003-core-01-platform-technology.md`, `docs/adr/0083-core-01-internal-headless-slice.md`, `docs/contracts/core-01-internal-headless-v0.md`, `docs/queue/packet-activations.json`, `docs/pr-plans/manifest.json`, `docs/pr-plans/CORE-01.md`, `docs/queue/implementation-registry.json` and PR #421 actual CMake source/evidence. Inspect Git before any edit.

## REQUIREMENTS
GOV-001..005, CAP-010/014, NFR-002/003/005 and owner C01-G3V05-01..06, only C01-INT-01..10 test obligations. Same exact stable packet ID in branch, PR and evidence.

## ARCHITECTURE RULES
Single-thread internal API; stdlib C++20 only, no vendor/public ABI, typed errors and state transitions, no-throw cleanup and injection test seam limited internally. Do not move/clone experimental code blindly; inspect/decompose based on contract.

## CONSTRAINTS
STANDARD risk only first internal slice: unit/integration, compile warnings/errors, error-path tests and regression across three standard public CI hosts. CI read-only checkout SHA pinned, no secrets/install/download/cache/upload/paid runners. No changes to original 80 module registry/selector or G2 ruleset. G3 global NOT_CLEARED, ADR-0003/0075 PROPOSED integral, NLE-D009 OPEN. No automatic next code packet.

## ACCEPTANCE CRITERIA
- Exact file allowlist, Source Check fresh, G6 packet selector outputs executor_ready true ONLY for -03; module selector `select_wo.py CORE-01` still BLOCKED.
- HeadlessHost contract state table and errors implemented, single-owner, no window/display/GPU/audio APIs; failure injection verifies rollback and cleanup paths.
- Future product C01-INT-01..10: 200/200 lifecycle cycles per OS, duplicate start, idempotent stop, invalid config rejection, every init/cleanup failure injected, destructor cleanup, separate resources count, negative/invalid transitions and no unexpected process side effects.
- CMake Presets schema6, min3.27, ninja, compile C++20 and CTest >=1 test per Windows/Linux/macOS; zero-test failure; warnings as errors; Linux sanitizers when preinstalled/supportable, otherwise marked NOT_QUALIFIED. Capture compiler version, image, architecture, CTest logs and SHA.
- No HIGH/CRITICAL known issue; CI Docs Validation + native jobs PASS at exact PR HEAD; objective pt-BR audit and correction in same PR if required. No prod release/ABI, no automatic G3 claim.

## TESTS
`python3 scripts/validate_docs.py`; `python3 scripts/validate_wo_registry.py`; `python3 scripts/validate_pr_plans.py`; `python3 -m unittest discover -s scripts -p test_validate_pr_plans.py`; `python3 scripts/select_packet.py NLE-PRPLAN-CORE-01-03 --json` (expects 0); `python3 scripts/select_wo.py CORE-01 --json` (expects 2) and selector for CORE-02-03 (expects 2). Native future: `cmake --preset core01-internal-debug`; `cmake --build --preset core01-internal-debug`; `ctest --preset core01-internal-debug --output-on-failure --no-tests=error` on Windows/Linux/macOS. These are **NOT YET EXECUTED** and must not be claimed PASS by gate PR.

## DELIVERABLES
8-file code allowlist from contract: `src/stormline/core/internal/headless_host.hpp`, `src/stormline/core/internal/headless_host.cpp`, `tests/core/headless_host_tests.cpp`, `CMakeLists.txt`, `CMakePresets.json`, `.github/workflows/core01-internal-headless.yml`, `docs/work-orders/NLE-PRPLAN-CORE-01-03.md` (already present, update only if necessary) and `docs/evidence/NLE-PRPLAN-CORE-01-03.md`. GitHub PR, actual native CI log IDs, Evidence Bundle, objective pt-BR audit and proposed checkpoint.

## REVIEW FORMAT
Portuguese Brazil, severity, base/head/context fingerprints, exact file list, unit/native matrix + sanitizer, risk/recovery/license/credentials, no high/critical, APPROVED / CORRECTION REQUIRED / BLOCKED. PR must remain DRAFT while checks or evidence absent. Squash merge only after approved, with main readback and independent checkpoint decision.

## STOP CONDITION
STALE HEAD/source, packet selector blocked, negative validator failing, unauthorized prerequisite/ADR, paid tool, unreviewed dependency, CI red, no approved risk/contract, high/critical, future patch not within exact allowlist, attempt to alter other 747 packets/79 modules or publish build. Never bypass ruleset or force push.

## CONTEXT LOCK
Gate baseline `c355de53bca5be1d64dedb4d7111bd40c8859e83`; reference blobs in `docs/queue/packet-activations.json` are Git blob SHA-1 historical only; executor MUST calculate fresh source SHA-256 after G6 merge, and stop/rebase on change.

## EVIDENCE BUNDLE
Pending separate code PR -03 with actual builds/tests. G6 gate approval evidence must never masquerade as implemented engine code or native tests.

