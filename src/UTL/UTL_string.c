#include "UTL/UTL.h"



/* the initial capacity of a string's buffer */
#define UTL_STRING_INITIAL_CAPACITY 64


/* one grow step for a string's capacity */
static inline int UTL_GrowCapacity(int capacity) {
    return capacity + (capacity >> 1); // capacity *= 1.5
}


/* compute what a string's capacity should be, given it's current capacity and the required minimum length */
static int UTL_ComputeNewStringCapacity(int minLength, int currentCapacity) {
    if (minLength < UTL_STRING_INITIAL_CAPACITY)
        return UTL_STRING_INITIAL_CAPACITY;

    if (currentCapacity < UTL_STRING_INITIAL_CAPACITY)
        currentCapacity = UTL_STRING_INITIAL_CAPACITY;

    while (minLength >= currentCapacity)
        currentCapacity = UTL_GrowCapacity(currentCapacity);
    
    return currentCapacity;
}


/** create a new UTL_String and initialze with given c-string
 *  leaves the new string empty if @from is null
 *  will compute length if @length is negative
 *  the returned string needs to be destroyed with UTL_DestroyString() */
UTL_String* UTL_CreateString(const char *cstr, int length) {

    // compute how many characters need to be copied on initialisation
    if (cstr == NULL) length = 0; // nothing to copy
    if (length < 0) length = strlen(cstr); // if negative -> compute length using null terminator
    // else, given length is used

    // compute initial capacity
    int capacity   = UTL_ComputeNewStringCapacity(length, 0);

    // allocate string object + buffer
    UTL_String *string = (UTL_String*) malloc(sizeof(UTL_String) + sizeof(char) * capacity);

    // init bookkeeping members
    string->capacity = capacity;
    string->length   = length;

    // init buffer
    memcpy(string->buf, cstr, sizeof(char) * length);
    string->buf[string->length] = 0;

    return string;
}


/** create a duplicate of a given string
 *  the returned string needs to be destroyed with UTL_DestroyString() */
UTL_String* UTL_DuplicateString(const UTL_String *string) {
    return UTL_CreateString(string->buf, string->length);
}


/** create a substring of a given string
 *  the new string contains the contents starting with @first and has length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
UTL_String* UTL_Substring(const UTL_String *string, int first, int length) {
    
    // snap @first to boundaries
    if (first < 0) first = 0;
    if (first >= string->length) return UTL_CreateString(NULL, -1);

    // snap @length to boundaries
    int maxLength = string->length - first;
    if (length > maxLength) length = maxLength;

    return UTL_CreateString(string->buf + first, length); 
}


/** free memory of a given UTL_String. returns null */
UTL_String* UTL_DestroyString(UTL_String *string) {
    free(string);
    return NULL;
}


/** make sure the given UTL_String has enough capacity for at least @minLength
 *  returns the new string (possible relocation) */
UTL_String* UTL_ReserveString(UTL_String *string, int minLength) {

    // do nothing if there is enough space
    if (minLength < string->capacity)
        return string;

    // else: compute required capacity and relocate string (content stays unchanged)
    string->capacity = UTL_ComputeNewStringCapacity(minLength, string->capacity);
    string = (UTL_String*) realloc(string, sizeof(UTL_String) + sizeof(char) * string->capacity);
    return string;
}


/** append the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr, int length) {
    return UTL_InsertToString(string, string->length, cstr, length); // insert behind last position
}


/** prepend the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
UTL_String* UTL_PrependToString(UTL_String *string, const char *cstr, int length) {
    return UTL_InsertToString(string, 0, cstr, length); // insert before first position
}


/** insert the contents of a given c-string into a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
UTL_String* UTL_InsertToString(UTL_String *string, int at, const char *cstr, int length) {

    // snap insert position to boundaries
    if (at < 0) at = 0;
    if (at > string->length) at = string->length;

    // compute how many characters need to be copied
    if (cstr == NULL) length = 0; // nothing to copy
    if (length < 0) length = strlen(cstr); // compute length using null terminator
    // else: use given length

    // compute and reserve new capacity
    int newLength = string->length + length;
    string = UTL_ReserveString(string, newLength);

    // make a gap for the new content
    memmove(string->buf + at + length, string->buf + at, string->length + 1 - at);

    // copy new content into gap
    memcpy(string->buf + at, cstr, length);

    string->length = newLength;
    return string;
}


/** find the first index of any of the given characters in a string, at or after @offset
 *  returns a negative value if no match is found */
int UTL_FindFirstOfAnyInString(UTL_String *string, const char *match, int offset) {
    for (int i = offset < 0 ? 0 : offset; i < string->length; i++)
        if (strchr(match, string->buf[i]))
            return i;
    return -1;
}


/** find the first index of a full match of the given pattern in a string, at or after @offset
 *  returns a negative value if no match is found */
int UTL_FindFirstOfAllInString(UTL_String *string, const char *match, int offset) {
    int lenMatch = strlen(match);
    if (lenMatch == 0) return -1;
    for (int i = offset < 0 ? 0 : offset; i < string->length - lenMatch + 1; i++)
        if (strncmp(string->buf + i, match, lenMatch) == 0)
            return i;
    return -1;
}


/** find the last index of any of the given characters in a string, at or before @offset
 *  returns a negative value if no match is found */
int UTL_FindLastOfAnyInString(UTL_String *string, const char *match, int offset) {
    for (int i = offset >= string->length ? string->length - 1 : offset; i >= 0; i--)
        if (strchr(match, string->buf[i]))
            return i;
    return -1;
}


/** find the last index of a full match of the given pattern in a string, at or before @offset
 *  returns a negative value if no match is found */
int UTL_FindLastOfAllInString(UTL_String *string, const char *match, int offset) {
    int lenMatch = strlen(match);
    if (lenMatch == 0) return -1;
    for (int i = offset > string->length - lenMatch ? string->length - lenMatch : offset; i >= 0; i--)
        if (strncmp(string->buf + i, match, lenMatch) == 0)
            return i;
    return -1;
}


/** remove parts of a string
 *  remove everything starting at @first and of length @length */
void UTL_RemoveFromString(UTL_String *string, int first, int length) {
    // TODO
}


/** remove parts of a string
 *  remove everything except content starting at @first and of length @length */
void UTL_RemoveFromStringRev(UTL_String *string, int first, int length) {
    // TODO
}