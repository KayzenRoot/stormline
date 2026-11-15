# NET-02 — Authoritative Dedicated, Headless Game Server Architecture v0.1

**Research WO:** NLE-P00-WO-002-NET-02 | **research issue:** #232 | **future coding:** [#63](https://github.com/KayzenRoot/stormline/issues/63) OPEN/BLOCKED | **BASE main:** `ef1eb35c8b11d239801e73c112b8c936835b9cdc` | 2026-11-15. **P00 DOCUMENTATION ONLY, PROPOSED.** No dedicated server process, binary, ECS, transport, tick, game match, test, deployment, benchmark or license decision has been implemented.

## 1. Product scope and objective proof
Catalog: "**Loop headless, simulação no servidor, validation commands e deployment local**". Acceptance: "**Servidor executa sem GPU e rejeita estado cliente arbitrário**". Target: original native Stormline dedicated server mode that can start in a local test environment, run the same approved deterministic/fixed-step gameplay rule path as a native client project where applicable (no special server fork), validate input intents before mutating authoritative state, safely host one or more logical matches with bounded isolation and intentionally release resources, and expose deployment health/observability without relying on a paid cloud service.

A single playable test, a documented protocol or a Kubernetes pod specification would not prove the catalog acceptance. Required **future** evidence: compiled headless build and actual launch without any graphics API/GPU/display resource, fixed-tick timeline, two or more authenticated client intents, forged/arbitrary client state rejected, reproducible gameplay state receipts and expected role isolation, clean stop/recovery and measured tick utilization/latency under impaired networks. This research contains neither binaries nor proof.

### Proposed server authority path
```text
Authenticated NET-01 transport -> network ingress admission & schema/size limits
 -> NET-05 session ticket/principal -> NET-02 authenticated match/actor binding
 -> transport monotonic timestamp + sequence/epoch -> bounded per-principal input queue
 -> CORE-04 TickId / CORE-03 ordered barrier and scheduled jobs
 -> NET-02 validation gateway (capability, ownership, epoch, phase, rate, plausibility)
 -> GAME-04 typed GameCommandGateway -> WORLD-01 authoritative ECS commit / SIM motion receipts
 -> committed authoritative state & application receipts (not raw client claims)
 -> NET-03 future snapshot/interest/replication, NET-04 future client reconciliation
 -> DATA-04 durable checkpoint/journal only when explicitly requested and validated
 -> NET-01 secure outbound profile, no presentation GPU requirement
```

NET-02 treats **client data as input proposals**: player movement/action target/ability intent, never authoritative Health/Position/Inventory/Quest rewards, World revision or direct ECS memory mutation. Correct client prediction is allowed as display-only (NET-04), not an authority grant.

## 2. Formal dependencies and strict module ownership
| Module | Owns authoritative truth / required input | NET-02 must NOT duplicate |
|---|---|---|
| **NET-01** *(catalog prerequisite)* | secure connection, message delivery/epoch, transport ACK, crypto and bounded transport queue | custom sockets/UDP/QUIC, network cipher/TLS, congestion, NAT/STUN/TURN |
| **WORLD-01** *(catalog prerequisite)* | stable entity+world generation identity, ECS component schemas, authoritative world write and snapshot barriers | second ECS, direct packet-to-component writes or borrowed pointer lifetime beyond barrier |
| **CORE-04** *(catalog prerequisite)* | authoritative TickId/fixed-step clock, monotonic simulation epoch, pause/replay policies | independent wallclock-derived tick in server process |
| **CORE-03/02/06** | jobs/read-write sets, memory/queue quotas and diagnostics | ad hoc thread pool, lock-free unsafe callback or unbounded global logs |
| **GAME-04** | versioned game state, abilities, cooldown, damage, inventory/quests, validated gameplay commands and game event receipts | new damage/loot/reward engine or raw client grant |
| **SIM-01..05** | physics/character motor/animation/vehicle grounded sim with accepted intents | arbitrary teleport/fake client physics |
| **NET-03** | world snapshot/delta/priority/interest, per-client visibility and outgoing replication | NET-02 broadcasting whole ECS including fog/secret entities |
| **NET-04** | client prediction/correction/lag compensation/rollback policies where approved | unbounded rewind of authoritative world or cross-player state |
| **NET-05** | identity/session/lobby/matchmaker, token issuer, session discovery and allocation; dedicated-server lifecycle adapter only checks claims | matchmaking/secret issuance or permanent lobby database |
| **NET-06** | layered anti-abuse/rate controls, security incident/fuzzing and cross-service attack analytics | claiming single command validation equals complete anti-cheat/DDoS prevention |
| **DATA-02/04/05** | asset identity, versioned save/checkpoints/CAS/journal and packaged content | ad hoc unencrypted persistence, invented distributed DB transactions or raw asset importer |
| **GAME-01/02/03, WORLD-02, EDIT/CLI/MCP/AI-01** | input action frames, sandbox scripting, UI, world scenes/prefabs, stage/validate/apply authoring under authorization | gameplay server accepting arbitrary editor/MCP shell, hot-reload code or live privileged changes |
| **PLAT/CORE-01** | OS process/service configuration, platform and socket interface | mandatory cloud Kubernetes dependency, custom system daemon or GPU initialization |

Formal catalog dependency is **NET-01 · WORLD-01 · CORE-04** only, all *research documented* and none implemented. The others are integration contracts, not reasons to rewrite the registry DAG.

## 3. Process and match lifecycle
Propose **`ServerProcessLifecycleV1`**: `BOOTSTRAP -> CONFIG_VALIDATING -> BINDING -> WARMUP -> READY -> DRAINING -> TERMINATED` with explicit `FAILED/UNHEALTHY`. Health readiness means meaningful ability to accept a new match and progress ticks under configured budget, not simply HTTP 200/socket listening. `MatchInstanceLifecycleV1`: `CREATED -> ALLOCATED -> LOADING -> WAITING_FOR_PLAYERS -> RUNNING -> COMPLETING -> FINALIZING -> CLOSED` plus typed failure. Separation process readiness vs individual-match readiness vs game simulation health must remain visible.

- Start from immutable versioned headless server pack/capability/config manifest; no graphics context/device/window or renderer thread required. Audio/VFX/UI cue sinks may be null/headless without affecting authoritative game events. Tick rate remains sourced from CORE-04, configurable only through validated policy, no frame time coupling.
- For local first proof, **one isolated process hosting one match** is the risk-minimal baseline. Future process with multiple match instances requires explicit per-match resource and thread isolation. Each match owns `MatchIdV1`, `WorldEpoch`, player principal map, bounded ingress queue and route/capability token; zero cross-match pointer/callback sharing. Multi-process isolation (one OS process per match) is a separate operational option, **not guaranteed by a C++ namespace or tenant ID**.
- Accept a connection only after NET-01 authenticated transport and NET-05 authorized short-lived join claim; verify role, expiry/audience, match allocation epoch, ownership, replay/nonces, rate, scene/capability/asset revision. A transport handshake is not player session acceptance. Ban/revoke/quarantine path returns typed error and non-sensitive telemetry.
- On graceful shutdown stop new allocations/join, drain bounded inflight safe game commands, finalize one durable operation with DATA-04 CAS/ack only if required, emit connection close and health status, then terminate. On SIGTERM allow a documented grace period and be prepared for SIGKILL; never claim guaranteed saving when infrastructure hard-kills. NET-05 orchestrator can request shutdown but cannot assume cross-process save atomicity.

## 4. Fixed-step authoritative execution and scheduling
For each `TickId`: freeze admitted and normalized input batch; validate session/time window/sequence and action target; order by documented stable semantic comparator (tick source, producer/player ordinal, command id, sequence) **not by nondeterministic thread arrival**, if fairness policy permits; calculate validated authoritative intents at a deterministic barrier; call GAME-04 command dispatcher, WORLD-01/SIM physics and stable commit in approved CORE-03 DAG; publish immutable state/receipts; hand off to NET-03 future replication, diagnostics and optional DATA durable checkpoint without blocking the simulation thread.

Time concerns: CORE-04 TickId authoritative; CORE-01 monotonic I/O time for deadlines/RTT, **neither network packet arrival timestamp nor UTC is authoritative simulation tick**. Input policy defines max ahead/late windows, duplication, reordering, bounded backlog/catch-up, timing jitter compensation and strategy for missing inputs. "Predict no input", "hold last direction", "pause match" or "simulate neutral action" choices are **game-policy decisions**, not magical global defaults. No infinite catch-up spirals if the simulation load exceeds tick budget. Schedule overload -> metrics and explicit degrade/drop or terminate; never silently skip critical authoritative GAME-04 mutation.

Determinism is **within a pinned backend+platform+build/seed and specified fixed-point policy** until proven; no claim bitwise cross-CPU/GPU/OS determinism of floating point. Input log replay needs versioned schema, seed, authoritative snapshots, game rule/scene assets and resimulation proof. Ban/give reward verification uses GAME-04 durable receipt and idempotency, not only matching packet hash.

## 5. Server command validation pipeline
1. **Ingress parse:** length/schema/version/endianness, authentication tag/session binding, decoded size limits, decompression cap, ingress rate, valid connection generation. Hard-reject raw client state snapshots or arbitrary component writes.
2. **Actor authorization:** NET-05/NET-02 principal and match membership; controlled actor ownership/role/capabilities; server-owned entities and fog-private state remain unaddressable. No client-provided magic user ID/role overrides a server ticket.
3. **Tick/sequence:** stale epoch/tick, future input, duplicate and out-of-order window, monotonic counter wrap; limited per actor inbox/CPU per tick; replay window and idempotent receipts.
4. **Game rules:** GAME-04 validated ability target, cooldown, energy/cost, inventory item identity, line-of-sight/physics query and quest/reward scope; SIM motor movement physics and speed caps. A client sends **ActionIntent**, not "I hit player for 9999" or "grant legendary loot".
5. **Commit receipts:** apply only through allowed WORLD-01/GAME-04 APIs on tick barrier, never from I/O callback. Explicit `REJECTED`, `VALIDATED_PENDING`, `COMMITTED`, `REPLAYED_DUPLICATE` and `RETRYABLE_ERROR` with normalized reason and budget usage; an ACK from NET-01 means **transport delivery**, not game commit.
6. **Outbound:** NET-03 owns interest-filtered snapshots; do not leak hidden opponent inventory/position/fog data in "full server state" debugging. Authorization extends to replay logs, observability and spectator access. NET-06 records abuse detection without raw PII/secret.

## 6. Match isolation, security and adverse clients
- Every resource carries match/tenant/world epoch/generation; multitenant allocator must not reuse stale handles or mix one match's event queue, scripts, RNG, asset/snapshot filters, persistent state or credentials with another. Match-local memory, CPU per tick, ingress/outbound capacity, log volume, script gas/time quotas and player limits are explicit and measured before enabling multi-match per process.
- Security model follows [OWASP Game Security Framework authoritative server guidance](https://owasp.github.io/www-project-gamesec-framework/OGSF.html). It emphasizes authoritative server, validation of player actions, no client authority over health/inventory/position, restricted data exposure, network protection and cheat risks. This is a **threat model**, not anti-cheat completeness.
- Client can lie, reorder, fabricate time, drop input, exploit floating-point, reconnect under different networks, DDoS, cause algorithmic complexity, amplify outbound snapshot, script event chains, inflate inventory/quest and use timing oracle. Harden crypto/transport via NET-01 and abuse via NET-06; server validates intent and uses stable saturation/overflow rules. Kernel-level anti-cheat, invasive client scanning and ban appeals are beyond this slice.
- Do not expose operator APIs or credentials on public gameplay port. External diagnostic/config/Editor/CLI/MCP actions require authenticated admin identity, independent role/capability, audit trail and no arbitrary code or shell, no endpoint SSRF, no raw ECS patch and no "debug grant item" in production. Trusted development environment and prod must remain segregated.
- Crash handling: no guaranteed exactly-once arbitrary external side effects across server process crash; use durable idempotency and DATA-04 game transactional boundaries. On lease expiry, missing committed checkpoint or source content mismatch, **fail closed** or controlled rebuild with explicit recovery reason.

## 7. Rollback, replication and fairness boundaries
- Server **does not require rollback by default**. Start with forward authoritative fixed tick and idempotent commands. NET-04 decides client prediction/reconciliation, rewind/lag compensation and limited historical state for hit validation, with server-pinned per-user fairness/latency policy. Independent snapshots for NET-03 and durable save checkpoints for DATA-04 have different retention/replay contracts.
- If rollback/rewind becomes approved for NET-02 critical gameplay, require bounded horizon in ticks/memory, immutable causality/event log, deterministic physics or safe partial rewind policy, no double grants, anti-wallhack/cross-match visibility, and snapshot replay proofs under loss/late input. No speculative rollback of purchases, storage, irreversible rewards or external calls.
- Tick rate, input acceptance window and bandwidth must balance CPU/game fairness. Lag spikes cannot cause self-authoritative client world state; explicit rate cap and operator alarms.
- Multi-region/replicated authoritative world and distributed consensus/quorum are **FUTURE** separate architecture, not guaranteed by running replicas or allocating a Kubernetes Pod. Avoid shared-world split brain with fencing lease/epoch, safe failover and DATA journal if eventually attempted.

## 8. Local-first deployment and optional orchestration
**NECESSARY future first implementation:** native headless server on localhost with CLI config/test harness and no GPU. Isolate filesystem/read-only assets, allowlisted game UDP/TCP ports, binding address/IPv4/IPv6, ephemeral test certificate identity, nonroot service, signal/health/readiness probes, bounded logs and encrypted session; one process one match with deterministic synthetic action fixture and crash recovery policy. Local no mandatory Kubernetes/PlayFab/GameLift/Agones/Nakama subscription.

**IMPORTANT future optional container:** reproducible multi-stage build with pinned minimal image digest/SBOM, nonroot, read-only root FS, dropped capabilities/seccomp/user namespaces where supported, cgroup memory/CPU/pids, graceful TERM and startup probes, secret injection via secure environment/mount with least privilege and no secret logs; no docker.sock mount. Container network/UDP port mapping, NAT+source IP and cloud IPv6 readiness must be *tested*, not assumed. Local integration can use OCI/container runtime, but no cluster orchestrator is required.

**FUTURE operational adapter:** Agones on Kubernetes for allocations/health/shutdown/ports via SDK; alternatives Nakama fixed-tick authoritative match runtime, Colyseus room-based JS, Open Match matchmaking only, PlayFab/Amazon GameLift managed services. They are **comparators/optional deployment adapters**, NOT replacement for Stormline native authoritative gameplay, not mandatory or necessarily free. [Agones GameServer lifecycle](https://agones.dev/site/docs/reference/gameserver/) separates creation/Ready/Allocated from match state; compare [local SDK testing](https://agones.dev/site/docs/guides/client-sdks/local/) without requiring cluster. Costs, service terms, platform licensing and availability must be revalidated before adoption.

## 9. Future acceptance/phase and proof
**NECESSARY:** native headless without GPU; CORE-04 fixed tick and CORE-03 barrier; NET-01 authenticated input; WORLD-01 single authoritative commit; GAME-04 validated simple move/ability; local spawn/health/shutdown; one match, deterministic replay and invalid state rejection; two independent fixture clients; testing with no cloud subscription.
**IMPORTANT:** bounded multi-match isolation, configurable physical load, persistence/restart, match lifecycle diagnostics, service/container adapter and cross-target Linux/Windows/macOS CPU builds. **FUTURE:** multi-region, large-scale Agones fleet, matchmaking vendor, cross-region failover, rollback-lag compensation and sophisticated anti-cheat systems. None are implemented or approved in this planning phase.
See [ADR-0048](../adr/0048-net-02-authoritative-headless-server-tick-command-gateway.md), [technology and licensing](../research/net-02-server-technology-license-matrix.md), [semantic contracts](../contracts/net-02-dedicated-server-api.md), [128 FUTURE acceptance tests](../testing/net-02-acceptance-matrix.md), [benchmark protocol](../research/net-02-server-benchmark-protocol.md).
