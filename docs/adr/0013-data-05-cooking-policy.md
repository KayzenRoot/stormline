# ADR-0013 — DATA-05 Portable Cooking, Immutable Bundles and Safe Patches

**Status:** PROPOSED / NOT APPROVED FOR IMPLEMENTATION
**Date:** 2026-11-14 | **WO:** NLE-P00-WO-002-DATA-05 | **Research issue:** #120 | **Future code:** #28 BLOCKED.

## Problem
The future commercial Stormline engine must export 2D/2.5D/3D/Web games with different hardware capabilities, fast first-use experiences, controlled CPU/RAM/VRAM I/O and safe patch distribution. Raw imported scenes are not appropriate executable delivery units; changing game assets must never silently corrupt previous valid installations.

## Proposed decisions
1. Define Stormline-owned typed `TargetProfileV1`, `CookPlan/ReceiptV1`, `BundleManifest/ChunkDescriptorV1`, `StreamRequestV1` and `PatchPlan/ReceiptV1` independent of codec vendor ABI.
2. Keep DATA-02 AssetId and DATA-04 authored scene as **sources of truth**. DATA-05 emits derived target-specific immutable chunks, never edits user-authored scenes or overwrites DATA-03 import receipts.
3. Use capability-negotiated profiles and explicit graceful fallbacks on Windows/Linux/macOS/Web/headless rather than OS-label-only codecs or assumed GPU decompression.
4. Prefer chunked immutable bundle generations with versioned verified content manifest, dependency DAG, explicit codec/dictionary/length/hash/loader minimum versions, and preload groups. Test deterministic output under exact recipes; bytewise claims require fixture proof.
5. Research zstd (dual BSD or GPLv2) and LZ4 (BSD library/GPL CLI) for lossless data, Brotli for relevant Web/metadata cases, meshoptimizer for geometry and KTX2/Basis for texture profiles, with exact tag/file license/SBOM review and decoder boundaries.
6. Distinguish content integrity (cryptographic digest) from publisher authenticity and freshness (future authorized trusted signing and release policy). Fail closed on externally acquired untrusted manifests; no signing keys now.
7. Stream progressively with bounded budgets, fair priority queues, cancel/retry/backpressure, CPU-ready versus GPU-ready distinction, and offline/Web range fallback. Web HTTP Range is optional, not a guaranteed CDN API.
8. Patch with verified unchanged-chunk reuse, copy-on-write candidate generations, staged verification, explicit commit intent and prior-good rollback. No in-place destructive patching or false filesystem+database atomicity.
9. R&D SASG prefetch prediction is **prove-or-drop** against static dependency priority + bounded LRU, with low-end p95/p99 and wasted-prefetch metrics; no second source of truth.
10. No native-only accelerated storage APIs, proprietary codecs, paid cloud, arbitrary MCP compilers or unsafe extraction as mandatory core dependencies.

## Alternatives
- Single massive monolithic archive: simple but whole-file update/long startup and recovery cost; benchmark instead of defaulting.
- Zip-only/untrusted arbitrary extraction: path/zip-bomb and random access concerns; do not expose OS paths.
- DirectStorage or GPU hardware decompression as universal baseline: platform/driver limitation, fallback required.
- Differential binary patch by default: may have better wire savings but more patch CPU/RAM and failure modes; only after measured A/B vs verified chunk reuse.
- Trust SHA-256 alone as authentication or anti-rollback: rejected. Trusted manifest source/signature and replay policy separate.
- Auto-select lowest texture resolution for all targets: rejected quality loss; capability/user quality profiles and golden comparators.
- Unlimited prefetch/uncapped memory: rejected.
- Blob file path as AssetId: violates DATA-02 stable identity.

## Deferred decisions (must be explicitly resolved before code)
Exact chunk size/alignment and hashing/canonicalization, low-memory tier budgets, pinned codec/tag, actual compiler flags, runtime binary scene codec, platform-specific texture formats/shader cache compatibility, encryption/signature/anti-rollback and delivery hosting, bundle extension and ABI, any legal licensing choice of Stormline code.

## Proof obligations
1. Native Windows/Linux/macOS (Apple Silicon) plus Web/headless compatibility matrix with real builds; hardware/driver target fingerprints.
2. KTX2/mesh/2D/audio/scene quality and serializer compatibility golden corpus, target fallback and portability tested.
3. Bytewise deterministic repeated cook or declared nondeterminism proof, linked toolchain/recipe revision and input/content hashes.
4. Malformed/truncated/decompression-bomb, offset overflow, race, stale manifest/ETag, trust-signature denial, MCP unauthorized writes and fuzzy decoding.
5. Bundle verify, streaming progressive load under RAM/VRAM/CPU budgets, startup time p50/p95/p99 and no pathological frame stalls.
6. Resumable range/200 fallback, offline Web, stale browser cache, loss/kill/disk full at every patch stage with last-good restore.
7. Source provenance, SBOM/notices, source license/redistribution rights, reproducible sample corpus.
8. Contract/version freeze, risk approval, exact paths/CI commands, predecessors implemented/approved/merged, SHA-256 Context Lock.

Research approval alone never changes #28 or any of the 80 implementation work orders from BLOCKED.
See [architecture](../architecture/data-05-cooking-streaming-bundles.md), [matrix](../research/data-05-cooking-technology-matrix.md), [contracts](../contracts/data-05-cook-bundle-api.md), [tests](../testing/data-05-acceptance-matrix.md).
