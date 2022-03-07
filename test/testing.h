#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define assertPass(cond) if (!(cond))  { printf(" %i ", __LINE__); return false; }


typedef struct {
    const char *label;
    bool (*func)(void);
} TestFuncEntry;


typedef struct {
    const char *label;
    TestFuncEntry *funcs;
} TestClassEntry;


#endif // TESTING_H