# ADR-0081 — Engine-Owned Semantic SDK with Capability-Gated Plugins and Explicit ABI

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT IMPLEMENTED. 2026-11-16.** NLE-P00-WO-002-BIZ-02, issue [#366](https://github.com/KayzenRoot/stormline/issues/366), catalog ordinal 78/80, base `0ee74d476b7c5ff09744b323cfde7423c06673b2`. Sole formal dependencies **GAME-02 + AI-01** and prior ADR-0043/ADR-0060 both PROPOSED. NLE-D009 engine license OPEN, 80/80 implementation WOs blocked.

## Context
Public SDKs must expose useful extension points without coupling game authors to internal C++ layout or offering a second security/transaction authority. Native library ABIs are target/compiler dependent; unsigned in-process plugin has process privileges. Web/WASI targets do not natively load system DLLs, and WASI host support differs by version and runtime. Future licensing of SDK, plugin samples, redistributables, and underlying engine runtime is legally undecided.

## Proposed policy (not a binding technology adoption)
1. **Source of truth is a versioned Stormline semantic API** with stable IDs, typed arguments/results/error codes, ownership and capability labels, feature detection, operation phases and explicit deprecation. GAME-02 is scripting host owner, AI-01 is authoring command router owner; SDK exposes adapters, never forks internal authority.
2. **Exactly two formal dependencies GAME-02 + AI-01**, consistent with catalog; PLAT, QA, DATA, WORLD, BIZ-01, AI-03/04/06 and CORE are integrations/transitive cross-checks, not newly added DAG predecessors.
3. **Native C ABI candidate** for explicitly trusted plugin boundary: one exported query entrypoint and version-negotiated function table, fixed-width types, `struct_size`, opaque handles, length-bounded buffers and explicit error/allocator model; no STL, C++ exception, VM pointer or C++ class cross library boundary. Public C++ convenience wrappers may be built *on top*, with source/ABI compatibility separately tracked.
4. **Native in-process is privileged.** Code signatures and hashes establish provenance/integrity, not sandbox confinement. Any community/untrusted plugin must be disabled unless approved separate-process containment or Wasm Component guest with tested restrictive imports and host quotas exists. OS dynamic loader and shared-library lifecycle hazards require real tests.
5. **WASM Component Model/WIT candidate** for language-neutral capability-oriented guest contracts; compare WASI 0.2 compatibility baseline with 0.3 async and host/browser tooling, use explicit imports only, no ambient network/filesystem/clock/process. WASI 0.3 support in runtime does not prove availability in browser JS/compilers or compatibility with current GAME-02 script VM.
6. **Plugin manifest is declarative, zero code execution at discovery.** Include digest, signature/trust, exact engine/API/ABI/schema range, target matrix, imports, data access, extension points, optional dependencies, SPDX and notices. Capabilities require separate owner-granted tokens bound to project/actor/role/target/expiry, checked at each privileged host operation; deny unknown and revoked grants.
7. **Lifecycle atomic/quiescent:** validate and stage before activation; separate capability/rights checks, resource budget and target features; on fault quarantine and preserve project state. Hot upgrade migrates state with versioned plan at safe owner fence; unsafe native unload is delayed until process restart; no marketing claim of seamless reload before proof.
8. **Compatibility discipline:** declare semantic SemVer 2.0.0 as proposed scheme (major breaking, minor additive, patch fix), separate ABI major, wire schema revision/feature flags and target OS/arch/compiler triple. Pre-1.0 API unstable, do not promise LTS; once 1.0 approved require explicitly defined migration/grace period and compatible test matrix.
9. **Developer contract:** versioned machine-readable schema drives reference/docs/binding templates, original rights-cleared examples, CMake relocatable config and offline smoke tests; CLI/Editor/MCP parity verified through same AI-01 command invocation, not public source rewrite or vendor-specific codegen. Generated bindings must preserve ownership and typed error mapping.
10. **Performance and safety evidence:** compare native vs Wasm IPC overhead, target determinism where applicable, p50/p95/p99, memory and binary sizes, startup, quotas, hot-reload rollback, malformed input/manifest fuzzer with real targets and hardware tier; no invented passing benchmark or CI coverage.
11. **Legal gate:** BIZ-01 source NLE-D009 remains OPEN, no chosen SPDX grant for engine, SDK, samples or plugin ABI. Preserve creator-authored games/assets and third-party redistributable rights, including tooling dependencies. No automatic permission to sublicense or distribute an engine binary.
12. **P00 scope:** eight new Markdown, 128 future B02 tests, no implementation, no build/SDK/published package, no running plugin sandbox, no license approval, no added required reviewers/paid tools, 80 coding WOs remain BLOCKED. Research approval != ADR ratification.

## Options and rejection
| Candidate | Benefit | Trade-off / current verdict |
|---|---|---|
| C++ ABI exposing templates/STL/vtables | ergonomics and zero wrappers | **Rejected** cross-toolchain/CRT/stdlib fragility and privilege surface |
| C ABI table + semantic schema | narrow ABI, binding friendly | **PROPOSED**; still OS/arch/calling-convention/packing compatibility and no isolation |
| Lua/Luau VM as external SDK plugin ABI | reuse GAME-02 | script-only host adapter candidate, no access to native plugin/raw VM |
| WASI WIT component host | multi-language guest isolation and structured imports | **R&D** until runtime/performance/browser and host-import security are verified |
| Out-of-process IPC | isolation from native crash/capability | **R&D** for untrusted plugins; OS sandbox and resource quotas complexity |
| Direct JS plugins for Web | browser-native author experience | **R&D** restricted to browser capabilities; CSP/worker isolations and binding controls needed |
| Trusted native everything | high speed | **Rejected** for untrusted supply chain; provenance alone no sandbox |
| Mandatory Wasmtime+Luau+native from day 1 | broad coverage | **Rejected** as premature complexity before one proven slice |

## Decision gates and hazards
Approval requires exact ABI header spec, struct layouts, packed/aligned tests, owned lifetimes, compiler/version/CRT matrix, host API schema freeze, trust domains and OS sandbox privileges, WASI version/toolchain, URL fetching policy, original samples provenance, target support, SemVer support policy, complete formal rights and privacy conditions, risk/benchmarks and measurable DoD, real QA-05 target qualification. P00 does not instantiate any of these.

Canonical sources: [GAME-02 ADR](0043-game-02-engine-owned-capability-script-host.md), [AI-01 ADR](0060-ai-01-shared-semantic-command-kernel.md), [BIZ-01 ADR](0080-biz-01-rights-compliance-policy.md), [technical matrix](../research/biz-02-sdk-plugin-technology-security-license-matrix.md), [semantic API](../contracts/biz-02-sdk-plugin-api.md).
