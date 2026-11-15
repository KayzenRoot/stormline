# EDIT-04 — Typed 2D Canvas, Tile Brush, UI Designer and Timeline Semantic API v0.1

**2026-11-15 | [#264](https://github.com/KayzenRoot/stormline/issues/264) | BASE `8036d723dbf07c13020536cf9a0550bb5afb4b32` | P00 PROPOSED ONLY.** These are logical contracts, not compiled C++ headers, JSON schemas, executable MCP endpoints or adopted wire protocols. Future implementation issue #71 BLOCKED. Formal prerequisites EDIT-02/TWO-02 documented but unimplemented.

## 1. Stable value objects and authority
| Candidate type V1 | Fields/invariants | Sole source/owner |
|---|---|---|
| `Edit2DSessionV1` | ProjectId, workspace/panel IDs, actor+capability, read-only mode, expected project/scene revision, input epoch | EDIT-02 project/EDIT-01 shell; EDIT-04 leases only |
| `CanvasViewportV1` | CanvasId, camera view ID+epoch, logical DIP/physical extent, display DPI, safeArea, origin epoch, zoom scale, pixelArtMode, source hash | TWO-01/GFX-07 camera; EDIT-04 view intent only |
| `CanvasTransformV1` | typed screen DIP/physical/world local/grid/atlas spaces, invertible affine matrix, rounding/tie-break, finite precision and epoch | CORE-05 numeric reference; reject singular or stale epoch |
| `GridSnapPolicyV1` | projection, grid origin/axes, cell size, snapping mode, visible/active flags, magnet threshold, tie-break | TWO-02 projection; UI policy stable |
| `ViewportPickV1` | project/map/scene/layer/TileId or UiNodeId, generation, source revision, viewport epoch, hit depth, clip and alpha rules | renderer hit plan with validation on receipt |
| `SpriteAtlasSelectionV1` | DATA-02 AssetId, TilesetId+revision, stable TileId(s), pixel rect, pivot/trim/flip/nine-slice and rights | DATA-02/05 asset source; TWO-01 Canvas render |
| `TileBrushDescriptorV1` | BrushId, shape POINT/LINE/RECT/ELLIPSE/STAMP/FLOOD/REPLACE/ERASE, tile pattern, seed, radius, pressure/spacing, max cells and scope | EDIT-04 tool intent; TWO-02 solver validates |
| `TileStrokeSampleV1` | rational sample ordering, signed64 cell, interpolated position/pressure, input source, captured actor epoch | EDIT-04 input adapter; no unbounded raw pointer path |
| `TileStrokePlanV1` | MapId/LayerId, expected per-chunk/source revision, brush and cells, terrain rule/hash, full halo diff and quota, fallback reason | TWO-02 canonical map and deterministic terrain rules |
| `TileEditPreviewV1` | source hash, affected cells+neighbors/chunks, collision stale warning, draw overlay, estimated memory/latency | EDIT-04 presentation only; not durable |
| `TileEditReceiptV1` | operation id, DATA-04 committed source revision+hash, chunks changed, terrain/collision ack or pending, undo token | DATA-04 commit; TWO-02 actual activation ack |
| `UiDesignerDocumentRefV1` | ProjectId, GAME-03 UiDocumentAssetId, UiTreeId/revision, preview locale/style profile | GAME-03 semantic model; DATA-04 durable source |
| `UiWidgetEditV1` | stable UiNodeId+generation, allowlisted widget/style/constraints property change, expected old value and source rev | GAME-03 validator; EDIT-04 choice/inspector |
| `UiResponsiveProfileV1` | logical/physical dimensions, DPI, orientation/safeArea, locale, RTL, textScale, focusSeat, reducedMotion | GAME-03 layout+focus, GFX-07 view |
| `UiPreviewResultV1` | layout revision, rectangles/clips, overflow/unsatisfied constraints, focus graph, styled glyph/text runs, a11y notices | GAME-03 layout/shaping plan, TWO-01/GFX presentation |
| `UiComponentTemplateV1` | namespaced component ID/version, immutable tokens/variants, slots and property allowlist, composition cycle bound, license/provenance | DATA-02/04 source, GAME-03 tree |
| `TimelineEditorRefV1` | TWO-03 ClipId/SequenceId, timebase rational, track IDs, loop mode and revision | TWO-03 evaluator source; EDIT-04 handles authoring UI |
| `TimelineKeyEditV1` | TrackId/KeyId, time rational, typed target and value/tangents, interpolation, expected key old rev | TWO-03 typed curve and ordering validation |
| `Rig2DPreviewV1` | SkeletonId/BoneId/generation, rest/pose transform, IK bounded diagnostic, viewport/device epoch | TWO-03 evaluator, TWO-01 draw; read-only overlay |
| `Edit2DCommandV1` | stable namespaced CommandId, actor/capability, origin GUI/SHORTCUT/CLI/MCP, target, expected DATA-04 revision, idempotency, allowlisted payload and undo domain | EDIT-01 registry; target edit owners enforce |
| `Edit2DPreviewV1` | accepted/rejected, deterministic before/after semantic diff, dependency/risk/rights, cost/quota, required confirmation and pending owners | non-mutating until approved |
| `Edit2DTransactionV1` | command/preview digest, operation/actor/authorization, project-scoped expected revisions, grouped stroke/key edit, recovery journal ref | DATA-04 stages/commits; EDIT-04 never writes file |
| `Edit2DUndoReceiptV1` | actor/undoDomain, transaction id, source rev/hash before/after, inverse preview and conflict state | DATA-04 undo history, EDIT-01 shell selection separate |
| `Edit2DErrorV1` | stage, stable error code, safe target locator, retryable, stale rev, no secrets/path disclosure | each owner explicit failure |

## 2. Semantic command surface, public Editor/CLI/MCP parity
| Namespaced command | Input contract -> result | Side effects and permissions |
|---|---|---|
| `edit2d.viewport.set_camera` / `edit2d.grid.configure` | viewport/zoom/pan/snapping policy -> view receipt | ephemeral workspace change only, EDIT-01/CORE-05 scope |
| `edit2d.sprite.select` | TilesetId+TileId/AssetId -> selection readback | read-only, stale atlas rejection |
| `edit2d.tile.stroke.preview` / `edit2d.tile.stroke.commit` | TileBrushDescriptor, sample span, chunk revisions -> bounded full halo diff / DATA-04 commit | WRITE_TILE_PROJECT with explicit destructive approval when replace/flood/indirect large edit |
| `edit2d.tile.layer.edit` | LayerId+reorder/parallax/opacity -> TWO-02 validated patch | source revision CAS, no physics activation claim |
| `edit2d.ui.widget.preview` / `edit2d.ui.widget.commit` | UiTree/NodeId, style/constraints diffs -> GAME-03 layout snapshot / canonical revision | WRITE_UI_PROJECT, no raw HTML/JS |
| `edit2d.ui.preview.profile` | viewport+locale+input+font profile -> snapshot/diagnostics | no canonical writes |
| `edit2d.timeline.key.preview` / `edit2d.timeline.key.commit` | TrackId/KeyId rational time and typed value -> TWO-03 preview/commit receipt | WRITE_ANIMATION, no runtime gameplay cue mutation |
| `edit2d.history.undo` / `edit2d.history.redo` | undo domain, token, expected source rev -> inverse preview/receipt | owner-scoped expected CAS, conflict refuse instead of replay |
| `edit2d.import.preview` / `edit2d.import.commit` | VFS grant + untrusted format/asset source, rights -> lossy field mapping/preview/commit | DATA-01/03 import and explicit owner confirmation |
| `edit2d.project.verify_gui_complete` | ProjectId and user-specified artifact requirements -> provenance & source transaction proof | read-only acceptance evidence, never fabricate "GUI-only" claim |

No direct filesystem command, shell eval, unsafe plugin, unscoped resource write, arbitrary URI or unapproved server invocation. All commands perform server/owner-side access checks EVEN if UI says disabled. Idempotency key required for mutating retries. Nondeterministic preview cannot be used as CAS proof.

## 3. Error codes and state transitions
Examples: `E04_INVALID_COORDINATE`, `E04_NONINVERTIBLE_TRANSFORM`, `E04_UNSUPPORTED_PROJECTION`, `E04_STALE_VIEWPORT_EPOCH`, `E04_STALE_TILE_REVISION`, `E04_TERRAIN_RULE_INCOMPLETE`, `E04_BRUSH_QUOTA`, `E04_UI_CONSTRAINT_CYCLE`, `E04_TEXT_SHAPING_UNAVAILABLE`, `E04_FONT_RIGHTS_UNKNOWN`, `E04_TIMELINE_INVALID_TIMEBASE`, `E04_PERMISSION_DENIED`, `E04_PENDING_OWNER_ACK`, `E04_SOURCE_CONFLICT`, `E04_RECOVERY_REQUIRED`, `E04_UNSUPPORTED_SCHEMA`.

State path: `VALIDATE -> PREVIEW_READY -> (DENIED | CONFIRM_REQUIRED | STAGED) -> COMMIT_BY_DATA04 -> ACK_PENDING/COMMITTED -> (UNDO_AVAILABLE | RECOVERY_REQUIRED)`. Cancel before commit is side-effect free; failure after partial commit must expose recovery and last-good, not unconditional "success". Undo does not guarantee restoring a source revised by another actor.

## 4. Schema compatibility and security
- Version each format and required feature capability, preserve unknown safe optional fields, reject unknown required fields on read/write. No automatic downgrade/migration with loss; explicit backup+preview and DATA-04 migration receipt. Deterministic semantic source digest including type/precision and sorted stable IDs.
- Reject NaN/Inf and dimension multiplication overflow, negative/cross-chunk floor mistakes, cyclic widget/bone/prefab references, unsupported compression/XXE/external file entities, SVG scripts, unsafe fonts; per-command file/CPU/cell/vertex/glyph quotas and granular role checks.
- Focus/input origin separation prevents accidental paint by gamepad or IME; text source sanitize + bidi and grapheme operations from GAME-03, not local regex. Locale rights and source provenance must survive import/export.
- Observability: CORE-06 trace IDs, duration histograms p50/p95/p99, edit bytes and region counts, no raw private project content in logs; bench tool separate.

## 5. Integration and test refs
[EDIT-01 command registry](edit-01-editor-shell-api.md), [EDIT-02 project](edit-02-project-management-api.md), [EDIT-03 scene](edit-03-scene-terrain-api.md), [TWO-01 Canvas](two-01-canvas-api.md), [TWO-02 map](two-02-tilemap-api.md), [TWO-03 animation](two-03-animation-api.md), [GAME-03 UI](game-03-ui-text-localization-api.md), [DATA-04 persistence](data-04-scene-api.md), [architecture](../architecture/edit-04-2d-ui-editor.md), [128 future tests](../testing/edit-04-acceptance-matrix.md).

**No ABI stability promise; no code compiled, engine, UI, tooling or MCP server exists.**
