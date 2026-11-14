# Backlog (dependency ordered)
Status: PLANNING; module implementation issues #18–#97 exist but remain BLOCKED. Research issues are separate.

| ID | Incremento | Predecessor | Estado |
|---|---|---|---|
| NLE-P00-WO-001 | Source Pack, identidade de marca, governança solo, CI docs | base Git | APPROVED: Source Pack integrado na PR #1; proteção da main ainda NÃO VERIFICADA |
| NLE-P00-WO-001-EXT-001 | README profissional, apresentação GitHub, templates, versionamento | WO-001 APPROVED, solicitação do proprietário | APPROVED: PR #3 merged, checkpoint/evidence em reconciliação documental |
| NLE-P00-WO-001-EXT-002 | Catálogo de 80 módulos, 2D/2.5D/3D/web e Windows/Linux/macOS, MCP-first e no-MVP como propostas | Solicitação explícita owner após EXT-001 | APPROVED / MERGED (PR #5), catálogo técnico de candidatos; sem código |
| NLE-P00-WO-002 | Pesquisa de stack/licenças por módulo, começando em NLE-P00-WO-002-CORE-01 (issue #6) | EXT-002 catalog e checkpoint integrados | CORE-01 a CORE-04: research docs APPROVED / MERGED; demais módulos aguardam, sem código |
| NLE-P00-WO-002-CORE-02 | Pesquisa std::pmr/mimalloc/rpmalloc, arenas e memória (issue #10) | CORE-01 docs/checkpoint APPROVED | RESEARCH DOCS APPROVED via PR #11, implementation NOT STARTED |
| NLE-P00-WO-002-CORE-03 | Research job scheduler, work stealing, task graph and thread affinity (CORE-03) | CORE-02 checkpoint/CI APPROVED | RESEARCH DOCS APPROVED / MERGED via PR #14; code NOT STARTED |
| NLE-P00-WO-002-QUEUE-001 | Fila de 80 WOs drafts bloqueadas, Zcode handoff, issues e validação CI | CORE-03 research/checkpoint approved | APPROVED AS BLOCKED QUEUE: 80 WOs + issues #18–97; zero engine implementation |
| NLE-P00-WO-002-CORE-04 | Time & simulation fixed-step, clock/replay research (issue #99) | CORE-03 + queue issue mapping checkpoint APPROVED | RESEARCH DOCS APPROVED / MERGED via PR #100; ADR-0006 PROPOSED for code, no implementation |
| NLE-P00-WO-002-CORE-05 | Math / Coordinates / Types research (issue #102) | CORE-04 checkpoint reconciled | RESEARCH IN PROGRESS / ADR-0007 PROPOSED; no code |
| NLE-P00-WO-003 | Arquitetura Core, memória, jobs, tempo, contratos | WO-002 APPROVED | PLANNED |
| NLE-P00-WO-004 | Arquitetura renderer, shaders, iluminação, VFX | WO-003 APPROVED | PLANNED |
| NLE-P00-WO-005 | World/terrain/physics/assets/audio | WO-003/004 APPROVED | PLANNED |
| NLE-P00-WO-006 | Rede, simulação e threat model | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-007 | Editor e autoria, UX e pipeline | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-008 | Benchmarks, qualidade, CI futura multi-OS | WO-004/005/006/007 APPROVED | PLANNED |
| NLE-P00-WO-009 | Auditoria integral P00, resolução de ADRs | anteriores APPROVED | PLANNED |

## Política
Somente a próxima WO NECESSARY pode iniciar. Corrigir bloqueios e manter a mesma WO/PR; sem encavalamento. Criar issues futuras **somente quando houver autorização explícita do proprietário**, identificadores estáveis e status BLOCKED; este requisito foi autorizado para o registro de planejamento de 80 módulos, sem habilitar execução. Entregas da fase M01+ são FUTURE até a aprovação do planejamento.
