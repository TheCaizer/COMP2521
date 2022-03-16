
CC = gcc
CFLAGS = -Wall -Werror -std=c11 -g

TEST_DRIVER = testListGetAbnormals.c
EXERCISE_FILE = listGetAbnormals.c
COMMON = list.c

SRC_FILES = $(TEST_DRIVER) $(EXERCISE_FILE) $(COMMON)

all: testListGetAbnormals

testListGetAbnormals: $(SRC_FILES)
	$(CC) $(CFLAGS) -o testListGetAbnormals $(SRC_FILES)

clean:
	rm -f testListGetAbnormals

