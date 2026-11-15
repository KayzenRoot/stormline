# GAME-04 — Gameplay Systems, Event Bus, Serialization and Benchmark Technology Matrix

**2026-11-15 | RESEARCH ONLY | ALL CANDIDATES NOT ADOPTED.** URLs link upstream product and exact license references inspected at research time; latest tag, transitive notices, SPDX, binary redistribution and supply-chain verification must be pinned again at future implementation. Stormline's **engine license remains OPEN (NLE-D009)**.

## A. Library and design evaluation
| Candidate | Evidence / official upstream | License / obligations | Role and evaluation | Gate |
|---|---|---|---|---|
| Stormline owned typed event envelope + bounded queue | [C++20 reference](https://en.cppreference.com/w/cpp/20) | original engine code license **OPEN** | leading semantic API, not a preselected implementation | stable order, schema, overflow, generation tokens, fuzz, benchmarks |
| [EnTT](https://github.com/skypjack/entt) + [signal/dispatcher docs](https://skypjack.github.io/entt/md_docs_2md_2signal.html) | MIT [LICENSE](https://github.com/skypjack/entt/blob/main/LICENSE) | retain copyright/license with redistributed code | internal dispatcher comparator, supports `trigger/enqueue/update`, has unordered listener execution caveat | do not let library decide deterministic world-commit order |
| [Flecs](https://www.flecs.dev/flecs/ObserversManual.html) | MIT [official API](https://www.flecs.dev/flecs/group__cpp__observers.html) | retain MIT notices | ECS observers/deferred queue comparator | WORLD-01 owns ECS; prevent duplicate registry / stage semantics drift |
| [Unreal Gameplay Ability System](https://dev.epicgames.com/documentation/unreal-engine/using-gameplay-abilities-in-unreal-engine) | Unreal Engine EULA / proprietary framework | reference documentation ONLY; **not a redistributable Stormline library** | ability lifecycle, costs/cooldowns/tags/effects, local prediction and replication comparison | no GAS source/assets/Blueprints copied |
| [Unity Netcode for Entities](https://docs.unity.cn/Packages/com.unity.netcode%401.6/manual/creating-multiplayer-gameplay.html) | Unity package/platform terms; verify before reuse | reference only | fixed-tick server-authoritative/prediction comparator | not evidence Stormline interoperates with Unity |
| [Godot stable docs](https://docs.godotengine.org/en/stable/tutorials/scripting/scene_tree.html) | Godot engine MIT [license](https://github.com/godotengine/godot/blob/master/LICENSE.txt) | retain notices if code used; docs/content have own terms | scene tree/signals/save pattern conceptual comparator | no second scene hierarchy or code copying |
| [FlatBuffers](https://github.com/google/flatbuffers) | Apache-2.0 [LICENSE](https://github.com/google/flatbuffers/blob/master/LICENSE) | preserve copyright/license/NOTICE and changes, patent conditions | optional compact event/save/wire schema candidate | schema evolution, CPU/size, wasm and validation; NET/DATA owners |
| [Protocol Buffers](https://github.com/protocolbuffers/protobuf) | BSD-3-Clause [LICENSE](https://github.com/protocolbuffers/protobuf/blob/main/LICENSE) | redistribution notices/no endorsement | optional authoring/net schema comparator | deterministic serialization is not default all-language hash equivalence |
| C++20 `std::variant`, `std::span`, `std::pmr` | standard library / selected toolchain terms | platform runtime/toolchain licensing varies | typed local payload, allocator/buffer baseline | compile ABI/schema, avoid typeid/RTTI as persistent schema key |
| [Google Benchmark](https://github.com/google/benchmark) | Apache-2.0 [LICENSE](https://github.com/google/benchmark/blob/main/LICENSE) | license/NOTICE check | future microbenchmark harness only | baseline pinned and real hardware required |
| [OpenTelemetry C++](https://github.com/open-telemetry/opentelemetry-cpp) | Apache-2.0 upstream license, verify release artifact | notices / dependency audit | optional CORE-06 trace adapter | no export of secrets or automatic remote telemetry |
| [SDL3](https://github.com/libsdl-org/SDL) | zlib [LICENSE](https://github.com/libsdl-org/SDL/blob/main/LICENSE.txt) | preserve source notice, mark modified versions | CORE-01 platform only, not gameplay events | no second poll loop |
| [Luau](https://github.com/luau-lang/luau) | MIT project files, inspect pin | preserve license; sandbox is host-dependent | GAME-02 only, emits typed intents | untrusted bytecode/host function allowlist |

## B. Architecture choices under comparison
- **Event delivery:** immediate publish/subscribe vs phase-scoped deferred ordered queue; prefer deferred for authoritative path, cosmetic signals may remain immediate in presentation domain only. Upstream EnTT notes listener order is not guaranteed; explicitly sort before authoritative commit.
- **Game state:** statechart/hierarchical state machine with transition guard and revisions vs ad hoc booleans; prefer scoped deterministic FSM for minimal core; hierarchical/orthogonal regions require future DAG/cycle/fanout proof.
- **Rule composition:** C++ data-driven ability/effect defs with GAME-02 capability hooks vs hardcoded gameplay hierarchy; prefer typed data + verified script hooks.
- **Storage:** DATA-04 canonical source CAS/journal and separated runtime snapshot vs direct JSON save and unbounded event sourcing. Do not claim cross-system ACID.
- **Networking:** authoritative input-command replication vs client event replication; restrict clients to validated commands and NET interest scopes. Replay lockstep only with measured deterministic numeric environment; otherwise authoritative server + prediction/reconciliation.
- **Serialization:** handwritten canonical schema/typed source vs FlatBuffers/Protobuf; ownership must remain DATA-04/NET; no library choice without bytewise migration and corrupted payload tests.
- **Safety:** per-world bounded queue, per-principal intent quotas, dynamic subscription token generations, recursion caps, redacted diagnostics and idempotent reward ledger. Script/JSON/network are untrusted.

## C. License, provenance and release checklist
1. Pin exact upstream release/commit, platform-specific distribution build, SPDX and license file hash; review all transitive headers/assets/generated schema tools and compiler runtime.
2. Retain attribution/NOTICE where required; verify Apache patent/NOTICE; keep engine code license choice OPEN until NLE-D009 approved.
3. Reject proprietary engine SDK import absent separate approval; documentation is for design comparison, no copied source or non-licensed gameplay assets.
4. Run SBOM/dependency vulnerability scan and sign-off at later code WO, including binary shader/assets/target packaging as relevant.
5. No benchmark or library has been executed, installed or linked by this research. No technical candidate is APPROVED.

## D. Reference research conclusions
[EnTT official dispatcher docs](https://skypjack.github.io/entt/md_docs_2md_2signal.html) explicitly separate immediate `trigger` from `enqueue/update` and do **not** guarantee listener order. [Flecs observers](https://www.flecs.dev/flecs/ObserversManual.html) distinguish observer reaction from system periodic execution and document staging enqueue behavior. [Unreal GAS docs](https://dev.epicgames.com/documentation/unreal-engine/using-gameplay-abilities-in-unreal-engine) demonstrate cost/cooldown/tags and client/server replication design patterns, but cannot supply Stormline's implementation. [Unity netcode docs](https://docs.unity.cn/Packages/com.unity.netcode%401.6/manual/creating-multiplayer-gameplay.html) describe server-fixed-step with interpolation and prediction, not generic cross-target bitwise determinism. Licenses above must be rechecked on exact future pins.

See [architecture](../architecture/game-04-gameplay-systems-event-bus.md), [ADR](../adr/0045-game-04-typed-deterministic-gameplay-event-bus.md) and [benchmark protocol](game-04-gameplay-benchmark-protocol.md).
