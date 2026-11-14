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

## DoD futuros
Funcional, testado, documentado, deployado quando aplicável e validado em ambiente-alvo, incluindo perf, segurança, compatibilidade e migração conforme risco. Não aceitar claim "completed" desacompanhada de evidência.

## Falha
CORRECTION REQUIRED: corrigir somente na mesma WO/PR; BLOCKED: resolver pré-requisito. Nenhum próximo incremento até aprovação válida.
