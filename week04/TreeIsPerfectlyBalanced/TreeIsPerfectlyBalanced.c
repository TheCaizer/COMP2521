
#include <stdlib.h>

#include "tree.h"

int height(Tree t, bool *isBpointer);

bool TreeIsPerfectlyBalanced(Tree t) {
	if(t == NULL){
		return true;
	}
	bool isB = true;
	bool *isbpointer = &isB;
	height(t, isbpointer);
	return isB;
}

int height(Tree t,bool *isBpointer){
	if(t == NULL){
		return 0;
	}
	int lDepth = height(t->left, isBpointer);
	int rDepth = height(t->right, isBpointer);
	int diff = lDepth - rDepth;
	if(diff > 1 || diff < -1){
		*isBpointer = false;
	}
	return 1 + lDepth + rDepth;
}