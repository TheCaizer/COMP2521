// mergeOrdered.c ... implementation of mergeOrdered function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
void ListAppend(ListRep *L, int val);
/* 
    You will submit only this one file.

    Implement the function "mergeOrdered" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

List mergeOrdered(List list1, List list2){
    List new;
    new = newList();
    Node *curr1 = list1->first;
    Node *curr2 = list2->first;
    //loop through the list and compare them
    //and then add to a new list
    while(curr1 != NULL && curr2 != NULL){
        if(curr1->value <= curr2->value){
            ListAppend(new, curr1->value);
            curr1 = curr1->next;
        }
        else if(curr1->value > curr2->value){
            ListAppend(new, curr2->value);
            curr2 = curr2->next;
        }
    }
    //if one list hits NULL adds the rest of the other list
    //to the new list
    if(curr2 == NULL){
        while(curr1 != NULL){
            ListAppend(new, curr1->value);
            curr1 = curr1->next;
        }
    }
    else if(curr1 == NULL){
        while(curr2 != NULL){
            ListAppend(new, curr2->value);
            curr2 = curr2->next;
        }
    }
    return new;
}
//function just adds a new node to the end of list
void ListAppend(ListRep *L, int val){
	Node *new;
	new = newNode(val);
	if (new == NULL) {
		fprintf(stderr, "Cannot create a new node!\n");
		exit(0);
	}
	if (L->last == NULL) {
		L->first = L->last = new;
	}
	else {
		L->last->next = new;
		L->last = new;
	}
}