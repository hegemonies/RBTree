#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rbtree.h"

rbtree *rbtree_create(int key, char *value, rbtree *parent)
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

rbtree *rbtree_add(rbtree *root, int key, char *value) {
	struct rbtree *node = root, *parent = NULL;
		
	while (node != NULL) {
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

void rbtree_delete(rbtree *root, int key)
{
	rbtree *node, *parent, *left, *right;
	rbtree *node_look, *node_look_left, *node_look_right;
	int flag = 1;

	node = rbtree_lookup(root, key);

	left = node->left;
	right = node->right;

	while (flag == 1) {
		flag = 0;
		parent = node->parent;

		if (left == NULL && right == NULL) {
			if (key < parent->key) {
				parent->left = NULL;
			} else if (key > parent->key) {
				parent->right = NULL;
			}
		} else if (left != NULL && right == NULL) {
			if (key < parent->key) {
				parent->left = left;
			} else if (key > parent->key) {
				parent->right = left;
			}
			left->parent = parent;
		} else if (right != NULL && left == NULL) {
			if (key < parent->key) {
				parent->left = right;
			} else if (key > parent->key) {
				parent->right = right;
			}
			right->parent = parent;
		} else if (left != NULL && right != NULL && right->left == NULL) {
			if (key < parent->key) {
				parent->left = right;
			} else if (key > parent->key) {
				parent->right = right;
			}
			right->left = left;
			right->parent = parent;
		} else if (left != NULL && right != NULL) {
			node_look = right;
			while (node_look->left == NULL) {
				node_look = node_look->right;
			}
			node = node_look->left;

			if (parent != NULL && key < parent->key) {
				parent->left = node;
			} else if (parent!= NULL && key > parent->key) {
				parent->right = node;
			} else if (parent == NULL) {
				root = node;
			}

			node_look_left = node_look->left->left;
			node_look_right = node_look->left->right;

			node_look->left->left = left;
			node_look->left->right = right;

			left = node_look_left;
			right = node_look_right;
			flag = 1;
		}
	}
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
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

rbtree *rbtree_max(rbtree *node)
{
	while (node->right !=  NULL) {
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
	rbtree *test;
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
					test = rbtree_rotate_left(node);
					if (test->parent == NULL) {
						root = test;
						printf("%d\n", root->key);
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				test = rbtree_rotate_right(node->parent->parent);
				if (test->parent == NULL) {
					root = test;
					printf("%d\n", root->key);
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
					test = rbtree_rotate_right(node);
					if (test->parent == NULL) {
						root = test;
						printf("%d\n", root->key);
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				test = rbtree_rotate_left(node->parent->parent);
				if (test->parent == NULL) {
					root = test;
					printf("%d\n", root->key);
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
    if (node == NULL) {
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
