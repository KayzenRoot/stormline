# SIM-04 — Reproducible Motion Quality, Compression and Runtime Benchmark Protocol

**Status: DESIGN ONLY / FUTURE, ZERO MEASUREMENTS.** WO NLE-P00-WO-002-SIM-04 | Research #183.

## 1. Benchmark questions
Does the chosen runtime deliver quality-per-ms for character motion while preserving source rights, deterministic gameplay event semantics and responsive movement under collision? How many CPU ms, allocations and bytes are spent in graph evaluation, clip decompression/sampling, retargeting, IK, event publication and animation-to-GFX palette generation? Is there an actual measured benefit to specialized compression/GPU or crowd LOD instead of CPU baseline?

## 2. Controlled and reproducible fixtures (to be authored, not present)
A. `MOTION-H1`: original 120-joint humanoid, idle/walk/run/strafe/crouch/jump and one combat swing with unique phase/foot/attack markers; skins with valid weights, 60s loop.  
B. `MOTION-H2`: 68-joint short humanoid with intentionally different proportions/twist chains, retarget compare to H1.  
C. `MOTION-Q1`: 80-joint original quadruped, gallop/turn/get-up, semantically different skeleton.  
D. `MOTION-A1`: malformed source and compressed/graph adversarial corpus: cycle, 1e9 count declaration, nonfinite quaternion, bad binary offsets, corrupted stream and untrusted extension.  
E. `MOTION-P1`: same authored locomotion plus moving platform, wall stop, off-ground ledge, streamed collider unload/reload and an independently-versioned SIM-03 motor trace.  
F. `MOTION-R1`: 16-body candidate ragdoll hierarchy under SIM-02; 3 activation/get-up loops and versioned physique response. Count is hypothetical, not shipped.

All fixtures require author-origin and redistribution license manifest, source hashes, units, skeleton hashes, provenance, revision, content/codec commit and synthetic generation seeds. Avoid borrowed studio/game animations and third-party models without explicit rights.

## 3. Workloads
| Scenario | Population and load | Target outcome |
|---|---|---|
| Hero CPU/headless | 1 H1 graph, 120 joints; idle-to-run-to-attack 60s | CPU per stage + root/markers vs TickId |
| Retarget precision | 1 H1→H2 and invalid H1→Q1 | local/world-space end-effector, pelvis orientation, visible foot error, typed failure |
| Crowd controlled | 10, 100, 1000 graphs with near/mid/far LOD | CPU p50/p95/p99 + alloc/working set; semantic events invariant to visibility |
| Motion + collision | 1 H1 and P1 flat/wall/moving/unready | requested/applied root delta error and no false grounded |
| Physical interaction | R1 activation/recovery with simultaneous streaming | PHYS safe barrier, valid body map, no stale handle/UAF |
| Codec bake/stream | uncompressed vs ozz-native vs ACL+explicit adapter (if built) | ratio, encode cost, decode CPU, max angular/world error and peak bytes |
| GPU skinning tier | reference CPU skin vs palette vertex/compute fallback | visual deviation plus GPU ms, VRAM and device-loss |
| Endurance | 60-minute mixed crowd/stream/reload/headless | leak rate, drop events, cpu p99 and typed fault recovery |

## 4. Measurement and quality method
- Pin build source SHA, compiler/linker, flags, SIMD/FP controls, vendor pins/license SBOM, assets, backend ABI; isolate power/thermal limits and repeat warm/cold stages. Exact CPU/GPU/driver/OS/arch/browser and graphics quality tier.
- CORE-04 sim TickId 30/60/120 Hz candidates, GPU presentation 20/60/144/240 FPS independent; compare event hashes and motion receipts across FPS.
- Record CPU stages in ns with CORE-06 profiler: p50/p95/p99 with run count, CI/bootstrap confidence intervals and outlier policy; normalized per agent, per joint and per bone chain. Log peak resident and per-clip compressed memory, allocator count, GPU ms and VRAM, upload bytes, device stalls; use isolated GPU to avoid comparing unlike render load.
- Compression error: max/median joint translation, quaternion angular error, forward-kinematic world-space wrist/foot deviation and skinned mesh vertex deviation. Objective thresholds **NOT SET** until baseline/quality study; never label perceptually lossless by file ratio alone.
- Quality rubric blind panel (future): foot sliding, anticipation, weight transfer, attack timing, blend discontinuity, contact mismatch, camera-independent silhouettes, non-humanoid retarget. Capture identical replay inputs/avatars/camera/lighting and randomize comparator display. Subjective claims require evidence, not rankings.
- Security measurements: corpus seeds, sanitizer stacks and status, allocation/time ceilings, rejection and typed error rates. Web: scalar/SIMD/threaded WASM fallback, browser memory, COOP/COEP constraints when applicable and Safari/Chromium/Firefox verification where feasible.
- Comparisons against established engines require the exact engine version, content equivalence, license/permissions, matched visual quality and declared hardware profile; **no superiority claim without controlled evidence**.

## 5. Future acceptance thresholds, not invented
No numerical fps, throughput, error degree, p99 milliseconds, memory MB or maximum characters are approved today. First gather baseline and set tier-specific targets through accepted ADR/DoD. `PROVE_OR_DROP` GPU compute skinning, neural and motion-matching candidates if no reproducible benefit. A result with unknown source revision, missing logs or selective successful run is INVALID, not PASS.

## 6. Output bundle and rollback
Future benchmark Evidence Bundle: SHA, fixtures+rights hashes, version pins, command lines, profiler trace/golden images/audio hash, CPU/GPU/VRAM distributions with confidence, platform matrix and regressions, data security/fuzzer results, independent objective audit in pt-BR, migration/revert plan and explicit result `PASS|FAIL|NOT_RUN|NOT_APPLICABLE`. No benchmark executed in this P00 research phase.
