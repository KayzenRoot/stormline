# NLE-PRPLAN-CORE-04-09 — Integrated time qualification (INTERNAL_ONLY)

**STATUS: G6 QUALIFICATION PACKET — test-only code authorized only after this gate merges.** **Gate:** G6 qualification + CORE-01 admission. **Formal packet:** `NLE-PRPLAN-CORE-04-09`. **Predecessor:** CORE-04-04..08. **Issue:** #21. **Base:** `754efc5a1dbf1043f9ae09c8f174d787ea594dc6`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **Contract:** [core-04-qualification-v0](../contracts/core-04-qualification-v0.md).

## OBJECTIVE

Qualify ClockSource/Timeline together under QLF-01..05: integrated, 24 h rational stress, recovery, overload and report-only benchmark.

## CONTEXT

CORE-04-01..08 are approved/completed/satisfied. CORE-01 is not module-qualified; selected capabilities are admitted. The owner instructed continuation on 2026-11-22. This packet is test-only.

## SCOPE

- `tests/core/core04_time_qualification_tests.cpp` QLF-01..05.
- Additive CMake/CTest and TSan target.
- Evidence file.

## OUT OF SCOPE

Production source, new API, third-party timing, renderer/physics/network/audio, thresholds, allocator, ABI, release, CORE-04-10.

## FILES / SOURCES TO READ

`AGENTS.md`, checkpoint, ADR-0107, timeline/qualification contracts, CORE-04-04 evidence, TICK tests, CMake/workflow.

## REQUIREMENTS

GOV-001..005; ADR-0107; QLF-01..05; no production change.

## ARCHITECTURE RULES

Test-only; public CORE-04 API + standard library; no SDL/QPC/third-party; no global override; boundaries unchanged.

## CONSTRAINTS

Risk `ELEVATED`; release `INTERNAL_ONLY`; no dependency/secret/paid service; CORE-02/03 not qualified; G3 NOT_CLEARED; NLE-D009 OPEN.

## ACCEPTANCE CRITERIA

- QLF-01..05 pass; 24 h exact repeated; recovery/overload typed.
- TSan/ASan/UBSan and Linux/Windows/macOS exact-head CI.
- No production/threshold/ABI/release; pt-BR audit.

## TESTS

QLF-01 integrated; QLF-02 24 h stress; QLF-03 recovery; QLF-04 overload; QLF-05 report-only. Full CTest.

## DELIVERABLES

Test source, CMake/workflow, evidence, CI, audit. No production change.

## REVIEW FORMAT

pt-BR: files, QLF matrix, stress/recovery, benchmark, sanitizers/CI, no overclaim. APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION

Stale, gate not merged, production change, deadlock/race, missing 24 h, threshold/ABI/release overclaim, HIGH/CRITICAL.

## CONTEXT LOCK

Base `754efc5`; timeline contract blob `7137e433f13b564ba4171d59750346e4a8815c47`.

## EVIDENCE BUNDLE

`docs/evidence/NLE-PRPLAN-CORE-04-09-G6-ACTIVATION.md` for gate; `docs/evidence/NLE-PRPLAN-CORE-04-09.md` for results.
