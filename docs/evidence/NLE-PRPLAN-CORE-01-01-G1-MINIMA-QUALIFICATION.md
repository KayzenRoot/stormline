# NLE-PRPLAN-CORE-01-01 — Evidence / G1 minimum support and 1.0 acceptance qualification

**Stable WO:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md). **Owner decision issue:** [#387](https://github.com/KayzenRoot/stormline/issues/387). **STATUS:** `RESEARCH_PROPOSAL_NOT_RATIFIED` (2026-11-16). Decision menu: [G1 minima dossier](../research/core-01-01-g1-minima-qualification.md). No new owner signature or ratification.

## Source Check and CONTEXT LOCK
- **Git main BASE:** `06edd79c9627fac0eb94d4d85130e09bc6034fa6`, verified via GitHub branch main.
- Previous main factual checkpoint [PR #389](https://github.com/KayzenRoot/stormline/pull/389) merged; owner G1 ratification [PR #388](https://github.com/KayzenRoot/stormline/pull/388) merged. C01-D01/D08/D09/D14 are `OWNER_RATIFIED_G1_BOUNDED`, eleven other C01-Dxx `AWAITING_OWNER`.
- **Critical Git blob IDs**, Git SHA-1 object fingerprints **NOT raw SHA-256**:
  - `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
  - `docs/11-checkpoint.md`: `18c6f0ddf36b02104a303400ff1c565853a37ace`
  - `docs/10-decisions-ledger.md`: `7194a7e0d122b3f0f4d20c4707f8b83728958e02`
  - `docs/03-scope.md`: `b7597e900116b0594dd2c87fffe93fe3a1f9e2ce`
  - `docs/09-definition-of-done.md`: `5514e876b09973054db4c3b8a031ba34b5fc9222`
  - `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
  - `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
  - `docs/05-security.md`: `eaa02b711f62498e41c82b6cb6615a94c375881c`
  - `docs/06-test-benchmark-plan.md`: `4c0be969744af6dd747cc828fbacc58662b06f40`
  - `docs/07-deployment.md`: `23d851be6a55826de269b3141109a772935a9f2d`
  - `docs/research/core-01-01-owner-technical-decision-dossier.md`: `c65183ae9c348d4d35ef947550c1a67f4ebe0846`
  - `docs/engineering/core-01-01-qualification-gates.md`: `46f0e7f4e6583654d574e14fb53ec25d9ba11fd6`
  - `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`: `72d0661f9d354a84733d991afc60cdee94d56fca`
  - `docs/pr-plans/CORE-01.md`: `83c99b434fcca508913de2ddef5386a430065048`
  - `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`
  - `docs/queue/implementation-registry.json`: `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
  - `docs/pr-plans/manifest.json`: `95782386c59e5af8ac1a8c92a7a35c87992463db`
  - `.github/workflows/docs.yml`: `c9d7b6688ed9484ecaf9968c9134bfaa70f73dc1`
- If main or any critical source changes before authoritative owner ratification/write, mark `STALE`, rebase the work and recompute raw file SHA-256 (Git blob hashes are for object identity, not raw SHA-256).

## Source findings and alternatives
| Requirement | Grounded public source | Status |
|---|---|---|
| Windows client floor | [Microsoft lifecycle](https://learn.microsoft.com/en-us/lifecycle/products/windows-11-home-and-pro); 24H2 Home/Pro ended Oct 2026, 25H2 supported to Oct 2027, 26H2 to Oct 2028 | Fact about external platform, **not chosen** as Stormline target |
| Windows CPU | [Windows 11 25H2 supported processor list](https://learn.microsoft.com/en-us/windows-hardware/design/minimum/supported/windows-11-25h2-supported-intel-processors) | Verify actual machine vendor OS support, don't substitute generic ISA list |
| Linux | [Ubuntu official release cycle](https://ubuntu.com/about/release-cycle) 24.04 standard until May 2029; [official packages](https://packages.ubuntu.com/search?keywords=glibc) glibc 2.39 for noble | Ubuntu 24.04 proposed; no broad distro/glibc ABI guarantee |
| macOS | [Apple Xcode requirements](https://developer.apple.com/xcode/system-requirements), [Tahoe devices](https://support.apple.com/pt-br/122867) | macOS 15 runtime candidate differs from Xcode 26 host min, Mac Intel conditional |
| Free runner candidates | [runner images maintained by GitHub](https://github.com/actions/runner-images/blob/main/README.md) | Future compile runners not native host tests, availability/cost must be verified at use |
| Release and acceptance | [Stormline Scope](../03-scope.md), [DoD](../09-definition-of-done.md), [Global gates](../engineering/p00-technical-approval-gates.md) | G1 partial; eight proposal subquestions all AWAITING_OWNER |

## Negative and conflict audit
- Original [Ledger](../10-decisions-ledger.md) ratifies **exactly four** earlier owner decisions; G1-M01..M08 have **NO OWNER RATIFICATION**, no implicit version/risk/release-class approval.
- Proposing Windows 11 25H2, Ubuntu 24.04, macOS 15 **does not revoke** mandatory Windows/Linux/macOS desktop; Web stays PLAT-03; 2D/2.5D/3D product scope and no public MVP remain binding.
- Linux/Windows/Mac host R$0 build CI is a **future candidate**, with no real release, hardware tests or native CI in repository.
- `main.protected=false`; GET /rulesets previously empty; protected details inaccessible via integration. G2 remains NOT VERIFIED and no change in this increment.
- ADR-0003 and 0075 PROPOSED, NLE-D009 license OPEN, NLE-D010 brand OPEN. 80 research documented, **80/80 implementation WOs BLOCKED**, 0 approved_adr, 0 executor_ready, 80 `UNDECIDED` release classes, 80 `UNCLASSIFIED` risks, `engine_implemented=false`. CORE-01-01/02 both `PLANNED_BLOCKED`, 748 proposed packets unchanged.
- Thirty samples support descriptive p50/p95, not statistically reliable high-quantile certification. Future 200/100 cycles are not evidence until actually executed; C01-Q001..Q032 `FUTURE_NOT_EXECUTED`.

## Files, tests and audit boundary
**Diff allowed:** exactly TWO new Markdown: this Evidence Bundle and [G1 minima dossier](../research/core-01-01-g1-minima-qualification.md). No edits to Checkpoint, Ledger, Scope, DoD, Architecture, Requirements, ADRs, Work Order, registry, manifest, workflow, code, license, branch settings or issue state during this proposal-only PR. Any independent checkpoint after an APPROVED documentary merge must be separately audited and must **not** record owner choice for G1-M01..08.

**Tests to confirm:** GitHub Docs Validation exact PR-head SUCCESS (Source Pack, links, DAG, registry/blocked selector, Skills/unit, 748 PR plans/unit), objective pt-BR audit, normal squash/main readback. **Native/headless/windowed tests: NOT RUN**. No CI result/PR ID/merge date is asserted until observed; link real evidence in PR discussion and post-merge checkpoint.

**Stop:** main/critical document STALE, new owner choice asserted without explicit statement, unsupported OS floor claimed as certified, unauthorized edits or code, CI failed, high/critical documentary fault, package 02 start or coding WO activation.
