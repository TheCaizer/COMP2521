# COMP2521; Question: rankPopularity

CC=gcc
CFLAGS=-Wall -Werror -g

all: testRankPopularity

testRankPopularity :  Graph.o rankPopularity.o testRankPopularity.c
	$(CC) -o testRankPopularity  testRankPopularity.c Graph.o  rankPopularity.o 

rankPopularity.o: Graph.h rankPopularity.c
	$(CC) -c rankPopularity.c
Graph.o:  Graph.h Graph.c
	$(CC) -c Graph.c
	
clean:
	rm -f testRankPopularity rankPopularity.o  Graph.o testRankPopularity.o core



