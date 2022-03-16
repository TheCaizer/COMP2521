// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DLList.h"

int main (void)
{
	/*DLList List = getDLList (stdin);
	putDLList (stdout, List);
	assert (validDLList (List));*/

	// TODO: more tests needed here
	printf("Creating a newDLList\n");
	DLList List1 = newDLList();
	printf("Testing Empty list\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 0);
	assert(DLListCurrent (List1) == NULL);
	printf("DLList is valid and succeeded creating new list with no node\n");

	printf("Testing DLListBefore\n");
    printf("Inserting lines \"Hello My name is Jim \"\n");
	DLListBefore(List1,"Hello My name is Jim");

	printf("Checking number of nodes is 1 and the current node.\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 1);
	assert(strcmp(DLListCurrent (List1),"Hello My name is Jim")== 0);
    printf("Success\n");

	printf("Test current node is the first node\n");
    printf("Inserting lines \"Nice to meet you\"\n");
	DLListBefore(List1,"Nice to meet you");
    
    printf("Checking number of nodes is 2 and the current nodes.\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 2);
	assert(strcmp(DLListCurrent (List1),"Nice to meet you")== 0);
    
    printf("Moving current node to 2\n");
    DLListMoveTo (List1, 2);
    assert(strcmp(DLListCurrent (List1),"Hello My name is Jim")== 0);
    printf("Success\n");
	
	printf("Checking command on last node\n");
    printf("Inserting \"Goodbye for now\" while in last node\n");
    DLListBefore(List1,"Goodbye for now");
	
	printf("Checking number of nodes is 3 and the current node.\n");
	assert(validDLList(List1));
    assert(DLListLength(List1) == 3);
    assert(strcmp(DLListCurrent (List1),"Goodbye for now")== 0);
	printf("Success and DLListBefore works fines\n");  

	printf("Testing DLListAfter\n");
    printf("Creating new second list\n");

	DLList List2 = newDLList();
	
	printf("Checking second List is valid and is empty\n");
    assert(validDLList(List2));
	assert(DLListLength(List2) == 0);
	assert(DLListCurrent (List2) == NULL);
    
    printf("Success\n");

	printf("Testing Empty List\n");
    printf("Inserting line \"Who Am I?\" in empty List\n");
	DLListAfter(List2,"Who Am I?");
	
    printf("Checking number of nodes is 1 and list is valid\n");
    assert(validDLList(List2));
	assert(DLListLength(List2) == 1);
	assert(strcmp(DLListCurrent (List2),"Who Am I?") == 0);
    printf("Success\n");
    
    printf("Testing DLListAfter when current node is last node\n");
    printf("Inserting line \"None of your business\"when current is in last node\n");
	DLListAfter(List2,"None of your business");
    
    printf("Checking list is valid and number of node is 2\n");
    assert(validDLList(List2));
	assert(DLListLength(List2) == 2);
	assert(strcmp(DLListCurrent (List2),"None of your business")== 0);
    
    printf("Moving current node to 1\n");
    DLListMoveTo (List2, 1);
    assert(strcmp(DLListCurrent (List2),"Who Am I?")== 0);
    printf("Success\n");
    
    printf("Test DLListAfter in first node\n");
    printf("Inserting line \"Stop asking questions\" while current is first node\n");
    DLListAfter(List2,"Stop asking questions");
    
    printf("Checking number of node is 3 and list is valid\n");
	assert(validDLList(List2));
    assert(DLListLength(List2) == 3);
    assert(strcmp(DLListCurrent (List2),"Stop asking questions") == 0);  
    printf("Success and DLListAfter works fine\n");

	printf("Testing List1 contains 3 nodes and is valid");
	assert(validDLList(List1));
	assert(DLListLength(List1) == 3);
	printf("Testing DLListDelete\n");
    DLListDelete(List1);
	
    printf("Testing List1 contains 2 nodes and is valid\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 2);
	assert(strcmp(DLListCurrent (List1),"Hello My name is Jim") == 0);
	printf("Deleting another node\n");
	DLListDelete(List1);
	
    printf("Testing List1 contains 1 nodes and is valid\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 1);
	assert(strcmp(DLListCurrent (List1),"Nice to meet you") == 0);

	printf("Deleting last node\n");
	DLListDelete(List1);
	
    printf("Testing List1 contains 0 nodes and is valid\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 0);
	assert((DLListCurrent (List1)) == NULL);

	printf("Testing delete with empty list\n");
	printf("Testing List1 contains 0 nodes and is valid\n");
    assert(validDLList(List1));
	assert(DLListLength(List1) == 0);
	assert((DLListCurrent (List1)) == NULL);
	printf("DLListDelete works fine\n");
	printf("All functions work fine\n");

	freeDLList (List1);
	freeDLList (List2);
	return EXIT_SUCCESS;
}
