# EDIT-05 — Reproducible Shader Graph, Preview, Variant and Export Benchmark Protocol

**P00 proposal, NOT EXECUTED | 2026-11-15 | [#268](https://github.com/KayzenRoot/stormline/issues/268) | future code #72 BLOCKED.** No editor binary, compiler build, shader output, target GPU preview, visual result, p50/p95/p99, accessibility pass or performance budget exists.

## 1. Environment manifest and repeatability
Pin exact engine/Editor commit, compiler release/build hash, node registry/schema version, optimization flags, target profile, OS/build, graphics API, GPU model/driver, CPU/RAM/VRAM, browser/WebGPU adapter, display DPI, power/thermal mode, locale, fonts and fixture/license digest. Separate cold cache from warm cache; record cache clear state and compilation cache key. Use at least 3 independent runs/seeds and 30 warmups. Capture >=1000 interactive/compile observations for p99; a handful of runs cannot justify tail latency. Alternate baseline/candidate run order to reduce thermal bias. Keep raw traces and exact graph/material revisions.

## 2. Graph and material fixtures
| Fixture | Scale / content | Measurements |
|---|---|---|
| SG-01 | 32 nodes, 64 edges, base PBR graph, 1 output | add/connect/validate, compile cold/warm, preview first-frame |
| SG-02 | 128 nodes, 256 edges, 4 reusable subgraphs, 3 graph stages | topology/type check, subgraph navigation and compile time |
| SG-03 | 512 nodes, 1,024 edges, 8 material outputs, 16 texture refs | pan/zoom, selection, dirty-region redraw, source-map navigation |
| SG-04 | 2,000 nodes, 4,096 edges, large graph and nested groups | input-to-paint, hit test, minimap, memory and cancellation |
| SG-05 | 10,000 nodes, 20,000 edges, synthetic sparse graph | stress, quotas, responsive editor and bounded validation |
| MT-01 | glTF metallic-roughness, clearcoat/sheen/transmission variants, original textures | parameter semantics, import loss report, preview fidelity |
| VR-01 | dynamic uniforms + 1/4/8/16/32 static feature combinations | variant count, cache hit/miss, compile time, artifact storage |
| PV-01 | sphere, shader ball, plane, cube, UV checker and 2D sprite | preview latency, color/normal/alpha, device loss and last-good |
| EX-01 | MaterialX supported/unsupported node set and glTF material subset | import/export time, round-trip digest, loss/rights report |
| SC-01 | hostile XML, huge graph, deep subgraph, NaN, unsupported node and cache corruption | parser CPU/RSS, fail-closed state, recovery and compiler sandbox |

Synthetic fixtures may be generated programmatically for stress, but catalog GUI-only acceptance must be authored through the actual editor UI with screen recording/command journal and no manual source-file edit.

## 3. Metrics and protocol
- Graph UI: input-to-paint and node drag/connect response p50/p95/p99, visible node count, dirty-region cost, CPU frame time, memory highwater and cancellation delay.
- Validation: nodes/edges/ports per second, type-check cost, cycle detection, subgraph depth, diagnostics count and deterministic semantic digest.
- Compiler: cold/warm compile duration, queue delay, cache hit ratio, peak RSS/disk, target artifact bytes, source-map completeness and timeout/cancel behavior.
- Variants: requested/actual static variant count, reachable combination count, cache invalidations, compile cost and artifact storage. Never benchmark uncontrolled Cartesian explosion as acceptable.
- Preview: request-to-first-frame, steady frame CPU/GPU p50/p95/p99, offscreen memory/VRAM, fence wait, stale preview count, device-loss recovery and last-good continuity.
- Export: stage/validate/commit/readback duration, bytes, hashes, supported/lossy node counts, rights/NOTICE completeness and rollback.
- Accessibility: keyboard-only completion time and errors, screen-reader announcement coverage, focus loss, text scaling, high contrast and reduced-motion correctness.
- Cross-target: Windows Vulkan/D3D12, Linux Vulkan/X11+Wayland, macOS Apple Silicon Metal, WebGPU and WebGL2 only where actual adapters exist. Unsupported combinations are explicit, not omitted.

## 4. Failure injection and security protocol
Crash compiler during parse/optimization/backend; time out a node implementation; cancel at queue/compile/link/preview; lose GPU/device mid-preview; invalidate compiler cache; race graph/material revision with CLI/MCP; interrupt DATA-04 transaction and DATA-05 export staging; corrupt schema/manifest; inject recursive subgraph, malicious XML/entity/path, oversized string/array, NaN/Inf and variant explosion. Verify last-good graph/material, journal replay/rollback, source hash, owner receipts and absence of unintended write/network/driver calls. Run parser/compiler fuzzing under suitable sanitizer/fuzzer after real source exists.

## 5. Baseline and thresholds
Numeric limits for graph size, compile time, preview latency, memory/VRAM, variant count, file size, parser depth and supported target tiers are **TBD**. Establish measured simple typed-graph baseline first, then compare MaterialX adapter and UI-library candidates on same hardware/build/fixture. No claimed performance improvement or "better than Unreal/Godot" result without reproducible output and declared rubric.

At P00: editor builds 0; compiler runs 0; target previews 0; graph export runs 0; benchmark samples 0; accessibility passes 0; future acceptance tests 128 NOT EXECUTED.

[Tests](../testing/edit-05-acceptance-matrix.md) · [Technology matrix](edit-05-visual-shader-technology-license-matrix.md) · [Architecture](../architecture/edit-05-visual-shader-material-graph.md).
