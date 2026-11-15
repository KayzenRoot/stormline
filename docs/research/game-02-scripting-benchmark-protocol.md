# GAME-02 — Reproducible Script VM, Host Binding, Sandbox and Hot Reload Benchmark Protocol

**P00 research-only protocol | Issue #212 | WO NLE-P00-WO-002-GAME-02 | Date 2026-11-15. ZERO BENCHMARK RUNS.** No Luau/Lua/WASM engine integration, compiler build, source/graph fixture, hot reload runtime, hardware test, measured CPU/GC, sandbox threat proof, Web binary or performance result.

## Questions to prove
1. Can one game entity script change a rule without recompiling CORE, using only checked WORLD-01 read snapshots, GAME-01 actions and WORLD-01/GAME typed authoritative command receipts?
2. Does Luau under our **specific host bindings** enforce capability denials, compiler/VM memory/instruction/time/host-call quotas, bytecode provenance and safe world/instance generations against hostile code?
3. Does textual source versus typed visual graph produce equivalent semantic command receipts and source-map diagnostics, or is a separate interpreted graph engine necessary and safely constrained?
4. Does hot reload stage/compile/migrate/quiesce/commit/rollback at a safe CORE-03/WORLD-01 fence with no UAF, duplicate event, frozen simulation or unrollbackable effect misreported as success?
5. What are native Windows/Linux/macOS, headless and Web compile footprint/latency/VM/runtime limits, and do Luau/Lua54/Wasmtime/WAMR/Wasm3 support the required sandbox and scripting semantics?
6. Is the benchmark deterministic for recorded `TickId`, seed, entity snapshot and input action frames across parallel workers, differing rendering FPS and target runtimes within explicitly defined numeric tolerance?

## Original legal reference fixtures (FUTURE, none generated)
- **LUAU-GOLDEN:** original simple move/attack ability script, typed component read, seeded damage computation, one queued component patch/event and expected Game/World commit oracle. No third-party game script pasted.
- **LUA54-GOLDEN:** independent semantically equivalent Lua 5.4 source within common subset, plus intentional dialect-only syntax rejection tests.
- **GRAPH-GOLDEN:** original `VisualGraphV1` with 16/64/256 nodes and safe loops/control flow, bound to common API schema; equivalent semantic input/output oracle vs textual source.
- **WASM-GOLDEN:** original WASM module with fuel-limited arithmetic, one permitted host call, unauthorized host import attempt and linear-memory cap.
- **EVIL-GOLDEN:** synthetic infinite loops, recursion, memory bombs, imports, crafted bytecode, host callback reentry, malformed graph/UTF-8/serialized API, stale generational entity handles, forbidden OS/network API requests and logging overflow.
- **RELOAD-GOLDEN:** same module with compatible state v1→v2 migration and intentionally incompatible schema/capability change, plus world unload during migration/commit.
- **TRACE-GOLDEN:** fixed simulation TickId/input action frames/world snapshot digest, seeded RNG and recorded deterministic world change receipts, no personal or copyrighted content.
All fixture source/hash/license/provenance, sample generation and permission status must be documented. Do not copy snippets from third-party games or unverified packages.

## Workload matrix
| Workload | Future load | Required measurements |
|---|---|---|
| VM cold/warm | 1/100/1000 modules, 32KiB/256KiB/1MiB source, varying types | compile/typecheck duration p50/p95/p99, cold/warm start, peak RSS, cache hits and missed imports |
| Script instances | 100/1000/10,000 instances, 60/120Hz fixed TickId, 30/60/144 render FPS | per-instance CPU median/p95/p99, tick budget/deadline misses, frame impact and GC pauses |
| Host API calls | 1/10/100 calls per script tick, scalar/typed struct/snapshot/command | native bridge overhead, bytes copied, denial path cost, component query cost and correctness |
| ECS command buffers | 10/100/1000 staged intents/tick across parallel scripts | validation/commit CPU, ordering, conflict rejection, stale handle/epoch and memory |
| Visual graph | 16/64/256 nodes, 1/4/16 subgraphs, typed loop vs forbidden cycles | schema validation/IR compile, source map, runtime CPU, parity digest and memory |
| Sandboxing | CPU infinite loop, stack, heap, host calls/queries/output floods | interrupts, resource enforcement, time to trap, per-world isolation, no host process crash or secret leak |
| Hot reload | 1/10/100 reloads/minute, 1000 sequential swaps, incompatible migration | compile-to-activate latency, old instance drain time, rollback success, stale handle count and leaks |
| WASM optional | Wasmtime (fuel/epoch), WAMR interp and Wasm3 interp, AOT/JIT as supported | program equivalence, startup, binary size, RSS, fuel/stop, WASI import deny and target capability |
| Portability | Windows/Linux/macOS/arm64 feasible, headless and browser WASM | exact compiler/runtime schema capabilities, semantic receipts, package distribution/SBOM and no mandatory GUI |
| Soak | 60 minutes at varying scripts/rate + world load/unload + hot reload | memory/GC high-water, dangling callback/UAF, CPU drift, hangs and diagnostics loss |

## Measurement and reproducibility method
- **Environment metadata:** Git BASE/HEAD, proposed ADR, exact compiler/runtime tag/commit/hashes, CMake flags, native toolchain/stdlib, ASan/TSan configuration, backend VM, script bytecode digest, API schema version, target OS/CPU/arch and power settings, WORLD-01/CORE-03/04/GAME-01 revisions.
- **Workload:** identical scripted business semantics and explicit runtime differences, original fixture hash, isolated seeded input/world trace, replays with fixed tick; report any unsupported language feature and don't pretend source-equivalence when semantics differ.
- **Time:** separate compile/typecheck, VM cold start, per-tick interpreter/JIT, host API bridge, ECS staged/commit and GC; p50/p95/p99/max, distribution and confidence intervals with repetitions and warm/cold separation.
- **Memory:** VM heap/stack, native host buffers, compiler output, WASM linear memory *and* total host/compiler memory; don't assume linear-memory cap bounds entire process.
- **Security:** adversarial fuzz corpus with compiler/VM and host callbacks, error budgets, timeout measurement and stable denial receipts. A sandbox runner and a malicious-code test must be separately audited; stronger process sandbox required for hostile plugins.
- **Hot reload:** record staging/quiescence/activation TickId, source/schema hash, migrator behavior, rollback policy, world side-effect idempotency and surviving old-VM references.
- **Targets:** Windows x64, Linux x64/ARM consideration, macOS arm64/Intel consideration, headless and Web; JIT availability and WASI imports must be actually tested per target. CI compile ≠ game performance.
- **Thresholds:** budgets for source, heap, instructions, script/tick CPU, host calls, compile/hot reload latency and VM count are **UNDECIDED** until baseline target minimum hardware and independent threat-model proof. No invented FPS, VM speedup, sandbox safety or zero-downtime hot reload claims.
- **Evidence:** raw benchmark CSV/traces, reproduction commands, source rights/fixture hashes, CI/build, fuzz/sanitizer, failure/rollback, differential results, independent review if HIGH_ASSURANCE and pt-BR objective audit. P00 has NONE.
