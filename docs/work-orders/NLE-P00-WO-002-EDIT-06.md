# NLE-P00-WO-002-EDIT-06 — VFX / Audio / Animation Authoring P00 Documentary Research Work Order

**2026-11-15 | Research [#272](https://github.com/KayzenRoot/stormline/issues/272) | catalog_order=55 | future implementation [#73](https://github.com/KayzenRoot/stormline/issues/73) OPEN/BLOCKED.** BASE main `67e6af436f4985474b2e6dc5aa47183c32113230`. Baseline 54/80 research documented, 26 pending, zero engine; all 80/80 implementation WOs BLOCKED. Formal dependencies **EDIT-02, GFX-08, AUD-04, SIM-04**, all research documented/ADR PROPOSED only and code issues #69/#36/#55/#49 OPEN/BLOCKED. Risk LOW for docs; future runtime/sync/realtime ELEVATED. Arbitrary native plugins or realtime untrusted code are OUT OF SCOPE and require separate HIGH_ASSURANCE approval.

## OBJECTIVE
Research a professional authoring workspace for sequencers/timelines, VFX particle graphs, audio DSP graphs, adaptive music/dialogue/timed text and skeletal animation state graphs. Editor/runtime must reproduce the same canonical source/evaluator content. Specify rational sequence time, CORE-04 TickId, AUD-01 SampleFrameId/DeviceEpoch mapping, owner receipts, buttons/commands, preview, validation, export, accessibility, licenses, security, 128 tests and benchmarks. **No engine code or dependency adoption.**

## CONTEXT
Source Pack precedence: checkpoint > Decisions Ledger/approved ADRs > Scope > DoD > Architecture > Requirements > remaining docs. Verified main SHA `67e6af436f4985474b2e6dc5aa47183c32113230`, no open PRs. Registry 80 modules, 54 documented/26 pending; EDIT-06 RESEARCH_PENDING, formal dependencies EDIT-02/GFX-08/AUD-04/SIM-04, code #73 OPEN/BLOCKED, risk UNCLASSIFIED, release UNDECIDED. Research issues #256/#144/#204/#183 are closed after prior readbacks; predecessor code #69/#36/#55/#49 remain OPEN/BLOCKED. All 80 code packets remain BLOCKED.

## SCOPE — exactly eight NEW Markdown files
1. [Architecture](../architecture/edit-06-vfx-audio-animation-authoring.md)
2. [ADR-0058 PROPOSED](../adr/0058-edit-06-unified-sequencer-vfx-audio-animation-authoring.md)
3. [Technology/license/security/interoperability matrix](../research/edit-06-authoring-technology-license-matrix.md)
4. [Typed sequencer/graph/button/preview contracts](../contracts/edit-06-authoring-api.md)
5. [Exactly 128 E06-T001..E06-T128 FUTURE tests](../testing/edit-06-acceptance-matrix.md)
6. [Benchmark/fault protocol](../research/edit-06-authoring-benchmark-protocol.md)
7. This Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-EDIT-06.md)

Research PR adds exactly these eight files. No checkpoint/backlog/registry/CI/code/SDK changes in research PR. After exact-final-HEAD Docs Validation and objective pt-BR audit, normal squash merge and factual main/API readback, create independent five-file checkpoint PR: checkpoint, backlog, registry (SOLE EDIT-06 research_status), this WO and Evidence. Target 55/80 documented (68.75%), 25 pending, zero engine; all 80 code WOs blocked. After checkpoint CI/audit/squash/readback, close #272. Future code #73 stays OPEN/BLOCKED. A separate four-Markdown historical closeout may follow with its own gates. Do not begin EDIT-07 until this closeout is objectively read back.

## OUT OF SCOPE
C++/Rust/TypeScript editor/runtime; new timeline/clock/evaluator; particle simulation, DSP/mixer, audio device, animation state machine or physics/root-motion runtime; codec/encoder or FMOD/Wwise/other SDK installation; arbitrary script/custom node/native plugin; microphone capture; remote/cloud compilation; collaborative timeline; AI auto-commit; media download or third-party proprietary assets; paid CI, CodeRabbit, external reviewer requirement; public MVP; release class/license approval; performance/a11y claims. No registry unblock, bypass, force-push or unapproved scope expansion.

## FILES / SOURCES TO READ
Canonical order: `docs/11-checkpoint.md` > `docs/10-decisions-ledger.md` and approved ADRs > `docs/03-scope.md` > `docs/09-definition-of-done.md` > `docs/04-architecture.md` > `docs/02-requirements.md` > `AGENTS.md` > `docs/product/module-catalog.md` > `docs/queue/implementation-registry.json` > `docs/queue/work-orders/EDIT-06.md`. Formal dependencies: EDIT-02 architecture/API/ADR-0054; GFX-08 architecture/API/ADR-0021/matrix/tests; AUD-04 architecture/API/ADR-0041/matrix/tests; SIM-04 architecture/API/ADR-0034/matrix/tests. Integration owners: AUD-03 architecture/API/ADR-0040, TWO-03 architecture/API, AUD-01, CORE-04, EDIT-01, EDIT-05, DATA-01/02/03/04/05, GFX-01/03/06/07, EDIT-07, QA-04 and AI/MCP. Official sources in matrix: OpenTimelineIO, glTF animation, WebVTT, TTML2, Effekseer, ozz, ACL, Web Audio API, FMOD legal, Godot AnimationTree and Unreal Sequencer.

## REQUIREMENTS
GOV-001..005; CAP-002, CAP-003, CAP-004, CAP-008, CAP-009, CAP-010, CAP-011, CAP-012, CAP-013, CAP-014, CAP-016; NFR-001..005; NLE-D013..020. Catalog acceptance: **Editor e modo runtime reproduzem mesmo conteúdo.** Requires real GUI authoring, same owner evaluator/source hashes, editor preview and game runtime playback/event receipt parity, not a mock editor-only simulation. No 1.0 release class, engine license NLE-D009, toolkit, codec, SDK or numeric budget approved.

## ARCHITECTURE RULES
EDIT-06 owns authoring UX and presentation only. EDIT-01 shell/button registry; EDIT-02 project scope; TWO-03 sequence/timebase; CORE-04 TickId; AUD-01 sample clock/mixer; GFX-08 VFX graph; AUD-03 DSP graph; AUD-04 music/dialogue/captions; SIM-04 animation graph/pose; SIM-03 root motion acceptance; SIM-02 physics; DATA-02/03/04/05 assets/import/persistence/cook; GFX-01/03/06/07 render/device/light/color; EDIT-07 preview; QA-04 security. Formal DAG remains exactly EDIT-02/GFX-08/AUD-04/SIM-04; AUD-03/TWO-03 are integration owners, no new direct edges. No generic graph IR/evaluator, duplicate sequence or clock. Same runtime evaluator and exact source revision for editor preview/runtime. All buttons use EDIT-01 EditorCommandIdV1 with GUI/CLI/MCP permission parity.

## CONSTRAINTS
Research-only risk LOW. Fingerprints in Evidence are Git blob object SHAs, **not byte SHA-256**. Refresh before mutation; checkpoint/Scope/DoD/Architecture/approved ADR drift => Context Lock STALE and recompile. No false claims of realtime audio, sample-exact audible output, deterministic GPU particles, root-motion acceptance, runtime parity or benchmark. All 80 code WOs remain BLOCKED.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight NEW Markdown deliverables, scoped diff only.
- [ ] ADR-0058 PROPOSED; formal DAG unchanged; domain-specific owner graph semantics retained.
- [ ] Sequencer view uses TWO-03 rational SequenceAsset; time sync maps CORE-04 TickId and AUD-01 SampleFrameId/DeviceEpoch.
- [ ] VFX/AUD DSP/AUD music-dialogue/SIM animation use existing owner APIs and runtime evaluators.
- [ ] Buttons follow EDIT-01 command registry with accessible names/states/disabled reasons, focus/IME, progress/cancel and GUI/CLI/MCP parity.
- [ ] Editor/runtime parity contract, last-good isolated preview, owner receipts, safe import/export and licensing/security matrix.
- [ ] Exactly 128 unique E06 tests all FUTURE/NOT EXECUTED; reproducible benchmark/fault protocol with thresholds TBD.
- [ ] Research PR exact-final-HEAD Docs Validation SUCCESS, exact eight-file diff, pt-BR audit APPROVED with no HIGH/CRITICAL, normal squash and main readback.
- [ ] Independent checkpoint PR changes exactly five files and only EDIT-06.research_status; own exact-head CI/audit/squash/readback. All 80 code WOs remain BLOCKED.
- [ ] Optional four-file historical closeout has own gates; #272 closes only after checkpoint readback, code #73 remains OPEN/BLOCKED.

## TESTS
Existing Docs Validation: Source Pack/local links, catalog taxonomy/DAG, registry schema and Zcode selector rejecting blocked WOs. Verify exactly eight new files and 128 unique IDs. CI must run at exact final PR HEAD; no local test claim without actual checkout. Future runtime matrix and benchmark protocol; all NOT EXECUTED.

## DELIVERABLES
Eight Markdown docs, research issue/branch/PR, exact base/head/diff, CI job evidence, pt-BR audit, risks, proposed checkpoint delta and actual main readback. No source code, audio output, VFX asset, animation clip or exported media.

## REVIEW FORMAT
Português brasileiro: APPROVED / CORRECTION REQUIRED / BLOCKED; exact base/head; eight file paths; 128 unique tests/count; CI run and steps; domain ownership/timebase/sync/security/license/accessibility audit; HIGH/CRITICAL defects; fixes; checkpoint delta and stop condition.

## STOP CONDITION
Stop on stale source/fingerprint, unexpected file diff, DAG inflation, duplicated owner evaluator/clock/mixer, unsupported codec/license, arbitrary executable node/plugin, RT callback allocation/lock/IO, timeline drift, editor/runtime mismatch, unsupported target promise, CI failure, test count mismatch, HIGH/CRITICAL or any attempt to unlock #73/another code packet.

## CONTEXT LOCK — planning baseline
Verified main BASE `67e6af436f4985474b2e6dc5aa47183c32113230`. Critical Git blob fingerprints at Source Check (Git object SHA-1, **not byte SHA-256**):
- Source Hierarchy `58a377bc76cafdd3377d733d4f30ef53661bb034`
- Checkpoint `cf7fad7e0b4065332a79c6018688ea6bfbd6ffbe`
- Decisions Ledger `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- Scope `4ef605c74632ece080b2650e37dd83a415b63310`
- DoD `160b3054db9ea1961308934b401488b838d24c3e`
- Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- AGENTS `3e57b719f8651407879ebb641707a048773ea4c2`
- Module catalog `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- Implementation registry `7595dd8309a98f324096e869a8d2e82ae154c28f`
- EDIT-06 blocked packet `e3cc63483530b59f6aafeab63e9ce78e369bb9b2`
- EDIT-02 architecture/API/ADR `48c7ab698950d48e761b56f1f05dbd56b4ea8d9e` / `d2ce33b3d52f9a73bbf7de51af80ab800ce4e720` / `ae328eeb6ee5a07b58f2235102d2114fe7ea1213`
- GFX-08 architecture/API/ADR/matrix/tests `33bf971654f557b7ad6d969eb68573e495ef7759` / `531cc596ff25e5964ec27e9e43d3a4f583dfcd36` / `ee87b963fd5953e2faf646cbc9d9d02723819ec0` / `568d498638ff0319689ff8b1ebc6bada1febffcd` / `5811dfc2abb44e2e954d969b1108531ea5ebf7d6`
- AUD-04 architecture/API/ADR/matrix/tests `8104ddac546ab5133372859e71e771b66750ccf0` / `65d8d1186896cf84eb4dc4f7ffe32aa57269b626` / `6dde2b1477c89eac717a070f8af932b48f5eae13` / `84db02a99be461208cdab8f66e0740a2ae71851f` / `dc38d8afb7baaaaf3a157062159c9af508e735d3`
- SIM-04 architecture/API/ADR/matrix/tests `8f1d0a9211c093322d8a2868cc6ef89a6308c919` / `da2dde2a7b742ed2fc72be5797cd0476d88d89bf` / `45bc3a8cec22e2b22160b2193869691d4fa4c8fc` / `732ffafcfbcd8164797e8074593e57bdd2cc4819` / `cf59f14aff28465141771f862bdde449ed151496`
- AUD-03 architecture/API/ADR `0847210bdfdcc7545a67695c4a0c46361f92e3c0` / `32a7be50b61b1829d5f11af32f6dc816fe06899d` / `b36bba1c6a00e686b21669af2d2cb9e9cc7cb293`
- TWO-03 architecture/API `f900c6b60e5d218723f985d4c518193ec09c1dee` / `0b9ae436513edc1dfcabb6f613cdd9deb2157b8a`
- CORE-04/AUD-01/DATA-04 architecture `b40b1bf97b934a883d6bb99e45bd40de6711912c` / `2967a42d44d115cfaf85ff9576e431c732daaf4e` / `7e88d4fecaa83c9922f255087df9f97f6300b61f`
- EDIT-01 command API `e2c713c6666f0521f44b1d0920b1a696391844d7`; EDIT-05 architecture/API `cf117bc70675a02bcf35db3e950a3fa68bf9f0d1` / `35f37fb5a7f7bd13492ffe8788461b00f3e11798`

Refresh before writes; any critical source change makes Context Lock STALE and requires rebase/re-audit.

## EVIDENCE BUNDLE
See [Evidence](../evidence/NLE-P00-WO-002-EDIT-06.md); record only observed base/head/diff/CI/audit/merge/readback. No inferred runtime/test/benchmark success.

## Research PR #273 APPROVED/MERGED; checkpoint PR initiated
- [Research PR #273](https://github.com/KayzenRoot/stormline/pull/273): BASE `67e6af436f4985474b2e6dc5aa47183c32113230`, final HEAD `9e2d6164b27d8bdcb9518bbc34d2b387e71b3c23`, exactly eight new Markdown. [Docs Validation #43736503999](https://github.com/KayzenRoot/stormline/actions/runs/43736503999) SUCCESS job #132880165544, all Source Pack/links, DAG, registry and blocked selector steps SUCCESS. [Audit #6897757289](https://github.com/KayzenRoot/stormline/pull/273#issuecomment-6897757289) APPROVED documentary only; normal squash and factual main/API readback `692fdf625102c4f82f451c78683dddca6d1882b2`. No code/SDK/CI/checkpoint/backlog/registry changes in research PR.
- 128 E06 IDs unique, FUTURE/NOT EXECUTED. ADR-0058 PROPOSED, NLE-D009 OPEN, #73 OPEN/BLOCKED. No runtime, preview, export, sample sync or native/Web tests.
- Independent checkpoint PR from main `692fdf625102c4f82f451c78683dddca6d1882b2` modifies exactly checkpoint/backlog/registry/this WO/Evidence. Only registry semantic delta is EDIT-06 research_status. Own CI/audit/merge/readback required before #272 closure. Target 55/80, 25 pending, all 80 code WOs blocked.

## Checkpoint #274 merged/read back; research issue #272 closed (factual)
- [PR #274](https://github.com/KayzenRoot/stormline/pull/274) BASE `692fdf625102c4f82f451c78683dddca6d1882b2`, final HEAD `4c72c1cf1ae3786a4d4710b6c21e779db737d6e7`, five-file checkpoint; [Docs Validation #43736759456](https://github.com/KayzenRoot/stormline/actions/runs/43736759456) SUCCESS job #132880961290; [pt-BR audit #6897793811](https://github.com/KayzenRoot/stormline/pull/274#issuecomment-6897793811) APPROVED documentary only; ordinary squash/main readback `b9e8221effd18e8e82285dc044d9271d8e551b0a), actual registry 55/80 researched, 25 pending, 80 code WOs blocked; [readback #6897798423](https://github.com/KayzenRoot/stormline/pull/274#issuecomment-6897798423). Research #272 CLOSED; code #73 OPEN/BLOCKED.
- ADR-0058 PROPOSED, NLE-D009 OPEN, 128 E06 FUTURE/NOT EXECUTED, zero sequencer/VFX/DSP/audio/animation runtime, preview/export or parity tests. All code WOs remain blocked. Historical closeout PR changes only four Markdown and has own CI/audit/squash/readback.
