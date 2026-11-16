# NLE-P00-WO-002-BIZ-02 — SDK, Plugins & Developer Experience: Research Work Order

**2026-11-16 | P00 DOCUMENTARY ONLY | [research #366](https://github.com/KayzenRoot/stormline/issues/366) OPEN until checkpoint verified | future coding [#96](https://github.com/KayzenRoot/stormline/issues/96) OPEN/BLOCKED.** Base main `0ee74d476b7c5ff09744b323cfde7423c06673b2`, ordinal 78/80, **FORMAL DEPENDENCIES GAME-02 + AI-01 ONLY** (ADR-0043, ADR-0060 PROPOSED). Baseline 77/80 research documented / 3 pending; 80/80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, executor_ready=0, approved_adr=0, release classes UNDECIDED, engine_implemented=false, NLE-D009 engine source license OPEN, no public MVP.

## OBJECTIVE
Investigate and specify a secure portable public SDK and plugins ecosystem: semantic versioned APIs, stable IDs, C native ABI/function-table candidate, language FFI/WIT bindings, trusted vs sandboxed extension modes, plugin package/manifest/permissions/lifecycle, gameplay and authoring command parity across Editor/CLI/MCP, documentation and original examples, clean CMake packages, Windows/Linux/macOS/Web portability and support matrix, SemVer/deprecation/migration, performance, crash/hot reload, privacy/licensing/third-party notices, R$0 CI and owner release gates. **No code execution.**

## CONTEXT / SOURCE CHECK
Canonical precedence: checkpoint, Decisions Ledger/approved ADR, Scope, DoD, Architecture, Requirements, other. GitHub `main` exact `0ee74d476b7c5ff09744b323cfde7423c06673b2`, public repo, zero open PR at starting check; P00 docs only, README LICENSE PENDING, no SDK or executable engine. Module catalog BIZ-02 78/80, sole formal `GAME-02 + AI-01`; predecessor GAME-02 ADR-0043 and AI-01 ADR-0060 both **PROPOSED / NOT IMPLEMENTED**. BIZ-01 ADR-0080 PROPOSED; license NLE-D009 OPEN, trademark NLE-D010 OPEN. Owner requires native Windows/Linux/macOS Editor and exported games; Web targeted, mobile optional. BIZ-03 and QA-05 are future integrations, NOT formal prerequisites for research. Future code issue #96 remains BLOCKED.

## CONTEXT LOCK
Source commit `0ee74d476b7c5ff09744b323cfde7423c06673b2`, source critical **Git blob SHA-1 object IDs, NOT raw byte SHA256**; implementation executor must compute actual SHA-256 raw content and invalidate STALE on changes:
- `docs/11-checkpoint.md` blob `ce2ecca98d476be383db3ceb8fe4286d80e6a8c0`
- `docs/10-decisions-ledger.md` blob `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md` blob `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md` blob `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md` blob `df62574cb3956c3ac9881631a4cf66be4e1abff1`
- `docs/02-requirements.md` blob `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`
- `docs/product/module-catalog.md` blob `18d69bca439831d65982cb0f8acbca1dbaa2eee9`
- `docs/queue/implementation-registry.json` blob `227ab37577c8944ea2f9ce3b338197bf34cf52a6`
- `docs/queue/work-orders/BIZ-02.md` blob `ee5f5dcf00435918c8136e89bdf8871aa0ff123e`
- `docs/adr/0043-game-02-engine-owned-capability-script-host.md` blob `8e5750b1ff608fcdf66980206d011d93ffd1efce`
- `docs/adr/0060-ai-01-shared-semantic-command-kernel.md` blob `bf0b04c0e0539f081c3f4804daf0b5645db7bc57`
- `docs/contracts/game-02-gameplay-scripting-api.md` blob `3dd5ad89e25e7fd39779eded236f26ab2d4a282b`
- `docs/contracts/ai-01-command-kernel-api.md` blob `ca0803152773395ac8f2868126d8cf2446fa4062`
- `AGENTS.md` blob `3e57b719f8651407879ebb641707a048773ea4c2`
- `.github/workflows/docs.yml` blob `cbbaf5731de75f1de4bdf8cad6489e6d73681d71`
All above are observed at specified base; if these or any approved critical decision change, STOP STALE and reconstruct context.

## SCOPE — NECESSARY P00: EXACTLY EIGHT **NEW** Markdown
1. [Architecture](../architecture/biz-02-sdk-plugin-developer-experience.md)
2. [ADR-0081 PROPOSED](../adr/0081-biz-02-sdk-plugin-abi-policy.md)
3. [2026 technology, security, license and OS matrix](../research/biz-02-sdk-plugin-technology-security-license-matrix.md)
4. [Typed SDK/plugin semantic evidence API](../contracts/biz-02-sdk-plugin-api.md)
5. [Exactly 128 unique B02-T001..B02-T128 FUTURE tests](../testing/biz-02-acceptance-matrix.md)
6. [Future benchmark and ABI compatibility protocol](../research/biz-02-sdk-plugin-benchmark-protocol.md)
7. This research Work Order
8. [Evidence Bundle](../evidence/NLE-P00-WO-002-BIZ-02.md)

Research PR modifies **only eight ADDED markdown**, no existing Source Pack, registry, backlog, checkpoint, code, CI, license or binary. After research CI + objective audit + squash/readback, separate independent checkpoint PR five MODIFIED (checkpoint/backlog/registry/BIZ-02 code WO/Evidence) with only BIZ-02 registry `research_status` change; then issue closure and four-Markdown historical PR with distinct CI/audit/merge/readback.

## OUT OF SCOPE
No actual C++ headers, compile, SDK install, plugin registry, shared libraries, WASI runtime adoption, VMs, browser JS modules, sample source output/asset published, real tests/benchmarks, CMake package/install, code signing/notarization, paid macOS/GPU runner, GitHub rule change, public alpha/MVP, SDK or engine license/EULA/royalties, private user data or customer content uploads, dependency downloads, backend releases, CodeRabbit, reviewer procurement, cleanup/refactor, future coding issue change or 80 WO activation.

## FILES / SOURCES TO READ
Canonical Context Lock sources above plus `docs/adr/0080-biz-01-rights-compliance-policy.md`, GAME-02/AI-01 contracts, blocked #96; official [MSVC ABI](https://learn.microsoft.com/en-us/cpp/porting/binary-compat-2015-2017?view=msvc-170), [DLL loading](https://learn.microsoft.com/en-us/windows/desktop/dlls/dynamic-link-library-best-practices), [CMake packages](https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html), [SemVer](https://semver.org/spec/v2.0.0.html), [WASI releases](https://wasi.dev/releases), [WASI 2026 features](https://github.com/WebAssembly/WASI/blob/main/docs/ComponentModelFeatures.md), [Component model](https://component-model.bytecodealliance.org/reference/faq.html), [Wasmtime](https://component-model.bytecodealliance.org/running-components/wasmtime.html), [upstream license](https://github.com/bytecodealliance/wasmtime/blob/main/LICENSE). Before implementing, verify exact upstream tags and licenses.

## REQUIREMENTS
Catalog acceptance: **Plugin/sample compatível com API publicada, teste de atualização**, purely future. Preserve GOV-001..005, NLE-D009 OPEN, D013 no MVP public, D014 full 2D/2.5D/3D/Web, D015 AI-native MCP gated, D017 native desktop targets, D018 solo approvals but no irreversible actions, D019/020 80 coding packets blocked. No implicit public runtime API guarantee from P00 docs.

## ARCHITECTURE RULES
GAME-02 scripting host owns `ScriptApiSchemaV1`, authorizations and tick command buffers; AI-01 owns `CommandDescriptorV1`, canonical mutation receipts/permissions for UI/CLI/future MCP. BIZ-02 only projects SDK and plugin lifecycle, explicit typed versions/ABI, no raw internal pointers or C++ STL crossing ABI. Native in-process trusted only with owner authorization, WASM/out-of-process guests deny ambient privileges, strict quotas/revocation, honest platform feature probes. Use original samples and genuine provenance; BIZ-01 governs future redistribution/legal license, but not new formal DAG edge.

## CONSTRAINTS
R$0 routine docs CI, no CodeRabbit/reviewer requirement/bypass/force push/paid tools or legal publication. No benchmark/future tests marked PASS. Documentation LOW risk; unknown native/WASM code and privilege isolation ELEVATED, untrusted native extension/rights/payment/exfiltration HIGH_ASSURANCE. Preserve 80 blocked.

## ACCEPTANCE CRITERIA
- [ ] Exactly eight new Markdown, ADR-0081 PROPOSED, formal GAME-02 + AI-01 only, no source license approval.
- [ ] Exactly 128 distinct future test IDs ordered B02-T001..B02-T128 all NOT EXECUTED, zero PASS.
- [ ] C ABI/ownership, guest isolation, Web target, performance, binary/toolchain and rights/capabilities research with primary sources and typed API; no claims of proven runtime.
- [ ] PR exact-head Docs Validation passes links/catalog/DAG/80 registry/blocked selector; objective pt-BR audit no HIGH/CRITICAL known.
- [ ] Research squash/main readback, separate checkpoint (sole semantic BIZ-02 registry research_status delta, 79 module records and root identical), own CI/audit/squash/readback.
- [ ] Historical four-Markdown PR with its own CI/audit/squash/readback; research issue closed only after checkpoint; code #96 OPEN/BLOCKED.

## TESTS
Current executable P00 checks: `python3 scripts/validate_docs.py`, `python3 scripts/validate_module_catalog.py`, `python3 scripts/validate_wo_registry.py`, `python3 scripts/select_wo.py BIZ-02` (must reject coding); exact commands verified by existing `.github/workflows/docs.yml` in CI. 128 B02 acceptance tests are **FUTURE/NOT EXECUTED**; no actual C++/WASM/JS tests, compilation, lint, sanitizer, penetration, benchmark or cross-OS evaluation.

## DELIVERABLES
Eight research Markdown, ADR PROPOSED, source matrix, typed API, test plan 128 future cases, benchmark plan, WO, Evidence, GitHub issue/PR, CI trace, pt-BR audit, independent checkpoint/history readbacks. Not an executable SDK or license.

## REVIEW FORMAT
Português brasileiro; BASE/HEAD/actual file list and diff, exact CI run/job/status, 128 test count, security/ABI/rights failure modes, matrix honesty, issue code blocked, proposed checkpoint delta, verdict APPROVED/CORRECTION REQUIRED/BLOCKED.

## STOP CONDITION
STOP when base STALE, unapproved release/license/royalties, unknown OS/ABI/VM support, unsafe native plugin capability, private data leakage, paid tool request, source mismatch, failed CI, HIGH/CRITICAL, attempted plugin code/executor activation or unauthorized scope.

## CHECKPOINT DELTA PROPOSED ONLY
After observed research merge: five-file independent checkpoint changes BIZ-02 `research_status RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED` **SOLE semantic registry modification**, 79 other full module objects and root unchanged, target **78/80 researched (97.5%)**, 2 pending, **80/80 code WOs still BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**, executor_ready=false, approved_adr=null, release_class UNDECIDED, engine=false, NLE-D009 license OPEN. No self-promotion by executor.
