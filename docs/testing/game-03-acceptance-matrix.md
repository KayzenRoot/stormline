# GAME-03 — Acceptance Matrix: 128 FUTURE Cases, NONE EXECUTED

**Research issue #216 | WO NLE-P00-WO-002-GAME-03 | future coding #59 OPEN/BLOCKED**. Exactly **128 prospective tests in 16 suites × 8**. All **FUTURE / NOT EXECUTED**. Catalog acceptance "UI gamepad/mouse, legibilidade, foco e internacionalização" is NOT met by plans. No UI implementation, screenshot, runtime, test fixture, font asset, assistive hardware, GPU benchmark or interoperability proof exists.

| Test ID | Prospective assertion and fixture | Status |
|---|---|---|
| GAME03-TREE-01 | UiDocumentV1 source validates stable ProjectId/NodeId/revision and rejects duplicate IDs | FUTURE / NOT EXECUTED |
| GAME03-TREE-02 | Deep nested cyclic parent reference is rejected before any layout or paint | FUTURE / NOT EXECUTED |
| GAME03-TREE-03 | Button, Text, Container, Progress, Dialog and TextField emit typed semantic descriptors | FUTURE / NOT EXECUTED |
| GAME03-TREE-04 | Hidden/disabled/readonly state never yields a clickable or focusable unauthorized node | FUTURE / NOT EXECUTED |
| GAME03-TREE-05 | Destroyed/recycled UiNodeHandle generation cannot be reused by stale callback | FUTURE / NOT EXECUTED |
| GAME03-TREE-06 | UI state mutation produces an immutable snapshot and bounded dirty subtree list | FUTURE / NOT EXECUTED |
| GAME03-TREE-07 | Long inventory list virtualizes visual children while retaining semantic item count and focus | FUTURE / NOT EXECUTED |
| GAME03-TREE-08 | Unknown required widget/schema revision fails closed with readable placeholder receipt | FUTURE / NOT EXECUTED |
| GAME03-LAY-01 | Flex row/column min/max/auto/percent constraints give expected headless rect oracle | FUTURE / NOT EXECUTED |
| GAME03-LAY-02 | RTL writing direction changes layout start/end without reversing child semantic IDs | FUTURE / NOT EXECUTED |
| GAME03-LAY-03 | Very long translated label wraps without crossing safe-area boundaries | FUTURE / NOT EXECUTED |
| GAME03-LAY-04 | Landscape portrait 16:9 21:9 and 4:3 breakpoints switch intentionally without overlap | FUTURE / NOT EXECUTED |
| GAME03-LAY-05 | Split-screen HUD stays inside its own view and does not steal focus from second seat | FUTURE / NOT EXECUTED |
| GAME03-LAY-06 | Negative/NaN/Inf dimensions and percent cycles are rejected before layout | FUTURE / NOT EXECUTED |
| GAME03-LAY-07 | Reflow after text scale/locale/font update invalidates only affected subtrees | FUTURE / NOT EXECUTED |
| GAME03-LAY-08 | Scrolling/virtualized content has stable anchor and no inaccessible offscreen control | FUTURE / NOT EXECUTED |
| GAME03-VIEW-01 | Logical-to-physical coordinate conversion agrees with viewport DPI and user text scale | FUTURE / NOT EXECUTED |
| GAME03-VIEW-02 | TV overscan/notch safe area keeps critical HUD buttons inside visible bounds | FUTURE / NOT EXECUTED |
| GAME03-VIEW-03 | GFX-07 unjittered view preserves sharp text under variable TAA scene jitter | FUTURE / NOT EXECUTED |
| GAME03-VIEW-04 | SDR display output applies color profile exactly once to UI color values | FUTURE / NOT EXECUTED |
| GAME03-VIEW-05 | HDR10/EDR unsupported monitor returns explicit SDR fallback, no invented HDR signal | FUTURE / NOT EXECUTED |
| GAME03-VIEW-06 | UI focus outline remains visible after camera cut/resolution and HDR mode change | FUTURE / NOT EXECUTED |
| GAME03-VIEW-07 | CPU layout viewport rects match GPU output-space clip/hit rectangles after scaling | FUTURE / NOT EXECUTED |
| GAME03-VIEW-08 | Multi-viewport camera and GFX device-generation changes invalidate stale UI draw plans | FUTURE / NOT EXECUTED |
| GAME03-CAN-01 | UI paint order preserves overlapping alpha painter order across nested CanvasLayers | FUTURE / NOT EXECUTED |
| GAME03-CAN-02 | Nested rounded clips and scrolling masks obey bounded depth and viewport scissor | FUTURE / NOT EXECUTED |
| GAME03-CAN-03 | TWO-01 TextRunDraw receives shaped glyph IDs/positions and valid font revision | FUTURE / NOT EXECUTED |
| GAME03-CAN-04 | Texture and atlas repack invalidates stale glyph UV after GPU fence completion | FUTURE / NOT EXECUTED |
| GAME03-CAN-05 | Sprite nine-slice and text glyph spans share clip without double blending | FUTURE / NOT EXECUTED |
| GAME03-CAN-06 | Glyph atlas memory limit returns safe tofu/fallback rather than invalid GPU pointer | FUTURE / NOT EXECUTED |
| GAME03-CAN-07 | GPU device lost/remount increments generation and rejects stale drawing resources | FUTURE / NOT EXECUTED |
| GAME03-CAN-08 | Headless plan generates geometry/semantics but never falsely reports GPU screenshot | FUTURE / NOT EXECUTED |
| GAME03-GRP-01 | UAX#29 emoji family ZWJ sequence is one grapheme for caret/backspace | FUTURE / NOT EXECUTED |
| GAME03-GRP-02 | Combining accents do not split into visible individual caret steps | FUTURE / NOT EXECUTED |
| GAME03-GRP-03 | Indic conjunct grapheme segmentation is stable under text editing | FUTURE / NOT EXECUTED |
| GAME03-GRP-04 | Unicode 18 segmentation policy version matches ICU data and golden fixtures | FUTURE / NOT EXECUTED |
| GAME03-GRP-05 | Word/sentence selection follows locale segmentation rather than byte offsets | FUTURE / NOT EXECUTED |
| GAME03-GRP-06 | Unpaired surrogates and invalid UTF-8 are rejected or replaced under explicit policy | FUTURE / NOT EXECUTED |
| GAME03-GRP-07 | Emoji variation selector sequence shaping preserves visual cluster integrity | FUTURE / NOT EXECUTED |
| GAME03-GRP-08 | Text truncation and ellipsis never break inside grapheme or escape partial markup | FUTURE / NOT EXECUTED |
| GAME03-BID-01 | Arabic/Hebrew paragraph correctly orders glyph runs without reversing raw code points | FUTURE / NOT EXECUTED |
| GAME03-BID-02 | Mixed Hebrew/English/numbers maintain correct UAX#9 resolved reading direction | FUTURE / NOT EXECUTED |
| GAME03-BID-03 | Untrusted player nickname with directional override is safely isolated and visibly reviewable | FUTURE / NOT EXECUTED |
| GAME03-BID-04 | Balanced FSI/PDI directional isolates contain interpolated dynamic ID/number | FUTURE / NOT EXECUTED |
| GAME03-BID-05 | RTL punctuation pairs and mirrored icons obey declared logical direction policy | FUTURE / NOT EXECUTED |
| GAME03-BID-06 | Selection/caret geometry maps logical grapheme indexes to visual bidi positions | FUTURE / NOT EXECUTED |
| GAME03-BID-07 | Locale switching LTR to RTL preserves focus and does not invert gameplay action mapping | FUTURE / NOT EXECUTED |
| GAME03-BID-08 | Malformed isolate sequences cannot spoof security-sensitive UI values or crash shaping | FUTURE / NOT EXECUTED |
| GAME03-SHP-01 | Arabic connected letter shaping uses contextual OpenType substitutions in golden output | FUTURE / NOT EXECUTED |
| GAME03-SHP-02 | Indic matra/conjunct placement matches validated shaped-run golden metrics | FUTURE / NOT EXECUTED |
| GAME03-SHP-03 | Kerning and ligature shaping provide correct cluster positions and interaction caret hit-test | FUTURE / NOT EXECUTED |
| GAME03-SHP-04 | Variable font axis changes invalidate shape/raster cache with bounded recalc | FUTURE / NOT EXECUTED |
| GAME03-SHP-05 | Mixed CJK Latin emoji fallback preserves line metrics and complex-script glyph IDs | FUTURE / NOT EXECUTED |
| GAME03-SHP-06 | Unsupported font script coverage returns explicit fallback/tofu with accessible text | FUTURE / NOT EXECUTED |
| GAME03-SHP-07 | Shaping version/font revision impacts cached run hash and is reproducible | FUTURE / NOT EXECUTED |
| GAME03-SHP-08 | Long untrusted string and malformed font tables hit parse/shaping CPU and glyph quotas | FUTURE / NOT EXECUTED |
| GAME03-FNT-01 | FreeType hinted grayscale glyph raster compares against original tiny-size reference | FUTURE / NOT EXECUTED |
| GAME03-FNT-02 | Color emoji fallback remains visual and does not force MSDF-only pipeline | FUTURE / NOT EXECUTED |
| GAME03-FNT-03 | Font face file import rejects malformed tables with bounded memory and safe error | FUTURE / NOT EXECUTED |
| GAME03-FNT-04 | Each packaged font asset carries exact OFL/embedding/license/reserved-name provenance | FUTURE / NOT EXECUTED |
| GAME03-FNT-05 | Font subsetting retains mandatory glyphs/script/features and required notices | FUTURE / NOT EXECUTED |
| GAME03-FNT-06 | Modified reserved-family-name font is correctly renamed or blocked per license | FUTURE / NOT EXECUTED |
| GAME03-FNT-07 | Font missing after hot reload/unload safely triggers fallback with no atlas UAF | FUTURE / NOT EXECUTED |
| GAME03-FNT-08 | Font scale DPI and hinting mode produce predictable cache-key invalidation | FUTURE / NOT EXECUTED |
| GAME03-MSD-01 | msdfgen candidate scales headline text without edge/median artifacts at reference sizes | FUTURE / NOT EXECUTED |
| GAME03-MSD-02 | Small 10px caption chooses hinted grayscale when MSDF thin-stroke quality fails | FUTURE / NOT EXECUTED |
| GAME03-MSD-03 | Rapid font-size animation does not unexpectedly blow atlas budget | FUTURE / NOT EXECUTED |
| GAME03-MSD-04 | Signed-distance reconstruction with sharp corners avoids bleeding between packed glyphs | FUTURE / NOT EXECUTED |
| GAME03-MSD-05 | Color emoji and multicolor glyph layers use compatible bitmap path | FUTURE / NOT EXECUTED |
| GAME03-MSD-06 | Subpixel raster under fractional DPI has stable visual/golden comparison thresholds | FUTURE / NOT EXECUTED |
| GAME03-MSD-07 | Fallback path remains legible without GPU compute or novel shader on WebGL2 | FUTURE / NOT EXECUTED |
| GAME03-MSD-08 | No renderer-speed superiority claimed until p95/p99 GPU and CPU measurements | FUTURE / NOT EXECUTED |
| GAME03-LOC-01 | pt-BR en-US fr-FR ar-EG ja-JP tags validated and resolved through explicit BCP-47 chain | FUTURE / NOT EXECUTED |
| GAME03-LOC-02 | Locale-specific plural/select counts and numbering match CLDR49 reference fixtures | FUTURE / NOT EXECUTED |
| GAME03-LOC-03 | Currency date unit and calendar localization uses typed args not preformatted strings | FUTURE / NOT EXECUTED |
| GAME03-LOC-04 | ICU79 MessageFormat2 unsupported preview API returns explicit capability NOT_AVAILABLE | FUTURE / NOT EXECUTED |
| GAME03-LOC-05 | Missing locale/key produces configured visible fallback and diagnostic receipt | FUTURE / NOT EXECUTED |
| GAME03-LOC-06 | Unknown named placeholder/type mismatch is rejected instead of silent interpolation | FUTURE / NOT EXECUTED |
| GAME03-LOC-07 | Locale migration/source CAS preserves glossary/context and translator provenance | FUTURE / NOT EXECUTED |
| GAME03-LOC-08 | CLDR50 development-only data is not silently treated as approved production data | FUTURE / NOT EXECUTED |
| GAME03-IME-01 | GAME-01 physical keyboard event never directly inserts text into focused TextField | FUTURE / NOT EXECUTED |
| GAME03-IME-02 | Japanese composition candidate/caret advances by grapheme not UTF-8 byte | FUTURE / NOT EXECUTED |
| GAME03-IME-03 | Dead key/AltGr composition yields correct localized text while gameplay shortcut suppressed | FUTURE / NOT EXECUTED |
| GAME03-IME-04 | Password typed text is excluded from logs telemetry replay and unauthorized script read | FUTURE / NOT EXECUTED |
| GAME03-IME-05 | IME focus loss/window suspend cancels or commits composition under declared policy | FUTURE / NOT EXECUTED |
| GAME03-IME-06 | Text selection/copy/paste obeys explicit user permissions and source size bounds | FUTURE / NOT EXECUTED |
| GAME03-IME-07 | Right-to-left IME candidate position maps to final clipped physical rectangle | FUTURE / NOT EXECUTED |
| GAME03-IME-08 | Screen reader label placeholder and TextField error states expose sanitized semantics | FUTURE / NOT EXECUTED |
| GAME03-FOC-01 | GAME-01 focus route directs one gamepad D-pad to UI semantic focus and suppresses Attack | FUTURE / NOT EXECUTED |
| GAME03-FOC-02 | Mouse pointer hit test uses final post-scale clip geometry and correct target | FUTURE / NOT EXECUTED |
| GAME03-FOC-03 | Keyboard-only navigation reaches essential menu controls without trap | FUTURE / NOT EXECUTED |
| GAME03-FOC-04 | Modal/dialog Back/Cancel restores previous focus and safe gameplay context | FUTURE / NOT EXECUTED |
| GAME03-FOC-05 | Gamepad spatial navigation produces deterministic target under equal-distance ties | FUTURE / NOT EXECUTED |
| GAME03-FOC-06 | Touch pointer cancel and drag alternative do not submit duplicated confirm intents | FUTURE / NOT EXECUTED |
| GAME03-FOC-07 | Two PlayerSeat split-screen contexts do not steal each other's focus | FUTURE / NOT EXECUTED |
| GAME03-FOC-08 | Virtualized list recycling retains stable focus semantic ID and visible rect | FUTURE / NOT EXECUTED |
| GAME03-ACC-01 | UiAccessibilityTree exposes role/name/value/expanded/disabled state for core controls | FUTURE / NOT EXECUTED |
| GAME03-ACC-02 | WCAG 2.2 keyboard focus visible and not obscured in real viewport fixture | FUTURE / NOT EXECUTED |
| GAME03-ACC-03 | Text can scale to configured accessibility target without essential content clipping | FUTURE / NOT EXECUTED |
| GAME03-ACC-04 | High contrast theme preserves readable text/nontext controls in SDR sample | FUTURE / NOT EXECUTED |
| GAME03-ACC-05 | Reduced-motion preference prevents nonessential parallax or flashing transition | FUTURE / NOT EXECUTED |
| GAME03-ACC-06 | Pointer gesture/drag has keyboard or single-pointer alternative for critical menu operation | FUTURE / NOT EXECUTED |
| GAME03-ACC-07 | Subtitle/SDH live region follows AUD-04 cue without losing speaker/non-speech identity | FUTURE / NOT EXECUTED |
| GAME03-ACC-08 | Assistive screen-reader hardware bridge is reported unverified until real user/OS test | FUTURE / NOT EXECUTED |
| GAME03-SEC-01 | Translated rich text with script/URL/style injection remains escaped and nonexecuting | FUTURE / NOT EXECUTED |
| GAME03-SEC-02 | Font file and SVG asset parser reject external URL/path or entity expansion | FUTURE / NOT EXECUTED |
| GAME03-SEC-03 | Nested UI tree/clip styles with exponential recursion hit bounded quotas | FUTURE / NOT EXECUTED |
| GAME03-SEC-04 | Bidi control spoof attempt on security-sensitive value is isolated/flagged | FUTURE / NOT EXECUTED |
| GAME03-SEC-05 | GAME-02 script without privilege cannot access private inventory/credentials via UI binding | FUTURE / NOT EXECUTED |
| GAME03-SEC-06 | MCP author with readonly scope cannot stage UI source or inject arbitrary html/eval | FUTURE / NOT EXECUTED |
| GAME03-SEC-07 | Stale node/viewport/asset/device generation cannot access freed GPU/host resource | FUTURE / NOT EXECUTED |
| GAME03-SEC-08 | Keyboard/password/IME and player chat content do not enter default telemetry or crash trace | FUTURE / NOT EXECUTED |
| GAME03-PLT-01 | Native Windows x64 keyboard mouse gamepad layout and text fixtures agree with public API | FUTURE / NOT EXECUTED |
| GAME03-PLT-02 | Linux Wayland/X11 actual IME clipboard font fallback is tested, not inferred | FUTURE / NOT EXECUTED |
| GAME03-PLT-03 | macOS arm64 Cocoa IME/accessibility adapter feasibility compared with GAME-01 host | FUTURE / NOT EXECUTED |
| GAME03-PLT-04 | Web browser input focus font loading restrictions and device contexts return explicit capability | FUTURE / NOT EXECUTED |
| GAME03-PLT-05 | Headless CPU semantic/layout oracle runs with zero GPU/audio/window dependencies | FUTURE / NOT EXECUTED |
| GAME03-PLT-06 | Native exports and Editor preserve locale/widget focus/semantic action behavior | FUTURE / NOT EXECUTED |
| GAME03-PLT-07 | Font library and data exact version licensing/notice SBOM verified in export bundles | FUTURE / NOT EXECUTED |
| GAME03-PLT-08 | Unsupported screen reader OS API and WebGPU HDR output fail safely without fake parity | FUTURE / NOT EXECUTED |
| GAME03-BEN-01 | 100/1000/10000-node trees layout p50/p95/p99 and worst-case CPU measured | FUTURE / NOT EXECUTED |
| GAME03-BEN-02 | 1/10/100k grapheme text with emoji CJK Arabic bidi measures shaping and cache | FUTURE / NOT EXECUTED |
| GAME03-BEN-03 | 1/4/16 atlas pages and variable font scales measure glyph cache pressure and VRAM | FUTURE / NOT EXECUTED |
| GAME03-BEN-04 | Locale switch and text scaling 10/100/1000 times check focus/reflow deadline | FUTURE / NOT EXECUTED |
| GAME03-BEN-05 | 100k inventory virtualization tests hit-test and scroll anchor correctness | FUTURE / NOT EXECUTED |
| GAME03-BEN-06 | 60-minute UI resize gamepad focus and font hot reload soak measures leaks | FUTURE / NOT EXECUTED |
| GAME03-BEN-07 | SDR/HDR screenshot and headless rect oracle compare rendered quality with tolerances | FUTURE / NOT EXECUTED |
| GAME03-BEN-08 | Actual keyboard-only and gamepad user tasks record completion and accessibility blockers | FUTURE / NOT EXECUTED |

## Evidence gates before any real approval
- **Unit/property:** semantic widget types/lifetime, layout constraint cycles/rounding, UAX#9/14/29 golden segmentation/bidi, typed CLDR message formatting, focus navigation spatial/geometric tie-breaks, safe overflow and CAS migration.
- **Integration:** GFX-07 unjittered HDR/SDR camera/display composition, TWO-01 TextRunDraw/glyph atlas/fences/Canvas clip, GAME-01 InputActionFrame/PlayerSeat, GAME-02 capability-checked view models/action intents, DATA-02/03/04/05 asset/provenance/rights/CAS/cook, AUD-04 captions only, CORE-03/04 work/time boundaries.
- **Accessibility:** actual WCAG 2.2 applicable checks for keyboard, contrast, focus, reflow, target size, alternate pointer/drag, OS screen-reader platforms; real human assistive tests rather than certification by documentation.
- **Language corpus:** original UTF-8/Unicode 18 Latin/ABNT2, Arabic/Hebrew RTL mixed strings, Hindi/Indic conjuncts, Japanese/Korean/Chinese, Thai line break, emoji ZWJ, variable fonts, Noto fallback original rights. No private usernames or copyrighted game scripts copied.
- **Fuzz/adversarial:** malformed OpenType font tables, bidi override, unsafe rich text/HTML/CSS, XML external entity, huge nested style/layout, weird CLDR plural, pointer capture/IME stale, GPU generation UAF and source file traversal.
- **Portability:** Windows/Linux/macOS actual adapters, headless semantic oracle, future Web browser capability with no false JavaScript/DOM parity, font and ICU data packages per target and verified notices.
- **Performance:** layout/shaping/raster/cache/focus/retained tree CPU p50/p95/p99/max, GPU glyph/atlas/clip cost and VRAM, locale switch/text scale invalidation, soak memory. Numerical thresholds TBD after baseline hardware.
- **Required Evidence Bundle:** original test fixtures with rights, Git base/head hashes, exact compiler/library/font/ICU data versions, build command/target, screenshot/color device calibration, CPU/GPU traces, fuzz/sanitizer, accessibility reports, failure/correction/recovery and pt-BR audit. **None collected in this P00 research.**

All 128 cases remain FUTURE / NOT EXECUTED, with no pass/fail or runtime performance claims.
