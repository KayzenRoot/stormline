# Evidence Bundle — NLE-P00-WO-002-GAME-03 Game UI, Text & Localization

**STATUS: RESEARCH PR #217 APPROVED/SQUASH-MERGED; FINAL EXACT-HEAD DOCS VALIDATION SUCCESS; SEPARATE CHECKPOINT PR PENDING INDEPENDENT CI/AUDIT/SQUASH/READBACK. NO GAME UI ENGINE.**  
**2026-11-15 | Research [#216](https://github.com/KayzenRoot/stormline/issues/216) | Future code [#59](https://github.com/KayzenRoot/stormline/issues/59) OPEN/BLOCKED | BASE main `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1`.**

## 1. Canonical source and preflight
Last GAME-02 research issue #212, PR #213, checkpoint PR #214, readback PR #215 merged and readback confirmed at main `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1`. Prior state **40/80 research documented (50%)**, **40 pending**, **0 runtime**; all **80** coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. Code #59 OPEN/BLOCKED. Catalog 41, dependencies GFX-07 and TWO-01 are research-only, not code. Source Pack priority checkpoint > Ledger approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS > Catalog/Registry > relevant gfx/two/game docs. Verified blob hashes in [Work Order](../work-orders/NLE-P00-WO-002-GAME-03.md).

## 2. Eight documentary artifacts
1. [Architecture](../architecture/game-03-ui-text-localization.md): owned UI tree, layout, HUD, Unicode shaping/linebreak/bidi, font assets, locale, focus, accessibility, privacy and GFX-07/TWO-01 boundaries.
2. [ADR-0044 PROPOSED](../adr/0044-game-03-engine-owned-ui-semantic-tree.md): one owned semantic UI model, candidate stack not adopted.
3. [Technology/licensing matrix](../research/game-03-ui-text-technology-license-matrix.md): Yoga MIT vs RmlUi MIT; HarfBuzz Old MIT; FreeType FTL/GPLv2, ICU79.1 Unicode-3.0/CLDR49, Unicode18 annexes/MF2, Noto SIL OFL1.1, msdfgen MIT, Skia BSD3, WCAG2.2 guidance.
4. [Versioned semantic contracts](../contracts/game-03-ui-text-localization-api.md): UI tree, node generation, viewport/density, layout/draw, input-focus, text graphemes, font/glyph, locale/message/bidi, accessibility, error/authoring receipts.
5. [128 FUTURE acceptance tests](../testing/game-03-acceptance-matrix.md), NOT EXECUTED.
6. [Reproducible UI/Unicode/HUD performance/quality protocol](../research/game-03-ui-text-benchmark-protocol.md), NOT EXECUTED.
7. [Research Work Order](../work-orders/NLE-P00-WO-002-GAME-03.md) with Context Lock/acceptance/stop.
8. This Evidence Bundle.

## 3. Verified official source references (2026-11-15)
[Yoga](https://github.com/react/yoga), [RmlUi](https://github.com/mikke89/RmlUi), [HarfBuzz Old MIT COPYING](https://github.com/harfbuzz/harfbuzz/blob/main/COPYING), [FreeType dual license](https://freetype.org/license), [FreeType 2.15.0](https://freetype.org/), [ICU 79.1](https://icu.unicode.org/), [ICU Unicode-3.0 license](https://github.com/unicode-org/icu/blob/main/LICENSE), [CLDR 49/50 status](https://github.com/unicode-org/cldr), [MessageFormat2 UTS #35](https://www.unicode.org/reports/tr35/tr35-messageFormat.html), [UAX9](https://www.unicode.org/reports/tr9/), [UAX14](https://www.unicode.org/reports/tr14/), [UAX29](https://www.unicode.org/reports/tr29/), [Noto SIL OFL](https://github.com/notofonts/noto-fonts/blob/main/LICENSE), [msdfgen](https://github.com/Chlumsky/msdfgen), [Skia BSD3](https://github.com/google/skia/blob/main/LICENSE), [WCAG 2.2](https://www.w3.org/TR/WCAG22/). No library/font/sample code/data adopted, licensed for shipment, imported or tested.

## 4. Verification ledger (actual observed only)
| Gate | Current status |
|---|---|
| Research issue #216 / dedicated branch from exact baseline | OBSERVED |
| Exactly 8 new scoped Markdown files / research PR diff | [PR #217](https://github.com/KayzenRoot/stormline/pull/217) Draft changed-file readback: exactly eight new Markdown documents; no runtime/code/font/SDK/CI changes. |
| Initial Docs Validation (prior HEAD) | [Run #43703576222](https://github.com/KayzenRoot/stormline/actions/runs/43703576222) SUCCESS on pre-Evidence-update HEAD `6c1038481188f58f29a028085085b2b1e6e77480`, job #132779747216; Source Pack/local links, taxonomy/dependency DAG, WO registry and Zcode blocked selector all SUCCESS. This update creates a new HEAD, requiring own exact-final-head CI. |
| CodeQL/SonarCloud/Socket extra security scanners exact HEAD | NOT VERIFIED |
| Game UI, layout or widget runtime implemented | NO |
| HarfBuzz/FreeType/ICU library installed, font imported or translation asset cooked | NO |
| Native/Web/headless screenshot or GPU output executed | NO |
| 128 FUTURE acceptance scenarios | NOT EXECUTED |
| Layout/shaping/atlas/performance/IME/user accessibility benchmark | NOT RUN |
| Fuzz/ASan/UBSan/TSan or hostile font/markup exploit test | NOT RUN |
| Objective pt-BR research audit | APPROVED documentary-only [comment #6892914372](https://github.com/KayzenRoot/stormline/pull/217#issuecomment-6892914372), no known HIGH/CRITICAL scoped docs. |
| Research PR squash/main readback | Normal squash main `9dc38f439a27f90b8e636f2202a50df044727dac`, main readback verified. |
| Separate checkpoint PR CI/audit/squash/readback | PENDING own exact-head Docs Validation/pt-BR objective audit/normal squash/main readback. |

## 5. Risk register and negative evidence
- **Trust:** hostile font binaries, SVG/markup, malicious locale placeholders/bidi controls, deep recursive layout, hidden external resource fetch, PII from game data into UI/MCP.
- **Glyph lifetime:** stale font/glyph atlas key/device generation, GPU upload fence/UAF, incorrect display color/HDR, text jitter, no honest fallback when font missing.
- **Focus/privacy:** text/IME/password leaking to gameplay scripts/telemetry, modal focus trap, inaccessible keyboard-only menu, gamepad PlayerSeat cross-leak, stale focus after virtualized item removal.
- **Globalization:** wrong complex-script shaping or grapheme segmentation, bidi mixed numbers, malformed CLDR locale chain, unjustified MF2 feature support, unlicensed font embedding and reserved names. ICU79 MF2 implementation preview portions need gate.
- **Per-platform claims:** Web fonts/GPU/IME differ, OS screen-reader accessibility interface not implemented/certified, no actual target screenshot, real 60fps or multi-lingual correctness.
- **Software license:** engine NLE-D009 OPEN; candidate libraries and font binaries separate legal chains. No adoption/pin/ship. Documentation risk LOW; future runtime ELEVATED.
No runtime mitigations are implemented. All **128 tests remain FUTURE/NOT EXECUTED**; no native/Web/headless build, UI screenshots, measured CPU/GPU, font raster, assistive user test or independent high-risk parser proof.

## 6. Proposed checkpoint delta (NOT PROMOTED)
After research PR final exact-HEAD CI/audit/squash/main readback and separate checkpoint PR own exact-HEAD CI/audit/squash/main readback, update **ONLY GAME-03** `research_status` `RESEARCH_PENDING` → `RESEARCH_DOCUMENTED_ADR_PROPOSED`. Result **41/80 research documented (51.25%)**, **39 pending**, **0 runtime modules**. All **80 coding packets** still `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; #59 OPEN/BLOCKED, ADR-0044 PROPOSED, release class UNDECIDED. Next GAME-04 #60 research only after checkpoint approval. No Zcode implementation permission.

## 7. Objective audit output
pt-BR APPROVED/CORRECTION REQUIRED/BLOCKED with base/head, exact eight-file diff, source fingerprints, licenses and font asset rights, Unicode/CLDR/MF2 status, GFX/TWO/GAME ownership, untrusted input/IME/privacy and accessibility, actual CI steps, future tests NOT RUN, high/critical risk review and separate checkpoint readback. No statement "completed" without verifiable evidence.

## 8. Verified research PR result
- [Research PR #217](https://github.com/KayzenRoot/stormline/pull/217) exactly 8 Markdown docs, BASE `eabf7cd8420e72c017a0e2aa3fdfe0eb0b309dd1`, final audited HEAD `dbd6b3e3d13513dd83c81f1f5168fc1d936a0b5e`, [Docs Validation #43703637595](https://github.com/KayzenRoot/stormline/actions/runs/43703637595) SUCCESS job #132779928220. Objective pt-BR audit #6892914372 APPROVED documentary-only.
- Normal squash main `9dc38f439a27f90b8e636f2202a50df044727dac`, readback verified. All 128 cases FUTURE/NOT EXECUTED; no code/fonts/assets/backend/bench or adopted SDK. Separate checkpoint PR still needs its independent exact-head audit/readback before canonical tally is promoted.
