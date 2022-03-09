#ifndef UTL_COMMON_H
#define UTL_COMMON_H



#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



/** compare function type to be used with generic containers */
typedef int (UTL_CmpFunc)(const void*, const void*);

/** hash function type to be used with generic containers */
typedef unsigned (UTL_HashFunc)(const void*);

/** copy function type to be used with generic containers */
typedef void (UTL_CopyFunc)(void*, const void*);



/** holds information about a type required for generic containers.
 *  stores the type's size in bytes, compare function, hash function,
 *  copy function and name */
typedef struct {
    size_t        size;     /** type's size in bytes */
    UTL_CmpFunc  *cmpFunc;  /** pointer to type's compare function */
    UTL_HashFunc *hashFunc; /** pointer to type's hash function */
    UTL_CopyFunc *copyFunc; /** pointer to type's copy function */
    const char   *name;     /** type's name */
} UTL_TypeInfo;



// type info structs for C's primitive data types
extern const UTL_TypeInfo UTL_TypeInfoInt;
extern const UTL_TypeInfo UTL_TypeInfoChar;
extern const UTL_TypeInfo UTL_TypeInfoFloat;


// encode a value into the bits of a pointer
#define UTL_ToPtr(type, val) (((union { type x; void *y; }) { .x = val}).y)

// decode a value from the bits of a pointer
#define UTL_FromPtr(type, ptr) (((union { type x; void *y;}) { .y = ptr}).x)


#endif // UTL_COMMON_H