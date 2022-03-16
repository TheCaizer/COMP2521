# COMP2521, Question: mergeOrdered .. 

CC=gcc
CFLAGS=-Wall -Werror -g

all: testMergeOrdered

testMergeOrdered : list.o  mergeOrdered.o  testMergeOrdered.o 
	$(CC) -o testMergeOrdered  testMergeOrdered.c list.o  mergeOrdered.o 


testMergeOrdered.o : testMergeOrdered.c  list.h 
mergeOrdered.o : mergeOrdered.c  list.h 
list.o : list.c  list.h 

clean:
	rm -f testMergeOrdered list.o mergeOrdered.o testMergeOrdered.o core



