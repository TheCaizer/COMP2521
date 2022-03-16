// List.c  

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "list.h"

// create an empty list
List newList(){

	ListRep *L;

	L = malloc(sizeof (ListRep));
	assert (L != NULL);
	L->first = NULL;
	L->last = NULL;
	return L;
}

// create a new List node
Node *newNode(int val){

	Node *new;
	new = malloc(sizeof(Node));
	assert(new != NULL);
	new->value = val;
	new->next = NULL;
	return new;
}

// free memory for a list
void dropList(List L){

	assert(L != NULL);
	Node *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

// display a list to given file (stdout)
void showList(FILE *out, List L){

	assert(out != NULL); assert(L != NULL);
	Node *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		if(count++ > 0) {
			fprintf(out,", ");
		}
		fprintf(out,"%d",curr->value);
	}
	fprintf(out,"\n");
}



/* appends an item at the end of the list
   'current' is not changed
*/
int ListAppend321987(ListRep *L, int val){

	Node *new;
	new = newNode(val);
	if (new == NULL) {
		fprintf(stderr, "Cannot create a new node!\n");
		return 0;
	}
	if (L->last == NULL) {
		L->first = L->last = new;
	}
	else {
		L->last->next = new;
		L->last = new;
	}
	//L->nitems++;
	return 1;
}


// creates a List by reading integer values from a line 
List getList(char *line) {

	char delim[] = ", ";
	int key;

	List l = newList(); 

	char *tkn = strtok(line, delim);

	while (tkn != NULL) {
		//printf("'%s'\n", tkn);
		int count = sscanf(tkn, "%d", &key) ;
		if(count == 1) {
			int succ = ListAppend321987(l, key) ;
			if(succ == 0){ 
				fprintf(stderr, "Cannot create a new node!\n"); 
				return NULL; 
			}
		}
			
		tkn = strtok(NULL, delim);
	}

	return l;
}


