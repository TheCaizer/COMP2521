//Jackie Cai z5259449
//Some helper code from lectures
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"
#include "readData.h"

// Function to count the number of vertices
int CountNodes(GraphPointer g){
    return g->nV;
}
// make a new edge between vertice v and vertice w
//where value is the value between the edges
void newEdge(GraphPointer g, Vertice v, Vertice w, int value){
    //make sure it's empty
    if (g->edges[v][w] == 0) {
        g->edges[v][w] = value;
        //add to number of edge
        g->nE++;
    }
}
// Removes a edge between v and w
void removeEdge(GraphPointer g, Vertice v, Vertice w){
    //check there is an edge there
    if (g->edges[v][w] != 0){
        g->edges[v][w] = 0;
        g->nE--;
    }
}
// create an new empty graph given number of vetices
GraphPointer createGraph(int nV){
    //check for valid number of vertices
    if(nV <= 0){
        printf("Not a valid vertice");
        return NULL;
    }
    GraphPointer new = malloc(sizeof(GraphPointer));
    if(new == 0){
        printf("Not enough memory");
        return NULL;
    }
    new->nV = nV; 
    new->nE = 0;
    new->edges = malloc(nV*sizeof(int *));
    if(new->edges == 0){
        printf("Not enough memory");
        return NULL;
    }
    int v = 0;
    while(v < nV){
        int w = 0;
        new->edges[v] = malloc(nV*sizeof(int));
        //loop through all the edges
        while(w < nV){
            new->edges[v][w] = 0;
            w++;
        }
        v++;
    }
    return new;
}
//Print the graph 
void printGraph(GraphPointer g){
    if(g == NULL){
        printf("Cant Print Empty Graph");
        exit(0);
    }
    int v = 0;
    while(v < g->nV){
        int w = 0;
        while(w < g->nV){
            printf("%d ",g->edges[v][w]);
            w++;
        }
        v++;
    }
}
// check if two vertices are connected and return value
int CheckConnect(GraphPointer g, Vertice v, Vertice w){
    return (g->edges[v][w]);
}
//return the number of vertices pointing to a vertices
double PointTo(GraphPointer g, Vertice v){
    int i = 0; 
    double nums = 0;
    while(i < g->nV){
        if(g->edges[i][v]){
            nums++;
        }
        i++;
    }
    //if 0 it is 0.5
    if(nums == 0){
        return 0.5;
    }
    else{
        return nums;
    }
}
//return number of vertices pointing out of a vertoces
double PointOut(GraphPointer g, Vertice v){
    int i = 0;; 
    double nums = 0; 
    while(i < g->nV){
        if(g->edges[v][i]){
            nums++;
        }
        i++;
    }
    //if its 0 the value is 0.5
    if(nums == 0){
        return 0.5;
    }
    else{
        return nums;
    }
}
//return the sum of vertices pointing to v
double SumPointTo(GraphPointer g, Vertice v){
    int i = 0;
    double sum = 0; 
    while(i < g->nV){
        if(g->edges[v][i]){
            sum = sum + PointTo(g,i);
        }
        i++;
    }
    return sum;
}
//return the sum of vertices pointing out of v
double SumPointOut(GraphPointer g, Vertice v){
    int i = 0;
    double sum = 0;
    while(i < g->nV){
        if(g->edges[v][i]){
            sum = sum + PointOut(g, i);
        }
        i++;
    }
    return sum;
}