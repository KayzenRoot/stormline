# DATA-05 — Asset Cooking, Compression, Bundle/Patch Technology Matrix

**WO:** NLE-P00-WO-002-DATA-05 | **Issue:** #120 | **State:** PROPOSED / DOCS ONLY.
Candidate descriptions are a **research shortlist**, not approved versions, selected implementations or measured benchmarks.

| Candidate / mechanism | License and official source | Candidate role / benefit | Selection gate / limitation |
|---|---|---|---|
| **Zstandard / libzstd** | [upstream dual BSD OR GPLv2](https://github.com/meta/zstd) | general lossless chunk compression / dictionary | choose **documented BSD terms** if distributed in permissive engine, exact tag and SBOM; measure CPU, cold start, RSS and tiny chunks |
| **LZ4 / lib** | [library BSD-2-Clause; CLI/utilities GPL-2.0-or-later](https://github.com/lz4/lz4/blob/dev/LICENSE) | candidate low-latency decode / streaming | avoid copying CLI GPL program into runtime by assumption; compare realistic load paths and memory |
| **Brotli** | [upstream MIT](https://github.com/google/brotli) | HTTP/Web-oriented text/metadata compression | stream lacks native checksum/uncompressed length; bundle manifest must provide integrity & bounds; compare vs HTTP content coding and double compression |
| **meshoptimizer** | [upstream MIT](https://github.com/zeux/meshoptimizer) | vertex/index/meshlet optimization/codec | index/vertex codec versions and quantization/triangle-order fidelity, decoder support; not universal Web GPU functionality |
| **KTX2** | [Khronos spec](https://registry.khronos.org/KTX/specs/2.0/ktxspec.v2.html) | texture container with mip/stream and Basis integration | compatible GPU texture targets vary; metadata/color/alpha, mips and low-memory loader evidence |
| **Basis Universal** | [upstream Apache-2.0 primarily; audit transitive](https://github.com/BinomialLLC/basis_universal) | universal texture transcode source | encode/decode/quality, hardware capabilities, package notices and vector tests; no guaranteed best format |
| **KTX-Software** | [mixed file licenses incl optional non-open ETC decoder](https://github.com/KhronosGroup/KTX-Software/blob/main/LICENSE.md) | optional KTX/Basis tooling | no non-open `etcdec`/feature default; exact file-level license and build-generated SBOM before using |
| **FlatBuffers** | [upstream Apache-2.0](https://github.com/google/flatbuffers) | candidate binary scene/runtime index | schema evolution/codegen and read guards; DATA-04 authored scene remains authority |
| **Protocol Buffers** | [upstream BSD-3-Clause](https://github.com/protocolbuffers/protobuf) | binary metadata schema candidate | generated tooling/runtime footprint, exact tags and unknown-field rules |
| **Cap'n Proto** | [upstream MIT](https://github.com/capnproto/capnproto) | binary schema candidate | security/size/ABI and portable build proof, random-access integration |
| **Owned chunked format** | proprietary code license remains OPEN | targeted mmap/seek layout / versioning | heavy maintenance, endian, fuzzing, migration, corrupted-offset risk; prefer simplest validated schema |
| **HTTP Range / ETag** | [RFC 9110](https://www.rfc-editor.org/rfc/rfc9110.html) | partial network bytes/resumable chunk loads | Range is OPTIONAL; 206/200/416, response encoding, CDN validators, fallback and CORS test |
| **Content-addressed patch** | own immutable manifest/chunk design | reuse unchanged verified bytes and safe rollback | encrypted/compressed variant digest, chunk granularity vs dedup; verified target generation before activation |
| **Merkle manifest** | design pattern, implementation TBD | partial proof candidate | trusted root/signing, overhead, algorithm agility, replay/anti-rollback; not automatically required |
| **Binary deltas (VCDIFF/bsdiff)** | exact implementation & license TBD | smaller patches for large changed chunks | CPU/RAM/bomb, copying legal terms, application complexity; benchmark against chunk-level reuse before choosing |
| **DirectStorage** | [Microsoft Docs](https://learn.microsoft.com/en-us/gaming/gdk/docs/features/common/storage/directstorage) | optional Windows-specific fast I/O adapter | not a cross-platform required dependency; runtime/GPU/driver capability fallback and actual measurements |
| **SASG original R&D** | project hypothesis, NOT implemented | adapt dependency-aware prefetch | compare to static priority/LRU; memory, time-to-play, stalls, wasted prefetch and quality |

## Shortlist policy
- Prefer generic chunks with **zstd or LZ4** chosen by actual codec+scene targets; default library version is **not** approved by this text. Avoid double-compressing BC/ASTC/ETC textures and already compressed audio unless a benchmark shows benefit.
- meshoptimizer useful for geometry while preserving authored subasset IDs; identify lossy quantization steps separately from lossless codec and profile meshlet/LOD order semantics.
- KTX2/Basis texture source or distribution is conditional on target GPU support and per-file licensing gate, particularly KTX-Software mixed licensing and optional non-open-source ETC decoding. The KTX2 spec explicitly supports mip-level distribution.
- Separate runtime binary scene index from DATA-04 authored JSON. Use own typed, versioned interface; select FlatBuffers/Protobuf/Cap'n Proto only after actual codegen/footprint/forward-compat comparisons.
- Native storage and browser HTTP have different failure paths; HTTP Range is not guaranteed, and a `Range` response can fall back to 200. No CDN/host selected or required.
- Digest algorithm proposals: SHA-256 interoperable baseline vs BLAKE3 (performance/dedup candidate), with algorithm-tagged manifests. **A digest by itself never authenticates remote publisher.** Trust signing/anti-rollback policy belongs controlled future export/distribution.
- Compression candidate legal precision: zstd reference implementation is dual BSD **or** GPLv2; LZ4 library BSD-2-Clause but CLI GPL. Check exact tag and compiled files, not just GitHub top-level badge.
- Optional proprietary SASG does not own an authoritative graph; compare with plain cached manifests+static priorities and drop if not objectively beneficial.

## Proposed comparison scorecard (not measured)
- Correctness/reproducibility and target feature parity: 25%
- Integrity/rollback/malicious bundle robustness: 25%
- Low-spec cold start, p95/p99 load latency and memory: 20%
- Patch sizes, storage/cache and Web fallback: 15%
- Licensing/SBOM/codegen and cross-platform maintenance: 10%
- Implementation simplicity/operability: 5%

No numeric library scores or winner until exact tag, compiler, dataset rights, target OS+hardware, low-memory budgets, golden outputs and real runs.

## Official source URLs verified in this research
- Zstandard: https://github.com/meta/zstd
- LZ4 licenses: https://github.com/lz4/lz4/blob/dev/LICENSE
- Brotli: https://github.com/google/brotli
- meshoptimizer: https://github.com/zeux/meshoptimizer
- KTX2: https://registry.khronos.org/KTX/specs/2.0/ktxspec.v2.html
- KTX-Software: https://github.com/KhronosGroup/KTX-Software/blob/main/LICENSE.md
- Basis Universal: https://github.com/BinomialLLC/basis_universal
- RFC 9110: https://www.rfc-editor.org/rfc/rfc9110.html

**NO** codec, bundle generator, runtime loader, patcher, signing service or benchmark is implemented.
