# CORE-03 — Proposta de admissão limitada (não ratificada)

**Status:** `PROPOSAL_ONLY / NO CODE AUTHORIZED / CORE-02 NOT_QUALIFIED`. **Base:** `6cd88cebf3e2e1c1c7b169b139889da433ceb83f`. **Módulo:** CORE-03. **Issue:** #20. **Referências:** [ADR-0005](../adr/0005-core-03-jobs-concurrency.md), [ADR-0086](../adr/0086-capability-based-l1-dependency.md), [ADR-0103](../adr/0103-core-03-governance-gate.md), [decisão CORE-03](core-03-adr-0005-decision.md).

## 1. Estado

- `CORE-03-01` é `APPROVED_GOVERNANCE` somente como planejamento.
- `CORE-03-02`..`-10` permanecem `PLANNED_BLOCKED`; nenhum código/teste de concorrência existe.
- CORE-02 está internamente fechado (`-03`..`-10`) mas **NOT_QUALIFIED**; a dependência formal CORE-02 não está satisfeita.
- Q4 físico do CORE-02 continua BLOCKED; NLE-D009 OPEN; G3 NOT_CLEARED.

## 2. Decisões pendentes A/B/C/D

| ID | Proposta | Ratificação necessária |
|---|---|---|
| A | ADR-0005 apenas como direção de planejamento, sem implementação/release | texto abaixo |
| B | risco LOW para documentos, ELEVATED para implementação concorrente, release INTERNAL_ONLY | texto abaixo |
| C | benchmark baseline jthread/pool + Taskflow 4.x + enkiTS; oneTBB condicional; SFAS não iniciado | texto abaixo |
| D1 | manter todo código CORE-03 bloqueado até CORE-02 module qualification | texto abaixo |
| D2 | admissão limitada por capacidades CORE-02-03..09, sem declarar CORE-02 completo, apenas para preparar/implementar fatia interna | texto abaixo |

## 3. Textos exatos de ratificação

**A:**
> RATIFICO a ADR-0005 exclusivamente como direção de planejamento do CORE-03 para contrato e benchmark de candidatos, sem selecionar Taskflow, enkiTS, oneTBB, SFAS ou qualquer tecnologia, sem aprovar API, dependência, release, thresholds ou código.

**B:**
> RATIFICO `LOW` para os artefatos documentais CORE-03, `ELEVATED` para a implementação futura de concorrência e `INTERNAL_ONLY` como release class proposta para as primeiras fatias internas; nenhuma release pública é autorizada.

**C:**
> RATIFICO um programa de benchmark isolado para CORE-03 com baseline C++20 `std::jthread`/pool fixo, Taskflow 4.x e enkiTS, mantendo oneTBB como comparador condicional e SFAS como pesquisa não iniciada; nenhum candidato será integrado ao default, à API pública ou ao produto antes de benchmark, licenças/advisories e nova ratificação.

**D1:**
> Mantenho todo o código CORE-03 bloqueado até que CORE-02 satisfaça seus critérios de módulo e haja autorização específica para o gate de implementação.

**D2:**
> RATIFICO uma admissão por capacidade para a primeira fatia interna CORE-03 baseada nos pacotes concluídos CORE-02-03..09, sem declarar CORE-02 módulo completo e sem promover G3, release ou licença. A dependência formal CORE-02 permanece registrada e o closeout CORE-03 exigirá sua qualificação ou nova decisão.

Escolher **D1 ou D2**, não ambos.

## 4. Próximo passo conforme a decisão

- **D1:** nenhum contrato/código CORE-03; aguardar qualificação CORE-02.
- **D2 + A/B/C:** preparar somente o contrato `CORE-03-02` (documental, sem código), com:
  - `TaskId`, `JobRequest`, `JobHandle`, `TaskGraph`, `JobFence`, `CancellationScope`, `WorkBudget`, `ExecutorStats`;
  - erros tipados (`CANCELLED`, `DEPENDENCY_FAILED`, `RESOURCE_EXHAUSTED`, `DEADLINE_MISSED`, `CYCLE_FOUND`, `AFFINITY_VIOLATION`, `DEADLOCK_RISK`, `WORKER_SHUTDOWN`);
  - ownership CORE-01/02/04/06/GFX/AUD, determinismo de commit, backpressure, cancelamento e shutdown;
  - allowlist, testes negativos, TSan/ASan/UBSan e benchmark report-only;
  - nenhum código antes do gate G6 de `CORE-03-03`.
- Implementação real de scheduler continua exigindo autorização posterior, contrato auditado, tecnologia/benchmark e gate próprio.

## 5. Limites

Esta proposta não aprova ADR-0005, não escolhe tecnologia, não cria contrato/API ativo, não altera manifest/registry/G3/licença e não autoriza código. Nenhum packet CORE-03 fica `EXECUTOR_READY` por este documento.
