# Research Work Order — NLE-P00-WO-002-GAME-02

**Date:** 2026-11-15 | **Research issue:** #212 | **Future implementation:** #58 OPEN/BLOCKED  
**BASE main:** `8b12b71f090974e7c909265cb249f3fec297c89e`. **P00 DOCUMENTATION ONLY.** Research risk LOW; future script-host sandbox + privileges ELEVATED; hostile untrusted scripts or irreversible privileged capabilities require independent HIGH_ASSURANCE review/proof before authorization. Release class UNDECIDED; engine code license NLE-D009 OPEN.

## OBJECTIVE
Research and specify the Stormline-owned gameplay scripting and public API layer across native Windows/Linux/macOS, headless server, future Web: Luau/Lua 5.4/Wasm runtime candidates, sandbox/capabilities and C++ binding safety, typed graph/text shared IR, deterministic WORLD-01 ECS snapshot/commands, CORE-03 job schedule/tick fences, GAME-01 action frames, hot reload/state migrations, diagnostics/debug/telemetry, reliable authoring via Editor/CLI/MCP, official SDK/licenses, 128 future tests and benchmark proof plan.

## CONTEXT
Last confirmed main after GAME-01 research #208/PR #209, checkpoint PR #210, readback closeout PR #211: `8b12b71f090974e7c909265cb249f3fec297c89e`. 39/80 research documented (48.75%), 41 pending, zero runtime modules, all 80 future coding packets BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null. GAME-02 catalog order 40 depends only on WORLD-01 and CORE-03; both are research/documentation, no runtime. Implementation issue #58 OPEN/BLOCKED. Next GAME-03 catalog order 41, future coding issue #59.

## SCOPE
Exactly eight new Markdown artifacts in dedicated research branch:
1. [Architecture — gameplay scripting and public API](../architecture/game-02-gameplay-scripting-api.md).
2. [ADR-0043 PROPOSED — capability-scoped ScriptHost](../adr/0043-game-02-engine-owned-capability-script-host.md).
3. [Official technology/license/threat matrix](../research/game-02-scripting-technology-license-matrix.md).
4. [Typed conceptual public scripting contracts](../contracts/game-02-gameplay-scripting-api.md).
5. [128 FUTURE prospective cases](../testing/game-02-acceptance-matrix.md).
6. [Reproducible benchmark protocol](../research/game-02-scripting-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-02.md).

Create research issue #212, branch at exact main, research PR Draft with exactly eight docs, exact-final-HEAD Docs Validation and objective pt-BR audit, normal squash/readback. **Only after research merged** open a separate checkpoint PR (five files: checkpoint, backlog, implementation-registry JSON, same WO and same Evidence Bundle) with its own exact-final-HEAD CI/audit/squash/readback. Close research issue #212 only after canonical registry checkpoint merge/readback.

## OUT OF SCOPE
Implementation of C++/Luau/Lua/Wasmtime/WAMR/Wasm3, runtime sandbox, WASI, native UI/visual editor, real script language parser, VM worker, C++ binding/headers, executable bytecode/fixture, hot reload, debugger, OS/container isolation, asset importer, public SDK, signing keys, cloud scripts, user-generated mods, native plugins, any app build, actual tests, fuzzer/benchmark/deployment, use of paid services, credentials, unrelated cleanup, broad governance refactor or modification/unlocking of coding issue #58. Do not append changes to existing CORE/WORLD/GAME canons in research PR.

## FILES/SOURCES TO READ (priority)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and APPROVED ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/GAME-02.md` > `docs/architecture/world-01-entity-component-model.md`, `docs/contracts/world-01-entity-api.md`, `docs/architecture/core-03-concurrency-jobs.md`, `docs/architecture/core-04-time-simulation.md`, `docs/architecture/game-01-input-control-mapping.md`, `docs/architecture/data-04-serialization-scene-format.md`. Official external project/standard/license links recorded in technology matrix.

## REQUIREMENTS
GOV-001..005, program CAP/NFR as relevant, NLE-D013 1.0 DoD before claim, NLE-D014 2D/2.5D/3D/Web, NLE-D015 AI/MCP only authorized public APIs, NLE-D016 80 catalog modules, NLE-D017 Windows/Linux/macOS + Web, NLE-D018 governed autonomy, NLE-D019 prewritten coding Work Orders, NLE-D020 queue blocked. Catalog acceptance **"Modificar regras sem recompilar Core e com limites de segurança."** remains unproven until actual executable runtime integration and safety/performance tests.

## ARCHITECTURE RULES
- WORLD-01 is sole entity identity/component/query/lifecycle/structural commit owner, with WorldInstanceEpoch/EntityGuid/generational EntityHandle and typed ComponentSchema/EntityCommandBuffer/commit receipt. No raw native pointer, ECS memory or privileged component write exposed.
- CORE-03 is sole job/worker/fence owner; CORE-04 sole TickId and rational time. GAME-01 owns input action frames. GAME/NET is gameplay/network authority. Script evaluates immutable snapshots and stages bounded typed intents; only WORLD/GAME/NET commit authoritative changes.
- DATA-02/03/04/05 owns ScriptAsset ID/rights, secure source import, authored CAS/schema migration, verified cooked artifacts. No host path, arbitrary require/download, native plugin or unsigned untrusted bytecode.
- ScriptHost/Module/Instance/CapabilityGrant/ScriptApiSchema/GameplayProgramIR/CommandBuffer/HotReloadPlan/Fault receipts are Stormline-owned and vendor-neutral.
- Luau MIT leading native textual hypothesis, Lua 5.4 MIT comparator; sol2/LuaBridge3 MIT optional narrow C++ binding experiments; Wasmtime Apache-2.0, WAMR Apache-2.0 LLVM exception, Wasm3 MIT optional WASM lane; imgui-node-editor MIT optional Editor UI only. NO dependency adopted. Bytecode must be generated by pinned trusted compiler and verified, not accepted as arbitrary user bytecode.
- Deny-by-default host imports, no OS/network/process/clock/random/native FFI/debug eval; capability grants scoped to principal/world/module revision/role/entity/component/event. VM quotas for CPU/heap/instructions/calls/queries/outputs and blocking C++ host callbacks. No false "sandbox safe" claim.
- Typed visual graph and text share same public API/IR/capability boundary, no second privileged interpreter; graph cycles/fanout bounded. Hot reload compile/migrate off tick, quiesce at safe fence, old-known-good rollback or disabled state; no reversible claim for post-commit irreversible gameplay/world effects.
- Editor/CLI/MCP author/preview/debug semantics share controlled API; no arbitrary eval, privileged remote attach or game state bypass.
- Deterministic logical commit and tick replay are conditional; native/Web float/JIT/GC/time equivalence not presumed. Headless/server must not require GUI/GPU/audio.

## CONSTRAINTS
Research-only, no runtime or benchmark. ADR-0043 **PROPOSED / NOT APPROVED FOR CODE**; no new tech/license decision. 128 prospective tests FUTURE / NOT EXECUTED. Preserve all 80 `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, release_class UNDECIDED; #58 OPEN/BLOCKED. Zero mandatory paid CI, no external reviewers, CodeRabbit, force-push, bypass or destructive action. Recheck all relevant source hashes before audit; drift marks Context Lock STALE.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown docs, internal links/Source Pack valid, no engine source/CI/SDK/binary/toolchain/secret changes.
- [ ] ADR-0043 PROPOSED; realistic Luau, Lua54, WASM and bindings license/security analysis, no adoption/invented versions/compatibility/performance.
- [ ] Single owned public ScriptApi schema and capability host; WORLD-01/CORE-03/Tick/GAME-01/GAME/NET/DATA boundaries explicit, no raw pointers or duplicated authority.
- [ ] Text and visual graph typed IR/host policy, sandbox and quotas, host callback hazards, signed/provenance bound bytecode, debug privacy, deterministic commit, safe hot reload failure/rollback specified.
- [ ] Exactly 128 future tests all NOT EXECUTED; benchmark protocol with reproducible original fixtures, CPU/heap/p95/p99/GC/hot reload/security, native/Web/headless, budgets UNDECIDED.
- [ ] Research PR final exact-HEAD Docs Validation SUCCESS (Source Pack/local links, taxonomy DAG, Work Order registry, Zcode blocked selector), objective pt-BR audit APPROVED, normal squash and main readback.
- [ ] Separate checkpoint PR with same Work Order, final exact-HEAD Docs Validation/audit/squash/readback; only GAME-02 research_status changes to RESEARCH_DOCUMENTED_ADR_PROPOSED, total **40/80 researched (50%), 40 pending, 0 runtime**.
- [ ] ALL 80 coding WOs still BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=false, approved_adr=null; code #58 OPEN/BLOCKED; next GAME-03 #59 research only after checkpoint readback.

## TESTS
P00: actual GitHub Docs Validation (local links/Source Pack, taxonomy/dependency DAG, registry invariants and Zcode blocked selector). No VM, real sandbox, native/Web/headless build, VM fuzzer, ASan/UBSan/TSan, source graph/script compiler, game runtime, memory/CPU/debugger, hot reload, security exploit tests, profiler or numerical benchmark. All 128 prospective cases NOT RUN.

## DELIVERABLES
Issue #212, eight documentary files, research PR with exact-head CI/audit/normal squash/readback, separate checkpoint PR with independent CI/audit/squash/readback, changed research_status only for GAME-02 and safe research issue closure. Evidence Bundle must identify actual observed SHA/workflow run, not claim success before obtained.

## REVIEW FORMAT
pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED; include base/HEAD SHA, 8-file diff, canonical blobs, license/ABI/host-sandbox and trust model, module integration, unsafe host callback/UAF/privacy risks, real CI steps, 128 FUTURE tests not run, known HIGH/CRITICAL, checkpoint delta and stop gates. No independent human reviewer required in solo workflow.

## STOP CONDITION
STALE checkpoint/ledger/Scope/DoD/Architecture/approved ADR, unexpected code/binary/SDK/credential changes, unreviewed VM host privilege or license issue, any known HIGH/CRITICAL, failed final-HEAD CI, unmergeable PR/ruleset, unsafe registry edit, unstaged side effects or missing acceptance item => CORRECTION REQUIRED same WO/PR or BLOCKED. Do not advance GAME-03 while GAME-02 requires correction/validation.

## CONTEXT LOCK — base Git blob fingerprints, not file SHA-256
BASE main `8b12b71f090974e7c909265cb249f3fec297c89e`.
- Checkpoint `85c6e9e6b989b911f04c24417f9af106770cdff7`
- Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Backlog `96741a3b4e9bc821e5f9f477475e6f8090a687e2`
- Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Implementation registry `7de734b57e16989f41043bc15120592718d8f1ab`
- Future coding Work Order `6193dc896e99fd19a4f515b5eb51ce3eb4d949cd`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- WORLD-01 architecture `099a92e687a47ab0ab2b35b480c69e9f4365723e`
- WORLD-01 entity contract `7220a1cf26ae3a2648f78b536fc38221715fcc76`
- CORE-03 jobs architecture `d27523a71854d2f3952453b2ec7a3ef31f2d4aac`
- CORE-04 clock `b40b1bf97b934a883d6bb99e45bd40de6711912c`
- GAME-01 input architecture `5f86d817a26a7142496788963453caf247dbfa50`
- DATA-04 serialization `7e88d4fecaa83c9922f255087df9f97f6300b61f`

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-02.md). At first write, PR/CI/audit/merge CHECKS pending.
