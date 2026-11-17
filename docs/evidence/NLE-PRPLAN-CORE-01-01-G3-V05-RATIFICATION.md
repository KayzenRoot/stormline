# NLE-PRPLAN-CORE-01-01 — G3-V05 ratificacao de fatia interna CORE-01

**Status: PROPOSED DOCUMENTARY EVIDENCE / NAO E APROVACAO G3 OU ATIVACAO DE CODIGO.** 2026-11-17.
**Base:** `dfd3451cdf4cc3793c484656e5a4405e39a985eb` (main, docs Source Check); **WO** `NLE-PRPLAN-CORE-01-01`; **issues:** [#387](https://github.com/KayzenRoot/stormline/issues/387), [#18](https://github.com/KayzenRoot/stormline/issues/18).

## Origem e autoridade
O proprietario RATIFICOU EXPRESSAMENTE na conversa: Opcao A apenas para CORE-01; C++20 interno, primeira fatia CPU-only headless sem SDL3, `MANDATORY_1_0` apenas como objetivo de produto, codigo inicial `INTERNAL_ONLY`, risco `STANDARD` para essa fatia, contratos tipados/RAII/rollback e CI provisoria com as toolchains observadas sem substituir os candidatos G3-V01. Autorizou PRs canônicas sequenciais e auditoria; NAO considerou G3 global CLEARED, NAO aprovou ADR-0003/0075 integralmente, NAO escolheu NLE-D009 e NAO liberou os 80 WOs. [Comentario #6954081280](https://github.com/KayzenRoot/stormline/issues/387#issuecomment-6954081280) era a PROPOSTA, nao o voto; esta evidencia registra a ratificacao explicitamente comunicada ao assistente.

## Observacoes tecnicas existentes, nao reexecutadas neste incremento
- [PR #421](https://github.com/KayzenRoot/stormline/pull/421) permanece Draft, HEAD `0d27dc7cfe5c0adcb0c4e1800c929666d3b5deb0`, apenas fixture C++20 sem engine.
- [CI nativa #44124073355](https://github.com/KayzenRoot/stormline/actions/runs/44124073355): 3/3 jobs completed/success e 1/1 CTest por OS na PR, Ubuntu 24.04 GCC13.3, Windows MSVC 19.51/14.51, macOS AppleClang17; source edition standard C++20. [Docs #44124073329](https://github.com/KayzenRoot/stormline/actions/runs/44124073329) SUCCESS.
- Nao ha prova do SDK Windows .9457 completo, dos MSVC14.50/14.52, GCC16.2/Clang23.1.5 ou da integracao do host real; nao inferir G3-P full PASS.

## Scope/diff do incremento documental
Somente adendos append-only a Ledger, Scope, DoD, ADR-0003 (mantido PROPOSED), gates CORE-01 e este unico arquivo de evidencia. Nenhum arquivo de codigo, registry, manifest, workflow, config GitHub, checkpoint ou outra ADR deve mudar. Novo checkpoint apenas delta PROPOSED apos auditoria/merge, nao nesta PR.

## Risco, legal, custos e limites
O owner ratificou STANDARD somente para futura primeira fatia interna, sem autorizar distribuicao nem decidir NLE-D009; nao instalar nova toolchain/biblioteca, nao pagar, nao introduzir secrets/privilegios; CI de producao segue por validar no WO -02. G2 ruleset 27393227 preservado.

## Evidencia/aceite e auditoria
Antes de aceitar esta PR, exigir: diff exato de seis docs, SHA base/head, docs-validation no head, consistencia canônica, traceabilidade da declaracao do owner, verificacao de links/registry/manifest e revisao objetiva pt-BR. Veredito `APPROVED DOCUMENTARY ONLY`, `CORRECTION REQUIRED` ou `BLOCKED`. Auditoria no mesmo contexto nao deve alegar independencia humana/tecnica de outro revisor.

## Checkpoint Delta PROPOSED, nao aplicado
Registrar somente ratificacao limitada de 2026-11-17 e limites, PR/CI/SHA apos recibos reais; sem alterar G3 global, ADR-0003/0075, NLE-D009, G2, registry/manifest, CORE-01-02/-03 e 80 WOs. Requer PR documental separada se necessario.
