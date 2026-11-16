# Evidence Bundle — NLE-P00-WO-002-BIZ-02 SDK, Plugins & Developer Experience (P00)

**2026-11-16 | RESEARCH ONLY | BASE `0ee74d476b7c5ff09744b323cfde7423c06673b2` | research #366 | future coding #96 OPEN/BLOCKED | formal GAME-02 + AI-01 ONLY.** ADR-0081 PROPOSED, NLE-D009 license OPEN, no actual SDK binaries or plugin execution. This Evidence file starts with **PENDING** for PR-specific GitHub CI/audit/squash until tool-observed proof; never fabricate.

## 1. Source Check observed
- GitHub `KayzenRoot/stormline` public main **exact** `0ee74d476b7c5ff09744b323cfde7423c06673b2` (verified), no open PR at start, protected=false observed; existing docs-only CI; no engine C++ implementation, plugin headers, SDK package, sample build, host VM or user releases.
- Canonical source hierarchy/ledger: source license NLE-D009 **OPEN**, trademark NLE-D010 OPEN, owner no public MVP, Windows/Linux/macOS native desktop and Web targeted; ADRs GAME-02 0043 / AI-01 0060 **PROPOSED**; BIZ-01 0080 **PROPOSED**.
- Registry `docs/queue/implementation-registry.json`: exactly 80 modules, BIZ-02 78/80 `research_status=RESEARCH_PENDING`, prior 77/80 research documented, 3 pending, **80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, 0 ready, 0 approved ADR, all releases UNDECIDED, engine false. Coding issue #96 OPEN/BLOCKED. Formal DAG **GAME-02 + AI-01 ONLY**, no extra deps added.
- Git blob SHA-1 identities recorded in [Work Order](../work-orders/NLE-P00-WO-002-BIZ-02.md); these are NOT raw byte SHA-256. Future coding executor must recalculate actual SHA-256 and STOP STALE.

## 2. Official technical and licensing research references
- [Microsoft MSVC 2015-2026 binary compatibility with constraints](https://learn.microsoft.com/en-us/cpp/porting/binary-compat-2015-2017?view=msvc-170); [DLL/DllMain loading rules](https://learn.microsoft.com/en-us/windows/desktop/dlls/dynamic-link-library-best-practices).
- [CMake importing/exporting Config package](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html), [Semantic Versioning specification](https://semver.org/spec/v2.0.0.html) (public API declaration).
- [WASI official releases](https://wasi.dev/releases): 0.3 current with async since June 2026; [WASI Component Model feature adoptions](https://github.com/WebAssembly/WASI/blob/main/docs/ComponentModelFeatures.md); [FAQ](https://component-model.bytecodealliance.org/reference/faq.html).
- [Wasmtime Component Model documentation](https://component-model.bytecodealliance.org/running-components/wasmtime.html) for WASI 0.2/0.3 support; [upstream Wasmtime LICENSE](https://github.com/bytecodealliance/wasmtime/blob/main/LICENSE) with Apache-2.0 LLVM exception text, exact future tag/transitive file-level audit remains required.
- [SPDX](https://spdx.org/licenses/), [REUSE](https://reuse.software/spec-3.3/), [ORT](https://github.com/oss-review-toolkit/ort) only proposals for future licensing audits; no scan performed and engine rights undecided. BIZ-01 approved **research**, not commercial license.

## 3. Exactly EIGHT NEW Markdown (research)
1. [Architecture](../architecture/biz-02-sdk-plugin-developer-experience.md)
2. [ADR-0081 PROPOSED](../adr/0081-biz-02-sdk-plugin-abi-policy.md)
3. [Technical/security/license matrix](../research/biz-02-sdk-plugin-technology-security-license-matrix.md)
4. [SDK/plugin semantic evidence API](../contracts/biz-02-sdk-plugin-api.md)
5. [128 FUTURE tests B02-T001..T128](../testing/biz-02-acceptance-matrix.md)
6. [Future benchmark protocol](../research/biz-02-sdk-plugin-benchmark-protocol.md)
7. [Research Work Order](../work-orders/NLE-P00-WO-002-BIZ-02.md)
8. This Evidence Bundle.

## 4. Future not implemented / not executed
| Research proposed | Actual evidence absent |
|---|---|
| Public semantic SDK and ABI table | no C/CPP headers, DLL/so/dylib or client compiled |
| Host language bindings and original Hello World | no codegen, sample code, package or output artifacts |
| WASI 0.2/0.3 guest and browser ESM | no Wasmtime instance, runtime installed or Web browser tests |
| Native trusted plugin lifecycle, safe unload | no dynamic library, app signing or quiescence proof |
| Sandbox OS/process isolation and capabilities | no real OS confinement/penetration test, only threat model |
| Semantic Editor/CLI/future MCP parity | no command implementation or source state to compare |
| Windows/Linux/macOS/Web target matrix | no real cross-target ABI/SDK consumer build or physical hardware test |
| 128 future B02-T001..B02-T128 cases | FUTURE/NOT EXECUTED, ZERO PASS, all hypothetical |
| License and commercial distribution rights | engine source NLE-D009 OPEN, no SDK/export grant or notices from package |
| CI exact PR head and objective audit | PENDING until observed; docs-only CI cannot prove product |

## 5. Research integration pending actual observation
- Prepared branch `docs/NLE-P00-WO-002-BIZ-02-research`, source `0ee74d476b7c5ff09744b323cfde7423c06673b2`. PR number, HEAD, diff exactly eight ADDED .md, CI run/job SUCCESS, pt-BR audit, squash/main readback must be appended only after real events.
- No license decision, release, public SDK, package publication, expense, private data upload or implementation issue activation. Research P00 risk LOW; future native plugin untrusted isolation and public source rights are HIGH_ASSURANCE.

## 6. Proposed independent checkpoint / historical closeout
- Once research PR merged/read back, **independent** checkpoint five modified files: checkpoint, backlog, registry, blocked BIZ-02 code WO, this Evidence. **Sole semantic registry delta** BIZ-02 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`, other 79 full module objects and all root keys intact. Target 78/80 (97.5%), 2 pending, 80/80 coding BLOCKED, 0 executor_ready/approved ADR, license OPEN.
- Research issue #366 CLOSE only after checkpoint CI/audit/squash/main readback; coding issue #96 remains OPEN/BLOCKED. Then independent historical closeout **four Markdown only** checkpoint/backlog/BIZ-02 WO/Evidence, own CI/audit/squash/main readback before next real catalog module.
- Next actual catalog module after BIZ-02 is **BIZ-03 Release, Installer & Lifecycle**, ordinal 79/80, formal PLAT-05 + BIZ-01 + QA-04 (verify from catalog), future code #97 BLOCKED. No increment automatically authorized.
