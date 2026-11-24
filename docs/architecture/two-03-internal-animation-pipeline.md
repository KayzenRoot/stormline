# TWO-03 internal 2D animation and sequencing metadata pipeline (INTERNAL_ONLY)

**Status:** `PROPOSED LOGICAL ARCHITECTURE / NO RUNTIME / NO AUDIO / NO EXPORT`. **ADR:** [ADR-0125](../adr/0125-two-03-internal-animation-pipeline.md). **Governance:** [two-03-governance-v0](../contracts/two-03-governance-v0.md). **Queue:** `NLE-PRPLAN-TWO-03-01`.

## 1. Purpose

Describe the bounded logical model TWO-03 will implement before any animation runtime, pose evaluation, audio schedule, cutscene playback or export. It validates animation/sequencing metadata, derives deterministic plans and reports typed fallback reasons. It does not advance time or draw a frame.

## 2. Modules and boundaries

- **TWO-03** owns logical flipbook, bone, blend, cutscene and timeline plans.
- **TWO-01** Canvas/sprite rendering; **DATA** durable assets/authoring; **AUDIO** sound; **GFX** rendering; **WORLD/GAME/PHYS** gameplay authority; export is a separate future owner.
- No dependency is added to an animation runtime, audio device, codec, importer, renderer or hardware driver.

## 3. Logical model

### 3.1 Flipbooks

- Sprite/atlas IDs/revisions, bounded frame count, rational frame durations/holds.
- First/last frame rules are explicit; zero/negative durations fail closed.
- No frame is sampled or drawn.

### 3.2 Bones

- Unique stable bone IDs, bounded parent DAG, finite local transforms.
- Cycle, missing parent and excessive depth fail closed.
- No pose or skin deformation is produced.

### 3.3 Blending

- Bounded clip weights, fade metadata and discrete-target rules.
- IDs/events are never interpolated; weights are normalized deterministically.
- No runtime blend executes.

### 3.4 Cutscenes

- Bounded tracks/cues with allowlisted kinds, rational times and nested-depth caps.
- Stable event IDs and dedup policy metadata; no playback or audio scheduling.

### 3.5 Timelines

- Rational timebase and checked frame/sample mapping.
- Loop/seek/reverse policy and event dedup epoch metadata.
- No clock, audio device or export exists.

## 4. Determinism and failure

- All plans are pure functions of validated inputs; stable IDs and declared order determine output.
- Errors are typed and fail closed; partial plans are not emitted.
- Stale revisions, cycles, invalid durations and budget exhaustion select declared safe paths.
- No allocation, exception, file, network, audio, GPU, thread or global state in the internal implementation.

## 5. Test strategy

- Unit oracles for flipbook, bone, blend, cutscene and timeline plans.
- Integrated qualification QLF-T301..T304: valid pipeline, deterministic repeat, failure recovery and 10,000 bounded attempts.
- Native CI on Linux/ASan/UBSan/TSan/Windows/macOS; no runtime, audio, export or visual assertion.

## 6. Explicit non-goals

- No animation runtime, pose evaluator, skinning, GPU buffer, shader or draw.
- No audio device/mixer, sample playback or A/V sync measurement.
- No video/image export, encoder, FFmpeg, frame dump or media file.
- No DragonBones/Spine/Rive/Lottie importer.
- No timeline editor UI, state-machine runtime, IK solver or root-motion authority.
- No hardware, memory, 60 FPS or visual qualification.
- No public ABI, release or production readiness.

## 7. Failure and stop conditions

Stop on stale source, attempted runtime/audio/export/import selection, unbounded animation or sequencing, failed tests, HIGH/CRITICAL findings or any release/ABI claim.
