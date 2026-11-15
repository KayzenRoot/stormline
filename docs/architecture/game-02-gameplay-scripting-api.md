# GAME-02 — Gameplay Scripting & API Architecture v0.1

**Research WO:** NLE-P00-WO-002-GAME-02 | **Research issue:** #212 | **Future code:** #58 OPEN/BLOCKED  
**BASE main:** `8b12b71f090974e7c909265cb249f3fec297c89e` | **P00 RESEARCH ONLY / ADR-0043 PROPOSED.** No scripting runtime, compiled script, sandbox, visual editor, native binding, Web/WASM engine, hot reload, debugger, shipped asset or performance evidence exists. Docs LOW risk; future runtime ELEVATED, and arbitrary third-party privileged code or secure multi-tenant script execution requires HIGH_ASSURANCE proof and separate approval.

## 1. Mission, guarantees and scope
Catalog scope: **"Scripting visual/textual a decidir, bindings, sandbox, hot reload e APIs estáveis."** Catalog acceptance: **"Modificar regras sem recompilar Core e com limites de segurança."** Provide a Stormline-owned, stable game-script authoring and execution contract that lets game designers modify entity behavior, event reactions, actions and approved game rules without recompiling platform/Core, while retaining a hard separation between guest code and game/OS authority.

Two authoring surfaces, one execution authority:
- **Textual scripting:** proposed **Luau** embedded in a purpose-built `ScriptHostV1` restricted VM, typechecked, source-revisioned and compiled off-tick. This is a *leading candidate*, not an adopted runtime. Lua 5.4 is the baseline compatibility and control comparator.
- **Visual scripting:** a directed, typed `VisualGraphV1` of domain-specific nodes with pin types, data/control/event edges, declared capabilities and explicit loops; convert to a validated `GameplayProgramIRV1` or generated source using the same `ScriptApiSchemaV1` and command semantics. Do not build a second privileged interpreter, and do not assume that a generic node canvas library supplies graph execution/security.
- **Optional WebAssembly:** independent evaluation lane for cross-language mod/plugin sandboxing (Wasmtime/WAMR/Wasm3) under the identical host ABI/capabilities. A general WASM VM is not automatically necessary for the first scripting feature and may add compile footprint, AOT/JIT/Web constraints and hard-to-audit WASI imports.

The **minimum future gameplay proof** is one original deterministic script reading a safe `EntitySnapshot` and `InputActionFrame`, yielding a bounded `ScriptCommandBuffer` to WORLD-01/GAME authorization, then editing the script and activating a staged revision without recompiling CORE. This proof is NOT performed in P00.

## 2. Explicit ownership matrix
| Owner | Source of truth GAME-02 consumes / outputs | Forbidden duplication |
|---|---|---|
| **WORLD-01 (catalog dependency)** | `WorldIdentityV1`, `EntityGuidV1`, ephemeral generational `EntityHandleV1`, `ComponentSchemaV1`, `EntityQuerySnapshotV1`, `EntityCommandBufferV1`, `EntityCommitReceiptV1`, lifecycle and stale/reflection rules | another ECS, unversioned raw component pointers, direct writes to archetype pages, entity generation reuse or unauthorized create/destroy |
| **CORE-03 (catalog dependency)** | job scheduler/affinity, bounded work and cancellation, declared read/write access sets, dependency graph, deterministic logical commit fence | VM-owned worker pool, own barrier, running guest on arbitrary worker or blocking an OS/audio callback |
| **CORE-04** | simulation timeline `TickId`, rational fixed-step, pause/replay/rollback fence | script-owned clock or using render delta/wall time to mutate authoritative gameplay |
| **GAME-01** | immutable `InputActionFrameV1` and PlayerSeat, action IDs, source provenance and focus semantics | direct SDL key polling, global keyboard/IME access, synthetic live key injection or input device ownership |
| **GAME-04 / NET (future)** | authoritative gameplay state, event bus, events/abilities/quest transitions, server/client roles, rollback and replication policy | script self-authorizing network/gameplay actions, arbitrary RPC, direct network socket or anti-cheat assumption |
| **DATA-02 / DATA-03 / DATA-04 / DATA-05** | stable `AssetId`, content provenance, script source/bundle validation, versioned authored schema/CAS/semantic diff/migration, cooked bytecode+content hash | host filesystem, independent parser/importer/asset DB or mutable code loaded from arbitrary URL/path |
| **CORE-02 / CORE-05 / CORE-06** | allocator/memory budgets and types/units, deterministic numeric conventions, trace/log/benchmark counters with privacy | custom allocator, unsynchronized global mutable caches, unbounded script print/trace |
| **AI-01/04/06 and EDIT/UI** | authorized public semantic author/preview/validate/debug/commit commands, role-scoped inspection, UI code/graph views | anonymous MCP `eval`, arbitrary shell/file/network access, direct privileged engine memory, separate no-validation edit path |
| **PLAT / native+Web** | platform availability, target runtime policy, dynamic code restrictions, Web JS/WASM permission constraints | relying on native JIT, direct OS APIs or WASI host imports on Web without capability proof |

**Critical dependency state:** WORLD-01 and CORE-03 are DOCUMENTED/PROPOSED but not engine code. Their contracts need implementation and approval before any GAME-02 coding is legal. This planning milestone doesn't change their status.

## 3. Script host architecture: one shared command boundary
```text
Authored Luau source      VisualGraph source (typed nodes)    [FUTURE] WASM component
  -> DATA-03 secure import and DATA-02 AssetId/revision
  -> GAME-02 parser/typecheck/Graph validator + shared ScriptApiSchemaV1
  -> GameplayProgramIRV1 + diagnostics + source map + capability manifest
  -> DATA-05 cooked signed/provenance-bound program (compiler/runtime fingerprint)
  -> GAME-02 ScriptHostV1 isolated guest instance (world/seat/role/revision)
        read-only WORLD-01 EntitySnapshot / GAME-01 ActionFrame / TickId / seeded random
        capability-checked host function bridge (no direct C++ pointer)
        bounded ScriptCommandBufferV1 (mutations as intents)
  -> CORE-03 deterministic commit barrier
  -> GAME/NET authority and WORLD-01 commit + receipt
  -> GAME-02 ScriptFault/trace/telemetry, no authority bypass
```

A script's success means **program executed and intent was submitted**, not that the world mutation was accepted. The authoritative commit can reject/partially apply only as explicitly specified by WORLD-01 transaction granularity and GAME/NET role; every outcome is a typed receipt, never silently successful.

### 3.1 Module, instance and lifecycle
- `ScriptModuleV1` identifies stable `AssetId`, ScriptModuleId/revision, source hash, language/dialect, typecheck config, API schema and compiler/runtime fingerprint, capability manifest, target platform, content provenance and import trust tier. Module references never accept arbitrary host file paths.
- `ScriptInstanceV1` has scoped ProjectId/WorldInstanceEpoch/EntityHandle generation/ScriptInstanceId/generation, principal, role, state-schema revision, enabled/pending/failed state and budget. World unload/rollback/entity destroy invalidates stale instances.
- Lifecycle PROPOSED: `IMPORTED → VALIDATED → COMPILED → STAGED → ACTIVE → SUSPENDING → DRAINING → RETIRED`, typed `REJECTED` and `FAULTED` with safe-disable/fallback. No loaded code may re-enter deallocated world objects.
- A per-instance or per-trust-domain VM minimizes shared globals; any shared VM threads require enforceable global isolation and vulnerability tests. Grouping trusted authored scripts for performance is a separately benchmarked tier; untrusted/community mods require stronger isolated execution (prefer separate process and/or independently verified WASM capabilities), not only a language flag.

### 3.2 API schemas, binding and ownership
- Stormline-owned `ScriptApiSchemaV1` declares stable function ID/namespace, argument/result types, units, mutability, authority/capability, thread/tick phase, side effect, allocation budget, error/denial semantics and deprecation schedule.
- Lua/Luau C API or sol2/LuaBridge3 are *internal adapter candidates only*. No plugin receives raw `lua_State*`, `World*`, `Component*`, native pointer, worker handle, TLS credential or C++ exception. Validate all host arguments before native reads/writes and return `ScriptApiResultV1`.
- Safe sample functions: `world.read_component(entity_guid, type_id)` via immutable snapshot, `input.action_state(action_id)`, `commands.set_component(entity_guid, typed_patch)`, `math.seeded_random(stream_id)`, `events.emit_authorized(event_id, payload)`. Actual names are conceptual, and GAME/WORLD owners validate at commit.
- No direct `execute`, `loadfile`, `dofile`, `package.loadlib`, native FFI, reflection into arbitrary C++ objects, environment variables, OS clock, raw sockets, DNS, host process or unrestricted file write. Even `print` is rate-limited and redacted by CORE-06.
- Stable entity GUID is persistent source identity, runtime EntityHandle is ephemeral; host bridge resolves each access against world instance/epoch and declared `ComponentSchemaV1`. A script cannot retain a valid raw pointer across structural ECS commit.

## 4. Trust tiers, sandbox and explicit capabilities
`ScriptTrustTierV1`: `ENGINE_TRUSTED_INTERNAL`, `PROJECT_AUTHORED`, `UNTRUSTED_EXTERNAL`. Trusted engine internals never automatically inherit host OS privileges in the user-facing VM. Trust levels are labels *not* permissions: grants are per ProjectId/WorldId/ScriptModuleId+revision/Principal/Role/CapabilityId, expiry and explicit audit.
- **Default deny** for all mutating host calls and all host ambient APIs. Read-only `EntitySnapshot` is filtered by world/role/component sensitivity and query cardinality.
- **Capabilities** include scoped `WORLD_READ_COMPONENT`, `WORLD_STAGE_MUTATION`, `GAME_EMIT_EVENT`, `INPUT_READ_ACTION`, `DEBUG_INSPECT_OWN_INSTANCE`, `EDITOR_STAGE_SCRIPT` and `SCRIPT_READ_ALLOWED_ASSET`; privileged stage/debug permissions do not grant execution authority.
- Grant `ScriptCapabilityGrantV1` includes authenticated user/service principal, world/project, module revision, permitted capability, entity/component/event scope, context, lease/epoch, rate limits and policy revision. Revocation takes effect at the next safe host-call or tick barrier; stale leases cannot be replayed.
- **Host API is the main escape boundary.** Luau's VM sandbox removes unsafe standard APIs but native host callbacks can reintroduce OS access or UAF. Apply an allowlisted manifest, handwritten or reviewed bindings, no arbitrary function registration and fuzz adversarial serialized values.
- **Resource quotas:** source/decode size; compiler time/memory; bytecode size; VM heap/stack; coroutine count; host calls/tick; action/event count; entity queries; read snapshot bytes; command-buffer bytes; debug/log volume. Enforce allocator quotas and watchdog/interrupt safepoints. For Luau verify `luaL_sandbox`, `luaL_sandboxthread`, `lua_Callbacks.interrupt` and allocator/memcat. Native host calls that block or loop can defeat guest interrupts: no unchecked callbacks on tick path.
- **Untrusted bytecode:** Luau's own security docs assume bytecode produced by trusted compiler; never execute imported unvalidated bytecode. DATA-03 compiles original source using pinned vetted toolchain, then DATA-05 cooks verified signed/content-addressed artifacts. Signature/integrity authenticity policy has approved keys/revocation separately; a hash alone isn't an authorization grant.
- **WASM optional isolation lane:** Wasmtime fuel/epoch and Store resource limits; WAMR/Wasm3 comparators; deny WASI filesystem/network/time/random by default and explicitly select import table. An isolated linear memory doesn't prevent malicious host imports, unbounded compiler/host memory or all side channels. Browser JIT/AOT policies, C++ native embedding footprint and platform legal terms must be proven.
- **High assurance** separate scope if unknown third-party scripts can initiate irreversible actions, privileged authorization, money/Web3/signed transactions or OS execution. Those are not part of GAME-02 baseline.

## 5. Timing, determinism and concurrency
- CORE-04 `TickId` sets logical script phase; GAME-01 supplies action frames. Only deterministic capabilities may run on an authoritative or replayable simulation path.
- Proposed phases `PRE_READ_SNAPSHOT → SCRIPT_READ_AND_STAGE → VALIDATE_INTENTS → CORE03_WORLD01_COMMIT_FENCE → PUBLISH_RECEIPTS`. Task graph and worker lifetime are CORE-03-owned; WORLD-01 publishes entity structural changes at own validated barrier. GAME-02 cannot mutate live ECS from worker.
- Script scheduling order uses world/instance epoch, tick, script-module priority, entity stable ID, script instance ID and sequence number; declare deterministic compare keys. Parallel read-only guest execution permitted only when captured snapshots and host call ordering are stable; do not promise identical native/ARM/Web floating-point, GC, JIT or nondeterministic resource execution.
- **Inputs:** `ScriptTickContextV1` has TickId, rational fixed delta, role, controlled seeded random stream, immutable input action frame digest, world revision and approved capabilities. No UTC time, wall clock, network fetch, external entropy or true non-deterministic timers on replicated authoritative script path.
- **Commands:** typed `ScriptCommandBufferV1` has per-origin quota, entity handle/expected generation, component expected schema/revision and game authority role. Validate and order before WORLD-01 commit; no partial unsafe write. Conflicts are resolved by a separately approved deterministic policy or reject; script runtime isn't authority.
- Event bus belongs GAME-04/NET; callbacks receive bounded immutable typed events, can stage follow-up intents for next allowed phase but never call into guest recursively from partially committed structural mutations. Causal cycles/duplicate replay need event IDs/tick/source sequence and backlog cap.

## 6. Visual scripting without a second game engine
- Graph authoring **IMPORTANT for full scope**, but NECESSARY proof first is a tiny graph path sharing the same `ScriptApiSchemaV1` functions and `GameplayProgramIRV1` with textual scripting. Node editor UI belongs EDIT, not GAME-02.
- `VisualGraphV1`: GraphId/AssetId, schema/compile rev, typed NodeId, PinId with value/flow/event types, edges, graph entry points, constants, subgraph imports, declarative ability scopes and source-map positions. No arbitrary native call node or reflection magic.
- Validation: no missing required pins, type/units mismatch, invalid conversion, data-only algebraic cycles unless explicitly legal delay/state operator; control-flow loops require static bound/host instruction budget; no overlarge fanout, recursive graph/subgraph cycles or import of unknown required node kind.
- Compile graph to a deterministic intermediate `GameplayProgramIRV1` with stable action/function IDs, typed dataflow and source maps, then a backend for Luau source/bytecode *only if transpilation semantics and debugging source maps are proved*. Alternative is a bounded Graph-IR interpreter adapter using same capability host calls, NOT a separate ECS/permissions path. Do not promise equivalent precision/GC/order across these backends before equivalence tests.
- Graph debuggability: node pin/edge execution trace and breakpoint mapped to script source span; stepping only at safe execution/yield boundaries and permissions. ImGui node-editor (MIT) is an optional UI comparator that **does not** implement visual scripting compilation.

## 7. Hot reload, saved state, migrations and rollback
- Stage new source/graph as DATA-04 immutable revision with expected CAS. DATA-03 parses, typechecks, compiles in CORE-03 non-RT job under quotas; resolve exact API capability diff, imports, source hash and target ABI. Never run untrusted compiler output directly during compilation or inside editor main/render/audio callback.
- `ScriptHotReloadPlanV1`: old/new module/bytecode hash, API schema revision, `ScriptStateSchemaV1`, migration plan, affected entity/instance set, capabilities, drain barrier, rollback option and side-effect replay policy. On safe tick fence, quiesce old instances, snapshot **only declared script-owned serializable state**; ECS/source-of-truth game state remains WORLD-01/GAME and cannot be overwritten by reload.
- Apply migrations through DATA-04 semantic validation and allowlisted pure functions; no execute-arbitrary-scripts during import and no unsafe pointer/function closure serialization. New module initializes into staging VM; preflight canaries deterministic scripted events/commands; commit both program revision and state swap atomically at defined world scope.
- On compile/type/schema/authority/capability/timeout failure: old revision remains active if safe; otherwise disable instance and emit typed receipt, not partial swap. Postcommit faults are not automatically reversible after external side effects: rollback/roll-forward must define what effects can be reverted, and multiplayer NET authority dictates coordinated activation/tick.
- Reference stability: persisted `EntityGuid` + component schema version validated to runtime EntityHandle per world epoch. Unloaded/destroyed entities return MISSING/STALE/UNLOADED, never resurrect a stale pointer.

## 8. Debugging and observability
- Source diagnostics: parse/type errors, lints, capability violations, source map, `ScriptFaultReceiptV1` with module rev, entity scope, TickId, bounded stack/span and redacted error. Include host callback errors and failures from WORLD-01 commit receipt.
- Debug protocol: attach only to authorized local Editor/headless test instance, no arbitrary remote attach by default. Breakpoints/step/stack/variable watch use read-only bounded paginated snapshots, no hidden world data or arbitrary `eval` in untrusted/debugger sessions. Multi-client session/lease and disconnect resume policy prevent permanent frozen worlds.
- CORE-06 telemetry: compile time, warmup, VM heap/GC, per-tick runtime p50/p95/p99, host-call count, traps/timeouts, command errors, reload success/rollback, queue depth. Privacy: no full script source or player/personal state logged by default.
- Debug pause vs sim pause uses CORE-04 authorization; no unexpected deadlock with CORE-03 jobs, no interrupting critical audio callback.

## 9. Portability, licensing and verification
- Required editor/client/headless native Windows/Linux/macOS; optional PLAT-03 Web. Luau MIT leading candidate, Lua 5.4 MIT comparator. No assertion of full Lua 5.4 source compatibility with Luau (mainly Lua 5.1 heritage).
- sol2 MIT, LuaBridge3 MIT binding adapters only if they can uphold strict type/ownership checks and protect host boundary; no code adoption.
- Wasmtime Apache-2.0 (official source), WAMR Apache-2.0 with LLVM exception, Wasm3 MIT, interpreter/no-JIT variants require cross-target verification and capability quotas. No engine license decision: NLE-D009 OPEN.
- Visual editors are authoring surfaces not security boundaries. Godot's VisualScript removal from version 4 is a *product caution*, not a technical reason to reject all visual scripting; original typed graph must prove user value vs maintenance/semantic drift.
- 128 FUTURE acceptance scenarios and benchmark protocol are documented, **NOT EXECUTED**. No VM host sandbox proof, compiler source, code generated/installed, Web/WASM/native ABI, hard limits, debugger, hot reload, unit/fuzz/ASan/TSan, p95/p99 performance or license adoption evidence.
- **Future NECESSARY slice:** original single entity Luau script with read-only snapshot + action frame, capability check and typed command commit; deterministic headless replay and one safe staging/reload with rollback. Add one tiny typed graph compiled to same semantic command path for parity acceptance. **IMPORTANT:** advanced debugger/profiler, multi-module packages and visual editor polish. **FUTURE:** arbitrary mod marketplace, user-uploaded native plugins, multi-language scripting simultaneously, JIT in all targets, remote code execution, package registry/network modules, live collaborative patching and AI generated code execution.
