# ADR-0040 — Engine-owned Immutable DSP Graph, AUD-01 Mixer Authority and Safe External Plugin Boundary

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
2026-11-14 | Research issue #201 | WO NLE-P00-WO-002-AUD-03 | Future coding #54 OPEN/BLOCKED.

## Context
AUD-01 owns output callback, voice, buses and audio sample clock. AUD-02 owns spatial acoustic/HRTF scene and may request IR convolution. DSP must process filters, dynamics, EQ, nonlinear effects and parameter automation with low-latency, predictable CPU and no callback blocking. A mutable dynamic graph or arbitrary native plugins can create cycles, heap churn, priority inversion, races, sensitive audio data exfiltration and unpredictable sound output. The project has no executable audio system or selected backend.

## PROPOSED decision
1. **Unique mixer owner:** AUD-01 controls devices, voice allocation, sample-frame clock, bus topology/routing/mix. AUD-03 owns effect-node semantic SDK and processing plan, not a second PCM mixer or device backend. AUD-02 provides room/IR/HRTF profiles; AUD-03 handles reusable DSP kernels only where actually needed, without duplicate HRTF processing.
2. **Type-validated DAG and off-RT compiler:** use versioned EffectGraph, Node/Port/Edge/Sidechain, Parameter/Automation and Snapshot contracts. Validate source rights/graph ownership, finite budgets, channels, sample layout, latency/tail, cycles and feedback, compile on CORE-03 worker and install immutable `DspExecutionPlan` at AUD-01 quantum boundary with deferred buffer/node retirement; reject zero-delay cycles. Feedback effects only with explicit stable bounded internal delay and future proofs.
3. **Realtime by construction:** callbacks accept preallocated buffers, fixed bounded node kernels and atomically published param segment events. No allocation/deallocation, locks/waits, blocking IPC, FFT/IR plan creation, file/network, plugin initialization, logging or dynamic graph rebuild on audio thread. Every allowed node has declared scratch bytes/latency/tail and worst-case time target; numerical targets TBD from measured hardware.
4. **First-party deterministic-safe kernels first:** gain, pan-aligned bypass, stable finite EQ/biquad filters, dynamic range compressor/expander/gate, bounded limiter, saturation and short delay, plus advanced FX/convolution after proof. Clip/NaN/denormal protection and explicit true-peak vs sample-peak semantics, quality degradation receipt, sidechain latency and click-free automation.
5. **Single sample-clock mapping:** AUD-01 controls `DeviceEpoch` + `SampleFrameId`; CORE-04 TickId maps rationally to precompiled sample offsets. Per-sample precision depends on node and declared capability, not assumed universal. RTPC command arbitration and snapshots are versioned authorized, buffered, rate-limited and role-checked.
6. **Native third-party plugins excluded baseline:** CLAP MIT/LV2 ISC are possible **future adapter standards**, not safe sandbox or automatic free rights for effect plugins. Arbitrary third-party native code may only run behind explicit opt-in and a demonstrated isolated/watchdog process or approved bounded WASM route, with measured latency/nonblocking RT bridge and safe bypass on crashes. If not feasible, **PROVE-OR-DROP**. In-process untrusted plugins are prohibited.
7. **Research technology status only:** DSPFilters MIT and Airwindows MIT as candidate algorithm/reference, KissFFT BSD-3 for optional FFT; FFTW GPL v2/commercial **not allowed as default runtime dependency** without approved engine license/legal obligations; Faust compiler LGPL vs generated code licenses **depend on individual input libraries/architecture** (GPL portions must be excluded) and Soundpipe MIT archived; no package installed/adopted, NLE-D009 engine software license OPEN.
8. **Security/portable proof gate:** strict schema/IR quotas and source rights, off-RT graph jobs, role/NET separation, native/headless/browser capability, future 128+ tests/benchmarks/ASan/TSan/fuzz and replay/rollback. Only measured evidence can certify real-time stability, clipping, CPU/latency, quality or engine superiority.

## Rejected alternatives
- Two separate bus mixers/device clocks managed by AUD-01 and AUD-03; ad hoc graph edits inside realtime callback.
- A zero-delay cyclic graph with recursive feedback, unbounded IR/FFT or hidden per-quantum allocations.
- Loading downloaded native CLAP/VST/LV2 plugins in process and calling them sandboxed.
- Treating compiler, plugin standard or library license as permission to ship proprietary DSP modules/sample content without per-file review.
- Claiming a sample-peak limiter detects intersample peaks or "zero latency" with lookahead/convolution.
- CPU-quality degradation that drops dialogue/gameplay event, or client DSP parameter update that grants gameplay authority.
- Auto-promoting this PROPOSED ADR into the code registry/issue #54 or advancing next module before checkpoint.

## Consequences and approval gate
Cost: own typed graph compiler/snapshot lifecycle, fixed latency compensation, per-node testing, security boundary and fallback; benefit: portable, predictable headless and safe realtime module ownership. Before any implementation, require AUD-01 executable API, approved ABI/release slice, numerical budgets, pinned source rights/SBOM, original PCM golden and callback instrumentation, crash/isolation tests and pt-BR objective audit. **No code, SDK, audio or tests implemented now. All 80 coding packets BLOCKED and issue #54 OPEN/BLOCKED.**
