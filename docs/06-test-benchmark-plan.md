# Test & Benchmark Plan
Status: PLAN; NÃO significa testes executados

## P00 documentação
- Validar arquivos obrigatórios, links locais relativos, ADRs e consistência dos estados.
- CI GitHub Actions via runner padrão gratuito; se execução indisponível, reportar BLOCKED em vez de fingir sucesso.
- Conferência humana/IA da precisão documental e ausência de promessas não provadas.

## Futuro runtime
- LOW: checks direcionados.
- STANDARD: unitários + lint + typecheck/build e integração aplicável.
- ELEVATED: STANDARD + regressão ampla, persistência/migração/segurança/recuperação.
- HIGH_ASSURANCE: dinheiro, signing, autenticação privilegiada ou ação irreversível; prova forte, teste independente e rollback/roll-forward.

## Medições a especificar
- Render: FPS, frametime p50/p95/p99, CPU main/render/jobs, GPU timings, VRAM, memória resident.
- Escala: número de entidades, triângulos, draw calls, transparências, partículas, luzes e dimensão de mundo.
- Multiplataforma: GPU vendor, driver, OS, versão do compilador e parâmetros de cena.
- Áudio: latência, CPU, x-runs/underruns, vozes simultâneas e posicionamento espacial.
- Rede: clientes simulados, latência, jitter, loss, tráfego/entidade, tempo de tick.
- Regressão visual: imagens de referência com tolerâncias por GPU e aprovação das mudanças.
- Estabilidade: sanitizers, stress, soak, vazamentos, crashes, importação corrupta.

## Política de evidências
Toda métrica exige hardware, versão do código, driver, build flags, conteúdo de cena, método, amostras e artefato reproduzível. 60 FPS/1080p é ideia de alvo a discutir, NÃO resultado nem requisito aprovado.
