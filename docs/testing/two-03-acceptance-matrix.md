# TWO-03 — Future 2D Animation & Sequencing Acceptance Matrix

**WO NLE-P00-WO-002-TWO-03 | Research #153 | Future coding #39 OPEN/BLOCKED**  
**ALL 106 CASES BELOW ARE FUTURE / NOT EXECUTED.** No native runtime, cue/event dispatcher, GPU mesh, AUDIO sample-clock measurement, exported media, fixtures, fuzz harness or editor timeline currently exists.

| Case | Prospective acceptance proof | Evidence to execute in future |
|---|---|---|
| TIM-001 | 24/1 frame to 48000Hz audio sample index exact | CPU numeric |
| TIM-002 | 24000/1001 frame and 48000Hz sample conversion golden | CPU numeric |
| TIM-003 | 30000/1001 and 44100Hz rational conversion tie rule | CPU numeric |
| TIM-004 | Long hour timeline no accumulated float frame drift | property |
| TIM-005 | Signed 64-bit overflow and zero denominator rejection | fuzz |
| TIM-006 | Huge rational denominator LCM explosion avoided | fuzz |
| TIM-007 | Fraction reduction preserves ordering over negative timestamps | unit |
| TIM-008 | Simulation-time versus presentation-time sampling separate | headless |
| TIM-009 | Pause and time-scale 0 preserve exact key timing | unit |
| TIM-010 | Backward seek/negative time reject or clamp by policy | unit |
| TIM-011 | Slow-motion variable rate monotonic scene time behavior | integration |
| FLI-001 | Nonuniform flipbook frame durations and holds exact | CPU |
| FLI-002 | Last frame half-open boundary and loop exact | unit |
| FLI-003 | Loop ping-pong and reverse sprite sequence correct | golden |
| FLI-004 | High-FPS render cannot interpolate discrete unrelated atlas UV | visual |
| FLI-005 | Sprite atlas repack revision invalidates stale texture handle | TWO-01 |
| FLI-006 | Texture missing yields explicit fallback not silent last frame | fault |
| FLI-007 | Tile flipbook via TWO-02 stable TileId and TWO-03 scheduler | integration |
| FLI-008 | Pixel-art nearest integer scale vs animated transform | visual |
| FLI-009 | Flipbook zero or negative duration and huge frame count reject | fuzz |
| RIG-001 | Bone DAG parent order and local/world transforms exact | CPU |
| RIG-002 | Bone cycles and disconnected references rejected | fuzz |
| RIG-003 | Bone negative determinant/mirror transform safe | math |
| RIG-004 | Rest pose bind matrices and weighted skinning golden | CPU |
| RIG-005 | Skin influences normalized and max count enforced | fuzz |
| RIG-006 | Degenerate zero weight or NaN mesh fails typed | fuzz |
| RIG-007 | Two-bone IK reachable targets convergence within tolerance | CPU |
| RIG-008 | IK unreachable/clamped target stable nonfinite-free | CPU |
| RIG-009 | Slot skin swap preserves Canvas painter layer order | golden |
| RIG-010 | Mesh vertex bound and GPU allocation capacity guards | GPU |
| RIG-011 | CPU reference equals GPU skin within approved epsilon | GPU |
| RIG-012 | WebGL2 no compute CPU rig path available | browser |
| RIG-013 | Device loss and atlas revision recover rig without stale pointers | fault |
| RIG-014 | Root motion passed as typed proposal not direct PHYS authority | security |
| BLN-001 | Blend 1D midpoint and endpoints normalized | CPU |
| BLN-002 | Additive delta around rest pose correct | CPU |
| BLN-003 | Masked per-bone blend influences only allowed bones | unit |
| BLN-004 | Blend weight NaN negative or sum zero handled explicit | fuzz |
| BLN-005 | Discrete frame blend versus carry policy explicit | golden |
| BLN-006 | State transition guard changes at fixed tick boundary | CPU |
| BLN-007 | Repeated transition instant loop bounded per tick | fuzz |
| BLN-008 | Interrupted one-shot does not replay duplicate marker | event |
| BLN-009 | Reverse transition and seek resets phase according policy | unit |
| BLN-010 | BlendSpace2D interpolation outside triangle selects fallback | CPU |
| BLN-011 | Same inputs after rollback produce same output pose | replay |
| EVT-001 | Cue exactly on clip boundary fired once not twice | CPU |
| EVT-002 | Dropped video frames do not skip gameplay/audio cue schedule | headless |
| EVT-003 | Seek across cue suppress or preview according event policy | unit |
| EVT-004 | Reverse over cue no unexpected combat hit dispatch | security |
| EVT-005 | Nested loops produce bounded event IDs with epoch | CPU |
| EVT-006 | Cue idempotency survives rollback replay owner ack | integration |
| EVT-007 | Audio/VFX/camera cue owners remain separate | architecture |
| EVT-008 | Untrusted arbitrary function/script track rejected | security |
| EVT-009 | Property allowlist denies inventory/network privileged edits | security |
| EVT-010 | Burst cue rate quota limits VFX/audio storm | stress |
| SEQ-001 | Multitrack shot camera cuts and overlap precedence exact | CPU |
| SEQ-002 | Nested sequence time remapping rational conversion | unit |
| SEQ-003 | Recursive sequence cycle and excessive nesting rejected | fuzz |
| SEQ-004 | Cutscene track seek pause reverse with correct cue policy | integration |
| SEQ-005 | Scene/Canvas layer opacity and camera blends preserve owner | visual |
| SEQ-006 | Subtitle timestamps and captions track localized key reference | accessibility |
| SEQ-007 | Reduced-motion and flash-safe preview policies respected | accessibility |
| SEQ-008 | Hot reload sequence preserves last-good revision on invalid edit | recovery |
| SEQ-009 | Asset streaming stall yields explicit incomplete readiness | fault |
| SEQ-010 | MCP concurrent staged edits CAS revision conflict | security |
| SEQ-011 | Editor save/reopen timeline exact tracks and key IDs | DATA-04 |
| AUD-001 | Original rational schedule equals correct sample indices | CPU numeric |
| AUD-002 | Audio-owner sample ack distinct from predicted target | integration |
| AUD-003 | 48000Hz one-second tone and frame timestamp schedule exact | fixture |
| AUD-004 | 44.1k 29.97fps long timeline no scheduling drift | CPU |
| AUD-005 | Audio device latency UNKNOWN not labeled measured | diagnostic |
| AUD-006 | Sound cue pause/seek behavior never arbitrarily replays | audio |
| AUD-007 | Realtime underrun and drift report audio receipt | device |
| AUD-008 | Offline frame export planned separately from actual encoded file | contract |
| AUD-009 | Audio sample and video frame counts after mux match policy | hardware |
| AUD-010 | Generated pulse/audio clap drift from decoded file measured | benchmark |
| AUD-011 | Unsupported reverse audio mode fails safely | fault |
| AUD-012 | FFmpeg LGPL vs GPL selected build and media patents gated | license |
| INT-001 | TWO-01 atlas/color/alpha layer order retained across poses | integration |
| INT-002 | TWO-02 animation tile reference absent safely | integration |
| INT-003 | GFX-07 motion vectors/reactive masks on skeleton switches | GPU |
| INT-004 | GFX-03 frame fences and GPU skin pool safe after unload | GPU |
| INT-005 | AUDIO VFX WORLD/PHYS causal cue intent ACK isolation | integration |
| INT-006 | Windows DX12/Vulkan actual sprite/bone/cutscene playback | hardware |
| INT-007 | Linux Vulkan native audio+render playback | hardware |
| INT-008 | macOS Apple Silicon Metal native playback | hardware |
| INT-009 | WebGPU feature checks and WebGL2 CPU fallback | browser |
| INT-010 | Headless fixed-tick pose schedule requires no GPU/audio device | headless |
| SEC-001 | Imported DragonBones JSON oversized mesh safe | fuzz |
| SEC-002 | DragonBones MIT exact runtime and authored asset rights audit | license |
| SEC-003 | Spine runtime license integration rejected without editor rights | license |
| SEC-004 | Rive MIT runtime and free splash/paid export conditions flagged | license |
| SEC-005 | Lottie unsupported audio/video/image sequence reported as loss | interop |
| SEC-006 | Lottie JSON scripts/expressions and remote URLs denied | security |
| SEC-007 | FFmpeg codec/source/flags/patent disclosures required predeploy | license |
| SEC-008 | MCP project boundary and private asset export denied | security |
| SEC-009 | Timeline huge key count/duration/curve control points bounded | fuzz |
| SEC-010 | Malicious nested clip recursion and integer overflow denied | fuzz |
| BEN-001 | 100/1000/10000 active animations only synthetic test loads | stress |
| BEN-002 | CPU pose p50/p95/p99 by bones/curves/active blends | benchmark |
| BEN-003 | CPU versus GPU mesh skinning cost versus image quality | benchmark |
| BEN-004 | A/V frame-sample residual across 10min and long cuts | benchmark |
| BEN-005 | Timeline memory cache and asset unload bounds | benchmark |
| BEN-006 | GPU frame-drop event fidelity and animation smoothness | benchmark |
| BEN-007 | STS prove-or-drop vs simple schedule checks | R&D |
| BEN-008 | Godot/DragonBones original matched rig comparisons only | benchmark |

## Future proof obligations
1. Build **original rights-cleared** pixel-art sheets with irregular frame durations; native 2D bone cutout/mesh rig with IK and deformation, keyed state machine/blend, cutscene camera/audio/VFX cue markers, title/subtitles and signed offline export sample manifest. No sample art/videos/audios copied from Spine/Rive/DragonBones/Godot or their tutorials without rights.
2. Headless CPU reference oracles must prove rational times (60/1, 24/1, 24000/1001, 30000/1001), exact sample schedules (48000, 44100), overflow/rounding/tie, pause/seek/loop/reverse, event-once and rollback independent of GPU frame pacing. These oracles do **not** prove audible A/V synchronization.
3. Actual AUDIO owner integration requires predicted vs acknowledged sample positions, measured device latency/underrun or UNKNOWN and future decoded export pulse/clap comparison against video frame timestamps. Freeze numeric allowable drift/latency and algorithm before approving DoD; no claims of sample-perfect audible playback from schedule alone.
4. Test real Windows DX12/Vulkan, Linux Vulkan, macOS Metal Apple Silicon and WebGPU/WebGL2 fallback, GFX/TWO-01 renderer ownership, GPU skinning optional, device loss/stream recovery and output HDR/reactive masks. Headless test not a native GPU frame capture.
5. Test hostile importer data size, nonfinite rig weights, bone cycle, nested clip recursion, external URL/code execution, cross-project MCP rights and exact license gates Spine custom, Rive splash, DragonBones MIT, Lottie-web MIT/unsupported audio and FFmpeg LGPL/GPL/config. Report all failures; no known HIGH/CRITICAL regression may remain before code.
6. Hardware FPS, CPU/GPU/VRAM/performance and frame/sample drift targets remain **UNDECIDED**; no 60fps or frame-exact media export proven today. All test rows are specification, not a PASS receipt.
