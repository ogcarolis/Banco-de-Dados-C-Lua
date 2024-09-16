// https://codereview.stackexchange.com/questions/63427/simple-key-value-store-in-c
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "extensao_lua.h"
#include "command.h"
#include "kvs.h"

int main(int argc, char *argv[]) {
  char input[100];
  KVSstore *banco;

  // Inicializando KVS
  banco = kvs_create();

  printf("Execute algum comando. Exemplos:\n");
  printf("- ADD chave valor ---> Adiciona o valor na chave\n");
  printf("- GET chave ---> Retorna o valor da chave se existir\n");
  printf("- EXIT --->  sair do programa\n");
  printf("CHAVES:\n");
  printf("- cpf_(nome)\n");
  printf("- data_(nome)\n");

  while (1) {
    // Imprime e mantém na mesma linha
    printf("> ");
    fflush(stdout);
    gets(input);

    Command command = get_command(input);

    // se igual, strcmp == 0
    if (!strcmp(command.command, "EXIT")) {
      printf("Fechando...\n");
      break;
    } else if (!strcmp(command.command, "ADD")) {
      Status status = kvs_put(banco, command.key, command.value);
      print_status(status);
      if (status.status == ERRO) {
        break;
      }
    } else if (!strcmp(command.command, "GET")) {
      char *value = kvs_get(banco, command.key);
      printf("%s\n", value);
    } else {
      printf("Comando não reconhecido!\n");
    }
  }

  kvs_destroy(banco);
  return 0;
}