# NLE-PRPLAN-CORE-02-08 — G6 activation (memory telemetry)

**Status:** `G6 PROPOSAL / CODE NOT IMPLEMENTED / GATE PENDING AUDIT`. **Base main:** `dd76fceb6b9e835dd505c24a3c89065317528440`. **Formal packet:** `NLE-PRPLAN-CORE-02-08`. **ADR:** [ADR-0100](../adr/0100-core-02-memory-telemetry.md). **Contract:** [core-02-memory-telemetry-v0](../contracts/core-02-memory-telemetry-v0.md). **WO:** [NLE-PRPLAN-CORE-02-08](../work-orders/NLE-PRPLAN-CORE-02-08.md).

## Owner authorization

The owner authorized continuous CORE-01 → CORE-02 construction on 2026-11-18, including sequential CORE-02-08/-09/-10 conditioned on individual gates. CORE-02-03/-04/-05/-06/-07 are completed; capability-based L1 and ADR-0086 remain ratified. This gate activates only `NLE-PRPLAN-CORE-02-08` after Docs Validation, pt-BR audit and merge.

It does not add global interception, pointer capture, export, SMF, approve ADR-0004, change G3 or authorize CORE-03 implementation.

## CORE-01 NECESSARY gap audit (Etapa A)

- `CORE-01-03`..`-16`, `NLE-CORE01-CORR-001`, `NLE-CORE01-QUAL-001` and `NLE-CORE01-QUAL-002` are completed/approved. No duplicated QUAL work is proposed.
- **NECESSARY executable now:** none identified. No remaining CORE-01 code defect is demonstrated by repository evidence; QUAL-001/002 already cover runtime baseline and ABI observation.
- **Requires physical hardware or owner ratification:** physical Windows/Linux/macOS runs, physical missing-display behavior, minimum OS/SDK/glibc/CRT versions, Wayland runtime, 30 cold + 30 warm acceptance, 32 C01-Q scenarios, p95/RSS thresholds, independent security review, license and release class.
- **FUTURE/not needed for the internal slice:** renderer/GPU, editor, network, audio and commercial qualification.
- Therefore the next executable NECESSARY work is the already-planned CORE-02 capability slice; the formal CORE-01 module dependency remains and no CORE-01 completion is claimed.

## Capability admission

Formal `CORE-01` dependency remains. Admitted only via completed `CORE-01-03/-06/-07/-08`, `module_completion_claimed=false`; no window/input/DPI/IME/hotplug/soak capability used.

## Bounded technical slice

- `MemoryTelemetry` per-domain/aggregate allocation, release, live, peak and cumulative counters; typed zero/invalid-domain/underflow; atomics; snapshot.
- Optional default-null hooks in `MemoryBlock`, `MonotonicArena`, `MemoryBudget` and `LeakTracker` for real-event accounting.
- No global interception, pointer/call-site capture, timestamps, sampling thread, export/I/O, third-party tooling, ABI or release.
- Exact allowlist: telemetry header/cpp/tests, additive hooks in existing memory files, additive CMake/workflow, evidence.

## Gate state after merge

- Manifest root `CORE02_08_READY_L1_CAPABILITY_OVERLAY`: **724 `PLANNED_BLOCKED`, 19 `COMPLETED`, 4 approved gates, 1 `EXECUTOR_READY` (`CORE-02-08`)**.
- Selector `-08` exit 0; all other IDs exit 2; 80/80 WOs BLOCKED; registry unchanged.

## Proof obligations

TLM-01..TLM-06; four CI jobs + ASan/UBSan; existing 99 Linux / 98 Windows/macOS CTests; no overclaim.

No code/native PASS is claimed by this gate.
