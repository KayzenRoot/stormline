# GAME-03 — UI Layout, Unicode Text, Localization, HUD and Accessibility Benchmark Protocol

**P00 RESEARCH ONLY | Issue #216 | WO NLE-P00-WO-002-GAME-03 | Date 2026-11-15.** No widgets/render code, actual fonts, display screenshots, keyboard/gamepad/IME devices, localization runtime, CPU/GPU benchmark or user test. Numbers below are **prospective workload configurations**, never measured results.

## Core research proof obligations
1. Can original game UI support reusable Button/Text/Container/Progress/Dialog/TextField and HUD without a second 2D renderer, using TWO-01 draw and GFX-07 unjittered SDR/HDR output?
2. Does one selected Yoga/RmlUi/owned layout strategy meet responsive multi-view/multi-locale/min-max/safe-area/large-text criteria with bounded time and memory? Do not double-adopt Yoga/RmlUi.
3. Does HarfBuzz + FreeType (and alternate HarfBuzz raster/msdfgen) reproduce Unicode18 UAX#9 bidi, #14 line break, #29 grapheme behavior and Arabic/Indic/CJK/emoji font fallback with safe source/license provenance?
4. Can ICU79.1/CLDR49 and constrained MessageFormat/ICU MF2 feature gating format plural, number, date/unit, BCP47 fallback, typed interpolations with bidi isolation and no executable markup?
5. Can GAME-01 gamepad/pointer/touch/keyboard action routing and GAME-03 actual focus, modal navigation/IME and accessibility semantics work in split-screen/native/Web without input leaks or focus traps?
6. Are untrusted font/markup/locale content, source CAS/permissions, private game data and OS accessibility APIs handled safely, while HUD and text CPU/GPU budgets remain sustainable?

## Original fixture design (FUTURE ONLY)
- **UI-GOLDEN:** original six-widget main menu, ARPG health/mana HUD, inventory (100/1000/100000 items virtualization), tooltip, split-screen menu, cutscene caption and modal focus/recovery task, with stable NodeIds.
- **LAY-GOLDEN:** viewport 640x360, 1280x720, 1920x1080, 3840x2160, 21:9 ultrawide, portrait and split-screen profiles, DPI 1.0/1.25/2/3, user text scale 100–200%, TV-safe offsets and notch margins, explicit logical vs physical dimensions.
- **TEXT-GOLDEN:** original short/long captions, Arabic/Hebrew with Latin numbers, Hindi/Devanagari, Japanese/CJK, Korean/Thai, accents, ZWJ emoji and RTL spoof/adversarial isolates, equal semantic string/expected grapheme-shape/oracle hash.
- **FONT-GOLDEN:** separately license-reviewed/attributed exact Noto font asset files with OFL 1.1 and reserved names, plus original custom shape fonts if available. **No actual font is bundled in P00.**
- **I18N-GOLDEN:** pt-BR/en-US/ar-EG/fr-FR/ja-JP messages with typed plural/gender/select/date/unit/amount, long-translation expansion and missing-key fallback using pinned CLDR49/Unicode18, with original translator/source rights.
- **INPUT-GOLDEN:** GAME-01 recorded action frames and gamepad D-pad/pointer/IME events, two PlayerSeats, invalid/stale pointer/focus, keyboard-only tasks and accessibility focus semantics.
- **SEC-GOLDEN:** malicious OpenType/rich text/nested UI/oversized localization placeholder/deceptive bidi, path/URL font import and private data access probes; no real personal user text copied.

## Prospective workloads
| Workload | Proposed matrix | Required evidence |
|---|---|---|
| Widget/layout | 100/1000/10000 nodes, 1/4/16 dirty subtrees, 1/8/32 style changes | full vs incremental layout CPU p50/p95/p99/max, allocations, rect oracle/overlap/clip error |
| Unicode text | 128/1024/10000 graphemes; Arabic, Indic, mixed LTR/RTL, emoji ZWJ and CJK | shaping+segmentation+break p50/p95/p99, glyph/fallback correctness, ICU/HB/FT version |
| Raster quality | 10/12/16/32/64/128 px hinted grayscale vs optional MSDF | visual golden error/edge/aliasing at target displays, atlas memory and CPU/GPU cost, fallback |
| Glyph cache | 1/4/16/64 atlas pages, font variants/axes, repeated locale switch | cache hit/eviction, stale UV events, GPU upload bytes, renderer fence correctness |
| Dynamic HUD | 1/2/4 players, 120Hz gameplay ticks, 60/120 FPS presentation where supported | GAME-01→focus→draw input latency, no duplicated intent, UI frame CPU/GPU cost |
| Responsive | desktop 16:9, 21:9, portrait, 4K, split-screen, UI scale 100–200% | clipping, focus visible/scroll, safe area, layout stability and text legibility |
| Accessibility | keyboard/gamepad/touch/one-handed, high contrast/reduced motion | user task completion, focus order, actual assistive-reader compatibility (if testable) |
| Localization | 100/1000 messages, plurals/date/number, locale switch 1000x | formatting correctness, cache invalidation, memory/CPU, fallback/unsafe markup |
| Malicious content | deep nodes/styles, bidi override, bad font, huge placeholder | parse CPU/memory/stack quota, no external network/file read, no crash/secret leak |
| Portability/soak | Win/Linux/macOS, headless Web experimental, 60min UI resize/focus/reload | executable/version/rights proof, RSS/VRAM leak, input focus receipts, GPU loss safety |

## Measurement methodology
- Pin base/head SHA, compiler/CMake, chosen layout library exact tag, HarfBuzz/FreeType/ICU/CLDR/font asset version+license/byte hashes, GPU driver/display, DPI, locale, input/gamepad and OS/browser/CPU/GPU capabilities and power state.
- Separate **headless geometric/text oracle** (no screenshot) from actual GPU screenshot. Compare RGB/linear/HDR output after GFX-07 transform with calibrated render/capture; avoid proving HDR from internal FP16 buffer.
- Profile stages separately: tree diff, style resolution, text segmentation/bidi/font fallback/shaping, line break/intrinsic measure, layout, glyph raster/cache, TWO-01 upload/draw and GFX-07 display pass; report CPU/GPU p50/p95/p99/max, sample size, confidence, allocations and GPU timing availability. First cold cache and warm cache distinct.
- Run input/IME/focus task trails, error receipts and visual focus observation. Accessibility cannot be established with only automated pixels; real representative users and assistive device/OS screen reader testing where authorized.
- Security corpus fuzz typography/markup/locale and perform sanitizers before declaring safe; recognize platform font parser risks, cross-origin Web font restrictions and pointer capture states. No malicious data run during this research.
- Numerical UI budgets, font atlas capacity, minimum supported accessibility hardware and target locale count are UNDECIDED until actual minimum hardware, display device and product DoD are approved. No claim of 60 FPS, zero reflow, universal language support, WCAG certification or better-than-Unreal UI.
- Evidence bundle must contain commands, raw traces/screenshot captures, failures/corrections, license/font rights, review in pt-BR and actual CI; current P00 has **NONE** of runtime evidence.
