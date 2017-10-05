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
	printf("key\tvalue\t&node\t\tparent\t\tleft\t\tright\t\tcolor\n\n");

	struct rbtree *root = rbtree_add(NULL, 10, "10");
	//print_tree_full(root);
	//printf("\n");
	root = rbtree_add(root, 5, "5");
	//print_tree_full(root);
	//printf("\n");
	root = rbtree_add(root, 3, "3");
	//print_tree_full(root);

	//printf("\n");
	root = rbtree_add(root, 11, "11");
	//print_tree_full(root);

	//printf("\n");
	root = rbtree_add(root, 12, "12");
	//print_tree_full(root);

	//printf("\n");
	root = rbtree_add(root, 6, "6");
	//print_tree_full(root);

	//printf("\n");
	root = rbtree_add(root, 8, "8");
	//print_tree_full(root);

	//printf("\n");
	root = rbtree_add(root, 9, "9");
	print_tree_full(root);


	printf("\n");
	root = rbtree_delete(root, 5);
	print_tree_full(root);

	return 0;
}