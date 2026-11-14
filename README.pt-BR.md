<div align="center">
  <h1>⚡ STORMLINE</h1>
  <h3>Uma iniciativa de engine 3D original da NexLabs Technology</h3>
  <p><strong>Mundos imersivos · Engenharia orientada a desempenho · Evolução contínua</strong></p>
  <p><a href="README.md">English</a> · <strong>Português (Brasil)</strong> · <a href="docs/00-source-hierarchy.md">Documentação</a> · <a href="docs/08-backlog.md">Roadmap</a></p>
</div>

> [!IMPORTANT]
> **Fase de planejamento (P00).** A Stormline ainda **não possui engine executável, editor, SDK, demo, benchmark gráfico nem versão pública**. As capacidades abaixo são objetivos de pesquisa e desenvolvimento, não funcionalidades entregues.

## Visão

A **Stormline** será uma engine 3D própria da NexLabs, desenvolvida com bibliotecas especializadas e com foco em iluminação, VFX, áudio espacial, movimento fluido, mundos extensos e uso eficiente de CPU/GPU, incluindo equipamentos de entrada.

Queremos criar tecnologia original e evolutiva, comprovando as melhorias com **cenários reprodutíveis e medições**, em vez de prometer superioridade sem evidências.

## Diferenciais em pesquisa

| Área | Direção estratégica (ainda não implementada) |
|---|---|
| 🌩️ Renderização e iluminação | Materiais modernos, sombras, qualidade visual e técnicas próprias verificadas por benchmark |
| ✨ VFX | Partículas densas e efeitos expressivos com custo previsível em GPU |
| 🔊 Áudio espacial | Imersão, mixagem e latência com atenção ao consumo de CPU |
| 🎮 Simulação | Animação, personagens, física, veículos e resposta fluida |
| 🌍 Mundos grandes | Terrenos, streaming, LOD e escalabilidade |
| 🖥️ Performance | Perfis de qualidade adaptáveis para GPUs e CPUs acessíveis |
| 🌐 Multiplayer | Arquitetura de rede autoritativa e servidores dedicados |

Referências técnicas de capacidade incluem jogos de combate combinado e ARPGs modernos. A Stormline não está afiliada às empresas responsáveis por esses jogos e **não utilizará conteúdo protegido sem licença**.

## Produtos previstos

- **Stormline Runtime:** execução e simulação.
- **Stormline Editor:** autoria e diagnóstico.
- **Stormline Server:** servidor dedicado desacoplado da interface gráfica.
- **Stormline Sandbox:** demonstrações originais e reproduzíveis.

Todos estão **planejados, não disponíveis**.

## Estado e roadmap

| Marco | Situação |
|---|---|
| P00: planejamento, identidade documental, governança | Em andamento |
| M01: base executável | Não iniciado |
| M02: renderização | Não iniciado |
| M03+: mundo, ferramentas, personagens, multiplayer | Não iniciado |

[Backlog e dependências](docs/08-backlog.md) · [Checkpoint](docs/11-checkpoint.md) · [Registro de decisões](docs/10-decisions-ledger.md)

## Documentação e governança

A fonte de verdade é o Git, os ADRs aprovados, o Scope, o DoD e o Checkpoint. Toda implementação seguirá Work Order com ID estável, PR, testes aplicáveis, Evidence Bundle e auditoria objetiva.

**Equipe solo:** a autoridade de aprovação é do proprietário; não existe exigência de revisor humano externo nem de CodeRabbit. O CI do repositório público utiliza ferramentas gratuitas. A proteção efetiva da branch ainda depende de verificação/configuração administrativa.

- [Arquitetura conceitual](docs/04-architecture.md)
- [Requisitos](docs/02-requirements.md) e [escopo](docs/03-scope.md)
- [Identidade da marca](docs/brand/brand-foundation.md)
- [Governança solo](docs/engineering/solo-governance.md)
- [Instruções para agentes](AGENTS.md)
- [Política de CI gratuito](docs/engineering/free-ci.md)
- [Como contribuir e relatar problemas](CONTRIBUTING.md)
- [Segurança](SECURITY.md) e [suporte](SUPPORT.md)

## Build e distribuição

**Ainda não há código de engine para compilar ou executar.** O repositório pode ser clonado para consultar a documentação e validar links com Python 3:

```bash
git clone https://github.com/KayzenRoot/stormline.git
cd stormline
python3 scripts/validate_docs.py
```

A pilha técnica e a licença pública do código **ainda não foram decididas**. Repositório público não significa permissão de reutilização, distribuição ou contribuição irrestrita. [Política de versões](docs/engineering/versioning.md).

---

<div align="center">
  <p><strong>STORMLINE</strong> · Uma iniciativa da <strong>NexLabs Technology</strong></p>
  <p><em>Construída com disciplina. Medida com evidências.</em></p>
</div>
