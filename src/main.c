#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "bstree.h"
#include "hashtab.h"
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
	bstree *root;
	root = bstree_create("root", rand() % 10, NULL);
	bstree *one, *two, *three;
	one = bstree_add(root, "a", 1);
	two = bstree_add(root, "zzzz", 2);
	three = bstree_add(root, "c", 3);
	
	print_tree(root);
	/*
	srand(time(0));
	FILE *text = fopen("ex3.txt", "r");
	char buf[512];
	int num = 260;
	char **str = malloc(num * sizeof(char*));
	for (int i = 0; fgets(buf, 512, text) != NULL; i++) {
		str[i] = (char*) malloc(strlen(buf) + 1);
		strcpy(str[i], buf);
	}
	//
	
	//printf("\n\nORIGINAL\n");
	//printf_array_str(str, num);
	//printf("MIX\n");
	//mix(str, num);
	//printf_array_str(str, num);
	
	//ДЕЕЕЕРЕЕЕЕВОООООО
	
	bstree *root;
	root = bstree_create(str[getrand(0, num)], getrand(0, num));
	printf("ROOT - %d : %s\n", root->value, root->key);

	for (int i = 1; i < num; i++) {
		bstree_add(root, str[i], getrand(1, num));
		if ((i + 1) % 26 == 0) {
			printf("!!!!!!!!%d\n", i + 1);

			for (int j = 0; j < 10; j++) {
				char *g = str[getrand(0, i - 10)];
				//printf("\n%s", g);
				bstree *node_search;
				double t[10];
				t[j] = wtime();
				node_search = bstree_search(root, g);
				t[j] = wtime() - t[j];
				//printf("%f\n", t[j]);
				
				if (node_search != NULL) {
					printf("НАШЕЛ -\t%d : %s", node_search->value, node_search->key);
				}
				
				if ((j + 1) == 10) {
					double avarage = 0;
					for (int k = 0; k < 10; k++) {
						avarage += t[k];
					}
					avarage /= 10;
					printf("AVARAGE :: %0.10f\n", avarage);
				}

			}
			
			
			//if (node_search != NULL) {
			//	printf("\nНАШЕЛ -\t%d : %s", node_search->value, node_search->key);
			//}
			
		}
	}
	// поиск
	
	//print_tree(root);
	printf("\n\n");
	//
	printf("\n\n");
	bstree *min_node = bstree_min(root);
	if (min_node != NULL) {
		printf("Минимальный узел -\t%d : %s", min_node->value, min_node->key);
	}
	//
	bstree *max_node = bstree_max(root);
	if (max_node != NULL) {
		printf("Максимальный узел -\t%d : %s", max_node->value, max_node->key);
	}
	
	//ХЭЭЭЭЭЭЩ ТАБЛИИИИИИИЦАААА
	
	listnode **hashtab = malloc(SIZE_ARR * sizeof(listnode*));
	hashtab_init(hashtab);
	//hashtab_add(hashtab, str[getrand(0, num)], getrand(0, num));
	printf("\n\n");
	
	for (int i = 0; i < num; i++) {
		int v = getrand(0, num);
		hashtab_add(hashtab, str[i], v);
	}
	for (int i = 1; i < num; i++) {
		int v = getrand(0, num);
		hashtab_add(hashtab, str[i], v);
		if ((i + 1) % 26 == 0) {
			printf("!!!!!!!!%d\n", i + 1);

			for (int j = 0; j < 10; j++) {
				char *g = str[getrand(0, i - 10)];
				//printf("\n%s", g);
				listnode *node_search;
				double t[10];
				t[j] = wtime();
				node_search = hashtab_lookup(hashtab, g);
				t[j] = wtime() - t[j];
				printf("%.10f\n", t[j]);
				
				if ((j + 1) == 10) {
					double avarage = 0;
					for (int k = 0; k < 10; k++) {
						avarage += t[k];
					}
					avarage /= 10;
					printf("AVARAGE :: %.10f\n", avarage);
				}
				
				if (node_search != NULL) {
					printf("\nНАШЕЛ -\t%d : %s", node_search->value, node_search->key);
				}
				
			}
		}
	}
	
	//кол-во колизий
	
	int count[num];
	int m = 0;
	for (int i = 0; i < num; i++) {
		count[i] = hashtab_hash(str[i]);
		if ((i + 1) % 10000 == 0) {
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < i; k++) {
					if (j != k) {
						if (count[j] == count[k]) {
							m++;
						}
					}
				}
			}
			printf("%d () %d\n", i, m);
			m = 0;
		}
	}
	
	//printf("%d\n", m);
	
	for (int i = 0; i < SIZE_ARR; i++) {
		listnode *tmp_node = hashtab[i];
		while (tmp_node) {
			printf("%d :=: %s\t", hashtab_hash(tmp_node->key), tmp_node->key);
			tmp_node = tmp_node->next;
		}
		printf("\n");
	}
	
	
	listnode *search_node = hashtab_lookup(hashtab, "морской\n");
	if (search_node != NULL) {
		printf("\nSearch:\n%d : %s", search_node->value, search_node->key);
	}
	
	hashtab_delete(hashtab, "морской\n");
	
	listnode *search_node_1 = hashtab_lookup(hashtab, "морской\n");
	if (search_node_1 != NULL) {
		printf("%d : %s", search_node_1->value, search_node_1->key);
	}
	
	//
	//free(root);
	free_str(str, num);
	free(str);
	
	fclose(text);
	*/
	return 0;
}

