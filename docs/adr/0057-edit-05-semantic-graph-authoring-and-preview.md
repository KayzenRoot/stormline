# ADR-0057 — Toolkit-Neutral Typed Shader Graph Authoring and Isolated Material Preview

**STATUS: PROPOSED / NOT ADOPTED / NOT OWNER-APPROVED / NO CODE AUTHORIZATION** | 2026-11-15 | research [#268](https://github.com/KayzenRoot/stormline/issues/268) | Work Order NLE-P00-WO-002-EDIT-05 | future code #72 OPEN/BLOCKED | BASE `7034fdce1d1d0220b349e8b333dc67cc6d19c515` | engine license NLE-D009 OPEN.

## Context and drivers
Stormline's catalog requires a visual shader/material graph editor with preview, variant management and a future proof of "Visualizar e exportar shader/material validado." Existing architecture separates GFX-02 shader compilation/reflection, GFX-05 material semantics, EDIT-01 shell, EDIT-02 project scope, DATA asset/persistence/cook and GFX GPU ownership. GFX-05 already says MaterialX is optional interchange and GFX-02 owns graph compilation while EDIT-05 owns visual UI. GFX-02 compiler targets are not proven uniform across Windows/Linux/macOS/Web; Slang Metal is experimental and WGSL output is work in progress. No editor/compiler/runtime exists.

## Proposed decision (not adopted)
1. EDIT-05 is a **toolkit-neutral visual authoring facade**, not a new graph compiler or material system. It uses EDIT-01's shared command registry and accessible shell.
2. GFX-02 is sole authority for canonical versioned shader graph semantics, node definitions, type checking/compile graph, reflection, compile cache, target variants and generated artifacts. Formal catalog edges for EDIT-05 remain **EDIT-02 + GFX-05 only**; GFX-02 is an integration owner, not an added DAG edge.
3. GFX-05 remains sole owner of MaterialDefinition extensions, PBR/stylized surface semantics, dynamic/static feature meaning, texture bindings and quality/fallback profiles. EDIT-05 edits through GFX-05/GFX-02 typed commands and does not fork MaterialDefinition or PBR math.
4. Editor stores graph-canvas layout/presentation separately from semantic graph content and compile digest. DATA-04 owns durable versioning/CAS/journal/migration. Layout changes cannot trigger compile or alter shader cache keys.
5. Graph editor exposes explicit toolbar buttons and keyboard/command palette with stable EDIT-01 CommandIds, accessible names/states/tooltips, disabled reasons, progress/cancel and owner-side permission checks. GUI, CLI and MCP invoke same semantic operations.
6. Graph baseline is a typed, bounded dataflow DAG with stable node/port/edge IDs, explicit conversions, stage/domain compatibility, versioned node registry and no recursive subgraphs or arbitrary executable code. Reusable subgraphs have stable input/output signatures and bounded depth.
7. Preview uses exact GFX-02 compile receipt/artifact and GFX-01/GFX-03/GFX-06/GFX-07 services. Preview is isolated/offscreen, generation tagged and non-mutating. Failure/device loss retains last-good preview; it never publishes broken runtime pipeline.
8. Dynamic parameters remain runtime data/uniform edits; static feature changes route through GFX-02 variant planning with deterministic, bounded, target-specific sets. No Cartesian variant explosion or silent target feature stripping.
9. MaterialX/glTF are optional interoperability formats. MaterialX 1.39.x graph format is an exchange candidate; import/export is preview-first with explicit unsupported/loss report, rights/provenance and no execution of imported node code. Do not copy other engines' editor code, shaders or assets.
10. Export is a staged, validated DATA-05 package operation with DATA-01 destination grant and owner receipts; no direct filesystem write, arbitrary URL, raw GPU pointer or unvalidated binary export.

## Alternatives and trade-offs
| Alternative | Strength | Why not default |
|---|---|---|
| MaterialX canonical runtime graph/compiler | rich cross-application node semantics and shader generation | runtime/compiler coupling, target parity and native/Web output not proved; keep optional adapter |
| New Stormline compiler in EDIT-05 | total control of visual nodes | duplicates GFX-02 and multiplies security/ABI burden; reject |
| Store only generated HLSL/GLSL/WGSL source | easy inspection/export | loses graph editability, source mapping and semantic target portability; not canonical |
| Treat every input as dynamic uniform | fewer variants | static structural features and stage/feature gates sometimes require compile-time specialization; semantic owner decides |
| Permit arbitrary custom code nodes/plugins | maximum extensibility | compiler/driver attack surface and project privilege escalation; future separate signed/isolated extension decision only |
| Adopt ImNodes immediately | small MIT C++ extension with node/pin/link/minimap | depends on Dear ImGui; EDIT-01 has not selected toolkit, upstream Linux note means viability unproven |
| Adopt React Flow everywhere | MIT graph UI with pan/zoom/selection/minimap and web ergonomics | React-based Web UI is not native desktop shell; platform bridge/parity unproven |
| Embed vendor engine material editor | mature workflows | proprietary licensing/IP/ABI and divergent runtime/compiler semantics; reject |
| Build custom widget toolkit now | total design control | duplicates EDIT-01 shell/accessibility/IME/platform burden; reject |

## Risks and proof obligations
Risks: graph type mismatch, hidden implicit conversion, node registry drift, unknown imported nodes, recursive subgraph, stage mismatch, shader variant explosion, compile stalls, compiler sandbox escape, malicious shader/texture import, cache poisoning, stale preview/device generation, layout/source digest coupling, color/normal semantics mismatch, inaccessible graph navigation, source/license leakage and cross-project MCP authorization.

Before owner approval: formal GFX-02 graph schema/registry/compile/diagnostic contract, GFX-05 MaterialDefinition and static/dynamic semantics, EDIT-01 accessible command/button backend, EDIT-02 project scope, DATA-03/04/05 source/import/persistence/package, GFX-01/03 actual device/offscreen/fence, GFX-06/07 preview environment/color, exact per-file dependency licenses/SBOM, Windows/Linux X11+Wayland/macOS/Web tests, compiler isolation/fuzz proof, real graph+material preview/export golden fixtures, measured p50/p95/p99 and approved budgets. Release class remains UNDECIDED and NLE-D009 OPEN.

**No technology is selected. ADR-0057 remains PROPOSED. Research approval cannot unlock #72 or any of the 80 implementation packets.**

See [architecture](../architecture/edit-05-visual-shader-material-graph.md), [technology matrix](../research/edit-05-visual-shader-technology-license-matrix.md), [contract](../contracts/edit-05-visual-shader-api.md).
