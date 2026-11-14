# Evidence Bundle — NLE-P00-WO-002-TWO-01 Research

**Status:** RESEARCH PR OPEN, INITIAL EXACT-HEAD CI PASS; FINAL HEAD REVALIDATION AND AUDIT PENDING  
**Research issue #147**, **future code issue #37 OPEN/BLOCKED**, **BASE main `2ec91d4cf0f3062745a5d4b6d340da7027317348`**. Branch `docs/NLE-P00-WO-002-TWO-01-canvas-research`.

## Context and source checks
- Canonical hierarchy checked: Checkpoint > Decisions+approved ADRs > Scope > DoD > Architecture > Requirements > AGENTS/catalog/registry/packet. Main `2ec91d4cf0f3062745a5d4b6d340da7027317348` after GFX-08 PR #145 and reconciliation PR #146 merged. All 80 code WOs BLOCKED, zero executor-ready.
- New 8 research docs proposed and 3 links-only updates in existing Architecture, Backlog and future blocked packet; **no registry or checkpoint change before research audit/merge**.
- Technology source reads: Skia BSD, ThorVG MIT SVG Tiny subset, Blend2D zlib CPU JIT, lyon Rust MIT/Apache/MPL alternatives, HarfBuzz shaping, FreeType FTL credit/GPLv2, msdfgen MIT core with ext deps, Rive MIT runtime and free exported .riv splash/paid no-splash, W3C SVG security and WebGPU. No software, fonts or assets installed/redistributed; exact SBOM versions not frozen.
- Design: original native Canvas batches and CPU/math fallback, alpha painter order, pixel-art/high DPI, atlas gutter/alpha, optional vectors/text international and font rights, GFX-03/05/06/07/08 boundaries, secure typed MCP, S2CC research prove-or-drop.

## Observed canonical Git file fingerprints (Git blob SHA, NOT raw file SHA-256)
- `docs/11-checkpoint.md`: `af65ed4a80588c83782ed05dfbc479ca42dc8d93`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `124be6a8a7118a8b315ee762a45708f7ed3733d8`
- `docs/queue/work-orders/TWO-01.md`: `bb944bfe218f3b156b8be6a2fa70f9d1ca99b134`
These are Git identities at base. Future code SHA-256 Context Lock must hash bytes and revalidate after canonical changes, not reuse these blob values as SHA-256.

## Test and risk honesty
- [Research PR #148](https://github.com/KayzenRoot/stormline/pull/148), initial HEAD `c10ffbf177724e8e092e1d1d9c92823cfe3ab732`, [Docs Validation #43627090409](https://github.com/KayzenRoot/stormline/actions/runs/43627090409) **SUCCESS on initial exact HEAD**. Updating this Evidence Bundle produces a new HEAD, so the final CI must be verified separately before audit/merge.
- Docs-only audit and normal squash merge: **PENDING**.
- All 81 proposed future Canvas tests **NOT EXECUTED**; no native pixel goldens, GPU engines, 60FPS benchmark, Arabic/Hindi production text, C++ build, GPU memory test, SVG fuzz, SDK/file distribution proof.
- Risk LOW for docs only. Future ELEVATED GPU/Unicode/source files. No known runtime security attestation, signed code, proprietary graphics library, real code execution or exported visual artifact.

## Proposed Checkpoint Delta, NOT YET APPLIED
Only after research PR APPROVED/MERGED: create separate same-WO checkpoint PR to change **TWO-01.research_status `RESEARCH_PENDING` -> `RESEARCH_DOCUMENTED_ADR_PROPOSED`**, record main research merge and next topological TWO-02. Preserve `approved_adr=null`, `release_class=UNDECIDED`, `work_order_status=BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, `executor_ready=false` across all 80. No premature code activation or next module research.

## Security/rights/open gates
Untrusted SVG/XML/fonts, frame/path/atlas limits, cross-project MCP, font attribution/embed, Rive authored splash, JIT restrictions, shader/storage backends, real GPU fixtures and objective 60FPS numeric DoD require future separate evidence. No authorization to download paid/third-party binaries.
