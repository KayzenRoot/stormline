# Architecture (conceptual)
Status: PROPOSED / NOT IMPLEMENTED

## Organização candidata
Applications (Editor / Client / Server / Test harness)
-> Public Engine API + World Runtime
-> Renderer, Physics, Animation, Audio, Networking, Terrain/Streaming, VFX
-> Core services (memory, jobs, logging, time, I/O, diagnostics)
-> Platform abstraction (Windows/Linux, CPU/GPU/OS).

## Princípios
- Engine própria; bibliotecas especializadas são dependências substituíveis quando isso tiver valor demonstrável.
- Servidor sem GPU/UI obrigatória; editor não deve controlar o ciclo de vida da simulação.
- Contratos explícitos para ownership, serialização, ID estável, tempo, coordenadas, assets e plugins.
- API pública não deve expor tipos de terceiros indiscriminadamente; evitar abstração sem evidência de necessidade.
- Tempo de simulação desacoplado do render; políticas de fixed step a definir.
- Posição global vs local, precisão de mapas grandes e origem deslocável a avaliar.
- Testabilidade e ferramentas de profiling desde o início.

## Stack candidato; NÃO aprovado
C++20, Vulkan, SDL3, Jolt, EnTT, miniaudio, glTF, meshoptimizer, Python, CMake, compilador de shaders e biblioteca de transporte sob avaliação. Matriz de licença, versão, suporte, performance e complexidade precede escolha definitiva.

## Pesquisa de inovação
Renderização e iluminação, VFX, áudio e hardware modesto merecerão ADRs e experimentos independentes; provar ganhos visuais e eficiência em cenas comparáveis. Não declarar tecnologia inédita sem pesquisa de anterioridade.

## Proposta AI-first em avaliação
A nova direção de produto exige avaliar um **Command Kernel** comum ao editor, CLI/headless e adaptador MCP, com contratos estáveis e auditáveis. Esta orientação está descrita como proposta em [AI/MCP Contract](product/ai-mcp-contract.md), não como sistema já projetado/implementado. A revisão técnica deverá considerar a especificação MCP 2026-07-28, backward compatibility, ferramentas/resources/prompts e segurança por capability/permission.

## CORE-01 — Platform & Lifecycle (pesquisa técnica PROPOSTA)
A direção preferencial de pesquisa é C++20 + SDL3 + CMake Presets/Ninja, com Win32, Wayland/X11 e Cocoa/Objective-C++ encapsulados em bridges estreitas quando necessário. A interface de host deve funcionar também sem display/GPU. SAPL (capability graph + event journal) é hipótese a medir, e **não** inovação comprovada. A decisão está apenas PROPOSED em [ADR-0003](adr/0003-core-01-platform-technology.md), com [contratos de plataforma](architecture/core-01-platform-lifecycle.md) e [matriz de tecnologias](research/core-01-platform-technology-matrix.md). A escolha gráfica Metal/Vulkan/D3D12 pertence a GFX-01, fora desta WO.

## CORE-02 — Memory & Allocators (pesquisa PROPOSTA)
Arquitetura de memória C++20 `std::pmr` com ownership, domains e budgets versionados; comparadores `malloc/new`, mimalloc e rpmalloc antes de qualquer substituição global. Hipótese de inovação `Stormline Memory Fabric` restrita a políticas e diagnósticos mensuráveis, não um malloc reinventado. Ver [CORE-02](architecture/core-02-memory-allocators.md), [matriz](research/core-02-memory-technology-matrix.md), [ADR-0004](adr/0004-core-02-memory-policy.md). GPU VRAM pertence ao módulo GFX-03. Nenhuma tecnologia de produção aprovada sem benchmark.

## CORE-03 — Jobs & Concurrency (proposta de pesquisa)
Scheduler de tarefas, execução paralela e work stealing com contratos de duração/cancelamento de jobs, afinidades, deterministic commit e quotas para hardware de poucos núcleos. Candidatos: C++20 `std::jthread`, Taskflow, enkiTS e oneTBB; avaliar Stormline Frame-Aware Scheduler somente se superioridade funcional/operacional for demonstrada. [Spec](architecture/core-03-concurrency-jobs.md), [matriz](research/core-03-technology-matrix.md), [ADR-0005](adr/0005-core-03-jobs-concurrency.md). Sem código ou benchmark.

## Gates
Arquitetura executável dependerá de NLE-P00-WO-003+ e aceite formal. Definições de rede, segurança, persistência e compatibilidade antecedem integração.
