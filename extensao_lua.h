#ifndef __EXTENSAO_LUA_H__
#define __EXTENSAO_LUA_H__

#include <stdlib.h>
#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "status.h"

typedef struct {
	Status status;
	char* formatado;
} Resposta;

Resposta verifica_cpf(const char* cpf);
Resposta verifica_data(const char* data);
void liberar_resposta(Resposta* resposta);


#endif /* #define __KVS_H__ */