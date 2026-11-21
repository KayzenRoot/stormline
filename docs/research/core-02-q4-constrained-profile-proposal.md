# CORE-02 Q4 — Proposta de metodologia de perfis limitados

**Status:** `PROPOSAL_ONLY / NOT RATIFIED / NO NEW CAMPAIGN`. **Base:** `6cd88cebf3e2e1c1c7b169b139889da433ceb83f`. **WO:** [NLE-CORE02-ALLOC-Q4-001](../work-orders/NLE-CORE02-ALLOC-Q4-001.md). **Issue:** #19.

## 1. Estado atual

- Full Q4 BLOCKED: sem hosts físicos Ubuntu 24.04 x64/macOS 15 arm64; sem máquinas exatas 2 vCPU/4 GiB e 4 vCPU/8 GiB; Windows host é `PHYSICAL_INFERRED_NOT_CERTIFIED`.
- Helper CD-01 é fail-closed; afinidade é `post_start_readback` e medições são aproximações.
- Nenhum allocator selecionado; CORE-02 NOT_QUALIFIED.

## 2. Opções

| Opção | Conteúdo | Limite |
|---|---|---|
| A (preferida) | Fornecer máquinas físicas exatas por OS/perfil | Requer acesso a hardware adicional |
| B | Perfil constrangido em host físico maior: CPU affinity comprovada e hard memory cap; rótulo `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` | Não satisfaz igualdade de hardware; exige ratificação expressa |
| C | Manter Q4 BLOCKED | Sem novos dados |

## 3. Requisitos mínimos da opção B

1. Host físico comprovável (não VM/CI), com CPU/RAM/SO/SMBIOS e recibos.
2. CPU affinity aplicada **antes** do início do workload (processo suspenso + `SetProcessAffinityMask` + resume) ou, se isso não for viável, medições explicitamente aproximadas e não elegíveis como perfil exato.
3. Hard memory cap via Job Object (`ProcessMemoryLimit`) para 4 GiB/8 GiB, com verificação de que o limite foi aplicado.
4. 3 execuções por perfil, exit 0, markers e contagem de resultados validados pelo helper fail-closed.
5. Windows 11 x64: host disponível; Ubuntu/macOS continuam BLOCKED sem hosts físicos.
6. Nenhum resultado de CI hospedado é aceito como prova física.
7. Nenhum allocator selecionado/threshold; apenas comparação report-only.

## 4. Texto exato de ratificação (opção B)

> RATIFICO a metodologia de perfis limitados `CONSTRAINED_PROFILE_NOT_EXACT_HARDWARE` para a campanha Q4 em host físico disponível, exigindo CPU affinity comprovada antes do workload, hard memory cap de 4 GiB ou 8 GiB via Job Object, três execuções por perfil, validação fail-closed e rotulagem explícita de que o hardware não é uma máquina física exata de 2 vCPU/4 GiB ou 4 vCPU/8 GiB. Esta ratificação não qualifica CORE-02, não seleciona allocator e não substitui os hosts Ubuntu 24.04 x64 e macOS 15 arm64 exigidos.

## 5. Próximo passo

- Se B for ratificada: nova WO/PR para implementar o launcher com processo suspenso, Job Object e verificação de limite; depois executar a campanha apenas no host Windows disponível e manter Ubuntu/macOS BLOCKED.
- Se A: aguardar fornecimento dos hosts exatos e repetir o helper fail-closed.
- Se C: nenhuma ação.
- Em qualquer caso, thresholds numéricos e seleção de allocator exigem ratificação posterior; CORE-02 continua NOT_QUALIFIED e CORE-03 bloqueado.
