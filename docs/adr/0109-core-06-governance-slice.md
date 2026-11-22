# ADR-0109 — CORE-06 governance and bounded diagnostics direction

**Status:** `OWNER-RATIFIED_BOUNDED_PLANNING_ONLY / NO CODE AUTHORIZED`. **Subordinate to ADR-0008 (ratified only as planning direction) and ADR-0086 (capability admission). Does not declare CORE-01 complete, approve implementation, public ABI, dependency, release, G3 or license.**

**Date:** 2026-11-22 | **WO:** `NLE-PRPLAN-CORE-06-01` | **Parent:** CORE-06 | **Issue:** #23.

## Context

CORE-05 closed as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. CORE-06 (`Diagnostics & Observability`) has research, architecture, ADR-0008 `PROPOSED` and a blocked code WO; no executable code exists. Its formal dependency `CORE-01` is not a qualified module, but selected CORE-01 capabilities are completed. The owner instructed continuation on 2026-11-22.

CORE-06 is security- and privacy-sensitive: crash dumps can contain project/user data, logs can leak secrets, telemetry can become hidden network traffic, and profiler listeners can expose local services. The first increments must therefore be local-only, bounded and fail-closed.

## Decision

- **A:** ADR-0008 is ratified only as planning direction for CORE-06. No third-party logging, profiling or crash library is selected by this ADR.
- **B:** CORE-06 begins with owned, versioned typed diagnostic values: schema version, build identity, monotonic timestamp domain, producer sequence, severity, stable reason/code, subsystem and bounded attributes. Library types never enter the core or public ABI.
- **C:** Local-first only. Remote telemetry, crash upload, analytics, profiler listening endpoints, network export and cloud dependencies are **OFF by default and not authorized** by this ADR.
- **D:** The first implementation slices are logs, traces/spans and local counters. Crashes, profiling adapters and opt-in local telemetry require later G6 packets with platform/security/retention evidence; they remain blocked until then.
- **E:** Diagnostic risk is `LOW` for documentation and `ELEVATED` for implementation/export/crash integration. Release class is `INTERNAL_ONLY`; no public ABI, SDK, release or distribution.
- **F:** CORE-06 owns the facade, event semantics, local sink policy, bounded buffering and correlation envelope. CORE-01 owns OS crash/process lifecycle; CORE-02 memory; CORE-03 job IDs; CORE-04 ticks; GFX owns GPU timing/device loss; AUD owns realtime audio constraints; DATA owns project provenance; EDIT/QA/AI consume authorized projections.
- **G:** No claim of zero/near-zero overhead, universal crash capture, cross-process clock identity, deterministic multi-thread ordering or secure dump handling. Bounded drop counters and typed `UNSUPPORTED`/`NOT_ENABLED` outcomes are required.

## Required before code

1. `CORE-06-02` contract audited with exact logical API, error model, bounded attribute policy, redaction rules, file allowlist and golden tests.
2. Individual `CORE-06-03` G6 activation and explicit owner authorization.
3. Tests for bounded buffers/drops, per-producer ordering, shutdown, invalid attributes, redaction fixtures and no-network behavior.
4. Separate gates for crash/profiling/telemetry, including platform/license/security/retention decisions.
5. MSVC/GCC/Clang/AppleClang CI; no HIGH/CRITICAL; no release/ABI claim.

## Consequence

- `CORE-06-01` may be prepared as `APPROVED_GOVERNANCE`; `CORE-06-02`..`-10` remain `PLANNED_BLOCKED`.
- CORE-01 remains not module-qualified; CORE-02 `NOT_QUALIFIED`; CORE-03/CORE-04/CORE-05 not qualified.
- G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`; engine not released.
- No implementation packet becomes `EXECUTOR_READY` by this ADR.
