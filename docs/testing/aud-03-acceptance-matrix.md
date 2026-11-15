# AUD-03 — Acceptance Matrix: 128 FUTURE Tests, NONE Executed

**Research issue #201 | WO NLE-P00-WO-002-AUD-03 | Future coding #54 OPEN/BLOCKED.** Exactly **128 proposed cases** (16 suites × 8). Every case below is **FUTURE / NOT EXECUTED**. Catalog acceptance **"Graph validado, teste de clipping, estabilidade em tempo real"** is **NOT MET** by documentation. No actual graph, compiled kernel, signal, plugin, native/Web audio runtime, callback profiler, frequency graph or benchmark output exists.

| Case | Prospective scenario | Status |
|---|---|---|
| AUD03-SRC-01 | Original legal graph source AssetId/revision resolves | FUTURE / NOT EXECUTED |
| AUD03-SRC-02 | Reject unauthorized third-party impulse response licensing | FUTURE / NOT EXECUTED |
| AUD03-SRC-03 | Invalid node count/huge edge fanout rejected | FUTURE / NOT EXECUTED |
| AUD03-SRC-04 | Duplicate NodeGuid and unknown port rejected | FUTURE / NOT EXECUTED |
| AUD03-SRC-05 | DATA-04 CAS conflict prevents partial graph save | FUTURE / NOT EXECUTED |
| AUD03-SRC-06 | Corrupt preset, parameter units and source revision rejected | FUTURE / NOT EXECUTED |
| AUD03-SRC-07 | No native executable script/file path accepted as graph source | FUTURE / NOT EXECUTED |
| AUD03-SRC-08 | Authoring schema parity Editor/CLI/MCP and dry-run receipts | FUTURE / NOT EXECUTED |
| AUD03-DAG-01 | Simple gain→EQ→master topological schedule oracle | FUTURE / NOT EXECUTED |
| AUD03-DAG-02 | Parallel sidechain/input graph processes each edge once | FUTURE / NOT EXECUTED |
| AUD03-DAG-03 | Reject zero-delay signal graph cycle before plan | FUTURE / NOT EXECUTED |
| AUD03-DAG-04 | Explicit delay in feedback path needs bounded stability proof | FUTURE / NOT EXECUTED |
| AUD03-DAG-05 | Bus ownership prevents second AUD-01 mix routing | FUTURE / NOT EXECUTED |
| AUD03-DAG-06 | Cross-channel send matrix rejects wrong layout and loop | FUTURE / NOT EXECUTED |
| AUD03-DAG-07 | Max node depth/fanout and scratch bytes fit quotas | FUTURE / NOT EXECUTED |
| AUD03-DAG-08 | Failure of graph compile preserves last safe snapshot | FUTURE / NOT EXECUTED |
| AUD03-EQF-01 | Biquad peak at center frequency matches analytic response | FUTURE / NOT EXECUTED |
| AUD03-EQF-02 | Lowpass magnitude/phase at cutoff and Nyquist measured | FUTURE / NOT EXECUTED |
| AUD03-EQF-03 | Highpass zero/DC response check | FUTURE / NOT EXECUTED |
| AUD03-EQF-04 | High shelf and low shelf gains match specified dB | FUTURE / NOT EXECUTED |
| AUD03-EQF-05 | Reject f<=0 or >=Nyquist and infinite Q | FUTURE / NOT EXECUTED |
| AUD03-EQF-06 | Pole radius stability under coefficient interpolation | FUTURE / NOT EXECUTED |
| AUD03-EQF-07 | Sample-rate change recompiles valid coefficients | FUTURE / NOT EXECUTED |
| AUD03-EQF-08 | Denormals/NaN/Inf audio and parameter input fail safely | FUTURE / NOT EXECUTED |
| AUD03-DYN-01 | Compressor attack/release envelope measured vs reference | FUTURE / NOT EXECUTED |
| AUD03-DYN-02 | Ratio/thresh/knee and makeup gain match analytic law | FUTURE / NOT EXECUTED |
| AUD03-DYN-03 | Sidechain key input aligned with graph latency | FUTURE / NOT EXECUTED |
| AUD03-DYN-04 | Peak vs RMS envelope differences declared and verified | FUTURE / NOT EXECUTED |
| AUD03-DYN-05 | Expander/gate hysteresis avoids rapid gain chatter | FUTURE / NOT EXECUTED |
| AUD03-DYN-06 | Time constants zero/negative rejected/typed fallback | FUTURE / NOT EXECUTED |
| AUD03-DYN-07 | Fast transients do not produce infinite gain/NaN | FUTURE / NOT EXECUTED |
| AUD03-DYN-08 | Dialogue priority and RTPC do not change GAME authority | FUTURE / NOT EXECUTED |
| AUD03-LIM-01 | Hard clip saturates finite float32 reference | FUTURE / NOT EXECUTED |
| AUD03-LIM-02 | Soft-clip THD+N/reference quality measurement | FUTURE / NOT EXECUTED |
| AUD03-LIM-03 | Sample-peak limiter preserves defined output threshold | FUTURE / NOT EXECUTED |
| AUD03-LIM-04 | True-peak limiter oversampled reconstruction tested separately | FUTURE / NOT EXECUTED |
| AUD03-LIM-05 | Lookahead latency included in graph reported frames | FUTURE / NOT EXECUTED |
| AUD03-LIM-06 | No invalid makeup gain triggers loud unsafe output | FUTURE / NOT EXECUTED |
| AUD03-LIM-07 | Intersample peak test detects sample-only limiter limitation | FUTURE / NOT EXECUTED |
| AUD03-LIM-08 | Silent/master mute transitions no click/no stale output | FUTURE / NOT EXECUTED |
| AUD03-DEL-01 | Circular delay ring wraps at exact declared sample | FUTURE / NOT EXECUTED |
| AUD03-DEL-02 | Fractional delay interpolation matches golden input | FUTURE / NOT EXECUTED |
| AUD03-DEL-03 | Feedback magnitude>=1 bounded/rejected unless proven stable | FUTURE / NOT EXECUTED |
| AUD03-DEL-04 | Delay reset/reload preserves no stale buffers | FUTURE / NOT EXECUTED |
| AUD03-DEL-05 | Chorus LFO rate/depth smoothing avoids zipper noise | FUTURE / NOT EXECUTED |
| AUD03-DEL-06 | Flanger variable delay signal doesn't allocate on callback | FUTURE / NOT EXECUTED |
| AUD03-DEL-07 | Stereo delay/pan preserve channel layout and labels | FUTURE / NOT EXECUTED |
| AUD03-DEL-08 | Infinite/reverse/negative delay time rejected | FUTURE / NOT EXECUTED |
| AUD03-REV-01 | Original synthetic IR produces known convolved output | FUTURE / NOT EXECUTED |
| AUD03-REV-02 | IR licensing and DATA-05 source hash validated | FUTURE / NOT EXECUTED |
| AUD03-REV-03 | Long IR max taps and partition memory cap enforced | FUTURE / NOT EXECUTED |
| AUD03-REV-04 | KissFFT plan prebuilt on CORE-03 not realtime callback | FUTURE / NOT EXECUTED |
| AUD03-REV-05 | Partitioned overlap-save/add buffer boundary continuity | FUTURE / NOT EXECUTED |
| AUD03-REV-06 | Wet/dry and sidechain convolution latency compensated | FUTURE / NOT EXECUTED |
| AUD03-REV-07 | Room HRTF material selected by AUD-02 not DSP scene solver | FUTURE / NOT EXECUTED |
| AUD03-REV-08 | IR hot reload drains old tail under policy without UAF | FUTURE / NOT EXECUTED |
| AUD03-RTS-01 | TickId rationally mapped to SampleFrame offset | FUTURE / NOT EXECUTED |
| AUD03-RTS-02 | Sample-accurate gain ramp per supported node granularity | FUTURE / NOT EXECUTED |
| AUD03-RTS-03 | Control-rate-only node reports quantized timing correctly | FUTURE / NOT EXECUTED |
| AUD03-RTS-04 | Simultaneous parameter events deterministic precedence | FUTURE / NOT EXECUTED |
| AUD03-RTS-05 | Unauthorized client/MCP DSP event rejected | FUTURE / NOT EXECUTED |
| AUD03-RTS-06 | Burst >per-block event quota returns typed overflow | FUTURE / NOT EXECUTED |
| AUD03-RTS-07 | Automation segment graph hot swap at quantum fence | FUTURE / NOT EXECUTED |
| AUD03-RTS-08 | Rollback/replay restores parameter values and curve cursor | FUTURE / NOT EXECUTED |
| AUD03-SNP-01 | DspPlanRevision immutable across realtime quantum | FUTURE / NOT EXECUTED |
| AUD03-SNP-02 | Old graph buffer freed only after AUD-01 callback ack | FUTURE / NOT EXECUTED |
| AUD03-SNP-03 | DeviceEpoch change invalidates stale compiled plan | FUTURE / NOT EXECUTED |
| AUD03-SNP-04 | Rate/layout reconfiguration compiles new graph offline | FUTURE / NOT EXECUTED |
| AUD03-SNP-05 | Bypass crossfade preserves tail or explicit tail cutoff | FUTURE / NOT EXECUTED |
| AUD03-SNP-06 | Simultaneous graph insert/remove creates no UAF | FUTURE / NOT EXECUTED |
| AUD03-SNP-07 | Crash mid DATA-04 authoring leaves canonical old revision | FUTURE / NOT EXECUTED |
| AUD03-SNP-08 | Duplicate delete/stop of NodeHandle idempotent | FUTURE / NOT EXECUTED |
| AUD03-LAT-01 | Parallel dry/wet paths align under node lookahead delay | FUTURE / NOT EXECUTED |
| AUD03-LAT-02 | Sidechain path aligns envelope to signal frame | FUTURE / NOT EXECUTED |
| AUD03-LAT-03 | Biquad near-zero latency declared separately from IR | FUTURE / NOT EXECUTED |
| AUD03-LAT-04 | Convolution FFT partition latency accounted not disguised | FUTURE / NOT EXECUTED |
| AUD03-LAT-05 | Graph cumulative latency matches measured impulse response | FUTURE / NOT EXECUTED |
| AUD03-LAT-06 | TailFrames finite and capped during voice/bus shutdown | FUTURE / NOT EXECUTED |
| AUD03-LAT-07 | Sample-rate mismatch can't silently halve/double delay | FUTURE / NOT EXECUTED |
| AUD03-LAT-08 | Graph rebuild latency event published to AUD-01 clock map | FUTURE / NOT EXECUTED |
| AUD03-PLG-01 | Native untrusted CLAP plugin rejected by default | FUTURE / NOT EXECUTED |
| AUD03-PLG-02 | Valid CLAP API host compatibility not considered sandbox | FUTURE / NOT EXECUTED |
| AUD03-PLG-03 | LV2 plugin licenses per bundle checked separately | FUTURE / NOT EXECUTED |
| AUD03-PLG-04 | External binary requires explicit owner opt-in and trust policy | FUTURE / NOT EXECUTED |
| AUD03-PLG-05 | Isolated bridge process crash bypasses without audio callback hang | FUTURE / NOT EXECUTED |
| AUD03-PLG-06 | Plugin CPU overrun watchdog and nonblocking ring semantics tested | FUTURE / NOT EXECUTED |
| AUD03-PLG-07 | Plugin cannot access host private audio/creds/network by default | FUTURE / NOT EXECUTED |
| AUD03-PLG-08 | Fuzz malformed plugin descriptors and ABI negotiation safely | FUTURE / NOT EXECUTED |
| AUD03-ACL-01 | GAME/NET roles limit RTPC producer and rate | FUTURE / NOT EXECUTED |
| AUD03-ACL-02 | MCP cannot execute scripts/native plugin load or shell | FUTURE / NOT EXECUTED |
| AUD03-ACL-03 | Audio source PCM not emitted in telemetry without consent | FUTURE / NOT EXECUTED |
| AUD03-ACL-04 | IR decompression bomb bounded at DATA-03 ingress | FUTURE / NOT EXECUTED |
| AUD03-ACL-05 | Feedback/FFT plan allocation DoS rejected pre-callback | FUTURE / NOT EXECUTED |
| AUD03-ACL-06 | Filter coefficient overflow denied without bad audio write | FUTURE / NOT EXECUTED |
| AUD03-ACL-07 | ASan/UBSan/TSan races during device/plan retire future | FUTURE / NOT EXECUTED |
| AUD03-ACL-08 | Graph artifact rights/author provenance retained after migration | FUTURE / NOT EXECUTED |
| AUD03-PER-01 | No malloc/free/new on RT callback path instrumented | FUTURE / NOT EXECUTED |
| AUD03-PER-02 | No mutex/file/network/log in process block | FUTURE / NOT EXECUTED |
| AUD03-PER-03 | Callback handles 0/1/128/256/512 frame requests safely | FUTURE / NOT EXECUTED |
| AUD03-PER-04 | Node CPU quota measured per block and bus | FUTURE / NOT EXECUTED |
| AUD03-PER-05 | Denormal-heavy IIR input doesn't blow CPU time | FUTURE / NOT EXECUTED |
| AUD03-PER-06 | 128 nodes/1000 automation event storm stress | FUTURE / NOT EXECUTED |
| AUD03-PER-07 | RT overload degrades bounded FX but keeps protected dialogue | FUTURE / NOT EXECUTED |
| AUD03-PER-08 | One-hour plugin-disabled stress no state/ring leaks | FUTURE / NOT EXECUTED |
| AUD03-WEB-01 | Windows x64 native DSP/headless compilation and PCM golden | FUTURE / NOT EXECUTED |
| AUD03-WEB-02 | Linux x64/ARM scalar DSP/headless compilation | FUTURE / NOT EXECUTED |
| AUD03-WEB-03 | macOS x64/ARM audio output and layout | FUTURE / NOT EXECUTED |
| AUD03-WEB-04 | Web/WASM AudioWorklet callback with no unsupported native lib | FUTURE / NOT EXECUTED |
| AUD03-WEB-05 | SIMD scalar equivalence within declared error | FUTURE / NOT EXECUTED |
| AUD03-WEB-06 | Output format mono/stereo/5.1 mapped correctly | FUTURE / NOT EXECUTED |
| AUD03-WEB-07 | OS/device suspend/resume recovers plan without stale epoch | FUTURE / NOT EXECUTED |
| AUD03-WEB-08 | GPU absence does not change DSP output event truth | FUTURE / NOT EXECUTED |
| AUD03-QA-01 | Sine sweep magnitude/phase response vs analytic oracle | FUTURE / NOT EXECUTED |
| AUD03-QA-02 | THD+N and alias spectra of saturation curve | FUTURE / NOT EXECUTED |
| AUD03-QA-03 | Impulse/step response of stable filters and feedback delay | FUTURE / NOT EXECUTED |
| AUD03-QA-04 | Reverb T60 estimate synthetic original IR with tolerance | FUTURE / NOT EXECUTED |
| AUD03-QA-05 | Binaural HRTF convolution AUD-02 integrated once not twice | FUTURE / NOT EXECUTED |
| AUD03-QA-06 | Blind listening controls loudness and headset provenance | FUTURE / NOT EXECUTED |
| AUD03-QA-07 | Original input zero/silence and noise without DC leak | FUTURE / NOT EXECUTED |
| AUD03-QA-08 | Latency/performance vs fair baseline no unsupported superiority | FUTURE / NOT EXECUTED |
| AUD03-BEN-01 | 32/64/128 built-in DSP nodes CPU p50/p95/p99 | FUTURE / NOT EXECUTED |
| AUD03-BEN-02 | 4/16 sidechain compressors with gain reduction traces | FUTURE / NOT EXECUTED |
| AUD03-BEN-03 | Convolution IR 0.25/1/4 s CPU/heap/latency | FUTURE / NOT EXECUTED |
| AUD03-BEN-04 | 48k/96k rates with equal block-length ms budget | FUTURE / NOT EXECUTED |
| AUD03-BEN-05 | RTPC 10/100/1000 events/sec and overflow policy | FUTURE / NOT EXECUTED |
| AUD03-BEN-06 | Process crash during graph swap with rollback and resumed output | FUTURE / NOT EXECUTED |
| AUD03-BEN-07 | Latency and clip counters correlate to output capture | FUTURE / NOT EXECUTED |
| AUD03-BEN-08 | Complete benchmark reproducibility SHA/vendor/license/fixtures | FUTURE / NOT EXECUTED |

## Future proof and evidence contract
- **Unit:** graph DAG/topological and sidechain/port validation, stable biquad/analytic filter coefficients, dB/linear units, envelope/gain computer, limiter/clipping oracle, ring delay/feedback stability, RTPC sample frame mapping and versioned parameter snapshots.
- **Integration:** AUD-01 one mix/device/sample clock and NullSink, AUD-02 HRTF/room IR payload without duplicate convolution, AUD-04 future music state RTPC consumer, DATA-03/04/05 source/rights/version, CORE-03 non-RT graph+FFT compiler and CORE-06 metering outside callback.
- **Safety/quality:** callback allocation/locks/IO prohibition, malformed graph/presets/vendor input fuzz, external plugin execution disabled absent sandbox, native/WASM and optional browser, sanitizers, memory/device/hot reload crash recovery. Track peak vs true peak separately, NaN/Inf/denormals, THD+N and audible clipping.
- **Performance:** future original sine/sweep/impulse/noise reference test signals, measured callback xrun/peak and p50/p95/p99 CPU/heap and per-node cost for equal device settings; sample-rate/block/voice/IR sizes, license and device clocks declared in benchmark.
- **Missing evidence:** no PASS for any future case. Existing GitHub Docs Validation checks Source Pack, taxonomy/dependency, work-order registry and Zcode BLOCKED selection **only**, not actual DSP/RT safety. Numerical thresholds and formal risk release conditions remain UNDECIDED.
