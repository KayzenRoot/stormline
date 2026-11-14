# Backlog (dependency ordered)
Status: INITIAL / NÃO são issues criadas

| ID | Incremento | Predecessor | Estado |
|---|---|---|---|
| NLE-P00-WO-001 | Source Pack, identidade de marca, governança solo, CI docs | base Git | APPROVED: Source Pack integrado na PR #1; proteção da main ainda NÃO VERIFICADA |
| NLE-P00-WO-001-EXT-001 | README profissional, apresentação GitHub, templates, versionamento | WO-001 APPROVED, solicitação do proprietário | APPROVED: PR #3 merged, checkpoint/evidence em reconciliação documental |
| NLE-P00-WO-001-EXT-002 | Catálogo de 80 módulos, 2D/2.5D/3D/web e Windows/Linux/macOS, MCP-first e no-MVP como propostas | Solicitação explícita owner após EXT-001 | APPROVED / MERGED (PR #5), catálogo técnico de candidatos; sem código |
| NLE-P00-WO-002 | Pesquisa de stack/licenças por módulo, começando em NLE-P00-WO-002-CORE-01 (issue #6) | EXT-002 catalog e checkpoint integrados | CORE-01 DOCUMENTATION IN PROGRESS; restantes PLANNED, sem implementação |
| NLE-P00-WO-003 | Arquitetura Core, memória, jobs, tempo, contratos | WO-002 APPROVED | PLANNED |
| NLE-P00-WO-004 | Arquitetura renderer, shaders, iluminação, VFX | WO-003 APPROVED | PLANNED |
| NLE-P00-WO-005 | World/terrain/physics/assets/audio | WO-003/004 APPROVED | PLANNED |
| NLE-P00-WO-006 | Rede, simulação e threat model | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-007 | Editor e autoria, UX e pipeline | WO-003/005 APPROVED | PLANNED |
| NLE-P00-WO-008 | Benchmarks, qualidade, CI futura multi-OS | WO-004/005/006/007 APPROVED | PLANNED |
| NLE-P00-WO-009 | Auditoria integral P00, resolução de ADRs | anteriores APPROVED | PLANNED |

## Política
Somente a próxima WO NECESSARY pode iniciar. Corrigir bloqueios e manter a mesma WO/PR; sem encavalamento. Não criar automaticamente todas as issues futuras. Entregas da fase M01+ são FUTURE até a aprovação do planejamento.
