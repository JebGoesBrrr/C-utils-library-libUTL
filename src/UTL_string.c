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
UTL_String* UTL_StringCreate(const char *cstr, int length) {

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
UTL_String* UTL_StringDuplicate(const UTL_String *string) {
    return UTL_StringCreate(string->buf, string->length);
}


/** create a substring of a given string
 *  the new string contains the contents starting with @first and has length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length) {
    
    // snap @first to boundaries
    if (first < 0) first = 0;
    if (first >= string->length) return UTL_StringCreate(NULL, -1);

    // snap @length to boundaries
    int maxLength = string->length - first;
    if (length > maxLength) length = maxLength;

    return UTL_StringCreate(string->buf + first, length); 
}


/** create a substring of a given string
 *  the new string contains all but the contents starting with @first of length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
UTL_String* UTL_StringSubstringRev(const UTL_String *string, int first, int length) {
    
    // snap @first to boundaries
    if (first < 0) first = 0;
    if (first >= string->length) return UTL_StringCreate(NULL, -1);

    // snap @length to boundaries
    int maxLength = string->length - first;
    if (length > maxLength) length = maxLength;
    
    UTL_String *substring = UTL_StringCreate(string->buf, first);
    substring = UTL_StringAppend(substring, string->buf + first + length, -1);
    return substring;
}


/** free memory of a given UTL_String. returns null */
UTL_String* UTL_StringDestroy(UTL_String *string) {
    free(string);
    return NULL;
}


/** clear the contents of a string, but keep the string object allocated */
void UTL_StringClear(UTL_String *string) {
    string->length = 0;
    string->buf[0] = 0;
}


/** make sure the given UTL_String has enough capacity for at least @minLength
 *  returns the new string (possible relocation) */
UTL_String* UTL_StringReserve(UTL_String *string, int minLength) {

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
UTL_String* UTL_StringAppend(UTL_String *string, const char *cstr, int length) {
    return UTL_StringInsert(string, string->length, cstr, length); // insert behind last position
}


/** prepend the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
UTL_String* UTL_StringPrepend(UTL_String *string, const char *cstr, int length) {
    return UTL_StringInsert(string, 0, cstr, length); // insert before first position
}


/** insert the contents of a given c-string into a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
UTL_String* UTL_StringInsert(UTL_String *string, int at, const char *cstr, int length) {

    // snap insert position to boundaries
    if (at < 0) at = 0;
    if (at > string->length) at = string->length;

    // compute how many characters need to be copied
    if (cstr == NULL) length = 0; // nothing to copy
    if (length < 0) length = strlen(cstr); // compute length using null terminator
    // else: use given length

    // compute and reserve new capacity
    int newLength = string->length + length;
    string = UTL_StringReserve(string, newLength);

    // make a gap for the new content
    memmove(string->buf + at + length, string->buf + at, string->length + 1 - at);

    // copy new content into gap
    memcpy(string->buf + at, cstr, length);

    string->length = newLength;
    return string;
}


/** find the first index of any of the given characters in a string, at or after @offset
 *  returns a negative value if no match is found */
int UTL_StringFindFirstOfAny(const UTL_String *string, const char *match, int offset) {
    for (int i = offset < 0 ? 0 : offset; i < string->length; i++)
        if (strchr(match, string->buf[i]))
            return i;
    return -1;
}


/** find the first index of a full match of the given pattern in a string, at or after @offset
 *  returns a negative value if no match is found */
int UTL_StringFindFirstOfAll(const UTL_String *string, const char *match, int offset) {
    int lenMatch = strlen(match);
    if (lenMatch == 0) return -1;
    for (int i = offset < 0 ? 0 : offset; i < string->length - lenMatch + 1; i++)
        if (strncmp(string->buf + i, match, lenMatch) == 0)
            return i;
    return -1;
}


/** find the last index of any of the given characters in a string, at or before @offset
 *  returns a negative value if no match is found */
int UTL_StringFindLastOfAny(const UTL_String *string, const char *match, int offset) {
    for (int i = offset >= string->length ? string->length - 1 : offset; i >= 0; i--)
        if (strchr(match, string->buf[i]))
            return i;
    return -1;
}


/** find the last index of a full match of the given pattern in a string, at or before @offset
 *  returns a negative value if no match is found */
int UTL_StringFindLastOfAll(const UTL_String *string, const char *match, int offset) {
    int lenMatch = strlen(match);
    if (lenMatch == 0) return -1;
    for (int i = offset > string->length - lenMatch ? string->length - lenMatch : offset; i >= 0; i--)
        if (strncmp(string->buf + i, match, lenMatch) == 0)
            return i;
    return -1;
}


/** remove parts of a string
 *  remove everything starting at @first and of length @length */
void UTL_StringRemoveAt(UTL_String *string, int first, int length) {

    // snap @first to boundaries
    if (first < 0) first = 0;
    if (first >= string->length) return; // nothing to delete

    // snap @length to boundaries
    int maxLength = string->length - first;
    if (length > maxLength) length = maxLength;

    memmove(string->buf + first, string->buf + first + length, string->length + 2 - first - length);
    string->length -= length;
}


/** remove parts of a string
 *  remove everything except content starting at @first and of length @length */
void UTL_StringRemoveAtRev(UTL_String *string, int first, int length) {
    
    // snap @first to boundaries
    if (first < 0) first = 0;
    if (first >= string->length) {
        // nothing to keep
        string->length = 0;
        string->buf[0] = 0;
        return;
    }

    // snap @length to boundaries
    int maxLength = string->length - first;
    if (length > maxLength) length = maxLength;

    // copy area to keep into beginning of string
    memmove(string->buf, string->buf + first, length);
    string->buf[length] = 0;
    string->length = length;
}


/** remove all occurences of any of the characters in @match from @string
 *  returnes the number of characters that where removed */
int UTL_StringRemoveAny(UTL_String *string, const char *match) {
    int i = UTL_StringFindFirstOfAny(string, match, 0);
    while (i >= 0) {
        UTL_StringRemoveAt(string, i, 1);
        i = UTL_StringFindFirstOfAny(string, match, i);
    }
    return 0;
}


/** remove all occurences of full matches of the characters in @match from @string
 *  returnes the number of characters that where removed */
int UTL_StringRemoveAll(UTL_String *string, const char *match) {
    // TODO
    (void) string;
    (void) match;
    return 0;
}


/** split @string into newly created substrings at all occurences of any character from @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returnes the number of created substrings */
int UTL_StringSplitOnAny(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux) {

    int numSubstrings = 0;

    int lastMatch = -1;
    while (true) {
        int newMatch = UTL_StringFindFirstOfAny(string, match, lastMatch+1);
        int subLength = newMatch >= 0 ? newMatch - (lastMatch+1) : string->length - (lastMatch+1);

        if (subLength > 0 || includeEmpty) {
            UTL_String *s = UTL_StringSubstring(string, lastMatch+1, subLength);
            if (cb) cb(aux, s);
            numSubstrings++;
        }

        lastMatch = newMatch;
        if (newMatch < 0) break;
    }

    return numSubstrings;
}


/** split @string into newly created substrings at all occurences of a full match of @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returns the number of created substrings */
int UTL_StringSplitOnAll(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux) {
    int numSubstrings = 0;
    int matchLength = strlen(match);
    int lastMatch = -matchLength; // exploit, that negative offsets are shifted to begin of string

    while (true) {
        int newMatch = UTL_StringFindFirstOfAll(string, match, lastMatch + 1);
        int subLength = newMatch > 0 ? ((newMatch - lastMatch) > matchLength ?newMatch - (lastMatch + matchLength) : 0) : string->length - (lastMatch + matchLength);

        if (subLength > 0 || includeEmpty) {
            UTL_String *s = UTL_StringSubstring(string, lastMatch + matchLength, subLength);
            if (cb) cb(aux, s);
            numSubstrings++;
        }

        lastMatch = newMatch;
        if (newMatch < 0) break;
    }

    return numSubstrings;
}


/** trim @string. cut off any occurence of any character in @match from the beginning the end
 *  returns the number of characters removed */
int UTL_StringTrim(UTL_String *string, const char *match) {
    int first = 0;
    while (first < string->length && strchr(match, string->buf[first])) first++;

    int last = string->length - 1;
    while (last >= 0 && strchr(match, string->buf[last])) last--;

    int oldLength = string->length;
    UTL_StringRemoveAtRev(string, first, last - first + 1);
    return oldLength - string->length;
}


/** group consecuitive occurences of any characters in @match into a single occurence.
 *  if @replace is true, the single occurence will always be the first character in @match
 *  returns the number of characters removed */
int UTL_StringGroup(UTL_String *string, const char *match, bool repalce) {

    if (string->length == 0 || !*match)
        return 0;

    int oldLength = string->length;

    char *readPtr = string->buf;
    char *writePtr = string->buf;
    bool inGroup = false;

    while (*readPtr) {
        if (!inGroup) {
            if (strchr(match, *readPtr)) {
                inGroup = true;
                *writePtr = repalce ? *match : *readPtr;
            }
            else {
                *writePtr = *readPtr;
            }
            writePtr++;
            readPtr++;
        }
        else {
            if (!strchr(match, *readPtr)) {
                inGroup = false;
                *writePtr = *readPtr;
                writePtr++;
            }
            readPtr++;
        }
    }

    *writePtr = 0;
    string->length = writePtr - string->buf;
    return oldLength - string->length;
}

/** concatenates a string to another
 *  will compute length if @length is negative
 *  returns the new string (possible relocation)
 *  returns the string that results from concatenating @string2 to @string1 */
UTL_String* UTL_StringConcatenate(UTL_String *string1, UTL_String *string2) {
    // TODO
    (void) string1;
    (void) string2;
    return (UTL_String*) NULL;
}

/** reverses a given string @string */
void UTL_StringReverse(UTL_String *string){
    // TODO
    (void) string;
}

/** converts a given string @string to uppercase */
void UTL_StringLower(UTL_String *string){
    // TODO
    (void) string;
}

/** converts a given string @string to uppercase */
void UTL_StringUpper(UTL_String *string){
    // TODO
    (void) string;
}

/** replaces every occurence of a found @match in @string */
void UTL_StringFindAndReplace(UTL_String *string, const char *match){
    // TODO
    (void) string;
    (void) match;
}