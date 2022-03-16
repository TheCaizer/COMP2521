
#include <stdlib.h>

#include "BSTree.h"

#include<stdio.h>

BSTree getkth (BSTree t, int *i, int *arr);
int size_tree(BSTree t);

int BSTreeGetKth(BSTree t, int k) {
	int *arr = (int *)malloc(size_tree(t) * sizeof(int));
	int index = 0;
	int *i = &index;
	getkth(t, i, arr);
	int result = arr[k];
	free(arr);
	return result;
}

BSTree getkth (BSTree t, int *i, int *arr){
	if(t == NULL){
		return NULL;
	}
	getkth(t->left, i, arr);
	arr[*i] = t->value;
	*i += 1;
	getkth(t->right, i ,arr);
	return t;
}

int size_tree(BSTree t){
	if(t == NULL){
		return 0;
	}
	return 1 + size_tree(t->left) + size_tree(t->right);
}