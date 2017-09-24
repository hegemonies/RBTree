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
	rbtree *root;
	root = rbtree_create("root", rand() % 10, NULL);
	rbtree *one, *two, *three;
	one = rbtree_add(root, "a", 1);
	two = rbtree_add(root, "zzzz", 2);
	three = rbtree_add(root, "c", 3);
	
	print_tree(root);
	
	return 0;
}