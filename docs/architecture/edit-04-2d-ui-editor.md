# EDIT-04 — 2D & UI Editor Architecture v0.1

**2026-11-15 | P00 RESEARCH ONLY | [#264](https://github.com/KayzenRoot/stormline/issues/264) | Work Order NLE-P00-WO-002-EDIT-04 | future code [#71](https://github.com/KayzenRoot/stormline/issues/71) OPEN/BLOCKED.** Verified source BASE main `8036d723dbf07c13020536cf9a0550bb5afb4b32`, catalog order 53/80, baseline 52/80 documented and 28 pending; 80/80 coding WOs BLOCKED. Formal DAG predecessors **EDIT-02 and TWO-02**, both research/ADR PROPOSED only. No engine or editor implemented.

## 1. Original ownership, no parallel authoring engines
Propose a **Stormline 2D Authoring Command Facade**. A single validated, capability-scoped semantic command path drives canvas, tiles, responsive UI and timeline inspectors from EDIT-01 buttons/menus/keyboard, optional CLI and AI/MCP. Viewport overlays and previews are *ephemeral projections* of immutable versioned source. EDIT-04 edits the authoring intent and interaction model, not the truth of assets, game UI layout engine, renderer or serialization. All live engine interfaces remain future work.

| Boundary | Exclusive authority | EDIT-04 obligation |
|---|---|---|
| EDIT-01 / CORE-01 | native window, panels, dock, focus/IME/OS events and accessibility host | panel/command descriptors, button labels, shortcuts, focus restore; no second toolkit |
| EDIT-02 / DATA-01 | ProjectId, project mode, sandboxed VFS grants | validate 2D capability, project-scoped permissions, no raw paths |
| DATA-02/03/04/05 | AssetId/provenance, safe import, canonical revision/CAS/journal/undo and packed/cooked assets | use stable ref + source revision, preview before commit; do not write data independently |
| CORE-04/05/06 | rational time, units/signed positions, diagnostics | finite double transforms, stable frame/tick correlation, redacted traces |
| TWO-01 / GFX-01/03/05/07 | sprite/glyph draw and alpha order, camera/display scale, textures/gpu fences, color/safe-area | pass typed draw/hit-test plans, never duplicate GPU pipeline |
| TWO-02 | sparse signed-64 tile coordinates, TileId, chunks, terrain rule evaluator, collision metadata | choose brush, author transaction, show rule diff, seek owner acknowledgment |
| TWO-03 | flipbook, keyframe, tween, skeletal/IK evaluator and tick semantics | keyframe/track editing, scrub/preview input and received poses |
| GAME-03 / GAME-01 | semantic UiTree/constraints/shaping/focus, gameplay input owner | author UiDocument, select widget and preview *same* runtime UI layout; command/edit input separate from game input |
| EDIT-03 / EDIT-07 | scene/prefab authoring operations / isolated play-in-editor | embed 2D scene selection through existing transaction owner; read-only play view, no silent writeback |
| QA-04 / AI-MCP | secure tooling, capability/auth/review grants | explicit scoped actor and authorization for public authoring commands, never remote arbitrary exec |

**Important:** EDIT-01/03/07, TWO-01/03, GAME-01/03, GFX, DATA, CORE and AI/MCP are *integration owners*, NOT new formal dependencies of EDIT-04; catalogue DAG remains **EDIT-02 + TWO-02 only**.

## 2. Viewport, coordinates, input and accessibility
- Viewport source coordinate: signed 64-bit tile-grid cell plus bounded local 2D double. Distinguish screen physical pixels, logical DIP, project/world units, camera, atlas texels and sprite local coordinates with typed transforms and origin epoch.
- Zoom about cursor and center, configurable pixel-art integer-scale mode, smooth zoom mode and hard finite min/max; anchored pan by mouse wheel/trackpad, keyboard, middle-button or touch gesture; preserve world point under gesture through DPI/monitor shifts and device loss.
- Grid overlays support orthogonal baseline and conditional isometric/staggered/hex ONLY after TWO-02 projection proof. Snapping explicitly records grid scale, origin, half-cell/tie-break and modifier override; never silently quantize canonical coordinates while previewing.
- Dirty-region rendering, viewport occlusion cull and chunked hit testing. Hit results carry project/scene/map/layer/chunk generation, viewport epoch and source revision; stale picks fail closed. Layer/pixel alpha and clipped hit policy must agree with visible selection.
- Sprite/atlas inspector uses DATA-02 stable AssetId + TileId, DATA-05 atlas revision, UV trim/pivot/nine-slice and bounded image metadata; pixel snapping does not interfere with rotation or opacity. Selection supports multi-select, range, box, lasso, keyboard and accessible list alternate.
- Inputs: pointer/mouse, trackpad, stylus if supported, touch, keyboard, IME and gamepad test commands. Native editor shortcuts are EDIT-01; gameplay device actions stay GAME-01. Explicit capture/focus prevents painting when typing in an inspector or hovering a button; accessible labels, shortcuts, hints and disabled reasons are mandatory.
- **Buttons/control conventions:** every toolbar action has stable namespaced CommandId, accessible name, tooltip, localized text, enabled predicate, busy/cancel state, undo domain, keyboard/gamepad route, explicit destructive confirmation. Decorative icon alone cannot convey meaning; no hidden hotkeys in text fields.

## 3. Tile authoring and atlas
- ONE canonical TWO-02 TileMapAssetV1. A brush preview consists of world cell set, TilesetRef, TileId/variant, radius/shape, actor, expected map/layer/chunk revisions and a bounded dependency neighborhood. Commit is one DATA-04 grouped transaction per stroke, not one history record per mouse sample.
- Rect/line/flood/stamp/erase/replace brushes have deterministic rasterization, tie breaks, brush seed, cap on cells/bytes/duration and preview cost. Pressure curves and random scatter optional only with reproducible seed and control.
- Terrain/Wang autotiling requests TWO-02 solver with explicit rule-set revision and neighborhood/chunk halo; preview lists *all* indirectly modified neighbors including out-of-brush and cross-chunk edits. Missing atlas tiles/rules show typed diagnostic and never silently paint incorrect transitions.
- Layer groups, visibility, alpha, ordering, parallax and z/painter order refer to TWO-01 and TWO-02 immutable IDs. Collision metadata authored separately from physics activation; display pending/mismatch from TWO-02 receipt instead of claiming physics sync.
- Tiled TMX/JSON and LDtk can be evaluated as import/export adapters: preflight safe path, dimensions, compressed/uncompressed ratio, external resource refs, tile transform flags, Wang IDs, orientation, Unicode names, schema versions and unknown-field loss reports. No copied proprietary sprites or original editor source; no format compatibility claim until fixtures pass.

## 4. Responsive UI and text editing
- EDIT-04 authors **GAME-03 UiDocumentV1/UiTreeV1** rather than storing another widget tree. Design panel displays bounded widget palette, hierarchy, inspector, styles/tokens/variants, responsive device profiles and focus graph; preview must run GAME-03 semantic layout and TWO-01/GFX-07 render for parity, not an imitation DOM renderer.
- Anchors, constraints and flex-like layout are expressed as GAME-03 typed layout properties with intrinsic text measure, min/max bounds, safe-area, DPI, percent, aspect, RTL and orientation. A CSS-like grid adapter is *IMPORTANT/conditional* until game UI layout owner approves compatible semantics. Reject cycles, impossible constraints, NaN, overflowing anchors and unsatisfied required features with actionable diagnostics.
- Designer uses preview profiles for narrow phone, tablet/desktop, ultrawide, split-screen and dynamic text magnification, locale and controller focus. Editing a breakpoint records semantic input conditions, never hard-coded device identifiers.
- Unicode sources are UTF-8 with grapheme-aware selection/caret/IME, bidirectional text, soft wrapping, ellipsis, plural and locale catalog references (GAME-03). HarfBuzz shaping/FreeType raster and ICU/Unicode segmentation are candidates already discussed in GAME-03; EDIT-04 must not maintain a second font shaper, glyph atlas or locale registry. Font rights/provenance and fallback are explicit.
- Buttons, text fields, menus and dialogs have semantic role/name, focus tab/spatial order, disabled/inert semantics, touch target policy, screen reader events, reduced motion and high-contrast preview. Cross-OS UIA/NSAccessibility/AT-SPI and actual Web semantics require later system tests, not inferred from document design.

## 5. Timeline, rig and live preview
- Timeline editor emits TWO-03 rational timebase AnimationClipV1/SequenceAssetV1 edits with stable key IDs, tracks, loop/reverse policy, typed eased interpolation and tangents; changes shown as source diff before commit.
- Flipbook/sprite sheets and keyframe tweening are NECESSARY proposed editor authoring. Bones, skin weights, IK, blend tree/state authoring are IMPORTANT follow-ons controlled by TWO-03 evidence and corresponding release-class decision; never fork simulation or assume Spine runtime rights.
- Scrub/playhead maps fixed time/tick from CORE-04; cue/audio/VFX owner must receive idempotent preview-only signals, never emit production gameplay side effects. EDIT-07 runs preview isolated from editing source; snapshots include seed, component revision, tick, input and device profile.
- Undo/redo of a keyframe, selection or brush never rewinds runtime simulations; UI selection undo (EDIT-01) is separate from canonical DATA-04 document history.

## 6. Durable edit transaction and recovery
Command lifecycle: `CAPABILITY_CHECK -> VALIDATE -> PLAN/PREVIEW -> USER_CONFIRM_IF_NEEDED -> STAGE -> DATA04_CAS_COMMIT -> OWNER_ACK -> RECEIPT/UNDO_TOKEN`. Aborts do not mutate source; all retries use idempotency key. A brush crossing chunks stages all desired changes; failed partial multi-file commits require journal/recovery proof, never claim cross-filesystem atomicity. Undo has actor/command group, revision/hash, safe inverse and conflict if changed externally. Keep last-known-good and explicit migration/report/backup; read-only open for unsupported required schema.

## 7. Quality and forward development gates
Future tests are enumerated as **128 E04-T001..E04-T128** in [acceptance matrix](../testing/edit-04-acceptance-matrix.md); [benchmark protocol](../research/edit-04-2d-ui-benchmark-protocol.md) covers 3 desktop OS, Web when available, hardware tiers, 1k/100k/1m cells and responsive text/animation. All metrics provisional and *NOT MEASURED*. No implementation authorizations: P00 document risk LOW, eventual durable edits ELEVATED, privileged import/plugin/AI operations up to HIGH_ASSURANCE after threat review. ADR-0056 PROPOSED, engine code license NLE-D009 OPEN.

Related [EDIT-02](../contracts/edit-02-project-management-api.md), [TWO-02](../contracts/two-02-tilemap-api.md), [GAME-03](../contracts/game-03-ui-text-localization-api.md), [TWO-03](../contracts/two-03-animation-api.md), [EDIT-03](../contracts/edit-03-scene-terrain-api.md).
