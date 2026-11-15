# GAME-02 — Acceptance Matrix: 128 FUTURE Tests, NONE EXECUTED

**Research issue #212 | WO NLE-P00-WO-002-GAME-02 | future coding #58 OPEN/BLOCKED.** Exactly **128 prospective cases** across **16 suites × 8**. Every test is **FUTURE / NOT EXECUTED**. Catalog acceptance "Modificar regras sem recompilar Core e com limites de segurança" is NOT MET by research documents. No script engine, sandbox, bytecode/compiler, visual graph, host binding, hot reload, source runtime, real tests or benchmark exists.

| Case | Prospective test/oracle | Status |
|---|---|---|
| GAME02-LAN-01 | Luau original source with gradual types parses and produces expected typecheck success receipt | FUTURE / NOT EXECUTED |
| GAME02-LAN-02 | Ill-typed arithmetic/entity API argument rejects before module activation | FUTURE / NOT EXECUTED |
| GAME02-LAN-03 | Lua 5.4-only syntax is not silently reported as Luau-compatible | FUTURE / NOT EXECUTED |
| GAME02-LAN-04 | Declared language/dialect/compiler hash mismatch rejects cached compiled artifact | FUTURE / NOT EXECUTED |
| GAME02-LAN-05 | Malformed UTF-8, oversized source and deeply nested parse hit explicit source limits | FUTURE / NOT EXECUTED |
| GAME02-LAN-06 | Compiler crash or out-of-memory fails with safe diagnostic without corrupting active world | FUTURE / NOT EXECUTED |
| GAME02-LAN-07 | Untrusted raw bytecode without trusted compiler provenance is never loaded | FUTURE / NOT EXECUTED |
| GAME02-LAN-08 | Compile diagnostics retain stable source spans across changes in source revision | FUTURE / NOT EXECUTED |
| GAME02-SAN-01 | Sandboxed Luau lacks file/system/process/native FFI/package loadlib APIs | FUTURE / NOT EXECUTED |
| GAME02-SAN-02 | Script cannot mutate shared globals of another isolated module without grant | FUTURE / NOT EXECUTED |
| GAME02-SAN-03 | Reflection/debug APIs cannot expose C++ pointers or privileged environment | FUTURE / NOT EXECUTED |
| GAME02-SAN-04 | Malicious host callback attempts to return dangling entity pointer and is rejected | FUTURE / NOT EXECUTED |
| GAME02-SAN-05 | Script calls host function without matching capability grant and receives DENIED | FUTURE / NOT EXECUTED |
| GAME02-SAN-06 | Capability revocation invalidates pending same-instance host calls and command intents | FUTURE / NOT EXECUTED |
| GAME02-SAN-07 | Trusted internal module does not inherit raw network/filesystem privilege by default | FUTURE / NOT EXECUTED |
| GAME02-SAN-08 | Guest text cannot access secrets/private player data via exceptions or stack traces | FUTURE / NOT EXECUTED |
| GAME02-BUD-01 | Infinite loop is interrupted or trapped within declared VM execution budget | FUTURE / NOT EXECUTED |
| GAME02-BUD-02 | Allocator quota rejects excessive table/string heap growth with safe VM fault | FUTURE / NOT EXECUTED |
| GAME02-BUD-03 | Excess coroutine/recursion/stack usage yields bounded fault without process crash | FUTURE / NOT EXECUTED |
| GAME02-BUD-04 | Compilation of huge adversarial input respects independent compile CPU/memory quota | FUTURE / NOT EXECUTED |
| GAME02-BUD-05 | Host C++ function with high cost cannot escape budget by blocking inside callback | FUTURE / NOT EXECUTED |
| GAME02-BUD-06 | Excessive host call/query/command volume is rejected at per-tick budget | FUTURE / NOT EXECUTED |
| GAME02-BUD-07 | Excessively large script print/log payload is capped and redacted | FUTURE / NOT EXECUTED |
| GAME02-BUD-08 | Quota exhaustion in one script instance does not crash or starve another world instance | FUTURE / NOT EXECUTED |
| GAME02-API-01 | ApiFunctionId with wrong schema/version is rejected before C++ function call | FUTURE / NOT EXECUTED |
| GAME02-API-02 | Malformed numeric NaN/Inf/negative or length in vector/struct argument is rejected | FUTURE / NOT EXECUTED |
| GAME02-API-03 | Generic Lua userdata cannot be cast to arbitrary native component object | FUTURE / NOT EXECUTED |
| GAME02-API-04 | Nested host call and reentrant script execution obey declared phase and bounds | FUTURE / NOT EXECUTED |
| GAME02-API-05 | Native C++ exceptions do not escape through C ABI/guest boundary | FUTURE / NOT EXECUTED |
| GAME02-API-06 | Unknown or revoked API function fails closed with typed result | FUTURE / NOT EXECUTED |
| GAME02-API-07 | Read-only host API may not mutate world, filesystem or renderer | FUTURE / NOT EXECUTED |
| GAME02-API-08 | Native/Web/headless adapters produce equivalent semantic API error results | FUTURE / NOT EXECUTED |
| GAME02-ECS-01 | Script resolves EntityGuid to live generational handle in matching world epoch | FUTURE / NOT EXECUTED |
| GAME02-ECS-02 | Entity destroyed/reused between snapshot and commit causes stale handle rejection | FUTURE / NOT EXECUTED |
| GAME02-ECS-03 | Cross-world entity handle cannot access another world's component | FUTURE / NOT EXECUTED |
| GAME02-ECS-04 | Component schema revision mismatch rejects unsafe update and produces migration hint | FUTURE / NOT EXECUTED |
| GAME02-ECS-05 | Readonly query snapshot expires at declared WORLD-01 structural commit fence | FUTURE / NOT EXECUTED |
| GAME02-ECS-06 | Script sets component only through typed EntityCommandBuffer, no raw archetype storage | FUTURE / NOT EXECUTED |
| GAME02-ECS-07 | Unloaded entity returns UNLOADED/UNKNOWN rather than silently creating one | FUTURE / NOT EXECUTED |
| GAME02-ECS-08 | Per-role protected component fields are absent from script query results | FUTURE / NOT EXECUTED |
| GAME02-JOB-01 | Script background jobs use CORE-03 worker ownership and declared read/write sets | FUTURE / NOT EXECUTED |
| GAME02-JOB-02 | Two scripts stage conflicting entity writes and deterministic commit policy rejects/merges correctly | FUTURE / NOT EXECUTED |
| GAME02-JOB-03 | World mutation does not become visible before WORLD-01 authoritative commit receipt | FUTURE / NOT EXECUTED |
| GAME02-JOB-04 | CORE-03 task cancellation drains guest instances before world unload | FUTURE / NOT EXECUTED |
| GAME02-JOB-05 | Guest cannot call unsafe main-thread OS API from scheduler worker | FUTURE / NOT EXECUTED |
| GAME02-JOB-06 | Task graph dependency cycle or owner deadlock is prevented/reported | FUTURE / NOT EXECUTED |
| GAME02-JOB-07 | Script command order is stable for same TickId/module/entity/source sequence | FUTURE / NOT EXECUTED |
| GAME02-JOB-08 | CORE-03 work-budget overrun yields deadline receipt instead of arbitrary blocking | FUTURE / NOT EXECUTED |
| GAME02-TIK-01 | Fixed TickId inputs produce equivalent action/command receipt with 30/144Hz render FPS | FUTURE / NOT EXECUTED |
| GAME02-TIK-02 | Same GAME-01 InputActionFrame and seeded RNG yield same authored decisions | FUTURE / NOT EXECUTED |
| GAME02-TIK-03 | Wall clock and external entropy are disabled on authoritative deterministic script path | FUTURE / NOT EXECUTED |
| GAME02-TIK-04 | Sim pause/step/scale are CORE-04-owned and script cannot change clock directly | FUTURE / NOT EXECUTED |
| GAME02-TIK-05 | Replay trace mismatch in schema/hash/seed/epoch fails with typed result | FUTURE / NOT EXECUTED |
| GAME02-TIK-06 | Float-sensitive workload is checked semantically with tolerances, not assumed bitwise identical | FUTURE / NOT EXECUTED |
| GAME02-TIK-07 | InputActionFrame from foreign seat or stale tick rejected before script execution | FUTURE / NOT EXECUTED |
| GAME02-TIK-08 | Script coroutine yield/resume follows permitted tick phase, not hidden wall timer | FUTURE / NOT EXECUTED |
| GAME02-GRF-01 | Simple typed visual graph compiles to same ScriptApiSchema host functions as textual source | FUTURE / NOT EXECUTED |
| GAME02-GRF-02 | Invalid pin type/unit across edges produces scoped error before graph activation | FUTURE / NOT EXECUTED |
| GAME02-GRF-03 | Illegal instantaneous data cycles and recursive subgraphs rejected with bounded traversal | FUTURE / NOT EXECUTED |
| GAME02-GRF-04 | Intentional loop node uses explicit static or runtime instruction bound | FUTURE / NOT EXECUTED |
| GAME02-GRF-05 | Graph authoring cannot define arbitrary native host-call node | FUTURE / NOT EXECUTED |
| GAME02-GRF-06 | Graph and textual equivalent program yield same read/intent/commit receipt digest | FUTURE / NOT EXECUTED |
| GAME02-GRF-07 | Source map reports original NodeId/PinId for graph execution fault | FUTURE / NOT EXECUTED |
| GAME02-GRF-08 | Graph UI canvas cannot execute unvalidated node when edited via CLI/MCP | FUTURE / NOT EXECUTED |
| GAME02-REL-01 | New script compilation/typecheck failure leaves old known-good module active | FUTURE / NOT EXECUTED |
| GAME02-REL-02 | Module changed state schema without migration returns incompatible plan | FUTURE / NOT EXECUTED |
| GAME02-REL-03 | Staging instance activation occurs at CORE-03/WORLD-01 safe tick fence only | FUTURE / NOT EXECUTED |
| GAME02-REL-04 | Pending old coroutine/task drains before old module or buffers are retired | FUTURE / NOT EXECUTED |
| GAME02-REL-05 | Successful state-only migration preserves declared script-owned values with correct revision | FUTURE / NOT EXECUTED |
| GAME02-REL-06 | Script reload cannot overwrite authoritative ECS/gameplay state from old snapshot | FUTURE / NOT EXECUTED |
| GAME02-REL-07 | Postcommit irreversible side effect is explicitly flagged nonreversible, not falsely rolled back | FUTURE / NOT EXECUTED |
| GAME02-REL-08 | Multiplayer clients/server apply coordinated authoritative script revision or reject mismatched tick | FUTURE / NOT EXECUTED |
| GAME02-MOD-01 | Only DATA-02 AssetId and pinned revision permitted for script require/import | FUTURE / NOT EXECUTED |
| GAME02-MOD-02 | Host absolute path, URL, symlink and parent traversal module import denied | FUTURE / NOT EXECUTED |
| GAME02-MOD-03 | Module cyclic dependency and fanout/size quotas reject pathological import graph | FUTURE / NOT EXECUTED |
| GAME02-MOD-04 | Content hash changed invalidates cached bytecode and dependent module manifest | FUTURE / NOT EXECUTED |
| GAME02-MOD-05 | Unsigned or tampered bytecode never runs even when filename is familiar | FUTURE / NOT EXECUTED |
| GAME02-MOD-06 | Data/asset author rights and platform export target are validated separately from VM license | FUTURE / NOT EXECUTED |
| GAME02-MOD-07 | Unknown required package capability blocks activation rather than ignoring it | FUTURE / NOT EXECUTED |
| GAME02-MOD-08 | Compile/cache artifact fingerprint includes compiler/runtime/API schema version | FUTURE / NOT EXECUTED |
| GAME02-DBG-01 | Authorized local Editor debugger sets breakpoint on matching script source revision | FUTURE / NOT EXECUTED |
| GAME02-DBG-02 | Missing debug scope cannot inspect instance variables or hidden world components | FUTURE / NOT EXECUTED |
| GAME02-DBG-03 | Single-step respects CORE-04 pause and finite lease rather than freezing audio thread | FUTURE / NOT EXECUTED |
| GAME02-DBG-04 | SourceMap translates VM program counter and graph pin to stable authored span | FUTURE / NOT EXECUTED |
| GAME02-DBG-05 | Script trace stack/message strips secrets, player PII, host paths and raw pointers | FUTURE / NOT EXECUTED |
| GAME02-DBG-06 | Debugger disconnect/timeout resumes or safe-stops simulation by declared policy | FUTURE / NOT EXECUTED |
| GAME02-DBG-07 | Runtime fault records TickId/module/instance/failed command receipt without full source dump | FUTURE / NOT EXECUTED |
| GAME02-DBG-08 | CORE-06 p95/p99 script CPU/heap/GC counters have bounded telemetry overhead | FUTURE / NOT EXECUTED |
| GAME02-WAS-01 | Wasmtime deterministic fuel timeout traps infinite guest loop at declared budget | FUTURE / NOT EXECUTED |
| GAME02-WAS-02 | Wasmtime store limiter rejects linear-memory/table/instance growth above limits | FUTURE / NOT EXECUTED |
| GAME02-WAS-03 | WASI filesystem/network/clock/random imports absent by default | FUTURE / NOT EXECUTED |
| GAME02-WAS-04 | WAMR interpreter and Wasm3 comparator reject malformed wasm module without host crash | FUTURE / NOT EXECUTED |
| GAME02-WAS-05 | Host import validates capability and generation before touching native world | FUTURE / NOT EXECUTED |
| GAME02-WAS-06 | Web/desktop JIT unavailable path reports safe interpreter/AOT fallback or UNSUPPORTED | FUTURE / NOT EXECUTED |
| GAME02-WAS-07 | Component Model/WIT ABI version mismatch rejects module at validation | FUTURE / NOT EXECUTED |
| GAME02-WAS-08 | Actual runtime memory including compiler/host overhead measured independently from linear memory | FUTURE / NOT EXECUTED |
| GAME02-NET-01 | Client script submits forged privileged gameplay event and server authority rejects | FUTURE / NOT EXECUTED |
| GAME02-NET-02 | Script cannot emit arbitrary network RPC/socket or change authentication role | FUTURE / NOT EXECUTED |
| GAME02-NET-03 | Role-scoped entity mutation denied even with valid module bytecode | FUTURE / NOT EXECUTED |
| GAME02-NET-04 | Event recursion/feedback loops bounded by event-queue and tick-phase caps | FUTURE / NOT EXECUTED |
| GAME02-NET-05 | Duplicate ScriptCommandBuffer event/sequence is idempotent at authoritative commit | FUTURE / NOT EXECUTED |
| GAME02-NET-06 | Cross-world and cross-user scripts cannot read secret player inventory | FUTURE / NOT EXECUTED |
| GAME02-NET-07 | Remote/MCP authoring principal may stage preview but not execute untrusted live eval | FUTURE / NOT EXECUTED |
| GAME02-NET-08 | Replay/rollback reapplication rejects stale grants and mismatched module revisions | FUTURE / NOT EXECUTED |
| GAME02-PLT-01 | Windows x64 native host compiles Luau comparator and validates owner/threading rules | FUTURE / NOT EXECUTED |
| GAME02-PLT-02 | Linux x64 and ARM feasibility with thread sanitizer and headless CLI harness | FUTURE / NOT EXECUTED |
| GAME02-PLT-03 | macOS arm64 and Intel feasibility with no mandatory JIT executable-page permissions | FUTURE / NOT EXECUTED |
| GAME02-PLT-04 | Browser WebAssembly/JS hosted execution uses scoped imports and feature fallback | FUTURE / NOT EXECUTED |
| GAME02-PLT-05 | Headless dedicated server works without GUI/GPU/audio and uses same ScriptApiSchema | FUTURE / NOT EXECUTED |
| GAME02-PLT-06 | Editor+export preserve semantic script API/capability behavior across target packages | FUTURE / NOT EXECUTED |
| GAME02-PLT-07 | Compiler/runtime library and any native binding packaging have reviewed notices/SBOM | FUTURE / NOT EXECUTED |
| GAME02-PLT-08 | Unsupported target backend returns explicit capability UNAVAILABLE, not a fake pass | FUTURE / NOT EXECUTED |
| GAME02-SEC-01 | Untrusted script parser/typechecker/VM bytecode fuzz under ASan/UBSan finds no blocker | FUTURE / NOT EXECUTED |
| GAME02-SEC-02 | Untrusted graph and API-call deserializer fuzz rejects malformed lengths/unions | FUTURE / NOT EXECUTED |
| GAME02-SEC-03 | Unauthorized host API path/property traversal and native function escape are denied | FUTURE / NOT EXECUTED |
| GAME02-SEC-04 | Forced native host exception/panic converts to typed fault without process termination | FUTURE / NOT EXECUTED |
| GAME02-SEC-05 | Entity handle stale/ABA/freed component under reload triggers no use-after-free | FUTURE / NOT EXECUTED |
| GAME02-SEC-06 | Graceful VM shutdown drains workers and no pending privileged events execute after revoke | FUTURE / NOT EXECUTED |
| GAME02-SEC-07 | OOM/stack/CPU starvation attempts cannot corrupt other scripts or editor project | FUTURE / NOT EXECUTED |
| GAME02-SEC-08 | Security review validates signed bytecode workflow, revocation, no default global eval | FUTURE / NOT EXECUTED |
| GAME02-BEN-01 | 100/1000/10000 script instances measure per-tick p50/p95/p99 and worst-frame CPU | FUTURE / NOT EXECUTED |
| GAME02-BEN-02 | 1/10/100 host calls per script measure native binding overhead and memory | FUTURE / NOT EXECUTED |
| GAME02-BEN-03 | Luau vs Lua 5.4 equivalent workload reports controlled comparable semantics | FUTURE / NOT EXECUTED |
| GAME02-BEN-04 | Wasmtime/WAMR/Wasm3 optional lanes measure cold compile, warm start, RSS and fuel costs | FUTURE / NOT EXECUTED |
| GAME02-BEN-05 | Typed visual graph compilation and execution compared to equivalent textual program | FUTURE / NOT EXECUTED |
| GAME02-BEN-06 | 1000 hot reload operations measure staging/activation latency/rollback/leaks | FUTURE / NOT EXECUTED |
| GAME02-BEN-07 | 30/60 minute sandbox-run with GC and repeated world unload shows no memory growth | FUTURE / NOT EXECUTED |
| GAME02-BEN-08 | Same captured TickId/ActionFrame/state across native and Web compares semantic receipts | FUTURE / NOT EXECUTED |

## Evidence obligations and pass/fail semantics
- **Source and ABI:** pin exact Luau/Lua/WASM/compiler runtime versions, C++20 toolchain, STL/ABI flags and ALL transitive license/SBOM. Original project scripts and graph fixtures only; never execute an untrusted asset at import.
- **Unit/property:** Parser/type, capability scope, phase/thread, host arg bounds, world instance/generation, deterministic order, signed artifact checks, graph pin/loops/IR, hot reload migration, typed errors.
- **Integration:** WORLD-01 snapshot/command/commit, CORE-03 worker barriers, CORE-04 TickId, GAME-01 InputActionFrame, GAME/NET role, DATA-02/03/04/05 import/cook/CAS, AI/Editor scope and CORE-06 diagnostics.
- **Security:** VM sandbox bypass attempts, native host callback abuse, unsigned bytecode, import traversal/WASI denied, script API privilege escalation, private content leak, fuzz + ASan/UBSan/TSan as applicable and high-assurance independent review if hostile privileged workloads.
- **Execution budget:** compiler memory/CPU, runtime fuel/instruction, VM heap/stack/coroutines, host calls, queries and command-buffer/event counts. A timeout that only logs but fails to stop is a FAIL.
- **Determinism:** fixed TickId, controlled seed and stable snapshot/command hash; compare semantic result and approved float tolerances across native/Web, not claim universal bitwise equivalence.
- **Hot reload:** compile/type/migrate stage, quiesce, safe swap, rollback old-known-good or disable, no rollback of irreversible side effect; network coordinated script version.
- **Visual scripting:** graph validation/permissions/source-map and text equivalence, no duplicate privileged execution boundary.
- **Performance:** p50/p95/p99/worst CPU, compile/warm start, memory/GC, host binding overhead, command throughput, file/ABI hashes, real target hardware, jitter and long-run leak.
- **Negative evidence:** NO case executed; no native/Web/headless builds, no scripts compiled/evaluated, no sandbox/fuzz/sanitizers or numerical benchmarks, no evaluated runtime adoption or malware resistance proof. Docs Validation tests documentation only.
