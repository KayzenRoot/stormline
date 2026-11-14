# TWO-04 — Typed 2.5D Hybrid Scene, Depth, Layer and Render Intent API v0.1

**Research #156 / NLE-P00-WO-002-TWO-04 | Future implementation #40 BLOCKED**.  
Versioned **semantic proposal only**, not C++ ABI, shader layouts, WebGPU bindings, authorized MCP host actions or actually rendered scene.

| Proposed logical type | Fields / versioned meaning | Invariants / external authority |
|---|---|---|
| `HybridScenePlanV1` | project+SceneId/revision, CameraId/GFX-07 ViewId, CanvasId, GFX-04 3D scene ref, quality/caps and output profile | one scene/source truth DATA-04 and GFX-03 render plan, not duplicate world |
| `HybridCompositionModeV1` | `SHARED_DEPTH_WORLD / ORDERED_CANVAS_OVERLAY / ISOLATED_SUBVIEW` | explicit depth availability vs pixel-order promise |
| `HybridCompositionLayerV1` | LayerId, group/source IDs, stable draw order, pass stage, mode, clip/opacity/isolation, depth/alpha policy, light mask | TWO-01 painter semantics, GFX-05 alpha and GFX-03 graph |
| `HybridCameraBridgeV1` | GFX-07 camera/view epoch, ortho/perspective, source handedness/up, world units, near/far, reversed-Z/clip, DPI/pixel-to-meter | finite matrices, coordinate conversion DATA-03, no automatic cross-view depth |
| `HybridAnchorV1` | stable AnchorId/SceneEntityId/asset+rev, `VIEW_ALIGNED/AXIS_LOCKED/WORLD_PLANE/SCREEN_OVERLAY`, pivot/feet, normal/tangent, size, bounds, anim ref | checked transforms, GFX-04 visible bounds, TWO-01 SpriteDraw compatible |
| `HybridDepthPolicyV1` | depth test/write, material alpha `OPAQUE/MASKED/BLENDED`, depth compare, sample/resolve, occlusion group, sort point and tie | scene depth/format GFX-01/03/07 and GFX-05 alpha; not global Y sort |
| `HybridTransparencyPlanV1` | stable painter/mesh priorities, sorted group, blend mode, optional weighted OIT recipe, accuracy/known loss | OIT approximate and opt-in, no silent cross-alpha reordering |
| `HybridLightingBridgeV1` | lit/unlit, normal facing/tangent, light group, receiver/caster layers/proxy and bounded shadow budget | GFX-05 materials, GFX-06 lighting and shadow owners |
| `HybridSubViewPlanV1` | child CameraId, graph render target/view/size/frame freshness, color+optional depth metadata, parent projection, budget, recursion cap | GFX-03 owns memory/barriers; depth only valid under verified transform |
| `HybridTemporalPlanV1` | motion vector/reactive/disocclusion intents, cut/rebase/history event, scene pixel art/native UI path | GFX-07 owns TAA/reconstruction/output and history |
| `HybridPassIntentV1` | source IDs, stage/dependencies, attachment use (color/depth/stencil), viewport/scissor, load/store/resolve, expected device generation | GFX-03 graph owns hazards/fence; no private GPU command stream |
| `HybridQualityBudgetV1` | GPU target time, sprite/mesh/light/subview/draw count, depth attachment sizes, transparency overdraw, CPU, VRAM and quotas | source measured vs ESTIMATED/UNKNOWN; no unlimited view recursion |
| `HybridQualityReceiptV1` | scene+view+revision/device/head, chosen mode, clipping/depth errors, fallback and quality loss, GPU/CPU/VRAM provenance | no fabricated screenshots/timings |
| `HybridEditTransactionV1` | project/SceneId expected DATA-04 revision, bounded staged camera/layer/anchor/depth/subview edit, role, journal token | scope CAS and rollback, permission and project boundary |

## Proposed render flow (not executed)
`DATA04_SCENE_SNAPSHOT -> GFX07_VIEW_CONVENTION -> GFX04_MESH_VISIBILITY + TWO01_SPRITE_DRAW_PLAN -> TWO04_DEPTH/ORDER_MODE_VALIDATE -> GFX03_PASS_DAG_DEPENDENCY_CHECK -> GFX05_MATERIAL+GFX06_LIGHT_INTENTS -> GFX07_POST/TEMPORAL+HUD_COMPOSITION -> GFX01_PRESENT`. Stage ordering is proposed, **not** a fixed deferred/forward shader schedule. Depth-writing masked world sprites must be placed consistently with 3D lighting, not arbitrarily after opaque lighting.

## Explicit invariants and failure modes
1. `SHARED_DEPTH_WORLD`: one compatible camera/projection/depth attachment or formally validated reprojection; opaque/masked may write depth, alpha-blended normally test but no write. Cannot promise global exact transparency intersection.
2. `ORDERED_CANVAS_OVERLAY`: exact stable Canvas painter order, native-resolution HUD possible, no 3D occlusion unless explicitly authored bridge. Depth-based DoF/fog not applicable if no world depth.
3. `ISOLATED_SUBVIEW`: render color/alpha to texture with GFX-03 lifecycle, frame freshness and max recursion; optional depth cannot be used as parent depth without a verified world transform and depth linearization.
4. No geometry/collision truth from sprite visual alpha or artist sort point; PHYS/WORLD controls gameplay. On invalid mode, stale device epoch or deleted scene asset, **fail explicit** not “sprite appears above wall” silently.

## Editor, CLI and MCP semantic parity
Readonly `InspectHybridScene`, `InspectHybridCameraBridge`, `PreviewHybridSortPlan`, `InspectDepthAvailability`, `InspectHybridLightingBridge`, `PreviewSubViewBudget`, `GetHybridQualityReceipt`. Mutations `StageHybridEdit`, `ValidateHybridEdit`, `CommitHybridEdit`, `CancelHybridOperation`, expected DATA-04 revision, project+capability scoped, journal/rollback. No arbitrary shader/graphics driver call, URL/file access, cross-project subview, shell, raw GPU pointer or export without rights. Estimated depth/quality preview must **not** be labeled rendered GPU proof.

## Error taxonomy
`HYBRID_VIEW_INVALID`, `CAMERA_PROJECTION_MISMATCH`, `COORDINATE_BRIDGE_OVERFLOW`, `ANCHOR_BASIS_DEGENERATE`, `DEPTH_ATTACHMENT_UNAVAILABLE`, `DEPTH_CONVENTION_MISMATCH`, `DEPTH_FORMAT_UNSUPPORTED`, `DEPTH_WRITE_ALPHA_CONFLICT`, `PAINTER_ORDER_CONFLICT`, `TRANSPARENCY_UNRESOLVED`, `LIGHT_NORMAL_INVALID`, `LIGHT_BUDGET_EXCEEDED`, `SHADOW_PROXY_INVALID`, `SUBVIEW_RECURSION_LIMIT`, `SUBVIEW_PROJECTION_MISMATCH`, `SUBVIEW_STALE_FRAME`, `ATTACHMENT_ALIAS_HAZARD`, `COLORSPACE_DOUBLE_TRANSFORM`, `TEMPORAL_HISTORY_STALE`, `GPU_DEVICE_GENERATION_STALE`, `VRAM_BUDGET_EXCEEDED`, `SCENE_REVISION_CONFLICT`, `SOURCE_RIGHTS_DENIED`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Include stage, retryable, safe redacted source id and fallback receipt; never print raw resource handles/scene secrets.

## Freeze before implementing
Owner-approved 1.0 release class/Scope/DoD, actual implemented TWO-01 and GFX-04, frozen GFX-01/03/05/06/07 color-depth-camera APIs, data+world authority, native/Web targets, device-specific depth/MSAA/hazard proof, original scene golden and pixel/HDR numeric tolerance, measured FPS/VRAM/p95/p99, exact C++/shader file list and raw SHA-256 Context Lock. **None approved today**, #40 still BLOCKED.
