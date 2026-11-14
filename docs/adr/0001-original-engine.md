# ADR-0001: Original engine and specialized libraries
Date: 2026-11-14 | Status: OWNER-APPROVED DIRECTION

## Contexto
A NexLabs deseja uma engine própria, não fork obrigatório de Unreal/Godot/O3DE. Objetivos incluem controle arquitetural, inovação em lighting/VFX/audio e alto desempenho.

## Decisão
Construir motor original e integrar bibliotecas especializadas sob contratos e auditoria de licença/segurança. Não reinventar indiscriminadamente física, windowing, codecs e transporte sem prova de necessidade.

## Alternativas
Fork de engine aberta; criar todas as bibliotecas do zero; solução original com componentes especializados (selecionada).

## Consequências
Maior investimento de engenharia, controle e flexibilidade; exigirá disciplina de interfaces, interoperabilidade, testes e manutenção. Stack exato permanece PROPOSED e depende da avaliação de P00.
