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

<div name="stringcreate"></div>

### `UTL_String* UTL_StringCreate(const char *cstr, int length)`

>Creates and returns a new `UTL_String` and initializes it with the given C-string `cstr`.
If `cstr` is `null` the new string will be empty.
If `length` is negative, this function will compute `cstr`'s length (and hence expects it to be null-terminated).
Otherwise `cstr` does not need to be null-terminated and `length` is used.
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

Examples:
```c
UTL_String *s1 = UTL_StringCreate(null, -1);          // create empty
UTL_String *s2 = UTL_StringCreate("Hello World", -1); // create with "Hello World"
UTL_String *s3 = UTL_StringCreate("Hello World", 5);  // create with "Hello"
```

<div name="stringduplicate">

### `UTL_String* UTL_StringDuplicate(const UTL_String *string)`

todo

</div>

<div name="stringsubstring">

### `UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length)`

todo

</div>

---

[back to main documentation](readme.md) <br>
[back to utl documentation](utl.md)
