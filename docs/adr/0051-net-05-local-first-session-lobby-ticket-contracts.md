# ADR-0051 — Local-first lobby/session coordinator with independently validated short-lived match tickets

**Status PROPOSED / NOT OWNER APPROVED / NOT ADOPTED** | 2026-11-15 | research #244 | NLE-P00-WO-002-NET-05 | future coding #66 OPEN/BLOCKED | base main `cfcc290fe93d21c2cb558a0d09dd2ea51f0eadce` | NLE-D009 engine code license OPEN.

## Decision context
The Stormline catalog demands create/join/leave, reconnect and predictable failures without mandatory SaaS. NET-01 transport and NET-02 authoritative server are only documented, and NET-06 dedicated abuse control research is queued **after** NET-05. No user-account provider or service license has been approved. Platform social identities (Steam/EOS), Open Match/Agones, and self-hosted Nakama have nonidentical authority and cost models. A lobby roster, server reservation, and game admission must not collapse into one unchecked state.

## Proposed decision
Adopt as a **future design candidate** an original Stormline-owned, typed **local-first coordination interface** with clean adapters for external auth, lobby discovery, matchmaking, server allocation and relay **but no mandatory backend subscription**. Formal initial slice is standalone self-host/localhost identity/lobby/match coordination with one fixed NET-02 server allocation, simple session join and failure handling. NET-05 owns authorization policy and creation of a **separate, audience-scoped, short-lived game join ticket**; NET-02 must independently validate it alongside live actor/match/lease/ban/revocation. NET-01 connection authenticity alone never confers gameplay permission. DATA-04 owns versions/CAS/outbox; NET-06 owns security abuse policies; neither duplicated.

- **Three receipts**: lobby membership accepted (NET-05), server instance reserved/ready (NET-02 coordinated via NET-05), gameplay join authorized (NET-02); transport ACK (NET-01) remains separate.
- **Finite lifecycle**: versioned identity session, party, lobby, matchmaking ticket, reservation and match session. Atomically gated membership/capacity; idempotent commands. The **lobby host owns lobby policy**, not authoritative game physics or server money/items.
- **Secure game ticket**: issuer/audience/type/key-allowlist/expiry/session+match+world/server allocation generation/actor+role scope, replay nonce/jti and current revocation/ban checks. Adapt [RFC 9700 OAuth security](https://www.rfc-editor.org/rfc/rfc9700.html) and [RFC 8725 JWT BCP](https://www.rfc-editor.org/rfc/rfc8725.html) for identity/token layers, not a homemade cipher. Sender-constrained HTTP OAuth tokens per [RFC 9449](https://www.rfc-editor.org/rfc/rfc9449.html) are **optional studied approach**, do not pretend DPoP secures game UDP automatically.
- **Reconnect**: reset transport connection, revalidate identity and role, renew short ticket under bounded grace, invalidate old connection/NET-03 baseline/NET-04 prediction and stale lease. Clear failure if server no longer active. Do not silently convert to guest or grant old permissions.
- **Optional discovery/matchmaking**: initial manual lobby selection and local ready-server allocation; party queue/fairness/skill and 3P backends are opt-in adapters. Steam/EOS proprietary terms and costs remain unapproved, Nakama/Open Match/Agones require deployment resources despite open-source code. No automatic paid cloud resource/spend.
- **No transparent authoritative host migration in baseline**. Dedicated match restart/resume needs DATA-04 checkpoint/fencing/NET-02 safe recovery and idempotency, otherwise fail closed. P2P host is not automatically authoritative.
- **Privacy**: presence invite-only/discoverable/friends-only/hidden, block lists and audience-aware metadata; player IP, private friends lists, tokens, precise online/offline claims and game world secret state never public by default.
- **Editor/CLI/MCP** may inspect, preview, stage/validate/commit **config profiles** under administrator role and DATA-04 expected revision, but cannot create billing/subscriptions, accept private invites as an admin, issue arbitrary player tokens, or impersonate user.

## Alternatives compared
| Candidate | Benefit | Risk / disposition |
|---|---|---|
| Local-first original typed coordinator + NET-02 validation | no mandatory SaaS, portable native/Web interfaces, controllable auth and failure semantics | must implement durable/replay/ban consistency and security hardening; **leading proposal** |
| Always-online EOS/Steamworks mandatory | discovery/friends/invites and ecosystem integration | platform credentials/terms, different app rights, service dependency and privacy; **optional** |
| Nakama authoritative engine as Stormline game loop | rich auth, sessions, parties, matchmaking | duplicates NET-02 gameplay authority/WORLD ECS; **comparison or backend adapter only** |
| Colyseus Node.js rooms as canonical game state | quick rooms/reconnect, MIT source | second game simulation/codec, TypeScript runtime; **reference or optional adapter** |
| Open Match + Agones mandatory | production matchmaking/fleets | multi-service Kubernetes cost, they do not implement identity/game authority; **optional later** |
| P2P host leader becomes authoritative automatically | low server cost | host cheating, migration state/data loss, NAT/IP exposure; **reject as baseline** |
| Guest unsigned public tokens | simple demos | impersonation and auth bypass; **explicitly reject outside isolated loopback tests** |

## Approval criteria and consequences
Approved only after NET-01/02 real backend and security model, owner-confirmed mode and Scope/DoD, release class/license, exact token issuer/key management, self-host local test with two client identities and one NET-02 server, negative replay/authz/privacy/expiry and disconnect tests, durable nonce/lease/capacity correctness, native/Web targets and actual cost benchmark. No “JWT verifies” shortcut for revocation/ban or game actions. No silent paid provider/host, no deployment. **Proposed ADR merging never unlocks Zcode**, all 80 implementation WOs blocked.
