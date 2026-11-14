# Source Hierarchy / Hierarquia canônica
Status: BASELINE PROPOSED | Work Order: NLE-P00-WO-001 | 2026-11-14

## Precedência obrigatória
1. Checkpoint aprovado, se houver.
2. Decisions Ledger e ADRs aprovados.
3. Scope.
4. Definition of Done.
5. Architecture.
6. Requirements.
7. Demais especificações, runbooks, backlog e textos.
8. Conversas e sugestões não versionadas, somente como contexto.

Código, Git, diffs, testes e evidência observável prevalecem sobre declarações narrativas de conclusão. Documentos não podem registrar como implementado o que não foi comprovado.

## Estados
- APPROVED: decisão ou incremento aceito com evidência verificável.
- PROPOSED: candidato sujeito a validação.
- BLOCKED: pré-requisito essencial ou risco impeditivo.
- CORRECTION REQUIRED: defeitos corrigíveis na mesma WO e PR.
- STALE: contexto/fingerprints invalidados por alteração em checkpoint, Scope, DoD, Architecture ou decisão relevante.
- NOT STARTED / NOT IMPLEMENTED: ausência de implementação verificada.

Uma decisão aprovada exige registro no Ledger/ADR; alterações passam por novo ADR e aceite do proprietário. Este Source Pack inicial é a **proposta documental em PR** até auditoria e merge; não se autodeclara aprovado.

## Alteração documental
Cada PR identifica fontes afetadas, risco, versão, compatibilidade, justificativa, evidências e Checkpoint Delta proposto. Primeiro auditar; somente após APPROVED atualizar formalmente fontes canônicas afetadas. Evitar docs contraditórias.

## Controle de contexto
Registrar base SHA, HEAD SHA e fingerprints SHA-256 dos arquivos críticos quando houver executor com acesso a Git. Ao detectar STALE, interromper writes e reconstruir o Context Lock.
