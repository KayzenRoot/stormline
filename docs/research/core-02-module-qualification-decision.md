# CORE-02 — Dossier de decisão para qualificação de módulo

**Status:** `DECISION_DOSSIER / NO DECISION RATIFIED / MODULE NOT_QUALIFIED`. **Base:** `8db294b0292660ce684341209a33b9c2c1d34000`. **Módulo:** CORE-02. **Issue:** #19. **Referências:** [ADR-0004](../adr/0004-core-02-memory-policy.md), [ADR-0102](../adr/0102-core-02-internal-sequence-closeout.md), [checkpoint](../11-checkpoint.md).

## 1. Estado atual comprovado

- `CORE-02-03..09` concluídos e auditados; `-10` encerrou a sequência interna como documentário.
- Última matriz nativa: **110/110** Linux e Linux ASan/UBSan, **109/109** Windows e macOS, no HEAD de `-09`.
- Implementado: `MemoryBlock`, `SystemMemoryResource` (baseline new/delete), `MonotonicArena`, `MemoryBudget`, `LeakTracker` explícito e `MemoryTelemetry` opt-in.
- Não implementado/qualificado: allocator comparison/selection, process-wide leak detection, telemetry export, SMF/reclaim, physical RSS/VRAM/fragmentation metrics, p95/RSS thresholds, ABI, license, release.
- ADR-0004 continua `PROPOSED`; NLE-D009 `OPEN`; G3 global `NOT_CLEARED`; `engine_implemented=false`.

## 2. Decisões materiais necessárias (nenhuma pré-ratificada)

| ID | Decisão | Opções mínimas | Evidência necessária antes de ratificar | Consequência se não decidida |
|---|---|---|---|---|
| Q1 | Ratificar ADR-0004 como política de memória | (a) aprovar como direção de planejamento; (b) manter PROPOSED | auditoria do texto e confirmação de que não seleciona allocator/release | CORE-02 permanece sem política canônica |
| Q2 | Estratégia de allocator | (a) manter somente baseline `std::pmr`/new-delete; (b) trial mimalloc 3.x + rpmalloc; (c) outro | versões/digests/licenças, benchmark em hardware aprovado, ASan/UBSan, cross-thread frees, OOM, ABI de plugin | nenhuma comparação/vencedor pode ser declarado |
| Q3 | Thresholds quantitativos | definir p50/p95/p99, RSS, overhead, fragmentation e low-RAM tiers | metodologia, hardware, amostras, noise, baseline | nenhum PASS de performance ou budget físico |
| Q4 | Matriz física | Windows 11 25H2 x64, Ubuntu 24.04 x64, macOS 15 arm64; opcionais Intel/Windows ARM64 | máquinas aprovadas, versões, drivers, recibos | G3 physical e qualificação de módulo bloqueados |
| Q5 | Leak/telemetria de escopo | (a) manter explícito/opt-in; (b) autorizar interceptação/export | desenho de segurança, overhead, privacidade, testes | process-wide leak / export permanecem NOT_QUALIFIED |
| Q6 | Revisão de segurança | (a) auditoria independente; (b) segundo mecanismo determinístico aprovado | escopo, evidência, ausência de HIGH/CRITICAL | release/qualificação de segurança bloqueados |
| Q7 | Licença do código | decidir NLE-D009 | decisão explícita do proprietário; compatibilidade de terceiros | release/distribuição bloqueados |
| Q8 | Release class / aceitação do módulo | `INTERNAL_ONLY` ou classe superior | DoD, gates, evidência física/segurança | módulo não pode ser declarado completo |

## 3. Protocolo mínimo proposto para Q2/Q3 (não executado)

1. Definir workloads reproduzíveis: blocos de tamanhos variados, arena slices, budgets, leak tokens, alocação concorrente e carga de streaming/asset simulada.
2. Medir baseline `SystemMemoryResource`, `std::pmr` default, `new/delete`, `malloc/free` e candidatos aprovados com versões/digests fixados.
3. Registrar p50/p95/p99, RSS, pico, retenção, fragmentação estimada (quando houver estimador definido), overhead de telemetria e falhas OOM.
4. Executar sanitizers disponíveis, cross-thread free, double-free, UAF, over-alignment, capacity/overflow e recuperação.
5. Repetir em hardware aprovado por SO; CI hospedado não é prova de performance física.
6. Auditar licenças, notices e advisories antes de qualquer venda/embutimento.
7. Não declarar vencedor sem comparação estatística e sem decisão explícita do proprietário.

## 4. Sequência recomendada

1. Proprietário ratifica ou rejeita Q1 (ADR-0004) e Q2 (estratégia de allocator).
2. Se Q2 = trial, autorizar WO de benchmark/qualificação com candidatos e licenças pinadas.
3. Definir Q3/Q4 com hardware e thresholds explícitos; executar a campanha.
4. Resolver Q5/Q6/Q7; somente então Q8 e eventual declaração de módulo.
5. CORE-03 permanece bloqueado até Q1/Q2/Q8 e dependência formal estarem satisfeitos.

## 5. Limites deste documento

Este dossier **não** aprova ADR-0004, não escolhe allocator, não fixa thresholds, não declara leak-free, não altera G3, NLE-D009, registry, release class ou checkpoint. Nenhum código é produzido ou autorizado por este texto. A decisão continua exclusiva do proprietário.
