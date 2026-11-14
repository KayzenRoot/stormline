# Stormline — AI-native / MCP Architecture Contract v0.1
Work Order: NLE-P00-WO-001-EXT-002 | Status: PROPOSED; NO IMPLEMENTATION.

## Objective
AI agents (Claude Code, Codex and compatible LLM hosts) and manual developers must work on the **same** projects with equivalent authoring power. MCP is a versioned **adapter** to an internal semantic command system; it must never be the only way to access the engine's capabilities.

## Why protocol versioning matters
MCP official revision `2026-07-28` introduced a stateless core, self-describing requests, updated Streamable HTTP behavior, protocol version info, request/response interactions and changes to extensions. Do **not** design new code around obsolete implicit MCP sessions, unsolicited server calls or legacy sampling/roots assumptions. Pin protocol adapter behavior and test selected hosts against their **actual** supported revision; maintain an explicit compatibility table.

References:
- https://modelcontextprotocol.io/specification/2026-07-28
- https://blog.modelcontextprotocol.io/posts/2026-07-28/
- https://ts.sdk.modelcontextprotocol.io/v2/

## Canonical architecture

```text
Human (Stormline Editor)         CLI / Headless API          Claude / Codex / other MCP Hosts
            \                           |                              /
             \                          |                             /
                     Validated Typed Command Kernel
                  (semantic operations + world transactions)
                               |
                Project model / assets / scenes / code
                               |
                Engine systems + deterministic tests
```

The MCP adapter exposes structured **tools, resources, prompts** and supported extensions only through negotiated compatibility. No provider-specific data type should be embedded in the runtime, renderer, physics, scripting core or asset schemas.

## Requirements

### 1. Canonical command kernel
- Operations have ID, version, schema, preconditions, postconditions, ownership, side-effect level, permission, undo/revert support and error model.
- Changes are semantic transactions using project revision handles, not raw disk overwrites.
- Read, create, patch, delete, generate, compile, preview, benchmark, export and build operations are eventually represented in the registry where that capability exists.
- All editor operations of the **approved authoring surface** must be mapped to public commands or documented as intentionally private administrative operations.
- Headless and human execution use the same validated functions. Result is equivalent given same project revision, input and environmental constraints.
- Atomic edits, idempotency keys and dry-run/previews for risky changes; deterministic outputs where meaningful, with explicit nondeterministic seeds where needed.

### 2. MCP server transport and compatibility
- Local `stdio` as an offline-friendly default for authorized desktop workflows.
- Remote HTTP only by explicit configuration; authenticate and authorize independently of claimed client name.
- Version negotiation/compatibility: assess 2026-07-28 support and known older hosts; no speculative compatibility guarantee.
- Use bounded, paginated responses, resources and prompts for context efficiency; advertise schema, tool metadata, progress and cancellation only as supported by the negotiated revision.
- Long running builds and tests use a Stormline job handle plus polling/results; map to MCP task extension only where truly supported by the remote peer. Respect 2026 revision of Tasks and avoid relying on legacy experimental behavior.
- No hard dependency on the host providing an LLM or sampling API: project creation and validation functions must run offline.

### 3. Operation namespaces (examples, NOT implemented)
- `stormline.project.*` — create, inspect, configure, validate, archive, export project.
- `stormline.scene.*` — list, create, patch, duplicate, remove, batch, inspect world.
- `stormline.asset.*` — query, import, reimport, materialize, validate licenses and references.
- `stormline.2d.*` — sprites, tilemaps, canvas, 2D lighting, timeline.
- `stormline.material.*` — graphs, textures, PBR properties and shader compilation.
- `stormline.lighting.*` — lamps, probes, shadow quality, daylight; validation by tiers.
- `stormline.vfx.*` — emitters, particle graphs, curves, profiles and stress scenes.
- `stormline.audio.*` — emitters, buses, spatial settings, DSP graph and previews.
- `stormline.animation.*` — clips, skeletons, controllers, IK and state machines.
- `stormline.physics.*` — 2D/3D bodies, colliders, constraints and simulation test.
- `stormline.gameplay.*` — input actions, scripts, events, UI, genre templates.
- `stormline.network.*` — server profiles, replication settings, simulation tests.
- `stormline.build.*` — build, cook, package and export to approved platforms.
- `stormline.test.*` — test, benchmark, compare golden scene and retrieve diagnostics.
- `stormline.capabilities.*` — list schemas, versions, permissions and examples.
These are **logical namespaces**, not claims about MCP tool naming requirements or actual deployed tool IDs; tool naming/version conventions will be decided by an ADR.

### 4. MCP Resources and prompts
- Resource catalog: project tree, hierarchy, selected object, schemas, asset metadata, test status, profiler findings, platform capabilities, ADR excerpts and build logs.
- Prompts/recipes: create 2D project, assemble playable 2.5D ARPG test scene, 3D map staging, author VFX, troubleshoot frame time, inspect asset imports, validate web export, optimize audio.
- Scope, permission and filtering apply to resources as well as tools. No automatic leakage of secrets, local paths outside workspace or licensed user data.
- Cache resources by revision/TTL and invalidate on changes; never return an entire project when a delta suffices.

### 5. Agent orchestration and developer workflows
- Workflows may be initiated by host LLM or owner request. Stormline is not obliged to host its own paid model provider.
- Model-neutral: Codex, Claude Code and other MCP-capable hosts are **compatibility targets**, not guaranteed integrations before conformance tests.
- Multi-agent edits require locking/optimistic concurrency, structured conflicts, actor attribution and recovery; never silently let one agent overwrite another.
- Generation of shaders/code/assets remains subject to provenance, license review, sandbox, validation and human approval before dangerous operations.
- Provide `plan -> preview/diff -> authorize -> apply -> validate -> evidence -> undo/rollback` for significant mutations.
- File creation, arbitrary process execution, network access, publish/deploy, asset deletion, signing, purchasing or privileged commands need narrow capabilities and explicit approval.

### 6. Security threat model
- Do not execute untrusted prompt/tool descriptions as privileged instructions.
- No unrestricted filesystem, arbitrary shell, default internet access, hidden network listeners or secrets exposure from MCP.
- Scope tools per workspace/project, path and operation category; apply least privilege.
- Local transports still enforce workspace boundaries and validation. Remote transport must consider authentication, authorization, CSRF/origin checks and network exposure.
- Audit who requested tool, arguments redacted, project revision, permission decision, outcome and reversible change ID.
- High-risk tools always require explicit permission; safe read-only queries may use pre-approved project capabilities under user configuration.

### 7. Performance and token efficiency
- Metadata query and pagination, selective context, caching and incremental project indexing.
- Tool IDs stable across versions; deprecated capabilities produce actionable errors.
- Query returns shape/summary before large detail; image/audio/video previews returned via bounded content or secure resource URI.
- Avoid thousands of near-identical tools; expose coherent domain tools with typed operations while preserving complete authoring coverage.

## Coverage obligations before commercial release
For each owner-approved module, create a test matrix:
`module ID | action ID | interface (Editor, CLI, MCP) | side effects | auth capability | schema version | integration test | expected artifact`.

**100% of approved public authoring operations** must be testable through the command kernel and available to MCP when authorized. Internal memory allocators, GPU driver handles and privileged secrets are not raw MCP tools; they are covered by diagnostics and controlled operations. No 'all engine internals as unrestricted tools' design.

## Acceptance demonstrations
1. Create/open/save a full 2D game sample manually and via MCP, with equivalent scene data and playable export.
2. Generate/modify 2.5D ARPG scene, characters, VFX, material/audio and validation without manual editor clicks.
3. Edit outdoor 3D terrain, lighting and vehicles; capture perf regression report and revert a failed change.
4. Build Web target, read compiler/validation feedback, repair a known error by tool calls, and export.
5. Attempt unauthorized writes/out-of-workspace access; verify rejection, no data loss and complete audit log.
6. Test host/protocol compatibility with selected Codex/Claude releases; claim integration **only after evidence**.
7. Test cancellation, incremental reads, concurrency conflicts, failed transactions and asset migration.

## Dependencies and open questions
Core command operations, asset schemas, editor parity, platform list, offline/per-provider policies, scripting language, MCP SDK selection, host compatibility and remote auth all require separate ADRs. Do not start implementation until P00 source/acceptance decisions are approved.
