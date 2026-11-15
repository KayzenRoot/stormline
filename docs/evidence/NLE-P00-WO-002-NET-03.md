# Evidence Bundle — NET-03 Replication & Interest Management Documentary Research

**Created 2026-11-15 | WO NLE-P00-WO-002-NET-03 | [research issue #236](https://github.com/KayzenRoot/stormline/issues/236) | future [coding #64](https://github.com/KayzenRoot/stormline/issues/64) OPEN/BLOCKED.** At initial draft **IN REVIEW, NOT APPROVED**. BASE main `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec` (NET-02 #233/#234/#235 research/checkpoint/closeout approved and read back). 45/80 research documented; 35 pending, 0 engine, 80/80 coding WOs blocked.

## Exactly eight new research Markdown
[Architecture](../architecture/net-03-replication-interest-management.md), [ADR-0049 PROPOSED](../adr/0049-net-03-authorized-per-client-snapshot-delta-interest.md), [technology/license primary source matrix](../research/net-03-replication-technology-license-matrix.md), [typed semantic API](../contracts/net-03-replication-interest-api.md), [128 future scenarios](../testing/net-03-acceptance-matrix.md), [benchmark protocol](../research/net-03-replication-benchmark-protocol.md), [research Work Order](../work-orders/NLE-P00-WO-002-NET-03.md), this Evidence Bundle. Research PR must change no registry/engine/CI/SDK.

## Initial objective proof state
| Evidence gate | At initial drafting |
|---|---|
| Research PR final HEAD and changed files | PENDING |
| Exact final HEAD Docs Validation (Source Pack, links, DAG, registry and Zcode blocked selector) | NOT RUN at creation |
| Objective pt-BR audit and normal squash/main/contract readback | PENDING |
| Separate checkpoint PR with own CI/audit/squash/readback | PENDING |
| 128 `N03-T001..N03-T128` IDs | **FUTURE / NOT EXECUTED, 0/128** |
| Two actual authenticated clients, game server, secure transport, decoder wire | **NOT IMPLEMENTED / NOT EXECUTED** |
| 8/16/32/64 client real test load and percentile stats | **NOT RUN / NOT MEASURED** |
| 2D/3D graphics/native/Web, schema compiler or code | **NOT BUILT / NOT ADOPTED** |
| Source SDK/dependency/license selection | **NONE; NLE-D009 OPEN** |

## Architecture / security / license risks for objective audit
- NET-03 only authorized per-client committed-state network projection, spatial interest, priority, delta/ACK and bounded send; NET-02 authoritative process and input, WORLD-01 ECS, CORE-04 clock, DATA-04 semantic schema and CAS, NET-01 security/transport, GAME-04 game receipts, NET-04 prediction, NET-05 sessions/roles, NET-06 privacy/abuse retain sole ownership. Catalog predecessors **NET-02 DATA-04** both documentary only.
- **Critical risk:** relevance is not permission. Field/entity authorization and role/match epoch must precede shared quantization, delta, cache, compression and packet encode. Never leak owner inventory or hidden player presence; revoked recipient gets no further newly private data and old queue/baseline invalidated. Already disclosed client data cannot be clawed back. Transport ACK not proof decoder applied a baseline. Potential compression length side-channel under chosen text/secret payload. All controls are **design proposals**, not implemented mitigations.
- Official licensing candidates only: Unreal Iris Epic EULA, Unity Netcode Unity package terms, Godot MIT, Valve Source SDK restricted, FlatBuffers Apache-2.0, Protobuf BSD-3-like, LZ4 lib BSD-2 and CLI GPL, zstd dual BSD OR GPL2, EnTT/Flecs MIT, optional OTel Apache2. No imports, exact versions, SDK, code, assets or cloud. ADR-0049 **PROPOSED**, NLE-D009 license **OPEN**.
- P00 documentation risk LOW. Future privacy/authorization, mixed-secret compression, persistence/rollback and hostile packet parsing ELEVATED, serious fail-closed HIGH/CRITICAL and separate approval. No known runtime quality claims, no anti-wallhack proof.
- Rollback at P00 only revert scoped Markdown; no persistent state or runtime migrations.

## Proposed checkpoint delta, not promoted before independent audit
Only after research final-HEAD CI/audit/squash/main readback, separate checkpoint PR changes precisely checkpoint, backlog, registry sole **NET-03 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, research Work Order and this Evidence. Expected **46/80 research documented (57.5%), 34 pending, 0 runtime**, ALL **80** coding WOs `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Future coding #64 OPEN/BLOCKED, research #236 CLOSED only after checkpoint actual readback, NET-04 documentary only after final closeout. No Zcode coding permission.

## Audit format
pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with Git BASE/final HEAD, exact changed file list/diff, actual Docs Validation run/job/steps, source/license/visibility proof obligations, 128 FUTURE tests explicitly NOT EXECUTED, benchmarks NOT RUN, risks and proposed versus observed checkpoint and rollback. A "COMPLETED" word is never runtime evidence.


## Research PR #237 objectively approved/merged and checkpoint delta proposed
- Research [PR #237](https://github.com/KayzenRoot/stormline/pull/237) BASE `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec`, final HEAD `fa878757a0134e3ec6513dd3e63d122e6c59a70a`, exactly 8 NEW Markdown docs (509 additions, zero deletions), [Docs Validation #43714176703](https://github.com/KayzenRoot/stormline/actions/runs/43714176703) **SUCCESS** job #132812021247 (Source Pack/links, module DAG, registry, blocked Zcode selector), [pt-BR objective audit #6894352265](https://github.com/KayzenRoot/stormline/pull/237#issuecomment-6894352265) **APPROVED documentary-only**, normal squash/main/PR/contract readback `fdd9ab7474b50aac8adfae3dd649cd6437959530`. N03-T001..N03-T128 exactly 128 unique IDs verified, all FUTURE/NOT EXECUTED, no replicator or measured 8/16/32/64 clients.
- Independent checkpoint PR BASE `fdd9ab7474b50aac8adfae3dd649cd6437959530`, exactly five docs/registry files, registry sole NET-03 research_status transition. Expected **46/80 researched (57.5%), 34 pending, zero runtime**, ALL 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED. Coding #64 OPEN/BLOCKED, ADR-0049 PROPOSED, code license OPEN. Checkpoint own exact-final-HEAD CI, objective audit, squash, main/registry readback **PENDING at creation**, issue #236 remains OPEN until that proof. No code or third-party libraries imported.


## NET-03 checkpoint PR #238 independently audited, merged, and read back (historical closeout)
- Research [PR #237](https://github.com/KayzenRoot/stormline/pull/237) final audited HEAD `fa878757a0134e3ec6513dd3e63d122e6c59a70a`, [Docs Validation #43714176703](https://github.com/KayzenRoot/stormline/actions/runs/43714176703) SUCCESS job #132812021247, [pt-BR audit #6894352265](https://github.com/KayzenRoot/stormline/pull/237#issuecomment-6894352265) APPROVED documentary-only, normal squash/readback `fdd9ab7474b50aac8adfae3dd649cd6437959530`.
- Independent checkpoint [PR #238](https://github.com/KayzenRoot/stormline/pull/238), final audited HEAD `55a6e5b9eaf0f3d090527fc6a476790668a48c5d`, [Docs Validation #43714473858](https://github.com/KayzenRoot/stormline/actions/runs/43714473858) **SUCCESS** job #132812905544 (Source Pack local links, DAG, registry and blocked Zcode selector), [objective pt-BR audit #6894387542](https://github.com/KayzenRoot/stormline/pull/238#issuecomment-6894387542) **APPROVED documentary-only**, normal squash main `8e583aca41708eabcdd80323f0dda44918975eb7`, [actual readback #6894396288](https://github.com/KayzenRoot/stormline/pull/238#issuecomment-6894396288) PR/main/registry verified. Research #236 CLOSED after this proof, future code #64 OPEN/BLOCKED.
- Final registry **46/80 research documented (57.5%), 34 pending, zero runtime**, 80/80 coding WOs blocked, zero executor_ready, zero approved_adr, release class UNDECIDED throughout. ADR-0049 PROPOSED, NLE-D009 OPEN; 128 N03 tests FUTURE/NOT EXECUTED; no real 8/16/32/64 client or codec/security/perf results. This historical closeout touches only four Markdown, NOT registry/source/CI/SDK, and itself requires exact-final-HEAD CI, objective audit, normal squash and readback. Older PENDING text reflects historical drafting state superseded by this factual evidence.
