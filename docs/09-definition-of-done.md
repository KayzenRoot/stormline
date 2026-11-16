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
