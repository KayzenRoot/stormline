# Definition of Done
Status: PROPOSED para o planejamento P00

## DoD da WO-001
1. Source Pack mínimo versionado em Git e indexado por README/hierarquia.
2. Branding documentado com separação explícita entre APPROVED, PROPOSED e NOT PRODUCED: nome, identidade, cores, logo, intro, áudio, aplicações.
3. Governança solo sem revisão humana externa, mas com PR, CI e auditoria objetiva.
4. CI gratuita documental verificável em PR, sem CodeRabbit/serviço pago; configurar required checks só após status existente.
5. Contrato de Codex/Zcode, template de WO e Evidence Bundle completos.
6. ADRs e Ledger coerentes com o consentimento do proprietário; sem declarações falsas sobre implementação, testes, marca ou licença.
7. Diff sem alterações inesperadas, sem segredos, sem arquivos de engine; documentação interna consistente.
8. Evidência: SHA base/head, arquivos, testes, resultados reais de CI, riscos, checkpoint delta proposto e revisão em pt-BR.
9. A auditoria conclui APPROVED sem HIGH/CRITICAL conhecido; merge sem bypass, seguido de verificação de main e atualização legítima do checkpoint.

## DoD da extensão NLE-P00-WO-001-EXT-001 (proposta do incremento)
1. README em inglês e versão pt-BR com estado de planejamento claramente visível, visão e áreas de pesquisa, arquitetura conceitual, roadmap, links, segurança, licença ainda aberta e transparência sobre benchmarks inexistentes.
2. Padrões de comunidade (contribuição, segurança, suporte, conduta), versionamento editorial e templates GitHub versionados.
3. Nenhum código de engine, logo final, release, credencial, serviço pago, review humano obrigatório ou decisão de licença por inferência.
4. Validação de todos os links locais, presença dos documentos e issue templates por Python stdlib; GitHub Actions docs-validation PASS no HEAD auditado.
5. Auditoria do diff, Evidence Bundle, ausência de HIGH/CRITICAL, PR aprovado e merge sem bypass; checkpoint e evidência reconciliados após merge.
6. Configurações de GitHub About, branch protections, private vulnerability reporting permanecem NOT VERIFIED enquanto o conector não suportar leitura/alteração.

## Critérios propostos da extensão de catálogo NLE-P00-WO-001-EXT-002
- Inventário de módulos 2D, 2.5D, 3D, Windows/Linux/macOS, web, gráfico, áudio, VFX, gameplay, editor, multiplayer, ferramentas e produto comercial.
- IDs únicos, dependências válidas sem ciclos e testes conceituais de aceitação por módulo.
- Contrato de comando comum a UI/CLI/MCP, autorização, schemas, transações, validação e compatibilidade MCP versionada.
- Conceito **No MVP**: marcos internos válidos, sem disponibilização comercial até atingir DoD global aprovado.
- Sem tecnologia aprovada por suposição; catálogo permanece PROPOSED até aceite do proprietário.
- CI documental e validador do catálogo verdes no SHA do PR; sem código de engine.

## DoD da preparação de Work Orders (NLE-P00-WO-002-QUEUE-001)
- 80 Work Orders drafts, IDs estáveis, dependências do catálogo corretas, estado explicitamente BLOCKED, release class UNDECIDED e nenhuma autorização de implementação.
- Registro machine-readable, 80 documentos individuais, validação automatizada de estrutura/links/DAG e comando read-only para o executor.
- Issues de planejamento rastreáveis, sem duplicatas e explicitamente não prontas para código.
- Guia Zcode com preflight, Scope/DoD/ADR/Context Lock, CI, evidência, auditoria e uso da mesma PR em correções.
- CI documentação PASS no SHA fixo, Evidence Bundle, auditoria e checkpoint posterior ao merge.
- Não declarar que Zcode pode apenas codificar em módulos ainda sem specification/approved ADR.

## DoD futuros
Funcional, testado, documentado, deployado quando aplicável e validado em ambiente-alvo, incluindo perf, segurança, compatibilidade e migração conforme risco. Não aceitar claim "completed" desacompanhada de evidência.

## Falha
CORRECTION REQUIRED: corrigir somente na mesma WO/PR; BLOCKED: resolver pré-requisito. Nenhum próximo incremento até aprovação válida.

## CORE-01 G1 — DoD e obrigações de prova ratificados parcialmente (2026-11-16)
O proprietário ratificou **C01-D01/D08/D09/D14** como contrato de projeto e proposta de mensuração futura. Isto **não comprova funcionalidade**, não libera o pacote 02, nem define os limiares complementares da versão 1.0. Ver [Ledger](10-decisions-ledger.md), [Evidence G1](evidence/NLE-PRPLAN-CORE-01-01-G1-RATIFICATION.md).

1. **D01:** núcleo mínimo de Platform & Lifecycle para Editor, cliente/jogo, servidor e testes; lifecycle e erros tipados com modo janela e modo headless. Especificar funcionalidades avançadas e exceções antes de fechar release classes.
2. **D08:** para cada alvo desktop inicial Windows x86_64, Linux x86_64, macOS arm64, fixar versão mínima de OS, CPU, SDK/runtime, build e testes em ambiente real. macOS Intel/Windows ARM64 condicionais; Web sob PLAT-03.
3. **D09:** o modo CPU-only headless deverá inicializar/encerrar sem GPU, janela, DISPLAY/WAYLAND_DISPLAY, sessão gráfica, editor ou dispositivo de áudio obrigatórios; tratar falhas parciais, eventos e vazamentos de recursos. NET-02 não é pré-requisito do host.
4. **D14:** os critérios numéricos futuros incluem **200/200** boots headless e **100/100** ciclos de janela por plataforma aprovada, replay de **10.000** eventos sintéticos, **30 cold + 30 warm** amostras de tempos, ausência de leaks detectáveis e recibos de CI/sanitizer/hardware/driver/compilador. Limites ainda não especificados de tempo/memória e a matriz física devem ser aprovados antes de declarar qualificação; 30 amostras não bastam para alegação robusta de p99.
5. **Prova e gate:** manter 32 casos C01-Q001..Q032 como FUTURE_NOT_EXECUTED, exigir registros reprodutíveis, testes negativos e regressão conforme risco. G1 fica PARTIALLY_RATIFIED_NOT_CLEARED; G2 e G3 abertos. Nenhuma ADR, tecnologia, licença ou classe do registry promovida por esta ratificação.

**DoD documental deste delta:** PR restrita aos registros de decisão/Scope/DoD/dossiê/gates/WO/evidência, GitHub Docs Validation no HEAD revisado, auditoria objetiva pt-BR, squash, readback e checkpoint independente. O DoD da engine 1.0 e G1 integral não foram cumpridos.

## CORE-01 G1 — aceite futuro ratificado para os parâmetros mínimos (2026-11-16)

As oito decisões `G1-M01..M08` foram expressamente ratificadas pelo proprietário com limites e obrigações de prova; ver [Ledger](10-decisions-ledger.md) e [Evidence Bundle](evidence/NLE-PRPLAN-CORE-01-01-G1-MINIMA-RATIFICATION.md). Estes são **oráculos FUTUROS**, não resultados.

1. **Suporte desktop:** validar Windows 11 25H2 x64 piso provisório e 26H2 compatível, Ubuntu 24.04 LTS x64/glibc 2.39 referência, macOS 15 Apple Silicon arm64 piso candidato com macOS 26 compatível. Separar versão Xcode host da deployment target. Definir patch mínimos, toolchains, CPU vendor/ABI, drivers e builds, e conferir EOL antes de liberar binários.
2. **CPU e hardware:** provar que host x86_64 básico não usa AVX/AVX2 obrigatório e checa capabilities antes do dispatch; host arm64 nativo. Rodar fixtures CPU-only headless 2 logical CPU/4 GiB sem display/GPU/áudio; janela 4 logical CPU/8 GiB. Não inferir hardware mínimo do Editor/jogo/renderizador.
3. **Profundidade CORE-01:** provar inicialização/encerramento, erro tipado, estados/lifecycle, eventos e caminhos básicos, janela e headless, sem leaks detectáveis e sem dependência circular de GFX/AUD/NET; itens advanced não se tornam obrigatórios em lote. Requer contratos e mapeamento final com Scope/DoD global por módulo.
4. **Critérios numéricos futuros:** **200/200 ciclos headless e 100/100 ciclos de janela por plataforma**, replay de **10.000 eventos**, **30 cold + 30 warm** amostras; **zero perda silenciosa de eventos classificados críticos**, testes negativos, zero UAF/leaks **detectados** por instrumentos aplicáveis, e erro tipado em até **5 s** quando não existir display. Definir categorias de eventos/coalescing, ciclos completos, timeout de CI, métricas e logs por SHA. **Não declarar p99 confiável** dessas amostras nem afirmar zero bugs globalmente.
5. **Performance ainda aberta:** medir p50/p95/RSS e orçamento CPU/memória; limiares absolutos de p95/RSS devem ser **calibrados e depois expressamente ratificados**, não são aprovados nesta rodada.
6. **Requalificação:** revalidar suporte de OS/CPU/dependências e segurança **90 dias antes de possível release pública**; reabrir mínimos defasados ou EOL. Nenhuma distribuição pública sem DoD 1.0 global, gates de compatibilidade/segurança/licenças concluídos e autorização separada.

**Status verificável:** C01-Q001..Q032 continuam `FUTURE_NOT_EXECUTED`; G1 `PARTIALLY_RATIFIED_NOT_CLEARED` enquanto provas, thresholds e product Scope/DoD faltarem; G2/G3 permanecem abertos; nenhum C++/CI nativo, hardware, benchmark, ABI, licença ou lançamento aprovado por esta documentação. Manter 80 code WOs BLOCKED, 0 approved ADR/ready, release/risk machine undecided/unclassified, CORE-01-02 PLANNED_BLOCKED e engine_implemented=false.

## CORE-01 G2/G3 — obrigações futuras após ratificação das onze direções A (2026-11-16)

As direções **C01-D02..D07/D10..D13/D15** foram expressamente ratificadas, **não** qualificadas como implementação funcional; detalhes em [Ledger](10-decisions-ledger.md), [opções ratificadas](research/core-01-01-g2-g3-owner-decision-options.md), [Evidence](evidence/NLE-PRPLAN-CORE-01-01-G2G3-OWNER-RATIFICATION.md).

1. **Compiladores e build (D02/D05):** fixar em deliberação posterior versões e matrizes MSVC/GCC/Clang/AppleClang, SDK e CMake/schema, Ninja; executar compilações C++20/build/test clean em Windows x64, Linux x64 e macOS arm64, com metadados/hash de binários, falhas negativas e cache determinístico. Nenhum build nesta etapa.
2. **Adapter e threads (D03/D04):** escolher release/digest SDL3 e validar uso de main thread, contagem init/quit e cleanup parcial, janela/IME/HiDPI/hotplug; host headless inicializa sem display, GPU, áudio ou editor obrigatórios e não bloqueia em callbacks.
3. **ABI e lifecycle (D06/D07):** provar ownership de handles, erros tipados, estados/transições, falha parcial, cancelamento e finalização idempotente; ABI C versionada condicional à aprovação de plugin/SDK externo, não garantia antecipada nem licença de distribuição.
4. **Capabilities/SAPL (D10):** SUPPORTED/UNSUPPORTED/UNKNOWN com fonte/confiança e erros honestos; SAPL extra só mediante benchmark CPU/RAM/semântica e limiar de aceite **ainda pendente de definição/aprovação**. Renderer fica em GFX-01.
5. **Classificação/segurança (D11/D12):** classificar cada incremento conforme fronteira de risco (STANDARD/ELEVATED/HIGH_ASSURANCE se aplicável) somente em autorização própria; validar proteções reais da `main`, jobs requeridos por nome real, fork sem segredos, merge negado com check vermelho e sem bypass. Hoje `main.protected=false`, rulesets vazios e API de proteção 403: **G2 não satisfeita**.
6. **Licenças e provas experimentais (D13/D15):** pin release/digests/SBOM/licenças de SDL3/CMake/Ninja/transitivos/NOTICE; licença da engine NLE-D009 continua OPEN. Experimento nativo exige **WO adicional e aprovação separada antes de qualquer código**, sem liberar executor/CORE-01-02 nem aprovar automaticamente ADR-0003.
7. **Vinculações obrigatórias:** evidências G1 anteriores (200/100 ciclos, 10k eventos, 30+30 amostras) e requalificação OS continuam **FUTURE_NOT_EXECUTED**. p95/RSS permanecem sujeitos a calibração/ratificação posterior; DoD global, release classes, compatibilidade e segurança/recuperação ainda não cumpridos.

**Veredito de DoD:** passou somente a aprovação das **direções de arquitetura**, não os testes/gates. G1 `PARTIALLY_RATIFIED_NOT_CLEARED`, G2 `BLOCKED_NOT_VERIFIED`, G3 `OWNER_DIRECTIONS_RATIFIED_NOT_TECHNICALLY_CLEARED`; ADR-0003/0075 `PROPOSED`, NLE-D009 `OPEN`, 80 code WOs `BLOCKED`, `engine_implemented=false`, CORE-01-02 `PLANNED_BLOCKED`. CI documental não demonstra plataforma nativa.
