# GAME-04 — Acceptance Matrix: Exactly 128 FUTURE Cases

**RESEARCH #220 / NLE-P00-WO-002-GAME-04 / CODE #60 BLOCKED.** Each scenario below is a **future test requirement only**. **0/128 EXECUTED, 0/128 PASSED, NO SOURCE OR TEST RUNNER.** They do not claim any engine feature exists.

## Test identification, evidence and suite protocol
Each test ID `G04-T001..G04-T128` must eventually bind to test source, seed and fixture SHA, target/toolchain, schema version, expected state/receipt, actual output, replay hash and redacted CI artifact. Missing implementation is not a pass. For determinism, run 100+ seeds or owner-approved sample size across fake clock, stable canonical ordering and simulated packet loss; same-target exact hashes before claims of cross-target numerical fidelity. Future coverage needs unit/property/fuzz/integration, sanitizer, crash/failure injections, headless replay, runtime multi-OS and Web capability gates; no thresholds yet approved.

| ID | Coverage | Future expected assertion | Actual state |
|---|---|---|---|
## Event typing
| G04-T001 | Event typing | reject unknown EventSchemaId | FUTURE / NOT EXECUTED |
| G04-T002 | Event typing | reject unsupported required version | FUTURE / NOT EXECUTED |
| G04-T003 | Event typing | accept known optional additive schema | FUTURE / NOT EXECUTED |
| G04-T004 | Event typing | reject payload wrong field type | FUTURE / NOT EXECUTED |
| G04-T005 | Event typing | preserve explicit unit/scale | FUTURE / NOT EXECUTED |
| G04-T006 | Event typing | reject invalid UTF-8 | FUTURE / NOT EXECUTED |
| G04-T007 | Event typing | reject oversize payload | FUTURE / NOT EXECUTED |
| G04-T008 | Event typing | stable serialize/decode round-trip | FUTURE / NOT EXECUTED |
## Event ordering
| G04-T009 | Event ordering | sort commands by tick phase and origin | FUTURE / NOT EXECUTED |
| G04-T010 | Event ordering | tie-break same actor different seq | FUTURE / NOT EXECUTED |
| G04-T011 | Event ordering | handle stable ID collision with typed failure | FUTURE / NOT EXECUTED |
| G04-T012 | Event ordering | reject past tick ingestion | FUTURE / NOT EXECUTED |
| G04-T013 | Event ordering | reject future tick outside horizon | FUTURE / NOT EXECUTED |
| G04-T014 | Event ordering | no nondeterministic map iteration | FUTURE / NOT EXECUTED |
| G04-T015 | Event ordering | produce identical canonical event hash | FUTURE / NOT EXECUTED |
| G04-T016 | Event ordering | verify read snapshot immutability | FUTURE / NOT EXECUTED |
## Event lifecycle
| G04-T017 | Event lifecycle | generation-scoped subscribe/unsubscribe | FUTURE / NOT EXECUTED |
| G04-T018 | Event lifecycle | unloaded world invalidates token | FUTURE / NOT EXECUTED |
| G04-T019 | Event lifecycle | hot reload invalidates old subscription | FUTURE / NOT EXECUTED |
| G04-T020 | Event lifecycle | unsubscription during callback deferred | FUTURE / NOT EXECUTED |
| G04-T021 | Event lifecycle | same callback cannot recursively emit | FUTURE / NOT EXECUTED |
| G04-T022 | Event lifecycle | handler produces next-phase intent only | FUTURE / NOT EXECUTED |
| G04-T023 | Event lifecycle | listener errors return safe receipt | FUTURE / NOT EXECUTED |
| G04-T024 | Event lifecycle | observer order cannot change world state | FUTURE / NOT EXECUTED |
## Storm prevention
| G04-T025 | Storm prevention | enforce max events per tick | FUTURE / NOT EXECUTED |
| G04-T026 | Storm prevention | enforce max event bytes | FUTURE / NOT EXECUTED |
| G04-T027 | Storm prevention | enforce per-principal rate | FUTURE / NOT EXECUTED |
| G04-T028 | Storm prevention | enforce causal chain depth | FUTURE / NOT EXECUTED |
| G04-T029 | Storm prevention | enforce max subscriber fanout | FUTURE / NOT EXECUTED |
| G04-T030 | Storm prevention | reject self-referential rule DAG | FUTURE / NOT EXECUTED |
| G04-T031 | Storm prevention | prevent queue growth on replay | FUTURE / NOT EXECUTED |
| G04-T032 | Storm prevention | authoritative overflow leaves world unchanged | FUTURE / NOT EXECUTED |
## States
| G04-T033 | States | valid transition commits once | FUTURE / NOT EXECUTED |
| G04-T034 | States | invalid transition guard denied | FUTURE / NOT EXECUTED |
| G04-T035 | States | stale state revision denied | FUTURE / NOT EXECUTED |
| G04-T036 | States | simultaneous transitions have deterministic winner | FUTURE / NOT EXECUTED |
| G04-T037 | States | pause state uses CORE-04 policy | FUTURE / NOT EXECUTED |
| G04-T038 | States | hierarchical state entry/exit order stable | FUTURE / NOT EXECUTED |
| G04-T039 | States | cancelled transition restores last-good | FUTURE / NOT EXECUTED |
| G04-T040 | States | state graph cycle policy validated | FUTURE / NOT EXECUTED |
## Scene flow
| G04-T041 | Scene flow | prepare scene without active mutation | FUTURE / NOT EXECUTED |
| G04-T042 | Scene flow | missing asset returns failure | FUTURE / NOT EXECUTED |
| G04-T043 | Scene flow | missing prefab variant fails safely | FUTURE / NOT EXECUTED |
| G04-T044 | Scene flow | activate at WORLD-01 barrier | FUTURE / NOT EXECUTED |
| G04-T045 | Scene flow | cancel prepared scene without leak | FUTURE / NOT EXECUTED |
| G04-T046 | Scene flow | old scene handles invalidated on retire | FUTURE / NOT EXECUTED |
| G04-T047 | Scene flow | overlay does not unload persistent state | FUTURE / NOT EXECUTED |
| G04-T048 | Scene flow | save handoff resolves durable GUID mapping | FUTURE / NOT EXECUTED |
## Ability activation
| G04-T049 | Ability activation | ungranted ability denied | FUTURE / NOT EXECUTED |
| G04-T050 | Ability activation | requirements and blocked tags enforced | FUTURE / NOT EXECUTED |
| G04-T051 | Ability activation | insufficient resource denies without cooldown | FUTURE / NOT EXECUTED |
| G04-T052 | Ability activation | cast cost and cooldown commit atomically | FUTURE / NOT EXECUTED |
| G04-T053 | Ability activation | interrupt refund policy exact | FUTURE / NOT EXECUTED |
| G04-T054 | Ability activation | charges and shared cooldown groups consistent | FUTURE / NOT EXECUTED |
| G04-T055 | Ability activation | script hook cannot bypass validator | FUTURE / NOT EXECUTED |
| G04-T056 | Ability activation | predicted client ability never grants authority | FUTURE / NOT EXECUTED |
## Cooldowns
| G04-T057 | Cooldowns | TickId equality boundary exact | FUTURE / NOT EXECUTED |
| G04-T058 | Cooldowns | pause and slow simulation policy respected | FUTURE / NOT EXECUTED |
| G04-T059 | Cooldowns | rollover and integer overflow rejected | FUTURE / NOT EXECUTED |
| G04-T060 | Cooldowns | charge regeneration deterministic | FUTURE / NOT EXECUTED |
| G04-T061 | Cooldowns | shared group cannot double-spend | FUTURE / NOT EXECUTED |
| G04-T062 | Cooldowns | zero-duration semantics explicit | FUTURE / NOT EXECUTED |
| G04-T063 | Cooldowns | cooldown reloading maintains remaining ticks | FUTURE / NOT EXECUTED |
| G04-T064 | Cooldowns | client visual timer never authoritative | FUTURE / NOT EXECUTED |
## Damage
| G04-T065 | Damage | armor mitigation deterministic order | FUTURE / NOT EXECUTED |
| G04-T066 | Damage | resistance caps and units checked | FUTURE / NOT EXECUTED |
| G04-T067 | Damage | health never negative beyond policy | FUTURE / NOT EXECUTED |
| G04-T068 | Damage | NaN and infinity rejected | FUTURE / NOT EXECUTED |
| G04-T069 | Damage | integer damage overflow saturated or denied | FUTURE / NOT EXECUTED |
| G04-T070 | Damage | friendly-fire policy enforced | FUTURE / NOT EXECUTED |
| G04-T071 | Damage | physics hit receipt stale rejected | FUTURE / NOT EXECUTED |
| G04-T072 | Damage | kill and assist attribution exactly once | FUTURE / NOT EXECUTED |
## Status effects
| G04-T073 | Status effects | ADD stack policy bounded | FUTURE / NOT EXECUTED |
| G04-T074 | Status effects | REFRESH expiry deterministic | FUTURE / NOT EXECUTED |
| G04-T075 | Status effects | REPLACE priority deterministic | FUTURE / NOT EXECUTED |
| G04-T076 | Status effects | MAX selection deterministic | FUTURE / NOT EXECUTED |
| G04-T077 | Status effects | periodic effects tick once | FUTURE / NOT EXECUTED |
| G04-T078 | Status effects | dispel immunity policy enforced | FUTURE / NOT EXECUTED |
| G04-T079 | Status effects | expired target cancels callbacks | FUTURE / NOT EXECUTED |
| G04-T080 | Status effects | on-hit chain causal loop rejected | FUTURE / NOT EXECUTED |
## Inventory
| G04-T081 | Inventory | split conserves item quantities | FUTURE / NOT EXECUTED |
| G04-T082 | Inventory | merge conserves quantity and IDs | FUTURE / NOT EXECUTED |
| G04-T083 | Inventory | move between containers all-or-nothing | FUTURE / NOT EXECUTED |
| G04-T084 | Inventory | capacity/weight and slots enforced | FUTURE / NOT EXECUTED |
| G04-T085 | Inventory | stale inventory revision rejects | FUTURE / NOT EXECUTED |
| G04-T086 | Inventory | duplicate command cannot mint item | FUTURE / NOT EXECUTED |
| G04-T087 | Inventory | equipment action checks slot rights | FUTURE / NOT EXECUTED |
| G04-T088 | Inventory | rollback/crash cannot duplicate item | FUTURE / NOT EXECUTED |
## Quests
| G04-T089 | Quests | objective consumes committed event only | FUTURE / NOT EXECUTED |
| G04-T090 | Quests | duplicate EventId does not increment | FUTURE / NOT EXECUTED |
| G04-T091 | Quests | out-of-order event cursor rejected | FUTURE / NOT EXECUTED |
| G04-T092 | Quests | quest FSM terminal state consistent | FUTURE / NOT EXECUTED |
| G04-T093 | Quests | branch reset requires authorization | FUTURE / NOT EXECUTED |
| G04-T094 | Quests | reward granted at most once | FUTURE / NOT EXECUTED |
| G04-T095 | Quests | private quest state read ACL enforced | FUTURE / NOT EXECUTED |
| G04-T096 | Quests | restore quest without re-award | FUTURE / NOT EXECUTED |
## Save and recovery
| G04-T097 | Save and recovery | save only after committed tick | FUTURE / NOT EXECUTED |
| G04-T098 | Save and recovery | STAGED never treated as DURABLE | FUTURE / NOT EXECUTED |
| G04-T099 | Save and recovery | journal interruption recovers last-good | FUTURE / NOT EXECUTED |
| G04-T100 | Save and recovery | old schema migration idempotent | FUTURE / NOT EXECUTED |
| G04-T101 | Save and recovery | unknown required schema fails closed | FUTURE / NOT EXECUTED |
| G04-T102 | Save and recovery | content fingerprint mismatch detected | FUTURE / NOT EXECUTED |
| G04-T103 | Save and recovery | old world epoch cannot load stale receipt | FUTURE / NOT EXECUTED |
| G04-T104 | Save and recovery | pending outbound side effect not replayed twice | FUTURE / NOT EXECUTED |
## Network security
| G04-T105 | Network security | client fabricated damage rejected | FUTURE / NOT EXECUTED |
| G04-T106 | Network security | client forged quest grant rejected | FUTURE / NOT EXECUTED |
| G04-T107 | Network security | client duplicated inventory transfer rejected | FUTURE / NOT EXECUTED |
| G04-T108 | Network security | server verifies player/seat role | FUTURE / NOT EXECUTED |
| G04-T109 | Network security | late command stale tick safely denied | FUTURE / NOT EXECUTED |
| G04-T110 | Network security | replication filters secret payloads | FUTURE / NOT EXECUTED |
| G04-T111 | Network security | CUE loss cannot change committed result | FUTURE / NOT EXECUTED |
| G04-T112 | Network security | server replay hash matches authoritative resimulation | FUTURE / NOT EXECUTED |
## Scripts and authoring
| G04-T113 | Scripts and authoring | GAME-02 host call only creates intent | FUTURE / NOT EXECUTED |
| G04-T114 | Scripts and authoring | script quota violation fails safely | FUTURE / NOT EXECUTED |
| G04-T115 | Scripts and authoring | visual/text scripting same authority gateway | FUTURE / NOT EXECUTED |
| G04-T116 | Scripts and authoring | unauthorized MCP cannot emit live event | FUTURE / NOT EXECUTED |
| G04-T117 | Scripts and authoring | Editor/CLI/MCP preview same semantic diff | FUTURE / NOT EXECUTED |
| G04-T118 | Scripts and authoring | DATA-04 CAS conflict rejected | FUTURE / NOT EXECUTED |
| G04-T119 | Scripts and authoring | untrusted rule schema cannot call OS/network | FUTURE / NOT EXECUTED |
| G04-T120 | Scripts and authoring | world unload stops script-generated events | FUTURE / NOT EXECUTED |
## Performance and targets
| G04-T121 | Performance and targets | headless deterministic stress fixture | FUTURE / NOT EXECUTED |
| G04-T122 | Performance and targets | p50/p95/p99 dispatcher measured not assumed | FUTURE / NOT EXECUTED |
| G04-T123 | Performance and targets | allocator budget under bounded fanout | FUTURE / NOT EXECUTED |
| G04-T124 | Performance and targets | Windows target compile and replay future | FUTURE / NOT EXECUTED |
| G04-T125 | Performance and targets | Linux target compile and replay future | FUTURE / NOT EXECUTED |
| G04-T126 | Performance and targets | macOS Apple Silicon target replay future | FUTURE / NOT EXECUTED |
| G04-T127 | Performance and targets | Web target capability/fallback future | FUTURE / NOT EXECUTED |
| G04-T128 | Performance and targets | two distinct game genres share core unchanged | FUTURE / NOT EXECUTED |

## Mandatory future proof
Reproduce one original platformer/puzzle ruleset and one original shooter/RPG ruleset through the identical GAME-04 APIs (no Core fork); verify replay hash, effect ordering, item/quest idempotency, scene/save recovery and NET authority boundaries. Independent Windows/Linux/macOS native and browser/headless feasibility matrices; p50/p95/p99 and high-tail gameplay budget defined only after baseline measurements. **Neither platform support, 128 tests nor benchmarks have run.**
