# ADR-0008 — CORE-06 Diagnostic and Observability Policy

**Status:** PROPOSED; NOT APPROVED FOR ENGINE IMPLEMENTATION  
**Work Order:** NLE-P00-WO-002-CORE-06 | **Research issue:** #105 | **Date:** 2026-11-14

## Context
Stormline will be a proprietary high-performance game engine, Editor and headless server with an AI/MCP-first authoring workflow on Windows/Linux/macOS, later Web. It requires reliable, evidence-backed diagnostics without hidden network telemetry, paid subscriptions, uncontrolled logging overhead or leakage of project secrets.

## Proposed policy

1. Own a small, versioned **typed diagnostic events/metrics/traces facade** and local/offline export contract; third-party library types do not leak into public SDK, editor/CLI/MCP schemas or gameplay.
2. Include build SHA, monotonic timestamp domain, stable event code, frame/tick/job IDs when known and scoped correlation. No promise of cross-process absolute clock identity.
3. Logging backend candidate: **spdlog (MIT)**, against minimal C++ standard library reference. Bounded queues, explicit drops and severe-event fallback. Never block frame-critical real-time audio callback.
4. Profiling backend candidates: **Tracy** (developer CPU/GPU/locks/memory), **Perfetto SDK** (in-process offline tracing). Choose by measured overhead, inspectability and platform coverage rather than adding both to shipping builds automatically.
5. **Crashpad** is research only. Native dumps are local, opt-in and privacy-sensitive; never auto-upload or require cloud for failure evidence. Real crash handler safety, symbols and OS support must be validated.
6. User/device telemetry, analytics, profiler listeners, networking and AI trace retrieval are disabled until explicitly authorized with scoped privacy/security controls.
7. Explore **Stormline Diagnostic Fabric** only as a lightweight frame-aware correlation layer, with a prove-or-drop benchmark against ordinary logging/profilers.
8. Review license, exact dependency versions, third-party notices, security advisories, retention and user consent before coding or distribution.

## Alternatives
- Pure ad hoc println: tiny but loses schema/correlation/security and becomes hard to audit.
- Universal heavy cloud APM/OpenTelemetry: inappropriate as mandatory in a zero-cost local-first game engine; reserve optional service interop.
- All custom profiler: high maintenance and unproven value; avoid.
- Required always-on Tracy listener: avoid networking/privacy/performance risk.
- Crashpad automatically uploading dumps: reject; potentially sends confidential memory.
- Single global synchronous logger on audio/render threads: reject blocking and frame jitter risk.

## Proof obligations before implementation ADR promotion
- Actual Windows/Linux/macOS builds, headless no-GPU path, relevant web feature mapping and ABI tests.
- Event schema stability; redaction of secrets/project data; bounded labels and storage; disk-full and permission-denied recovery.
- Simulated crash in isolated child process and dump-local workflow, correct symbols with build SHA and safe export permissions.
- A/B with diagnostics off/low/high against the same 2D, ARPG VFX and 3D workloads, measuring frame-time p95/p99, CPU, memory and disk.
- Thread safety, overflow, recursion, shutdown, sampling, retention, network-disabled assurance and MCP authorization tests.
- License/provenance/third-party dependency tags and independent objective audit, no HIGH/CRITICAL defects.

## Consequences
This ADR **only proposes** an observability foundation. It does not choose an implemented logging library, guarantee zero overhead, produce a crash handler or authorize upload. Deferred decisions are release diagnostics profile, native minidump mechanism, exact trace export, build symbol distribution, privacy retention, Web fallback and feature-tier budgets.

Future coding issue #23 stays `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`. Zcode will code only after a full implementation-ready WO with file paths, APIs, tests and current Context Lock.
