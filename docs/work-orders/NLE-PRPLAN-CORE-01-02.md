# NLE-PRPLAN-CORE-01-02 — CORE-01 Typed Internal Headless Contract

**Status:** PROPOSED FOR OBJECTIVE AUDIT; NO EXECUTOR CODE ALLOWED BY THIS WO.
**Base SHA:** `13b316153d817b7a49fd1d82ccd7193faa5a50f0`; **previous:** G3-V05 decisions [PR #422](https://github.com/KayzenRoot/stormline/pull/422) MERGED; checkpoint [PR #423](https://github.com/KayzenRoot/stormline/pull/423) MERGED. **Source hierarchy:** Checkpoint > Ledger/approved ADR > Scope > DoD > Architecture > Requirements. **Parent stable WO:** `NLE-PRPLAN-CORE-01-01`. **Next code packet:** `NLE-PRPLAN-CORE-01-03`; **module issue:** #18 (still BLOCKED).

## OBJECTIVE
Define a complete, small executable-quality contract for CPU-only/headless internal C++20 host, to remove G4/G5 architectural ambiguity before any code module activation.

## CONTEXT
Owner explicitly ratified only internal headless direction, future MANDATORY_1_0 objective and STANDARD first-slice risk. [PR #421](https://github.com/KayzenRoot/stormline/pull/421) Draft fixture built/tested 3/3 Windows/Linux/macOS in standard hosted CI; not the exact G3-V01 candidate set nor a real engine host. CORE-01 has zero formal predecessor modules. G1 partial; G2 CLEARED only by ruleset 27393227; G3 NOT_CLEARED globally, ADR-0003/0075 PROPOSED.

## SCOPE
A proposed internal contract (states, errors, RAII, lifecycle rollback, test seams, supported/unsupported boundaries), bounded ADR-0083, exact planned code path allowlist, reproducible CMake/CTest proof plan and per-slice risk evaluation. Formalize gate evidence G4/G5 without touching implementation.

## OUT OF SCOPE
Product code; code PR -03, SDL3 integration, window/input, public C ABI or plugin ABI, adopting global SDK/toolchain, paid CI/tools, new external dependencies, source license, enabling 80 WOs, unblocking CORE-01 #18, modifying registry/manifest/validators or making a release.

## FILES/SOURCES TO READ
`AGENTS.md`; `docs/11-checkpoint.md`; `docs/10-decisions-ledger.md`; `docs/03-scope.md`; `docs/09-definition-of-done.md`; `docs/04-architecture.md`; `docs/02-requirements.md`; `docs/adr/0003-core-01-platform-technology.md`; `docs/adr/0075-qa-01-ci-matrix-security-policy.md`; `docs/engineering/core-01-01-qualification-gates.md`; `docs/queue/work-orders/CORE-01.md`; `docs/pr-plans/CORE-01.md`; `docs/contracts/core-01-internal-headless-v0.md` and PR #421 evidence/CI.

## REQUIREMENTS
GOV-001..005; CAP-010, CAP-014, CAP-016 target; NFR-002/003/005; owner-ratified C01-G3V05-01..06. C01-Q005/Q006/Q007/Q008 and Q021..Q024 are **future product proofs**, not passed by PR #421.

## ARCHITECTURE RULES
C++20 standard library only, narrow internal ownership, typed errors, no public ABI/platform-specific or SDL pointers, no GPU/display/audio dependence, no singleton, no implicit telemetry or privilege, explicit rollback. Startup/cleanup failure is observable; failed state prohibits new initialization until safe cleanup.

## CONSTRAINTS
Risk STANDARD for internal first slice only; no external costs, no new binaries/vendor assets, no paid runner/secret or production deployment. G3 global remains NOT_CLEARED; provisional compiler matrix is not support/release qualification. G2 ruleset intact. Do not widen dependency graph. All existing 80 module work orders and 748 planned packages remain blocked throughout this PR.

## ACCEPTANCE CRITERIA
1. Exact typed API name/ownership, state/error transition table and failure recovery modes documented.
2. Test IDs C01-INT-01..10 have objective future oracles, real preinstalled runner/toolchain evidence scopes and honest unavailable labels.
3. Exact eight-file proposed -03 allowlist, build command pattern, rollback, risk and security requirements; separate gate G6 approval remains required.
4. Bounded ADR-0083 does not approve ADR-0003/0075 integral, global G3 or NLE-D009; consent evidence traceable to owner chat.
5. No changes to engine code, registry/manifest, workflows, ruleset or other module files.
6. Exact HEAD Docs Validation PASS and objective pt-BR audit, no HIGH/CRITICAL identified in this documentary scope; squash and main readback only if APPROVED. After merge create checkpoint delta only if genuinely needed and do not promote executor by inference.

## TESTS
Now: GitHub Docs Validation (Source Pack links, catalog, registry, blocked selector, PR plans/skills) at exact HEAD. No native test on this PR. Historical fixture in PR #421: Windows MSVC14.51, Linux GCC13.3, macOS AppleClang17 each 1/1 CTest PASS, no engine test. Future -03: run configured CMake Presets/CTest 200 cycles and fault tests on each approved provisional runner; Linux sanitizers if available; track actual results and failures.

## DELIVERABLES
This Work Order; contract; bounded ADR-0083; proposed Evidence Bundle; minimum Ledger/G4/G5 gate record, docs CI and audit; checkpoint delta PROPOSED only. No code.

## REVIEW FORMAT
Portuguese (Brazil): source SHA/fingerprints, six-file diff, contract invariants/negative tests/risk, licensing and G3 limitations, CI receipts, risks, verdict APPROVED DOCUMENTARY ONLY / CORRECTION REQUIRED / BLOCKED; don't claim independent human audit.

## STOP CONDITION
Stale sources, missing owner scope, new global ADR claim, erroneous test PASS, missing typed API/error transition, risky external deployment, new cost/dependency, registry/manifest/validator changes, failed CI, HIGH/CRITICAL, premature code -03 or merge bypass. G6 never implicit.

## CONTEXT LOCK
Base HEAD `13b316153d817b7a49fd1d82ccd7193faa5a50f0`. Critical Git blob SHA-1 from readback: checkpoint `71a2f7731c6ff40852a43cc94805d95a5650b630`; Ledger `397dc41607ce9e69e74d4fbeeb15eb683548056e`; Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`; DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; ADR-0003 `50d028c7a28acc25164256c5f4547c14ac7192d4`; registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`; manifest `95782386c59e5af8ac1a8c92a7a35c87992463db`. These are Git blob SHA-1, NOT raw SHA-256; future executor must compute actual SHA-256 at activation. Any source drift => STALE/rebase and re-audit.

## CHECKPOINT DELTA PROPOSED
After verified merge of -02, document only contract review and bounded ADR-0083, G4/G5 limited status and G6 pending. Do not mark G3 global cleared, code implemented, other 79 WOs released, or any full product DoD satisfied.
