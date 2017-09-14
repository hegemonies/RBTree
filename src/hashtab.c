#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtab.h"
#define SIZE_ARR 50

int hashtab_hash(char *key)
{
	int hash = 0;
	for (int i = 0; i < strlen(key); i++) {
		hash = (hash * 127 + key[i]) % SIZE_ARR;
	}
	return abs(hash);
}

void hashtab_init(struct listnode **hashtab)
{
	for (int i = 0; i < SIZE_ARR; i++) {
		hashtab[i] = NULL;
	}
}

void hashtab_add(struct listnode **hashtab, char *key, int value)
{
	int index = hashtab_hash(key);
	//printf("%d\n", index);
	listnode *node = malloc(sizeof(*key));
	if (node != NULL) {
		node->key = key;
		node->value = value;
		node->next = hashtab[index];
		hashtab[index] = node;
		//printf("%d :: %p :: %p :: %s\n", node->value, hashtab[index], node->next, node->key);
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key)
{
	int index = hashtab_hash(key);
	listnode *node;
	for (node = hashtab[index]; node != NULL; node = node->next) {
		if (strcmp(node->key, key) == 0) {
			return node;
		}
	}
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key)
{
	int index = hashtab_hash(key);
	listnode *p;
	listnode *prev = NULL;
	for (p = hashtab[index]; p != NULL; p = p->next) {
		if (strcmp(p->key, key) == 0) {
			if (prev == NULL) {
				hashtab[index] = p->next;
			} else {
				prev->next = p->next;
			}
			free(p);
			return;
		}
		prev = p;
	}
}
