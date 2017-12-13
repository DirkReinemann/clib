CC=gcc
CFLAGS=-g -std=c11 -Wall -Werror
TEST_SOURCES=clibtest.c clib.c unity.c
TEST_BIN=clibtest

all: test

test-compile:
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_BIN)

test: test-compile
	./$(TEST_BIN)

clean:
	-rm -f $(TEST_BIN)
