# NET-05 — Exactly 128 FUTURE Local-First Session & Lobby Acceptance Tests

**Research #244 | WO NLE-P00-WO-002-NET-05 | future implementation #66 OPEN/BLOCKED.** Exactly 128 unique N05-T001..N05-T128 test obligations. ALL **FUTURE / NOT EXECUTED**: executed=0, passed=0, failed=0 because there is no server/client/backend, game identity provider, test harness or network runtime. Documentation-only GitHub Docs Validation is **not** gameplay/auth/cryptographic/security proof.

Future every result needs: user-approved DoD/budgets, stable case ID and requirements/contract trace, source base/head SHA and built artifacts, provider/auth keys via isolated fixtures only, target OS/browser/native, one NET-02 headless match and two authenticated principals, fake/real network profile and seed, exact commands/CI run, state before/after, security denial and redacted evidence, TTL/clock drift, role/ban/visibility epochs, per-client join authorization, data store consistency and standardized typed error plus objective pt-BR audit verdict. No secret/PII in artifacts. Numbers/timing/scale targets remain TBD pending owner baseline.

| ID | Area | Future assertion | Current state |
|---|---|---|---|
## Identity and token validation
| N05-T001 | Identity and token validation | OIDC public client PKCE flow accepted only after real issuer proof | FUTURE / NOT EXECUTED |
| N05-T002 | Identity and token validation | expired identity token rejected | FUTURE / NOT EXECUTED |
| N05-T003 | Identity and token validation | invalid issuer/audience rejected | FUTURE / NOT EXECUTED |
| N05-T004 | Identity and token validation | JWT algorithm confusion or none denied | FUTURE / NOT EXECUTED |
| N05-T005 | Identity and token validation | untrusted kid/jku source URL blocked | FUTURE / NOT EXECUTED |
| N05-T006 | Identity and token validation | account subject cannot impersonate another | FUTURE / NOT EXECUTED |
| N05-T007 | Identity and token validation | refresh token rotation and reuse detection future | FUTURE / NOT EXECUTED |
| N05-T008 | Identity and token validation | logout/revocation stops future authenticated operations | FUTURE / NOT EXECUTED |
## Local-first and provider isolation
| N05-T009 | Local-first and provider isolation | local isolated test provider needs no SaaS account | FUTURE / NOT EXECUTED |
| N05-T010 | Local-first and provider isolation | localhost test guest credential refused on public bind | FUTURE / NOT EXECUTED |
| N05-T011 | Local-first and provider isolation | provider unavailable returns typed failure | FUTURE / NOT EXECUTED |
| N05-T012 | Local-first and provider isolation | no automatic Epic/Steam/AWS cloud enrollment | FUTURE / NOT EXECUTED |
| N05-T013 | Local-first and provider isolation | optional self-host provider works without vendor API | FUTURE / NOT EXECUTED |
| N05-T014 | Local-first and provider isolation | provider account unlink invalidates relevant sessions | FUTURE / NOT EXECUTED |
| N05-T015 | Local-first and provider isolation | issuer clock/key rollover policy fail-closed | FUTURE / NOT EXECUTED |
| N05-T016 | Local-first and provider isolation | raw provider secret never stored in scene/source | FUTURE / NOT EXECUTED |
## Lobby lifecycle
| N05-T017 | Lobby lifecycle | create lobby stores expected generation | FUTURE / NOT EXECUTED |
| N05-T018 | Lobby lifecycle | open/invite-only/locked transitions valid | FUTURE / NOT EXECUTED |
| N05-T019 | Lobby lifecycle | closed lobby cannot reopen stale generation | FUTURE / NOT EXECUTED |
| N05-T020 | Lobby lifecycle | host lobby permission not game authority | FUTURE / NOT EXECUTED |
| N05-T021 | Lobby lifecycle | simultaneous lobby close and join serializes | FUTURE / NOT EXECUTED |
| N05-T022 | Lobby lifecycle | ready/launch requires authorized membership | FUTURE / NOT EXECUTED |
| N05-T023 | Lobby lifecycle | lobby state owner transfer rules versioned | FUTURE / NOT EXECUTED |
| N05-T024 | Lobby lifecycle | lobby cleanup on last member TTL eventual | FUTURE / NOT EXECUTED |
## Join leave capacity and concurrency
| N05-T025 | Join leave capacity and concurrency | two concurrent joins cannot overbook one slot | FUTURE / NOT EXECUTED |
| N05-T026 | Join leave capacity and concurrency | duplicate join idempotent no second seat | FUTURE / NOT EXECUTED |
| N05-T027 | Join leave capacity and concurrency | leave idempotent and releases reservation once | FUTURE / NOT EXECUTED |
| N05-T028 | Join leave capacity and concurrency | stale leave cannot remove rejoined generation | FUTURE / NOT EXECUTED |
| N05-T029 | Join leave capacity and concurrency | full lobby rejects with typed privacy-safe error | FUTURE / NOT EXECUTED |
| N05-T030 | Join leave capacity and concurrency | invalid content/game build join denied | FUTURE / NOT EXECUTED |
| N05-T031 | Join leave capacity and concurrency | kicked member old ticket cannot rejoin | FUTURE / NOT EXECUTED |
| N05-T032 | Join leave capacity and concurrency | leader departure race handled without split leadership | FUTURE / NOT EXECUTED |
## Invitations and social privacy
| N05-T033 | Invitations and social privacy | invitation recipient-specific expiry checked | FUTURE / NOT EXECUTED |
| N05-T034 | Invitations and social privacy | revoked code cannot be reused | FUTURE / NOT EXECUTED |
| N05-T035 | Invitations and social privacy | one-time invitation consumed atomically | FUTURE / NOT EXECUTED |
| N05-T036 | Invitations and social privacy | blocked player invitation rejected | FUTURE / NOT EXECUTED |
| N05-T037 | Invitations and social privacy | guessable invite code brute-force bounded | FUTURE / NOT EXECUTED |
| N05-T038 | Invitations and social privacy | friends-only lobby hidden from strangers | FUTURE / NOT EXECUTED |
| N05-T039 | Invitations and social privacy | private lobby ID not enumerable via search | FUTURE / NOT EXECUTED |
| N05-T040 | Invitations and social privacy | invite notification does not expose private contact | FUTURE / NOT EXECUTED |
## Presence and discovery
| N05-T041 | Presence and discovery | presence HIDDEN not listed to non-audience | FUTURE / NOT EXECUTED |
| N05-T042 | Presence and discovery | stale presence heartbeat expires | FUTURE / NOT EXECUTED |
| N05-T043 | Presence and discovery | presence update coalescing bounded | FUTURE / NOT EXECUTED |
| N05-T044 | Presence and discovery | public lobby metadata allowlist excludes IP | FUTURE / NOT EXECUTED |
| N05-T045 | Presence and discovery | discover pagination and rate quotas | FUTURE / NOT EXECUTED |
| N05-T046 | Presence and discovery | unknown region client fails safe on compatibility | FUTURE / NOT EXECUTED |
| N05-T047 | Presence and discovery | spectator visibility requires explicit role | FUTURE / NOT EXECUTED |
| N05-T048 | Presence and discovery | search result no full private friend roster | FUTURE / NOT EXECUTED |
## Party matchmaking
| N05-T049 | Party matchmaking | party leadership transfer generation-safe | FUTURE / NOT EXECUTED |
| N05-T050 | Party matchmaking | party roster matching does not split group | FUTURE / NOT EXECUTED |
| N05-T051 | Party matchmaking | party member leaves while ticket queued safely | FUTURE / NOT EXECUTED |
| N05-T052 | Party matchmaking | duplicate matchmaker ticket deduped | FUTURE / NOT EXECUTED |
| N05-T053 | Party matchmaking | queue cancellation races matched event predictably | FUTURE / NOT EXECUTED |
| N05-T054 | Party matchmaking | offline ticket handling explicit not assumed | FUTURE / NOT EXECUTED |
| N05-T055 | Party matchmaking | matchmaking result does not auto-join server | FUTURE / NOT EXECUTED |
| N05-T056 | Party matchmaking | matchmaker provider absent allows manual local selection | FUTURE / NOT EXECUTED |
## Server allocation separation
| N05-T057 | Server allocation separation | lobby created without server process allowed | FUTURE / NOT EXECUTED |
| N05-T058 | Server allocation separation | match reservation distinct actual NET-02 ready | FUTURE / NOT EXECUTED |
| N05-T059 | Server allocation separation | allocator failure releases stale reservation | FUTURE / NOT EXECUTED |
| N05-T060 | Server allocation separation | two matches cannot claim same fenced server lease | FUTURE / NOT EXECUTED |
| N05-T061 | Server allocation separation | allocated endpoint not automatically player authorization | FUTURE / NOT EXECUTED |
| N05-T062 | Server allocation separation | server health failure prevents fresh ticket | FUTURE / NOT EXECUTED |
| N05-T063 | Server allocation separation | server game actor owner checked at actual join | FUTURE / NOT EXECUTED |
| N05-T064 | Server allocation separation | host lobby cannot issue privileged server command | FUTURE / NOT EXECUTED |
## Match join ticket cryptography
| N05-T065 | Match join ticket cryptography | game ticket audience restricted server instance | FUTURE / NOT EXECUTED |
| N05-T066 | Match join ticket cryptography | match/world generation mismatch denied | FUTURE / NOT EXECUTED |
| N05-T067 | Match join ticket cryptography | ticket typ differs from lobby OAuth token | FUTURE / NOT EXECUTED |
| N05-T068 | Match join ticket cryptography | ticket nonce replay denied across reconnection | FUTURE / NOT EXECUTED |
| N05-T069 | Match join ticket cryptography | ticket expired/not yet valid denied | FUTURE / NOT EXECUTED |
| N05-T070 | Match join ticket cryptography | key rotation with configured trust window | FUTURE / NOT EXECUTED |
| N05-T071 | Match join ticket cryptography | ticket theft binding policy reviewed future | FUTURE / NOT EXECUTED |
| N05-T072 | Match join ticket cryptography | transport handshake alone not game join acceptance | FUTURE / NOT EXECUTED |
## Reconnection and recovery
| N05-T073 | Reconnection and recovery | disconnect not treated as identity logout | FUTURE / NOT EXECUTED |
| N05-T074 | Reconnection and recovery | bounded reconnect grace rotates ticket | FUTURE / NOT EXECUTED |
| N05-T075 | Reconnection and recovery | reconnect on different IP revalidates identity | FUTURE / NOT EXECUTED |
| N05-T076 | Reconnection and recovery | closed match reconnect fails predictably | FUTURE / NOT EXECUTED |
| N05-T077 | Reconnection and recovery | ban during disconnect denies resume | FUTURE / NOT EXECUTED |
| N05-T078 | Reconnection and recovery | NET-03 baseline invalidated after new epoch | FUTURE / NOT EXECUTED |
| N05-T079 | Reconnection and recovery | NET-04 predicted input history reset | FUTURE / NOT EXECUTED |
| N05-T080 | Reconnection and recovery | server crash recovery cannot assert durable success | FUTURE / NOT EXECUTED |
## NAT relay and connectivity
| N05-T081 | NAT relay and connectivity | ICE success/failure surfaced as NET-01 result | FUTURE / NOT EXECUTED |
| N05-T082 | NAT relay and connectivity | STUN alone not promised NAT traversal | FUTURE / NOT EXECUTED |
| N05-T083 | NAT relay and connectivity | TURN optional relay credentials expire | FUTURE / NOT EXECUTED |
| N05-T084 | NAT relay and connectivity | relay endpoint cannot be client arbitrary SSRF target | FUTURE / NOT EXECUTED |
| N05-T085 | NAT relay and connectivity | direct peer IP hidden when privacy requires | FUTURE / NOT EXECUTED |
| N05-T086 | NAT relay and connectivity | relay costs require explicit opt-in | FUTURE / NOT EXECUTED |
| N05-T087 | NAT relay and connectivity | IPv6/direct server discovery capability checked | FUTURE / NOT EXECUTED |
| N05-T088 | NAT relay and connectivity | browser unsupported network mode honest failure | FUTURE / NOT EXECUTED |
## Migration and data integrity
| N05-T089 | Migration and data integrity | lobby host transfer not game host migration | FUTURE / NOT EXECUTED |
| N05-T090 | Migration and data integrity | dedicated server migration default unsupported | FUTURE / NOT EXECUTED |
| N05-T091 | Migration and data integrity | DATA-04 checkpoint lease fencing future | FUTURE / NOT EXECUTED |
| N05-T092 | Migration and data integrity | duplicate server allocation after crash guarded | FUTURE / NOT EXECUTED |
| N05-T093 | Migration and data integrity | old allocation epoch cannot access new game | FUTURE / NOT EXECUTED |
| N05-T094 | Migration and data integrity | reservation recovered without duplicate player slots | FUTURE / NOT EXECUTED |
| N05-T095 | Migration and data integrity | idempotent outbox prevents duplicate external rewards | FUTURE / NOT EXECUTED |
| N05-T096 | Migration and data integrity | stale provider callback cannot revive a match | FUTURE / NOT EXECUTED |
## Abuse and permission boundaries
| N05-T097 | Abuse and permission boundaries | lobby spam create quota future | FUTURE / NOT EXECUTED |
| N05-T098 | Abuse and permission boundaries | invite fanout abuse detection future | FUTURE / NOT EXECUTED |
| N05-T099 | Abuse and permission boundaries | malicious lobby metadata size/UTF safety future | FUTURE / NOT EXECUTED |
| N05-T100 | Abuse and permission boundaries | operator endpoint cannot mint arbitrary user ticket | FUTURE / NOT EXECUTED |
| N05-T101 | Abuse and permission boundaries | MCP client cannot impersonate private lobby user | FUTURE / NOT EXECUTED |
| N05-T102 | Abuse and permission boundaries | JWT SSRF and open redirect negative tests future | FUTURE / NOT EXECUTED |
| N05-T103 | Abuse and permission boundaries | unknown actor role fails closed | FUTURE / NOT EXECUTED |
| N05-T104 | Abuse and permission boundaries | banned/revoked membership overrides cached presence | FUTURE / NOT EXECUTED |
## Cross-platform and storage
| N05-T105 | Cross-platform and storage | native Windows local session client future | FUTURE / NOT EXECUTED |
| N05-T106 | Cross-platform and storage | native Linux local session client future | FUTURE / NOT EXECUTED |
| N05-T107 | Cross-platform and storage | native macOS local session client future | FUTURE / NOT EXECUTED |
| N05-T108 | Cross-platform and storage | Web browser OIDC flow future | FUTURE / NOT EXECUTED |
| N05-T109 | Cross-platform and storage | local in-memory restart non-durability explicit | FUTURE / NOT EXECUTED |
| N05-T110 | Cross-platform and storage | durable self-host store CAS recovery future | FUTURE / NOT EXECUTED |
| N05-T111 | Cross-platform and storage | no credential logged or stored in export bundle | FUTURE / NOT EXECUTED |
| N05-T112 | Cross-platform and storage | session schema version migration test future | FUTURE / NOT EXECUTED |
## Reliability and performance
| N05-T113 | Reliability and performance | 2 concurrent local clients lifecycle future | FUTURE / NOT EXECUTED |
| N05-T114 | Reliability and performance | 8 simulated lobby clients fixture future | FUTURE / NOT EXECUTED |
| N05-T115 | Reliability and performance | 16 simulated lobby clients fixture future | FUTURE / NOT EXECUTED |
| N05-T116 | Reliability and performance | 32 simulated lobby clients fixture future | FUTURE / NOT EXECUTED |
| N05-T117 | Reliability and performance | 64 simulated lobby clients fixture future | FUTURE / NOT EXECUTED |
| N05-T118 | Reliability and performance | p95/p99 create join reconnect latency future | FUTURE / NOT EXECUTED |
| N05-T119 | Reliability and performance | allocation churn memory and CPU bounded future | FUTURE / NOT EXECUTED |
| N05-T120 | Reliability and performance | provider outage graceful backoff measured future | FUTURE / NOT EXECUTED |
## Governance and release gates
| N05-T121 | Governance and release gates | 128 N05 future IDs unique and unexecuted | FUTURE / NOT EXECUTED |
| N05-T122 | Governance and release gates | no mandatory paid backend or cloud runtime | FUTURE / NOT EXECUTED |
| N05-T123 | Governance and release gates | third-party SDK license/NOTICE review future | FUTURE / NOT EXECUTED |
| N05-T124 | Governance and release gates | source pack and ADR pinned before coding | FUTURE / NOT EXECUTED |
| N05-T125 | Governance and release gates | HIGH/CRITICAL auth issue blocks progression | FUTURE / NOT EXECUTED |
| N05-T126 | Governance and release gates | no engine backend tested at P00 | FUTURE / NOT EXECUTED |
| N05-T127 | Governance and release gates | 80 coding work orders remain blocked | FUTURE / NOT EXECUTED |
| N05-T128 | Governance and release gates | NET-06 next only after readback | FUTURE / NOT EXECUTED |

## Future benchmark/trust proof
- Controlled test categories include local without paid service; identity provider down, password/token expired, key rotation, replay/cross-audience, concurrent capacity and stale invite, raw hidden lobby discovery denial, matchmaking ticket cancellation, NET-02 game admission vs lobby membership, reconnect after NET-01 rebind, NAT/ICE/TURN optional and explicit relay cost approval.
- Test 2 clients functional; 8/16/32/64 are **candidate load axes**, not acceptance thresholds or guaranteed player counts. Run security/lifecycle correctness before throughput.
- Windows/Linux/macOS/Web support needs real builds and actual client flows. All 128 test cases **NOT EXECUTED**; no P00 auth/security/latency claim.
