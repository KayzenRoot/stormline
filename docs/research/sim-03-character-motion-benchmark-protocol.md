# SIM-03 — Reproducible Character Motion, Contact and CPU Benchmark Protocol

**Research #180 | WO NLE-P00-WO-002-SIM-03 | FUTURE EXPERIMENTS ONLY / NO RUNS**.

## Clean-room datasets and capture manifest
Use original synthetic geometric stages: 2D tiles/platforms with one-way edges, 2.5D orthographic presentation with 2D solver, 3D stairwell/slope/ceiling/corner/terrain cave, moving/rotating platform, high-speed thin wall, streamed ground pending, teleport/rebase. No third-party game assets or copied motion animations. Record generator version, exact geometry/material and collider revision hashes; source licensing; input action logs with TickId and authority; backend tag/SHA/ABI, compiler and flags; worker count; CPU/GPU model; OS; fixed physics timestep; authoritative world and render frame rates; thresholds and capture raw artifacts.

## Future tracks
1. **Analytic/reference locomotion:** floor acceleration and braking, integration under no contacts, gravity jump apex/time from independent CPU oracle; account for float tolerances and numerical profile.
2. **Different presentation FPS:** 24, 30, 60, 120, 240 visual frames and 30/60/120 fixed-tick candidates; compare exact count/order of ticks and command receipts, and bounded pose divergence under pinned profile.
3. **Ground contact fidelity:** 5/15/30/45/60-degree authored slopes, steps and ceilings with parametric radii/heights, sliding/ground snap and discontinuous triangle seams; independently verify geometric collision bounds.
4. **Sweeps, CCD and safety budgets:** speed/skin/iteration/obstacle density matrix, thin-wall failure, stall spikes, error receipts and no unbounded loops.
5. **Actions and responsiveness:** input→next confirmed tick response, buffered jump and coyote windows (ticks), start/stop latency under simulation load, hover/ground attachment, dash and crouch transitions. No guessed human perceptual thresholds.
6. **Platforms:** horizontal/vertical and rotating source, ride, detach, teleport, profile revision, unload/reload; compare platform-relative pose and event lifetimes.
7. **Streaming/origin:** absent vs staged vs PHYS-acknowledged collision source, static terrain seam, chunk eviction, live player crossing cells and far-origin shift at tick barrier; assert no invisible ground authority.
8. **Replay/prediction boundary:** single worker vs 2/8 workers, same pinned backend across Windows/Linux/macOS and Web where available, no promise of exact cross-OS equality. Test invalid rollback-without-physics-state and full log re-simulation.
9. **Scale:** rights-cleared original 2D/3D crowds with 1, 100, 1000 and candidate 10000 motors; static/moving platform ratios and bounded contact density; mean/p50/p95/p99/worst CPU time, query count, allocations, peak RSS; hard-stop on OOM/resource caps.
10. **Security:** malformed/missing asset, NaN/Inf, stale handle, arbitrary impulse from remote/MCP, enormous shape/sweep and event-flood fuzz; sanitizer/crash traces redacted, not auto-uploaded.
11. **Backend comparison:** Jolt CharacterVirtual, Box2D experimental geometric mover and Rapier only if licensed and integrated in controlled later A/B research. Measure feature gaps and adapter stability, do not mix physics worlds as interchangeable proofs.
12. **Human playtests:** original 2D platformer, ARPG click movement and FPS navigation stage; blinded A/B profiles and repeatable tasks, report error/correction attempts and qualitative ratings, never present subjective feel as physics proof.

## Result schema
`BenchmarkReceiptV1`: tested commit SHA, fixture hash and rights, target+build, hardware/driver, physics ABI and profile, tick/frame rates, CPU query p50/p95/p99/worst, RSS, allocator spikes, grounded/contact mismatch count, blocked input latency, replay divergence, errors and confidence/limitations. Paired baseline and sample distribution required; never compare unlike hardware scenes.

**STOP conditions:** memory corruption, UAF, unbounded loop, live ground absent without safe fallback, missing source provenance, unsupported Web feature falsely advertised, HIGH/CRITICAL, unauthorized external write, or invalid replay claim. No numeric budgets/results exist at research stage.
