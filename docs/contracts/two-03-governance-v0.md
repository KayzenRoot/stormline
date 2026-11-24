# TWO-03 INTERNAL_ONLY Animation Governance Contract v0 (NLE-PRPLAN-TWO-03-01)

**Status:** `GOVERNANCE PROPOSAL / NOT IMPLEMENTED / NO CODE AUTHORIZED`. **Base:** `f093ce5`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md), [ADR-0024](../adr/0024-two-03-deterministic-animation-sequencing-policy.md) planning-only. **WO:** [NLE-PRPLAN-TWO-03-01](../work-orders/NLE-PRPLAN-TWO-03-01.md).

## Objective

Record ownership, trust boundaries, release/risk classes and gates before TWO-03 implementation. No animation runtime, pose evaluation, audio schedule, cutscene playback, encoder, dependency, public ABI or release is authorized.

## Admission and boundaries

- Formal dependency is `TWO-01`; it is not module-qualified.
- TWO-03 owns logical flipbook, bone, blend, cutscene and timeline plans.
- TWO-01 Canvas; DATA assets/authoring; AUDIO sound; GFX rendering; WORLD/GAME/PHYS authority.
- No runtime, audio device, codec, importer, renderer or hardware driver is selected.

## Policy invariants

1. **No runtime or export.** Metadata/planning only; no frame sample, pose, skin, audio, encoder or media file.
2. **Rational time.** Frame durations and cue times are rational/checked; float drift and overflow fail closed.
3. **Bounded and finite.** Fixed capacities; NaN/Inf, zero/negative durations, cycles and unbounded nesting are rejected.
4. **No interpolation of identity.** Sprite IDs and event IDs are discrete; weights apply only to numeric pose channels.
5. **Gameplay authority external.** Cue intents are proposals to owners; TWO-03 does not mutate gameplay state.
6. **Deterministic.** Stable IDs, declared order and rational time determine output.
7. **No visual/performance claim.** Plans are not playback, audio sync, exported video or 60 FPS.
8. **Release boundary.** `INTERNAL_ONLY`; no ABI, hardware, driver, performance, security or production claim.

## First-slice scope (future, blocked)

- `-03` flipbook frame metadata.
- `-04` 2D bone hierarchy metadata.
- `-05` clip blend metadata.
- `-06` cutscene track/cue metadata.
- `-07` rational timeline evaluation metadata.
- `-08` integrated qualification and `-09` closeout remain blocked.

## Gate state after merge

- Manifest root `TWO03_01_APPROVED_GOVERNANCE_ONLY`: **537 `PLANNED_BLOCKED`, 0 `EXECUTOR_READY`, 168 `COMPLETED`, 43 approved gates**.
- `TWO-03-01` becomes `APPROVED_GOVERNANCE`; `TWO-03-02`..`-09` remain `PLANNED_BLOCKED`.

## Stop / rollback / security

Stop on stale source, missing admission, runtime/audio/export/import selection, unbounded animation, public ABI/release or HIGH/CRITICAL. Revert normally; never force push.

No implementation is authorized by this governance contract.
