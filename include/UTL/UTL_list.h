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


/** set object at given index in a list */
extern void UTL_ListSet(UTL_List *list, int at, void *obj);


/** append a new object to the back of the list */
extern void UTL_AppendToList(UTL_List *list, void *obj);


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
