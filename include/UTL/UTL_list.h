#ifndef UTL_LIST_H
#define UTL_LIST_H



#include "UTL/UTL.h"



/** different types of lists  */
typedef enum {
    UTL_ARRAY_LIST,     // list of objects, backed by an array
    UTL_LINKED_LIST,    // list of objects, backed by linked nodes
    UTL_ARRAY_LISTP,    // list of pointers, backed by an array
    UTL_LINKED_LISTP    // list of pointers, backed by linked nodes
} UTL_ListType;



/** abstract base type for all lists */
typedef struct {
    const UTL_ListType         listType;    // type of this list (array vs linked, objects vs pointers)
    const UTL_TypeInfo * const dataType;    // type of the contained data
    const int                  count;       // number of objects currently in the list
} UTL_List;


// abstract list functions ////////////////////////////////////////////////////////////////////////////////////////////


/** free the memory associated with the given list */
extern void UTL_DestroyList(UTL_List *list);


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


extern void UTL_ListPopBack(UTL_List *list);


extern void UTL_ListPopFront(UTL_List *list);


extern void UTL_ListRemoveAt(UTL_List *list, int at);


// list constructors //////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing objects directly, backed by an array */
extern UTL_List* UTL_CreateArrayList(UTL_TypeInfo *dataType);


/** create a new list, storing pointers, backed by an array */
extern UTL_List* UTL_CreateArrayListP(UTL_TypeInfo *dataType);


/** create a new list, storing objects directly, backed by linked nodes */
extern UTL_List* UTL_CreateLinkedList(UTL_TypeInfo *dataType);


/** create a new list, storing pointers, backed by linked nodes */
extern UTL_List* UTL_CreateLinkedListP(UTL_TypeInfo *dataType);




#endif // UTL_LIST_H
