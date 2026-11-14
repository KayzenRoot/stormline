# Research Work Order — NLE-P00-WO-002-GFX-02

**Research issue:** #126 | **Future implementation:** #30 BLOCKED | **Date:** 2026-11-14  
**State:** APPROVED / MERGED FOR DOCUMENTAL RESEARCH ONLY (PR #127) | **ADR-0015:** PROPOSED / NO ENGINE CODE  
**BASE main / Context Lock:** `d968809bc4869a3a39f1fb1f82f75d5a212dfbda` (GFX-01 research/checkpoint PRs #124/#125 audited and merged).
**Risk:** LOW docs, future ELEVATED compiler/driver attack surface, invalid cache/parameter graph and hot reload data loss.

## OBJECTIVE
Specify a secure, incremental, target-aware Shader & Material Compilation architecture for original Stormline 2D/2.5D/3D/Web and Windows/Linux/macOS; produce technology/license matrix, ADR, typed API, diagnostics, variant/caching, hot reload/recovery and future test obligations before any Zcode code. Make executor responsible for approved implementation only, not toolchain/architecture choices.

## CONTEXT
GFX-01 RHI research documented but not implemented; DATA-03 importer research documented not implemented; code dependency issue #29 and #26 still BLOCKED. Owner-approved vision includes AI-native Editor/CLI/MCP, no public MVP, free public GitHub CI, solo audited PRs, no CodeRabbit or mandatory external reviewers. All 80 code WOs remain blocked and release classes undecided.

## SCOPE
- Compare Slang, HLSL/DXC, GLSL/glslang, shaderc/glslc, SPIRV-Tools, SPIRV-Cross, Tint/Naga, native MSL/Metal and browser WGSL/WebGPU plus WebGL2 degraded.
- Validate upstream statuses: Slang Metal experimental, WGSL work-in-progress; DXC HLSL->SPIR-V recommended by Vulkan guide; DXC UIUC licensing vs Slang Apache-2.0 with LLVM exception.
- Bound owned ShaderDefinition/MaterialDefinition/ShaderRecipe/VariantKey/Reflection/CacheReceipt/HotReload contract, with DATA-02 AssetId source identity and DATA-05 derived binary.
- Explicit source include graph, binding layouts, stage IO, target capabilities, material parameter overrides, deterministic plan vs nondeterministic compiled-byte limitations.
- Incremental cache, variant budget explosion guard, last-good generational hot reload and device-loss safety with GFX-01, compiler worker isolation, scoped Editor/CLI/MCP diagnostics and authorization.
- ADR-0015 PROPOSED, matrix, architecture, typed API, 30 future tests, Work Order, Evidence Bundle, canonical Architecture/Backlog and future #30 blocked packet links; SSVF prove-or-drop experiment.

## OUT OF SCOPE
No C++ engine, shader source compilation, compiler vendoring, GPU drivers, generated binaries, shader graph editor implementation, material/PBR renderer (GFX-05), render graph (GFX-03), paid services, CodeRabbit, mandatory external human reviewers, bypass/force-push, public app/release or signed distribution. No 80-WO activation.

## FILES / SOURCES TO READ
Read `docs/11-checkpoint.md`, `docs/10-decisions-ledger.md` and approved ADRs, `docs/03-scope.md`, `docs/09-definition-of-done.md`, `docs/04-architecture.md`, `docs/02-requirements.md`, `docs/00-source-hierarchy.md`, `AGENTS.md`; GFX-01 architecture/contracts, DATA-01/02/03/04/05 docs, catalog/registry and blocked [#30](https://github.com/KayzenRoot/stormline/issues/30), official Slang, DXC, Khronos, W3C, Apple and Tint/Naga sources.

## REQUIREMENTS
GOV-001..005, CAP-001/002/004/008/009/010/011/012/013/014/016, NFR-001..005, decisions NLE-D013..020. Specific future 1.0 release-class and performance/feature targets still UNDECIDED. Catalog candidate scenario: deterministic builds, file/line diagnostics, stable variants, only future executable proof.

## ARCHITECTURE RULES
- Shader identity/provenance DATA-02, DATA-03 import, editable scene DATA-04, cooked artifacts DATA-05. GFX-01 RHI capability and device generation is authoritative.
- GFX-02 compiles/reflection/layout; GFX-03 schedules GPU passes; GFX-05 implements PBR/material properties; EDIT-05 visual graph UI. No reimplementing their scope.
- Native Metal and browser WGSL need first-class fallback; do not falsely assume one Slang compiler gives production full-portability.
- Shader source and binary untrusted; deny path traversal, arbitrary host compiler flags/process/URL or direct GPU native command via MCP. Cap variant count, size, memory, CPU, worker privileges; last-good on failure.
- Exact tags/licensing with SBOM source rights required before any compiled dependency, no fabricated benchmark or test.

## CONSTRAINTS
P00 docs only, no C++/shader/artifact/driver, no secrets, paid services, CodeRabbit, mandatory outside reviewer or bypass. Stop on STALE Context Lock, changed approved decision or HIGH/CRITICAL known issue.

## ACCEPTANCE CRITERIA
- [ ] Detailed compiler diagram, target matrix and lifecycle with source identity, constraints, GPU readiness, shader/material responsibility boundaries.
- [ ] License matrix accurate for Slang Apache-2.0 WITH LLVM-exception and its transitive libs, DXC University of Illinois and ThirdPartyNotices, SPIRV-Cross per-file SPDX, WebGPU consumes WGSL.
- [ ] ADR-0015 remains PROPOSED; typed semantic API and scoped Editor/CLI/MCP, no arbitrary source driver execution.
- [ ] At least 20 tests (30 specified) including 2D/2.5D/3D, Vulkan/D3D12/Metal/WebGPU/WebGL2, cache/version, variant caps, security/MCP, hot reload/device loss.
- [ ] All 80 implementation WOs BLOCKED and executor_ready=false, #30 unactivated, no new code.
- [ ] Exact HEAD free GitHub docs-validation success, scoped diff, pt-BR objective audit with no HIGH/CRITICAL, normal squash merge/readback.
- [ ] Checkpoint reconciliation after research approval in separate **same-WO** docs-only PR, no GFX-03 until approved.

## TESTS
Actual GitHub docs CI: Source Pack/local links, 80 catalog DAG, registry/selector. SHD-001..030 are **future NOT RUN**; no C++ compiler, shader translation, GPU Mac/Windows/Linux or Web browser tests.

## DELIVERABLES
`docs/architecture/gfx-02-shader-material-compilation.md`; `docs/research/gfx-02-shader-technology-matrix.md`; `docs/adr/0015-gfx-02-shader-compilation-policy.md`; `docs/contracts/gfx-02-shader-api.md`; `docs/testing/gfx-02-acceptance-matrix.md`; this WO; Evidence Bundle; architecture/backlog/blocked packet links; CI and objective audit and checkpoint delta.

## REVIEW FORMAT
Review pt-BR, base/head SHA, scoped diff, exact CI run, risk/requirements/licenses/feature compatibility, future hardware tests, evidence, no HIGH/CRITICAL; verdict `APPROVED / CORRECTION REQUIRED / BLOCKED`.

## STOP CONDITION
If approved checkpoint/Scope/DoD/Architecture/ADR changed -> STALE/rebase; if compiler source rights unknown, unsafe MCP/host exec, no bounded variant or hot reload recovery, test failure, known HIGH/CRITICAL, paid/bypass or code diff: BLOCKED or CORRECTION in **same WO/PR**. No next module until reconciliation.

## CONTEXT LOCK
BASE `d968809bc4869a3a39f1fb1f82f75d5a212dfbda`; Git blob IDs for critical sources in Evidence Bundle explicitly **not SHA-256 of file bytes**. At any future implementation activation collect actual SHA-256 and exact approved source/code versions.

## CHECKPOINT
After APPROVED research PR, merge/readback then reconcile checkpoint/backlog/research WO/Evidence and registry `GFX-02.research_status` via distinct audited PR of same WO. Keep ADR-0015 PROPOSED, #30 and all 80 executable WOs BLOCKED.
