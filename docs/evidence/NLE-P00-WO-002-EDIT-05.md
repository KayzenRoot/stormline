# Evidence Bundle — NLE-P00-WO-002-EDIT-05 (Visual Shader & Material Graph P00 Research)

**2026-11-15 | [research #268](https://github.com/KayzenRoot/stormline/issues/268) | future code [#72](https://github.com/KayzenRoot/stormline/issues/72) OPEN/BLOCKED | BASE main `7034fdce1d1d0220b349e8b333dc67cc6d19c515`.** Baseline 53/80 research documented (66.25%), 27 pending, zero engine, all 80/80 code WOs BLOCKED.

## 1. Verified Source Check
- Current main recent commit and compare readback: `7034fdce1d1d0220b349e8b333dc67cc6d19c515`, compare from previous final EDIT-04 closeout `7034fdce1d1d0220b349e8b333dc67cc6d19c515...main` = **identical** (ahead 0/behind 0).
- No open pull requests at Source Check.
- Catalog order 54, formal dependencies **EDIT-02 + GFX-05** only; both documentary research/ADR PROPOSED, not implemented. EDIT-02 #69 and GFX-05 #33 are OPEN/BLOCKED. GFX-02 #30 is integration owner/OPEN/BLOCKED. EDIT-05 future code issue #72 already exists and is OPEN/BLOCKED.
- Registry readback: 80 modules, 53 research documented, 27 pending; all 80 coding packets `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, `release_class=UNDECIDED`. EDIT-05 `research_status=RESEARCH_PENDING`, `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, formal dependencies EDIT-02/GFX-05, `catalog_order=54`.
- Canonical Source Pack and exact Git blob object SHAs are in research WO Context Lock. Those are **Git blob SHA-1 identifiers, not byte SHA-256**. No executor SHA-256 fingerprints were produced.

## 2. Technical findings from repository and official sources
- EDIT-01 ADR-0053 is toolkit-neutral/PROPOSED and owns shared command registry, button labels/shortcuts, focus/accessibility and panel host. Graph canvas must not create a private button/command system.
- GFX-02 owns ShaderDefinition/MaterialDefinition compiler-facing schemas, graph compilation/reflection/variants/cache/compiled artifacts; GFX-05 owns PBR/stylized material, parameter and texture semantics. EDIT-05 owns visual authoring UX/presentation only.
- MaterialX v1.39 specification and v1.39.5 release provide typed node definitions, graph/subgraph interchange and an example Graph Editor; upstream is Apache-2.0. MaterialX is optional interchange, not mandatory runtime/compiler.
- Slang official targets document Metal as experimental and WGSL as work in progress; no single compiler can be promised across all Stormline targets from docs alone.
- ImNodes is MIT and supplies immediate-mode node/pin/link and minimap primitives but depends on Dear ImGui; upstream says Linux has not been tested for its example build. xyflow/React Flow core is MIT and offers browser graph interactions but does not supply native EDIT-01 desktop shell.
- Godot VisualShaders and MaterialX Graph Editor are workflow references only. Unreal static switches illustrate compile-time permutation growth; no proprietary source/assets copied.
- Khronos glTF material schemas and ratified extension registry define interoperable material fields; KHR_materials_variants maps asset material assignments and is not identical to shader compiler variants.
- Risks: untrusted MaterialX/XML/clipboard/import, graph cycles/depth/variant bombs, compiler escape/cache poisoning, stale GPU generation, inaccessible graph navigation, path/source disclosure and unauthorized MCP writes. Proposed defenses are owner boundaries, bounded typed DAG, no arbitrary executable node, isolated GFX-02 compiler, capability/CAS and last-good preview.

## 3. Exactly eight research documents (expected scope)
1. architecture `docs/architecture/edit-05-visual-shader-material-graph.md`
2. ADR-0057 PROPOSED `docs/adr/0057-edit-05-semantic-graph-authoring-and-preview.md`
3. technology/license/threat matrix `docs/research/edit-05-visual-shader-technology-license-matrix.md`
4. typed contract `docs/contracts/edit-05-visual-shader-api.md`
5. 128 future tests `docs/testing/edit-05-acceptance-matrix.md`
6. benchmark/fault protocol `docs/research/edit-05-visual-shader-benchmark-protocol.md`
7. Work Order `docs/work-orders/NLE-P00-WO-002-EDIT-05.md`
8. this Evidence Bundle

All external technology claims are linked to official upstream/specification sources in the matrix. No package/toolkit/compiler installed or selected.

## 4. Tests and evidence status
- E05-T001..E05-T128: **128 unique FUTURE / NOT EXECUTED**, 0 pass, 0 fail.
- Native C++/UI build: NOT RUN.
- Graph schema/serialization or shader compilation: NOT RUN.
- Windows/Linux/macOS/WebGPU/WebGL2 preview and export: NOT RUN.
- GPU/device-loss/VRAM/variant/compile benchmark: NOT RUN / NOT MEASURED.
- UIA/macOS AX/AT-SPI, keyboard-only, IME and screen reader: NOT RUN.
- No code, SDK, source asset, binary, dependency, generated shader or SBOM adopted.
- Documentation CI, exact PR diff, objective pt-BR audit, merge and readback remain PENDING until actual observed results are appended.

## 5. Proposed checkpoint delta, not yet promoted
Only after research PR exact-final-HEAD Docs Validation, audit APPROVED, ordinary squash merge and factual main readback: separate checkpoint PR modifies exactly five files: checkpoint, backlog, registry (SOLE EDIT-05 `research_status=RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`), this WO and Evidence. Target 54/80 research documented (67.5%), 26 pending, zero engine; all 80/80 code WOs remain blocked with executor_ready=false, approved_adr=null and release_class=UNDECIDED. ADR-0057 remains PROPOSED; #72 remains OPEN/BLOCKED. Research #268 closes only after checkpoint main readback. Historical four-doc closeout, if used, requires its own CI/audit/merge/readback. No code authorization.

## 6. Risks and stop conditions
Stop on stale canonical sources, unexpected file diff, DAG inflation, owner boundary duplication, license ambiguity represented as approval, unsupported platform claim, unsafe node/code import, failed docs CI, count mismatch or any attempt to unlock code. Research-document risk LOW; future runtime/compile/import risk ELEVATED. No runtime security claim is made.
