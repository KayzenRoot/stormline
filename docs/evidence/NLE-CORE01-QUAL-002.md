# NLE-CORE01-QUAL-002 — Native ABI/Toolchain Evidence Bundle

**STATUS:** TESTS IMPLEMENTED / NATIVE CI AND FINAL AUDIT PENDING. No CORE-01 module qualification.  
**Risk:** STANDARD preflight, test-only source, no production changes.  
**Base:** `main@7da51f4a314a81959aa31cb56f5f5d06228fe4bc`.  
**Work Order:** [NLE-CORE01-QUAL-002](../work-orders/NLE-CORE01-QUAL-002.md).  
**PR / final tested HEAD:** to be filled only after actual GitHub readback.

## Source Check (2026-11-18)
Canonical hierarchy checked against Git: checkpoint `abfdb3d0dd588829c89321b69bbc54fb0a82250e`, Ledger `01aa967790dc1ea5e72c2ebebae7b832ec579981`, Scope `0b65820507d946d2b2b4ed3a2b869e60cafaaf22`, DoD `e0b7c2466ebec9790a715e47490c015cfb502db4`, Architecture `df62574cb3956c3ac9881631a4cf66be4e1abff1`, Requirements `14c84b5cd7334b81f63e6a2ba8a07bef73fdee7b`. Git blob SHA is **not** SHA256 of an emitted executable. G3-V02 prior experimental fixture and the merged QUAL-001 were inspected for no unnecessary duplication.

## Exact allowlist (5)
1. `tests/core/core01_abi_portability_tests.cpp` (new typed C++20 layout/ownership and invalid-handle oracle)
2. `cmake/core01_abi_probe.cmake` (new native binary inspection and malformed-file negative)
3. `CMakeLists.txt` (additive target/CTest/build-time native receipt only)
4. `docs/work-orders/NLE-CORE01-QUAL-002.md` (bounded WO)
5. This Evidence Bundle

No changes to runtime source, CI workflow, G2 rules, SDK/downloads/dependencies, licenses, ADRs, manifest or registry.

## Proof oracles, not yet execution proof
- Positive and negative C++20 tests: internal header fields, exact field types, type traits (ownership/non-copy, no-throw destructors), observed sizeof/alignof, compiler and standard-library macros; reject unissued/forged `NativeWindowHandle` without a video init. **Not** frozen public ABI; `std::thread::id` and `std::unique_ptr` are not binary-crossable.
- Native CMake probe reads own just-built exact test binary, SHA256/size, OS/arch/toolchain/CMake/Ninja versions. Rejects malformed file header with dedicated negative CTest. Tools must be already preinstalled; no shell or downloads. Post-build prints receipts even if normal CTest hides green output.
- Linux: `readelf` ELF64 x86_64 header, `DT_NEEDED`, actual GLIBC/GLIBCXX symbol-version requirements and ISA property **if present**; absence of GNU ISA marker = explicit NOT_QUALIFIED, not a proof that AVX is absent; no oldest-distro floor.
- Windows: `dumpbin` PE x64 header, imported DLL/CRT, observed WindowsSDKVersion and VCToolsVersion environment, redist/floor remain NOT_QUALIFIED.
- macOS: `lipo` arm64, `otool -l` LC_BUILD_VERSION/minos/SDK, `otool -L` dependent libraries, observed Xcode/`xcrun` SDK; physical macOS 15 runtime floor NOT_QUALIFIED.
- Expected CTests **99 Linux and Linux ASan/UBSan**, **98 Windows and macOS**, from 95/94 respectively. Required native logs/ASan/UBSan and Docs Validation: PENDING, do not claim PASS.

## CI receipts
| System | Workflow/job | CTests | ABI binary SHA256 | G3 partial proof | State |
|---|---|---|---|---|---|
| Linux GCC | PENDING | 0/99 not run | PENDING | P04/P06/P07/P11 proposed | NOT_RUN |
| Linux ASan+UBSan | PENDING | 0/99 not run | PENDING | sanitizer execution pending | NOT_RUN |
| Windows MSVC | PENDING | 0/98 not run | PENDING | P03/P06/P07/P11 proposed | NOT_RUN |
| macOS arm64 | PENDING | 0/98 not run | PENDING | P05/P06/P07/P11 proposed | NOT_RUN |
| Docs Validation | PENDING | N/A | N/A | no native inference | NOT_RUN |

## Limits / risk / corrections
No claim of product minimum OS/SDK/glibc/CRT, available physical CPU, ISA requirement proof without notes and tests, external ABI/C SDK, plugin support, compiler interoperability, candidate G3-V01 toolchain approval, Windows/macOS headless without physical display, release/distribution, NLE-D009 decision or owner-ratified performance threshold. ELF symbols show *observed binary requirements*, not a commercial support floor. Native ABI layout is internal and compiler-specific, not serialized contract.

**Correction Delta:** none at initial authoring. If actual CI fails, collect red logs, diagnose only within same five paths, correct regressions, rerun exact HEAD; keep PR Draft pending audit.

**Governance invariants:** CORE-01-03..16 internal COMPLETED; 80/80 module Work Orders BLOCKED, 0 EXECUTOR_READY, `engine_implemented=false`. Manifest Git blob `dc01d3ccc62e857feeb61b3be599f66ae2c08c44`; registry blob `abbf8e5f971b8de5d73f55c9ec5a0bd7a2632024`. ADR-0003/0075 PROPOSED, NLE-D009 OPEN, global G3 NOT_CLEARED. No new WO/module activation. Do not promote checkpoint before independently audited squash merge.

## Independent pt-BR audit / checkpoint delta
**PENDING** exact-head native CI, preflight readback, code/diff audit, status `APPROVED`/`CORRECTION REQUIRED`/`BLOCKED`. Proposed checkpoint is strictly a factual record of observed receipts and remaining limitations; create its own one-file PR only after APPROVED+merge and separate Docs Validation, pt-BR audit and readback.
