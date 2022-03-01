# replace with path to your c compiler
CC="mingw64/bin/gcc.exe"
CFLAGS="-std=c99 -Wall -Wextra -O2 -I include"
CFLAGS_FOR_LIB="--shared -fpic"

function buildUtilsLibrary() {
    mkdir -p build
    CMD="$CC $CFLAGS $CFLAGS_FOR_LIB src/UTL/*.c -o build/libUTL.dll"
    echo $CMD
    eval $CMD
}

buildUtilsLibrary