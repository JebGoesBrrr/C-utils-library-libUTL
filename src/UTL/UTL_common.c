#include "UTL/UTL.h"

// functions and type information for int data type
static int UTL_CompareInt(const void *p1, const void *p2) {
    const int *i1 = (const int*)p1;
    const int *i2 = (const int*)p2;

    if (*i1 < *i2) return -1;
    if (*i1 > *i2) return  1;
    return 0;
}

static unsigned UTL_HashInt(const void *p) {
    return *(const unsigned*)p;
}

static void UTL_CopyInt(void *dst, const void *src) {
    *((int*)dst) = *((int*)src);
}

const UTL_TypeInfo UTL_TypeInfoInt = (UTL_TypeInfo) {
    .size     = sizeof(int),
    .cmpFunc  = &UTL_CompareInt,
    .hashFunc = &UTL_HashInt,
    .copyFunc = &UTL_CopyInt,
    .name     = "int"
};

// functions and type information for float data type
static int UTL_CompareFloat(const void *p1, const void *p2) {
    const float *f1 = (const float*)p1;
    const float *f2 = (const float*)p2;

    if (*f1 < *f2) return -1;
    if (*f1 > *f2) return  1;
    return 0;
}

static unsigned UTL_HashFloat(const void *p){
    return *(const unsigned*)p;
}

static void UTL_CopyFloat(void *dst, const void *src){
    *((float*)dst) = *((float*)src);
}

const UTL_TypeInfo UTL_TypeInfoFloat = (UTL_TypeInfo) {
    .size     = sizeof(float),
    .cmpFunc  = &UTL_CompareFloat,
    .hashFunc = &UTL_HashFloat,
    .copyFunc = &UTL_CopyFloat,
    .name     = "float"
};

// functions and type information for char data type
static int UTL_CompareChar(const void *p1, const void *p2) {
    const char *c1 = (const char*)p1;
    const char *c2 = (const char*)p2;

    if (*c1 < *c2) return -1;
    if (*c1 > *c2) return  1;
    return 0;
}

static unsigned UTL_HashChar(const void *p){
    return (unsigned) *(const char*)p;
}

static void UTL_CopyChar(void *dst, const void *src){
    *((char*)dst) = *((char*)src);
}

const UTL_TypeInfo UTL_TypeInfoChar = (UTL_TypeInfo) {
    .size     = sizeof(char),
    .cmpFunc  = &UTL_CompareChar,
    .hashFunc = &UTL_HashChar,
    .copyFunc = &UTL_CopyChar,
    .name     = "char"
};
