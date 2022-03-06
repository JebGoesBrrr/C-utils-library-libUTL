.phony: clean

CC 				= gcc
CLFAGS 			= -std=c99 -Wall -Wextra -O2 -I include
CFLAGS_FOR_LIB 	= --shared -fpic

UTL_SRC  = $(wildcard src/UTL/*.c)
TEST_SRC = $(wildcard src/test/*.c)

all: UTL TEST

UTL: build/libUTL.dll

build/libUTL.dll:
	$(CC) $(CLFAGS) $(CFLAGS_FOR_LIB) $(UTL_SRC) -o $@

TEST: UTL build/test.exe

build/test.exe:
	$(CC) $(CLFAGS) $(TEST_SRC) -o $@ -L build -lUTL

clean:
	rm -f build/*
