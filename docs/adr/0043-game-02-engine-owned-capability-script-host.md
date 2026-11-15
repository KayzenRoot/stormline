# ADR-0043 — Engine-Owned Capability-Scoped Script Host and Shared Gameplay API

**STATUS: PROPOSED / NOT APPROVED FOR CODE** | Date: 2026-11-15  
**WO NLE-P00-WO-002-GAME-02 | Research issue #212 | Future coding issue #58 OPEN/BLOCKED**

## Context
GAME-02 requires scripting textual/visual, stable C++ gameplay APIs, safe sandbox and hot reload without recompiling CORE. WORLD-01 is sole entity/component owner; CORE-03 solely owns scheduler/deterministic commit barriers; GAME-01 produces semantic action frames. All these subsystems remain nonimplemented research proposals. Embedding Lua/Luau/WASM alone does not establish host API safety, determinism, performance or code/asset rights.

## Proposed decision (11 clauses)
1. **Stormline owns the semantic scripting boundary**. Publish versioned `ScriptApiSchemaV1`, `ScriptModuleV1`, `ScriptInstanceV1`, `ScriptCapabilityGrantV1`, `GameplayProgramIRV1`, `ScriptCommandBufferV1`, `ScriptFaultReceiptV1` and hot reload contracts independent of the VM implementation. No vendor-native C++ or scripting runtime types in public game API.
2. **Luau (MIT) is the leading first textual VM candidate**, evaluated against PUC-Lua 5.4 (MIT) under the same host interface, not adopted. Luau gradual typing, linter/typechecker and explicit sandbox hooks are useful. Luau is not transparently Lua 5.4-compatible; use a declared dialect and treat bytecode as compiler-specific trusted artifacts. No raw bytecode from untrusted uploads.
3. **Host API is deny-by-default and capability-scoped** to project/world/module revision/principal/role/entity/component/event/tick. No implicit file/network/process/os clock/native library/FFI/debug eval, hidden game state or arbitrary host function. Even trusted engine-authored scripts get only declared capabilities; GAME/NET alone authorizes actual gameplay effects.
4. **VM budgets are hard gates**, not best-effort monitoring: compile CPU/memory, source/bytecode size, execution instructions/time, memory/stack/coroutine, query cardinality, command count, host-call count, event queue and telemetry. For Luau evaluate allocator+memcat and interrupt callbacks. Callbacks inside native/C++ code must be bounded; VM interrupt isn't a defense against blocking hostile native host code.
5. **WORLD-01 ECS access is via scoped immutable snapshot and typed command buffer**, never raw pointer/direct mutable component reference. Resolve durable EntityGuid to validated world-specific generational EntityHandle, follow read/write schemas and owner authority; WORLD-01/CORE-03 commit at explicit fence and return receipt. Scripts don't set scene/server state directly.
6. **CORE-04 TickId and GAME-01 InputActionFrame are input to gameplay**. No wall-clock/OS entropy/renderer FPS or uncontrolled parallel mutable execution in authoritative scripts. Deterministic run must record version, seeded RNG, ordered inputs, schema and command receipts; bitwise float/GPU/native-vs-Web reproducibility isn't presumed.
7. **Graph and text share the same capability API and semantic intermediate representation**. Visual graph nodes must be typed, versioned, budgeted and source-mapped; graph is compiled/validated rather than arbitrary UI-executed C++ function calls. The Editor owns node canvas; GAME-02 owns graph schema/validation/execution semantics. Typed graph codegen vs Graph-IR interpreter needs equivalence proof, not a second unreviewed engine.
8. **Hot reload is staged and atomic at authorized safe barrier**. DATA-04 owns source revision/CAS and schema migration; CORE-03 does off-tick compilation, WORLD-01 validates referenced handles; drain old tasks, snapshot only script-owned safe state, migrate and swap by versioned plan. Failure keeps old known-good or safe-disabled; irreversible effects cannot be undone by pretending source rollback is a full world rollback.
9. **WebAssembly is a separate optional proof lane, not an automatic second baseline VM**. Wasmtime (Apache-2.0), WAMR (Apache-2.0 LLVM exception), Wasm3 (MIT) test fuel/epoch/instruction quotas, no default WASI imports, memory/instance limits, native+Web/headless cost and AOT/JIT portability. Do not assume WASM linear-memory isolation also isolates dangerous host imports. For hostile/community mods require separate process/stronger independently proven sandbox or BLOCKED.
10. **Debugging is permissioned and nonexecuting by default**: break/step and read-only paginated variables with explicit role and redact; no untrusted REPL/eval/shell, remote attach or reading private secrets. CORE-06 owns metrics, CORE-04 sim pause, CORE-03 scheduling.
11. **No tech adoption or release proof**: SDL/World/Core documents are proposed, not code. Luau, Lua, sol2/LuaBridge, Wasmtime, WAMR, Wasm3, ImGui node editor have independent licenses/notice/transitive checks. The engine license decision NLE-D009 remains OPEN. 128 prospective tests and performance/compatibility/security proof obligations must run before code readiness or marketing claims.

## Alternatives considered
- Expose raw EnTT/archetype/native C++ pointers or `lua_State*` as gameplay API.
- Trust Lua/Luau default libraries or WASM sandbox without validating host callbacks/quotas/rights.
- Allow arbitrary unsigned/untrusted bytecode, `eval`, native modules or network imports from project assets.
- Execute scripts directly on CORE-03 arbitrary workers against live mutable ECS with no deterministic commit.
- Implement visual graphs as a second privileged runtime with separate bindings and authorization.
- Pause simulation/reload mid-tick and partially swap script revisions.
- Treat JIT/floating-point/GC/OS timing as deterministic across native/Web without proofs.
- Automatically implement Luau + Lua 5.4 + Wasmtime concurrently before a single minimal vertical slice is proved.

## Consequences / decisions still open
Pros: modular scripting without Core rebuild, authoring parity, least privilege and owned public API. Costs: compiler/runtime adapter testing, sandbox/host callback hardening, deterministic scheduling, state-migration complexity, visual graph documentation/debuggability and cross-platform proof. Default first small slice: one signed/validated original source, read snapshot, bounded command intent, tick receipt, safe reload rollback, tiny graph parity. RUNTIME budget thresholds, API schema, software licenses, target compatibility, VM adoption and authority policy remain **UNDECIDED**.
**ADR PROPOSED; no code, runtime, compiled script, security proof, benchmark, deployment, licensing adoption or authorization for #58. All 80 code packets stay BLOCKED.**
