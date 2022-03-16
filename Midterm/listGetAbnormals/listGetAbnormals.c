
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

List addList(List l, Node temp);

List listGetAbnormals(List l, int threshold) {
	//make new list
	List result = newList();
	//check if the size can be used to compute  the function
	//since 0,1,2 size would mean NULL is prev and next, cant compute
	if(l->size <= 2){
		return result;
	}
	//the first one doesnt matter since first prev and last next is NULL
	//therefore we can skip checking that
	Node head = l->first->next;
	//as stated before the last deosent matter since it can never be in result
	while(head != l->last){
		//check if next and prev is NULL to extra precautions
		if(head->prev != NULL || head->next != NULL){
			//check for threshold
			if(abs(head->value - head->prev->value) >= threshold && abs(head->value - head->next->value) >= threshold){
				//if it passes all condition add to list
				addList(result, head);
			}
		}
		//iterate through list
		head = head->next;
	}
	return result;
}
//Add to list
List addList(List l, Node temp){
	//make a new node with the value to not alter the list
	Node node = newNode(temp->value);
	//empty list therefore you can add it if it's condition match
	if(l->size == 0){
		l->first = node;
		l->last = node;
		l->size++;
		return l;
	}
	else{
		//adds normally
		l->last->next = node;
		//sets prev as the last node
		node->prev = l->last;
		//sets the last node in list as the new node
		l->last = node;
		l->size++;
		return l;
	}
}
