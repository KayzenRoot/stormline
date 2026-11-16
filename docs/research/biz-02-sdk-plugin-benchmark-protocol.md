# BIZ-02 — Future SDK/Plugin Stability, ABI Compatibility, Sandbox and Developer Experience Benchmark Protocol

**FUTURE/NOT EXECUTED · no builds, SDK, plugin binaries or sample tests.** NLE-P00-WO-002-BIZ-02, issue #366, source `0ee74d476b7c5ff09744b323cfde7423c06673b2`. All 128 `B02-T001..B02-T128` are future oracles. Formal predecessors GAME-02 + AI-01 only, both ADRs PROPOSED. License OPEN, all code WOs blocked.

## Future benchmark questions and comparisons
| Experiment | Comparable A/B candidates | Required fixture / metrics / hazard |
|---|---|---|
| SDK semantic call overhead | canonical AI-01 owner direct vs generated C wrapper vs Editor/CLI shim | authenticated synthetic project, same command and semantic digest, p50/p95/p99 ns/us, allocations, variance, no mutating privilege bypass |
| Native plugin cold boot | C table plugin with no external deps vs isolated worker | real Windows/Linux/macOS clean host, manifest verify time, dylib load/init (DllMain restriction), memory, crashes, ASLR, signer/digest |
| WASM component import | Wasmtime guest WASI 0.2 vs 0.3 optional or WAMR comparator | pinned runtime, WIT interface, support matrix, cold compile, AOT/JIT status, hostcall latency, memory peak, fuel/epoch stop |
| Browser plugin | original JS worker/ESM vs optional WASM component | real browser/OS, CSP, secure context, feature probe, startup, memory quota, duration, no native binary loading |
| Gameplay tick cost | baseline GAME-02 script API vs extension adapter | deterministic synthetic 2D/3D scene, budget per tick, command receipt parity, p50/p95/p99 and script GC pauses |
| Hot upgrade | same minor version upgrade vs incompatible major migration vs fault | known-good project, staged schema/CAS + hash snapshot, crash injection and rollback semantic readback, time until safe recovery |
| Package build | CMake config install from non-default prefix vs relocatable copy vs offline consumer install | clean compiler image, bytes produced, rebuild hash/variance, link compatibility, no network or hidden absolute path |
| Developer onboarding | original HelloWorld quickstart cold setup with docs | steps to first successful build/error, error clarity, localization/a11y and no paid accounts; not claim real usability until measured |
| Permission overhead | deny-by-default vs grant check + revoke on host operations | synthetic actors/project, unauthorized operations zero accepted, per-call overhead, rights leak and leak-proof logs |
| License/dependency distribution | exact SDK/plugin package vs export game distribution manifest | SPDX/NOTICE/source offer legal gate (BIZ-01), license OPEN blocks public release, no fake compliance certificate |

## Experimental methodology
1. Pre-register exact workload, target, OS CPU/GPU where relevant, architecture, physical vs emulated flag, compiler/linker and runtime versions, WASI WIT baseline, plugin binary schema/manifest hash and sample provenance. Code and actual artifact must exist before tests.
2. Collect cold and warmed samples with separate compiler/JIT and cache state; use independent repetitions, report distributions (median/p95/p99, confidence/variance) and resource peak, do not hide outliers/failed activations. Numeric performance threshold is **TBD BY OWNER WITH BASELINE**; do not invent 60 FPS/cold boot times in research.
3. Test adversarial manifests, version conflicts, ABI mismatch, missing linker symbols, malformed UTF-8, overflow, allocator mismatch, invalid instance handle, unload under load, revoked grants, out-of-process crash and WASM imported host-call vulnerabilities. Mark fault simulated vs real.
4. Cross-target controls: Windows x64/MSVC toolchain and optional ARM, Linux glibc ABI + Wayland/X11 stack, native macOS Apple arm64 plus conditional Intel, Web Chromium/Firefox/Safari when supported. Actual Mac and physical GPU/hardware fleet may not be available under R$0; **NOT_QUALIFIED** on unsupported hosts.
5. Permission and capability checks integrated with GAME-02 and AI-01, no separate superuser. Each output has exact host/grant/project/error/semantic receipt; compare Editor/CLI/MCP semantics only after those adapters exist.
6. Check package is signed/notarized only when actual owner-approved signing account/artifact is available, do not claim signed package from manifest field. No sample/marketplace release with NLE-D009 OPEN.
7. Regression/rollback: run N-1 client against current host for approved support windows, verify no accidental ABI break in compatible semver, known-good migration rollback, zero private project data in logs, versioned docs and third-party notices.
8. No paid third-party CI or mandatory code reviewer. GitHub docs workflow today validates only Source Pack links, catalog DAG and blocked WO registry. Future public runner compute may be free, artifact storage and privileged Apple signing/cross-platform device labs are separate cost gates.

## Stop conditions / Evidence Bundle
No owner-approved ABI/schema/release class or actual plugin ABI/toolchain, missing source rights, failed mandatory test, unsupported target/OS, sandbox escape, private-data leakage, HIGH/CRITICAL vulnerability, or unapproved fees => BLOCKED. Artifacts must include base/head SHA, exact build commands, tests/runs, device versions, fixture hash, license notices, comparison statistics, sanitizer/fuzz logs, release rollback, reviewer and approval. Current performance, security and compatibility claims are **not measured**.

[Full 128 future test matrix](../testing/biz-02-acceptance-matrix.md) · [technical matrix](../research/biz-02-sdk-plugin-technology-security-license-matrix.md) · [semantic API](../contracts/biz-02-sdk-plugin-api.md).
