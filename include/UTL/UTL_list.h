#ifndef UTL_LIST_H
#define UTL_LIST_H



#include "UTL/UTL.h"



/** different types of lists  */
typedef enum {
    UTL_ARRAY_LIST,  // list backed by an array
    UTL_LINKED_LIST  // list backed by linked nodes
} UTL_ListType;



/** abstract base type for all lists */
typedef struct {
    const UTL_ListType         listType;  // type of this list (array vs linked, objects vs pointers)
    const UTL_TypeInfo * const dataType;  // type of the contained data
    const bool                 byRef;     // are objects in this list stored by pointer, or directly by value
    const int                  count;     // number of objects currently in the list
} UTL_List;



/** abstract base type for all list iterators */
typedef struct {
    UTL_List *list;     // the list into which this iterator is pointing
    void     *auxData;  // for internal use -- don't use
    int       index;    // index into the list
} UTL_ListIter;



// abstract list functions ////////////////////////////////////////////////////////////////////////////////////////////



/** free the memory associated with the given list */
extern void UTL_ListDestroy(UTL_List *list);


/** get object at given index from a list */
extern void* UTL_ListGet(UTL_List *list, int at);


/** get the last objet from a list */
extern void* UTL_ListGetBack(UTL_List *list);


/** get the first object from a list */
extern void* UTL_ListGetFront(UTL_List *list);


/** set object at given index in a list */
extern void UTL_ListSet(UTL_List *list, int at, void *obj);


/** append a new object to the back of the list */
extern void UTL_ListPushBack(UTL_List *list, void *obj);


/** prepend a new object to the front of the list */
extern void UTL_ListPushFront(UTL_List *list, void *obj);


/** append a new object to the back of the list */
extern void UTL_ListInsert(UTL_List *list, int at, void *obj);


/** remove the last object from a list */
extern void UTL_ListPopBack(UTL_List *list);


/** remove the first object from a list */
extern void UTL_ListPopFront(UTL_List *list);


/** remove the object at index @at from the list */
extern void UTL_ListRemove(UTL_List *list, int at);


/** find the first index of the given object, at or after @offset */
extern int UTL_ListFindFirst(UTL_List *list, void *obj, int offset);


/** find the last index of the given object, at or before @offset */
extern int UTL_ListFindLast(UTL_List *list, void *obj, int offset);


/** */
extern bool UTL_ListContains(UTL_List *list, void *obj);


/** sort a list */
extern void UTL_ListSort(UTL_List *list);


/** return true if the given list is sorted */
extern bool UTL_ListIsSorted(UTL_List *list);


extern void* UTL_ListFold(UTL_List *list, void* (*foldFunc)(void*,void*), void *state);


/** get an iterator to the beginning of the list */
extern UTL_ListIter UTL_ListGetIteratorFront(UTL_List *list);


/** get an iterator to the end of the list */
extern UTL_ListIter UTL_ListGetIteratorBack(UTL_List *list);


/** get an iterator pointing at an index in the list */
extern UTL_ListIter UTL_ListGetIteratorAt(UTL_List *list, int at);


// list iterators /////////////////////////////////////////////////////////////////////////////////////////////////////


extern bool UTL_ListIterHasNext(UTL_ListIter *iter);


extern bool UTL_ListIterHasPrev(UTL_ListIter *iter);


extern bool UTL_ListIterIsValid(UTL_ListIter *iter);


extern void UTL_ListIterNext(UTL_ListIter *iter);


extern void UTL_ListIterPrev(UTL_ListIter *iter);


extern void* UTL_ListIterGet(UTL_ListIter *iter);


extern void UTL_ListIterSet(UTL_ListIter *iter, void *obj);


extern void UTL_ListIterInsert(UTL_ListIter *iter, void *obj);


extern void UTL_ListIterRemove(UTL_ListIter *iter);


// list constructors //////////////////////////////////////////////////////////////////////////////////////////////////


/** Create a new list 
 *  @listType: what kind of list (array, linked, etc..)
 *  @dataType: what type of objects are stored
 *  @byRef: true of objects are stored by pointer, false if they are stored directly by value */
extern UTL_List* UTL_ListCreate(UTL_ListType listType, const UTL_TypeInfo *dataType, bool byRef);




#endif // UTL_LIST_H
