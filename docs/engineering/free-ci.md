# Free CI & Tooling Policy
Status: POLÍTICA APROVADA; baseline DOCS-CI incluída nesta proposta, execução pendente.

## Restrições
Custo obrigatório de serviço R$0, repo público. Não integrar CodeRabbit ou serviços que exijam assinatura, créditos pagos, cartão ou overage. Nunca assumir que todas as ferramentas são ilimitadas: conferir termos, rate limits, retenção, concorrência e políticas de uso do GitHub.

## Camada P00 (agora)
- GitHub Actions em runner padrão ubuntu-latest para documentação; actions/checkout confiável; permissions: contents: read.
- Python da imagem hospedada, biblioteca padrão, scripts/validate_docs.py (sem pip/npm/credenciais).
- Job estável docs-validation, acionado por PR e push em main.
- Bloquear merge por checks somente depois de primeiro run PASS confirmado.
- Não instalar CodeRabbit, não pagar CodeQL, não chamar APIs externas, não configurar tokens.

## Camada M01+ (futura, depende do código)
- Linux: CMake/CTest, clang-format, clang-tidy, UBSan/ASan, compiladores suportados.
- Windows: build e testes em runner padrão Windows se necessário; lidar com toolchain e orçamento de armazenamento.
- CodeQL para repositórios públicos com suporte às linguagens utilizadas; Dependabot alertas/updates gratuitos conforme elegibilidade; revisar política antes de ativar.
- Licenças/SBOM: inventário reproduzível e scanner livre quando comprovado.
- Render/benchmark de GPU real deve rodar em hardware dedicado ou executor aprovado, nunca declarar que runners de CI possuem GPU compatível.

## Segurança Actions
Evitar pull_request_target em código não confiável, restringir permissões, dependências versionadas, runners efêmeros e sem secrets; auditar actions antes de adicionar. Caches e artifacts somente necessários; nenhum workflow com conta paga.

## Proteção da main (planejada, não comprovada)
Exigir PR, checks reais de docs-validation, proibir force-push/deletion, 0 required approvals e sem external required reviewer. Não afirmar que essas opções foram aplicadas se não foi possível ler/gravar as settings.

## Gate operacional
CI verde é evidência, não prova suficiente de qualidade. Conferir diff, conteúdo documental, segurança e licenciamento. Se falhar, CORRECTION REQUIRED.
