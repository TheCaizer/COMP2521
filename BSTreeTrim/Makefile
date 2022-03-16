
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testBSTreeTrim.c
EXERCISE_FILE = BSTreeTrim.c
COMMON = BSTree.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testBSTreeTrim

testBSTreeTrim: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testBSTreeTrim $(SRC_FILES)

clean:
	rm -f testBSTreeTrim

