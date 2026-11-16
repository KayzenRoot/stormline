# NLE-PRPLAN-CORE-01-01 — G1 Owner Ratification Evidence Bundle

**Work Order:** `NLE-PRPLAN-CORE-01-01`. **Status:** FOUR OWNER-RATIFIED BOUNDED G1 DECISIONS, G1 NOT CLEARED. **Date:** 2026-11-16. [Decision issue #387](https://github.com/KayzenRoot/stormline/issues/387). Prior qualification [PR #385](https://github.com/KayzenRoot/stormline/pull/385) and its independent checkpoint [PR #386](https://github.com/KayzenRoot/stormline/pull/386) were DOCUMENTARY-ONLY approvals.

## Owner authority, exact boundary
Direct owner declaration in this conversation: **“Como proprietário do Stormline, RATIFICO EXPRESSAMENTE, sem modificações, as recomendações C01-D01, C01-D08, C01-D09 e C01-D14 apresentadas para o Gate G1, incluindo os limites e obrigações de prova descritos.”** This file is an assistant-authored faithful transcription, **not an independent GitHub signature**. No owner authorization of C01-D02..D07/D10..D13/D15, ADR-0003, GitHub settings, paid services, engine license, code or packet 02.

## Source Check / Context Lock
- Exact base Git commit on `main`: `7b555067c8f7f8e7770b60cbab53e139d19bf132`. Every fingerprint below is a **Git blob SHA-1 object ID**, not a raw SHA-256 digest; a future executor must generate fresh raw SHA-256 values and recheck a fresh main HEAD.
- `docs/11-checkpoint.md`: `28dfe1dff20e66f940ed2cd36060aa661c4c0b27`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/adr/0003-core-01-platform-technology.md`: `2ee92dda5ab81ddcc446b9d5325d29257350e217`
- `docs/research/core-01-01-owner-technical-decision-dossier.md`: `3bd753d05742642f987c4ee1b42d31c9b9a16546`
- `docs/engineering/core-01-01-qualification-gates.md`: `1dfdd57b9d842589d3c1dbc87d731c80d15d9abc`
- `docs/work-orders/NLE-PRPLAN-CORE-01-01.md`: `ce7f174b0ff4e669124a89ca0f3edff1487518a6`
- `docs/queue/implementation-registry.json`: `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`
- `docs/pr-plans/manifest.json`: `95782386c59e5af8ac1a8c92a7a35c87992463db`

## Ratified decision and outstanding proof
| ID | Ratified bounded rule | Objective future proof (NOT RUN) |
|---|---|---|
| C01-D01 | Minimal CORE-01 host mandatory as design intent for 1.0 Editor/client/server/test, optional advanced features separate | Full 1.0 Scope/DoD, min requirements and release-class mapping; registry UNDECIDED |
| C01-D08 | Initial desktop Windows x86_64, Linux x86_64, macOS Apple Silicon arm64; Intel Mac and Win ARM64 conditional, Web separate PLAT-03 | Owner-defined OS/SDK/CRT/glibc floors, physical hardware and native OS qualification |
| C01-D09 | True CPU-only headless; no obligatory window/display/GPU/audio/editor; NET-02 owns dedicated game server | Real no-display CPU-only start/stop, teardown/error/sanitizers, 200 cycles per qualified OS |
| C01-D14 | Future test protocol with 200 headless boots, 100 window cycles/OS, 10k events, 30 cold + 30 warm samples and 32 future test cases | Approve additional thresholds/hardware, reproduce test runs & attach log+SHA; 30 samples do not justify high-confidence p99 |

## Conflict and invariant review
- No direct conflict with approved NLE-D013 no public MVP, NLE-D014 2D/2.5D/3D/Web vision, NLE-D017 Win/Linux/macOS desktop. D08 does not demote the browser target or claim Intel/Win ARM64 certification.
- **G1 PARTIALLY_RATIFIED_NOT_CLEARED:** minimum OS versions, capability exclusions, complete DoD and numeric runtime thresholds remain open. G2 settings NOT VERIFIED: `main.protected=false`, `rulesets=[]`, detailed GET protection HTTP 403. G3 still open.
- Eleven owner decisions `C01-D02..D07/D10..D13/D15` AWAITING_OWNER; ADR-0003/0075 PROPOSED; `NLE-D009` engine license OPEN, `NLE-D010` brand OPEN.
- 80/80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`; 0 executor_ready and 0 approved ADR; all risks UNCLASSIFIED and registry release classes UNDECIDED; `engine_implemented=false`. Manifest CORE-01-01/02 `PLANNED_BLOCKED`, no packet 02 or code.
- 32 C01-Q001..Q032 all `FUTURE_NOT_EXECUTED`, no native/soak/hardware/benchmark/lifecycle tests claimed. The documentary workflow validates Markdown/registry only.

## Documentary PR boundaries and review
Allowed file scope: modify Ledger, Scope, DoD, existing CORE-01 dossier, qualification gates, existing WO (append-only), and ADD this Evidence Bundle. **Forbidden:** editing ADRs, registry, manifest, implementation WO/issue, build/code, license, branch protections or CI configuration.

**Acceptance evidence:** exact PR HEAD GitHub Docs Validation SUCCESS, file diff audit (7 Markdown only), objective pt-BR independent audit in PR discussion, no known HIGH/CRITICAL within documentary change, squash, full main readback and independent checkpoint PR. The **PR discussion and independent checkpoint** are the source for the actual PR number, HEAD, workflow run/job, audit and merge SHA after those events exist; they are not yet asserted at authoring.

**STOP:** stale critical source, missing owner's explicit bounded authorization, file diff outside seven Markdown files, checks FAILED, high/critical known defect, unauthorized promotion of ADR/release/risk/code, or any attempt to start CORE-01-02.

## Actual PR #388 documentary closure (independent checkpoint to follow)
- [PR #388](https://github.com/KayzenRoot/stormline/pull/388), base `7b555067c8f7f8e7770b60cbab53e139d19bf132`, final HEAD `307099f641fb926401224231e64efb000f960de8`; exactly seven Markdown (six MODIFIED + this ADDED), no registry/manifest/ADR/settings/code changes.
- GitHub Actions Docs Validation [run #43872744317](https://github.com/KayzenRoot/stormline/actions/runs/43872744317) SUCCESS, job `docs-validation` #133317854722 (all steps SUCCESS, including blocked Zcode selector). Objective pt-BR documentary-only audit [comment #6917289716](https://github.com/KayzenRoot/stormline/pull/388#issuecomment-6917289716): APPROVED. Normal SQUASH [main commit `fc5706d687e32b9b104e4aec1513edffb5dac8f6`](https://github.com/KayzenRoot/stormline/commit/fc5706d687e32b9b104e4aec1513edffb5dac8f6) read back; 4 bounded owner ratifications and 11 open decisions confirmed.
- **Independent checkpoint PR/CI/audit** remains separate evidence to be recorded in that PR and checkpoint; no result is prematurely claimed here. G1 still NOT CLEARED, G2/G3 open, 80 coding WOs BLOCKED, license NLE-D009 OPEN, engine_implemented=false.
