/* testEqualBST.c 
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int equalBST(BSTree t1, BSTree t2);

int main(int argc, char *argv[])
{
	char buffer[1024];

	char *line1 = fgets(buffer, sizeof(buffer), stdin);
	BSTree t1 = getBST(line1); 
	printf("\nDisplaying t1 (sideways) \n"); 
	showBSTree(t1);

	char *line2 = fgets(buffer, sizeof(buffer), stdin);
	BSTree t2 = getBST(line2); 
	printf("\n\nDisplaying t2 (sideways) \n"); 
	showBSTree(t2);

	char *line3 = fgets(buffer, sizeof(buffer), stdin);
	BSTree t3 = getBST(line3); 
	printf("\n\nDisplaying t3 (sideways) \n"); 
	showBSTree(t3);

	printf("\n -------  \n"); 	
	int ans1 = equalBST(t1, t2);
	fprintf(stdout, "equalBST(t1, t2) returns: %d \n", ans1);
	int ans2 = equalBST(t2, t3);
	fprintf(stdout, "equalBST(t2, t3) returns: %d \n", ans2);

	freeBSTree(t1);
	freeBSTree(t2);
	freeBSTree(t3);

	return 0;
}

