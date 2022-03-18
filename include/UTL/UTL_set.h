#ifndef UTL_SET_H
#define UTL_SET_H



#include "UTL/UTL.h"


typedef enum {
    UTL_ARRAY_SET,
    UTL_HASH_SET
} UTL_SetType;

typedef struct {
    const UTL_SetType setType;
    const UTL_TypeInfo *dataType;
    const bool byRef;
    const int count;
} UTL_Set;


typedef struct {
    UTL_Set *set;
    struct {
        int i;
        void *ptr;
    } auxData;
} UTL_SetIter;



extern UTL_Set* UTL_SetCreate(UTL_SetType setType, const UTL_TypeInfo *dataType, bool byRef);


extern void UTL_SetDestroy(UTL_Set *set);


extern void UTL_SetClear(UTL_Set *set);


extern void UTL_SetInsert(UTL_Set *set, void *obj);


extern bool UTL_SetContains(UTL_Set *set, void *obj);


extern void UTL_SetUnion(UTL_Set *set, const UTL_Set *other);


extern void UTL_SetIntersection(UTL_Set *set, const UTL_Set *other);


extern bool UTL_SetDifference(UTL_Set *set, const UTL_Set *other);






extern UTL_SetIter UTL_SetGetIterator(UTL_Set *set);

extern void* UTL_SetIterGet(UTL_SetIter *iter);

extern bool UTL_SetIterIsValid(UTL_Set *iter);

extern void UTL_SetIterNext(UTL_SetIter *iter);

extern void UTL_SetIterHasNext(UTL_SetIter *iter);


#endif // UTL_SET_H