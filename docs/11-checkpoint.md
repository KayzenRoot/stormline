# Checkpoint — Stormline

**Data de verificação:** 2026-11-14  
**Fase:** P00, planejamento documental. Nenhuma engine executável, SDK, demo, build, release ou benchmark gráfico entregue.  
**Último incremento de pesquisa documental aprovado:** `NLE-P00-WO-002-DATA-03` — importadores, conversão e reimportação idempotente, PROPOSTA de arquitetura (sem engine implementada).  
**Main SHA comprovado após o merge da PR #115:** `d6993c2e67a5fd53c19126f0d0473a62e0e7909f`.  
**Evidence Bundle mais recente:** [NLE-P00-WO-002-DATA-03](evidence/NLE-P00-WO-002-DATA-03.md).

## 1. Fundação previamente aprovada
- `NLE-P00-WO-001`: Source Pack, identidade da marca **documentada como proposta**, governança solo e CI documental.
- PR #1 integrada por squash, commit `926fa0c64706619354ad365e1a942d303c6ca58d`, HEAD auditado `62c4eb03a54efb89de56ddad86a9bdf56dec5463`.
- PR #2 de reconciliação documental integrada, commit `dcd6c81d092d629caf2f4f143bdd9377a262f87d`.
- Evidence Bundle anterior: [NLE-P00-WO-001](evidence/NLE-P00-WO-001.md).

## 2. Apresentação e organização do repositório
- Solicitação do proprietário: README internacional muito profissional e repositório público com organização de startup.
- `NLE-P00-WO-001-EXT-001` foi autorizada como **extensão documental** da fundação, sem iniciar a pesquisa técnica `NLE-P00-WO-002`.
- Branch `docs/NLE-P00-WO-001-EXT-001-repo-presentation`.
- Base SHA `dcd6c81d092d629caf2f4f143bdd9377a262f87d`, último HEAD auditado `ab5b315923329053bccd20699ea8e8deb76c0132`.
- PR #3: 20 arquivos (README inglês, README pt-BR, versões, comunidade, issue templates, standards, validator, Scope/DoD/Backlog). Diff documental, sem código de engine.
- GitHub Actions `Docs Validation` run `43587690479`, job `docs-validation`: **SUCCESS** no HEAD auditado.
- Auditoria técnica em pt-BR: **APPROVED** para o escopo documental, sem defeitos HIGH/CRITICAL identificados no diff revisado.
- Squash merge normal da PR #3 confirmado com SHA `e41274bb841094630ba71843b0876bb5d79370f4`. README e workflow relidos na main após merge.
- Evidência e checkpoint reconciliados por mudança documental pós-merge sujeita a validação automatizada antes de integração.

## 3. Diretrizes aprovadas pelo proprietário
- Nome Stormline; motor próprio NexLabs com integração criteriosa de bibliotecas especializadas.
- Governança do proprietário com IA como arquitetura/auditoria/execução: sem exigência de revisores humanos externos.
- Qualidade verificável e CI gratuito para repositório público; **sem CodeRabbit**, sem subscrições pagas obrigatórias.
- Tecnologia original pretendida para renderização/iluminação, VFX, áudio, performance e experiências como shooters e ARPGs. Nenhuma novidade técnica ou superioridade foi comprovada.

## 4. Pendências explícitas
- `main` protections, required checks e configurações administrativas do GitHub: **NOT VERIFIED / NOT APPLIED** via conexão disponível; somente documentadas como recomendações.
- Description, topics, website e imagem social-preview do campo About: **NOT APPLIED**; descrição/tópicos candidatos em [repository-standards](engineering/repository-standards.md).
- Private vulnerability reporting: **NOT VERIFIED**. Security.md não anuncia canal como habilitado.
- Licença para código, trademark/domínio, aprovação de paleta/logo/intro/sonic signature: OPEN ou PROPOSED, conforme Ledger.
- Nenhum build de C++, renderer, VFX, áudio, física, multiplayer ou GPU benchmark existe.
- Badges indicam apenas CI documental, não qualidade de runtime nem aprovação de produto.

## 5. Catálogo de módulos e autonomia de planejamento (novembro de 2026)
- PR #5, HEAD auditado `6fd10ed65bea105c14d40797f2a14455a4cd4d0c`, foi aprovado para integrar **o inventário de 80 módulos e 14 áreas**, não para tornar cada tecnologia automaticamente obrigatória à versão 1.0.
- GitHub Actions run `43590210539`, job docs-validation: SUCCESS, incluindo verificação de links e DAG de dependências.
- Squash merge PR #5: `06c6a624812bed255ab153793a988fef50dd311a`, confirmado por leitura da main. Evidence: [NLE-P00-WO-001-EXT-002](evidence/NLE-P00-WO-001-EXT-002.md).
- Dono do projeto autorizou continuidade de propostas técnicas de rotina sem perguntar repetidamente; permanecem necessários testes, auditoria, controles de segurança e consentimento explícito para gastos, ações irreversíveis ou bypass.
- Windows, Linux e macOS são plataformas desktop obrigatórias para Editor e jogos exportados; a matriz de hardware/macOS Intel deverá ser decidida e testada. Jogos web são alvo adicional.
- Nenhum módulo de código implementado, e nenhum desempenho AAA comprovado. Repositório permanece em P00.

## 6. Pesquisa tecnológica CORE-01 concluída documentalmente
- Issue #6, módulo CORE-01, WO filha `NLE-P00-WO-002-CORE-01`; **pesquisa/ADR PROPOSED entregue, sem implementação**.
- PR #8 base `c5ef59c13e65db2a79a04d420cdfc9a9c10768d6`, HEAD auditado `d8c5eccbf5620c9075373c545146d94866f1fd8b`; CI [run 43591720602](https://github.com/KayzenRoot/stormline/actions/runs/43591720602) docs-validation SUCCESS.
- Squash merge PR #8 SHA `85e04b98163bb273a2c1e3d08fd4fd95d0ba9893`, confirmado na main; Evidence Bundle [CORE-01](evidence/NLE-P00-WO-002-CORE-01.md).
- Tecnologias preferidas para avaliação futura: C++20, SDL3, CMake Presets/Ninja, bridges Win32/Cocoa/Wayland/X11; hipótese SAPL ainda sem vantagem comprovada.
- Windows/Linux/macOS no Editor e em exports, com Apple Silicon; Intel/minimum OS/assinaturas e render Metal/Vulkan aguardam ADRs de plataforma/gráficos. A spec não demonstra compilação nem desempenho.
- NLE-P00-WO-002 é programa de pesquisa modular ainda em andamento; cada próximo módulo receberá sua WO filha sequencial.

## 7. Pesquisa tecnológica CORE-02 concluída documentalmente
- Issue #10, WO filha `NLE-P00-WO-002-CORE-02`, memória/alocadores/budgets; pesquisa e ADR-0004 entregues, **sem código**.
- PR #11: base `98738969c970c2f04cfaa35c84da86ab41688744`, HEAD auditado `25bad2fedc56e7e66e42ceaae3922d0711bf1b16`; CI [run 43592434642](https://github.com/KayzenRoot/stormline/actions/runs/43592434642) docs-validation SUCCESS.
- Squash merge PR #11: `dabc066897358e95fa92c8624441cc6b0f4a83f0`, confirmado por leitura da main.
- [Evidence Bundle CORE-02](evidence/NLE-P00-WO-002-CORE-02.md) documenta limites de evidência e próximos gates.
- Tecnologias candidatas: C++20 `std::pmr`, sistema como baseline, mimalloc 3.x e rpmalloc para A/B, Tracy/sanitizers para profiling; SMF como hipótese **não comprovada**.
- Nenhuma alocação real foi substituída. Sem benchmark, binários, testes de GPU/OS ou melhorias provadas. ADR-0004 mantém status PROPOSED.

## 8. CORE-03 — jobs/concurrency, aprovado documentalmente
- Issue #13, `NLE-P00-WO-002-CORE-03`: especificação do scheduler, pesquisas Taskflow/enkiTS/oneTBB/C++20 e ADR-0005 PROPOSED.
- PR #14 base `b76e7fd9992dcc012c212e8afe3d2836d9776c63`, HEAD auditado `cdab3939056541ce924571333f5942adbbc81973`; [CI 43593597518](https://github.com/KayzenRoot/stormline/actions/runs/43593597518) docs-validation SUCCESS.
- Merge squash `15702e6228f1571596ef3b34e2592783ba786c74` confirmado por read-back de main. [Evidence Bundle](evidence/NLE-P00-WO-002-CORE-03.md).
- Hipótese de tecnologia própria SFAS permanece pesquisa, não prova de desempenho ou scheduler implementado.
- Nenhuma versão pública ou programa C++ foi criado.

## 9. Fila completa de Work Orders preparada (não executável)
- O proprietário solicitou precriar WOs/issues para que o Zcode, quando autorizado, codifique em vez de decidir produto/arquitetura.
- PR #17 (base `3db4507ffa99896a799c0da7fe0be738fa4a4f4c`, HEAD auditado `1b45aee397d5a375cc95202840611b4e0e251435`) integrou **80 pacotes individuais**, registry topológico JSON, scripts de validação e seleção em modo somente leitura, contrato Zcode. O merge squash foi `b479396d0751e316691b859079a589c8c0c189a7`, conferido por readback da main.
- [CI 43595119500](https://github.com/KayzenRoot/stormline/actions/runs/43595119500): docs-validation **SUCCESS**, incluindo 80 WOs, DAG e teste de que seletor recusa trabalho bloqueado.
- **80 issues de implementação futura em estado PLANNING/BLOCKED foram criadas e conferidas**, números #18 a #97, 80 IDs de WO únicos, 0 faltantes/duplicados. Ver [fila](queue/README.md) e [registro](queue/implementation-registry.json); mapeamento numérico incluído em delta documental auditável.
- Todas as WOs permanecem `BLOCKED_PENDING_TECHNOLOGY_AND_CONTRACTS`, release class UNDECIDED, `executor_ready=false`. Não existem código, benchmarks, arte, exportadores ou implementação de MCP.
- [Evidence Bundle da fila](evidence/NLE-P00-WO-002-QUEUE-001.md) lista SHAs, CI, limitações e riscos. Nenhum requisito de revisor externo, CodeRabbit ou serviço pago.

## 10. CORE-04 — relógio de simulação e determinismo de agendamento
- Issue de pesquisa [#99](https://github.com/KayzenRoot/stormline/issues/99), Work Order `NLE-P00-WO-002-CORE-04`, pesquisa aprovada **exclusivamente como documentação**, sem código de runtime.
- PR [#100](https://github.com/KayzenRoot/stormline/pull/100): base main `90eaf1b7cef148dfd168e3fa1ac8f7e9be603216`; HEAD auditado `27eafe1d514d909a51470766eb4513d4bbf5ef40`. [CI final 43597153261](https://github.com/KayzenRoot/stormline/actions/runs/43597153261): **SUCCESS** com Source Pack/links, catálogo/DAG, registry de 80 WOs e teste que rejeita executor em estado BLOCKED. Falha Markdown anterior foi corrigida na mesma PR; ver Evidence Bundle.
- Auditoria objetiva em pt-BR: **APPROVED para o escopo documental**, sem HIGH/CRITICAL conhecido; squash merge normal da PR #100 em `17b1a4c75e87fcf424a6cf42f198e72c4da2ea9a` com leitura de main confirmada.
- Decisão preferencial **PROPOSTA**: `std::chrono::steady_clock` monotônico injetável, contador racional/integer tick fixo, interpolação de apresentação, time debt observável e pausa/single-step. [Arquitetura](architecture/core-04-time-simulation.md), [matriz](research/core-04-technology-matrix.md) e [ADR-0006](adr/0006-core-04-time-policy.md) seguem em estado de pesquisa; **ADR-0006 não é autorização de implementação**.
- Agendamento de ticks é distinto de determinismo numérico cross-OS em física/rede. Nenhum build C++, benchmark, hardware test, clock funcional, SDK, editor, renderizador, release ou deploy foi observado. **Issue futura #21 permanece PLANNING/BLOCKED** e `executor_ready=false`.

## 11. CORE-05 — matemática, precisão espacial e IDs estáveis
- Issue de pesquisa [#102](https://github.com/KayzenRoot/stormline/issues/102), WO `NLE-P00-WO-002-CORE-05`; pesquisa concluída **apenas documentalmente**. Issue de implementação [#22](https://github.com/KayzenRoot/stormline/issues/22) permanece BLOCKED.
- PR [#103](https://github.com/KayzenRoot/stormline/pull/103): BASE `c96fcc0d5e5094c84cd1e0af9085fba6849bcecb`, HEAD auditado `fc1949b1da58f8c89bafb16560498fc0bfd32cf0`. [CI 43597892824](https://github.com/KayzenRoot/stormline/actions/runs/43597892824) docs-validation SUCCESS, incluindo Source Pack/links, catálogo, registro de 80 WOs e seletor que recusa status BLOCKED.
- Auditoria pt-BR APPROVED para pesquisa documental, sem HIGH/CRITICAL identificado no escopo; merge squash `c5f5b97508d31f4abb49671e9d4d9a59c7bc940f`, lido de volta na main.
- [Arquitetura](architecture/core-05-math-coordinate-types.md), [matriz de bibliotecas](research/core-05-technology-matrix.md), [ADR-0007](adr/0007-core-05-coordinate-policy.md) PROPOSED. C++20 com contratos próprios, GLM candidato, float64 global/float32 relativo ou célula+offset, IDs persistentes distintos de handles voláteis; eixos RH Y-up e unidades SI são **propostas**, não interface já executável.
- Nenhum build, benchmark numérico, teste de precisão, engine, renderer ou integração física/rede foi realizado. [Evidência](evidence/NLE-P00-WO-002-CORE-05.md).
- `NLE-EXEC-WO-CORE-05-001` permanece `executor_ready=false` e RELEASE CLASS UNDECIDED. A pesquisa não libera o Zcode.

## 12. CORE-06 — diagnósticos, profiling e crash evidences
- Issue de pesquisa [#105](https://github.com/KayzenRoot/stormline/issues/105), WO `NLE-P00-WO-002-CORE-06` aprovada **somente para documentação**. Issue de implementação [#23](https://github.com/KayzenRoot/stormline/issues/23) permanece BLOCKED.
- PR [#106](https://github.com/KayzenRoot/stormline/pull/106): BASE main `cc18ce33a05cbadac330effcc7ad6ddf29380721`, HEAD auditado `e12aec2ee7f410e5f024e98295a2f109e1aef834`. [CI 43599614853](https://github.com/KayzenRoot/stormline/actions/runs/43599614853) docs-validation SUCCESS (Source Pack/links, 80-module DAG, 80 WOs registry e seletor de bloqueio).
- Auditoria pt-BR APPROVED para pesquisa documental. Merge squash `a76cb2bb3d39af44897df89d348c667fa1cb4fc3` lido de volta na main; sem defeitos HIGH/CRITICAL documentais conhecidos.
- Contratos de logs, spans, métricas, crash-envelope local e correlação por build SHA/tick/job/frame propostos. [Arquitetura](architecture/core-06-diagnostics-observability.md), [matriz](research/core-06-technology-matrix.md), [ADR-0008](adr/0008-core-06-observability-policy.md) (PROPOSED). spdlog, Tracy, Perfetto, Crashpad **apenas candidatos**, sem vendor instalado nem cloud obrigatório; SDF hipótese de R&D.
- Privacidade local-first e telemetria/upload OFF por padrão; crash dumps potencialmente sensíveis. [Evidence Bundle](evidence/NLE-P00-WO-002-CORE-06.md).
- CORE-01..CORE-06 possuem **pesquisa de planejamento**, nenhuma implementação C++ ou testes reais de benchmark/crash/CPU/GPU. `NLE-EXEC-WO-CORE-06-001` permanece `executor_ready=false`.

## 13. DATA-01 — Virtual File System, segurança de montagem e persistência
- Research issue [#108](https://github.com/KayzenRoot/stormline/issues/108), WO `NLE-P00-WO-002-DATA-01`: pesquisa aprovada **somente como documentação**; implementation issue [#24](https://github.com/KayzenRoot/stormline/issues/24) continua BLOCKED.
- PR [#109](https://github.com/KayzenRoot/stormline/pull/109): base main `3befddfb0df42ee5a8a749fb39116bfbd36fb01a`, HEAD auditado `fc08fb2c4374405acecfd9c56a8f543b40fe0410`; GitHub Actions [43600716325](https://github.com/KayzenRoot/stormline/actions/runs/43600716325) docs-validation SUCCESS: Source Pack/links, 80-module DAG, 80-WO registry, seletor recusando WO BLOCKED.
- Auditoria objetiva em pt-BR APPROVED apenas para pesquisa; squash merge `aca78dab42e3ecfa5f8a9b4101c7f7ad41b0e17b` confirmado em leitura de main. Nenhum HIGH/CRITICAL documental conhecido.
- [Arquitetura DATA-01](architecture/data-01-virtual-file-system.md), [matriz de tecnologia](research/data-01-vfs-technology-matrix.md), [ADR-0009](adr/0009-data-01-vfs-policy.md) PROPOSED; namespace lógico, mounts/overlays com permissões, abertura por handle para contenção, quotas e escrita staged. PhysicsFS zlib e libzip BSD-3-Clause candidatos; nenhuma dependência instalada.
- Path traversal, TOCTOU, symlink/junction, ZIP-bomb/zip-slip, recuperação após crash e risco de perda de dados requerem testes nativos. SAMG é hipótese de R&D não comprovada.
- [Evidence Bundle DATA-01](evidence/NLE-P00-WO-002-DATA-01.md): sem build C++, fuzzing, runtime filesystem, benchmark, integração real ou sandbox comprovado. Implementation issue #24 preservada com `executor_ready=false`.

## 14. DATA-02 — Asset Registry, IDs persistentes e provenance
- Research issue [#111](https://github.com/KayzenRoot/stormline/issues/111), `NLE-P00-WO-002-DATA-02` research documentation APPROVED. Implementation issue [#25](https://github.com/KayzenRoot/stormline/issues/25) continua BLOCKED.
- PR [#112](https://github.com/KayzenRoot/stormline/pull/112): base main `7924f0eaf1eaf711e2316da7f4ee3dc7521afddb`, HEAD auditado `99076f7df0e63e12e082329830bbac49cd241143`; [CI 43601883375](https://github.com/KayzenRoot/stormline/actions/runs/43601883375) docs-validation SUCCESS (Source Pack/links, 80-module DAG, registry de 80 WOs, selector bloqueado).
- Auditoria em pt-BR APPROVED somente para pesquisa documental; merge squash `a5664bfccf011dc3300c54a18d6ae846ee0926d8` confirmado por leitura de main/arquitetura. Nenhum defeito HIGH/CRITICAL documental conhecido.
- [Arquitetura](architecture/data-02-asset-registry.md), [matriz](research/data-02-asset-registry-technology-matrix.md), [ADR-0010](adr/0010-data-02-asset-identity.md) PROPOSED, [contrato de API](contracts/data-02-registry-api.md), [16 cenários de testes](testing/data-02-acceptance-matrix.md).
- Direção candidata: `AssetId` persistente independente do caminho físico, hash, revision e runtime handle; avaliar UUIDv7/v4, SQLite derivado com metadados canônicos portáteis versus outras alternativas e BLAKE3/SHA-256; dependências/provenance e operações sem quebrar referência.
- SQLite WAL single writer/local-only e política de durabilidade são requisitos de avaliação; alterações VFS+SQLite **não constituem uma transação atômica**. Journal/reconciliação e falhas injetadas são provas futuras. SAPG é R&D não comprovado.
- [Evidence Bundle](evidence/NLE-P00-WO-002-DATA-02.md). Sem C++ compilado, SQLite criado, benchmarks, testes de recuperação, GPU, plataforma ou MCP implementados; as 80 WOs permanecem BLOCKED/`executor_ready=false`.

## 15. DATA-03 — importação e conversão segura, recibos e reimportação
- Issue de pesquisa [#114](https://github.com/KayzenRoot/stormline/issues/114), WO `NLE-P00-WO-002-DATA-03`, **APPROVED para documentos somente**; [issue #26](https://github.com/KayzenRoot/stormline/issues/26) de implementação continua BLOCKED.
- PR [#115](https://github.com/KayzenRoot/stormline/pull/115): base main `b477dbecacc733a251666644ac05173f9390d159`, HEAD auditado `d5cd189e55452c351e7cddb8d15f31eed5577201`. [CI 43603329199](https://github.com/KayzenRoot/stormline/actions/runs/43603329199) docs-validation SUCCESS, incluindo links/Source Pack, 80 módulos/DAG, 80 WOs e seletor bloqueado.
- Auditoria em pt-BR APPROVED para pesquisa documental, squash merge `d6993c2e67a5fd53c19126f0d0473a62e0e7909f` confirmado por leitura de main e artefatos. Nenhum HIGH/CRITICAL conhecido no escopo documental.
- [Arquitetura](architecture/data-03-import-conversion-pipeline.md), [matriz de tecnologia](research/data-03-importer-technology-matrix.md), [ADR-0011 PROPOSED](adr/0011-data-03-import-policy.md), [API semântica](contracts/data-03-import-api.md), [20 testes futuros](testing/data-03-acceptance-matrix.md).
- Conformidade glTF/GLB, fastgltf/cgltf MIT, Assimp BSD-based; KTX-Software licenças mistas com decoder ETC não open-source opcional sob bloqueio de distribuição. OpenUSD condicional. Nenhuma biblioteca vendored.
- `AssetId` preservado em reimportação, mapeamento estável de subassets e usuário overrides protegidos por preview/conflito propostos; import receipts e staged commit devem respeitar DATA-01 VFS e DATA-02 reconstrução de índices.
- [Evidence Bundle](evidence/NLE-P00-WO-002-DATA-03.md): não foram executados parser/codec, C++ builds, testes de fuzz/fidelidade/recovery, benchmarks hardware/macOS ou MCP. Nenhum importador funcional, engine ou conversor entregue. `executor_ready=false` nas 80 WOs.

## 16. Próximo incremento
`NLE-P00-WO-002-DATA-04`: pesquisa de Serialization & Scene Format, contratos versionados, diffs semânticos e migrações com roundtrip seguro, **PLANNED / NOT STARTED** até esta reconciliação passar CI/auditoria/merge. O próximo incremento é documental; nenhuma WO do Zcode executável.
