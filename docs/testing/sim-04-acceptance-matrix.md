# SIM-04 — Acceptance Matrix: 96 FUTURE Cases, NONE EXECUTED

**Research issue #183 | WO NLE-P00-WO-002-SIM-04 | Coding issue #49 BLOCKED | DOCUMENTARY ONLY.** All 96 cases below are **PLANNED / NOT EXECUTED**. No fixtures, headless SDK, CI engine, native/Web builds, GPU, assets or test reports exist in Stormline at this stage.

## Acceptance interpretation
Catalog acceptance: locomotion/combat animation with coherent transitions **and measured cost**. Every future test must record exact source+asset hashes, backend versions/build compiler/flags/CPU/GPU/browser/device target, timestamp/TickId, golden hash or tolerance, repeat count, leak/fault logs and PASS/FAIL; CI gate and owner acceptance must be separately evidenced. Cross-platform numerical results may have declared tolerances, not assumed byte-identical.

| ID | Prospective scenario | Status |
|---|---|---|
| SIM04-SRC-01 | Valid original humanoid and quadruped source import | FUTURE / NOT EXECUTED |
| SIM04-SRC-02 | Reject parent-cycle skeleton and self-parent joint | FUTURE / NOT EXECUTED |
| SIM04-SRC-03 | Reject duplicate JointGuid and non-unique binding | FUTURE / NOT EXECUTED |
| SIM04-SRC-04 | Reject inverseBind mismatch and non-invertible bind transform | FUTURE / NOT EXECUTED |
| SIM04-SRC-05 | Reject NaN/Infinity/zero-scale source transforms | FUTURE / NOT EXECUTED |
| SIM04-SRC-06 | Validate glTF STEP/LINEAR/CUBICSPLINE track semantics | FUTURE / NOT EXECUTED |
| SIM04-SRC-07 | Reject out-of-bounds accessor/negative/unsorted key timestamps | FUTURE / NOT EXECUTED |
| SIM04-SRC-08 | Preserve source revision, license rights and hash after reimport | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-01 | Idle-walk-run 1D blend weights normalized | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-02 | 2D directional motion blend phase continuity | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-03 | Layer mask isolates upper body combat | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-04 | Additive blend preserves rest pose with missing channel | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-05 | Deterministic interrupted transition priority | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-06 | Reject unsupported node/expression/unbounded state cycle | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-07 | Fail closed on graph revision mismatch and hot reload | FUTURE / NOT EXECUTED |
| SIM04-GRAPH-08 | Protect graph update against unauthorized Editor/CLI/MCP principal | FUTURE / NOT EXECUTED |
| SIM04-SYNC-01 | One marker on exact transition boundary | FUTURE / NOT EXECUTED |
| SIM04-SYNC-02 | Loop wraps produce each eligible marker once per tick | FUTURE / NOT EXECUTED |
| SIM04-SYNC-03 | Large tick delta accounts for skipped phase interval | FUTURE / NOT EXECUTED |
| SIM04-SYNC-04 | Reverse and playback-speed changes honor event policy | FUTURE / NOT EXECUTED |
| SIM04-SYNC-05 | Multiple layers do not double-emit GAME attack effect | FUTURE / NOT EXECUTED |
| SIM04-SYNC-06 | Audio event aligns with AUDIO owner sample mapping | FUTURE / NOT EXECUTED |
| SIM04-SYNC-07 | Pause/step and variable render FPS preserve TickId marker log | FUTURE / NOT EXECUTED |
| SIM04-SYNC-08 | Reject duplicate/late/out-of-order parameter sequences | FUTURE / NOT EXECUTED |
| SIM04-ROOT-01 | Extract motion delta without direct world teleport | FUTURE / NOT EXECUTED |
| SIM04-ROOT-02 | SIM-03 applied delta on flat unobstructed ground | FUTURE / NOT EXECUTED |
| SIM04-ROOT-03 | Wall collision receives partial or rejected root receipt | FUTURE / NOT EXECUTED |
| SIM04-ROOT-04 | Moving-platform support and origin epoch remain coherent | FUTURE / NOT EXECUTED |
| SIM04-ROOT-05 | Root motion blocked by missing/unready collider | FUTURE / NOT EXECUTED |
| SIM04-ROOT-06 | Rollback/snapshot playback flags unproven numeric profile | FUTURE / NOT EXECUTED |
| SIM04-ROOT-07 | Cross-build replay reports divergence not bitwise claim | FUTURE / NOT EXECUTED |
| SIM04-ROOT-08 | Root-motion source/actor permissions cannot be spoofed | FUTURE / NOT EXECUTED |
| SIM04-RET-01 | Compatible original humanoids of different proportions | FUTURE / NOT EXECUTED |
| SIM04-RET-02 | Asymmetric different axes/up direction with authored correction | FUTURE / NOT EXECUTED |
| SIM04-RET-03 | Missing optional twist bones apply defined fallback | FUTURE / NOT EXECUTED |
| SIM04-RET-04 | Reject mandatory semantic joint absent or duplicated | FUTURE / NOT EXECUTED |
| SIM04-RET-05 | Reject stale source skeleton hash and target revision | FUTURE / NOT EXECUTED |
| SIM04-RET-06 | Root/pelvis scale policy preserves declared dimensions | FUTURE / NOT EXECUTED |
| SIM04-RET-07 | Quadruped must not silently use humanoid profile | FUTURE / NOT EXECUTED |
| SIM04-RET-08 | Retarget pose compared against source control skeleton | FUTURE / NOT EXECUTED |
| SIM04-IK-01 | Two-bone analytic solver reaches valid targets | FUTURE / NOT EXECUTED |
| SIM04-IK-02 | CCD/FABRIK bounded iteration and no overflow | FUTURE / NOT EXECUTED |
| SIM04-IK-03 | Pole and joint limits prevent invalid bend | FUTURE / NOT EXECUTED |
| SIM04-IK-04 | No-ground/stream-unready disables foot lock safely | FUTURE / NOT EXECUTED |
| SIM04-IK-05 | Moving platform contact epoch/normal verified | FUTURE / NOT EXECUTED |
| SIM04-IK-06 | Support origin rebasing matches CORE-05 transforms | FUTURE / NOT EXECUTED |
| SIM04-IK-07 | Aim/look target unauthorized or nonfinite rejected | FUTURE / NOT EXECUTED |
| SIM04-IK-08 | IK visual adjustment does not overwrite authoritative motor | FUTURE / NOT EXECUTED |
| SIM04-RAG-01 | Activation only after SIM-02 accepted body receipt | FUTURE / NOT EXECUTED |
| SIM04-RAG-02 | Partial joint coverage uses masked fallback pose | FUTURE / NOT EXECUTED |
| SIM04-RAG-03 | Reject stale PHYS epoch/body generation before activation | FUTURE / NOT EXECUTED |
| SIM04-RAG-04 | Physical pose mapped after PHYS post-step barrier | FUTURE / NOT EXECUTED |
| SIM04-RAG-05 | No contact listener writes ECS or animation graph reentrantly | FUTURE / NOT EXECUTED |
| SIM04-RAG-06 | Recovery checks motor capsule clearance and get-up policy | FUTURE / NOT EXECUTED |
| SIM04-RAG-07 | Cancel/reverse recovery without body leak or sudden teleport | FUTURE / NOT EXECUTED |
| SIM04-RAG-08 | Web unsupported ragdoll tier returns explicit capability error | FUTURE / NOT EXECUTED |
| SIM04-CMP-01 | Uncompressed and compressed world-space FK error measured | FUTURE / NOT EXECUTED |
| SIM04-CMP-02 | Quaternion antipodal and near-180 rotations stable | FUTURE / NOT EXECUTED |
| SIM04-CMP-03 | No ACL/ozz raw stream format conflation | FUTURE / NOT EXECUTED |
| SIM04-CMP-04 | Reject codec tag/hash/version mismatch | FUTURE / NOT EXECUTED |
| SIM04-CMP-05 | Corrupt/truncated compressed block fails closed | FUTURE / NOT EXECUTED |
| SIM04-CMP-06 | Bound chunk inflation, allocations and decompression time | FUTURE / NOT EXECUTED |
| SIM04-CMP-07 | Evict clip only after live pose jobs and leases end | FUTURE / NOT EXECUTED |
| SIM04-CMP-08 | Cold/Warm cache/memory load across clip boundary measured | FUTURE / NOT EXECUTED |
| SIM04-SKN-01 | CPU reference pose vs GPU palette skin shape match | FUTURE / NOT EXECUTED |
| SIM04-SKN-02 | Four-plus joint weighted skin with normalized weights | FUTURE / NOT EXECUTED |
| SIM04-SKN-03 | Nonuniform scale and inverseBind handling explicit | FUTURE / NOT EXECUTED |
| SIM04-SKN-04 | Render interpolation cannot emit gameplay events | FUTURE / NOT EXECUTED |
| SIM04-SKN-05 | Device loss recovers render while CPU headless continues | FUTURE / NOT EXECUTED |
| SIM04-SKN-06 | LOD cuts visual bones without cutting GAME marker timing | FUTURE / NOT EXECUTED |
| SIM04-SKN-07 | Morph targets and skinned mesh optional tier explicit | FUTURE / NOT EXECUTED |
| SIM04-SKN-08 | Cross-driver golden image tolerance defined not falsely passed | FUTURE / NOT EXECUTED |
| SIM04-SEC-01 | Reject foreign project/world/slot generation | FUTURE / NOT EXECUTED |
| SIM04-SEC-02 | Reject malicious KHR_animation_pointer property writes | FUTURE / NOT EXECUTED |
| SIM04-SEC-03 | Graph parser fuzz invalid byte counts and deep nesting | FUTURE / NOT EXECUTED |
| SIM04-SEC-04 | Clip decompression bomb and allocator quota reject | FUTURE / NOT EXECUTED |
| SIM04-SEC-05 | Denial of service marker spam/rate limit and drop accounting | FUTURE / NOT EXECUTED |
| SIM04-SEC-06 | No unlicensed sample animation/character distributed | FUTURE / NOT EXECUTED |
| SIM04-SEC-07 | Report sanitizers ASan/UBSan/TSan clean only after actual run | FUTURE / NOT EXECUTED |
| SIM04-SEC-08 | Abort/cancel racing hot reload without dangling pose readers | FUTURE / NOT EXECUTED |
| SIM04-PLT-01 | Windows x64/ARM profile with CPU evaluator | FUTURE / NOT EXECUTED |
| SIM04-PLT-02 | Linux x64/ARM profile with CPU evaluator | FUTURE / NOT EXECUTED |
| SIM04-PLT-03 | macOS ARM64/Intel profile where supported | FUTURE / NOT EXECUTED |
| SIM04-PLT-04 | WASM scalar fallback under memory limit | FUTURE / NOT EXECUTED |
| SIM04-PLT-05 | WASM SIMD and optional threads capability matrix | FUTURE / NOT EXECUTED |
| SIM04-PLT-06 | No graphics device mandatory for server events/root | FUTURE / NOT EXECUTED |
| SIM04-PLT-07 | Editor preview and CLI/MCP authoring same schema | FUTURE / NOT EXECUTED |
| SIM04-PLT-08 | Same source with numeric/SIMD differences reports tolerances | FUTURE / NOT EXECUTED |
| SIM04-BEN-01 | One hero 120-bone graph CPU p50/p95/p99 | FUTURE / NOT EXECUTED |
| SIM04-BEN-02 | 100 agents diverse pose/graph CPU and memory | FUTURE / NOT EXECUTED |
| SIM04-BEN-03 | 1000 far crowd visual-only LOD and marker invariants | FUTURE / NOT EXECUTED |
| SIM04-BEN-04 | Blend/retarget/IK stage microprofile with source revision | FUTURE / NOT EXECUTED |
| SIM04-BEN-05 | Ragdoll transitions under contact and streaming load | FUTURE / NOT EXECUTED |
| SIM04-BEN-06 | Compression ratio/decode warm/cold vs uncompressed | FUTURE / NOT EXECUTED |
| SIM04-BEN-07 | Locomotion/combat motion artifact blind human review | FUTURE / NOT EXECUTED |
| SIM04-BEN-08 | One-hour stress steady memory, event count and recovery | FUTURE / NOT EXECUTED |

## Proposed evidence gates and blockers
1. Unit: source/schema validation, graphs, time math, root extraction, deterministic marker order and recoverable typed errors.
2. Integration: DATA-03 import and DATA-05 cooking, WORLD entity lifecycle, SIM-03 root motion, SIM-02 physical authority, GFX shader/skin palette only after those runtimes exist.
3. Security/regression: parser/graph fuzz, malicious keyframes and compressed bytes, ACLs/actor authorization, sanitizer and data-race reports with exact build.
4. Visual: original licensed/generative test character set and authored screenshots/filmstrip; blinded human study of locomotion/combat transitions and subjective artifacts with clear rubric, frame captures plus measured objective bone errors.
5. Benchmark: CPU p50/p95/p99, memory/peak allocation, compression ratio/error and visual GPU/VRAM/tier on pinned hardware and OS. **Thresholds are UNDECIDED pending baseline**; compare like for like.
6. CI: existing Docs Validation can validate documentation only; it does not execute any of the 96 runtime tests. Never convert planning counts into coverage percentages or claim them passed.

## Delivery decision
All 96 acceptance cases remain NOT RUN. Backend selection, KPI budgets, gameplay superiority, deterministic platform parity, release scope and future code WO must be reviewed independently after upstream runtime is available. No implementation authorization from this matrix.
