# NET-02 — Exactly 128 FUTURE Dedicated Server Acceptance Tests

**Research issue #232 / WO NLE-P00-WO-002-NET-02 / code #63 OPEN/BLOCKED.** IDs `N02-T001..N02-T128` are **FUTURE / NOT EXECUTED**; total specified=128, executed=0, passed=0 because **NO runnable dedicated server or test harness exists**, not because tests failed. GitHub Docs Validation is P00 document CI and cannot be counted as server build or runtime pass.

For every future test require: expected rule/contract section and proof obligation, Git base/head SHA, approved ADR and backend revisions, deterministic fixture seed and original game assets, real native target OS/arch, CORE-04 tick policy, world/scene hashes, two or more client role/credentials when applicable, exact commands/CI job, measured result and redacted trace/memory/CPU data, real test source, owner permissions, risk and regression status. Separate simulated network loss/CPU trace from live LAN/cloud; numeric targets remain **TBD not owner-approved**.

| ID | Future category | Expected assertion (must be tested later) | Current state |
|---|---|---|---|
## Headless boot and target
| N02-T001 | Headless boot and target | server binary launches without physical GPU | FUTURE / NOT EXECUTED |
| N02-T002 | Headless boot and target | no graphics device/window API linkage | FUTURE / NOT EXECUTED |
| N02-T003 | Headless boot and target | audio/UI/VFX null consumers preserve gameplay | FUTURE / NOT EXECUTED |
| N02-T004 | Headless boot and target | local CLI boot only approved config | FUTURE / NOT EXECUTED |
| N02-T005 | Headless boot and target | server process startup version digest logged | FUTURE / NOT EXECUTED |
| N02-T006 | Headless boot and target | bind IPv4 or IPv6 only per policy | FUTURE / NOT EXECUTED |
| N02-T007 | Headless boot and target | unsupported OS target typed failure | FUTURE / NOT EXECUTED |
| N02-T008 | Headless boot and target | headless shutdown returns nonzero on fatal invalid config | FUTURE / NOT EXECUTED |
## Fixed tick and scheduler
| N02-T009 | Fixed tick and scheduler | CORE-04 TickId increases exactly once | FUTURE / NOT EXECUTED |
| N02-T010 | Fixed tick and scheduler | variable render FPS never changes server tick | FUTURE / NOT EXECUTED |
| N02-T011 | Fixed tick and scheduler | network wallclock cannot override fixed tick | FUTURE / NOT EXECUTED |
| N02-T012 | Fixed tick and scheduler | CORE-03 barrier orders system writes | FUTURE / NOT EXECUTED |
| N02-T013 | Fixed tick and scheduler | no recursive ingress changes ECS mid-tick | FUTURE / NOT EXECUTED |
| N02-T014 | Fixed tick and scheduler | bounded tick catch-up on overload | FUTURE / NOT EXECUTED |
| N02-T015 | Fixed tick and scheduler | overrun metric reflects actual missed budget | FUTURE / NOT EXECUTED |
| N02-T016 | Fixed tick and scheduler | tick pause/step policy authorized and versioned | FUTURE / NOT EXECUTED |
## Command ingress and schema
| N02-T017 | Command ingress and schema | malformed action schema rejected before allocation | FUTURE / NOT EXECUTED |
| N02-T018 | Command ingress and schema | oversized payload rejected by length bound | FUTURE / NOT EXECUTED |
| N02-T019 | Command ingress and schema | unknown command type rejected | FUTURE / NOT EXECUTED |
| N02-T020 | Command ingress and schema | client full-world snapshot never accepted as intent | FUTURE / NOT EXECUTED |
| N02-T021 | Command ingress and schema | client health/XP/score override rejected | FUTURE / NOT EXECUTED |
| N02-T022 | Command ingress and schema | future tick beyond horizon rejected | FUTURE / NOT EXECUTED |
| N02-T023 | Command ingress and schema | stale client action epoch denied | FUTURE / NOT EXECUTED |
| N02-T024 | Command ingress and schema | bounded inbox protects from flood | FUTURE / NOT EXECUTED |
## Identity and actor ownership
| N02-T025 | Identity and actor ownership | NET-01 TLS handshake alone never authorizes game | FUTURE / NOT EXECUTED |
| N02-T026 | Identity and actor ownership | expired signed match ticket rejected | FUTURE / NOT EXECUTED |
| N02-T027 | Identity and actor ownership | ticket match audience must match process | FUTURE / NOT EXECUTED |
| N02-T028 | Identity and actor ownership | replayed join nonce rejected | FUTURE / NOT EXECUTED |
| N02-T029 | Identity and actor ownership | revoked session cannot run commands | FUTURE / NOT EXECUTED |
| N02-T030 | Identity and actor ownership | actor ownership cannot be forged | FUTURE / NOT EXECUTED |
| N02-T031 | Identity and actor ownership | player role cannot escalate to admin | FUTURE / NOT EXECUTED |
| N02-T032 | Identity and actor ownership | NET-05 issuer and epoch revalidated on reconnect | FUTURE / NOT EXECUTED |
## GAME-04 rule authority
| N02-T033 | GAME-04 rule authority | damage intent validates cooldown+LOS | FUTURE / NOT EXECUTED |
| N02-T034 | GAME-04 rule authority | client loot grant rejected without game rules | FUTURE / NOT EXECUTED |
| N02-T035 | GAME-04 rule authority | quest reward duplicate commit prevented | FUTURE / NOT EXECUTED |
| N02-T036 | GAME-04 rule authority | ability cost applied atomically with effect | FUTURE / NOT EXECUTED |
| N02-T037 | GAME-04 rule authority | inventory item IDs source authoritative | FUTURE / NOT EXECUTED |
| N02-T038 | GAME-04 rule authority | movement request validated through motor | FUTURE / NOT EXECUTED |
| N02-T039 | GAME-04 rule authority | game event commit separate from transport ACK | FUTURE / NOT EXECUTED |
| N02-T040 | GAME-04 rule authority | GAME-04 script sandbox cannot mutate server raw ECS | FUTURE / NOT EXECUTED |
## World and physics ownership
| N02-T041 | World and physics ownership | WORLD-01 is sole authoritative component commit | FUTURE / NOT EXECUTED |
| N02-T042 | World and physics ownership | entity generation prevents stale pointer write | FUTURE / NOT EXECUTED |
| N02-T043 | World and physics ownership | SIM motor intent rejects teleport cheat | FUTURE / NOT EXECUTED |
| N02-T044 | World and physics ownership | collision/physics receipt aligned TickId | FUTURE / NOT EXECUTED |
| N02-T045 | World and physics ownership | physics step deterministic same pinned target | FUTURE / NOT EXECUTED |
| N02-T046 | World and physics ownership | world source hash mismatch fails safe | FUTURE / NOT EXECUTED |
| N02-T047 | World and physics ownership | scene load failure leaves world last-good | FUTURE / NOT EXECUTED |
| N02-T048 | World and physics ownership | server cannot call client render transforms for truth | FUTURE / NOT EXECUTED |
## Match lifecycle
| N02-T049 | Match lifecycle | new match only from valid allocation | FUTURE / NOT EXECUTED |
| N02-T050 | Match lifecycle | ALLOCATED to RUNNING requires readiness | FUTURE / NOT EXECUTED |
| N02-T051 | Match lifecycle | closed match cannot restart old epoch | FUTURE / NOT EXECUTED |
| N02-T052 | Match lifecycle | server process health distinct match health | FUTURE / NOT EXECUTED |
| N02-T053 | Match lifecycle | joining during DRAINING denied | FUTURE / NOT EXECUTED |
| N02-T054 | Match lifecycle | graceful shutdown bounds command drain | FUTURE / NOT EXECUTED |
| N02-T055 | Match lifecycle | forced SIGKILL recovery typed not guaranteed | FUTURE / NOT EXECUTED |
| N02-T056 | Match lifecycle | match completion releases lease and quotas | FUTURE / NOT EXECUTED |
## Per-match isolation
| N02-T057 | Per-match isolation | cross match client message rejected | FUTURE / NOT EXECUTED |
| N02-T058 | Per-match isolation | cross match entity ID read rejected | FUTURE / NOT EXECUTED |
| N02-T059 | Per-match isolation | match script RNG streams independent | FUTURE / NOT EXECUTED |
| N02-T060 | Per-match isolation | match event queue quota isolated | FUTURE / NOT EXECUTED |
| N02-T061 | Per-match isolation | one match overload cannot corrupt neighbor | FUTURE / NOT EXECUTED |
| N02-T062 | Per-match isolation | match memory ownership released after close | FUTURE / NOT EXECUTED |
| N02-T063 | Per-match isolation | stale generation callback cannot reenter | FUTURE / NOT EXECUTED |
| N02-T064 | Per-match isolation | private match diagnostics redacted per principal | FUTURE / NOT EXECUTED |
## Rate limits and anti-cheat
| N02-T065 | Rate limits and anti-cheat | fire-rate exceeds GAME-04 cooldown rejected | FUTURE / NOT EXECUTED |
| N02-T066 | Rate limits and anti-cheat | superhuman movement velocity denied | FUTURE / NOT EXECUTED |
| N02-T067 | Rate limits and anti-cheat | out of line-of-sight attack denied | FUTURE / NOT EXECUTED |
| N02-T068 | Rate limits and anti-cheat | packet replay/sequence wrap bounded | FUTURE / NOT EXECUTED |
| N02-T069 | Rate limits and anti-cheat | resource exhaustion path returns quota error | FUTURE / NOT EXECUTED |
| N02-T070 | Rate limits and anti-cheat | NET-06 abuse and ban signal typed not full anti-cheat | FUTURE / NOT EXECUTED |
| N02-T071 | Rate limits and anti-cheat | client time skew cannot buy unfair authority | FUTURE / NOT EXECUTED |
| N02-T072 | Rate limits and anti-cheat | spectator role cannot submit actor moves | FUTURE / NOT EXECUTED |
## Input ordering and replay
| N02-T073 | Input ordering and replay | input batch frozen before authoritative tick | FUTURE / NOT EXECUTED |
| N02-T074 | Input ordering and replay | same target+seed produces replay hash | FUTURE / NOT EXECUTED |
| N02-T075 | Input ordering and replay | duplicate intent idempotent receipt | FUTURE / NOT EXECUTED |
| N02-T076 | Input ordering and replay | out-of-order arrival sorted per policy | FUTURE / NOT EXECUTED |
| N02-T077 | Input ordering and replay | late input outside window discarded | FUTURE / NOT EXECUTED |
| N02-T078 | Input ordering and replay | simultaneous actors deterministic tie-break | FUTURE / NOT EXECUTED |
| N02-T079 | Input ordering and replay | reconnect does not replay irreversible reward | FUTURE / NOT EXECUTED |
| N02-T080 | Input ordering and replay | log compaction preserves replay needed cursor | FUTURE / NOT EXECUTED |
## Rollback and fairness
| N02-T081 | Rollback and fairness | rollback default DISABLED | FUTURE / NOT EXECUTED |
| N02-T082 | Rollback and fairness | NET-04 rewind requires approved horizon | FUTURE / NOT EXECUTED |
| N02-T083 | Rollback and fairness | past snapshot replay scoped per match | FUTURE / NOT EXECUTED |
| N02-T084 | Rollback and fairness | irreversible inventory reward not rewound | FUTURE / NOT EXECUTED |
| N02-T085 | Rollback and fairness | lag compensation does not leak hidden players | FUTURE / NOT EXECUTED |
| N02-T086 | Rollback and fairness | excessively late hit rejected per fairness policy | FUTURE / NOT EXECUTED |
| N02-T087 | Rollback and fairness | CPU/memory rewind budget enforced | FUTURE / NOT EXECUTED |
| N02-T088 | Rollback and fairness | forward-only gameplay passes without history | FUTURE / NOT EXECUTED |
## Persistence and recovery
| N02-T089 | Persistence and recovery | DATA-04 CAS checkpoint receipt distinct tick | FUTURE / NOT EXECUTED |
| N02-T090 | Persistence and recovery | stale checkpoint source revision denied | FUTURE / NOT EXECUTED |
| N02-T091 | Persistence and recovery | process crash yields explicit recovery state | FUTURE / NOT EXECUTED |
| N02-T092 | Persistence and recovery | duplicate outbox side effect idempotent | FUTURE / NOT EXECUTED |
| N02-T093 | Persistence and recovery | partial checkpoint restore last-good | FUTURE / NOT EXECUTED |
| N02-T094 | Persistence and recovery | no raw log contains private inventory/token | FUTURE / NOT EXECUTED |
| N02-T095 | Persistence and recovery | durable save not assumed from transport ACK | FUTURE / NOT EXECUTED |
| N02-T096 | Persistence and recovery | checkpoint replay validates schema/content hash | FUTURE / NOT EXECUTED |
## Local deployment
| N02-T097 | Local deployment | standalone local process needs no Kubernetes | FUTURE / NOT EXECUTED |
| N02-T098 | Local deployment | local port clash returns bind error | FUTURE / NOT EXECUTED |
| N02-T099 | Local deployment | nonroot process can bind scoped port | FUTURE / NOT EXECUTED |
| N02-T100 | Local deployment | read-only game assets and config enforced | FUTURE / NOT EXECUTED |
| N02-T101 | Local deployment | health readiness checks tick progress not 200 only | FUTURE / NOT EXECUTED |
| N02-T102 | Local deployment | graceful TERM and forced stop tested future | FUTURE / NOT EXECUTED |
| N02-T103 | Local deployment | runtime log and secret redaction future | FUTURE / NOT EXECUTED |
| N02-T104 | Local deployment | headless container under no-GPU quota future | FUTURE / NOT EXECUTED |
## Cloud/orchestration optional
| N02-T105 | Cloud/orchestration optional | Agones SDK not required local run | FUTURE / NOT EXECUTED |
| N02-T106 | Cloud/orchestration optional | Agones allocation adapter lifecycle future | FUTURE / NOT EXECUTED |
| N02-T107 | Cloud/orchestration optional | missing cluster produces explicit not configured | FUTURE / NOT EXECUTED |
| N02-T108 | Cloud/orchestration optional | GameLift/PlayFab billing approval required | FUTURE / NOT EXECUTED |
| N02-T109 | Cloud/orchestration optional | Open Match not mistaken for game simulation | FUTURE / NOT EXECUTED |
| N02-T110 | Cloud/orchestration optional | container image digest and SBOM future | FUTURE / NOT EXECUTED |
| N02-T111 | Cloud/orchestration optional | cloud ingress ports documented and least privilege | FUTURE / NOT EXECUTED |
| N02-T112 | Cloud/orchestration optional | no automatic service paid account provisioning | FUTURE / NOT EXECUTED |
## Stress and observability
| N02-T113 | Stress and observability | 8 player authoritative fixture future | FUTURE / NOT EXECUTED |
| N02-T114 | Stress and observability | 16 player authoritative fixture future | FUTURE / NOT EXECUTED |
| N02-T115 | Stress and observability | 32 player authoritative fixture future | FUTURE / NOT EXECUTED |
| N02-T116 | Stress and observability | 64 player authoritative fixture future | FUTURE / NOT EXECUTED |
| N02-T117 | Stress and observability | tick CPU p50/p95/p99 raw sample future | FUTURE / NOT EXECUTED |
| N02-T118 | Stress and observability | memory/ingress/queue resource slope future | FUTURE / NOT EXECUTED |
| N02-T119 | Stress and observability | packet loss/jitter/disconnect simulation future | FUTURE / NOT EXECUTED |
| N02-T120 | Stress and observability | server recovery and log correlation future | FUTURE / NOT EXECUTED |
## Governance and release gates
| N02-T121 | Governance and release gates | source and ADR pinned before code activation | FUTURE / NOT EXECUTED |
| N02-T122 | Governance and release gates | license/supply chain CVE proof future | FUTURE / NOT EXECUTED |
| N02-T123 | Governance and release gates | negative client-state mutation suite future | FUTURE / NOT EXECUTED |
| N02-T124 | Governance and release gates | cross OS native headless smoke future | FUTURE / NOT EXECUTED |
| N02-T125 | Governance and release gates | role scoped Editor/CLI/MCP parity future | FUTURE / NOT EXECUTED |
| N02-T126 | Governance and release gates | architecture review no HIGH/CRITICAL future | FUTURE / NOT EXECUTED |
| N02-T127 | Governance and release gates | 128 tests remain unexecuted at P00 | FUTURE / NOT EXECUTED |
| N02-T128 | Governance and release gates | 80 implementation work orders remain BLOCKED | FUTURE / NOT EXECUTED |

## Future proof map (nothing executed)
- Headless no-GPU process + real link/load trace, valid and malicious client test, per-match/actor isolation, fixed TickId, WORLD-01 single authority, GAME-04 game validation, NET-01 secure transport, NET-03 replication only when built, NET-04 lag-comp policy only when approved, NET-05 session tickets and NET-06 adversarial checks.
- Fault injection: 0/1/5/10% packet loss and burst, jitter 0/5/20/50 ms, RTT 1/20/60/120ms, process crash SIGTERM/SIGKILL, reauth revoked, overload and wallclock skew, malformed intent/oversized asset/anti-amplification, disallowed administrative shell.
- Eight, sixteen, thirty-two and sixty-four simulated clients are **future workload axes**, not a promise of supported population or performance; real capacity and hardware tiers require measured baselines. Metrics p50/p95/p99 and economics vs native/OCI/Agones optional future.
- Owner must approve risk/Scope/DoD/ABI/license/dependencies before changing future code #63 to EXECUTOR_READY. These 128 specs do not unlock any packet.
