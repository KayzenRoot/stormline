# ADR-0048 — Engine-owned headless authoritative server with typed tick barrier and validated input

**Status: PROPOSED / NOT OWNER APPROVED / NOT ADOPTED** | 2026-11-15 | [Research #232](https://github.com/KayzenRoot/stormline/issues/232) | WO NLE-P00-WO-002-NET-02 | coding #63 OPEN/BLOCKED | engine license NLE-D009 OPEN.

## Decision context
The Stormline 80-module catalog calls for a dedicated server that runs without graphics hardware and rejects arbitrary client-world state, while retaining a clean engine-owned world and tick model. Formal predecessors NET-01/WORLD-01/CORE-04 have **only** documentary research, so actual functionality cannot yet be demonstrated. GAME-04's validated commands and NET-05 session binding are needed for a game demo; neither transport encryption nor a matchmaker can substitute server gameplay authority. Deployment architecture must be local-first, with optional infrastructure only, preserving solo/free-CI governance.

### Proposed decision
Provide **one native Stormline server process mode**, reusing the shared engine WORLD-01/ECS, CORE-04 fixed TickId, CORE-03 scheduler and GAME-04 authorized command gateway, with **no graphics/audio device required** and a **server-owned read/write barrier**. NET-01 supplies encrypted/authenticated transport messages but not gameplay authority. Ingress is a typed, bounded per-principal action-intent queue; server validates identity, match/world epoch, actor ownership, input frequency, replay/tick horizon and gameplay rule before committing to ECS. NET-03 handles future replicas/interest, NET-04 handles prediction/rewind where necessary, NET-05 handles sessions/matchmaking/allocation, NET-06 handles abuse. The deployment path is local process first, container second, optional Agones/managed services only after independent proof.

- Start with **one process/one match** to achieve independent vertical test and security boundary. Multiple matches require separate memory/queue/actor tables and quotas, with a default stronger process-per-match boundary for adversarial content until isolation is proven. A per-match C++ object is not an OS sandbox.
- Use CORE-04 authoritative tick, not network I/O callbacks, OS wallclock or render FPS. Freeze admission and validate input at each tick; apply through GAME-04/WORLD-01. Phase and ordering policy versioned and replayable on a pinned platform. Tick overload is visible and bounded, with no silent unbounded catch-up.
- Client input is never authority over health/position/inventory/economy. GAME-04 emits application commit receipts distinct from NET-01 transport ACK, with explicit rejection reasons. Server may provide non-sensitive predicted response but not trust the client's prediction.
- **Rollback not mandatory**. When future NET-04 lag compensation is chosen, restrict to approved state/horizon with deterministic replay, no duplicate irreversible side effects and no unexplained data exposure; server process headless != automatic rollback guarantee.
- Lifecycle `BOOTSTRAP -> READY -> DRAINING -> CLOSED` and match lifecycle are independently typed, with health/readiness/termination and crash recovery; no guarantee of exactly-once cross-process external effects unless durable transactional design proves it.
- Editor/CLI/MCP may preview/stage/validate deploy configs with scoped authorization, but **no public arbitrary server shell/network dial/actor state mutation**. Real deployment and privileged secrets require separate permissions and optional hosting adapter.
- Do not adopt Agones/Nakama/Open Match/Colyseus/PlayFab/GameLift now: use their documented patterns as constraints and compare licenses/costs only.

## Alternatives
| Option | Benefits | Tradeoffs / disposition |
|---|---|---|
| Client-hosted/listen server or P2P | no dedicated hosting, quick local play | host cheating, owner disconnect/session migration and shared trust; **not baseline for competitive/economy gameplay** |
| Cloud/Agones/Kubernetes as fundamental core | elastic fleets/lifecycle | costly complexity, locks a paid or cluster environment, doesn't implement world simulation; **reject mandatory** |
| Replace Stormline server with Nakama authoritative Lua/Go engine | fixed-tick match handler, backend integration | duplicates gameplay ECS/physics/simulation and AI-native C++/editor contracts; **reference/optional backend adapter only** |
| JS Colyseus server of truth | rapid room/replication proof | another runtime/serializer, WORLD-01 split, unsuitable blanket low-level physics authority; **reference only** |
| Shared native engine headless + validated command ingress | single truth, no GPU, local executable, stable tick + simulation authority | task scheduling and input validation, load isolation, safe replay and ops require real code/proof; **leading proposal** |
| Authoritative distributed multi-region server from v1 | resilience/latency-region | consensus and split-brain hazards, latency/cost/complexity; **FUTURE** |
| Mandatory server rewind for all games | some shooter lag compensation | irreversible state/economy rollback, CPU/memory/replay complexity; **explicitly NOT baseline** |

## Threats and dependency rationale
[OWASP Game Security Framework](https://owasp.github.io/www-project-gamesec-framework/OGSF.html) supplies a risk-based server-authority checklist: validation of critical actions, state under server control, least data exposed to clients, resource/rate controls and peer auth. Use with OWASP ASVS where relevant. It is not proof that the future engine prevents cheating or an authorization to scan client devices. Data isolation, spoofing, replays, timing attacks, privileged admin functions, per-match resource starvation, forged health signals and crash durability require future tests.

Sources informing lifecycle/benchmark design: [Agones GameServer](https://agones.dev/site/docs/reference/gameserver/), [Agones local](https://agones.dev/site/docs/guides/client-sdks/local/), [Nakama fixed tick](https://heroiclabs.com/docs/nakama/concepts/multiplayer/authoritative/), [AWS GameLift lifecycle](https://docs.aws.amazon.com/gameliftservers/latest/developerguide/gamelift-howitworks.html), [Microsoft PlayFab container servers](https://learn.microsoft.com/en-us/gaming/playfab/features/multiplayer/servers/). Technology adaptation requires independent rights/ABI/hosting proof; **no code adopted**.

## Consequences and owner approval gates
Advantages: auditable server authority, independent deployment infrastructure, local-first R$0 mandatory service, smaller security attack surface, headless CPU-only benchmark, portable GAME/WORLD integration. Costs: ticking/validation/observability CPU, operational deployment and anti-abuse design, possible input/latency tradeoffs; "authoritative" alone is not invulnerable to cheating or denial of service.

Owner may APPROVE only after NET-01/WORLD-01/CORE-04 interfaces and code implementation, risk/release class and license, exact native toolchain and security threat review, measurable tick target and overload/rollback/DR proof, headless no-GPU binary, negative authorization tests, cross-OS build where in agreed Scope, 128 traceable test matrix and independent objective audit. This documentary ADR remains **PROPOSED**, never an automatic Zcode unlock; all 80 implementation WOs remain blocked.
