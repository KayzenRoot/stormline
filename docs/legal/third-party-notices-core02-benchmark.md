# Third-party notices — CORE-02 allocator benchmark

**Scope:** optional benchmark target `stormline_core02_allocator_bench` only. Not linked into production engine targets. Build-time FetchContent downloads exact commits; no third-party source is vendored in this repository.

| Component | Version | Commit | License | Upstream |
|---|---|---|---|---|
| mimalloc | v3.7.0 | `1ed67b5156a763441d2ec3c20221a7b3cd866129` | MIT | https://github.com/microsoft/mimalloc |
| rpmalloc | 2.0.1 | `beef233c176b235587c0145f765e4316e5ca60d1` | MIT | https://github.com/mjansson/rpmalloc |

Both upstream `LICENSE` files are MIT. If a benchmark binary is ever distributed, the MIT copyright/license notices from both projects must accompany it. This notice does not select either allocator, does not change NLE-D009 (`OPEN`) and does not authorize redistribution or release.

**Build isolation:** mimalloc is configured with `MI_OVERRIDE=OFF`; rpmalloc is compiled with `ENABLE_OVERRIDE=0`. The harness calls explicit `mi_*`/`rp*` APIs; no global `malloc/free/new/delete` replacement is installed.

**Verification date:** 2026-11-19. Re-check licenses/advisories before any update, distribution or production use.
