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

## CORE-01 G1 — parâmetros mínimos 1.0 expressamente ratificados, sujeitos a qualificação (2026-11-16)

O proprietário ratificou individualmente por conjunto identificado `G1-M01..M08`, mantendo o escopo original `C01-D01/D08/D09/D14`. Ver [Ledger](10-decisions-ledger.md), [seleção que delimita as alternativas](research/core-01-01-g1-delegated-selection.md) e [Evidence Bundle](evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-RATIFICATION.md).

- **M01/M02/M03:** matriz inicial de Windows 11 25H2 x64 piso **provisório** (26H2 compatível), Ubuntu 24.04 LTS x64 com glibc 2.39 de referência e macOS 15 Apple Silicon arm64 (26 compatível). Fixação de builds, patches, toolchains e **comprovação de compatibilidade** pendentes. Reavaliar pisos que percam suporte antes da distribuição. Windows ARM64 e macOS Intel condicionais; Web continua PLAT-03.
- **M04/M05:** não impor AVX/AVX2 no host mínimo x86_64; otimizações dependem de ISA detectada e CPUs oficiais do SO. **Hardware de prova** headless: 2 processadores lógicos/4 GiB; com janela: 4 lógicos/8 GiB, sem estabelecer mínimo comercial da engine/Editor nem requisito de GPU do renderer.
- **M06:** núcleo mínimo de CORE-01 é obrigatório como objetivo 1.0: init/teardown, lifecycle, estados/erros tipados, eventos delimitados, paths essenciais e modos janela/headless. Recursos avançados condicionais; não adotar classes MANDATORY_1_0 para os 80 módulos por inferência.
- **M07/M08:** protocolo futuro conforme [DoD](09-definition-of-done.md), sem teste executado. Requalificação 90 dias antes de eventual release pública, sem MVP público; nenhuma data de lançamento aprovada.

**G1 permanece parcialmente ratificado e NÃO CLEARED:** arquitetura tecnológica, SDKs exatos, provas de hardware, thresholds p95/RSS, escopo produto 1.0 e classes globais seguem pendentes. Registro de código e manifesto PLANNED_BLOCKED, ADR-0003 PROPOSED e NLE-D009 OPEN continuam intactos. Este incremento autoriza **somente documentação** das oito escolhas.

## CORE-01 G2/G3 — escolha arquitetural limitada, sem autorização de implementação (2026-11-16)

O proprietário ratificou as opções A de **C01-D02/D03/D04/D05/D06/D07/D10/D11/D12/D13/D15**, todas com ressalvas do [dossiê de qualificação](research/core-01-01-g2-g3-owner-decision-options.md) e [Evidence](evidence/NLE-PRPLAN-CORE-01-01-G2G3-OWNER-RATIFICATION.md). **Escopo imediato: somente formalização documental.**

- **Host e build:** direção de C++20 interno sem módulos C++20 obrigatórios; SDL3 através de adapter interno não vazando headers/tipos na ABI; modo janela em main thread e headless sem vídeo/áudio obrigatórios; CMake/CTest Presets + Ninja com fallback nativo. Versões concretas de compiladores/CMake/SDL/SDK, hashes e smoke nativo permanecem **não definidos/não executados**.
- **API e comportamento:** C++/RAII internamente e HostHandle opaco; futura C ABI versionada só para fronteira externa *se plugin/SDK tiver aprovação própria*; lifecycle tipado com init parcial/cleanup, capacidade tri-state; SAPL proprietária somente mediante benefício demonstrado.
- **Segurança e governança:** escolha de framework de risco por slice e CI padrão GitHub R$0. Na ratificação limitada de D12, a proteção ainda exigia autorização e prova separadas: o snapshot histórico era `protected=false`, rulesets `[]`. **Posteriormente, G2 foi autorizado e comprovado separadamente**: ruleset `27393227` ativo só na `main`, PR obrigatória, `docs-validation` strict, squash e nenhum bypass; `G2 CLEARED` somente nesse escopo, conforme [Evidence G2 aplicado](evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md). Este registro não modifica o ruleset nem autoriza checks nativos. Licenças **terceirizadas** serão verificadas sem escolher a licença Stormline (`NLE-D009 OPEN`).
- **Dependência experimental:** qualquer experimento para validar a pilha exige **Work Order própria e autorização futura explícita**, não é automaticamente iniciado pela decisão D15. O pacote `CORE-01-02` e as 80 WOs de código continuam bloqueados.

Estas direções **não** estabelecem alcance de plugin/SDK, risco específico, release_class, mecanismo de build já funcional, compatibilidade certificada nem DoD 1.0 concluído. As 12 ratificações anteriores de G1 permanecem; G1 parcial; **G2 passou de NOT VERIFIED no snapshot desta seção a CLEARED após a aplicação independente do ruleset 27393227**; G3 continua não tecnicamente liberado, G3-V01 `AWAITING_OWNER`, G3-V02 não autorizado e ADR-0003/0075 PROPOSED.

## CORE-01 G3-V01 — baseline candidato ratificado, sem execução (2026-11-16; registro posterior)
A [declaração expressa do proprietário na issue #387](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6929911139) **ratifica a opção A COM AJUSTES apenas como seleção de candidatos para futura avaliação**, vinculada à WO `NLE-PRPLAN-CORE-01-01`. Esta seção posterior substitui **somente o status temporal G3-V01 `AWAITING_OWNER`** mencionado no histórico acima: o estado atual é `G3-V01 OWNER_RATIFIED_OPTION_A_ADJUSTED_CANDIDATE_ONLY`. **Não** altera as 23 decisões bounded previamente ratificadas nem transforma G3 em `CLEARED`.

Candidatos selecionados: C++20; MSVC **14.50 referência / 14.52 comparador** e SDK Windows **10.0.26100.9457**; GCC **16.2 / Clang 23.1.5**; Xcode **26.3**, AppleClang completo **pendente de verificação**; SDL3 **3.4.20**; CMake **4.4.5 referência / 4.5.0 comparador**; Ninja **1.13.2**. **CMake mínimo 3.27 e Presets schema 6 são candidatos apenas**, não mínimos de produção aprovados. Não se inferem instalação real, hashes, ABI, direitos de redistribuição ou suporte multiplataforma.

**Fora do escopo autorizado:** G3-V02, execução de provas nativas, C++/build, PRs de código, aprovação ADR-0003/0075, decisão de licença NLE-D009, alteração G2 (ruleset `27393227`), registry/manifest/workflows, classes de risco/release e CORE-01-02. G3-P01..P16 continuam `FUTURE_NOT_EXECUTED`; G1 segue parcial, G2 apenas `CLEARED` no escopo documental protegido, G3 **não qualificado tecnicamente**, 80 WOs de código `BLOCKED`, `engine_implemented=false`.

## CORE-01 G3-V02 — permissão documental separada, execução BLOQUEADA (2026-11-17)
[Autorização expressa do proprietário, #6945990286](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6945990286) permite somente a elaboração/auditoria da [proposta futura de experimento NLE-G3-V02-EXP-001](work-orders/NLE-G3-V02-EXP-001-PROPOSED.md), sob a mesma WO de qualificação `NLE-PRPLAN-CORE-01-01`. Este registro POSTERIOR esclarece o histórico `Fora do escopo autorizado: G3-V02`: a **EXECUÇÃO de G3-V02 continua fora do escopo**; somente a **PREPARAÇÃO DOCUMENTAL** foi autorizada. Nenhum código, compilação, testes nativos, toolchain, CI workflow, mudança em G2/registry/manifest, ADR/licença ou avanço CORE-01-02 é permitido.

Risco futuro `ELEVATED` é **proposta**, não classe das 80 coding WOs. G3-V01 ratificado como CANDIDATO, 23 direções bounded anteriores preservadas, G3 tecnicamente não liberado, provas G3-P01..P16 `FUTURE_NOT_EXECUTED`, G3-V02 `EXPERIMENT_EXECUTION_NOT_AUTHORIZED`, G2 CLEARED apenas ruleset 27393227, ADR-0003/0075 PROPOSED, NLE-D009 OPEN, 80/80 WOs BLOCKED, CORE-01-01/02 PLANNED_BLOCKED e engine=false. Após PR documental, STOP e requerer nova autorização de execução.

## CORE-01 G3-V05 — ratificacao de fatia interna (2026-11-17; objetivo de produto vs primeira fatia)

Ratificacao EXPRESSA do owner na conversa posterior ao registro historico G3-V02, sob `NLE-PRPLAN-CORE-01-01`, com proposta rastreada em [issue #387 comentario #6954081280](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280). Apenas o CORE-01 tem objetivo futuro `MANDATORY_1_0` para capacidades minimas platform/lifecycle; a **primeira fatia tecnica e somente `INTERNAL_ONLY`**: processo CPU-only headless, C++20, estados e erros tipados, RAII e rollback, sem SDL3, janela, render, GPU/audio, plugins, C ABI externa, rede ou release. Nao exige as 80 capacidades para o primeiro build e nao afirma funcionalidades da engine prontas.

Os compiladores encontrados em [PR #421](https://github.com/KayzenRoot/stormline/pull/421) podem ser usados como CI **PROVISORIA para esta fatia**, nao como matriz final de suporte ou alteracao dos candidatos G3-V01. `STANDARD` foi ratificado para a primeira fatia de codigo; prova e contrato ainda exigem gate. `G1` global segue parcial, `G3` global nao qualificado, `ADR-0003/0075` PROPOSED, `NLE-D009` OPEN. Registro, manifesto, 80 WOs e CORE-01-02/03 nao sao promovidos por este Scope. A aprovacão por gate G4/G5/G6 e PRs sequenciais permanece obrigatoria.
