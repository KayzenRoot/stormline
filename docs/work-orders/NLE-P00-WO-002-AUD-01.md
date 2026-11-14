# Research Work Order — NLE-P00-WO-002-AUD-01

**2026-11-14 | Research issue #195 | Future code issue #52 OPEN/BLOCKED**  
**BASE main:** `21e50e73cf1f5f3a3c01bb2f869422161b28e248` | **P00 DOCUMENTARY ONLY**, risk LOW docs, future ELEVATED for RT memory, codec fuzz, hotplug, privacy/device/network. Release class UNDECIDED, engine code license NLE-D009 OPEN.

**RESEARCH RESULT APPROVED/MERGED:** [PR #196](https://github.com/KayzenRoot/stormline/pull/196), final audited head `ba3146b32346df92fc9c4e5b7be84096075c78c2`, [Docs Validation #43655480415](https://github.com/KayzenRoot/stormline/actions/runs/43655480415) SUCCESS job #132632929897, objective pt-BR audit comment #6886186954, normal squash main `b70abb72357c48610ec9610816a922226c19355c` and readback. Separate checkpoint PR still requires own CI/audit. 128 tests NOT RUN, coding issue #52 BLOCKED.

## OBJECTIVE
Specify a proprietary-semantics Stormline low-latency audio device/mixer with native output multi-backend, sample clock and CORE-04 mapping, float32 bus DAG mixing, voice virtualization and priority, stream/decode off real-time threads, resampling, device hotplug, headless NullSink and optional browser AudioWorklet, typed security/privacy/authoring contracts, future measurable underrun/latency/voice tests.

## CONTEXT
At issue opening, predecessor SIM-07 research #192 PR #193 + checkpoint PR #194 audited/merged, latest main `21e50e73cf1f5f3a3c01bb2f869422161b28e248`. Baseline 34/80 researches documented, 46 pending (historical CORE-04 research-status gap), zero engine implemented; all 80 coding WOs BLOCKED. AUD-01 catalog order 35, dependencies **CORE-01 · CORE-03**, both researched on paper but not implemented. AUD-02/03/04 pending; future code #52 OPEN/BLOCKED.

## SCOPE
Eight new research-only Markdown documents: architecture, ADR-0038 PROPOSED, current technology/license matrix (SDL3/miniaudio vs PortAudio/cubeb, dr_libs/Opus/libsamplerate, AudioWorklet), semantic versioned voice/bus/device/time API, 128 FUTURE test case matrix, reproducible benchmark/quality protocol, full Work Order and Evidence Bundle. Dedicated GitHub research issue/branch/PR, exact-HEAD Docs Validation and pt-BR objective audit; normal squash/main readback. Separate minimal checkpoint PR with independent exact-head CI/audit/squash and registry research_status only.

## OUT OF SCOPE
C++ audio runtime, SDK install/vendor pin, actual sound capture/production, microphone/loopback recorder or voice chat without explicit permission, proprietary copyrighted samples, DSP plugin synthesis and HRTF/AUD-02/AUD-03/AUD-04 implementation, network transport/game command changes, target numerical performance promises, other module cleanup, paid services, external reviewer, force-push or release of coding #52.

## FILES / SOURCES TO READ
Canonical order: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md`/approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/AUD-01.md`. Module contracts [CORE-04 clock](../architecture/core-04-time-simulation.md), [DATA-05 streaming/cook](../architecture/data-05-cooking-streaming-bundles.md), CORE-01/02/03/06 research, EDIT/CLI/MCP. Official audio sources linked in research license matrix. Future source code paths/CI commands TBD on code approval; don't invent.

## REQUIREMENTS
GOV-001..005, CAP-003 audio and CAP-004 interactions, native Win/Linux/macOS Editor+export, optional Web AudioWorklet, headless CPU/null render, 2D/2.5D/3D clients, accessible per-bus/dialogue priorities, all authoring commands through one scoped Editor/CLI/MCP kernel, license/source rights, original signal fixtures, no public MVP until DoD. Catalog acceptance underruns/latency/voice cost remains UNMET.

## ARCHITECTURE RULES
CORE-01 owns native device/lifecycle, CORE-03 decode worker job and cancellation, CORE-02 audio memory arenas, CORE-04 TickId while **device owns sample clock**, CORE-06 counters, DATA-02/03/04/05 source rights/asset/CAS/cook. AUD-01 owned bus DAG f32 mix/voice lifecycle/virtualization; AUD-02 HRTF/spatial, AUD-03 DSP effects, AUD-04 music/dialogue in later WOs. No callback lock/allocation/log/file IO/codec decode; one PCM backend adapter, no double mixing, bounded queue and samples, generational handles/DeviceEpoch, secure no-input permission by default.

## CONSTRAINTS
Docs-only, no packages/audio files or code, no actual device/latency/voice benchmark, no source license decision. 128 runtime tests **FUTURE/NOT EXECUTED**. All coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`; future #52 OPEN/BLOCKED, release class UNDECIDED. No paid service, CodeRabbit, force push/history rewrite or CI bypass.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 new docs with clear architecture, bus/clock/voice/stream/security boundaries and no code adopted.
- [ ] ADR-0038 PROPOSED, official candidate/license matrix and exact upstream versions/unverified dependency closure clearly described.
- [ ] Typed API and error codes; explicit sample clock vs fixed game tick; RT no lock/alloc/IO, device hotplug/epoch, bounded voice virtualization, source codec rights.
- [ ] 128 planned tests and reproducible benchmark/rights/privacy plan **NOT EXECUTED**, no fabricated hardware threshold.
- [ ] Research PR with exactly 8 doc paths, final-HEAD Docs Validation SUCCESS and objective pt-BR APPROVED, no known HIGH/CRITICAL in scoped diff, normal squash main readback.
- [ ] Separate same-WO checkpoint PR with exact-HEAD CI/audit/squash/main readback: research tallies **35/80 (43.75%)** documented, **45 pending** (CORE-04 historic gap), 0 implemented; every coding packet still blocked, #52 OPEN/BLOCKED.
- [ ] Only then issue #195 research closed and AUD-02 next research candidate; do not unlock executor.

## TESTS
P00 only existing GitHub Docs Validation (Source Pack/links, catalog/DAG, work order registry, Zcode blocked selector). No C++/audio native/browser/headless implementation or fuzz/sanitizer/actual CPU/latency performance tests were run. Future matrix 128 cases all NOT EXECUTED. Record actual final head workflow run/job and all steps after Evidence revisions.

## DELIVERABLES
Architecture, ADR-0038, technology/license matrix, semantic API, acceptance matrix 128, benchmark protocol, this Work Order and Evidence Bundle, research issue #195, PR(s), actual CI/audit receipts and source checkpoint. Coding issue #52 remains separate blocked.

## REVIEW FORMAT
pt-BR objective report with exact BASE/HEAD, changed files, CI workflow/job and results, licensing/source/privacy threats, no executed runtime benchmarks, regression/security concerns, verdict APPROVED/CORRECTION REQUIRED/BLOCKED, checkpoint delta proposed and next stop condition.

## STOP CONDITION
If stale base/critical Source Pack fingerprints, unexpected non-doc diff, ambiguous license/remote source, missing exact-HEAD CI, failing CI, known HIGH/CRITICAL in docs, accidental executor-ready flag, unresolved correction or bypass, STOP: Correction Delta on same WO/PR or BLOCKED. No AUD-02 research until checkpoint merged and readback confirmed.

## CONTEXT LOCK
BASE main `21e50e73cf1f5f3a3c01bb2f869422161b28e248`; canonical blobs at preflight: checkpoint `319a05d912a548057465944f4874ac7549272b70`, ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`, Scope `4ef605c74632ece080b2650e37dd83a415b63310`, DoD `160b3054db9ea1961308934b401488b838d24c3e`, architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`, catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`, registry `1f0ff0da0a8408d33f71a75f8c8060451ce0abc3`. Revalidate critical changes, don't overwrite approved decisions.

## EVIDENCE
See [Evidence Bundle](../evidence/NLE-P00-WO-002-AUD-01.md). PR/CI/audit/merge only reported after actual GitHub observation.
