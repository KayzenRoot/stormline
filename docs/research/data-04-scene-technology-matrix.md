# DATA-04 — Scene Serialization, Schema and Evolution Technology Matrix

**WO:** NLE-P00-WO-002-DATA-04 | **Issue:** #117 | **State:** PROPOSED / DOCS ONLY.
No technology is selected for implementation, pinned, installed or benchmarked.

| Candidate | License / source checkpoint | Potential advantage | Costs / selection gate |
|---|---|---|---|
| Strict JSON UTF-8, canonical pretty writer | RFC 8259; own schema/encoder | readable, Git-reviewable, Web/AI tool interchange | no comments; duplicate-key/float/order discipline; large documents |
| JSON Schema Draft 2020-12 | open specification, not a runtime library | portable structural validation, tooling | semantic graph and authorization checks still owned; validate exact implementation |
| JSON5 | [upstream MIT](https://github.com/json5/json5), JavaScript reference | comments/trailing commas for handwritten configs | alternative authoring input only; comment-preserving roundtrip parser must be proven; not preferred canonical persisted scene |
| TOML / toml++ | [upstream MIT](https://github.com/marzer/tomlplusplus) | human-readable project settings | large heterogeneous scene graphs and nested structures awkward; not preferred scene baseline |
| YAML / yaml-cpp | [upstream MIT](https://github.com/jbeder/yaml-cpp) (exact tag audit) | familiar authoring ecosystem | anchors/aliases/tags and complex parsing/canonicality increase risk; no arbitrary object instantiation; opt-in at most |
| nlohmann/json | [upstream MIT](https://github.com/nlohmann/json) | mature C++20 friendly JSON DOM/serializer and ergonomics | DOM peak memory/latency, duplicate-key and number behavior audited before selection |
| simdjson | [upstream Apache-2.0](https://github.com/simdjson/simdjson) (verify exact tag) | high-throughput C++ parse candidate | parse only does not supply stable semantic writer/schema/migrations; memory/CPU compatibility |
| FlatBuffers | [upstream Apache-2.0](https://github.com/google/flatbuffers) | typed binary access; potential efficient runtime loads | schema/codegen/versioning constraints; generated code, Web build and compatibility proof |
| Protocol Buffers | [upstream BSD-3-Clause](https://github.com/protocolbuffers/protobuf) (confirm release files) | mature generated typed schemas/evolution practices | runtime/allocator/ABI and unknown-field semantics in exact language version |
| Cap'n Proto | [upstream MIT](https://github.com/capnproto/capnproto) | zero-copy-oriented binary schema ecosystem | alignment, security, dependencies, footprint, Web/Windows/macOS tests |
| Owned chunked binary | engine-owned, subject to engine code license OPEN | explicit streaming and target-specific layout | high maintenance/fuzz/corruption burden; only if standard codecs fail |
| RFC 8785 JCS | [IETF RFC](https://www.rfc-editor.org/rfc/rfc8785.html) | stable hash/signature bytes of compatible JSON data | **not** text pretty-print format, UTF-16 property ordering and IEEE-754 constraints; do not assume arbitrary numbers supported |
| RFC 6902 JSON Patch | [IETF RFC](https://www.rfc-editor.org/rfc/rfc6902.html) | transparent generic patch comparator | array-index/hierarchy semantic instability; typed stable-ID ops are required on top |
| Stormline SSD | own R&D hypothesis (not implemented) | potential compact, explainable AI-safe semantic deltas | prove benefit vs ordinary ID-keyed AST diff / JSON Patch or drop |

## Preferred research direction, not adopted stack
1. **Start with strict JSON SceneDocument + Stormline-owned schema and typed SceneIR** as the initial planning baseline; no comments in canonical scene source. JSON Schema 2020-12 can supplement, not replace graph and capability validation.
2. Compare nlohmann/json (MIT) vs simdjson (Apache-2.0) + dedicated writer on the same licensed goldens; do not prejudge speed/footprint. Avoid unsupported claim that parsing library enforces all schema/security semantics.
3. Prefer readable deterministic Git-diff authoring source. Candidate RFC 8785 JCS for content digest only if a compliant implementation passes conformance; integer IDs string-encoded and float rules explicit.
4. DATA-05 selects **runtime** binary schema separately via FlatBuffers/Protobuf/Cap'n Proto versus an owned chunked approach, based on real load/memory, field-evolution and Web tests. Do not impose binary parser on editable source merely for a hypothetical FPS gain.
5. Preserve unknown optional extensions without unsafe execution; unsupported required plugin capability forces read-only/explicit failure. Include plugin/asset license provenance.
6. Reject YAML custom tags/unbounded aliases as a default untrusted project format; evaluate JSON5/TOML only if fidelity/testability beats strict JSON.
7. Assign semantic operations stable EntityId/Component IDs; ordinary line-based diff and vanilla JSON Patch cannot guarantee a safe 3-way scene merge by themselves.
8. SSD remains prove-or-drop against simple typed diff with comparable fixtures, with no duplicate authority.

## Comparison scorecard to execute later
Semantic roundtrip/unknown-field preservation 25%; migration safety and security 25%; cross-platform/CI/toolchain compatibility 15%; human Git review/AI semantics 15%; peak memory and p95 latency 10%; license/SBOM and maintenance 10%. Numeric 1–10 rankings are forbidden until equal datasets, exact versions and toolchain measurements exist.

## Research references (checked 2026-11-14)
- JSON Schema: https://json-schema.org/draft/2020-12
- JSON RFC: https://www.rfc-editor.org/rfc/rfc8259.html
- JCS RFC: https://www.rfc-editor.org/rfc/rfc8785.html
- JSON Patch RFC: https://www.rfc-editor.org/rfc/rfc6902.html
- FlatBuffers: https://flatbuffers.dev/ and https://github.com/google/flatbuffers
- Protobuf: https://protobuf.dev/ and https://github.com/protocolbuffers/protobuf
- Cap'n Proto: https://capnproto.org/ and https://github.com/capnproto/capnproto
- nlohmann/json: https://github.com/nlohmann/json
- simdjson: https://github.com/simdjson/simdjson
- JSON5: https://json5.org/
- TOML: https://toml.io/en/ and https://github.com/marzer/tomlplusplus
- yaml-cpp: https://github.com/jbeder/yaml-cpp

Exact tagged distribution licenses, notices and transitive packages require later validation. No dependency was installed or runtime performance measured.
