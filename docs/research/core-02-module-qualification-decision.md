# CORE-02 — Pacote de decisão para qualificação de módulo

**Status:** `DECISION_PACKAGE / NO DECISION RATIFIED / MODULE NOT_QUALIFIED`. **Base:** `cd2e6f77a4ede2a47fc64229686c061d5e24ece1`. **Módulo:** CORE-02. **Issue:** #19. **Referências:** [ADR-0004](../adr/0004-core-02-memory-policy.md), [ADR-0102](../adr/0102-core-02-internal-sequence-closeout.md), [checkpoint](../11-checkpoint.md).

## 1. Estado comprovado

- `CORE-02-03..09` concluídos/auditados; `-10` encerrou a sequência interna como documentário.
- Última matriz nativa: **110/110** Linux e Linux ASan/UBSan; **109/109** Windows e macOS, no HEAD de `-09`.
- Implementado: `MemoryBlock` ownership, `SystemMemoryResource` baseline, `MonotonicArena`, `MemoryBudget`, `LeakTracker` explícito e `MemoryTelemetry` opt-in.
- Não qualificado: allocator comparison/selection, process-wide leak detection, telemetry export, SMF/reclaim, RSS/VRAM/fragmentação física, p95/RSS thresholds, ABI, licença e release.
- ADR-0004 `PROPOSED`; NLE-D009 `OPEN`; G3 global `NOT_CLEARED`; `engine_implemented=false`.

## 2. Q1 — Ratificação da ADR-0004

**Pergunta:** a ADR-0004 deve ser ratificada como política de memória do CORE-02?

| Opção | Conteúdo | Trade-offs | Risco |
|---|---|---|---|
| A (recomendada) | Ratificar **somente como direção de planejamento**: `std::pmr` explícito, baseline de sistema/fallback, arenas limitadas, SMF como pesquisa, sem selecionar allocator/threshold/release | Consolida a política já usada pelo código; não antecipa decisões materiais | Baixo, desde que o texto exclua implementação/release |
| B | Manter `PROPOSED` até benchmark físico | Nenhum risco de interpretação; mantém CORE-02 sem política canônica | Bloqueia indefinidamente a qualificação |
| C | Ratificar como política de implementação/release | Permitiria alegar decisão tecnológica sem evidência | Alto; rejeitada |

**Recomendação:** opção A, com texto que exclua explicitamente allocator, SMF, thresholds, G3, release e licença.

**Texto exato para ratificação:**
> RATIFICO a ADR-0004 exclusivamente como direção de planejamento da política de memória do CORE-02, preservando `std::pmr` explícito, baseline de sistema/fallback e arenas limitadas. Esta ratificação não seleciona allocator de terceiro, não aprova SMF, thresholds, G3, release class, NLE-D009 ou distribuição, e não autoriza código além das WOs já aprovadas.

## 3. Q2 — Estratégia de allocator

**Pergunta:** qual estratégia de allocator deve orientar a qualificação?

| Opção | Conteúdo | Vantagens | Riscos/custos |
|---|---|---|---|
| A | Somente baseline (`SystemMemoryResource`/`new/delete`/`std::pmr`) | Zero dependência nova; ABI/CRT simples; já implementado | Pode não atender metas futuras de tail latency; não cumpre sozinho “comparar allocators” |
| B (recomendada) | Baseline permanece default; autorizar **somente harness isolado** para mimalloc 3.x e rpmalloc | Comparação controlada sem override global; evidência antes de escolha | Exige versões/digests/licenças/advisories, hardware e metodologia |
| C | Selecionar mimalloc agora | Potencial performance | Sem benchmark/licença/ABI; rejeitada |
| D | Selecionar rpmalloc agora | Potencial performance | Sem benchmark/licença/ABI; rejeitada |
| E | Allocator proprietário/SMF agora | Controle | Pesquisa sem evidência; rejeitada |

**Evidência mínima para trial:** versões/digests e licenças fixados; benchmark em hardware Q4; ASan/UBSan/TSan quando suportado; UAF/double-free/cross-thread/OOM/over-alignment; p50/p95/p99/RSS; nenhum tipo de terceiro na API; sem override global.

**Recomendação:** opção B, com baseline como default e nenhum vencedor declarado antes de Q3/Q4.

**Texto exato para ratificação:**
> RATIFICO a estratégia de allocator do CORE-02: `SystemMemoryResource`/`std::pmr` permanece o default e fallback; autorizo somente um harness de benchmark isolado para mimalloc 3.x e rpmalloc, com versões, digests, licenças e advisories fixados, sem override global, sem ABI pública e sem integração de produção. Nenhum allocator de terceiro será selecionado como default antes de Q3/Q4 e de nova ratificação explícita.

## 4. Q3 — Thresholds quantitativos

**Pergunta:** quais números usar como PASS/FAIL?

| Opção | Conteúdo | Consequência |
|---|---|---|
| A (recomendada) | `REPORT_ONLY`: registrar p50/p95/p99, RSS, overhead e churn sem threshold | Evita inventar metas; permite qualificação metodológica |
| B | Thresholds provisórios agora | Exigiria números não calibrados; risco de falso PASS/FAIL |
| C | Sem medição | Não qualifica |

**Recomendação:** A até Q4 e ratificação numérica separada. Nenhum limite p95/RSS/fragmentação é aprovado por este pacote.

**Texto exato para ratificação:**
> RATIFICO que Q3 permanece `REPORT_ONLY`: nenhum threshold de p50/p95/p99, RSS, overhead, fragmentação ou alocação por frame será usado como PASS/FAIL até a matriz física Q4 e uma ratificação numérica separada. As medições serão registradas com metodologia, hardware e SHA.

## 5. Q4 — Matriz física

**Pergunta:** onde executar a qualificação de performance/memória?

| Opção | Conteúdo | Limite |
|---|---|---|
| A | Somente CI hospedado | Não é prova física; rejeitada para performance/memória |
| B (recomendada) | Windows 11 x64, Ubuntu 24.04 x64, macOS 15 arm64; perfis 2 vCPU/4 GiB e 4 vCPU/8 GiB, usando os pisos já ratificados G1-M04/M05 | Exige máquinas e recibos; não define hardware comercial |
| C | Uma única máquina | Não cobre matriz obrigatória |

**Recomendação:** B, reaproveitando os perfis G1-M04/M05 já ratificados, sem criar novos mínimos comerciais.

**Texto exato para ratificação:**
> RATIFICO a matriz física de qualificação CORE-02 em Windows 11 x64, Ubuntu 24.04 x64 e macOS 15 arm64, com perfis de 2 vCPU/4 GiB e 4 vCPU/8 GiB conforme G1-M04/M05. Máquinas, versões, drivers e recibos exatos serão registrados; CI hospedado não conta como prova física.

## 6. Q7 — Licença

**Pergunta:** escolher NLE-D009 agora?

| Opção | Conteúdo | Consequência |
|---|---|---|
| A (recomendada) | Manter `OPEN`; qualificação interna sem distribuição | Permite avançar internamente sem decisão de licença |
| B | Escolher licença agora | Exige decisão jurídica/owner; fora do escopo técnico |

**Recomendação:** A. Nenhuma licença é escolhida por este pacote.

**Texto exato para ratificação:**
> Mantenho NLE-D009 `OPEN`; nenhuma licença de código é escolhida por este incremento. Qualificação interna não autoriza distribuição, publicação ou release; esses atos permanecem bloqueados até decisão específica.

## 7. Bloco consolidado de ratificação

Copie e responda explicitamente os itens desejados:

```text
Q1 = A (ADR-0004 apenas como direção de planejamento)
Q2 = B (baseline default + harness isolado mimalloc/rpmalloc, sem seleção)
Q3 = A (REPORT_ONLY, sem thresholds até Q4 + ratificação numérica)
Q4 = B (matriz física G1-M04/M05: Win11 x64, Ubuntu 24.04 x64, macOS 15 arm64)
Q7 = A (NLE-D009 permanece OPEN; sem release)
```

Qualquer item não ratificado mantém o gate correspondente bloqueado.

## 8. Consequência da ratificação

Com Q1/Q2/Q3/Q4/Q7 ratificados, o próximo incremento NECESSARY seria uma **WO de benchmark/qualificação CORE-02**, test-only e isolada, com harness de allocators, metodologia, hardware e evidências — sem integrar terceiro ao default e sem release. Sem essa ratificação, nenhum código novo é autorizado.

## 9. Limites

Este pacote não aprova ADR-0004, não escolhe allocator, não fixa thresholds, não declara leak-free, não altera G3, NLE-D009, registry, release class ou checkpoint. Nenhum código é produzido ou autorizado por este texto.
