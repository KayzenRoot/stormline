# Evidence Bundle — NET-05 Sessions & Lobby Interfaces Research

**Created 2026-11-15 | [research issue #244](https://github.com/KayzenRoot/stormline/issues/244) | WO NLE-P00-WO-002-NET-05 | [future coding #66](https://github.com/KayzenRoot/stormline/issues/66) OPEN/BLOCKED.** BASE verified main `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce`, previous NET-04 PR #241/#242/#243 audited/merged/readback. Research currently **IN REVIEW / NOT OWNER APPROVED / NO RUNTIME**. 47/80 research documented, 33 pending, 0 engine and 80/80 implementation packets blocked.

## Eight NEW research documents
[Architecture](../architecture/net-05-sessions-lobby-interfaces.md), [ADR-0051 PROPOSED](../adr/0051-net-05-local-first-session-lobby-ticket-contracts.md), [technology/license matrix](../research/net-05-session-lobby-technology-license-matrix.md), [typed contracts](../contracts/net-05-session-lobby-api.md), [128 FUTURE tests](../testing/net-05-acceptance-matrix.md), [benchmark protocol](../research/net-05-session-lobby-benchmark-protocol.md), [research Work Order](../work-orders/NLE-P00-WO-002-NET-05.md), this Evidence Bundle. Research PR changes none of registry, Source Pack checkpoint, engine source, CI, third-party libraries.

## Actual versus future proof at initial writing
| Gate | Status at drafting |
|---|---|
| Research PR number, exact changed files and final Git HEAD | PENDING |
| Research exact-final-HEAD Docs Validation, link/DAG/registry/Zcode checks | NOT YET RUN at drafting |
| Research objective pt-BR audit + normal squash/main readback | PENDING |
| Separate checkpoint PR own CI/audit/squash/main readback | PENDING |
| Exactly 128 N05-T001..N05-T128 | **FUTURE / NOT EXECUTED (0 passed, 0 failed)** |
| Actual local two-client lobby, auth and headless NET-02 server | **NOT IMPLEMENTED** |
| Real JWT signer/revoker, crypto/SSO, abuse tests, security assessment | **NOT IMPLEMENTED/NOT TESTED** |
| 8/16/32/64 session clients, native/Web builds, NAT/relay and measured p99 | **NOT RUN / NOT MEASURED** |
| Backend/provider/SDK/cloud costs, token/keys, public port and code license | **NOT SELECTED / NOT DEPLOYED / NLE-D009 OPEN** |

## Architecture, license and security evidence checklist
- NET-05 lobby/party/presence/session/invite/matchmaking/ticket orchestration only, NET-01 connection/crypto/NAT, NET-02 server readiness/actor admission, NET-03 viewer snapshot access, NET-04 client prediction reset, NET-06 abuse, GAME-04 game rewards, WORLD-01 ECS, CORE-04 tick, DATA-04 versioned CAS/durable state. Formal prerequisites NET-01 · NET-02 only, both researched but no code.
- Threats: token substitution/alg none/issuer confusion, unsigned guest public, JWT revocation and replay-store split brain, copied invite code, IP/hidden lobby/PII disclosure, enum timing, forged role, capacity double-book, stale allocation/connection lease and forced host migration, spoofed social account, spam/fanout/DoS and paid relay/cloud abuse. All protections **proposed but not implemented**, auth future HIGH_ASSURANCE.
- Official candidates: Nakama Apache2, Colyseus MIT, Open Match Apache2, Agones Apache2, Ory Hydra/Keycloak Apache2 candidate, Steamworks/EOS platform/service terms, GameLift/PlayFab hosted terms, coturn file-level license verify later. RFC9700, RFC8725, RFC9449, ICE/STUN/TURN. No adopted third party or source copied. ADR-0051 PROPOSED, engine NLE-D009 OPEN.
- No actual tests, native builds, rolling deploy, external secrets, cloud account, fees or security claim. Rollback current P00 is revert documentary diff only; no game/player data or infra migration occurred.

## Proposed checkpoint delta (not approved/promoted before gates)
After research PR exact-HEAD Docs Validation/audit/squash/main readback, separate checkpoint PR only `docs/11-checkpoint.md`, `docs/08-backlog.md`, `docs/queue/implementation-registry.json` **sole NET-05 research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**, this research WO and Evidence Bundle. Target **48/80 research (60%), 32 pending, zero executable engine**, ALL 80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. Coding #66 OPEN/BLOCKED, research #244 closes **only after** independent checkpoint CI/audit/squash/actual main readback. Historical 4-document closeout when needed with own validation. NET-06 research next only after final closure.

## Review format
Pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED, BASE/HEAD and Git blob fingerprints, exact changed files/diffs/CI run/job steps, source license and auth/anti-abuse risks, exactly 128 FUTURE tests NOT EXECUTED and benchmarks NOT MEASURED, severity/recovery/rollback and actual Checkpoint Delta proof after merge. Written "completed" is not server functionality evidence.


## Research PR #245 objectively APPROVED/MERGED and independent checkpoint proposal
- [Research PR #245](https://github.com/KayzenRoot/stormline/pull/245), BASE `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce`, audited final HEAD `c095dcb3237d720a8124ca14eda29f1e133b5a12`, exactly eight NEW Markdown docs (491 additions, zero deletions), [Docs Validation #43717339399](https://github.com/KayzenRoot/stormline/actions/runs/43717339399) **SUCCESS** job #132821599405 all Source Pack/local links, module DAG, registry, blocked Zcode selector success; [pt-BR objective audit #6894785619](https://github.com/KayzenRoot/stormline/pull/245#issuecomment-6894785619) **APPROVED DOCUMENTARY ONLY**, normal squash/main/PR/API readback `2031e44994aef5379521063985c001c08342f2d9`. Exactly 128 unique N05-T001..N05-T128 **FUTURE/NOT EXECUTED**, zero real server/auth/security or benchmarks.
- Independent checkpoint PR BASE `2031e44994aef5379521063985c001c08342f2d9`, five allowed files (checkpoint/backlog/registry/this WO/Evidence), registry sole NET-05 research_status change. Expected **48/80 research (60%), 32 pending, 0 engine**, all 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null, release_class UNDECIDED, future coding #66 OPEN/BLOCKED. ADR-0051 PROPOSED and code license NLE-D009 OPEN; provider/runtime not adopted. Checkpoint own exact-final-HEAD CI/audit/squash/main readback PENDING at creation; research #244 remains OPEN until actual main readback.
