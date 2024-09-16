#include "status.h"
#include <stdio.h>

void print_status(Status status) {
	switch((int)status.status) {
		case (int)ERRO:
			printf("ERRO: %s\n", status.mensagem);
			break;
		case (int)FALHA:
			printf("FALHA: %s\n", status.mensagem);
			break;
		case (int)SUCESSO:
			printf("SUCESSO: %s\n", status.mensagem);
			break;
	}
}