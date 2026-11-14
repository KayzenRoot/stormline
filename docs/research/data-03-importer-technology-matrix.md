# DATA-03 — Importers, Codecs, Formats and Licensing Research

**WO:** NLE-P00-WO-002-DATA-03 | **Research issue:** #114 | **Status:** PROPOSED / DOCS ONLY

| Candidate | Purpose | License/provenance | Practical benefit | Risk and selection gate |
|---|---|---|---|---|
| Khronos glTF 2.0/GLB | 3D baseline transfer standard | specification/extension policy, not implementation library | meshes, PBR materials, skins, morphs, animation | validate required extensions, coordinate/material semantics |
| **fastgltf** | high-performance C++20 glTF parser | **MIT** in upstream `LICENSE.md` | modern C++20 accessors/optional SIMD | benchmark vs cgltf, safety/fuzz, API and extension coverage; exact tag |
| **cgltf** | lightweight C99 glTF 2.0 parser/writer | **MIT** | compact zero/low-dependency baseline | extra decoders for extension features; parser bounds tests |
| **Assimp** | multi-format legacy 3D importer | **BSD-3-Clause-based**; contributed data/third-party notices vary | many formats in one adapter | larger format/decoder surface; opt-in only when fidelity and demand proven |
| **OpenUSD** | complex scene/composition exchange | inspect exact upstream LICENSE and third-party notices | high-end interchange workflows | significant ecosystem integration, version/ABI/SDK size; optional separate adapter |
| **KTX-Software** | KTX2 texture load/encode/decode | mostly **Apache-2.0**, **MIXED** per official license; optional Ericsson/etcdec proprietary case | GPU-oriented texture payload/container | non-open-source etcdec feature must be omitted or expressly cleared; run REUSE SBOM |
| **Basis Universal** | texture supercompression/transcoding | primary encoder/transcoder **Apache-2.0**, third-party notices | compressed GPU texture workflows | encoder footprint, GPU format/quality and source rights; check exact target build |
| PNG/JPEG decode candidates | 2D/sprite/color input | TBD per exact lib; no dependency selected | broad content usability | dimensions/ICC/EXIF/alpha and malformed image risk |
| OpenEXR/HDR decode candidates | professional HDR and 3D textures | TBD per exact lib/tag | HDR lighting/texture workflows | memory/bomb safety, linear color and high-bit-depth cost |
| PCM/WAV, FLAC, Vorbis, Opus candidates | audio source import and validated intermediate | exact codec licenses/patents TBD | independent runtime sound sources | multichannel layout, loops, codec vulnerabilities, streaming separation |
| Dedicated import worker | untrusted parser isolation (platform-dependent) | own interface and platform APIs | contain decoder crash/resource use | OS sandboxing/security test; child process alone isn't an isolation guarantee |
| SIRG (proprietary hypothesis) | importer receipts + explainable invalidation | not implemented | potential deterministic reimport and AI reason diagnostics | A/B vs simple receipt + DATA-02 graph, prove-or-drop |

## Proposed selection sequence, not a final stack
1. Define **glTF 2.0** conformance baseline and semantic intermediate format independent of parsers. Evaluate **fastgltf vs cgltf** (MIT) on the same fixture corpus, sanitizers and security checks. **No winner preselected**.
2. Keep Assimp behind an opt-in legacy format adapter if commercial need/fidelity and dependency surface justify it. Don't automatically compile all decoders into shipping runtimes.
3. Treat KTX2 as *source/container support* and Basis Universal as a *codec/transcoding option*, while final per-platform compression and runtime cooked bundles belong DATA-05.
4. KTX-Software licensing is **not uniformly Apache-2.0**: its own upstream license calls out an optional **non-open-source ETC decoder** (`etcdec`), requiring explicit build exclusion or separate approval. A purely free/open distribution must validate SBOM and build configuration, not just repository root SPDX.
5. OpenUSD advanced pipeline is an OPTIONAL/IMPORTANT candidate pending architecture, license, resource and interoperability evidence, not a prerequisite for glTF.
6. Audio and HDR decoders need an individual license/SBOM/CVE gate; avoid assuming codec legal terms by format name.
7. A proprietary source/receipt graph must not duplicate DATA-02 authoritative dependencies/provenance or claim novel speedups absent tested evidence.

## Weighted evaluation (proposed)
- Semantic fidelity (meshes/UV/skin/material/colorspace/audio): **25%**
- Parsing security and isolation/fuzz evidence: **25%**
- Reimport identity, override merge and recovery correctness: **20%**
- CPU p95/p99, peak RAM and I/O on modest hardware: **15%**
- License/SBOM/maintenance, distribution compliance: **10%**
- Toolchain simplicity, Web/headless interop: **5%**

Do not insert subjective 1–10 scores until comparable test fixtures, exact pinned versions, hardware and real outputs exist. Browser and macOS support must be verified, not inferred from license or Windows builds.

## Official sources checked 2026-11-14
- glTF: https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html
- Required glTF extension semantics: https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md
- fastgltf license: https://github.com/spnda/fastgltf/blob/main/LICENSE.md
- fastgltf docs: https://fastgltf.readthedocs.io/latest/
- cgltf and MIT license: https://github.com/jkuhlmann/cgltf
- Assimp license: https://github.com/assimp/assimp
- KTX-Software **mixed licensing and etcdec notice**: https://github.com/KhronosGroup/KTX-Software/blob/main/LICENSE.md
- Basis Universal encoder/transcoder notices: https://github.com/BinomialLLC/basis_universal
- OpenUSD: https://github.com/PixarAnimationStudios/OpenUSD

**All are research candidates. No C++ package, decoder, asset conversion, renderer or measured benchmark is implemented.**
