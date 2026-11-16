# QA-02 — Test Framework, Graphics/Audio Oracles, Security, License and Cost Research

**2026-11-16 | P00 DOCUMENTARY RESEARCH | [research #345](https://github.com/KayzenRoot/stormline/issues/345) | WO NLE-P00-WO-002-QA-02 | future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED | source HEAD `3ffd1c76092c65a355a57ce2e713291dc83d2a72`.** Formal DAG **QA-01 + GFX-03 ONLY** (ADR-0075 and ADR-0016 PROPOSED), 72/80 researches documented at start, all 80 code WOs BLOCKED, release classes UNDECIDED, engine=false.


**2026 source-grounded options only. No selected/adopted exact library version, test run, renderer, audio sample, GPU image, hardware proof, approved golden baseline, CI workflow or paid testing vendor.** Verify exact license tags and third-party assets/model weights prior to any code.

## Primary authoritative references
| Reference | Current documented technical fact | Stormline future proof |
|---|---|---|
| [CMake GoogleTest module](https://cmake.org/cmake/help/latest/module/GoogleTest.html) | `gtest_discover_tests()` introspects compiled executable and handles parameterized tests but requires `CROSSCOMPILING_EMULATOR` for cross compiling; `gtest_add_tests()` statically scans sources | QA-01 CTest nonzero test count and platform-runner proof; no Linux-host run of Windows test binary |
| [Catch2 upstream](https://github.com/catchorg/Catch2) | Catch2 v3 C++ native test framework, BSL-1.0 (Boost Software License) | alternative to GoogleTest, no duplicate runtime if unneeded |
| [doctest upstream](https://github.com/doctest/doctest) | C++ unit test framework MIT and single-header | alternative, check exact features and ABI |
| [Playwright screenshot](https://playwright.dev/docs/test-snapshots) | `toHaveScreenshot` waits for stable consecutive captures; pixelmatch `threshold`, `maxDiffPixels`, `maxDiffPixelRatio`, OS/browser snapshots vary | pinned Chromium/Firefox/WebKit, OS, DPR, fonts/locale/animations; baseline update never automatic |
| [Playwright ARIA snapshots](https://playwright.dev/docs/aria-snapshots) | accessible role/name/attribute YAML snapshot for DOM hierarchy and keyboard flows | *browser accessibility semantics* only; native OS screen reader still separate |
| [Vulkan Validation Layers](https://docs.vulkan.org/guide/latest/development_tools.html) | Khronos validation/synchronization/GPU assisted validation flags | independent of image perceptual pass; GPU-AV has performance overhead and real Vulkan driver requirements |
| [SwiftShader Vulkan](https://github.com/google/swiftshader) | CPU Vulkan implementation under Apache-2.0, some third-party folders different licenses | pinned and sandboxed headless future, never classify software renderer as physical GPU |
| [Chromium SwiftShader deprecation](https://chromium.googlesource.com/chromium/src/+/main/docs/gpu/swiftshader.md) | automatic WebGL SwiftShader fallback deprecated; manual `--enable-unsafe-swiftshader` reduces safety for untrusted content | do not enable flag on arbitrary game content, use explicit offline trusted fixtures only if owner approves |
| [OpenImageIO idiff](https://openimageio.readthedocs.io/en/latest/idiff.html) | absolute/relative pixel error & perceptual comparison plus diff image, supports multiple formats | pin plugins and EXR/PNG decode, comparison color space and dimensions |
| [scikit-image SSIM](https://scikit-image.org/docs/stable/api/skimage.metrics) | `structural_similarity` for float images requires **explicit `data_range`**; implicit float dtype can yield wrong range | ensure linear-light or display-referred fixed domain and channel handling, no global threshold |
| [Playwright test config](https://playwright.dev/docs/api/class-testconfig) | `toHaveScreenshot` defaults perceptual threshold 0.2 but other bounds unset by default; masks/dynamic style supported | define per-fixture bound rather than inheriting permissive defaults |
| [SDL platform docs](https://wiki.libsdl.org/SDL3/FrontPage) | event/time/audio device capabilities, OS rendering and input vary | gameplay event replay/gamepad/audio capture via respective owners, not extra QA-02 DAG |
| [CTest 4.x](https://cmake.org/cmake/help/latest/manual/ctest.1.html) | test selection, parallel scheduling, JUnit XML, failure and timeout handling | CI runner must fail zero tests and report skipped/unsupported |
| [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions) | public standard hosted runner compute free, storage and larger runner may incur cost | artifact corpus and screenshots need quotas/retention, no paid visual SaaS |

## Candidate tooling, license and deployment constraints (all PROPOSED)
| Candidate | Upstream license / rights to verify by exact version | Role | Risk/conditions |
|---|---|---|---|
| GoogleTest/GoogleMock | BSD-3-Clause, verify release tag/license | C++20 parameterized/unit/integration assertions | CMake test discovery needs executable or emulator, mocking must not hide lifecycle |
| Catch2 v3 | Boost Software License 1.0 | native alternative | features/compile overhead, avoid redundant frameworks |
| doctest | MIT | small C++ native alternative | reporter/CTest interoperability validation needed |
| CMake/CTest | BSD-3-Clause | test orchestration and JUnit | QA-01 owner, no runtime test present |
| Playwright + browser bundles | Playwright Apache-2.0 as upstream project, browsers have separate Chromium/Firefox/WebKit licenses | Web game/UI visual + ARIA snapshots, fixed browser/OS | browser download size/storage/patches, no native Mac/Windows scene equivalence |
| pixelmatch | ISC | per-pixel/browser diff | threshold not oracle for semantic behavior |
| OpenImageIO `idiff` | BSD-3-Clause (verify plugins and codecs) | PNG/EXR pixel/perceptual compare | OCIO/color conversion/profile licensing, signed heatmap and security |
| scikit-image + numpy | BSD-3-Clause for scikit-image, NumPy BSD-3-Clause and dependencies by pin | SSIM/MAE/RMSE and programmatic heatmap | explicit data_range and float range, OOM limits on large images |
| OpenColorIO | BSD-3-Clause (verify exact repo tag/config rights) | linear↔sRGB/ACES/HDR color reference | OCIO config license, gamut mapping and ICC differences |
| OpenEXR/Imath | BSD-3-Clause family (verify transitive/third-party) | linear HDR golden storage | decompression/zip bombs, >16bit float, metadata canonicalization |
| libpng | libpng license variant by version | deterministic PNG encoding | metadata/time/chunk order, alpha/ICC, malicious PNG parsing |
| RenderDoc | MIT (official project [renderdoc.org](https://renderdoc.org/), verify exact source release) | optional **owned** D3D12/Vulkan/OpenGL frame replay debug evidence | no Metal capture via RenderDoc assumption; permission/process attach and captured secrets |
| Khronos Vulkan SDK/layers | Apache-2.0 for Vulkan-ValidationLayers; platform loader/SDK/driver licenses vary | Vulkan sync errors/readback | GPU-assisted overhead, driver hardware not implied |
| SwiftShader CPU Vulkan | Apache-2.0 + third-party notices | software Vulkan offscreen | **not physical GPU**, Chromium browser unsafe fallback distinct |
| DirectX 12/PIX | Microsoft SDK proprietary and PIX terms by version | Windows GPU evidence via separately approved tools | not R$0 assumed for proprietary cloud lab, no software/physical equivalence |
| Metal/MTL capture/Xcode Instruments | Apple proprietary SDK/developer terms | native macOS GFX capture from actual device | hosted VM ≠ Metal physical validation, no developer account/spend assumed |
| WebGPU validation / wgpu | Apache-2.0/MIT in wgpu ecosystem exact module to verify | backend owner’s typed WebGPU frames | browser vendor, device loss and API tier, no native GFX implementation here |
| Image metrics LPIPS (optional) | PyTorch model/code separate licenses, **weights and training corpus require verification** | perceptual metric research only | large dep, nondeterminism, false negative, avoid automatic downloads |
| ffmpeg / ffprobe (optional) | configure-dependent LGPL/GPL/nonfree flags, codecs patent/rights; exact build license verify | offline PCM/FFT/framemd5/frequency/EBU R128 only if approved | no media redistribution or production shader/audio encoder adoption |
| libebur128 (optional) | MIT under common upstream tags verify | EBU R128 loudness fixture | loudness alone insufficient for onset/clipping/cross-channel |
| Python `wave` + NumPy | Python PSF, NumPy BSD-3 | generated original PCM and RMS/FFT | sample rate/dither/config fixed, no external audio files or ML cloud |
| Generated sine/impulse/noise fixtures | original synthetic waveform authored by project | audio test evidence | **no copyrighted track** and no actual waveform currently generated |
| Original scenes/font samples/sprites | project-owned rights must be verified, font licenses e.g. OFL-1.1 if selected | 2D atlas, 2.5D isometric layers, 3D PBR, UI glyphs | all required images/audio/goldens must have license/source evidence; NLE-D009 engine license OPEN |
| dEQP / VK-GL-CTS (optional owner) | Apache-2.0 Khronos test conformance submodules/asset rights by tag | external graphics API conformance reference | huge suites, HW/driver costs, NOT QA-02 first increment or engine proof |
| Accessibility test tools | Playwright/browser built-ins, native platform screen-reader/proprietary SDK terms | ARIA/contrast/tab/focus/rules | screenshot only not equivalent screen-reader quality |

## Comparator and quality classification, never single global magic number
| Field | Future default *policy to calibrate*, not approved numeric threshold | Hard failure independent of metric |
|---|---|---|
| Exact state/golden | pixel identical only if same deterministic backend/shader/fixture format and declared bit-exact | wrong ActorId, PassId, SceneRevision, draw order, alpha layer, text missing |
| LDR sRGB pixel diff | convert to declared linear or display-referred profile, bound max absolute and %diff by fixture | bad premultiplication/ICC/gamut/letterbox/wrong color channel |
| HDR linear EXR | explicit float range and exposure/tone map, compare linear float and display transform separately | NaN/Inf/unbounded luminance/negative depth |
| Driver tolerant | fixture+GPU family/backend/driver and shader/compiler versions, measured bounded threshold + SSIM/edges | severe blackframe, geometry, UI text, depth, IDs, temporal flicker |
| Temporal | fixed simulation tick and history seed, compare keyframe sequence and motion traces | frame-order/fence/device generation error |
| Audio | fixed PCM channels/sample rate, RMS/peak/FFT/latency/correlation/tolerance | missing channel, clipping, silence, gross timing |
| A11y | semantic roles, labels, focus, keyboard alternative + contrast UI | elements unreachable, unlabeled controls, truncated Unicode UI |
| Missing baseline | explicit review gate, never auto accept update | wrong asset rights, unknown device, synthetic reference |
| Platform unsupported | explicit UNSUPPORTED/BLOCKED documented and owner matrix | silent success from headless software when physical required |

## Threat model and evidence/rights safeguards
- Malicious PNG/EXR/WAV/GIF/asset data, parser overflow, oversized dimensions, crafted ICC tags, decompression zip bombs, long waveform and recursion: decode in bounded memory/CPU sandbox, trusted engine fixtures and explicit size/format allowlist. Negative test fixtures should be synthetic and not privilege escalation.
- A malicious or careless change might silently regenerate snapshot goldens to match bug; protect references with separate baseline review/commit SHA and compare expected/actual/diff/semantic masks and owner approval. Never auto-update on PR failure.
- Attacker-supplied artifact path traversal, symlinks, remote URLs, executable tests/Playwright script embedded in untrusted user project; use QA-01 read-only tokens, no implicit shell/root, no hidden cloud/permission.
- Private user screenshots, audio recordings, conversations and commercial game assets must not be uploaded to public artifact logs; only original source fixture rights, redacted baseline metadata and explicit owner privacy consent.
- Exact GPU/driver fingerprints should be coarse enough not to uniquely identify people; no hidden user hardware telemetry.
- Model-based oracles can misclassify adversarial visual changes. No ML-driven PASS override, all hard checks and security gates remain primary. Label skipped/unsupported instead of claiming green.
- Native GPU debug capture/RenderDoc/PIX/Metal acquisition requires owner and target GPU consent; CI ephemeral hosted hardware not physical GPU certification.

## Research risk and owner gates
Research docs LOW. Future complex renderer/scene/audio integration STANDARD/ELEVATED, untrusted fixture parsing and CI privilege HIGH_ASSURANCE where required. No HIGH/CRITICAL known in current docs, but zero executable security proof. Pin versions, approve source license and data/fixtures, calibrate per class via real baseline measured tests and use objective pt-BR audit. No paid or author-less golden generation.

[Architecture](../architecture/qa-02-functional-visual-test-oracles.md) · [benchmark protocol](qa-02-visual-audio-benchmark-protocol.md) · [ADR-0076](../adr/0076-qa-02-deterministic-golden-regression-policy.md).
