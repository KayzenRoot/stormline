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

## Gates
Arquitetura executável dependerá de NLE-P00-WO-003+ e aceite formal. Definições de rede, segurança, persistência e compatibilidade antecedem integração.
