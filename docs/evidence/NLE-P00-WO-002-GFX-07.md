# Evidence Bundle — NLE-P00-WO-002-GFX-07 Research

**State:** RESEARCH DOCS AUDITED/APPROVED/MERGED; CHECKPOINT RECONCILIATION REQUIRES SEPARATE CI/AUDIT | **Research #141** | **Future code #35 BLOCKED** | **BASE main:** `bd45e076f789e0b934076a1973139400d3eb382b` | **Research branch:** `docs/NLE-P00-WO-002-GFX-07-camera-color-research`.  
**Risk:** LOW documents; future ELEVATED GPU history, HDR/monitor/capture and untrusted LUT/vendor DLL. No code/SDK/HDR GPU measured.

## Context Lock and research facts
- Canonical source precedence verified: checkpoint -> Decisions/ADRs -> Scope -> DoD -> Architecture -> Requirements. Main `bd45e076f789e0b934076a1973139400d3eb382b`; GFX-06 PRs #139/#140 merged, implementation dependencies not delivered.
- Official source and licensing reading: OpenColorIO BSD-3-Clause/ACES2; AMD FSR SDK 2.4 prebuilt signed loader/effect DLLs; NVIDIA Streamline DLSS-G prebuilt plugin; Intel XeSS proprietary binary redistribution terms; W3C WebGPU GPU texture color management boundary; Unreal TSR ghost documentation; Microsoft Windows HDR. Exact versions/SBOM/rights are future per-provider gates.
- New architecture, technology/license matrix, ADR-0020 PROPOSED, semantic API, 77 NOT RUN acceptance cases, quality/latency benchmark protocol, research WO, this evidence; additive GFX-07 links to architecture, backlog and existing blocked packet.
- `docs/queue/implementation-registry.json` **unchanged in research PR**, registry 80 blocked, executor_ready=0. Proposed separate checkpoint delta after approved/merged research PR: **ONLY** GFX-07 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; `approved_adr=null`, release class UNDECIDED, code #35 BLOCKED.

## Not yet evidenced
- [Research PR #142](https://github.com/KayzenRoot/stormline/pull/142): BASE `bd45e076f789e0b934076a1973139400d3eb382b`, initial HEAD `fbd0779910fa39ca6e9cc7c380e88d2002dc2a31`, 11 files docs only. [Docs Validation #43624036306](https://github.com/KayzenRoot/stormline/actions/runs/43624036306) **SUCCESS on initial exact HEAD**; future evidence commit requires NEW exact-HEAD check before audit.
- Final [Docs Validation #43624090643](https://github.com/KayzenRoot/stormline/actions/runs/43624090643) SUCCESS at **final HEAD** `830ddbe54b56825bfd902faa2b273d68532a2b99`, with Socket Security/SonarCloud checks SUCCESS. PR #142 audited in pt-BR APPROVED **docs-only**, 11-file scope, no known HIGH/CRITICAL documentation defect; normal squash merged `5bab9b54b83cfb48a8591e040a3f3e4ecd4a69c3`. Checkpoint PR requires separate exact-HEAD audit.
- All 77 future tests, numerical color/ACES2 comparison, GPU HDR screenshots, VRAM p95/p99, native Win/Linux/macOS/Web render builds and signed SDK tests: **NOT EXECUTED**.
- SRCC proof and superiority vs Unreal/GGG **NOT ESTABLISHED**.
- No deployment, credentials, paid CI, vendor binaries or visual assets delivered.

## Canonical Git content fingerprints at base (Git blob hashes, NOT raw SHA-256)
- `docs/11-checkpoint.md`: `ec451c485e2337ee1e0faec11d9ed8de49b2f51f`
- `docs/10-decisions-ledger.md`: `d47abc54aa3aa1826d6a0a3c67dbfcaf1853ae9e`
- `docs/03-scope.md`: `4ef605c74632ece080b2650e37dd83a415b63310`
- `docs/09-definition-of-done.md`: `160b3054db9ea1961308934b401488b838d24c3e`
- `docs/04-architecture.md`: `466de5483bd953d33562e6dd249eda7cf462183c`
- `docs/queue/work-orders/GFX-07.md`: `ecfcfb8f4b420118140b99db161952ae3f40606b`
These represent observed Git content identities, not proof a future source file meets frozen code Context Lock.

## Future exact-head workflow
Only after observed green docs CI + 11-file scoped diff objective audit, use normal squash PR. Then separate same-WO checkpoint PR; validate final HEAD CI and audit before merge. No next research module if correction required; never promote code on documentation alone.

## Checkpoint Delta and readback policy
Only `GFX-07.research_status` can change to `RESEARCH_DOCUMENTED_ADR_PROPOSED`; code #35, all 80 blocked WOs, `approved_adr=null`, `executor_ready=false`, release classes unchanged. This same-WO checkpoint PR requires its own green final HEAD and pt-BR objective audit, normal squash merge and main readback before declaring GFX-08 next. No graphics, verified HDR, benchmark, code or vendor binaries implied.
