# Codex / Zcode / DeepSeek — Executor Playbook
Status: PROCESS PROPOSED alinhado às instruções do proprietário.

## Entrada
Receber 1 Work Order com ID estável, branch base/HEAD SHA, arquivos canônicos, objetivos mensuráveis e stop condition. Confirmar que a WO anterior está APPROVED e as fontes não estão STALE.

## Preflight obrigatório
1. Ler AGENTS, Checkpoint, Ledger/ADRs, Scope, DoD, Architecture e documentos de domínio relevantes.
2. Fazer git status, log, branch, SHA base/head, diff e fingerprints SHA-256 dos documentos críticos.
3. Verificar conflitos com PRs, CODEOWNERS, rulesets, CI e restrições de pagamento.
4. Classificar risco e registrar testes exigidos. Se faltar fonte ou houver conflito, BLOCKED.
5. Não criar implementação de engine enquanto P00 não estiver APPROVED.

## Execução
- Branch do tipo docs/NLE-P00-WO-001-...; usar o mesmo WO ID no PR e Evidence Bundle.
- Implementar somente o necessário; preferir pequenos commits, sem refatoração lateral.
- Mudança visual: produzir alternativas editáveis, demonstrar responsividade, cores, contrastes e licenças, mas nunca autopromover a arte para APPROVED.
- Dependência nova: analisar licença, manutenção, CVEs, custo, API, fallback, substituibilidade.
- Código: unit tests e integrações; profiling para claims de performance; não editar testes para esconder regressões.
- Commit/push, abrir/atualizar PR; aguardar checks, auditar objetivamente.
- Qualquer CORRECTION REQUIRED volta à mesma branch/PR, não abre nova WO paralela.

## Evidence Bundle obrigatório
WO ID, objetivo, base_sha/head_sha, arquivos, diffs, decisões, comandos exactos e resultados, CI links/status, testes/lint/typecheck/build aplicáveis, análise de segurança/arquitetura/licença, risco residual, erros/correções, rollback, e Checkpoint Delta **proposto**.

## Review em português brasileiro
Veredito: APPROVED, CORRECTION REQUIRED ou BLOCKED, com falhas severizadas e referências a evidência. Somente após APPROVED e merge válido: ler main de novo, atualizar fontes canônicas afetadas e registrar checkpoint delta. Não alegar ações não executadas.

## Escalada
Sem revisão externa, sem CodeRabbit, sem pagamento, sem bypass; impossibilidade real deve ser documentada como BLOCKED e apresentada ao proprietário.
