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

#define UTL_ListObj2Pos(list, obj) (list->byRef ? &(obj) : (obj))

#define UTL_ListPos2Obj(list, obj) (list->byRef ? *((void**)(obj)) : (void*)(obj))


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
    return UTL_ListPos2Obj(list, pos);
}


void* UTL_LinkedListGet(UTL_LinkedList *list, int at) {

    if (at >= list->count) return NULL;

    UTL_LinkedListNode *node = list->sentinel.next;
    while (at--) node = node->next;

    return UTL_ListPos2Obj(list, node->obj);
}

void* UTL_ArrayListGetBack(UTL_ArrayList *list) {
    if (list->count == 0) return NULL;

    uint8_t *pos = list->data + UTL_ListDataSize(list) * list->count - 1;
    return UTL_ListPos2Obj(list, pos);
}

void* UTL_LinkedListGetBack(UTL_LinkedList *list) {
    if (list->count == 0) return NULL;

    return UTL_ListPos2Obj(list, list->sentinel.prev->obj);
}

void* UTL_ArrayListGetFront(UTL_ArrayList *list) {
    if (list->count == 0) return NULL;

    return UTL_ListPos2Obj(list, list->data);
}

void* UTL_LinkedListGetFront(UTL_LinkedList *list) {
    if (list->count == 0) return NULL;

    return UTL_ListPos2Obj(list, list->sentinel.next->obj);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void UTL_ArrayListPushBack(UTL_ArrayList *list, void *obj) {

    if (list->count == list->capacity) {
        list->capacity += list->capacity >> 1;
        list->data = realloc(list->data, UTL_ListDataSize(list) * list->capacity);
    }

    uint8_t *pos = list->data + UTL_ListDataSize(list) * list->count;
    memcpy(pos, UTL_ListObj2Pos(list, obj), UTL_ListDataSize(list));
    
    list->count++;
}


static void UTL_LinkedListPushBack(UTL_LinkedList *list, void *obj) {

    UTL_LinkedListNode *node = malloc(sizeof(UTL_LinkedListNode) + UTL_ListDataSize(list));
    memcpy(node->obj, UTL_ListObj2Pos(list, obj), UTL_ListDataSize(list));

    node->next = &list->sentinel;
    node->prev = list->sentinel.prev;

    list->sentinel.prev->next = node;
    list->sentinel.prev = node;

    list->count++;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static UTL_ListIter UTL_ArrayListGetIteratorFront(UTL_ArrayList *list) {
    return (UTL_ListIter) {
        .list    = (UTL_List*) list,
        .auxData = NULL,
        .index   = 0
    };
}


static UTL_ListIter UTL_ArrayListGetIteratorBack(UTL_ArrayList *list) {
    return (UTL_ListIter) {
        .list    = (UTL_List*) list,
        .auxData = NULL,
        .index   = list->count - 1
    };
}


static UTL_ListIter UTL_LinkedListGetIteratorFront(UTL_LinkedList *list) {
    return (UTL_ListIter) {
        .list    = (UTL_List*) list,
        .auxData = list->sentinel.next,
        .index   = 0
    };

}


static UTL_ListIter UTL_LinkedListGetIteratorBack(UTL_LinkedList *list) {
    return (UTL_ListIter) {
        .list    = (UTL_List*) list,
        .auxData = list->sentinel.prev,
        .index   = list->count - 1
    };
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

/** get the last objet from a list */
void* UTL_ListGetBack(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListGetBack((UTL_ArrayList*) list);
        case UTL_LINKED_LIST:
            return UTL_LinkedListGetBack((UTL_LinkedList*) list);
        default:
            return NULL;
    }
}


/** get the first object from a list */
void* UTL_ListGetFront(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListGetFront((UTL_ArrayList*) list);
        case UTL_LINKED_LIST:
            return UTL_LinkedListGetFront((UTL_LinkedList*) list);
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


void* UTL_ListFold(UTL_List *list, void* (*foldFunc)(void*,void*), void *state) {
    UTL_ListIter iter = UTL_ListGetIteratorFront(list);

    while (UTL_ListIterIsValid(&iter)) {
        state = foldFunc(state, UTL_ListIterGet(&iter));
        UTL_ListIterNext(&iter);
    }

    return state;
}


/** get an iterator to the beginning of the list */
UTL_ListIter UTL_ListGetIteratorFront(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListGetIteratorFront((UTL_ArrayList*) list);
        case UTL_LINKED_LIST:
            return UTL_LinkedListGetIteratorFront((UTL_LinkedList*) list);
        default:
            return (UTL_ListIter) { .list = NULL, .auxData = NULL, .index = 0 };
    }
}


/** get an iterator to the end of the list */
UTL_ListIter UTL_ListGetIteratorBack(UTL_List *list) {
    switch (list->listType) {
        case UTL_ARRAY_LIST:
            return UTL_ArrayListGetIteratorBack((UTL_ArrayList*) list);
        case UTL_LINKED_LIST:
            return UTL_LinkedListGetIteratorBack((UTL_LinkedList*) list);
        default:
            return (UTL_ListIter) { .list = NULL, .auxData = NULL, .index = 0 };
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool UTL_ListIterHasNext(UTL_ListIter *iter) {
    if (!iter->list) return false;

    return iter->index < iter->list->count - 1;
}


bool UTL_ListIterHasPrev(UTL_ListIter *iter) {
    if (!iter->list) return false;

    return iter->index > 0;
}


bool UTL_ListIterIsValid(UTL_ListIter *iter) {
    return iter->list != NULL && iter->index >= 0 && iter->index < iter->list->count;
}


void UTL_ListIterNext(UTL_ListIter *iter) {
    if (!iter->list) return;

    if (UTL_ListIterIsValid(iter)) {
        iter->index++;

        switch (iter->list->listType) {
            case UTL_ARRAY_LIST:
                break;
            case UTL_LINKED_LIST:
                iter->auxData = ((UTL_LinkedListNode*)(iter->auxData))->next;
                break;
            default:
                break;
        }
    }
}


void UTL_ListIterPrev(UTL_ListIter *iter) {
    if (!iter->list) return;

    if (UTL_ListIterIsValid(iter)) {
        iter->index--;

        switch (iter->list->listType) {
            case UTL_ARRAY_LIST:
                break;
            case UTL_LINKED_LIST:
                iter->auxData = ((UTL_LinkedListNode*)(iter->auxData))->prev;
                break;
            default:
                break;
        }
    }
}


void* UTL_ListIterGet(UTL_ListIter *iter) {
    if (!iter->list) return NULL;

    uint8_t *pos;

    switch (iter->list->listType) {
        case UTL_ARRAY_LIST:
            pos = ((UTL_ArrayList*)(iter->list))->data + UTL_ListDataSize(iter->list) * iter->index;
            break;
        case UTL_LINKED_LIST:
            pos = ((UTL_LinkedListNode*)iter->auxData)->obj;
            break;
        default:
            pos = NULL;
            break;
    }

    return UTL_ListPos2Obj(iter->list, pos);
}


void UTL_ListIterSet(UTL_ListIter *iter, void *obj) {
    if (!iter->list) return;

    uint8_t *pos;

    switch (iter->list->listType) {
        case UTL_ARRAY_LIST:
            pos = ((UTL_ArrayList*)(iter->list))->data + UTL_ListDataSize(iter->list) * iter->index;
            break;
        case UTL_LINKED_LIST:
            pos = ((UTL_LinkedListNode*)iter->auxData)->obj;
            break;
        default:
            pos = NULL;
            break;
    }

    memcpy(pos, UTL_ListObj2Pos(iter->list, obj), UTL_ListDataSize(iter->list));
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

    list->data = malloc(UTL_ListDataSize(list) * list->capacity);

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