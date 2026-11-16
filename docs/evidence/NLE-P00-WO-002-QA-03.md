# Evidence Bundle — NLE-P00-WO-002-QA-03 Performance Lab Research

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research issue #349](https://github.com/KayzenRoot/stormline/issues/349) OPEN until audited independent checkpoint | future code [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED | SOURCE main `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`.** Catalog QA-03 order 74/80, **FORMAL PREREQS EXACT QA-02 + CORE-06 + GFX-08**, prior ADR-0076/0008/0021 all PROPOSED. Baseline 73/80 documented, 7 pending, all 80 code packets BLOCKED, 0 executor ready, 0 approved ADR, all release classes UNDECIDED, engine_implemented=false, NLE-D009 engine license OPEN.


**NO ACTUAL ENGINE BUILD OR BENCHMARKS, GPU/CPU/VRAM/POWER THERMAL OBSERVATIONS, C++ PROFILER INSTALL, TRACE FILE, CI CTEST OR PUBLIC RELEASE.** All p50/p95/p99 examples are methodological, NOT observations. Research issue #349 OPEN until independent checkpoint; future coding #92 OPEN/BLOCKED.

## 1. Pre-write GitHub SOURCE CHECK ACTUALLY OBSERVED
- Main HEAD **a81a924b921da629c74ca6d3f4ccb7a2a72e3c19**, 0 open PRs, file tree no QA-03 new research/ADR-0077. Only pre-existing `.github/workflows/docs.yml` Docs Validation, not C++ build or GPU profiler; Source Hierarchy checkpoint > approved Decisions Ledger/ADR > Scope > DoD > Architecture > Requirements.
- Registry exactly 80 modules: QA-03 **ordinal 74 RESEARCH_PENDING**, **73/80 research documented, 7 pending, ALL 80/80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release classes UNDECIDED, engine_implemented=false**. NLE-D009 source engine license OPEN, no public MVP NLE-D013.
- Formal dependency **EXACT QA-02 + CORE-06 + GFX-08**. Prior [QA-02 ADR-0076](../adr/0076-qa-02-deterministic-golden-regression-policy.md), [CORE-06 ADR-0008](../adr/0008-core-06-observability-policy.md), [GFX-08 ADR-0021](../adr/0021-gfx-08-vfx-graph-particle-policy.md), ALL PROPOSED, no implemented or approved engine. QA-02 golden and original scene, CORE-06 owned typed metrics, GFX-08 particle graph; other owners are integration only.
- [Context Lock in WO](../work-orders/NLE-P00-WO-002-QA-03.md) lists exact baseline Git **blob SHA-1 OIDs**, **NOT raw SHA256** (future executor must calculate SHA256 before approving code). Baseline no changes to critical canonical sources.

## 2. Official references checked, candidates NOT adopted
- [Khronos Vulkan queries](https://docs.vulkan.org/spec/latest/chapters/queries.html) valid bits/timestampPeriod/queue cross clock/fences, [VK_EXT_memory_budget](https://docs.vulkan.org/refpages/latest/refpages/source/VK_EXT_memory_budget.html) dynamic per-heap memory use/budget rather than installed physical VRAM; no GPU query actually run.
- [Microsoft D3D12 timestamp](https://learn.microsoft.com/en-us/windows/win32/direct3d12/timing) frequency/calibration/heap/copy queue and idle clock drift; [DXGI memory budget](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgiadapter3-queryvideomemoryinfo) dynamic current process budget/usage; no Windows hardware.
- [Apple Metal counter sets](https://developer.apple.com/documentation/metal/gpu-counters-and-counter-sample-buffers) per supported device/counter sample, [CPU/GPU clock correlation](https://developer.apple.com/documentation/metal/converting-gpu-timestamps-into-cpu-time) and [recommendedMaxWorkingSetSize](https://developer.apple.com/documentation/metal/mtldevice/recommendedmaxworkingsetsize), currentAllocatedSize/unified RAM; no physical Mac.
- [W3C WebGPU](https://www.w3.org/TR/webgpu/) optional privacy-quantized `timestamp-query`, no browser or real WebGPU sample and no universal browser tier guaranteed.
- [Tracy](https://github.com/wolfpld/tracy) profiler BSD-3, [Google Benchmark](https://github.com/google/benchmark/blob/main/docs/user_guide.md) Apache2 candidate, [PresentMon MIT](https://github.com/GameTechDev/PresentMon/blob/main/LICENSE.txt) present/ETW, [RenderDoc MIT](https://renderdoc.org/), [Linux perf_event_open](https://man7.org/linux/man-pages/man2/perf_event_open.2.html) permissions, [Nsight Systems](https://developer.nvidia.com/nsight-systems/get-started) and Xcode/PIX/AMD proprietary/free tools conditional. No licenses accepted, no vendor account/payments, no downloaded tools.
- [GitHub Actions billing](https://docs.github.com/en/billing/concepts/product-billing/github-actions) standard hosted public compute free **conditional**, artifact storage and larger/private runners not universally zero; hosted VM cannot prove physical GPU/VRAM/energy. No cost usage actually collected.
- p50/p95/p99, block bootstrap paired independent sessions, actual hardware/driver/quality tier with visual QA-02 gate and recording overhead **are protocols only**; no empirical confidence intervals or measured frame metrics.

## 3. Exactly EIGHT NEW Markdown research files
1. [Architecture](../architecture/qa-03-performance-lab-scalability.md).
2. [ADR-0077 PROPOSED](../adr/0077-qa-03-statistical-performance-tier-policy.md).
3. [Research technology/license/security/cost matrix](../research/qa-03-profilers-gpu-counters-license-cost-matrix.md).
4. [Versioned semantic performance evidence API](../contracts/qa-03-performance-evidence-api.md).
5. [128 FUTURE Q03-T001..Q03-T128](../testing/qa-03-acceptance-matrix.md).
6. [Future statistical benchmark protocol](../research/qa-03-benchmark-statistical-protocol.md).
7. [Research Work Order](../work-orders/NLE-P00-WO-002-QA-03.md).
8. This Evidence Bundle.

## 4. Difference between research and real proof
| Documented candidate / Source Check | Missing executable/runtime evidence |
|---|---|
| Source and proposed owner DAG true | No QA-02/C++ game scene or CORE-06 tracing/VFX effect runtime |
| Vulkan/DX/Metal/WebGPU counter concepts and clocks | No real timestamp query, GPU/fence, driver or display/present trace |
| VRAM dynamic budgets CPU/unified memory model | No allocations/VRAM usage/residency or GPU pressure measurements |
| Candidate low/balanced/high/cinematic tier requirements | No owner-approved FPS/p95/p99 target/low-end device, no graphical benchmark |
| Tracy/Google Benchmark/PresentMon/perf/profilers | No native tool installation or benchmark session |
| Fixed raw quantile/block bootstrap method | No measured statistical confidence/effect size |
| 128 unique future test intentions | All FUTURE/NOT EXECUTED, no PASS |
| CI Docs Validation (PENDING actual research run) | No CI engine compile, GPU/physical thermal validation or published release |

## 5. PR/CI/Audit PENDING actual occurrence
Research branch `docs/NLE-P00-WO-002-QA-03-performance-research`, BASE `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`. Do **not** preclaim PR/head number, actual GitHub Docs run/job SUCCESS, objective pt-BR audit, squash SHA or readback until observed. Risk LOW for research, future perf instrumentation ELEVATED, privileged sensitive operations HIGH_ASSURANCE. No owner approval source license/release/hardware.

## 6. Checkpoint Delta PROPOSAL ONLY
After exact-head Docs Validation SUCCESS, objective pt-BR audit APPROVED, normal squash/main readback, independent **FIVE MODIFIED** checkpoint/backlog/registry JSON/this WO/Evidence. **Sole registry semantic QA-03 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, other 79 module objects/root unchanged. Expected **74/80 researched (92.5%), 6 pending, ALL 80 code WOs BLOCKED, ready=0, approved ADR=0, releases UNDECIDED, engine=false**. Own CI/audit/squash/main readback before issue research #349 CLOSED, coding #92 OPEN/BLOCKED. Then **four Markdown historical PR** own CI/audit/squash/readback and next REAL module **QA-04 Security, Fuzzing & Supply Chain** ordinal 75/80 formal **QA-01 + NET-06 + AI-06**, future code [#93](https://github.com/KayzenRoot/stormline/issues/93) OPEN/BLOCKED.
