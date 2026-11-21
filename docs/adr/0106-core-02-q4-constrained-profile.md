# ADR-0106 — CORE-02 Q4 constrained-profile methodology (owner-ratified)

**Status:** `OWNER_RATIFIED_CONSTRAINED_PROFILE / IMPLEMENTATION_AUTHORIZED_FOR_LAUNCHER / NO QUALIFICATION`. **Subordinate to ADR-0004 (planning direction) and the Q4 ratification. Does not qualify CORE-02, select an allocator or alter production.**

**Date:** 2026-11-21 | **WO:** `NLE-CORE02-ALLOC-Q4-001` (next correction/campaign) | **Parent:** CORE-02 | **Issue:** #19.

## Context

Full Q4 is BLOCKED by missing physical Ubuntu/macOS hosts and exact 2 vCPU/4 GiB and 4 vCPU/8 GiB machines. The Windows host is `PHYSICAL_INFERRED_NOT_CERTIFIED`; the existing helper applies affinity after process start. The owner ratified option B: constrained profiles on an available physical host, with provable affinity before workload, hard memory cap, three runs, fail-closed validation and explicit non-exact-hardware labeling.

## Decision

- Implement a Q4 launcher/profile runner that, on Windows:
  - creates the benchmark process **suspended**;
  - assigns a Job Object with `ProcessMemoryLimit` of 4 GiB or 8 GiB;
  - applies the CPU affinity mask before resuming the process;
  - validates exit code, markers, result count and runs fail-closed;
  - labels output `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` and affinity coverage `before_resume`.
- Execute the campaign only on the available Windows physical-inferred host; Ubuntu 24.04 x64 and macOS 15 arm64 remain **BLOCKED**.
- Preserve report-only timing, no thresholds/ranking/winner, no allocator default/integration, no release.
- Historical Q4 evidence remains BLOCKED and is not rewritten.

## Proof obligations

- Launcher tests: suspended start, affinity readback before resume, Job Object memory limit applied, exit/marker/run-count failures, success path.
- Campaign: 2 vCPU/4 GiB and 4 vCPU/8 GiB constrained profiles, three runs each, CPU/RAM/OS/compiler/hashes and raw logs.
- Explicit label that constrained profiles are not exact physical machines; no Q4 PASS or module qualification.
- CI Windows for launcher/tests; existing matrix preserved.

## Consequence

- Q4 remains `PARTIAL_CONSTRAINED` even after Windows campaign; Ubuntu/macOS gaps remain.
- CORE-02 remains `NOT_QUALIFIED`; no allocator selection; CORE-03 unaffected.
- Any threshold or allocator selection requires separate ratification.
