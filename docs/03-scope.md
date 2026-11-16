# Scope
Status: P00 DOCUMENTATION ONLY

## Dentro do NLE-P00-WO-001 (NECESSARY)
- Documentar identidade proposta, logo, paleta, tipografia, intro, assinatura sonora e regras de produção dos assets.
- Criar Source Pack mínimo, Source Hierarchy, ADRs, Ledger, Checkpoint e Backlog.
- Formalizar governança solo, papel de Codex/Zcode, evidência, PR e controles de CI gratuitos.
- Implantar apenas o mínimo de automação de **validação documental**; sem código de engine.

## Extensão de apresentação NLE-P00-WO-001-EXT-001 (owner-requested)
Somente documentação e organização pública do repositório: README inglês profissional, versão pt-BR, Changelog, versionamento proposto, arquivos comunitários, templates de issues, padrões de formatação e validação documental ampliada. A extensão não altera o aceite da WO-001 nem antecipa a pesquisa tecnológica WO-002. Ver [Work Order específica](work-orders/NLE-P00-WO-001-EXT-001.md).

## Nova extensão de planejamento solicitada: NLE-P00-WO-001-EXT-002 (INDEX APPROVED / MERGED)
O proprietário exige primeiro um catálogo **completo** de módulos antes de fixar tecnologias: 2D, 2.5D, 3D, jogos web, suporte nativo a Windows/Linux/macOS para Editor e exports, editor profissional, MCP/LLM nativo e **sem MVP público**. Esta extensão foi integrada apenas como **documentação**, com inventário candidato, contratos de IA e critérios propostos de prontidão comercial. Ela não aprova automaticamente 80 módulos como MUST-HAVE, não altera o status de implementação e não avança a WO-002. Ver [Module Catalog](product/module-catalog.md), [MCP Contract](product/ai-mcp-contract.md), [Full Release](product/full-release-readiness.md) e [Work Order](work-orders/NLE-P00-WO-001-EXT-002.md).

## Extensão de preparação de execução — NLE-P00-WO-002-QUEUE-001 (owner-requested)
Preparar todos os **80 pacotes de Work Orders futuros**, issues de planejamento e contrato de handoff do Zcode, mas mantê-los **BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS**. Isto não transforma a taxonomia candidata em requisitos de código aprovados. A seleção de tecnologias, contrato de API/dados, caminhos concretos, critérios numéricos de benchmarks, risco e release-class são preenchidos e auditados ao detalhar cada módulo. Zcode não terá a responsabilidade de decidir arquitetura ou scope. Ver [fila](queue/README.md), [registro](queue/implementation-registry.json), [handoff](engineering/zcode-handoff.md) e [Work Order](work-orders/NLE-P00-WO-002-QUEUE-001.md).

## Fora do incremento
Nenhuma implementação C++, shader, build Vulkan, editor, física, VFX, runtime, servidor, asset gráfico final, vídeo final, áudio final, hospedagem, autenticação, credencial, release ou deploy da engine. Não presumir marca registrada nem uso exclusivo do nome.

## Classificação
- NECESSARY agora: documentos fundacionais, consistência, validação automática documental.
- IMPORTANT próximo: pesquisa tecnológica/licenças e benchmarks especificados, ainda sem implementação.
- FUTURE: runtime, renderizador, editor, multiplayer, VFX, áudio, eventual SDK e distribuição.
- OUT OF SCOPE atual: recursos pagos, requisitos de aprovação externa, cópia de IP de jogos e promessas de performance AAA.

## Expansão
Somente incluir uma funcionalidade no incremento quando houver evidência de que o DoD vigente a exige. Planejamento futuro não é autorização para programar.

## CORE-01 G1 — escopo 1.0 ratificado com limites (2026-11-16)
Ratificação **somente** de C01-D01, C01-D08, C01-D09 e C01-D14, mediante declaração expressa do proprietário. Fonte: [Ledger](10-decisions-ledger.md), [dossiê](research/core-01-01-owner-technical-decision-dossier.md) e [evidência](evidence/NLE-PRPLAN-CORE-01-01-G1-RATIFICATION.md). O incremento atual é exclusivamente documental.

- **D01:** o *mínimo* do CORE-01 é requisito pretendido para a 1.0: inicializar, gerenciar eventos/estados/erros, desligar e operar com/sem janela nos hosts de Editor, cliente/jogo, servidor e teste. Capacidades avançadas são condicionais, sem tornar todo módulo ou os 80 módulos mandatórios. MANDATORY_1_0 é ratificação **de direção do escopo mínimo**, não modificação automática do campo de registry.
- **D08:** Windows x86_64, Linux x86_64 e macOS arm64 (Apple Silicon) são os perfis iniciais desktop a qualificar. Wayland/X11 conforme capacidade real; macOS Intel e Windows arm64 condicionais. Versões mínimas de SO/SDK/glibc/CRT não foram escolhidas; Web é alvo separado PLAT-03, sem revogar a visão aprovada.
- **D09:** headless CPU-only verdadeiro, sem GPU, display/janela, sessão gráfica, áudio ou editor obrigatórios; servidor autoritativo NET-02 permanece módulo distinto.
- **D14:** protocolo de qualificação futura de 200 boots headless, 100 ciclos de janela por SO aprovado, 10.000 eventos e 30 cold + 30 warm amostras; nenhuma suíte foi executada.

**Não há ratificação de todo Scope/DoD 1.0 nem Gate G1 encerrado.** Mínimos de hardware, exclusões específicas e limites complementares permanecem abertos; release_class/risk dos 80 WOs seguem UNDECIDED/UNCLASSIFIED. ADR-0003 permanece PROPOSED, NLE-D009 OPEN; CORE-01-01/02 PLANNED_BLOCKED, nenhum código autorizado.
