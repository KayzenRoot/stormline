# Research Work Order — NLE-P00-WO-002-GAME-03

**Date:** 2026-11-15 | Research issue **#216** | Future implementation issue **#59 OPEN/BLOCKED**  
**BASE main:** `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1` | **P00 DOCUMENTATION ONLY.** Research risk LOW; future native UI/font/image parsing, accessibility/security and color-integrity risk ELEVATED. Release class UNDECIDED; engine code license NLE-D009 OPEN.

**RESEARCH PR #217 APPROVED/MERGED:** [PR #217](https://github.com/KayzenRoot/stormline/pull/217), final audited HEAD `dbd6b3e3d13513dd83c81f1f5168fc1d936a0b5e`, [Docs Validation #43703637595](https://github.com/KayzenRoot/stormline/actions/runs/43703637595) SUCCESS job #132779928220, pt-BR objective audit comment #6892914372 APPROVED documentary-only; normal squash main `9dc38f439a27f90b8e636f2202a50df044727dac` and main readback verified. Separate checkpoint PR requires its own CI/audit/squash/main readback. 128 future tests NOT EXECUTED, coding #59 OPEN/BLOCKED.

## OBJECTIVE
Deeply research the Stormline-owned Game UI, Text & Localization semantic tree, widgets/HUD, responsive layout with DPI/safe areas, Unicode 18 shaping/segmentation/bidi/line break, HarfBuzz+FreeType raster/font fallback, ICU79.1/CLDR49 and controlled MessageFormat2/locale packaging, GFX-07/TWO-01 rendering ownership, GAME-01 device/focus/IME, GAME-02 typed scoped data bindings/authoritative action intents, text/font/translation asset rights, privacy/denial, real future test/benchmark/CI plan.

## CONTEXT
GAME-02 research issue #212 and PR #213 merged; checkpoint PR #214 and readback closeout PR #215 merged/readback, latest main `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1`; checkpoint shows **40/80 research documented (50%)**, 40 pending, 0 runtime modules implemented. All **80** coding packets remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. GAME-03 is catalog order 41, required GFX-07 and TWO-01 dependencies only researched/PROPOSED, not implemented. Future coding issue #59 OPEN/BLOCKED; next GAME-04 catalog order 42 coding issue #60 OPEN/BLOCKED.

## SCOPE
Exactly eight **new Markdown files**:
1. [Architecture](../architecture/game-03-ui-text-localization.md).
2. [ADR-0044 PROPOSED](../adr/0044-game-03-engine-owned-ui-semantic-tree.md).
3. [Official technology/license/standards matrix](../research/game-03-ui-text-technology-license-matrix.md).
4. [Typed semantic API/contracts](../contracts/game-03-ui-text-localization-api.md).
5. [Exactly 128 FUTURE acceptance cases](../testing/game-03-acceptance-matrix.md).
6. [Reproducible UI/text/i18n/accessibility benchmarks protocol](../research/game-03-ui-text-benchmark-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-03.md).
Create research #216 and branch from exact main, research PR Draft; verify exact-final-HEAD Docs Validation + scoped pt-BR audit, normal squash/main readback. Then **independent checkpoint PR** changes only checkpoint/backlog/GAME-03 research_status in registry and this WO/Evidence Bundle; own exact-final-HEAD CI/audit/normal squash/main readback. Close research #216 only after checkpoint readback and preserve all implementation blocks.

## OUT OF SCOPE
All actual engine C++/Rust/JS/Web UI, GPU Canvas/glyph implementations, font files, ICU data, dependency installation, bindings, third-party assets, code generated from web pages, game inputs, runtime locale formatting, OS screen-reader adapters, tests/benchmark/fuzz/ASan, deployed build, screenshot, UI game, paid services/CI, global HTML/CSS/JavaScript parser, native keylogging/clipboard access, arbitrary URL/font import, reimplement GFX-07/TWO-01/GAME-01/GAME-02, refactor old files, modifying coding issue #59, authorizing Zcode or jumping to GAME-04 before checkpoint approval.

## FILES/SOURCES TO READ (canonical order)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/GAME-03.md` > `docs/architecture/gfx-07-camera-color-postprocessing.md` + `docs/contracts/gfx-07-camera-color-api.md` > `docs/architecture/two-01-renderer-canvas.md` + `docs/contracts/two-01-canvas-api.md` > `docs/architecture/game-01-input-control-mapping.md` > `docs/architecture/game-02-gameplay-scripting-api.md` > `docs/architecture/aud-04-music-dialogue-cinematic-audio.md`. Official upstream sources and licenses linked in matrix.

## REQUIREMENTS
GOV-001..005, owner NLE-D001..020 decisions as relevant (do not override APPROVED, NLE-D009 engine license OPEN), NLE-D013 do not claim v1 released until DoD, NLE-D014 2D/2.5D/3D/Web, NLE-D015 authorized AI/CLI/MCP parity, NLE-D016 80 modules complete indexed catalog, NLE-D017 Windows/Linux/macOS + planned Web, NLE-D018 solo governed autonomy, NLE-D019 coding WO packets prewritten but blocked, NLE-D020 all coding blocked. Catalog acceptance: **"UI gamepad/mouse, legibilidade, foco e internacionalização."** Not achieved by documentation.

## ARCHITECTURE RULES
- GAME-03 owns only semantic game widget/focus tree, layouts, locale/text shaping/accessible metadata, immutable UI draw intent. **TWO-01** owns Canvas/glyph atlas/draw/clips and GFX-03 GPU fences. **GFX-07** owns output camera/unjittered UI, tone mapping/HDR/SDR/display transform; no duplicate compositor.
- **GAME-01** owns device/actions/InputActionFrame; GAME-03 owns actual widget/modal/IME focus and returns typed InputFocusRoute; **GAME-02/GAME/NET** owns read-only authorized game data and game-state authority, never arbitrary eval/direct UI gameplay mutations.
- **DATA-01/02/03/04/05** owns safe font/catalog import, asset rights/provenance, stable IDs, CAS and cookbook packaging; no direct host paths or remote font/assets.
- Layout single authority: Yoga MIT focused calculator candidate, RmlUi MIT full framework comparator; both are **NOT** auto-selected together; choose on tested ownership/layout/performance/accessibility evidence, exact pin and rights.
- Text: HarfBuzz Old MIT + per-file notices shapes, FreeType 2.15.0 FTL or GPLv2 selected license (not dual obligations silently mixed), ICU79.1 Unicode-3.0 + third-party notices/CLDR49, Unicode18 UAX#9/#14/#29, BCP47 and optional MessageFormat2 stable spec but ICU API preview caveat. Noto fonts OFL 1.1 are separate licensed assets; no font imported. MSDFgen MIT and Skia BSD3 comparator only.
- Bidi isolation/typed plural/date currency placeholders; no HTML/JS/CSS/script/unsafe rich markup or font-file attack path. Constrain source node/markup depth, invalid RTL control, layout recursion, glyph atlas CPU/GPU budgets. Text/IME/password privacy and safe focus restore after invalid node/locale/viewport changes.
- Accessibility by semantic roles/labels/focus, keyboard/gamepad/pointer alternatives, text scale, reduced motion, high contrast; WCAG2.2 is reference only, no screen reader/assistive hardware certification until native/Web/user tests.
- Latency/UI quality targets and font asset choices remain UNDECIDED. No actual throughput claim; no runtime. All plans remain PROPOSED.

## CONSTRAINTS
P00 docs only. No source, backend/SDK/font install, renderer, export, test, benchmark, scanned library or adoption. Preserve approved ADRs and full user Source Pack. Zero mandatory paid CI, no external reviewer, no ruleset bypass, no force push. Unknown licensing/brand/SDK/persistence/security claims must remain undecided. New research must not unlock any implementation. Context Lock STALE upon main/checkpoint/approved decision changes.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 new Markdown docs, correct links and Source Pack hierarchy, no code/assets/dependencies.
- [ ] ADR-0044 PROPOSED; one engine-owned semantic UI tree, no duplicate Canvas/HDR/OS input/gameplay authority; typed contract API and privacy/security.
- [ ] Compare Yoga vs RmlUi, HarfBuzz+FreeType (separate shaping/raster), ICU/CLDR/Unicode18/MessageFormat2, SVG/MSDF/Skia optional and actual license/asset rights with credible current sources.
- [ ] Correct responsive layout, TV safe area/viewport/DPI, GFX-07 HDR/SDR unjittered composition and TWO-01 actual glyph/atlas lifetime, focus/IME GAME-01 and data/action GAME-02 boundaries.
- [ ] Multi-language RTL/Indic/CJK/emoji/font fallback, grapheme/line break/locale plural/date/number/units/Bidi-injection rules and explicit fallback, plus accessibility WCAG2.2 caveat.
- [ ] 128 FUTURE cases, ALL NOT EXECUTED, reproducible benchmark protocol with real-target proof gates and explicit UNDECIDED numerical budgets.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS, pt-BR objective audit APPROVED, normal squash and main readback, no known HIGH/CRITICAL.
- [ ] Separate checkpoint PR own exact-final-HEAD Docs Validation/audit/squash/readback; exactly **one registry difference** GAME-03 `research_status` → `RESEARCH_DOCUMENTED_ADR_PROPOSED`.
- [ ] Final **41/80 researched (51.25%)**, 39 pending, 0 runtime, all 80 code WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`, code issue #59 OPEN/BLOCKED. Next GAME-04 #60 only documentary research after readback.

## TESTS
Only actual GitHub **Docs Validation** of Source Pack/local links, module DAG, WO registry and Zcode selector blocked behavior. **128 FUTURE UI/runtime tests NOT EXECUTED**, no layout solver/font/ICU/GPU/text/IMEs/accessibility real user/browser runs, fuzz/sanitizers, native/Web/headless render binaries or measured benchmark.

## DELIVERABLES
Research issue #216 and eight scoped docs; research PR with observed CI/pt-BR audit/normal squash/readback, separate checkpoint PR with independent gates and correct registry delta, final Evidence Bundle/readback documented and research issue close. Future implementation packet #59 remains open/blocked.

## REVIEW FORMAT
APPROVED / CORRECTION REQUIRED / BLOCKED in pt-BR; base/HEAD SHA, changed files, canonical fingerprints, licence/font rights/source, GFX/TWO/GAME authority, no unsafe UI markup/IME/PII/screen reader claims, 128 tests not run, CI actual workflow/jobs, security/privacy/rollback/risk, HIGH/CRITICAL and proposed registry/checkpoint delta. NO assertion "completed" without objective evidence.

## STOP CONDITION
STALE main/critical source pack, unverified data/font license, unsafe HTML/JS/source import, privacy leak, invented performance/accessibility, duplicate rendering authority, unexpected code, failing Docs Validation, unsafe registry modifications, unmergeable ruleset or known HIGH/CRITICAL => CORRECTION REQUIRED on same WO/PR or BLOCKED. Do not start GAME-04 before GAME-03 checkpoint closeout.

## CONTEXT LOCK — Git blob hashes at base (not file SHA-256)
BASE `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1`.
- Checkpoint `12de8a693bc94180179d7956767b7d1dd7c38242`
- Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Backlog `4c440ceb0b54ea60fa54b6be91fe707056eafe1d`
- Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Registry `75f2fdd403f1bfc5a41d5facf3e62108e73d9cf0`
- Future coding WO `da1409dd5968df9be67d0b98d084aa7051dc9a9e`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- GFX-07 architecture `2f8ead7b021f8d68e256599f2205cfacc26de85c`; contracts `07de1be322a9b1838be8d0efb8279ac43d78ad55`
- TWO-01 architecture `5faa6b919d882416e8ae492631c3144fa6efe294`; contracts `0dbc1312972352ded567c51c8745a22abec39eff`
- GAME-01 `5f86d817a26a7142496788963453caf247dbfa50`
- GAME-02 `c5429cabdf14bc1e7dc8b3eac11e77274dc51776`
- AUD-04 `8104ddac546ab5133372859e71e771b66750ccf0`

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-03.md). Research PR #217 exact-final-head Docs Validation, pt-BR audit, normal squash and main readback complete. Separate checkpoint PR remains pending its own gates.
