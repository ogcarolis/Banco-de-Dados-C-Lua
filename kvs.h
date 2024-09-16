#ifndef __KVS_H__
#define __KVS_H__

#include <stdlib.h>
#include <string.h>
#include "extensao_lua.h"
#include "status.h"

// https://www.inf.pucrs.br/~pinho/LaproI/Structs/Structs.htm
typedef struct {
	const void *key;
	void *value;
} KVSpair;

typedef struct {
	KVSpair *pairs;
	size_t length;
} KVSstore;

KVSstore *kvs_create(void);

void kvs_destroy(KVSstore *store);

Status kvs_put(KVSstore *store, const char *key, char *value);

void *kvs_get(KVSstore *store, const void *key);

#endif /* #define __KVS_H__ */