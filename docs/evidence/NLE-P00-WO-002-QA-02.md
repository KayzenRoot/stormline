# Evidence Bundle — QA-02 Automated Functional & Visual Tests, NLE-P00-WO-002-QA-02

**2026-11-16 | DOCUMENTATION ONLY | [research #345](https://github.com/KayzenRoot/stormline/issues/345) OPEN until independently verified checkpoint | [future code #91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED.** This document does **not** claim any native code, test runner, original test scene/PCM/golden, GPU capture, artifact, browser test, security scan, hardware or release was executed.

## 1. Source Check observed
- Requested main `3ffd1c76092c65a355a57ce2e713291dc83d2a72`, zero open PR, initial tree contained no QA-02 research files/ADR-0076; existing `.github/workflows/docs.yml` only docs verification. Source hierarchy checkpoint > Ledger approved ADR > Scope > DoD > Architecture > Requirements. No code implementation or QA-01 CTest runner.
- Registry 80 modules; QA-02 order 73 research `RESEARCH_PENDING`, **72/80 research documented, 8 pending, ALL 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, ready=0, approved_adr=0, release classes UNDECIDED, engine_implemented=false**. Source license NLE-D009 OPEN, NLE-D013 prohibits public MVP until v1.0 DoD.
- **Exactly formal QA-01 + GFX-03**, [QA-01 ADR-0075](../adr/0075-qa-01-ci-matrix-security-policy.md) and [GFX-03 ADR-0016](../adr/0016-gfx-03-render-graph-policy.md) PROPOSED. QA-01 owns build/CTest receipt, GFX-03 owns pass/aliasing/readback GPU generations; gameplay/audio/browser/device and QA-03/04/05 other owners transitive only. Source blob SHA-1 OIDs in [Work Order Context Lock](../work-orders/NLE-P00-WO-002-QA-02.md) are **not raw SHA-256 file digests**, future code actor must compute raw SHA256.

## 2. Official external sources researched, not adopted nor tested
- [CMake GoogleTest](https://cmake.org/cmake/help/latest/module/GoogleTest.html) `gtest_discover_tests()` runs compiled binary; cross compilation requires emulator, not free platform coverage; alternatives [Catch2 BSL1](https://github.com/catchorg/Catch2) / [doctest MIT](https://github.com/doctest/doctest).
- [Playwright visual comparison](https://playwright.dev/docs/test-snapshots) `toHaveScreenshot()` per OS/browser, browser animation/DPR/font/locale and expected snapshots, pixelmatch thresholds; [ARIA snapshots](https://playwright.dev/docs/aria-snapshots) browser semantic tree only, not native accessibility.
- [Khronos Vulkan Validation](https://docs.vulkan.org/guide/latest/development_tools.html) separate sync/GPU resource hazard truth; [SwiftShader](https://github.com/google/swiftshader) CPU Vulkan candidate Apache2 with third parties and **not physical GPU proof**, [Chromium SwiftShader fallback](https://chromium.googlesource.com/chromium/src/+/main/docs/gpu/swiftshader.md) unsafe/deprecated for untrusted content.
- [OpenImageIO idiff](https://openimageio.readthedocs.io/en/latest/idiff.html) absolute/relative and perceptual pixel/heatmap candidate; [scikit-image SSIM](https://scikit-image.org/docs/stable/api/skimage.metrics) explicit `data_range` for floats. LDR linear vs display sRGB, alpha/HDR/MSAA/driver-tier protocols proposed; no calibration measurement or baseline generated.
- Original generated sine/impulse/noise and color/scene material rights must be verified; audio sample-rate/channel/phase/FFT/RMS/peak/true-peak/silence/clipping tests planned, no recorded sound. R$0 GitHub standard runner compute conditionally free, **artifact storage may incur costs**, no actual usages.
- RenderDoc/Metal PIX capture, optional ML/LPIPS weights and FFmpeg licensing separate unapproved candidate; all exact versions/third-party notices and source engine license NLE-D009 **UNDECIDED/OPEN**.

## 3. Research PR EXACTLY EIGHT NEW Markdown
1. [Architecture](../architecture/qa-02-functional-visual-test-oracles.md).
2. [ADR-0076 PROPOSED](../adr/0076-qa-02-deterministic-golden-regression-policy.md).
3. [Technology/licenses/security matrix](../research/qa-02-test-framework-graphics-audio-license-matrix.md).
4. [Semantic fixture/test result API](../contracts/qa-02-test-fixture-evidence-api.md).
5. [Exactly 128 future Q02 tests](../testing/qa-02-acceptance-matrix.md).
6. [Future visual/audio benchmark protocol](../research/qa-02-visual-audio-benchmark-protocol.md).
7. [WO](../work-orders/NLE-P00-WO-002-QA-02.md).
8. This Evidence Bundle.

## 4. Actual proof vs missing proof
| Verified documentary research | Explicitly NOT accomplished in P00 |
|---|---|
| Source Git baseline/Source Pack, proposed ownership, official references | no approved implementation dependency or compiled engine/CTest suite |
| Eight new Markdown and Q02-T001..T128 FUTURE/NOT_EXECUTED design | no Q02 test PASS, actual scene or input replay |
| Color/pixel/SSIM/driver class proposals | no golden PNG/EXR/render screenshot or GPU hardware measurement |
| Browser Playwright/ARIA and original PCM fixture protocol | no browser test/artifact or waveform, no accessibility device |
| Trust/rights, malicious fixtures and baseline approval model | no actual parser security/hardware/asset-rights clearance |
| Existing Docs Validation | **PENDING PR run**, never QA-02 runtime test |

## 5. PR/CI/Audit/Merge PENDING until observed
Research branch `docs/NLE-P00-WO-002-QA-02-research`, BASE `3ffd1c76092c65a355a57ce2e713291dc83d2a72`. Real PR/head, eight-file statuses, Docs Validation run/job SUCCESS, pt-BR objective audit, squash/main readback must be recorded after occurrence. P00 LOW documentary, future renderer/decoder ELEVATED, privileged/cost/secret HIGH_ASSURANCE if used; no source license or release approval. Research #345 OPEN until independent checkpoint, code #91 OPEN/BLOCKED.

## 6. Independent Checkpoint Delta proposal, NOT self-promoted
After research own CI/audit/squash/main readback, independent checkpoint PR exactly **5 MODIFIED files**: docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO and Evidence. **Sole semantic registry QA-02 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 module objects and root unchanged; **73/80 researches documented (91.25%), 7 pending, ALL 80/80 code WOs BLOCKED, ready=0, approved ADR=0, release classes UNDECIDED, engine=false**. Own CI/audit/squash/readback, close research #345 only then, future code #91 OPEN/BLOCKED. Final historical **4 Markdown** checkpoint/backlog/WO/Evidence with own CI/audit/squash/main readback, next **QA-03 Performance Lab & Scalability Tiers**, order 74/80 deps QA-02+CORE-06+GFX-08, future issue [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED. No real tests or software implementation.


## Research #346 completed documentation, independent checkpoint PENDING
- [Research PR #346](https://github.com/KayzenRoot/stormline/pull/346) BASE `3ffd1c76092c65a355a57ce2e713291dc83d2a72`, final research HEAD **`464738d5304528ac4cead52e3754aaa5c6bb700e`** after an in-PR correction of OpenImageIO's actual Apache-2.0/legacy BSD-3-Clause license and review text. Exactly **EIGHT newly ADDED Markdown** architecture, ADR-0076 PROPOSED, tech/license/security matrix, semantic fixture evidence API, 128 future Q02 tests, benchmark, WO, Evidence. [Docs Validation exact-head #43799680776](https://github.com/KayzenRoot/stormline/actions/runs/43799680776) **SUCCESS** job #133076546244 (Source Pack/links, catalog DAG, registry, blocked selector), [objective pt-BR audit #6906651606](https://github.com/KayzenRoot/stormline/pull/346#issuecomment-6906651606) APPROVED documentary; normal squash/main readback **`5957b91b8b76fd61f26d9348ea527c08a1748a49`** and original 72/80 registry unchanged at research integration.
- Proposed independent checkpoint **SOLE semantic registry QA-02** `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, all other 79 module objects and root flags identical. Target **73/80 researches documented (91.25%), 7 pending, ALL 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release class UNDECIDED all, engine_implemented=false**. Formal DAG **QA-01 + GFX-03 ONLY**; predecessor ADR-0075/0016 PROPOSED, new ADR-0076 PROPOSED, source license NLE-D009 OPEN, Q02-T001..Q02-T128 FUTURE/NOT EXECUTED. **No C++ engine, CTest/Playwright run, original asset/golden PNG/EXR, PCM audio, GPU hardware/driver capture, a11y or runtime test.** The existing CI only validates documentation, not functional/visual gameplay.
- [Research issue #345](https://github.com/KayzenRoot/stormline/issues/345) remains OPEN until independent checkpoint own Docs CI/audit/squash/main readback, future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED. Then close #345 and perform separate four-Markdown factual history with its own CI/audit/squash/readback. Next real catalog **QA-03 Performance Lab & Scalability Tiers**, order **74/80**, formal **QA-02 + CORE-06 + GFX-08**, future code [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED.
- This document cannot be interpreted as actual GPU/driver baseline calibration/visual regression PASS. All Q02 future tests unexecuted.
