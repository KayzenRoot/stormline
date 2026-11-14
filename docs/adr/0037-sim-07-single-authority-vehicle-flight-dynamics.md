# ADR-0037 — Stormline-owned Vehicle Commands and Single-Authority Physics

**STATUS: PROPOSED / NOT APPROVED FOR CODE**  
2026-11-14 | Research issue #192 | WO NLE-P00-WO-002-SIM-07 | Future implementation issue #57 OPEN/BLOCKED.

## Context
Vehicles span wheeled and tracked locomotion, buoyancy, flight and rotor thrust. A second third-party physics integrator running beside SIM-02 would break contacts and make replay/netcode ambiguous. GAME-01 and NET-02..04 authority must not be bypassed by custom vehicle controls. The project is in docs-only P00: even GAME-01 and NET code research are pending and no runtime engine exists.

## Proposed decision
1. **Engine-owned semantic public contract:** versioned VehicleAsset/Profile, VehicleHandle and SeatHandle, ControlIntent, ForcePlan, PhysicsAck, VehicleStateSnapshot, Water/WindSample, ControlAuthority/Capabilities and typed errors. No Jolt/JSBSim/Chrono/Bullet native C++ types, units or pointers cross Stormline public ABI.
2. **One physics owner:** SIM-02 owns rigid bodies, constraints, collision and global state integration. SIM-07 computes per-domain *bounded forces/torques/constraint settings* and applies only through SIM-02 validated pre-step request+post-step receipt. World transforms, character motion and contacts never applied directly from render or network.
3. **Road baseline:** Jolt Physics MIT `WheeledVehicleController` and `TrackedVehicleController` are **leading private adapter candidates** because SIM-02 itself already researches Jolt, but not selected/integrated. Project Chrono BSD-3-Clause is a high-fidelity research/reference comparator; direct second Chrono solver alongside Jolt is rejected unless later a completely explicit one-owner backend replacement and tested world migration.
4. **Water baseline:** authored volume-based buoyancy/drag and prop/rudder force model (not CFD), requiring WORLD-04 water/wave/current source versions; no authoritative force from purely rendered water height. Supports headless and capability-limited Web fallback.
5. **Flight baseline:** owned bounded 6DoF coefficient-based aero for wing and simplified rotor/actuator-disc forces, with explicit assistance modes and no real-world certification claims. JSBSim LGPL-2.1 Flight Dynamics Model is a **reference or separately evaluated adapter** with a licensing/integration proof obligation; its own solver cannot be double-stepped with SIM-02. Advanced helicopters/CFD/sea state/ground effect are FUTURE.
6. **Input/seat authority:** GAME-01 canonical remapped bounded controls, GAME/GAME-01 validated occupant/driver, SIM-03 enter/exit safe clearance. No privileged editor/MCP live vehicle force, damage, spoofed client seat or direct physics mutation.
7. **Network/time:** CORE-04 TickId, deterministic command-order/log, NET-02 authoritative headless and NET-03/04 snapshot/rollback owner, with World/Body/Seat generation, source/OriginEpoch. Cross-OS bitwise agreement not assumed.
8. **Safety/limits:** bound mass/inertia/force/steering, wheel/track/rotor table size and per-tick work, deny nonfinite values, stale profiles/world/wind/terrain and unauthorized control; serializable/recoverable authored sources through DATA-03/04/05. Consumer GFX/AUD only read receipts.
9. **License selection remains open:** exact upstream tags, ABI, transitive SPDX/SBOM, sample model rights and LGPL-2.1 build distribution requirements must be independently reviewed after engine license NLE-D009 is decided. Nothing adopted and no runtime approved.

## Rejected alternatives
- A per-vehicle custom free-running physics world/second integrator or a JSBSim full-state step and Jolt body step on same entity.
- GUI/particle/flight-camera transform presented as physics truth or network client force authority.
- Claiming physically certified flight/boat/tire realism without validated measured/oracle and fixture provenance.
- Mandatory CUDA/CFD/expensive proprietary middleware, aircraft XML arbitrary commands/plugin loads or unlicensed real-world vehicle data.
- Selecting Chrono simply because it has more simulation features, absent measured game runtime cost and integration contract.
- Releasing SIM-07 code from this PROPOSED ADR or expanding NECESSARY slice to all five vehicle domains.

## Tradeoffs and gate
Engine-owned adapters/force integration have higher validation burden but preserve single physics owner, portable headless/gameplay truth and source/license choice. High-fidelity references may help future physical regressions, but hard real-time and multiplayer require purpose-built budgets. Before code: approved SIM-02+SIM-03+GAME-01 runtime and relevant NET/world contracts, audited exact pinned vendor/rights/ABI, legal LGPL obligations, numeric/quality targets, next smallest NECESSARY code slice and ELEVATED/NET replay recovery tests. Until then ADR is PROPOSED; all 80 coding packets BLOCKED and #57 OPEN/BLOCKED.
