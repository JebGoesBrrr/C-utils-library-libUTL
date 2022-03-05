# UTL_String

## Description

```c
typedef struct {
    int  length;     /** length of content, excluding null terminator */
    int  capacity;   /** capacity of buffer */
    char buf[];      /** buffer (null terminated c-string) */
} UTL_String;
```

## Functions

* [UTL_StringCreate](#stringcreate)
* [UTL_StringDuplicate](#stringduplicate)
* [UTL_StringSubstring](#stringsubstring)

---

<div name="stringcreate">

`UTL_String* UTL_StringCreate(const char *cstr, int length)`

todo

</div>

<div name="stringduplicate">

`UTL_String* UTL_StringDuplicate(const UTL_String *string)`

todo

</div>

<div name="stringsubstring">

`UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length)`

todo

</div>

---

[back to main documentation](readme.md) <br>
[back to utl documentation](utl.md)
