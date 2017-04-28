#ifndef BSTREE_H
#define BSTREE_H

#include <stdlib.h>
#include <string.h>

struct bstree
{
	char *key;
	int value;
	struct bstree *left;
	struct bstree *right;
};

struct bstree *bstree_create(char *key, int value);		//Создание корня дерева
void bstree_add(struct bstree *tree, char *key, int value);	//Добавление элементов в бинарное дерево поиска
struct bstree *bstree_lookup(struct bstree *tree, char *key);	//Поиск элементов в бинарном дереве и хеш-таблице
struct bstree *bstree_min(struct bstree *tree);			//Поиск минимального элемента в бинарном дереве
struct bstree *bstree_max(struct bstree *tree);			//Поиск максимального элемента в бинарном дереве

#endif
