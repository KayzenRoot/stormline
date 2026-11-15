# GAME-04 — Reproducible Event / Gameplay / Persistence / Multiplayer Benchmark Protocol

**P00 research plan only. RUNS = ZERO. TARGETS/NUMERIC PASS BUDGETS = UNDECIDED.** Research #220, future code #60 BLOCKED. No FPS, throughput, p99, memory efficiency, determinism or server scalability result is claimed.

## 1. Hypotheses to validate, not facts
H1: a bounded typed authoritative event queue has acceptably low CPU p99 and memory for 2D, ARPG and shooter workloads without a duplicate general-purpose bus. H2: deterministic phase batching enables replay-stable state under controlled host/seed; parallel read-only evaluation preserves canonical order. H3: data-defined abilities/quests/inventory across two genres need no CORE fork. H4: failed scene loading, save and network replay have predictable recovery without duplicate grants. H5: an owned queue, EnTT adapter and Flecs observer comparator provide different performance/maintenance trade-offs; no winner is known.

## 2. Reproducibility metadata (required each future run)
`BenchRunManifestV1`: exact Git base/head SHA, ADR pin, dependency versions/license commit SHA, compiler flags/C++ ABI/toolchain, build optimization/LTO/sanitizer mode, OS/kernel/arch, CPU model/cores/clock/power policy, RAM/NUMA, browser engine version if Web, device governor, thermal and background load, scene/rules/data asset+schema hashes, seed, queue budgets, target profile, headless/client/server mode, warmup/duration/repetitions and command transcript. Instrument CORE-06 sanitized spans without leaking user data. Capture raw CSV/JSON from real harness only, never invented percentiles.

## 3. Fixture families and load dimensions
| Fixture | Dimensions | Checks |
|---|---|---|
| `F01_EventTiny` | 0/1/10/100/1k subscribers, 1..100k events/tick, 16B..4KiB typed payload, 1-8 worker variants | enqueue/dispatch/validate latency, fanout, allocation, deterministic order |
| `F02_BurstStorm` | benign peaks, malicious causal cycles and quota breaches; varying depth/bytes/unique principals | p99/p99.9, memory peak, overflow status, zero unauthorized commit |
| `F03_AbilityCombat` | 1/100/1k entities, 1..64 concurrent abilities/actor, cooldown, status layering, AoE fanout | valid/denied activation cost, effect application time, canonical hash |
| `F04_InventoryQuest` | 1..100k items and quest objectives, duplicate/out-of-order commands, save/restore | transaction latency, duplicate grants = 0, recovery journal |
| `F05_SceneFlow` | scenes/prefabs with 1k..100k nodes/instances and missing asset/rev conflicts | staging/activation pause p95, peak RAM, cancellation recovery |
| `F06_NetworkSim` | 1/8/16/32/64 synthetic clients, 0..250ms RTT and loss/jitter profiles, reconnect | server CPU/tick, correction count, unauthorized denial, replay |
| `F07_CrossTarget` | Win x64, Linux x64/ARM64, macOS Apple Silicon; browsers/Web target as supported | compile/integration success, canonical deterministic reference scope |
| `F08_GenreReuse` | independent original puzzle/platformer and original shooter/ARPG fixtures | no changes to CORE/GAME-04 required for rule variance; valid exports |

Fixture sizes and 8/16/32/64 client counts are exploratory **not performance promises**. Use project-authored synthetic assets, not copyrighted commercial game captures.

## 4. Primary and secondary metrics
- **CPU:** simulation microseconds/tick, event enqueue→verified commit p50/p95/p99/p99.9, activation/quest/save stage latency, handler count and phase barrier overhead. Separate CPU time from network/IO and rendering.
- **Memory:** peak/steady heap bytes, queue backlog, `std::pmr` allocations, RSS, scene transfer working-set, lifecycle/leak and per-world quotas.
- **Correctness:** state/trace canonical hash across N repeats on SAME fixed target first; divergence count and first event; no duplicate item/reward or unauthorized effect; exact recovery receipts.
- **NET:** server tick lateness, correction frequency, replicated bytes/s and filtered private event exposure. Network percentiles include simulated RTT/loss explicitly.
- **Integration:** DATA-04 source commit versus runtime activation versus durable save times, plus last-good recovery under injected crash/failure.
- **Target:** no GPU/renderer performance claim from GAME-04. Native and Web availability require actual build/run evidence; browser timers may differ.

## 5. Measurement protocol
1. Baseline empty deterministic tick+WORLD-01 commit with CORE-03/04 fake clock, then increment event count and listeners one axis at a time.
2. Pin seed, asset manifests and schema versions; run controlled warmups until stable, minimum repetitions/CI sample size set in later approved test plan, report median/p95/p99 via raw samples and error bars. Avoid claiming a tail percentile with fewer than sufficient samples (e.g. p99 from ten runs).
3. Compare owned local queue against EnTT dispatcher and Flecs observers *only inside equivalent stable-sorted/validated wrapper*; report raw upstream fast path separately and **never** compare unsafe immediate to safe validated path as equivalent.
4. Repeat single-thread then CORE-03 allowed worker graph with immutable snapshots and deterministic consolidation. Nondeterministic races invalidate result.
5. Inject overflow, subscriber removal, world epoch reset, corrupted data, power-loss at journal step, network duplication/delay, parser fuzz and process restart; require fail closed and no double-grant.
6. Cross-target property tests: exact hash where numeric portability is deliberately established; otherwise invariant comparisons and explicit divergence classification. Do not assume floating-point bit identity across architectures.
7. Collect ASan/UBSan/TSan/fuzz (where supported), heap leak, schema migration and network auth results from actual runner only; unexecuted = UNKNOWN.
8. Set **candidate** budgets from baseline with hardware tier and product acceptance, then secure approval in later ADR. No arbitrary 60/120 FPS target imposed here.
9. Replicate on at least two comparable system loads; publish full fixture digests, commands, environment and failure/negative findings. Every report names warmup, confidence and provenance.

## 6. Stop/approval rules and eventual implementation
A known HIGH/CRITICAL security, integrity, migration or replay defect blocks promotion. If budgets fail, return CORRECTION REQUIRED for same coding WO. Maintain cost-zero/public GitHub CI and supplement with declared local hardware as necessary. This protocol is not a CI run, test proof, benchmark outcome or permission to unblock #60.

Related [matrix](game-04-gameplay-technology-license-matrix.md), [contracts](../contracts/game-04-gameplay-event-api.md), [128 FUTURE tests](../testing/game-04-acceptance-matrix.md).
