# AUD-01 — Acceptance Matrix: 128 FUTURE Cases, None Executed

**Research #195 | WO NLE-P00-WO-002-AUD-01 | Future coding #52 OPEN/BLOCKED | P00 DOCS-ONLY.** Exactly **128 future tests** (16 groups × 8 cases), ALL **FUTURE / NOT EXECUTED**, no audio device, mixer, source, output test, profiler trace, WAV fixture, real latency measurement or build. Catalog target: **"Testes de underruns, latência e custo por quantidade de vozes"** UNMET.

| ID | Future scenario | Status |
|---|---|---|
| AUD01-RT-01 | No allocation on callback path under instrumented allocator | FUTURE / NOT EXECUTED |
| AUD01-RT-02 | No mutex/condition wait or synchronous I/O on callback | FUTURE / NOT EXECUTED |
| AUD01-RT-03 | Callback handles frame count zero, one and configured max | FUTURE / NOT EXECUTED |
| AUD01-RT-04 | Callback duration under declared per-buffer budget measured | FUTURE / NOT EXECUTED |
| AUD01-RT-05 | Large callback count beyond bounds fails safely not buffer overrun | FUTURE / NOT EXECUTED |
| AUD01-RT-06 | No logging/DSP graph compilation/codec decode on callback | FUTURE / NOT EXECUTED |
| AUD01-RT-07 | Reentrant device close waits only on non-RT retirement barrier | FUTURE / NOT EXECUTED |
| AUD01-RT-08 | Silence output initialized on underrun and reports counter | FUTURE / NOT EXECUTED |
| AUD01-CLK-01 | CORE-04 TickId to audio frame rational mapping under 44.1 kHz | FUTURE / NOT EXECUTED |
| AUD01-CLK-02 | Clock mapping 48 kHz with no accumulated integer drift | FUTURE / NOT EXECUTED |
| AUD01-CLK-03 | 100k tick schedule has bounded quantization remainder | FUTURE / NOT EXECUTED |
| AUD01-CLK-04 | DeviceEpoch change rejects stale clock commands | FUTURE / NOT EXECUTED |
| AUD01-CLK-05 | Suspend/resume maps monotonic sample clock with discontinuity receipt | FUTURE / NOT EXECUTED |
| AUD01-CLK-06 | Audio device drift vs game tick reported with error estimate | FUTURE / NOT EXECUTED |
| AUD01-CLK-07 | Rendering 20/60/240 FPS does not change logical audio schedule | FUTURE / NOT EXECUTED |
| AUD01-CLK-08 | Nonfinite/negative timestamp and overflow rejected | FUTURE / NOT EXECUTED |
| AUD01-DEV-01 | Enumerate devices without opening capture microphones | FUTURE / NOT EXECUTED |
| AUD01-DEV-02 | Open default output with actual negotiated format | FUTURE / NOT EXECUTED |
| AUD01-DEV-03 | Mono/stereo/5.1 channel map labels validated | FUTURE / NOT EXECUTED |
| AUD01-DEV-04 | Device format 44.1/48/96 kHz supported or typed fallback | FUTURE / NOT EXECUTED |
| AUD01-DEV-05 | Backend rejects unsupported exclusive mode without fake success | FUTURE / NOT EXECUTED |
| AUD01-DEV-06 | NullSink works with no sound card/headless | FUTURE / NOT EXECUTED |
| AUD01-DEV-07 | Two logical output streams do not double-mix same source | FUTURE / NOT EXECUTED |
| AUD01-DEV-08 | OS device ID recycle cannot reuse retired generation | FUTURE / NOT EXECUTED |
| AUD01-BUS-01 | Master Music SFX Dialogue UI bus DAG topological sum | FUTURE / NOT EXECUTED |
| AUD01-BUS-02 | Two sends to same destination sum exactly once per route | FUTURE / NOT EXECUTED |
| AUD01-BUS-03 | Reject cycle/missing bus/duplicate BusGuid | FUTURE / NOT EXECUTED |
| AUD01-BUS-04 | Bus graph revision swap occurs at audio-quantum barrier | FUTURE / NOT EXECUTED |
| AUD01-BUS-05 | Mute/solo transitions click-free bounded ramp | FUTURE / NOT EXECUTED |
| AUD01-BUS-06 | Clipping/NaN gain input clamped/rejected with receipt | FUTURE / NOT EXECUTED |
| AUD01-BUS-07 | Different channel layouts route correctly without channel swap | FUTURE / NOT EXECUTED |
| AUD01-BUS-08 | AUD-03 specialized DSP graph not duplicated in base mixer | FUTURE / NOT EXECUTED |
| AUD01-VOC-01 | 32/64/128/256/512 voice stress with measured capacity | FUTURE / NOT EXECUTED |
| AUD01-VOC-02 | VoiceHandle stale generation fails without UAF | FUTURE / NOT EXECUTED |
| AUD01-VOC-03 | Virtual voice advances cursor without mixing samples | FUTURE / NOT EXECUTED |
| AUD01-VOC-04 | Re-promoted virtual voice resumes correct loop/sample position | FUTURE / NOT EXECUTED |
| AUD01-VOC-05 | Priority protects UI/dialogue vs ambient steals | FUTURE / NOT EXECUTED |
| AUD01-VOC-06 | Voice steal yields proper fade and typed receipt | FUTURE / NOT EXECUTED |
| AUD01-VOC-07 | Per-bus hard cap and owner quota cannot be bypassed | FUTURE / NOT EXECUTED |
| AUD01-VOC-08 | Voice end/cancel/drain double event idempotent | FUTURE / NOT EXECUTED |
| AUD01-STR-01 | Decode and prefetch run CORE-03 worker only | FUTURE / NOT EXECUTED |
| AUD01-STR-02 | Stream chunk loaded under memory and IO quota | FUTURE / NOT EXECUTED |
| AUD01-STR-03 | Seek/loop at verified sample frame when codec supports | FUTURE / NOT EXECUTED |
| AUD01-STR-04 | Decoder cancellation during device loss avoids stale buffer | FUTURE / NOT EXECUTED |
| AUD01-STR-05 | Ring underflow gives silence and exact underflow count | FUTURE / NOT EXECUTED |
| AUD01-STR-06 | Excessive queue buffered seconds capped with typed overrun | FUTURE / NOT EXECUTED |
| AUD01-STR-07 | Multiple streams are fairly prefetched without starvation | FUTURE / NOT EXECUTED |
| AUD01-STR-08 | Large audio file doesn't allocate full PCM in callback | FUTURE / NOT EXECUTED |
| AUD01-SRC-01 | PCM WAV validated sample count/channels/stride | FUTURE / NOT EXECUTED |
| AUD01-SRC-02 | Malformed WAV chunk length and integer overflow rejected | FUTURE / NOT EXECUTED |
| AUD01-SRC-03 | Random MP3/FLAC bytes parser fuzz planned | FUTURE / NOT EXECUTED |
| AUD01-SRC-04 | Opus invalid container/seek table rejected without crash | FUTURE / NOT EXECUTED |
| AUD01-SRC-05 | Source provenance and rights checked by DATA-02/03 | FUTURE / NOT EXECUTED |
| AUD01-SRC-06 | External URL/path traversal blocked by DATA-01 VFS | FUTURE / NOT EXECUTED |
| AUD01-SRC-07 | Compression bomb/long-duration metadata cap enforced | FUTURE / NOT EXECUTED |
| AUD01-SRC-08 | Codec license/NOTICE/SBOM and sample rights fixture audited | FUTURE / NOT EXECUTED |
| AUD01-RES-01 | 44.1 to 48 kHz sine frequency/aliasing reference | FUTURE / NOT EXECUTED |
| AUD01-RES-02 | 48 to 44.1 conversion preserves channel layout | FUTURE / NOT EXECUTED |
| AUD01-RES-03 | Input varying chunk sizes produces continuous sample sequence | FUTURE / NOT EXECUTED |
| AUD01-RES-04 | Rate change within allowed bounds with no reset click | FUTURE / NOT EXECUTED |
| AUD01-RES-05 | No duplicate resample stage on SDL stream+owned mixer | FUTURE / NOT EXECUTED |
| AUD01-RES-06 | NaN/Infinity source PCM does not poison output | FUTURE / NOT EXECUTED |
| AUD01-RES-07 | Sample conversion float32 to target PCM saturates correctly | FUTURE / NOT EXECUTED |
| AUD01-RES-08 | Resampler CPU/quality compared against future libsamplerate oracle | FUTURE / NOT EXECUTED |
| AUD01-HOT-01 | Default device switches during 32 active voices | FUTURE / NOT EXECUTED |
| AUD01-HOT-02 | Physical device remove returns loss event and NullSink fallback | FUTURE / NOT EXECUTED |
| AUD01-HOT-03 | Device reopen increments DeviceEpoch and resets mapping | FUTURE / NOT EXECUTED |
| AUD01-HOT-04 | Rapid unplug/replug churn does not leak streams | FUTURE / NOT EXECUTED |
| AUD01-HOT-05 | Close while callback in flight deferred safely | FUTURE / NOT EXECUTED |
| AUD01-HOT-06 | Audio source reload while playing preserves revision fence | FUTURE / NOT EXECUTED |
| AUD01-HOT-07 | Device rate/layout change gets correct conversion and fades | FUTURE / NOT EXECUTED |
| AUD01-HOT-08 | Failure to reopen leaves initialized silence not dangling device | FUTURE / NOT EXECUTED |
| AUD01-WEB-01 | Secure HTTPS AudioWorklet availability checked | FUTURE / NOT EXECUTED |
| AUD01-WEB-02 | Autoplay without user activation rejected/awaited | FUTURE / NOT EXECUTED |
| AUD01-WEB-03 | AudioWorklet callback stays bounded and nonblocking | FUTURE / NOT EXECUTED |
| AUD01-WEB-04 | SharedArrayBuffer absent uses documented safe ring fallback | FUTURE / NOT EXECUTED |
| AUD01-WEB-05 | Background browser visibility suspend/resume behavior reported | FUTURE / NOT EXECUTED |
| AUD01-WEB-06 | WASM scalar/threads/SIMD capability and memory negotiated | FUTURE / NOT EXECUTED |
| AUD01-WEB-07 | Audio buffer block-size variance handled correctly | FUTURE / NOT EXECUTED |
| AUD01-WEB-08 | Browser device routing and clock limits disclosed | FUTURE / NOT EXECUTED |
| AUD01-SEC-01 | Unauthorized MCP microphone capture denied without permission | FUTURE / NOT EXECUTED |
| AUD01-SEC-02 | Unauthorized remote device reconfiguration denied | FUTURE / NOT EXECUTED |
| AUD01-SEC-03 | Remote PlaySound burst rate limit with audit receipt | FUTURE / NOT EXECUTED |
| AUD01-SEC-04 | No private decoded PCM/PII in public metrics or logs | FUTURE / NOT EXECUTED |
| AUD01-SEC-05 | Malformed command/VoiceHandle replay authorization rejected | FUTURE / NOT EXECUTED |
| AUD01-SEC-06 | Callback race ASan/TSan/UBSan future test | FUTURE / NOT EXECUTED |
| AUD01-SEC-07 | Resource bomb saturates quotas without deadlock | FUTURE / NOT EXECUTED |
| AUD01-SEC-08 | Unexpected codec/file reads cannot access host paths | FUTURE / NOT EXECUTED |
| AUD01-FMT-01 | Known sum 2 sine tones verified vs offline golden PCM | FUTURE / NOT EXECUTED |
| AUD01-FMT-02 | Signed polarity/interleaved channel order oracle | FUTURE / NOT EXECUTED |
| AUD01-FMT-03 | Stereo pan center/left/right weights within declared law | FUTURE / NOT EXECUTED |
| AUD01-FMT-04 | Master clipping peak and RMS measurement reference | FUTURE / NOT EXECUTED |
| AUD01-FMT-05 | Gain ramp avoids single-step discontinuity at mute boundary | FUTURE / NOT EXECUTED |
| AUD01-FMT-06 | Silence bit pattern and denormal threshold validated | FUTURE / NOT EXECUTED |
| AUD01-FMT-07 | Downmix/upmix source labels and energy response tested | FUTURE / NOT EXECUTED |
| AUD01-FMT-08 | No feedback cycles or unbounded submix buffers | FUTURE / NOT EXECUTED |
| AUD01-AUD-01 | GAME event accepted separate from voice audibility receipt | FUTURE / NOT EXECUTED |
| AUD01-AUD-02 | No damage/gameplay event depends on virtual audio finishing | FUTURE / NOT EXECUTED |
| AUD01-AUD-03 | Scripted music state AUD-04 deferred not implemented as device owner | FUTURE / NOT EXECUTED |
| AUD01-AUD-04 | Spatial attenuation HRTF AUD-02 deferred not in base engine | FUTURE / NOT EXECUTED |
| AUD01-AUD-05 | Physics sound event scheduled with CORE-04 tick and delay | FUTURE / NOT EXECUTED |
| AUD01-AUD-06 | Audio bus gain persisted through DATA-04 CAS authoring | FUTURE / NOT EXECUTED |
| AUD01-AUD-07 | Editor CLI MCP stage profile yields identical validation | FUTURE / NOT EXECUTED |
| AUD01-AUD-08 | Headless NullSink deterministic PCM render replay logged | FUTURE / NOT EXECUTED |
| AUD01-MET-01 | Atomic underrun counter sampled only non-RT | FUTURE / NOT EXECUTED |
| AUD01-MET-02 | Callback worst/max/p95/p99 duration with timing overhead disclosed | FUTURE / NOT EXECUTED |
| AUD01-MET-03 | Decoded queued frames and backlog starvation metric | FUTURE / NOT EXECUTED |
| AUD01-MET-04 | Active virtual stolen voice counts and per-bus quota metrics | FUTURE / NOT EXECUTED |
| AUD01-MET-05 | Device epoch change/hotplug error counters | FUTURE / NOT EXECUTED |
| AUD01-MET-06 | Resampler and mixer CPU time split without RT log stalls | FUTURE / NOT EXECUTED |
| AUD01-MET-07 | Local opt-in telemetry redacted and sample privacy checked | FUTURE / NOT EXECUTED |
| AUD01-MET-08 | False PASS avoided when no physical device measurement exists | FUTURE / NOT EXECUTED |
| AUD01-PORT-01 | Windows WASAPI shared/exclusive backend future build/test | FUTURE / NOT EXECUTED |
| AUD01-PORT-02 | Linux PipeWire/Pulse/ALSA/JACK capability future test | FUTURE / NOT EXECUTED |
| AUD01-PORT-03 | macOS CoreAudio format/device switch future test | FUTURE / NOT EXECUTED |
| AUD01-PORT-04 | Windows ARM64/Linux ARM64/macOS ARM64 support future compilation | FUTURE / NOT EXECUTED |
| AUD01-PORT-05 | Headless CI NullSink no GPU/device | FUTURE / NOT EXECUTED |
| AUD01-PORT-06 | Web AudioWorklet HTTPS isolation and user gesture tested | FUTURE / NOT EXECUTED |
| AUD01-PORT-07 | App restart recovers authored buses but not raw old handle | FUTURE / NOT EXECUTED |
| AUD01-PORT-08 | Audio shutdown bounds drain and memory retirement under stress | FUTURE / NOT EXECUTED |
| AUD01-BEN-01 | 32 voice static tone mixer p50/p95/p99 CPU | FUTURE / NOT EXECUTED |
| AUD01-BEN-02 | 256 voices heavy category mix with protected dialogue | FUTURE / NOT EXECUTED |
| AUD01-BEN-03 | 512 virtual voices vs 32 audible measured CPU and heap | FUTURE / NOT EXECUTED |
| AUD01-BEN-04 | 1 hour streaming/seek and hotplug churn memory leaks | FUTURE / NOT EXECUTED |
| AUD01-BEN-05 | Device roundtrip/instrumented output latency on hardware | FUTURE / NOT EXECUTED |
| AUD01-BEN-06 | 44.1/48/96 sample rate resample SINAD/aliasing rubric | FUTURE / NOT EXECUTED |
| AUD01-BEN-07 | Buffer 128/256/512/1024 frame workload and dropout | FUTURE / NOT EXECUTED |
| AUD01-BEN-08 | Native+Web+NullSink feature tier measured, no false universal zero XRUN | FUTURE / NOT EXECUTED |

## Evidence rules and thresholds
- Unit: exact known PCM arithmetic, bus DAG ordering, VoiceHandle generation, rational TickToSample mapping, security/actor permissions, read/write buffer bounds and simulator NullSink.
- Integration: DATA-03/05 validated sources/decode (off realtime thread), CORE-01 backends and device hotplug, CORE-03 jobs, CORE-04 timing, AUD-02/03/04 extension boundaries, Editor/CLI/MCP authoring CAS.
- Failure/recovery: OS unplug/suspend, ring underflow, device sample rate changes, streaming starvation, cancellation, malformed codec, parser fuzz, ASan/UBSan/TSan and leak audit.
- Quality: offline golden sample captures from **original legally-cleared synthetic fixtures**, aliasing/distortion/phase/rate tests, p50/p95/p99 CPU/callback, memory and exact xrun/drop counts; native device end-to-end latency only with external loopback measurement and full settings.
- Platforms: Windows/Linux/macOS x64/ARM native, Web browser AudioWorklet HTTPS/user activation, always CPU NullSink headless, all with measured capabilities and stated limitations.

**No PASS/FAIL from the 128 runtime cases exists today.** Future hardware threshold and number of simultaneously audible voices **TBD by measured reference baseline**, not promised. Existing GitHub Docs Validation only validates Source Pack/links/catalog/registry and blocked Zcode selector, never acoustics or real-time behavior.
