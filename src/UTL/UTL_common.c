#include "UTL/UTL_common.h"

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
