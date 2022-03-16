
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeTrim(BSTree t, int lower, int upper);

int main(void) {
	BSTree t = readBSTree(0);
	
	printf("Enter value of lower: ");
	int lower = 0;
	while (scanf("%d", &lower) != 1) {
		printf("Enter value of lower: ");
	}
	
	printf("Enter value of upper: ");
	int upper = 0;
	while (scanf("%d", &upper) != 1) {
		printf("Enter value of upper: ");
	}
	
	printf("BST before trimming values between %d and %d:\n",
	       lower, upper);
	printBSTree(t);
	
	t = BSTreeTrim(t, lower, upper);
	
	printf("BST after trimming values between %d and %d:\n",
	       lower, upper);
	printf("=== ignored by test >>>\n");
	printBSTree(t);
	printf("<<< ignored by test ===\n");

	printf("\nInorder traversal of the BST: ");
	printBSTreeInorder(t);
	printf("\n");
	
	freeBSTree(t);
}

