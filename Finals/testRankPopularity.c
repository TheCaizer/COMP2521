/* Testing module for rankPopularity ...
   Written by Ashesh Mahidadia
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

#define NODES 20


void rankPopularity( Graph g, int src, double *mnV ) ;

int main(void) {

  Graph g = newGraph(NODES);
  int from, s, d; 
  
  int count = fscanf(stdin, "from: %d ", &from );
  if(count != 1){ 
    fprintf(stdout, "\n Error: incorrect input!! \n\n" );
    return 1; 
  }
  fprintf(stdout, "rankPopularity, From: %d \n\n", from );
  while(fscanf(stdin, "%d %d", &s, &d) == 2){
    insertDirectedEdge(g, s, d);   
    fprintf(stdout, "Edge inserted:  %d -> %d \n", s, d);
  }
  fprintf(stdout, "\n");
    

  int i;
  double *mnV;   

  mnV = malloc((g->nV + 1)*sizeof(double));
  for (i = 0; i < (g->nV + 1); i++) { 
	mnV[i] = -1;
  }
  
  rankPopularity(g, from , mnV ); 

  fprintf(stdout, "\nrankPopularity: \n" );
  for (i = 0; i < (g->nV + 1); i++) {
	if(mnV[i] != -1){
  		fprintf(stdout, " node: %d, rank: %10.3lf \n" , i, mnV[i] );
	}
  }
  fprintf(stdout, " \n" );

  free(mnV);
  freeGraph(g);
  
  return 0;
}
