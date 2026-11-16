# NLE-P00-WO-002-PLAT-03 — Browser Runtime P00 Research Work Order

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


Research [#325](https://github.com/KayzenRoot/stormline/issues/325) OPEN pending independent checkpoint; future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED. Documentation risk LOW; future browser, origin security, content integrity and optional hosted deployment ELEVATED/HIGH_ASSURANCE as applicable. No shell/browser automation in this research.

## OBJECTIVE
Document source-backed Browser Runtime policy for Wasm C++20/JS host, WebGPU capability and WebGL2 real 2D/representative 3D fallback, secure-context and thread/Worker/gesture browser lifecycle, DATA-05 verified streaming/caching/offline updates, licenses/threat model, typed contracts, browser smoke and **128 future tests**. Catalog acceptance: "2D e cenário 3D browser compatíveis em browsers matriz; sem alegar 1:1 nativo."

## CONTEXT / SOURCE CHECK
Source precedence checkpoint > Decisions Ledger/ADRs > Scope > DoD > Architecture > Requirements > other. Live main matches BASE `dc7404722c347419197d001a7d61de3d676264b0`; zero open PRs. Registry 80 modules, **67 research documented and 13 pending**, PLAT-03 68/80, all 80 code WOs BLOCKED, executor_ready=0, approved_adr=0, release_class UNDECIDED, engine_implemented=false; issue #86 OPEN/BLOCKED. Owner NLE-D013 no public MVP, D014 native+Web creation, D015 authorized AI/MCP, D016 80-module inventory, D017 desktop and Web planning, D018 delegated routine research, D019-020 blocked queue, NLE-D009 engine license OPEN.

## CONTEXT LOCK
At BASE `dc7404722c347419197d001a7d61de3d676264b0`, below **Git blob SHA-1 object IDs, NOT raw byte SHA-256**. If critical docs, checkpoint, Ledger/approved ADR, Scope, DoD, Architecture, source contracts or HEAD unexpectedly shift, mark STALE and stop/rebuild; actual source SHA-256 fingerprints are a separate future code preflight. No silent rebase:
- `AGENTS.md` — `3e57b719f8651407879ebb641707a048773ea4c2`
- `docs/00-source-hierarchy.md` — `58a377bc76cafdd3377d733d4f30ef53661bb034`
- `docs/11-checkpoint.md` — `a2fa29357a2bbce7602e01343c213d079f3fa91b`
- `docs/10-decisions-ledger.md` — `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md` — `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md` — `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md` — `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` — `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md` — `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json` — `be0779268abe506f2c87e15d61da168cfa936c1c`
- `docs/queue/work-orders/PLAT-03.md` — `86f388d0618887e7425a30941d34b57c74d84cfc`
- `docs/architecture/two-01-renderer-canvas.md` — `5faa6b919d882416e8ae492631c3144fa6efe294`
- `docs/contracts/two-01-canvas-api.md` — `0dbc1312972352ded567c51c8745a22abec39eff`
- `docs/adr/0022-two-01-native-2d-renderer-policy.md` — `ada82006bf9c0ec8d1fa1b564a30db0276054bef`
- `docs/architecture/gfx-01-graphics-rhi.md` — `4512de487da7df97969b56f8e5f508a56125ab32`
- `docs/contracts/gfx-01-rhi-api.md` — `822cbd118df75b4acf033443d5f75842d1344ae7`
- `docs/adr/0014-gfx-01-rhi-backends.md` — `27b3f4533083c6b6a23a989e0eb8661898d44ade`
- `docs/architecture/data-05-cooking-streaming-bundles.md` — `0e77be93e7d0fa2404acd297b98c1ef4545cb948`
- `docs/contracts/data-05-cook-bundle-api.md` — `f78d246ac2730f503ede0a1823334a39ba4040e7`
- `docs/adr/0013-data-05-cooking-policy.md` — `ab661c5111a1d4aebf79381c0a3834e572c0c762`

## SCOPE — exactly eight NEW Markdown only (NECESSARY)
1. [Browser architecture](../architecture/plat-03-browser-runtime.md).
2. [ADR-0071 PROPOSED](../adr/0071-plat-03-browser-runtime-capability-policy.md).
3. [Technology/license/security research](../research/plat-03-browser-technology-license-security-matrix.md).
4. [Browser target semantic APIs](../contracts/plat-03-browser-target-api.md).
5. [128 future P03 tests](../testing/plat-03-acceptance-matrix.md).
6. [Browser hardware/benchmark protocol](../research/plat-03-browser-benchmark-protocol.md).
7. This research WO.
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-PLAT-03.md).

Research PR creates ONLY these eight NEW Markdown files, NO code, registry, checkpoint, backlog, CI or existing ADR modifications.

## OUT OF SCOPE
Build/execute WASM, install SDK, modify package.json/CMake/CI, run browser smoke or GPU benchmark, publish website, configure live hosting/CDN/service worker, download SDK binary, create/ship renderer, release game or editor, unfreeze source license, add unapproved libraries/terms or use paid infrastructure; changes to TWO-01/GFX-01/DATA-05 owners, coding issue #86, any of the 80 queue WOs, unapproved mobile/console/VR target, unsupported WebGPU universal claim, broad refactor.

## FILES / SOURCES TO READ
Canon order above, AGENTS, catalog, 80 implementation registry, #86, GFX-01/TWO-01/DATA-05 architecture/API/ADR. Official W3C WebGPU/WGSL, MDN secure WebGPU/WebGL2 device lost/CSP, WebAssembly memory32/memory64 and instantiateStreaming MIME, Emscripten pthread restrictions, COOP/COEP/crossOriginIsolated/Permissions Policy, Storage APIs/ServiceWorker/HTTP Range, browser user-activation rules. Exact version/license pin only at future P01 activation after owner approval.

## REQUIREMENTS
GOV-001..005; security/privacy/performance/compatibility NFRs; catalog browser acceptance and target matrix; NLE-D013..020. **Formal dependencies ONLY TWO-01 + GFX-01 + DATA-05**, all predecessor ADRs still PROPOSED, no new DAG edge. Native/Wasm semantics, resource and asset truth remain with predecessor owners.

## ARCHITECTURE RULES
- TWO-01 2D alpha/order/clip and native renderer correctness, browser host adapts presentation only.
- GFX-01 owns RHI, GPU device/context generations, WebGPU negotiation and **WebGL2 reduced 3D**. GFX-02 owns shaders; no false native GPU equivalence.
- DATA-05 immutable manifest/asset provenance/decoders/cook; PLAT bounded fetch/Range/cache/quota and reversible staged generation. Hash != signature.
- Wasm32 unthreaded baseline; browser capability-gated threaded separate artifact with effective COOP/COEP+SAB, Worker/OffscreenCanvas conditional; main-thread asynchronous host and CORE-04 sim authority.
- Browser user gestures for audio/gamepad/pointer lock/fullscreen/clipboard/files, trust-boundary CSP/HTTPS/CORS/CORP/COEP/Permissions Policy, no unrestricted MCP, private token or XSS scripts.
- Real named browser/OS/GPU compatibility matrix; no public product before full DoD; no adopted versions/tier/memory budgets without proof.

## CONSTRAINTS
P00 documentation LOW; future app origin/cached update/security high assurance as risk demands. Free public GitHub Actions documentation CI; no CodeRabbit, mandatory external reviewer, secret, shell privileges, force push, paid deployment or irreversible action. Source Lock must remain fresh before writes/merge. Third-party licenses/SBOM and rights open until pinned.

## ACCEPTANCE CRITERIA
- [ ] Exactly 8 NEW Markdown with correct links and evidence, zero code/registry/CI/checkpoint/backlog changes in research PR.
- [ ] ADR-0071 PROPOSED, formal graph TWO-01+GFX-01+DATA-05 ONLY, browser host ownership and W0/W1 conditional degradation documented.
- [ ] WASM32/worker/SAB/COOP+COEP, WebGPU/GL2, 2D+3D quality, browser GPU lifecycle, input permission and audio, manifest/content integrity, Range/CSP/CORS, ServiceWorker/multi-tab/eviction, privacy/accessibility and licenses researched with primary official sources.
- [ ] Exactly unique P03-T001..T128 (8×16) FUTURE/NOT EXECUTED with independent oracle, protocol with real browser/hardware matrix and no fake PASS.
- [ ] Source Lock, exact build/runner provenance, future security and version gates; NLE-D009 engine license remains OPEN; no code release/class approval.
- [ ] Research PR Docs Validation exact-head SUCCESS, independent objective pt-BR review APPROVED, normal squash and main readback.
- [ ] Separate five-file checkpoint PR sole PLAT-03 research_status mutation; its own CI/audit/squash/readback before research issue #325 closes.
- [ ] Four Markdown factual historical closeout PR with own CI/audit/squash/readback, then next **PLAT-06** 69/80 (CORE-01+GFX-01+GAME-01). Never unlock any 80 future code packets.

## TESTS
P00: Source Pack & links, 80-module DAG, registry and blocked selector by GitHub Docs Validation; GitHub PR file list exactly eight added; independent readback of 128 test IDs and statuses; no native browser scripts. P01 future actual Emscripten/Clang reproducible artifact, browser WPT/Playwright plus real physical Chrome/Firefox/Safari configured fixtures and security/benchmark harness. NOT EXECUTED today.

## DELIVERABLES
Eight Markdown files, source issue/PR, head/base SHA, reproducible cited source claims, CI run/job receipts, audit in pt-BR, Evidence Bundle and checkpoint delta **proposal only**. Separate checkpoint and factual history PRs later, no engine code/hosting.

## REVIEW FORMAT
Pt-BR: actual main/head SHAs, diff, code-queue invariants, 8/128 count, external primary research/rights, security/privacy CSP and loss, actual Docs Validation, defects with severity/rollback and verdict APPROVED/CORRECTION REQUIRED/BLOCKED. A documented ADR is not owner approval to code.

## STOP CONDITION
Any STALE context, owner preemption, missing rights, incorrect dependencies/8 files/128 cases, known HIGH/CRITICAL, new code/CI/registry in research PR, failed Doc Validation, unsupported performance claims, unapproved spend/public website, mismatched SHA => BLOCKED or same WO/PR CORRECTION REQUIRED.

## CHECKPOINT/EVIDENCE PROCEDURE
Research PR **must not** self-promote. Once merged+readback and objectively audited, independent 5-file checkpoint modifies checkpoint/backlog/implementation-registry/this WO/Evidence, with **only PLAT-03 research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED**. Expected post-readback 68/80 documented, 12 pending, all 80 coding WOs BLOCKED, ready=0, approved_adr=0, release_class UNDECIDED all, engine=false. Close research #325 only after this independently audited checkpoint, future code #86 stays OPEN/BLOCKED. Four-Markdown historical closeout own CI/audit/squash/readback before PLAT-06.
