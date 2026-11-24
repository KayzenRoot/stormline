# ADR-0125 — Bounded internal 2D animation, blending and sequencing plans

**Status:** `APPROVED FOR INTERNAL LOGICAL PIPELINE ONLY` — owner-authorized continuation, 2026-11-23. **Keeps:** [ADR-0024](0024-two-03-deterministic-animation-sequencing-policy.md) as planning-only context.

## Context

TWO-02 completed its internal sequence as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`. TWO-03 research, architecture and ADR-0024 exist, but no animation runtime, pose evaluator, audio scheduling, cutscene playback, encoder, renderer or hardware qualification is authorized. A fail-closed logical layer is required before any runtime work.

## Decision

Ratify a first TWO-03 internal pipeline that validates and plans metadata only:

1. **Flipbooks.** Stable sprite/atlas IDs/revisions, bounded frame count, rational frame durations and holds, and explicit first/last-frame inclusion. No frame is sampled or drawn.
2. **2D bones.** Unique stable bone IDs, bounded parent DAG, finite local transforms, checked depth and cycle rejection. No pose is evaluated and no skin is deformed.
3. **Blending.** Bounded clip weights, declared fade and discrete-target policy; sprite/event IDs are never interpolated. No runtime blend is executed.
4. **Cutscenes.** Bounded sequence tracks and cue intents with allowlisted kinds, rational cue times, nesting-depth caps and stable event IDs. No cutscene plays and no audio is scheduled.
5. **Timelines.** Rational animation timebase, checked frame/sample mapping, loop/seek/reverse policy and event dedup metadata. No clock, audio device, encoder or export exists.
6. **Boundaries.** TWO-01 owns Canvas/sprite rendering; DATA owns assets/authoring; AUDIO owns sound scheduling/mix; GFX owns rendering; WORLD/GAME/PHYS own gameplay authority; export remains a separate future owner.

## Non-decisions

- No animation runtime, pose evaluator, skinning, GPU buffer, shader, sample or draw.
- No audio device, mixer, sample-accurate hardware playback, A/V drift measurement or codec.
- No video/image export, encoder, FFmpeg, frame dump or encoded media.
- No DragonBones/Spine/Rive/Lottie importer or runtime.
- No editor timeline UI, state-machine runtime, IK solver or root-motion authority.
- No visual golden, 60 FPS, hardware, driver, memory or performance qualification.
- No public ABI, release class beyond `INTERNAL_ONLY`, engine license decision or production-readiness claim.

## Ownership

- TWO-03 owns logical flipbook, bone, blend, cutscene and timeline plans with typed failure metadata.
- It does not own renderers, GPU resources, audio, gameplay state, durable assets or export.

## Consequences

- The layer is deterministic and testable on every CI platform without a GPU, audio device, codec or renderer.
- Any future runtime, audio scheduler, exporter or visual comparison requires a new owner-approved contract/slice and platform evidence.
- ADR-0024 remains planning context; this ADR neither ratifies its rational-time runtime, audio-master or export decisions nor selects any dependency.

## Evidence gates

Contract `TWO-03-02`, five implementation slices `-03`..`-07`, qualification `-08`, closeout `-09`, exact-head native CI and pt-BR audit. Stop on stale source, native runtime/audio/export selection, released ABI or HIGH/CRITICAL.
