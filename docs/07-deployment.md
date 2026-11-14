# Deployment & Distribution
Status: NÃO APLICÁVEL a P00; PLANO

## Presente
Somente documentação em GitHub público e CI documental gratuito. Sem engine build, pacote instalável, site, releases binárias, servidores, custos de cloud ou deploy de runtime.

## Futuro
Planejar pipelines separados para Editor, Client, Dedicated Server e SDK; compatibilidade de OS/CPU/GPU, assinaturas se necessárias, binários e símbolos de depuração, assets, checksum e cadeia de provenance.

## Reprodutibilidade
Pinagem de compiladores, SDKs e toolchains; cache mensurável; release tags imutáveis; artefatos testados. Não publicar releases sem critérios de DoD, segurança, licenças e teste em máquina-alvo.

## Custos
É proibido introduzir serviço com faturamento obrigatório. Runners padrão em repositórios públicos são normalmente gratuitos e sem cobrança de minutos, mas sujeitos às políticas e limites técnicos do GitHub; validar condições antes de expandir o CI. Self-hosted runner só após analisar manutenção e segurança.
