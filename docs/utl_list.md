# UTL_List

* [Description](#description)
* [Examples](#examples)
* [Functions](#functions)

## Description

todo

&nbsp;&nbsp;Types of lists

```c
/** different types of lists  */
typedef enum {
    UTL_ARRAY_LIST,  // list backed by an array
    UTL_LINKED_LIST, // list backed by linked nodes
} UTL_ListType;
```

todo

```c
/** abstract base type for all lists */
typedef struct {
    const UTL_ListType  listType;  // array or linked
    const UTL_TypeInfo *dataType;  // type of the contained data
    const bool          byRef;     // objects stored by pointer or by value?
    const int           count;     // number of objects currently in the list
} UTL_List;
```

todo

```c
/** abstract base type for all list iterators */
typedef struct {
    UTL_List *list;     // the list into which this iterator is pointing
    void     *auxData;  // for internal use -- don't use
    int       index;    // index into the list
} UTL_ListIter;
```

## Examples

```c
// create list of int, stored by value, backed by array
UTL_List *list = UTL_ListCreate(UTL_ARRAY_LIST,  &UTL_TypeInfoInt, false);

// fill list
for (int i = 0; i < 16; i++)
    UTL_ListPushBack(list, &i);

// print list using iterator
printf("%2i [", list->count);

UTL_ListIter iter = UTL_ListGetIteratorFront(list);
while (UTL_ListIterIsValid(&iter)) {
    int i = *(int*) UTL_ListIterGet(&iter);
    printf("%2i ", i);
    UTL_ListIterNext(&iter);
}

printf("]\n");

// clean up
UTL_ListDestroy(list);
```

## Functions

### Constructor and Destructor

* [UTL_ListCreate](todo)
* [UTL_ListDestroy](todo)

### List functions

* [UTL_ListGet](todo)
* [UTL_ListGetBack](todo)
* [UTL_ListGetFront](todo)
* [UTL_ListSet](todo)
* [UTL_ListPushBack](todo)
* [UTL_ListPushFront](todo)
* [UTL_ListInsert](todo)
* [UTL_ListPopBack](todo)
* [UTL_ListPopFront](todo)
* [UTL_ListRemove](todo)
* [UTL_ListFindFirst](todo)
* [UTL_ListFindLast](todo)
* [UTL_ListContains](todo)
* [UTL_ListSort](todo)
* [UTL_ListIsSorted](todo)

### Iterator functions

* [UTL_ListGetIteratorFront](todo)
* [UTL_ListGetIteratorBack](todo)
* [UTL_ListIterHasNext](todo)
* [UTL_ListIterHasPrev](todo)
* [UTL_ListIterNext](todo)
* [UTL_ListIterPrev](todo)
* [UTL_ListIterGet](todo)
* [UTL_ListIterSet](todo)
* [UTL_ListIterInsert](todo)
* [UTL_ListIterRemove](todo)

---

<a name=""></a>

### UTL_List\* UTL_ListCreate(UTL_ListType listType, const UTL_TypeInfo \*dataType, bool byRef)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListDestroy(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void* UTL_ListGet(UTL_List *list, int at)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void* UTL_ListGetBack(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void* UTL_ListGetFront(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListSet(UTL_List *list, int at, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListPushBack(UTL_List *list, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListPushFront(UTL_List *list, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListInsert(UTL_List *list, int at, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListPopBack(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListPopFront(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListRemove(UTL_List *list, int at)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### int UTL_ListFindFirst(UTL_List *list, void *obj, int offset)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### int UTL_ListFindLast(UTL_List *list, void *obj, int offset)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### bool UTL_ListContains(UTL_List *list, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListSort(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### bool UTL_ListIsSorted(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### UTL_ListIter UTL_ListGetIteratorFront(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### UTL_ListIter UTL_ListGetIteratorBack(UTL_List *list)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### bool UTL_ListIterHasNext(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### bool UTL_ListIterHasPrev(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListIterNext(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListIterPrev(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void* UTL_ListIterGet(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListIterSet(UTL_ListIter *iter, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListIterInsert(UTL_ListIter *iter, void *obj)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name=""></a>

### void UTL_ListIterRemove(UTL_ListIter *iter)

todo

&nbsp;&nbsp;Examples:

```c
todo
```

---

[back](index.md)
