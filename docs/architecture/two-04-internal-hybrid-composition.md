# TWO-04 — Internal logical hybrid composition pipeline

**Status:** `APPROVED INTERNAL ARCHITECTURE / LOGICAL METADATA ONLY`. **ADR:** [ADR-0126](../adr/0126-two-04-internal-hybrid-composition.md). **Planning policy remains:** [ADR-0025](../adr/0025-two-04-depth-order-hybrid-composition-policy.md) `PROPOSED`. **Runtime renderer claims:** none.

## 1. Purpose

Define a bounded, deterministic metadata layer that records how a project intends to combine 2D and 3D content, without executing any rendering. The pipeline answers: which projection was requested, which layer order and composition mode apply, how objects tie-break for sorting, and which hybrid effect bridges were requested. It does not answer how many pixels were drawn or whether the GPU produced them.

## 2. Logical model

- **Camera intent:** projection kind, near/far planes, orthographic half-height/aspect or perspective field of view/aspect, revision and identity. Values must be finite and positive where required. No matrix is composed.
- **Layer intent:** layer identity/revision, composition mode (`SharedDepthWorld`, `OrderedCanvasOverlay`, `IsolatedSubview`), stable author order, depth-test/write intent, alpha policy (`Opaque`, `Masked`, `Blended`) and object count.
- **Sort intent:** bounded opaque object references with layer order, depth key and tie-breaker; deterministic stable ordering is produced as metadata, not a GPU draw list.
- **Effect bridge intent:** lit/unlit request, shadow proxy request, subview maximum width/height and recursion bound, fallback reason when a bridge cannot be represented.
- **Diagnostics:** typed error plus source ID and index; outputs reset on failure.

## 3. Composition modes

- `SharedDepthWorld`: requests one compatible world-depth interpretation; opaque/masked metadata may request depth write, blended metadata must not request depth write.
- `OrderedCanvasOverlay`: requests stable painter order; depth test/write requests are invalid because no world depth is promised.
- `IsolatedSubview`: requests a bounded child view; depth transfer to the parent is not promised, and subview identity/recursion must be explicit.

Invalid mode/policy combinations fail closed with a typed error. No silent fallback is permitted.

## 4. Ownership boundaries

- TWO-01 owns Canvas sprite/layer painter behavior.
- GFX-03 owns depth/stencil attachments, graph hazards and render targets.
- GFX-04 owns mesh visibility/bounds; GFX-05 materials/alpha; GFX-06 lighting/shadows; GFX-07 cameras/post/output.
- TWO-02/TWO-03 own tilemap/animation metadata; DATA-04 owns scene revisions/transactions.
- PHYS/WORLD own collision and gameplay truth; sort points and visual alpha never define collision.
- TWO-04 owns only the logical intent records and their validation.

## 5. Determinism and bounds

All plans are fixed-capacity, header-only, `noexcept` and allocation-free. Capacities are frozen in `-02`; slicing and overload behavior must be deterministic across compilers. No clock, random source, file, network, audio, GPU, thread or global state is allowed.

## 6. Planned slices

| Slice | Logical deliverable | Oracle |
|---|---|---|
| `-03` | orthographic/perspective camera intent | CAM-01 |
| `-04` | 2D/3D layer and composition-mode intent | LAY-01 |
| `-05` | deterministic bounded sort intent | SRT-01 |
| `-06` | hybrid effect bridge intent | EFE-01 |
| `-07` | integrated qualification | QLF-T401..T404 |
| `-08` | closeout | evidence/audit |

`-02` must freeze exact types, capacities, error codes, allowlists and test fixtures before `-03` is activated.

## 7. Explicit non-goals

No camera matrix evaluation, frustum culling, render graph execution, depth attachment creation, GPU resource lifetime, shader compilation, material evaluation, lighting solve, subview rendering, temporal history, editor viewport, importer, export, hardware measurement or public ABI. ADR-0025 remains the separate planning authority for those future runtime decisions.
