# Solo Governance / Governança sem revisores externos
Status: DIRETRIZ DO PROPRIETÁRIO APROVADA; controles GitHub ainda por verificar.

## Quem decide
O proprietário administra, autoriza arquitetura, escopo, risco, PR e merge. GPT é arquiteto/auditor técnico; Codex/Zcode/DeepSeek são executores sob WO. Nenhum revisor humano externo obrigatório. Não usar CodeRabbit ou serviços de review pagos. Auditoria objetiva continua indispensável.

## Fluxo mandatório
ANALYZE -> SOURCE CHECK -> NEXT NECESSARY INCREMENT -> WORK ORDER -> CONTEXT LOCK -> PREFLIGHT -> EXECUTOR -> TESTS/EVIDENCE -> PR -> AUDIT -> APPROVED/CORRECTION REQUIRED/BLOCKED -> CHECKPOINT DELTA -> MERGE -> NEXT.

- Aprovações no GitHub: preferir PR obrigatório, **0 aprovações humanas exigidas**; nenhum CODEOWNERS que torne review obrigatório.
- Required checks devem usar nomes de jobs efetivamente existentes e estáveis; configurar proteção após o primeiro CI comprovado.
- Sem bypass de rulesets, force-push, merge forçado, reescrita de histórico ou ação destrutiva sem autorização explícita.
- Se o plano Free/estado do repositório impedir controle, registrar BLOCKED e não simular proteção.
- Owner approval + auditoria baseada em evidências pode permitir merge, não é necessário contratar aprovador de fora.
- Não criar dependência de produtos cobrados por uso ou que excedam o orçamento R$0.

## Regras de auditoria
Verificar Scope, Architecture, Requirements, DoD, diff, regressões, segurança, compatibilidade, tratamento de erros, testes e checkpoint proposto. Não aprovar defeito HIGH/CRITICAL. Corrigir na **mesma** WO/PR quando possível. O agente executor não promove unilateralmente Checkpoint Delta.

## Rastreabilidade
WO ID nas issues, branches, PR, mensagens de commit, evidence bundles e checkpoint. Corrigir nomenclatura e divergências antes de merge.
