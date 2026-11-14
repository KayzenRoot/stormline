# CORE-06 — Diagnostics/Profiling Technology Matrix

**Work Order:** NLE-P00-WO-002-CORE-06 | **Status:** RESEARCH ONLY; NO DEPENDENCIES INSTALLED

| Candidate | Technology and mechanics | License/portability | Primary fit | Risks / evaluation |
|---|---|---|---|---|
| C++20 minimal owned structured diagnostic interface | semantic event schema, bounded buffer and opaque sink contract | Stormline-owned API; platform standard libraries | stable public contract regardless of logging library | own schema/versioning, conversion correctness and tests |
| **spdlog** | thread-safe formatted loggers with console/file/rotating and optional async sinks | **MIT**, with fmt dependency also MIT; Windows/Linux/macOS per official README | practical native logging backend candidate | avoid synchronous disk writes in hot path, bounded queue policy, pin version |
| **Tracy** | CPU/GPU/lock/memory frame profiling and interactive analysis | BSD-3-Clause candidate, exact tag/license verify; OS support to test | primary developer profiling comparator | profiler client/network, privacy, capture overhead and deployment |
| **Perfetto SDK** | in-process spans/counters to trace, offline timeline/SQL analysis | Apache-2.0 main project; exact third-party notices to audit, C++17+ | profiler/trace format comparator; offline diagnosis | SDK footprint, trace overhead, permissions if system backend used |
| **Crashpad** | native crash handler/minidump capture infrastructure | Chromium source terms to inspect per checkout, no approved vendor integration | native local crash report candidate | extra processes/handler, crash dumps PII, platform support, signed distribution |
| Native platform crash tools | Windows dumps/ETW; Linux core/perf; macOS Instruments/crash logs | OS/toolchain terms, tools vary by platform | benchmark oracle and fallback | privacy/legal and environment restrictions, not identical formats |
| Sanitizers | ASan/UBSan/TSan | compiler/runtime distribution rules | developer-only corruption/race detection | not guaranteed on all OS/compiler combos; not runtime telemetry |
| OpenTelemetry C++ | instrumented trace/metric exporter, Apache-2.0 | candidate only where interoperability demands | headless services later | extra dependency/footprint, remote exporter/privacy complexity |
| SDF (in-house hypothesis) | correlated tick/frame/job, bounded flight recorder and AI-ready summary | original proposal; not built | if it enables actionable regressions without cost | prove-or-drop vs simple adapters and ensure no hidden network |

## Selection guidance
1. Freeze an **owned event schema** independent of profiler SDKs: timestamp domain, build ID, severity, trace/span, frame/tick/job/correlation, bounded attributes and redaction profiles.
2. **Evaluate spdlog** first for native logs; keep stdlib output/reference baseline and pin exact versions/legal notices later.
3. **Evaluate Tracy** for deep developer frame CPU/GPU profiling and **Perfetto SDK** for portable offline traces. Do not require both in shipping builds unless measured value justifies memory/CPU overhead.
4. Crashpad requires an explicit per-OS security and distribution decision, and its local dumps still must be treated as potentially sensitive. Do not enable upload automatically.
5. The custom SDF must prove correlation value, crash/incident reproducibility and acceptable overhead before adoption; do not reinvent a full profiler.
6. For mobile/web future targets, choose feature/compatibility tier per target rather than claiming the same crash machinery works everywhere.

## No fabricated scores
Proposed evaluation weights: accuracy/actionability 25%, CPU/frame-time overhead 20%, privacy/security 20%, portability/editor/headless 15%, license/maintenance 10%, disk/memory/build footprint 10%. Actual scores and quantitative pass/fail thresholds **require real evidence** from representative workloads.

## Source links
- spdlog README and license: https://github.com/gabime/spdlog , https://github.com/gabime/spdlog/blob/v1.x/LICENSE
- Tracy: https://github.com/wolfpld/tracy
- Perfetto SDK/license: https://perfetto.dev/docs/instrumentation/tracing-sdk , https://github.com/google/perfetto/blob/main/LICENSE
- Crashpad: https://chromium.googlesource.com/crashpad/crashpad
- OpenTelemetry C++: https://github.com/open-telemetry/opentelemetry-cpp

**No selected production library, no C++ engine code, no profiling capture and no observed benchmark.** A future technology/OS/ABI/legal review must precede integration.
