# Evidence Bundle — NLE-P00-WO-002-PLAT-03 Browser Runtime P00 Research

**2026-11-15 | P00 DOCUMENTARY RESEARCH ONLY / NO ENGINE | research [#325](https://github.com/KayzenRoot/stormline/issues/325) | NLE-P00-WO-002-PLAT-03 | future implementation [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED | BASE `dc7404722c347419197d001a7d61de3d676264b0`.** Order 68/80; **formal deps TWO-01 + GFX-01 + DATA-05 ONLY** (ADR-0022/0014/0013 PROPOSED), 67/80 documented before research, 13 pending, 80/80 future coding WOs BLOCKED, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine=false, NLE-D009 license OPEN.


## 1. Observed SOURCE CHECK before documentation writes
- Main HEAD exactly requested `dc7404722c347419197d001a7d61de3d676264b0`; latest previous PLAT-02 historical closeout; no open PRs. Catalog PLAT-03 68/80, formal deps **TWO-01 + GFX-01 + DATA-05 ONLY**, all three predecessor research ADR-0022/0014/0013 PROPOSED and never engine-code authorization.
- Registry 80, 67 research documented, 13 pending including PLAT-03, all 80 BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, ready=0, approved_adr=0, release classes all UNDECIDED, engine=false. Future code [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED, research [#325](https://github.com/KayzenRoot/stormline/issues/325) OPEN until checkpoint.
- NLE-D009 engine source license OPEN, NLE-D013 no public MVP; actual source hierarchy and relevant Git blob SHA-1 OIDs (not raw SHA-256) in [Work Order](../work-orders/NLE-P00-WO-002-PLAT-03.md). Critical drift => STALE/recheck.

## 2. External primary research, and limits
- [W3C WebGPU](https://www.w3.org/TR/webgpu/) and [MDN WebGPU](https://developer.mozilla.org/en-US/docs/Web/API/WebGPU_API): HTTPS secure context, actual adapter/device/probe, not universal browser support; [device lost](https://developer.mozilla.org/en-US/docs/Web/API/GPUDevice/lost) needs generational re-create.
- [MDN WebGL2](https://developer.mozilla.org/en-US/docs/Web/API/WebGL2RenderingContext) and [WEBGL_lose_context](https://developer.mozilla.org/en-US/docs/Web/API/WEBGL_lose_context): reduced GPU fallback with real context loss, no native/WebGPU feature equivalence.
- [MDN instantiateStreaming](https://developer.mozilla.org/en-US/docs/WebAssembly/Reference/JavaScript_interface/instantiateStreaming_static): `application/wasm`, CSP; [Wasm memory](https://developer.mozilla.org/en-US/docs/WebAssembly/Reference/JavaScript_interface/Memory/Memory) max address vs actual device budget.
- [Emscripten pthread](https://emscripten.org/docs/porting/pthreads.html), [COOP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Cross-Origin-Opener-Policy), [COEP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Cross-Origin-Embedder-Policy), [crossOriginIsolated](https://developer.mozilla.org/en-US/docs/Web/API/Window/crossOriginIsolated) and [Permissions Policy](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Permissions-Policy/cross-origin-isolated): separate threaded/unthreaded artifacts, real origin headers, Workers/ads/popup compatibility gates.
- [Storage quota eviction](https://developer.mozilla.org/en-US/docs/Web/API/Storage_API/Storage_quotas_and_eviction_criteria), [CacheStorage](https://developer.mozilla.org/en-US/docs/Web/API/CacheStorage), [HTTP Range](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/Range_requests): no persistent offline or guaranteed Range, staging and last-good are necessary.
- All exact SDK versions, source licenses, browser support and hardware capability profiles UNPINNED; documented candidates are NOT adoption, certification or code.

## 3. EXACT eight new Markdown research docs
1. [Architecture](../architecture/plat-03-browser-runtime.md).
2. [ADR-0071 PROPOSED](../adr/0071-plat-03-browser-runtime-capability-policy.md).
3. [Technology/license/security matrix](../research/plat-03-browser-technology-license-security-matrix.md).
4. [Typed semantic browser API](../contracts/plat-03-browser-target-api.md).
5. [128 P03 FUTURE tests](../testing/plat-03-acceptance-matrix.md).
6. [Browser hardware benchmark](../research/plat-03-browser-benchmark-protocol.md).
7. [Work Order](../work-orders/NLE-P00-WO-002-PLAT-03.md).
8. This Evidence Bundle.

Only these eight NEW Markdown in research PR. No engine code, actual web page, hosting, CI files, registry, checkpoint, backlog, old ADR or future code status mutated.

## 4. Truthful evidence matrix
| Claim | Research evidence | NOT demonstrated |
|---|---|---|
| 8 docs and unchanged implementation | pending GitHub PR tree/diff readback | no Emscripten compiler or Wasm binary |
| 128 future P03 test cases | unique P03-T001..T128 table, FUTURE/NOT EXECUTED | no automated native/real browser test passed |
| Capability and graphics policy | upstream specs, owner contracts | no WebGPU device/real WebGL2 3D scene |
| Security/permissions | modeled CSP/COOP/COEP/XSS/asset integrity | no actual deployed origin headers, penetration or auth controls |
| Streaming and offline design | DATA-05 manifold and browser API research | no HTTP CDN, ServiceWorker cache, IndexedDB or actual offline fallback |
| Performance/size | future benchmark protocol | no measured FPS/p95/bytes/memory or native-vs-browser parity |
| Legal | license risks and notice requirements | NLE-D009 OPEN, no SPDX/SBOM audit or redistribution clearance |

## 5. Initial PR/CI/audit/merge pending until observed
- Research branch: `docs/NLE-P00-WO-002-PLAT-03-browser-research`; base `dc7404722c347419197d001a7d61de3d676264b0`. Research PR/head, CI run/job, independent pt-BR audit, squash SHA and postmerge main readback **PENDING**. No synthetic CI claim; update via later separately reviewed checkpoint/closeout.
- P00 documentary risk LOW. Runtime XSS, untrusted Wasm, content cache poisoning, permission/IO and supply-chain risk ELEVATED/HIGH_ASSURANCE; prevent file/system scope escalation. No live host, native software or privileged actions created.
- Rollback normal audited docs revert, no code/data conversion or irreversible deployment.

## 6. Independent checkpoint delta PROPOSAL ONLY
After actual Docs Validation SUCCESS on research exact head, audited pt-BR APPROVED and normal squash/main readback, prepare separate **five-file checkpoint** docs/11-checkpoint.md, docs/08-backlog.md, docs/queue/implementation-registry.json, this Work Order and this Evidence. Only PLAT-03 research_status `RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, no other module changes. Target **68/80 researched (85%), 12 pending, all 80 code WOs BLOCKED, ready=0, approved_adr=0, releases all UNDECIDED, engine=false**. ADR-0071 remains PROPOSED and all 128 P03 future tests NOT EXECUTED. Checkpoint own CI/pt-BR audit/squash/readback and then close research #325. Keep code #86 OPEN/BLOCKED. Separate **four-Markdown historical closeout** with own CI/audit/squash/main readback. Next REAL catalog **PLAT-06 macOS Desktop Target** (69/80), deps CORE-01+GFX-01+GAME-01.


## Research #326 proof; independent checkpoint PENDING
- [Research PR #326](https://github.com/KayzenRoot/stormline/pull/326): base `dc7404722c347419197d001a7d61de3d676264b0`, head `6cf03349299fcfd4b6ad6bc1c2622f5df4a47ff0`, exactly eight new Markdown; [Docs Validation run #43788703912](https://github.com/KayzenRoot/stormline/actions/runs/43788703912) **SUCCESS** job #133042024891 (Source Pack/links, DAG, registry+blocked selector); [pt-BR objective audit #6905127909](https://github.com/KayzenRoot/stormline/pull/326#issuecomment-6905127909) **APPROVED documentary**; normal squash/main readback `4cf8047998e90f2d31848585acc496f021b1e037`, ADR-0071 PROPOSED present.
- Independent checkpoint **SOLE registry semantic mutation** PLAT-03 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; other 79 module entries and all flags unmodified. Target **68/80 researches documented (85%), 12 pending, all 80 code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, executor_ready=0, approved_adr=0, release classes all UNDECIDED, engine_implemented=false**. ADR-0071 PROPOSED, NLE-D009 engine license OPEN, exactly 128 P03 tests FUTURE/NOT EXECUTED, no Wasm/browser code/real browser/graphics/benchmarks.
- [Research issue #325](https://github.com/KayzenRoot/stormline/issues/325) OPEN until independent checkpoint CI/pt-BR audit/squash/main readback; future code [#86](https://github.com/KayzenRoot/stormline/issues/86) OPEN/BLOCKED. After proof, close #325 and file separate FOUR Markdown historical closeout (own CI/audit/squash/readback) before PLAT-06 macOS target (69/80; CORE-01+GFX-01+GAME-01).
- Docs Validation proves documentation only, not actual browser support. Checkpoint must undergo own CI/audit/squash/readback before issue close. License/versions/SBOM not approved, 128 tests FUTURE/NOT EXECUTED.
