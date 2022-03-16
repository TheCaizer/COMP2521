// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/* 
    You will submit only this one file.

    Implement the function "rankPopularity" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - You can add static helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/
double inDegree(Graph g, int src);
double outDegree(Graph g, int src);
int dfsPathCheck(Graph g, int v, int dest);
int hasPathDFS(Graph g, int src, int dest);
int *visited;

void rankPopularity(Graph g, int src, double *mnV) {
	int i;
    int j;
    visited = calloc (g->nV, sizeof (int));
    int numV = g->nV;
    for(i = 0; i < numV;i++){
        if(hasPathDFS(g, src, i) == 1){
            mnV[i] = inDegree(g, i)/outDegree(g, i);
        }
    }
    mnV[src] = inDegree(g, src)/outDegree(g, src);
    free(visited);
}
//finds the number of degree going in
double inDegree(Graph g, int src){
    double count = 0;
    int i;
    int numV = g->nV;
    for(i = 0;i < numV;i++){
        if(adjacent(g, i, src)){
            count++;
        }
    }
    return count;
}
//finds the number of degree going out
double outDegree(Graph g, int src){
    double count = 0;
    int i;
    int numV = g->nV;
    for(i = 0;i < numV;i++){
        if(adjacent(g, src, i)){
            count++;
        }
    }
    if(count == 0){
        return 0.5;
    }
    else{
        return count;
    }
}
//depth first search from lecture
int dfsPathCheck(Graph g, int v, int dest){
    visited[v] = 1;
    int w;
    for (w = 0; w < g->nV; w++) {
        if (!g->edges[v][w]) continue;
        if (w == dest) return 1; // found path
        if (!visited[w]) {
            if (dfsPathCheck(g, w, dest)){
                return 1;
            }
        }
    }
    return 0; // no path from v to dest
}
int hasPathDFS(Graph g, int src, int dest){
    int i;
    for (i = 0; i < g->nV; i++)
        visited[i] = 0;
    return dfsPathCheck (g, src, dest);
}
