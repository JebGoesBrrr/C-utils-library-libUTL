# Utils Library (UTL)

---

* [Description](#description)
* [Usage](#usage)
* [Generic Containers](#generic-containers)
* [Documentation by Topic](#documentation-by-topic)

---

## Description

Todo

---

## Usage

todo

```c
#include <UTL/UTL.h>
```

todo

```txt
gcc <myfile.c> -L <path to filder with libUTL.dll> -lUTL
```

---

## Generic Containers

todo

```c
/** compare function type to be used with generic containers */
typedef int (UTL_CmpFunc)(const void*, const void*);

/** hash function type to be used with generic containers */
typedef unsigned (UTL_HashFunc)(const void*);

/** copy function type to be used with generic containers */
typedef void (UTL_CopyFunc)(void*, const void*);
```

todo

```c
typedef struct {
    size_t        size;     /** type's size in bytes */
    UTL_CmpFunc  *cmpFunc;  /** pointer to type's compare function */
    UTL_HashFunc *hashFunc; /** pointer to type's hash function */
    UTL_CopyFunc *copyFunc; /** pointer to type's copy function */
    const char   *name;     /** type's name */
} UTL_TypeInfo;
```

todo

```c
UTL_TypeInfo myTypeInfo = (UTL_TypeInfo) {
    .size     = sizeof(myType),
    .cmpFunc  = &myTypesCmpFunc,
    .hashFunc = &myTypesHashFunc,
    .name     = "myType"
};
```

---

## Documentation by Topic

* [String](utl_string.md)
* [Parsing](utl_parsing.md)
* [Array](utl_array.md)
* [List](utl_list.md)
* [Set](utl_set.md)
* [Map](utl_map.md)
* [Config](utl_config.md)

---