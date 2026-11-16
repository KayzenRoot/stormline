# Evidence Bundle — G2 main enforcement applied and probed

**DATA:** 2026-11-16 · **STATUS:** `ENFORCEMENT_APPLIED / G2-P01..P04,P06..P08,P10,P11 OBSERVED / P05-POSITIVE E P09-STRICT PENDING / G2_NOT_YET_PROMOTED` · **WORK ORDER ESTÁVEL:** [NLE-PRPLAN-CORE-01-01](../work-orders/NLE-PRPLAN-CORE-01-01.md) · [issue #387](https://github.com/KayzenRoot/stormline/issues/387) **OPEN** · [plano G2](../research/core-01-01-g2-branch-enforcement-qualification.md) · [matriz de gates](../engineering/core-01-01-qualification-gates.md).

Este é o primeiro incremento **privilegiado** do G2. Diferente do [Evidence de qualificação](NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-QUALIFICATION.md) (somente proposta), aqui há **uma alteração administrativa real**: um único ruleset de repositório ativo sobre `refs/heads/main`. Nenhuma configuração global de merge, workflow, código, ADR, registry, manifest ou licença foi alterada. A promoção documental de `G2 CLEARED` é reservada ao checkpoint independente, após observação do merge positivo e da prova strict.

## 1. Autoridade e Source Check

- **Autorização:** o proprietário autorizou expressamente, nesta execução de 2026-11-16, a aplicação controlada das proteções G2, condicionada a Source Check, acesso administrativo efetivo, snapshot, rollback e validações. Essa autorização é **separada** da ratificação conceitual `C01-D12` e não foi inferida de documento algum.
- **Source Check:** `git fetch`, branch local `main`, HEAD local e remoto = `0ef8eb69baac03b805f11af6c29a053185128b6f`; HEAD esperado idêntico. **Contexto não STALE.**
- **Hierarquia consultada:** checkpoint > Decisions Ledger/ADRs aprovados > Scope > DoD > Architecture > Requirements > gates G2/segurança/WO. ADR-0003 e ADR-0075 permanecem `PROPOSED`; `NLE-D009` permanece `OPEN`.
- **Conta:** `KayzenRoot` é conta de usuário (`type=User`), portanto não há camada de rulesets de organização; `GET /orgs/KayzenRoot/rulesets` retorna 404 esperado e não aplicável.

### Fingerprints SHA-256 das fontes críticas (arquivo físico, não blob Git)

| Fonte | SHA-256 |
|---|---|
| `docs/11-checkpoint.md` | `f7d9b9fbfd6adadd5547efd66dffea947957f4d6b2e9ccb9132bb1cd1fc23c72` |
| `docs/10-decisions-ledger.md` | `8923d29d13622613037a4e6de7afa69f796b97bda65123b1739c4e9aa4a50b71` |
| `docs/03-scope.md` | `b8aaa5786252450ce27f59ee27958886c680f79edb262fb3e17ff7e66704976f` |
| `docs/09-definition-of-done.md` | `b1a9335f01906a817a8e9d908aac3bda7c69f63b34843b282357574532201eee` |
| `docs/04-architecture.md` | `be7f687c7f6db2154536c92426f9c4fd469bb92c3f4896476831437bdaad5930` |
| `docs/02-requirements.md` | `6e19ad35c7e08f54756eff6372a57def673fd6da9166d91da29770196db3fed0` |
| `docs/engineering/core-01-01-qualification-gates.md` | `2fb3c5089fc2549b3b832e2e4814fbad96d16adffc8a5791e8417ecaf08d1496` |
| `docs/research/core-01-01-g2-branch-enforcement-qualification.md` | `aab738b5b037be92b743063e99d87906d5011a33392e2930a3220279e2db2282` |
| `docs/evidence/NLE-PRPLAN-CORE-01-01-G2-ENFORCEMENT-QUALIFICATION.md` | `e5fc1f4b6fe6d84a40ad19285c49f09b77614a9bae4f3d9ba9c50e8bb74eb81d` |
| `docs/work-orders/NLE-PRPLAN-CORE-01-01.md` | `67b074d013540f1c74b64506db5ab27fc73f565a46b4e0dc82d5f5c4a08041b0` |
| `.github/workflows/docs.yml` | `f0c2d8674e150bf2533d26249ff3ca9e57825da55b77846c67e0ec26ef2877a9` |
| `docs/queue/implementation-registry.json` | `c924399f957b5bae500a93893bb286d1d543433462296a62ef9e466820593ef6` |
| `docs/pr-plans/manifest.json` | `923e0cf0c5a414c75c16567646ec812b29cddf06c7dae83e515cacdc4927dd3f` |

## 2. Preflight administrativo

| Verificação | Resultado observado | Interpretação |
|---|---|---|
| `gh auth status` | conta `KayzenRoot`, token OAuth com escopos `gist`, `read:org`, `repo` | Sessão utilizável; nenhum token exibido |
| `GET /repos/KayzenRoot/stormline` | `permissions.admin=true`, `visibility=public`, `default_branch=main` | **ADMIN efetivo**; sem 403 |
| `GET /branches/main` (antes) | `protected=false`, SHA `0ef8eb6…` | Sem enforcement comprovado antes da mudança |
| `GET /rulesets` (antes) | `[]` | Zero rulesets de repositório |
| `GET /rules/branches/main` (antes) | `[]` | Zero regras efetivas |
| `GET /branches/main/protection` (antes) | HTTP **404** `Branch not protected` | Ausência de proteção clássica, **não** falta de permissão; o mesmo token é admin |
| Rulesets de organização | 404 (`KayzenRoot` é User) | Camada inexistente |

### Snapshot imutável capturado antes da escrita

| Artefato | SHA-256 |
|---|---|
| `snapshot-repo.json` | `d63d4497afa3fa8c2c80cf45743142f3a9fc9f9511b79e5e95ca57a64aaeaf22` |
| `snapshot-branch-main.json` | `8e5eed74e7e06d46e127881bff847e0196fe8ed5dfa26ddd356db0deee855671` |
| `snapshot-rulesets.json` (`[]`) | `4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945` |
| `snapshot-effective-rules.json` (`[]`) | `4f53cda18c2baa0c0354bb5f9a3ecbe5ed12ab4d8e11ba873c2f11161202b945` |
| `snapshot-workflows.json` | `03a8f8e29c36acc8decdb8252218115b71cfad85a38ec1097b6e8fb746091540` |
| `snapshot-classic-protection.json` | `422e613103f4d644a295e372749b8800ca872e8349658d0194be6fb0a0a4b29c` |

O estado anterior era inequívoco e restaurável: **nenhum** ruleset, **nenhuma** regra efetiva, **nenhuma** proteção clássica, `main.protected=false`. Alterações globais de merge não foram tocadas.

## 3. Configuração aplicada

**Payload** (`sha256=349f4b7d245a4c6247bd3d9d70119bf4fae2a38243fef48f4bf064c4cb19a2b5`), criado por `POST /repos/KayzenRoot/stormline/rulesets`:

```json
{
  "name": "g2-main-enforcement",
  "target": "branch",
  "enforcement": "active",
  "conditions": {"ref_name": {"include": ["refs/heads/main"], "exclude": []}},
  "rules": [
    {"type": "pull_request", "parameters": {
      "required_approving_review_count": 0,
      "dismiss_stale_reviews_on_push": false,
      "require_code_owner_review": false,
      "require_last_push_approval": false,
      "required_review_thread_resolution": false,
      "allowed_merge_methods": ["squash"]
    }},
    {"type": "required_status_checks", "parameters": {
      "strict_required_status_checks_policy": true,
      "do_not_enforce_on_create": false,
      "required_status_checks": [{"context": "docs-validation", "integration_id": 15368}]
    }},
    {"type": "required_linear_history"},
    {"type": "non_fast_forward"},
    {"type": "deletion"}
  ],
  "bypass_actors": []
}
```

**Resposta real (corpo capturado):** criação aceita, `id=27393227`, `node_id=RRS_lACqUmVwb3NpdG9yec5W4cXHzgGh_Ms`, `created_at=2026-11-16T14:36:12.180-03:00`, `enforcement=active`, `bypass_actors=[]`, **`current_user_can_bypass="never"`**. Resposta `sha256=587c99fc81ed850ceea7856f74134a86363dd92f6b1fa05faa9cc7e195bdd5be`.

O API injetou `require_extra_approval_for_unattributed_changes: true` (default do GitHub). A documentação oficial afirma que esse campo **não tem efeito quando `required_approving_review_count=0`**; portanto a política autorizada de zero aprovações permanece íntegra. Nenhum bypass foi criado.

## 4. Readback integral

- `GET /rulesets/27393227` → `sha256=587c99fc81ed850ceea7856f74134a86363dd92f6b1fa05faa9cc7e195bdd5be` (byte-idêntico à resposta de criação), `enforcement=active`, include exato `refs/heads/main`, cinco regras, `bypass_actors=[]`, `current_user_can_bypass="never"`.
- `GET /rulesets` → exatamente **um** ruleset: `{id:27393227, name:g2-main-enforcement, enforcement:active, target:branch}`.
- `GET /rules/branches/main` → `sha256=aeb4a7a3c2b2d42827f1ecf0d67c08b0ec640baef0b7c197246ec62d21917cdf`; lista as cinco regras com `ruleset_id=27393227`.
- `GET /branches/main` → `protected=true`, SHA `0ef8eb69baac03b805f11af6c29a053185128b6f`.
- Configurações globais de merge permanecem `allow_squash_merge=true`, `allow_merge_commit=true`, `allow_rebase_merge=true`; a restrição a squash existe **apenas** no ruleset da `main`.
- `DELETE`/`PATCH` não foram executados.

## 5. Required check real

| Item | Evidência |
|---|---|
| Contexto exato | `docs-validation` (nome do **job**, não o workflow `Docs Validation`) |
| Provedor | `app.id=15368`, `app.slug=github-actions` (GitHub Actions), derivado de Check Runs reais |
| Unicidade | Único workflow no repositório (`GET /actions/workflows` → 1); único Check Run `docs-validation` por commit/PR observado |
| Evento | workflow dispara em `pull_request` e `push: main`; sem filtros `paths`, sem `if` de job, sem `pull_request_target` |
| Isolamento | `permissions: contents: read`, `persist-credentials: false`, default do repositório `read`, `can_approve_pull_request_reviews=false`, nenhum segredo referenciado |
| Execução real | [PR #404](https://github.com/KayzenRoot/stormline/pull/404), head `391e5036…`, [run 43920602387](https://github.com/KayzenRoot/stormline/actions/runs/43920602387), job `133486539980`: **success**, steps 1–10 (setup, checkout e 8 validações) e post/complete todos `success`, nenhum `skipped` |
| Runner | `ubuntu-latest`, grupo `GitHub Actions`, runner hospedado padrão |

## 6. Matriz de provas G2-P01..P12

| Prova | Resultado | Evidência objetiva |
|---|---|---|
| G2-P01 Source Lock e diff autorizado | **PASS** | HEAD exato, fingerprints, payload hash, snapshot prévio, um único ruleset |
| G2-P02 Alvo exclusivo e readback | **PASS** | `refs/heads/main` only; `protected=true`; readback admin |
| G2-P03 PR obrigatória, zero revisores | **PASS** | `required_approving_review_count=0`, `require_code_owner_review=false`, `require_last_push_approval=false`, `required_reviewers=[]` |
| G2-P04 Check exato, único, produzido e strict | **PASS** | `docs-validation`/app 15368, sem filtros, job completo, `strict=true`, `integration_id` vinculado |
| G2-P05 Check falho/ausente bloqueia; verde permite | **PASS NEGATIVO / POSITIVO PENDENTE** | PRs #402 e #403 bloqueadas (mensagens abaixo); merge verde desta PR será o positivo, registrado no checkpoint |
| G2-P06 Push direto sem PR negado | **PASS (config proof)** | Regra `pull_request` efetiva + `current_user_can_bypass=never`; admin também foi negado no merge; **nenhum push real na main tentado**; `git push --dry-run` foi descartado como prova (não avalia regras do servidor) |
| G2-P07 Force-push e deleção proibidos | **PASS (readback)** | Regras `non_fast_forward` e `deletion` efetivas no ruleset 27393227; **nenhuma operação destrutiva tentada** |
| G2-P08 Sem bypass | **PASS** | `bypass_actors=[]`, `current_user_can_bypass=never`; tentativas de merge do próprio admin negadas pelas regras |
| G2-P09 Squash funcional e base stale exige nova qualificação | **PARCIAL** | `allowed_merge_methods=["squash"]` + `strict=true` no readback; squash e stale serão observados após esta PR e registrados no checkpoint |
| G2-P10 Segurança de forks | **PASS (policy)** | `pull_request` (não `pull_request_target`), token `contents: read`, `persist-credentials:false`, zero segredos, default read; nenhum fork externo foi executado neste incremento |
| G2-P11 Runners padrão gratuitos R$0 | **PASS** | Repositório público, `ubuntu-latest`, `GET /actions/runners` = `0` self-hosted, nenhum larger runner/pago habilitado |
| G2-P12 Readback/rollback + auditoria + checkpoint | **PENDENTE** | Rollback documentado abaixo; auditoria pt-BR e checkpoint independente serão as últimas etapas |

## 7. Testes negativos reais (branches/PRs descartáveis, nunca mergeadas)

Todas as PRs de prova são temporárias, não produtivas e foram criadas após a ativação do ruleset.

| PR | Cenário | Check | Resultado do merge | Evidência |
|---|---|---|---|---|
| [#402](https://github.com/KayzenRoot/stormline/pull/402) | link local quebrado de propósito | `docs-validation` **FAILURE** ([run 43920519668](https://github.com/KayzenRoot/stormline/actions/runs/43920519668), job 133486243035) | HTTP **405**, `mergeStateStatus=BLOCKED` | `Repository rule violations found / Required status check "docs-validation" is failing.` |
| [#403](https://github.com/KayzenRoot/stormline/pull/403) | commit com `[skip ci]`, check nunca emitido | **ausente** (0 runs; nenhum Check Run `docs-validation`) | HTTP **405**, `mergeStateStatus=BLOCKED` | `Repository rule violations found / Required status check "docs-validation" is expected.` |
| [#404](https://github.com/KayzenRoot/stormline/pull/404) | documento válido, CI verde | `docs-validation` **SUCCESS** ([run 43920602387](https://github.com/KayzenRoot/stormline/actions/runs/43920602387)) | `mergeStateStatus=CLEAN` (não mergeada) | Será usada para provar que base desatualizada bloqueia após a main avançar |

As mensagens acima são a resposta literal do GitHub API, não interpretação. A PR #403 comprova o caso de check **ausente**; a #402, o caso de check **falho**. Nenhuma delas foi mergeada; serão fechadas e as branches removidas após a coleta final.

## 8. Bypass, apps e efeitos sobre automação

- `bypass_actors=[]` e `current_user_can_bypass="never"`: o próprio proprietário/admin não contorna o ruleset.
- Observados Check Runs de terceiros já instalados: SonarCloud (`app_id=12526`) e Socket Security (`app_id=156372`). Eles **não** estão na lista de bypass e não foram modificados; continuam apenas reportando checks informativos.
- O listing de check suites revelou **16 suites**, sendo 14 vazias/queued de integrações de conta e 2 concluídas (SonarCloud e Socket). Nenhum app recebeu bypass; qualquer merge futuro continua sujeito às mesmas cinco regras.
- A automação Codex usa a credencial do proprietário; não há bypass específico. Merge só é permitido com a PR exigida e `docs-validation` verde no commit atualizado.
- Efeito prático: pushes diretos e merges que não sejam squash deixam de ser aceitos na `main`; PRs precisam ser atualizadas após mudança da base. O fluxo documental existente já usa PR + squash, portanto não há quebra de processo.

## 9. Custo e segurança

- Repositório **público**; runners `ubuntu-latest` padrão do GitHub Actions são gratuitos para repositórios públicos segundo a documentação oficial. Nenhum larger runner, runner self-hosted, serviço pago, segredo ou deployment foi habilitado.
- Nenhuma alteração em `.github/workflows/docs.yml` ou em qualquer workflow.
- Nenhuma dependência, runtime C++, SDL3, CMake, Ninja ou contrato técnico foi modificado.

## 10. Rollback exato

Estado anterior comprovado: zero rulesets, zero regras efetivas, sem proteção clássica, `main.protected=false`. Para reverter integralmente:

```bash
gh api --method DELETE repos/KayzenRoot/stormline/rulesets/27393227
gh api repos/KayzenRoot/stormline/rulesets                     # esperado: []
gh api repos/KayzenRoot/stormline/rules/branches/main          # esperado: []
gh api repos/KayzenRoot/stormline/branches/main --jq .protected # esperado: false
```

Como nenhuma configuração global foi alterada, o rollback se limita à remoção do ruleset 27393227. Alternativa menos destrutiva: `PATCH` com `enforcement=disabled` (não usada). O rollback deve ser executado apenas por decisão do proprietário e registrado com novo readback.

## 11. Riscos, limitações e pendências

- **P05 positivo e P09 strict** ainda não observados nesta PR; serão fechados no checkpoint com SHA/run reais.
- **P10** é prova de política/configuração, não execução de PR de fork externo; nenhum fork real foi criado.
- **P06/P07** são provas de configuração efetiva; nenhum push/force/delete real na `main` foi tentado, conforme proibição do Work Order.
- Apenas `docs-validation` é obrigatório. Checks nativos Windows/Linux/macOS/GPU continuam inexistentes e **não** foram exigidos, evitando deadlock.
- `strict` aumenta rebases/reruns após a main avançar; custo aceito e documentado.
- Nenhum problema HIGH/CRITICAL conhecido no diff documental.

## 12. Invariantes preservados

23 direções técnicas bounded preservadas; G1 `PARTIALLY_RATIFIED_NOT_CLEARED`; G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; ADR-0003 e ADR-0075 `PROPOSED`; `NLE-D009 OPEN`; 80/80 coding WOs `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`; zero `executor_ready`; zero `approved_adr`; 80 `release_class=UNDECIDED` e `risk=UNCLASSIFIED`; `engine_implemented=false`; CORE-01-01 e CORE-01-02 `PLANNED_BLOCKED`. Nenhum registry/manifest/workflow/ADR/código foi alterado.

## 13. Escopo documental desta PR

Esta PR adiciona **exatamente um Markdown novo** (este Evidence Bundle). A promoção de `G2 CLEARED`, a atualização do checkpoint, do backlog e dos documentos de gates/plano G2 ocorrem em **PR de checkpoint independente**, somente após o merge positivo e a prova strict serem observados e auditados. Até lá, `G2_NOT_YET_PROMOTED`.
