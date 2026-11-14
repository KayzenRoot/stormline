# Research Work Order — NLE-P00-WO-002-GFX-03

**Research issue:** #129 | **Future implementation issue:** #31 BLOCKED | **Date:** 2026-11-14  
**State:** APPROVED / MERGED FOR DOCUMENTAL RESEARCH ONLY (PR #130) | **ADR-0016:** PROPOSED / NO ENGINE CODE  
**Context Lock BASE main:** `e76d561d98dd4192d8bae1fb66cab09e194fbc70` (GFX-02 research/checkpoint PRs #127/#128 audited and merged).
**Risk:** LOW docs; future ELEVATED GPU sync/alias/device loss/VRAM.

## OBJECTIVE
Architect a safe, portable, high-performance Stormline Render Graph & GPU Resource Manager across 2D/2.5D/3D, native Vulkan/D3D12/Metal, browser WebGPU and headless validation, including explicit pass DAG hazards, synchronization, transient alias memory proof, VRAM budgets, frame epochs, recovery, contracts and future tests before Zcode implementation.

## CONTEXT
P00 docs only; owner-approved Windows/Linux/macOS Editor and exported runtimes, Web, AI-native Editor/CLI/MCP, solo objective audit, public GitHub free checks and no public MVP before 1.0 DoD. GFX-01/GFX-02 and CORE-03 research documentation exists but runtime implementation does **not**. All 80 future executable WOs BLOCKED, release class UNDECIDED.

## SCOPE
- Owned versioned `RenderGraphDefinition/PassNode/ResourceUse/GraphPlan/SyncPlan/AllocationPlan` typed schema; dependency edges RAW/WAR/WAW, explicit external/temporal side effects, subresource tracking, cycle and read-before-write validation.
- GPU queue/cross-frame fences, per-device generation and ownership, resource lifetimes covering real GPU completions, optional safe alias with conservative no-alias/serial fallback.
- Candidate Vulkan Synchronization2, D3D12 legacy/enhanced optional barriers, Apple Metal MTLHeap/hazard modes/fences, browser WebGPU usage-scope validation and explicit WebGL2 degraded behavior.
- Compare Vulkan Memory Allocator MIT, D3D12 Memory Allocator MIT, native Metal heap and WebGPU managed memory, exact SBOM/tag gates.
- VRAM budget snapshots known/estimated/unknown, UMA/dedicated limits, persistent vs transient vs DATA-05 streams, pressure fallback, GPU+CPU timing and safe recovery.
- Cross-frame/reload/resize/dynamic-resolution plan invalidation, engine-internal commit vs read-only Editor/CLI/MCP inspect/preview.
- Architecture, matrix, ADR-0016 PROPOSED, semantic API, at least 30 (34 specified) future RGP tests, Evidence Bundle, Source Pack links, future blocked packet, SAFG optional prove-or-drop.

## OUT OF SCOPE
No C++ implementation, no Vulkan/D3D12/Metal GPU SDK integration, heap/allocator installation, shader, actual render graph, driver profiling, scene/lighting/VFX algorithms, render graph editor, Web host, public release, paid CI/CodeRabbit, mandatory external human reviewer, bypass, force push, secrets or 80-WO activation.

## FILES / SOURCES TO READ
Canonical: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md`; `docs/00-source-hierarchy.md`, `AGENTS.md`, module catalog/registry, CORE-02/03/06 research, GFX-01/02 research/contracts and DATA-05, [future packet](../queue/work-orders/GFX-03.md) and code issue #31, official Khronos/Microsoft/Apple/W3C/GPUOpen specifications.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/005/008/009/010/011/012/013/014/016, NFR-001..005, owner decisions NLE-D013..020, GFX-03 catalog candidate acceptance: validate sync, measure CPU/GPU/VRAM under standard scenes (future only). 1.0 release class, numeric budgets and coding files remain UNDECIDED.

## ARCHITECTURE RULES
- CORE-03 CPU jobs; CORE-02 CPU mem; GFX-01 native RHI/device/fence and GPU memory primitive; GFX-02 shader reflection; GFX-03 graph ordering/VRAM heap plan. GFX renderers and TWO own actual visual passes. DATA-05 owns cooked source content.
- Never alias based solely on CPU pass DAG; actual GPU queue completion and in-flight frame epochs plus backend heap compatibility must be proven. Fallback no-alias + serial queue.
- Stage/access/subresource validation, queue ownership, explicit imported resource states, temporal history, device-loss generational handles; no uninitialized read or silent required quality loss.
- Browser WebGPU cannot accept arbitrary Vulkan/D3D barriers and may hide VRAM budget; unknown fields treated conservatively.
- Editor/CLI/MCP semantic read-only preview, no arbitrary GPU pointers/native queue submissions, shell/file/network or unapproved GPU allocations.
- Exact library tag and license/SBOM, hardware+driver proof and quantitative benchmarks before approved backend/memory architecture. SAFG only prove-or-drop.

## CONSTRAINTS
Documentation-only P00; no engine artifacts, paid service/CodeRabbit, credential, force-push, ruleset bypass or mandatory outside reviewer. Any HIGH/CRITICAL known issue, failed CI, stale Source Pack or unapproved GPU memory assumption blocks progress.

## ACCEPTANCE CRITERIA
- [ ] Architecture defines safe pass DAG, hazards and full multi-queue/in-flight lifetime + alias proof; typed source boundaries and fallback.
- [ ] Matrix covers Vulkan Synchronization2, D3D12 legacy/enhanced optional, native Metal MTLHeap/fences, WebGPU usage scope, VMA/D3D12MA license MIT and honest hardware/VRAM limitations.
- [ ] ADR-0016 remains PROPOSED; semantic API typed, error taxonomy, memory budgets, graph plan, diagnostics, Editor/CLI/MCP scope and anti-use-after-free.
- [ ] 34 RGP future tests cover 2D/2.5D/3D, Win/Linux/macOS Apple Silicon/Web, real hardware and synchronization, async/alias, device loss, low VRAM, regression/CI/SBOM/fuzz.
- [ ] Current scope docs only, no code/SDK, issue #31 and 80 other packets BLOCKED/`executor_ready=false`.
- [ ] Exact final research HEAD free docs-validation success, changed files/docs links valid, pt-BR audit no HIGH/CRITICAL, normal squash merge/readback.
- [ ] Separate same-WO checkpoint delta audited/merged before GFX-04.

## TESTS
Current free docs CI checks Source Pack/local links, 80-module dependency DAG, blocked registry and blocked selector. Future RGP-001..034 **NOT RUN**. Never claim native GPUs, Mac Metal/Web browser, VRAM or p95 tests have been run.

## DELIVERABLES
`docs/architecture/gfx-03-render-graph-gpu-memory.md`, `docs/research/gfx-03-rendergraph-technology-matrix.md`, `docs/adr/0016-gfx-03-render-graph-policy.md`, `docs/contracts/gfx-03-render-graph-api.md`, `docs/testing/gfx-03-acceptance-matrix.md`, research WO, Evidence Bundle, Architecture/Backlog/blocked packet links, scoped research PR, objective audit and proposed Checkpoint Delta.

## REVIEW FORMAT
Pt-BR, `APPROVED / CORRECTION REQUIRED / BLOCKED`, exact base/head SHA, diff+files, CI job/scope tests, licensing/security/hardware/VRAM risks, no fake software completion, proposed Checkpoint Delta. Only docs approval available in this increment.

## STOP CONDITION
Stop upon STALE checkpoint/ADR/Scope/DoD/Architecture, evidence gap, unbounded synchronization/aliasing or MCP native execution, mandatory external reviewer/paid service, failed CI, known HIGH/CRITICAL, secret or code scope intrusion. Correct only in same WO/PR; don't start next module if correction required.

## CONTEXT LOCK
BASE `e76d561d98dd4192d8bae1fb66cab09e194fbc70`. Critical source Git blob fingerprints captured in Evidence Bundle and **not** passed off as SHA-256 of file bytes; future code activation requires actual SHA-256, verified dependencies/ADR/DoD and exact C++ paths/commands.

## CHECKPOINT
Only after approved research PR merged+read back, update Checkpoint, Backlog, this WO, Evidence Bundle and registry `GFX-03.research_status` via **separate audited docs-only PR of same WO**, preserving ADR-0016 PROPOSED and all 80 implementation WOs BLOCKED.
