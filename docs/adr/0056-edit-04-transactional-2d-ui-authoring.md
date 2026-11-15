# ADR-0056 — Shared Semantic 2D Authoring, Transactional Tile Painting and Runtime-Parity UI Preview

**STATUS: PROPOSED / NOT OWNER-APPROVED / NOT CODE AUTHORIZATION** | 2026-11-15 | Research [#264](https://github.com/KayzenRoot/stormline/issues/264), WO NLE-P00-WO-002-EDIT-04, future code #71 OPEN/BLOCKED | BASE `8036d723dbf07c13020536cf9a0550bb5afb4b32`.

## Context and decision drivers
Catalog EDIT-04 (53/80) requires *"Projeto 2D completo construído pela interface sem acesso direto a arquivos"* as a **future** executable acceptance condition. Formal prerequisites EDIT-02 and TWO-02 have documentary research/PROPOSED ADRs but no engine. Avoid duplicate renderers, UI tree, tile serializer, scheduler, animation evaluator, undo manager and unsafe external code. Cross-OS professional workflows and AI-native authoring must be both usable and auditable.

## PROPOSED decision (not adopted)
1. EDIT-04 owns the **semantic 2D editor facade and UX** only. A typed `Edit2DCommandV1/PreviewV1/TransactionV1/ReceiptV1` is common for toolbar/buttons, keyboard, CLI and MCP with per-actor scoped capability, expected canonical revision, idempotency and explicit confirmation.
2. Canonical tiles: TWO-02 sparse 64-bit signed grid and stable tile/atlas IDs. Deterministic batch stroke with halo, cross-chunk edits shown before commit, bounded rules/seeds; DATA-04 owns scene persistence/journal/undo/redo/CAS, no independently saved editor map or GPU source.
3. Canvas transforms are typed across DIP/physical/world/grid/atlas, DPI/device-epoch checked, anchored zoom/pan with pixel-art mode. TWO-01/GFX render and hit-test plans; EDIT-04 UI never allocates GPU resources or assumes frame-accurate GPU pick.
4. UI authoring targets GAME-03's **single retained semantic UiTreeV1**, responsive layout and text/RTL/focus rules. EDIT-04 previews the same GAME-03 layout on GFX-07/TWO-01, not a second CSS engine or font shaping stack. Layout algorithm (Yoga/RmlUi/first-party) remains GAME-03 ADR-0044 PROPOSED pending benchmarks.
5. Timeline editors author TWO-03 rational key/clip/rig contracts; TWO-03 owns playback/IK/tween evaluation. EDIT-07 play preview isolated, no gameplay side effects or implicit writes.
6. Imported Tiled/LDtk/other formats are treated as untrusted, bounded adapters under DATA-03/01, with loss report, no external path traversal or scripts; license/source/provenance checks before any vendor adoption. No native import/export guarantee yet.
7. Strict UI control parity: stable CommandId, accessible role/name/state/tooltip, keyboard/gamepad/touch route and same source revision permission check for all invocation origins. No direct file edit or arbitrary script from MCP.
8. Phased candidate: NECESSARY orthogonal canvas, grid/snap, atlas selection, tile paint/erase/terrain preview, editable UI with responsive anchors/flex baseline and flipbook/key timeline, undo/save/restore and accessible input; IMPORTANT isometric/hex, brush procedural pressure, full CSS grid, IK authoring and advanced skeletal features subject to approved release classes. FUTURE real-time collaboration, proprietary Spine editor integration, untrusted remote plugins and cloud sync. No features automatically become 1.0 mandatory from catalog alone.

## Considered alternatives and tradeoffs
- **Copy vendor editors:** mature UX but licensing/IP, portability, integration and loss of owned contracts make unacceptable as default.
- **Dedicated 2D mutable graph plus custom tile writer:** easier short-term UI but split persistence/undo authority and inconsistent scene snapshots, reject.
- **Immediate-mode GUI for entire game UI:** convenient editor but not sufficient semantic GAME-03 accessibility, localization and retained layout parity; editor shell toolkit remains separate EDIT-01 comparison.
- **Full web/HTML DOM UI authoring:** expressive but different engine/runtime rendering, security and bundle footprint, not assumed; consider conditional Web adapter only.
- **Adopt Tiled JSON or Spine as mandatory internal format/runtime:** external constraints and license compatibility, reject pending explicit proof and authorization.
- **Custom unified engine-core at first increment:** broad high-risk scope without executable baselines, reject.

## Risks, obligations and non-goals
Risks: stale chunk/atlas revisions, overflow/negative-grid floor division, autotile neighbor corruption, wrong alpha/compositing, costly flood brush, lost focus/IME, inaccessible controls, layout cycles, Unicode bidi spoofing, malformed font/scene/animation data, version migration data loss, permission bypass via MCP, preview/game state leakage, device loss. Mitigate with typed bounds, capability gates, immutable previews, quota, deterministic seed, CAS/hash/last-good, redacted logs, per-owner receipt and fault injection. Security/privacy/dependency compliance remains unverified until runtime proof.

**Not decided:** engine source license NLE-D009, final UI/layout toolkit or dependency versions, schema/ABI, shipping release class, hardware budgets/OS minimums, accessibility certification, commercial rights for any third-party asset. These require separate approved technical decisions and actual tests.

## Acceptance evidence required before adopting
- Exactly 128 unique E04 future scenarios catalogued, zero claimed runtime passes.
- Scoped eight-document research PR and independent checkpoint PR each pass exact-final-HEAD Docs Validation, objective pt-BR audit, ordinary squash and main readback.
- Later proof: entire original 2D demo authored from GUI **without filesystem text editing**, reproducible open/save/reopen, cross-platform pixels/RTL/gamepad/accessibility, tile seam/undo/crash and performance; measured and owner-approved release scope.
- **Decision status remains PROPOSED.** All 80 coding WOs including #71 stay blocked regardless of research merge.

See [architecture](../architecture/edit-04-2d-ui-editor.md), [API](../contracts/edit-04-2d-ui-api.md) and [technology/license matrix](../research/edit-04-2d-ui-technology-license-matrix.md).
