#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "rbtree.h"
#include <time.h>
#include <sys/time.h>
#define SIZE_ARR 50

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void mix(char **str, const int n)
{
	int tmp = n - 1;
	for (int i = 0; tmp > 0; i++) {
		int rand_i = getrand(0 , tmp - 1);
		char *buf = str[tmp];
		str[tmp] = str[rand_i];
		str[rand_i] = buf;
		tmp--;
	}
}

void printf_array_str(char **str, int num)
{	
	FILE *f = fopen("total.txt", "w");
	for (int i = 0; i < num; i++) {
		fprintf(f, "%p : %d : %s", str[i], i + 1, str[i]);
	}
	printf("\n\n");
	fclose(f);
}

void free_str(char **str, int num)
{
	for (int i = 0; i < num; i++) {
		free(str[i]);
	}
}

int main()
{
	srand(time(0));

	rbtree *root = rbtree_create(10, "10", NULL);
	rbtree *one = rbtree_add(root, 5, "1");
	rbtree *two = rbtree_add(root, 6, "2");
	rbtree *three = rbtree_add(root, 11, "3");

	printf("%d :: %s :: %p :: %p :: %p :: %p\n", root->key, root->value, root, root->parent, root->left, root->right);
	printf("%d :: %s :: %p :: %p :: %p :: %p\n", one->key, one->value, one, one->parent, one->left, one->right);
	printf("%d :: %s :: %p :: %p :: %p :: %p\n", two->key, two->value, two, two->parent, two->left, two->right);
	printf("%d :: %s :: %p :: %p :: %p :: %p\n", three->key, three->value, three, three->parent, three->left, three->right);

	print_tree(root);

	rbtree_delete(root, 10);

	if (root) {
		printf("\n\n%d :: %s :: %p :: %p :: %p :: %p\n", root->key, root->value, root, root->parent, root->left, root->right);
		if (one) {
			printf("%d :: %s :: %p :: %p :: %p :: %p\n", one->key, one->value, one, one->parent, one->left, one->right);
		}
		if (two) {
			printf("%d :: %s :: %p :: %p :: %p :: %p\n", two->key, two->value, two, two->parent, two->left, two->right);
		}
		if (three) {
			printf("%d :: %s :: %p :: %p :: %p :: %p\n", three->key, three->value, three, three->parent, three->left, three->right);
		}
	}
	
	print_tree(root);
	
	return 0;
}