
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List listGetAbnormals(List l, int threshold);

static void checkRules(NodeData *oldNodeData, NodeData *newNodeData);

int main(void) {
	printf("> Enter list: ");
	List l = readList();
	NodeData *lNodeDataBefore = getListNodeData(l);

	printf("> Enter threshold: ");
	int threshold = 0;
	scanf("%d", &threshold);
	assert(threshold >= 0);

	printf("\n-----------------\n");
	printf(">> Original list:\n");
	printList(l);
	
	printf("\n>> Threshold: %d", threshold);
	printf("\n-----------------\n");
	
	
	List abnormals = listGetAbnormals(l, threshold);
	NodeData *lNodeDataAfter = getListNodeData(l);
	printf(">> Abnormals:\n");
	if (abnormals == NULL) {
		printf("NULL\n");
	} else {
		printList(abnormals);
		checkValidity(abnormals);
	}

	checkRules(lNodeDataBefore, lNodeDataAfter);

	free(lNodeDataBefore);
	free(lNodeDataAfter);
	freeList(l);
	freeList(abnormals);
}

static void checkRules(NodeData *oldNodeData, NodeData *newNodeData) {
	if (!notModified(oldNodeData, newNodeData)) {
		printf("Error: You modified the original list. You must not "
		       "modify the original list.\n");
	}
}

