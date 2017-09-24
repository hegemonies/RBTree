#ifndef rbtree_H
#define rbtree_H

typedef enum {
	red,
	black
} nodeColors;

typedef struct rbtree {
	char *value;
	int key;
	struct rbtree *left;
	struct rbtree *right;
	struct rbtree *parent;
	nodeColors color;
} rbtree;


rbtree *rbtree_create(int key, char *value, rbtree *parent);

rbtree *rbtree_add(rbtree *root, int key, char *value);

void rbtree_delete(rbtree *root, int key);

rbtree *rbtree_lookup (rbtree *root, int key);

rbtree *rbtree_min(rbtree *root);

rbtree *rbtree_max(rbtree *root);

void print_tree(rbtree *root);

void rbtree_fixup(rbtree *root,	rbtree *node);

void rbtree_rotate_left(rbtree *node);

void rbtree_rotate_right(rbtree *node);

void print_tree_full(rbtree *node);

#endif