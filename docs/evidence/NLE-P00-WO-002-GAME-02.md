# Evidence Bundle — NLE-P00-WO-002-GAME-02 Gameplay Scripting & API

**STATUS: RESEARCH PR #213 APPROVED/SQUASH-MERGED; FINAL EXACT-HEAD DOCS VALIDATION SUCCESS; SEPARATE CHECKPOINT PR PENDING ITS OWN CI/AUDIT/SQUASH/READBACK. NO SCRIPT ENGINE.**  
**2026-11-15 | Research [#212](https://github.com/KayzenRoot/stormline/issues/212) | Future code [#58](https://github.com/KayzenRoot/stormline/issues/58) OPEN/BLOCKED | BASE main `8b12b71f090974e7c909265cb249f3fec297c89e`.**

## 1. Source Pack and Context Lock
GAME-01 research #208/PR #209, checkpoint #210 and closeout #211 merged; main SHA `8b12b71f090974e7c909265cb249f3fec297c89e`. Before GAME-02: 39/80 research documented (48.75%), 41 pending, 0 implemented, 80 coding packets BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null. GAME-02 catalog #40, requires WORLD-01 and CORE-03, both documents only and not engine code. Code #58 OPEN/BLOCKED. Source priority checkpoint > approved Ledger/ADRs > Scope > DoD > Architecture > Requirements > AGENTS > catalog/registry > WORLD/CORE/GAME reference docs. All Git blob fingerprints in [Work Order](../work-orders/NLE-P00-WO-002-GAME-02.md). No approved canonical decision overwritten.

## 2. Eight documentary research artifacts
1. [Architecture](../architecture/game-02-gameplay-scripting-api.md): Luau/Lua/WASM candidates, ScriptHost, capabilities, VM/host quotas, WORLD-01 ECS, CORE-03 jobs, GAME-01 input, CORE-04 TickId, visual/text IR, deterministic commit, debugging, hot reload and privacy.
2. [ADR-0043 PROPOSED](../adr/0043-game-02-engine-owned-capability-script-host.md).
3. [Technology/license/security matrix](../research/game-02-scripting-technology-license-matrix.md): Luau MIT, PUC-Lua 5.4 MIT, sol2 MIT, LuaBridge3 MIT, Wasmtime Apache-2.0, WAMR Apache-2.0 LLVM exception, Wasm3 MIT, imgui-node-editor MIT; all not adopted.
4. [Typed semantic contracts](../contracts/game-02-gameplay-scripting-api.md): module/source/VM/instance/host function/capability/IR/graph/ECS command/hot reload/fault/debug/receipt.
5. [128 FUTURE acceptance tests](../testing/game-02-acceptance-matrix.md), NOT EXECUTED.
6. [Reproducible VM/host security/performance benchmark protocol](../research/game-02-scripting-benchmark-protocol.md), NO numerical benchmark run.
7. [Research Work Order](../work-orders/NLE-P00-WO-002-GAME-02.md) with canonical fingerprints, full scope/DoD/stop.
8. This Evidence Bundle.

## 3. Official references checked (2026-11-15)
- [Luau source/MIT](https://github.com/luau-lang/luau), [sandbox](https://luau.org/sandbox/), [C API](https://luau.org/api/), [security](https://github.com/luau-lang/luau/blob/master/SECURITY.md), [PUC-Lua 5.4](https://www.lua.org/manual/5.4/manual.html), [Lua MIT](https://www.lua.org/license.html).
- [sol2 MIT](https://sol2.readthedocs.io/en/latest/licenses.html), [LuaBridge3 MIT](https://github.com/kunitoki/LuaBridge3).
- [Wasmtime Apache-2.0](https://github.com/bytecodealliance/wasmtime/blob/main/LICENSE), [fuel/epoch interruption](https://docs.wasmtime.dev/examples-interrupting-wasm.html), [Store limits](https://docs.wasmtime.dev/c-api/store_8h.html), [WAMR](https://github.com/wasm-micro-runtime/wasm-micro-runtime), [Wasm3](https://github.com/wasm3/wasm3), [WASI feature status](https://github.com/WebAssembly/WASI/blob/main/docs/ComponentModelFeatures.md).
- [Godot VisualScript removal](https://godotengine.org/article/godot-4-will-discontinue-visual-scripting/), [ImGui node editor MIT](https://github.com/thedmd/imgui-node-editor).

## 4. Verification ledger (actual observed evidence only)
| Gate | Current status |
|---|---|
| Research issue #212 and branch from exact base main | OBSERVED |
| Exactly eight Markdown files and research PR changed-file diff | [PR #213](https://github.com/KayzenRoot/stormline/pull/213) Draft inspected: exactly 8 newly added Markdown files; no code, SDK, dataset or CI change. |
| Initial Docs Validation | [Run #43701653288](https://github.com/KayzenRoot/stormline/actions/runs/43701653288) SUCCESS on pre-Evidence-update head `614c0b6bc1a85bd137fab874789bf354cc446838`, job #132773892137; Source Pack/local links, module DAG, WO registry and Zcode blocked selector all SUCCESS. New Evidence commit must be revalidated. |
| CodeQL/SonarCloud/Socket or other scanner exact HEAD | NOT VERIFIED |
| Compiler/VM/runtime/host API integrated | NO |
| Native/Web/headless executable, VM sandbox built | NO |
| Lua/Luau/WASM source compiled or bytecode executed | NO |
| Visual graph compiled, hot reload or debugger exercised | NO |
| 128 FUTURE acceptance tests | NOT EXECUTED |
| VM CPU/memory/GC/host call/latency/p95/p99 benchmark | NOT RUN |
| Fuzz/ASan/UBSan/TSan/security exploit proof | NOT RUN |
| Objective pt-BR documentary audit | APPROVED documentary-only [comment #6892661141](https://github.com/KayzenRoot/stormline/pull/213#issuecomment-6892661141), no known HIGH/CRITICAL in scoped eight-doc diff. |
| Research PR squash/main readback | PR #213 normal squash main `bfefc3075947bd984c70b0013b44c4e34d253190`, readback verified. |
| Separate checkpoint PR CI/audit/squash/readback | PENDING own exact-final-HEAD Docs Validation/pt-BR objective audit/normal squash/main readback. |

## 5. Risk register and negative evidence
- **Host callback privilege:** Luau sandbox can be defeated by unsafe C++ bindings; no raw entity pointers, FFI, OS/network or unchecked reflection. Source typecheck is not sandbox proof.
- **Infinite loop / host-call hang:** VM guest interrupt may not preempt C++ callback; compile/heap/instruction/time/query/host call/console quotas required. No quota runtime has been measured or implemented.
- **Untrusted bytecode:** Luau assumes compiler-origin validity; arbitrary uploaded bytecode must be rejected or recompiled from vetted source. Cryptographic artifact authenticity is conceptual and not operational.
- **ECS stale/ABA/data race:** WORLD-01 generational handle/cell/snapshot epoch may be stale after unload/reload. CORE-03 worker may only stage intents and use validated data.
- **Hot reload:** migration and old/new instance overlap can cause memory UAF or duplicate irreversible side effects; safe fence and rollback plan only documented.
- **Visual graph parity:** nodes and text may diverge in semantics; IR/source maps need tested equivalence. Graph editor MIT only GUI candidate.
- **Native/Web/JIT/float:** browser and OS runtime restrictions, WASI imports, GC and float ordering need proof; no universal determinism or speed claims.
- **Privacy:** debugger, exception trace or MCP could leak secret game/world/player state; permissioned sanitized telemetry only. Third-party rights/SBOM and NLE-D009 engine software license open.
No known HIGH/CRITICAL in purely documentary scope can be concluded only after PR audit; live risk mitigation and sandbox security are NOT PROVEN.

## 6. Proposed checkpoint delta (NOT PROMOTED)
Only after exact-final-HEAD research PR CI/audit/squash/main readback and **separate checkpoint PR** exact-final-HEAD CI/audit/squash/main readback, GAME-02 research_status alone changes RESEARCH_PENDING → RESEARCH_DOCUMENTED_ADR_PROPOSED. Then **40/80 (50%) researched, 40 pending, 0 runtime modules**. All 80 code WOs remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null. Coding issue #58 OPEN/BLOCKED, ADR-0043 PROPOSED, software license NLE-D009 OPEN. Next GAME-03 #59 research only; NO Zcode coding unlock.

## 7. Audit output contract
Objective pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED; BASE/HEAD SHA, changed docs and canonical fingerprints, official license/VM/host API/adversarial security/capability/hot reload ownership and preview/recovery, actual CI and negative evidence, 128 tests FUTURE, exact research-status diff and postmerge readback. No "completed" based solely on a comment.

## 8. Audited research merge evidence
- Research [PR #213](https://github.com/KayzenRoot/stormline/pull/213), exactly eight Markdown documents, BASE `8b12b71f090974e7c909265cb249f3fec297c89e`, final HEAD `03f2b2a15cfeeb65631cfdd1912183e5e4f25e11`, [Docs Validation #43701714741](https://github.com/KayzenRoot/stormline/actions/runs/43701714741) SUCCESS job #132774084828; objective pt-BR audit #6892661141 APPROVED documentary only.
- Normal squash main `bfefc3075947bd984c70b0013b44c4e34d253190`, readback verified. No Luau/Lua/WASM code built or executed, no VM rights adopted; 128 future cases NOT EXECUTED.
- Separate checkpoint PR shall be independently validated before registry research status is canonical. Future code #58 remains OPEN/BLOCKED.
