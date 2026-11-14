# Requirements
Status: INITIAL CANDIDATES; somente decisões do proprietário no Ledger têm aprovação.

## Requisitos de programa (atuais)
- GOV-001: manter Source Pack Git versionado antes da primeira implementação da engine.
- GOV-002: operar solo; sem requisito de revisão humana externa.
- GOV-003: CI e automações de repositório com custo obrigatório de serviço R$0 no repositório público; sem CodeRabbit.
- GOV-004: toda alteração passa por WO, Context Lock, PR, testes aplicáveis, Evidence Bundle, auditoria e checkpoint controlado.
- GOV-005: nunca declarar recurso entregue sem teste; não iniciar próxima WO enquanto a atual estiver bloqueada ou exigir correção.
- BRAND-001: nome selecionado: Stormline; instituição: Stormline Engine by NexLabs; marca ainda requer clearance.
- BRAND-002: produzir guia detalhado de símbolo, paleta, tipografia, motion e áudio, com versões acessíveis.

## Capacidades pretendidas (NÃO implementadas)
- CAP-001: renderização 3D em tempo real, material PBR, sombras, efeitos de alta densidade e evolução de iluminação.
- CAP-002: VFX de alta qualidade com perfis de hardware e limites de simulação/transparência.
- CAP-003: áudio espacial, mixagem, dinâmica e diagnóstico de custo.
- CAP-004: personagens, animações, câmera, input e movimento fluidos.
- CAP-005: terrenos, streaming, LOD e cenários amplos.
- CAP-006: física, colisões e veículos terrestres e aéreos.
- CAP-007: rede com servidor autoritativo, segurança e replicação.
- CAP-008: editor, importador e formatos de assets versionados.
- CAP-009: desempenho escalável em GPUs/CPUs acessíveis.
- CAP-010: extensibilidade, diagnóstico, testes e compatibilidade.

## Novas diretrizes declaradas pelo proprietário (extensão documental em avaliação)
- CAP-011: 2D e 2.5D são modos de autoria de primeira classe, além de 3D.
- CAP-012: exportação e reprodução de jogos em navegador são parte da visão; matriz de compatibilidade, gráficos e custos precisam ser especificados.
- CAP-013: interface manual e **AI-native** com MCP, Codex, Claude e hosts LLM compatíveis, cobrindo todas as funções **públicas de autoria aprovadas**, por comandos tipados e controles de segurança.
- CAP-014: não publicar MVP; permitir builds internos de integração e testes, lançar 1.0 comercial somente após DoD completo e escopo 1.0 aprovado.
- CAP-016: suporte nativo obrigatório a **Windows, Linux e macOS** no Editor e nos jogos exportados, com matriz de versão/arquitetura e testes multi-OS; suporte web permanece requisito independente. Apple Silicon deve integrar a matriz; Intel e versão mínima serão definidos em ADR.
- CAP-015: capacidade extensível para múltiplos gêneros, sem exigir hardcode de regras particulares no núcleo.
Detalhamento ainda **PROPOSED**, ver [catálogo](product/module-catalog.md) e [prontidão comercial](product/full-release-readiness.md). Não há nova implementação aprovada por estes requisitos.

## Qualidade
- NFR-001: objetivos quantitativos só são válidos quando possuem cena, plataforma, versão, drivers, configuração e métrica.
- NFR-002: controles de segurança e licença para cada dependência e asset.
- NFR-003: separar runtime, editor e server para reduzir acoplamento.
- NFR-004: integridade de dados, migração de formatos e recuperação devem ser especificadas antes de persistência.
- NFR-005: toda decisão nova deve declarar trade-offs e alternativas.

## Critérios de rastreabilidade
Cada WO cita IDs de requisitos, condições de aceitação, testes/evidências, arquivos afetados e estado. Requisitos futuros serão refinados em ADRs e planos de benchmark; isso não autoriza implementação.
