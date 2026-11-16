# NLE-P00-WO-002-QA-02 — Automated Functional & Visual Tests: Research Work Order

**2026-11-16 | P00 DOCUMENTATION ONLY | [research #345](https://github.com/KayzenRoot/stormline/issues/345) | [future code #91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED | source HEAD `3ffd1c76092c65a355a57ce2e713291dc83d2a72` | NLE-P00-WO-002-QA-02**. Formal **QA-01 + GFX-03 ONLY**, predecessors ADR-0075/0016 PROPOSED; baseline 72/80 research documented, 8 pending, ALL 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready/approved_adr, all release_class UNDECIDED, engine_implemented=false. NLE-D009 engine source license OPEN; NLE-D013 no public MVP.


**Current risk LOW documentary; future native test/renderer/decoder STANDARD/ELEVATED, privileged signing/untrusted code HIGH_ASSURANCE if later introduced.**

## OBJECTIVE
Research modern C++20 functional/unit and integration test frameworks and GFX-03 render-graph observability, golden image/driver-tolerant comparison, software/headless vs native GPU verification, original deterministic 2D/2.5D/3D scenes, synthetic audio PCM comparison, browser Playwright screenshots/ARIA, gameplay event replay, accessibility and robust baseline update/security/privacy/licensing. Produce proposed ADR, semantic contracts, exactly eight Markdown and exactly 128 FUTURE objective cases with independent benchmark protocol. **No real game engine/code/tests/binaries built in P00.**

## CONTEXT / SOURCE CHECK
Authoritative order: checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > AGENTS/catalog. Requested main HEAD verified exactly `3ffd1c76092c65a355a57ce2e713291dc83d2a72`, no open PR, tree no QA-02 or ADR-0076 conflicts, `.github/workflows/docs.yml` only Docs Validation, **no actual C++ or GFX runners**. Catalog 80 modules; QA-02 order 73/80 research_status RESEARCH_PENDING, 72 researched/8 pending, ALL 80/80 coding WOs BLOCKED, ready 0, approved ADR 0, release classes UNDECIDED, engine false. Source license NLE-D009 OPEN, D013 no public MVP, D014 2D/2.5D/3D/Web, D017 desktop Windows/Linux/macOS Editor and game targets, D018 routine safe docs only, D019/020 all code packet blocked. **Exact formal predecessors QA-01 + GFX-03**, their ADR-0075/0016 PROPOSED (not implementation authority); QA-01 CTest/CI and GFX-03 typed RenderGraph graph passes/resource lifetime/fence owners. CORE/GAME/GFX other, AUD, TWO, UI, DATA/EDIT, PLAT, QA-03/04/05 all integration/transitive, NOT new catalog formal edges.

## CONTEXT LOCK
Exact base Git SHA `3ffd1c76092c65a355a57ce2e713291dc83d2a72`. Observed these are **Git blob SHA-1 object IDs, NOT file SHA-256**. Future code preflight must compute byte SHA-256 and stop as STALE if checkpoint, ledger/approved ADR, Scope, DoD, Architecture, Requirements, catalog/registry, QA-01 or GFX-03 critical contract changes.
- `AGENTS.md` — `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md` — `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md` — `aa250bf14fbf83c7f5458ec734b86e426ff2c299`
- `docs/10-decisions-ledger.md` — `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md` — `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md` — `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md` — `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` — `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md` — `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json` — `3050b9a5989353adc985af1458e9dbafd6db2d3d`
- `docs/queue/work-orders/QA-02.md` — `9bfd23876bffc6400f4367df6ad93705d619bf77`
- `.github/workflows/docs.yml` — `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`
- `docs/adr/0075-qa-01-ci-matrix-security-policy.md` — `22e91a36c1e0a8121163fa4778abd0489fed86e5`
- `docs/adr/0016-gfx-03-render-graph-policy.md` — `216719c5d19d4877bcfb7d60923e07f4f58b5109`
- `docs/contracts/gfx-03-render-graph-api.md` — `78702022c131f1f13a66cee959d3b8095a19bb2b`
- `docs/contracts/qa-01-ci-evidence-api.md` — `ccaa79cfc34fff3e58b68fa7d2b1f594f5d8154f`

## SCOPE (NECESSARY, EXACTLY EIGHT NEW Markdown)
1. [Architecture](../architecture/qa-02-functional-visual-test-oracles.md).
2. [ADR-0076 PROPOSED](../adr/0076-qa-02-deterministic-golden-regression-policy.md).
3. [Technology/license/security/tool comparison matrix](../research/qa-02-test-framework-graphics-audio-license-matrix.md).
4. [Typed semantic test fixture/result contracts](../contracts/qa-02-test-fixture-evidence-api.md).
5. [Exactly 128 FUTURE Q02-T001..Q02-T128](../testing/qa-02-acceptance-matrix.md).
6. [Future reproducible visual/audio benchmark protocol](../research/qa-02-visual-audio-benchmark-protocol.md).
7. This WO.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-QA-02.md).
Research PR only adds eight Markdown, not existing Source Pack/registry/checkpoint/backlog, no C++/CTest/YAML/runner/graphics screenshot files.

## OUT OF SCOPE
No real unit tests, gtest/Catch2 install, CMake/CTest binary, render graph/GPU/SwiftShader/Playwright runner, real screenshot/golden image/EXR/PCM/audio playback/fixtures, browser deployment, license adoption, model weights, paid rendering service, public game samples, changes to approved prior ADRs/other module code, release class, implementation queue, CI/rulesets, project root cleanup, privileged GPU access, App Store signing/public MVP.

## FILES/SOURCES TO READ
All Context Lock paths, original QA-02 future code issue #91 and next QA-03 #92. Primary official references: [CMake GoogleTest](https://cmake.org/cmake/help/latest/module/GoogleTest.html), [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html), [Catch2](https://github.com/catchorg/Catch2), [doctest](https://github.com/doctest/doctest), [Playwright screenshot](https://playwright.dev/docs/test-snapshots), [Playwright ARIA](https://playwright.dev/docs/aria-snapshots), [Vulkan Validation](https://docs.vulkan.org/guide/latest/development_tools.html), [SwiftShader](https://github.com/google/swiftshader) and [Chromium unsafe fallback](https://chromium.googlesource.com/chromium/src/+/main/docs/gpu/swiftshader.md), [OpenImageIO idiff](https://openimageio.readthedocs.io/en/latest/idiff.html), [scikit-image SSIM](https://scikit-image.org/docs/stable/api/skimage.metrics), [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions). All software versions/rights require separate future approval.

## REQUIREMENTS
Catalog acceptance **"Falhas de regressão reproduzíveis; tolerância documentada para drivers."** Unit tests nonzero executed after code, integration functional/scene deterministic traces, golden source/provenance, GPU driver class differences and conservative semantic invariants, original audio waveform rights, accessible UI/browser and actual platform evidence. 1.0 public release prohibited until full DoD. All QA-02 code packets remain BLOCKED.

## ARCHITECTURE RULES
- QA-01 owns C++20 CI, CTest counts, source/head/job/cost/provenance; QA-02 consumes, never adds own runner implementation. GFX-03 owns render graph passes/resource/fences/device epochs; QA-02 requests capture and synchronized readback, never implements GFX backend.
- Use original rights-cleared content-addressed scenes/atlas/alpha 2D, isometric 2.5D and 3D PBR/shadows, offline PCM synthesized and browser gameplay traces. Fixed tick/RNG/input/actor IDs/locale/OS/browser/GPU profile and SHA.
- Native software Vulkan SwiftShader candidate for deterministic headless, but no claim on real Vulkan/D3D12/Metal GPU; Chromium unsafe SwiftShader WebGL fallback NOT allowed for arbitrary untrusted content. Browser Playwright pinned OS/version/fonts/DPR/viewport and ARIA snapshots distinct from native accessibility.
- Strict state, geometry, read-before-init, fence/time/tick, visible text, semantic a11y and safety gates override permissive SSIM/pixel tolerances. Color linear/sRGB/ICC/HDR capture/alpha/MSAA and driver tier documented; float SSIM data_range explicit. Zero cross-GPU universal pixel-exact assumption.
- Audio PCM sample rate/channel/mixer/latency, RMS/peak/correlation/FFT and clipping on own synthetic source. No copyright music or real microphone content. Baseline updates require separate audited owner approval and before/after/heatmap; failing PR never self-ratifies goldens.
- Sandboxed image/audio/asset decode, size bounds, malicious file and symlink/path traversal protections, no real user/private screenshot uploads, no paid GPU/test cloud and no external AI/ML oracle auto-pass.

## CONSTRAINTS
Risk LOW P00, current Docs Validation only, no paid/privileged tools, no external reviewer mandatory, no license/SDK or alpha product adoption, no force push/history rewrite, no HIGH/CRITICAL unresolved, Context Lock source stale requires redo. All 80 implementation WOs remain blocked; source license OPEN.

## ACCEPTANCE CRITERIA
- [ ] Research PR exactly 8 ADDED Markdown with links valid, ADR-0076 **PROPOSED**, formal deps QA-01+GFX-03 only.
- [ ] Current 2026 technically source-backed CMake/GTest/Catch2/doctest, Playwright, Vulkan validation/SwiftShader caution, SSIM/data_range/color/HDR/driver tolerance, original synthetic audio/scene replay, accessibility/privacy/licensing/cost fully documented.
- [ ] **Exactly 128 sequential unique Q02-T001..Q02-T128** eight groups ×16 all FUTURE/NOT EXECUTED with benchmark, no fabricated PASS.
- [ ] Research exact-head Docs Validation SUCCESS, objective pt-BR audit APPROVED documentary, normal squash and main readback; no code/registry change in initial PR.
- [ ] **Independent checkpoint exactly 5 MODIFIED** files docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO, Evidence. Sole semantic registry QA-02 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, other 79 objects and root fields identical. Target **73/80 researched (91.25%), 7 pending, 80 code WOs blocked, executor_ready=0, approved_adr=0, all releases UNDECIDED, engine=false**. Independent CI/audit/squash/readback before closing research issue #345; coding #91 OPEN/BLOCKED.
- [ ] Independent **4 Markdown historical PR** checkpoint/backlog/WO/Evidence, own CI/audit/squash/main readback, next REAL QA-03 Performance Lab & Scalability Tiers ordinal 74/80 deps QA-02 + CORE-06 + GFX-08, code #92 blocked.

## TESTS
P00 only actual GitHub Docs Validation (Source Pack/relative links, catalog DAG, 80 registry and Zcode selector blocking execution), PR files/statuses, exact Q02 IDs and five-file JSON semantic diff. **No engine code, unit/functional/headless Playwright/visual/audio tests executed**, no real images/PCM/driver metrics. Future measured test fleet required after owner approvals, not this increment.

## DELIVERABLES
Issue #345 research, 8 new Markdown ADR/architecture/matrix/API/tests/benchmark/WO/Evidence, GitHub research PR exact source/head, Doc CI run/job, objective pt-BR audit/squash/main readback; checkpoint five-file independent PR, CI/audit/squash/readback and close #345; factual historical four-Markdown independent PR CI/audit/squash/readback. No release/engine.

## REVIEW FORMAT
pt-BR APPROVED / CORRECTION REQUIRED / BLOCKED, exact BASE/HEAD/changed statuses, source-lock Git blob vs raw SHA, exact formal DAG, tool/rights/privacy/security/cost, future 128 case IDs and NOT_EXECUTED vs actual CI docs, defect severity and risks, checkpoint delta, merge readback. Independent objective review no external human reviewer mandated.

## STOP CONDITION
STALE source, wrong deps/files/128 IDs, CI failed, false baseline/GPU/PCM/engine claims, license/asset rights/security HIGH/CRITICAL, unexpected privileged/paid tool or runner or unapproved branch action => BLOCKED or CORRECTION REQUIRED same WO/PR. Do not advance QA-03 or unlock QA-02 code until current documentary gates complete.

## CHECKPOINT DELTA PROPOSED ONLY
After research CI/audit/squash/main readback five-file PR with sole QA-02 research_status JSON delta. Own CI/audit/squash/main readback before closing research #345; code #91 still BLOCKED. Then factual 4-Markdown history own gates. Next QA-03 catalog 74/80, formal QA-02+CORE-06+GFX-08. 80/80 code packets blocked always.
