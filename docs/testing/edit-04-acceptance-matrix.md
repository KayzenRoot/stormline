# EDIT-04 — Exactly 128 Future Acceptance Tests (E04-T001..E04-T128)

**2026-11-15 | [#264](https://github.com/KayzenRoot/stormline/issues/264) | P00 DESIGN, NO EXECUTION.** `NLE-P00-WO-002-EDIT-04`; code [#71](https://github.com/KayzenRoot/stormline/issues/71) BLOCKED. Each row is a **future executable test obligation**, not a passing test. Baseline 52/80 research documented, 80 coding WOs BLOCKED. **Total cases: 128; passed: 0; failed: 0; not executed: 128.**

## Oracle protocol and fixtures
- Every future test requires a fixture manifest with content hash, schema version, seed, test-mode OS/graphics backend/driver, device tier, renderer DPI, build HEAD, expected revision and API owner. Reject nonreproducible or unlicensed content.
- Validated means compare durable source revisions/digests, readback/source state, rendered/a11y output and negative failure receipt as applicable, with explicit numeric tolerances approved by owner; use no invented visual/hardware results.
- G1 viewport: scales, screen orientation, two monitors and input emulation; G2 tiles: source-managed original tileset and sparse maps with negative boundaries/terrain rule fixtures; G3 UI: responsive viewports and component library; G4 language: Unicode 18 and fonts with rights; G5 timeline: signed rational time/skeleton; G6 storage: crash/disk fault fixtures; G7 security: hostile parser/actor inputs; G8 integration/performance: three OS and Web matrix after implementation.
- Catalog acceptance GUI-only 2D project proof is E04-T126/E04-T127, *NOT* achieved by file-based fixture creation or hand-authored JSON. Document step-by-step screen recording, command log, files inspected read-only and cross-target replay in future.

## Complete unique acceptance matrix
| Test ID | Category | Proposed scenario and required oracle | Fixture / collection | Status |
|---|---|---|---|---|
| E04-T001 | FUNCTIONAL | Cursor-anchored wheel zoom retains pointed world coordinate within validated epsilon | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T002 | FUNCTIONAL | Fractional display-DPI pan/zoom inverse transform round-trip bounds remain finite | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T003 | FUNCTIONAL | Integer pixel-art zoom renders nearest texel without unintended shimmer | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T004 | FUNCTIONAL | Noninteger smooth zoom uses explicit filtering and does not rewrite sprite UV | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T005 | FUNCTIONAL | Drag-pan interrupted by focus loss cancels pointer capture and source edits | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T006 | FUNCTIONAL | Trackpad gesture with reversed scroll honors user remap and preserved anchor | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T007 | FUNCTIONAL | Touch pinch with rotation keeps selected object and avoids accidental paint | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T008 | FUNCTIONAL | Keyboard pan and zoom operate with no pointing device and clear shortcut labels | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T009 | FUNCTIONAL | Gamepad mode maps navigation to authoring UI without capturing gameplay seat | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T010 | FUNCTIONAL | Monitor transfer DPI epoch change invalidates stale pick then remaps anchor | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T011 | FUNCTIONAL | Negative signed64 grid cell world-to-grid floor division is mathematical floor | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T012 | FUNCTIONAL | Large origin rebase keeps selection anchored and IDs unchanged | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T013 | FUNCTIONAL | Orthographic grid snap half-cell tie break is deterministic and editable | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T014 | FUNCTIONAL | Rotated/noninvertible viewport transform yields typed rejection no persistent edit | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T015 | FUNCTIONAL | Multi-selection lasso respects clip/alpha/layer and provides accessible list alternative | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T016 | FUNCTIONAL | Offscreen, unloaded or stale GPU pick is rejected with generation mismatch | Fixture group G1, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T017 | FUNCTIONAL | Atlas tiles select by stable TileId after atlas repack or asset rename | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T018 | FUNCTIONAL | Atlas nine-slice pivot/trim/flip combinations preserve source image bounds | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T019 | FUNCTIONAL | Brush one-cell click commits exactly one grouped DATA-04 operation | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T020 | FUNCTIONAL | Diagonal stroke rasterization covers deterministic same cells for same samples | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T021 | FUNCTIONAL | Rectangle/ellipse paint preview clearly shows affected cells before commit | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T022 | FUNCTIONAL | Stamp scatter with identical seed/revision yields identical semantic result | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T023 | FUNCTIONAL | Erase/repaint source equality restores exact tile+variant metadata | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T024 | FUNCTIONAL | Large flood fill refuses quota without any persistent chunk modification | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T025 | FUNCTIONAL | Wang corner/edge terrain rule updates every impacted neighbor in preview | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T026 | FUNCTIONAL | Incomplete terrain rule set errors rather than silent wrong auto-connection | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T027 | FUNCTIONAL | Brush crossing positive chunk boundary persists and reloads both sides | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T028 | FUNCTIONAL | Brush crossing negative chunk boundary uses correct chunk/key and neighbor halo | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T029 | FUNCTIONAL | Layer group reorder maintains alpha/painter order and collision provenance | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T030 | FUNCTIONAL | Parallax preview affects draw offset only, never stored collision positions | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T031 | FUNCTIONAL | Tile orientation orthogonal/isometric/hex unsupported mode reports capability accurately | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T032 | FUNCTIONAL | Collision activation remains pending until matching TWO-02 owner acknowledgment | Fixture group G2, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T033 | FUNCTIONAL | New UI document uses GAME-03 UiDocument/UiTree stable IDs not duplicate graph | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T034 | FUNCTIONAL | Widget palette rejects unknown required widget types | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T035 | FUNCTIONAL | Anchor min/max constraints respond to narrow viewport with no negative sizes | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T036 | FUNCTIONAL | Flex row/column intrinsic text resize uses GAME-03 real text measurements | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T037 | FUNCTIONAL | Percent-of-auto cycle reports constraint loop with stable error location | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T038 | FUNCTIONAL | Optional grid adapter not offered unless GAME-03 capability is supported | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T039 | FUNCTIONAL | Landscape/portrait profile recalculation keeps safe-area margins | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T040 | FUNCTIONAL | Ultrawide and split-screen profiles render unjittered overlays correctly | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T041 | FUNCTIONAL | High-DPI scale changes do not double-apply text/transform scaling | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T042 | FUNCTIONAL | Large text accessibility zoom recomputes layout without clipped focus | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T043 | FUNCTIONAL | Reusable component variant override leaves sibling definitions intact | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T044 | FUNCTIONAL | Nested component cycle is rejected and source unchanged | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T045 | FUNCTIONAL | Responsive preview matches actual GAME-03 layout plan hash for same inputs | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T046 | FUNCTIONAL | Unknown required layout feature fails closed; optional field can round-trip | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T047 | FUNCTIONAL | Style/theme token state variant is stable across save and reopen | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T048 | FUNCTIONAL | UI inspector selection references valid node/generation after hierarchy change | Fixture group G3, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T049 | A11Y/I18N | Emoji ZWJ grapheme caret cannot split user-perceived character | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T050 | A11Y/I18N | Arabic shaping and RTL focus maintain logical versus visual indexes | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T051 | A11Y/I18N | Indic conjunct cluster edit preserves shaping and IME composition | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T052 | A11Y/I18N | Mixed bidi numerals and LTR labels display/copy in safe logical order | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T053 | A11Y/I18N | Unicode 18 grapheme and line-break fixtures match normative reference | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T054 | A11Y/I18N | Font fallback across Latin/CJK/emoji has defined missing-glyph reporting | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T055 | A11Y/I18N | Invalid UTF-8 import is rejected with sanitized diagnostics | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T056 | A11Y/I18N | Unlicensed font asset is blocked at authoring/export preflight | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T057 | A11Y/I18N | Locale/BCP47 variant and pluralized message preview use GAME-03 catalog | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T058 | A11Y/I18N | Localized button expands width and preserves no-overlap responsive layout | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T059 | A11Y/I18N | Every icon-only toolbar button has role/name/tooltip/disabled reason | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T060 | A11Y/I18N | Button press via mouse, keyboard and gamepad resolves same CommandId and receipt | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T061 | A11Y/I18N | Modal dialog traps focus appropriately and returns focus on cancel | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T062 | A11Y/I18N | IME composing in inspector never triggers tile painting or global shortcut | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T063 | A11Y/I18N | High-contrast and reduced-motion preview disclose unsupported platform semantics | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T064 | A11Y/I18N | Screen reader native UIA/AX/AT-SPI smoke testing records real evidence per OS | Fixture group G4, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T065 | FUNCTIONAL | Flipbook frames keep stable SpriteAssetId/atlas revisions after repack | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T066 | FUNCTIONAL | Rational frame time seeking exactly round-trips over long timeline duration | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T067 | FUNCTIONAL | Keyframe insertion at duplicate timestamp has documented deterministic policy | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T068 | FUNCTIONAL | Bezier tangent NaN/Inf fails without modifying curve source | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T069 | FUNCTIONAL | Tween interpolation at endpoints matches typed value and finite tolerance | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T070 | FUNCTIONAL | Reversed/looped timeline boundaries fire preview cues idempotently | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T071 | FUNCTIONAL | Moving a key between tracks generates one undoable semantic transaction | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T072 | FUNCTIONAL | Delete/restored key recovers original stable KeyId and time after redo conflict check | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T073 | FUNCTIONAL | Scrub does not mutate play-mode simulation state or network actors | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T074 | FUNCTIONAL | Timeline FPS preview uses CORE-04 clock not GUI wall-delta accumulation | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T075 | FUNCTIONAL | Bone parent-cycle in proposed skeleton is rejected before preview | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T076 | FUNCTIONAL | IK unreachable target produces bounded diagnostic rather than hanging | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T077 | FUNCTIONAL | Skin weight invalid sums/indices reject before render staging | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T078 | FUNCTIONAL | Rig preview stale skeleton/device epoch does not draw stale geometry | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T079 | FUNCTIONAL | Animated tile clip and terrain map revisions cohere or report pending | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T080 | FUNCTIONAL | Reduced motion pauses decorative authored UI animation without source mutation | Fixture group G5, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T081 | RECOVERY | Brush drag commit is one history group, not a record per pointer sample | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T082 | RECOVERY | Undo with matching revision restores semantic before state and digest | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T083 | RECOVERY | Redo with changed external revision refuses conflict rather than overwriting | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T084 | RECOVERY | Delete layer cancel before confirmation leaves source and history unchanged | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T085 | RECOVERY | Source CAS race between UI and CLI accepts one and rejects stale writer | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T086 | RECOVERY | MCP retry with same idempotency key does not duplicate paint | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T087 | RECOVERY | Crash before staging creates no committed partial result | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T088 | RECOVERY | Crash after one multi-chunk write replays or rolls back using journal | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T089 | RECOVERY | Disk-full during multi-file transaction preserves last-known-good and error | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T090 | RECOVERY | Unsupported required schema opens read-only without silent migration | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T091 | RECOVERY | Explicit migration previews lossy fields and requires backup+confirmation | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T092 | RECOVERY | Save/reopen identical project reproduces TileId, UI NodeId and keyframes | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T093 | RECOVERY | Unknown optional fields round-trip and are never evaluated as scripts | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T094 | RECOVERY | Import TMX/LDtk supported subset produces transparent loss report | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T095 | RECOVERY | Export/import handles signed negative coordinates and preserves handedness | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T096 | RECOVERY | Export with missing assets/fonts reports missing rights/refs before writes | Fixture group G6, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T097 | SECURITY | Unauthorized read-only actor cannot commit brush/UI/timeline mutations | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T098 | SECURITY | AI/MCP and GUI command parity enforces same scoped capability on owner side | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T099 | SECURITY | Project A actor cannot edit Project B even with guessed stable IDs | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T100 | SECURITY | Symlink/reparse/../ path escape in imported tileset is denied by DATA-01 | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T101 | SECURITY | Compressed/decompression bomb and oversized image are rejected under budgets | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T102 | SECURITY | TMX malicious XML external entity and SVG active content execute nothing | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T103 | SECURITY | Tile metadata containing code or scripts remains inert untrusted data | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T104 | SECURITY | Malformed variable font and invalid glyph collection fail bounded parse | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T105 | SECURITY | Overflow of signed64 chunk/index arithmetic fails closed with stable error | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T106 | SECURITY | High-rate pointer flood and hostile MCP request trigger quotas not OOM | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T107 | SECURITY | Sensitive path, token and source text are not written into diagnostics | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T108 | SECURITY | Source revision and authorization checked again at commit not just toolbar | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T109 | SECURITY | Asset license/provenance and NOTICE are required for exported fixtures | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T110 | SECURITY | Focus escape from modal on remote command cannot alter hidden source | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T111 | SECURITY | Crash recovery never trusts unsigned external journal content as code | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T112 | SECURITY | Imported copyrighted sample assets are excluded from shared benchmark packs | Fixture group G7, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T113 | PERF/INTEGRATION | Windows native DPI/IME/keyboard pointer tests record renderer and driver | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T114 | PERF/INTEGRATION | Linux X11 and Wayland variants explicitly log unsupported window behaviors | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T115 | PERF/INTEGRATION | macOS Apple Silicon native focus/IME/accessibility and display profile checked | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T116 | PERF/INTEGRATION | macOS Intel tested or explicitly NOT SUPPORTED by approved target matrix | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T117 | PERF/INTEGRATION | WebGPU and WebGL2 fallback UI rendering modes compared when available | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T118 | PERF/INTEGRATION | Small low-tier GPU p50/p95/p99 frame and CPU/GPU memory measured not asserted | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T119 | PERF/INTEGRATION | Mid-tier 100k-cell map viewport brush and chunk latency histogram captured | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T120 | PERF/INTEGRATION | Stress 1m sparse cells and heavy terrain halo checks memory ceiling | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T121 | PERF/INTEGRATION | 10k widgets dirty-subtree responsive reflow bound and layout validity tested | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T122 | PERF/INTEGRATION | 10k glyph mixed-script locale/shaping cache miss and frame impact measured | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T123 | PERF/INTEGRATION | 1k keyframe interactive scrub and seek p95/p99 under repeatable runs | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T124 | PERF/INTEGRATION | Live preview/edit switch 100 times has no leaked subscriptions or source changes | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T125 | PERF/INTEGRATION | GPU device loss during brush preview preserves canonical source and recovers | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T126 | PERF/INTEGRATION | Test 1 completes editor GUI-only original 2D project: create/paint/UI/animate | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T127 | PERF/INTEGRATION | Test 2 saved project reopens, exports and replays with no direct file editing | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |
| E04-T128 | PERF/INTEGRATION | Full fixture validates UI/CLI/MCP parity without elevating blocked code status | Fixture group G8, repeat baseline and verify typed receipt/snapshot/hash | FUTURE / NOT EXECUTED |

## Count and owner handoff
- Group G1 tests 001–016; G2 017–032; G3 033–048; G4 049–064; G5 065–080; G6 081–096; G7 097–112; G8 113–128.
- Selected future tests map to GOV-004/005, CAP-008/010/011/012/013/014/016 and NFR-001..005; exact release-class applicability, risk/test coverage and success thresholds must be approved before Zcode activation. Runtime owner receipts: EDIT-02, TWO-01/02/03, GAME-03, GFX-07, DATA-04 and EDIT-01.
- **All test cases NOT EXECUTED.** No C++ build, screenshot diff, UIA/AX/AT-SPI pass, GPU benchmark, native editor, crash result or GUI-created project exists.

[Architecture](../architecture/edit-04-2d-ui-editor.md) · [semantic API](../contracts/edit-04-2d-ui-api.md) · [benchmark protocol](../research/edit-04-2d-ui-benchmark-protocol.md).
