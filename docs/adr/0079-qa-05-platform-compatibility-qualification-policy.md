# ADR-0079 — Evidence-Gated Platform Compatibility, Recovery and Release Qualification

**2026-11-16 | P00 DOCUMENTARY RESEARCH ONLY | [research #357](https://github.com/KayzenRoot/stormline/issues/357) | NLE-P00-WO-002-QA-05 | future coding [#94](https://github.com/KayzenRoot/stormline/issues/94) OPEN/BLOCKED | source main `a42519c8a79346a4974fa74c44f7cac26f4ad43c`.** Module QA-05 ordinal 76/80; **FORMAL dependencies exactly QA-02 + PLAT-05**, prior ADR-0076 and ADR-0074 PROPOSED. Initial registry 75/80 researched, 5 pending, 80/80 future code WOs BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS, 0 ready/approved ADRs, release classes UNDECIDED all, engine_implemented=false, NLE-D009 engine source license OPEN, NLE-D013 no public MVP.


**STATUS: PROPOSED / NOT RATIFIED / NOT IMPLEMENTED / NO QUALIFIED HARDWARE, BUILD OR PUBLIC RELEASE.**

## Problem
An export that compiles on a cloud runner may fail on user hardware because of driver capabilities, OS/ABI/libc, GPU feature sets, browser policy, input/font/audio/display stack, packaging dependencies and migrations. A game may render once then corrupt saves during a crash or fail when updating. QA-05 needs a policy that qualifies **actual** product/platform/release cells, rather than claiming Windows/Linux/macOS/Web compatibility from a conceptual architecture, QA-02 goldens or synthetic headless simulation.

## Proposed decisions
1. **Only formal prerequisites QA-02 + PLAT-05.** QA-02 ADR-0076 controls fixtures/goldens and deterministic functional truth; PLAT-05 ADR-0074 controls build/export/release manifests, versions, signing/provenance and rollback. Both PROPOSED. QA-05 owns **compatibility and qualification evidence** and cannot take over compiler, golden approvals, installer, data schema or release publisher. GFX/CORE/GAME/DATA/QA-01/03/04/BIZ/etc are integration/transitive, not new DAG edges.
2. **Owner release matrix stays undecided.** Desktop Windows/Linux/macOS Editor and game exports are owner-directed required destination classes, but minimum supported OS/CPU/GPU/driver versions and tested tier still await approval. Web games planned; mobile optional outside mandatory 1.0 unless later explicitly ratified. Candidate Win x86_64/optional arm64, Linux distro x86_64 with ABI/Wayland/X11, macOS native Apple Silicon arm64 and conditional Intel x86_64 with macOS<=26 eligibility, browser secure-context WebGPU optional / WebGL2 only if separately approved. No implicit claim of every vendor chip/version.
3. **Feature-probe first, not brand lists.** D3D12 device feature levels/SM/adapter, Vulkan profile/required extension/surface/ICD, Metal `supportsFamily(MTLGPUFamily)`, WebGPU adapter features+limits and security/browsers all require actual runtime evidence. Device capability != shader correctness or actual robust driver, and browser privacy may bucket limits. Native Intel+AMD+NVIDIA+Apple comparison requires actual representative hardware and pinned driver OS.
4. **Physical proof is distinct from functional simulation.** Windows WARP, Vulkan SwiftShader, llvmpipe, Xvfb and hosted VM may provide valuable deterministic/software tests but **must never be counted as physical vendor GPU, display/HDR, thermal/VRR, actual driver or true latency proof**. Missing physical device => NEEDS_HOST or NOT_QUALIFIED, never PASS. Cloud providers/Apple host hardware costs not assumed R$0.
5. **Multi-layer gates:** L0 immutable original QA-02 fixture and approved expected result; L1 clean PLAT-05 native build/export manifest and architecture dependency; L2 toolchain/run-time ABI and clean OS installation; L3 actual GPU capability rendering/input/audio and accessibility; L4 sustained stability/soak and recovery with synthetic original saves; L5 update/downgrade/recovery+release artifact signatures and license/NOTICE; L6 cross-platform owner review/DoD decision. Missing required layers => BLOCKED or NOT_QUALIFIED; `Docs Validation SUCCESS` only proves documentary structure.
6. **Crash/data recovery truly transactional:** maintain known-good state before write/migration, detect save schema/hash/checkpoint, simulate fault at boundary stages and test real platform durability, fail closed on partial states, don't overwrite healthy backup; if downgrade impossible, deny downgrade explicitly and allow restore from pre-migration. OS recovery callbacks or atomic rename are not a substitute for fsync/dir sync and power-failure tests per real FS.
7. **Sustained regression and performance:** predeclared soak duration/rounds/hardware/software versions and fault injection classes (OOM, GPU device lost, storage full, network loss, idle/resume/suspend, hotplug, signal/crash, restart). Distinguish simulated fault from real GPU reset. QA-02 golden/function acceptance and integration QA-03 p95/p99 with actual data; no future 128 tests marked PASS until run. No hardware/driver support conclusions from one screenshot or FPS average.
8. **Reproducible releases not automatically safe:** PLAT-05 owns separate code signing/notarization and manifest; SHA reproducibility may require normalized timestamps/path/link order and deterministic assets, but release qualification also verifies installer, rights, runtime libraries, app permissions, upgrade slot and rollback. No certificate, Apple account, paid notarization or approved source redistribution exists currently. No public MVP until v1.0 DoD NLE-D013 and NLE-D009 license decision.
9. **Security, accessibility, privacy:** crash dump/error logs and optional telemetry redacted and consent-based, no publishing private project contents/keys to CI; test known vulnerable runtimes/permissions in isolated QA per QA-04 proposals but no claim security certification. Accessibility native screen reader requires platform hardware and separate owner; Web ARIA and screenshot are insufficient alone.
10. **R$0 and staged evidence:** standard hosted GitHub public runner compute conditional free, artifact storage/larger runners paid risk, actual physical GPUs/macOS host/browser lab possibly unavailable. Tests not possible on approved hardware -> NOT_QUALIFIED, support claim limited to verified cells. Exactly 128 Q05-T001..T128 future tests, eight Markdown, ADR-0079 PROPOSED, 80/80 coding WOs BLOCKED, no engine implementation.

## Rejected shortcuts and unresolved decisions
| Shortcut | Reason to reject / owner gate |
|---|---|
| Support Windows/Linux/macOS/Web with GitHub Docs Validation green | checks Markdown only, not native builds nor devices |
| Treat Win WARP CPU render as Intel/NVIDIA/AMD GPU proof | software driver does not exercise vendor device, display or driver |
| Assume Vulkan extension name or Metal version is enough | feature/device/presentation and shader execution must be probed |
| Use Rosetta x86-only macOS game as long-term Apple Silicon support | Apple 2026 transition and OS 27 support changes; native arm64 qualification required |
| Claim every Linux distribution supported because Ubuntu compiles | glibc/libstdc++/libdrm/Wayland/X11/driver/runtime packaging differ |
| Browser support from a single Chrome WebGPU run | Firefox/Safari/OS/secure context/device features differ |
| Ignore browser tab suspension or device loss | breaks session/recovery and corrupted storage |
| Trust atomic rename as power-cut durability | write/dir sync and real file-system behavior matter |
| “Backup exists” implies recoverable | restore checksum/independent readback must actually pass |
| Allow downgrade that truncates new save state | explicit incompatible schema gate and restore path |
| Adopt absolute min VRAM/driver/OS floor without real samples | release-class and test matrix owner UNDECIDED |
| Upload customer crash dump to public artifact | privacy/license/security breach |
| Declare signed/notarized export from config alone | requires actual builder/cert/verification and owner |
| Add paid hardware cloud or Store account without approval | R$0 constraints and owner consent |
| Automatically unblock QA-05 code after documentary PR | 80 code WOs remain BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS |

## Decision gates still pending
Owner ratifies OS minimums/CPU/GPU/driver tiers, Web fallback and conditional Intel support, hardware fleet+access, release classes, target C++ ABI and native packaging, legal licenses, actual test duration/stability and recovery thresholds, original test fixture rights, QA-02 golden approval, PLAT-05 toolchain/signature metadata and rollback policy, required no-HIGH/CRITICAL security and all release DoD. In P00 there are no actual qualification measurements or software artifacts.

[Architecture](../architecture/qa-05-compatibility-release-qualification.md) · [technology and license matrix](../research/qa-05-platform-hardware-tool-license-cost-matrix.md) · [semantic API](../contracts/qa-05-qualification-evidence-api.md).
