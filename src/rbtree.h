#ifndef rbtree_H
#define rbtree_H

typedef enum {
	red,
	black
} nodeColors;

typedef struct rbtree {
	int value;
	char *key;
	struct rbtree *left;
	struct rbtree *right;
	struct rbtree *parent;
	colors color;
} rbtree;


rbtree *rbtree_create(char *key, int value, rbtree *parent);

rbtree *rbtree_add(rbtree *root, char *key, int value, rbtree *parent);

//rbtree *rbtree_lookup(rbtree *root, char *key);

rbtree *rbtree_search(rbtree *node, char *key);

rbtree *rbtree_min(rbtree *root);

rbtree *rbtree_max(rbtree *root);

void print_tree(rbtree *root);

#endif