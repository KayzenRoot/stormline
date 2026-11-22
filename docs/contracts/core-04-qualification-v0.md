# CORE-04 INTERNAL_ONLY Qualification Contract v0 (NLE-PRPLAN-CORE-04-09)

**Status:** `CONTRACT PROPOSAL / TEST-ONLY / NO PRODUCTION CODE`. **Base:** `754efc5`. **ADR:** [ADR-0107](../adr/0107-core-04-governance-slice.md). **WO:** [NLE-PRPLAN-CORE-04-09](../work-orders/NLE-PRPLAN-CORE-04-09.md).

## Objective

Qualify the implemented ClockSource/Timeline together under deterministic integrated load, long-run rational stress, recovery/overload and report-only timing. Test-only; no production change.

## Admission and boundaries

- Formal `CORE-01` dependency remains; CORE-01 is not module-qualified. Admission remains limited to CORE-01-03/-06/-07/-08/-12/-13.
- CORE-04-03/-04 are the production slices; this contract adds no API/type/dependency/ABI/release.
- No renderer, physics, network or audio qualification.

## Qualification matrix

| ID | Scenario | Oracle |
|---|---|---|
| QLF-01 integrated | multiple timelines, fake clocks, configs, pause/step/replay/scale | all expected tick counts and compatibility outcomes |
| QLF-02 rational stress | 24 h at 60 Hz partitioned into 1 s pumps, repeated | exactly 5,184,000 ticks per run; no drift |
| QLF-03 recovery | clock error, invalid config, debt limit, TickOverflow, replay mismatch, fresh timeline | typed errors, Failed/Running states, no hang |
| QLF-04 overload | DropExcess, Carry debt, frame clamp and overload bursts | bounded ticks, recorded drops/debt, no silent loss |
| QLF-05 benchmark/report-only | 1,000,000 synthetic ticks | prints elapsed/throughput; no threshold or ranking |

## Exact implementation allowlist

1. `tests/core/core04_time_qualification_tests.cpp`
2. `CMakeLists.txt` (additive CORE-04 qualification target/tests)
3. `.github/workflows/core01-internal-headless.yml` (TSan target)
4. `docs/evidence/NLE-PRPLAN-CORE-04-09.md`

No production source, dependency, API, ABI or release change.

## Stop / rollback / security

Stop on stale source, missing admission, production change, deadlock, data race, silent tick loss, threshold/ABI/release overclaim, HIGH/CRITICAL. Unmerged: close the branch; after merge: normal revert PR.

`CORE-04-10` remains blocked.
