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



typedef struct {
    UTL_TypeInfo *keyInfo;
    UTL_TypeInfo *valInfo;
    bool keyByRef;
    bool valByRef;
} UTL_GenericInfo;

static size_t UTL_GenericDataSize(UTL_GenericInfo *info) {
    size_t keySizeRaw = info->keyByRef ? sizeof(void*) : info->keyInfo->size;

    // no value?
    if (!info->valInfo)
        return keySizeRaw;

    size_t keySize = (keySizeRaw % 8 == 0) ? (keySizeRaw) : (keySizeRaw + (8 - keySizeRaw % 8));

    size_t valSizeRaw = info->valByRef ? sizeof(void*) : info->valInfo->size;
    size_t valSize = (valSizeRaw % 8 == 0) ? (valSizeRaw) : (valSizeRaw + (8 - valSizeRaw % 8));

    return keySize + valSize;
}

static void* UTL_GenericGetKey(UTL_GenericInfo *info, void *dataPos) {
    if (info->keyByRef) return *((void**)dataPos);
    else return dataPos;
}

static void* UTL_GenericGetVal(UTL_GenericInfo *info, void *dataPos) {
    size_t keySizeRaw = info->keyByRef ? sizeof(void*) : info->keyInfo->size;
    size_t keySize = (keySizeRaw % 8 == 0) ? (keySizeRaw) : (keySizeRaw + (8 - keySizeRaw % 8));

    dataPos = (void*) (((uintptr_t)dataPos) + keySize);
    if (info->valByRef) return *((void**)dataPos);
    else return dataPos;
}

static void UTL_GenericSetKey(UTL_GenericInfo *info, void *dataPos, void *key) {
    if (info->keyByRef)
        *((void**)dataPos) = key;
    else
        memcpy(dataPos, key, info->keyInfo->size);
}

static void UTL_GenericSetVal(UTL_GenericInfo *info, void *dataPos, void *val) {
    size_t keySizeRaw = info->keyByRef ? sizeof(void*) : info->keyInfo->size;
    size_t keySize = (keySizeRaw % 8 == 0) ? (keySizeRaw) : (keySizeRaw + (8 - keySizeRaw % 8));

    dataPos = (void*) (((uintptr_t)dataPos) + keySize);
    if (info->valByRef)
        *((void**)dataPos) = val;
    else
        memcpy(dataPos, val, info->valInfo->size);
}


#endif // UTL_COMMON_H
