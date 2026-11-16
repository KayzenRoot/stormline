# AI-08 — Authoring Workflow Technology, Standards, Licensing and Threat Research

**2026-11-15 | P00 RESEARCH ONLY / NOT IMPLEMENTED | [research #309](https://github.com/KayzenRoot/stormline/issues/309) | NLE-P00-WO-002-AI-08 | [future code #82](https://github.com/KayzenRoot/stormline/issues/82) OPEN/BLOCKED | BASE `55250c21f834067524014bdb70eedcdddbf6949e`.** Catalog 64/80; formal predecessors **AI-05 + AI-07 ONLY**, both ADRs PROPOSED; baseline 63/80 researched, 17 pending, 80/80 code WOs BLOCKED, no engine. NLE-D009 license OPEN.

## 1. Primary sources and distinctions
| Source/technology | Current reference | Relevant fact and architecture decision |
|---|---|---|
| MCP **2026-07-28** | [Spec](https://modelcontextprotocol.io/specification/2026-07-28) / [release](https://blog.modelcontextprotocol.io/posts/2026-07-28/) | stateless per request, owner tool calls, user-selected resources/prompts, MRTR and opt-in extensions; AI-04 owns protocol |
| MCP Tasks extension | [Tasks interoperability](https://csharp.sdk.modelcontextprotocol.io/v2/concepts/tasks/tasks.html) | `io.modelcontextprotocol/tasks` negotiated per request; tasks/get handles, polling and status; **some SDKs do not implement extension** |
| MCP Python SDK 2026 migration | [migration guide](https://py.sdk.modelcontextprotocol.io/migration/) | old experimental Tasks removed; redesigned 2026 extension not yet in that SDK at time of docs; do not assume support |
| MCP elicitation | [Elicitation](https://modelcontextprotocol.io/specification/2026-07-28/client/elicitation) | form input for nonsensitive values, URL for sensitive interactions; neither replaces owner-trusted approval |
| OpenUSD | [Pixar OpenUSD introduction](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/docs/intro.rst) | layer stacks, reference/payload, variant sets, time-sampled scene composition; **interop candidate, not Stormline DATA-04 native source** |
| OpenUSD licensing | [OpenUSD LICENSE.txt](https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt) | **Tomorrow Open Source Technology License 1.0** with modified trademark section vs Apache 2.0; bundled components have distinct notices; check exact release |
| glTF 2.0 | [Khronos specification](https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html) and [extensions](https://github.com/KhronosGroup/glTF/blob/main/extensions/README.md) | meshes, nodes, skins, animation, materials, binary/JSON, extensionsRequired negotiation; portable interop, not general gameplay source |
| MaterialX | [Specification](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/documents/Specification/MaterialX.Specification.md), [LICENSE](https://github.com/AcademySoftwareFoundation/MaterialX/blob/main/LICENSE) | standard material/shading node graphs; root Apache-2.0, exact version and transitive licenses needed; target shader mapping may lose semantics |
| OpenTimelineIO | [OTIO docs](https://github.com/AcademySoftwareFoundation/OpenTimelineIO/blob/main/docs/index.rst) | clips/tracks/transitions/markers and external media refs; **not embedded audio/video** or engine gameplay animation runtime |
| OWASP Agentic Top 10 2026 | [OWASP resource](https://genai.owasp.org/resource/owasp-top-10-for-agentic-applications-for-2026/) | goal hijack/tool misuse/privilege abuse/memory poisoning and agent-agent trust require owner-controlled tools, not prompt guards |

## 2. Candidate orchestration and serialization, no adoption
| Candidate | License/release concern | Benefits | Gate/gaps |
|---|---|---|---|
| Stormline versioned typed recipe AST, owner command DAG | engine source code license NLE-D009 OPEN | model-neutral, deterministic static recipes, no new interpreted code runtime | high engineering/proof burden, planner boundedness and schema migrations |
| JSON Schema 2020-12 + canonical typed manifest | standard format; parser/validator exact license/tag to verify | validate typed params/outputs, owner schemas and unknown fields | canonical hashing/Unicode/number normalization and cross-C++/JS parity |
| YAML or arbitrary templating language | varies; feature-rich tags/exec hooks | human authoring convenience | unsafe construction/eval, surprising coercion, alias explosion; **not default** |
| BPMN/workflow framework | many runtime licenses/transitive dependencies | graphical state machines and retries | redundant coordinator and cloud/service burden, conflicts with AI-07 receipts |
| Offline deterministic static recipe library | source rights per recipe and all referenced assets | zero cloud cost and reproducible golden fixtures | cannot claim unpinned generative media is bitwise repeatable |
| Optional LLM planner (provider-neutral adapter) | model terms, rate/cost/privacy, client/version & output rights | flexible creative proposals | no default paid/cloud dependency; all proposals need typed validation and owner grant |
| Optional MCP Tasks and durable handles | SDK/extension version/licensing owned AI-04 | long cook/compile flows with polling, cancellation and scoped recovery | Python SDK may lack implementation; no hidden transport state, no fake task |
| Owner build/cook pipelines | DATA-05 and target SDK license not approved | validated target game packages | no export until actual platform owner supports, no network publish as side effect |
| OpenUSD v26.11 family | TSOL-1.0 and component mixed notices | non-destructive layered DCC export/reimport | heavy optional deps, version/OS builds, source semantics/stable IDs, rendering not native authority |
| glTF 2.0 + optional extensions | Khronos spec; importer/exporter code licenses separately | portable 3D assets with explicit extension support | shaders/physics/behavior/UI/export platform not all covered; reject unknown required extension |
| MaterialX | Apache-2.0 root + SPDX/NOTICE per tag | material graphs, PBR nodes, standard interchange | target shader compile/texture semantics and security sandbox |
| OTIO | exact repo/source/license and adapters need review | timeline metadata interchange | media external, no runtime audio engine |
| Blender tools | Blender GPL distribution and plugin/API restrictions require legal review | external DCC interoperability fixture | not ship Blender code/embedded GPL component without review; no arbitrary Blender Python executed in engine |
| Godot editor/plugin concepts | core MIT but third-party plugins differ | editor workflow and semantic node tools research | Stormline remains distinct engine; no component copied without license |
| Remote generation asset API | model/licensing/PII/paid policy unresolved | richer audio/images | out of default P00, requires explicit user approval and rights-cleared provenance |

## 3. Target capabilities and interoperability limitations
- OpenUSD layers/variants can represent DCC assembly and non-destructive overrides; converting to Stormline source requires DATA-04 owner schema and stable AssetId provenance, not string-path remap. Unsupported arc, payload, variant or timeline semantics => PARTIAL/UNSUPPORTED.
- glTF 2.0 is transport for mesh/material/skin/animation, not gameplay scripts, physics solver, AI behaviors, game UI and target binary; `extensionsRequired` unknown MUST fail safe or preserve only with proven owner semantics.
- MaterialX graph unit/color-space and node semantics must be mapped through GFX-07 owner typed graph and validated/compiled for real target; a generated graph is not a compiled shader.
- Audio event graphs/timelines need licensed source media; OTIO stores editorial *references*, not sound files. Never auto-generate or fetch commercial copyrighted media as default.
- Windows/Linux/macOS/Web target cook/export differs by GPU/drivers, codec and filesystem rules; explicit target profile with capability digest, no universal "works everywhere" claim.

## 4. Threats and response
| Threat | Future mitigation / oracle |
|---|---|
| Prompt injection inside scene names, docs, resource content or recipes | mark as inert untrusted data; typed schema/owner PEP; zero privileged actions |
| Tool-chain amplification, recursion, cyclic graph, token exhaustion | depth/fanout/ops/bytes/time caps, deterministic DAG validation, per-agent quotas |
| Cross-project resource URI or asset smuggling | AI-05 ACL before visibility/hydration; AI-06 current owner rights on every tool |
| Untrusted template code/JS/Python/shell emitted by model | no eval, no arbitrary external subprocess/network; safe owner sandboxed script API only |
| Hidden destructive side effect or changed export destination | AI-07 explicit plan/semantic diff; AI-06 trusted approval bound to exact source/target |
| Owner source changes during multi-step plan | revision-vector CAS; re-read/replan/reconsent, typed conflict not overwrite |
| Audio/media/font/model licensing/PII provenance | signed/verified owner source rights, license flags, asset redistribution policy, no real customer data |
| Host SDK lacks Tasks, cook or recompilation | capability handshake, explicit UNSUPPORTED, no silent fallback to unverified feature |
| Unknown glTF extension/unsupported MaterialX node | explicit required capabilities, typed error with no partial fake success |
| False generated output/source proof | independent DATA-04/asset owner reopen, actual compiler/build/cook receipt and verified output artifacts |
| External publishing cannot be undone | compensation-only class; explicit user destination consent, no automatic upload |
| Telemetry and tool traces leak user prompts/assets | redacted request/receipt hashes and minimum retention; no bearer token or raw source dumps |
| License/third-party game content contamination | allowlisted source rights/provenance+notices; reject unknown licenses and imitation of unlicensed assets |

## 5. Benchmark and license decision gate
Pin exact source owner schemas and version, OS/host/SDK/protocol, recipe identity/seed, module owner capabilities, asset rights, target/cook profile and model provider/version if used. Compare deterministic offline recipe and optional model proposals on the same task fixtures; report measurable completion coverage, operations, manual *editing* actions, consent actions separately, semantic source equivalence, correctness, privacy and latency/cost. No numerical targets approved, no tests run. Before any adoption require exact release/tag, SBOM/SPDX+NOTICE, patents/trademarks, CVE/security patches, Windows/Linux/macOS and optional Web build proof. License NLE-D009 remains OPEN.

[Architecture](../architecture/ai-08-authoring-workflows.md) · [ADR-0067](../adr/0067-ai-08-declarative-owner-authoring-recipes.md) · [Contracts](../contracts/ai-08-authoring-workflow-api.md).
