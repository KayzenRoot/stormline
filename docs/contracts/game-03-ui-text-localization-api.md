# GAME-03 — UI/HUD, Text, Localization, Focus and Accessibility Semantic API v0.1

**Issue #216 | WO NLE-P00-WO-002-GAME-03 | future implementation #59 OPEN/BLOCKED.** These `V1` concepts describe **PROPOSED semantic contracts only**; not implemented C++ headers/ABI, runtime, JSON schema, GPU draw command or deployed API.

## 1. Proposed typed contracts
| Logical type | Key semantic fields | Owner, invariant, risk |
|---|---|---|
| `UiDocumentV1` | ProjectId, UiDocumentAssetId, schema version/hash, root NodeId, stylesheet/LayoutId, locale catalog references, rights, sourceRevision | DATA-02 identity and DATA-04 canonical source/CAS, GAME-03 semantic layout validator |
| `UiTreeV1` | UiTreeId/instance epoch, immutable nodes/revisions, parent and ordered children, lifecycle/focus/accessibility policy | GAME-03, bounded acyclic hierarchy/depth, no raw pointer |
| `UiNodeHandleV1` | UiTreeEpoch, NodeId, generation, source revision | GAME-03, stale/recycled node generation rejected |
| `UiWidgetDescriptorV1` | semantic type Container/Text/Button/Image/Toggle/Slider/Progress/Scroll/List/Tab/Dialog/TextField/RichText; properties/style/role/actions | GAME-03 typed allowlist, no arbitrary HTML/JS/eval |
| `UiStyleTokensV1` | font AssetId/axes, color token, spacing, radius, border, opacity, states, motion preference, layer/clip | GAME-03 style validation; GFX-07 color and TWO-01 draw ownership |
| `UiLayoutConstraintsV1` | flex/stack/grid-like kind, min/max/auto/percent, intrinsic text measure, align, wrap, anchors, margins, aspect, RTL policy | GAME-03 single layout engine, reject cycles/nonfinite impossible constraints |
| `UiViewportProfileV1` | GFX-07 CameraRenderViewV1 id+epoch, logical/physical dimensions, DPI, UI scale, safeArea, orientation, split-screen, color profile | GFX-07 actual output/device owner; unjittered UI viewport |
| `UiLayoutPlanV1` | UiTreeId/revision, viewport/font/locale keys, logical rects/clips/transforms, dirty subtree, paint/focus geometries, diagnostics | GAME-03 geometry, TWO-01 actual Canvas clipping/draw |
| `UiDrawPlanV1` | layout plan hash, order/layer, CanvasLayer, TextRunDraw, SpriteDraw, clip stack, resource generation and budget | GAME-03 builds typed plan; TWO-01 owns GPU batches/glyph atlas, GFX-07 presentation |
| `UiInputRouteV1` | GAME-01 PlayerSeat/WindowEpoch, InputActionFrame, focused NodeId/gen, modal owner, pointer capture token, IME/text owner, consume/propagate | GAME-03 owns actual widget focus and returns InputFocusRoute to GAME-01 |
| `UiFocusTreeV1` | navigation order/spatial neighbors, role/name/visible/disabled/modal rules, focus restore token, selected field/scroll anchor | GAME-03; stable keyboard/gamepad/TV navigation, no hidden trap |
| `UiInteractionIntentV1` | UiEventId, source node/action, principal/role, tick/seat/epoch, target game action ID, expected state revision, idempotency | GAME-02/GAME/NET validates authority and commits; UI never mutates game |
| `UiDataBindingViewV1` | scoped immutable GAME-02 view model revision, allowlisted type/field, subscription/rate/stale policy, redaction | GAME-03 consumes only permitted fields, no arbitrary eval |
| `UiTextSourceV1` | UTF-8 validated source, language/script/direction, normalized policy, markup allowlist, grapheme budget, provenance | DATA-03 parse/rights, GAME-03 Unicode segmentation and rendering plan |
| `UiTextShapingPlanV1` | UAX29 grapheme clusters, UAX9 bidi runs, UAX14 line segments, HarfBuzz glyph runs/positions, font AssetId/revision/fallback, ligatures/axes/features | GAME-03 shapes; TWO-01 draws glyph plan/atlas |
| `UiFontAssetV1` | AssetId, source hash, font face/weight/axes, OpenType features, script coverage, embedding/subset rights, fallback priority | DATA-02/03 rights/import, DATA-05 cook, license per font |
| `UiGlyphCacheKeyV1` | font AssetId/revision, glyph ID, raster mode, scale/DPI, font axes, atlas generation, device/fence epoch | GAME-03 text layout cache; TWO-01 glyph atlas actual lifecycle |
| `UiCompositionTextV1` | focused TextField NodeId/gen, grapheme cursor/selection, IME composition range, candidate screen rect, privacy flag | CORE-01/GAME-01 text events, GAME-03 UI text; no keylog/password trace |
| `UiLocaleBundleV1` | ProjectId/BundleId, BCP-47 locale, CLDR data version, messages keyed ID/type/placeholder schema, completeness, source hash, rights | DATA-04 versioned source/cook, GAME-03 resolves |
| `UiLocaleResolutionV1` | requested/actual locale, verified fallback chain, resolved message key, placeholder types, plural/select/date/units, missing key status | GAME-03, no silent incorrect language selection |
| `UiMessageFormatV1` | key, formatter dialect/version (stable ICU or MF2 gated), typed args, bidi isolate mode, markup whitelist, output length/source | GAME-03, no script/URL/HTML injection or bidi spoof |
| `UiAccessibilityTreeV1` | roles/labels/descriptions/values/states, focus hierarchy, live-region policy, text alternatives/caption links, reading order | GAME-03 semantic data; PLAT adapter native/browser assistive bridge feasibility |
| `UiAccessibilityPreferencesV1` | scale, reduced motion, high contrast, gamepad nav, captions preference, focus visibility/timeout/target size, locale | GAME-03 user-scoped validated data; UX proof required |
| `UiQualityBudgetV1` | max nodes/depth, clip levels, layout passes, text/markup length, glyphs/atlases, tasks/frame/CPU/GPU targets and source type | explicit bounded policy; numeric values UNDECIDED until real hardware |
| `UiQualityReceiptV1` | tree/viewport/locale/font revisions, cache hits/misses, layout CPU, glyph draw cost, GPU measured/estimated/unknown, clipping/warnings | CORE-06 redacted diagnostics, no invented measurements |
| `UiAuthoringTransactionV1` | project/user role, expected DATA-04 revision, typed stage/preview/validate/commit/rollback UI/theme/locale changes | DATA-04 source CAS; Editor/CLI/MCP parity, no direct filesystem |
| `UiErrorV1` | typed status, node/key/locale/viewport/epoch, expected vs actual revision, recovery, redacted diagnostics | GAME-03 graceful fallback |

## 2. Contracted semantic operations
1. `InspectUiCapabilities(target,viewport)` -> supported/unsupported/unknown accessibility, font, text, gamepad, HDR, Web/OS bridge; no blanket parity.
2. `StageUiDocument(project, assetId, source, expectedRevision, principal)` -> DATA-03 import and DATA-04 CAS; no active runtime mutation.
3. `ValidateUiTree(tree, role)` -> bounded node/schema/styles/parent graph, public API/capability and rights checks.
4. `CompileUiLayout(tree,viewport,locale,fontRevisions)` -> deterministic bounded geometry plan using one chosen solver; no renderer/OS call.
5. `ResolveLocalizedMessage(messageKey,locale,typedArgs,policy)` -> BCP-47/CLDR formatting, Unicode bidi isolates, safe span output and exact fallback receipt.
6. `ShapeUiText(source,fontFallback,viewport,locale)` -> grapheme/bidi/script/linebreak, font+glyph run with missing glyph receipt, not GPU atlas ownership.
7. `BuildUiDrawPlan(layout,shaping,view)` -> typed TWO-01 Canvas sprite/text/clip requests with GFX-07 unjittered/color placement.
8. `UpdateUiFocus(route,actionFrame,expectedTreeRevision)` -> UI-owned focus navigation and GAME-01 consumption contract, no second raw input pump.
9. `ApplyUiTextComposition(focusedTextField,IMEEvent)` -> grapheme selection/caret/undo and no private text telemetry.
10. `BindUiDataView(node,immutableSnapshot,principal)` -> scoped GAME-02 data view and redaction; no evaluator.
11. `EmitUiActionIntent(node,action,expectedGameState)` -> GAME/GAME-02/NET authorizes; no direct game state write.
12. `InspectUiAccessibilityTree(view,principal)` -> bounded semantic hierarchy; actual OS screen reader bridge is PLAT and test-gated.
13. `UpdateUiLocale(locale,expectedBundleRevision)` -> invalidate text/layout/glyph caches preserving caret/focus where valid.
14. `StageUiEdit/PreviewUiEdit/CommitUiEdit/CancelUiEdit` -> same DATA-04 CAS/semantic diff/rollback for Editor/CLI/MCP, no arbitrary HTML injection.
15. `InspectUiQualityReceipt` -> actual/estimated/unknown timings, memory/cache/font/glyph failure and privacy-safe warnings.
16. `DestroyUiTree(treeEpoch)` -> invalidate focus, callbacks and pending draws only after TWO-01/GFX-03 fence lifetimes.

## 3. Hard requirements and error taxonomy
- Node ownership/generation, source revisions and consistent project/viewport are mandatory. No C++/DOM/GPU handle escapes public game API; no duplicate Canvas/tone mapping/OS input.
- Font shape/raster/cache levels separated: GAME-03 layout+shaping, TWO-01/ GFX-03 atlas GPU lifecycle, GFX-07 screen/color. HDR text unjittered and final output contrast test is deferred.
- GAME-01 generates action frame, GAME-03 owns focus and composition; UI cannot swallow password/IME into gameplay script. GAME-02 only capability-checked read/intent; game authority remains GAME/NET.
- Data source and localization rights are DATA owners; dynamic values typed and bidi isolated, unknown required messages/error not silent success. No untrusted rich markup execute/OS fetch.
- Typed errors: `UI_TREE_STALE`, `UI_NODE_GENERATION_STALE`, `UI_LAYOUT_CYCLE`, `UI_LAYOUT_NONFINITE`, `UI_LAYOUT_BUDGET_EXCEEDED`, `UI_VIEWPORT_INVALID`, `UI_SAFE_AREA_CONFLICT`, `UI_FOCUS_INVALID`, `UI_FOCUS_TRAP`, `UI_POINTER_CAPTURE_STALE`, `UI_IME_COMPOSITION_STALE`, `UI_INPUT_UNAUTHORIZED`, `UI_ACTION_DENIED`, `UI_PRIVATE_DATA_DENIED`, `UI_FONT_NOT_LICENSED`, `UI_FONT_INVALID`, `UI_FONT_FALLBACK_MISSING`, `UI_SHAPING_FAILED`, `UI_BIDI_INVALID`, `UI_GRAPHEME_INVALID`, `UI_TEXT_TOO_LARGE`, `UI_RICH_TEXT_UNSAFE`, `UI_LOCALE_UNSUPPORTED`, `UI_LOCALE_FALLBACK_CYCLE`, `UI_MESSAGE_PLACEHOLDER_MISMATCH`, `UI_MF2_UNAVAILABLE`, `UI_GLYPH_ATLAS_STALE`, `UI_GPU_DEVICE_LOST`, `UI_COLOR_PROFILE_MISMATCH`, `UI_CONTEXT_EPOCH_STALE`, `UI_REVISION_CONFLICT`, `UI_CAPABILITY_DENIED`, `UI_RESOURCE_EXHAUSTED`, `UI_INTERNAL_FAILURE`.
- All v1 types are proposals, not current engine ABI/schema. Each target needs real tests, GPU displays, OS accessibility and locale/font rights before promises.
