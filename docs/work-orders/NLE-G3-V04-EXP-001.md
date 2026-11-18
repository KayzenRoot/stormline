# NLE-G3-V04-EXP-001 — isolated CORE-01 headless lifecycle candidate

**Status:** DRAFT EXPERIMENT ONLY; NOT MODULE IMPLEMENTATION; DO NOT PROMOTE G3 OR MERGE WITHOUT OBJECTIVE REVIEW.
**Parent WO:** NLE-PRPLAN-CORE-01-01 | **Issue:** #387 | **Base:** `dfd3451cdf4cc3793c484656e5a4405e39a985eb`.
**Owner direction:** 2026-11-17 explicit authorization to start real Stormline construction one module at a time with code PRs, tests and CI, expressly preserving all individual gates and 80 blocked implementation WOs. This PR is a bounded non-product experiment, not an implicit approval of ADR-0003/0075 or a release class.

## OBJECTIVE
Provide a compilable C++20 CPU-only lifecycle candidate and exercise a deterministic 200-cycle headless test with no GUI/audio/device requirement, as evidence for future CORE-01 decisions.

## CONTEXT
The canonical checkpoint, Ledger, Scope, DoD, Architecture and Requirements remain superior sources. G1 partially ratified, G2 active only for main/docs-validation, G3 not technically cleared; CORE-01's 16 implementation packet entries and all 80 WOs remain blocked.

## SCOPE
Only an isolated original C++20 two-state headless prototype, its CMake build, a one-CTest exercise, and a tightly scoped read-only checkout/standard-runner PR CI. It is under `experiments/`, not product `src/`.

## OUT OF SCOPE
Engine module activation, API/ABI contract, SDL3, window/input, resource ownership, graphics, audio, networking, full SDK/MSVC/GCC/Clang version qualification, sanitizer/hardware certification, release, deployment, installers, paid services, artifact/cache upload, ADR acceptance and gate promotion.

## FILES/SOURCES TO READ
`AGENTS.md`, `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md`, ADR-0003/0075, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `docs/engineering/core-01-01-qualification-gates.md`, `docs/queue/work-orders/CORE-01.md`, existing G3-V02 evidence.

## REQUIREMENTS
Standard C++20 only; startup/shutdown state transitions, typed errors, observable duplicate-start/stop behavior, 200 deterministic cycles, nonzero exit on failure. No silent compiler fallback counted as G3-P PASS.

## ARCHITECTURE RULES
Original experimental namespace only; no vendor API leakage, no product ABI, no cross-thread assumptions, no GPU/display/audio requirements.

## CONSTRAINTS
No install, no downloading toolchains/dependencies, no secrets, no writable GitHub tokens, no changing G2/ruleset, registry/manifest, ADRs or 80 blocked WOs. Standard public hosted runners, 8 minute timeout per job, cost goal R$0; account-specific billing not verified. Proposed risk ELEVATED only for this experimental CI, never auto-applied to module WOs. Changes limited to this WO, evidence, workflow and three experiment files.

## ACCEPTANCE CRITERIA
Only if C++20 compile/link and CTest genuinely run, label that precise OS/compiler as EXPERIMENTAL_SMOKE_PASS, not CORE-01 release support. Report per-OS failures honestly. A green docs-validation alone does not pass the native test.

## TESTS
Local preliminary: CMake 3.31.6/Ninja, GCC 14.2.0 and Clang 17.0.0, each 1/1 CTest PASS, 200 cycles per run. GitHub Actions on Ubuntu/Windows/macOS is pending until this PR runs. None of these compilers are the exact G3-V01 Windows/Linux candidates.

## DELIVERABLES
Minimal code, CMake/CTest, PR-only CI, this WO, factual evidence record and proposed checkpoint delta (no promotion).

## REVIEW FORMAT
Objective pt-BR, base/head and file allowlist, native job/result receipts, build security and license/cost limits, regressions and APPROVED EXPERIMENTAL ONLY / CORRECTION REQUIRED / BLOCKED. Do not merge while risk, CI or owner scope remain unresolved.

## STOP CONDITION
Unapproved toolchain, download/installation, paid job, CI failure, stale context, HIGH/CRITICAL, unauthorized changes, any attempt to release CORE-01 or unblock 80 WOs. When uncertain, leave PR DRAFT.
