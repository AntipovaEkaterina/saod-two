#ifndef myHashTab
#define myHashTab

#include <string.h>
#include <stdlib.h>

#define HASHTAB_MUL 31
#define HASHTAB_SIZE 40960

unsigned int KP_Hash(char *key);
unsigned int ADD_Hash(void *key);

struct listnode *hashtab[HASHTAB_SIZE];

struct listnode
{
	char *key;
	int value;
	struct listnode *next;
};

void hashtab_init(struct listnode **hashtab);

void hashtab_add(struct listnode **hashtab, char *key, int value, int mode); //Добавление элементов в хеш-таблицу
/*
Mode:
1:	KP_Hash
0:	ADD_Hash
*/

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key, int mode); //Поиск элементов в хеш-таблице

void hashtab_delete(struct listnode **hashtab, char *key, int mode);

#endif
