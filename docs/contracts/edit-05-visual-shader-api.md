# EDIT-05 — Visual Shader & Material Graph Typed Semantic API v0.1

**P00 RESEARCH PROPOSAL ONLY | 2026-11-15 | [#268](https://github.com/KayzenRoot/stormline/issues/268) | BASE `7034fdce1d1d0220b349e8b333dc67cc6d19c515`.** Logical versioned types and commands, not compiled C++ headers, JSON Schema, MCP server, compiler, renderer, file format or stable ABI. GFX-02 owns canonical shader graph semantics/compilation; GFX-05 owns material semantics; EDIT-05 owns authoring UI and view state.

## 1. Canonical references and typed objects
| Proposed type | Fields / invariants | Authority |
|---|---|---|
| `ShaderGraphDocumentV1` | ShaderAssetId/revision, graph schema version, graph domain/stage, stable NodeId/PortId/EdgeId arrays, output refs, required feature set, node registry snapshot, provenance digest | **GFX-02 canonical schema owner**; this contract requests formalization there |
| `ShaderNodeDefinitionRefV1` | namespaced NodeTypeId, exact semantic version, definition digest, input/output signature, stage/domain and target feature gates, implementation ref, license/provenance | GFX-02 immutable trusted registry; EDIT-05 display only |
| `ShaderNodeInstanceV1` | NodeId, definition ref, parameter values, per-input bindings/defaults, owner source revision, stable display name | GFX-02 graph semantics; DATA-04 persistence |
| `ShaderPortDescriptorV1` | PortId, direction INPUT/OUTPUT, typed value, semantic/unit/color-space/coordinate convention, stage/domain, required/optional, finite default/range | GFX-02 type system; no implicit lossy conversion |
| `ShaderGraphEdgeV1` | EdgeId, source NodeId/PortId, destination NodeId/PortId, type adapter ref if explicit | GFX-02 topology; one valid edge per destination unless node definition declares multi-input |
| `ShaderGraphSubgraphRefV1` | subgraph AssetId/revision, interface signature digest, node registry compatibility and bounded depth | GFX-02; no recursion or unknown required interface |
| `ShaderGraphValidationReportV1` | graph/material revisions, schema/topology/type/stage/target errors, node/pin/edge locators, required feature list, deterministic digest | GFX-02 validates; EDIT-05 presents |
| `GraphPresentationStateV1` | graph AssetId/revision, node positions, zoom/pan, grouping, collapsed nodes, minimap state, pinned preview output, layout version | EDIT-05 presentation; EDIT-01/DATA-04 persist separately from compile digest |
| `MaterialGraphBindingV1` | MaterialAssetId/revision, GFX-02 ShaderDefinition ref, GFX-05 MaterialSurfaceProfile/PbrParameters/MaterialInstance refs, texture bindings | GFX-05 canonical semantics; DATA-02 stable IDs |
| `MaterialParameterEditV1` | parameter ID/type, value, dynamic/static classification from owner schema, expected material revision, optional target profile | GFX-05 validation; EDIT-05 inspector intent |
| `MaterialVariantPlanV1` | static feature set, target profile, ShaderVariantKey, expected graph/material revision, reflection/layout digest, estimated/actual budget, unsupported features | GFX-02/GFX-05; no duplicate variant compiler |
| `ShaderGraphCompileRequestV1` | graph/material revisions, semantic digest, compiler profile ref, target capability snapshot, variant key, quotas, idempotency/cancel token | GFX-02 compile service; no arbitrary command flags |
| `ShaderGraphCompileReceiptV1` | status, compiler/profile digest, artifact ID, target, reflection/layout signature, source map, cache provenance, duration/resource receipt, diagnostics | GFX-02; estimates distinct from measured values |
| `MaterialPreviewSessionV1` | session ID/generation, graph/material revision, compile receipt, target profile, preview primitive, environment ref, camera/color profile, offscreen lease | EDIT-05 controls; GFX-01/03/06/07 own actual device/render/light/color |
| `MaterialPreviewReceiptV1` | preview generation, artifact/material revision, device generation, fence state, last-good ref, unsupported feature/loss report, render status | GFX-03/GFX-07 actual receipt; stale generation rejected |
| `ShaderExportPlanV1` | graph/material revision, target set, requested source/interchange/cooked package forms, supported node set, license/provenance, expected output manifest | EDIT-05 plans; GFX-02 compiles, DATA-05 packages, DATA-01 grants destination |
| `ShaderExportReceiptV1` | manifest digest, source revision, compiled artifact IDs, target feature report, files/bytes, rights notices, destination grant and readback digest | DATA-05/DATA-01 actual commit receipt; no fabricated export |
| `Edit5CommandInvocationV1` | EditorCommandIdV1, origin GUI/SHORTCUT/PALETTE/CLI/MCP, actor capability, project/material/graph refs, expected revision, idempotency key, typed args | EDIT-01 registry + owner authorization |
| `Edit5CommandReceiptV1` | accepted/rejected/cancelled, owner, operation/transaction ID, resulting revision, preview/compile/export receipt, safe error and focus restore | target owner; no generic success without readback |
| `Edit5TransactionV1` | staged graph/material diff, actor, source hash/revision, preview digest, DATA-04 CAS/journal ref, undo domain | DATA-04 commit; EDIT-05 cannot write files |
| `Edit5ErrorV1` | stable code, stage, node/pin/edge locator, retryability, source revision, safe redacted diagnostic | owner-specific typed error |

## 2. Shared button/command registry and toolbar contract
Toolbar buttons are EDIT-01 `EditorCommandIdV1` registrations, not a private EDIT-05 event bus. Each command declares localized label/description, accessible role/name, tooltip, category, icon+text policy, active graph/material context, enabled predicate and disabled reason, keyboard shortcut, allowed origins, required capability, undo domain, busy/progress/cancel state and confirmation policy. Server-side owner validates authorization and expected revision even if button is disabled.

| Namespaced semantic command | Input -> output | Side effects / permission |
|---|---|---|
| `edit5.graph.node.add` | NodeTypeId + graph revision + canvas position -> node preview/receipt | WRITE_GRAPH, trusted node registry only |
| `edit5.graph.node.connect.preview` / `edit5.graph.node.connect.commit` | Node/Port IDs + expected graph revision -> typed connection report / DATA-04 transaction receipt | WRITE_GRAPH; reject incompatible types/stages/cycles |
| `edit5.graph.node.delete` / `edit5.graph.node.duplicate` | selected NodeIds -> staged semantic diff | WRITE_GRAPH, bounded fan-out and dependent edge preview |
| `edit5.graph.group.create` / `edit5.graph.subgraph.open` | selected nodes / SubgraphAssetId -> group or scoped graph view | group view is presentation; subgraph source requires owner contract |
| `edit5.graph.view.set` / `edit5.graph.view.frame` / `edit5.graph.view.minimap` | viewport intent -> presentation receipt | view state only, no compile digest/source mutation |
| `edit5.graph.layout.preview` / `edit5.graph.layout.commit` | selected node layout -> layout diff | presentation undo domain only |
| `edit5.graph.validate` | graph/material revision + target -> validation report | read-only, no compiler execution |
| `edit5.graph.compile.preview` / `edit5.graph.compile.cancel` | compile request + target/variant -> GFX-02 receipt | COMPILE_PREVIEW capability and quotas; isolated cancellable job |
| `edit5.material.parameter.preview` / `edit5.material.parameter.commit` | parameter edit + material revision -> validation/receipt | WRITE_MATERIAL; dynamic/static impact explicit |
| `edit5.material.variant.plan` / `edit5.material.variant.build` | static features + target -> bounded plan / GFX-02 compile receipt | explicit variant budget; no unbounded compile matrix |
| `edit5.preview.configure` / `edit5.preview.pin_output` | preview profile/output -> session receipt | read-only, GFX owner leases |
| `edit5.source.inspect` | artifact/receipt -> source text/map | read-only compiler receipt, redact host paths and secrets |
| `edit5.export.preview` / `edit5.export.commit` | target package + destination grant -> loss/license report / verified export receipt | EXPORT_VALIDATED_MATERIAL; DATA-01/05 authorization and stage |
| `edit5.history.undo` / `edit5.history.redo` | owner undo token + expected revision -> inverse preview/receipt | DATA-04 CAS conflict refuses stale overwrite |

## 3. Graph invariants and type rules
- Stable IDs survive node rename/reorder; paste/duplicate generates new local NodeId/EdgeId and preserves only valid DATA-02 AssetId refs.
- Every edge connects a declared output to a compatible input; type, width, stage, unit, coordinate basis and color-space rules validated. Conversion must be explicit, versioned and loss annotated.
- Baseline graph is bounded DAG. Cycles, recursive subgraphs, unbounded loop/iteration and unresolved required NodeTypeId are rejected. Node/edge/depth caps are versioned policy, numeric thresholds TBD.
- Canonical semantic graph digest excludes positions, pan/zoom, selection, minimap, comments and panel state. Presentation state has independent revision/digest and undo domain.
- Shader graph schema migrations are deterministic, previewed, DATA-04-owned and backup/rollback capable. Unknown required schema/node => read-only or unsupported; unknown safe optional metadata can round-trip opaque without execution.
- Stage/domain, required feature and target compatibility are checked before compile. No "compile succeeded" inferred from graph validation alone.

## 4. Preview and compiler state machine
`EDIT -> VALIDATE -> COMPILE_QUEUED -> COMPILE_RUNNING -> COMPILE_RECEIPT -> PREVIEW_QUEUED -> GPU_FENCE_COMPLETE -> PREVIEW_READY`. Error/cancel/device loss yields typed failure and retains last-good artifact/image; source revision never changes. Stale graph/material/target/device generation invalidates receipt. GFX-02 owns compile/cache; GFX-03 owns resource/fence; GFX-01 owns device generation; GFX-06/07 own light/color. Editor does not call driver or publish runtime pipeline.

## 5. Typed error examples
`E05_UNKNOWN_NODE_TYPE`, `E05_NODE_VERSION_UNSUPPORTED`, `E05_PORT_TYPE_MISMATCH`, `E05_STAGE_MISMATCH`, `E05_GRAPH_CYCLE`, `E05_SUBGRAPH_RECURSION`, `E05_GRAPH_QUOTA_EXCEEDED`, `E05_TARGET_FEATURE_UNSUPPORTED`, `E05_SHADER_COMPILE_FAILED`, `E05_COMPILER_TIMEOUT`, `E05_COMPILER_SANDBOX_DENIED`, `E05_REFLECTION_MISMATCH`, `E05_VARIANT_BUDGET_EXCEEDED`, `E05_PREVIEW_STALE_GENERATION`, `E05_DEVICE_LOST`, `E05_SOURCE_REVISION_CONFLICT`, `E05_IMPORT_LOSS_REQUIRES_CONFIRMATION`, `E05_LICENSE_DENIED`, `E05_EXPORT_NOT_VALIDATED`, `E05_CAPABILITY_DENIED`, `E05_RECOVERY_REQUIRED`.

## 6. Security and compatibility
No arbitrary source string/OS command/URL/raw path/GPU pointer/driver flag via graph node or MCP. Graph import is non-executable; compiler is isolated and bounded by GFX-02; node implementation provenance is checked; every write uses actor capability, expected revision and idempotency. Export requires rights and target validation. Windows/Linux/macOS/Web profile gaps remain explicit. Numeric quotas and ABI are TBD, not implied by this proposal.

[Architecture](../architecture/edit-05-visual-shader-material-graph.md) · [ADR-0057](../adr/0057-edit-05-semantic-graph-authoring-and-preview.md) · [128 future tests](../testing/edit-05-acceptance-matrix.md) · [benchmark protocol](../research/edit-05-visual-shader-benchmark-protocol.md).
