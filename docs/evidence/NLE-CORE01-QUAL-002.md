# NLE-CORE01-QUAL-002 — Native ABI & Toolchain Compatibility Evidence

**Status:** PARTIAL TESTED HEAD / EXACT FINAL HEAD CI, AUDIT & MERGE PENDING.  
**Work Order:** [NLE-CORE01-QUAL-002](../work-orders/NLE-CORE01-QUAL-002.md). **PR:** [#481](https://github.com/KayzenRoot/stormline/pull/481).  
**Risk:** STANDARD, test-only, scoped to five allowed repository paths, no new toolchains or workflow modifications.  
**Source base:** `main@7da51f4a314a81959aa31cb56f5f5d06228fe4bc`.  
**Latest inspected code HEAD:** `94b59b9496e49f0a8779e6056ee666e15147142d`, with Windows/macOS/Linux ASan+UBSan pass, Linux normal in progress at last readback. This document-only commit must be re-validated by its own exact-HEAD CI.

## Source Check & Context Lock
Canonical precedence inspected before writes: checkpoint `abfdb3d0dd588829c89321b69bbc54fb0a82250e`; Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981`; Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`; DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`; Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`; Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`. All SHA strings here are Git blobs except separately labeled binary SHA256. G3-V02 detached fixture and NLE-CORE01-QUAL-001 were inspected; no duplicated vendor/toolchain experiment.

**Exact allowlist:** `tests/core/core01_abi_portability_tests.cpp` NEW, `cmake/core01_abi_probe.cmake` NEW, `CMakeLists.txt` ADDITIVE, `docs/work-orders/NLE-CORE01-QUAL-002.md` NEW, this Evidence NEW. Nothing under `src/` or existing CI, G2, ADRs, dependencies/SDKs, license, manifest, registry.

**Immutable registry/manifest:** manifest blob `dc01d3ccc62e857feeb61b3be599f66ae2c08c44` (748 packets: 19 COMPLETED, 725 PLANNED_BLOCKED, 2 APPROVED_GOVERNANCE, 2 APPROVED_CONTRACT); registry blob `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024` (80/80 WOs BLOCKED, zero EXECUTOR_READY, `engine_implemented=false`). CORE-01 internal -03..-16 COMPLETED; ADR-0003/0075 PROPOSED; NLE-D009 OPEN; G3 global NOT_CLEARED.

## Tests implemented and scope of qualification
- Test-only executable compiled as internal C++20; compile-time checks: native handle `uint64_t` value/generation, `uint8_t` enum underlying type, standard-layout/trivially-copyable transport, RAII non-copy and non-move host/runtime/window/capability objects, no-throw destruction. Runtime prints sizeof/alignof, endian, compiler and C++ stdlib macros, and rejects unissued/forged native handle without SDL video. **Sizes are observed, not frozen public ABI.**
- CMake `-P` inspects exact own executable, computes **real** SHA256, detects CMake/Ninja/compiler/arch, invokes only preinstalled `readelf`/ `dumpbin`/ `otool`/ `lipo`/ `xcrun`/ `xcodebuild`. A malformed file beside the test binary is passed to the same probe as negative oracle, must fail specifically on magic/header; file removed afterward. Native post-build prints evidence because green CTest normally hides stdout.
- ELF64 x86_64 demands observable dynamic imports, GLIBC and GLIBCXX version requirements; GNU ISA-note inspection is **optional evidence** and remains `NOT_QUALIFIED` if unavailable. This does not prove x86 CPU with no AVX.
- PE x64 demands visible CRT DLL imports and observed Windows SDK/toolset environment from preinstalled `vcvars64`. Debug CRT imports are NOT authorization to distribute/debug-CRT-only binaries.
- Mach-O arm64 demands `LC_BUILD_VERSION`, min OS/SDK recorded, dylib dependencies, host SDK and Xcode metadata. Installed host toolchain is not the owner-ratified G3 candidate unless independently matched and approved.
- Fail-closed: wrong file format, missing tools, missing mandatory header/versions/imports, malformed parser or CTest failure is not a PASS.

## Correction Delta in same Work Order / PR
**CD-01 — MSVC C++20 detection.** First CI [#44408859459](https://github.com/KayzenRoot/stormline/actions/runs/44408859459), Windows job `135171305755` failed C2338: MSVC default `__cplusplus=199711` under valid `/std:c++20` without `/Zc:__cplusplus`. Test oracle was wrong. Corrected solely test header: `_MSVC_LANG >= 202002` for MSVC, `__cplusplus >= 202002` elsewhere, print both. No compiler flag or production change. macOS passed 98/98 on first run; earlier Linux jobs cancelled by existing PR concurrency on the correction.

**CD-02 — ELF inspection command isolation.** Second CI [#44409168543](https://github.com/KayzenRoot/stormline/actions/runs/44409168543): Windows **98/98 PASS**, macOS **98/98 PASS**, Linux and Linux ASan failed at new CMake probe `ABI_FAIL missing ELF dependencies or symbol-version inspection` despite successfully linking C++20 test executable. Corrected CMake probe only: separate mandatory `readelf -d` and `readelf --version-info` calls, optional `readelf -n` for ISA (explicit NOT_QUALIFIED when unavailable), detailed return/error diagnostics. No weakening of GLIBC/GLIBCXX or import requirements, no workflow or toolchain change.

## Observed native run on exact code HEAD `94b59b9...`
[CORE-01 internal headless #44409782984](https://github.com/KayzenRoot/stormline/actions/runs/44409782984); [Docs Validation #44409782840](https://github.com/KayzenRoot/stormline/actions/runs/44409782840) **SUCCESS**. Three native jobs completed green; Linux normal is **IN_PROGRESS in runner dependency provisioning** at the time of this Evidence-only write, not proven PASS and not claimed as such.

| OS and GitHub job | CTest | Binary SHA256 (exact built ABI test executable) | Observed metadata / scope |
|---|---|---|---|
| [Windows #135174504773](https://github.com/KayzenRoot/stormline/actions/runs/44409782984/job/135174504773) | **98/98 PASS** | `9aa674af73f2f6d42f00884fe0cad785926a4a84094a6fd9c31421f2bb4b3c7e` | PE x64; MSVC 19.51.36260.0, toolset 14.51.36231, WindowsSDKVersion 10.0.26100.0, CMake4.4.5/Ninja1.13.2; `MSVCP140D`, `VCRUNTIME140D`, `UCRTBASED` debug CRT; redist floor **NOT_QUALIFIED** |
| [macOS #135174504082](https://github.com/KayzenRoot/stormline/actions/runs/44409782984/job/135174504082) | **98/98 PASS** | `3121c90fef9016051d8871a16842e5f91a99096959516654e9b2d4425ff624cb` | Mach-O arm64, minos15.0, SDK15.5, Xcode16.4 build16F6, AppleClang17.0.0.17000013, CMake4.4.5/Ninja1.13.2, libc++/libSystem/libobjc; candidate Xcode26.3 **NOT_QUALIFIED** |
| [Linux sanitizer #135174504733](https://github.com/KayzenRoot/stormline/actions/runs/44409782984/job/135174504733) | **99/99 PASS**, ASan/UBSan enabled, zero reported sanitizer errors | `02138235e10fe6a5660a6eef54a0177e7f2c70bc4f7d10cb00a7f4943d83ffff` | ELF64 x86_64, GCC13.3, CMake3.31.6/Ninja1.13.2; highest observed GLIBC_2.38, GLIBCXX_3.4.32; NEEDED libasan8/libubsan1/libstdc++/libgcc_s/libc; note_rc=1, ISA **NOT_QUALIFIED** |
| Linux normal | **PENDING** | PENDING | ABI test/99 CTests need exact-head confirmed success |

**Observed internal C++ sizes:** `NativeWindowHandle=24 bytes, align=8` on Windows/Linux/macOS; `Window=16 bytes, SdlRuntime=8` on MSVC but `Window=24, SdlRuntime=16` on GCC/AppleClang. This directly demonstrates why a stable C++ cross-binary ABI must **NOT** be claimed. ABI candidates (GCC16.2, Clang23.1.5, MSVC14.50/14.52, Windows SDK build .9457, Xcode26.3) are not auto-qualified by these observed runner versions.

## Scope of negative oracles
GitHub CTest passes only if `core01_abi_internal_negative` rejects unissued/default/forged handles, and `core01_abi_native_negative` confirms malformed-object inspection refuses a false positive. No test simulates actual binary-compatible SDK plugin or physical external OS floor. Both tests run on actual platforms, no unauthorized external process beyond CMake and own binary.

## Security, legal, rollback and limitations
Existing repo CI with `contents:read`, pinned checkout, public standard runners and already authorized Linux dependencies. The test script spawns no untrusted shell/network, no new tools or downloads; build-tree malformed file is removed. Source-code license NLE-D009 stays OPEN; third-party ABI/toolchain licenses and SBOM/release readiness remain out of scope. No known HIGH/CRITICAL introduced in test-only diff based on static inspection; no full security certification.

**NOT_QUALIFIED:** external ABI/plugins, stable `sizeof` across compilers, no-AVX CPU support, compatibility of historical glibc/CRT/SDK, runtime on physical Win11/macOS15/Wayland Linux, G3-V01 candidate versions, library redistribution, signing, performance p95/RSS thresholds, release and entire CORE-01 module. Zero claim of G3 globally CLEARED.

**Execution gate:** this Evidence-only update changes the PR head and triggers fresh native+Docs validation; since existing CI uses `cancel-in-progress`, pending Linux normal from the previous head may become CANCELLED. Final audit must prove **four native jobs** on the new exact head; prior 3/4 cannot substitute. If any fail, remain Draft and fix only same WO/PR.

## Independent audit, merge, checkpoint
**PENDING**: exact final HEAD CI receipts, pt-BR objective audit, APPROVED/ CORRECTION REQUIRED / BLOCKED, Ready, squash merge, separate checkpoint documentation PR and readback. Proposed Checkpoint Delta: factual limited native ABI observation, binary SHA256 and OS compatibility gaps; no modification to G2, G3 status, ADRs, registry/manifest, NLE-D009 or module completion.
