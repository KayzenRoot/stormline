# Technology & Innovation Radar
Status: PROPOSED

## Trilhas prioritárias
1. Lighting: GI eficiente, sombras escaláveis, temporal stability, transparências.
2. VFX: partículas GPU/CPU balanceadas, temporal reuse, overdraw control, volumétricos.
3. Audio: espacialização eficiente, mixagem dinâmica, oclusão, latência.
4. World: streaming, LOD, instancing, IO e precisão numérica.
5. Animation: compressão, blending e latência de input/movimento.
6. Network: interesse espacial, snapshots, prediction/reconciliation.
7. Tooling: importação rápida, hot reload, diagnóstico e fluxos do editor.

## Método de avaliação
HIPÓTESE -> anterioridade -> cenário reprodutível -> baseline contra técnica comum -> custo (CPU/GPU/VRAM/latência) -> qualidade -> riscos -> ADR -> experimento -> decisão. Classes: WATCH, INVESTIGATE, TRIAL, ADOPT, HOLD.

## Prova de inovação
Não chamar uma técnica de inédita sem pesquisa prévia de literatura, patentes, projetos abertos e documentação; não prometer superioridade antes dos benchmarks. Documentar trade-offs e hardware acessível.
