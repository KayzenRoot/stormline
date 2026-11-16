# AI-08 — Reproducible Complete-Scenario, Workflow Coverage and Agent Efficiency Benchmark Protocol

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Formal deps AI-05 + AI-07 only; ADR-0067 PROPOSED; 63/80 research at baseline; 80/80 future code packets BLOCKED; engine false, NLE-D009 license OPEN.

**FUTURE / NOT MEASURED.** No recipe runner, owners, agent, game builder, real target export, host, benchmark, scene, audio/video generation or conformance test has been executed. Numerical thresholds are not approved.

## 1. Falsifiable hypothesis and study question
Can a model-neutral, bounded, rights-aware recipe graph produce a whole supported 2D/3D scene and verified export using *only typed authoring tool calls* without any manual editing operations, while honoring AI-05 source privacy, AI-07 transactional integrity, human consent and actual target/owner limitations? Compare (A) deterministic offline typed recipe; (B) optional model planner generating the same validated typed operations with fixed model/version/prompt/output; and (C) qualified manual editor baseline with identical validated scene outcome. Avoid comparing nonexistent features, and do not treat model-written screenshots as actual source proof.

Core success requires *source-owner readback and target package validation*, not a subjective agent summary. Zero unauthorized reads/writes, no unlicensed source and no hidden missing mandatory node are hard security gates.

## 2. Pin exact environment and rights
Record Git base/head/Source Pack fingerprints, AI-05 context revision and owner index/ACL/policy epoch, AI-07 ChangeSet schema/commit receipt, AI-06 grant+consent references, AI-01 command descriptors, DATA-02/04 source, owner capability profile and target build/cook versions, recipe manifest digests, stable AssetIds, external blob hashes+licenses, OS/arch, hardware CPU/GPU/RAM, renderer/driver, shader and audio codecs and sandbox. If a model is optional, pin provider+model/release, temperature/top_p, prompt hash, output blobs and token costs/price; distinguish estimate from exact provider tokens.

## 3. Deterministic future test fixtures
| Fixture | Contents and independent ground truth | Target |
|---|---|---|
| WF-2D-S | 1 2D room, layered tilemap, camera, collision, responsive HUD, animation/timeline, 1 licensed audio event and behavior | Windows/Linux/macOS headless+editor |
| WF-3D-S | 1 3D scene, instanced prefab, camera, physically plausible light, PBR material, bounded VFX, safe script event and audio cue | Windows/Linux/macOS |
| WF-WEB-S | same rights-clear 2D scene with web-safe assets, shader fallbacks and export target | Web target if owner supports |
| WF-MULTI | 100 scenes, 10k asset references, 1k recipe steps, 32 actors with disjoint/overlap edits | stress and ACL race |
| WF-MEDIA | synthetic fonts/sounds/textures with mixed allowed/restricted redistribution | provenance/licensing |
| WF-SEC | poisoned docs, hostile template, forged tool descriptions, cross-project refs and untrusted script code | zero unauthorized effects |
| WF-COMP | missing required VFX/GAME/audio/target owner or MCP Tasks extension | explicit unsupported/failure |
| WF-CRASH | source commit followed by cook failure, crash during apply and failed compensation | actual partial/readback recovery |
| WF-LOCALE | CJK/RTL/emoji and focus/gamepad navigation with reduced-motion preference | accessibility and typography |

At least one fully supported sample fixture **per target claimed**, including actual asset source and rights receipts. When owners do not exist (P00), every real execution is NOT EXECUTED, never manufactured PASS.

## 4. Benchmark matrix and metrics
| ID | Future experiment | Independent measurement |
|---|---|---|
| WF-B01 | discovery and context pin per recipe | owner-authorized bytes, source citations, latency, data-leak count |
| WF-B02 | fixed recipe JSON schema parse and DAG validation | invalid graph rejection, CPU/RSS, schema version compatibility |
| WF-B03 | typed operation planning on 2D/3D scenes | required owner command coverage, semantic plan digest correctness |
| WF-B04 | no-source-side-effect preview with visual reference | actual disk/source diff=0, owner semantic diff fidelity |
| WF-B05 | typed AI-07 apply with grant/consent | source readback success, total owner operations and latency |
| WF-B06 | shader/VFX/audio owner compatibility | typed sockets, owner shader compile and audio/VFX receipts, time |
| WF-B07 | gameplay behavior and UI localization/accessibility | compile failures, graph validity, text/focus/contrast oracle |
| WF-B08 | target DATA-05 cook and export | built file manifest, package digest, target compatibility, time |
| WF-B09 | zero manual editing acceptance | count manual scene edit actions=0, human consent actions reported separately |
| WF-B10 | deterministic offline vs optional model planner | semantic output equality, model variance/error rate and token cost |
| WF-B11 | concurrent actor/project and ACL/consent revocation | unauthorized owner effect=0, stale conflicts, no lost updates |
| WF-B12 | crash/partial/fault injection and resume | duplicate writes=0, truthful AI-07 journal and completion states |
| WF-B13 | source rights restrictions and export | blocked unlicensed assets, intact notices and provenance |
| WF-B14 | optional MCP Tasks-supported vs unsupported host | task handle scopes, polling overhead, explicit fallback/unsupported |
| WF-B15 | large scenario quota and incremental rebuild | p50/p95/p99 latency, bytes/RSS/CPU, unchanged owner rework avoided |
| WF-B16 | Codex/Claude/Editor/CLI semantic parity | actual host/version, same owner source digest and target receipt |

## 5. Measurement procedure
- Use seed/rights-cleared test bundle and independent expected owner source truth; do not score model's natural language description as a scene. Keep source/target readback distinct from AI-07 plan and preview.
- Use >=5 independent trials and sufficient samples for p95/p99; publish raw samples, cold/warm and hardware/OS profiles. Do not invent millisecond thresholds. Separate AI-05 context, AI-07 transaction, shader/cook and host model latency; record retries and API costs.
- Count **manual authoring edits**, human consent clicks, user task choices, unresolved conflicts and manual repair separately. Zero manual editing is not zero supervision. If human must fix missing node or asset manually, future catalog acceptance fails for that supported fixture.
- Workflow coverage denominator is independently enumerated declared owner-required features and scene steps, not whatever agent happened to generate; any skipped mandatory feature yields incomplete status.
- Security negative checks use synthetic OS outside-project sentinel hashes, no network except fixture allowlist, no secret tokens, no real customer files, unlicensed media or external publishing.
- Reproducibility requires pinned recipe/tool schema/source revisions and **actual** generated media blob hashes; seed-only model/media cannot justify bit-identical claim.
- Target compiled outputs (Windows/Linux/macOS/Web where supported) must have true checksums/manifest/launch validation separately from dry-run; don't certify cross-GPU visual quality without controlled renders.

## 6. Future evidence record schema
```text
A08BenchmarkReceiptV1 {
 git_base_sha,git_head_sha,critical_source_oids,recipe_id_version_digest,
 ai05_context_generation_owner_source_revision_acl_epoch,
 ai07_plan_digest_owner_commit_receipt,ai06_grant_consent_ref,
 ai01_command_versions,owner_capability_profile_versions,
 target_os_arch_web_driver,source_asset_rights_licensing_digest,
 fixture_seed,golden_truth_digest,optional_model_id_prompt_sampling,
 captured_generated_media_blob_hashes,required_steps_count,
 owner_supported_steps,owner_unsupported_steps,owner_source_readback_digest,
 semantic_diff_fidelity,manual_edit_actions,human_approval_actions,
 shader_compile_audio_vfx_game_ui_validation,export_package_digest,
 unauthorized_owner_or_fs_changes,unlicensed_content_count,
 cross_project_leaks,retry_duplicates,partial_recovery_stage,
 context_bytes,token_estimate_or_exact_basis,tool_call_count,
 cold_warm_latency_samples,p50_p95_p99,peak_cpu_ram_io,cost,
 unsupported_or_skipped_cases,verdict,independent_audit_ref
}
```
All metrics NOT MEASURED, no real host tests or engine code. Any incomplete owner module invalidates a "full scenario" claim. Technology/runtime license and owner approval separately required.

[Architecture](../architecture/ai-08-authoring-workflows.md) · [Future tests](../testing/ai-08-acceptance-matrix.md) · [MCP Tasks extension docs](https://csharp.sdk.modelcontextprotocol.io/v2/concepts/tasks/tasks.html).
