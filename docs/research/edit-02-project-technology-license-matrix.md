# EDIT-02 — Project Format, Template, Storage, Security and License Technology Matrix

**Primary-source research 2026-11-15. P00 documentary only, ZERO installed SDK/CLI or selected storage library.** Engine source license **NLE-D009 OPEN** and ADR-0054 PROPOSED. Verify exact upstream tag/commit, SPDX/file/LICENSE, transitive dependency notices, crypto/signing and platform compatibility before adoption. Existing engines inspire patterns; their project/assets/templates are **not** Stormline dependencies or redistributable starter content.

## 1. Evidence from professional engine architecture
| Reference | Original documented behavior | Stormline design implication (not copied or implemented) |
|---|---|---|
| [Godot Project Manager](https://docs.godotengine.org/en/stable/tutorials/editor/project_manager.html) | creates/imports projects with root path, template and recently used projects; accepts ZIP import with product-specific behavior | dedicated launcher and mode/target validation, **secure archive extraction separately required** |
| [Godot project.godot](https://docs.godotengine.org/en/stable/tutorials/editor/project_settings.html) | source-control-friendly INI-formatted root descriptor and project settings, unspecified settings may inherit defaults | descriptor should be diffable, defaults versioned/explicit, avoid version-dependent implicit values |
| [Unity asset metadata](https://docs.unity3d.com/jp/current/Manual/asset-database-contents.html), [.meta GUID](https://docs.unity3d.com/kr/2018.3/Manual/BehindtheScenes.html) | GUIDs in asset sidecar metadata preserve references independently from file names; caches can be regenerated | DATA-02 owns stable AssetId, metadata and source/derived separation, EDIT-02 does **not** reimplement it |
| [Unity package manifest](https://docs.unity3d.com/es/current/Manual/upm-manifestPrj.html) | project `Packages/manifest.json` contains dependency declarations; package manager uses registry/lock info | versioned dependency manifest & immutable hash/lock, no surprise network package restore |
| [Unreal projects and templates](https://dev.epicgames.com/documentation/pt-br/unreal-engine/working-with-projects-and-templates-in-unreal-engine) | `.uproject` identifies project; browser mirrors content directory; templates enable different game starting points | separate project descriptor/mode from world/scene representation, original starter templates |
| [SQLite WAL](https://www.sqlite.org/wal.html), [durability pragma](https://www.sqlite.org/pragma.html) | WAL supports local same-host readers and one writer, **not cross-host network filesystem**, synchronous=NORMAL may lose latest acknowledged commit on power failure | may cache index but **cannot** be canonical cross-platform multi-host project transaction without proof |
| [Linux openat2](https://man7.org/linux/man-pages/man2/openat2.2.html), [Windows reparse points](https://learn.microsoft.com/windows/win32/fileio/reparse-point-operations) | OS supports rooted handle-relative resolution restrictions and reparse info | DATA-01+CORE-01 secure path handles; string normalize/verify then reopen is TOCTOU-vulnerable |

## 2. Technology and source-code license study, none selected
| Candidate (primary source) | Verified/preliminary source rights | Technical benefit, caution and required due diligence |
|---|---|---|
| Original deterministic UTF-8 **JSON descriptor** with schema/provenance | Stormline-authored format, engine license **still OPEN**; JSON format itself no linked commercial binary by necessity | human diff, reproducible tests; canonical number/Unicode/range and object-key policy, unknown-required feature fail-closed; don't equate JSON syntax with valid project |
| Original TOML/INI/YAML alternatives | formats specified independently, parser licensing varies by concrete library | TOML ergonomic, INI/simple Godot precedent, YAML flexible but implicit typing/anchors are threat surface; owner chooses with parsing/security evidence |
| [simdjson](https://github.com/simdjson/simdjson), [license statement](https://github.com/simdjson/simdjson/blob/master/README.md) | **Apache-2.0 OR MIT** for core, repo includes Boost/LLVM exception/BSD third-party parts; check exact distribution | fast JSON parsing; speed alone cannot prevent oversized/depth/duplicate keys or semantic path attacks |
| [nlohmann/json](https://github.com/nlohmann/json), [LICENSE.MIT](https://github.com/nlohmann/json/blob/develop/LICENSE.MIT) | **MIT** core; bundled components to verify | convenient deterministic JSON handling, allocator/CPU and huge/deep adversarial JSON must be bounded |
| [Protocol Buffers](https://github.com/protocolbuffers/protobuf/blob/main/LICENSE) | **BSD-3-Clause** | binary schemas/unknown fields; a binary internal index/IPC candidate, **not required for root human-readable descriptor** |
| [FlatBuffers](https://github.com/google/flatbuffers) | **Apache-2.0** | binary metadata/packs, requires verifier/size bounds and schema version discipline; not user-facing root descriptor default |
| [SQLite](https://www.sqlite.org/copyright.html), [license and warranty](https://www.sqlite.org/purchase/license) | core **public domain**, proprietary extensions **not covered**; optional warranty purchased in some jurisdictions | local generated asset/project index only; WAL and synchronous=FULL/EXTRA/recovery/locking tradeoffs, network FS caution |
| [libarchive](https://www.libarchive.org/) | official **New BSD License**, exact bundled components/subsystem license notices may vary | parser for ZIP/tar import/export, **not** automatic ZIP-slip/symlink/hardlink/decompression bomb prevention; add explicit constrained extraction policy |
| [OpenUSD](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt), [repo](https://github.com/PixarAnimationStudios/OpenUSD) | dev LICENSE currently headed **Tomorrow Open Source Technology License 1.0**, Apache-2.0-like but **trademark clause differs**, third-party notices apply; **do not label blanket plain Apache-2.0** | useful future USD scene/asset interoperability, but runtime complex and **not EDIT-02 canonical project descriptor**, defer to data import modules/license review |
| [zstd](https://github.com/facebook/zstd/blob/dev/LICENSE) | core **BSD-3-Clause OR GPLv2** according to upstream release; exact files/tool choices to verify | archive compression for optional exports; never enable unlimited expansion, streaming cap required |
| [GoogleTest](https://github.com/google/googletest/blob/main/LICENSE) | **BSD-3-Clause** | future negative tests/fault injection, no project integrity proof merely by choosing it |
| [Google Benchmark](https://github.com/google/benchmark/blob/main/LICENSE) | **Apache-2.0** | future controlled filesystem benchmarks, cannot prove power-loss persistence on unsupported media |
| filesystem-specific APIs | OS SDK platform terms, kernel capabilities, no generic portable guarantee | Linux openat2 RESOLVE_BENEATH/NO_SYMLINKS, macOS openat/O_NOFOLLOW and file identity, Windows CreateFile reparse handle policy; **test each platform** |
| remote templates/marketplaces/online registries | **license per package/template/art/fonts and provider terms**, expenses/SSRF concerns | future opt-in only; original zero-cost local templates without external network requirement |

## 3. Filesystem/storage option evaluation
| Option | Advantage | Failure and selection gate |
|---|---|---|
| plain files in user project + deterministic descriptor + VFS | Git-readable, cross-OS, portable | multi-file atomicity requires staging/markers/CAS; source of truth still schema-owner files |
| SQLite for generated index/cache | transactional queries and fast project search | cache regenerable and not authoritative; WAL local host only, unsupported network fs and power-loss sync mode |
| giant SQLite canonical monolithic project | single DB transaction | poor human diff, source-control merge, recovery/transitive assets; **not proposed default** |
| zip all project into one archive on every edit | portable export | expensive updates and crash/corrupt archive risk; only explicit bounded snapshot/export |
| multi-instance leases with OS file lock only | simple local | stale locks and PID reuse/TOCTOU, cloud sync split-brain and case-insensitive FS; use expected revisions+read-only fallback |
| remote object/SQL transactional service | cross-host concurrency possible | paid operational burden/online requirement/privacy, separate future design/consent |
| global path hash as asset identity | deterministic cache | rename breaks references and hash collision/duplication semantics; **reject** |

## 4. Threat matrix and path/format conditions
| Threat ID | Attack/OS hazard | Owner and future proof |
|---|---|---|
| P-01 | `../`, UNC, drive absolute, Windows ADS or reserved device filenames | DATA-01 rooted VFS handle, EDIT-02 reject and typed error, actual OS fixture |
| P-02 | symlink/junction/reparse/hardlink/mount escape | DATA-01/CORE-01 component handle nofollow and volume identity, no TOCTOU between preview and commit |
| P-03 | ZIP-slip/tar link, archive bomb/huge sparse file | EDIT-02 bounded parser+extract with libarchive candidate under explicit policy, no scripts |
| P-04 | Unicode normalization/case/length collision | OS platform valid-name set and unique ID, readable error; preserve display name |
| P-05 | crash/power failure during staging or commit | immutable prior content, atomic same-volume rename+flush where supported and journal marker + recovery; real fault injection |
| P-06 | concurrent writers/old lock and stale project schema | scoped lease/CAS and read-only fallback, monotonic generation + owner consistency |
| P-07 | newer project format/unknown required feature | minimum reader/version contract deny or read-only, no destructive downgrade |
| P-08 | asset GUID loss after relocate/import/export | DATA-02 owner stable IDs and dependency-ref test, path not identity |
| P-09 | malicious template post-create scripts/dependency URLs | no automatic exec/download; signed/hash provenance and explicit user approval, SSRF limitations |
| P-10 | false durability assumptions (SQLite WAL NORMAL, remote share, bad sync) | selected storage backend-specific power-fault test, no blanket crash-safe claim |
| P-11 | backup hardlink mutated, snapshot missing after migration | immutable source/verify digest, copy-on-write safety or physical copy, roll-forward/rollback |
| P-12 | project path, personal data or hidden assets leaked to logs/MCP | redact scoped metadata, role and explicit capability |
| P-13 | GPU/Web target incompatibility | GFX/Web feature check, unsupported mode/config refusal, not fake functional exporter |
| P-14 | user cancellation after commit/accidental overwrite | explicit rollback and original target preservation, never auto delete existing project |
| P-15 | project manager indexing massive dirs/hotplug storage | quotas/timeouts, cancellation, async status, no UI main-thread stall |
| P-16 | licenses of imported asset/template/plugin | original template by default and SBOM/provenance/asset rights check, no automatic restricted material |

## 5. Selection/proof duties
Pin exact source tag/sha, SPDX and transitive SBOM, target OS/arch, mode compatibility and licensing. Do not conflate permissive parser licenses with safe path resolution, or a database ACID claim with directory-level power-loss proof. SQLite WAL is **not** cross-host network FS suitable; OpenUSD is **not** unconditionally plain Apache-2.0 on its current dev tree. NLE-D009 engine license stays OPEN; no SDK/library/provider selected or installed; ALL 128 tests FUTURE/NOT EXECUTED.
