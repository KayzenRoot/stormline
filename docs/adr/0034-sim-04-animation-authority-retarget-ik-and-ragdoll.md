# ADR-0034 — Stormline-Owned Animation Graph, Root-Motion Authority and Physics-Ragdoll Boundary

**Status: PROPOSED / NOT APPROVED FOR ENGINE CODE**  
**Date:** 2026-11-14 | Research issue #183 | WO NLE-P00-WO-002-SIM-04 | Future coding issue #49 OPEN/BLOCKED.

## Context
GlTF, ozz-animation and ACL offer useful standards or specialized kernels but cannot by themselves define Stormline's gameplay authority, retarget/IK semantics, assets, graph authoring or ragdoll lifetime. SIM-03 controls character motion and SIM-02 physics contact/rigid bodies. A render-frame-driven animation controller that overwrites world transforms would break replay and server/headless execution. Existing 2D/cinematic owner TWO-03 must not be duplicated.

## Proposed decision
1. **Engine-owned versioned boundary:** Stormline owns Skeleton/Clip/AnimationGraph/RetargetProfile/RagdollProfile, session handles with generation and world/asset epoch, typed revisioned source and state/receipt schemas. Never expose ozz/ACL/Jolt native types in public API.
2. **Clock and evaluation:** CORE-04 fixed TickId and validated graph parameters drive gameplay-significant transitions/markers. CPU pose sampling/headless baseline. Renderer interpolation is read-only and does not own event timing.
3. **Root motion request/ack:** Clip-root deltas are sampled before SIM-03 move; SIM-03 acceptance/collision constrains applied displacement. Graph may use authoritative applied-motion receipt for phase corrective feedback but cannot modify entity physics. World/NET authority is external to SIM-04.
4. **Ragdoll ownership:** SIM-02 exclusively owns bodies, constraints and physics lifecycle. SIM-04 requests activation/deactivation and consumes immutable PHYS snapshots; transition/recovery must be safe, bounded and acknowledged by SIM-03 when character motor is relevant.
5. **Retarget and IK:** Authored joint-mapping profiles, stable semantic/bind-space basis, bounded analytic/iterative IK, physics-contact-derived foot placement and per-chain failure fallback. Per-instance pose stages order explicitly.
6. **Compression and backend:** ozz-animation (MIT) is **leading CPU runtime candidate**, ACL (MIT) **optional alternative clip compression/decompression component**, not automatically plug compatible with ozz native clip runtime. An adapter/coherent Stormline pose contract must be benchmarked; no double codec or automatic speed assumption. glTF 2.0 import is a candidate via DATA-03 with strict rights, parser validation and optional extension allowlisting. All third-party pins remain **UNSELECTED**.
7. **Transport and AI authoring:** Editor, CLI and MCP stage graph authoring via shared validated kernel/CAS and receipts. Never expose direct arbitrary bone mutation in untrusted tool calls or sidestep game/physics permissions.
8. **Evidence:** runtime speed, low memory, quality and deterministic replay are **FUTURE PROOF OBLIGATIONS**. Test at multiple hardware tiers and browser; cross-OS bitwise equivalence not claimed.

## Rejected alternatives
- Unconditional vendor runtime as SDK public ABI: couples formats, license updates and future replacement.
- GPU-only graph evaluation: fails headless/server/Web fallback and deterministic event order.
- Animation-derived direct ECS/physics teleport or hidden ragdoll solver: violates SIM-03/SIM-02 authority.
- Automatically bundling proprietary FBX tooling/sample motion datasets: rights and redistribution risks.
- Mandatory neural/motion-matching runtime without measured quality, provenance, reproducibility or cost baseline.

## Trade-offs
Owned graph/schema and adapters cost engineering effort but preserve independent renderer/physics and a stable public API. CPU headless path adds memory/compute that must be measured. Lossy compression needs objective bone/world error limits and perceptual testing. IK grounding must reconcile physics revisions without false support. Feature tiers must expose explicit capability/failure receipts, not silent divergence.

## Approval and stop gate
PROPOSED only. Before coding #49, secure approved upstream code contracts (DATA-03/SIM-03/SIM-02/CORE and relevant WORLD/GFX), pinned SDK tags and SBOM/attribution, signed-off release class, typed API, narrow NECESSARY code slice, actual tests, budget thresholds and Context Lock. Until all accepted, `executor_ready=false`; no library integrated and no benchmark, test execution, demo or runtime delivered.
