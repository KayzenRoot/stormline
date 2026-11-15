# EDIT-03 — Exactly 128 FUTURE Scene, World and Terrain Acceptance Tests

**2026-11-15 | research [#260](https://github.com/KayzenRoot/stormline/issues/260) | WO NLE-P00-WO-002-EDIT-03 | coding [#70](https://github.com/KayzenRoot/stormline/issues/70) OPEN/BLOCKED.** Exactly unique IDs **E03-T001..E03-T128**, all **FUTURE / NOT EXECUTED**: executed=0, passed=0, failed=0. No functioning editor, ECS, terrain, GFX viewport, scene/prefab serializer, streaming or test harness exists. Docs Validation is **documentation CI only**.

## Future test evidence requirements
Every executable future test needs real Git base/head source SHA and binaries, approved ADR/schema and source code license, OS Windows/Linux X11+Wayland/macOS and renderer/backend/hardware tier, original synthetic project+scene+terrain asset fixtures with recorded seed and permissions, WORLD-01 generational IDs, WORLD-04 tile and layer schema, DATA-02 AssetId and DATA-04 expected revision plus original/final on-disk hashes, action/transaction receipt with undo and crash injection point, comparison of semantic before/after and save/reopen/restore, scene-aware keyboard/accessibility evidence, GFX device loss/ref counts if applicable, redacted logs, exact CI/test commands and risk/defect/correction evidence. Use real source and VFS, not just mocked editor events.

Real code must prove **"Editar terreno/objetos, salvar e restaurar sem regressão"** including canonical scene/terrain files after fresh restart and deterministic diff/undo for at least one 2D/3D scene, multiple objects and terrain tile. Rendering or a preview screenshot alone cannot satisfy. Use actual owner-approved quantization tolerance; no made-up pixel or frame budgets. Multi-select batch semantics explicit, all-or-nothing or enumerated partial failures. Future terrain CPU/GPU results compare approved tolerance, not exact floating-point matches across ISA by assumption.

| ID | Domain | Future assertion | Status |
|---|---|---|---|
## Hierarchy and stable identity
| E03-T001 | Hierarchy and stable identity | create one original 2D scene with stable node IDs future | FUTURE / NOT EXECUTED |
| E03-T002 | Hierarchy and stable identity | create original 3D scene with typed root future | FUTURE / NOT EXECUTED |
| E03-T003 | Hierarchy and stable identity | rename parent without changing child stable IDs future | FUTURE / NOT EXECUTED |
| E03-T004 | Hierarchy and stable identity | reparent node without path-based reference break future | FUTURE / NOT EXECUTED |
| E03-T005 | Hierarchy and stable identity | reject a hierarchy cycle before mutation future | FUTURE / NOT EXECUTED |
| E03-T006 | Hierarchy and stable identity | delete an entity invalidates old generation selection future | FUTURE / NOT EXECUTED |
| E03-T007 | Hierarchy and stable identity | virtualized tree locates 10000 synthetic nodes future | FUTURE / NOT EXECUTED |
| E03-T008 | Hierarchy and stable identity | hierarchy save/reopen preserves exact order and refs future | FUTURE / NOT EXECUTED |
## Selection and inspector reflection
| E03-T009 | Selection and inspector reflection | select multiple nodes with keyboard range future | FUTURE / NOT EXECUTED |
| E03-T010 | Selection and inspector reflection | multi-selection mixed property state visible future | FUTURE / NOT EXECUTED |
| E03-T011 | Selection and inspector reflection | CORE-05 type metadata validates property units future | FUTURE / NOT EXECUTED |
| E03-T012 | Selection and inspector reflection | typed inspector rejects out-of-range scalar future | FUTURE / NOT EXECUTED |
| E03-T013 | Selection and inspector reflection | inspect stale EntityId without memory access future | FUTURE / NOT EXECUTED |
| E03-T014 | Selection and inspector reflection | different component types allow partial read only future | FUTURE / NOT EXECUTED |
| E03-T015 | Selection and inspector reflection | all-or-nothing batch edit rejects failed target future | FUTURE / NOT EXECUTED |
| E03-T016 | Selection and inspector reflection | selection after cell unload shows recoverable placeholder future | FUTURE / NOT EXECUTED |
## Gizmo transform math
| E03-T017 | Gizmo transform math | world translation under rotated parent future | FUTURE / NOT EXECUTED |
| E03-T018 | Gizmo transform math | local rotation with normalized quaternion future | FUTURE / NOT EXECUTED |
| E03-T019 | Gizmo transform math | parent-space nonuniform scale preserves intended transform future | FUTURE / NOT EXECUTED |
| E03-T020 | Gizmo transform math | zero scale singular parent transform safely rejected future | FUTURE / NOT EXECUTED |
| E03-T021 | Gizmo transform math | negative scale and mirror handedness documented future | FUTURE / NOT EXECUTED |
| E03-T022 | Gizmo transform math | multi-select pivot applied without parent-child double transform future | FUTURE / NOT EXECUTED |
| E03-T023 | Gizmo transform math | NaN and infinity input refused before commit future | FUTURE / NOT EXECUTED |
| E03-T024 | Gizmo transform math | world origin rebasing preserves gizmo coordinates future | FUTURE / NOT EXECUTED |
## Gizmo interaction and snapping
| E03-T025 | Gizmo interaction and snapping | axis-lock constrained drag deterministic future | FUTURE / NOT EXECUTED |
| E03-T026 | Gizmo interaction and snapping | grid distance snapping on X Y Z future | FUTURE / NOT EXECUTED |
| E03-T027 | Gizmo interaction and snapping | angular snapping around active pivot future | FUTURE / NOT EXECUTED |
| E03-T028 | Gizmo interaction and snapping | surface snap respects collision/visibility policy future | FUTURE / NOT EXECUTED |
| E03-T029 | Gizmo interaction and snapping | numeric keyboard transform equals pointer target future | FUTURE / NOT EXECUTED |
| E03-T030 | Gizmo interaction and snapping | Escape cancels preview without source edit future | FUTURE / NOT EXECUTED |
| E03-T031 | Gizmo interaction and snapping | pointer drag commits one grouped scene undo future | FUTURE / NOT EXECUTED |
| E03-T032 | Gizmo interaction and snapping | gizmo scale changes with DPI without wrong pointer transform future | FUTURE / NOT EXECUTED |
## GPU picking and viewport
| E03-T033 | GPU picking and viewport | GFX object-ID picking resolves correct EntityId generation future | FUTURE / NOT EXECUTED |
| E03-T034 | GPU picking and viewport | async GPU pick rejects stale frame epoch future | FUTURE / NOT EXECUTED |
| E03-T035 | GPU picking and viewport | picker ignores hidden and unauthorized objects future | FUTURE / NOT EXECUTED |
| E03-T036 | GPU picking and viewport | transparent overlapping object target policy tested future | FUTURE / NOT EXECUTED |
| E03-T037 | GPU picking and viewport | selection after streamed cell unload rejects old hit future | FUTURE / NOT EXECUTED |
| E03-T038 | GPU picking and viewport | 2D editor viewport coordinates mapped to world correctly future | FUTURE / NOT EXECUTED |
| E03-T039 | GPU picking and viewport | 3D viewport device loss preserves authored source future | FUTURE / NOT EXECUTED |
| E03-T040 | GPU picking and viewport | viewport hidden/occluded throttles without sim clock change future | FUTURE / NOT EXECUTED |
## Undo redo and atomic commits
| E03-T041 | Undo redo and atomic commits | undo scene edit does not alter EDIT-01 layout history future | FUTURE / NOT EXECUTED |
| E03-T042 | Undo redo and atomic commits | redo restores identical canonical DATA-04 hash future | FUTURE / NOT EXECUTED |
| E03-T043 | Undo redo and atomic commits | drag stroke coalesces into bounded undo transaction future | FUTURE / NOT EXECUTED |
| E03-T044 | Undo redo and atomic commits | scene transaction CAS conflict refuses stale overwrite future | FUTURE / NOT EXECUTED |
| E03-T045 | Undo redo and atomic commits | idempotent retry cannot insert duplicate entity future | FUTURE / NOT EXECUTED |
| E03-T046 | Undo redo and atomic commits | crash after source commit before UI receipt recovers once future | FUTURE / NOT EXECUTED |
| E03-T047 | Undo redo and atomic commits | disk full during multi-file write preserves last-good future | FUTURE / NOT EXECUTED |
| E03-T048 | Undo redo and atomic commits | undo after foreign revision requires explicit rebase or conflict future | FUTURE / NOT EXECUTED |
## Prefab definitions and instances
| E03-T049 | Prefab definitions and instances | prefab source creates two stable instance IDs future | FUTURE / NOT EXECUTED |
| E03-T050 | Prefab definitions and instances | edit instance override doesn't change sibling future | FUTURE / NOT EXECUTED |
| E03-T051 | Prefab definitions and instances | nested prefab instance preserves stable child references future | FUTURE / NOT EXECUTED |
| E03-T052 | Prefab definitions and instances | recursive prefab graph cycle refused before allocation future | FUTURE / NOT EXECUTED |
| E03-T053 | Prefab definitions and instances | apply override to source needs explicit permission future | FUTURE / NOT EXECUTED |
| E03-T054 | Prefab definitions and instances | revert override restores base without losing unrelated overrides future | FUTURE / NOT EXECUTED |
| E03-T055 | Prefab definitions and instances | source upgrade triggers three-way conflict instead of silent deletion future | FUTURE / NOT EXECUTED |
| E03-T056 | Prefab definitions and instances | duplicate prefab remaps internal references correctly future | FUTURE / NOT EXECUTED |
## Prefab variants and composition
| E03-T057 | Prefab variants and composition | variant layers have explicit source ordering future | FUTURE / NOT EXECUTED |
| E03-T058 | Prefab variants and composition | tombstoned child remains stable under reimport future | FUTURE / NOT EXECUTED |
| E03-T059 | Prefab variants and composition | missing source AssetId causes clear degraded read-only state future | FUTURE / NOT EXECUTED |
| E03-T060 | Prefab variants and composition | asset rename preserves prefab provenance future | FUTURE / NOT EXECUTED |
| E03-T061 | Prefab variants and composition | unknown required field in prefab patch refuses commit future | FUTURE / NOT EXECUTED |
| E03-T062 | Prefab variants and composition | override semantic diff roundtrip preserves original fields future | FUTURE / NOT EXECUTED |
| E03-T063 | Prefab variants and composition | source vs instance property inspector provenance displayed future | FUTURE / NOT EXECUTED |
| E03-T064 | Prefab variants and composition | scene serialization and importer no foreign source license assumption future | FUTURE / NOT EXECUTED |
## Terrain sculpting and heightfield
| E03-T065 | Terrain sculpting and heightfield | raise brush changes only committed target height tiles future | FUTURE / NOT EXECUTED |
| E03-T066 | Terrain sculpting and heightfield | lower brush clamps within declared quantization policy future | FUTURE / NOT EXECUTED |
| E03-T067 | Terrain sculpting and heightfield | smooth with fixed kernel has deterministic expected values future | FUTURE / NOT EXECUTED |
| E03-T068 | Terrain sculpting and heightfield | flatten brush references explicit world elevation future | FUTURE / NOT EXECUTED |
| E03-T069 | Terrain sculpting and heightfield | stamp with bounded dimensions rejects oversize image future | FUTURE / NOT EXECUTED |
| E03-T070 | Terrain sculpting and heightfield | erosion seed and version reproduce semantic terrain delta future | FUTURE / NOT EXECUTED |
| E03-T071 | Terrain sculpting and heightfield | heightfield cave overhang request returns unsupported type future | FUTURE / NOT EXECUTED |
| E03-T072 | Terrain sculpting and heightfield | brush across terrain tile boundary stitches height and normals future | FUTURE / NOT EXECUTED |
## Terrain splatmaps and masks
| E03-T073 | Terrain splatmaps and masks | weightmap paint updates selected material layer only future | FUTURE / NOT EXECUTED |
| E03-T074 | Terrain splatmaps and masks | weight channels normalize with declared rounding policy future | FUTURE / NOT EXECUTED |
| E03-T075 | Terrain splatmaps and masks | holes layer preserves adjacent height when toggled future | FUTURE / NOT EXECUTED |
| E03-T076 | Terrain splatmaps and masks | terrain manual paint survives procedural regeneration future | FUTURE / NOT EXECUTED |
| E03-T077 | Terrain splatmaps and masks | layer reorder changes composition deterministically future | FUTURE / NOT EXECUTED |
| E03-T078 | Terrain splatmaps and masks | destructive flatten requires explicit backup and approval future | FUTURE / NOT EXECUTED |
| E03-T079 | Terrain splatmaps and masks | corrupt paint mask dimension rejects before allocation future | FUTURE / NOT EXECUTED |
| E03-T080 | Terrain splatmaps and masks | untrusted texture shader reference cannot run script future | FUTURE / NOT EXECUTED |
## Foliage and procedural terrain
| E03-T081 | Foliage and procedural terrain | stable foliage instance IDs after density repaint future | FUTURE / NOT EXECUTED |
| E03-T082 | Foliage and procedural terrain | seed and cell origin reproduce deterministic scatter future | FUTURE / NOT EXECUTED |
| E03-T083 | Foliage and procedural terrain | foliage placement density cap never exceeds memory budget future | FUTURE / NOT EXECUTED |
| E03-T084 | Foliage and procedural terrain | undo foliage erasure restores original refs future | FUTURE / NOT EXECUTED |
| E03-T085 | Foliage and procedural terrain | regenerated procedural source preserves manual overrides future | FUTURE / NOT EXECUTED |
| E03-T086 | Foliage and procedural terrain | foliage GPU instance buffer is cache not source future | FUTURE / NOT EXECUTED |
| E03-T087 | Foliage and procedural terrain | invalid procedural graph version refuses unsafe overwrite future | FUTURE / NOT EXECUTED |
| E03-T088 | Foliage and procedural terrain | foliage neighbor cell edge continuity checked future | FUTURE / NOT EXECUTED |
## World streaming and LOD
| E03-T089 | World streaming and LOD | loaded cell generation required to edit future | FUTURE / NOT EXECUTED |
| E03-T090 | World streaming and LOD | unloaded cell metadata visible but not mutable future | FUTURE / NOT EXECUTED |
| E03-T091 | World streaming and LOD | dirty cell cannot silently unload future | FUTURE / NOT EXECUTED |
| E03-T092 | World streaming and LOD | streaming camera move doesn't drop pending brush edits future | FUTURE / NOT EXECUTED |
| E03-T093 | World streaming and LOD | LOD seam across two terrain cells remains within tolerance future | FUTURE / NOT EXECUTED |
| E03-T094 | World streaming and LOD | HLOD regeneration doesn't overwrite canonical entities future | FUTURE / NOT EXECUTED |
| E03-T095 | World streaming and LOD | double precision world origin shift keeps long-range selection future | FUTURE / NOT EXECUTED |
| E03-T096 | World streaming and LOD | streaming memory pressure yields bounded cancel/retry future | FUTURE / NOT EXECUTED |
## Persistence and recovery
| E03-T097 | Persistence and recovery | scene reopened from DATA-04 matches semantic source diff future | FUTURE / NOT EXECUTED |
| E03-T098 | Persistence and recovery | terrain layers reopened produce same final heightfield future | FUTURE / NOT EXECUTED |
| E03-T099 | Persistence and recovery | process killed during brush stage leaves no committed partial stroke future | FUTURE / NOT EXECUTED |
| E03-T100 | Persistence and recovery | process killed after commit recovers idempotent history future | FUTURE / NOT EXECUTED |
| E03-T101 | Persistence and recovery | backup and rollback after corrupt scene schema preserves original future | FUTURE / NOT EXECUTED |
| E03-T102 | Persistence and recovery | world multi-cell save marker recovers consistent state future | FUTURE / NOT EXECUTED |
| E03-T103 | Persistence and recovery | power loss durability verified only by OS/FS controlled evidence future | FUTURE / NOT EXECUTED |
| E03-T104 | Persistence and recovery | compatibility with unknown scene format returns read-only or deny future | FUTURE / NOT EXECUTED |
## Security and permissions
| E03-T105 | Security and permissions | asset URI traversal cannot escape DATA-01 root future | FUTURE / NOT EXECUTED |
| E03-T106 | Security and permissions | untrusted prefab with extreme depth rejected bounded future | FUTURE / NOT EXECUTED |
| E03-T107 | Security and permissions | malicious heightmap decompression bomb rejected future | FUTURE / NOT EXECUTED |
| E03-T108 | Security and permissions | plugin cannot obtain raw native shell/editor privilege future | FUTURE / NOT EXECUTED |
| E03-T109 | Security and permissions | AI MCP terrain mass erasure requires explicit user consent future | FUTURE / NOT EXECUTED |
| E03-T110 | Security and permissions | CLI and GUI actor scopes share the same authorization future | FUTURE / NOT EXECUTED |
| E03-T111 | Security and permissions | source path and private asset IDs redacted from logs future | FUTURE / NOT EXECUTED |
| E03-T112 | Security and permissions | paid asset or service cannot be fetched automatically future | FUTURE / NOT EXECUTED |
## Accessibility and cross platform
| E03-T113 | Accessibility and cross platform | keyboard hierarchy reparent and inspector navigation future | FUTURE / NOT EXECUTED |
| E03-T114 | Accessibility and cross platform | screen-reader announces invalid selection and property future | FUTURE / NOT EXECUTED |
| E03-T115 | Accessibility and cross platform | Windows DPI and UIA tested with native editor future | FUTURE / NOT EXECUTED |
| E03-T116 | Accessibility and cross platform | macOS Retina and VoiceOver tested with native editor future | FUTURE / NOT EXECUTED |
| E03-T117 | Accessibility and cross platform | Linux Wayland focus and AT-SPI Orca tested future | FUTURE / NOT EXECUTED |
| E03-T118 | Accessibility and cross platform | CJK IME numeric field composition doesn't trigger gizmo future | FUTURE / NOT EXECUTED |
| E03-T119 | Accessibility and cross platform | right-to-left field localization retains stable property IDs future | FUTURE / NOT EXECUTED |
| E03-T120 | Accessibility and cross platform | reduced motion and high contrast show selected gizmo alternative future | FUTURE / NOT EXECUTED |
## Governance and acceptance
| E03-T121 | Governance and acceptance | exactly 128 E03 IDs are unique sequential FUTURE | FUTURE / NOT EXECUTED |
| E03-T122 | Governance and acceptance | formal EDIT-02 WORLD-04 dependencies remain documentary future | FUTURE / NOT EXECUTED |
| E03-T123 | Governance and acceptance | ADR-0055 remains PROPOSED no renderer or library adopted | FUTURE / NOT EXECUTED |
| E03-T124 | Governance and acceptance | engine code license NLE-D009 remains OPEN | FUTURE / NOT EXECUTED |
| E03-T125 | Governance and acceptance | Docs Validation not misreported as runtime gameplay tests | FUTURE / NOT EXECUTED |
| E03-T126 | Governance and acceptance | all 80 implementation Work Orders remain blocked | FUTURE / NOT EXECUTED |
| E03-T127 | Governance and acceptance | catalog save restore terrain objects proof still FUTURE | FUTURE / NOT EXECUTED |
| E03-T128 | Governance and acceptance | EDIT-04 research only after EDIT-03 final readback | FUTURE / NOT EXECUTED |

## Future controlled test safety and stop gates
- All fixtures synthetic and locally owned, no imported Epic/Unity paid assets, secrets, production games or public service targets. Never run untrusted project plugin code implicitly.
- Stage non-destructive brush/transform previews; verify zero source mutation before commit, world/scene revision CAS, single grouped undo and actual DATA-04 durable receipt after fresh reopen. On kill/power fault simulation, distinguish process crash from filesystem durability and verify original hashes.
- Audit full prefab source plus instance override graph, loaded/unloaded cells and WORLD-04 layer source not GPU cache. Deleting generated assets must not destroy source. Permission/capability checks apply uniformly to UI/CLI/MCP, and any HIGH/CRITICAL data loss, traversal, arbitrary code or irreversible auto edit blocks future release.
- **All 128 E03 test cases FUTURE/NOT EXECUTED at P00**, no actual engine/editor/terrain/benchmark or sanitizer tests have been run. No code package unblocked.
