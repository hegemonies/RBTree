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

rbtree *rbtree_delete(rbtree *root, int key)
{
	rbtree *node = rbtree_lookup(root, key);
	rbtree *save = node;
	rbtree *new_node;
	nodeColors save_color = save->color;

	if (node->left == NULL) {
		new_node = node->right;
		root = rbtree_transplant(root, node, node->right);
	} else if (node->right == NULL) {
		new_node = node->left;
		root = rbtree_transplant(root, node, node->left);
	} else {
		save = rbtree_min(node->right);
		save_color = save->color;
		new_node = save->right;
		if (save->parent == node) {
			new_node->parent = save;
		} else {
			root = rbtree_transplant(root, save, save->right);
			save->right = node->right;
			save->right->parent = save;
		}
		root = rbtree_transplant(root, node, save);
		save->left = node->left;
		save->left->parent = save;
		save->color = node->color;
	}
	if (save_color == black) {
		if (new_node == NULL) {
			new_node = rbtree_create(0, 0, node->parent);
			new_node->color = black;
		}
		rbtree_delete_fixup(root, new_node);
	}
	return root;
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

rbtree *rbtree_delete_fixup(rbtree *root, rbtree *node)
{
	rbtree *test;
	while (node != root && node->color == black) {
		if (node == node->parent->left) {
			rbtree *brother = node->parent->right;
			if (brother != NULL && brother->color == red) {
				brother->color = black;
				node->parent->color = red;
				test = rbtree_rotate_left(node->parent);
				if (test->parent == NULL) {
					root = test;
				}
				brother = node->parent->right;
			}
				if (brother->left->color == black && brother->right->color == black) {
					brother->color = red;
					node = node->parent;
				} else {
					if (brother->right->color == black) {
						brother->left->color = black;
						brother->color = red;
						test = rbtree_rotate_right(brother);
						if (test->parent == NULL) {
							root = test;
						}
						brother = node->parent->right;
					}
					brother->color = node->parent->color;
					node->parent->color = black;
					brother->right->color = black;
					test = rbtree_rotate_left(node->parent);
					if (test->parent == NULL) {
						root = test;
					}
					node = root;
				}
		} else {
			rbtree *brother = node->parent->right;
			if (brother != NULL && brother->color == red) {
				brother->color = black;
				node->parent->color = red;
				test = rbtree_rotate_right(node->parent);
				if (test->parent == NULL) {
					root = test;
				}
				brother = node->parent->left;
			}

			if (brother == NULL) {
				brother = rbtree_create(0, 0, node->parent);
				brother->color = black;
				brother->parent->right = brother;
			}
			if (brother->left == NULL) {
				brother->left = rbtree_create(0, 0, brother);
				brother->left->color = black;
			}
			if (brother->right == NULL) {
				brother->right = rbtree_create(0, 0, brother);
				brother->right->color = black;
			}

			if (brother->left->color == black && brother->right->color == black) {
				brother->color = red;
				node = node->parent;
			} else {
				if (brother->left->color == black) {
					brother->right->color = black;
					brother->color = red;
					test = rbtree_rotate_left(brother);
					if (test->parent == NULL) {
						root = test;
					}
					brother = node->parent->left;
				}
				brother->color = node->parent->color;
				node->parent->color = black;
				brother->left->color = black;
				test = rbtree_rotate_right(node->parent);
				if (test->parent == NULL) {
					root = test;
				}
				node = root;
			}
		}

	}
	node->color = black;

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
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				test = rbtree_rotate_right(node->parent->parent);
				if (test->parent == NULL) {
					root = test;
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
					}
				}
				node->parent->color = black;
				node->parent->parent->color = red;
				test = rbtree_rotate_left(node->parent->parent);
				if (test->parent == NULL) {
					root = test;
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
