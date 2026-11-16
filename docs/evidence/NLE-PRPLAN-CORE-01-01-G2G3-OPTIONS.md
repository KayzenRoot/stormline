# NLE-PRPLAN-CORE-01-01 — G2/G3 owner-options Evidence Bundle / Context Lock

**Status: DOCUMENTARY TECHNICAL OPTIONS ONLY, NOT OWNER-RATIFIED.** **Date:** 2026-11-16. **Stable WO:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md). **Issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387). [Technical board and 11 choices](../research/core-01-01-g2-g3-owner-decision-options.md).

## Goal and authority
The owner asked to continue **Source Check and analysis** of the remaining eleven `C01-D02..D07/D10..D13/D15` with best options, alternatives, trade-offs and proof obligations. Owner explicitly did **NOT** ratify these choices, ADR-0003, G2 settings, NLE-D009 license or implementation. The proposed A options do not become approved merely by being documented, discussed, CI-tested or merged. Before a new ratification, owner must explicitly accept/modify/defer **each identified decision**. Four original C01 G1 and eight G1-M decisions remain independently OWNER_RATIFIED_G1_BOUNDED.

## Source Check / Context Lock
- **main exact base SHA:** `2c88ac3ba88c3c0dde639fbf3969c24860c9de3f` (GitHub branch main readback on 2026-11-16).
- **Git blob SHA-1 IDs, not raw-file SHA-256** (individually checked at that base):
  - `docs/11-checkpoint.md`: `e23f86d63d5ee544b85f3731273e8d0e0a26cfe8`
  - `docs/10-decisions-ledger.md`: `ce78ac20f575b1a7ac5111c5ea59126ecb22b09d`
  - `docs/03-scope.md`: `32bce8996dfc5174f70bf54d1c1088347ef6f14d`
  - `docs/09-definition-of-done.md`: `12a5661eaa6e7b73fce1b0c6605598dcf6543ee7`
  - `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
  - `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
  - `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
  - `docs/05-security.md`: `eaa02b711f62498e41c82b6cb6615a94c375881c`
  - `docs/06-test-benchmark-plan.md`: `4c0be969744af6dd747cc828fbacc58662b06f40`
  - `docs/07-deployment.md`: `23d851be6a55826de269b3141109a772935a9f2d`
  - `docs/research/core-01-01-owner-technical-decision-dossier.md`: `c65183ae9c348d4d35ef947550c1a67f4ebe0846`
  - `docs/engineering/core-01-01-qualification-gates.md`: `08b942dca534702673d2048854194acd5d8211e3`
  - `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`: `089a5ce7c92184cae70c3cca12a7e94ca957edbd`
  - `docs/evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-RATIFICATION.md`: `7a91891ea2c6c1a899121003b5aba977b7147a08`
  - `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`
  - `docs/adr/0075-qa-01-ci-matrix-security-policy.md`: `22e91a36c1e0a8121163fa4778abd0489fed86e5`
  - `docs/pr-plans/CORE-01.md`: `83c99b434fcca508913de2ddef5386a430065048`
  - `docs/queue/implementation-registry.json`: `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
  - `docs/pr-plans/manifest.json`: `95782386c59e5af8ac1a8c92a7a35c87992463db`
  - `.github/workflows/docs.yml`: `c9d7b6688ed9484ecaf9968c9134bfaa70f73dc1`
- **Freshness:** if main, checkpoint, Ledger/ADRs, Scope, DoD, Architecture, Requirements or registry/manifest changes, mark this proposal `STALE` and rerun Source Check/rebase. Actual executor must produce raw SHA-256 fingerprints in a future explicit code WO; Git object IDs above cannot be presented as those SHA-256 digests.

## Direct live GitHub evidence for G2 (read-only)
- `GET branches/main` reports **`protected=false`**.
- `GET /repos/KayzenRoot/stormline/rulesets` returned **`[]`**.
- `GET /repos/KayzenRoot/stormline/branches/main/protection` returned **403 Resource not accessible by integration**.
- CI workflow named `Docs Validation` contains a job named **`docs-validation`**, triggered by PR and pushes to main; its existence and passing runs **do not mean the check is required or enforced** for merging.
- Future G2 proposal: require PR and status check by actual name, restrict bypass/force-push/deletion, maintain solo-owner no external review requirement, verify enforcement using appropriate privileges and **negative evidence** of blocked failing merge. **No settings action was taken**; no branch is protected by virtue of this document.

## Verified external technical facts (proposal basis only)
- [Microsoft C++20 flags](https://learn.microsoft.com/en-us/cpp/build/reference/std-specify-language-standard-version): `/std:c++20`, use supported stdlib/compiler combinations; no cross-platform build was run.
- [SDL3 init/threading/refcounts](https://wiki.libsdl.org/SDL3/SDL_InitSubSystem) and [SDL_RunOnMainThread deadlock caution](https://wiki.libsdl.org/SDL3/SDL_RunOnMainThread) and [SDL3 main modes](https://wiki.libsdl.org/SDL3/README-main-functions): inform D03-D04 but do not certify SDL adoption.
- [CMake preset JSON/CTest support](https://cmake.org/cmake/help/v3.27/manual/cmake-presets.7.html): recommend schema/versions only as candidates; no presets created.
- [SDL zlib](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt), [CMake BSD-3-Clause](https://cmake.org/licensing/), [Ninja Apache-2.0](https://github.com/ninja-build/ninja): upstream license sources, need snapshot, pinned release and transitive audit before distribution.
- [GitHub standard public hosted runners](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-syntax) free; [GitHub rulesets](https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-rulesets/available-rules-for-rulesets) and [fork/privileged workflow risks](https://docs.github.com/en/actions/reference/security/securely-using-pull_request_target) for the security proposal. No production-native jobs activated.

## Invariants, negative proof and restrictions
- Exactly **11/11 C01-D02/D03/D04/D05/D06/D07/D10/D11/D12/D13/D15 still `AWAITING_OWNER`**. Twelve bounded G1 decisions (4 original C01 + 8 minima) already ratified; G1 `PARTIALLY_RATIFIED_NOT_CLEARED`.
- G2 `BLOCKED_NOT_VERIFIED`, G3 `OPEN_OWNER_DECISION`; G4-G8 not started/blocked. ADR-0003 and ADR-0075 **PROPOSED**. Engine license `NLE-D009 OPEN`, brand `NLE-D010 OPEN`.
- 80/80 coding Work Orders `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, 0 executor_ready, 0 approved ADR, 80 `release_class=UNDECIDED`, 80 `risk=UNCLASSIFIED`, `engine_implemented=false`. Manifest CORE-01-01 **PLANNED_BLOCKED** despite completed governance subwork; CORE-01-02 **PLANNED_BLOCKED**. Issue #18 remains BLOCKED. No code or packet 02.
- `C01-Q001..Q032 FUTURE_NOT_EXECUTED`; benchmark/risk/native CI/physical tests all **NOT RUN**. Documentation validator is not evidence of C++ ABI/lifecycle/OS support.
- No license selection, changes to `main` settings, CI workflow, code, registry, manifest or ADR.

## Work scope / acceptance / tests and stop
**Exactly two new Markdown files**: [technical options](../research/core-01-01-g2-g3-owner-decision-options.md) and this evidence. No edits to canonical checkpoint, Ledger, Scope/DoD, Architecture/Requirements, ADRs, old dossier, WO, issue state, registry/manifest, CI, license or code in the proposal PR.

**Acceptance:** GitHub diff exactly two ADDED Markdown, Source Pack/link validation, module DAG, registry and Zcode blocked selector, skill/unit, future PR plan registry/unit all SUCCESS at exact PR HEAD; objective pt-BR audit with no known HIGH/CRITICAL within documentary scope, no auto-ratification. Squash/readback and **independent factual checkpoint PR** only if approved and due. Actual PR/head/workflow run IDs are to be recorded once observed in its PR and independent checkpoint, never preclaimed.

**STOP:** any stale critical source, owner selection inferred, G2 protection falsely claimed, failed CI, artifact beyond two Markdown, unauthorized branch protection/ADR/license/queue/code change, high/critical issue or launch of CORE-01-02.

## PR #396 closure: observed after merge, separate checkpoint not preclaimed
- [PR #396](https://github.com/KayzenRoot/stormline/pull/396) BASE `2c88ac3ba88c3c0dde639fbf3969c24860c9de3f`, exact HEAD `1fa4908f744ae9e80bf7429672fa4597e2c886bb`; **exactly 2 ADDED Markdown**, no other file changed.
- Exact-head GitHub Docs Validation [run #43883365084](https://github.com/KayzenRoot/stormline/actions/runs/43883365084) `SUCCESS`, job `docs-validation` **#133354861062**, all steps SUCCESS including Zcode blocked selector. Objective pt-BR [audit #6918861852](https://github.com/KayzenRoot/stormline/pull/396#issuecomment-6918861852) `APPROVED DOCUMENTARY ONLY`. Normal squash [main commit `2f505d213d6eddb32a8ffe8e749c7ee849af5923`](https://github.com/KayzenRoot/stormline/commit/2f505d213d6eddb32a8ffe8e749c7ee849af5923) independently read back from GitHub.
- The checkpoint documenting this status requires its **own PR/CI/audit/squash/readback**; no result is claimed until executed. Eleven C01 decisions remain `AWAITING_OWNER`, 12 earlier bounded G1 ratifications intact, G2 unprotected/unverified, G3 open, all 80 coding WOs BLOCKED, no code/ADR/license change.
