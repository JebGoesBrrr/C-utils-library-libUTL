.phony: clean

CC 				= gcc
CLFAGS 			= -std=c99 -Wall -Wextra -O2 -I include
CFLAGS_FOR_LIB 	= --shared -fpic

UTL_SRC = $(wildcard src/UTL/*.c)

UTL: build/libUTL.dll
	@echo ""

build/libUTL.dll:
	$(CC) $(CLFAGS) $(CFLAGS_FOR_LIB) $(UTL_SRC) -o $@

clean:
	rm build/*
