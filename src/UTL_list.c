#include "UTL/UTL.h"


#define UTL_ARRAY_LIST_INITIAL_CAPACITY 64



/** list of objects, backed by an array */
typedef struct {
    const UTL_ListType listType;         // see UTL_List
    const UTL_TypeInfo * const dataType; // see UTL_List
    int count;                           // see UTL_List

    int capacity;   // maximum number of objects that could be stored in this list without relocation
    void *data;     // array containing all objects
} UTL_ArrayList;



/** list of pointers, backed by an array */
typedef struct {
    const UTL_ListType listType;         // see UTL_List
    const UTL_TypeInfo * const dataType; // see UTL_List
    int count;                           // see UTL_List

    int capacity;   // maximum number of pointers that could be stored in this list without relocation
    void **data;    // array containing all pointers
} UTL_ArrayListP;



typedef struct UTL_LinkedListNode UTL_LinkedListNode;
struct UTL_LinkedListNode {
    UTL_LinkedListNode *next;
    UTL_LinkedListNode *prev;
    uint8_t obj[];
};

/** list of objects, backed by linked nodes */
typedef struct {
    const UTL_ListType listType;         // see UTL_List
    const UTL_TypeInfo * const dataType; // see UTL_List
    int count;                           // see UTL_List

    UTL_LinkedListNode sentinel; // first and last node of the list
} UTL_LinkedList;



typedef struct UTL_LinkedListNodeP UTL_LinkedListNodeP;
struct UTL_LinkedListNodeP {
    UTL_LinkedListNodeP *next;
    UTL_LinkedListNodeP *prev;
    void *obj;
};

/** list of pointers, backed by linked nodes */
typedef struct {
    const UTL_ListType listType;         // see UTL_List
    const UTL_TypeInfo * const dataType; // see UTL_List
    int count;                           // see UTL_List

    UTL_LinkedListNodeP sentinel; // first and last node of the list
} UTL_LinkedListP;



_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_ArrayList,   listType));
_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_ArrayListP,  listType));
_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_LinkedList,  listType));
_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_LinkedListP, listType));

_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_ArrayList,   dataType));
_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_ArrayListP,  dataType));
_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_LinkedList,  dataType));
_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_LinkedListP, dataType));

_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_ArrayList,   count));
_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_ArrayListP,  count));
_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_LinkedList,  count));
_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_LinkedListP, count));


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



static void UTL_DestroyArrayList(UTL_ArrayList *list) {
    free(list->data);
    free(list);
}


static void UTL_DestroyArrayListP(UTL_ArrayListP *list) {
    free(list->data);
    free(list);
}


static void UTL_DestroyLinkedList(UTL_LinkedList *list) {
    UTL_LinkedListNode *node = list->sentinel.next;
    while (node != &list->sentinel) {
        UTL_LinkedListNode *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}


static void UTL_DestroyLinkedListP(UTL_LinkedListP *list) {
    UTL_LinkedListNodeP *node = list->sentinel.next;
    while (node != &list->sentinel) {
        UTL_LinkedListNodeP *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



static void UTL_AppendToArrayList(UTL_ArrayList *list, void *obj) {
    (void)list;
    (void)obj;
}


static void UTL_AppendToArrayListP(UTL_ArrayListP *list, void *obj) {
    (void)list;
    (void)obj;
}


static void UTL_AppendToLinkedList(UTL_LinkedList *list, void *obj) {
    (void)list;
    (void)obj;
}


static void UTL_AppendToLinkedListP(UTL_LinkedListP *list, void *obj) {
    (void)list;
    (void)obj;
}



// abstract list functions ////////////////////////////////////////////////////////////////////////////////////////////



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



/** create a new list, storing objects directly, backed by an array */
UTL_List* UTL_CreateArrayList(UTL_TypeInfo *dataType) {
    UTL_ArrayList *list = (UTL_ArrayList*) malloc(sizeof(UTL_ArrayList));

    *(UTL_ListType*)(&list->listType) = UTL_ARRAY_LIST;
    *(UTL_TypeInfo**)(&list->dataType) = dataType;

    list->capacity = UTL_ARRAY_LIST_INITIAL_CAPACITY;
    list->count = 0;

    list->data = malloc(list->dataType->size * list->capacity);

    return (UTL_List*) list;
}


/** create a new list, storing pointers, backed by an array */
UTL_List* UTL_CreateArrayListP(UTL_TypeInfo *dataType) {
    UTL_ArrayListP *list = (UTL_ArrayListP*) malloc(sizeof(UTL_ArrayListP));

    *(UTL_ListType*)(&list->listType) = UTL_ARRAY_LISTP;
    *(UTL_TypeInfo**)(&list->dataType) = dataType;

    list->capacity = UTL_ARRAY_LIST_INITIAL_CAPACITY;
    list->count = 0;

    list->data = malloc(sizeof(void*) * list->capacity);

    return (UTL_List*) list;
}


/** create a new list, storing objects directly, backed by linked nodes */
UTL_List* UTL_CreateLinkedList(UTL_TypeInfo *dataType) {
    UTL_LinkedList *list = (UTL_LinkedList*) malloc(sizeof(UTL_LinkedList));

    *(UTL_ListType*)(&list->listType) = UTL_LINKED_LIST;
    *(UTL_TypeInfo**)(&list->dataType) = dataType;

    list->count = 0;
    list->sentinel.next = &list->sentinel;
    list->sentinel.prev = &list->sentinel;

    return (UTL_List*) list;
}


/** create a new list, storing pointers, backed by linked nodes */
UTL_List* UTL_CreateLinkedListP(UTL_TypeInfo *dataType) {
    UTL_LinkedListP *list = (UTL_LinkedListP*) malloc(sizeof(UTL_LinkedListP));

    *(UTL_ListType*)(&list->listType) = UTL_LINKED_LISTP;
    *(UTL_TypeInfo**)(&list->dataType) = dataType;

    list->count = 0;
    list->sentinel.next = &list->sentinel;
    list->sentinel.prev = &list->sentinel;

    return (UTL_List*) list;
}
