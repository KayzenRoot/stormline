# Evidence Bundle — NET-04 Prediction, Reconciliation & Lag Research

**2026-11-15 | Research [#240](https://github.com/KayzenRoot/stormline/issues/240) | Work Order NLE-P00-WO-002-NET-04 | future code [#65](https://github.com/KayzenRoot/stormline/issues/65) OPEN/BLOCKED.** Initial phase RESEARCH IN REVIEW / NOT OWNER-APPROVED / NOT IMPLEMENTED. BASE main `6701b8f6e99654112a6bf792c8b33d565ad71b42` after NET-03 #237/#238/#239 validated/audited/normal squash/readback. **46/80 research documented, 34 pending, 0 engine, all 80 coding WOs blocked**. Git blob base/context lock in research Work Order.

## Exactly eight NEW Markdown
[Architecture](../architecture/net-04-prediction-reconciliation-lag.md), [ADR-0050 PROPOSED](../adr/0050-net-04-bounded-client-prediction-authoritative-reconciliation.md), [Technology/license matrix](../research/net-04-prediction-technology-license-matrix.md), [Typed semantic API](../contracts/net-04-prediction-reconciliation-api.md), [128 FUTURE tests](../testing/net-04-acceptance-matrix.md), [Benchmark protocol](../research/net-04-prediction-benchmark-protocol.md), [Research WO](../work-orders/NLE-P00-WO-002-NET-04.md), this Evidence Bundle. Research PR must not change implementation registry/source/CI/package metadata.

## Evidence status at initial drafting
| Obligation | At creation |
|---|---|
| Research PR final HEAD/changed file readback | PENDING, verify exact eight NEW Markdown |
| Research exact-final-HEAD Docs Validation Source Pack/links/DAG/registry/blocked selector | NOT RUN at creation |
| Research objective pt-BR audit and ordinary squash/main readback | PENDING |
| Separate checkpoint PR with own final-HEAD CI/audit/squash/readback | PENDING |
| 128 cases N04-T001..N04-T128 | FUTURE/NOT EXECUTED (zero runtime passes/fails) |
| Native game client/headless authoritative server/SIM-03 replay | NOT BUILT, NOT IMPLEMENTED |
| Clock sync/interpolation/lag/hit fairness correctness and negative cheat tests | NOT EXECUTED |
| CPU resimulation p50/p95/p99 and input-to-display correction metrics | NOT MEASURED |
| Source SDK or library/toolchain code/benchmark/cloud installation | NONE; NLE-D009 license OPEN |

## Architectural proof obligations, threat model and rights
- NET-04 owns local client **disposable bounded** prediction+input ring/reconciliation/interpolation/smoothing and optional server-side **read-only**, narrowly scoped lag-comp hitbox history if separately approved. Formal catalog predecessors NET-03 and SIM-03 documentary only. NET-01 transport/TLS/RTT, NET-02 authoritative game+actor validation, NET-03 authorized snapshots+baseline, NET-05 session, NET-06 abuse, CORE-04 tick/CORE-03 scheduler, SIM-03 motor/physics, GAME-04 damage/inventory/loot/quests and DATA-04 durable source/save remain distinct. No source/runtime actual interfaces implemented.
- Threats: client forged hit/time/delay/epoch, rewind-window abuse and peeker advantage, attacker-generated packet/input flood, sim desync/collision cohort mismatch and float FP drift, infinite resim CPU, duplicate game effects/rewards after replay, predicted spawn incorrect identity, private/hide entity leak on visibility revocation, tampered profile/MCP live rewind. Controls are **documented responsibilities, NOT implemented mitigations**. Research docs LOW risk, future net/fairness ELEVATED, privileged irreversible/economy HIGH_ASSURANCE.
- Upstream comparison only: Unity Netcode package/Unity terms (NOT automatic MIT), Unreal EULA, Valve Source SDK 2013 restrictive non-MIT, Godot MIT, independently authored Gaffer articles (not implementation license), optional Google Benchmark Apache2, Catch2 BSL-1.0/GoogleTest BSD3 after exact pin. No source, SDK, assets or code copied or approved; engine license NLE-D009 OPEN, ADR-0050 PROPOSED. No guaranteed Web, OS, cross-CPU bit-determinism or p99.
- Initial rollback is simple revert of scoped docs; no changing game data, remote infrastructure, compiler or runtime binaries.

## Proposed checkpoint delta (not promoted until separate objective gates)
After research PR exact-final-HEAD Docs Validation/objective audit/normal squash/actual readback, update exactly checkpoint, backlog, registry **sole NET-04 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, NET-04 research Work Order and this Evidence Bundle in separate PR with own CI/audit/squash/readback. Expected **47/80 research (58.75%), 33 pending, zero runtime**; all **80** code WOs `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`; coding #65 OPEN/BLOCKED, research #240 close ONLY after checkpoint main readback. Optional four-file historical closeout with own CI/audit/readback. No Zcode unlock, no next NET-05 before completed final readback.

## Objective review format
Pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED, exact BASE and HEAD and Git blob context, diff file list, CI run/job steps (or explicit NOT RUN), 128 future tests NOT EXECUTED, security/anti-cheat and copyright/rights caveats, no invented benchmark/perf, risk severity, rollback and factual Checkpoint Delta after CI+merge.


## Observed research PR #241 and separate checkpoint proposal
- [Research PR #241](https://github.com/KayzenRoot/stormline/pull/241), BASE `6701b8f6e99654112a6bf792c8b33d565ad71b42`, audited final HEAD `7ae14978fb71dcf6809b608f493276be214655fb`, exactly eight NEW Markdown (506 adds, 0 deletes), [Docs Validation #43715830922](https://github.com/KayzenRoot/stormline/actions/runs/43715830922) **SUCCESS** job #132817045630 all Source Pack/local links/DAG/registry/Zcode blocked selector SUCCESS, [pt-BR objective audit #6894577101](https://github.com/KayzenRoot/stormline/pull/241#issuecomment-6894577101) **APPROVED documentary-only**, normal squash main `2cc7228cffe56d2e73d26e9af78ed998127a1366` and main/PR/contract readback. 128 N04-T001..128 unique specified **FUTURE/NOT EXECUTED**; no runtime/build/security/fairness/bench proof.
- This independent checkpoint PR base `2cc7228cffe56d2e73d26e9af78ed998127a1366` changes exactly five files checkpoint/backlog/registry/research WO/Evidence and **only NET-04 research_status** field. Proposed **47/80 researched (58.75%), 33 pending, zero executable engine**, all 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED. Coding #65 OPEN/BLOCKED, research #240 OPEN until checkpoint readback, ADR-0050 PROPOSED, NLE-D009 OPEN. Own exact-final-HEAD Docs Validation/audit/squash/main readback PENDING at writing. No code/library/cloud adoption.
