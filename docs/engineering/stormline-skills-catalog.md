# Stormline | Agent Skills Pack v0.1 — 36 focused workflows

**Status:** Documented, repository-local and ready for discovery by compatible Codex clients, **not activated engine work**. Work Order `NLE-P00-GOV-002-SKILLS`, [issue #378](https://github.com/KayzenRoot/stormline/issues/378), BASE `356695b078001f4f9caa94d1119ae045bf391375`. `AGENTS.md`, Checkpoint, Ledger, Scope, DoD and formal module ADR prerequisites retain priority. **80/80 research documented; 80/80 implementation WOs blocked, 0 ready/approved ADR; NLE-D009 license OPEN.**

## How to use
Codex recognizes checked-in skills under `.agents/skills/<skill-name>/SKILL.md`. Match naturally by the YAML `description`, or explicitly reference one with `$stormline-editor-ux` or `$stormline-ci-quality-gates` in compatible Codex environments. Another agent (Zcode/OpenCode) can read these as instructions by explicit file path; **automatic discovery outside Codex is not verified**. No skill executes code or produces assets automatically by being installed. The [manifest](stormline-skills-manifest.json) maps every one of 80 module IDs to primary skills; use `python3 scripts/validate_skills.py` to verify integrity.

Skills are **workflows**, not one copy per module: one narrow skill can assist many related modules, while a Work Order selects exactly what is necessary. Minimize context: read the chosen SKILL.md and only the relevant approved sources, not all 36 skill bodies. The user may call multiple skills sequentially (design -> implementation after authorization -> QA -> audit) but permissions do NOT accumulate or bypass owner gate.

## All 36 specialized skills

| Skill | Family | When to use / not use | Source |
|---|---|---|---|
| `stormline-source-check` | governance | Use for any Stormline task before research, code, design, docs or merge; reject stale context and unverified claims. | [SKILL.md](../../.agents/skills/stormline-source-check/SKILL.md) |
| `stormline-work-orders` | governance | Use to specify or hand off one bounded Stormline Work Order; never use a draft as permission to run code. | [SKILL.md](../../.agents/skills/stormline-work-orders/SKILL.md) |
| `stormline-adr-qualification` | governance | Use to review a PROPOSED module ADR, compare alternatives and prepare a technical decision for explicit owner approval; never self-ratify. | [SKILL.md](../../.agents/skills/stormline-adr-qualification/SKILL.md) |
| `stormline-evidence-audit` | governance | Use to objectively review Stormline PRs, CI runs, test evidence and checkpoint deltas; provide verdict in Brazilian Portuguese. | [SKILL.md](../../.agents/skills/stormline-evidence-audit/SKILL.md) |
| `stormline-license-compliance` | governance | Use for third-party dependency, asset, font, icon, plugin, SDK, engine license, redistribution or trademark audits. | [SKILL.md](../../.agents/skills/stormline-license-compliance/SKILL.md) |
| `stormline-visual-direction` | design | Use to define premium Stormline art direction for the desktop editor, launcher, dialogs and dashboards; not for generating final brand assets without approval. | [SKILL.md](../../.agents/skills/stormline-visual-direction/SKILL.md) |
| `stormline-design-tokens` | design | Use when defining UI theme tokens for colors, typography, spacing, elevation, border, radii, glass/transparency and state semantics. | [SKILL.md](../../.agents/skills/stormline-design-tokens/SKILL.md) |
| `stormline-responsive-layout` | design | Use for editor workspace layout, dockable panels, resizable inspectors, sidebars and adaptive desktop/Web structures. | [SKILL.md](../../.agents/skills/stormline-responsive-layout/SKILL.md) |
| `stormline-iconography` | design | Use to plan original SVG icon families, editor toolbar glyphs, file-type marks, command buttons and launcher symbols. | [SKILL.md](../../.agents/skills/stormline-iconography/SKILL.md) |
| `stormline-editor-ux` | design | Use to specify creator workflows in Stormline Editor: scenes, hierarchy, inspector, assets, node graph, undo/redo and AI command review. | [SKILL.md](../../.agents/skills/stormline-editor-ux/SKILL.md) |
| `stormline-motion-microinteractions` | design | Use to specify refined desktop UI transitions, hover/focus feedback, glass depth motion and original splash animations. | [SKILL.md](../../.agents/skills/stormline-motion-microinteractions/SKILL.md) |
| `stormline-accessibility` | design | Use to audit keyboard, screen reader, focus, contrast, scaling, color-blind and localization requirements for the editor or game UI. | [SKILL.md](../../.agents/skills/stormline-accessibility/SKILL.md) |
| `stormline-visual-review` | design | Use to review UI screenshots, design tokens, icon consistency or visual regressions against an approved reference. | [SKILL.md](../../.agents/skills/stormline-visual-review/SKILL.md) |
| `stormline-platform-build` | engine | Use for future approved cross-platform C++20 host/build, CMake toolchains, headless startup and platform boundary work. | [SKILL.md](../../.agents/skills/stormline-platform-build/SKILL.md) |
| `stormline-core-runtime` | engine | Use for approved core clocks, memory, threading, diagnostics, math and platform-independent engine services. | [SKILL.md](../../.agents/skills/stormline-core-runtime/SKILL.md) |
| `stormline-asset-pipeline` | engine | Use for approved virtual filesystem, asset IDs, importer, serialization, cooking, migration and streaming bundle tasks. | [SKILL.md](../../.agents/skills/stormline-asset-pipeline/SKILL.md) |
| `stormline-rendering-rhi` | engine | Use for approved graphics backend, rendering device, resource lifetime, render graph, culling, HDR and GPU memory work. | [SKILL.md](../../.agents/skills/stormline-rendering-rhi/SKILL.md) |
| `stormline-shaders-materials` | engine | Use for approved shader compilation, PBR materials, textures, VFX graphs, lighting models and quality tiers. | [SKILL.md](../../.agents/skills/stormline-shaders-materials/SKILL.md) |
| `stormline-world-ecs` | engine | Use for approved ECS identities, entity lifecycle, prefab graphs, scene editing transactions and gameplay ownership. | [SKILL.md](../../.agents/skills/stormline-world-ecs/SKILL.md) |
| `stormline-world-streaming` | engine | Use for approved terrain, procedural generation, spatial partition, LOD, streaming, origin shifts and large worlds. | [SKILL.md](../../.agents/skills/stormline-world-streaming/SKILL.md) |
| `stormline-2d-hybrid` | engine | Use for approved native 2D, tilemaps, UI composition, 2.5D depth and 2D skeletal/flipbook animation. | [SKILL.md](../../.agents/skills/stormline-2d-hybrid/SKILL.md) |
| `stormline-physics-animation` | engine | Use for approved 2D/3D physics, character controllers, animation graphs, navigation, destruction and vehicle dynamics. | [SKILL.md](../../.agents/skills/stormline-physics-animation/SKILL.md) |
| `stormline-audio-systems` | engine | Use for approved device mixer, spatial sound, DSP graph, interactive music, dialogue and cinematic timeline. | [SKILL.md](../../.agents/skills/stormline-audio-systems/SKILL.md) |
| `stormline-gameplay-scripting` | engine | Use for approved gameplay script host, API bindings, input, events, UI/localization and composable genre packs. | [SKILL.md](../../.agents/skills/stormline-gameplay-scripting/SKILL.md) |
| `stormline-network-backend` | engine | Use for approved multiplayer transport, authoritative servers, snapshots, prediction, sessions and abuse mitigation. | [SKILL.md](../../.agents/skills/stormline-network-backend/SKILL.md) |
| `stormline-ai-mcp` | engine | Use for approved AI-native editor command kernel, semantic index, MCP adapter, grants and recoverable changesets. | [SKILL.md](../../.agents/skills/stormline-ai-mcp/SKILL.md) |
| `stormline-editor-tools` | engine | Use for approved editor shell, inspector, scene/terrain/2D/graph authoring, sequencer, debug and Play-In-Editor tools. | [SKILL.md](../../.agents/skills/stormline-editor-tools/SKILL.md) |
| `stormline-sdk-plugins` | engine | Use for approved public SDK, engine-hosted plugins, examples, external ABI and developer onboarding. | [SKILL.md](../../.agents/skills/stormline-sdk-plugins/SKILL.md) |
| `stormline-test-planning` | qa | Use to design traceable unit, integration, golden, negative and acceptance tests for one approved Work Order. | [SKILL.md](../../.agents/skills/stormline-test-planning/SKILL.md) |
| `stormline-deterministic-regression` | qa | Use for fixed-step clock, save/project golden tests, replay, asset import and cross-platform semantic regression. | [SKILL.md](../../.agents/skills/stormline-deterministic-regression/SKILL.md) |
| `stormline-performance-benchmarks` | qa | Use to plan or analyze real CPU/GPU, frame-time, memory, audio, network and startup performance baselines. | [SKILL.md](../../.agents/skills/stormline-performance-benchmarks/SKILL.md) |
| `stormline-security-review` | qa | Use for security audit of source, CI, sandbox, network, parsers, auth, signing, privacy and supply chain. | [SKILL.md](../../.agents/skills/stormline-security-review/SKILL.md) |
| `stormline-cross-platform-testing` | qa | Use for real Windows/Linux/macOS/Web compatibility, installer behavior, input, font, GPU driver and hardware qualification. | [SKILL.md](../../.agents/skills/stormline-cross-platform-testing/SKILL.md) |
| `stormline-crash-soak-recovery` | qa | Use for long-running stress/soak, crash loop, project/save integrity, migration and rollback failure injection. | [SKILL.md](../../.agents/skills/stormline-crash-soak-recovery/SKILL.md) |
| `stormline-ci-quality-gates` | qa | Use to design or maintain zero-paid GitHub Actions validation, native build matrix and least privilege quality gates. | [SKILL.md](../../.agents/skills/stormline-ci-quality-gates/SKILL.md) |
| `stormline-release-lifecycle` | qa | Use for future approved versioned build/export, installer, signed release feeds, updates, rollback and support. | [SKILL.md](../../.agents/skills/stormline-release-lifecycle/SKILL.md) |

## Visual experience target (owner-directed intent, tokens not frozen)
[Stormline UI visual proposal](stormline-editor-visual-system-proposal.md) describes elegant desktop-style glass panels, original vector iconography, graph/viewport/inspector layouts, accessible contrast, CPU/GPU fallback, reusable components, animation discipline, and screenshots/fidelity checks. Inspiration is the *craft quality* of modern desktop operating systems; **no copying Apple's icons, protected brand, app screenshots, San Francisco proprietary resources or layouts**. Existing [Brand Foundation](../brand/brand-foundation.md) and [Logo Spec](../brand/logo-system.md) remain PROPOSED, and no artwork is delivered by this skills increment.

## Acceptance and safety
- 36 SKILL.md with standard frontmatter (`name` lowercase slug and unique, `description` under 1024 chars) and executable-instruction workflow with Source Check, stop condition, evidence and bounded scope. No network or dependency installation merely by reading.
- 80 real module IDs from registry each mapped to valid skills; `python3 scripts/validate_skills.py` and its stdlib unit tests run in existing Docs Validation workflow. Validator concerns skills **format and manifest**, not C++/GPU/QA executed by skills.
- No new third-party logos/assets, credential, cloud charge, license, toolkit adoption, engine binary, test PASS, branch setting action, release or 80-WO unlock.
- Changes to skills require same Work Order/Context Lock/PR/CI/audit/readback. Skill instructions cannot outrank AGENTS or Source Pack.

## Official standard references
- [OpenAI Codex skills location and manual frontmatter](https://learn.chatgpt.com/docs/build-skills)
- [Agent Skills file format specification](https://agentskills.io/specification)
- [OpenAI skill-creator guidance](https://github.com/openai/skills/blob/main/skills/.system/skill-creator/SKILL.md)
