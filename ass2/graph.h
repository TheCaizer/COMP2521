//Jackie Cai z5259449
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Typedef and their structs///////
// Struct of the Graph where nV is number of vertices
// and nE is number of edges and there is a matrix
// of the vertices (adjacent matrix)
typedef struct Graph{
    int nV;
    int nE;    
    int **edges;
}Graph;
typedef struct Graph *GraphPointer;
typedef int Vertice;
///Helper Functions with the Graph//////////////////
void newEdge(GraphPointer g, Vertice v, Vertice w, int value); 
int CountNodes(GraphPointer g);
void removeEdge(GraphPointer, Vertice v, Vertice w);
GraphPointer createGraph(int nV); 
void printGraph(GraphPointer g); 
int CheckConnect(GraphPointer g, Vertice v, Vertice w); 
double PointTo(GraphPointer g, Vertice v);
double PointOut(GraphPointer g, Vertice v);
double SumPointTo(GraphPointer g, Vertice v);
double SumPointOut(GraphPointer g, Vertice v);