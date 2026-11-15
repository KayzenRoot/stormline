# AUD-02 — Acceptance Matrix: 128 FUTURE Tests, NONE Executed

**Research issue #198 | WO NLE-P00-WO-002-AUD-02 | Future implementation #53 OPEN/BLOCKED.** Exactly **128 prospective cases** (16 suites × 8). All **FUTURE / NOT EXECUTED**: no HRTF SOFA imported, audio generated, room scene, headless mixer, ray/IR simulation, native/Web build, acoustics CPU result, listening evaluation or recorded fixture.

Catalog acceptance: **"Cenário de posições/obstáculos com áudio validado e custos medidos"** currently UNMET.

| ID | Future test scenario | Status |
|---|---|---|
| AUD02-POS-01 | Point emitter directly ahead gives expected azimuth/elevation | FUTURE / NOT EXECUTED |
| AUD02-POS-02 | Source moves behind listener with correct front/back signs | FUTURE / NOT EXECUTED |
| AUD02-POS-03 | Listener rotates 90° and source azimuth changes without pop | FUTURE / NOT EXECUTED |
| AUD02-POS-04 | Stale EntityGuid or WorldEpoch transforms rejected | FUTURE / NOT EXECUTED |
| AUD02-POS-05 | Origin rebase preserves source-listener relative position | FUTURE / NOT EXECUTED |
| AUD02-POS-06 | Source/listener near-coincident zero distance stays finite | FUTURE / NOT EXECUTED |
| AUD02-POS-07 | 2D/headlocked mode never invents 3D depth from pixel art | FUTURE / NOT EXECUTED |
| AUD02-POS-08 | 2.5D mapped world plane and explicit height policy validated | FUTURE / NOT EXECUTED |
| AUD02-ATT-01 | Near and far attenuation match declared finite curve | FUTURE / NOT EXECUTED |
| AUD02-ATT-02 | Missing attenuation curve falls back to safe authored profile | FUTURE / NOT EXECUTED |
| AUD02-ATT-03 | Directional sound behind axis receives bounded reduction | FUTURE / NOT EXECUTED |
| AUD02-ATT-04 | Radial source/listener speed Doppler sign correctly applied | FUTURE / NOT EXECUTED |
| AUD02-ATT-05 | Zero/near-zero sound speed or invalid velocity rejected | FUTURE / NOT EXECUTED |
| AUD02-ATT-06 | Supersonic relative speed clamps pitch without overflow | FUTURE / NOT EXECUTED |
| AUD02-ATT-07 | Moving/teleporting sources crossfade vs discontinuous click | FUTURE / NOT EXECUTED |
| AUD02-ATT-08 | Nonmonotonic custom distance curve rejected or declared intended | FUTURE / NOT EXECUTED |
| AUD02-HRF-01 | SOFA listener/view/up axis converted to CORE-05 convention | FUTURE / NOT EXECUTED |
| AUD02-HRF-02 | Left/right ear impulse symmetry at zero azimuth oracle | FUTURE / NOT EXECUTED |
| AUD02-HRF-03 | Interpolated HRTF at midmeasurement angle has smooth gain | FUTURE / NOT EXECUTED |
| AUD02-HRF-04 | Front/back/height localization blind listening fixture planned | FUTURE / NOT EXECUTED |
| AUD02-HRF-05 | Headphone user changes dataset without realtime parse | FUTURE / NOT EXECUTED |
| AUD02-HRF-06 | SOFA sample-rate mismatch produces explicit SRC plan | FUTURE / NOT EXECUTED |
| AUD02-HRF-07 | Speaker mode bypasses headphone HRTF and uses layout panner | FUTURE / NOT EXECUTED |
| AUD02-HRF-08 | Mono and hearing-accessibility fallback preserves audibility | FUTURE / NOT EXECUTED |
| AUD02-SOF-01 | Reject unsupported SOFA convention and malformed header | FUTURE / NOT EXECUTED |
| AUD02-SOF-02 | Bounds on direction/count/receiver channels and sample arrays | FUTURE / NOT EXECUTED |
| AUD02-SOF-03 | Reject compressed HDF5 bomb and integer multiply overflow | FUTURE / NOT EXECUTED |
| AUD02-SOF-04 | Data rights/attribution for bundled default HRTF checked | FUTURE / NOT EXECUTED |
| AUD02-SOF-05 | Personalized HRTF import requires explicit opt-in consent | FUTURE / NOT EXECUTED |
| AUD02-SOF-06 | No profile upload or microphone/head-scan by default | FUTURE / NOT EXECUTED |
| AUD02-SOF-07 | On revoke, personalized HRTF cache retired after audio fence | FUTURE / NOT EXECUTED |
| AUD02-SOF-08 | User HRTF delete/export/retention policies tested | FUTURE / NOT EXECUTED |
| AUD02-OCC-01 | Wall between source/listener attenuates declared band profile | FUTURE / NOT EXECUTED |
| AUD02-OCC-02 | Removing wall with correct source revision reduces occlusion | FUTURE / NOT EXECUTED |
| AUD02-OCC-03 | Missing cell returns GEOMETRY_UNREADY, not clear LOS | FUTURE / NOT EXECUTED |
| AUD02-OCC-04 | Open door material portal transitions smoothly | FUTURE / NOT EXECUTED |
| AUD02-OCC-05 | Glass vs stone band transmission differs as authored | FUTURE / NOT EXECUTED |
| AUD02-OCC-06 | Multi-ray partial occlusion converges under bounded count | FUTURE / NOT EXECUTED |
| AUD02-OCC-07 | Dynamic physics obstacle query uses correct SIM-02 epoch | FUTURE / NOT EXECUTED |
| AUD02-OCC-08 | Occlusion not used as GAME hit/stealth authority | FUTURE / NOT EXECUTED |
| AUD02-MAT-01 | Surface absorption/transmission/scattering coefficients bounded | FUTURE / NOT EXECUTED |
| AUD02-MAT-02 | Invalid negative or NaN absorption rejected | FUTURE / NOT EXECUTED |
| AUD02-MAT-03 | Frequency-dependent surface profile changes reflected energy | FUTURE / NOT EXECUTED |
| AUD02-MAT-04 | Renderer-hidden LOD not mistaken for absent wall | FUTURE / NOT EXECUTED |
| AUD02-MAT-05 | Collision mesh without acoustic tag doesn't claim full material | FUTURE / NOT EXECUTED |
| AUD02-MAT-06 | Surface topology revision cancels cached ray result | FUTURE / NOT EXECUTED |
| AUD02-MAT-07 | Acoustic proxy and authored scene remain coordinate-consistent | FUTURE / NOT EXECUTED |
| AUD02-MAT-08 | Cross-cell wall deduped at shared streaming seam | FUTURE / NOT EXECUTED |
| AUD02-REF-01 | Single-room first bounce expected path delay oracle | FUTURE / NOT EXECUTED |
| AUD02-REF-02 | Reflection order and ray budget cap bounded CPU jobs | FUTURE / NOT EXECUTED |
| AUD02-REF-03 | Unloaded reflector cell invalidates affected reflections | FUTURE / NOT EXECUTED |
| AUD02-REF-04 | Reflective stone vs absorptive panel controls response | FUTURE / NOT EXECUTED |
| AUD02-REF-05 | Impulse tap update crossfades without audible click | FUTURE / NOT EXECUTED |
| AUD02-REF-06 | Energy not amplified without explicit authored gain | FUTURE / NOT EXECUTED |
| AUD02-REF-07 | GFX ray tracing off cannot kill CPU direct sound | FUTURE / NOT EXECUTED |
| AUD02-REF-08 | Ray tracing never executes on AUD-01 realtime callback | FUTURE / NOT EXECUTED |
| AUD02-REV-01 | Room impulse response/source hash validated | FUTURE / NOT EXECUTED |
| AUD02-REV-02 | Hall/closet transition changes tail smoothly | FUTURE / NOT EXECUTED |
| AUD02-REV-03 | Late reverb route sends only once to AUD-01 bus | FUTURE / NOT EXECUTED |
| AUD02-REV-04 | AUD-03 DSP processing extension does not duplicate device mix | FUTURE / NOT EXECUTED |
| AUD02-REV-05 | IR duration/memory and filter taps capped | FUTURE / NOT EXECUTED |
| AUD02-REV-06 | IR loaded/FFT plan only on non-realtime worker | FUTURE / NOT EXECUTED |
| AUD02-REV-07 | Wet/dry and bypass preserve intelligible dialogue | FUTURE / NOT EXECUTED |
| AUD02-REV-08 | Missing IR falls back to bounded gain/delay approximation | FUTURE / NOT EXECUTED |
| AUD02-ROM-01 | Listener and source same room direct path accepted | FUTURE / NOT EXECUTED |
| AUD02-ROM-02 | Closed portal attenuates cross-room source correctly | FUTURE / NOT EXECUTED |
| AUD02-ROM-03 | Room A-B-C loop graph traversal bounded and reproducible | FUTURE / NOT EXECUTED |
| AUD02-ROM-04 | Portal opening fraction material/revision changes response | FUTURE / NOT EXECUTED |
| AUD02-ROM-05 | Room branch into unloaded cell marked pending/uncertain | FUTURE / NOT EXECUTED |
| AUD02-ROM-06 | Two listeners have distinct room and privacy scopes | FUTURE / NOT EXECUTED |
| AUD02-ROM-07 | Destruction SIM-06 topology update invalidates room graph | FUTURE / NOT EXECUTED |
| AUD02-ROM-08 | Room transitions never yield infinite reverb recursion | FUTURE / NOT EXECUTED |
| AUD02-AMB-01 | ACN/SN3D vs FuMa format mismatch explicitly rejected | FUTURE / NOT EXECUTED |
| AUD02-AMB-02 | First-order Ambisonics yaw rotation reference impulse | FUTURE / NOT EXECUTED |
| AUD02-AMB-03 | Spatial bed orientation tied to listener transform epoch | FUTURE / NOT EXECUTED |
| AUD02-AMB-04 | Higher-order order/channel count capped and supported per tier | FUTURE / NOT EXECUTED |
| AUD02-AMB-05 | Headphone decode and speaker decode not double spatialized | FUTURE / NOT EXECUTED |
| AUD02-AMB-06 | Mono sound preserves center loudness across capability fallback | FUTURE / NOT EXECUTED |
| AUD02-AMB-07 | Channel indexing correct when author switches output mode | FUTURE / NOT EXECUTED |
| AUD02-AMB-08 | Unknown browser channel layout returns capability fallback | FUTURE / NOT EXECUTED |
| AUD02-STR-01 | WORLD-03 acoustic cell lease held during query | FUTURE / NOT EXECUTED |
| AUD02-STR-02 | Cell unload cancels stale geometry/ray jobs safely | FUTURE / NOT EXECUTED |
| AUD02-STR-03 | WorldOrigin rebase updates listener/source/room coordinates | FUTURE / NOT EXECUTED |
| AUD02-STR-04 | Streaming load returns last verified acoustic response with age | FUTURE / NOT EXECUTED |
| AUD02-STR-05 | Stale room/IR bake rejected on source mesh revision change | FUTURE / NOT EXECUTED |
| AUD02-STR-06 | Cross-cell source path remains uncertain until leases ready | FUTURE / NOT EXECUTED |
| AUD02-STR-07 | No callback UAF during geometry snapshot swap | FUTURE / NOT EXECUTED |
| AUD02-STR-08 | Source material changes use DATA-04 CAS and DATA-05 cook source | FUTURE / NOT EXECUTED |
| AUD02-PER-01 | Max rays per source per update bounded by tier | FUTURE / NOT EXECUTED |
| AUD02-PER-02 | IR bank resident memory capped and eviction safe | FUTURE / NOT EXECUTED |
| AUD02-PER-03 | High-priority dialogue gets direct rendering before ambient path | FUTURE / NOT EXECUTED |
| AUD02-PER-04 | Many distant virtual AUD-01 voices skip expensive HRTF work | FUTURE / NOT EXECUTED |
| AUD02-PER-05 | 1000 source query storm backpressured with typed error | FUTURE / NOT EXECUTED |
| AUD02-PER-06 | Expensive propagation job cannot starve CORE-03 audio decode | FUTURE / NOT EXECUTED |
| AUD02-PER-07 | GPU geometry accelerator failure preserves CPU fallback | FUTURE / NOT EXECUTED |
| AUD02-PER-08 | Measured source count 8/32/128/512 produces cost histogram | FUTURE / NOT EXECUTED |
| AUD02-NET-01 | Untrusted client source visibility cannot reveal hidden NPC | FUTURE / NOT EXECUTED |
| AUD02-NET-02 | Acoustic debug API redacts restricted source coordinates | FUTURE / NOT EXECUTED |
| AUD02-NET-03 | Network replayed command cannot inject a new source voice | FUTURE / NOT EXECUTED |
| AUD02-NET-04 | Actor seat/listener role and viewer revision verified | FUTURE / NOT EXECUTED |
| AUD02-NET-05 | Server authoritative sound event remains independent of occlusion | FUTURE / NOT EXECUTED |
| AUD02-NET-06 | Player audio settings cannot change gameplay damage/range | FUTURE / NOT EXECUTED |
| AUD02-NET-07 | Forged acoustic material/portal edit denied by GAME policy | FUTURE / NOT EXECUTED |
| AUD02-NET-08 | Two players with different world interest receive allowed audio only | FUTURE / NOT EXECUTED |
| AUD02-RTC-01 | AUD-01 callback has no acoustic scene queries or file parsing | FUTURE / NOT EXECUTED |
| AUD02-RTC-02 | Plan publication at AudioFrame quantum boundary without blocking | FUTURE / NOT EXECUTED |
| AUD02-RTC-03 | New HRTF filter profile swapped with deferred old buffer retirement | FUTURE / NOT EXECUTED |
| AUD02-RTC-04 | DeviceEpoch changed invalidates obsolete sample render plan | FUTURE / NOT EXECUTED |
| AUD02-RTC-05 | Headless NullSink uses same semantic spatial plan | FUTURE / NOT EXECUTED |
| AUD02-RTC-06 | No RT allocation/lock/log/codec/FFT planning in source spatialization | FUTURE / NOT EXECUTED |
| AUD02-RTC-07 | Graphics frame 20/60/240 FPS doesn't alter sample position | FUTURE / NOT EXECUTED |
| AUD02-RTC-08 | Underflow from missed spatial plan uses typed fallback not noise | FUTURE / NOT EXECUTED |
| AUD02-SAF-01 | Malformed acoustic mesh/triangles rejected before ray tracing | FUTURE / NOT EXECUTED |
| AUD02-SAF-02 | Truncated SOFA/HDF5 fuzz hardens importer | FUTURE / NOT EXECUTED |
| AUD02-SAF-03 | Oversized IR/room graph cancellation no memory leak | FUTURE / NOT EXECUTED |
| AUD02-SAF-04 | ASan/UBSan/TSan future scene/unload/plan ownership tests | FUTURE / NOT EXECUTED |
| AUD02-SAF-05 | MCP cannot read hidden HRTF/voice/room source metadata | FUTURE / NOT EXECUTED |
| AUD02-SAF-06 | Crash during DATA-05 bake keeps last valid chunks | FUTURE / NOT EXECUTED |
| AUD02-SAF-07 | HRTF dataset rights and attribution closure checked | FUTURE / NOT EXECUTED |
| AUD02-SAF-08 | Intentional audio output clipping and overgain denied/clamped | FUTURE / NOT EXECUTED |
| AUD02-BEN-01 | Native Win/Linux/macOS CPU headless acoustic fixture | FUTURE / NOT EXECUTED |
| AUD02-BEN-02 | Web AudioWorklet/SOFA support capability with safe fallback | FUTURE / NOT EXECUTED |
| AUD02-BEN-03 | P50/p95/p99 CPU ray/path/IR and callback measured separately | FUTURE / NOT EXECUTED |
| AUD02-BEN-04 | Blind front/back/height localization test headset provenance | FUTURE / NOT EXECUTED |
| AUD02-BEN-05 | Original room impulse response measured relative to analytic oracle | FUTURE / NOT EXECUTED |
| AUD02-BEN-06 | Early reflection/occlusion sounds compared to legal reference fixture | FUTURE / NOT EXECUTED |
| AUD02-BEN-07 | One-hour streaming+rebase+door+HRTF change no leaks/clicks | FUTURE / NOT EXECUTED |
| AUD02-BEN-08 | No claim of AAA superiority without matched measured hardware | FUTURE / NOT EXECUTED |

## Future verification hierarchy
- Unit/golden: physically plausible unit conversions/azimuth, HRTF filter interpolation/ear channel labels, directivity/Doppler and atten curves, room/portal graph/room impulse response, ray intersections vs geometric oracle and finite fallback.
- Integration: AUD-01 f32/VoiceHandle/DeviceEpoch/NullSink, WORLD-02 stable rooms/proxy geometry, WORLD-03 leases/OriginEpoch, WORLD-04 materials, SIM-02 collider revisions, DATA-03/04/05 source rights/cook and CORE-03 async scheduling.
- Security/failure: hostile SOFA/HDF5/mesh/IR input, rate/size quota, stale pointers during device/source unload, UAF, privacy/hidden enemy source, ASan/TSan/UBSan and crash-recovery after stale baked data.
- Acoustic accuracy: original fixtures, measured impulse delay/attenuation error, objective CPU/heap/IR cost, source localization blind tests on known headphones with listener consent, sample/driver and independent platform baselines; no guarantee perfect personalization.
- Native/Web matrix: Win/Linux/macOS CPU, optional WASM AudioWorklet with explicit browser activation/fallback. No measured universal feature support, GPU dependence or sound quality claims today.

**All 128 cases remain NOT RUN** and have no PASS/FAIL. The GitHub Docs Validation on research/registry is documentary-only and does not execute any audio runtime. Quantitative thresholds, measured localization and device latency require actual built test scenes and independently verifiable evidence.
