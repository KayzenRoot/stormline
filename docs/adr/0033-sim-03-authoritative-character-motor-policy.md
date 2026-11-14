# ADR-0033 — Engine-Owned Fixed-Tick Character Motor and Collision-Gated Movement

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
**2026-11-14 | Research #180 | WO NLE-P00-WO-002-SIM-03 | Future code #48 OPEN/BLOCKED**

## Context
SIM-01 and SIM-02 are only documentary research, with replaceable physics backends. A direct Jolt `CharacterVirtual` or Box2D mover exposed to game logic would lock the Stormline public ABI and weaken reproducibility, Web fallbacks and safety. Camera-driven or animation-frame-driven movement would also break independent headless and server semantics.

## Proposed decision
1. Keep versioned Stormline-owned `CharacterMotorProfile`, `CharacterIntent`, `MotorState`, `MotorMotionReceipt` and opaque generation-scoped handles as the stable public boundary.
2. Use **CORE-04 fixed TickId**, validated commands and pre-step barriers for intent; obtain authoritative 2D or 3D shape sweeps/contact from SIM-01/02 via narrow, replaceable capability interfaces. Render interpolation and camera are consumers, not authorities.
3. Prefer **kinematic query-driven locomotion as the default candidate** for player-controlled characters. Dynamic-assisted NPC/physical controllers may be opt-in after bounded solver evidence. Backend choice remains open. Jolt CharacterVirtual is a strong 3D adapter candidate, Box2D character mover 3.1+ is experimental 2D candidate, and Rapier APIs are a portability comparison, not dependencies selected.
4. Support explicit dimension, up-vector, units, ground/step/slope policies, moving platforms, one-way collision rules only where backend and profile support; fail closed for nonresident/corrupt ground and stale world/collider epochs.
5. Represent grace, buffered action and state transitions in integer ticks rather than wall-clock seconds. Any reusable dash/jump system is motor policy, not hardcoded genre rules.
6. Interoperate with SIM-04 root motion as an *intent request*, never an animation renderer transform directly overwriting authoritative position. NET prediction/reconciliation and GAME input ownership remain separate.
7. Treat deterministic replay as a future **proof obligation** scoped by backend, compiler/numeric profile, contact revisions and command order; do not promise bit-identical cross-platform results or rollback without complete solver state.

## Rejected candidates
- Proprietary controller behavior or third-party native object directly published as SDK contract: replaceability and licensing/ABI risk.
- Rigid body only, no kinematic controller: difficult to provide precise and consistent jump/step/slope semantics across action genres.
- GPU-driven character collision or rendering-derived movement authority: no portable headless/server/Web guarantee.
- Recreating collision solvers, ECS, input devices, pathfinding, ragdoll or network gameplay inside SIM-03: owner overlap and scope creep.

## Consequences, risks and approval gate
Benefits: one authoring schema for human/CLI/MCP, headless-compatible deterministic-command design, explicit 2D/3D contract. Costs: adapters may need implementation-specific contact filtering and extra sweeps, CPU memory/time budgets, an explicit capability matrix, more edge cases and character-platform lifecycle handling.

**No libraries are installed, no executable tests ran, no performance or gameplay feel claim is proven.** Approve versioned backend license/ABI and World/Physics/CORE contracts only after predecessors are implemented and evaluated, and scope/release-class/DoD are formally locked. Until then the proposed ADR must NOT be promoted and coding #48 stays BLOCKED.
