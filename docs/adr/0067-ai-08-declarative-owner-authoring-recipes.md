# ADR-0067 — Versioned Declarative Recipes, Owner-Cited Context and Transactional Authoring

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Catalog 64/80; formal predecessors **AI-05 + AI-07 ONLY**, both ADRs PROPOSED; baseline 63/80 researched, 17 pending, 80/80 code WOs BLOCKED, no engine. NLE-D009 license OPEN.

**STATUS: PROPOSED / NOT RATIFIED / NOT ADOPTED / NO IMPLEMENTATION AUTHORIZATION.**

## Problem
An AI-native game engine requires model-neutral orchestration of complete typed authoring workflows while remaining fully controllable, repeatable, secure and compatible with manual editor changes. LLM text alone cannot provide authoritative scene state, licenses, commands, tool execution results or trusted approval. Unrestricted scripting is a supply-chain and privilege escalation trap. Existing AI-05 read-only context and AI-07 transactional changeset research must remain distinct owners.

## Proposed decision
1. **Formal dependencies exactly AI-05 + AI-07.** AI-05 owns authorized contextual discovery, scoped template/recipe resources, source revision and citation; AI-07 owns typed ChangeSet preview/commit/rollback/partial outcomes. AI-01, AI-06, AI-04, DATA/WORLD/GFX/TWO/AUDIO/GAME owners and AI-09 are **transitive/integration ports**, not new formal edges. AI-08 never writes canonical source directly.
2. **Declarative, versioned, owner-authorized recipe DAG**: typed immutable manifest, explicit inputs/outputs/preconditions/side-effect categories, owner CommandId, bounded dependencies, capability/target checks, schema version, deterministic seed, license/rights, max depth/fanout/CPU/bytes and failure policy. Reject arbitrary code execution, import strings as instructions, unsupported owner nodes, cycles and undeclared network paths. No dynamic eval/unsafe general-purpose template interpreter.
3. **Progressive source context**: AI-05 provides least-context Context Capsules pinned to source owner revision/rights/AI-02 index generation/policy epoch, not whole repository dump. Agent text and context are untrusted and cannot authorize new reads. Expired/partial context yields safe stale/unsupported status.
4. **Tool calls must compile to AI-07 typed ChangeSets** with owner preview/semantic diff and original AI-01 CommandIds. AI-07/AI-06 enforce owner grant and one-use consent at actual commit. Never call fake generated script or raw file writes for missing owner capabilities.
5. **Zero manual editing** acceptance means supported end-to-end authoring scenario can be generated from typed tool calls and reviewed source/target receipts without a human drawing/placing each object. It **does not waive** trusted human consent for high-risk or external actions and does not assert that all creative quality is automatic.
6. **Determinism is conditional and evidentiary**: version/seed/source revision/schema/profile fixed with fully pinned external assets can give repeatable owner-level semantic outputs. Generic LLM/model or image/audio generation is non-deterministic unless actual output bytes/license receipts pinned. Never equate prompt/seed with bit-identical audio/render/art.
7. **Explicit capability negotiation and graceful-but-honest degradation**: recipe step requiring absent renderer, script sandbox, sound source, target exporter, OS process or visual validator is UNSUPPORTED; complete workflow is NOT COMPLETE. Optional steps may be skipped only when marked OPTIONAL upfront with bounded owner-approved substitute and evidence; never silently omit declared mandatory behavior.
8. **Owner and target validators**: schema/ref integrity, connected node graphs, script API safety, shader compile, finite VFX and game behavior, localization/accessibility and owner cook/export receipt must be proven when capability exists. Source commit != runtime compile/publish. Report VALIDATION_FAILED/PARTIAL/EXPORT_PENDING with precise boundaries.
9. **Security, provenance and licensing**: all imported/LLM-proposed text and external assets are data, not trusted tools; content rights, source AssetIds, provenance/license restrictions and budget limits survive all recipe steps. No proprietary third-party game graphics/music/audio or unknown license as default assets.
10. **MCP compatibility via AI-04** modern 2026-07-28 protocol, optional negotiated Tasks extension, MRTR input as data only, not trusted approval; no direct SDK/server or deprecated Sampling as baseline. Hosts Codex/Claude require actual version-pinned tests, not protocol assumption.
11. **No code or technology adoption**: OpenUSD, glTF, MaterialX, OTIO, Godot/Blender tooling, workflow runtimes and graph compilers remain *interop/research candidates*, not selected. Exact release/tag and SPDX/NOTICE/CVE/packaging/target license obligations require separate approval; NLE-D009 remains OPEN. No paid/cloud LLM mandatory.
12. **128 FUTURE / NOT EXECUTED tests** with target fixture/owner oracle, independent benchmark. ADR-0067 is PROPOSED, future code #82 and all 79 other code WOs stay BLOCKED.

## Alternatives
| Candidate | Advantage | Rejection/defer reason |
|---|---|---|
| LLM returns scene JSON and writes files directly | quick demo | bypasses owner SceneIR/AssetId, policy and transactional recovery; schema hallucination |
| Agent executes arbitrary Python/JavaScript/C++ generated by model | broad flexibility | arbitrary filesystem/network capability, malicious plugins and nondeterminism |
| AI-08 duplicates AI-05 search/context index | local convenience | split source truth, ACL leakage, stale provenance and new formal dependency |
| AI-08 performs AI-07 commits itself | lower overhead | bypasses consent, CAS, partial recovery/undo, idempotency |
| Entire repository/scene source injected into each prompt | no retrieval work | unbounded tokens, rights/privacy leak and unnecessary cost |
| One monolithic "create game" opaque tool | simple API | no reviewable semantic changes, failure localization, predictable permissions or recovery |
| Full BPMN service, remote orchestrator or workflow SaaS | mature features | operational complexity, paid/cloud/offline dependency and separate command authority |
| Adopt OpenUSD as native authoritative SceneIR | rich DCC composition | conflicts with DATA-04 owner/versioning/engine semantics; interop may be optional |
| Use MaterialX or glTF as engine source of truth for all shader/scene | standard portability | interop cannot express every game behavior/target and proprietary source extensions |
| Treat model seed as guaranteed reproducible output | easy caching | remote model/provider changes, image/audio non-determinism and license conflicts |
| Silent skip absent VFX/audio/script/export | demo passes | violates declared complete scenario and user trust |
| Auto-run MCP prompts or input_required as high-risk consent | fewer clicks | prompt is data, MRTR is not AI-06 trusted approval |
| Assume optional Tasks support in every SDK | efficient operations | actual SDK capability varies; unsupported host must use proven alternative |
| Immediate external export/upload followed by generic rollback | automation | external side effect may be irreversible and needs owner/destination consent |

## Consequences and proof obligations
Better model independence, reusable templates, source integrity, safe no-manual-edit authoring and clear quality failure states. Costs: owner capability matrices, recipe versioning/migration, context freshness, typed graph compiler, target-specific validations, operation budgets, trace/audit, compatibility maintenance and stricter rights evidence. Full workflows depend on many downstream owners which are **not implemented** today and must not be silently inferred from documentary descriptions.

## Ratification gate
- Owner-approved recipe JSON Schema/IDL, canonicalization, source fingerprints/target profiles, SDK/graph runtime choice and exact rights rules.
- AI-05 privacy/revision/citation and AI-07 plan/commit/recovery interfaces actually exist and pass owner tests; AI-06 consent/JIT permission and AI-01 typed commands enforced.
- 128 A08 scenarios executed, end-to-end three representative fixtures pass with no manual scene edit and independent owner source/cook readback, all mandatory owner capabilities supported.
- Fixed hardware/OS versions and host/SDK interoperability; actual model-neutral baseline and without-mandatory-cloud recipe proof; benchmark thresholds owner-approved.
- No HIGH/CRITICAL, independent security/release review, validated licensing/SBOM/CVE and separate ADR ratification. Until then **PROPOSED**, no implementation authorized.

[Architecture](../architecture/ai-08-authoring-workflows.md) · [Contracts](../contracts/ai-08-authoring-workflow-api.md) · [Technology matrix](../research/ai-08-workflow-technology-license-threat-matrix.md).
