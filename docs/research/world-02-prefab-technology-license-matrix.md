# WORLD-02 — Scene/Prefab Composition Technology and Licensing Matrix

**Research #162 | WO NLE-P00-WO-002-WORLD-02 | Proposed only; NO engine/vendor runtime, assets, custom code or import tool installed.**

| Candidate | Role | Technical/legal risks | Future evidence and scope |
|---|---|---|---|
| Stormline original Scene/Prefab source with GUIDs + link/typed overrides | NECESSARY | authoring complexity and propagation correctness; needs DATA-04 journal | save/reopen, source rev/3-way merge, headless |
| Rooted forest for instance hierarchy, separate DAG for prefab/variant dependencies | NECESSARY | reject parent/variant loops, bounded expansion, source-vs-instance ID | cycle and deep-graph fuzz, wrong-world denial |
| Field-level 3-way rebase with apply/revert and removal tombstones | NECESSARY | stable TypeId+FieldId, simultaneous base/local conflict, structural list edits | no silent local override loss, undo/redo |
| Stable NodeGuid/PrefabId/SceneId/InstanceId | NECESSARY | ID collision, duplicate instancing/reimport/remap, avoids name/path references | clone, rename, reparent, serialize |
| CORE-05 affine TRS+full-matrix transform bridge | NECESSARY | KEEP_WORLD inverse can be undefined, shear/nonuniform negative scales | world transform epsilon and reject unrepresentable |
| Deferred ECS instantiation via WORLD-01, journal through DATA-04 | NECESSARY | source commit vs runtime publish not a single atomic physical transaction | crash/replay, old/new snapshot consistency |
| Godot 4.6 PackedScene instancing / Node.owner | REFERENCE ONLY | PackedScene serializer owns nested nodes marked owner; engine node tree is not Stormline ECS and syntax differs | MIT engine, author asset rights separate; no code copied |
| Unity 6 nested prefab / Variant / Apply-Revert | REFERENCE ONLY | proven override UX concepts; proprietary editor, YAML/binary imported assets are NOT automatically open | do not ship Unity SDK/source/assets; own comparable fixtures |
| OpenUSD scene composition layers/references/variants | OPTIONAL FUTURE importer or design reference | powerful USD arcs/strength ordering/list editing, substantial dependency/plugin stack; not identical to Stormline override hierarchy | **TOST License 1.0** upstream, distinct from Apache-2.0 Section 6, many third-party rights, exact pinned legal gate |
| Open 3D Engine (O3DE) prefab templates/links/patches | OPTIONAL FUTURE conceptual reference | prefab propagation/link design, larger engine integration not justified absent benchmark | O3DE core **Apache-2.0 OR MIT**, 3rd-party/Qt and asset licenses independent; pinned rights gate |
| Textual JSON/XML/YAML scene serialization | OPTIONAL wire format, not selection | human-readable diff vs denial-of-service, schema spoofing and source encoding issues | DATA-03 parser, DATA-04 writer, no native arbitrary code |
| Stable binary scene cook for runtime | IMPORTANT future owner | lower startup overhead, version/migration and DATA-05 cook/integrity | DATA-05 owns cache/stream, DATA-04 owns canonical author data |
| SIOP incremental impact propagation planner | OPTIONAL PROVE-OR-DROP | complex dependency invalidation/false negatives vs full rebuild | image/field correctness and p99 vs simple baseline |

## Version-sensitive source and license precautions
- Godot core engine is licensed MIT, and `PackedScene` vs `Node.owner` illustrate instance serialization; a Godot node is NOT equivalent to the ECS EntityGuid/generational handle ownership. Third-party scenes, art and fonts remain separately copyrighted.
- Unity 6 Prefab/Variant and nested override UI demonstrate targeted Apply/Revert semantics with proprietary software and file formats. A purchased Unity asset is not an automatically distributable test fixture for Stormline; don't copy schemas from undocumented internals.
- **OpenUSD repo dev LICENSE currently starts with Tomorrow Open Source Technology License 1.0**, explicitly stating difference from original Apache-2.0 in Section 6 on trademarks. Third-party source bundles and media/other licenses appear in same upstream LICENSE; do not simplify to an Apache license or ship this SDK without a pinned version, counsel/compliance check, transitive SBOM and actual platform builds. The public compositing model is an intellectual reference, not code.
- **O3DE LICENSE.txt** provides Apache-2.0 OR MIT option for the engine; third-party packages may have their own GPL/LGPL/proprietary/Qt terms. Never treat entire prebuilt editor as MIT by default, and do not assume O3DE's prefabs API is stable C++/Web ABI for Stormline.
- DATA-02/03/04 must validate external file references, nested scene paths, dependency graph cycles and decompression size limits; no arbitrary remote fetch/expression/script in prefab data. Signed source revision/asset rights and code-plugin execution are independent permissions.
- Source code, binary build, imported scene and media copyrights are separate. Current Stormline **adopts none** of these third-party runtimes, licenses or content. Benchmark numeric thresholds are TBD until approved DoD.

## Primary official references (design research, NOT integrated libraries)
- Godot 4.6 scene instancing and node lifetime: https://docs.godotengine.org/en/4.6/tutorials/scripting/nodes_and_scene_instances.html
- Godot 4.6 editor ownership of scene persistence: https://docs.godotengine.org/en/4.6/tutorials/plugins/running_code_in_the_editor.html
- Godot engine official MIT license: https://godotengine.org/license/
- Unity 6 nested prefabs: https://docs.unity.com/en-us/engine/6000.6/manual/working-with-gameobjects/prefabs/nested
- Unity 6 prefab instance apply/revert override: https://docs.unity.com/en-us/engine/6000.6/manual/working-with-gameobjects/prefabs/override/prefab-instance-overrides
- Unity prefab variants: https://docs.unity.com/en-us/engine/6000.7/manual/working-with-gameobjects/prefabs/prefab-variants
- OpenUSD versioned scene composition principles and strength precedence: https://docs.nvidia.com/learn-openusd/latest/composition-basics/strength-ordering.html
- OpenUSD actual source license and bundled third-party notices (Tomorrow Open Source Technology License 1.0, not plain Apache-2): https://github.com/PixarAnimationStudios/OpenUSD/blob/dev/LICENSE.txt
- O3DE upstream dual-license and third-party packages: https://github.com/o3de/o3de/blob/development/LICENSE.txt
