// Implementation of the BST ADT using an AVL tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Time.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Time time;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};

////////////////////////////////////////////////////////////////////////
// Function Prototypes

static void doFree(Node n);
static Node doInsert(Node n, Time time);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Time time);
static Node search_prev_node(Node t, Time time);
static Node search_c_node(Node t, Time time);

////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

// Creates a new empty tree
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

// Frees all memory associated with the given tree
void TreeFree(Tree t) {
    doFree(t->root);
    free(t);
}

static void doFree(Node n) {
    if (n != NULL) {
        doFree(n->left);
        doFree(n->right);
        TimeFree(n->time);
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Insertion

// Inserts  a  copy of the given time into the tree if it is not already
// in the tree
void TreeInsert(Tree t, Time time) {
    t->root = doInsert(t->root, time);
}

static Node doInsert(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    // insert recursively
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsert(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, time);
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return n;
    }

    // insertion done
    // correct the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));
    //add code
    if (height(n->left) - height(n->right) > 1){
        if (TimeCmp(time, n->left->time) > 0){
            n->left = rotateLeft(n->left);
            n = rotateRight(n);
        } else{
            n = rotateRight(n);
        }
    }
    else if(height(n->right) - height(n->left) > 1){
        if (TimeCmp(time, n->right->time) < 0){
            n->right = rotateRight(n->right);
            n = rotateLeft(n);
        } else{
            n = rotateLeft(n);
        }
    }

    return n;
}

static Node newNode(Time time) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    n->time = TimeCopy(time);
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Rotates  the  given  subtree left and returns the root of the updated
// subtree.
static Node rotateLeft(Node n) {
    if (n == NULL){
        return n;
    }
    Node n2 = n->right;
    if(n2 == NULL){
        return n;
    }
    n->right = n2->left;
    n2->left = n;
    if (height(n->left) > height(n->right)){
        n->height = height(n->left) + 1;
    } else{
        n->height = height(n->right) + 1;
    }
    if(height(n2->left) > height(n2->right)){
        n2->height = height(n2->left) + 1;
    } else{
        n2->height = height(n2->right) + 1;
    }
    return n2;
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
    if (n == NULL){
        return n;
    }
    Node n2 = n->left;
    if(n2 == NULL){
        return n;
    }
    n->left = n2->right;
    n2->right = n;

    if (height(n->left) > height(n->right)){
        n->height = height(n->left) + 1;
    } else{
        n->height = height(n->right) + 1;
    }
    if(height(n2->left) > height(n2->right)){
        n2->height = height(n2->left) + 1;
    } else{
        n2->height = height(n2->right) + 1;
    }
    return n2;
}

// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////
// Specialised Operations

// Returns the latest time in the tree that is earlier than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeFloor(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    Node prev = search_prev_node(t->root, time);
    if(prev == NULL){
        return NULL;
    }
    return prev->time;
}

static Node search_prev_node(Node t, Time time){
    if(t == NULL){
        return NULL;
    }
    Time ceiling = time;
    Node largest = NULL;
    if(TimeCmp(t->time, ceiling) > 0){
        largest = search_prev_node(t->left, time);
    } else if(TimeCmp(t->time, ceiling) < 0){
        largest = search_prev_node(t->right, time);
    }
    if(TimeCmp(t->time, ceiling) > 0 && largest == NULL){
        return NULL;
    }
    if(largest == NULL || (TimeCmp(t->time, largest->time) > 0 && TimeCmp(t->time, ceiling) < 0)){
        return t;
    }
    else{
        return largest;
    }
}

// Returns the earliest time in the tree that is later than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeCeiling(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    Node prev = search_c_node(t->root, time);
    if(prev == NULL){
        return NULL;
    }
    return prev->time;
}

static Node search_c_node(Node t, Time time){
    if(t == NULL){
        return NULL;
    }
    Time floor = time;
    Node smallest = NULL;
    if(TimeCmp(t->time, floor) > 0){
        smallest = search_c_node(t->left, time);
    } else if(TimeCmp(t->time, floor) < 0){
        smallest = search_c_node(t->right, time);
    }
    if(TimeCmp(t->time, floor) < 0 && smallest == NULL){
        return NULL;
    }
    if(smallest == NULL || (TimeCmp(t->time, smallest->time) < 0 && TimeCmp(t->time, floor) > 0)){
        return t;
    }
    else{
        return smallest;
    }
}

////////////////////////////////////////////////////////////////////////
// Printing

//////////////////
// List the items

static void doList(Node n);

void TreeList(Tree t) {
    doList(t->root);
}

static void doList(Node n) {
    if (n != NULL) {
        doList(n->left);
        TimeShow(n->time);
        printf("\n");
        doList(n->right);
    }
}

///////////////////////////
// Show the tree structure

typedef unsigned long long uint64;
static void doShow(Node n, int level, uint64 arms);

void TreeShow(Tree t) {
    if (t->root != NULL && t->root->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(t->root, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Node n, int level, uint64 arms) {
    if (n == NULL) return;

    TimeShow(n->time);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        // if (n->left != NULL) {
        //     for (int i = 0; i <= level; i++) {
        //         if ((1LLU << i) & arms) {
        //             printf("│     ");
        //         } else {
        //             printf("      ");
        //         }
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// Testing
// All  functions below exist for testing purposes ONLY. Do NOT use them
// in your code.

static Node doInsertLeaf(Node n, Time time);

void TreeRotateLeftAtRoot(Tree t) {
    t->root = rotateLeft(t->root);
}

void TreeRotateRightAtRoot(Tree t) {
    t->root = rotateRight(t->root);
}

void TreeInsertLeaf(Tree t, Time time) {
    t->root = doInsertLeaf(t->root, time);
}

static Node doInsertLeaf(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsertLeaf(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsertLeaf(n->right, time);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    return n;
}
