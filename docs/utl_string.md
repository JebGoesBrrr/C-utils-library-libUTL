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
* [UTL_StringDestroy](#stringdestroy)
* [UTL_StringClear](#stringclear)
* [UTL_StringReserve](#stringreserve)
* [UTL_StringAppend](#stringappend)
* [UTL_StringPrepend](#stringprepend)
* [UTL_StringInsert](#stringinsert)
* [UTL_StringFindFirstOfAny](#stringfindfirstofany)
* [UTL_StringFindFirstOfAll](#stringfindfirstofall)
* [UTL_StringFindLastOfAny](#stringlastofany)
* [UTL_StringFindLastOfAll](#stringlastofall)
* [UTL_StringRemoveAt](#stringremoveat)
* [UTL_StringRemoveAtRev](#stringremoveatrev)
* [UTL_StringRemoveAny](#stringremoveany)
* [UTL_StringRemoveAll](#stringremoveall)
* [UTL_StringSplitOnAny](#stringsplitonany)
* [UTL_StringSplitOnAll](#stringsplitonall)
* [UTL_StringTrim](#stringtrim)
* [UTL_StringGroup](#stringgroup)

---

<a name="stringcreate"></a>

### UTL_String* UTL_StringCreate(const char *cstr, int length)

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

<a name="stringduplicate"></a>

### UTL_String* UTL_StringDuplicate(const UTL_String *string)

Creates and returns a new `UTL_String` that will have the same contents as the given `string`.
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:

```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1);
UTL_String *s2 = UTL_StringDuplicate(s1);
```

---

<a name="stringsubstring"></a>

### UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length)

Creates and returns a new `UTL_String` that will contain a sub-string of the given `string` (starting with the character at index `first` and having length `length`).
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:

```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1);
UTL_String *s2 = UTL_StringSubstring(s1, 0, 5); // "Hello"
UTL_String *s3 = UTL_StringSubstring(s1, 6, 5); // "World"
```

---

<a name="stringsubstringrev"></a>

### UTL_String* UTL_StringSubstringRev(const UTL_String *string, int first, int length)

Creates and returns a new `UTL_String` that will contain a sub-string of the given `string` (excluding everything starting with the character at index `first` and having length `length`).
The returned string objects needs to be destroyed with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:

```c
UTL_String *s1 = UTL_StringCreate("Hello World", -1;
UTL_String *s2 = UTL_StringSubstringRev(s1, 0, 6); // "World"
UTL_String *s3 = UTL_StringSubstringRev(s1, 5, 6); // "Hello"
```

---

<a name="stringdestroy"></a>

### UTL_String* UTL_StringDestroy(UTL_String *string)

Destroy a string and free it's memory. Returns `null`.

&nbsp;&nbsp;Examples:

```c
UTL_String *s = UTL_StringCreate("Hello World, -1"); // allocates a string
s = UTL_StringDestroy(s);                            // frees the string (s is now null)
```

---

<a name="stringclear"></a>

### void UTL_StringClear(UTL_String *string)

Clear a string's content to be the empty string `""`. The string object itself stays allocated and must still be destroyes with `UTL_StringDestroy()`.

&nbsp;&nbsp;Examples:

```c
UTL_String *s = UTL_StringCreate("Hello World", -1); // s->buf == "Hello World"
UTL_StringClear(s);                                  // s->buf == ""
```

---

<a name="stringreserve"></a>

### UTL_String* UTL_StringReserve(UTL_String *string, int minLength)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringappend"></a>

### UTL_String* UTL_StringAppend(UTL_String *string, const char *cstr, int length)

Append the content of the given c-string to `string`.
If `cstr` is `null`, the strings is unchanged.
If `length` is negative `cstr`'s length is computed (and `cstr` must be null-terminated).
Else `length` is used and `cstr` does not need to be null-terminated.
Since this function may relocate the string, `string` becomes invalid and a new pointer to the string is returned.

&nbsp;&nbsp;Examples:

```c
UTL_String *s = UTL_StringCreate("Hello", -1);
s = UTL_StringAppend(s, " ", -1);
s = UTL_StringAppend(s, "World", -1); // s->buf == "Hello World"
```

---

<a name="stringprepend"></a>

### UTL_String* UTL_StringPrepend(UTL_String *string, const char *cstr, int length)

Prepend the content of the given c-string to `string`.
If `cstr` is `null`, the strings is unchanged.
If `length` is negative `cstr`'s length is computed (and `cstr` must be null-terminated).
Else `length` is used and `cstr` does not need to be null-terminated.
Since this function may relocate the string, `string` becomes invalid and a new pointer to the string is returned.

&nbsp;&nbsp;Examples:

```c
UTL_String *s = UTL_StringCreate("World", -1);
s = UTL_StringPrepend(s, " ", -1);
s = UTL_StringPrepend(s, "Hello", -1); // s->buf == "Hello World"
```

---

<a name="stringinsert"></a>

### UTL_String* UTL_StringInsert(UTL_String *string, int at, const char *cstr, int length)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringfindfirstofany"></a>

### int UTL_StringFindFirstOfAny(const UTL_String *string, const char *match, int offset)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringfindfirstofall"></a>

### int UTL_StringFindFirstOfAll(const UTL_String *string, const char *match, int offset)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringfindlastofany"></a>

### int UTL_StringFindLastOfAny(const UTL_String *string, const char *match, int offset)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringfindlastofall"></a>

### int UTL_StringFindLastOfAll(const UTL_String *string, const char *match, int offset)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringremoveat"></a>

### void UTL_StringRemoveAt(UTL_String *string, int first, int length)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringremoveatrev"></a>

### void UTL_StringRemoveAtRev(UTL_String *string, int first, int length)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringremoveany"></a>

### int UTL_StringRemoveAny(UTL_String *string, const char *match)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringremoveall"></a>

### int UTL_StringRemoveAll(UTL_String *string, const char *match)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringsplitonany"></a>

### int UTL_StringSplitOnAny(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringsplitonall"></a>

### int UTL_StringSplitOnAll(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringtrim"></a>

### int UTL_StringTrim(UTL_String *string, const char *match)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---

<a name="stringgroup"></a>

### int UTL_StringGroup(UTL_String *string, const char *match, bool repalce)

TODO

&nbsp;&nbsp;Examples:

```c
todo
```

---
[back](index.md)
