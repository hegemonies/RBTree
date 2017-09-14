#ifndef BSTREE_H
#define BSTREE_H

typedef enum {
	red,
	black
} colors;

typedef struct bstree {
	int value;
	char *key;
	struct bstree *left;
	struct bstree *right;
	struct bstree *parent;
	colors color;
} bstree;

//typedef struct bstree bstree_t;

bstree *bstree_create(char *key, int value, bstree *parent);

bstree *bstree_add(bstree *tree, char *key, int value, bstree *parent);

//bstree *bstree_lookup(bstree *tree, char *key);

bstree *bstree_search(bstree *node, char *key);

bstree *bstree_min(bstree *tree);

bstree *bstree_max(bstree *tree);

void print_tree(bstree *tree);

#endif
