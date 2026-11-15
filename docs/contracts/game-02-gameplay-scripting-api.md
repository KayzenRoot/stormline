# GAME-02 — Gameplay Scripting, Capabilities, Visual Graph and Reload Semantic Contracts v0.1

**Issue #212 | WO NLE-P00-WO-002-GAME-02 | Future code #58 OPEN/BLOCKED.** Conceptual, versioned **semantic contracts only**: not C++ headers/ABI, Luau bytecode, WIT interface, real binding, compiled graph, serializer or executable API.

## 1. Versioned contract inventory
| Proposed contract | Key fields and responsibilities | Owner / invariants |
|---|---|---|
| `ScriptLanguageV1` | LUAU / LUA54_COMPARATOR / WASM_OPTIONAL / GRAPH_IR, declared dialect, source encoding, compiler and runtime fingerprint | module validation, no implied cross-language binary compatibility |
| `ScriptModuleV1` | ProjectId, ScriptModuleId, AssetId/revision/source hash, language, API schema version/hash, compiler flags, content origin/trust tier, target platforms, capability manifest | GAME-02 semantic identity, DATA-02 provenance, DATA-03 secure import, DATA-04 CAS/cook DATA-05 |
| `ScriptModuleImportReceiptV1` | importer version, text/source size, UTF-8 validation, dependency resolution, declared imports, diagnostics and rights status | DATA-03 import/scan, typed error and quotas |
| `ScriptDependencyManifestV1` | ModuleId + exact revision/hash for allowed imports, resolution order, cycle budget, source owner and capability transitivity | no host filesystem/remote fetch, reproducible DAG and deny dynamic arbitrary native require |
| `ScriptApiSchemaV1` | stable API UUID/name, numeric schema revision, typed signature, units, side-effect kind, phase/thread/authority, required capability, deprecation and error codes | Stormline-owned public API; no raw VM/C++ vendor type |
| `ScriptApiFunctionV1` | namespace + stable function ID, scalar/struct/handle types, input/output bounds, read/write component sets, max cost, permitted reentry/async | host adapter maps native code only to reviewed limited entry points |
| `ScriptCapabilityGrantV1` | GrantId, issuer/principal/role, ProjectId, WorldInstanceEpoch, ModuleId/revision, function/capability/target/EntityGuid/ComponentTypeId scope, expiry/lease, rate quota, revocation version | fail-closed even on trusted script; zero ambient OS or gameplay authority |
| `ScriptTrustTierV1` | ENGINE_TRUSTED_INTERNAL / PROJECT_AUTHORED / UNTRUSTED_EXTERNAL; isolation/approval policy and feature cap | trust tier never substitutes for actual capability authorization |
| `ScriptInstanceHandleV1` | ScriptInstanceId+generation, ModuleId/revision, WorldInstanceEpoch, EntityGuid+temporary EntityHandle generation, role, lease, lifecycle | stale/ABA/cross-world rejected; no pointer retention |
| `ScriptInstanceStateV1` | CREATED/STAGED/ACTIVE/PAUSED/DRAINING/FAULTED/DISABLED/RETIRED, tick, fault budget, state schema and activation generation | controlled state machine, no half-active hot reload |
| `ScriptStateSchemaV1` | fields/types/units/defaults/version, ScriptOwned flag, serialization constraints, migration hash, opaque state limits | DATA-04 owns persisted schema and staged migration; no native closure/pointer serialization |
| `ScriptTickContextV1` | TickId, rational dt, SimulationEpoch, WorldSnapshotRef+revision, PlayerSeat action frame digest, deterministic seed stream, authorized role and grants | CORE-04 clock, GAME-01 input; no wall time/network/OS entropy on deterministic path |
| `ScriptReadSnapshotV1` | Project/World/Epoch, immutable queried EntityGuid + validated runtime generation, typed ComponentSchemaId/version and bounded fields | WORLD-01 authority, read scope/visibility; view expires at barrier |
| `ScriptHostCallV1` | ApiFunctionId, typed args/lengths, originating InstanceId/generation, tick/phase, grant token ID, expected world/schema/role, call ID | check quota, ABI, source, bounds, role, no native pointers or generic eval |
| `ScriptApiResultV1` | call ID, ACCEPTED/DENIED/STALE/FAILED, sanitized return values, actual cost, mapped typed fault and retry semantics | no implicit completed world mutation |
| `ScriptCommandBufferV1` | WorldInstanceEpoch, issued TickId, module+instance+entity ID, stable sequence, bounded WORLD-01 entity component patches and game events with role | GAME-02 stages, WORLD-01/GAME/NET validates and applies at CORE-03 fence |
| `ScriptCommitReceiptV1` | operation IDs, expected/applied world revision, accepted/rejected/partial explicit transaction mode, changed entities, replay/fault info | WORLD-01 commit authority; client script never self-authorizes |
| `ScriptBudgetV1` | compiler source/time/memory, VM heap/stack/coroutines, instruction/fuel/time, host calls, API cost, query rows, cmd bytes, output log bytes | enforced independently, default deny, typed stop on exceed |
| `ScriptExecutionReceiptV1` | InstanceId, TickId, module+ABI hashes, scheduled/actual CPU, fuel/instructions, VM heap/GC, host-call count, staged command digest, traps/status | CORE-06 metrics; separate staged from committed state and latency uncertainty |
| `ScriptFaultReceiptV1` | FaultId, severity/code, sanitized stack/source-map span, module rev, instance/world/epoch, phase/tick, last-known-good/disable reason | redacted diagnostics, no secrets/private player data |
| `GameplayProgramIRV1` | canonical typed operations/function IDs, values/control flow, side effects/capabilities, version, stable IDs, source map, instruction/fanout quotas | GAME-02-owned graph/text semantic target, not raw C++ AST or unrestricted VM |
| `VisualGraphV1` | GraphId/AssetId/revision, NodeId/PinId, value/control/event edges, functions, entry points, typed constants, imports, capability request, node layout metadata | DATA-04 source/CAS, GAME-02 graph parser/compiler; EDIT owns UI canvas |
| `VisualGraphValidationReceiptV1` | typed pin matches, unreachable/dead/error nodes, illegal loops/cycles/recursion, target ABI/capability, source-map diagnostics, compile hash | bounded validation; no side effects from source graph |
| `ScriptHotReloadPlanV1` | old/new ModuleId/revision/hash/API hash, instances affected, quiescence barrier, migration state snapshot/check, role/grant diff, canary, fallback, tick of swap | off-tick CORE-03 compile, DATA-04 CAS, WORLD-01 stable entity identity, single safe fence |
| `ScriptHotReloadReceiptV1` | plan ID, old/new active revision, staged/published/failed/rolled-back, side effect boundary, invalidated handles and cause | no pretend rollback of irreversible actions after world commit |
| `ScriptDebugSessionV1` | principal, Project/World/Instance scope, read-only variable permission, lease, max stack/locals/trace, breakpoint/step policy | no arbitrary eval/remote attach/shell, CORE-04 pause authorization |
| `ScriptDebugReceiptV1` | diagnostic/breakpoint ID, source-map location, paused TickId, bounded sanitized trace/value previews, timeout/release outcome | debugger must not read hidden world state or stall audio/world indefinitely |
| `ScriptCompilerReceiptV1` | target OS/arch, compiler/dialect version, input hash, validated bytecode/IR digest, typecheck results, import/capability closure and compiled-resource budget | trusted compiler-only bytecode, runtime ABI pinned, DATA-05 cook/provenance |
| `ScriptCapabilityReportV1` | supported/unknown/unavailable text/visual/WASM, JIT/AOT/Web/headless restrictions, memory/runtime/debug/coverage capability, benchmark proof | no false claim all target platforms work |
| `ScriptErrorV1` | typed error code, source module/tick/world/role, recoverability, redacted message/diagnostic ID | no OS secrets, arbitrary guest traceback or raw memory leak |

## 2. Authoring, compilation and execution operations
1. `InspectScriptCapabilities(project, target, role)` → feature, restrictions and actual proof status; unimplemented must return UNAVAILABLE/UNKNOWN, not success.
2. `StageScriptModule(source, lang, manifest, expectedRevision, principal)` → DATA-03 validated UTF-8, rights/import/size scan, DATA-04 source CAS; no code execution while parsing.
3. `StageVisualGraph(graph, expectedRevision, principal)` → pin/schema/capability validation, normalized source and semantic diff; EDIT can render but cannot bypass validation.
4. `CompileScriptSource(moduleId, revision, targetConfig)` → CORE-03 bounded background compile, typecheck, trusted bytecode/IR, source-map and content hash; no unsafe runtime import.
5. `CompileVisualGraphToIR(graphRevision, targetApiSchema)` → typed `GameplayProgramIRV1`/source maps using common API, equivalence tests vs text path, not privileged node execution.
6. `ValidateScriptCapabilities(module, grantSet, worldScope, actor)` → deny if module demands ungranted call, untrusted tier or stale role; return diff/denials.
7. `CreateScriptInstance(world, entityGuid, moduleRevision, grantSet)` → resolve fresh WORLD-01 EntityHandle/WorldEpoch and choose VM isolation budget; never expose C++ pointer.
8. `ScheduleScriptTick(instance, scriptTickContext, immutableSnapshot)` → CORE-03 job with phase/access sets and bounded budget, GAME-01 action frame; return execution receipt.
9. `CallScriptApi(instance, functionId, typedArgs, grant)` → check function ID/schema, role/units/quota/thread and map host function to safe read or **stage** operation only.
10. `CommitScriptIntents(commandBuffer, tickFence, gameAuthority)` → WORLD-01/NET validate and commit in declared deterministic order; typed accepted/rejected receipt.
11. `PreviewScriptReload(oldRev, newRev, targetWorld)` → compile/type/capability/state schema/compatibility/side-effect diff and deterministic canary; old runtime untouched.
12. `ActivateScriptReload(plan, approvedFence, role)` → drain old, snapshot only script-owned state, migrate, stage/swap active instance revision at boundary, error rollback or safe disable.
13. `SetScriptBreakpoint(session, moduleRev, sourceSpan)` → permissioned debug role and finite lease; no arbitrary eval or remote attach default.
14. `ReadScriptDiagnostics(instance, cursor, limit, principal)` → redacted bounded fault/trap/heap/CPU/GC/commit receipts, CORE-06 metrics source.
15. `ReplayScriptTrace(headlessHarness, immutableInputs, fixedTick, moduleHashes)` → approved test-only isolated harness and semantic receipt oracle; no live cheating/input injection.
16. `RevokeScriptCapability(grantId, reason, policyRevision)` → safe host-call/tick fence revocation, stop pending privileged commands and invalidate stale replay.

## 3. Typed failures
`SCRIPT_LANGUAGE_UNSUPPORTED`, `SCRIPT_COMPILER_UNAVAILABLE`, `SCRIPT_MODULE_STALE`, `SCRIPT_SOURCE_INVALID_UTF8`, `SCRIPT_SOURCE_TOO_LARGE`, `SCRIPT_IMPORT_NOT_ALLOWED`, `SCRIPT_UNTRUSTED_BYTECODE`, `SCRIPT_COMPILER_BUDGET_EXCEEDED`, `SCRIPT_TYPECHECK_FAILED`, `SCRIPT_GRAPH_INVALID`, `SCRIPT_GRAPH_UNBOUNDED_CYCLE`, `SCRIPT_PIN_TYPE_MISMATCH`, `SCRIPT_GRAPH_IR_INCOMPATIBLE`, `SCRIPT_API_SCHEMA_STALE`, `SCRIPT_FUNCTION_NOT_EXPOSED`, `SCRIPT_HOST_CALL_INVALID`, `SCRIPT_CAPABILITY_DENIED`, `SCRIPT_CAPABILITY_REVOKED`, `SCRIPT_AUTHORITY_DENIED`, `SCRIPT_WORLD_UNLOADED`, `SCRIPT_WORLD_EPOCH_STALE`, `SCRIPT_ENTITY_HANDLE_STALE`, `SCRIPT_COMPONENT_SCHEMA_MISMATCH`, `SCRIPT_QUERY_QUOTA_EXCEEDED`, `SCRIPT_VM_MEMORY_EXCEEDED`, `SCRIPT_VM_STACK_EXCEEDED`, `SCRIPT_VM_INSTRUCTION_BUDGET_EXCEEDED`, `SCRIPT_VM_TIMEOUT`, `SCRIPT_HOST_CALLBACK_BLOCKED`, `SCRIPT_JOB_CANCELLED`, `SCRIPT_TICK_EPOCH_STALE`, `SCRIPT_NONDETERMINISTIC_IMPORT`, `SCRIPT_COMMAND_BUFFER_FULL`, `SCRIPT_COMMIT_REJECTED`, `SCRIPT_REPLAY_MISMATCH`, `SCRIPT_RELOAD_SCHEMA_MISMATCH`, `SCRIPT_RELOAD_QUIESCE_TIMEOUT`, `SCRIPT_RELOAD_MIGRATION_FAILED`, `SCRIPT_RELOAD_SIDE_EFFECT_NOT_REVERSIBLE`, `SCRIPT_DEBUG_NOT_AUTHORIZED`, `SCRIPT_DEBUG_LEASE_EXPIRED`, `SCRIPT_LOG_QUOTA_EXCEEDED`, `SCRIPT_WEB_RUNTIME_RESTRICTED`, `SCRIPT_RUNTIME_UNAVAILABLE`, `SCRIPT_INTERNAL_FAILURE`.

## 4. Hard cross-module invariants
- WORLD-01 sole entity lifecycle/query/structural command/commit owner, all generational handles checked and expired across world/structural epochs; scripting never mutates raw ECS storage.
- CORE-03 sole thread/job/barrier owner, CORE-04 sole TickId/sim clock owner. Guest reads immutable snapshots and stages typed commands; no background C++ host callbacks with unchecked lifetime.
- GAME-01 sole action-map/input frame owner; GAME-02 scripts cannot poll devices or forge trusted input.
- GAME/NET sole gameplay/network authority; role/capability grants checked at call **and** commit.
- DATA-02/03/04/05 sole script identity/rights/import/CAS/source schema/cook. No arbitrary URL/path or unsigned untrusted bytecode; exact pinned compiler/runtime fingerprint before deployment.
- Text scripts and visual graph require same public API and semantic guardrails, no privileged graph node.
- Hot reload never mutates partially committed state and fails with old-known-good or safe disable; no pretending irreversible side effects rolled back.
- No OS/system/network, native FFI, full debug lib, raw C++ pointer, hidden script evaluation or default telemetry of private state.
- All named v1 types are proposals, not actual ABI/serialized format, with zero implementation/bench evidence.
