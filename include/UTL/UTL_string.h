#ifndef UTL_STRING_H
#define UTL_STRING_H



/** self growing string buffer
 *  stores the string's length, how much space is currently allocated
 *  and the contents all in one continuous piece of memory */
typedef struct {
    int length;     /** length of content, excluding null terminator */
    int capacity;   /** capacity of buffer */
    char buf[];     /** buffer (null terminated c-string) */
} UTL_String;


extern int UTL_StringCompare(const UTL_String *string1, const UTL_String *string2);

extern unsigned UTL_CstringHash(const char *cstring);

extern unsigned UTL_StringHash(const UTL_String *string);

extern const UTL_TypeInfo UTL_TypeInfoString;


/** create a new UTL_String and initialze with given c-string
 *  leaves the new string empty if @from is null
 *  will compute length if @length is negative
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_StringCreate(const char *cstr, int length);


/** create a duplicate of a given string
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_StringDuplicate(const UTL_String *string);


/** create a substring of a given string
 *  the new string contains the contents starting with @first and has length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_StringSubstring(const UTL_String *string, int first, int length);


/** create a substring of a given string
 *  the new string contains all but the contents starting with @first of length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_StringSubstringRev(const UTL_String *string, int first, int length);


/** free memory of a given UTL_String. returns null */
extern UTL_String* UTL_StringDestroy(UTL_String *string);


/** clear the contents of a string, but keep the string object allocated */
extern void UTL_StringClear(UTL_String *string);


/** make sure the given UTL_String has enough capacity for at least @minLength
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_StringReserve(UTL_String *string, int minLength);


/** append the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_StringAppend(UTL_String *string, const char *cstr, int length);


/** prepend the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_StringPrepend(UTL_String *string, const char *cstr, int length);


/** insert the contents of a given c-string into a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_StringInsert(UTL_String *string, int at, const char *cstr, int length);


/** append a string to another
 *  returns the new string (possible relocation, see UTL_StringAppend)
 *  same behavior as UTL_StringAppend(string, other->buf, other->length) */
extern UTL_String* UTL_StringConcat(UTL_String *string, const UTL_String *other);


/** find the first index of any of the given characters in a string, at or after @offset
 *  returns a negative value if no match is found */
extern int UTL_StringFindFirstOfAny(const UTL_String *string, const char *match, int offset);


/** find the first index of a full match of the given pattern in a string, at or after @offset
 *  returns a negative value if no match is found */
extern int UTL_StringFindFirstOfAll(const UTL_String *string, const char *match, int offset);


/** find the last index of any of the given characters in a string, at or before @offset
 *  returns a negative value if no match is found */
extern int UTL_StringFindLastOfAny(const UTL_String *string, const char *match, int offset);


/** find the last index of a full match of the given pattern in a string, at or before @offset
 *  returns a negative value if no match is found */
extern int UTL_StringFindLastOfAll(const UTL_String *string, const char *match, int offset);


/** remove parts of a string
 *  remove everything starting at @first and of length @length */
extern void UTL_StringRemoveAt(UTL_String *string, int first, int length);


/** remove parts of a string
 *  remove everything except content starting at @first and of length @length */
extern void UTL_StringRemoveAtRev(UTL_String *string, int first, int length);


/** remove all occurences of any of the characters in @match from @string
 *  returnes the number of characters that where removed */
extern int UTL_StringRemoveAny(UTL_String *string, const char *match);


/** remove all occurences of full matches of the characters in @match from @string
 *  returnes the number of characters that where removed */
extern int UTL_StringRemoveAll(UTL_String *string, const char *match);


/** split @string into newly created substrings at all occurences of any character from @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returnes the number of created substrings */
extern int UTL_StringSplitOnAny(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux);


/** split @string into newly created substrings at all occurences of a full match of @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returnes the number of created substrings */
extern int UTL_StringSplitOnAll(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux);


/** trim @string. cut off any occurence of any character in @match from the beginning the end
 *  returns the number of characters removed */
extern int UTL_StringTrim(UTL_String *string, const char *match);


/** group consecuitive occurences of any characters in @match into a single occurence.
 *  if @replace is true, the single occurence will always be the first character in @match
 *  returns the number of characters removed */
extern int UTL_StringGroup(UTL_String *string, const char *match, bool repalce);


/** reverses a given string @string */
extern void UTL_StringReverse(UTL_String *string);

/** converts a given string @string to lowercase */
extern void UTL_StringToLower(UTL_String *string);

/** converts a given string @string to uppercase */
extern void UTL_StringToUpper(UTL_String *string);

/** check if a given string @string is lowercase */
extern bool UTL_StringIsLower(const UTL_String *string);

/** check if a given string @string is uppercase */
extern bool UTL_StringIsUpper(const UTL_String *string);

/** replaces every occurence of a found @match in @string with what? */
extern void UTL_StringFindAndReplace(UTL_String *string, const char *match);

#endif // UTL_STRING_H
