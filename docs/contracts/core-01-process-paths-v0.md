# CORE-01 INTERNAL_ONLY Portable Process Paths Contract v0 (NLE-PRPLAN-CORE-01-06)

**Status:** `CONTRACT PROPOSAL / NOT IMPLEMENTED / NOT EXTERNAL ABI`. **Base:** `b3638de6c6918e36b49726af63abeb09bd35f140`. **Owner authority:** `STORM-CORE-01-IMPL-001` (2026-11-17). **Work Order:** [NLE-PRPLAN-CORE-01-06](../work-orders/NLE-PRPLAN-CORE-01-06.md). **Bounded ADR:** [ADR-0083](../adr/0083-core-01-internal-headless-slice.md) remains limited to the internal CPU-only slice.

## Objective and bounded scope

Provide a small, read-only, internal C++20 API for portable process paths: current working directory, system temporary directory, absolute normalization, containment inside an explicit root, and a UTF-8 representation. It is a query utility, **not** a virtual filesystem, asset resolver, sandbox engine or permission system.

Explicitly out of scope: file/directory creation, writing, deletion, renaming, watching, copying, permission changes, network, telemetry, logging of private paths, environment mutation, SDL3, window/GPU/audio, public C ABI or plugin surface, and any VFS/DATA-01 ownership.

## Internal API (exact names)

Namespace `stormline::core::internal`, no symbol/ABI stability guarantee:

```cpp
#include <cstdint>
#include <filesystem>
#include <string>

enum class PathError : std::uint8_t {
    None,
    CurrentDirectoryUnavailable,
    TemporaryDirectoryUnavailable,
    NotFound,
    AccessDenied,
    InvalidPath,
    PathTraversalRejected,
    AllocationFailed,
    InternalFailure
};

struct PathResult final {
    PathError error{PathError::None};
    std::filesystem::path path{};
    [[nodiscard]] bool ok() const noexcept { return error == PathError::None; }
};

struct PathTextResult final {
    PathError error{PathError::None};
    std::string utf8{};
    [[nodiscard]] bool ok() const noexcept { return error == PathError::None; }
};

[[nodiscard]] PathResult current_directory() noexcept;
[[nodiscard]] PathResult temporary_directory() noexcept;
[[nodiscard]] PathResult normalize_absolute(const std::filesystem::path& input) noexcept;
[[nodiscard]] PathResult normalize_within_root(
    const std::filesystem::path& root,
    const std::filesystem::path& candidate) noexcept;
[[nodiscard]] PathTextResult to_utf8(const std::filesystem::path& input) noexcept;
```

All five functions are `noexcept`; no C++ exception may cross the boundary. A test-only seam may force a `std::error_code` for deterministic mapping tests, but it must not be a public API, must be thread-local, and must default to no injection.

## Semantics

### `current_directory()`

Calls `std::filesystem::current_path(ec)`. Returns an absolute path on success. `permission_denied` maps to `AccessDenied`; `no_such_file_or_directory` or another unavailable condition maps to `CurrentDirectoryUnavailable`.

### `temporary_directory()`

Calls `std::filesystem::temp_directory_path(ec)`. Returns the system temporary directory on success. `permission_denied` maps to `AccessDenied`; missing/unavailable maps to `TemporaryDirectoryUnavailable`. It does not create the directory.

### `normalize_absolute(input)`

- Empty input, an embedded NUL, or an invalid UTF-8 representation is `InvalidPath`.
- Resolves `std::filesystem::absolute(input, ec)` then `std::filesystem::weakly_canonical(..., ec)`.
- Does not require the final path to exist; a non-existing suffix is preserved after the canonical existing prefix.
- `permission_denied` maps to `AccessDenied`; other filesystem failures map to `InternalFailure`.
- A `std::bad_alloc` maps to `AllocationFailed`; any other caught exception maps to `InternalFailure`.

### `normalize_within_root(root, candidate)`

- `root` must exist and be a directory; missing root is `NotFound`, inaccessible root is `AccessDenied`, non-directory root is `InvalidPath`.
- A relative `candidate` is joined to `root`; an absolute `candidate` is used as provided.
- Both paths are weakly canonicalized. Existing symlinks are resolved; a symlink that resolves outside `root` is `PathTraversalRejected`.
- Containment is checked component-wise after canonicalization, not by string prefix. A candidate equal to the root is accepted; a candidate whose canonical path is not under the root is `PathTraversalRejected`.
- Missing candidate components are allowed and preserved; missing root is an error.
- Empty candidate, embedded NUL or invalid UTF-8 is `InvalidPath`.
- No file is created, opened for write, modified, renamed or removed.

### `to_utf8(input)`

- Converts the native path through `std::u8string`/`std::filesystem::path::u8string()` and returns UTF-8 bytes in `std::string`.
- Validates the resulting byte sequence as UTF-8; invalid sequences return `InvalidPath`.
- `std::bad_alloc` maps to `AllocationFailed`; other caught exceptions map to `InternalFailure`.
- No logging, redaction or telemetry; the caller owns any private-path handling.

## Error mapping

| Native condition | `PathError` |
|---|---|
| `std::errc::permission_denied` | `AccessDenied` |
| `std::errc::no_such_file_or_directory` | `NotFound` (root/status) or the function fallback |
| `std::errc::invalid_argument` / embedded NUL / empty required path | `InvalidPath` |
| canonical path outside root | `PathTraversalRejected` |
| `std::bad_alloc` | `AllocationFailed` |
| any other caught exception | `InternalFailure` |

Function fallbacks: `current_directory` → `CurrentDirectoryUnavailable`; `temporary_directory` → `TemporaryDirectoryUnavailable`; normalizers → `InternalFailure`.

## Unicode policy

- Paths are stored as `std::filesystem::path` and preserve the platform's native representation.
- **No NFC/NFD normalization is imposed** and no ICU/Unicode library is added. Composed and decomposed names remain distinct filesystem names, matching OS behavior.
- Windows native UTF-16 is converted to UTF-8 by the standard library for `to_utf8`; POSIX bytes are treated as UTF-8 and validated. Invalid UTF-8 is a typed error, not a crash or silent replacement.
- The API never logs, prints or transmits a path.

## Read-only and ownership guarantees

- Production code uses only `current_path`, `temp_directory_path`, `status`, `absolute`, `weakly_canonical` and `lexically_normal`/component comparison. It contains no creation, write, delete, rename, copy, permission-change, network or telemetry call.
- Tests may create a private fixture under the system temporary directory and remove it; the library itself never does.
- No global singleton, ambient root, current-directory mutation or hidden allocation beyond standard-library path/string storage.
- The functions are stateless and safe for independent concurrent calls. The optional forced-error test seam is `thread_local` and test-only.

## Test oracles (future implementation)

| ID | Scenario | Oracle |
|---|---|---|
| PATH-01 | `current_directory` | absolute, existing directory; repeated calls stable |
| PATH-02 | `temporary_directory` | absolute, existing directory; no creation |
| PATH-03 | Unicode round-trip | non-ASCII directory name survives `path` → `normalize_absolute` → `to_utf8`; composed/decomposed distinct |
| PATH-04 | Invalid input | empty, embedded NUL and invalid UTF-8 → `InvalidPath` |
| PATH-05 | Traversal | `root/../outside` and absolute outside path → `PathTraversalRejected` |
| PATH-06 | Contained normalization | `root/sub/../file` accepted and resolved under root |
| PATH-07 | Access denial | real POSIX `chmod` denial where supported; deterministic `permission_denied` mapping on every target |
| PATH-08 | Unavailable paths | forced `no_such_file_or_directory` maps to the correct unavailable typed error |
| PATH-09 | Symlink escape | a symlink inside root pointing outside is rejected where symlinks can be created |
| PATH-10 | No writes | fixture entry set unchanged after all query calls; no write/create/delete in production source |
| PATH-11 | Repeated queries | 200 iterations per query without error or state growth |
| PATH-12 | Regression | all existing CORE-01 headless CTests still pass on Windows, Linux and macOS |

Sanitizers run when the preinstalled Linux toolchain supports them. Real Windows ACL denial is environment-dependent; if not reproducible, it is recorded `NOT_QUALIFIED`, while the deterministic mapping test still runs. No PASS is claimed for an unexecuted case.

## Exact implementation allowlist for packet -06

1. `src/stormline/core/internal/process_paths.hpp`
2. `src/stormline/core/internal/process_paths.cpp`
3. `tests/core/process_paths_tests.cpp`
4. `CMakeLists.txt` (add the paths target and CTests; existing headless target preserved)
5. `docs/evidence/NLE-PRPLAN-CORE-01-06.md`

`docs/work-orders/NLE-PRPLAN-CORE-01-06.md` is created by the gate and is not modified by the code packet unless an audited correction is required. No other path is allowed.

## Stop / rollback / security

- Stop on stale canonical source, missing gate, failing existing tests, HIGH/CRITICAL issue, unapproved dependency or attempted write/VFS scope.
- Unmerged rollback: close the code branch; `main` is untouched. After a future merge: normal revert PR, never force push.
- No engine license change; `NLE-D009 OPEN`. No redistribution, packaging or public release.
- Risk `STANDARD`, release class `INTERNAL_ONLY`, only this internal slice. ADR-0003/0075 remain `PROPOSED`; G3 global remains `NOT_CLEARED`.

**Contract is a proposal until the exact gate PR passes Docs Validation, objective pt-BR audit and merge; code packet -06 remains blocked until then.**
