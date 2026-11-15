# GAME-05 — Exactly 128 FUTURE Acceptance Test Scenarios

**Research #224 / WO NLE-P00-WO-002-GAME-05 / implementation #61 BLOCKED**. All IDs `G05-T001..G05-T128` are **FUTURE / NOT EXECUTED**. There is no runnable test runner, engine code, game project, binary, Web sample or benchmark. **Executed = 0; passed = 0; failed = 0.** Future matrix is a specification only.

Each future case must bind a fixture hash, authorized role, module API schema/ADR pin, real test source and framework, target OS/toolchain, seed and expected/actual receipts, evidence artifact, regression classification and review. For comparable replay measure same-target deterministic first; cross-target numeric exactness requires separately proven policy. Never count a docs validator as a gameplay acceptance pass. P00 tests in GitHub Actions cover Source Pack/links, DAG/registry and blocked Zcode selector only.

| ID | Test area | Future expected assertion | Current state |
|---|---|---|---|
## Manifest and schema
| G05-T001 | Manifest and schema | stable template IDs independent of paths | FUTURE / NOT EXECUTED |
| G05-T002 | Manifest and schema | reject unknown required manifest version | FUTURE / NOT EXECUTED |
| G05-T003 | Manifest and schema | preserve unknown optional fields | FUTURE / NOT EXECUTED |
| G05-T004 | Manifest and schema | canonical manifest hash stable | FUTURE / NOT EXECUTED |
| G05-T005 | Manifest and schema | typed field units validated | FUTURE / NOT EXECUTED |
| G05-T006 | Manifest and schema | reject malformed UTF-8 identifiers | FUTURE / NOT EXECUTED |
| G05-T007 | Manifest and schema | reject oversized metadata quota | FUTURE / NOT EXECUTED |
| G05-T008 | Manifest and schema | source manifest round-trip versioned | FUTURE / NOT EXECUTED |
## Dependency resolver
| G05-T009 | Dependency resolver | detect direct dependency cycle | FUTURE / NOT EXECUTED |
| G05-T010 | Dependency resolver | detect transitive dependency cycle | FUTURE / NOT EXECUTED |
| G05-T011 | Dependency resolver | diamond dependency conflict receipt | FUTURE / NOT EXECUTED |
| G05-T012 | Dependency resolver | exact pin resolves unchanged dependency | FUTURE / NOT EXECUTED |
| G05-T013 | Dependency resolver | missing required feature fails closed | FUTURE / NOT EXECUTED |
| G05-T014 | Dependency resolver | optional dependency missing degrades explicitly | FUTURE / NOT EXECUTED |
| G05-T015 | Dependency resolver | untrusted remote URL not fetched | FUTURE / NOT EXECUTED |
| G05-T016 | Dependency resolver | deterministic topological order | FUTURE / NOT EXECUTED |
## Capability targeting
| G05-T017 | Capability targeting | Windows x64 capability report truthful | FUTURE / NOT EXECUTED |
| G05-T018 | Capability targeting | Linux x64 capability report truthful | FUTURE / NOT EXECUTED |
| G05-T019 | Capability targeting | macOS Apple Silicon report truthful | FUTURE / NOT EXECUTED |
| G05-T020 | Capability targeting | Web no-JIT fallback or UNAVAILABLE | FUTURE / NOT EXECUTED |
| G05-T021 | Capability targeting | headless no renderer dependency | FUTURE / NOT EXECUTED |
| G05-T022 | Capability targeting | offline puzzle no NET requirement | FUTURE / NOT EXECUTED |
| G05-T023 | Capability targeting | online shooter rejects absent NET authority | FUTURE / NOT EXECUTED |
| G05-T024 | Capability targeting | unknown hardware profile never becomes PASS | FUTURE / NOT EXECUTED |
## Rights and supply chain
| G05-T025 | Rights and supply chain | reject missing asset rights | FUTURE / NOT EXECUTED |
| G05-T026 | Rights and supply chain | record original authored asset provenance | FUTURE / NOT EXECUTED |
| G05-T027 | Rights and supply chain | CC BY attribution metadata preserved | FUTURE / NOT EXECUTED |
| G05-T028 | Rights and supply chain | CC BY-SA terms flag compatible packaging | FUTURE / NOT EXECUTED |
| G05-T029 | Rights and supply chain | reject NC/ND rights when disallowed | FUTURE / NOT EXECUTED |
| G05-T030 | Rights and supply chain | no copied commercial-game trademarks/assets | FUTURE / NOT EXECUTED |
| G05-T031 | Rights and supply chain | transitive dependency notices retained | FUTURE / NOT EXECUTED |
| G05-T032 | Rights and supply chain | license change requires review receipt | FUTURE / NOT EXECUTED |
## Composition and collisions
| G05-T033 | Composition and collisions | base pack priority typed and stable | FUTURE / NOT EXECUTED |
| G05-T034 | Composition and collisions | independent feature order canonical | FUTURE / NOT EXECUTED |
| G05-T035 | Composition and collisions | collision duplicated action ID rejected | FUTURE / NOT EXECUTED |
| G05-T036 | Composition and collisions | component write-set conflict detected | FUTURE / NOT EXECUTED |
| G05-T037 | Composition and collisions | project override preserves base asset | FUTURE / NOT EXECUTED |
| G05-T038 | Composition and collisions | rebase preserves nonconflicting overrides | FUTURE / NOT EXECUTED |
| G05-T039 | Composition and collisions | deleted base property tombstone handled | FUTURE / NOT EXECUTED |
| G05-T040 | Composition and collisions | same project recipe reproduces hash | FUTURE / NOT EXECUTED |
## Project stage and CAS
| G05-T041 | Project stage and CAS | preview performs zero filesystem writes | FUTURE / NOT EXECUTED |
| G05-T042 | Project stage and CAS | stage requires scoped principal | FUTURE / NOT EXECUTED |
| G05-T043 | Project stage and CAS | stale expected revision rejects | FUTURE / NOT EXECUTED |
| G05-T044 | Project stage and CAS | cross-asset failure yields recovery plan | FUTURE / NOT EXECUTED |
| G05-T045 | Project stage and CAS | cancel stage cleans temporary resources | FUTURE / NOT EXECUTED |
| G05-T046 | Project stage and CAS | commit produces correct DATA-04 receipt | FUTURE / NOT EXECUTED |
| G05-T047 | Project stage and CAS | same idempotency token does not duplicate | FUTURE / NOT EXECUTED |
| G05-T048 | Project stage and CAS | existing project overwrite requires consent | FUTURE / NOT EXECUTED |
## 2D platformer
| G05-T049 | 2D platformer | jump buffer uses CORE-04 ticks | FUTURE / NOT EXECUTED |
| G05-T050 | 2D platformer | coyote-time exact tick boundary | FUTURE / NOT EXECUTED |
| G05-T051 | 2D platformer | one-way platform contact controlled by SIM | FUTURE / NOT EXECUTED |
| G05-T052 | 2D platformer | moving-platform carry no double move | FUTURE / NOT EXECUTED |
| G05-T053 | 2D platformer | scene checkpoint restart state consistent | FUTURE / NOT EXECUTED |
| G05-T054 | 2D platformer | keyboard/gamepad/touch action parity planned | FUTURE / NOT EXECUTED |
| G05-T055 | 2D platformer | 2D pixel/world unit policy consistent | FUTURE / NOT EXECUTED |
| G05-T056 | 2D platformer | replay same seed same target canonical | FUTURE / NOT EXECUTED |
## Shooter
| G05-T057 | Shooter | aim/fire mapped through GAME-01 | FUTURE / NOT EXECUTED |
| G05-T058 | Shooter | ammo cost and cooldown commit together | FUTURE / NOT EXECUTED |
| G05-T059 | Shooter | hitscan validates SIM physics receipt | FUTURE / NOT EXECUTED |
| G05-T060 | Shooter | projectile rules no client self-hit authority | FUTURE / NOT EXECUTED |
| G05-T061 | Shooter | reload cancellation exact FSM | FUTURE / NOT EXECUTED |
| G05-T062 | Shooter | friendly-fire rules source scoped | FUTURE / NOT EXECUTED |
| G05-T063 | Shooter | combat HUD consumes read-only state | FUTURE / NOT EXECUTED |
| G05-T064 | Shooter | shooter sample without Core patch | FUTURE / NOT EXECUTED |
## ARPG
| G05-T065 | ARPG | weighted loot RNG seed and stream stable | FUTURE / NOT EXECUTED |
| G05-T066 | ARPG | loot weight overflow rejected | FUTURE / NOT EXECUTED |
| G05-T067 | ARPG | item reward granted exactly once | FUTURE / NOT EXECUTED |
| G05-T068 | ARPG | skill unlock dependency DAG checked | FUTURE / NOT EXECUTED |
| G05-T069 | ARPG | status proc chain bounded | FUTURE / NOT EXECUTED |
| G05-T070 | ARPG | inventory stack/affix schema compatible | FUTURE / NOT EXECUTED |
| G05-T071 | ARPG | quest progress uses committed event only | FUTURE / NOT EXECUTED |
| G05-T072 | ARPG | ARPG sample uses original names/assets | FUTURE / NOT EXECUTED |
## Vehicle and racing
| G05-T073 | Vehicle and racing | vehicle recipe references SIM-05 controller | FUTURE / NOT EXECUTED |
| G05-T074 | Vehicle and racing | checkpoint order anti-skip validated | FUTURE / NOT EXECUTED |
| G05-T075 | Vehicle and racing | lap count and race phase stable | FUTURE / NOT EXECUTED |
| G05-T076 | Vehicle and racing | reset car respects physics authority | FUTURE / NOT EXECUTED |
| G05-T077 | Vehicle and racing | analog input deadzone mapping honored | FUTURE / NOT EXECUTED |
| G05-T078 | Vehicle and racing | time trial uses CORE-04 ticks | FUTURE / NOT EXECUTED |
| G05-T079 | Vehicle and racing | racing cues AUD-04 cannot affect lap | FUTURE / NOT EXECUTED |
| G05-T080 | Vehicle and racing | vehicle/race sample without Core fork | FUTURE / NOT EXECUTED |
## Strategy
| G05-T081 | Strategy | grid coordinate conversion CORE-05 correct | FUTURE / NOT EXECUTED |
| G05-T082 | Strategy | action point budget cannot underflow | FUTURE / NOT EXECUTED |
| G05-T083 | Strategy | turn order deterministic on same target | FUTURE / NOT EXECUTED |
| G05-T084 | Strategy | fog of war hides secrets per role | FUTURE / NOT EXECUTED |
| G05-T085 | Strategy | path query uses nav owner and quotas | FUTURE / NOT EXECUTED |
| G05-T086 | Strategy | out-of-order stale turn rejected | FUTURE / NOT EXECUTED |
| G05-T087 | Strategy | undo only in authorized local scope | FUTURE / NOT EXECUTED |
| G05-T088 | Strategy | strategy sample adds no second ECS | FUTURE / NOT EXECUTED |
## Puzzle
| G05-T089 | Puzzle | switch graph cycle policy enforced | FUTURE / NOT EXECUTED |
| G05-T090 | Puzzle | door/switch pure state replay exact | FUTURE / NOT EXECUTED |
| G05-T091 | Puzzle | undo excludes irreversible side effects | FUTURE / NOT EXECUTED |
| G05-T092 | Puzzle | unsolvable puzzle fixture detected | FUTURE / NOT EXECUTED |
| G05-T093 | Puzzle | hint does not leak private player data | FUTURE / NOT EXECUTED |
| G05-T094 | Puzzle | puzzle exports with no network | FUTURE / NOT EXECUTED |
| G05-T095 | Puzzle | pause/resume no duplicate input | FUTURE / NOT EXECUTED |
| G05-T096 | Puzzle | puzzle has accessible alternative controls | FUTURE / NOT EXECUTED |
## Animation and audio
| G05-T097 | Animation and audio | SIM-04 root motion remains intent | FUTURE / NOT EXECUTED |
| G05-T098 | Animation and audio | animation event never self-authorizes damage | FUTURE / NOT EXECUTED |
| G05-T099 | Animation and audio | missing clip yields typed fallback | FUTURE / NOT EXECUTED |
| G05-T100 | Animation and audio | retarget binding schema incompatible fails | FUTURE / NOT EXECUTED |
| G05-T101 | Animation and audio | AUD-04 adaptive cue mapping typed | FUTURE / NOT EXECUTED |
| G05-T102 | Animation and audio | missing dialogue locale fallback explicit | FUTURE / NOT EXECUTED |
| G05-T103 | Animation and audio | headless game ignores cosmetic cues safely | FUTURE / NOT EXECUTED |
| G05-T104 | Animation and audio | audio and animation clocks not replaced | FUTURE / NOT EXECUTED |
## Editor CLI MCP parity
| G05-T105 | Editor CLI MCP parity | Editor preview same semantic plan as CLI | FUTURE / NOT EXECUTED |
| G05-T106 | Editor CLI MCP parity | CLI preview same as MCP authorized view | FUTURE / NOT EXECUTED |
| G05-T107 | Editor CLI MCP parity | MCP cannot run untrusted native template code | FUTURE / NOT EXECUTED |
| G05-T108 | Editor CLI MCP parity | no template may execute arbitrary shell | FUTURE / NOT EXECUTED |
| G05-T109 | Editor CLI MCP parity | import returns bounded diagnostics | FUTURE / NOT EXECUTED |
| G05-T110 | Editor CLI MCP parity | undo/redo uses DATA-04 transactions | FUTURE / NOT EXECUTED |
| G05-T111 | Editor CLI MCP parity | permissioned stage rejects wrong project | FUTURE / NOT EXECUTED |
| G05-T112 | Editor CLI MCP parity | missing target capability surfaced not fabricated | FUTURE / NOT EXECUTED |
## Export and migration
| G05-T113 | Export and migration | native Windows export future smoke | FUTURE / NOT EXECUTED |
| G05-T114 | Export and migration | native Linux export future smoke | FUTURE / NOT EXECUTED |
| G05-T115 | Export and migration | native macOS export future smoke | FUTURE / NOT EXECUTED |
| G05-T116 | Export and migration | Web exporter future browser smoke | FUTURE / NOT EXECUTED |
| G05-T117 | Export and migration | headless fixture builds same frozen Core | FUTURE / NOT EXECUTED |
| G05-T118 | Export and migration | old pack schema migration reports diff | FUTURE / NOT EXECUTED |
| G05-T119 | Export and migration | failed migration restores last good | FUTURE / NOT EXECUTED |
| G05-T120 | Export and migration | binary and asset hashes recorded by target | FUTURE / NOT EXECUTED |
## Performance and regression
| G05-T121 | Performance and regression | p50/p95/p99 creation measured future | FUTURE / NOT EXECUTED |
| G05-T122 | Performance and regression | deep package graph resolves bounded future | FUTURE / NOT EXECUTED |
| G05-T123 | Performance and regression | memory/IO quota fixture future | FUTURE / NOT EXECUTED |
| G05-T124 | Performance and regression | malformed pack fuzz future | FUTURE / NOT EXECUTED |
| G05-T125 | Performance and regression | two independent genres no Core diff future | FUTURE / NOT EXECUTED |
| G05-T126 | Performance and regression | all six sample genres reuse API future | FUTURE / NOT EXECUTED |
| G05-T127 | Performance and regression | cold/warm export time on target future | FUTURE / NOT EXECUTED |
| G05-T128 | Performance and regression | docs/ABI/rights regression suite future | FUTURE / NOT EXECUTED |

## Required genre and platform evidence later
Six independently original synthetic genre fixtures and two full demonstrated builds sharing the same frozen Core SHA without Core edits; Windows/Linux/macOS Editor + exports, browser/Web with explicit fallback, headless simulation, distinct role/rights tests, full source provenance and asset notices. Future GAME-04/SIM-04/AUD-04 integrations, migration/recovery, network authorization and AI CLI/MCP parity must be tested on actual implementation. Performance/compatibility thresholds remain UNDECIDED until measured baselines. **Nothing in this matrix authorizes implementation**.
