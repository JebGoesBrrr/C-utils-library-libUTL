#include "UTL/UTL.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// abstract list functions ////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** free the memory associated with the given list */
void UTL_DestroyList(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            UTL_DestroyArrayList((UTL_ArrayList*) list);
            break;
        case UTL_LINKED_LIST:
            UTL_DestroyLinkedList((UTL_LinkedList*) list);
            break;
        case UTL_ARRAY_LISTP:
            UTL_DestroyArrayListP((UTL_ArrayListP*) list);
            break;
        case UTL_LINKED_LISTP:
            UTL_DestroyLinkedListP((UTL_LinkedListP*) list);
            break;
        default: break;
    }
}


/** append a new object to the back of the list */
void UTL_AppendToList(UTL_List *list, void *obj) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            UTL_AppendToArrayList((UTL_ArrayList*) list, obj);
            break;
        case UTL_LINKED_LIST:
            UTL_AppendToLinkedList((UTL_LinkedList*) list, obj);
            break;
        case UTL_ARRAY_LISTP:
            UTL_AppendToArrayListP((UTL_ArrayListP*) list, obj);
            break;
        case UTL_LINKED_LISTP:
            UTL_AppendToLinkedListP((UTL_LinkedListP*) list, obj);
            break;
        default: break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// array list functions ///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing objects directly, backed by an array */
UTL_ArrayList* UTL_CreateArrayList(UTL_TypeInfo *dataType) {
    (void) dataType;
    return NULL;
}


/** see UTL_DestroyList */
void UTL_DestroyArrayList(UTL_ArrayList *list) {
    (void) list;
}


/** see UTL_AppendToList */
void UTL_AppendToArrayList(UTL_ArrayList *list, void *obj) {
    (void) list;
    (void) obj;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// array p-list functions /////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing pointers, backed by an array */
UTL_ArrayListP* UTL_CreateArrayListP(UTL_TypeInfo *dataType) {
    (void) dataType;
    return NULL;
}


/** see UTL_DestroyList */
void UTL_DestroyArrayListP(UTL_ArrayListP *list) {
    (void) list;
}


/** see UTL_AppendToList */
void UTL_AppendToArrayListP(UTL_ArrayListP *list, void *obj) {
    (void) list;
    (void) obj;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// linked list functions //////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing objects directly, backed by linked nodes */
UTL_LinkedList* UTL_CreateLinkedList(UTL_TypeInfo *dataType) {
    (void) dataType;
    return NULL;
}


/** see UTL_DestroyList */
void UTL_DestroyLinkedList(UTL_LinkedList *list) {
    (void) list;
}


/** see UTL_AppendToList */
void UTL_AppendToLinkedList(UTL_LinkedList *list, void *obj) {
    (void) list;
    (void) obj;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// linked p-list functions ////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing pointers, backed by linked nodes */
UTL_LinkedListP* UTL_CreateLinkedListP(UTL_TypeInfo *dataType) {
    (void) dataType;
    return NULL;
}


/** see UTL_DestroyList */
void UTL_DestroyLinkedListP(UTL_LinkedListP *list) {
    (void) list;
}


/** see UTL_AppendToList */
void UTL_AppendToLinkedListP(UTL_LinkedListP *list, void *obj) {
    (void) list;
    (void) obj;
}
