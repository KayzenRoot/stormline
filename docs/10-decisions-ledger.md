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
| NLE-D011 | Branch protections/required checks concretamente ativos | VERIFIED_G2_BOUNDED | Ruleset `27393227` ativo exclusivamente na `main`, PR obrigatória, `docs-validation` strict (app 15368), squash, sem bypass/force/delete; [Evidence G2](evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md). Checks nativos futuros ainda não qualificados. |
| NLE-D012 | Assets finais de logo, áudio e animação | NOT PRODUCED | Produção futura |
| NLE-D013 | Sem MVP público: Stormline só poderá ser lançada após DoD completo da versão 1.0 aprovada; builds internos de testes permitidos | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D014 | Plataforma completa de criação 2D, 2.5D, 3D e jogos web, com editor manual | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D015 | AI-native, MCP para autoria com Codex, Claude e LLMs compatíveis; cobertura de operações públicas autorizadas, sem acesso irrestrito | OWNER-DIRECTED | Solicitação explícita do proprietário |
| NLE-D016 | Catálogo de 80 módulos e 14 domínios como índice arquitetural; classes obrigatórias para 1.0 e escolhas técnicas ainda não fixadas | APPROVED INVENTORY / OPEN RELEASE CLASSES | PR #5, auditada e integrada como planejamento |
| NLE-D017 | Windows, Linux e macOS como destinos desktop obrigatórios para Editor e jogos exportados; web continua planejado | OWNER-DIRECTED | Nova solicitação explícita; matrizes/targets mínimos dependem de ADR |
| NLE-D018 | Autonomia delegada para propostas técnicas e integrações documentais de rotina com CI/auditoria; despesas, ações irreversíveis, bypass e HIGH/CRITICAL permanecem bloqueadas sem autorização adequada | OWNER-DIRECTED | Solicitação de prosseguir sem perguntas repetitivas, condicionada à governança aprovada |
| NLE-D019 | Preparar todos os pacotes de Work Order/issues antes da execução, para Zcode se limitar à codificação após aprovação técnica | OWNER-DIRECTED | Solicitação explícita; o catálogo não libera code WOs automaticamente |
| NLE-D020 | Fila versionada de 80 drafts BLOCKED, execução permitida somente após ADR/contratos/arquivos/testes/Context Lock aprovados | APPROVED AS BLOCKED QUEUE, NOT CODING | PR #17 and 80 issues #18–97; registry mapping audited |
| NLE-D021 | CORE-02 Q4: metodologia `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` em host físico, com affinity antes do workload, hard memory cap via Job Object, 3 execuções, fail-closed e rótulo de hardware não exato | OWNER-RATIFIED | Conversa de 2026-11-21; [ADR-0106](adr/0106-core-02-q4-constrained-profile.md) |
| NLE-D022 | CORE-03: A (ADR-0005 só planejamento), B (LOW docs/ELEVATED implementação/INTERNAL_ONLY), C (benchmark jthread/Taskflow/enkiTS; oneTBB condicional; SFAS não iniciado), D2 (admissão limitada CORE-02-03..09, sem declarar módulo completo) | OWNER-RATIFIED | Conversa de 2026-11-21; [ADR-0105](adr/0105-core-03-limited-capability-admission.md) |
| NLE-D023 | CORE-03-04 “prioridades” satisfeito por CORE-03-03/JOB-04 (ordem FrameCritical>High>Normal>Background, tie-break TaskId, reserva background); sem aging, fairness weights, deadline ou código adicional | OWNER-DECIDED | “satisfeito continue” em 2026-11-21; [evidência](evidence/NLE-PRPLAN-CORE-03-04.md) |
| NLE-D024 | CORE-03-05 “dependências” satisfeito por CORE-03-03/JOB-02/JOB-03/JOB-09 (DAG, ciclo, arestas inválidas, ordem de commit, dependentes falhos); sem mutação dinâmica pós-finalize, dependências entre grafos ou resource policy | EVIDENCE-BASED SATISFACTION / OWNER CONTINUATION | Continuação de 2026-11-21; [evidência](evidence/NLE-PRPLAN-CORE-03-05.md) |
| NLE-D025 | CORE-03-06 “afinidade” satisfeito por CORE-03-03/JOB-06 (MainThread somente owner, worker wait DeadlockRisk, non-owner WrongThread, pump wrong-thread no-op); sem pinning de SO, NUMA, GPU/audio ou hard real-time | EVIDENCE-BASED SATISFACTION / OWNER CONTINUATION | Continuação de 2026-11-21; [evidência](evidence/NLE-PRPLAN-CORE-03-06.md) |
| NLE-D026 | CORE-03-07 “cancelamento” satisfeito por CORE-03-03/JOB-05/JOB-08 (escopo cooperativo, pending cancelado, isolamento, wait Cancelled, stop idempotente, pós-shutdown ShuttingDown); sem interrupção forçada ou cancelamento preemptivo | EVIDENCE-BASED SATISFACTION / OWNER CONTINUATION | Continuação de 2026-11-21; [evidência](evidence/NLE-PRPLAN-CORE-03-07.md) |
| NLE-D027 | CORE-03-08 “isolamento de dados” no escopo v0 = JobState privado por job + contextos caller-owned + commit serializado; resource read/write, aliasing, memória CORE-02 e isolamento GPU/audio ficam fora do v0 | EVIDENCE-BASED SATISFACTION / SCOPED | Continuação de 2026-11-21; [evidência](evidence/NLE-PRPLAN-CORE-03-08.md) |

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

## CORE-01 G1 — oito parâmetros expressamente ratificados pelo proprietário (2026-11-16)

**Fonte de autoridade:** declaração expressa do proprietário nesta conversa: “Como proprietário do Stormline, RATIFICO EXPRESSAMENTE as oito seleções técnicas G1-M01..G1-M08 do documento docs/research/core-01-01-g1-delegated-selection.md, no HEAD 709bcaaab9f4d1a95546ff62a4dceaeaf4935cf0, exatamente nos termos e limites apresentados”. O detalhamento e os limites estão na [seleção delegada](research/core-01-01-g1-delegated-selection.md) e no [Evidence Bundle da ratificação](evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-RATIFICATION.md). É transcrição da declaração na conversa, não assinatura digital GitHub. **Nenhuma das 11 decisões C01 restantes foi ratificada.**

| Decision | Decisão do proprietário, delimitada e condicionada a prova futura | Estado |
|---|---|---|
| G1-M01 | Windows 11 25H2 x64 como mínimo **provisório** de desktop, 26H2 como compatibilidade; revalidar lifecycle, versões e CPU suportadas no lançamento. Não certificar versões agora. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M02 | Ubuntu 24.04 LTS x86_64 / glibc 2.39 como distribuição e ABI **de referência inicial**, não compatibilidade automática com outras distros nem prova de símbolos. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M03 | macOS 15 arm64 Apple Silicon como deployment floor candidato e macOS 26 como compatibilidade; requisitos e versão mínima do host Xcode são independentes. Intel Mac condicional. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M04 | Baseline CPU x86_64 sem requisito de AVX/AVX2, com dispatch otimizado somente após detecção; Apple Silicon nativo arm64. Respeitar CPU suportada pelo sistema operacional e validar ISA real. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M05 | Fixtures de prova: headless CPU-only 2 processadores lógicos/4 GiB RAM sem GPU/display/áudio; smoke com janela 4 lógicos/8 GiB. **Não** são requisitos mínimos para o Editor nem a engine inteira. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M06 | Somente núcleo essencial CORE-01 é obrigatório na 1.0 (lifecycle, estados, erros, eventos, caminhos essenciais, janela básica e headless); extras condicionais. Release class machine permanece UNDECIDED até classificação por módulo autorizada e DoD global. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M07 | Protocolo futuro 200 ciclos headless/100 ciclos janela por SO, 10.000 eventos, 30 cold+30 warm; zero perda silenciosa de eventos críticos, testes negativos, nenhum UAF/leak detectado, erro tipado em até 5 s se display faltar. **p95/RSS ainda não definidos**, somente calibrar e submeter à ratificação posterior. | OWNER_RATIFIED_G1_BOUNDED |
| G1-M08 | Requalificar suporte do SO, segurança e vendors **90 dias antes de eventual release pública** e sempre que EOL afetar requisitos. Manter sem MVP público e 1.0 condicionada ao DoD completo. | OWNER_RATIFIED_G1_BOUNDED |

**Limites e STOP:** 8/8 ratificações são escolha de **requisitos futuros**, não testes/pisos certificados nem autorização de release. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`: versões mínimas de patch/SDK/toolchain, compatibilidade real, hardware, thresholds p95/RSS, mapa de release classes de 80 módulos e DoD comercial global ainda requerem provas/decisões. As quatro C01-D01/D08/D09/D14 ratificações anteriores persistem, outras 11 C01-Dxx continuam AWAITING_OWNER. G2 branch enforcement NÃO VERIFICADO; G3 tecnologia/ABI/licenças OPEN. ADR-0003/0075 PROPOSED, NLE-D009 OPEN; registry/manifest intocados, 80 coding WOs BLOCKED, CORE-01-01/02 PLANNED_BLOCKED, engine_implemented=false. Nenhuma suíte C++ executada.

## CORE-01 G2/G3 — ratificação expressa e delimitada das onze opções A (2026-11-16)

**Autoridade:** o proprietário declarou explicitamente: “RATIFICO EXPRESSAMENTE as recomendações A das 11 decisões C01-D02, C01-D03, C01-D04, C01-D05, C01-D06, C01-D07, C01-D10, C01-D11, C01-D12, C01-D13 e C01-D15, exatamente conforme docs/research/core-01-01-g2-g3-owner-decision-options.md, a partir do HEAD 139a874c69e6a358777bc3356ba4e51eb4ae1253, incluindo todas as ressalvas, trade-offs e obrigações de prova”. A declaração na conversa foi transcrita em [Evidence G2/G3](evidence/NLE-PRPLAN-CORE-01-01-G2G3-OWNER-RATIFICATION.md), e a [matriz de recomendações A](research/core-01-01-g2-g3-owner-decision-options.md) é parte integrante do alcance. **Não é aprovação automática da ADR, de tecnologia validada nem de execução.**

| ID | Direção técnica aprovada pelo proprietário, dentro dos limites da opção A | Obrigações pendentes e exclusões | Status |
|---|---|---|---|
| C01-D02 | C++20 interno; sem módulos C++20 obrigatórios, sem C++23 por padrão | Compilers/stdlib/SDK versões e builds nativos; sem aprovar ADR-0003 | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D03 | SDL3 como adapter fino do host, SDL escondida da API pública | Pin tag/hash/licenças; eventos, HiDPI, IME, hotplug nas três plataformas | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D04 | SDL3 vídeo/main thread com refcounts/init/quit balanceados, headless sem dependência de vídeo/áudio; shim main candidato | Entrypoints/cleanup em falha, deadlocks e threads por SO ainda NÃO EXECUTADOS | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D05 | CMake Presets + CTest Presets + Ninja padrão e fallback de geradores nativos | CMake 3.27/schema 6 ainda candidatos, não versão fixada; compilar/testar 3 SO | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D06 | C++ RAII/handles opacos internamente; preferir futura C ABI versionada apenas se plugin/SDK externo tiver escopo autorizado | Não prometer C++ ABI universal nem aprovar SDK/plugins; contratos de ownership pendentes | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D07 | Máquina de estados explícita, InitFailed recuperável e erros tipados/cleanup idempotente | Matriz de transição, falhas/timeout, 200/100 ciclos futuros, sem código | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D10 | SUPPORTED/UNSUPPORTED/UNKNOWN com fonte/confiança; thin adapter primeiro, SAPL somente mediante prova | Limite de overhead não aprovado, benchmark e casos UNKNOWN pendentes; GFX-01 mantém renderer | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D11 | Framework de risco por slice: STANDARD base candidato, ELEVATED integrações sensíveis, HIGH_ASSURANCE apenas quando aplicável | Nenhum WO classificado automaticamente; 80 risk=UNCLASSIFIED | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D12 | Objetivo de CI GitHub Actions R$0 e PRs isoladas, eventual proteção/required checks por decisão e execução separadas | **Snapshot histórico no ato da ratificação D12:** G2 NOT VERIFIED (`protected=false`, rulesets `[]`); o enforcement foi posteriormente autorizado e comprovado em ação independente (`27393227`, G2 CLEARED limitado ao `docs-validation`). D12 não autorizou por si escrita de settings. | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D13 | Licenças das dependências SDL3/CMake/Ninja e SBOM/SPDX por versão, hash e transitivos | Não escolher licença da engine, NLE-D009 OPEN, sem redistribuição autorizada | `OWNER_RATIFIED_G2G3_BOUNDED` |
| C01-D15 | Separar escolha conceitual da comprovação; WO experimental futura só se indispensável e expressamente autorizada | Não criar experimento/código; ADR-0003/0075 PROPOSED, CORE-01-02 BLOQUEADO | `OWNER_RATIFIED_G2G3_BOUNDED` |

**Interpretação vinculante:** ratificação da *direção candidata* não é qualificação da pilha: G3 permanece `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, naquele momento G2 `BLOCKED_NOT_VERIFIED` (snapshot histórico); **posteriormente** a etapa G2 independente comprovou `CLEARED` apenas no escopo `docs-validation` do ruleset `27393227`, sem checks nativos novos. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, 4 C01-D01/D08/D09/D14 + 8 G1-M01..M08 ratificações anteriores preservadas. ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`; não promover risk/release_class nem aprovar licenças da engine. 80 coding WOs `BLOCKED`, 0 ready/approved ADR, CORE-01-01/02 `PLANNED_BLOCKED`, `engine_implemented=false`. C01-Q001..Q032 `FUTURE_NOT_EXECUTED`. Comprovar stack/contratos/custos/segurança e revisar ADR em trabalho futuro separadamente autorizado.

## Readback factual posterior G2 / G3-V01 pendente (2026-11-16)
Os trechos anteriores marcados `G2 NOT VERIFIED` ou `rulesets=[]` pertencem aos momentos históricos das ratificações G1 e G2/G3, **antes da autorização administrativa e comprovação independentes do G2**. O estado atual, confirmado em readback da `main` no HEAD `b727790349e49de4ee71ec3416e109038f188d92`, é **G2 `CLEARED` somente para o ruleset `27393227`** e seu check `docs-validation`; não há aprovação de CI C++ nativa. [Evidence aplicado](evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-APPLIED.md).
A qualificação G3 exata mantém 23 ratificações bounded, mas **G3-V01 `AWAITING_OWNER`**, conforme [solicitação expressa na issue #387](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6928082093); **G3-V02 não autorizado**. ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`, registry/manifest intactos, 80 WOs de código `BLOCKED`, `CORE-01-02 PLANNED_BLOCKED` e `engine_implemented=false`. Este readback factual não registra novo voto nem escolhe versão/ABI.

## CORE-01 G3-V01 — ratificação expressa delimitada de baseline CANDIDATO (2026-11-16; registro posterior)
**Autoridade:** declaração expressa do proprietário nesta conversa, registrada de modo rastreável na [issue #387, comentário #6929911139](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6929911139), na mesma Work Order `NLE-PRPLAN-CORE-01-01`. **Decisão:** `G3-V01 OWNER_RATIFIED_OPTION_A_ADJUSTED_CANDIDATE_ONLY`, opção A COM AJUSTES. O readback anterior acima, `G3-V01 AWAITING_OWNER`, é snapshot histórico anterior a esta ratificação, NÃO estado atual. As **23 direções bounded anteriores** permanecem idênticas e não são recontadas como efeito deste voto separado.

**Baseline apenas para futura avaliação:** C++20 interno; MSVC **14.50 referência** e **14.52 comparador** (VS Build Tools 2026 18.12.0 é produto distinto cuja disponibilidade precisa de verificação), Windows SDK **10.0.26100.9457**; GCC **16.2**, LLVM/Clang **23.1.5**; Xcode **26.3**, **AppleClang full build ainda desconhecido**; SDL3 **3.4.20**; CMake **4.4.5 referência**, **4.5.0 comparador**; Ninja **1.13.2**. CMake mínimo **3.27** e `CMakePresets.json` **schema 6** foram aceitos **somente como candidatos**, não como mínimos contratados ou aprovados para produção.

**Limites e prova:** isto NÃO aprova versões instaladas/pins imutáveis, hash SHA-256, SDK/toolchain/ABI, artefatos, suporte Win/Linux/macOS, desempenho, licenças de terceiros, SBOM, redistribuição, compilação, testes ou ADRs. A escolha do candidato foi ratificada, mas **G3-P01..P16 permanecem `FUTURE_NOT_EXECUTED`** para as provas técnicas e verificação objetiva; nenhum PASS foi inferido. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G2 `CLEARED` somente pelo ruleset `27393227`, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; **G3-V02 `NOT_AUTHORIZED`**. ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`, registry/manifest/workflows intocados, **80 coding WOs `BLOCKED`**, zero ready/approved ADR, CORE-01-01/02 `PLANNED_BLOCKED`, `engine_implemented=false`. A próxima ação NECESSARY é documental e auditada; **nenhuma PR de implementação nem experimento nativo** foi autorizada.

## CORE-01 G3-V02 — documentação experimental AUTORIZADA, execução NÃO AUTORIZADA (2026-11-17)
**Autoridade expressa:** [proprietário na issue #387, comentário #6945990286](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6945990286) sob Work Order de governança `NLE-PRPLAN-CORE-01-01`. **Estado limitado:** `G3-V02 DOCUMENT_PREPARATION_AUTHORIZED_ONLY / EXPERIMENT_EXECUTION_NOT_AUTHORIZED`. O novo consentimento é SOMENTE DOCUMENTAL e não altera as 23 direções bounded históricas nem a ratificação candidata G3-V01.

Autorizado agora: proposta **não executável** de WO experimental separada [NLE-G3-V02-EXP-001](work-orders/NLE-G3-V02-EXP-001-PROPOSED.md), com todos os campos obrigatórios, fixture C++20 mínimo **apenas especificado**, matriz Win/Linux/macOS, proveniência/licenças/SBOM, segurança de forks, custo-alvo R$0, riscos ELEVATED **apenas propostos para execução futura**, provas G3-P02..P14 e Evidence Bundle; PR documental, Docs Validation, auditoria pt-BR, squash e checkpoint independente se devido.

**Expressamente NÃO autorizado:** executar G3-V02, escrever/compilar/rodar fixture, instalar SDK/toolchain, alterar CI/workflows/G2 ruleset `27393227`, registry/manifest/CORE-01-02 ou as 80 coding WOs, aprovar ADR-0003/0075, escolher NLE-D009, liberar G3 ou marcar provas G3-P01..P16 PASS. G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`, G1 PARTIAL, G2 CLEARED apenas no escopo documental, G3-V01 candidato, G3-V02 execução `NOT_AUTHORIZED`; 80 coding WOs `BLOCKED`, zero executor_ready/approved ADR, engine=false. **STOP após documentação auditada: exigir novo voto expresso para experimento.**

## CORE-01 G3-V05 — ratificacao de fatia interna (2026-11-17; ratificacao explicita, execucao condicionada)

**Autoridade:** Proprietario do Stormline ratificou expressamente na conversa de 2026-11-17 a Opcao A delimitada no comentario https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280; o comentario registra a PROPOSTA anterior, nao constitui por si o voto. A declaracao de aceite esta reproduzida na PR desta decisao.
**WO:** `NLE-PRPLAN-CORE-01-01`; **base Git confirmada:** `dfd3451cdf4cc3793c484656e5a4405e39a985eb`; **experimento:** [PR #421](https://github.com/KayzenRoot/stormline/pull/421) DRAFT, HEAD `0d27dc7cfe5c0adcb0c4e1800c929666d3b5deb0`, com [CI nativa 3/3](https://github.com/KayzenRoot/stormline/actions/runs/44124073355) e [docs-validation PASS](https://github.com/KayzenRoot/stormline/actions/runs/44124073329). Estes sao testes da fixture isolada, nao da engine nem das versoes candidatas exatas.

| Chave | Decisao EXPRESSAMENTE RATIFICADA somente para o primeiro incremento CORE-01 | Limite |
|---|---|---|
| C01-G3V05-01 | C++20 interno, `CPU_ONLY_HEADLESS` como primeira fatia, inicialmente sem SDL3 | Sem produto, janela, SDK externo, renderer ou API C publica |
| C01-G3V05-02 | CORE-01 `MANDATORY_1_0` **como objetivo futuro**; trabalho inicial `INTERNAL_ONLY` | Nao conclui G1 completo, Scope/DoD da engine 1.0, distribuicao nem release_class global do registry |
| C01-G3V05-03 | Risco `STANDARD` **para a primeira fatia interna**, com unit, integracao, lint aplicavel, builds multi-OS, erros negativos e regressao | Nao reclassifica as outras 79 WOs nem o experimento G3-V04 (risco distinto) |
| C01-G3V05-04 | Contrato a especificar em `NLE-PRPLAN-CORE-01-02`: tipos de estado/erro/configuracao, RAII, rollback de init parcial, encerramento idempotente | Nenhuma ABI externa/API publica/HostHandle final aprovada pelo voto |
| C01-G3V05-05 | CI provisoria: Windows MSVC `14.51`, Ubuntu GCC `13.3`, macOS AppleClang `17`, conforme receipts reais da PR #421 | Somente provas da fatia interna, nao qualifica G3 global nem substitui MSVC 14.50/14.52, SDK Windows .9457, GCC 16.2/Clang 23.1.5 ou CMake candidatos |
| C01-G3V05-06 | Tramitar decisao/contrato por PRs auditadas; `-03` de codigo somente apos satisfazer G1/G3/G4/G5/G6 delimitados | Nao aprova ADR-0003/0075 integralmente, NLE-D009, nem 80 WOs; sem atalho ou autopromocao |

**Status decorrente:** `OWNER_RATIFIED_BOUNDED_INTERNAL_DIRECTION`. Trata-se de autorizacao para tramitar as PRs canônicas minimas, nao de qualificar a stack inteira nem ativar executor por inferencia. O trecho selecionado da ADR-0003 continua dependente de qualificacao objetiva e decisao em PR; ADR-0003 permanece `PROPOSED` integralmente. `G1 PARTIALLY_RATIFIED_NOT_CLEARED`, `G2 CLEARED` somente ruleset `27393227`, `G3 OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; `G4` aprovacao tecnica da fatia PENDENTE, `G5` e `G6` pendentes; `NLE-PRPLAN-CORE-01-02/-03` ainda `PLANNED_BLOCKED`. Preservados ADR-0075 `PROPOSED`, `NLE-D009 OPEN`, `80/80` implementation WOs `BLOCKED`, `0` executor-ready, `748` packets `PLANNED_BLOCKED`, `engine_implemented=false`.

## CORE-01 packet NLE-PRPLAN-CORE-01-02 — bounded contract decision under G3-V05 (2026-11-17)

This section records the technical contract **PROPOSAL for audit**, not a new owner vote or implementation grant. The owner's ratification remains C01-G3V05-01..06 above: C++20 CPU-only headless `INTERNAL_ONLY`, future `MANDATORY_1_0` target and STANDARD first-slice risk. [ADR-0083](adr/0083-core-01-internal-headless-slice.md) is deliberately bounded to that slice; [typed contract](contracts/core-01-internal-headless-v0.md) and [WO -02](work-orders/NLE-PRPLAN-CORE-01-02.md) define prospective private interfaces, rollback, states and tests. G4/G5 become eligible for **BOUNDED** qualification only after exact-head Docs Validation and objective pt-BR audit of their PR and readback; G6 remains BLOCKED until a separate individual activation proof. The legacy ADR-0003/0075 remain PROPOSED in general; G3 global NOT_CLEARED and all 80 original coding WOs BLOCKED. Do not treat ADR-0083 as a new full CORE-01 release approval.

## CORE-02 Q4 — ratificação da metodologia de perfis limitados (2026-11-21)

**Autoridade:** proprietário do Stormline, resposta expressa à proposta `docs/research/core-02-q4-constrained-profile-proposal.md`.

O proprietário ratificou a opção **B**: metodologia `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` em host físico disponível, com CPU affinity comprovada antes do workload, hard memory cap de 4 GiB ou 8 GiB via Job Object, três execuções por perfil, validação fail-closed e rótulo explícito de que o hardware não é uma máquina física exata de 2 vCPU/4 GiB ou 4 vCPU/8 GiB. A ratificação não qualifica CORE-02, não seleciona allocator e não substitui os hosts Ubuntu 24.04 x64 e macOS 15 arm64 exigidos. Q4 permanece sem PASS completo; a campanha Windows será `PARTIAL_CONSTRAINED`, não qualificação de módulo.

## CORE-03 — ratificação A/B/C/D2 (2026-11-21)

**Autoridade:** proprietário do Stormline, resposta expressa à proposta `docs/research/core-03-limited-admission-proposal.md`.

- **A:** ADR-0005 ratificada somente como direção de planejamento, sem selecionar tecnologia/API/dependência/release/código.
- **B:** risco `LOW` para documentos, `ELEVATED` para implementação futura de concorrência, release `INTERNAL_ONLY` para primeiras fatias internas; sem release pública.
- **C:** benchmark isolado com baseline C++20 `std::jthread`/pool fixo, Taskflow 4.x e enkiTS; oneTBB condicional; SFAS não iniciado; nenhum candidato integrado ao default/API/produto sem benchmark, licenças/advisories e nova ratificação.
- **D2:** admissão limitada por capacidades concluídas `CORE-02-03..09`, sem declarar CORE-02 módulo completo e mantendo a dependência formal registrada. Autoriza somente preparar o contrato `CORE-03-02`; código exige `CORE-03-03` G6 e autorização posterior.

CORE-03-01 permanece governance-only; `CORE-03-02`..`-10` continuam `PLANNED_BLOCKED`. CORE-02 continua `NOT_QUALIFIED`; G3 `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 module WOs `BLOCKED`.
