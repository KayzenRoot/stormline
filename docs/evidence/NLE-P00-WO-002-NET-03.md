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
