# Backlog (dependency ordered)
Status: PLANNING; module implementation issues #18–#97 exist but remain BLOCKED. Research issues are separate.

| ID | Incremento | Predecessor | Estado |
|---|---|---|---|
| NLE-P00-WO-001 | Source Pack, identidade de marca, governança solo, CI docs | base Git | APPROVED: Source Pack integrado na PR #1; proteção da main ainda NÃO VERIFICADA |
| NLE-P00-WO-001-EXT-001 | README profissional, apresentação GitHub, templates, versionamento | WO-001 APPROVED, solicitação do proprietário | APPROVED: PR #3 merged, checkpoint/evidence em reconciliação documental |
| NLE-P00-WO-001-EXT-002 | Catálogo de 80 módulos, 2D/2.5D/3D/web e Windows/Linux/macOS, MCP-first e no-MVP como propostas | Solicitação explícita owner após EXT-001 | APPROVED / MERGED (PR #5), catálogo técnico de candidatos; sem código |
| NLE-P00-WO-002 | Pesquisa de stack/licenças por módulo, começando em NLE-P00-WO-002-CORE-01 (issue #6) | EXT-002 catalog e checkpoint integrados | CORE-01..CORE-06 e DATA-01: research docs APPROVED / MERGED; DATA-02 research APPROVED / MERGED; DATA-03, DATA-04, DATA-05, GFX-01, GFX-02, GFX-03 and GFX-04 research APPROVED / MERGED; engine not implemented |
| NLE-P00-WO-002-CORE-02 | Pesquisa std::pmr/mimalloc/rpmalloc, arenas e memória (issue #10) | CORE-01 docs/checkpoint APPROVED | RESEARCH DOCS APPROVED via PR #11, implementation NOT STARTED |
| NLE-P00-WO-002-CORE-03 | Research job scheduler, work stealing, task graph and thread affinity (CORE-03) | CORE-02 checkpoint/CI APPROVED | RESEARCH DOCS APPROVED / MERGED via PR #14; code NOT STARTED |
| NLE-P00-WO-002-QUEUE-001 | Fila de 80 WOs drafts bloqueadas, Zcode handoff, issues e validação CI | CORE-03 research/checkpoint approved | APPROVED AS BLOCKED QUEUE: 80 WOs + issues #18–97; zero engine implementation |
| NLE-P00-WO-002-CORE-04 | Time & simulation fixed-step, clock/replay research (issue #99) | CORE-03 + queue issue mapping checkpoint APPROVED | RESEARCH DOCS APPROVED / MERGED via PR #100; ADR-0006 PROPOSED for code, no implementation |
| NLE-P00-WO-002-CORE-05 | Math / Coordinates / Types research (issue #102) | CORE-04 checkpoint reconciled | RESEARCH IN PROGRESS / ADR-0007 PROPOSED; no code |
| NLE-P00-WO-002-DATA-03 | 2D/3D/textures/audio and idempotent reimport research (issue #114) | DATA-02 research/checkpoint APPROVED | RESEARCH DOCS APPROVED / MERGED via PR #115; ADR-0011 PROPOSED; implementation #26 BLOCKED |
| NLE-P00-WO-002-DATA-04 | Serialization & Scene Format, schema migrations and semantic diff technology research (issue #117) | DATA-03 checkpoint APPROVED | RESEARCH DOCS APPROVED / MERGED PR #118; ADR-0012 PROPOSED, implementation #27 BLOCKED |
| NLE-P00-WO-002-DATA-05 | Cooking, streaming bundles, incremental patching, target profiles (research #120) | DATA-04 checkpoint APPROVED / MERGED | RESEARCH DOCS APPROVED / MERGED PR #121; ADR-0013 PROPOSED; implementation #28 BLOCKED |
| NLE-P00-WO-002-GFX-01 | Graphics RHI/backends, resources, GPU feature tiers and device loss (research #123) | DATA-05 checkpoint APPROVED / MERGED; CORE-01/02 research documented | RESEARCH DOCS APPROVED / MERGED PR #124; ADR-0014 PROPOSED; implementation #29 BLOCKED |
| NLE-P00-WO-002-GFX-02 | Shader & Material Compilation, reflection, variants, cross-target IR and safe hot reload (research #126) | GFX-01 checkpoint APPROVED / MERGED; DATA-03 research documented | RESEARCH DOCS APPROVED / MERGED PR #127; ADR-0015 PROPOSED; implementation #30 BLOCKED |
| NLE-P00-WO-002-GFX-03 | Render Graph & GPU Resource Manager, DAG hazards, barriers, safe alias, VRAM and device-lost recovery (research #129) | GFX-02 checkpoint APPROVED / MERGED; GFX-01/CORE-03 research documented | RESEARCH DOCS APPROVED / MERGED PR #130; ADR-0016 PROPOSED; implementation #31 BLOCKED |
| NLE-P00-WO-002-GFX-04 | Geometry, Occlusion & LOD, instancing, conservative frustum/Hi-Z, HLOD/meshlets and bounded geometry streaming (research #132) | GFX-03 checkpoint APPROVED / MERGED; DATA-05 research documented | RESEARCH DOCS APPROVED / MERGED PR #133; ADR-0017 PROPOSED; implementation #32 BLOCKED |
| NLE-P00-WO-002-GFX-05 | Materials, Texture Systems & PBR: metallic-roughness and stylized domains, KTX2/BasisU, texture mip/alpha/decal and optional bounded virtual texturing (research #135) | GFX-04 checkpoint APPROVED/MERGED, GFX-02/DATA-03 researched | RESEARCH DOCS APPROVED / MERGED via PR #136; ADR-0018 PROPOSED; implementation #33 BLOCKED; NO CODE |
| NLE-P00-WO-002-GFX-06 | Research responsive physically aware lights, stable CSM/virtual shadows, GI/probes/Radiance Cascades/volumetrics and platform tiers (research #138) | GFX-05 research/checkpoint integrated, GFX-03/GFX-05 code not started | RESEARCH DOCS APPROVED / MERGED via PR #139; ADR-0019 PROPOSED; future implementation #34 BLOCKED; NO CODE |
| NLE-P00-WO-002-GFX-07 | Research cinematic camera, ACES2/OCIO color/HDR SDR pipeline, exposure, temporal/native upscale, optional vendor SDKs and accessibility (research #141) | GFX-06 research/checkpoint merged; code GFX-06 not implemented | RESEARCH DOCS APPROVED / MERGED via PR #142; ADR-0020 PROPOSED; future implementation #35 BLOCKED; NO CODE |
| NLE-P00-WO-002-GFX-08 | Research typed effect node graphs, hybrid CPU/GPU VFX, ribbons/trails/alpha/OIT, scalable lights/fog, 2D/2.5D/3D and Web tiers (research #144) | GFX-07 research/checkpoint integrated, GFX-03/05 code not started | RESEARCH DOCS APPROVED / MERGED via PR #145; ADR-0021 PROPOSED; future code #36 BLOCKED; NO CODE |
| NLE-P00-WO-003 | Arquitetura Core, memória, jobs, tempo, contratos | WO-002 APPROVED | PLANNED |
| NLE-P00-WO-004 | Arquitetura renderer, shaders, iluminação, VFX | WO-003 APPROVED | PLANNED |
| NLE-P00-WO-005 | World/terrain/physics/assets/audio | WO-003/004 APPROVED | PLANNED |
| NLE-P00-WO-006 | Rede, simulação e threat model | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-007 | Editor e autoria, UX e pipeline | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-008 | Benchmarks, qualidade, CI futura multi-OS | WO-004/005/006/007 APPROVED | PLANNED |
| NLE-P00-WO-009 | Auditoria integral P00, resolução de ADRs | anteriores APPROVED | PLANNED |

## Política
Somente a próxima WO NECESSARY pode iniciar. Corrigir bloqueios e manter a mesma WO/PR; sem encavalamento. Criar issues futuras **somente quando houver autorização explícita do proprietário**, identificadores estáveis e status BLOCKED; este requisito foi autorizado para o registro de planejamento de 80 módulos, sem habilitar execução. Entregas da fase M01+ são FUTURE até a aprovação do planejamento.
