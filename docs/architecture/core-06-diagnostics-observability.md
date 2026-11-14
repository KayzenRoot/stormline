# CORE-06 — Diagnostics & Observability Architecture v0.1

**Work Order:** NLE-P00-WO-002-CORE-06 | **Research issue:** #105 | **Status:** PROPOSED / DOCS ONLY  
**Risk:** LOW for documentation; ELEVATED for actual crash-reporting, security and data pipelines.  
**Context Lock baseline:** cc18ce33a05cbadac330effcc7ad6ddf29380721

## 1. Objective and product boundaries

Stormline targets AAA-class creative capabilities with performance tiers for affordable hardware, across native Windows/Linux/macOS Editor and game exports, headless servers, and later web. Observability must be a **foundational service**, not an optional debugging afterthought. It will enable reproducible diagnosis of frame-time spikes, job starvation, memory pressure, audio glitches, graphics errors, asset corruption and AI-generated authoring changes.

This document specifies **future** types, contracts and proof obligations. There is no C++ implementation, profiler integration, crash upload or benchmark in the repository.

- CORE-06 owns common event semantics, aggregation, tracing/metrics interfaces, local diagnostics policy, build identifiers and safe diagnostic export.
- CORE-01 owns OS crash/process lifecycle and native capability signals; CORE-04 owns authoritative ticks; CORE-03 owns job scheduling; CORE-02 owns memory allocation.
- GFX-01/GFX-03 own GPU-specific timing and device-loss diagnosis, exposed through CORE-06 adapters only.
- AUD-01 owns real-time audio; network modules own packet/server metrics and privacy/anti-abuse; DATA owns project asset provenance and integrity.
- EDIT-07 provides UI debug/profiling; QA-03 supplies performance scenarios and budgets; AI-09/AI-04 provide authorized, redacted, paginated AI inspection.
- CORE-06 should have **no dependency** on editor UI, a cloud service, paid dashboard, a graphics device, or MCP provider.

## 2. Candidate contract and schemas (conceptual, NOT C++ ABI)

| Contract | Fields/behavior | Required safeguards |
|---|---|---|
| `DiagnosticEventV1` | schema_version, build_id/commit, event_id, monotonic_time_ns, sequence, subsystem, severity, code, correlation, bounded attributes | bound lengths/types; avoid arbitrary stringified secrets; explicit unknown fields/version |
| `CorrelationContextV1` | session_id (ephemeral/rotating), frame_id?, tick_id?, job_id?, transaction_id?, world_revision?, trace_id? | stable within authorized scope, no hardware fingerprint or user ID by default |
| `DiagnosticSink` | accept / flush / shutdown / bounded failure policy and buffer capacities | non-blocking option and dropped-event counters; no deadlock during shutdown |
| `TraceSpanV1` | start/end monotonic time, parent and child span IDs, thread lane and outcome | never promise universal total ordering across threads; explicit clock domains |
| `CounterSampleV1` | metric_id, units, sample time, dimensions, confidence/availability, value | bounded cardinality; reject NaN/Inf/overflow; no unbounded labels |
| `CrashEnvelopeV1` | build and symbol metadata, platform, stack/minidump reference (local), bounded preceding events | consent/retention/redaction, no network upload by default; crash-safe collection rules |
| `DiagnosticExportV1` | version, schema, redaction profile, encoding, data scope, manifest checksum, toolchain/build IDs | allow offline inspection; explicit export permission and path containment |

**Severity:** TRACE, DEBUG, INFO, WARN, ERROR, FATAL (canonical stable values). **Diagnostic reason:** invalid_input, project_asset_error, allocation_pressure, frame_budget_overrun, job_deadline_miss, device_lost, audio_underrun, network_peer_error, crash_unhandled; preserve unknown future codes.

### Clock semantics
- Record monotonic process-relative timestamp from CORE-01; translate to CORE-04 `TickId` and frame presentation ID if known.
- Wall-clock time is optional metadata, not simulation time and not evidence that two remote systems share synchronized clocks.
- Distributed/client-server trace correlation requires explicit clock synchronization and uncertainty metadata, not naked timestamp equality.
- Clock resumption/suspend must not fabricate elapsed simulation ticks; refer to CORE-04 rational-step debt policy.

### Event ordering and lifetime
- Producers can emit in parallel. Preserve **per-producer sequence**, not a false total order across arbitrary worker threads.
- Bounded MPSC or per-thread ring buffers may be explored; overflow increments `events_dropped` with reason and source, never silently loses critical warnings.
- Logging and tracing must be disabled/sampled for release hot paths where appropriate. A zero/near-zero disabled instrumentation cost is a **future measurement objective**, not a guarantee.

## 3. Candidate technical architecture

```text
Editor / Client / Headless Server / Unit Harness
          |
 Typed Stormline Diagnostics Facade (versioned)
          |
 Event / Metric / Span / Crash / Export contracts
          |
 Bounded buffers + policy + redaction + correlation
          |
 Local file/console  |  Profiling adapters  |  Optional crash-local
       |              Tracy / Perfetto         Crashpad review
       +-----------------+----------------------+
                         |
            Offline Evidence Bundle / QA / AI redacted resources
```

Primary local logging candidate is **spdlog** (MIT), compared with a minimal standard-library sink. Support plain text console and newline-delimited structured event export, with local rotating files only when explicitly configured. Its optional asynchronous queue must use bounded capacity with backpressure policy designed not to stall frame/audio threads.

**Tracy** is a strong optional developer frame/CPU/GPU/memory profiler candidate. Do **not** enable a remote profiler listening endpoint or connect automatically in shipping configurations; networking and privacy require explicit capability. No project dependency is installed here.

**Perfetto** is a complementary optional in-process trace exporter. Its C++ SDK can produce offline traces without external daemon/cloud, but system tracing can require additional permissions. Trace format selection needs benchmark, maintenance and export workflow evaluation; shipping both Tracy and Perfetto by default might be wasteful.

**Crashpad** is a native crash collection candidate, not assumed mandatory. It has handler/process and platform packaging implications, plus licensing/security obligations. Crash report should be generated locally and uploaded **only after explicit opt-in and a later approved endpoint architecture**. Local support fallback must work when no network is present.

## 4. Privacy and threat model

- **OFF by default:** any remote telemetry, crash upload, analytics, unique device IDs, hidden listeners, user/path/upload of project contents.
- **Local-first:** development logs and traces only inside configured project/temp directories with strict size/retention caps; no traversal beyond workspace.
- **Redaction at source and export:** tokens/keys, absolute paths where sensitive, customer project names, private content, IP addresses, chat/MCP prompts and tool arguments are suppressed unless explicitly allowed under consented debugging scope.
- **No arbitrary MCP or LLM access:** tools can query aggregated, authorized, bounded diagnostics for current project; no process memory reads, crashes dumps containing secrets, unrestricted filesystem or uploading.
- Crash dumps may include sensitive memory even after log redaction. Dump inspection/export requires **separate authorization** and default local-only retention; don't treat them as safe JSON.
- Avoid crashing inside the crash handler: no heap allocation, locks, complex logger calls or asynchronous-signal-unsafe operations in signal context. Use OS-supported design and preinitialized crash systems.
- Anti-abuse: log flooding, pathological labels/high-cardinality metrics, recursive errors, disk exhaustion, binary dump parsing, deliberate hostile strings, untrusted game network data.
- Software telemetry for users/minors and downstream game projects requires distinct data controller/privacy treatment at future commercial release.

## 5. Own R&D hypothesis — Stormline Diagnostic Fabric (SDF)

SDF could provide **frame-aware evidence** that associates:
1. frame/tick + task timeline + memory budget + GPU/asset event with a common correlation envelope;
2. a bounded rolling incident buffer that captures events leading to a p99 frame hitch or crash;
3. reproducible test fixture manifests and before/after regression comparison;
4. AI-readable issue summaries with strict field-level redaction, rather than raw crash dumps;
5. automatic degraded modes when instrumentation threatens frame budgets.

**Prove-or-drop:** retain SDF only if experiments demonstrate meaningful diagnosis and reproducibility gains over a simple spdlog + Tracy/Perfetto setup **without unacceptable memory, CPU, disk or privacy cost**. Do not claim unique inventions or patented technology without prior-art work.

## 6. Failure handling and operability

- Full buffer: drop/summarize low-severity events while retaining critical bounded records; count drops and provide overflow diagnostic.
- Disk full/permission denied: switch to bounded in-memory diagnostics or drop safely without deadlocking the engine.
- Renderer GPU hang: capture last valid CPU-side context, not untrusted GPU pointer data; device-loss integration belongs GFX.
- Headless crash: local crash envelope, no GUI or GPU requirement, reliable process exit code and correlation to server tick.
- Forced process kill: no guarantee of final flush or complete dump. Do not claim universal crash capture.
- Audio realtime: pre-allocated counter/atomic increment or designated lock-free report only; no logging, blocking, disk I/O or allocation from callback.
- Shutdown: timed bounded flush, preserve critical events if possible; no indefinite hang or secret exposure.
- Unknown profiler capabilities return typed `UNSUPPORTED` or `NOT_ENABLED`, not false zero values.

## 7. Proposed future benchmark and test matrix

| Scenario | Measurement / proof obligation |
|---|---|
| Logging disabled, medium, extreme spam | p50/p95/p99 CPU/frame overhead and memory vs no instrumentation, dropped count, disk I/O |
| Game 2D, ARPG VFX stress, 3D world, Web target | correlation of frame/tick, jobs, GPU, assets and audio with measured overhead |
| Crash fault injection in isolated child process | local crash envelope and symbolication by build SHA, sensitive fields redacted; no network |
| Multi-threaded job race and shutdown | per-producer ordering, cancellation and no deadlock |
| OOM/disk full/permission denied | bounded failure path, no unhandled recursion or project corruption |
| Tracy and Perfetto alternatives | equal-workload A/B, quality of diagnosis, integration and runtime footprint |
| AI/MCP redacted diagnostic resources | read-only access, pagination, denied secrets/paths, oversized output handling |
| Windows x64 / Linux x64 / macOS Apple Silicon; Intel feasibility | compile/native crash capture matrices, ASan/UBSan/TSan where supported |
| Headless server with no display/GPU/network | logging and local incident handling still usable |

Metrics, devices, workload duration, performance thresholds and dependency tags must be defined and audited before an implementation WO; no results are currently available. CI-hosted runners cannot replace physical GPU/driver tests or reliably reproduce actual crash platform behavior.

## 8. Module acceptance and future code gate

Candidate catalog proof: **reproducible CPU frame/job/failure capture traceable to exact build**. Prove successful game export diagnostics, privacy controls and no mandatory cloud.

This doc's passing documentation CI means **only** that planned text and link/registry structure validate. The implementation issue #23 and 80-module queue must remain BLOCKED and `executor_ready=false` until a separate code WO supplies exact APIs, dependencies, security and test fixtures.

## Sources
- spdlog: https://github.com/gabime/spdlog
- spdlog license: https://github.com/gabime/spdlog/blob/v1.x/LICENSE
- Tracy: https://github.com/wolfpld/tracy
- Perfetto SDK: https://perfetto.dev/docs/instrumentation/tracing-sdk
- Perfetto license: https://github.com/google/perfetto/blob/main/LICENSE
- Crashpad: https://chromium.googlesource.com/crashpad/crashpad
