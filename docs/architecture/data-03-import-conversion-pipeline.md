# DATA-03 — Secure Import, Conversion and Idempotent Reimport

**WO:** `NLE-P00-WO-002-DATA-03` | **Research issue:** #114 | **Future implementation:** #26  
**Status:** RESEARCH PROPOSED / NOT IMPLEMENTED | **Base main:** `b477dbecacc733a251666644ac05173f9390d159`  
**Risk:** LOW for documentation; **ELEVATED** for untrusted decoders, format libraries, I/O and project integrity.

## Mission and guiding invariants

Stormline must accept professional 2D sprites, 3D scenes and meshes, rigs, animations, material/texture sources and audio without silently degrading their fidelity, bypassing the workspace sandbox, corrupting user edits, losing stable references or forcing cloud services. The import layer produces versioned, validated **intermediate artifacts**; it does **not** own the final renderer, runtime animation system, audio mixer, global scene schema or target-specific cooked bundles.

1. **Same verified input bytes + normalized options + importer/plugin version + target policy + declared dependencies => equivalent semantic result.** Byte-for-byte reproducibility is only promised for formats and toolchains where proven. Source modification, nondeterministic codecs/parallel reductions and platform floating-point differences require explicit tolerance or `NON_REPRODUCIBLE` report.
2. **No partial publication:** output is staged inside a restricted workspace, validated, then associated with DATA-02 revision/receipts through an explicitly recoverable operation; DATA-01 staged writes and SQLite are **not** an atomic combined transaction.
3. **Stable identity:** DATA-02 `AssetId` survives move/rename and intended reimport; derived subassets require durable, importer-qualified stable mapping or explicitly unresolved conflicts. Reimport must never overwrite user-authored overrides without conflict/merge policy.
4. **Secure by default:** no arbitrary host filesystem/network/subprocess access for import plugins; external glTF URIs resolved only through DATA-01 VFS, bounded to project namespace and quotas.
5. **Low cost to disable and operate:** engine/servers need only validated compiled artifacts for shipping; expensive decoders belong Editor/asset-build target where justified, not mandatory client runtime.
6. **Editor/CLI/MCP parity:** a common semantic command kernel handles `Inspect -> Preview -> Import/Stage -> Validate -> Commit`, with scoped capabilities, audit and cancellation.

## Ownership and dependency direction

- **CORE-01:** OS path/loader APIs, sandbox process capabilities when available, native target differences.
- **CORE-02:** pooled scratch allocation and bounded decompression/parse memory.
- **CORE-03:** concurrent task graph, cancellation/backpressure and latency budget. DATA-03 never schedules more than job policy allows.
- **CORE-05:** proposed coordinate, precision, meters/radians, right-handed Y-up policy, vector transformations and conversion errors. No implicit reinterpretation of source handedness/units.
- **CORE-06:** structured, redacted diagnostics, importer timing and build SHA.
- **DATA-01:** validated virtual paths, safe opens, read-only mounts, staged writes and quota. It alone mediates host storage.
- **DATA-02:** `AssetId`, revisions, dependencies, metadata/provenance, transaction/recovery contract. DATA-03 produces receipts/updates; it does not choose identity from the file name/content hash.
- **DATA-04:** canonical serialization of scenes and metadata; importer-specific parsed AST/intermediate conversion is DATA-03, not permanent scene format.
- **DATA-05:** target cooking/texture compression/streaming/bundle patching. Import stage may produce intermediate texture data, not automatically final GPU formats.
- **GFX/TWO/AUD/WORLD:** consume semantically typed artifact descriptors. Rendering, mip streaming and sound spatialization belong to their respective modules.
- **AI/EDIT:** interfaces consume typed import capabilities. MCP cannot launch arbitrary binary or access raw host paths.

## Pipeline architecture and stages

```text
Authorized semantic command (Editor/CLI/MCP)
  -> Validate project scope / VFS capability / request quota
  -> Inspect bounded header + sniff actual format (not extension alone)
  -> Resolve declared dependencies in scoped DATA-01 namespace
  -> Select pinned importer and declared feature/extensions policy
  -> Parse untrusted source with strict limits / optional isolated worker
  -> Validate semantic geometry/images/audio/animation and legal origin hints
  -> Convert to canonical typed intermediate artifact(s)
  -> Assign/retain AssetId and stable subasset mapping via DATA-02
  -> Generate manifest/receipt, preview diffs, preserve user overrides
  -> Stage outputs through DATA-01; intent + reconcile DATA-02 state
  -> Commit or recover, invalidate dependents through DATA-02
  -> Emit bounded timings/errors to CORE-06, publish result for Editor/CLI/MCP
```

Stages 1–8 must have **no visible mutation** of canonical project state. Stage/commit are explicit, idempotently recoverable with operation ID. A crash can leave a journal/recovery-required state, never an unreported half-import.

## Logical types / contracts (proposed, not native ABI)

| Type | Required fields and semantics | Failure/security |
|---|---|---|
| `ImporterIdV1` | vendor/name/version, supported formats/features, manifest digest | pin version, explicit third-party notice |
| `ImportRequestV1` | project, source `VfsPath`, expected `AssetId?`, source revision?, profile, options, operation ID, caller scope | no host path; caller capability |
| `ImportOptionsV1` | conversion schema version, target semantics, scale, axis/handedness, color profile, quality policy | type-checked; reject ambiguous/default-breaking options |
| `ImportCapabilityV1` | decoder, supported extensions and limits, memory/CPU/disk budgets, isolation mode | no arbitrary filesystem/network |
| `SourceFingerprintV1` | algorithm-tagged digest, size, declared dependency digests, importer config hash | SHA/hash is integrity hint, not publisher identity |
| `ImportPlanV1` | source summary, output types, costs bounds, dependency/permission review and preview hash | no writes in dry run; bounded response |
| `ImportArtifactV1` | type, subasset key, format/schema revision, digest, size, conversion record, validation status | never publish partial/truncated artifacts |
| `ImportReceiptV1` | operation ID, AssetId, importer version, source digest, options digest, dependency versions, artifacts, warning/error summary, commit sequence | reproducible, redacted, versioned, retry-safe |
| `ReimportPlanV1` | previous receipt, changed source/options, stable mappings, user overrides, 3-way conflict diagnostics | do not overwrite authored edits silently |
| `ImportErrorV1` | stable error code, stage, retryability, limited sanitized details | no absolute file path, credentials or raw file content |

**Errors:** `UNSUPPORTED_FORMAT`, `REQUIRED_EXTENSION_MISSING`, `VERSION_UNSUPPORTED`, `SOURCE_MISSING`, `DEPENDENCY_UNRESOLVED`, `CAPABILITY_DENIED`, `RESOURCE_LIMIT`, `DECOMPRESSION_BOMB`, `MALFORMED_ASSET`, `OUT_OF_BOUNDS`, `INVALID_TRANSFORM`, `COLORSPACE_AMBIGUOUS`, `DECODE_FAILURE`, `ID_CONFLICT`, `SUBASSET_REMAP_REQUIRED`, `OVERRIDE_CONFLICT`, `NON_REPRODUCIBLE`, `SOURCE_CHANGED`, `STALE_REVISION`, `CANCELLED`, `COMMIT_FAILED`, `RECOVERY_REQUIRED`, `UNKNOWN`.

## Formats and feature policy

### 3D: glTF 2.0 / GLB baseline
Khronos [glTF 2.0 specification](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html) and extensions registry define semantics. Candidate loaders:
- **fastgltf** MIT (modern C++20, efficient parsing and glTF features), subject to pinned release, unsupported feature mapping, A/B performance and fuzzing.
- **cgltf** MIT (small C99 single-file baseline), good portability/footprint comparator; extension support may need external decoders.
- **Assimp** BSD-3-Clause-based (legacy/many-file-format adapter), conditional due to dependency/importer complexity and per-format fidelity gaps.
- **OpenUSD** optional high-end scene exchange separate adapter/research target; do not assume USD composition, layering, custom plugins or Hydra are supported by the glTF pipeline. Audit exact distribution and dependency footprint before adding.

**Validation:** bufferView/accessor bounds, sparse accessors, vertex index range, primitive modes, morph target counts, skin joint hierarchy/inverse-bind transforms, animation curves/interpolation, local/world transforms, negative scale/mirror, tangent space, PBR alpha/transmission and texture extension policies. Reject missing **required** extensions unless a spec-compliant fallback is explicitly supported. Unknown optional extensions must be preserved or documented as dropped in the receipt, never silently treated as full fidelity.

**URI rules:** reject `http(s)`, `file:`, absolute paths, `..`, device paths and symlink escapes unless a separately audited fetch mechanism is authorized. Data URIs require explicit bounded decoded-byte quota. Relative buffers/textures must remain inside approved DATA-01 source mount scope.

### Texture / 2D
- Preserve image width/height, pixel aspect, orientation, bit depth, channel count, alpha mode (premultiplied/straight), color-transfer/ICC assumptions and normal map vector semantics.
- Candidate **KTX2/Khronos KTX-Software** for texture containers, **Basis Universal** for cross-GPU transcoding; do not confuse an intermediate import with final platform cooking DATA-05.
- **Critical licensing gate:** KTX-Software is mixed-license; official license notes a non-open-source Ericsson-licensed ETC decoder in an optional feature. Must **exclude or explicitly authorize** this component (`LIBKTX_FEATURE_ETC_UNPACK=NO` where applicable), verify build SBOM/REUSE file license and exact tag before packaging. Do not label the entire repo Apache-2.0.
- PNG/JPEG/EXR/HDR and sprite atlas semantics are candidate ingestion targets, with individual decoder/license/security reviews. Color/tangent conversion passes visual golden comparison with tolerances.
- Animated sprites/tilesets require deterministic frame metadata and subasset mapping, without DATA-03 taking ownership of TWO runtime.

### Audio
- Candidate PCM/WAV and optional Ogg/Vorbis/FLAC/Opus source decoding (format-by-format codecs, license, patent/security review).
- Conversion must preserve sample rate, channel mask/layout, sample depth, loop markers where supported and clipping/loudness evidence; define channel-downmix policy and bit-exact vs tolerance-based acceptance.
- Output is validated PCM/audio intermediate metadata; runtime mixing/streaming belongs AUD and final target encoding belongs DATA-05.

### Animation
- Preserve clips, named/joint-keyed subassets, skeleton hierarchy, rest transforms, coordinate convention, keyframe interpolation and morph curves. Retargeting policy belongs GAME/SIM or a future special module; importer may report needs/unsupported.
- Reimport should preserve stable skeleton/animation subasset references by deterministic mapped keys and change-impact report; ambiguous remaps become explicit conflicts.

## Import receipt and reproducibility

Candidate normalized cache key: `Hash(typed source digests + dependency snapshots + importer binary/build version + canonical options + conversion policy + format extension capabilities)`. Include algorithm/encoding version. Filename, wall-clock and raw host paths must not be hidden semantic cache keys.

**Idempotence:** identical verified source and receipt tuple yields equivalent accepted semantic output; store an output manifest and compare it. Cache-hit result can reattach same artifact to same AssetId revision. A codec that produces nondeterministic bytes must have recorded tolerances and report unsupported strict-bitwise contract rather than falsely claim exact reproducibility.

**Reimport overrides:** separate source-owned fields from user-authored fields. Use versioned import base vs new import candidate and user edits in three-way merge. If conflicting edits cannot merge safely, stage diff and require explicit user approval. Retain old asset revision and journal until resolved. Never silently clear a custom material slot, animation marker or user override.

## Security and safety

- **Untrusted parsing:** prefer memory/time capped isolated worker for risky libraries with possible process sandbox; evaluate native OS sandboxes and safe IPC, with fail-closed fallback where strong isolation unavailable. Sandboxing is not achieved by a child process alone.
- **Resource accounting:** cumulative parsed bytes (including external buffer loads), decompressed bytes/ratio, object/vertex/face/joint/clip/texture counts, recursion depth, command time and memory. Integer multiply/add checked before allocation.
- **No untrusted execution:** imports never run embedded scripts, macros, shaders or arbitrary user commands; no network fetch or plugin URL resolution.
- **Path security:** source/dependencies and staged outputs all go through DATA-01 capability-safe VFS. No raw host paths or unrestricted import source in MCP.
- **Content safety:** schema validation, fuzzer corpus/regressions, dependency CVEs, malformed files, NaN/Inf transform/attribute handling, malicious extensions and cycles.
- **Project data integrity:** staging/recovery, disk-full, cancel, duplicate AssetId/subasset mismatch and explicit rollback/roll-forward.
- **Supply-chain/licensing:** package notices, codegen provenance, restrictive codecs and **source asset rights** must be tracked separately (importability does not confer redistribution rights).

## Proposed innovation: Stormline Import Receipt Graph (SIRG)

Research hypothesis: deterministic, explainable per-source graph connecting `ImportReceipt`, toolchain/options, dependency digests, stable subassets and downstream invalidation through DATA-02. It could enable AI to ask why a reimport changed a mesh without exposing private prompts.

**Prove-or-drop** against plain versioned receipts + SQL dependency edges and current DATA-02 provenance. Do not build a second conflicting provenance graph; SIRG should be an optional derived view if measurable benefit is established, not a second authority.

## Cross-platform and performance test obligations

| Future proof | Scenarios and observable outcome |
|---|---|
| GLB/glTF geometry | mesh primitives, sparse accessors, PBR variants, skin/morph, animation, extension required/optional handling |
| 2D and texture | sRGB/linear, ICC/EXIF/orientation, alpha, normal map, KTX2/Basis, texture golden images |
| Audio | PCM quantization, channel layouts, loops, duration and controlled decode tolerances |
| Import idempotence | reimport unchanged source/options twice yields semantic manifest equivalence and same AssetId |
| User overrides | edit derived material/clip -> reimport -> preserve or conflict preview; no silent loss |
| Subasset stability | renamed/moved parent, inserted joints/meshes or changed importer version reports stable or explicit remap |
| Malicious input | nested/huge buffers/URI escapes, invalid sparse offsets, corrupt compressed payload, overflow and timeout |
| Crash/fault injection | parse/convert/stage/intent/commit interruption, disk full, cancel and recovery without published partial revision |
| CI/build/target | Windows x64, Linux x64, macOS arm64, Intel feasibility; headless; Web fallback/adapter |
| Scale and performance | p50/p95/p99 import latency, total bytes, peak RSS, CPU; 1k small assets + large 3D scenes |
| MCP security | scoped command preview, no arbitrary paths/network/SQL/process, bounded output and redaction |

Benchmark evidence requires precise SHA, importer version, compiler flags, hardware/OS, dataset/license fixture, seed, input/output digests, sample count, format/extension matrix, peak RAM and failure logs. GitHub CI can't prove visual fidelity/driver performance on real gaming hardware.

## Proposed readiness gates

Before upgrading #26 to EXECUTOR_READY: freeze exact format features/extensions and fallback matrix, pinned library source/license/SBOM, API and intermediate format, semantic equivalence tolerances, specific source paths, test fixtures/hardware/CI commands, privilege isolation, DATA-01/02 approved implementation contracts, release class, risk level and fresh SHA-256 Context Lock. **Current approval of research is not implementation approval.**

See [matrix](../research/data-03-importer-technology-matrix.md), [API contract](../contracts/data-03-import-api.md), [test matrix](../testing/data-03-acceptance-matrix.md), [ADR-0011](../adr/0011-data-03-import-policy.md).
