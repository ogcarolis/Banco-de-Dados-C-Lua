#include "extensao_lua.h"

Resposta verifica_cpf(const char* cpf);
Resposta verifica_data(const char* data);

Resposta f (lua_State* L, const char* string, char* funcao);

lua_State* lua_start();

lua_State* lua_start() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "script.lua");

	return L;
}

Resposta verifica_cpf(const char* cpf) {
	lua_State* L = lua_start();
	Resposta res = f(L, cpf, "validarCPF");
	lua_close(L);
	return res;
}

Resposta verifica_data(const char* data) {
	lua_State* L = lua_start();
	Resposta res = f(L, data, "validarData");
	lua_close(L);
	return res;
}

Resposta f (lua_State* L, const char* string, char* funcao) {
	lua_getglobal(L, funcao);
	lua_pushstring(L, string);

	Status status = {ERRO, ""};
	Resposta resposta = {status, ""};
	
	if (lua_pcall(L, 1, 1, 0) != 0) {
		snprintf(status.mensagem, sizeof(status.mensagem), "error running function %s: %s", funcao, lua_tostring(L, -1));
		lua_pop(L, 1); 
		resposta.status = status;
		return resposta;
	}

	if (!lua_istable(L, 1) != 0) {
		snprintf(status.mensagem, sizeof(status.mensagem), "function %s must return a table", funcao);
		lua_pop(L, 1);
		resposta.status = status;
		return resposta;
	}

	// RESPOSTA = { valido (1), cpf_formatado (2), mensagem (3) }
	lua_getfield(L, -1, "valido");
	int valido = lua_toboolean(L, -1);
	lua_pop(L, 1);

	status.status = valido ? SUCESSO : FALHA;

	lua_getfield(L, -1, "mensagem");
	const char* mensagem = lua_tostring(L, -1);
	if (mensagem) {
		strncpy(status.mensagem, mensagem, sizeof(status.mensagem) - 1);
		status.mensagem[sizeof(status.mensagem) - 1] = '\0';
	}
	lua_pop(L, 1);

	resposta.status = status;

	lua_getfield(L, -1, "formatado");
	const char* formatado = lua_tostring(L, -1);
	if (formatado) {
		resposta.formatado = strdup(formatado);
	}
	lua_pop(L, 1);

	lua_pop(L, 1);
	
	return resposta;
}

void liberar_resposta(Resposta* resposta) {
	free(resposta->formatado);
	resposta->formatado = NULL;
}