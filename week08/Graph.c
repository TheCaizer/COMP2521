// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);
	int gsize = g->nV;
	int **gmatrix = g->edges;
	int isFound = 0;
	// create new queue
	Queue toVisit = newQueue();
	// create array to store previous vertex
	Vertex *isVisited = malloc((unsigned long)gsize * sizeof(Vertex));
	// Use -1 to mark a visited vertex since 0 is vertex
	for (int i = 0; i < gsize; i++)
		isVisited[i] = -1;
	// add current vertex (src) into queue 
	QueueJoin(toVisit, src);
	isVisited[src] = -404;
    // while queue is not empty, (breadth first search)
	while (!isFound && !QueueIsEmpty(toVisit)) {
		// dequeue 
		Vertex curr = QueueLeave(toVisit);
		if (curr == dest)
			isFound = 1;
		// add adjacent vertices of current vertex to queue
		for (int i = 0; i < gsize; i++) {
			// if weight of edge is bigger than max, do not add to queue
			if (isVisited[i] == -1 && gmatrix[curr][i] < max && curr != i) {
				// if vertex i is not visited (0), and weight of edge is less than max
                // and previous vertex is not equal current
				// make curr's adjacent node's previous be curr
				isVisited[i] = curr;
				// add vertex i into queue
				QueueJoin(toVisit, i); 
			}
		}
	}
	dropQueue(toVisit);

	int numVertex = 0;
	if (isFound) {
		// store path from src to dest in path array
		// start from destination, go to source
		int *temp = calloc((unsigned long)gsize, sizeof(int));
		for(int i = dest; i != -404; i = isVisited[i]) {
			temp[numVertex] = i;
			numVertex++;
		}
        // reverse temp array to get path array
		for (int i = 0; i < numVertex; i++)
			path[i] = temp[numVertex - i - 1];
		free(temp);
	}
	free(isVisited);
	return numVertex;
}
