#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bstree.h"

bstree *bstree_create(char *key, int value, bstree *parent)
{
	bstree *b = malloc(sizeof(bstree));
	if (b == NULL) {
		return NULL;
	}
	b->key = key;
	b->value = value;
	b->color = red;
	b->left = NULL;
	b->right = NULL;
	b->parent = parent;
	return b;
}

bstree *_bstree_add(bstree *tree, char *key, int value, bstree *parent)
{
	if (tree == NULL) {
		tree = bstree_create(key, value, parent);
	} else if (strcmp(key, tree->key) < 0) {
		tree->left = bstree_add(tree->left, key, value, tree);
	} else if (strcmp(key, tree->key) > 0){
		tree->right = bstree_add(tree->right, key, value, tree);
	}
	return tree;
}

bstree *bstree_search(bstree *node, char *key)
{
	while (node) {
		char *tmp = malloc(strlen(key) + 1);
		strcpy(tmp, key);
		tmp[(strlen(key))] = '\0';
		int num = strcmp(tmp, node->key);
		if (num < 0) {
			free(tmp);
			node = node->left;
			continue;
		}
		if (num > 0) {
			free(tmp);
			node = node->right;
			continue;
		}
		if (num == 0) {
			free(tmp);
			return node;
		}
	}
	return NULL;
}

bstree *bstree_min(bstree *tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->left != NULL) {
		//printf("Иду на лево\n");
		tree = tree->left;
	}
	return tree;
}

bstree *bstree_max(bstree *tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->right !=  NULL) {
		//printf("Иду на право\n");
		tree = tree->right;
	}
	return tree;
}

void print_tree(bstree *tree)
{
    if (tree == NULL) {
    	return;
    }
    print_tree(tree->left);
    printf("%d : %s\n", tree->value, tree->key);
    print_tree(tree->right);
}
