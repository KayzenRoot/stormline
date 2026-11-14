# Evidence Bundle — NLE-P00-WO-002-TWO-01 Research

**Status:** DRAFT / RESEARCH PR FINAL-HEAD CI/AUDIT PENDING  
**Research issue #147**, **future code issue #37 OPEN/BLOCKED**, **BASE main `2ec91d4cf0f3062745a5d4b6d340da7027317348`**. Branch `docs/NLE-P00-WO-002-TWO-01-canvas-research`.

## Context and source checks
- Canonical hierarchy checked: Checkpoint > Decisions+approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/packet. Main `2ec91d4cf0f3062745a5d4b6d340da7027317348` after GFX-08 PR #145 and reconciliation PR #146 merged. All 80 code WOs BLOCKED, zero executor-ready.
- New 8 research docs proposed and 3 links-only updates in existing Architecture, Backlog and future blocked packet; **no registry or checkpoint change before research audit/merge**.
- Technology source reads: Skia BSD, ThorVG MIT SVG Tiny subset, Blend2D zlib CPU JIT, lyon Rust MIT/Apache/MPL alternatives, HarfBuzz shaping, FreeType FTL credit/GPLv2, msdfgen MIT core with ext deps, Rive MIT runtime and free exported .riv splash/paid no-splash, W3C SVG security and WebGPU. No software, fonts or assets installed/redistributed; exact SBOM versions not frozen.
- Design: original native Canvas batches and CPU/math fallback, alpha painter order, pixel-art/high DPI, atlas gutter/alpha, optional vectors/text international and font rights, GFX-03/05/06/07/08 boundaries, secure typed MCP, S2CC research prove-or-drop.

## Test and risk honesty
- Research PR/head/exact-HEAD Docs Validation: **PENDING**; do not assert PASS until retrieved.
- Docs-only audit and normal squash merge: **PENDING**.
- All 81 proposed future Canvas tests **NOT EXECUTED**; no native pixel goldens, GPU engines, 60FPS benchmark, Arabic/Hindi production text, C++ build, GPU memory test, SVG fuzz, SDK/file distribution proof.
- Risk LOW for docs only. Future ELEVATED GPU/Unicode/source files. No known runtime security attestation, signed code, proprietary graphics library, real code execution or exported visual artifact.

## Proposed Checkpoint Delta, NOT YET APPLIED
Only after research PR APPROVED/MERGED: create separate same-WO checkpoint PR to change **TWO-01.research_status `RESEARCH_PENDING` -> `RESEARCH_DOCUMENTED_ADR_PROPOSED`**, record main research merge and next topological TWO-02. Preserve `approved_adr=null`, `release_class=UNDECIDED`, `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false` across all 80. No premature code activation or next module research.

## Security/rights/open gates
Untrusted SVG/XML/fonts, frame/path/atlas limits, cross-project MCP, font attribution/embed, Rive authored splash, JIT restrictions, shader/storage backends, real GPU fixtures and objective 60FPS numeric DoD require future separate evidence. No authorization to download paid/third-party binaries.
