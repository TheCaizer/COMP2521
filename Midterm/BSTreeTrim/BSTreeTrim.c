
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"
BSTree minNode(BSTree node);
BSTree deleteNode(BSTree t, int value);

BSTree BSTreeTrim(BSTree t, int lower, int upper){
	//Base Case
	if(t == NULL){
		return NULL;
	}
	//Iterate through the tree and starts checking from the bottom right (lowest value)
	t->left = BSTreeTrim(t->left, lower, upper);
	t->right = BSTreeTrim(t->right, lower, upper);
	//checks the condition for deleting node
	if(t->value >= lower && t->value <= upper){
		//takes the tree and the value that needs to be deleted
		return deleteNode(t, t->value);
	}
	//if he node doesnt have to be deleted returns the tree
	return t;
}
//Deletes a node after you find its within given range
BSTree deleteNode(BSTree t, int value){ 
    //Base case 
    if(t == NULL){
		return t;
	} 
    // Checks the value within the node if its less than the value
    if(value < t->value){ 
		//recursively finds the node, if it is less than the value then
		//the value would be in the left sub-tree
        t->left = deleteNode(t->left, value); 
	}
    // checks the value within the node if it is greater than the value
    else if(value > t->value){
		//recursively finds the node, if it is greater than the value then
		//the value would be in the right sub-tree
        t->right = deleteNode(t->right, value); 
	}
    // If the node value is equal to the value then you need to delete it
    else{ 
		//Checks if there are child nodes within the tree
		//If there is one child, left or right is NULL 
		if (t->left == NULL){ 
			//Stores the right child in a temp node
			BSTree temp = t->right; 
			//deletes the node
			free(t); 
			//returns the right child which replaces the node that has 
			//been deleted
			return temp; 
		}
		//same as above but for left child
		else if(t->right == NULL){ 
			BSTree temp = t->left; 
			free(t); 
			return temp; 
		}
		// Node with two child, will search for the smallest value in the 
		// right subtree as it would be less than all values in the right subtree
		// but greater than the values in the left subtree. It can replace the node
		// being deleted 
		BSTree temp = minNode(t->right); 
		// Copy value into the node
		t->value = temp->value; 
		//replaces the right subtree with the same subtree
		// but deletes the value from the right subtree that was copied
		t->right = deleteNode(t->right, temp->value); 
    }
	//return tree
    return t; 
}
//Finds the smallest value within a tree
BSTree minNode(BSTree node){
	//current pointer
    BSTree curr = node; 
    //as long as left is not NULL iterates through to find the
	//left most subtree
    while(curr != NULL && curr->left != NULL){ 
        curr = curr->left; 
	}
	//returns
    return curr; 
}

BSTree count(BSTree t, int val){
    if(t == NULL){
        return 0;
    }
    else if(t->value >= val){
        return count(t->left, val);
    }
    else{
        return 1 + count(t->left, val) + count(t->right, val);
    }
}