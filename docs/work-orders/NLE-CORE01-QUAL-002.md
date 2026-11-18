# NLE-CORE01-QUAL-002 — Native ABI & Toolchain Compatibility Proof

**Owner authorization:** expressly bounded, 2026-11-18; **scope NECESSARY / test-only / INTERNAL_ONLY**.  
**RISK (preflight): STANDARD** for compile-only and local inspection of own test binary using preinstalled tools, no privileged actions/network/dependency changes; classification re-evaluate if additional tool installation or external ABI is needed.  
**Status:** OWNER_AUTHORIZED, evidence/CI **PENDING**, not a product/module qualification.  
**BASE / CONTEXT LOCK:** `main@7da51f4a314a81959aa31cb56f5f5d06228fe4bc`; check stale before each promotion.

## OBJECTIVE
Executable and fail-closed proof of **observed** C++20 internal type layouts/ownership constraints and PE/ELF/Mach-O binary architecture, dependencies, toolchain provenance, ABI/version metadata and SHA256 across currently authorized free native CI, without claiming stable external ABI or minimum supported OS/compiler.

## CONTEXT / SOURCE HIERARCHY
Checkpoint `docs/11-checkpoint.md` Git blob `abfdb3d0dd588829c89321b69bbc54fb0a82250e` >
Decisions Ledger `docs/10-decisions-ledger.md` `01aa967790dc1ea5e72c2ebebae7b832ec579981` and bounded ADRs >
Scope `docs/03-scope.md` `0b65820507d946d2b2b4ed3a2b869e60cafaaf22` >
DoD `docs/09-definition-of-done.md` `e0b7c2466ebec9790a715e47490c015cfb502db4` >
Architecture `docs/04-architecture.md` `df62574cb3956c3ac9881631a4cf66be4e1abff1` >
Requirements `docs/02-requirements.md` `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`.
Read `docs/research/core-01-01-g3-toolchain-abi-qualification.md`, `docs/engineering/core-01-01-qualification-gates.md`, approved bounded CORE-01 contracts, `experiments/g3-v02` and its Evidence, `CMakeLists.txt`, `CMakePresets.json`, CI `.github/workflows/core01-internal-headless.yml`, `src/stormline/core/internal/*.{hpp,cpp}`, and last merged baseline `docs/evidence/NLE-CORE01-QUAL-001.md`. Git blobs are Git identities, not artifact SHA256.

## SCOPE / REQUIREMENTS (NECESSARY)
1. Add C++20 **test-only** fixture verifying internal header ABI *properties* with compile-time and runtime oracles: exact `uint64_t` native handle fields, standard-layout/trivially-copyable transport, enum underlying values, no copy/move ownership of Host/Window/SDL runtime, fail-closed unissued native handle; print observed sizes/alignments/compiler macros rather than pin product ABI.
2. Add CMake **test-only** PE/ELF/Mach-O inspection, using tools already preinstalled on runner. Fail if wrong file format, architecture, missing mandatory inspection tool, command failure, or absent required metadata. Test malformed-binary negative via an isolated build-tree fixture, not real source or arbitrary paths. Exact executable SHA256, toolchain details, CMake/Ninja versions, OS/arch. Mark absent ISA marker, unsupported physical-floor proof and candidate-version mismatches as **NOT_QUALIFIED** explicitly, not as passed floors.
3. ELF Linux: `readelf` real executable header, interpreters/dynamic dependencies, GNU symbol-version needs `GLIBC` and `GLIBCXX`; GNU property/ISA metadata observed or `NOT_QUALIFIED` if absent, never infer CPU without AVX. No promised oldest-glibc floor.
4. PE Windows: actual `dumpbin` PE headers machine x64, imported DLLs/CRT, SDK observed from `vcvars64` environment (`WindowsSDKVersion`); no assertion that installed headers/SDK or CRT redist are product floor without matching proof. Do not execute privileged shell or install package.
5. Mach-O macOS arm64: `otool` load commands including `LC_BUILD_VERSION`, min OS/SDK fields, shared library imports; `lipo` arm64 architecture; `xcrun` observed SDK, `xcodebuild` Xcode version. No certification of runtime on minimum macOS 15 without physical or OS-target validation.
6. Integrate pure additive test target and CTest(s) in existing `CMakeLists.txt`; build time printed inspection receipt is needed because CI hides stdout on successful CTests. Preserve 92+ established tests and QUAL-001 baseline.

## OUT OF SCOPE
Engine source, SDK/plugin/public C ABI or binary-version guarantee, exact candidate versions not installed, new compiler/SDK/dependency/license/workflow, toolchain download/installation, source-license vote NLE-D009, ABI portability between different compilers or CRTs, hardware/gpu/driver/real Wayland, signing/notarization/distribution, performance floor p95/RSS, G3 global clear, G2/rulesets, modules CORE-02+ or registry activation.

## FILES / ALLOWLIST (EXACT)
1. **NEW** `tests/core/core01_abi_portability_tests.cpp`
2. **NEW** `cmake/core01_abi_probe.cmake`
3. **ADD-ONLY** `CMakeLists.txt`
4. **NEW** `docs/work-orders/NLE-CORE01-QUAL-002.md`
5. **NEW** `docs/evidence/NLE-CORE01-QUAL-002.md`
No other modified repo paths. Build-tree temporary negative file allowed, removed in test.

## ARCHITECTURE RULES
C++20 internal types and RAII only, no SDL types/macros in internal headers, no added API/ABI/export, no mutable global adapter state, no STD type promise across binaries, no generated/vendor library modifications. `NativeWindowHandle` internal layout observed, not pinned. G3-P03/P04/P05/P06/P07/P11 qualified **partially** when actual receipt exists; P01/P02/P12/P16 and G3 global remain pending.

## CONSTRAINTS / PREFLIGHT
STANDARD test-only slice, standard public free runners, existing PR CI and pinned checkout, read-only token, no credentials, downloads/installations/new jobs/workflow edits, no external binary uploads. CMake probe uses exact `$<TARGET_FILE:...>` produced in the same checkout; no user-configurable command shell. Inspect tools with `find_program`; missing essential tool is FAIL/BLOCKED, not skipped PASS. Negative test must fail-closed if forged object were accepted. All CTest cases run in supported OS; Linux ASan/UBSan must be really enabled and error-free. No forced binary architectures or unsupported linking.

## ACCEPTANCE CRITERIA
- Positive C++ test and negative type/invalid handle/argument tests compile and run Windows/Linux/macOS; evidence of sizes/alignments and main C++20/STL runtime metadata.
- Native probe returns code 0 only on observed correct architecture/format, required ABI/import/version fields, and SHA256 of the exact binary; false object/malformed header returns failure inside negative test. Logs include relevant PE/ELF/Mach-O receipts with explicit `NOT_QUALIFIED` where no minimum/ISA/SDK proof.
- Existing regression plus new CTests entirely green in Linux GCC, Linux ASan/UBSan (enabled), Windows MSVC and macOS AppleClang, Docs Validation on the exact PR HEAD; zero sanitizer errors/HIGH/CRITICAL and no `NOT_QUALIFIED` disguised as qualified.
- Evidence records base/head SHA, five-file diff/allowlist, raw real CI jobs and SHA256 receipts, errors/corrections, source/ABI limitations, risks, pt-BR independent audit and proposed Checkpoint Delta. Only after APPROVED may squash merge and a separately audited checkpoint PR occur.

## TESTS
Existing `cmake --preset core01-internal-debug`; `cmake --build --preset core01-internal-debug`; `ctest --preset core01-internal-debug --output-on-failure` (Windows/Linux/macOS), plus `core01-internal-asan` on Linux. Explicit new `core01_abi_portability`, `core01_abi_portability_negative`, `core01_abi_native_probe`, `core01_abi_native_negative` CTests. Verify Linux probe output `GLIBC/GLIBCXX` from actual binaries, Windows `dumpbin` output and macOS `otool/lipo`. Docs Validation via same repository CI.

## DELIVERABLES
One bounded PR Draft until audited, C++20 test-only code, CMake native probe, additive CMake integration, this WO, Evidence Bundle with actual receipts, requested correction within same PR, pt-BR audit; squash merge on APPROVED, checkpoint in independent documentary PR with separate audit/merge/readback.

## REVIEW FORMAT
In pt-BR: Source Check / Context Lock, five-file allowlist, real tool versions/ABI fields/SHA, negative self-tests, CI counts/sanitizers, risk and known limits, security/regressions, recommendation, **APPROVED / CORRECTION REQUIRED / BLOCKED**. Auditor must not equate job SUCCESS with proof of a specific missing field.

## STOP CONDITION
Main/decision/critical source changes (STALE), missing tools or native host capability, out-of-allowlist, need for SDK/compiler or CI workflow change, HIGH/CRITICAL, CI failure or unsupported statement, ABI/public interface/new license decision, source change or destructive action. Leave Draft/BLOCKED, request owner authorization to exceed boundary. Keep CORE-01-03..16 COMPLETED, manifest `dc01d3ccc62e857feeb61b3be599f66ae2c08c44`, registry `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`: 80/80 module WOs BLOCKED, 0 EXECUTOR_READY, engine_implemented=false, ADR-0003/0075 PROPOSED, NLE-D009 OPEN and global G3 NOT_CLEARED.
