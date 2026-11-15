# EDIT-04 — Reproducible Editor 2D/UI/Tilemap Benchmark and Failure Protocol

**P00 proposal, NOT EXECUTED** | 2026-11-15 | [#264](https://github.com/KayzenRoot/stormline/issues/264), future implementation #71 BLOCKED. No executable engine, editor, CI for native code, target hardware, benchmark result, regression or a11y certification. No runtime p50/p95/p99 claims.

## 1. Measurement purpose and setup
Define the experiment before selecting technology. Pin build Git commit, compiler/optimization, graphics/API backend, OS/kernel/window system, CPU/GPU/VRAM/RAM, driver, DPI/color/HDR, monitor scale, battery/power state, concurrency, locale/font hashes and input source. Windows 11, Linux X11+Wayland, macOS Apple Silicon native are mandatory target families in product direction; Intel OS minima TBD, WebGPU/WebGL2 availability recorded rather than assumed. Profiles LOW/MED/HIGH/WEB set actual hardware and numeric budgets **only after owner approval**.

Two-run warmup and 30 measured controlled samples per fixture candidate, with CPU/GPU timestamp/profiler clock calibration; keep per-run raw traces and aggregate median/p50, p95, p99, min/max, memory highwater, stutter count, missing samples, and 95% CI or explicitly insufficient sampling. Note 30 samples alone estimate p99 poorly: use >=1000 frame/command observations for tail quantiles, not inferred reliability. Alternate baseline/candidate order to reduce thermal/cache bias; rerun on a second machine and 3 seeds. No scoring cherry-pick.

## 2. Signed, original, reproducible fixtures
| Fixture | Corpus / scale | Observation / oracle |
|---|---|---|
| CV-01 | Original sprite project: 500 sprites / 8 layers / 2 texture atlases | Zoom/pan frame CPU/GPU, pixel-art snapping, stable selection hash |
| CV-02 | Canvas source 100k+ sprites with 4 zoom levels and 3 parallax groups | clip/alpha ordering, culling and atlas/resource residency |
| TM-01 | Sparse world 1k/100k/1m occupied tile cells; negative and positive chunk seams | paint 1/100/10k cells, autotiling halo diff, serializer round-trip, memory |
| TM-02 | Multiple original terrain Wang edge/corner variants and animated atlas | deterministic neighbor rule seam/seed and collision activation mismatch |
| UI-01 | 100/1k/10k nested widgets, 3 depth profiles, 4 responsive widths | dirty subtree reflow p95/p99, unsatisfied constraints and focus order |
| UI-02 | Original text: Latin, Arabic, Devanagari, CJK, emoji ZWJ, RTL/mixed bidi, 1/10k glyph runs | shaping/line break, fallback, IME caret, font atlas capacity and rights |
| AN-01 | 100/1k/10k keyframes, 10–100 tracks and 2D flipbook/skeletal candidate | scrub p95/p99, key manipulation determinism, memory, unwanted gameplay cue count=0 |
| RC-01 | Original project with 1k edits, 10 simultaneous UI/CLI/MCP command races and crash windows | revision/hash, stale rejection, journal recovery, error taxonomy and no data loss |
| IO-01 | Malformed original TMX/LDtk JSON, tiled image/font/decompression/path symlink fixtures | parser CPU/heap limit, non-execution, permission denial, no privilege escalation |
| E2E-01 | Actual GUI-only author workflow on empty project and all 3 desktop OS targets | Editor-created project/tiles/UI/timeline/save/reopen/export, replayed command journal, no manually authored project files |

All media/program assets must be original or explicitly redistributable; store digest and license. No third-party copyrighted game sprites, sample fonts or user files. A script must generate sanitized numeric scene specifications for stress fixtures; **GUI-only acceptance must be demonstrated by real editor interaction instead**.

## 3. Operations, thresholds and fairness
- Record frame presentation CPU render / GPU submit / GPU present, actual FPS and p50/p95/p99; editor input-to-preview and input-to-durable-ack histograms; count dropped/stale pick and brush retries. Compare interactive frame against headless plan processing separately.
- Capture brush 1/100/10k-cell edit cost, indirect changed cells, chunks touched, CPU resident+peak/VRAM, undo bytes, save/reopen wall time and semantic digest. Record cold/warm caches separately, trigger deterministic seeds.
- Capture UI reflow with localization, textScale=1/1.5/2, RTL/IME and platform a11y routes; memory/time per glyph/WidgetId, layout-loop errors and focus graph correctness.
- Stress 100 switches between edit and EDIT-07 isolated preview with GPU device loss, canceled strokes, source revision race, disk-full and process kill at every DATA-04 journal phase. Compare last-good/readback/undo digest and pending physics owner acknowledgments.
- Benchmark format includes `experiment_id`, `git_sha`, `schema_versions`, `device_profile`, `seed`, `fixture_sha256`, `command_id`, `iteration`, `actual_cpu_ms`, `gpu_ms_or_unavailable`, `peak_rss`, `vram_or_unknown`, `input_latency_ms`, `result_status`, `semantic_digest`, `license_digest`, `trace_id`. Missing GPU timestamp must be marked UNAVAILABLE, not zero.
- Proposed *illustrative investigation triggers*, not accepted SLA: any frame over intended tier budget, >0 silent data loss, >0 unexpected script execution, >0 unapproved writes, >0 unequal source digest after save/reopen, 100% deterministic brush cells for pinned seed. Numeric performance thresholds are deliberately **TBD** pending benchmarking + owner-signed DoD and release class.

## 4. Cross-platform and security test obligations
Windows native DPI, IME, keyboard/gamepad/touch if hardware; Linux X11/Wayland (no absolute global window positioning expectation); macOS Cocoa Apple Silicon with AX and hardened resource permission; browser WebGPU/WebGL2 fallback when runnable, no claim of Web native editor shipping. Screen reader behavior via OS native integration must be checked, not only ARIA Web pattern guidance. Unicode/UAX normative fixture and licensed font packs required.
Fuzz fonts, TMX external entities, LDtk payloads, compressed tiles, SVG scripts and high-rate MCP calls under sanitizer/ASAN/UBSAN or platform alternatives with deterministic fixture/minimization. GPU driver loss and restore exercise GFX owners. No external cloud CI, paid services or sample asset license assumptions.

## 5. Baseline and future reporting
At P00: actual runs **0**, binaries **0**, performance datapoints **0**, confirmed cross-platform UI **0**, future E04 cases **128 NOT EXECUTED**. Baseline conditions and comparison implementation are TBD. Future report must include all reproducible raw results, CIs, negative cases, cost/thermal fairness, competing library options, failure correction, scope gate and owner-defined performance acceptance before claiming superiority.

[Tests](../testing/edit-04-acceptance-matrix.md) · [Technology/license matrix](edit-04-2d-ui-technology-license-matrix.md) · [Contract](../contracts/edit-04-2d-ui-api.md).
