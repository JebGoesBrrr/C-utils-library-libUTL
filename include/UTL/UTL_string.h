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



/** create a new UTL_String and initialze with given c-string
 *  leaves the new string empty if @from is null
 *  will compute length if @length is negative
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_CreateString(const char *cstr, int length);


/** create a duplicate of a given string
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_DuplicateString(const UTL_String *string);


/** create a substring of a given string
 *  the new string contains the contents starting with @first and has length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_Substring(const UTL_String *string, int first, int length);


/** create a substring of a given string
 *  the new string contains all but the contents starting with @first of length @length
 *  the returned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_SubstringRev(const UTL_String *string, int first, int length);


/** free memory of a given UTL_String. returns null */
extern UTL_String* UTL_DestroyString(UTL_String *string);


/** make sure the given UTL_String has enough capacity for at least @minLength
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_ReserveString(UTL_String *string, int minLength);


/** append the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr, int length);


/** prepend the contents of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_PrependToString(UTL_String *string, const char *cstr, int length);


/** insert the contents of a given c-string into a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_InsertToString(UTL_String *string, int at, const char *cstr, int length);


/** find the first index of any of the given characters in a string, at or after @offset
 *  returns a negative value if no match is found */
extern int UTL_FindFirstOfAnyInString(const UTL_String *string, const char *match, int offset);


/** find the first index of a full match of the given pattern in a string, at or after @offset
 *  returns a negative value if no match is found */
extern int UTL_FindFirstOfAllInString(const UTL_String *string, const char *match, int offset);


/** find the last index of any of the given characters in a string, at or before @offset
 *  returns a negative value if no match is found */
extern int UTL_FindLastOfAnyInString(const UTL_String *string, const char *match, int offset);


/** find the last index of a full match of the given pattern in a string, at or before @offset
 *  returns a negative value if no match is found */
extern int UTL_FindLastOfAllInString(const UTL_String *string, const char *match, int offset);


/** remove parts of a string
 *  remove everything starting at @first and of length @length */
extern void UTL_RemoveFromString(UTL_String *string, int first, int length);


/** remove parts of a string
 *  remove everything except content starting at @first and of length @length */
extern void UTL_RemoveFromStringRev(UTL_String *string, int first, int length);


/** remove all occurences of any of the characters in @match from @string
 *  returnes the number of characters that where removed */
extern int UTL_RemoveAnyFromString(UTL_String *string, const char *match);


/** remove all occurences of full matches of the characters in @match from @string
 *  returnes the number of characters that where removed */
extern int UTL_RemoveAllFromString(UTL_String *string, const char *match);


/** split @string into newly created substrings at all occurences of any character from @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returnes the number of created substrings */
extern int UTL_SplitStringAtAny(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux);


/** split @string into newly created substrings at all occurences of a full match of @match
 *  if non null, the callback @cb will be called on each created substring: cb(aux, substr);
 *  if @includeEmpty is false, empty substrings are ignored
 *  returnes the number of created substrings */
extern int UTL_SplitStringAtAll(const UTL_String *string, const char *match, bool includeEmpty, void (*cb)(void*,void*), void *aux);


/** trim @string. cut off any occurence of any character in @match from the beginning the end
 *  returns the number of characters removed */
extern int UTL_TrimString(UTL_String *string, const char *match);


/** group consecuitive occurences of any characters in @match into a single occurence.
 *  if @replace is true, the single occurence will always be the first character in @match
 *  returns the number of characters removed */
extern int UTL_GroupString(UTL_String *string, const char *match, bool repalce);


#endif // UTL_STRING_H
