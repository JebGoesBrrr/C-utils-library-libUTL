#ifndef UTL_COMMON_H
#define UTL_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// compare function type
typedef int (UTL_CmpFunc)(const void*, const void*);

// hash function type
typedef unsigned (UTL_HashFunc)(const void*);

// copy function type
typedef void (UTL_CopyFunc)(void*, const void*);

// holds information about a type, required for generic containers
typedef struct {
    size_t size;
    UTL_CmpFunc *cmpFunc;
    UTL_HashFunc *hashFunc;
    UTL_CopyFunc *copyFunc;
    const char *name;
} UTL_TypeInfo;



// type info structs for C's primitive data types

extern UTL_TypeInfo UTL_TypeInfoInt;
extern UTL_TypeInfo UTL_TypeInfoChar;
extern UTL_TypeInfo UTL_TypeInfoFloat;


#endif // UTL_COMMON_H