# EDIT-05 — Visual Shader & Material Graph Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #268](https://github.com/KayzenRoot/stormline/issues/268) | Work Order NLE-P00-WO-002-EDIT-05 | future code [#72](https://github.com/KayzenRoot/stormline/issues/72).** Verified BASE main `7034fdce1d1d0220b349e8b333dc67cc6d19c515`; catalog order 54/80, research registry 53/80 documented, 27 pending. Formal dependencies **EDIT-02 + GFX-05** are documentary/ADR PROPOSED only. All 80 coding WOs remain BLOCKED. No shader editor, graph compiler, renderer, GPU preview, material export or runtime exists.

## 1. Mission, catalog acceptance and ownership
Catalog capability: **"Editor de materiais/nodes, shader preview, variant management."** Catalog acceptance: **"Visualizar e exportar shader/material validado."** This is a future functional test, not evidence satisfied by documents.

EDIT-05 provides the manual, professional authoring surface and command workflow for visual shader/material graphs. It owns graph canvas interaction, graph-editor presentation state, node selection/inspection, typed authoring intents, graph diagnostics presentation, preview controls and export UX. It does **not** own the semantic compiler, material physics, source asset identity, project filesystem, GPU resources, render graph or native editor toolkit.

| Owner | Sole source of truth | EDIT-05 boundary |
|---|---|---|
| **EDIT-02 (formal dependency)** | ProjectId, project mode, capability profiles, DATA-01 root grants and project-scoped lifecycle | validate active project and target profile; never invent project identity, VFS or raw paths |
| **GFX-05 (formal dependency)** | PBR/stylized material semantics, alpha/decal/texture roles, quality profiles and MaterialDefinition extensions | expose material semantics through typed APIs; no second PBR model or texture residency system |
| GFX-02 (integration owner; NOT a new formal DAG edge) | ShaderDefinition/MaterialDefinition compiler-facing schemas, canonical graph semantics, node definitions, compilation, reflection, variants, cache and compiled artifacts | author and preview graphs through GFX-02; no compiler, optimizer, source generator, shader cache or driver calls |
| EDIT-01 / CORE-01 | toolkit-neutral shell, panel/window host, command registry, keyboard/focus/IME/accessibility and OS event routing | provide graph panel descriptors and command metadata; no second toolkit or private command registry |
| DATA-02 / DATA-03 | permanent AssetIds/revisions/provenance/dependency graph; untrusted import and reimport receipts | use stable refs and safe import receipts; no shadow asset database or privileged parser |
| DATA-04 | versioned authored source, canonical serialization, migration, CAS/journal/undo/recovery | stage graph and presentation changes through source revision/transaction authority; no private graph writer |
| DATA-05 | immutable target cooked packages/artifacts, manifests, provenance, hashes and rollback | request validated package/export artifacts; no independent shader cooker/cache |
| GFX-01 / GFX-03 | RHI capabilities/device generations/handles; render graph, upload, barriers, GPU memory and fences | consume capability snapshots and preview receipts only; never own GPU pointers or VRAM |
| GFX-06 / GFX-07 | lighting/environment and camera/color/tone mapping | request compatible preview lighting/color; no invented light or HDR output |
| EDIT-07 / CORE-06 / QA-04 | play/debug/profile lifecycle, diagnostics/traces, secure SDLC/fuzzing | link diagnostics to source IDs and preview generation; do not run gameplay or duplicate profilers |
| AI/MCP / CLI | public permissioned semantic operations | same command IDs, actor capability, expected revision, preview and receipt as manual UI |

**Formal dependency graph stays exactly EDIT-02 + GFX-05.** GFX-02, EDIT-01, DATA, GFX-01/03/06/07, EDIT-07, QA-04 and AI/MCP are integration owners, not added formal edges. Their runtime implementations remain unbuilt. EDIT-02 #69, GFX-05 #33, GFX-02 #30 and EDIT-05 code #72 are OPEN/BLOCKED.

## 2. Toolkit-neutral graph workspace and button conventions
The editor is a panel hosted by EDIT-01. Candidate workspace: (a) node library/search/favorites; (b) central graph canvas; (c) property/parameter inspector; (d) isolated material preview; (e) validation/compile diagnostics and variant target panel. Panels dock/hide/restore only through EDIT-01. Do not select Qt, Dear ImGui, ImNodes, React Flow or another toolkit here; EDIT-01 ADR-0053 remains PROPOSED.

**Every visible toolbar button is a view of EDIT-01's shared EditorCommandIdV1 registry**, never an independent callback with hidden privileges. Required command metadata: stable namespaced CommandId, localized accessible name/description, category, tooltip/help, icon+text policy, enabled predicate and disabled reason, busy/progress/cancel state, allowed origin, active graph/material context, required capability, undo domain, shortcut and confirmation policy. Mouse, keyboard, command palette, CLI and MCP resolve the same public semantic command and owner-side authorization. Icon color/shape alone never conveys status or type. Text input/IME focus wins over graph shortcuts; Escape cancels pending wire/drag/dialog before closing a panel.

| Toolbar control / CommandId candidate | User-visible behavior | Safety and button-state contract |
|---|---|---|
| Save / `edit5.graph.save` | persist graph + view state | enabled only with write grant and dirty revision; DATA-04 CAS receipt |
| Undo / Redo | reverse graph or parameter edit | active owner-scoped undo domain, conflict warning; never undo compile or gameplay event |
| Add Node / Search Nodes | searchable categorized palette at pointer or graph center | only nodes from versioned trusted registry and current graph domain |
| Validate Graph | non-mutating schema/type/topology/target checks | report ready/warnings/errors; no compile or source mutation |
| Compile Preview | isolated preview compilation for selected target | explicit compile permission/quota; cancellable; last-good retained on failure |
| Preview On/Off / Pin Output | show/hide and pin chosen output preview | preview-only, generation tagged; stale output visibly marked |
| Variant Profile | select target/profile and inspect feature differences | no silent static switch change or target downgrade |
| Frame Selection / Frame All / Minimap | navigate large graph | presentation-only and keyboard accessible |
| Auto Arrange | arrange selected nodes | preview layout delta; graph source/compile digest unchanged |
| Show Generated Source | inspect GFX-02 generated source/map, read-only | compiler receipt-backed; no edit/execute or secret/path leakage |
| Export Validated | preview and export verified shader/material package | disabled until graph/material/target/license checks pass; DATA-05 package receipt |

## 3. Canonical graph model, typed nodes and versioning
**Canonical semantic graph ownership belongs to GFX-02.** Existing GFX-02 owns ShaderDefinitionV1, MaterialDefinitionV1, reflection, compiler profile and compiled artifact. GFX-05 extends material semantics through MaterialSurfaceProfileV1/PbrParametersV1/MaterialVariantPlanV1. EDIT-05 must not mint a second canonical ShaderGraph or MaterialDefinition. The proposed `ShaderGraphDocumentV1` in the API contract requests GFX-02 to formalize a versioned graph representation and schema migration; it is not an adopted ABI or executable schema.

A graph node has stable NodeId, namespaced NodeTypeId + exact version, typed input/output ports, default values, stage/domain and explicit feature requirements. A link connects one output PortId to one input PortId. Types are explicit (scalar/vector/color/matrix, texture/sampler, coordinate/normal, material closure/surface and compiler-defined semantic types). Color space, units, coordinate basis, normal convention and precision are part of semantics, not just UI color. Unsafe or lossy conversion is an explicit conversion node with diagnostic; no implicit arbitrary casts.

Initial shading graph is a bounded **directed acyclic dataflow graph**. Detect cycles before compilation; no arbitrary loop, recursion, unbounded iteration or feedback node. Reusable node groups/subgraphs have declared input/output interface signature, exact version and bounded nesting; recursive subgraph references are rejected. Graph outputs must match selected shader/material domain and stage. Vertex/fragment/light or compute domain is available only when GFX-02 target contract explicitly supports it; unsupported stages fail visibly.

Node registry definitions are immutable versioned metadata: node type ID, input/output signatures, defaults/ranges, stage/domain, target feature gates, implementation reference, provenance/license, diagnostic text and estimated complexity. The editor renders a trusted definition; it does not load arbitrary user DLL, script, source snippet or network plugin. Unknown optional node data can be preserved as opaque source metadata when safe; unknown required node/feature opens read-only or fails validation, never silently drops shading.

**Graph presentation is not shader semantics.** Node positions, zoom/pan, selection, collapsed state, comments/frames, minimap and pinned preview are editor presentation. Store through EDIT-01/DATA-04 workspace/document state with separate revision/digest. They must not affect shader semantic digest, compile cache key or output. Graph semantic edits and presentation-only layout edits use separate undo domains and conflict policy.

## 4. Authoring interactions, navigation and buttons
- Add node via toolbar button, context menu at cursor or keyboard palette; search by name/category/type, show compatible ports and target support before insertion.
- Wire creation previews source/destination port type, stage, unit/color-space conversion and connection validity. Invalid connection never commits; valid connection has deterministic replacement behavior when an input already has a link.
- Support single/multi select, box select, copy/paste with regenerated local IDs and preserved only valid DATA-02 AssetId refs, duplicate, delete, group/frame, collapse, comment/annotation, reroute and safe auto-layout. Advanced collaboration is FUTURE.
- Pan/zoom with cursor anchoring, grid/snap, frame selection/all, minimap and focus-preserving search. Large graphs use viewport culling and spatial hit testing. UI remains responsive while compile/preview runs asynchronously.
- Inspector exposes typed editable fields, reset-to-default, parameter grouping, min/max/range and unit/color semantics. It shows dynamic vs static compile-time values and variant impact before a static change.
- Generated source is a read-only GFX-02 diagnostic view with node/pin source map. It is not an alternate text editor; manual shader source edits are OUT OF SCOPE.
- Keyboard-only graph operations support add, search, select, connect/disconnect, inspect, navigate subgraph, validate, preview, undo/redo and export. Provide accessible semantic node/port list as alternate to spatial canvas; screen readers receive role/name/state/connection context. Do not rely on wire color alone.
- Clipboard import is untrusted data, normalized to current project/graph, quota checked and stripped of unknown executable metadata.

## 5. Material semantics, parameters and variants
GFX-05 owns PBR and stylized material meaning. The editor exposes its material model/profile and uses existing GFX-02/GFX-05 contracts: MaterialDefinitionV1, MaterialInstanceV1, MaterialSurfaceProfileV1, PbrParametersV1, MaterialTextureBindingV1, MaterialQualityProfileV1, MaterialVariantPlanV1 and MaterialValidationReceiptV1. Do not redefine baseColor, metallic, roughness, alpha, normal, transmission, sampler or texture residency.

Dynamic material instance parameters are uniform/data changes and should not trigger shader recompilation when reflection and GFX-05 semantics say they are dynamic. Static feature switches alter the compiled feature set and route through GFX-02 variant planning. Limit combinations and compile only approved/reachable target profiles; report deterministic variant budget and why a new variant is required. No unbounded Cartesian product, silent feature stripping or false "free at runtime" claim. Target variants are distinct from glTF KHR_materials_variants, which is asset-level material assignment and not compiler permutation.

## 6. Preview, compilation, diagnostics and last-good behavior
Preview is a read-only isolated authoring session, not EDIT-07 play-in-editor and not the game world. The graph editor submits semantic source revision + target profile to GFX-02. GFX-02 validates/compiles and returns reflection, artifact identity, cache/provenance, source map and typed diagnostics. GFX-01 validates device capabilities; GFX-03 owns offscreen target/GPU resources/fences; GFX-06 supplies approved neutral preview environment; GFX-07 owns camera/color/tone mapping. EDIT-05 only presents preview lease/receipt.

Preview presets may include shader ball/sphere, cube, plane, UV checker, 2D sprite and controlled material swatch. Fixtures must be original or rights-cleared. Same target artifact and material semantics must be used for preview and runtime; if target lacks a feature, show explicit fallback/difference report, not a fabricated match. Preview generation includes graph/material revision, compiler profile, target, device generation and output selection. Stale output is visibly marked. Failed compile/device loss/cancel retains last-good image and receipt without mutating source or publishing broken runtime pipeline. The editor cannot allocate GPU resources or bypass GFX-03 completion fences.

## 7. Target compatibility, import/export and interoperability
Target profiles are capability snapshots, not OS-name guesses: Windows Vulkan/D3D12, Linux Vulkan, macOS Metal, WebGPU and reduced WebGL2. GFX-02 compiler matrix remains authority: Slang Metal is experimental and WGSL output work-in-progress in current documentation; DXC is not a universal MSL/WGSL exporter. A graph feature may be supported, translated with explicit loss, or unsupported per target. Required unsupported feature => typed failure; no silent lowering.

MaterialX is optional interchange, not canonical runtime or mandatory editor dependency. Import is preview-first: validate document/schema, node definitions, graph topology, external file references, textures, rights and unsupported features; produce exact loss/compatibility report before DATA-03 import. Export is a deterministic projection of supported graph/material semantics; unknown nodes are not converted to arbitrary source. glTF material export is limited to material core and ratified/verified extensions; graph-only procedural semantics may require explicit bake/unsupported report. KHR_materials_variants is asset-level mapping, not proof of shader-variant build.

Catalog validated export flow: validate graph + material + source rights + target capability -> GFX-02 compile receipt -> GFX-05 material validation -> DATA-05 immutable package manifest -> DATA-01 scoped destination grant and staged export -> DATA-04/DATA-05 readback digest and export receipt. No raw filesystem path, shell command, network upload or unvalidated binary export.

## 8. Security, privacy, reliability and accessibility
Threat inputs include MaterialX XML/JSON, clipboard graph payloads, imported node definitions, textures/includes, project assets, malformed numeric parameters, oversized/deep graphs, cyclic subgraphs, shader compiler inputs and AI/MCP calls. Threats: XML entity/path traversal, decompression bomb, memory/CPU/VRAM exhaustion, recursive graph evaluation, variant explosion, compiler escape, shader cache poisoning, stale GPU handles, malicious node implementation, hidden code execution, project cross-scope writes and source/absolute-path leakage.

Proposed defenses: DATA-01 scoped VFS/no-follow; DATA-03 bounded non-executable parser; DATA-02 rights/provenance; DATA-04 schema/CAS/journal; GFX-02 isolated compiler with no network/host path and allowlisted options; per-document/node/edge/depth/parameter/compile quotas; signed/approved node registry provenance; source and target digest checks; idempotency and owner-side authorization on every write; redacted CORE-06 diagnostics. No arbitrary custom node code, script node or untrusted plugin in this module.

Accessibility: semantic role/name/state for every button/node/port, non-color-only wire types, high contrast, text scaling, reduced motion, keyboard alternatives, focus/IME safety, localized diagnostics and screen-reader graph list. Windows UIA, macOS AX and Linux AT-SPI/Wayland require real native tests; metadata alone is not conformance.

## 9. Scope classification and evidence gates
- **NECESSARY research:** graph/editor ownership, typed node/port/link contract, canvas interactions/buttons, compile/preview lifecycle, material parameter and bounded variant flow, validated export, security/license matrix, exactly 128 future tests and benchmark/fault protocol.
- **IMPORTANT candidates:** reusable subgraphs/node groups, comments/frames/reroutes, graph auto-layout, advanced search/favorites, shader source-map navigation, Web graph editor adapter. Require owner acceptance and actual usability/performance evidence before becoming 1.0 must-have.
- **FUTURE:** user-authored executable custom nodes/plugins, unrestricted script/code nodes, collaborative graph editing, cloud shader compilation, remote asset upload, ML-generated graphs that auto-commit, ray-tracing/material promises without target proof.
- **OUT OF SCOPE:** engine code, compiler/IR, GPU/driver, PBR model, asset registry/importer/cooker, toolkit choice, shader-language choice, dependency installation, public release, numeric performance claims and owner approval of any ADR.

See [ADR-0057](../adr/0057-edit-05-semantic-graph-authoring-and-preview.md), [technology/license matrix](../research/edit-05-visual-shader-technology-license-matrix.md), [typed API](../contracts/edit-05-visual-shader-api.md), [128 future tests](../testing/edit-05-acceptance-matrix.md) and [benchmark protocol](../research/edit-05-visual-shader-benchmark-protocol.md).
