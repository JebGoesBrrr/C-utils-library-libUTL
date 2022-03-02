#ifndef UTL_STRING_H
#define UTL_STRING_H



/** self growing string buffer
 *  stores the string's length, how much space is currently allocated
 *  and the contents all in one contionous piece of memory */
typedef struct {
    int length;     /** length of content, excluding null terminator */
    int capacity;   /** capacity of buffer */
    char buf[];     /** buffer (null terminated c-string) */
} UTL_String;



/** create a new UTL_String and initialze with given c-string
 *  leaves the new string empty if @from is null
 *  will compute length if @length is negative
 *  the retuned string needs to be destroyed with UTL_DestroyString() */
extern UTL_String* UTL_CreateString(const char *cstr, int length);


/** free memory of a given UTL_String. returns null */
extern UTL_String* UTL_DestroyString(UTL_String *string);


/** make sure the given UTL_String has enough capacity for at least @minLength
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_ReserveString(UTL_String *string, int minLength);


/** append the contetns of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_AppendToString(UTL_String *string, const char *cstr, int length);


/** prepend the contetns of a given c-string to a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_PrependToString(UTL_String *string, const char *cstr, int length);


/** insert the contetns of a given c-string into a UTL_String
 *  does nothing if the given string is NULL
 *  will compute length if @length is negative
 *  returns the new string (possible relocation) */
extern UTL_String* UTL_InsertToString(UTL_String *string, int at, const char *cstr, int length);


/** find the first index of any of the given characters in a string, at or after @offset
 *  returns a negative value of no match is found */
extern int UTL_FindFirstOfAnyInString(UTL_String *string, const char *match, int offset);


/** find the first index of a full match of the given pattern in a string, at or after @offset
 *  returns a negative value of no match is found */
extern int UTL_FindFirstOfAllInString(UTL_String *string, const char *match, int offset);


/** find the last index of any of the given characters in a string, at or before @offset
 *  returns a negative value of no match is found */
extern int UTL_FindLastOfAnyInString(UTL_String *string, const char *match, int offset);


/** find the last index of a full match of the given pattern in a string, at or before @offset
 *  returns a negative value of no match is found */
extern int UTL_FindLastOfAllInString(UTL_String *string, const char *match, int offset);

/** create a duplicate of a given string and return it */
extern int UTL_DuplicateString(UTL_String *string, const char *match, int offset);

#endif // UTL_STRING_H
