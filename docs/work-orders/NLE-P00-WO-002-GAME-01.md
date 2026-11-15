# Research Work Order — NLE-P00-WO-002-GAME-01

**Date:** 2026-11-15 | **Research issue:** #208 | **Future implementation issue:** #56 OPEN/BLOCKED  
**BASE main:** `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9` | **P00 DOCUMENTATION ONLY.** Research risk LOW; future runtime implementation ELEVATED for privacy/focus, multi-device input spoofing, malformed input profiles, critical bindings, cross-platform consistency and accessibility. Release class UNDECIDED; engine code license NLE-D009 OPEN.

## OBJECTIVE
Research and specify engine-owned keyboard/mouse/gamepad/touch semantic input and action mapping, focus/context routing, player seats, accessible remapping, tick-scoped action frames and replay, CORE-01/04 integration, native and Web adapters, security/privacy, official technology/license matrix and future test/benchmark protocols.

## CONTEXT
AUD-04 research issue #204 closed after research PR #205, separate checkpoint PR #206 and readback closeout PR #207 merged. Last main readback `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9`. Checkpoint shows **38/80** research documented (47.5%), **42 pending**, **0 runtime modules implemented**. All 80 code packets remain `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false`, `approved_adr=null`. Catalog order GAME-01=39, required CORE-01 platform/lifecycle, itself only researched not implemented. Future code issue #56 remains OPEN/BLOCKED; next GAME-02 is catalog order 40, future code issue #58.

## SCOPE
Exactly eight new Markdown documents:
1. [Input/control architecture](../architecture/game-01-input-control-mapping.md)
2. [ADR-0042 PROPOSED](../adr/0042-game-01-engine-owned-input-actions.md)
3. [Input technology/license/standards matrix](../research/game-01-input-technology-license-matrix.md)
4. [Versioned semantic API and error contracts](../contracts/game-01-input-actions-api.md)
5. [128 prospective acceptance cases](../testing/game-01-acceptance-matrix.md)
6. [Reproducible responsiveness/device/accessibility benchmark protocol](../research/game-01-input-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-01.md)

Create research issue #208 and dedicated research branch/PR; validate exact final HEAD Docs Validation, perform objective pt-BR scoped audit, normal squash/readback. Then create a **separate checkpoint PR** with own exact-head CI/audit/squash/readback. Reconcile only the GAME-01 research_status, backlog, checkpoint and appropriate WO/Evidence; close #208 only after successful checkpoint readback.

## OUT OF SCOPE
Any code, SDK install, SDL3/native adapter implementation, OS global event hooks, controller database import/download, driver/USB HID privileges, platform input handling, physical/virtual device, new window/event pump, gameplay action script, UI/IME focus renderer, cloud profile sync, anti-cheat, network input authority, device fingerprint collection, haptics/rumble/gyro integration, actual gamepad testing, input latency benchmark, Web browser build, deployment, paid CI or extraneous cleanup. Do not modify future code issue #56 or unlock any of the 80 coding packets.

## FILES / SOURCES TO READ (canonical order)
`docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/GAME-01.md` > `docs/architecture/core-01-platform-lifecycle.md`, `docs/architecture/core-04-time-simulation.md`, `docs/architecture/data-04-serialization-scene-format.md` and related approved/proposed docs. Official technology/spec/license URLs appear in the research matrix.

## REQUIREMENTS
GOV-001..005, program CAP/NFR candidates as relevant, NLE-D013 no public MVP before v1 DoD, NLE-D014 2D/2.5D/3D + Web games, NLE-D015 AI/MCP authorized public authoring APIs, NLE-D016 80-module inventory, NLE-D017 required Windows/Linux/macOS desktop and planned Web, NLE-D018 delegated routine documentary actions without bypass/payment, NLE-D019 prewritten code Work Orders, NLE-D020 all blocked queue. Catalog acceptance **"Mapeamentos consistentes entre editor, runtime e exports"** remains NOT PROVEN.

## ARCHITECTURE RULES
- **CORE-01 exclusively owns OS SDL3/native event loop**, window/device/focus/host lifecycle and PlatformEvent; GAME-01 cannot pump SDL independently or expose third-party types in public APIs.
- GAME-01 owns semantic device-state normalization, opaque DeviceEpoch, PlayerSeat routing, versioned `ActionMap/Binding/Context/ActionFrame`, accessible remapping and deterministic action resolver.
- **CORE-04 owns TickId**; input sampled at fixed-tick fences, all button edge events preserved, render FPS/wall clock cannot advance gameplay input. Replay can prove resolver determinism only, not hardware/whole game.
- UI/Editor owns actual focus, text entry and IME; input context routes are immutable read-only. GAME/NET validates gameplay action authority; remote client action frame is untrusted.
- DATA-01/02/04/05 own scoped VFS, asset identity, authoring CAS/journal/migration and cooked profile packaging. CLI/MCP authoring through same role-scoped typed commands; no raw input injection or background capture.
- Physical scancode differs from logical key/Unicode text, keyboard locale and virtual accessibility devices. Mouse absolute/relative/DPI, touch pointers/multigesture and gamepads analog must be capability gated and bounded.
- SDL3 zlib preferred CORE-01 adapter candidate, GLFW zlib comparator, HIDAPI multi-license future; optional Microsoft GameInput/Apple Game Controller vendor SDK terms not assumed permissive; SDL_GameControllerDB repository zlib optional data after exact provenance review. W3C Gamepad Working Draft 2026-11-14, Pointer Events Level 3 Recommendation 2026-06-30, WCAG 2.2 reference only. Nothing adopted.
- Focus loss/disconnect/overflow synthesizes safe release+reset; no stuck actions, data corruption, unbounded queues or hidden escape key removal. Privacy: no persistent HID fingerprints, text/password capture, OS hooks or default per-key logs. Accessibility: alternate single-pointer/keyboard paths, hold-toggle/one-handed/recovery.

## CONSTRAINTS
No source/runtime code, SDK/asset/license adoption, claimed latency or device support. Do not change existing approved ADR, CORE-01 or code packet. Future coding issue #56 must remain OPEN/BLOCKED, all 80 WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS` / `executor_ready=false` / `approved_adr=null`; release_class UNDECIDED. Zero mandatory paid CI, solo objective audit, no external reviewer, force push or bypass. If Source Pack or main changed, mark Context Lock STALE before further actions.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new scoped Markdown artifacts, correct links and source ownership; no runtime files, external dataset, assets, CI or unrelated changes.
- [ ] ADR-0042 remains PROPOSED, no SDL3/GLFW/HIDAPI/GameInput/Apple SDK or controller DB adopted.
- [ ] CORE-01 event/lifecycle ownership; CORE-04 fixed tick; GAME-01 device-seat-action-context mapping; UI focus/IME; DATA-04 CAS; GAME/NET authority are coherently separated.
- [ ] Keyboard layout/physical vs logical/IME, mouse/touch, multi-controller seats, analog deadzones, conflict-safe remaps, persistence/migration, accessibility, focus-loss recovery, Web denial/fallback and privacy/security are contractually specified.
- [ ] Source/licensing/W3C status verified and bounded, no universal platform/driver/assistive support claims.
- [ ] Exactly **128** future acceptance cases, all **FUTURE / NOT EXECUTED**; reproducible hardware/input latency/throughput/replay/accessibility benchmark protocol, thresholds UNDECIDED.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS (Source Pack+links, module DAG, registry, Zcode blocked selector), objective pt-BR scoped audit APPROVED, normal squash and main readback.
- [ ] Separate checkpoint PR exact-final-HEAD Docs Validation/audit/squash/readback; **only GAME-01 research_status** changes to `RESEARCH_DOCUMENTED_ADR_PROPOSED`; **39/80 documented (48.75%), 41 pending, 0 runtime**.
- [ ] All 80 implementation packets remain blocked, `executor_ready=false`, `approved_adr=null`; code #56 OPEN/BLOCKED. Next research GAME-02 (#58) only after checkpoint readback.

## TESTS
Research-only GitHub **Docs Validation** (local links, Source Pack, module taxonomy/DAG, registry, Zcode blocked selector). No SDL/native/Web/headless runtime, C++/WASM build, actual keyboard/controller/touch device test, fuzz/ASan, accessibility user/assistive tests, benchmark/latency or profiler run. All 128 prospective cases NOT EXECUTED.

## DELIVERABLES
Issue #208; eight scoped documents; research PR with recorded exact final HEAD, all passing applicable docs checks, Evidence Bundle and pt-BR audit/normal squash/main readback; independent checkpoint PR with its own CI/audit/normal squash/main readback; research issue close after checkpoint readback. No Zcode coding authorization.

## REVIEW FORMAT
In pt-BR state APPROVED / CORRECTION REQUIRED / BLOCKED, exact BASE/HEAD SHA, changed files, verified Source Pack critical Git blob fingerprints, requirements/ownership/standards/licenses/privacy/accessibility/rollback review, actual workflow run/job steps and result, 128 prospective cases NOT RUN, absence/presence HIGH/CRITICAL, scoped checkpoint delta and safe readback. No "completed" claim without actual evidence.

## STOP CONDITION
Stop on approved decision or critical Source Pack drift, license/permission ambiguity requiring owner decision, unexpected source code/SDK/credential/data capture, privacy leak, inaccessible critical remapping, high/critical documentary defect, non-green exact-head CI, registry safety invariant failure or merge/ruleset rejection. Corrections remain SAME research WO/PR, no GAME-02 research overlap while blocked.

## CONTEXT LOCK — Git blob fingerprints (not SHA-256; recheck before merge)
Main base `0a3aa77229f5663e55fdf9b8b99a786c9edb1cc9`.
- Checkpoint `e38dc2d0d9408492784b57858add2200587530e7`
- Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- Backlog `54e8ef07eb925aa5c0d46251898706e9d6d393b3`
- Catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Registry `80faa7df5ac377298dd42df3338d76cd7f0429b1`
- Implementation shell `e2e199b5c572bc29b11c34472a9abf4c5dc2d4f7`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- CORE-01 `11c7ec4125f40cf0172aa552a1e9835e84d2c172`
- CORE-04 `b40b1bf97b934a883d6bb99e45bd40de6711912c`
- DATA-04 `7e88d4fecaa83c9922f255087df9f97f6300b61f`

## EVIDENCE
[Evidence Bundle](../evidence/NLE-P00-WO-002-GAME-01.md). At initial drafting, PR/CI/audit/merge remain PENDING.
