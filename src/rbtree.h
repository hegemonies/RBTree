#ifndef RBTREE_H
#define RBTREE_H

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

//struct rbtree EmptyNode = {0, 0, NULL, NULL, NULL, black};
//struct rbtree *NullNode = &EmptyNode; 


rbtree *rbtree_create(int key, char *value, rbtree *parent);

rbtree *rbtree_add(rbtree *root, int key, char *value);

rbtree *rbtree_delete(rbtree *root, int key);

rbtree *rbtree_transplant(rbtree *root, rbtree *node, rbtree *new_node);

rbtree *rbtree_delete_fixup(rbtree *root, rbtree *node);

rbtree *rbtree_lookup (rbtree *root, int key);

rbtree *rbtree_min(rbtree *root);

rbtree *rbtree_max(rbtree *root);

void print_tree(rbtree *root);

rbtree *rbtree_fixup(rbtree *root,	rbtree *node);

rbtree *rbtree_rotate_left(rbtree *node);

rbtree *rbtree_rotate_right(rbtree *node);

void print_tree_full(rbtree *node);

#endif