# NLE-P00-WO-002-NET-03 — Replication & Interest Management Research Work Order

**Date:** 2026-11-15 | [research issue #236](https://github.com/KayzenRoot/stormline/issues/236) | future [coding #64](https://github.com/KayzenRoot/stormline/issues/64) OPEN/BLOCKED | **BASE main** `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec` | catalog order 46/80 | risk P00 docs LOW, future gameplay/network-data privacy ELEVATED. This Work Order **does not authorize coding**.

## OBJECTIVE
Research and propose original server-authoritative per-client snapshot, delta, spatial interest, relevance and per-field authorization, priority/fair bandwidth, bounded baseline/ACK/resync, typed quantization/optional compression, reliable lifecycle and loss-tolerant state delivery, cross-OS/Web codec/transport capabilities, data privacy, adversarial threat model, exactly 128 future tests and reproducible 8/16/32/64-client benchmark protocol. Compare contemporary upstream architectures/licensing without copying source, SDK or proprietary engine logic.

## CONTEXT
Stormline P00 documentation only, **no engine, client, server, network stack, test binary or benchmark**. NET-02 research+checkpoint+readback PR #233/#234/#235 completed exact-final-HEAD Docs Validation, pt-BR audit and normal squash/main readback to `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec`. **45/80 research documented (56.25%), 35 pending, 0 runtime, 80/80 coding WOs blocked**. NET-03 catalog **formal predecessors NET-02 and DATA-04**, only documentary/PROPOSED; NET-01, WORLD-01/03, CORE-04, GAME-04, NET-04/05/06 are separate owners/interface consumers.

## SCOPE
Exactly **eight NEW Markdown files** in a documentary research PR:
1. [architecture](../architecture/net-03-replication-interest-management.md)
2. [ADR-0049 PROPOSED](../adr/0049-net-03-authorized-per-client-snapshot-delta-interest.md)
3. [upstream technology/license matrix](../research/net-03-replication-technology-license-matrix.md)
4. [versioned semantic contracts](../contracts/net-03-replication-interest-api.md)
5. [exactly 128 FUTURE test cases](../testing/net-03-acceptance-matrix.md)
6. [8/16/32/64-player benchmark protocol](../research/net-03-replication-benchmark-protocol.md)
7. this Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-NET-03.md)

Research branch `docs/NLE-P00-WO-002-NET-03-replication-interest`. Need own exact-final-HEAD Docs Validation, objective pt-BR audit, normal squash/main readback. **After APPROVED** separate checkpoint PR updating only five files checkpoint/backlog/registry sole NET-03 research_status/this WO/Evidence, own CI/audit/squash/main readback. Optional historical readback closeout PR only four Markdown, own gates. Expected after checkpoint **46/80 research (57.5%), 34 pending, 0 implemented**. Research issue #236 CLOSE only after objective checkpoint main readback. Code #64 stays OPEN/BLOCKED. Do not start NET-04 until final audited closeout/readback.

## OUT OF SCOPE
No engine source (C++/Rust/Go/JS), changing WORLD or NET implementation, compiling libs, proto codegen, SDK import, copying Unreal/Unity/Godot/Valve source or sample assets, creating wire/schema files, running artificial clients/cloud/Agones, network packet captures, live tests or benchmarks, numeric p99 promises or tested 64-client claims, adopting licenses/ABI, changing Scope/DoD without owner, Zcode unlock, paid CI, CodeRabbit or forced merge.

## FILES / SOURCES TO READ (canonical hierarchy)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` / approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/NET-03.md`. Prior [NET-02 architecture](../architecture/net-02-authoritative-dedicated-server.md), [NET-02 contract](../contracts/net-02-dedicated-server-api.md), [NET-01 contract](../contracts/net-01-transport-connection-api.md), [GAME-04 contract](../contracts/game-04-gameplay-event-api.md), relevant WORLD-01/03 and DATA-04 research and NET-04/05/06 prospective contracts. Official technology references linked from matrix. Re-check critical Git blob hashes at base/branch.

## REQUIREMENTS
GOV-001..005 and applicable product CAP/NFR and NLE-D source Ledger; catalog acceptance "*Teste de 8/16/32/64 clientes quando perf target definido*". Treat **player counts as future workload axes and not approved performance capability**. No broadcast of health/owner inventory/hidden actors outside authorized role/match; client view is NOT server authority. Source code license NLE-D009 OPEN, ADR-0049 PROPOSED, release class UNDECIDED and no adopted library/codec.

## ARCHITECTURE RULES
NET-03 only owns authorized per-recipient replication projection, interest/priority/delta baseline and network receipt; NET-02 owns authoritative game process/match/validated input; WORLD-01/03 owns ECS/spatial data and committed barrier; CORE-04/03 owns time/jobs; GAME-04 owns gameplay/economy; DATA-04 owns versioned source schema/CAS (not packet ACK); NET-01 transport/cwnd/encryption; NET-04 client prediction, interpolation/reconciliation; NET-05 sessions/roles; NET-06 abuse and privacy; EDIT/CLI/MCP authorization. **Authorization precedes interest/quantization/cache/compression**. Per-recipient baseline only from app-ACKed frame in same policy/world/schema epoch; transport ACK is not decoded ACK. No unbounded queues/reassembly, forced shared secret cache or plaintext fallback. Revocation fences stale pending packets. Origin/quant rules CORE-05, no lossy game authority.

## CONSTRAINTS
P00 documentation only, original architecture and IP, no mandatory paid cloud/CI/external reviewer, no force push, no history rewrite or permission bypass. Use official sources for technology/license claims; evaluate actual file-level rights only when adoption considered. No code, game server, 8/16/32/64 measured stats, zero real tests. Security issues HIGH/CRITICAL require correction/block, not cosmetic caveats.

## ACCEPTANCE CRITERIA
- [ ] Research PR has **exactly 8 new Markdown**, canonical links and Source Pack compatibility; no engine source, registry, CI or dependency change.
- [ ] Proposed ADR-0049 and coherent typed architecture separate output eligibility/field ACL from spatial relevance, authorized caching, delta baseline, app-level ACK, generational spawn/despawn, fair quota, optional compression and NET-04 view handoff.
- [ ] Technological licensing matrix compares Unreal Iris proprietary EULA, Unity Netcode package terms not assumed MIT, Godot MIT, Valve Source SDK restricted, FlatBuffers Apache2, Protobuf BSD3, LZ4 library BSD2/CLI GPL, zstd dual BSD OR GPL2, and no code copied/adopted.
- [ ] Versioned semantic API and explicit fail-closed errors for schema/world/role/revocation/permission/ACK/quantization/decompression/NET-01 transport, editor/CLI/MCP preview permission, privacy observability.
- [ ] Exactly **128 unique N03-T001..N03-T128 FUTURE/NOT EXECUTED** cases including unauthorized decoded wire, 8/16/32/64 load axes, cross-OS/Web, loss/jitter/reconnect, p95/p99 future benchmark. No false PASS/performance promise.
- [ ] Research exact-final-HEAD GitHub Docs Validation success, objective pt-BR audit APPROVED documentary-only, normal squash and actual main readback.
- [ ] Separate checkpoint exact-final-HEAD Docs Validation/audit/squash/main readback, **sole NET-03 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**; result 46/80 research (57.5%), 34 pending, 0 runtime.
- [ ] All **80** coding packets `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`, code #64 OPEN/BLOCKED; research #236 closed only after checkpoint readback.
- [ ] Final review/closeout readback before next NET-04 research; no executor coding authorization.

## TESTS
Run actual GitHub Docs Validation on exact final research/checkpoint/closeout PR HEAD (Source Pack links, DAG/taxonomy, registry and blocked Zcode selector) and deterministic 128-ID uniqueness check. All 128 NET-03 acceptance cases are **future/not executed**; NO build, game, native/Web, security codec, packet stream, compression, latency, load or benchmark actually run. Docs CI is not runtime security proof.

## DELIVERABLES
Research issue #236, eight docs, research PR evidence exact HEAD/CI/audit/squash/main readback, checkpoint PR own gates and only registry single-field semantic delta, optional four-doc history closeout, Evidence Bundle, pt-BR objective verdict, proposed and then verified Checkpoint Delta. Do not modify implementation issue #64.

## REVIEW FORMAT
Pt-BR `APPROVED / CORRECTION REQUIRED / BLOCKED`; Git base/head SHA, key Git blob fingerprints, changed files/diff, exact CI run/job/steps, 128 FUTURE tests explicitly NOT EXECUTED, capability/rights/privacy threats, no invented benchmarks, known HIGH/CRITICAL, rollback, checkpoint proposed vs observed, state of 80 blocked WOs. Correction Delta only in same PR/WO.

## STOP CONDITION
STALE canonical context or unapproved ADR modified, any second authority/ECS/codec adopted without license, field privacy leak or shared private cache, unbounded ACK/queue/decompress, CI failed, HIGH/CRITICAL defect, any code packet ready/approved, wrong registry patch or unauthorized merge => CORRECTION REQUIRED or BLOCKED; no next module while open.

## CONTEXT LOCK (Git blob IDs, NOT file SHA256)
Base main `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec`; checkpoint `e47c18f2d347315f1511b2a28827477a020fce4e`; Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`; Scope `4ef605c74632ece080b2650e37dd83a415b63310`; DoD `160b3054db9ea1961308934b401488b838d24c3e`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`; Backlog `3bc3c367abbce474ad5a38d5da9afdaf541172ea`; Registry `103d8a3dab1ce5e2489a4fc8a3a9dacf40251ca9`; Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`; code draft `f44ef2edd047565d39082a50318a7aa8994e56ba`; AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`; NET-02 architecture `56f42dfa24a3868b3061ba177f45b4242fdcf26d`; NET-02 API `5e3a5bca27620248bee8f1a9658a760bf728940e`; NET-01 API `a41347d8cc0042d336598af2c5de8b533c91c428`; GAME-04 API `0f5f2edc888052f401ce1c2fe85828a299f43520`. Fresh read and rebase if changed; future implementation lock requires code fingerprints.

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-NET-03.md). PR/CI/merge/checkpoint pending at writing, do not assert an implemented engine.


## Research PR #237 objectively approved/merged and checkpoint delta proposed
- Research [PR #237](https://github.com/KayzenRoot/stormline/pull/237) BASE `d2cc5af8d8e1ffe7f0bececf934b89818692c2ec`, final HEAD `fa878757a0134e3ec6513dd3e63d122e6c59a70a`, exactly 8 NEW Markdown docs (509 additions, zero deletions), [Docs Validation #43714176703](https://github.com/KayzenRoot/stormline/actions/runs/43714176703) **SUCCESS** job #132812021247 (Source Pack/links, module DAG, registry, blocked Zcode selector), [pt-BR objective audit #6894352265](https://github.com/KayzenRoot/stormline/pull/237#issuecomment-6894352265) **APPROVED documentary-only**, normal squash/main/PR/contract readback `fdd9ab7474b50aac8adfae3dd649cd6437959530`. N03-T001..N03-T128 exactly 128 unique IDs verified, all FUTURE/NOT EXECUTED, no replicator or measured 8/16/32/64 clients.
- Independent checkpoint PR BASE `fdd9ab7474b50aac8adfae3dd649cd6437959530`, exactly five docs/registry files, registry sole NET-03 research_status transition. Expected **46/80 researched (57.5%), 34 pending, zero runtime**, ALL 80 coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class=UNDECIDED. Coding #64 OPEN/BLOCKED, ADR-0049 PROPOSED, code license OPEN. Checkpoint own exact-final-HEAD CI, objective audit, squash, main/registry readback **PENDING at creation**, issue #236 remains OPEN until that proof. No code or third-party libraries imported.
