#include "UTL/UTL.h"
#include "memcheck.h"
#include <stdio.h>

int main() {
    initMallocs();
    printf("Hello World\n");
    printMallocs();
    return 0;
}