# ADR-0022 — Stable Canvas2D Semantics and Optional Vector/Text Adapters

**Status:** PROPOSED / NOT APPROVED FOR ENGINE CODE  
**Date:** 2026-11-14 | **Research #147** | **WO NLE-P00-WO-002-TWO-01** | **Future implementation #37 BLOCKED**.

## Context
Stormline must offer native 2D/2.5D, not fake 3D only. Incorrect transparent reordering, broken high-DPI/pixel art, font/BiDi gaps, unsafe SVG imports and heavy/paid third-party editors are risks. 60 FPS requires a named platform/hardware/fixture, none exists yet.

## Proposed policy
1. Own a **semantic Canvas2D** for sprites/atlases/layers/orthographic views/clips/vector/text render plans. GFX-01 backend+presentation, GFX-02 shaders, GFX-03 GPU memory/fences, GFX-05 texture/colorspace, GFX-06 2D lighting, GFX-07 output and camera, DATA-02/03/04/05 identity/import/cook and TWO-02/03/04 future features remain authoritative.
2. GPU instance sprite batches ordered by **stable painter sequence**, only contiguous compatible merges; transparent group/mask/clip/layer order is never illegally reordered for fewer draws. CPU math/reference and WebGL2 reduced rendering are required; fancy compute optional per target.
3. Pixel-perfect integer snapping/letterboxing and high-DPI continuous modes are separate, with no text/UI jitter or mandatory TAA. Atlas gutters/mips, premultiplied alpha and sRGB-to-linear conversion are exactly once.
4. Optional bounded vector adapter benchmark: ThorVG MIT SVG Tiny/Lottie subset, Skia BSD broad alternative, Blend2D zlib CPU/JIT not mandatory in restricted/Web, lyon Rust MIT/Apache/MPL path FFI not guaranteed. No vendor library adopted by docs.
5. Typed `TextRunDrawV1` glyph rendering belongs to TWO-01; high-level editor/UI handles complex line breaking/BiDi input/IME/accessibility tree. HarfBuzz candidate shaping, FreeType FTL with **credit clause** or explicit GPLv2, msdfgen MIT core plus dependencies, and separately licensed font files. Unicode correctness must be proven for non-Latin scripts.
6. Rive MIT runtime is optional import only; source authoring/editor/free splash and paid no-splash exports prevent making it obligatory or claiming free full tool chain. Third-party artwork and brand terms remain independent.
7. No arbitrary SVG scripts/resources/fonts/paths, unbounded vector tessellation, direct GPU pointers, unsigned plugins or agent-driven code execution. DATA-03 imports and DATA-04 transactional authoring mediate Editor/CLI/MCP project-scoped change with expected revision and quotas.
8. 60 FPS only a future **benchmark target**, not passing capability. Require overdraw, draw count/atlas eviction, p50/p95/p99 CPU/GPU+VRAM with original rights-cleared 2D fixtures and actual Windows/Linux/macOS/Web hardware.
9. S2CC clarity-aware batch/cache optimization OPTIONAL PROVE-OR-DROP, no originality/performance proven. Native source order and UI readability are more important than batch count.
10. All 80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`/`executor_ready=false`, implementation #37 open. Release class UNDECIDED and ADR-0022 merely proposed. Before executing require final owner-approved 1.0 Scope/DoD, implemented GFX-01/DATA-03 predecessors, named GPU/browser fixtures, exact frozen ABI/source files/library revisions/licenses and SHA-256 Context Lock/audit.

## Rejected defaults
Full “Skia clone”, Blend2D JIT as universal Web runtime, Rive account/splash dependency, text ASCII only, premature full SVG2/HTML/script support, 2D lighting duplicate, sort transparent sprites for batching, magic 60 FPS guarantee, UI TAA blurring, raw imported system fonts bundled without rights.

## Future evidence (NOT EXECUTED)
CPU math golden and DrawPlan logic, native GPU sprite/atlas/text/vector, Unicode/RTL+color fallbacks, pixel-perfect multi-DPI/window, alpha nested groups, SVG fuzz, WebGL2/WebGPU/Metal/Vulkan/DX12 and device loss/atlas reclaim, reproducible p95/p99 and legal proof. See [architecture](../architecture/two-01-renderer-canvas.md), [matrix](../research/two-01-renderer-technology-license-matrix.md), [API](../contracts/two-01-canvas-api.md), [tests](../testing/two-01-acceptance-matrix.md), [benchmark](../research/two-01-benchmark-protocol.md).
