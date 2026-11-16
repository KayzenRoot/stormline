# QA-03 — Exactly 128 FUTURE Performance Lab Acceptance Tests (Q03-T001..Q03-T128)

**2026-11-16 | P00 DOCS ONLY, NO PERFORMANCE RUNS OR IMPLEMENTED ENGINE.** Research [#349](https://github.com/KayzenRoot/stormline/issues/349); future coding [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED, BASE `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`. QA-03 catalog 74/80 formal predecessors **QA-02 + CORE-06 + GFX-08 ONLY**, ADR-0076/0008/0021/0077 PROPOSED. **Exactly 8 groups × 16, Q03-T001..Q03-T128, ALL FUTURE / NOT EXECUTED.** No frame, GPU query, memory observation or benchmark PASS exists.

## Acceptance hierarchy for future implementation
1. Source hierarchy/release class/owner-approved QA-02 rights-cleared source fixture+golden, CORE-06 monotonic trace, GFX-08 graph/population budgets and base/head SHA must match before actual capture. Engine source license NLE-D009 OPEN currently, 80 code WOs blocked, no public MVP.
2. Separate CPU simulation/render wall, GPU actual per API pass timestamps with valid clock/frequency/calibration, and display/present pacing with actual event source. A standard hosted CI runner is not a physical Vulkan/D3D12/Metal thermal/display simulator.
3. Statistics derive from ordered raw `ns` frame series with chosen quantile interpolation, complete valid sample count, independent session count, warmup separate, correlated-frame block CI, paired randomized ABBA A/B and no post-hoc outlier erasure. p99 confidence and class comparisons require actual enough repeats; skip fake precision.
4. Dynamic VK_EXT_memory_budget/DXGI QueryVideoMemoryInfo/Metal recommended working set and unified shared RAM must be distinguished from static dedicated physical VRAM size. Missing API feature or sensor => UNSUPPORTED/UNKNOWN not zero.
5. Tier LOW/BALANCED/HIGH/CINEMATIC are **quality candidates**, owner must ratify target OS/driver/display Hz/cpu,gpu,vram and fidelity. Never accept faster wrong scene or lower visual fidelity without QA-02 correctness approval. p95/p99 target frame budgets not fixed in P00.
6. Energy/thermal only with genuine physical sensors and safe sessions: public/free CI may lack stable actual GPU. All paid runner/hardware/cloud, privileged process attach and telemetry secrets blocked without owner.
7. A real PASS requires source/head, hardware/software flag and driver, original asset rights, QA-02 snapshot, CORE-06 trace, GFX-08 graph, actual time/memory/power (or missing marker), raw SHA, quantile/CI method, objective review. The Docs Validation job only validates paper artifacts.
8. No HIGH/CRITICAL defect, fake SLSA/privacy rights, missing risk or source staleness tolerated. False-positive flaky or underpowered experiments reported INCONCLUSIVE, not green.

## Group 1 — CLOCKS-CPU-FRAME-PACING

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T001 | CPU monotonic event clock stable across clock resets/wall-clock daylight changes | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T002 | CPU simulation wall time separated from sum worker CPU busy time | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T003 | CPU update/physics/job waiting and render submission separate spans | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T004 | Frame ID and simulation tick correlate to exact source/fixture hashes | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T005 | Present-request events not mistaken for displayed frame timestamps | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T006 | Displayed interval derives from actual valid present/display source and unit | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T007 | Frame pacing identifies late/dropped/duplicated present events explicitly | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T008 | Idle vs active GPU clock frequency drift detected via calibration quality | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T009 | Cross-domain CPU/GPU clocks require paired calibration and confidence bounds | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T010 | GPU timestamp raw 64bit overflow/wrap and valid bits correctly checked | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T011 | Profiler enabled vs disabled overhead measured on same build/scene | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T012 | CPU thread scheduling/context switch variance recorded without elevated rights | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T013 | Frame-time negative or NaN/Infinity samples rejected, not coerced to zero | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T014 | VSYNC/VRR/fps cap/refresh period identified per session, not inferred from FPS | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T015 | Input-to-display latency only claimed with actual reliable timing endpoints | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |
| Q03-T016 | Frame recording interrupted or dropped events mark session invalid or incomplete | future real CPU/present hardware-clock trace and QA-02 input-tick source hash | FUTURE / NOT EXECUTED |

## Group 2 — GPU-QUERY-VULKAN-D3D12-METAL-WEBGPU

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T017 | Vulkan timestampValidBits=0 rejects native GPU elapsed query | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T018 | Vulkan timestampPeriod ns/tick converts raw query delta with safe arithmetic | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T019 | Vulkan multi-queue timestamps not subtracted without compatible time domains | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T020 | Vulkan vkCmdWriteTimestamp2 and query result after valid GPU synchronization | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T021 | Vulkan calibrated timestamp capability checked and calibration error captured | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T022 | Vulkan GPU-pass duration excludes CPU-side vkQueueSubmit unless explicit | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T023 | D3D12 timestamp query heap type matches direct/compute/copy queue capability | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T024 | D3D12 GetTimestampFrequency converts GPU tick count via floating calculation | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T025 | D3D12 GetClockCalibration samples linked CPU/GPU clock with uncertainty | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T026 | D3D12 copy queue timestamp unsupported yields explicit typed UNSUPPORTED | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T027 | Metal MTLCounterSampleBuffer only uses supported counterSets and stage sampling | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T028 | Metal counter sample resolve failure recorded and not counted as zero GPU time | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T029 | Metal CPU/GPU clock conversion uses paired observations and valid device epoch | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T030 | WebGPU timestamp-query optional feature missing returns UNSUPPORTED | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T031 | WebGPU privacy quantization and browser background throttling labelled | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |
| Q03-T032 | All APIs differentiate multi-queue overlap from summed pass execution time | future real API-specific query capability/clock/fence device readback trace | FUTURE / NOT EXECUTED |

## Group 3 — MEMORY-VRAM-STREAMING

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T033 | CPU resident peak memory reported separately from virtual/committed allocations | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T034 | Vulkan VK_EXT_memory_budget heapBudget and heapUsage checked for each heap | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T035 | Vulkan memory budget changes under OS concurrent pressure are logged | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T036 | DXGI QueryVideoMemoryInfo Budget/CurrentUsage retrieved on intended adapter/node | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T037 | DXGI local vs nonlocal memory segment classification remains distinct | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T038 | Metal recommendedMaxWorkingSetSize treated as guidance not guaranteed quota | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T039 | Metal currentAllocatedSize sampled with device generation and unified memory flag | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T040 | Unified Apple CPU/GPU shared RAM not double counted in total memory | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T041 | GPU image transient aliasing/fragmentation recognized separately from allocation | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T042 | CPU heap allocator leak ramp detected during sustained deterministic scene | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T043 | Texture streaming mip eviction honors dynamic VRAM safety margin | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T044 | GPU transient VFX memory budget remains bounded as particle count rises | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T045 | Out-of-memory/device loss samples remain failures not excluded as outliers | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T046 | Buffer upload stalls separated from GPU render execution and frame pacing | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T047 | Shader/PSO cache cold build and warmed streaming sessions compared distinctly | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |
| Q03-T048 | Unknown memory budget or sampling permission yields typed unsupported/invalid | future real OS/API allocation/working set budget observations and pressure behavior | FUTURE / NOT EXECUTED |

## Group 4 — SCENE-SCALE-QUALITY-TIERS

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T049 | Original 2D sprite/tilemap/UI scene scaling controlled by fixture asset SHA | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T050 | 2D dense Unicode/UI atlas upload pressure and CPU render cost recorded | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T051 | 2D high zoom pan animations compare frame pacing across consistent view | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T052 | 2.5D isometric draw-depth and parallax overdraw cost measured | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T053 | 2.5D transparent layers/camera movement cause bounded GPU pass cost | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T054 | 3D PBR material/shader permutations locked across performance baseline | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T055 | 3D directional/local shadow resolution and cascade count tied to tier | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T056 | 3D dynamic lights occlusion and mesh LOD scaling quantified | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T057 | 3D streaming world terrain/asset stalls include IO/memory and frame effects | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T058 | 3D skeletal animation crowds and visible entity counts correlate workload | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T059 | VFX GFX-08 live/spawn/kill particle count and overdraw tracked | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T060 | VFX GPU compute/CPU fallback selected by approved target capability | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T061 | GPU culling/drawcalls changes measured without dropping intended actors | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T062 | Adaptive quality tier transition avoids oscillation and temporal flash artifacts | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T063 | QA-02 semantic golden gate blocks faster benchmark with wrong visual output | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |
| Q03-T064 | LOW/BALANCED/HIGH/CINEMATIC tiers remain candidates until owner approval | future original QA-02 scenes + GFX-08 visual-fidelity invariants, real target and tier | FUTURE / NOT EXECUTED |

## Group 5 — STATISTICS-REGRESSION-EXPERIMENTS

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T065 | p50 frame interval measured from raw nonnegative ordered frame timestamps | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T066 | p95 tail frame time computed with fixed documented quantile convention | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T067 | p99 measured only with enough actual frames and independent session counts | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T068 | p99 uncertainty reported with block/bootstrap rather than false precision | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T069 | Frame drops and pauses included with explicit event policy, never erased | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T070 | Warmup stabilization and cold startup phases separated by predeclared criteria | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T071 | Randomized ABBA paired A/B order handles thermal and clock drift | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T072 | Source/scene/driver/quality mismatch returns INCOMPARABLE not performance PASS | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T073 | Regression report includes absolute ms and percentage effects with CI | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T074 | Correlated adjacent frames not treated as independent confidence samples | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T075 | Profiler overhead sample captured and reported with scope and timing | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T076 | Multiple hypothesis/scene tier comparisons disclose false positive policy | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T077 | Small sample insufficient power => INCONCLUSIVE not green | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T078 | Outlier handling predeclared and retains raw excluded/invalid observations | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T079 | Benchmark repetition random interleaving does not alter QA-02 scene state | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |
| Q03-T080 | Pass/fail threshold owner-approved before current results rather than post-hoc | future frame raw traces, independently repeated sessions, quantile/bootstrap paired analysis | FUTURE / NOT EXECUTED |

## Group 6 — THERMAL-ENERGY-HARDWARE

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T081 | Physical hardware GPU vendor/device driver display OS source verified | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T082 | Software CPU Vulkan renderer tagged software and not real GPU certified | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T083 | GitHub hosted VM cannot satisfy real GPU thermal/power benchmark evidence | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T084 | Battery versus AC/charging/energy saver mode captured where supported | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T085 | CPU GPU clocks and power limits observed with actual sensor provenance | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T086 | GPU/CPU thermal throttling onset captured during long stable 3D scene | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T087 | Ambient thermal variability and fan curve recorded or marked UNKNOWN | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T088 | Power watts and elapsed joules sourced from meter not guessed TDP | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T089 | Hardware sensor unavailable recorded UNKNOWN not zero or fake PASS | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T090 | Battery low power profile maintains stated quality-tier visual invariants | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T091 | Apple Silicon unified memory thermal behavior tested only on real Mac | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T092 | Low-cost Intel integrated GPU target produces actual supported baseline | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T093 | Entry AMD GPU and NVIDIA GPU profiles compared only within own class | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T094 | GPU device loss during stress recorded and rejects completed-run PASS | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T095 | Physical display VSync/VRR capability checked for pacing tests | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |
| Q03-T096 | Unsupported mobile target never enabled without owner release class approval | future actual GPU/CPU/display power/temperature sensor and physical host evidence | FUTURE / NOT EXECUTED |

## Group 7 — PRIVACY-SECURITY-LICENSE-COST

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T097 | Profiling local-only opt-in default prevents unsolicited upload of traces | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T098 | Trace export scrubs private project paths and editor user data | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T099 | GPU vendor device fingerprints privacy-scoped and no user identifier logged | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T100 | Untrusted benchmark fixture cannot execute arbitrary shell/privileged shader | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T101 | Perf trace parser rejects oversized/recursive/zip bomb or malformed JSON | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T102 | Windows ETW elevated permission request not performed without approval | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T103 | Linux perf_event_paranoid restriction respected without root fallback | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T104 | macOS Instruments permissions developer entitlements not bypassed | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T105 | Fork PR lacks hardware profiling privileged secrets or self-hosted runner access | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T106 | Third-party profiler license and bundled dependencies verified by pinned revision | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T107 | RenderDoc capture cannot ingest unrelated copyrighted commercial game assets | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T108 | Tracy capture external remote endpoint blocked by default | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T109 | Unknown proprietary tool free-to-use terms or cloud fee triggers COST_GUARD | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T110 | Artifact retention size limits stay within R$0 approved budget | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T111 | Unapproved source license prevents public benchmark app binary publication | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |
| Q03-T112 | Security HIGH/CRITICAL during profiler integration blocks quality tier promotion | future sandbox/privacy/rights/free-cost and negative security test results | FUTURE / NOT EXECUTED |

## Group 8 — EVIDENCE-BENCHMARK-GOVERNANCE

| Future test ID | Objective test scenario | Independent oracle (future) | Status |
|---|---|---|---|
| Q03-T113 | Raw frame trace SHA ties exact Git BASE HEAD fixture and engine build | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T114 | QA-02 fixture/golden approval and VFX-08 graph digest recorded in run | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T115 | CORE-06 typed trace monotonic frame IDs and dropped-event count complete | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T116 | GPU query receipt includes queue time domain valid bits and calibration proof | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T117 | Memory budget source units sample interval and unified caveat visible | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T118 | Quality tier ownership and target FPS budget explicit not implied | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T119 | CI source-only docs validation never used as engine perf PASS | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T120 | Measured hardware/software flag OS/driver/CPU/GPU/display exact without PII | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T121 | Raw A/B sessions and randomized order remain downloadable under permitted ACL | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T122 | p50 p95 p99 statistics derived reproducibly from exact raw data and method | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T123 | Bootstrap confidence and multiple scenes distinguish incomparable classes | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T124 | Regression threshold and severity objective audit before checkpoint | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T125 | Failed visual/correctness baseline blocks apparent FPS improvement | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T126 | Thermal unstable or profiler dropped trace => INCONCLUSIVE/INVALID | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T127 | Release 1.0 DoD/source license and owner approval required for deployment | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |
| Q03-T128 | Future code WO #92 remains blocked until three predecessors and proof approved | future full raw trace SHA+CI/QA-02/CORE-06/GFX-08 receipts and pt-BR objective audit | FUTURE / NOT EXECUTED |


## Truth gate
All Q03 test cases here are FUTURE / NOT EXECUTED; neither an engine, quality-tier runtime, GPU profiler, trace/benchmark/physical hardware, nor a build/sanitizer/static scan has run in this document WO. Current acceptance "Benchmarks comparáveis p50/p95/p99 por hardware e quality tier" **NOT IMPLEMENTED OR VERIFIED**. Formal deps unchanged, all 80 coding WOs BLOCKED and 0 ready; ADR-0077 PROPOSED.

[Benchmark](../research/qa-03-benchmark-statistical-protocol.md) · [architecture](../architecture/qa-03-performance-lab-scalability.md) · [API](../contracts/qa-03-performance-evidence-api.md).
