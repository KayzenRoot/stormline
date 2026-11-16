# NLE-P00-WO-002-QA-03 — Performance Lab & Scalability Tiers P00 Research Work Order

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research issue #349](https://github.com/KayzenRoot/stormline/issues/349) OPEN until audited independent checkpoint | future code [#92](https://github.com/KayzenRoot/stormline/issues/92) OPEN/BLOCKED | SOURCE main `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`.** Catalog QA-03 order 74/80, **FORMAL PREREQS EXACT QA-02 + CORE-06 + GFX-08**, prior ADR-0076/0008/0021 all PROPOSED. Baseline 73/80 documented, 7 pending, all 80 code packets BLOCKED, 0 executor ready, 0 approved ADR, all release classes UNDECIDED, engine_implemented=false, NLE-D009 engine license OPEN.


**Documentary risk LOW.** Future native GPU/driver trace, physical OS benchmarking, untrusted fixture parsing and thermal/energy ELEVATED. Privileged profiling, private telemetry/signing/release HIGH_ASSURANCE. No actual code/testing/hardware task authorized.

## OBJECTIVE
Research a technically rigorous, statistically valid, R$0-targeted Stormline performance lab for original 2D/2.5D/3D/Web scenes: CPU/GPU/present frametimes p50/p95/p99, frame pacing, pipeline queues/timestamps/calibration for Vulkan/D3D12/Metal/WebGPU, CPU RAM/OS VRAM budget/streaming/allocator usage, VFX scalability, affordable integrated and discrete real GPU classes, quality tier architecture with fidelity QA-02 gates, cold-vs-warm shader/asset caches, trace overhead, power/thermal and regression comparison, security/licensing/rights/evidence. Produce ADR PROPOSED + eight docs and exactly 128 **FUTURE NOT_EXECUTED** acceptance cases. Catalog acceptance **"Benchmarks comparáveis p50/p95/p99 por hardware e quality tier."** Remains NOT IMPLEMENTED.

## CONTEXT/SOURCE CHECK
Source order checkpoint > Decisions Ledger/approved ADR > Scope > DoD > Architecture > Requirements > other; AGENTS Git/code/test evidence prevails. Main HEAD exactly **a81a924b921da629c74ca6d3f4ccb7a2a72e3c19**, no open PR, docs-only `.github/workflows/docs.yml`, clean tree no QA-03 new files/ADR-0077. Registry **80 modules, 73 researches documented, 7 pending, QA-03 ordinal 74 RESEARCH_PENDING, 80/80 future coding WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, all release_class UNDECIDED, engine_implemented=false**. NLE-D009 source license OPEN, D013 no public MVP, D014 2D/2.5D/3D/Web, D017 Windows/Linux/macOS Editor/game desktop required (Web planned), D018 safe documentary automation/no expenses, D019/20 prepared coding queue blocked. Formal deps **ONLY QA-02 + CORE-06 + GFX-08**, ADR-0076/0008/0021 all PROPOSED. QA-01/04/05, GFX-01/03, PLAT, DATA, GAME, CORE other and BIZ are transitive/integration ONLY, never new formal graph edges.

## CONTEXT LOCK — immutable Git blob OIDs, NOT raw SHA-256
Source BASE exact main commit `a81a924b921da629c74ca6d3f4ccb7a2a72e3c19`. Object hashes below are Git blob identifiers (SHA-1), **not raw file SHA-256**. A future code executor must compute SHA256 fingerprints and stop STALE if checkpoint, decisions, Scope, DoD, Architecture, Requirements, catalog/registry, QA-02/CORE-06/GFX-08 critical documents or HEAD change.
- `AGENTS.md`: `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md`: `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md`: `b3c10f621adafbd5496a8dbd397737e60544329c`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md`: `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md`: `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json`: `c78d203a0b326c20eed2f79535e480bc35dba898`
- `docs/queue/work-orders/QA-03.md`: `cd0fc3533f4cdbb2eee8b35255cd20286fb0c66a`
- `.github/workflows/docs.yml`: `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`
- `docs/adr/0076-qa-02-deterministic-golden-regression-policy.md`: `3b26fb16204369b015d2c4b66aaa37c7592cb57f`
- `docs/adr/0008-core-06-observability-policy.md`: `208f12cee3538c4d1471d8a2de937e9b9ed754b9`
- `docs/adr/0021-gfx-08-vfx-graph-particle-policy.md`: `ee87b963fd5953e2faf646cbc9d9d02723819ec0`
- `docs/contracts/qa-02-test-fixture-evidence-api.md`: `0ca60bab3a5474339e2ab977ac6a0ca57754804c`
- `docs/contracts/gfx-08-vfx-api.md`: `531cc596ff25e5964ec27e9e43d3a4f583dfcd36`
- `docs/architecture/core-06-diagnostics-observability.md`: `12893dcb7bcd7c263f979a3b12202126e5791491`

## SCOPE — EXACTLY EIGHT NEW Markdown (NECESSARY)
1. [Architecture](../architecture/qa-03-performance-lab-scalability.md).
2. [ADR-0077 PROPOSED](../adr/0077-qa-03-statistical-performance-tier-policy.md).
3. [2026 profilers/counters/cost/licensing/security research matrix](../research/qa-03-profilers-gpu-counters-license-cost-matrix.md).
4. [Versioned semantic performance experiment/evidence API](../contracts/qa-03-performance-evidence-api.md).
5. [Exactly 128 FUTURE Q03-T001..Q03-T128 cases](../testing/qa-03-acceptance-matrix.md).
6. [Statistically valid benchmark and quality tiers protocol](../research/qa-03-benchmark-statistical-protocol.md).
7. This Work Order.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-QA-03.md).

Initial research branch/PR only **8 ADDED Markdown**, no change existing registry/checkpoint/backlog/workflows, engine source, ADR predecessor, license, hardware tools or future code issues. Subsequent 5-file independent checkpoint and final 4-Markdown history are separate sequential PRs, not in initial scope.

## OUT OF SCOPE
No C++ profiling code, Tracy/Google Benchmark integration or binaries, actual GPU query, CPU/GPU frame sample/benchmark, original scene/sample/render, physical hardware purchase/usage, screenshot trace/proprietary content, simulator/mobile target, paid service/device/cloud runner, sensor root permissions, new GitHub CI/ruleset, source engine license ratification, release-class adoption, production telemetry/deploy, public engine MVP, broad cleanup or rewriting approved ADRs.

## FILES/SOURCES TO READ
All Context Lock sources and original future code [#92](https://github.com/KayzenRoot/stormline/issues/92); actual QA-02/CORE-06/GFX-08 architectures and semantic API. 2026 official authoritative sources [Vulkan query spec](https://docs.vulkan.org/spec/latest/chapters/queries.html), [VK_EXT_memory_budget](https://docs.vulkan.org/refpages/latest/refpages/source/VK_EXT_memory_budget.html), [D3D12 GPU timing](https://learn.microsoft.com/en-us/windows/win32/direct3d12/timing), [DXGI memory info](https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgiadapter3-queryvideomemoryinfo), [Metal counter sets](https://developer.apple.com/documentation/metal/gpu-counters-and-counter-sample-buffers), [Metal CPU/GPU clocks](https://developer.apple.com/documentation/metal/converting-gpu-timestamps-into-cpu-time), [Metal memory budget](https://developer.apple.com/documentation/metal/mtldevice/recommendedmaxworkingsetsize), [WebGPU](https://www.w3.org/TR/webgpu/), [Tracy](https://github.com/wolfpld/tracy), [PresentMon](https://github.com/GameTechDev/PresentMon), [Google Benchmark](https://github.com/google/benchmark/blob/main/docs/user_guide.md), [Linux perf events](https://man7.org/linux/man-pages/man2/perf_event_open.2.html), [GitHub Actions costs](https://docs.github.com/en/billing/concepts/product-billing/github-actions). Exact versions/licenses/platform compatibility to be reverified upon owner activation.

## REQUIREMENTS
GOV-001..005 source hierarchy PR audit free CI R$0, NLE-D009/013..020, catalog performance acceptance. Quality, timing and memory measured on actual licensed original scene+driver and runtime, no false precision. Stable original 2D/2.5D/3D scene and VFX fidelity under QA-02, CORE-06 locally owned telemetry/privacy, GFX-08 live particle bounds, frame results p50/p95/p99 by exact comparable tier/hardware. Future hardware/cost and code blocked pending approval.

## ARCHITECTURE RULES
1. Typed `PerfExperimentRequestV1`, `PerfHardwareProfileV1`, `PerfClockDomainV1`, `PerfFrameRecordV1`, `PerfGpuQueryReceiptV1`, `PerfMemoryBudgetV1`, `PerfStatisticsV1`, `PerfPairedRegressionV1` and `PerfEvidenceReceiptV1` proposed; no vendor pointers in public ABI or double-implement CORE-06 diagnostics.
2. CPU busy vs wall/submit, GPU pass vs queue and present/display pacing separate. Vulkan nonzero timestampValidBits/timestampPeriod, D3D12 query heap/frequency/calibration, Metal supported counter sets/CPU GPU alignment, WebGPU timestamp-query optional privacy rounded. Must wait fences, handle wrap/clock error and unsupported APIs; no GPU timings from CPU-only runner.
3. Dynamic VRAM budgets Vulkan heapBudget/heapUsage, DXGI Budget/CurrentUsage, Metal currentAllocatedSize/recommendedMaxWorkingSetSize/unified RAM. Track residency/peak/fragmentation and streaming stutters, no static VRAM = usable budget guarantee or shared RAM double-count.
4. QA-02 original fixtures+goldens and GFX-08 graph/particle fidelity must pass. Quality tier settings LOW/BALANCED/HIGH/CINEMATIC merely candidate, no release class or FPS target/DoD approved; wrong frame/graphics cannot count as faster PASS.
5. Workload pin scene SHA, GPU/driver/OS/browser/hardware physical flag, compiler/shader/graph, render resolution/postfx/asset config, clock, Hz/VRR, power/thermal sensor and cold/warm cache, seed camera/input, trace overhead, lost events and timeouts.
6. Ordered raw frame intervals, quantile method predeclared, p50/p95/p99 with independent sessions and block bootstrap for correlated frames, randomized paired ABBA A/B test, same hardware/tier + uncertainty; no p99 claim from 5 samples, no post-hoc outlier deletion or incomplete sample coercion.
7. Profiling future Travis? **NO**; evaluate pinned Tracy BSD-3, Google Benchmark Apache2, PresentMon MIT, RenderDoc MIT, Vulkan tools Apache2 and proprietary Xcode/PIX/Nsight availability; no subscriptions, remote telemetry, privileged access or cloud GPU. Standard hosted free public runner compute cannot certify actual physical GPU/energy and artifacts/cache storage may cost.
8. Security/local privacy: default local opt-in, redact user scene/shader/filepaths/device IDs and trace data, parser size caps, no untrusted arbitrary benchmark fixture scripts, no hidden network endpoints or false hardware source and no public release until full v1.0 DoD and engine source license resolved.

## CONSTRAINTS
LOW documentary research and real Docs Validation only, no Source Pack rewrite, no new code CI, no authorization for paid hardware/cloud or privileged sensor, no force push/historical rewriting or accidental commit of binary, no HIGH/CRITICAL known defect, stop if STALE or accepted predecessor changes. All 80 implementation packets remain BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 NEW .md in research PR, relative links valid, no existing source/CI/registry/checkpoint/backlog changes.
- [ ] ADR-0077 PROPOSED; three formal QA-02+CORE-06+GFX-08 dependencies unchanged, predecessor ADRs PROPOSED.
- [ ] Deep 2026 official research on clocks, Vulkan/D3D12/Metal/WebGPU, actual/present clocks, memory budget, VFX scale, statistical methods, quality tiers, physical hardware/thermal/power/privacy/security/licenses/free costs, no fabricated measurement.
- [ ] Exactly 128 sequential unique Q03-T001..Q03-T128 eight groups×16, all FUTURE/NOT EXECUTED, benchmark protocol explicit.
- [ ] Research own exact-head Docs Validation SUCCESS, objective audit pt-BR APPROVED, normal squash/main readback.
- [ ] Independent checkpoint exactly **5 MODIFIED** docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this WO and Evidence. **SOLE semantic registry QA-03 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`**, remaining 79 modules/root identical, target **74/80 researches (92.5%), 6 pending, ALL 80 code WOs BLOCKED, executor_ready=0, approved_adr=0, all release classes UNDECIDED, engine=false**. Own Doc CI/audit/squash/main readback before closing research #349, coding #92 OPEN/BLOCKED.
- [ ] Final separate four-Markdown factual historical closeout checkpoint/backlog/WO/Evidence own Docs CI/audit/squash/main readback, next REAL QA-04 Security Fuzzing & Supply Chain ordinal 75/80 formal QA-01+NET-06+AI-06, future code #93 BLOCKED.

## TESTS
P00 only Docs Validation Source Pack relative links/catalog DAG/80 registry+Zcode selector blocking, changed-file statuses, 128 unique Q03 test ID check and sole JSON semantic delta, actual CI run/job evidence. **No real C++/GPU code, Vulkan/D3D12/Metal/WebGPU timestamps, profiling/VRAM/thermal, benchmark/p50/p95/p99 or hardware testing executed.** Future testing requires actual all targets, QA-02 fixture and known hardware classes, repeatable statistical confidence and owner DoD.

## DELIVERABLES
Issue research #349, eight Markdown, research PR/own CI+pt-BR audit/normal squash/readback, independently audited five-file checkpoint then close #349, separate factual four-Markdown historical PR with own CI/audit/squash/readback and next module CTA. No engine code.

## REVIEW FORMAT
pt-BR objective Source Check BASE/HEAD/critical blob OIDs (SHA-1 Git vs raw SHA256), exact three formal dependencies, file status/diff/test count, tool license/cost/security and privacy, clock/VM/statistics truth, Docs CI actual job/run, no fake GPU benchmark, finding risk HIGH/CRITICAL, verdict **APPROVED / CORRECTION REQUIRED / BLOCKED**, Checkpoint Delta and readback. No acceptance of implementation from DOCS green.

## STOP CONDITION
If stale Scope/DoD/checkpoint/ADR, extra formal edges, wrong eight docs/128 IDs, failed Doc CI, unapproved paid/hardware/privileged capture, HIGH/CRITICAL, fake stats/physical GPU/result or missing reviewer => BLOCKED or CORRECTION REQUIRED same WO/PR. No QA-04 planning until QA-03 history audited/merged/readback. No coding unlock.

## CHECKPOINT DELTA PROPOSAL ONLY
After research verified CI/audit/squash/readback, independent five-file checkpoint single QA-03 research_status change 73 ->74 researched, 7->6 pending, other 79 unaffected; own CI/audit/squash/main, close research #349 only after proof. Future code #92 remains OPEN/BLOCKED. Separate four-Markdown historical record own gates then QA-04 formal QA-01+NET-06+AI-06.
