# DATA-03 — Importer Acceptance, Security and Benchmark Matrix

**Research WO:** NLE-P00-WO-002-DATA-03 | **Status:** future tests ONLY, NOT EXECUTED.

| ID | Risk | Future fixture/test | Required objective proof |
|---|---|---|---|
| IMP-001 | STANDARD | Valid glTF2 GLB meshes, UV, normals/tangents, primitive modes | converted geometry matches reference within specified tolerances |
| IMP-002 | ELEVATED | Unknown `extensionsRequired`, known optional PBR | required unsupported extension fails; optional loss reported, never silent |
| IMP-003 | ELEVATED | Sparse accessors, oversized buffer views, invalid indices/stride | reject malformed input with bounded memory/no parser crash |
| IMP-004 | STANDARD | Skeletal animation, joints, inverse-bind, morph targets | stable subasset keys and interpolated pose/reference comparison |
| IMP-005 | STANDARD | 2D PNG/JPEG/EXR and KTX2/Basis, alpha, sRGB/linear, ICC | color/tolerance and orientation/alpha semantics verifiable |
| IMP-006 | STANDARD | WAV PCM and candidate FLAC/Vorbis/Opus multichannel audio | sample/channel/duration/loop metadata, declared error tolerance |
| IMP-007 | ELEVATED | Reimport unchanged source, options and dependency snapshot twice | same AssetId and equivalent manifest, no unwanted revision/no drift |
| IMP-008 | ELEVATED | Reimport changed mesh with edited material override | preserve overrides or emit explicit conflict; never erase user data |
| IMP-009 | ELEVATED | Rename/move source, insert/remove mesh/animation subassets | stable mappings or flagged remap, dependent scene remains correct |
| IMP-010 | ELEVATED | Asset import crash between parse/stage/commit/reconcile | last valid revision visible, deterministic recovery, no half-publish |
| IMP-011 | ELEVATED | Cancel/disk full/worker killed/permission revoked | quota/cancel honored, old asset valid, no leaked handle/orphan temp |
| IMP-012 | ELEVATED | glTF URI traversal, file/http URI, symlink, huge data URI | scoped VFS containment, denied network/host path |
| IMP-013 | ELEVATED | Fuzz corrupt archive/texture/mesh/audio, integer overflows/decompression | sanitized crash/failure paths, bounded RAM/CPU and parser isolation |
| IMP-014 | STANDARD | Cross OS Windows/Linux/macOS and headless server | native import capability/error parity without GPU/display |
| IMP-015 | STANDARD | Web adapter, unsupported formats, fetch scopes | explicit degraded capability; no assumption native decoders work in WASM |
| IMP-016 | STANDARD | p50/p95/p99 import 1k 2D assets and large 3D scenes | reproducible latency/RSS/disk/CPU trace with exact versions/hardware |
| IMP-017 | STANDARD | fastgltf/cgltf/Assimp A/B on common licensed fixture corpus | fidelity, perf, footprint, CVE, license and unsupported feature report |
| IMP-018 | ELEVATED | KTX-Software optional etcdec license feature in build/SBOM | no non-approved non-open-source component included by default |
| IMP-019 | ELEVATED | MCP unauthorized import/options/source path and prompt disclosure | deny privileged request, redact and bound pagination, preview before commit |
| IMP-020 | STANDARD | SIRG vs DATA-02 receipt/dependency table | prove diagnostic/correctness benefit or drop proprietary graph |

## Test protocol before code WOs
- Freeze exact importer tags, artifacts and runner commands; avoid fabricated CLI/API commands before repo contains code.
- Golden fixture licenses/rights must allow tests and distribution; source models from existing commercial games cannot be copied.
- Use format specification conformance assets where redistribution allowed, plus independently generated original source fixtures.
- Store expected material transform/UV/pose/audio outputs with explicit error tolerances and quality/fidelity rubric.
- Use one deterministic seed, exact image/decode tolerance semantics, scene size, stress run count and test asset hashes.
- Include static license/SBOM validation, dependency CVE checks and sanitizers/fuzz regression after chosen implementation.
- CI public free runners do not prove physical Mac/GPU real-world performance; mark such checks PENDING until run on actual supported devices.
- Observe real CI, log exact HEAD/base, false positives, failure fix and rerun for the future Work Order.

**Current research only:** GitHub Action docs validation and 80-WO blocker checks. None of IMP-001..020 have been executed.
