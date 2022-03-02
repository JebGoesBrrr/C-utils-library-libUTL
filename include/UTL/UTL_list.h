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
    UTL_ListType listType;  // type of this list (array vs linked, objects vs pointers)
    UTL_TypeInfo *dataType; // type of the contained data
    int count;              // number of objects currently in the list
} UTL_List;



/** list of objects, backed by an array */
typedef struct {
    UTL_ListType listType;  // see UTL_List
    UTL_TypeInfo *dataType; // see UTL_List
    int count;              // see UTL_List

    int capacity;   // maximum number of objects that could be stored in this list without relocation
    void *data;     // array containing all objects
} UTL_ArrayList;



/** list of pointers, backed by an array */
typedef struct {
    UTL_ListType listType;  // see UTL_List
    UTL_TypeInfo *dataType; // see UTL_List
    int count;              // see UTL_List

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
    UTL_ListType listType;  // see UTL_List
    UTL_TypeInfo *dataType; // see UTL_List
    int count;              // see UTL_List

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
    UTL_ListType listType;  // see UTL_List
    UTL_TypeInfo *dataType; // see UTL_List
    int count;              // see UTL_List

    UTL_LinkedListNodeP sentinel; // first and last node of the list
} UTL_LinkedListP;



#endif // UTL_LIST_H