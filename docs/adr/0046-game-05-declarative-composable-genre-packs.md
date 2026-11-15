# ADR-0046 — Composable, declarative original genre packs (one Stormline runtime)

**Status: PROPOSED, NOT APPROVED / NOT ADOPTED** | 2026-11-15 | Research #224 | `NLE-P00-WO-002-GAME-05` | Future code #61 OPEN/BLOCKED.

## Context
The index requires shooter, vehicles, ARPG loot/skills/inventory, 2D platformer, racing, strategy and puzzle, but new genres must not require forking Core or a separate engine. GAME-04 owns event/ability/inventory and authoritative state; SIM-04 owns skeletal animation/root-motion intent; AUD-04 owns music/dialogue/cinematic audio. Even though these plans are documented, no executable dependency exists. Game templates from third-party engines demonstrate architecture, not permission to copy code or assets or claim functional compatibility.

## Proposed decision
Create a **Stormline-owned semantic, declarative source package model** (`GenrePackManifestV1`, `GenreFeaturePackV1`, `GameProjectBlueprintV1`, `GenreRecipeV1`) composed by stable IDs and explicit versioned dependency DAGs. A template contains authored rule data, optional GAME-02 sandbox script references and typed slots linking GAME-01 input, GAME-04 state/ability/quest/loot, WORLD-02 scenes/prefabs, SIM-04 animation, AUD-04 cue and DATA content. No genre-specific Core extension, second tick/ECS/physics/network/event dispatcher or native arbitrary plugin host.

- Feature composition has deterministic precedence, collision detection, capability constraints, target compatibility, graph depth/size quotas, provenance and rights.
- Editor/CLI/MCP use identical staged, validated, role-checked DATA-04 CAS commands. A preview is read-only and no untrusted template can execute code or fetch dependencies during import.
- Templates are templates **for source creation**, not shipping asset/data packs or a right to distribute somebody else's art. Ship only original or separately audited, approved and attributed assets.
- Public packs may describe offline/puzzle, server-authoritative shooter or ARPG profiles; NET remains the authority and may be absent when offline. A declarative `net_ready` flag is not proof.
- A future test must create at least two independently original genres from the same immutable engine revision, build/export across agreed desktop targets/Web capability, and verify no Core patch or exploit.
- ADR establishes no concrete C++ package code, serialized schema pin, release class, numeric budget or dependency adoption.

## Evaluated alternatives
| Choice | Strength | Limitation / ruling |
|---|---|---|
| Per-genre engine forks | maximum customization | prohibited maintenance, security and ABI divergence; conflicts with catalog acceptance |
| Hardcoded genre subclasses inside CORE | simple demos initially | giant engine policy surface, Core rebuild for a new genre; reject |
| Pure external C++/native plugins | power and compiled speed | ABI, security, signing and platform distribution complexity; FUTURE separate permission/ABI ADR, not untrusted baseline |
| Shared monolithic sample game | quick showpiece | hard to prove reusable genre systems or clean exports |
| Stormline source-level pack manifest, pure data + bounded script | reproducible composition, provenance, same rules across targets | migration/validation complexity, must prove tool UX, benchmark and security; **leading proposal** |
| Adopt a foreign engine's plugin runtime (Unreal Lyra/O3DE/Unity) | proven production examples | platform coupling, incompatible ABI/license and copied IP; **references only** |

## Evidence, hazards and consequences
**Pros:** original templates with shared data/rights/authority contracts, bounded add-on complexity, portable reproducible project generation, reusable test suites. **Cons:** schema evolution, migration, dependency resolver, capability failures, potential overabstraction; prove with smallest vertical sample and a second distinct genre before broadening. Do not build seven game frameworks at once or invent a content marketplace.

Candidate reference frameworks: Godot MIT demo projects ([source](https://github.com/godotengine/godot-demo-projects), project-level asset audits still required), Bevy engine **MIT OR Apache-2.0** ([source](https://github.com/bevyengine/bevy)), O3DE engine **Apache-2.0 OR MIT with separate 3P terms** ([license](https://github.com/o3de/o3de/blob/development/LICENSE.txt)), Stride **MIT except individual third-party files** ([source](https://github.com/stride3d/stride)), proprietary Unreal Lyra modular experience and Unity character samples **reference only, no assets/code copied**. No dependency adopted.

**Security and risk:** P00 research LOW; later implementation ELEVATED for untrusted source/asset graphs, scripting, authoring transactions and target export; privileged irreversible money or native executable plugin admissions HIGH_ASSURANCE and separately out of baseline. Never present template examples as permission to mimic copyrighted game designs/assets.

**Approval gate:** approved versioned API, direct fixture proof, 128 future cases, numeric benchmark targets, real Windows/Linux/macOS/Web gate, exact pins/rights/SBOM, owner-approved production ADR and Scope/DoD, prerequisites implemented. No technical decision is owner-approved by this documentary merge, no Zcode coding and ALL 80 implementation packets remain blocked.
