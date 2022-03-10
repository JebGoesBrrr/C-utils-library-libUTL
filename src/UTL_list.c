#include "UTL/UTL.h"


#define UTL_ARRAY_LIST_INITIAL_CAPACITY 64



/** list of objects, backed by an array */
typedef struct {
    UTL_ListType        listType; // see UTL_List
    const UTL_TypeInfo *dataType; // see UTL_List
    bool                byRef;    // see UTL_List
    int                 count;    // see UTL_List

    int      capacity; // maximum number of objects that could be stored in this list without relocation
    uint8_t *data;     // array containing all objects
} UTL_ArrayList;



typedef struct UTL_LinkedListNode UTL_LinkedListNode;
struct UTL_LinkedListNode {
    UTL_LinkedListNode *next;
    UTL_LinkedListNode *prev;
    uint8_t obj[];
};

/** list of objects, backed by linked nodes */
typedef struct {
    UTL_ListType        listType; // see UTL_List
    const UTL_TypeInfo *dataType; // see UTL_List
    bool                byRef;    // see UTL_List
    int                 count;    // see UTL_List

    UTL_LinkedListNode sentinel; // first and last node of the list
} UTL_LinkedList;




_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_ArrayList,  listType));
_STATIC_ASSERT(offsetof(UTL_List, listType) == offsetof(UTL_LinkedList, listType));

_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_ArrayList,  dataType));
_STATIC_ASSERT(offsetof(UTL_List, dataType) == offsetof(UTL_LinkedList, dataType));

_STATIC_ASSERT(offsetof(UTL_List, byRef) == offsetof(UTL_ArrayList,  byRef));
_STATIC_ASSERT(offsetof(UTL_List, byRef) == offsetof(UTL_LinkedList, byRef));

_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_ArrayList,  count));
_STATIC_ASSERT(offsetof(UTL_List, count) == offsetof(UTL_LinkedList, count));



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define UTL_ListDataSize(list) (list->byRef ? sizeof(void*) : list->dataType->size)

#define UTL_ListObjSrc(list, obj) (list->byRef ? &(obj) : (obj))

#define UTL_ListObjDst(list, obj) (list->byRef ? *((void**)(obj)) : (void*)(obj))


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void UTL_ArrayListDestroy(UTL_ArrayList *list) {
    free(list->data);
    free(list);
}


static void UTL_LinkedListDestroy(UTL_LinkedList *list) {
    UTL_LinkedListNode *node = list->sentinel.next;
    while (node != &list->sentinel) {
        UTL_LinkedListNode *next = node->next;
        free(node);
        node = next;
    }
    free(list);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void* UTL_ArrayListGet(UTL_ArrayList *list, int at) {

    if (at >= list->count) return NULL;

    uint8_t *pos = list->data + UTL_ListDataSize(list) * at;
    return UTL_ListObjDst(list, pos);
}


void* UTL_LinkedListGet(UTL_LinkedList *list, int at) {

    if (at >= list->count) return NULL;

    UTL_LinkedListNode *node = list->sentinel.next;
    while (at--) node = node->next;

    return UTL_ListObjDst(list, node->obj);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void UTL_ArrayListPushBack(UTL_ArrayList *list, void *obj) {

    if (list->count == list->capacity) {
        list->capacity += list->capacity >> 1;
        list->data = realloc(list->data, UTL_ListDataSize(list) * list->capacity);
    }

    uint8_t *pos = list->data + UTL_ListDataSize(list) * list->count;
    memcpy(pos, UTL_ListObjSrc(list, obj), UTL_ListDataSize(list));
    
    list->count++;
}


static void UTL_LinkedListPushBack(UTL_LinkedList *list, void *obj) {

    UTL_LinkedListNode *node = malloc(sizeof(UTL_LinkedListNode) + UTL_ListDataSize(list));
    memcpy(node->obj, UTL_ListObjSrc(list, obj), UTL_ListDataSize(list));

    node->next = &list->sentinel;
    node->prev = list->sentinel.prev;

    list->sentinel.prev->next = node;
    list->sentinel.prev = node;

    list->count++;
}



// abstract list functions ////////////////////////////////////////////////////////////////////////////////////////////



/** free the memory associated with the given list */
void UTL_ListDestroy(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            UTL_ArrayListDestroy((UTL_ArrayList*) list);
            break;
        case UTL_LINKED_LIST:
            UTL_LinkedListDestroy((UTL_LinkedList*) list);
            break;
        default:
            break;
    }
}


/** get object at given index from a list */
void* UTL_ListGet(UTL_List *list, int at) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListGet((UTL_ArrayList*) list, at);
        case UTL_LINKED_LIST:
            return UTL_LinkedListGet((UTL_LinkedList*) list, at);
        default:
            return NULL;
    }
}


/** append a new object to the back of the list */
void UTL_ListPushBack(UTL_List *list, void *obj) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            UTL_ArrayListPushBack((UTL_ArrayList*) list, obj);
            break;
        case UTL_LINKED_LIST:
            UTL_LinkedListPushBack((UTL_LinkedList*) list, obj);
            break;
        default:
            break;
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/** create a new list, storing objects directly, backed by an array */
static UTL_List* UTL_ArrayListCreate(const UTL_TypeInfo *dataType, bool byRef) {
    UTL_ArrayList *list = (UTL_ArrayList*) malloc(sizeof(UTL_ArrayList));

    list->listType = UTL_ARRAY_LIST;
    list->dataType = dataType;
    list->byRef    = byRef;


    list->capacity = UTL_ARRAY_LIST_INITIAL_CAPACITY;
    list->count = 0;

    list->data = malloc((byRef ? sizeof(void*) : dataType->size) * list->capacity);

    return (UTL_List*) list;
}


/** create a new list, storing objects directly, backed by linked nodes */
static UTL_List* UTL_LinkedListCreate(const UTL_TypeInfo *dataType, bool byRef) {
    UTL_LinkedList *list = (UTL_LinkedList*) malloc(sizeof(UTL_LinkedList));

    list->listType = UTL_LINKED_LIST;
    list->dataType = dataType;
    list->byRef    = byRef;

    list->count = 0;
    list->sentinel.next = &list->sentinel;
    list->sentinel.prev = &list->sentinel;

    return (UTL_List*) list;
}


/** Create a new list 
 *  @listType: what kind of list (array, linked, etc..)
 *  @dataType: what type of objects are stored
 *  @byRef: true of objects are stored by pointer, false if they are stored directly by value */
UTL_List* UTL_ListCreate(UTL_ListType listType, const UTL_TypeInfo *dataType, bool byRef) {
    switch (listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListCreate(dataType, byRef);
        case UTL_LINKED_LIST:
            return UTL_LinkedListCreate(dataType, byRef);
        default:
            return NULL;
    }
}