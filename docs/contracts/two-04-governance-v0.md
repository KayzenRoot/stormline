# TWO-04 governance contract v0 — internal logical hybrid composition

**Status:** `APPROVED GOVERNANCE / INTERNAL_ONLY / NO RUNTIME RENDERING`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Architecture:** [two-04-internal-hybrid-composition](../architecture/two-04-internal-hybrid-composition.md). **Planning-only policy:** [ADR-0025](../adr/0025-two-04-depth-order-hybrid-composition-policy.md) remains `PROPOSED`.

## 1. Scope

This contract governs the internal TWO-04 sequence: logical camera projection intent, 2D/3D layer intent, deterministic sort intent and hybrid effect bridge intent. It does not authorize runtime rendering, GPU resources, shaders, matrices, lighting, subview execution, editor UI, export, hardware measurement or public ABI.

## 2. Invariants

1. **GOV-001 Fail closed:** invalid IDs, revisions, modes, policies, finite values, capacity or timing produce a typed error and zeroed output; no silent fallback.
2. **GOV-002 Single authority:** GFX-03 owns depth attachments, GFX-04 meshes, GFX-05 materials, GFX-06 lighting, GFX-07 cameras/output, TWO-01 Canvas order, DATA-04 scene revisions, PHYS/WORLD collision truth.
3. **GOV-003 Mode explicitness:** `SharedDepthWorld`, `OrderedCanvasOverlay` and `IsolatedSubview` are distinct. Invalid mode/policy combinations must fail; painter order and world depth must never be conflated silently.
4. **GOV-004 Determinism:** bounded fixed-capacity plans, stable sort tie-breaking, no allocation, exception, file, network, audio, GPU, clock, thread or global state.
5. **GOV-005 No runtime claim:** no matrix evaluation, frustum culling, draw list, shader, render graph, depth attachment, subview execution, frame timing or visual proof.
6. **GOV-006 Diagnostics:** every error carries a typed code, source ID and bounded index; output plans are reset before validation.
7. **GOV-007 Traceability:** one stable Work Order ID across issue, branch, PR, evidence and corrections; exact allowlists per slice.

## 3. Planned API areas (frozen only in `-02`)

- Camera projection intent: orthographic/perspective kind, near/far, ortho half-height/aspect or perspective fov/aspect, identity/revision.
- Layer intent: identity/revision, composition mode, stable order, depth test/write intent, alpha policy, object count.
- Sort intent: bounded object IDs/revisions, layer order, depth key, stable tie-breaker, deterministic output order.
- Effect bridge intent: lit/unlit, shadow proxy, subview width/height/recursion, fallback reason.
- Common diagnostic and capacity types under `src/stormline/hybrid/`.

Exact type names, capacities, error enums and allowlists are frozen by `TWO-04-02` before implementation. No code may be created from this governance contract alone.

## 4. Slice oracles

| ID | Scenario | Oracle |
|---|---|---|
| CAM-01 | camera intent | projection kind, finite positive parameters, near < far, bounds |
| LAY-01 | layers | unique IDs, explicit mode, order, depth/alpha policy validity |
| SRT-01 | sorting | deterministic stable order, ties, capacity, no duplicate object IDs |
| EFE-01 | effect bridges | lit/shadow intent, subview bounds/recursion, fallback receipt |
| QLF-T401 | integrated | camera -> layer -> sort -> effect |
| QLF-T402 | deterministic repeat | identical plans/order |
| QLF-T403 | failure recovery | typed error followed by valid operation |
| QLF-T404 | bounded overload | 10,000 attempts keep caps |

## 5. Out of scope

Renderer, GPU backend, depth/stencil attachment, render graph, shader, material, lighting, shadow, subview render, camera matrix, frustum, editor viewport, importer, export, audio, physics, navigation, hardware, performance, ABI, release and production readiness.

## 6. Qualification statement

Passing internal CI qualification is not physical, OS, security, soak, visual or performance qualification. TWO-04 may close only as `INTERNAL_SEQUENCE_COMPLETE_NOT_QUALIFIED`.
