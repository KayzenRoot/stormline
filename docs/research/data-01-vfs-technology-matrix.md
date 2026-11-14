# DATA-01 — Virtual File System Candidate Technology Matrix

**WO:** NLE-P00-WO-002-DATA-01 | **Research issue:** #108 | **State:** PROPOSED RESEARCH ONLY

| Candidate | Mechanism | License | Main benefits | Risks / gates |
|---|---|---|---|---|
| **C++20 `std::filesystem`** | path/dir/file metadata primitives | compiler standard library distribution terms | portable basic path semantics, zero direct library addition | canonicalization not race-free sandbox; insufficient for untrusted roots |
| **Owned minimal mount table + native handle backend** | typed `VfsPath`, priority mount list, read-only dirs, safe platform opens | Stormline-owned API code | few dependencies, simplest security baseline and fallbacks | needs careful native Win32/POSIX confinement tests and resource ownership |
| **PhysicsFS** | portable search-path and archive mounts, overlay priority | **zlib** per official upstream | convenient packed game assets and layered mounts | source search path/symlink behavior not identical to secure sandbox; verify exact revision and archives supported |
| **libzip 1.12.1** | ZIP read/write/create and temporary-file archive replacement | **BSD-3-Clause** per official license | archive writer/editor pipeline when needed | transitive compression libraries and ZIP parsing limits; dependency overlap with PhysicsFS |
| **Native ZIP encoder or read-only custom pack** | simple streaming bundle format with signed manifest option later | original/optional codec library terms | exact control over runtime package; limit complexity at first step | maintenance/security/parsing burden and no invented compression benefits |
| **Archive tooling via external OS commands** | `unzip` subprocess and system utilities | tool-dependent | useful local QA fixture generation only | **reject** for runtime/untrusted path, subprocess/security/distribution |
| **Network/cloud mounts** | HTTP/S3, remote caching | provider/SDK terms vary | possible future streaming | out of scope for DATA-01; separate permission/auth/security ADR required |
| **Stormline Asset Mount Graph (SAMG)** | mount snapshot graph, explainable overlay and incremental cache invalidation | research candidate, no code | potential diagnostics and safe AI editing value | must outperform simple mount table/safety baseline |

## Decision procedure, no fabricated performance rankings

1. Start with **typed, owned `VfsPath` and mount/capability contract**; use `std::filesystem` only for trusted native path assistance and file metadata. Never present lexical normalization or `canonical` as complete sandbox.
2. Use a plain read-only directory mount table as mandatory control case; benchmark PhysicsFS for overlay/archive usability and feature coverage. No premature third-party types in public SDK.
3. Consider libzip **only** for ZIP archive editing/creation if not handled adequately by a smaller target-specific cooking subsystem; avoid two runtime libraries with overlapping features.
4. Use native capability-safe handle-based open and fail-closed behavior for untrusted directory mounts. Linux `openat2`, Windows reparse handling and macOS dirfd are implementation research gates.
5. Preserve DATA-02 persistent AssetId independence from VFS paths; streaming bundles and patching belong DATA-05.
6. Keep SAMG only after objective correctness or latency improvement and measured memory/build cost, not for branding.

### Weighted proposed evaluation
- Security against path escape, symlink race and malformed archives: **30%**
- Correctness and crash recovery: **20%**
- Windows/Linux/macOS/Web/headless compatibility: **15%**
- Lookup/IO tail latency, RAM/cache pressure: **15%**
- License provenance, maintenance and supply chain: **10%**
- Simplicity, modularity and Editor/MCP ergonomics: **10%**

No actual performance measurements exist; weighted scores are intentionally blank.

### Primary official sources
- C++ filesystem: https://en.cppreference.com/w/cpp/filesystem
- PhysicsFS zlib license and repository: https://github.com/icculus/physfs
- PhysicsFS mount API: https://www.icculus.org/physfs/docs/html/physfs_8h.html
- libzip license: https://libzip.org/license/
- libzip documentation (1.12.1): https://libzip.org/documentation/libzip/
- Linux safe open: https://man7.org/linux/man-pages/man2/openat2.2.html
- Windows reparse handling: https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew

## Holding points

- No final library/version selected or vendored.
- No archive parser benchmark/security fuzzing has run.
- No actual VFS sandbox verified on Windows/Linux/macOS.
- No cloud, paid provider, plugin unrestricted disk read, DRM or file system writes are authorized.
- Public engine release and VFS implementation remain FUTURE.
