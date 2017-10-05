#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rbtree.h"

struct rbtree EmptyNode = {"0", 0, NULL, NULL, NULL, black};
struct rbtree *NullNode = &EmptyNode;

rbtree *rbtree_create(int key, char *value, rbtree *parent)
{
	rbtree *b = malloc(sizeof(rbtree));
	if (b == NULL) {
		return NULL;
	}
	b->key = key;
	b->value = value;
	b->color = red;
	b->left = NullNode;
	b->right = NullNode;
	b->parent = parent;

	return b;
}

rbtree *rbtree_add(rbtree *root, int key, char *value) {
	struct rbtree *node = root, *parent = NULL;
		
	while (node != NullNode && node != NULL) {
		parent = node;
		if (key < node->key) {
			node = node->left;
		} else if (key > node->key) {
			node = node->right;
		} else {
			return root;
		}
	}

	node = rbtree_create(key, value, parent);
	if (node == NULL) {
		return root;
	}

	if (root == NULL) {
		root = node;
		root->color = black;
		return root;
	} else if (key < parent->key) {
		parent->left = node;
	} else if (key > parent->key) {
		parent->right = node;
	}
	root  = rbtree_fixup(root, node);

	return root;
}

rbtree *rbtree_delete(rbtree *tree, int key)
{
	rbtree *node, *node_trans;
	nodeColors node_color;

	node = rbtree_lookup(tree, key);
	if (node == NULL) {
		printf("Error, not element\n");
		return tree;
	}
	node_color = node->color;

	if (node->left != NULL && node->right == NullNode) {
		node_trans = node->left;
		tree = rbtree_transplant(tree, node, node->left);
	} else if (node->right != NULL && node->left == NullNode) {
		node_trans = node->right;
		tree = rbtree_transplant(tree, node, node->right);
	} else {
		rbtree *node_old = node;
		node = rbtree_min(node->right);
		node_color = node->color;
		node_trans = node->right;

		if (node->parent == node_old) {
			node_trans->parent = node;
		} else {
			tree = rbtree_transplant(tree, node, node->right);
			node->right = node_old->right;
			node->right->parent = node;
		}
		tree = rbtree_transplant(tree, node_old, node);
		node->left = node_old->left;
		node->left->parent = node;
		node->color = node_old->color;
	}
	if (node_color == black) {
		tree = rbtree_delete_fixup(tree, node_trans);
	}
	return tree;
}

rbtree *rbtree_delete_fixup(rbtree *tree, rbtree *node)
{
	rbtree *test;
	while (node != tree && node->color == black) {
		if (node == node->parent->left) {
			rbtree *node_br = node->parent->right;
			if (node_br != NULL && node_br->color == red) {
				node_br->color = black;
				node->parent->color = red;
				test = rbtree_rotate_left(node->parent);
				if (test->parent == NULL) {
					tree = test;
				}
				node_br = node->parent->right;
			}
			if (node_br->left->color == black && node_br->right->color == black) {
				node_br->color = red;
				node = node->parent;
			} else {
				if (node_br->right->color == black) {
					node_br->left->color = black;
					node_br->color = red;
					test = rbtree_rotate_right(node_br);
					if (test->parent == NULL) {
						tree = test;
					}
					node_br = node->parent->right;
				}
				node_br->color = node->parent->color;
				node->parent->color = black;
				node_br->right->color = black;
				test = rbtree_rotate_left(node->parent);
				if (test->parent == NULL) {
					tree = test;
				}
				node = tree;
			}
		} else {
			rbtree *node_br = node->parent->left;
			if (node_br != NULL && node_br->color == red) {
				node_br->color = black;
				node->parent->color = red;
				test = rbtree_rotate_right(node->parent);
				if (test->parent == NULL) {
					tree = test;
				}
				node_br = node->parent->left;
			}

			if (node_br->left->color == black && node_br->right->color == black) {
				node_br->color = red;
				node = node->parent;
			} else {
				if (node_br->left->color == black) {
					node_br->right->color = black;
					node_br->color = red;
					test = rbtree_rotate_left(node_br);
					if (test->parent == NULL) {
						tree = test;
					}
					node_br = node->parent->left;
				}
				node_br->color = node->parent->color;
				node->parent->color = black;
				node_br->left->color = black;
				test = rbtree_rotate_right(node->parent);
				if (test->parent == NULL) {
					tree = test;
				}
				node = tree;
			}
		}

	}
	node->color = black;

	return tree;
}

rbtree *rbtree_transplant(rbtree *root, rbtree *node, rbtree *new_node)
{
	if (node->parent == NULL) {
		root = new_node;
	} else if (node == node->parent->left) {
		node->parent->left = new_node;
	} else {
		node->parent->right = new_node;
	}
	if (new_node != NULL) {
		new_node->parent = node->parent;
	}

	return root;
}

rbtree *rbtree_lookup (rbtree *root, int key)
{
	rbtree *node = root;

	while (node != NULL) {
		if (key == node->key) {
			return node;
		} else if (key < node->key) {
			node = node->left;
		} else if (key > node->key) {
			node = node->right;
		}
	}
	
	return node;
}

rbtree *rbtree_min(rbtree *node)
{
	while (node->left != NullNode) {
		node = node->left;
	}
	return node;
}

rbtree *rbtree_max(rbtree *node)
{
	while (node->right !=  NullNode) {
		node = node->right;
	}
	return node;
}

void print_tree(rbtree *node)
{
    if (node == NULL) {
    	return;
    }
    print_tree(node->left);
    printf("%d : %s\n", node->key, node->value);
    print_tree(node->right);
}

rbtree *rbtree_fixup(rbtree *root,	rbtree *node)
{
	rbtree *tmp;
	while (node->parent != NULL && node->parent->color == red) {
		if (node->parent == node->parent->parent->left) {//левое поддерево
			rbtree *uncle = node->parent->parent->right;
			if (uncle != NULL && uncle->color == red) {//дядя красный -> 1 случай
				node->parent->color = black;
				uncle->color = black;
				node->parent->parent->color = red;
				node = node->parent->parent;
			} else {
				if (node == node->parent->right) {
					node = node->parent;
					tmp = rbtree_rotate_left(node);
					if (tmp->parent == NULL) {
						root = tmp;
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				tmp = rbtree_rotate_right(node->parent->parent);
				if (tmp->parent == NULL) {
					root = tmp;
				}
			}
		} else {
			rbtree *uncle = node->parent->parent->left;
			if (uncle != NULL && uncle->color == red) {//дядя красный, узел справа - 4 случай
				node->parent->color = black;
				node->parent->parent->color = red;
				uncle->color = black;
				node = node->parent->parent;
			} else {
				if (node == node->parent->left) {
					node = node->parent;
					tmp = rbtree_rotate_right(node);
					if (tmp->parent == NULL) {
						root = tmp;
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				tmp = rbtree_rotate_left(node->parent->parent);
				if (tmp->parent == NULL) {
					root = tmp;
				}
			}
		}
	}
	root->color = black;
	return root;
}

rbtree *rbtree_rotate_left(rbtree *node)
{
	rbtree *des = node->right;
	node->right = des->left;
	if (des->left != NULL) {
		des->left->parent = node;
	}
	des->parent = node->parent;
	if (node->parent != NULL) {
		if (node->parent->left == node) {
			node->parent->left = des;
		} else {
			node->parent->right = des;
		}
	} else {
		des->parent = node->parent;
	}

	des->left = node;
	node->parent = des;
	return des;
}

rbtree *rbtree_rotate_right(rbtree *node)
{
	rbtree *des = node->left;
	node->left = des->right;
	if (des->right != NULL) {
		des->right->parent = node;
	}
	des->parent = node->parent;
	if (node->parent != NULL) {
		if (node->parent->right == node) {
			node->parent->right = des;
		} else {
			node->parent->left = des;
		}
	} else {
		des->parent = node->parent;
	}
	des->right = node;
	node->parent = des;
	return des;
}

void print_tree_full(rbtree *node)
{
    if (node == NULL || node == NullNode) {
    	return;
    }
    print_tree_full(node->left);
    printf("%d\t%s\t%p\t", node->key, node->value, node);
    if (!node->parent) {
    	printf("%p\t\t", node->parent);
    } else {
    	printf("%p\t", node->parent);
    }
    if (!node->left) {
    	printf("%p\t\t", node->left);
    } else {
    	printf("%p\t", node->left);
    }
    if (!node->right) {
    	printf("%p\t\t", node->right);
    } else {
    	printf("%p\t", node->right);
    }
    if (node->color == red) {
    	printf("red\n");
    } else {
    	printf("black\n");
    }
    print_tree_full(node->right);
}