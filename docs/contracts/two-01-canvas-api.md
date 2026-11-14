# TWO-01 — Typed Canvas, Sprite, Vector and Glyph Render API v0.1

**WO NLE-P00-WO-002-TWO-01 | Research #147 | Code #37 BLOCKED**. Semantic proposal only; NOT C++ ABI, compiled shader, live GPU API or wire schema.

| Proposed type | Fields and stable versioned intent | Constraints and owner |
|---|---|---|
| `Canvas2DSceneV1` | project+SceneId+CanvasId/revision, viewport/camera, logical and physical pixels, DPI, working color/alpha | DATA-04 identity/scene, GFX-07 view/presentation |
| `CanvasCamera2DV1` | CameraId/revision, ortho transform, pixel scale/zoom/rotation/snap mode, safe areas/letterbox | finite and CORE-05/GFX-07 math, unjittered UI |
| `CanvasLayerV1` | layer id+parent, stable depth/order, drawing sequence, opacity, clip/mask and blend | alpha painter order, bounded nesting |
| `SpriteDrawV1` | SpriteAssetId/material+revision, atlas region, pivot, trim/flip/nine-slice, transform, tint, layer/order | GFX-05 texture/alpha, checked UV and sizes |
| `AtlasRegionV1` | DATA-05 AtlasId/revision, subrect and gutter/mips/sampler/color profile, device generation/fence | no stale atlas UV, GFX-03 resource ownership |
| `SpriteBatchPlanV1` | validated ordered contiguous spans, material+sampler/texture/clip/view, instance buffer size/draw count | never reorder interfering alpha layers |
| `CanvasClipStackV1` | nested bounded scissor/path/stencil depth, parent/mask and alpha isolation | no offscreen leaks/NaN, GFX-03 pass |
| `VectorPathV1` | PathId/revision, contour lines/quad/cubic, winding, join/cap, miter/dash/gradient | DATA-03 sanitized import, segment/time quotas |
| `VectorDrawPlanV1` | path/raster scale, tessellation/cache/bounded fallback, source revision | no vendor ABI, no unchecked extra shader |
| `TextRunDrawV1` | grapheme cluster/glyph ids and positions, font AssetId/revision, direction/script/baseline+clip | UI owns layout+input, Canvas only renders glyph plans |
| `GlyphAtlasPlanV1` | font+scale/hinting/gray-MSDF mode, glyph page/table/generation/rights and eviction | GFX-03 fence, no unlicensed fonts |
| `CanvasLightRequestV1` | layer+receiver/caster masks, source material normal and GFX-06 light plan link | GFX-06 actually owns lighting |
| `CanvasQualityBudgetV1` | sprites/glyphs/path segments/clip depth/atlas bytes/overdraw and CPU/GPU target, source | actual vs estimates, GFX-03 memory limits |
| `CanvasQualityReceiptV1` | scene/frame+device fingerprint, contiguous batches, alpha order, cost/degrade/unknown source/errors | redacted and reproducible, no fabricated GPU time |
| `CanvasEditTransactionV1` | project/CanvasId, expected revision, allowlisted staged commands, role and DATA-04 journal | optimistic CAS/rollback and quota |

## Submission and recovery
`SCENE_SNAPSHOT -> ASSET_RIGHTS_CONFIRMED -> LAYER_ORDER_VALIDATED -> CAMERA_AND_COLOR_VALIDATED -> REFERENCE_BATCH_PLAN -> GFX03_GRAPH_SUBMIT -> GPU_FENCE_COMPLETE -> GFX01/GFX07_PRESENT`. Repack/resize/device lost/font revision => invalidate cache and safe fallbacks, never an invalid GPU descriptor or altered alpha painter order.

## Editor, CLI, MCP safe semantic operations
- `InspectCanvas`, `InspectCanvasLayers`, `InspectSprite`, `PreviewCanvasBatchPlan`, `PreviewCanvasQualityBudget`, `InspectFontGlyphFallback`, `GetCanvasQualityReceipt`: project-scoped, bounded read-only, clearly ESTIMATED versus real GPU measured.
- `StageCanvasEdit` -> `ValidateCanvasEdit` -> `CommitCanvasEdit`, `CancelCanvasOperation`: scoped role, expected revision, DATA-04 journal and idempotent rollback. Asset import via DATA-03, not direct file/network MCP.
- Forbidden: arbitrary SVG XML script, CSS/HTML, OS font filepath/network download, native GPU buffer, shader text/JIT upload, private asset export, cross-project scene edits, unlimited clip/shape operations.

## Typed failure taxonomy
`CANVAS_INVALID`, `CANVAS_COORDINATE_OVERFLOW`, `CANVAS_VIEWPORT_INVALID`, `PIXEL_SNAP_INCOMPATIBLE`, `SPRITE_UV_INVALID`, `ATLAS_REGION_STALE`, `ATLAS_CAPACITY_EXCEEDED`, `PAINTER_ORDER_CONFLICT`, `MATERIAL_ALPHA_MISMATCH`, `CLIP_STACK_EXCEEDED`, `VECTOR_PATH_INVALID`, `VECTOR_COMPLEXITY_LIMIT`, `SVG_EXTERNAL_REFERENCE_DENIED`, `FONT_RIGHTS_DENIED`, `FONT_FALLBACK_MISSING`, `TEXT_SHAPING_UNAVAILABLE`, `BIDI_LAYOUT_UNSUPPORTED`, `CANVAS_BUDGET_EXCEEDED`, `DISPLAY_DPI_CHANGED`, `GPU_GENERATION_STALE`, `SHADER_LAYOUT_MISMATCH`, `SOURCE_REVISION_CONFLICT`, `CAPABILITY_DENIED`, `CANCELLED`, `RECOVERY_REQUIRED`. Return safe stage, retryability, correlated request and redacted metadata.

## Freeze gate
Concrete ABI, C++ paths, backend shader layout, source import/cook, real font licenses and localization, accepted 60 FPS fixture/thresholds, GFX-01 DATA-03 implementation and GFX-03/05/07 contracts, SHA-256 Context Lock. No executor-ready from this document.
