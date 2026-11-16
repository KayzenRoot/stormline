# Decisions Ledger
Data base: 2026-11-14 | Responsável por aceite: proprietário NexLabs
Este Ledger separa instruções aprovadas pelo proprietário, propostas técnicas e ações de execução.

| ID | Decisão / situação | Estado | Base |
|---|---|---|---|
| NLE-D001 | Nome do produto: **Stormline** | OWNER-SELECTED | Conversa do proprietário |
| NLE-D002 | Engine própria da NexLabs, com bibliotecas especializadas | OWNER-APPROVED | Conversa do proprietário |
| NLE-D003 | Desenvolvimento de longo prazo, faseado, documental antes do código | OWNER-APPROVED | Conversa do proprietário |
| NLE-D004 | Sem obrigação de revisores humanos externos; proprietário decide | OWNER-APPROVED | Conversa do proprietário |
| NLE-D005 | Repositório público; CI/segurança gratuitos; proibição de CodeRabbit | OWNER-APPROVED | Conversa do proprietário |
| NLE-D006 | Identidade Dark Premium Tech, paleta azul/ciano e S energético | PROPOSED | Brand Foundation v0.1 |
| NLE-D007 | Slogan Power Meets Precision | PROPOSED | Brand Foundation v0.1 |
| NLE-D008 | C++20, Vulkan, SDL3, Jolt etc. | PROPOSED | Pesquisa P00 pendente |
| NLE-D009 | Licença do código da engine | OPEN | Não decidir implicitamente |
| NLE-D010 | Registro de marca/domínio e disponibilidade de Stormline | OPEN | Clearance pendente |
| NLE-D011 | Branch protections/required checks concretamente ativos | NOT VERIFIED | Inspeção de settings pendente |
| NLE-D012 | Assets finais de logo, áudio e animação | NOT PRODUCED | Produção futura |
| NLE-D013 | Sem MVP público: Stormline só poderá ser lançada após DoD completo da versão 1.0 aprovada; builds internos de testes permitidos | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D014 | Plataforma completa de criação 2D, 2.5D, 3D e jogos web, com editor manual | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D015 | AI-native, MCP para autoria com Codex, Claude e LLMs compatíveis; cobertura de operações públicas autorizadas, sem acesso irrestrito | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D016 | Catálogo de 80 módulos e 14 domínios como índice arquitetural; classes obrigatórias para 1.0 e escolhas técnicas ainda não fixadas | APPROVED INVENTORY / OPEN RELEASE CLASSES | PR #5, auditada e integrada como planejamento |
| NLE-D017 | Windows, Linux e macOS como destinos desktop obrigatórios para Editor e jogos exportados; web continua planejado | OWNER-DIRECTED | Nova solicitação explícita; matrizes/targets mínimos dependem de ADR |
| NLE-D018 | Autonomia delegada para propostas técnicas e integrações documentais de rotina com CI/auditoria; despesas, ações irreversíveis, bypass e HIGH/CRITICAL permanecem bloqueadas sem autorização adequada | OWNER-DIRECTED | Solicitação de prosseguir sem perguntas repetitivas, condicionada à governança aprovada |
| NLE-D019 | Preparar todos os pacotes de Work Order/issues antes da execução, para Zcode se limitar à codificação após aprovação técnica | OWNER-DIRECTED | Solicitação explícita; o catálogo não libera code WOs automaticamente |
| NLE-D020 | Fila versionada de 80 drafts BLOCKED, execução permitida somente após ADR/contratos/arquivos/testes/Context Lock aprovados | APPROVED AS BLOCKED QUEUE, NOT CODING | PR #17 and 80 issues #18–97; registry mapping audited |

Os estados OWNER-* são contexto aprovado; o arquivo em si só vira fonte canônica após auditoria e integração do PR. Nenhuma proposta técnica é aprovada por simples inclusão em documentação. Ver [ADR 0001](adr/0001-original-engine.md), [ADR 0002](adr/0002-solo-free-governance.md).

## CORE-01 G1 — ratificação expressa delimitada do proprietário (2026-11-16)
**Autoridade:** o proprietário declarou nesta conversa: “RATIFICO EXPRESSAMENTE, sem modificações, as recomendações C01-D01, C01-D08, C01-D09 e C01-D14 apresentadas para o Gate G1, incluindo os limites e obrigações de prova descritos”. Ver [issue #387](https://github.com/KayzenRoot/stormline/issues/387) e [Evidence Bundle G1](evidence/NLE-PRPLAN-CORE-01-01-G1-RATIFICATION.md). É transcrição documental de autorização na conversa, não assinatura digital independente no GitHub.

| ID | Conteúdo ratificado (limitado) | Estado | Proof obligations remanescentes |
|---|---|---|---|
| C01-D01 | Núcleo **mínimo** do host CORE-01 obrigatório para futura 1.0 de Editor/jogo-cliente/servidor/testes desktop; capacidades avançadas separadas. Proposta de MANDATORY_1_0 somente para mínimo, não para todos os 80 módulos. | OWNER_RATIFIED_G1_BOUNDED | Detalhar mínimos, exclusões e DoD global; **registry release_class UNDECIDED** até qualificação e decisão específica. |
| C01-D08 | Windows x86_64, Linux x86_64, macOS Apple Silicon arm64 como perfis iniciais desktop obrigatórios candidatos; Wayland/X11 por capacidade; macOS Intel e Windows arm64 condicionais. Web permanece PLAT-03. | OWNER_RATIFIED_G1_BOUNDED | Versões mínimas SO/CPU/SDK/GLIBC/CRT, recursos e hardware físico ainda NOT_QUALIFIED. |
| C01-D09 | Host CPU-only headless sem depender de GPU, display/janela, sessão gráfica, dispositivo de áudio ou editor; NET-02 é dono futuro do servidor autoritativo. | OWNER_RATIFIED_G1_BOUNDED | Provar isolamento, boot/teardown, erros, recursos, sem leaks e 200 ciclos por SO aprovado; NOT_EXECUTED. |
| C01-D14 | Protocolo futuro com 200 ciclos headless, 100 ciclos de janela por SO aprovado, 10.000 eventos, 30 amostras cold + 30 warm e 32 cenários FUTURE; sem alegar PASS ou p99/FPS. | OWNER_RATIFIED_G1_BOUNDED | Definir hardware e thresholds ainda abertos, executar CI nativa/testes reais/sanitizers e publicar recibos. |

**Alcance exato:** estas quatro ratificações **não** aprovam ADR-0003/0075, C++20/SDL3/CMake/Ninja, ABI, G2/regras GitHub, NLE-D009 (OPEN), riscos/registry, teste de produto ou implementação. **Onze decisões C01-D02..D07/D10..D13/D15 permanecem AWAITING_OWNER**; G1 PARTIALLY_RATIFIED_NOT_CLEARED, G2 NOT VERIFIED, G3 OPEN. Todos os 80 code WOs BLOCKED, CORE-01-01 e CORE-01-02 PLANNED_BLOCKED e engine_implemented=false.
