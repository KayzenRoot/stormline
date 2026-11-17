# G3-V02 | Disposable C++20 Toolchain Probe

**WO:** NLE-G3-V02-EXP-001. **Scope:** explicitly authorized one-time experiment, NOT engine implementation. No CORE-01-02, SDK/ABI, SDL3 lifecycle, production binaries, ADR adoption, license selection or release approval.

## Authorized source files
The fixture consists only of main.cpp, CMakeLists.txt, this CMakePresets.json and this README. A separately scoped PR workflow checks exact preinstalled toolchain and build-tool versions before compiling. Missing or mismatched candidates report **NOT_QUALIFIED** and do not get installed, replaced or counted as a test pass.

## Candidate matrix (owner-ratified for evaluation only)
| Job | Exact required candidate | Build prerequisites |
|---|---|---|
| Linux GCC | GCC 16.2 | CMake 4.4.5 + Ninja 1.13.2 |
| Linux Clang | Clang 23.1.5 | CMake 4.4.5 + Ninja 1.13.2 |
| Windows MSVC ref | MSVC 14.50 + Windows SDK 10.0.26100.9457 | CMake 4.4.5 + Ninja 1.13.2 |
| Windows MSVC compare | MSVC 14.52 + Windows SDK 10.0.26100.9457 | CMake 4.4.5 + Ninja 1.13.2 |
| macOS AppleClang | Xcode 26.3, full AppleClang version must be recorded | CMake 4.4.5 + Ninja 1.13.2 |

The CMake 4.5.0 comparator and CMake 3.27 + Presets schema 6 minimum are **candidates**, not declared compatible or installed. They must be reported as NOT_QUALIFIED if unavailable. SDL3 3.4.20 is a provenance-only candidate, never linked by this fixture. No SDK/toolchain installer, Homebrew, apt, Chocolatey or download script is allowed.

## Security and costs
Repository is public; workflow uses standard GitHub-hosted runners, a first-party checkout pinned to an audited commit SHA, read-only token, no secrets, no paid larger runners, no cache/artifact upload, no deployment, and a PR-branch guard. Fork PRs and unrelated future branches cannot run native jobs. CI is deliberately separate from protected docs-validation, which remains the only existing required check.

## Interpretation and stop
A job with **NOT_QUALIFIED** represents an honest preflight with zero native tests, even if the CI step itself succeeds. Only a matching preinstalled toolchain may configure, compile, link, run CTest (>=1 real test), and report **SMOKE_PASS** with a SHA-256 receipt. Results cover this fixture and exact environment only; no G3-P proof is auto-promoted to PASS. The workflow's lack of upload-artifact keeps the binary ephemeral. Recorded build outputs under ignored temp build directories are runner-local and disposed with the VM.

After PR review, audit actual workflow steps, hashes, missing candidates, security, cost and exact HEAD. STOP on untrusted fork, paid runner, unexpected privilege, unknown toolchain/SDK, failed CTest, missing provenance, scope drift or HIGH/CRITICAL. No further engine/module work is authorized.
