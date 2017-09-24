#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rbtree.h"

rbtree *rbtree_create(char *key, int value, rbtree *parent)
{
	rbtree *b = malloc(sizeof(rbtree));
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
/*
rbtree *_rbtree_add(rbtree *tree, char *key, int value, rbtree *parent)
{
	if (tree == NULL) {
		tree = rbtree_create(key, value, parent);
	} else if (strcmp(key, tree->key) < 0) {
		tree->left = rbtree_add(tree->left, key, value, tree);
	} else if (strcmp(key, tree->key) > 0){
		tree->right = rbtree_add(tree->right, key, value, tree);
	}
	return tree;
}
*/

rbtree *RBT_add(rbtree *root, char *key, int value)
{
	if (!root) {
		root = rbtree_create(key, value, NULL);
		return root;
	}
	rbtree *node = root;
	rbtree *parent;
	while (node) {
		if (!strcmp(key, tree->key)) {
			break;
		}
		if (strcmp(key, tree->key) < 0) {
			parent = node;
			node = node->left;
			parent->left = node;
		} else {
			parent = node;
			node = node->right;
			parent->right = node;
		}
		
		//node = strcmp(key, tree->key) < 0 : node->left ? node->right;
	}
	node = rbtree_create(key, value, parent);
	
}

rbtree *rbtree_search(rbtree *node, char *key)
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

rbtree *rbtree_min(rbtree *tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->left != NULL) {
		//printf("Иду на лево\n");
		tree = tree->left;
	}
	return tree;
}

rbtree *rbtree_max(rbtree *tree) {
	if (tree == NULL) {
		return NULL;
	}
	while (tree->right !=  NULL) {
		//printf("Иду на право\n");
		tree = tree->right;
	}
	return tree;
}

void print_tree(rbtree *tree)
{
    if (tree == NULL) {
    	return;
    }
    print_tree(tree->left);
    printf("%d : %s\n", tree->value, tree->key);
    print_tree(tree->right);
}