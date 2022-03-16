// List.h - Interface to singly-linked list ADT

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/* External view of List (item is of type int).
   The file List.c is NOT provided for this exam.

   To simplify this exam setup, we are exposing the 
   following types to a client.
*/


typedef struct _list_rep *List;

typedef struct _node {
   int value;
   struct _node *next;
} Node;

typedef struct _list_rep {
   Node *first;
   Node *last;
} ListRep;


// create an empty list
List newList();

// create a new List node
Node *newNode(int val);

// free memory for a list
void dropList(List);

// display a list to given file (stdout)
void showList(FILE *out, List L);


// creates a List by reading integer values from a line 
List getList(char *line);


// zip two lists into one
List zipList(List, List);

#endif
