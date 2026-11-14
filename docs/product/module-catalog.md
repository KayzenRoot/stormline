# Stormline — Complete Engine Module Catalog v0.1

**Work Order:** NLE-P00-WO-001-EXT-002 (owner-requested planning extension)  
**Date:** 2026-11-14 | **Status:** PROPOSED FOR OWNER REVIEW, NOT APPROVED | **Implementation:** NONE  
**Baseline:** `9032fe3eeb28ef3ac1ec786387e42a3758ed703a`  
**Scope:** Inventory of intended modules for a complete commercial engine. Not an implementation instruction or a frozen 1.0 scope.

## Product strategy and definitions

Stormline is planned as an **original, commercial-capable, human + AI-native 2D/2.5D/3D engine**, covering desktop and browser releases. The owner requests **NO MVP** and **NO public use before full release readiness**. Internal integration milestones are engineering verification stages, *not* public MVPs, launches or promises to meet all possible game types. A commercial 1.0 requires a frozen, owner-approved versioned capability matrix, with all MUST-HAVE modules and acceptance tests satisfied. A general-purpose engine cannot meaningfully guarantee every possible engine feature forever; post-1.0 innovation continues under a compatibility policy.

User-facing quality references: military combined-arms games for world/network/vehicle requirements and Path of Exile 2-like modern ARPG capability for action, animation, lighting, VFX and audio. Reference games remain unaffiliated and their protected content shall not be copied.

**Definition of module:** a cohesive, independently documented capability boundary with an explicit API/contract, owner, dependencies, failure isolation where relevant, tests, resource budgets and exposure to editor/CLI/AI. A row in this table is a **candidate module**, not evidence a library/package exists. Modules may be consolidated/split through ADRs once evidence exists.

**Integration policy:** human editor actions, CLI/headless actions and MCP tools invoke one common validated command kernel with structured identifiers and transactions. There is no shadow AI-only data model and no arbitrary write access to project files.

## Overview

| Area | Candidate modules | Purpose |
|---|---:|---|
| 01 · Foundation / Kernel | 6 | Infraestrutura comum nativa; nenhum sistema gráfico, editor ou servidor deve ser obrigatório ao iniciar o Core. |
| 02 · Data, Assets & Persistence | 5 | Todos os editores e agentes operam sobre formatos documentados, transações e IDs estáveis, não sobre blobs opacos. |
| 03 · Rendering, Lighting & VFX | 8 | Prioridade máxima de pesquisa: qualidade medida por hardware, estabilidade temporal e custos reais de CPU/GPU. |
| 04 · 2D & 2.5D Native Workflows | 4 | 2D é um pipeline de primeira classe, não apenas um plano/mesh dentro do renderizador 3D. |
| 05 · Scene, Worlds & Spatial Systems | 5 | Modelo de mundo compartilhado por gameplay, editor, MCP, física e networking. |
| 06 · Physics, Animation & AI Gameplay | 6 | Simulação física e de personagens separada de gráficos, inclusive modo servidor dedicado. |
| 07 · Audio & Interactive Sound | 4 | Áudio será módulo com telemetria e autoria próprios, e não integração secundária. |
| 08 · Gameplay Framework & Genres | 5 | O runtime deve habilitar muitos gêneros sem hardcoded de regras militares ou ARPG no Core. |
| 09 · Multiplayer & Online | 6 | Cliente/servidor confiável e seguro, com limites claros; serviços cloud pagos não são pré-requisitos. |
| 10 · Professional Editor & Authoring | 7 | Experiência manual completa, desacoplada do runtime e equivalente em poder ao controle por IA. |
| 11 · AI-native & MCP Integration | 9 | Toda a capacidade de autoria aprovada terá contrato versionado e testável, acessível a humano, CLI e MCP. |
| 12 · Platforms, Packaging & Runtime Targets | 5 | Mesmos dados de projeto com builds específicos e redução de recursos por plataforma. |
| 13 · Quality, Security & Performance Engineering | 5 | Metas de qualidade são parte da especificação do produto, não um plugin instalado no fim. |
| 14 · Commercial Product & Ecosystem | 3 | A engine só estará pronta para uso comercial após distribuição, documentação e acordos claros. |
| **TOTAL** | **78** | **Proposed catalog, not 78 delivered modules or fixed scope.** |

## Catalog by subsystem

### 01 · Foundation / Kernel

Infraestrutura comum nativa; nenhum sistema gráfico, editor ou servidor deve ser obrigatório ao iniciar o Core.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `CORE-01` | **Platform & Lifecycle** | Inicialização, sistema operacional, janelas, eventos, paths, ciclo de vida e interfaces portáveis. | Foundational | Inicializar e desligar headless e com janela, sem leaks detectáveis. |
| `CORE-02` | **Memory & Allocators** | Ownership, alocadores, arenas, budgets, leak tracking e telemetria de memória. | CORE-01 | Comparar allocators e detectar vazamentos em carga reproduzível. |
| `CORE-03` | **Jobs & Concurrency** | Agendador de tarefas, prioridades, dependências, afinidade, cancelamento, isolamento de dados. | CORE-02 | Teste de determinismo aplicável e stress sem data races. |
| `CORE-04` | **Time & Simulation Clock** | Tempo real, tick fixo, interpolação, pausa, stepping, replay determinístico onde exigido. | CORE-01 | Reproduzir ticks consistentes com FPS variáveis. |
| `CORE-05` | **Math / Coordinates / Types** | Vetores, matrizes, espaços de coordenadas, unidades, precisão e IDs estáveis. | CORE-01 | Golden tests para transformações, precisão, overflow e mudança de origem. |
| `CORE-06` | **Diagnostics & Observability** | Logs, traces, contadores, crashes, profiling e telemetria local opt-in. | CORE-01 | Captura reproduzível de CPU frame/jobs, falha e rastreabilidade por build. |

### 02 · Data, Assets & Persistence

Todos os editores e agentes operam sobre formatos documentados, transações e IDs estáveis, não sobre blobs opacos.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `DATA-01` | **Virtual File System** | Paths virtualizados, mounts, overlays, permissão, cache e abstração de armazenamento. | CORE-01 | Montar packs, validar paths e bloquear traversal. |
| `DATA-02` | **Asset Registry & Metadata** | IDs estáveis, dependências, tags, queries, schema, referências e provenance. | DATA-01 | Renomear/mover asset preservando referências. |
| `DATA-03` | **Import & Conversion Pipeline** | Importadores 2D/3D, texturas, animações, áudio, validação e relatórios de origem. | DATA-02 | Reimport idempotente sem perder edição derivada. |
| `DATA-04` | **Serialization & Scene Format** | Schemas versionados, representação declarativa, mudanças compatíveis e diffs semânticos. | CORE-05 · DATA-02 | Round-trip equivalente; diff estruturado e migração testada. |
| `DATA-05` | **Cooking, Streaming Bundles & Patching** | Compilação de assets por target, compressão, streaming, manifests e atualização incremental. | DATA-03 · DATA-04 | Empacotar e verificar hash de bundle; carga progressiva com limite de memória. |

### 03 · Rendering, Lighting & VFX

Prioridade máxima de pesquisa: qualidade medida por hardware, estabilidade temporal e custos reais de CPU/GPU.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `GFX-01` | **Graphics Abstraction (RHI)** | Dispositivos, queues, buffers, texturas, sincronização, feature tiers e backends. | CORE-01 · CORE-02 | Testar ciclo de vida de recursos, perda/recuperação de device e validação API. |
| `GFX-02` | **Shader & Material Compilation** | Linguagem/pipeline de shaders, reflexão, variantes, cache, compilação incremental. | GFX-01 · DATA-03 | Build determinístico, diagnóstico por arquivo/linha, variantes estáveis. |
| `GFX-03` | **Render Graph & GPU Resource Manager** | Passes, dependências, barriers, transient resources e orçamento VRAM. | GFX-01 · CORE-03 | Validar sincronização e medir CPU/GPU/VRAM sob cenas padrão. |
| `GFX-04` | **Geometry, Occlusion & LOD** | Instancing, culling, HLOD, mesh streaming, vegetação e geometry optimization. | GFX-03 · DATA-05 | Grande cena com culling correto e evidência de custo. |
| `GFX-05` | **Materials, Texture Systems & PBR** | Shading físico, textura virtual/opcional, mips, filtros, decals e transparência. | GFX-02 · DATA-03 | Cenas golden de materiais e limites de overdraw. |
| `GFX-06` | **Lighting & Shadows** | Luzes, cascades/virtual shadows candidatos, GI, probes, reflexos e luz volumétrica. | GFX-03 · GFX-05 | Comparação visual e temporal com budgets por tier de hardware. |
| `GFX-07` | **Camera, Color & Post-processing** | Exposição, tone mapping, HDR quando disponível, antialiasing, motion blur opcional e upscale. | GFX-06 | Testes de cor/estabilidade, compatibilidade e falhas de GPU. |
| `GFX-08` | **VFX & Particle Graph** | CPU/GPU particles, ribbons, trails, transparência, volumétricos, pooling e budgets. | GFX-03 · GFX-05 | Stress de efeitos ao estilo ARPG com frametimes, VRAM e qualidade comparável. |

### 04 · 2D & 2.5D Native Workflows

2D é um pipeline de primeira classe, não apenas um plano/mesh dentro do renderizador 3D.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `TWO-01` | **2D Renderer & Canvas** | Sprites, atlases, layers, câmera, pixel snapping, lights, shadows e batching. | GFX-01 · DATA-03 | Cena 2D 60 FPS sob cenário/hardware definidos; texto e sprites sem artifacts. |
| `TWO-02` | **Tilemaps & 2D Worlds** | Grades, tiles, collision shapes, parallax e streaming de mapas 2D. | TWO-01 · DATA-04 | Editor pode salvar/reabrir mapas; streaming e colisão correspondentes. |
| `TWO-03` | **2D Animation & Sequencing** | Flipbooks, bones 2D, blend, cutscenes e timelines. | TWO-01 | Timeline reproduzível e exportada com sincronismo áudio. |
| `TWO-04` | **2.5D Hybrid Composition** | Orthographic/perspective cameras, layers 2D/3D, sorting e efeitos híbridos. | TWO-01 · GFX-04 | Projeto mistura sprites e mundo 3D preservando ordem/iluminação. |

### 05 · Scene, Worlds & Spatial Systems

Modelo de mundo compartilhado por gameplay, editor, MCP, física e networking.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `WORLD-01` | **Entity Component Model** | Identidade, componentes, lifecycle, queries e reflexão de tipos. | CORE-05 · DATA-04 | Criar/destruir entidades preservando invariantes e referências. |
| `WORLD-02` | **Scene & Prefab Hierarchy** | Árvore/graph, composição, prefab variants, instancing e transformações. | WORLD-01 · DATA-02 | Alterações em prefabs propagam de forma controlada, com undo/redo. |
| `WORLD-03` | **Spatial Index & World Streaming** | Células, interest queries, origem espacial, streaming assíncrono. | WORLD-02 · DATA-05 | Percorrer mapa amplo sem stalls além do orçamento definido. |
| `WORLD-04` | **Terrain & Environment** | Terrenos, splatmaps, vegetação, água, céu, clima e editorabilidade. | WORLD-03 · GFX-04 | Benchmark de travessia e render de biomas 3D originais. |
| `WORLD-05` | **Procedural Generation Framework** | Seeds, graphs, regras, biomos, geometria e content generators. | WORLD-04 · DATA-03 | Mesmo seed + versão produz resultado idêntico; edição manual preservada. |

### 06 · Physics, Animation & AI Gameplay

Simulação física e de personagens separada de gráficos, inclusive modo servidor dedicado.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `SIM-01` | **Physics 2D** | Corpos rígidos 2D, colisão, queries, joints, triggers e máscaras. | WORLD-01 · TWO-01 | Suite 2D de colisão, estabilidade e stress. |
| `SIM-02` | **Physics 3D** | Corpos rígidos, shapes, broadphase, queries, constraints e integrações. | WORLD-02 · CORE-03 | Testes de colisão/escala, memória e simulação headless. |
| `SIM-03` | **Character Controller & Movement** | Kinematic/dynamic controllers 2D/3D, locomoção, input response e câmera desacoplada. | SIM-01 · SIM-02 | Golden replay de movimento e variação de FPS. |
| `SIM-04` | **Skeletal Animation & Motion** | Retargeting, blend trees, IK, ragdoll, compressão, sync e root motion. | SIM-03 · DATA-03 | Animação de locomotion/combat com transições coerentes e custo medido. |
| `SIM-05` | **Navigation & Behavior** | Navmesh, steering, behavior trees/statecharts e percepção de NPCs. | WORLD-03 · SIM-02 | NPCs navegam em mundo dinâmico e sob streaming. |
| `SIM-06` | **Destruction & Environmental Response** | Fraturas/debris opcionais por tiers, impactos, marcas, física e VFX coordenados. | SIM-02 · GFX-08 · WORLD-03 | Degradação controlada, orçamento de fragmentos e sincronização. |

### 07 · Audio & Interactive Sound

Áudio será módulo com telemetria e autoria próprios, e não integração secundária.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `AUD-01` | **Audio Device & Mixer** | Output multi-device, sample-rate, buses, voz virtualizada, streaming e limites. | CORE-01 · CORE-03 | Testes de underruns, latência e custo por quantidade de vozes. |
| `AUD-02` | **Spatial Audio & Acoustic World** | HRTF/opções de spatialization, atenuação, oclusão, reverberação e salas. | AUD-01 · WORLD-02 | Cenário de posições/obstáculos com áudio validado e custos medidos. |
| `AUD-03` | **DSP & Sound Graph** | Filtros, efeitos, RTPC/automation, snapshots, mixing hierárquico. | AUD-01 | Graph validado, teste de clipping, estabilidade em tempo real. |
| `AUD-04` | **Music, Dialogue & Cinematic Audio** | Adaptive music, diálogos, legendas/locais e sincronismo com cutscenes. | AUD-03 · AUD-02 | Troca de estado musical sem glitches, acessibilidade e fallback. |

### 08 · Gameplay Framework & Genres

O runtime deve habilitar muitos gêneros sem hardcoded de regras militares ou ARPG no Core.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `GAME-01` | **Input & Control Mapping** | Keyboard/mouse/gamepad/touch, remapping, múltiplos dispositivos, acessibilidade. | CORE-01 | Mapeamentos consistentes entre editor, runtime e exports. |
| `GAME-02` | **Gameplay Scripting & API** | Scripting visual/textual a decidir, bindings, sandbox, hot reload e APIs estáveis. | WORLD-01 · CORE-03 | Modificar regras sem recompilar Core e com limites de segurança. |
| `GAME-03` | **Game UI, Text & Localization** | Widgets, layouts responsivos, foco, texto, fontes licenciadas, idiomas e HUD. | GFX-07 · TWO-01 | UI gamepad/mouse, legibilidade, foco e internacionalização. |
| `GAME-04` | **Gameplay Systems & Event Bus** | Estados de jogo, scene flow, eventos, ability hooks, save hooks e data-driven rules. | GAME-02 · GAME-01 · WORLD-02 | Projetos de gêneros diferentes compartilham o framework sem forks. |
| `GAME-05` | **Genre Templates & Systems** | Shooter, veículos, ARPG loot/skills/inventário, plataforma 2D, corrida, estratégia e puzzle. | GAME-04 · SIM-04 · AUD-04 | Amostras originais cobrem gêneros e exportam sem alterar Core. |

### 09 · Multiplayer & Online

Cliente/servidor confiável e seguro, com limites claros; serviços cloud pagos não são pré-requisitos.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `NET-01` | **Transport & Connection Layer** | Reliable/unreliable, congestion, timeouts, discovery, encryption conforme threat model. | CORE-01 | Testes com latência, jitter, perda e desconexão. |
| `NET-02` | **Authoritative Dedicated Server** | Loop headless, simulação no servidor, validation commands e deployment local. | NET-01 · WORLD-01 · CORE-04 | Servidor executa sem GPU e rejeita estado cliente arbitrário. |
| `NET-03` | **Replication & Interest Management** | State snapshots, delta, relevância espacial, prioridades e compressão. | NET-02 · DATA-04 | Teste de 8/16/32/64 clientes quando perf target definido. |
| `NET-04` | **Prediction, Reconciliation & Lag** | Client-side prediction, rollback quando cabível, interpolação e lag compensation. | NET-03 · SIM-03 | Replay de entrada gera estados toleráveis e métricas de correção. |
| `NET-05` | **Sessions & Lobby Interfaces** | Match/session/lobby abstractions; integração com backend externo opcional. | NET-01 · NET-02 | Criar/join/leave, reconexão e falhas previsíveis sem SaaS obrigatório. |
| `NET-06` | **Network Security & Abuse Control** | Trust boundaries, quotas, validation, fuzzing, replay controls, logs e privacy. | NET-02 · NET-05 | Testes adversariais e ausência de bypass de autoridade. |

### 10 · Professional Editor & Authoring

Experiência manual completa, desacoplada do runtime e equivalente em poder ao controle por IA.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `EDIT-01` | **Editor Shell & Workspace** | Docking, workspaces, shortcut profiles, undo host, project manager e acessibilidade. | CORE-01 | Workspace salva/reabre, UI de múltiplos monitores com erros recuperáveis. |
| `EDIT-02` | **Project Creation & Management** | Wizard 2D/2.5D/3D/web, templates, schema upgrade e project validation. | EDIT-01 · DATA-01 | Criar projetos de todos os modos com configurações corretas. |
| `EDIT-03` | **Scene/World/Terrain Editor** | Hierarchy, gizmos, inspector, terrain brushes, prefabs, streaming cells. | EDIT-02 · WORLD-04 | Editar terreno/objetos, salvar e restaurar sem regressão. |
| `EDIT-04` | **2D & UI Editor** | Canvas, tilemap painting, UI responsive preview, animation timelines 2D. | EDIT-02 · TWO-02 | Projeto 2D completo construído pela interface sem acesso direto a arquivos. |
| `EDIT-05` | **Visual Shader & Material Graph** | Editor de materiais/nodes, shader preview, variant management. | EDIT-02 · GFX-05 | Visualizar e exportar shader/material validado. |
| `EDIT-06` | **VFX/Audio/Animation Authoring** | Sequencers, particle editor, audio graphs, state machines e timelines. | EDIT-02 · GFX-08 · AUD-04 · SIM-04 | Editor e modo runtime reproduzem mesmo conteúdo. |
| `EDIT-07` | **Debug, Profiling & Preview** | Play-in-editor, breakpoints, render debugger, stats, memory/GPU/audio inspector. | EDIT-01 · CORE-06 | Erro rastreável do projeto até subsistema e asset. |

### 11 · AI-native & MCP Integration

Toda a capacidade de autoria aprovada terá contrato versionado e testável, acessível a humano, CLI e MCP.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `AI-01` | **Headless Command Kernel** | Operações sem GUI: create/open/edit/validate/build/export; command bus tipado e versionado. | WORLD-02 · DATA-04 · GAME-02 | Mesma operação manual/CLI produz estado semanticamente igual. |
| `AI-02` | **Project Semantic Index** | Índice incremental de cenas, scripts, assets, referências, docs e schemas para agentes. | AI-01 · DATA-02 | Consultas filtradas com contexto mínimo e atualização incremental. |
| `AI-03` | **Capability Registry & Schemas** | Catálogo refletido de operações, JSON Schema, permissões, versions, errors e deprecation. | AI-01 | 100% das ações públicas de autoria enumeradas e rastreáveis. |
| `AI-04` | **MCP Server & Protocol Adapter** | Tools/resources/prompts, stdio local, HTTP remoto seguro, compatibilidade por versão. | AI-03 | Conformance test MCP e interação com hosts selecionados. |
| `AI-05` | **MCP Context Resources & Templates** | Schemas, exemplos, cenas, documentação, prompts/recipes, introspecção paginada. | AI-02 · AI-04 | Agente descobre estrutura sem copiar repositório inteiro. |
| `AI-06` | **Agent Security & Authorization** | Capabilities, workspace scopes, grants, audit logs, consent, sandbox e isolamento. | AI-04 · AI-01 | Agente não pode modificar arquivos/projetos fora do escopo. |
| `AI-07` | **Transactional Planning & Undo** | Diff preview, dry-run, changesets, atomic apply, checkpoints, rollback e conflitos. | AI-01 · AI-06 | Mudança multi-objeto pode ser revisada, revertida e repetida. |
| `AI-08` | **AI Authoring Workflows** | Recipes de cenas 2D/3D, shader, VFX, áudio, scripts, comportamento, correção e exportação. | AI-05 · AI-07 | Cenários completos gerados por tool calls com zero edição manual obrigatória. |
| `AI-09` | **AI Validation & Optimization** | Agentes executam testes visuais/funcionais, benchmarks e propõem deltas de performance. | AI-07 · CORE-06 | Relatório com antes/depois, evidência reproduzível e aprovação humana. |

### 12 · Platforms, Packaging & Runtime Targets

Mesmos dados de projeto com builds específicos e redução de recursos por plataforma.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `PLAT-01` | **Windows Desktop Target** | Window/input/GPU/audio targets, empacotamento e atualização. | GFX-01 · GAME-01 | Build e smoke test em hardware Windows definido. |
| `PLAT-02` | **Linux Desktop Target** | Distribuições/camada de compatibilidade, GPU/audio/windowing e packaging. | GFX-01 · GAME-01 | Build e smoke test em Linux definido. |
| `PLAT-03` | **Browser Runtime (WebAssembly/WebGPU/WebGL)** | Execução em navegador com targets de memória, sandbox, loading e fallbacks. | TWO-01 · GFX-01 · DATA-05 | 2D e cenário 3D browser compatíveis em browsers matriz; sem alegar 1:1 nativo. |
| `PLAT-04` | **Mobile Target Adaptation** | Input touch, orçamento bateria/termal, GPUs mobile e packaging, sujeita a validação de custo. | GFX-01 · GAME-01 | Plataformas móveis selecionadas com smoke/compatibilidade documentadas. |
| `PLAT-05` | **Build, Export & Distribution** | Export templates, assets por target, package manifests, símbolos, checksums e distribuição. | PLAT-01 · PLAT-02 · PLAT-03 · DATA-05 | Export reprodutível de aplicações aprovadas; falhas claras por target. |

### 13 · Quality, Security & Performance Engineering

Metas de qualidade são parte da especificação do produto, não um plugin instalado no fim.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `QA-01` | **Build & Continuous Integration** | Compilação multi-OS, testes, lint, format, sanitizers e registro de toolchain. | CORE-01 | CI verde em targets permitidos, builds e versões rastreáveis. |
| `QA-02` | **Automated Functional & Visual Tests** | Unitários, integração, golden images, audio tests, headless playtests e fixtures. | QA-01 · GFX-03 | Falhas de regressão reproduzíveis; tolerância documentada para drivers. |
| `QA-03` | **Performance Lab & Scalability Tiers** | CPU/GPU/VRAM budgets, frametimes, cenas de referência, GPUs acessíveis, regressão. | QA-02 · CORE-06 · GFX-08 | Benchmarks comparáveis p50/p95/p99 por hardware e quality tier. |
| `QA-04` | **Security, Fuzzing & Supply Chain** | Threat models, security gates, parsers fuzz, SBOM, licenças, incident playbooks. | QA-01 · NET-06 · AI-06 | Fuzzing e auditoria de riscos HIGH/CRITICAL antes de release. |
| `QA-05` | **Compatibility & Release Qualification** | Matriz de GPU/OS/browser, crash recovery, carga prolongada, migração e suporte. | QA-02 · PLAT-05 | Cenários de compatibilidade e recuperação aprovados por plataforma. |

### 14 · Commercial Product & Ecosystem

A engine só estará pronta para uso comercial após distribuição, documentação e acordos claros.

| ID | Proposed module | Scope | Depends on | Acceptance scenario / evidence to specify |
|---|---|---|---|---|
| `BIZ-01` | **Commercial Licensing & Compliance** | Política de licença, royalties ou não, third-party notices, IP, privacy, acessibilidade. | QA-05 | Licença aprovada e publicável, direitos de dependências/assets auditados. |
| `BIZ-02` | **SDK, Plugins & Developer Experience** | API versionada, extensões, samples, docs técnicas e portabilidade. | GAME-02 · AI-01 | Plugin/sample compatível com API publicada, teste de atualização. |
| `BIZ-03` | **Release, Installer & Lifecycle** | Installer/updates, samples originais, crash reports opt-in, rollback e suporte de manutenção. | PLAT-05 · BIZ-01 · QA-04 | Instalar/exportar/atualizar/reverter em ambientes-alvo sem intervenção de dev. |

## Release requirement model (proposed)

Each catalog item gets **Release Class** at the next planning stage:
- **MANDATORY FOR 1.0** — all acceptance tests and platform matrix must pass before any commercial/public launch. Baseline includes native 2D/2.5D/3D authoring, editor, scripting, AI/MCP coverage, Windows/Linux and Web target, audio/VFX/lighting, asset pipeline, export, security and documentation. Exact titles, depth, and constraints require owner approval in the versioned capability matrix.
- **RESEARCH / ADVANCED TECHNIQUE** — custom GI, new VFX algorithm, ray tracing, physics or audio innovations require benchmarks and ADRs; do not block 1.0 unless explicitly declared mandatory after technical proof.
- **PLATFORM CONDITIONAL** — mobile, console-specific integration and specialized vendor SDKs need explicit target, licensing, test hardware and budget decision. Mobile here is a candidate to assess, not automatic mandatory target; consoles are not promised.

**No MVP** does not mean no milestones, unit tests, vertical integration samples, pre-release builds, or internal tooling. It means no public/paid product until the agreed **complete** DoD is objectively met. All internal builds are labeled non-public engineering artifacts.

## Capability coverage matrix

| Product mode | Minimum end-to-end authored scenario to eventually prove |
|---|---|
| 2D | Top-down or platform game created with editor + agent, sprites, animations, 2D physics, audio, UI, save/load, packaged desktop/browser |
| 2.5D | Original ARPG-style demo combining 2D UI and effects with 3D geometry, camera, animation, responsive input and gameplay |
| 3D | Outdoor combat-world sample with characters, vehicles, physics, lighting, environmental audio, streaming and measurable perf |
| Web | Browser target from same project with graceful quality/feature reduction, compatibility table and explicit loading constraints |
| Multiplayer | Dedicated headless authority, client prediction/replication, reconnect/security, latency/jitter/loss testing |
| AI-native workflow | Project generated/edited/validated/exported by MCP and CLI; every authoring action has deterministic semantics, user-visible diff, permission and undo when applicable |

## Cross-cutting global invariants

1. **Accessibility:** keyboard/gamepad navigation and accessible UI, readable controls, reduced-motion options where applicable, text localization and audio/subtitle needs.
2. **Performance:** CPU frame time, GPU time, VRAM, RAM, I/O, battery when relevant, loading time, stutter and tail latency measured by hardware + scene. Tier targets are TBD, not confirmed.
3. **Security:** untrusted assets, plugins, scripts, MCP agents, network peers and project files all require threat models and least privilege.
4. **Portability:** data schemas portable; feature-tier fallback based on platform capability; don't claim web/native parity.
5. **Extensibility:** only validated public APIs, semver policy and migration paths; do not over-abstract without evidence.
6. **Resilience:** save recovery, idempotent reimports, crash-safe transactions, asset migration and reproducible builds.
7. **Original IP:** no copying proprietary engine code, game content or audiovisual assets, and no claims of invention without prior-art research.
8. **Commercial readiness:** license and legal clearance before distribution, and no subscriptions required for core authoring/CI under owner's no-cost constraint.

## Architectural dependency boundaries

- CORE and DATA are base capabilities; no dependency on editor UI or provider-specific AI APIs.
- 2D workflows have dedicated render, animation and physics rather than a 3D-only requirement.
- All rendering, animation and audio modules must be callable without the editor for testing or runtime.
- Server simulation must not depend on graphics API or editor.
- The command kernel is separate from the MCP protocol adapter; versioned protocol compatibility is tested independently.
- Commercial and QA packages depend on existing modules, but don't define game-specific rules in the Core.

## MCP-first requirement (not 'raw API exposed')

Every **approved authoring capability** must have a stable typed operation (read or mutate), discoverable schemas, authorization and validation, not an unrestricted per-module internal API. Per-operation mapping is tracked as `module -> command -> CLI -> MCP tool/resource -> editor action -> tests`. Completion requires coverage tests in both manual and AI workflows. See [AI/MCP architecture brief](ai-mcp-contract.md).

## High-risk unknowns that prevent freezing this catalog

- Choice of supported scripting languages, hot reload model, ABI and sandboxing.
- Exact native/web rendering backends, feature tiers, shader portability and browser compatibility.
- Full target platform list (mobile, consoles), legal constraints and associated test-hardware costs.
- Serialization/transaction format and authority model, multi-agent edit conflicts, asset provenance.
- Networking, anti-cheat and multiplayer capacity requirements (no invented 64-client benchmark).
- Quantitative acceptance targets for visual quality/performance and the scope of proprietary research.
- License, SDK/plugin policies, trademarks and commercial distribution agreement.

## Decisions and next steps

This module inventory is a **proposal only** and does not supersede approved Source Pack or checkpoint. Only after owner review and objective audit may its classification be reflected in Requirements, Scope, DoD and Architecture. The already planned `NLE-P00-WO-002` (technology/license research) remains unstarted; its inputs should include this catalog once approved. No engine code or assets are created in this Work Order.
