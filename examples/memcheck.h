#ifndef EXAMPLES_MEMCHECK_H
#define EXAMPLES_MEMCHECK_H

#include <stdio.h>

extern void* __real_malloc(size_t);
extern void* __real_realloc(void*, size_t);
extern void  __real_free(void*);

static int numMalloc;
static int numRealloc;
static int numFree;

static int effectiveAlloc;
static int effectiveFree;

void* __wrap_malloc(size_t size) {
    numMalloc++;
    if (size) effectiveAlloc++;
    return __real_malloc(size);
}

void* __wrap_realloc(void *ptr, size_t size) {
    numRealloc++;
    void *newptr = __real_realloc(ptr, size);

    if (ptr != newptr) {
        if (ptr == NULL)
            effectiveAlloc++;
        else if (newptr == NULL)
            effectiveFree++;
        else {
            effectiveAlloc++;
            effectiveFree++;
        }
    }

    return newptr;
}

void __wrap_free(void *ptr) {
    numFree++;
    if (ptr) effectiveFree++;
    return __real_free(ptr);
}

static void initMallocs(void) {
    numMalloc = numRealloc = numFree = effectiveAlloc = effectiveFree = 0;
}

static void printMallocs(void) {
    int m = numMalloc;
    int r = numRealloc;
    int f = numFree;

    int ea = effectiveAlloc;
    int ef = effectiveFree;

    printf("\n");
    printf("----------------------------------\n");
    printf("---------- memory stats ----------\n");
    printf("----------------------------------\n");
    printf(" function     | #calls \n");
    printf("  - malloc()  |  %2i\n", m);
    printf("  - realloc() |  %2i\n", r);
    printf("  - free()    |  %2i\n", f);
    printf("----------------------------------\n");
    printf(" effective    |\n");
    printf("  - allocs    |  %2i\n", ea);
    printf("  - frees     |  %2i\n", ef);

}


#endif // EXAMPLES_MEMCHECK_H