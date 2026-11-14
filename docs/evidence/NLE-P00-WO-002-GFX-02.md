# Evidence Bundle — NLE-P00-WO-002-GFX-02

**Date:** 2026-11-14 | **Research issue:** #126 | **Future code issue:** #30 BLOCKED
**Evidence state:** DOCUMENTAL RESEARCH APPROVED / MERGED; CODE IMPLEMENTATION BLOCKED / NO ENGINE CODE. No C++, compiled shaders, GPU binaries, compiler dependencies, material editor, code tests or deployment.
**BASE main:** `d968809bc4869a3a39f1fb1f82f75d5a212dfbda` | **Research branch:** `docs/NLE-P00-WO-002-GFX-02-shader-research`. Research risk LOW, future shader compiler/driver & authoring integrity ELEVATED.

## Canonical Context Lock (baseline from live GitHub)
Fingerprints below are **Git blob object SHA-1 IDs, NOT SHA-256 of file bytes**. A future C++ executor must acquire fresh actual SHA-256 fingerprints and revalidate canonical sources, baseline main, approved ADR and code inventory:
- Checkpoint `docs/11-checkpoint.md`: `0e027bd86355688de3f53dabf051320ebada30bd`
- Decisions Ledger `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- Definition of Done `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `docs/04-architecture.md`: `ea2c19cae5d30ad9a321b0f7e06d175ba30da99e`
- Requirements `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Future GFX-02 code packet `docs/queue/work-orders/GFX-02.md`: `04ebff5b5f9d0ad624d41d2958c0c0808621cd02`
- Registry `docs/queue/implementation-registry.json`: `72a517cf485c48a241673921d30efb51c612f859`
- Predecessor GFX-01 RHI architecture `docs/architecture/gfx-01-graphics-rhi.md`: `4512de487da7df97969b56f8e5f508a56125ab32`
- Agent contract `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`

## Research artifacts / boundaries
- Owned typed ShaderRecipe, MaterialDefinition/Instance compiler-facing (PBR GFX-05), MaterialIR, reflection/binding layouts, per-target shader artifacts and precise source/include snapshots.
- Upstream tech/law: Slang Apache-2.0 WITH LLVM-exception but experimental Metal and work-in-progress WGSL; DXC UIUC and ThirdPartyNotices, glslang/spirv-tools, SPIRV-Cross file-level SPDX, Tint/Naga, native MSL and browser WGSL. No compiler pinned, vendored or selected.
- Variant ceiling, differentiated cooked-artifact cache versus driver-specific pipeline cache, transactional generational hot reload preserving last-good, device loss and bounded untrusted shader input. AI-native commands are scoped semantic operations, not shell/native GPU calls.
- 30 acceptance tests future SHD-001..030, including Apple Silicon native Metal, WebGPU WGSL, WebGL2 degradation, source diagnostic locations, rights/SBOM, compiler sandbox, cache poison and actual performance.
- Original SSVF optimization only prove-or-drop, never assumed beneficial.

## Actual tests and evidence (fill only observed data)
- Preliminary research HEAD `94c141f3fb4fc89246a5113006e3365ea72ad26d`: [Docs Validation #43611408051](https://github.com/KayzenRoot/stormline/actions/runs/43611408051) **SUCCESS**, Source Pack/links, 80 modules/DAG, registry and blocked-selector checks. Final audited research HEAD `dae67ef8f3307d2f10a525442e6dc01d7fc771b3` passed [Docs Validation #43611454959](https://github.com/KayzenRoot/stormline/actions/runs/43611454959) **SUCCESS**.
- [Research PR #127](https://github.com/KayzenRoot/stormline/pull/127) preliminary scope audit: 10 docs-only files, +414 / 0 removed; no C++/shader binaries/compiler installs, CI config or apparent embedded secret in added lines. Registry: 80/80 WOs BLOCKED and 0 executor_ready, code issue #30 stays open PLANNING/BLOCKED. Final research HEAD `dae67ef8f3307d2f10a525442e6dc01d7fc771b3` passed CI #43611454959 and objective pt-BR **APPROVED DOCUMENTATION ONLY** ([PR #127 audit comment](https://github.com/KayzenRoot/stormline/pull/127#issuecomment-6879939272)).
- All SHD-001..030, shader compilation, C++ builds, GPU driver tests, macOS/Web browser, shader fuzzing, benchmark, CI sanitizer, deployment: **NOT RUN**.
- Normal squash merge [PR #127](https://github.com/KayzenRoot/stormline/pull/127) SHA `076362cd71020359cd8fe8475a3f623e1e3a4fe8` VERIFIED in main and GFX-02 architecture readback. Separate same-WO checkpoint reconciliation is pending independent CI/audit/merge.

## Risks and gates
Untrusted shader compiler/driver inputs and legacy/experimental targets have future ELEVATED implications. Exact shader source and dependency rights, compiler/platform toolchain licenses, source-map privacy, deterministic variant key and safe rollback need executable proof. Browser WGSL is not SPIR-V. No false 4-target parity or cloud compiler functionality claim. 80 future implementation WOs remain BLOCKED and `executor_ready=false`.

## Checkpoint Reconciliation (pending this separate PR's audit)
Only GFX-02.research_status is promoted to RESEARCH_DOCUMENTED_ADR_PROPOSED in registry as a documentation progress marker. ADR-0015 remains PROPOSED and unselected; implementation #30 and other 79 WOs remain BLOCKED / executor_ready=false. CI, pt-BR audit, normal squash merge/readback and research issue #126 closure must occur before GFX-03.
