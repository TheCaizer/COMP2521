/* Binary Search BSTree ADT interface 
   Written by Ashesh Mahidadia  
*/

#ifndef BSTree_H
#define BSTree_H

#include <stdbool.h>

/* External view of BSTree (key is of type int)
   The file BSTree.c is NOT provided for this exam.

   To simplify this exam setup, we are exposing the 
   following types to a client.
*/

#define key(tree)  ((tree)->key)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef int Key;      

typedef struct Node *BSTree;
typedef struct Node {
   int  key;
   BSTree left, right;
} Node;


BSTree newBSTree();        // create an empty BSTree
void freeBSTree(BSTree);   // free memory associated with BSTree
void showBSTree(BSTree);   // display a BSTree (sideways)
BSTree BSTreeInsert(BSTree, Key);   // insert a new key into a BSTree

BSTree  getBST(char *line);

#endif

