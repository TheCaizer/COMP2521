# COMP2521, Question: equalBST
# Written by Ashesh Mahidadia, May 2019

CC=gcc
CFLAGS=-Wall -Werror -g

all: testEqualBST

testEqualBST : BSTree.o equalBST.o testEqualBST.o
	$(CC) -o testEqualBST  BSTree.o  equalBST.o testEqualBST.o

equalBST.o : equalBST.c  BSTree.h 
BSTree.o : BSTree.c  BSTree.h 
testEqualBST.o : testEqualBST.c  BSTree.h 

clean:
	rm -f testEqualBST equalBST.o testEqualBST.o BSTree.o core
