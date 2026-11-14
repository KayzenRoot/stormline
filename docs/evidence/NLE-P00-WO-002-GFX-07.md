# Evidence Bundle — NLE-P00-WO-002-GFX-07 Research

**State:** DRAFT PENDING PR + CI/AUDIT | **Research #141** | **Future code #35 BLOCKED** | **BASE main:** `bd45e076f789e0b934076a1973139400d3eb382b` | **Research branch:** `docs/NLE-P00-WO-002-GFX-07-camera-color-research`.  
**Risk:** LOW documents; future ELEVATED GPU history, HDR/monitor/capture and untrusted LUT/vendor DLL. No code/SDK/HDR GPU measured.

## Context Lock and research facts
- Canonical source precedence verified: checkpoint -> Decisions/ADRs -> Scope -> DoD -> Architecture -> Requirements. Main `bd45e076f789e0b934076a1973139400d3eb382b`; GFX-06 PRs #139/#140 merged, implementation dependencies not delivered.
- Official source and licensing reading: OpenColorIO BSD-3-Clause/ACES2; AMD FSR SDK 2.4 prebuilt signed loader/effect DLLs; NVIDIA Streamline DLSS-G prebuilt plugin; Intel XeSS proprietary binary redistribution terms; W3C WebGPU GPU texture color management boundary; Unreal TSR ghost documentation; Microsoft Windows HDR. Exact versions/SBOM/rights are future per-provider gates.
- New architecture, technology/license matrix, ADR-0020 PROPOSED, semantic API, 77 NOT RUN acceptance cases, quality/latency benchmark protocol, research WO, this evidence; additive GFX-07 links to architecture, backlog and existing blocked packet.
- `docs/queue/implementation-registry.json` **unchanged in research PR**, registry 80 blocked, executor_ready=0. Proposed separate checkpoint delta after approved/merged research PR: **ONLY** GFX-07 `research_status: RESEARCH_PENDING -> RESEARCH_DOCUMENTED_ADR_PROPOSED`; `approved_adr=null`, release class UNDECIDED, code #35 BLOCKED.

## Not yet evidenced
- Research HEAD, PR, exact-HEAD GitHub Actions/docs/security checks: **PENDING**.
- Audit pt-BR HIGH/CRITICAL, merge SHA and readback: **PENDING**.
- All 77 future tests, numerical color/ACES2 comparison, GPU HDR screenshots, VRAM p95/p99, native Win/Linux/macOS/Web render builds and signed SDK tests: **NOT EXECUTED**.
- SRCC proof and superiority vs Unreal/GGG **NOT ESTABLISHED**.
- No deployment, credentials, paid CI, vendor binaries or visual assets delivered.

## Future exact-head workflow
Only after observed green docs CI + 11-file scoped diff objective audit, use normal squash PR. Then separate same-WO checkpoint PR; validate final HEAD CI and audit before merge. No next research module if correction required; never promote code on documentation alone.
