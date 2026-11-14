# ADR-0011 — DATA-03 Secure and Reproducible Import Policy

**Status:** PROPOSED / NOT APPROVED FOR IMPLEMENTATION  
**Date:** 2026-11-14 | **Research WO:** NLE-P00-WO-002-DATA-03 | **Issue:** #114 | **Future code issue:** #26

## Problem
Stormline's manual Editor and AI-native pipelines need robust, safe, fast 2D/2.5D/3D/textures/animation/audio imports with stable references, fidelity and a controlled reimport cycle. Third-party decoder/format code operates on potentially hostile input and may become a commercial distribution liability. DATA-01/02 research is approved as **planning only**, not executable APIs.

## Proposed architecture decisions
1. Own `ImportRequestV1`, `ImportPlanV1`, `ImporterDescriptorV1`, `ImportReceiptV1`, `ImportArtifactV1`, `ReimportPlanV1` and `ImportErrorV1`, independent of specific parser/codec types.
2. Use **glTF 2.0/GLB as the initial 3D conformance baseline**, comparing **fastgltf and cgltf** with equal fixtures. Assimp remains conditional multi-format adapter; OpenUSD remains a separate advanced case. Unsupported `extensionsRequired` cannot be ignored.
3. Validate and normalize explicit source unit, coordinate, color/alpha and animation semantics with CORE-05. Do not silently drop PBR/skin/morph/channel data or claim equivalent without golden tolerance tests.
4. Importers operate under scoped DATA-01 VFS access, bounded URI/decompression/resource limits, with a carefully audited isolated process for high-risk decoders when proven feasible. No arbitrary shell/network from project, plugin or MCP.
5. Generate content-addressed **intermediate artifacts** and a versioned source/options/toolchain/dependency `ImportReceipt`; DATA-02 alone owns AssetId and reference graph, DATA-04 schema and DATA-05 cooking.
6. **Reimport is idempotent at semantic contract level** for the same immutable inputs, options, dependency state and toolchain; bytewise determinism must be tested per codec/platform, not claimed generically.
7. Reimport preserves stable AssetId and subasset mapping where possible, and never silently overwrites user-authored overrides; emit a conflict/preview where merge cannot be safely resolved.
8. Stage outputs, preview changes, then commit with an application-level recovery journal across DATA-01 filesystem and DATA-02 index. Do not treat them as a single ACID transaction.
9. KTX-Software licensing requires **special handling**: most original files Apache-2.0, but upstream includes optional non-open-source Ericsson-licensed ETC decoder. Disable/exclude `LIBKTX_FEATURE_ETC_UNPACK` path unless separately authorized after legal/build review. Exact tag and file-level REUSE/SBOM verification before use; Basis Universal has additional third-party notices.
10. Stormline Import Receipt Graph (SIRG) is an **R&D hypothesis** and must pass prove-or-drop against DATA-02 receipts/standard graph, not become a duplicate source of truth.

## Alternatives
- **Embed Assimp and every decoder in core/runtime:** avoid package size, attack surface, build/license complexity and headless shipping cost before demand is proved.
- **Auto-fix malformed inputs or discard unknown required glTF features:** reject silent fidelity loss. Return typed error/report unsupported feature.
- **Use source hash as AssetId:** reject under DATA-02 stable identity requirements.
- **All imports execute subprocess commands/plugins unsandboxed:** reject security/privilege escalation.
- **Cloud conversion as requirement:** reject zero paid/infrastructure and privacy rules.
- **Overwrite generated content + user edits on reimport:** reject data loss.
- **Always-on proprietary import graph:** avoid without benchmark gains.

## Decisions deliberately deferred
Exact library versions, supported extension subset, normal/tangent transform rules, audio codec set, pixel/ICC policies, scene intermediate serialization, KTX build feature selection, isolation implementation per platform, source-code license of engine and quantitative import budgets.

## Proof obligations for future implementation
- Pin exact versions/license/third-party notices + CVE scan; exclude non-approved KTX components with build-generated SBOM.
- Golden mesh/skin/morph/PBR/2D texture/HDR/audio fixtures across Windows/Linux/macOS and Web feature tier; show conformance failure/fallback policy.
- Fuzz/ASan/UBSan/TSan supported configurations, URI/path escape, memory/decompression and timeout/error isolation.
- Idempotent reimport, stable subasset IDs and 3-way user override merge, dependency invalidation, fault-injection at import commit states and recovery after crash/disk full/cancel.
- Measure p50/p95/p99 throughput/peak RSS/storage by fixture format and target; low-core machines and import batch/cancel.
- Editor/CLI/MCP least-privilege authorization, preview/commit and redaction; headless operation without GPU.

## Consequence
This ADR can be merged after docs-only CI as a **proposed planning artifact**. It is not a license clearance, security certification, decoder integrated or executable code authorization. Implementation issue #26 remains BLOCKED with `executor_ready=false` until a separate approved, concrete WO and source-context lock.
