# Banco-de-Dados-C-Lua
Fazer um banco de dados Chave-valor no estilo Redis ou Memcached.

Contém apenas 2 comandos

- **ADD** chave valor ⇒ Adiciona dado no Banco

- **GET** chave ⇒ Busca chave no Banco

Este banco é feito em C. Foi estendido o banco de dados com a VM do LUA e feito:

## Sistema de extensões:
  - Todas as chamadas vem ser passadas à VM do Lua. O código C não precisa saber quais funções foram incluídas.
  - Todas as transformações devem retornar sucesso ou erro como resultado final
  - Retorno de transformações: Se a extensão tiver uma transformação que dados ou cálculo. Deve-se retornar este valor em uma estrutura específica do C
  - Estruturas de erro: Se algum dado ou entrada for inválido ou se a operação não for possível, além de retornar falso na função, explica-se o motivo do insucesso. Deve-se retornar este valor em uma estrutura específica do C

## Extensão: Validador de CPF
  - **ADD:** Se a chave for no formato 'cpf_*’, deve-se validar se dígito verificador do CPF é válido. A entrada deve ser feita em apenas com os 11 números, sem formatação. http://clubes.obmep.org.br/blog/a-matematica-nos-documentos-a-matematica-dos-cpfs
  - **GET:** formatar o cpf para o formato: "000.000.000-00”

Exemplo:

1. ADD cpf_zezinho 12345678900
2. GET cpf_zezinho => 123.456.789-00

## Extensão: Formatador de Data
  - **ADD:** Se a chave for no formato 'data_’, validar formato de data em ISO8601 (2022-10-23)
  - **GET:** Formatar no formato brasileiro dd/mm/aaaa

Exemplo:

1. ADD data_nascimento_zezinho 2000-01-23
2. GET data_nascimento_zezinho => 23/01/2021

## Desenvolvedores
Carolina Gimenez

Eduarda Medeiros

Gustavo Pagnotta
