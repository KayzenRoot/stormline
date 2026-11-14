# SIM-04 — Stormline Skeletal Animation & Motion Architecture

**WO:** NLE-P00-WO-002-SIM-04 | **Research:** #183 | **Future coding:** #49 OPEN/BLOCKED  
**BASE main:** `4dc7060fc0de16c036364a7363755a9ec4ea9144` | **P00 PROPOSED / DOCUMENTATION ONLY**, no engine, animation runtime, meshes, assets, measurements, implementation authorization or adopted backend.  
**Risk:** LOW for documentary research; FUTURE ELEVATED for native parsing/runtime memory, adversarial assets, concurrency, physics authority, procedural pose, codec bounds and replay.

## 1. Product objective and explicit gates
Design an engine-owned 3D skeletal animation subsystem supporting authored skeleton/skin/clip/graph assets, CPU/headless sampling, blend trees, additive layer masks, timed events, retargeting, IK and grounding, root motion, animation-to-ragdoll transitions, compression and crowd-aware execution. Target believable locomotion/combat without promising cinematic superiority absent visual studies and measured quality. Compatibility: native Windows/Linux/macOS, browser capability-gated, 2D/2.5D coexistence. First future code increment shall be **NECESSARY smallest vertical slice**, not the entire feature set.

Catalog acceptance: 'Animação de locomotion/combat com transições coerentes e custo medido' — remains FUTURE/NOT TESTED.

## 2. Authority and ownership (no duplicate engine)
| Owner | Boundary | Forbidden inside SIM-04 |
|---|---|---|
| CORE-04 | authoritative TickId, fixed time, integer/fixed-ratio event schedule | second clock based on FPS or wall time |
| CORE-05 | units/handedness/global-local transforms and OriginEpoch | new coordinate convention |
| CORE-02/03/06 | memory budget, jobs and diagnostics | ad-hoc global allocator, private thread manager or unbounded logs |
| WORLD-01/02 | generation-scoped EntityGuid, scene and prefab hierarchy | second ECS/scene database |
| WORLD-03 | cell residency/lease/revisions and safe world source | assuming unloaded ground is valid |
| DATA-02/03/04/05 | asset IDs/provenance, validated import, authored revisions, journal, target cooking/streamed data | independent untrusted FBX/glTF reader, writer or streamer |
| SIM-03 | accepted movement and root-motion receipt; collision/ground authority | altering entity position from pose or GPU interpolation |
| SIM-02 | physical ragdoll bodies, constraints, PHYS step/contacts | alternate rigid-body solver or direct unsafe contact callback |
| TWO-03 | 2D skeletal/timeline/sprite/cinematic cue semantics | duplicate 2D sequencer and audio clock |
| GFX-01/02/03/04 | GPU resource/palette ownership, skinning shader, culling/LOD/instance tiers | bespoke renderer, GPU allocator, graphics synchronization |
| GAME/NET/AUD | gameplay events, attack windows, server authority, audio cue consumption | unrestricted event scripts, anti-cheat authority, audio playing |
| EDIT/CLI/MCP | shared validated authoring commands and preview sessions | privileged raw runtime mutation or user-file shell execution |

## 3. Data model and import pipeline
Authored: `SkeletonSourceV1` with unique JointGuid, sanitized joint names, parent DAG, bind/rest local transforms, global inverse bind, unit basis, skin palette map and immutable ContentHash. `ClipSourceV1` with sorted key times/rational timebase, sparse channels, interpolation, motion curves, bounded marker list, root trajectory and ownership/provenance manifest. `AnimationGraphV1` with finite DAG/state transitions, parameters and versioned graph bytecode candidate. `RetargetProfileV1` with source/target skeleton hashes, correspondence map by stable semantics, additive offsets, scale/basis policy and unsupported-joint masks. `MotionDatabaseV1` is a **FUTURE** optional searchable feature database, not baseline.
Imported glTF 2.0: skin joints/inverseBindMatrices, node transforms, morph channels, animation samplers with STEP/LINEAR/CUBICSPLINE, validation of strictly increasing finite timestamps and accessor ranges. `KHR_animation_pointer` is optional capability-gated and constrained to supported authored properties, never generic arbitrary mutation. FBX via third-party converter may require separate SDK/content licensing, therefore **NOT chosen as a required runtime input**. DATA-03 retains importer and rights records; DATA-05 cooks compact runtime output, authenticates checksums, decompresses in bounded memory and rejects corrupt chunks.

## 4. Frame, tick and pose scheduling contract
**Authoritative tick path (CPU/headless-capable):**
1. Validate immutable graph/source revisions, active skeleton generations, capability profile and producer permissions; consume committed graph parameters by TickId with deterministic tie-breaking.
2. Evaluate graph state and phase/event-crossing policy once for the tick (handling loops, direction, reverse, large tick jumps, seeks, skipped clips and exact boundary dedup).
3. Decode/sample **locomotion root trajectory PRE-SIM-03** into `RootMotionIntentV1` with units, expected TickId, source asset/graph epoch, delta and bounded velocity. **It is a request**, not applied world translation.
4. SIM-03/physics accepts/rejects/constrains root motion in their fixed-step schedule. Do not guarantee a bespoke phase-order implementation until CORE-04/SIM-03 runtime is actually built.
5. After authoritative PHYS/MOTOR result, compute or reconcile graph phase as policy allows; resolve sampled local pose, additive masks, retarget and constrained IK from validated support/epoch. On ragdoll-active bones, SIM-02 physical snapshot is authoritative after its post-step barrier.
6. Publish immutable `PoseSnapshotV1` and ordered event receipts to WORLD/GAME/AUD plus read-only interpolation pose for GPU. GPU presentation may interpolate transforms, cannot generate missing gameplay events or overwrite root position.

No unbounded frame catch-up; stale/duplicate ticks and partial stream data fail closed or use clearly marked degradation with no physical/action authority. Simulation and animation evaluation are CPU and headless-capable, and render can evaluate presentation LOD separately without altering gameplay markers.

## 5. Graph composition and locomotion quality
- Parameterized state machines (idle/walk/run/sprint/jump/fall/land/combat/stagger), 1D/2D blend spaces with normalized nonnegative weights; additive layer mixing with masks in valid joint range and explicit coordinate conventions.
- Sync groups with authored phase markers, stable phase mapping across stride transitions and time-warp bounded by speed limits; transitions with interrupt policy, queued actions and event dedup. Prevent double attack/hit cues when clip wraps or is crossfaded.
- Crouch, jump, landing and combat root trajectories must be SIM-03 requests, with feedback from applied motion to mitigate foot slide or blocked dash; phase correction cannot grant motion/teleport.
- First future slice: idle/walk/run + single combat action, 2 skeletons, deterministic marker receipts, 1D/2D mix, no mesh required in headless mode. Motion matching, neural animation and full-body physics locomotion are optional FUTURE after baseline metrics and licensing/robustness proof.

## 6. Retarget and procedural IK
Canonical retarget semantics: target rest-pose baseline, source/target joint semantic pairs, authored orientation correction, root scaling policy, twist distribution, per-chain length ratio, missing joint fallback and bind-space validation. Detect cycles, noninvertible transforms, mismatched handedness, reordered/renamed joints and missing source channels. Retarget data is cached by skeleton/profile revision hash; mismatched revision rejects instead of corrupt pose.
IK candidate stages: two-bone analytic solver for hands/feet, CCD/FABRIK bounded iteration for chains, pole/limits, aim/look-at and pelvis offset; ordered after blend/retarget. Foot grounding must consume **SIM-03/SIM-02 grounded collision receipt** with exact support revision/WorldEpoch. Moving platform velocity and origin rebases must be handled by owner-provided transforms, never a render-only raycast authority. Ground not resident: do not lock foot or claim standing; recover gracefully from stale support.

## 7. Ragdoll and recovery handshake
States `ANIMATED`, `ACTIVATING_RAGDOLL`, `PHYSICAL`, `RECOVERING`, `DISABLED` with owner-controlled transitions at PHYS safe barriers. A versioned `RagdollProfileV1` maps skeleton JointGuid to SIM-02 physical body/constraint handles and collision layers. Startup requires loaded collider/source revision and actual body creation receipt; PHYSICAL snapshots from SIM-02 dominate mapped bones; unmapped remain safe masked animation. Transition to recovery uses bounded capsule clearance + SIM-03 motor acknowledgment + safe pre-step/respawn policy; blend captured physical pose toward authored get-up clip, with source/epoch consistency. Never instantiate a second solver or mutate PHYS listener reentrantly. Ragdoll can be unsupported in Web/crowd LOD and must advertise capability.

## 8. Performance and quality tiers (hypotheses, not achieved)
CPU-first clip decode, SoA/local-pose scratch via CORE-02/03 arena, immutable job inputs, skin palette upload by GFX-03, optional compute skinning **only if proven** vs vertex/CPU baseline. Skin LOD: FULL, REDUCED_BONES, SAMPLE_RATE_REDUCED (visual-only), FROZEN_VISUAL (far crowd), HEADLESS_GAMEPLAY (minimum semantic events/root). Never throttle root/gameplay markers based on camera visibility. Cap active tracks, graphs, bones, blend layers, decompression windows, IK iterations and ragdoll bodies; stream chunk revisions pinned per graph tick. Profile CPU p50/p95/p99, alloc, memory, render GPU/VRAM and animation visual discontinuity, per OS/GPU; budgets provisional until baseline.

## 9. Failure and threat model
Malformed/cyclic skeleton, 10^9 joints/keys, NaN quaternion, zero scale, sparse channel OOB, compressed clip zip bomb, unexpected codec tag, malicious `KHR_animation_pointer`, forged asset ACL/ownership, stale graph epoch, hot-reload during job, reused slot generation, unsynchronized physics reads, marker spam and underflow loop counters => typed error, rejected revision and stable last-known safe pose; no arbitrary code execution. Confirm licenses, SBOM, signed provenance, third-party notices and fixture ownership before vendor import. Security tests are future and must include parser fuzz and sanitizer runs.

## 10. Cross-platform acceptance and evolution
Native headless CPU pose API is baseline. WebAssembly support is a **candidate** requiring memory/SIMD/multithreading isolation fallbacks, browser bundling permissions and event timing validation. GPU skinning feature tiers use RHI not platform-specific public APIs. Version `V1` source and runtime schemas; migration is DATA-04 owned with rollback and byte-for-byte hash/receipt. All proposed paths and quality claims require future implementation evidence. Next after documentation is **SIM-05 research**, never SIM-04 code activation.
