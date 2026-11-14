# ADR-0002: Solo governance with free public CI
Date: 2026-11-14 | Status: OWNER-APPROVED DIRECTION

## Contexto
O proprietário não deseja revisor humano externo nem custos obrigatórios de qualidade/CI. Repo é público.

## Decisão
PRs com verificação automatizada, auditoria objetiva e aprovação administrativa do proprietário, **sem required approvals de terceiros**. Proibir CodeRabbit e ferramentas pagas obrigatórias. Usar runners padrão gratuitos de GitHub Actions e controles de segurança públicos elegíveis.

## Alternativas
Review humano obrigatório, SaaS pago, desenvolvimento direto em main; rejeitadas como fluxo normal.

## Consequências
Responsabilidade integral de governança e risco do proprietário; reforçar testes/CI e Evidence Bundle. Preferir branch protection de PR + checks + 0 reviews, sem bypass. A configuração do GitHub é ação operacional separada; não presumir concluída pelo ADR.
