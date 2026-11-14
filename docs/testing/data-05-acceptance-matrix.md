# DATA-05 — Future Cooking, Streaming, Patch and Security Acceptance Matrix

**WO:** NLE-P00-WO-002-DATA-05 | **Research issue:** #120 | **Status:** TESTS SPECIFIED; NOT EXECUTED.
All tests require actual toolchain/source SHA, fixture license+digest, exact target profile/codec version, expected output and run URL; metrics are evidence rather than marketing claims.

| ID | Risk | Future fixture / exercise | Required objective proof |
|---|---|---|---|
| COOK-001 | STANDARD | original 2D sprites/atlas, layers and color profiles | target texture/sprite atlas semantics + AssetId references preserved within declared tolerances |
| COOK-002 | STANDARD | 2.5D mixed sprite/mesh and shader variants | scene cooked with explicit capability fallbacks, no silent layer/order loss |
| COOK-003 | STANDARD | 3D glTF/PBR, mesh skin/morph and tangents | meshoptimizer/codec A/B compares fidelity, size and loader compatibility |
| COOK-004 | STANDARD | KTX2/Basis + BC/ASTC/ETC capability tiers, normal maps, alpha, mipmaps | target format negotiated, color/normal fidelity, fallback and mip correctness |
| COOK-005 | STANDARD | WAV/Opus/Vorbis candidates with stereo/surround | sample/channel/duration metadata and quality tolerances; no unjustified double compression |
| COOK-006 | ELEVATED | pin DATA-03 receipts, DATA-04 scenes, DATA-02 dependency snapshot, recook twice | equivalent derived scene, consistent chunk hashes if bytewise guaranteed, no source mutation |
| COOK-007 | STANDARD | changed one small shared asset / long dependency DAG | affected cook nodes rebuilt; untouched chunks reused by verified digest |
| COOK-008 | ELEVATED | cook from stale source revision/renamed AssetId/unresolved subasset | explicit error/conflict, no mismapped stable references |
| COOK-009 | ELEVATED | malformed chunk count, zero/huge length, offset overflow/overlap | reject before read/alloc; no out-of-range seek or crash |
| COOK-010 | ELEVATED | tampered manifest and valid content hash from untrusted signer | byte integrity and publisher trust reported separately, unsigned remote activation denied |
| COOK-011 | ELEVATED | corrupt chunk, dictionary or compressed payload, expansion bomb | checksum failure/limited decompression and deadline, no OOM/data exposure |
| COOK-012 | ELEVATED | unauthorized source/content, third-party restricted asset | provenance and redistribution policy blocks cook/export, sanitized report |
| COOK-013 | STANDARD | progressive startup and large scene (cold cache) | BOOTSTRAP_REQUIRED group usable before optional chunks; bounded RAM/CPU/VRAM and p50/p95/p99 |
| COOK-014 | ELEVATED | tight memory/GPU upload budgets, cancel/deadline and queue starvation | no unbounded resident growth, proper cancellation, fairness and resource release |
| COOK-015 | STANDARD | visible next-region vs prediction prefetch | SASG vs baseline priorities+bounded LRU, measure wasted bytes and p95/p99; drop if not superior |
| COOK-016 | STANDARD | Web HTTP range 206, full 200 fallback, 416, stale ETag/If-Range | correct slice verification or graceful full-download fallback, cache/representation safety |
| COOK-017 | ELEVATED | Web offline/cache eviction/reload across version switch | previous valid generation or explicit offline unavailable, no mixed generation |
| COOK-018 | ELEVATED | patch with unchanged chunks and changing target profile | verify identical chunks reused only when codec/target semantics match; no stale content |
| COOK-019 | ELEVATED | kill/cancel/disk full at each patch stage including activation/reconcile | crash recovery to one verified generation; no acknowledged half-commit |
| COOK-020 | ELEVATED | retry same idempotency key; rollback/roll-forward and garbage collection | no duplicate update, prior-good retained until safe, security anti-rollback policy respected |
| COOK-021 | ELEVATED | MCP caller attempts arbitrary host path, URL, signing key, shell and bypass | denied with zero side effects and no leak; authorized preview read-only |
| COOK-022 | STANDARD | native Windows x64/Linux x64/macOS arm64 (Intel feasibility), Web and headless | exact loader feature/ABI parity and honest unsupported target errors |
| COOK-023 | STANDARD | 1k tiny assets vs huge 3D world and tiny Web packages | comparable zstd/LZ4/Brotli/meshopt/KTX2 experiments p50/p95/p99, peak RSS, size, IO/network bytes, first-use |
| COOK-024 | ELEVATED | license/codec component build: Zstd, LZ4 CLI/lib, KTX etcdec, Basis | exact source and build SBOM excludes nonapproved proprietary/copy-left runtime component; notices complete |
| COOK-025 | STANDARD | signed release with compatible/noncompatible minimum loader versions | fail-closed trust/format negotiation, safe fallback or explicit error, no unknown required feature use |
| COOK-026 | ELEVATED | corrupt or stale CDN range, dictionary confusion and rapid generation switch | no mixed content, digest+version verify and bounded retries |
| COOK-027 | ELEVATED | physically weak CPU/GPU/RAM and old SSD/HDD profile | reproducible load/encode/decode times, stalls and memory under declared configuration |
| COOK-028 | STANDARD | change chunk size / binary diff strategy vs content chunk reuse | A/B patch bytes, CPU/RAM/storage, failure rates and rollback complexity; no unsupported speed claim |

## Test plan and benchmark protocol
- **Golden fixtures:** independently authored or redistributable rights-cleared 2D/2.5D/3D scenes, dense material/animation/audio assets, plugin metadata, variations, exact fingerprints; do not include copyrighted game assets without rights.
- **Security/fuzz:** malformed file/manifest, decoder plugin CVE checks, sizes/offsets/dictionaries, path traversal, random bytes, malicious chunk metadata, network replay, cache and release-signature confusion.
- **Durability:** deterministic fault injection at every stage including staging/verify/commit-identity/current-generation rename/reconcile/GC, readback old and new content, prove no partial acknowledgment.
- **Portability:** actual native OS, macOS Apple Silicon, Intel target decision, browser/WebAssembly adapter, headless service with exact input/feature constraints; GitHub docs CI alone does not prove GPU or platform availability.
- **Performance:** record p50/p95/p99, CPU load, RAM peak, disk I/O, VRAM and GPU upload timing if available, compression ratio, patch network bytes, first useful frame, stutter duration, prefetch waste. Establish baseline hardware and realistic datasets before threshold or percentile claims.
- **Determinism:** build/version/codec/recipe/target/source SHA; explicit bytewise vs semantic tolerance and non-reproducible modes; cache contamination and cross-project rights tests.
- **License/supply chain:** pin tags, transitive notices, machine-generated SBOM, reproduce chosen compilation flags and prove that forbidden optional decoder code isn't present.
- **CI:** current free docs-validation checks only Source Pack/links/DAG/blocked queue. Future code checks need real build commands, seeded datasets, cross-OS hosts, sanitizer/fuzzer where feasible and actual run logs.

**NONE of COOK-001..028 have been run.** No bundle, codec executable, source migration or runtime engine exists.
