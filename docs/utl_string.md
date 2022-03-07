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
* [UTL_StringSubstringRev](#stringsubstringrev)

---

<div name="stringcreate"></div>

### `UTL_String* UTL_StringCreate(const char *cstr, int length)`

Creates and returns a new `UTL_String` and initializes it with the given C-string `cstr`.
If `cstr` is `null` the new string will be empty. If `length` is negative, this function will compute `cstr`'s length (and hence expects it to be null-terminated).
Otherwise `cstr` does not need to be null-terminated and `length` is used.
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:
```c
UTL_String *s1 = UTL_StringCreate(null, -1);          // create empty
UTL_String *s2 = UTL_StringCreate("Hello World", -1); // create with "Hello World"
UTL_String *s3 = UTL_StringCreate("Hello World", 5);  // create with "Hello"
```

---

<div name="stringduplicate"></div>

### `UTL_String* UTL_StringDuplicate(const UTL_String *string)`

Creates and returns a new `UTL_String` that will have the same contents as the given `string`.
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:
```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1);
UTL_String *s2 = UTL_StringDuplicate(s1);
```

---

<div name="stringsubstring"></div>

### `UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length)`

Creates and returns a new `UTL_String` that will contain a sub-string of the given `string` (starting with the character at index `first` and having length `length`).


&nbsp;&nbsp;Examples:
```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1);
UTL_String *s2 = UTL_StringSubstring(s1, 0, 5); // "Hello"
UTL_String *s3 = UTL_StringSubstring(s1, 6, 5); // "World"
```

---

<div name="stringsubstringrev"></div>

### `UTL_String* UTL_StringSubstringRev(const UTL_String *string, int first, int length)`

Creates and returns a new `UTL_String` that will contain a sub-string of the given `string` (excluding everything starting with the character at index `first` and having length `length`).
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:
```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1;
UTL_String *s2 = UTL_StringSubstringRev(s1, 0, 6); // "World"
UTL_String *s3 = UTL_StringSubstringRev(s1, 5, 6); // "Hello"
```

---

[back](index.md)
