# Security / Segurança
Status: THREAT MODEL PLANNED; NÃO testado

## Superfícies prioritárias
Shaders e drivers; parsers de assets e formatos; plugins; arquivos do editor; scripts; memória nativa; canais de rede; servidores públicos; workflows de GitHub e tokens dos agentes.

## Controles mínimos
- Princípio de menor privilégio: GITHUB_TOKEN read-only por padrão; permissions: contents: read em Actions.
- Não executar código de PR não confiável com segredos; evitar pull_request_target em jobs que executam alterações do PR.
- Nenhum secret hardcoded, token, conta de terceiros ou credencial nos docs/logs/assets.
- Validar entradas, tamanhos, limites e proveniência de recursos; ferramentas nativas precisam de fuzzing e sanitizers quando criadas.
- Inventário SBOM, versões fixadas ou controladas, revisão de licenças e CVEs.
- Preparar ameaça de servidor autoritativo, validação de eventos, DoS/rate limiting e abuso de rede em ADR futuro.
- Controles de supply chain: auditoria de actions e dependências; sem serviços pagos ou CodeRabbit.
- Public repo não é sinônimo de software open source: licença ainda PENDING.
- Proibir force-push e bypass não autorizado; revisão externa não é requisito, mas testes objetivos são.

## Resposta a incidentes
Paralisar WO impactada como BLOCKED, registrar escopo, SHA, risco e mitigação; corrigir na mesma WO quando seguro, auditar novamente antes de merge. Não expor dados sensíveis no Evidence Bundle.
