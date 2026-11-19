# CORE-03 — Pacote de decisão ADR-0005 e contrato -02

**Status:** `DECISION_PACKAGE / ADR-0005 PROPOSED / NO CODE AUTHORIZED / CORE-03-01 GOVERNANCE ONLY`. **Base:** `cd2e6f77a4ede2a47fc64229686c061d5e24ece1`. **Módulo:** CORE-03. **Issue:** #20. **Referências:** [ADR-0005](../adr/0005-core-03-jobs-concurrency.md), [arquitetura CORE-03](../architecture/core-03-concurrency-jobs.md), [ADR-0103](../adr/0103-core-03-governance-gate.md), [governance contract](../contracts/core-03-governance-v0.md).

## 1. Estado atual

- `CORE-03-01` é `APPROVED_GOVERNANCE` somente como planejamento.
- `CORE-03-02`..`-10` permanecem `PLANNED_BLOCKED`; não há `EXECUTOR_READY`.
- ADR-0005 é `PROPOSED`; nenhuma tecnologia foi selecionada; nenhum código/teste de concorrência existe.
- CORE-02 permanece `NOT_QUALIFIED`; a dependência formal CORE-02 não está satisfeita.
- G3 global `NOT_CLEARED`; NLE-D009 `OPEN`; 80/80 WOs BLOCKED.

## 2. Decisão A — Status da ADR-0005

| Opção | Conteúdo | Trade-offs | Risco |
|---|---|---|---|
| A (recomendada) | Ratificar ADR-0005 **somente como direção de planejamento** para o contrato `-02` e benchmark de candidatos | Permite preparar contrato sem escolher tecnologia; mantém código bloqueado | Baixo se o texto excluir implementação/release |
| B | Ratificar como decisão de implementação | Permitiria código sem benchmark/contrato | Alto; rejeitada |
| C | Rejeitar ADR-0005 | Encerra a direção atual | Perde trabalho de pesquisa; não recomendada |

**Texto exato para ratificação:**
> RATIFICO a ADR-0005 exclusivamente como direção de planejamento do CORE-03 para contrato e benchmark de candidatos. Esta ratificação não seleciona Taskflow, enkiTS, oneTBB, SFAS ou qualquer tecnologia, não aprova API, dependência, release, thresholds ou código, e não altera CORE-02/G3/licença.

## 3. Decisão B — Classe de risco e release

| Item | Proposta | Justificativa |
|---|---|---|
| Artefato de planejamento (`-01`/`-02`) | `LOW` | Documentos/contrato sem execução concorrente |
| Implementação futura | `ELEVATED` | Data races, deadlock, cancelamento, starvation, ordem de commit |
| Release class futura | `INTERNAL_ONLY` | Sem qualificação física/segurança/ABI/licença |

**Texto exato para ratificação:**
> RATIFICO `LOW` para os artefatos documentais CORE-03, `ELEVATED` para a implementação futura de concorrência e `INTERNAL_ONLY` como release class proposta para as primeiras fatias internas. Nenhuma release pública é autorizada.

## 4. Decisão C — Tecnologia candidata

| Candidato | Papel | Vantagens | Riscos |
|---|---|---|---|
| C++20 `std::jthread` + pool fixo | Baseline/controle | Sem dependência; lifecycle claro; determinismo simples | Escala limitada; não é task graph |
| Taskflow 4.x (MIT) | Grafo/DAG baseline | API madura, header-only, dynamic subflows | Versão/licença/ABI; overhead a medir |
| enkiTS (zlib) | Comparador fine-grained | Leve, portátil | Menos recursos de grafo; medir |
| oneTBB (Apache-2.0) | Terceiro comparador | Ecossistema maduro | Footprint/ABI/dependência; apenas se justificado |
| SFAS proprietário | R&D | Potencial budget/determinismo | Sem evidência; não iniciar antes dos baselines |

**Recomendação:** benchmark isolado com baseline fixo + Taskflow + enkiTS; oneTBB somente se dependência for justificada; SFAS somente após baselines. Nenhum vencedor declarado sem hardware, licenças, advisories e métricas.

**Texto exato para ratificação:**
> RATIFICO um programa de benchmark isolado para CORE-03 com baseline C++20 `std::jthread`/pool fixo, Taskflow 4.x e enkiTS, mantendo oneTBB como comparador condicional e SFAS como pesquisa não iniciada. Nenhum candidato será integrado ao default, à API pública ou ao produto antes de benchmark, licenças/advisories e nova ratificação.

## 5. Decisão D — Dependência CORE-02

| Opção | Conteúdo | Consequência |
|---|---|---|
| A (recomendada) | Manter código CORE-03 bloqueado até CORE-02 module qualification | Rigor formal; atrasa CORE-03 |
| B | Capability admission limitada usando `-03..-09` concluídos, sem declarar CORE-02 completo | Permite preparar/implementar fatia interna com dívida formal explícita | Exige ratificação específica e ADR-0086 |
| C | Ignorar dependência | Inaceitável |

**Recomendação:** A para código; B somente se o proprietário quiser antecipar uma fatia interna e ratificar a admissão por capacidade, mantendo CORE-02 `NOT_QUALIFIED`.

**Texto exato para ratificação (se B):**
> RATIFICO uma admissão por capacidade para a primeira fatia interna CORE-03 baseada nos pacotes concluídos CORE-02-03..-09, sem declarar CORE-02 módulo completo e sem promover G3/release. A dependência formal CORE-02 permanece registrada e o closeout CORE-03 exigirá sua qualificação ou nova decisão.

## 6. Contrato CORE-03-02 — pré-requisitos

O contrato só pode ser preparado após A/B/C (e D, se B) ratificados. Deve definir, no mínimo:

- `TaskId`, `JobRequest`, `JobHandle`, `TaskGraph`, `JobFence`, `CancellationScope`, `WorkBudget`, `ExecutorStats`;
- erros tipados: `CANCELLED`, `DEPENDENCY_FAILED`, `RESOURCE_EXHAUSTED`, `DEADLINE_MISSED`, `CYCLE_FOUND`, `AFFINITY_VIOLATION`, `DEADLOCK_RISK`, `WORKER_SHUTDOWN`;
- ownership CORE-01/02/04/06/GFX/AUD e proibição de tipos de terceiro na API;
- determinismo de commit, cancelamento, shutdown, backpressure e isolamento de dados;
- allowlist exata, testes negativos, TSan/ASan/UBSan e benchmark report-only;
- nenhuma implementação antes do gate G6 de `-03`.

## 7. Bloco consolidado de ratificação

```text
A = ADR-0005 apenas como direção de planejamento
B = risco LOW (docs) / ELEVATED (implementação) / release INTERNAL_ONLY
C = benchmark baseline jthread + Taskflow 4.x + enkiTS; oneTBB condicional; SFAS não iniciado
D = manter código bloqueado até CORE-02 module qualification
    [ou D = admissão por capacidade CORE-02-03..-09, sem declarar módulo completo]
```

Qualquer item não ratificado mantém `CORE-03-02` e todos os pacotes de código bloqueados.

## 8. Limites

Este pacote não aprova ADR-0005, não escolhe tecnologia, não cria contrato/API, não altera manifest/registry/G3/licença e não autoriza código. Nenhuma implementação CORE-03 pode começar antes das ratificações e do gate próprio.
