# QA-02 — Future Visual/Audio/Headless Test Reproducibility & Cost Benchmark Protocol

**2026-11-16 | FUTURE PROTOCOL ONLY, NO MEASUREMENTS.** Research #345 | future code #91 BLOCKED | formal QA-01+GFX-03 ONLY | main base `3ffd1c76092c65a355a57ce2e713291dc83d2a72`. No original samples/binaries, GPU capture, CTest, browser screenshots, audio waveform, p50/p95/p99 or hardware benchmark exists today.

## Goal, methodology and environmental lock
Before any future test, owner approves thresholds separately per fixture/test-class (strict invariant, pixel exact, driver tier/perceptual, temporal, offline PCM and accessibility). Record source+GFX-03 graph+shader+DATA cooked snapshot hashes, deterministic seed/fixed tick/event trace and original rights clearances; QA-01 CI head/job/runner/software versions, target platform/backend/software vs real GPU/driver and device generation; camera/DPI/viewport/quality/ICC/gamut/sRGB/PQ/HDR/alpha/MSAA/TAA history, screenshot readback synchronization and waveform sample rate/PCM layout. No legitimate comparison across different unknown profiles.

## Candidate future bench fleet
| Class | Future build/host | Explicit scope of evidence |
|---|---|---|
| QA2-SW-VK | trusted headless Linux x86_64 SwiftShader Vulkan CPU software with pinned version | deterministic 2D/2.5D/3D software subset, **NOT actual NVIDIA/AMD/Intel/Apple GPU evidence** |
| QA2-VK-PC | real Windows/Linux Vulkan hardware owner selected, validation layers where supported | GPU shaders, resource graph, driver tiers, render goldens and device lost |
| QA2-D3D12 | real Windows x64/approved Win ARM D3D12 hardware | native render and UI test only if platform implemented |
| QA2-METAL | real macOS Apple Silicon and Intel conditional | Metal device/generation/capture and font/A11y separate; hosted VM ≠ physical |
| QA2-WEB | real pinned Chromium/Firefox/WebKit browser + HTTPS origin | Playwright WebGPU/WebGL2, screenshot/ARIA/DOM/keyboard, strict browser profile and no unsafe fallback |
| QA2-GFX-HDR | real HDR-capable display/renderer + calibrated capture | PQ/HDR/tonemap color-space metadata and float quantization reference |
| QA2-AUDIO | offline virtual PCM output from future AUD mixer | no speaker/mic, original sine/noise/impulse fixtures, sample clock and multi-channel |
| QA2-ORIGINAL | original authored 2D atlas, 2.5D isometric/parallax, 3D PBR/light/shadows/particles + UI/Unicode | rights-cleared asset lineage, fixed simulation and render snapshot |
| QA2-TRUST | untrusted malformed image/audio/archive/reference, CI fork and cache | no arbitrary script, secret leaks, baseline poisoning or costs |
| QA2-HW-A11Y | owner-approved native Windows/macOS/Linux hardware screen-reader input and color modes | native accessibility test, beyond browser ARIA and image diff |

## Candidate run matrix
| Protocol | Future test target and conditions | Raw artifact and comparison |
|---|---|---|
| QA2-B01 | native C++20 GTest/Catch2/CTest unit fixture and parametrized discovery | nonzero CTest cases/elapsed/JUnit/return codes/source SHA |
| QA2-B02 | deterministic 2D sprites/UI glyphs, alpha, sRGB/ICC with QA2-SW-VK | raw exact/same-stack PNG, reference/golden diff and hashes |
| QA2-B03 | 2.5D isometric tiles/shadows/parallax and camera movement | pass order, depth/alpha hit-areas, expected+actual/diff |
| QA2-B04 | representative 3D PBR material/shadows normal/depth and HDR | linear EXR float, display transforms and semantic masks |
| QA2-B05 | GPU driver family comparisons Vulkan/D3D12/Metal | per-driver calibrated tolerance and metrics, validated hardware receipt |
| QA2-B06 | render graph UAV/alias and fence hazards and GPU device loss | Vulkan validation/GFX-03 typed faults, first failing pass |
| QA2-B07 | temporal antialias/animation/particle input traces | fixed-tick multi-frame history and first mismatch time |
| QA2-B08 | physics/gameplay automated headless loop | state checks and input trace last-good checkpoint |
| QA2-B09 | Playwright Web screenshot/ARIA and browser gameplay end state | per-OS/browser snapshots, viewport/DPR/font/locale, keyboard |
| QA2-B10 | original PCM sine+impulse+silence/peak/spectra on offline mixer | sample rate/FFT/RMS/peak/true peak/correlation/onset |
| QA2-B11 | optional native A11y and Unicode shaping | actual screen reader+focus, layout and contrast with owner |
| QA2-B12 | intentionally changed shader and wrong object id | strict logic mask fail even if SSIM high |
| QA2-B13 | golden baseline update with separate PR and deliberate visual change | authorized expected/actual/diff, old/new SHA and reviewer |
| QA2-B14 | malformed EXR/PNG/WAV, archive traversal and oversized frame | bounded decoder resources and no private files leaked |
| QA2-B15 | artifacts and CI time/bytes/R$0 storage/trusted fork policy | actual usage/retention/cost and redacted evidence |
| QA2-B16 | full real owner QA gate, replay and issue triage | 128 cases actual statuses after implementation, 1.0 DoD separate |

## Statistical and failure protocol
- For renderer comparisons, do not assume a fixed broad threshold: first collect repeated captures under **identical pinned environment** and real GPU driver variation; calibrate and freeze per fixture/tier metrics before using them to accept regressions. Report max absolute, MAE, RMSE, mismatch percent, SSIM with explicit floating `data_range`, edge/flicker score, semantic masks, ICC/color-profile and confidence. Correlated adjacent frames are **not independent samples**.
- For CI cost and compile/test duration measure ≥5 independent runs for median and variability, but do not claim p99 from five summary trials. For temporal jitter/frame sequences capture many time-correlated frames and account for effective sample size. QA-03 owns sustained FPS/VRAM per hardware tiers, not QA-02 implied benchmark.
- Negative test deliberately corrupts source/golden and proves FAIL and fully reproducible replay on same pinned baseline; no automatic reference re-record. Rate of flaky false-positive/false-negative and baseline maintenance cost must be tracked, not tuned solely to reduce red CI.
- Privacy/security/rights: synthetic original fixtures only, no copyrighted media or private screenshots, no out-of-policy telemetry, no paid visual SaaS or GPU cloud; use QA-01 R$0 shared artifact/cache/storage cap and authorized owner device. Hardware unavailable => BLOCKED/UNSUPPORTED rather than software PASS substitution.
- Future `Qa2BenchmarkReceiptV1`: source/fixture+golden SHA, source license and owners, test ID, original scene/camera/event seed and tick, QA-01 exact job and toolchain, backend/GPU-driver/software and OS, metrics+threshold signed approval, before/actual/diff hashes, raw PCM/timing, test first fail frame, a11y/rights, CI cost and pt-BR audit/DoD verdict. P00 none produced.

[128 future cases](../testing/qa-02-acceptance-matrix.md) · [architecture](../architecture/qa-02-functional-visual-test-oracles.md) · [tool matrix](qa-02-test-framework-graphics-audio-license-matrix.md).
