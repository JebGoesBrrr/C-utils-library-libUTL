.phony: clean mkdirs

CC 		= gcc
CFLAGS	= -std=c99 -Wall -Wextra -O2 -I include

SRC_LIB  	= $(wildcard src/*.c)
SRC_TEST 	= $(wildcard test/*.c)
SRC_EXAMPLE = $(wildcard examples/*.c)

OBJ_LIB 	= $(addsuffix .o,$(addprefix tmp/,$(notdir $(basename $(SRC_LIB)))))
OBJ_TEST 	= $(addsuffix .o,$(addprefix tmp/test/,$(notdir $(basename $(SRC_TEST)))))
EXE_EXAMPLE	= $(addsuffix .exe,$(addprefix build/example_,$(notdir $(basename $(SRC_EXAMPLE)))))

all: lib test examples

lib: mkdirs build/libUTL.dll

test: mkdirs build/test.exe

examples: mkdirs $(EXE_EXAMPLE)

build/libUTL.dll: $(OBJ_LIB)
	$(CC) --shared $^ -o $@

build/test.exe: $(OBJ_TEST)
	$(CC) $^ -o $@ -L build -lUTL

tmp/%.o : src/%.c
	$(CC) $(CFLAGS) -c -fpic $< -o $@

build/example_%.exe : examples/%.c examples/memcheck.h
	$(CC) $(CFLAGS) $< -o $@ $(OBJ_LIB) -Wl,--wrap,malloc -Wl,--wrap,realloc -Wl,--wrap,free

tmp/test/%.o : test/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*
	rm -f tmp/*.o
	rm -f tmp/test/*.o

mkdirs:
	mkdir -p build
	mkdir -p tmp
	mkdir -p tmp/examples
	mkdir -p tmp/test