# QA-02 — Exactly 128 FUTURE Functional, Golden, Headless and Audio Test Cases (Q02-T001..Q02-T128)

**2026-11-16 P00 DOCUMENTARY RESEARCH; NO ENGINE OR QA-02 TEST RUN.** Research [#345](https://github.com/KayzenRoot/stormline/issues/345), future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED, base `3ffd1c76092c65a355a57ce2e713291dc83d2a72`. Formal dependencies **QA-01 + GFX-03 ONLY**, their ADR-0075 and ADR-0016 PROPOSED, all 80 implementation WOs BLOCKED, no C++ binary or GPU/audio tests. **EXACTLY EIGHT groups of sixteen cases, Q02-T001..Q02-T128 all FUTURE/NOT EXECUTED, no PASS.**

## Gates for future software execution
- Stable content-addressed original rights-cleared 2D/2.5D/3D/Web scenes, actor hierarchy, CPU fixed-step seed and input trace, rendering GFX-03 graph pass/attachment device epoch, and target actual backend/driver and software flag. Missing raw SHA/signed baseline approval/tolerance => fail/blocked, never implicitly generate goldens.
- Strict C++ state and graph invariant tests first, then same-software raster exact goldens when meaningful, then driver-scoped color-correct tolerant pixel/SSIM/edge checks with strict semantic UI geometry IDs and approved thresholds; no SSIM success to override black frame, text, geometry or wrong state.
- Web Playwright screenshot/ARIA/semantic gameplay tests require browser OS/version, DPI, font, locale and reduced motion fixed; no cross-platform screenshot acceptance without driver+browser tier proof.
- Audio uses original offline PCM waveform metrics with sample clock/rate/bit depth/channel specified, never copyrighted music or microphone content, and compares beyond RMS to timing, spectral and clipping when sample-exact not appropriate.
- Test runner must be actual QA-01 CTest/GTest and nonzero expected count with JUnit/test logs, not Docs Validation. Headless software SwiftShader is not real GPU; Chromium unsafe SwiftShader flag not used on untrusted content.
- Real benchmarks and security/QA-05 physical GPU/a11y coverage are later owner-separated. All P00 matrix rows **design scenarios only**, hardware costs/fixtures and ADR not ratified.
- Negative malicious file and baseline tampering tests require sandbox/rights/redaction, no arbitrary shell/ML download, no unapproved fee. Baseline mutation is a separate owner-audited PR with before/after and hashes.
- Every PASS future must link actual head SHA/job/fixture hashes/backend/driver/readback/output and reviewer, first frame/tick failure replay; no global skips and no HIGH/CRITICAL.

## Group 1 — UNIT-STATE-DETERMINISM

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T001 | Unit test discovery through QA-01 CTest executes more than zero actual tests | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T002 | GoogleTest gtest_discover_tests cross-compile requires emulator or explicit alternative | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T003 | Fixed tick simulation replay creates stable world state hash on same profile | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T004 | RNG seed and algorithm pinned with repeatable shuffled-order fixture | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T005 | Stable ActorId and scene hierarchy canonical serialization roundtrips | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T006 | Event queue input timestamp ordering and cancel semantics deterministic | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T007 | Error codes for missing asset/scene/hardware are typed and nonzero | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T008 | Scene fixture manifest SHA and source revision unchanged during run | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T009 | Deterministic locale decimal and timezone invariants maintained | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T010 | Test clock frozen despite OS wall clock and DST changes | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T011 | Float rounding mode and CPU instruction set included in test profile | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T012 | Transient race scheduling is not silently asserted deterministic | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T013 | Unit parameterized test cases preserve unique CTest IDs and logs | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T014 | Property-based invalid scene graph cycle produces predictable rejection | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T015 | Reproduction seed and first failing simulation tick captured for failed test | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |
| Q02-T016 | Test skipped/all-xfail or timeout cannot report functional suite PASS | QA-01 actual pinned CTest nonzero unit run, seed/source/fixture state and first failure | FUTURE / NOT EXECUTED |

## Group 2 — RENDER-GRAPH-OFFSCREEN

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T017 | GFX-03 render pass graph cycle rejected with stable error oracle | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T018 | Read-before-initialization of transient target flagged by render graph | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T019 | Resource aliasing lifetime overlap reported before golden capture | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T020 | GPU fence/timeline synchronized before CPU staging readback | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T021 | Stale device generation invalidates older color/depth attachments | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T022 | 2D sprite alpha premultiplication reference golden in pinned software backend | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T023 | 2D tile atlas seams and pixel snapping with camera zoom compared | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T024 | 2.5D isometric depth/layer order and alpha shadow compositing validated | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T025 | 3D PBR material normal roughness and texture binding test captured | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T026 | 3D direct/indirect lighting and shadow map oracle remains semantics-bound | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T027 | Depth reversed-Z, handedness and origin convention validated in pass readback | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T028 | MSAA and TAA history seed/profile captured with golden image | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T029 | Texture ASTC/BC compressed vs decoded reference compare per approved tier | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T030 | RenderGraph debug capture GPU-AV warnings cannot be mistaken for zero issues | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T031 | Offscreen SwiftShader Vulkan software result tagged software not physical GPU | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |
| Q02-T032 | GPU device loss/recovery interrupts capture without reusing invalid target | GFX-03 actual graph readback fence/resource generation + software vs physical renderer capability receipt | FUTURE / NOT EXECUTED |

## Group 3 — GOLDEN-COLOR-COMPARATOR

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T033 | Exact PNG image hash check only for identical deterministic render environment | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T034 | Golden registry carries fixture/version/source/baseline approval digest | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T035 | Original image and current rendered image dimensions equal or explicit reject | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T036 | Linear RGB and display sRGB transfer conversion performed before compare | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T037 | HDR linear EXR floating data_range declared to SSIM comparator | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T038 | ICC profile/color primaries mismatches produce typed COLOR_SPACE_UNKNOWN | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T039 | Premultiplied versus straight alpha compositing yields correct oracle | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T040 | Per-channel MAE RMSE and maximum difference included in report | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T041 | Mismatch fraction and absolute max pixels policy bounded by fixture | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T042 | SSIM value alone cannot override missing scene object or text | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T043 | Perceptual metric disabled when unlicensed model weights unknown | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T044 | Semantic mask validates text boundaries and layering independent of SSIM | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T045 | Anti-alias/mipmap/driver jitter tolerance scoped to named GPU driver tier | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T046 | Incorrect baseline backend/OS/driver metadata rejected before diff | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T047 | Heatmap expected and actual hashes tied to source and CI attempt | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |
| Q02-T048 | Intentional baseline update requires separate owner-approved review | approved golden fixture, color space and driver class, pixel/SSIM/hard semantic data and heatmap | FUTURE / NOT EXECUTED |

## Group 4 — TEMPORAL-SCENES-GAMEPLAY

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T049 | Frame sequence capture uses fixed-step tick with deterministic input trace | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T050 | Temporal antialias jitter history reset after scene camera cut | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T051 | 2D character animation interpolation and keyframe hitbox checked | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T052 | 2.5D layer/parallax transition stable with moving camera and depth | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T053 | 3D skeletal pose animation time and skinned geometry regression captured | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T054 | Particle/VFX seeded spawn order and bounded emission verified | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T055 | Flicker/glitch detection on repeated static scene frame sequences | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T056 | Physics collision/contact ordering stable within documented oracle | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T057 | Gamepad reconnect or disconnect cancels held semantic actions | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T058 | Mouse keyboard and touch pointer input replay respects window focus | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T059 | Player navigation/farm/quest fixture deterministic objectives assert state | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T060 | Scene save/load last-good state survives headless playtest restart | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T061 | Timewarp/pause/resume preserves simulation tick and UI animated state | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T062 | Playtest terminated mid-save leaves prior world snapshot intact | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T063 | Cross-compiler replay differences reported by independent source/profile | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |
| Q02-T064 | First failing simulation tick and screenshot frame recovered by replay bundle | real deterministic fixed-tick scene and gameplay replay with source hash and first-frame/tick trace | FUTURE / NOT EXECUTED |

## Group 5 — AUDIO-OFFLINE-FIXTURES

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T065 | Original synthetic 440 Hz sine PCM appears at approved frequency/bin | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T066 | Impulse onset and latency sample offset bounded by mixer graph policy | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T067 | Stereo panning left/right energy balance preserves channel orientation | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T068 | Silence fixture produces near-zero RMS and DC offset within strict floor | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T069 | Gain/mute transitions produce no unexpected channel bleed or glitch | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T070 | Fixed sample rate and bit depth conversion records resampler identity | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T071 | Peak and true-peak clipping exceedance produces AUDIO_MISMATCH | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T072 | Loop boundary crossfade continuity avoids impulse click | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T073 | Pitch shift/time stretch reference bounded by approved spectral oracle | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T074 | Room audio/spatial attenuation fixture distance scale stable | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T075 | Audio async buffer underrun detected as explicit failure not silence pass | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T076 | Audio stream mixing with fixed tick maintains sync across frame rates | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T077 | Compiler SIMD output tolerance scoped to PCM rate and float precision | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T078 | Loss of audio device does not block headless offline PCM test | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T079 | Captured waveform and reference content hashes plus copyright rights verified | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |
| Q02-T080 | Unapproved copyrighted song playback/sample recording never enters CI | actual offline original PCM buffer with declared sample rate/channel and waveform metrics | FUTURE / NOT EXECUTED |

## Group 6 — WEB-A11Y-UI-GAME

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T081 | Playwright Web screenshot baseline segmented by browser and OS | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T082 | Web snapshot fixes viewport DPR font pack locale and animation state | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T083 | Playwright maxDiffPixels threshold and per-suite tolerance explicitly pinned | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T084 | DOM/ARIA snapshot roles and accessible names match approved UI contract | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T085 | Keyboard-only tab navigation can reach every declared interactive control | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T086 | High-contrast UI text and focus ring remain visible in golden capture | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T087 | Text UTF-8 shaping ligature/RTL and combining glyphs not clipped | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T088 | Font fallback and scalable text preserve logical layout constraints | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T089 | Native Editor accessibility marked NOT_EXECUTED without OS screenreader proof | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T090 | Reduced-motion setting disables critical animation without hiding content | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T091 | Screen/camera flash frequency accessibility oracle validates chosen limits | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T092 | Browser WebGPU capability failure uses explicit WebGL2 reduced tier if approved | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T093 | WebGL2 unavailable does not silently route to unsafe SwiftShader | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T094 | Network-offline browser playtest uses only verified app generation/cache | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T095 | Browser WebGPU render target readback mapped to correct texture colorspace | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |
| Q02-T096 | Playwright web game session demonstrates input and scene semantic end-state | real pinned browser Web snapshot + ARIA/keyboard/semantic scene result, native A11y separate | FUTURE / NOT EXECUTED |

## Group 7 — SECURITY-PRIVACY-LICENSE

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T097 | Malicious oversized PNG/EXR dimensions rejected before decode allocation | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T098 | Malformed PCM WAV chunk length bounded and syntax rejected | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T099 | Zip-slip/archive path traversal fixture rejected without writing outside sandbox | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T100 | Symlink and UNC/ADS filename escapes rejected in golden registry | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T101 | Reference and test artifact paths cannot access user private projects | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T102 | Private screenshot/chat/audio identifier redacted from public evidence | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T103 | Unauthorized golden image regeneration from failing PR denied | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T104 | Golden approved review hash tamper detected and marked invalid | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T105 | Missing original test asset/license receipt blocks public golden use | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T106 | Proprietary game frames cannot be used as Stormline owned fixtures | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T107 | Unknown perceptual model weight license blocks metric activation | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T108 | Headless browser unsafe SwiftShader flag prohibited for untrusted content | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T109 | Test-runner fork PR cannot access CI deploy/AI secrets or certificates | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T110 | Malicious fixture shader doesn't gain unrestricted shell/driver privileges | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T111 | Public artifact storage upload applies size/TTL and R$0 cost guards | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |
| Q02-T112 | High severity test oracle security or integrity finding blocks merge | independent negative sandbox/rights/privacy/hash/CI permission test receipts | FUTURE / NOT EXECUTED |

## Group 8 — EVIDENCE-CI-REGRESSION-REVIEW

| Future test ID | Testable objective and scenario | Independent future oracle | Status |
|---|---|---|---|
| Q02-T113 | CTest/JUnit report cases count match actual executed suite and HEAD | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T114 | QA-01 test harness job/runner image/compiler/SDK/source metadata complete | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T115 | First failing test fixture/replay seed and input trace recorded | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T116 | Visual mismatch stores expected actual and heatmap independently hashed | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T117 | Driver-specific tolerance recorded with owner and expiry before test | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T118 | Independent reference run validates same fixture source and target tier | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T119 | Baseline change review contains before/after and semantic nonregression | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T120 | Flaky replay records original failures and retries rather than hiding | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T121 | Missing baseline yields BASELINE_REVIEW_REQUIRED not PASS | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T122 | Unsupported physical GPU tier is explicit UNSUPPORTED not approved | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T123 | Perceptual pass cannot override strict state or text/accessibility failure | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T124 | Audio metric mismatch reports sample clock/channel/latency and raw PCM | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T125 | CI artifacts are redacted/small and never claim code signing | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T126 | QA-03 performance p95/p99 and QA-05 physical qualification not inferred | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T127 | Future executor cannot unlock QA-02 WO based solely on documentation | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q02-T128 | Approved quality gate requires real evidence and no known HIGH/CRITICAL defect | QA-01 CI job/CTest source/head hashes, approved baseline diff and pt-BR objective audit | FUTURE / NOT EXECUTED |


## Current truth and stop condition
Catalog acceptance "Falhas de regressão reproduzíveis; tolerância documentada para drivers" is **NOT IMPLEMENTED OR TESTED**; QA-01 and GFX-03 predecessors only documentary, no baseline asset or compiled scene or CTest suite. `ADR-0076 PROPOSED`, 128 future Q02 tests **NOT EXECUTED**, no code owner release decision. All 80 code WOs still BLOCKED; no public MVP, source license NLE-D009 OPEN. [Benchmark protocol](../research/qa-02-visual-audio-benchmark-protocol.md) · [contracts](../contracts/qa-02-test-fixture-evidence-api.md) · [architecture](../architecture/qa-02-functional-visual-test-oracles.md).
