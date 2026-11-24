# SIM-03 governance contract v0 — internal logical character motor metadata

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO CHARACTER RUNTIME`. **ADR:** [ADR-0134](../adr/0134-sim-03-internal-character-motor-metadata.md). **Architecture:** [sim-03-internal-character-motor-metadata](../architecture/sim-03-internal-character-motor-metadata.md). **Planning-only policy:** [ADR-0033](../adr/0033-sim-03-authoritative-character-motor-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal SIM-03 sequence: logical controller profile descriptors, locomotion descriptors, input response intent and decoupled camera intent. It does not authorize a motor, sweeper, contact query, solver, input device layer, camera transform, animation root motion, ECS mutation, editor UI or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid dimensions, modes, tick windows, speeds or references produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** SIM-01/02 own collision/physics, CORE-03/04/06 own jobs/tick, WORLD-01/02 own entities/scenes, GAME/NET own input authority, SIM-04 owns root motion, GFX/editor own camera rendering.
3. **GOV-003 Identity separation:** controller/locomotion/camera metadata is not a solver or motor handle and never exposes backend types or raw pointers.
4. **GOV-004 Determinism:** fixed-capacity plans, stable ordering where required, integer tick windows only, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no motor, collision-gated movement, camera update, input polling, contact/event, replay or gameplay-feel benchmark.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Controller intent: dimension, mode, extents, up axis, ground/step/slope policies.
- Locomotion intent: speeds, acceleration, jump/dash descriptors, tick-based windows.
- Input intent: action/axis descriptors and buffering metadata.
- Camera intent: follow/look/damping descriptors and independence flags.
- Common diagnostic and capacity types under `src/stormline/character/`.

Exact type names, capacities, error enums and allowlists are frozen by `SIM-03-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| CTRL-01 | controllers | dimension/mode allowlists, finite extents, up axis, policy flags |
| LOCO-01 | locomotion | finite speeds, acceleration bounds, tick windows, jump/dash descriptors |
| INPUT-01 | input response | bounded actions/axes, dead zones, buffer windows |
| CAM-01 | decoupled camera | finite offsets/damping, independence flags, no transform write |
| QLF-S301 | integrated | controller -> locomotion -> input -> camera |
| QLF-S302 | deterministic repeat | identical plans/counts |
| QLF-S303 | failure recovery | typed error followed by valid operation |
| QLF-S304 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Motor/sweeper/contact execution, solver/backend, input devices, camera update, animation root motion, ECS mutation, replay/snapshot, editor, GPU, audio, export, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not the catalog's golden movement replay/FPS-variation suite, gameplay-feel, security, soak or performance qualification. SIM-03 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
