
#include "list.h"

Node AddNode(Node curr, Node new);

List listSetDifference(List l1, List l2) {
	List diff = newList();
	Node curr1 = l1->head;
	
	while(curr1 != NULL){
		Node currf = l2->head;
		bool in_l2 = false;
		while(currf != NULL){
			if (curr1->value == currf->value){
				in_l2 = true;
			}
			currf = currf->next;
		}
		if(in_l2 == false){
			diff->head = AddNode(diff->head, newNode(curr1->value));
		}
		curr1 = curr1->next;
	}
	return diff;
}

Node AddNode (Node curr, Node new){
	if(curr == NULL){
		return new;
	}
	curr->next = AddNode(curr->next, new);
	return curr;
}