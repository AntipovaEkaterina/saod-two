#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

#define HASHTAB_SIZE 10000
#define HASHTAB_MUL  10

unsigned int hashtab_hash(char *key) {
	unsigned int h = 0;
	char *p;
	for(p = key; *p != '\0'; p++) {
	   h = h * HASHTAB_MUL + (int)p;
	}
	return h % HASHTAB_SIZE;
}

unsigned add_hash(char *key, int len) {
	unsigned h = 0;
	char *p = key;
	int i;
	for(i = 0; i < len; i++)
		h += p[i];
	return h % HASHTAB_SIZE;
}

void hashtab_init(struct listnode **hashtab) {
	int i;
	for(i = 0; i< HASHTAB_SIZE; i++) 
	  hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, char *key, int value, int *col) {
	struct listnode *node, *search;
	int index = add_hash(key, strlen(key));
	//int index = hashtab_hash(key);
	node = malloc(sizeof(*node));
	if (node != NULL) {
	node->key = key;
	node->value = value;
	if (hashtab[index] == NULL) {
		node->next = hashtab[index];
		hashtab[index] = node;
	} 
	else {
		*col=*col+1;
		for (search = hashtab[index]; search; search = search->next) {
			if (search->next == NULL) {
				search->next = node;
				node->next = NULL;
				break;
				}
			}
		}
	}
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key){
	int index;
	struct listnode *node;
	index = add_hash(key, strlen(key));
	//index = hashtab_hash(key);
	node = hashtab[index];
        while(node != NULL){
	if(strcmp(node->key, key) == 0)
		return node;
	node = node->next;
	}
	return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key) {
	int index;
	struct listnode *p, *prev = NULL;
	index = hashtab_hash(key);
	for(p = hashtab[index]; p != NULL; p = p->next) {
		if(strcmp(p->key,key) == 0) {
			if(prev == NULL)
				hashtab[index] = p->next;
			else
				prev->next = p->next;
			free(p);
			return;
		}
		prev = p;
	}
}

void hashprint(struct listnode **hashtab, char *key) {
	struct listnode *node;
	int index = hashtab_hash(key);
	for(node = hashtab[index]; node != NULL; node = node->next){
		printf("%s", node->key);
	}
}
