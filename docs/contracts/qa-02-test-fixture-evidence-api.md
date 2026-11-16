# QA-02 — Proposed Deterministic Fixture, Visual, Audio and Regression Evidence Contracts v0.1

**2026-11-16 | P00 DOCUMENTARY RESEARCH | [research #345](https://github.com/KayzenRoot/stormline/issues/345) | WO NLE-P00-WO-002-QA-02 | future code [#91](https://github.com/KayzenRoot/stormline/issues/91) OPEN/BLOCKED | source HEAD `3ffd1c76092c65a355a57ce2e713291dc83d2a72`.** Formal DAG **QA-01 + GFX-03 ONLY** (ADR-0075 and ADR-0016 PROPOSED), 72/80 researches documented at start, all 80 code WOs BLOCKED, release classes UNDECIDED, engine=false.


**Design-only semantic API; no C++ ABI/executable class, gtest, CTest, screenshot, waveform, GPU capture or CI workflow created.** QA-02 exposes portable IDs and immutable manifests, not SDL/VkImage/D3D12/MTL pointers or a new renderer.

## Formal predecessors EXACT TWO
| Formal | Proposed owned source | QA-02 consumes |
|---|---|---|
| **QA-01** | [CI evidence API](qa-01-ci-evidence-api.md), ADR-0075 PROPOSED | source/runner/toolchain/CTest test counts/JUnit/evidence, trust/cost gate, no new runner implementation |
| **GFX-03** | [Render Graph API](gfx-03-render-graph-api.md), ADR-0016 PROPOSED | graph PassNode/ResourceUse DAG and device generations, lifetime, explicit render capture and fences, no new RHI scheduling |

All gameplay, sound, scene, Unicode, browser, native OS and QA-03/04/05 are transitive/integration owners and not extra formal dependency edges.

## Versioned logical type contracts
| Type | Required logical fields | Invariant / rejection |
|---|---|---|
| `QaFixtureManifestV1` | stable FixtureId/revision/source SHA, owner license/rights receipt, source/cooked asset ids+digests, original scene 2D/2.5D/3D/browser/audio category, dependency closure, expected outcomes | missing rights/stale/modified scene -> STALE_FIXTURE/UNTRUSTED |
| `QaDeterminismProfileV1` | random seed/algorithm, tick numerator/denominator, initial world snapshot hash, canonical actor order, input event trace, frozen time/locale/float mode | inconsistent clock/seed/snapshot invalidates comparator |
| `QaInputReplayV1` | action IDs/device/seat/window, event order/tick, pointer/keyboard/gamepad, expected state checks, schema version | input cancel/ordering/dropped event explicitly fails |
| `QaHeadlessSessionV1` | actual runtime/host/headless/no-GPU/software/native GPU, fixture, world+surface/device generation, invocation timeout, expected tests | no physical GPU proof from SW/headless |
| `QaGraphicsCaptureProfileV1` | GFX-03 render graph ID/pass/resource, backend/driver/software flag, device generation, resolution+viewport/DPR, camera, shader/compiler digest, color primaries/transfer/ICC, linear/HDR/sRGB and alpha/MSAA/exposure | cannot compare unknown color profile/unsynced fence/expired resource |
| `QaCaptureReadbackReceiptV1` | target pass/ResourceId/subresource, graph compile hash, synchronized fence/timeline, frame tick/history seed, pixels/format/hash and validity | no read-before-write/alias lifetime, stale generation -> failure |
| `QaGoldenBaselineV1` | BaselineId, FixtureId/profile/device tier, content SHA/format, approved oracle and metric thresholds, owner rights/approved PR/reviewer, approval time & expiry | missing baseline or unreviewed threshold -> BASELINE_REVIEW_REQUIRED |
| `QaImageComparatorPolicyV1` | exact/per-channel abs/relative/SSIM/edge/semantic masks, threshold budget, compare in declared color space with float data_range, max mismatch pixels/pct | no global magic thresholds or SSIM bypass of hard fail |
| `QaImageDiffReceiptV1` | expected/actual hashes, diff image/heatmap hash, per-channel maximum+RMSE/MAE, SSIM if specified, masks, semantic failures, first offending frame | missing asset/mask/driver tier/metric -> BLOCKED |
| `QaTemporalFrameSequenceV1` | ordered frame tick/time, stage readback refs, history seed, event state hash, GFX-03 pass dependencies, flicker/temporal oracle | no mixed frames or aliasing, deterministic tolerance |
| `QaAudioFixtureV1` | synthetic/original waveform hash/rights, sample rate/channels/layout, initial graph state, mixer profile, seed/fixed tick, expected onset/peak | no copyrighted/music samples and no external microphone |
| `QaAudioDiffReceiptV1` | expected/actual PCM hashes, sample clock/latency, RMS/peak/true peak/correlation/spectrum/channel/isolation/clipping bounds | unknown channel config or sample-rate conversion -> explicit mismatch |
| `QaA11yReceiptV1` | Web ARIA snapshot schema/roles/labels/tab and focus results, text layout/contrast, native screen-reader required/not-tested marker | ARIA/web screenshot never proves native UI accessibility |
| `QaPlaytestTraceV1` | runtime replay source/seed/ticks, world checksum per tick, actor IDs, expected hits/path/nav/save, first failed command/state diff | cannot call playtest PASS from simulated plan only |
| `QaBaselineChangeRequestV1` | original approved baseline rev, new candidate hashes, before/after/diff, rationale, authorized approver, QA CI and rights/license evidence | no automatic `--update-snapshots` in PR failure, approval separate |
| `QaRegressionResultV1` | TestId/fixture/baseline, CI HEAD/job, backend/driver, numerical and semantic findings, first mismatch tick/frame, triage severity, status | PASS only when all required checks actually run |
| `QaFailureClassV1` | MISSING_BASELINE, UNTRUSTED_FIXTURE, STALE_SOURCE, DRIVER_CLASS_MISMATCH, CAPTURE_UNSYNCHRONIZED, COLOR_SPACE_UNKNOWN, AUDIO_MISMATCH, A11Y_FAIL, REPLAY_DIVERGENCE, GPU_DEVICE_LOST, NO_TESTS_EXECUTED, INFRA_FAIL, COST_GUARD | explicit failure and preserving last-good baseline |

## Candidate non-executable operations
| Operation | Owner | Semantics |
|---|---|---|
| `resolve_qa_fixture(id, revision)` | QA-02 registry | immutable rights-verified scene/cooked snapshot |
| `lock_qa_determinism(profile)` | QA-02 test harness | fixed tick/seed/time/locale/float and trace |
| `run_qa_functional_assertions(session)` | QA-02 through QA-01 CI | CTest receipt, nonzero test count |
| `replay_qa_input_actions(trace)` | QA-02 + gameplay integration | stable tick events and state hashes |
| `request_gfx_pass_readback(graph,pass,resource)` | GFX-03 owner, QA-02 consumer | actual fence/synchronized FrameReadbackReceipt |
| `compare_qa_images(expected,actual,policy)` | QA-02 | typed image/metric/semantic oracle; no fake pass |
| `compare_qa_audio(referencePCM,actualPCM)` | QA-02 + AUD owner | offline sample metrics and timing, no speaker playback |
| `assert_qa_browser_snapshot(page)` | QA-02, Playwright future | screenshot and ARIA + pinned browser/OS conditions |
| `evaluate_qa_accessibility(snapshot)` | QA-02 / UI owner | semantic role/tab/contrast evidence and explicit native TBD |
| `propose_qa_baseline_change(receipts)` | owner review | separate pending approval, not automatic |
| `verify_qa_regression_gate(results)` | QA-01 orchestrates, QA-02 supplies | nonzero tested cases and all hard invariants |
| `emit_qa_replay_bundle(failure)` | QA-02 evidence | source/fixture hashes, seed/events, first mismatch, expected/actual/diff/PCM, redacted |
| `check_qa_license_security(fixtures)` | QA-04/owner integration | validated original fixtures, no private content, no arbitrary script |
| `certify_physical_gpu_compat()` | QA-05 only | not part QA-02 run unless independently executed |
| `publish_engine_build()` | BIZ-03 only | never QA-02 or P00 |

## Invariants and Stop
- No implicit parsing of untrusted fixtures or third-party private projects. All captures sandboxed and size bounded, human baseline changes require audited approval. Runtime readback must wait GPU fence and use live graph/resource generation. No native handle leakage through CI artifacts.
- Hard semantic logic/geometry/text/accessibility failures override perceptual SSIM, and no universal threshold across driver tiers. Unknown hardware/driver or codec/cspace => UNKNOWN/BLOCKED. A comparison result is not confidence in native GPU equivalence.
- C++ unit/Playwright test discovery and CTest expected count >0, raw fail/skip/xfail and stderr included. Software renderer/Chromium SwiftShader opt-in only trusted tests, never automatic browser fallback on untrusted content.
- Audio fixture original synthesized PCM with explicit time/sample config, no recording user microphone/copyright material, no claims on loudness across hardware without actual measurement. No active soundtrack playback.
- Source license NLE-D009 OPEN, ADR-0076 PROPOSED, all 80 code WOs BLOCKED. Future 128 tests NOT_EXECUTED and engine not implemented.

[Architecture](../architecture/qa-02-functional-visual-test-oracles.md) · [128 future cases](../testing/qa-02-acceptance-matrix.md) · [ADR](../adr/0076-qa-02-deterministic-golden-regression-policy.md).
