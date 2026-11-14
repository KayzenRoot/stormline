# DATA-05 — Target Cooking, Bounded Streaming Bundles and Transactional Patching

**Research WO:** NLE-P00-WO-002-DATA-05 | **Issue:** #120 | **Future code:** #28, BLOCKED
**Status:** RESEARCH PROPOSED / NO ENGINE | **Context Lock main:** 8659327e73e803dcf09345e95f14647375ce9fe5
**Risk:** LOW documentation, future ELEVATED (untrusted content, multi-file updates, memory safety and rollback).

## Mission
Produce **derived** target-specific, verifiable runtime resources from validated DATA-03 intermediate artifacts and DATA-04 scene IR. Enable progressive content delivery without global downloads, bounded resident-memory use, deterministic rebuilds under pinned inputs, and recoverable incremental updates across native Windows/Linux/macOS, Web and headless. This layer never edits authoritative project scenes or claims a particular GPU feature universally supported.

### Five invariants
1. **Source of truth:** DATA-04 project scenes and DATA-02 AssetId/dependency provenance, never cooked bundles. A bundled AssetId reference resolves through an explicit target manifest; no path or digest becomes the permanent AssetId.
2. **Determinism:** same source bytes, dependencies, recipe/tool versions, target profile and declared environment should yield equivalent output; bytewise identity must be explicitly proven per codec/compiler/platform. Nondeterministic encoders require clear stable-equivalence conditions or must be excluded from reproducible-release mode.
3. **No unverified activation:** staged data becomes visible only after chunk/manifest validation, compatibility checks and recoverable commit. A hash checks *content integrity* and does **not** establish publisher authenticity.
4. **Bounded load:** streaming queue enforces CPU jobs, disk/network I/O, RAM decompression and GPU upload/VRAM budgets; priorities are hints with starvation prevention, backpressure and cancellation.
5. **Safe patch:** updating a project/app creates an immutable candidate generation and performs an atomic pointer/version switch where supported, plus journal/reconcile and rollback or roll-forward. Do not promise atomic filesystem+SQLite+remote object storage transactions.

## Dependency and ownership boundaries
- DATA-01 VFS: scoped mounts, handle-based path security, staged writes, verified read and recoverable operations. Never unsafe archive extraction to absolute OS paths.
- DATA-02: durable AssetId, revision, graph and provenance. Cooker snapshots dependencies and emits derived cache receipts; source registry remains authoritative.
- DATA-03: validated mesh/texture/audio/animation intermediary and importer receipt; DATA-05 must not silently reinterpret original importer options.
- DATA-04: editable scene, serialized schema, semantic revision; DATA-05 outputs **runtime** representation as derived artifact and never changes authoring data.
- CORE-02/03/06: memory allocations, concurrency cancellation, redacted metrics/profiling and build correlation.
- GFX, AUD, TWO, WORLD: consumers request assets, mips/LOD, streaming priority and upload scheduling. Graphics/physics behavior is **not** implemented by the cooker.
- PLAT-03: Web loader/network adapter; PLAT-05: game export/installer/distribution and release signing policy. DATA-05 defines content layout and verify semantics, not deployment infrastructure or OS installer.
- EDIT/AI: same typed semantic cook inspection/preview/commit kernel; authorization checked, no unrestricted local commands/MCP writes.

## Target profiles, tiered outputs
Target profile must include OS/architecture/runtime ABI, graphics API capability set, texture block formats, shader binary/cache compatibility, available audio codecs, storage/memory tier and browser feature profile. Distinguish **capability** from OS label: not every Windows GPU supports the same BC/ASTC/ETC family or shader model. Web defaults to explicitly negotiated capabilities/fallback, not native codec assumptions.

Proposed transforms:
- Mesh: validate geometry/skin/morph identity, configure quantization error bounds, meshoptimizer-based vertex/index processing or meshlets **only if compatible with consumers**; HLOD generation belongs WORLD/GFX policy, while packaging versions is DATA-05.
- Texture: preserve color profile, alpha, normal map and mip semantics; package target-compatible compressed format or universal KTX2/Basis payload and legal fallback; no silent fidelity or precision loss. Texture cooking must carry format/version and GPU quality golden rubric.
- Audio: package normalized source metadata, sample layouts and selected runtime codec with channel/error tolerance; spatial mixing belongs AUD. No double-compress already encoded audio by default.
- Scene: compiled runtime representation candidate (FlatBuffers, Protobuf, Cap'n Proto or bounded owned chunk format), with explicit schema and endian/ABI rules; no raw arbitrary C++ object dumps.
- Shader: optional precompiled/cache output with driver/compiler/feature fingerprint and fallback-to-validated source/IR where permitted; shader compiler and variant policy belong GFX; do not ship a GPU-driver-specific cache as universal artifact.
- 2D/2.5D: texture atlases, animation sprite tables and layered scene parts; stable AssetId/subasset references preserved, order semantics never inferred from chunk order.

## Pipeline / provenance
```text
Authorized inspect/preview (Editor/CLI/MCP)
  -> Freeze DATA-02 dependency graph and DATA-04 scene revisions
  -> Validate DATA-03 receipts + provenance + target capability profile
  -> Resolve cook DAG, check cycles and version/policy compatibility
  -> Plan codec choices, quality warnings, budgets, and expected changes
  -> Reuse verified immutable cached artifacts or run bounded transformation jobs
  -> Verify semantic/golden tolerances, chunks, lengths and digest algorithms
  -> Group by startup/residency/access profile; assign immutable chunk references
  -> Stage bundle payload, index, manifest and signed-policy metadata (signature only if authorized)
  -> Readback verify manifests and chunk digests; write transaction intent
  -> Publish candidate generation / reconcile DATA-02 derived references
  -> Switch active generation with recovery receipt; retain previous valid generation
```
A cook operation does **not** change authoritative imported or authored revisions. Cache keys include all semantic inputs, pipeline/codec versions, options, platform capabilities and target policy; omit secret/absolute host paths and wall-clock unless explicitly part of the semantic algorithm. For shared cache, validate privacy/project isolation; cross-tenant dedup is opt-in only after rights and disclosure analysis.

## Proposed versioned chunk / bundle layout
- **Content manifest** `BundleManifestV1`: format/version, project/release IDs, generation ID, target profile, minimum loader version, recipe/toolchain fingerprint, content/hash algorithm and canonicalization rules, signed/trust policy marker, dependency snapshot, list of immutable bundle/chunk descriptors, preload groups, required feature flags, verified counters and total byte limits.
- **Chunk descriptor** `ChunkDescriptorV1`: stable hash of stored bytes (algorithm tagged), decoded length, compressed length, file/bundle ID, checked byte offset/alignment, codec and decoder minimum version, optional dictionary digest, target capability and explicit *decoded* digest where warranted. No blind trust of declared sizes.
- **Artifact index**: AssetId+revision+subasset+target variant -> ordered chunk references, codec semantics, logical data slices and residency hint. Stable entity ID mapping is from DATA-04 and can never be overwritten by index ordering.
- **Bundle**: read-only deterministic header, index/footer scheme selected after exact loader tests. Random-access offsets checked with overflow-safe arithmetic, no aliasing or overlapping unless explicitly supported and verified. Prefer immutable bundle blobs over mutable in-place patching.
- **Integrity vs authenticity:** independent digest verification ensures stored bits match a trusted expected digest; if manifest can originate externally, require secure distribution and pinned/trusted verification keys/signatures **under a future PLAT-05 trust-policy ADR**. No cryptographic keys or release signing are provisioned in this research.
- **Merkle tree** optional optimization for partial authenticated verification, not a substitute for signed trusted root nor an automatic design choice; compare to simple chunk digest manifest.

## Progressive streaming and backpressure
Each `StreamRequestV1` specifies consumer, AssetId variant, group, deadline/priority class, optional cancel token, allowed memory ceilings and expected generation ID. Proposed scheduler: required startup -> current-visible -> imminent-world -> optional prefetched. Prevent starvation using bounded queues and fair-share quotas; avoid prefetch killing critical IO.

Per chunk state: MISSING -> REQUESTED -> FETCHING -> STORED_UNVERIFIED -> VERIFIED_STORED -> DECOMPRESSING -> READY_CPU -> UPLOAD_PENDING -> READY_CONSUMER, with failures -> RETRY_BOUNDED / FAILED; `READY_CONSUMER` only after decoder and device resource validated. GPU memory ownership belongs GFX, so DATA-05 issues size/priority advice and receives completion callbacks rather than claiming its own VRAM allocator.

Cache eviction must honor pinned/in-flight/current-generation references, size/age policy, and never delete the only prior-good rollback assets. Cold boot, low RAM and offline Web fallback explicitly tested. Request coalescing, prioritization and read-ahead are candidate optimizations; count wasted prefetch bytes and dropped frames, not only compression ratio.

### Browser delivery
HTTP byte ranges are **optional** according to [RFC 9110](https://www.rfc-editor.org/rfc/rfc9110.html). Web loader must tolerate 206 partial, 200 full-body fallback, 416, stale ETag/If-Range and CDN/proxy byte transformation; range offsets refer to the negotiated representation, not blindly to original uncompressed file. Verify CORS, Cache-Control/service worker version pin, reload races, offline quota, storage eviction and digest authenticity. WebAssembly module compilation streaming is separate from **asset bundle** streaming; do not conflate the two.

## Incremental patching & recovery
1. Compare two **trusted** compatible immutable manifests (base and desired target); prepare a preview listing new/reused/removed chunk digests, estimated bytes and target compatibility.
2. Reuse *verified* unchanged chunks with content-addressed storage. Stage only new chunks and verified optional binary deltas when A/B data proves their benefit over whole-chunk reuse.
3. Check storage, transfer, CPU/RAM quotas before starting; download/write temporary objects with checksums, bounded retries and resume only on strong validators.
4. Verify candidate generation completely, including decompressed semantic capability and required startup assets; record commit intent and prior-good generation.
5. Activate through pointer/current-generation switch and reconciled manifest under DATA-01. On crash during stage/commit/reconcile, reopen prior valid generation or finish verified new one deterministically.
6. Retention/GC runs only after activation proof and rollback window; no destructive in-place patching. If authentication/freshness cannot be established for a remote update, fail closed rather than activate.

Avoid rollback to a known vulnerable manifest: distinguish user recovery from security anti-rollback/freshness policy, which requires future authorized signing/trust and release governance. Not a license to auto-install unsigned updates.

## Threat model
Hostile asset or manifest: crafted offset overflow/overlap, duplicate chunk index, hash length/type confusion, attacker-controlled dictionary, recursive references/cycles, bomb ratio/time, oversized dimensions, invalid codec output, path traversal and symlinks, tampered CDN byte ranges, response content-encoding mismatch, zip-slip extraction, unbounded cache or concurrency, malicious plugin upload, stale target profile, downgrade attacks and TOCTOU.

- All bundle mounts are read-only by default through capability-safe DATA-01 VFS. No extraction of untrusted paths or arbitrary URI fetch from manifest.
- Bound encoded and decoded byte counts, recursion, object/dependency graph size, chunk count, concurrent jobs, retries, CPU time and peak resident RAM; audit platform-specific isolation of decoders.
- Validate strong digest after transfer; validate content semantics after decompress. Avoid allocating based solely on untrusted decoded-size metadata. Verify signer/trust externally when required.
- MCP command kernel grants bounded `bundle.inspect`, `cook.plan`, `cook.preview`, `bundle.verify` and separately privileged commits; never accept host path, shell, arbitrary compiler flags/plugins, network endpoint or signing key via assistant-supplied parameters.
- Provenance/license: a source asset being importable does **not** prove rights to redistribute a cooked derivative. Include per-asset/source restriction flags and third-party notices. Explicitly review mixed-license KTX software/non-open ETC decoder exclusion.

## R&D hypothesis: Stormline Adaptive Streaming Graph (SASG)
An optional derived prediction map from DATA-02 dependencies, scene visibility hints, startup states and observed latency could improve warmup without modifying authoritative graph. **Prove-or-drop** versus simple dependency priority + bounded LRU/clock cache and fixed prefetch. Measure time-to-first-useful-scene, p95/p99 stalls, CPU/IO/VRAM and wasted bytes on the same licensed scenes and weak-device profiles. Never claim ML inference is necessary or that SASG already exists. Algorithm cannot bypass privacy or memory quotas.

## Future proof gates before #28
Approved engine release class and target matrix, selected exact pinned recipe/codec versions, platform decoders and license/SBOM, format/manifest/patch schema, source inventory and CI commands, robust low-memory/corruption fixtures, exact numeric budgets/benchmarks, DATA-03/04 implementation predecessors merged, signing trust path for remote distribution, confirmed non-destructive rollback, fresh base SHA and *actual* SHA-256 Context Lock. Engine execution currently remains BLOCKED.

See [technology matrix](../research/data-05-cooking-technology-matrix.md), [ADR-0013](../adr/0013-data-05-cooking-policy.md), [API](../contracts/data-05-cook-bundle-api.md), and [future tests](../testing/data-05-acceptance-matrix.md).
