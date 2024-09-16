#include "kvs.h"

static const size_t kvs_pair_size = sizeof(KVSpair);
static const size_t kvs_store_size = sizeof(KVSstore);

static int kvs_sort_compare(const void *a, const void *b) {
  const KVSpair *pairA = a;
  const KVSpair *pairB = b;
  return strcmp((const char *)pairA->key, (const char *)pairB->key);
}

static int kvs_search_compare(const void *key, const void *element) {
  const KVSpair *pair = element;
  return strcmp((const char *)key, (const char *)pair->key);
}

static KVSpair *kvs_get_pair(KVSstore *store, const void *key) {
  if ((!store) || (!store->pairs)) {
    return NULL;
  }
  return bsearch(key, store->pairs, store->length, kvs_pair_size,
                 kvs_search_compare);
}

static void kvs_resize_pairs(KVSstore *store) {
  if (!store) {
    return;
  }
  store->pairs = realloc(store->pairs, kvs_pair_size * store->length);
}

static void kvs_sort_pairs(KVSstore *store) {
  if ((!store) || (!store->pairs)) {
    return;
  }
  qsort(store->pairs, store->length, kvs_pair_size, kvs_sort_compare);
}

static void kvs_create_pair(KVSstore *store, const void *key, void *value) {
	if (!store) {
		return;
	}
	++store->length;
	kvs_resize_pairs(store);

	KVSpair *pair = &store->pairs[store->length - 1];

	pair->key = malloc(strlen((const char *)key) + 1);
	strcpy((char *)pair->key, (const char *)key);

	pair->value = malloc(strlen((const char *)value) + 1);
	strcpy((char *)pair->value, (const char *)value);

	kvs_sort_pairs(store);
}

static void kvs_remove_pair(KVSstore *store, KVSpair *pair) {
	if ((!store) || (!pair)) {
		return;
	}

	free((void *)pair->key);
	free(pair->value);
	pair->key = NULL;
	pair->value = NULL;

	kvs_sort_pairs(store);
	--store->length;
	kvs_resize_pairs(store);
}

KVSstore *kvs_create(void) {
  KVSstore *store = malloc(kvs_store_size);
  store->pairs = NULL;
  store->length = 0;
  return store;
}

void kvs_destroy(KVSstore *store) {
	if (!store) {
		return;
	}
	if (store->pairs) {
		for (size_t i = 0; i < store->length; ++i) {
			free((void *)store->pairs[i].key);
			free(store->pairs[i].value);
		}
		free(store->pairs);
	}
	free(store);
}

Status kvs_put(KVSstore *store, const char *key, char *value) {
  KVSpair *pair = kvs_get_pair(store, key);
  Status status = {ERRO, ""};
  if (pair) {
		if (strncmp(key, "cpf_", strlen("cpf_")) == 0) {
			
			if (value) {
				Resposta resposta = verifica_cpf(value);
				
				status = resposta.status;
				if (status.status == SUCESSO) {
					free(pair->value);
					pair->value = malloc(strlen((const char *)resposta.formatado) + 1);
					strcpy((char *)pair->value, (const char *)resposta.formatado);
				}

				liberar_resposta(&resposta);
			} else {
				kvs_remove_pair(store, pair);
				status.status = SUCESSO;
				strcpy(status.mensagem, "Chave removida");
			}

		} else if (strncmp(key, "data_", strlen("data_")) == 0) {
			if (value) {
				Resposta resposta = verifica_data(value);

				status = resposta.status;
				if (status.status == SUCESSO) {
					free(pair->value);
					pair->value = malloc(strlen((const char *)resposta.formatado) + 1);
					strcpy((char *)pair->value, (const char *)resposta.formatado);
				}

				liberar_resposta(&resposta);
			} else {
				kvs_remove_pair(store, pair);
				status.status = SUCESSO;
				strcpy(status.mensagem, "Chave removida");
			}
		} else {
			status.status = FALHA;
			strcpy(status.mensagem, "Chave inválida");
		}
    
  } else if (value) {
    if (strncmp(key, "cpf_", strlen("cpf_")) == 0) {
      Resposta resposta = verifica_cpf(value);

      status = resposta.status;

      if (status.status == SUCESSO)
        kvs_create_pair(store, key, resposta.formatado);

			liberar_resposta(&resposta);
    } else if (strncmp(key, "data_", strlen("data_")) == 0) {
			Resposta resposta = verifica_data(value);

			status = resposta.status;
			
			if (status.status == SUCESSO)
      	kvs_create_pair(store, key, resposta.formatado);
			
			liberar_resposta(&resposta);
    } else {
      status.status = FALHA;
			strcpy(status.mensagem, "Chave inválida");
    }
  }
	else {
		status.status = FALHA;
		strcpy(status.mensagem, "É necessário adicionar um valor");
	}

  return status;
}

/////// GET
void *kvs_get(KVSstore *store, const void *key) {
  KVSpair *pair = kvs_get_pair(store, key);
  return pair ? pair->value : NULL;
}