# Definition of Done
Status: PROPOSED para o planejamento P00

## DoD da WO-001
1. Source Pack mínimo versionado em Git e indexado por README/hierarquia.
2. Branding documentado com separação explícita entre APPROVED, PROPOSED e NOT PRODUCED: nome, identidade, cores, logo, intro, áudio, aplicações.
3. Governança solo sem revisão humana externa, mas com PR, CI e auditoria objetiva.
4. CI gratuita documental verificável em PR, sem CodeRabbit/serviço pago; configurar required checks só após status existente.
5. Contrato de Codex/Zcode, template de WO e Evidence Bundle completos.
6. ADRs e Ledger coerentes com o consentimento do proprietário; sem declarações falsas sobre implementação, testes, marca ou licença.
7. Diff sem alterações inesperadas, sem segredos, sem arquivos de engine; documentação interna consistente.
8. Evidência: SHA base/head, arquivos, testes, resultados reais de CI, riscos, checkpoint delta proposto e revisão em pt-BR.
9. A auditoria conclui APPROVED sem HIGH/CRITICAL conhecido; merge sem bypass, seguido de verificação de main e atualização legítima do checkpoint.

## DoD da extensão NLE-P00-WO-001-EXT-001 (proposta do incremento)
1. README em inglês e versão pt-BR com estado de planejamento claramente visível, visão e áreas de pesquisa, arquitetura conceitual, roadmap, links, segurança, licença ainda aberta e transparência sobre benchmarks inexistentes.
2. Padrões de comunidade (contribuição, segurança, suporte, conduta), versionamento editorial e templates GitHub versionados.
3. Nenhum código de engine, logo final, release, credencial, serviço pago, review humano obrigatório ou decisão de licença por inferência.
4. Validação de todos os links locais, presença dos documentos e issue templates por Python stdlib; GitHub Actions docs-validation PASS no HEAD auditado.
5. Auditoria do diff, Evidence Bundle, ausência de HIGH/CRITICAL, PR aprovado e merge sem bypass; checkpoint e evidência reconciliados após merge.
6. Configurações de GitHub About, branch protections, private vulnerability reporting permanecem NOT VERIFIED enquanto o conector não suportar leitura/alteração.

## Critérios propostos da extensão de catálogo NLE-P00-WO-001-EXT-002
- Inventário de módulos 2D, 2.5D, 3D, web, gráfico, áudio, VFX, gameplay, editor, multiplayer, ferramentas e produto comercial.
- IDs únicos, dependências válidas sem ciclos e testes conceituais de aceitação por módulo.
- Contrato de comando comum a UI/CLI/MCP, autorização, schemas, transações, validação e compatibilidade MCP versionada.
- Conceito **No MVP**: marcos internos válidos, sem disponibilização comercial até atingir DoD global aprovado.
- Sem tecnologia aprovada por suposição; catálogo permanece PROPOSED até aceite do proprietário.
- CI documental e validador do catálogo verdes no SHA do PR; sem código de engine.

## DoD futuros
Funcional, testado, documentado, deployado quando aplicável e validado em ambiente-alvo, incluindo perf, segurança, compatibilidade e migração conforme risco. Não aceitar claim "completed" desacompanhada de evidência.

## Falha
CORRECTION REQUIRED: corrigir somente na mesma WO/PR; BLOCKED: resolver pré-requisito. Nenhum próximo incremento até aprovação válida.
