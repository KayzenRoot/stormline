# NET-05 — Identity, Lobby, Matchmaking, Allocation, NAT/Relay Technology and License Matrix

**Official-source study 2026-11-15, all choices hypothetical.** Code licenses do not guarantee free hosted service, product redistribution rights, user-account provider access, platform SDK permissions or permission to import cloud keys. Freeze exact Git SHA/release file-level LICENSE/NOTICE/transitive SBOM/ABI/OS arch and official service terms when actually adopting. No SDK, account, dependency, provider, runtime, production token, cloud resource or engine code license selected. NLE-D009 **OPEN**.

## 1. Backend/engine comparison
| Source / official documentation | Preliminary code rights vs paid/service obligations | Relevant capability / architectural boundary |
|---|---|---|
| **Original Stormline local coordinator** | future Stormline engine license **OPEN**, no external mandatory SaaS, hardware/operation still costs | versioned lobby/party/invite/ticket interface, local one-server first; no implementation today |
| [Nakama source](https://github.com/heroiclabs/nakama), [LICENSE](https://github.com/heroiclabs/nakama/blob/master/LICENSE), [sessions](https://heroiclabs.com/docs/nakama/concepts/session/), [parties](https://heroiclabs.com/docs/nakama/concepts/parties/), [matchmaker](https://heroiclabs.com/docs/nakama/concepts/multiplayer/matchmaker/) | core source **Apache-2.0**; Heroic Cloud managed service pricing/terms separate; SQL/storage/ops infrastructure not zero-cost by inference | strong full service reference: signed JWT sessions/refresh, presence, parties, ticket pools. Nakama matchmaker result **does not auto-join a game**, server-authoritative match logic would be its own runtime and not Stormline NET-02 |
| [Colyseus source](https://github.com/colyseus/colyseus), [LICENSE](https://github.com/colyseus/colyseus/blob/master/LICENSE) | core **MIT**; optional Colyseus Cloud commercial terms, Node.js and dependencies | room-based create/join/seat reservation/reconnection, matchmaker; not a drop-in C++ engine or security proof |
| [Open Match](https://github.com/googleforgames/open-match), [README/license](https://github.com/googleforgames/open-match/blob/main/README.md) | **Apache-2.0** core; Kubernetes/service infrastructure and operation costs distinct | player search tickets, matching assignment and backfill orchestration, **not an auth issuer, NET-02 game or NAT relay** |
| [Agones](https://github.com/agones-dev/agones), [GameServerAllocation](https://agones.dev/site/docs/reference/gameserverallocation/) | core **Apache-2.0**, Kubernetes cluster/hosting and SDK deps separate | atomic dedicated server allocation/lifecycle, independent from lobby membership and game admission |
| [Keycloak](https://www.keycloak.org/), [GitHub](https://github.com/keycloak/keycloak) | generally **Apache-2.0** source; verify exact tagged LICENSE, dependencies and operational database costs | optional OIDC identity provider, not a game lobby or matchmaker |
| [Ory Hydra](https://github.com/ory/hydra), [LICENSE](https://github.com/ory/hydra/blob/master/LICENSE) | core **Apache-2.0**; hosted Ory Network contractual pricing and integrated login identity separate | OIDC/OAuth authorization-server building block, NOT complete game identity backend by itself |
| [Steamworks matchmaking](https://partner.steamgames.com/doc/features/multiplayer/matchmaking), [Steamworks partner terms](https://partner.steamgames.com/doc/home) | **Valve Steamworks SDK and Steam distribution/partner agreements**; do not treat publicly readable docs as MIT; access/fees/eligibility to be checked | Steam lobby presence, invites, filters and friend/social APIs, platform-specific optional provider, not universal external identity or NET-02 game proof |
| [Epic Online Services](https://dev.epicgames.com/docs/game-services/lobbies) | **Epic EOS SDK service/license and developer terms**, product-specific free tier and policy must be checked; not permissive source by default | optional cross-platform session/lobby/account/social SDK; no required Epic account for Stormline local use |
| [AWS GameLift Servers](https://docs.aws.amazon.com/gameliftservers/latest/developerguide/gamelift-howitworks.html) | **AWS metered hosting/service contract** and SDK licenses per version, never assumed free | optional dedicated match server placement with costs; not lobby authority or login |
| [Microsoft PlayFab Multiplayer](https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/servers/) | Microsoft **managed service terms/pricing**, SDK per pinned package | optional server allocations, player data service; not baseline Stormline engine |
| [coturn](https://github.com/coturn/coturn), [license file](https://github.com/coturn/coturn/blob/master/LICENSE) | historically BSD-style permissive terms, exact version and additional third-party build rights **verify before adoption** | TURN/STUN relay infrastructure; bandwidth costs, secret lifecycle and peer-privacy; not matchmaker or game authority |

## 2. Standards / security references are NOT software license grants
| Normative source | Technical relevance and not-to-confuse clause |
|---|---|
| [RFC 9700 OAuth Security BCP](https://www.rfc-editor.org/rfc/rfc9700.html) | PKCE/redirect/refresh/security posture for client identity OAuth flows; OIDC implementation details separate |
| [RFC 8725 JWT BCP](https://www.rfc-editor.org/rfc/rfc8725.html) | alg allowlist, explicit token typ/aud/iss, prevent token substitution and untrusted kid/jku/SSRF; token signature does NOT mean current game role or single use |
| [RFC 9449 DPoP](https://www.rfc-editor.org/rfc/rfc9449.html) | sender-constrained **HTTP OAuth token**; do not transplant to UDP/QUIC game packets without explicit adapted security design |
| [RFC 8445 ICE](https://www.rfc-editor.org/rfc/rfc8445.html) / [RFC 8489 STUN](https://www.rfc-editor.org/rfc/rfc8489.html) / [RFC 8656 TURN](https://www.rfc-editor.org/rfc/rfc8656.html) | connectivity/NAT/relay; STUN alone not full NAT solution, TURN costs resources; NET-01 owns network stack |
| [RFC 9000 QUIC](https://www.rfc-editor.org/rfc/rfc9000.html) / [RFC 9001 TLS](https://www.rfc-editor.org/rfc/rfc9001.html) | secure transport; no automatic game session authority or user authentication |
| [OWASP Game Security Framework](https://owasp.org/projects/gamesec-framework) | threat checklist only, not implementation/certification of anti-cheat |

## 3. Local-first decision matrix
| Configuration | Production readiness | Cost / infrastructure dependency | NET-05 fit |
|---|---|---|---|
| isolated loopback test-id and in-memory lobby | **test only**, no public binding or durable session assumptions | no mandatory paid SaaS; OS process/CPU cost | NECESSARY first runnable fixture only after approvals |
| production self-hosted identity + durable tokens/session store | security review/keys/backup/HA/anti-abuse required | software may be OSS, hosting still paid or self-host hardware | IMPORTANT production alternative |
| Steamworks/EOS provider adapter | platform terms and token validation must be approved | platform ecosystem, SDK/service dependence | optional after ports/game distribution strategy |
| Nakama or Colyseus adapter | licensing, C++ bindings, identity/data handling integration proof | own servers/datastore or paid managed hosting | optional, do not replace engine game authority |
| Open Match + Agones fleet | scale/lease/failover/ops prove first | Kubernetes multi-service infrastructure, never mandatory | FUTURE |
| direct peer-to-peer + TURN relay | privacy/NAT/security tradeoff | relay bandwidth/abuse cost, heterogeneous networks | FUTURE, game-specific; no host-trust default |

## 4. Adoption gates
- Pin exact source/SDK rights, image/OS/ARM64/Web targets, hosted quota/pricing, identity PII/LGPD policies, SPDX/NOTICE/SBOM and support/update posture.
- Test malicious join/link/callback, identity provider down, clock skew, replay and revocation/ban, scale of lobby/presence, provider cancellation, zombie allocation, lease fencing and no paid cloud auto-provisioning.
- Never import Steam/EOS/Valve/Unreal/Unity proprietary source/assets into Stormline on presumed MIT grounds. Never claim free service from OSS license.
- **No choice adopted; ADR-0051 PROPOSED; engine license NLE-D009 OPEN; 128 future scenarios NOT EXECUTED.**
