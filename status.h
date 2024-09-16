#ifndef __STATUS_H__
#define __STATUS_H__

#define MAX_MESSAGE_LENGTH 256

typedef enum TipoStatus {
	ERRO = 0,
	FALHA = 1,
	SUCESSO = 2
} TipoStatus;

typedef struct {
	TipoStatus status;
	char mensagem[MAX_MESSAGE_LENGTH];
} Status;

void print_status(Status status);

#endif